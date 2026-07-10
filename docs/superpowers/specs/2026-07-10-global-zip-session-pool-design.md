# Global ZIP Session Pool Design

## Goal

Allow concurrent reads from immutable in-memory ZIP archives without sharing a mutable `memory_file` cursor or `unzip_File` state. Bound the total number of ZIP sessions across all `folder_zip::folder` instances with a runtime-configurable process-wide limit.

## Configuration

`platform::system` exposes:

```cpp
void set_zip_file_session_maximum(::collection::count count);
::collection::count zip_file_session_maximum() const;
```

The default is 8. Values below 1 are clamped to 1. The setter is thread-safe and records the desired limit; resizing may be reconciled lazily during later session acquisition and release operations.

Increasing the limit allows later acquisitions to create more sessions. Decreasing it never interrupts an active reader. While active usage exceeds the new limit, new acquisitions wait. Excess idle sessions are closed during later pool activity.

## Session Ownership

The ZIP bytes remain in one immutable `memory_base` per opened archive. Every ZIP session has independent mutable state:

```cpp
::pointer<memory_file> m_pfile;
unzip_File m_unzipfile;
::pointer<memory_base> m_pmemory;
bool m_bInUse;
```

Each `memory_file` references the archive's immutable memory without copying it and owns only its cursor. Each `unzip_File` is opened against that cursor and is used by one lease at a time.

## Global Pool

`folder_zip` owns one process-wide pool shared by all `folder_zip::folder` instances. The configured limit bounds the total number of allocated sessions, including idle sessions.

Acquisition uses this order:

1. Reuse an idle session already bound to the requested archive memory.
2. Create a session when the pool contains fewer sessions than the current limit.
3. Rebind an idle session from another archive by closing its `unzip_File`, attaching a new `memory_file` to the requested immutable memory, and opening a new `unzip_File`.
4. Wait when every permitted session is active.

Pool acquisition and release are synchronized. Opening, locating, and reading through a leased session do not require the old folder-wide ZIP lock because no mutable cursor or unzip state is shared.

## Lease Lifetime

An RAII lease owns exclusive use of one session. It returns the session on destruction, including exception paths.

Existence and metadata queries use a temporary lease. `folder_zip::folder::get_file(path)` acquires a lease, locates and opens the requested entry, and transfers the lease into the returned `folder_zip::file`. The file retains the lease until close or destruction, so subsequent reads continue using the same cursor and `unzip_File`.

The public `locate_file(path)` operation becomes an existence query and does not leave shared current-entry state behind. Session-specific file information and position move out of `folder_zip::folder` and into the lease or returned file.

## Cleanup And Errors

Creating or rebinding a session is transactional. If `memory_file` creation or `unzip_Open2` fails, the pool does not publish the unusable session and any reserved capacity is returned.

Returning a lease closes an open current entry and resets the unzip handle to a reusable state. If reset fails, the session is removed and closed instead of being returned to the idle pool.

Pool shutdown closes all idle sessions. Active leases keep their folder and archive memory alive; their sessions close when those leases are returned.

## Verification

Coverage must include:

- Independent reads from the same immutable archive through multiple concurrent sessions.
- Concurrent reads from different ZIP folder instances while respecting one global limit.
- Waiting when all sessions are leased and resuming after a release.
- Increasing and decreasing the desired limit without cancelling active reads.
- Rebinding an idle session from one archive to another.
- Automatic release after failures and exceptions.
- ASan reproduction of simultaneous resource ZIP lookup and context-menu loading without an invalid `memory_file` source pointer.
