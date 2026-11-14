# Google Drive virtual folder

This `folder` and `fs::data` provider advertises **Google Drive** at
`google-drive://` when no installed Google Drive filesystem mirror is available.
An installed mirror keeps priority. Both providers use the single `google-drive://`
URI scheme.

The first browse uses `api_google` with the existing
`matter://api/google.network_payload` OAuth client configuration and the
`https://www.googleapis.com/auth/drive.readonly` scope. Enable the Drive API for
that Google project. Authentication uses the configured browser and a separate
profile, so cloud-platform-only tokens are not reused.

## Creating folders

`folder::create_folder(parent, name)` and `fs::data::create_folder(parent, name)`
return the provider path of the created directory. The base implementations report
unsupported operations. `fs::set` delegates to the selected filesystem; native and
mirrored filesystems use directory creation. The Google Drive implementation posts
folder metadata with the selected parent ID to Drive's `files.create` endpoint.
The returned path contains the new Drive ID, rather than its display name.

**New Folder** opens a name dialog, performs creation off the UI thread, and refreshes
the listing on success. Invalid names and API errors are reported without closing the
dialog. A failed local cache update after successful remote creation is not reported
as a failed creation, avoiding an unnecessary duplicate on retry.

Browsing retains its read-only profile. The first creation uses a separate
`profile_write` login with `https://www.googleapis.com/auth/drive`, so creating a folder
inside an arbitrary browsed parent requests additional Google consent. File uploads,
rename, deletion, and Google Workspace export remain unsupported.

Reference: [Google Drive folder creation](https://developers.google.com/workspace/drive/api/guides/folder).

## Cache locations

* `~/folder/.google_drive/profile/`: read-only login state managed by `api_google`.
* `~/folder/.google_drive/profile_write/`: login state for folder creation.
* `~/folder/.google_drive/files/<id>.json`: most recently fetched metadata.
* `~/folder/.google_drive/listings/<folder-id>/<page>.json`: listing pages.
* `~/folder/google_drive/<id>/<version>`: downloaded binary contents.

This is an on-demand cache. Listings and metadata require an online connection.
Opening a binary file checks its remote version and the cached file's length.
New downloads are checked for length and a stable remote version before caching.
Older versions remain available on disk; automatic eviction is not implemented.
The existing API transport downloads into memory, so memory use scales with file size.

URI components are Drive IDs, for example `google-drive://<folder-id>/<file-id>`.
The browser displays actual names through listing titles, including duplicate names.
Google Workspace documents and shortcuts can be listed, but opening them reports
that export or resolution is required. Uploads, rename, deletion, and export are
not implemented.

Recursive enumeration is also not implemented; the provider reports it explicitly.

Build `folder_google_drive`, `api_google`, and the affected `acme`/`apex` modules,
then rebuild/prepare `_app_core_hello_multiverse`. Its dependency list includes both
plugins. Select Google Drive in the file browser to begin login.

## Icons and cached thumbnails

`file::enumerator::get_file_image_info` is a nonvirtual adapter inherited by both
`fs::data` and `folder`. It queries the optional `file::image_info_provider`
capability through RTTI. This preserves the existing enumerator vtable, so older
providers safely return false instead of dispatching through an incompatible
virtual slot. `fs::set` routes requests to the owning provider.
It supplies folder status, the display filename (for extension icons), and an
optional existing local thumbnail path. It must not authenticate or perform
remote I/O. Returning false preserves the ordinary shell behavior.

The file manager passes its filesystem provider to the shell. Provider hints
travel with the queued image request. The shell requests generic folder/type
icons from its OS adapter and decodes cached images through ca2's image loader,
without using OS thumbnail handlers. Thumbnail cache paths participate in icon
cache identity, so a newly cached version can replace a generic icon.

Drive enumeration caches per-file metadata. Icon queries read that metadata and
only advertise an image cache file when its version and byte size match.
