# Global ZIP Session Pool Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the single shared in-memory ZIP cursor with a process-wide bounded pool of independent ZIP sessions whose desired maximum is configurable through `platform::system`.

**Architecture:** `platform::system` stores only the thread-safe desired maximum, keeping `acme` independent of `folder_zip`. A new `folder_zip` session component owns the global pool, independent `memory_file` cursors, `unzip_File` handles, and RAII leases. `folder_zip::folder` stores immutable archive memory, while each returned `folder_zip::file` owns one lease and all current-entry state.

**Tech Stack:** C++20, ca2 pointer/particle ownership, minizip-compatible `unzip_*` API, `std::mutex`, `std::condition_variable`, CMake/CTest, MSVC AddressSanitizer.

## Global Constraints

- The default process-wide ZIP session maximum is exactly 8.
- Values below 1 are clamped to 1.
- The maximum applies to all allocated sessions, including idle sessions, across every `folder_zip::folder` instance.
- Runtime decreases never cancel active readers; excess idle sessions are removed lazily.
- The immutable archive bytes are shared without copying, but every session has its own `memory_file` cursor and `unzip_File` state.
- A returned `folder_zip::file` retains its session lease until `close()` or destruction.
- Preserve unrelated changes in the dirty worktree, especially existing Visual Studio project configuration edits.

---

### Task 1: Add the `platform::system` configuration API

**Files:**
- Modify: `acme/platform/system.h`
- Modify: `acme/platform/system.cpp`
- Create: `folder_zip/test/system_zip_session_limit.cpp`
- Modify: `folder_zip/CMakeLists.txt`

**Interfaces:**
- Produces: `void platform::system::set_zip_file_session_maximum(::collection::count count)`
- Produces: `::collection::count platform::system::zip_file_session_maximum() const`
- Produces: an optional CTest executable named `folder_zip_system_limit_test`

- [ ] **Step 1: Add the failing configuration test and its CMake target**

Add this test source:

```cpp
#include "acme/platform/system.h"

int main()
{
   ::platform::system system;

   if (system.zip_file_session_maximum() != 8)
      return 1;

   system.set_zip_file_session_maximum(3);
   if (system.zip_file_session_maximum() != 3)
      return 2;

   system.set_zip_file_session_maximum(0);
   if (system.zip_file_session_maximum() != 1)
      return 3;

   return 0;
}
```

Under `if(BUILD_TESTING)` in `folder_zip/CMakeLists.txt`, add:

```cmake
add_executable(folder_zip_system_limit_test test/system_zip_session_limit.cpp)
target_link_libraries(folder_zip_system_limit_test PRIVATE static_acme)
add_test(NAME folder_zip_system_limit_test COMMAND folder_zip_system_limit_test)
```

- [ ] **Step 2: Build the test and verify the missing API fails compilation**

Run:

```powershell
cmake --build C:\Users\camilo\code\main\cmake-build-release --target folder_zip_system_limit_test --config Release
```

Expected: compilation fails because `zip_file_session_maximum` and `set_zip_file_session_maximum` are not members of `platform::system`.

- [ ] **Step 3: Add the thread-safe desired maximum**

Add an atomic-compatible count member initialized by the constructor and these declarations to `system.h`:

```cpp
::collection::count m_countZipFileSessionMaximum;

void set_zip_file_session_maximum(::collection::count count);
::collection::count zip_file_session_maximum() const;
```

Initialize it in `platform::system::system()`:

```cpp
m_countZipFileSessionMaximum = 8;
```

Implement access under the system synchronization object so reads and writes cannot race:

```cpp
void system::set_zip_file_session_maximum(::collection::count count)
{
   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   m_countZipFileSessionMaximum = maximum((::collection::count)1, count);
}

::collection::count system::zip_file_session_maximum() const
{
   _synchronous_lock synchronouslock(const_cast<system *>(this)->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   return m_countZipFileSessionMaximum;
}
```

- [ ] **Step 4: Rebuild and run the configuration test**

Run:

```powershell
cmake --build C:\Users\camilo\code\main\cmake-build-release --target folder_zip_system_limit_test --config Release
ctest --test-dir C:\Users\camilo\code\main\cmake-build-release -R folder_zip_system_limit_test --output-on-failure
```

Expected: build succeeds and CTest reports `100% tests passed` for this test.

- [ ] **Step 5: Commit only the configuration API and test**

```powershell
git add acme/platform/system.h acme/platform/system.cpp folder_zip/test/system_zip_session_limit.cpp folder_zip/CMakeLists.txt
git commit -m "feat: configure global zip session limit"
```

---

### Task 2: Build the global session pool and RAII lease

**Files:**
- Create: `folder_zip/session.h`
- Create: `folder_zip/session.cpp`
- Create: `folder_zip/test/session_pool.cpp`
- Modify: `folder_zip/_.h`
- Modify: `folder_zip/CMakeLists.txt`
- Modify carefully: `folder_zip/folder_zip.vcxproj`
- Modify carefully: `folder_zip/folder_zip.vcxproj.filters`

**Interfaces:**
- Consumes: a requested maximum read from `platform::system::zip_file_session_maximum()`
- Produces: `folder_zip::session_pool::reconcile(::collection::count)` and `acquire(memory_base *)` returning `::pointer<folder_zip::session_lease>`
- Produces: `folder_zip::session_lease::unzip_file()` and `folder_zip::session_lease::file_info()`
- Produces: `folder_zip::global_session_pool()`

- [ ] **Step 1: Write a failing pool test for reuse, waiting, and lazy shrink**

Create two distinct `read_only_memory` instances containing valid small ZIP archives. Exercise these observable rules in `folder_zip/test/session_pool.cpp`:

```cpp
auto ppool = create_newø<::folder_zip::session_pool>();
ppool->reconcile(2);

auto please1 = ppool->acquire(pmemoryArchive1);
auto please2 = ppool->acquire(pmemoryArchive1);
if (ppool->session_count() != 2 || ppool->active_count() != 2)
   return 1;

std::atomic_bool acquiredThird = false;
std::thread waiter([&]
{
   auto please3 = ppool->acquire(pmemoryArchive2);
   acquiredThird = true;
});

std::this_thread::sleep_for(std::chrono::milliseconds(50));
if (acquiredThird)
   return 2;

please1.release();
waiter.join();
if (!acquiredThird)
   return 3;

please2.release();
ppool->reconcile(1);
if (ppool->session_count() != 1)
   return 4;
```

Use the existing ZIP writer callbacks to build each archive in memory during test setup; do not load a filesystem ZIP.

- [ ] **Step 2: Add the source and test targets, then verify the missing types fail compilation**

Add `session.cpp` and `session.h` to both `library_source` targets. Add `folder_zip_session_pool_test` under `BUILD_TESTING`, linking `static_folder_zip`, `static_acme`, and `zlib`. Add only the two new source entries to the existing Visual Studio project and filters files.

Run:

```powershell
cmake --build C:\Users\camilo\code\main\cmake-build-release --target folder_zip_session_pool_test --config Release
```

Expected: compilation fails because `session_pool`, `session_lease`, and `global_session_pool` do not exist.

- [ ] **Step 3: Declare the session component**

Define these focused types in `session.h`:

```cpp
namespace folder_zip
{
   class session
   {
   public:
      ::pointer<memory_base> m_pmemory;
      ::pointer<memory_file> m_pfile;
      unzip_File m_unzipfile = nullptr;
      unzip__file_info m_fileinfo{};
      bool m_bCurrentFileOpen = false;
      bool m_bInUse = false;

      ~session();
      bool bind(memory_base * pmemory);
      bool reset();
      void close();
   };

   class session_pool;

   class session_lease : virtual public ::particle
   {
   public:
      ::pointer<session_pool> m_ppool;
      session * m_psession = nullptr;

      ~session_lease() override;
      unzip_File unzip_file() const;
      unzip__file_info & file_info();
      void release();
   };

   class session_pool : virtual public ::particle
   {
   public:
      std::mutex m_mutex;
      std::condition_variable m_condition;
      ::array<::pointer<session>> m_sessiona;
      ::collection::count m_countActive = 0;
      ::collection::count m_countDesiredMaximum = 8;

      ::pointer<session_lease> acquire(memory_base * pmemory);
      void release(session * psession);
      void reconcile(::collection::count maximum);
      ::collection::count session_count();
      ::collection::count active_count();
   };

   CLASS_DECL_FOLDER_ZIP ::pointer<session_pool> global_session_pool();
}
```

Forward-declare the three types in `folder_zip/_.h`.

- [ ] **Step 4: Implement transactional binding and pool acquisition**

Implement `session::bind()` by closing previous state, constructing a new `memory_file` over the supplied immutable `memory_base`, and calling `unzip_Open2`. Publish `m_pmemory`, `m_pfile`, and `m_unzipfile` only after opening succeeds.

Implement `session_pool::acquire()` under `std::unique_lock` with this exact order:

```cpp
auto maximum = m_countDesiredMaximum;
reconcile_idle_sessions_while_locked(maximum);

for (;;)
{
   if (auto psession = find_idle_bound_session_while_locked(pmemory))
      return lease_session_while_locked(psession);

   if (m_sessiona.count() < maximum)
      return create_and_lease_session_while_locked(pmemory);

   if (auto psession = find_any_idle_session_while_locked())
   {
      if (!psession->bind(pmemory))
         throw ::exception(error_failed);
      return lease_session_while_locked(psession);
   }

   m_condition.wait(lock);
   maximum = m_countDesiredMaximum;
}
```

`reconcile(maximum)` clamps and stores `m_countDesiredMaximum`, then trims idle sessions when possible. `release()` must reset the current entry, remove the session if reset fails, mark reusable sessions idle, decrement `m_countActive`, lazily trim idle sessions above `m_countDesiredMaximum`, and notify one waiter. `session_lease::~session_lease()` calls `release()` exactly once.

- [ ] **Step 5: Run the pool test under normal and ASan configurations**

Run:

```powershell
cmake --build C:\Users\camilo\code\main\cmake-build-release --target folder_zip_session_pool_test --config Release
ctest --test-dir C:\Users\camilo\code\main\cmake-build-release -R folder_zip_session_pool_test --output-on-failure
```

Then build the same source with the repository's `DebugAsan|x64` configuration and run it. Expected: both tests exit 0; ASan reports no invalid access or leak from session acquisition/rebinding.

- [ ] **Step 6: Commit the isolated pool implementation**

```powershell
git add folder_zip/session.h folder_zip/session.cpp folder_zip/_.h folder_zip/CMakeLists.txt folder_zip/folder_zip.vcxproj folder_zip/folder_zip.vcxproj.filters folder_zip/test/session_pool.cpp
git commit -m "feat: add shared zip session pool"
```

---

### Task 3: Move folder and file operations onto leases

**Files:**
- Modify: `folder_zip/folder.h`
- Modify: `folder_zip/folder.cpp`
- Modify: `folder_zip/file.h`
- Modify: `folder_zip/file.cpp`
- Create: `folder_zip/test/concurrent_folder_reads.cpp`
- Modify: `folder_zip/CMakeLists.txt`

**Interfaces:**
- Consumes: `folder_zip::global_session_pool()` and `session_pool::acquire`
- Produces: `folder::acquire_session()` that calls `global_session_pool()->reconcile(system()->zip_file_session_maximum())` before acquisition
- Produces: `folder::locate_file(session_lease *, const file::path &, bool openCurrentFile)`
- Produces: `folder_zip::file::m_psessionlease`

- [ ] **Step 1: Write a failing concurrent integration test**

Create two folders backed by separate immutable in-memory ZIP archives. Set the system maximum to 2. Start two threads, repeatedly call `get_file(path)`, read the complete payload, and compare it with the known bytes. Hold both returned files open simultaneously and verify a third acquisition waits until one file closes. Repeat with two files from the same archive and two files from different archives.

Run the test before migration. Expected: the existing implementation either serializes all reads through the folder lock or reproduces shared-current-entry corruption under concurrent access; it cannot satisfy the two simultaneous independent leases.

- [ ] **Step 2: Replace folder-wide read state with immutable archive memory**

In `folder.h`, remove read-side ownership of:

```cpp
file_pointer m_pfile;
unzip_File m_unzip_file;
unzip__file_info m_unzip_fileinfo;
```

Keep writing state separate. Add:

```cpp
::pointer<memory_base> m_pmemoryReadOnly;

::pointer<session_lease> acquire_session();
bool locate_file(session_lease * please, const ::file::path & path, bool bOpenCurrentFile);
```

In `open_for_reading`, require an in-memory file, retain `pfile->get_memory()` as immutable archive memory, and validate it once by acquiring and releasing a session.

- [ ] **Step 3: Make location operations session-local**

Refactor `locate`, `locate_file`, `locate_folder`, `has_sub_folder`, and `enumerate` to acquire a temporary lease and pass its `unzip_File` through private helpers. No helper may read or write a folder-level current entry.

`locate_file(path)` returns only existence. `get_file(path)` performs locate-and-open on one lease and transfers that lease plus copied `unzip__file_info` into the returned `folder_zip::file`.

- [ ] **Step 4: Move read, seek, size, and close onto the file lease**

In `file.h`, add:

```cpp
::pointer<session_lease> m_psessionlease;
unzip__file_info m_unzipfileinfo{};
```

Update all read-side methods to use `m_psessionlease->unzip_file()`:

```cpp
auto unzipfile = m_psessionlease ? m_psessionlease->unzip_file() : nullptr;
if (!unzipfile)
   return 0;
```

`read()` calls `unzip_ReadCurrentFile(unzipfile, ...)`. `translate()` closes/reopens the current entry on that same handle when seeking backward and consumes bytes when seeking forward. `size()` returns `m_unzipfileinfo.uncompressed_size`. `is_opened()` checks the lease and handle. `close()` closes the current entry and releases `m_psessionlease`; the destructor calls `close()`.

- [ ] **Step 5: Run concurrent folder tests and compile both library variants**

Run:

```powershell
cmake --build C:\Users\camilo\code\main\cmake-build-release --target folder_zip_session_concurrency_test folder_zip static_folder_zip --config Release
ctest --test-dir C:\Users\camilo\code\main\cmake-build-release -R "folder_zip_(session_pool|session_concurrency)_test" --output-on-failure
```

Expected: both concurrent archive scenarios pass, the third reader waits and resumes, and shared/static `folder_zip` compile successfully.

- [ ] **Step 6: Commit the folder/file migration**

```powershell
git add folder_zip/folder.h folder_zip/folder.cpp folder_zip/file.h folder_zip/file.cpp folder_zip/test/concurrent_folder_reads.cpp folder_zip/CMakeLists.txt
git commit -m "fix: isolate concurrent zip readers"
```

---

### Task 4: Verify runtime resizing and the original ASan path

**Files:**
- Modify if test coverage requires it: `folder_zip/test/concurrent_folder_reads.cpp`
- Read-only verification: `acme/filesystem/file/memory_file.h`
- Read-only verification: `acme/filesystem/filesystem/file_context.cpp`

**Interfaces:**
- Consumes: completed system limit API, global pool, and lease-based folder/file implementation
- Produces: evidence that the original `inline_byte_array_copy` failure no longer occurs

- [ ] **Step 1: Extend the concurrency test with runtime resizing**

Start with maximum 3 and hold three leases. Set the maximum to 1, release two leases, and verify no second active lease is granted while one remains. Release the final lease and verify exactly one new acquisition proceeds. Raise the maximum to 4 and verify four later acquisitions can proceed without cancelling or replacing active readers.

- [ ] **Step 2: Run the complete focused test set under ASan**

Build and run `folder_zip_system_limit_test`, `folder_zip_session_pool_test`, and `folder_zip_session_concurrency_test` using `DebugAsan|x64`. Expected: all exit 0 with no ASan diagnostic.

- [ ] **Step 3: Reproduce the musical-player context-menu path**

Run `shared_app_veriwell_musical_player.exe` under ASan, open the context menu repeatedly while other matter/resource work is active, and retain the generated ASan log. Expected: no access violation from `memory_file::read_inline`, `inline_byte_array_copy`, or the ZIP callbacks.

- [ ] **Step 4: Inspect the final scoped diff**

Run:

```powershell
git diff --check
git diff --stat HEAD~3 -- acme/platform/system.h acme/platform/system.cpp folder_zip
```

Expected: no whitespace errors introduced by this work; changes remain limited to the configuration API, ZIP session implementation, folder/file migration, project source registration, and focused tests.

- [ ] **Step 5: Commit any final test-only corrections**

If Step 1 required a test correction, stage only `folder_zip/test/concurrent_folder_reads.cpp` and commit it with:

```powershell
git add folder_zip/test/concurrent_folder_reads.cpp
git commit -m "test: cover zip session pool resizing"
```
