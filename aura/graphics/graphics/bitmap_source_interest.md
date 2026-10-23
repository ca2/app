# Bitmap source interest

On Windows, `set_bitmap_source(name)` registers the existing shared bitmap and
monitors the producer application's `appdata://bitmap_source/` folder. There is
no additional source-name directory. Publishing starts only while a consumer
holds a lease; this is independent of `FPS_DEBUG`.

## Consumer integration

Include `aura/graphics/graphics/bitmap_source_buffer.h`. Keep a
`::pointer<::graphics::bitmap_source_interest>` member in the consuming object:

```cpp
constructø(m_pBitmapInterest);
m_pBitmapInterest->acquire(
   directory()->appdata("app-core/hello_multiverse"),
   "app_graphics3d_hello_space.<unique-instance-id>.txt");
```

Replace `<unique-instance-id>` with a unique value for each simultaneous consumer
instance. Acquire before opening/reading the shared bitmap; retry opening the
bitmap if the producer is not running yet. Keep the lease alive while consuming,
and call `release_interest()` or destroy/release the object when finished. Its
context must be initialized, as `constructø` does. `acquire` throws on errors or
when another consumer already owns that exact declaration.

The app-data path must resolve to the producer's application data directory.
Do not use the consumer's own `appdata://` folder.

## Protocol

- Each consumer opens its declaration read/write with shared read/write access.
- Hold an exclusive, nonblocking byte-range lock at offset `0x7ffffffe`, length 1.
  Locking beyond EOF does not grow the file and leaves its contents available for
  future request metadata. The initial declaration may be empty.
- The producer probes that same byte range on each `.txt` declaration. Only a
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

The hello_space source is not present in this checkout; its bitmap reader still
needs to acquire this lease using the integration above.
