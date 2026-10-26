# Bitmap source interest

On Windows, `set_bitmap_source(appid, name, bCreate)` addresses a named bitmap
under the producer application's roaming data. The producer monitors the
source-specific folder for active consumer leases. Publishing starts only while
a consumer holds a lease; this is independent of `FPS_DEBUG`.

## Consumer integration

Pass the producer app ID and source name when opening the bitmap as a consumer:

```cpp
bitmapSource->set_bitmap_source(
   "app-core/hello_multiverse", "HelloMultiverse!!", false);
```

The consumer app ID comes from the current application. The declaration path is
`roaming/<producer-app-id>/bitmap-source/<source-name>/<consumer-app-id>.txt`;
for hello_space this is
`roaming/app-core/hello_multiverse/bitmap-source/HelloMultiverse!!/app-core/hello_space.txt`.
The shared bitmap is stored as `buffer.bin` beside that declaration. The
consumer holds the declaration's lock for as long as its bitmap source is open.

## Protocol

- Each consumer opens its declaration read/write with shared read/write access.
- Hold an exclusive, nonblocking byte-range lock at offset `0x7ffffffe`, length 1.
  Locking beyond EOF does not grow the file and leaves its contents available for
  future request metadata. The initial declaration may be empty.
- The producer recursively probes that same byte range on each `.txt` declaration. Only a
  lock-conflict result establishes interest. Other open/lock failures do not.
- Files beginning with `_` are ignored. An unlocked file is inactive, regardless
  of its filename. Stale files are left in place; they need no cleanup for correct
  behavior. Neither side renames or deletes files during probing.
- Windows releases locks when handles close or processes terminate, including
  crashes. One active lease is sufficient; releasing one of multiple leases does
  not stop publishing while another remains active.
- A background worker checks every 500 ms. Start and stop detection can therefore
  take approximately one polling interval, plus filesystem/scheduling delay.
  There are no directory scans or lease probes in the per-frame copy path.
- Existing mapped buffers remain allocated when interest stops; contents stop
  updating. Readers should not interpret a successful map open as a fresh frame.

The implementation uses the existing Windows `LockFile` adapter, which supports
both recent Windows and the ReactOS/XP build without newer API imports. The POSIX
adapter currently implements byte-range locks as no-ops, so demand control is
not enabled there: publishing retains its prior behavior and acquiring this
lease reports `error_not_supported`.
