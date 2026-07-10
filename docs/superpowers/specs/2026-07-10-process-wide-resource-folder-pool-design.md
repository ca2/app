# Process-Wide Resource Folder Pool Design

## Goal

Replace the shared `file_context::m_pfolderResource` instance and the low-level
ZIP session pool with a process-wide bounded pool of complete resource folders.
Callers receive a move-only RAII lease, so a folder cannot be handed to another
caller until the current operation finishes.

## Component Boundary

The pool belongs to `acme` and works exclusively with the generic `::folder`
interface. It must not include, cast to, or otherwise reference
`folder_zip::folder`.

Folders are created through `platform::system::folder_factory()` and bound to
resource data through the existing virtual `::folder::open_for_reading()` API.
The selected folder component may be `folder_zip`, but that is a runtime factory
decision outside the pool.

## Public API

`file_context::resource_folder()` returns a move-only
`resource_folder_lease` instead of a raw `::folder *`. The lease provides:

- `operator->()` and `get()` for generic folder access.
- Boolean testing for acquisition failure.
- Move construction and move assignment.
- Automatic return to the process-wide pool on destruction.

The existing `platform::system` setter and getter continue to configure the
process-wide maximum. Values below one remain clamped to one.

## Pool Ownership

`platform::system` owns one `resource_folder_pool`. Pool entries contain:

- A `::pointer<::folder>`.
- A strong pointer to the immutable resource memory used to open the folder.
- An in-use flag.

The pool uses `locking::mutex`, `locking::unique_lock`, and
`locking::condition_payload`. It never depends on a folder implementation's
internal synchronization.

## Acquisition

`file_context::resource_folder()` obtains the main resource block and wraps it
in shared immutable memory. It asks the system pool for a folder bound to that
memory.

While holding the pool lock, acquisition follows this order:

1. Lazily remove idle entries above the configured maximum.
2. Lease an idle entry already bound to the same memory.
3. If the allocated count is below the maximum, construct and open a new
   generic folder through the folder factory.
4. If an idle entry is bound to different memory, replace its folder with a
   newly constructed generic folder opened on the requested memory.
5. If every entry is active, wait on the condition payload and retry from the
   beginning after waking.

Folder construction and opening are transactional. A failed replacement does
not publish a partially initialized folder.

## Release And Resizing

Lease destruction marks its entry idle and wakes one waiter. Runtime decreases
never interrupt active leases. Excess idle entries are removed during
acquisition, release, or reconciliation. Runtime increases wake all waiters so
new capacity can be used immediately after the next reconciliation.

The configured maximum counts all allocated resource folders, including idle
entries, across all `file_context` instances in the process.

## Caller Migration

Every `resource_folder()` caller must retain the lease for the complete folder
operation. Existing `auto pfolder = resource_folder()` call sites continue to
use `pfolder->...`. Explicit raw pointer variables are changed to lease values.

`create_resource_file()` keeps the lease until the selected entry has been
fully copied into its independent output `memory_file`. Enumeration, type
queries, and extraction retain the lease until their operation returns.

No file obtained from a leased resource folder may outlive that lease. Current
callers already consume or copy files before returning; tests will enforce this
behavior for resource-file creation.

## Folder Implementation Simplification

After callers use complete-folder leases, each folder instance has one active
owner. `folder_zip` can return to owning one `memory_file` cursor and one
`unzip_File` handle per folder. The low-level `folder_zip::session_pool`, session
lease, and global pool are removed.

This simplification remains local to `folder_zip`; the resource pool itself has
no knowledge that the component is ZIP-backed.

## Error Handling

If resource memory is unavailable or folder construction/opening fails,
`resource_folder()` returns an empty lease. Failed entries are not added to the
pool. Existing callers retain their current not-found or empty-result behavior.

## Verification

Focused tests will cover:

- Default, clamped, decreased, and increased process-wide limits.
- Waiting when active leases reach the limit.
- Reuse for the same resource memory and replacement for different memory.
- Lazy shrinking while leases remain active.
- More reader threads than available folders repeatedly reading distinct ZIP
  entries without cross-entry payloads.
- The exact musical-player menu payload remaining distinct from the German
  authentication form payload.

The final verification target is
`shared_app_veriwell_musical_player` from `solution-windows/multimedia.sln` in
`DebugAsan|x64`.
