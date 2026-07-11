# Process-Wide Resource Folder Pool Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the shared resource folder and ZIP-specific session pool with a generic, process-wide bounded pool of complete `::folder` instances returned through RAII leases.

**Architecture:** `platform::system` owns a generic `resource_folder_pool` implemented in `acme`. `file_context::resource_folder()` acquires a move-only lease using stable immutable resource memory as the archive key, while folder construction and opening use only the folder factory and virtual `::folder` API. `folder_zip` returns to one cursor per folder because a leased folder has one active caller.

**Tech Stack:** C++20, ca2 `::pointer` ownership, `locking::mutex`, `locking::unique_lock`, `locking::condition_payload`, generic `::folder` factory API, MSVC AddressSanitizer, `multimedia.sln`.

## Global Constraints

- The pool must not include or cast to any `folder_zip` type.
- The configured maximum is process-wide, defaults to 8, and clamps values below 1 to 1.
- The maximum counts active and idle allocated folders across every `file_context`.
- Runtime decreases do not cancel active leases; excess idle folders are removed lazily.
- Resource bytes remain shared immutable memory and are not copied per folder.
- Every caller retains its lease for the complete folder operation.
- Preserve the user's uncommitted locking, status, memory, and Visual Studio project changes.

---

### Task 1: Add the generic resource-folder pool and lease

**Files:**
- Create: `acme/filesystem/filesystem/resource_folder_pool.h`
- Create: `acme/filesystem/filesystem/resource_folder_pool.cpp`
- Modify: `acme/platform/system.h`
- Modify: `acme/platform/system.cpp`
- Modify carefully: `acme/acme.vcxproj`
- Modify carefully: `acme/acme.vcxproj.filters`
- Modify: `acme/CMakeLists.txt`
- Create: `folder_zip/test/resource_folder_pool.cpp`
- Modify: `folder_zip/CMakeLists.txt`

**Interfaces:**
- Produces: `resource_folder_lease`, a move-only RAII wrapper with `::folder * get() const`, `operator->()`, and boolean conversion.
- Produces: `resource_folder_pool::acquire(memory_base *, const ::function<::pointer<::folder>()> &)`.
- Produces: `platform::system::resource_folder_pool()`.
- Consumes: `platform::system::zip_file_session_maximum()` as the desired generic folder maximum.

- [ ] **Step 1: Write a failing pool test**

Create a fake generic folder through a callback and acquire two leases at a maximum of two. Start a third thread and verify it cannot acquire until one lease is destroyed. Use two distinct `read_only_memory` instances to verify same-memory reuse and different-memory replacement. Reduce the maximum from three to one while three leases remain active, then verify lazy removal as leases return.

The test must use only `resource_folder_pool`, `resource_folder_lease`, `memory_base`, and `::folder`; it must contain no `folder_zip::folder` cast.

- [ ] **Step 2: Compile the test and verify the missing API fails**

Compile the source with the `DebugAsan|x64` include and link settings used by the existing focused tests.

Expected: compilation fails because `resource_folder_pool.h` and its types do not exist.

- [ ] **Step 3: Implement stable pool entries and the move-only lease**

Define a pool entry containing:

```cpp
struct resource_folder_pool_entry
{
   ::pointer<memory_base> m_pmemory;
   ::pointer<::folder> m_pfolder;
   bool m_bInUse = false;
};
```

Store entries as `std::vector<std::unique_ptr<resource_folder_pool_entry>>` so entry addresses remain stable while leases exist. The lease stores a pool pointer and entry pointer. Its destructor calls `return_to_pool()` exactly once; move operations clear the source.

- [ ] **Step 4: Implement bounded acquisition and lazy reconciliation**

Under `locking::unique_lock`, acquisition must:

```cpp
for (;;)
{
   trim_idle_entries_while_locked();

   if (auto pentry = find_idle_matching_memory_while_locked(pmemory))
      return lease_entry_while_locked(pentry);

   if (m_entrya.size() < m_countDesiredMaximum)
      return create_and_lease_while_locked(pmemory, functionCreateFolder);

   if (auto pentry = find_any_idle_entry_while_locked())
      return replace_and_lease_while_locked(pentry, pmemory, functionCreateFolder);

   m_conditionpayload.wait(lock);
}
```

Construct and open the replacement folder before publishing it into an entry. `return_to_pool()` marks the entry idle, trims excess idle entries, unlocks, and calls `notify_one()`.

- [ ] **Step 5: Add process ownership and build registration**

Add a lazily created pool member/accessor to `platform::system`. Register the two source files in CMake and the existing Visual Studio project without changing the user's locking project entries.

- [ ] **Step 6: Build and run the pool test under ASan**

Expected: waiting, reuse, replacement, lazy shrinking, and expansion all exit 0 with no ASan diagnostic.

- [ ] **Step 7: Commit only the generic pool checkpoint**

```powershell
git add acme/filesystem/filesystem/resource_folder_pool.h acme/filesystem/filesystem/resource_folder_pool.cpp acme/platform/system.h acme/platform/system.cpp acme/CMakeLists.txt acme/acme.vcxproj acme/acme.vcxproj.filters folder_zip/test/resource_folder_pool.cpp folder_zip/CMakeLists.txt
git commit -m "feat: add generic resource folder pool"
```

---

### Task 2: Return RAII folder leases from `file_context`

**Files:**
- Modify: `acme/filesystem/filesystem/file_context.h`
- Modify: `acme/filesystem/filesystem/file_context.cpp`
- Modify: `acme/filesystem/filesystem/directory_context.cpp`
- Modify: `apex/filesystem/filesystem/dir_context.cpp`
- Modify: `apex/networking/application/application.cpp`
- Create: `folder_zip/test/resource_file_context.cpp`

**Interfaces:**
- Consumes: `platform::system::resource_folder_pool()` and `resource_folder_pool::acquire()`.
- Produces: `resource_folder_lease file_context::resource_folder()`.
- Produces: stable `file_context::m_pmemoryResource` shared by every folder opened for that resource archive.

- [ ] **Step 1: Write a failing resource-file test**

Build an in-memory ZIP containing `popup_lyricimpact.menu` and `system/user/authenticate.xhtml`. Through a test `file_context`, repeatedly acquire folder leases with a process maximum of two from eight threads. Copy each requested file before releasing its lease and assert the menu never equals the authentication form.

- [ ] **Step 2: Run the test against the raw-pointer API**

Expected: compilation fails because `resource_folder()` does not return `resource_folder_lease` and cannot express lease lifetime.

- [ ] **Step 3: Cache stable immutable resource memory**

Replace `m_pfolderResource` and `m_bFolderResourceCalculated` with:

```cpp
::pointer<read_only_memory> m_pmemoryResource;
```

Initialize it once from `get_main_resource_block()` under the existing `file_context` synchronization.

- [ ] **Step 4: Implement lease-returning `resource_folder()`**

Call the system pool with `m_pmemoryResource` and a generic creation callback. The callback must:

```cpp
::pointer<::folder> pfolder;
system()->folder_factory()->constructø(m_papplication, pfolder);
pfolder->initialize(this);
auto pfile = allocateø::memory_file(m_pmemoryResource);
pfolder->open_for_reading(pfile);
return pfolder;
```

Return an empty lease on unavailable resource memory or construction/open failure.

- [ ] **Step 5: Migrate every caller to retain the lease**

Change explicit `::folder *` variables to `auto` or `resource_folder_lease`. Keep the lease in scope through `type`, `locate`, `get_file`, `enumerate`, `e_extract_all`, and complete file copying. Do not extract a raw folder pointer into a longer-lived variable.

- [ ] **Step 6: Run the resource-file contention test**

Expected: all menu and authentication payload comparisons pass under eight-thread contention with a two-folder limit and no ASan diagnostic.

- [ ] **Step 7: Commit the lease migration**

```powershell
git add acme/filesystem/filesystem/file_context.h acme/filesystem/filesystem/file_context.cpp acme/filesystem/filesystem/directory_context.cpp apex/filesystem/filesystem/dir_context.cpp apex/networking/application/application.cpp folder_zip/test/resource_file_context.cpp
git commit -m "fix: lease pooled resource folders"
```

---

### Task 3: Remove the ZIP-specific session pool

**Files:**
- Delete: `folder_zip/session.h`
- Delete: `folder_zip/session.cpp`
- Modify: `folder_zip/folder.h`
- Modify: `folder_zip/folder.cpp`
- Modify: `folder_zip/file.h`
- Modify: `folder_zip/file.cpp`
- Modify: `folder_zip/_.h`
- Modify: `folder_zip/CMakeLists.txt`
- Modify carefully: `folder_zip/folder_zip.vcxproj`
- Modify carefully: `folder_zip/folder_zip.vcxproj.filters`
- Modify: `folder_zip/test/concurrent_folder_reads.cpp`

**Interfaces:**
- Consumes: the guarantee that one `resource_folder_lease` has exclusive use of a complete folder.
- Produces: one `memory_file` cursor and `unzip_File` handle owned by each `folder_zip::folder`.

- [ ] **Step 1: Adapt the ZIP regression test to complete-folder leases**

Exercise more caller threads than the generic pool maximum. Each thread acquires a complete folder lease, locates one entry, copies it fully, and releases the lease. Verify distinct payloads for the requested menu and authentication entries.

- [ ] **Step 2: Restore one read cursor per folder**

Move read-side state back to `folder_zip::folder`:

```cpp
file_pointer m_pfile;
unzip_File m_unzip_file = nullptr;
unzip__file_info m_unzip_fileinfo{};
```

`open_for_reading()` closes any prior handle before opening the supplied generic in-memory file. The destructor closes its handle. Folder/file operations use that folder-owned handle under the folder synchronization object.

- [ ] **Step 3: Remove session types and build entries**

Delete the low-level pool and lease files, remove their declarations and project entries, and remove the old session-pool test target. Preserve the generic resource-folder pool tests.

- [ ] **Step 4: Build `folder_zip` and run all focused tests**

Build through `multimedia.sln` with `DebugAsan|x64`. Expected: generic pool, resource file-context, and concurrent payload tests all exit 0.

- [ ] **Step 5: Commit the folder simplification**

```powershell
git add -A folder_zip
git commit -m "refactor: pool complete resource folders"
```

---

### Task 4: Verify the musical-player resource path

**Files:**
- Read-only verification: `source/app-veriwell/_matter/musical_player/_std/_std/popup_lyricimpact.menu`
- Read-only verification: `source/app/_matter/main/de-de/de-de/system/user/authenticate.xhtml`

**Interfaces:**
- Consumes: completed generic pool, lease-returning `file_context`, and single-cursor folder implementation.
- Produces: evidence that distinct matter requests cannot cross-return payloads.

- [ ] **Step 1: Run each ASan test twenty times**

Run the generic pool and resource contention executables in a loop. Expected: 20/20 successful runs for each executable and no ASan report.

- [ ] **Step 2: Build the requested startup target**

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe' `
  'C:\Users\camilo\code\main\solution-windows\multimedia.sln' `
  /t:shared_app_veriwell_musical_player `
  /p:Configuration=DebugAsan /p:Platform=x64 /m:1 /nr:false /v:minimal
```

Expected: exit 0 and `time-windows/x64/DebugAsan/shared_app_veriwell_musical_player.exe` is produced.

- [ ] **Step 3: Inspect the final scoped diff**

Run `git diff --check`, confirm the worktree contains the user's pre-existing uncommitted changes, and verify this implementation changed only generic pool ownership, resource-folder callers, folder ZIP simplification, project registration, and focused tests.

- [ ] **Step 4: Report interactive verification separately**

If the musical-player context menu is not manually exercised, state that explicitly. Do not claim the interactive path was tested solely from build and unit-test evidence.
