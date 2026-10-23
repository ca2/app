# Published alpha statistics for static pixel sources

Statistics belong to the logical `image::image` view, not its stride padding or
unused bitmap allocation. They are an explicit snapshot of its pixels.

## Usage and freshness

Images default to `pixel_usage::unknown`. Changing framebuffers should be marked
with `set_pixel_usage(image::pixel_usage::frame_buffer)`; requests to compute
static alpha statistics then return false. No draw implicitly scans pixels.

Once a still image has finished loading/drawing and its destination graphics or
writable pixel lease has ended:

```cpp
image::alpha_statistics statistics;
if (pimage->publish_static_pixels(&statistics))
{
   // Counts and conservative opaque rectangles now describe this source.
}
bool current = pimage->alpha_statistics_up_to_date();
```

`publish_static_pixels()` declares a static source and explicitly recomputes its
snapshot. It returns false when pixels are unavailable, the image is empty, or a
destination graphics/pixel lease is active. A graphics readback may be required.
`get_alpha_statistics(out)` explicitly computes a stale static snapshot or reuses
a current one. `get_cached_alpha_statistics(out)` never scans/maps; it returns
false for a stale/busy snapshot. The all-opaque GDI+ fast path uses a
nonblocking constant-size cached classification. The mixed-image path requests a
cached region list only when at least half the image is covered by retained
opaque regions and the list has at most 64 entries. That bounded snapshot copy
avoids copying large region lists on ordinary draws. Neither path scans or maps
pixels while drawing.

Graphics acquisition, mutable bitmap/GPU target access, writable maps, copies,
resize/descriptor/storage changes and destruction invalidate the cache. The last
snapshot is retained in the image, but the validity flag becomes false. Re-publish
or explicitly request statistics after completing subsequent writes.

`map(image::e_map_read_only)` preserves cache validity when the logical view is
unchanged and avoids publishing CPU modifications on unmap. It is a read-only
contract: the legacy pixmap pointer type does not enforce constness. Existing
`e_map_load` and `e_map_discard` mappings remain potentially writable. Direct raw
pixel/bitmap changes and shared backing aliases require explicit
`invalidate_alpha_statistics()` for every affected image. Do not publish shared
storage as static while another owner may mutate it. Callers must continue to
serialize image rendering/writes and lifetime according to existing image rules.

## Snapshot contents

- Transparent pixels: alpha = 0.
- Opaque pixels: alpha = 255.
- Translucent pixels: 0 < alpha < 255.
- Logical image size and origin.
- Disjoint fully opaque rectangles and their total covered pixel count.

Counting uses the pixmap's alpha-channel index and row stride. Opaque areas are
found in 32x32 tiles, including smaller edge tiles. Horizontal runs are merged,
then vertically extended when their horizontal extents match. Rectangles smaller
than 4096 pixels are discarded. Every retained rectangle is fully opaque, but the
method can miss thin/irregular opaque areas; it never classifies a mixed tile as
opaque. Transparent + opaque + translucent equals the logical pixel count.

## Candidate diagnostics

With `FPS_DEBUG`, publication reports one `Alpha optimization candidate` per
snapshot for sources of at least 65536 pixels where any of these holds:

- The entire source is opaque.
- Large opaque rectangles cover at least 50% of the source.
- At least 95% is opaque and at most 1% is translucent.

Reports include all alpha percentages, rectangle count and opaque-region
coverage. Low translucency is an optimization hint, not proof of a rendering bug:
transparent holes must still preserve the destination. No scans or repeated
warnings occur on ordinary draws. The statistics API remains available when
`FPS_DEBUG=0`.

Image metadata also retains the source URI for path-loaded images. Derived images
can identify their derivation and immediate source size while carrying the
original source URI forward. Alpha-candidate diagnostics include this provenance,
so a resized Hello Multiverse cache can be traced back to the image file that
provided its pixels.

The GDI+ backend also reports `FPS opaque-copy` aggregates about every two
seconds while `FPS_DEBUG` is enabled. Candidate draw counts show how often a
published candidate reaches the image renderer; the `skip(...)` counters
identify which fast-path requirement rejects it. Full and mixed
attempt/success/fallback counts show whether the optimization actually runs.
The report includes pixels copied without blending, time spent in the copy
calls, time spent drawing the clipped blended remainder, and total time in each
optimization path. These timings are CPU-side GDI+ call durations, not GPU or
desktop-compositor completion times.

## Current optimization

GDI+ uses `CompositingModeSourceCopy` for a current fully opaque static source of
at least 65536 pixels, only for an unscaled full-image draw with full opacity,
no matrix/color filter, pixel page units/scale, and an identity transform plus
integer translation. Source and native bitmap dimensions must agree. Native
compositing state is restored afterward; unsuccessful attempts fall back to the
existing draw.

For mixed static sources, the same exact-draw restrictions apply. When at least
50% of the image is covered by at most 64 retained opaque rectangles, GDI+ copies
those source rectangles with `SourceCopy`, then draws the full image with
`SourceOver` clipped to the complement of those rectangles. Transparent and
translucent pixels therefore retain normal blending. Rectangles are conservative,
fully opaque source-pixel regions. Scaled, rotated, faded, animated/all-frame,
filtered, and otherwise unsupported draws retain the original path. The
platform-neutral statistics and cache types live with image metadata; other
backends can consume the same rectangles and choose their own equivalent
operation.

These paths preserve the existing destination clip and compositing state. A
failed setup or opaque-region copy falls back before the blended remainder is
drawn. Runtime pixel-equivalence and performance measurements are still needed
on Windows and ReactOS/XP-compatible builds.

Hello Multiverse publishes its resized still-image cache after graphics release,
and declares its per-frame scene output as a framebuffer. Animated sources are
not automatically declared static. Other clients opt in after completing writes.

No new operating-system APIs are required. The shared implementation and GDI+
path use APIs already present in the Windows/ReactOS-XP builds. Compilation is
checked on both toolchains; runtime pixel equivalence and performance remain
unverified. Rebuild consumers of the changed public image class together.
