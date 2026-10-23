# Shared GPU brush fills

`gpu::graphics` implements `fill_ellipse`, `fill_polygon` and the brush overload of
`fill_rectangle`, plus the `fill(path)`/`fill(path, brush)` overloads. OpenGL, Vulkan, DirectX 11 and DirectX 12 drawing classes forward
to these implementations. The existing `draw_ellipse` outline implementation is
unchanged.

The common shader evaluates solid, two-color linear, elliptical radial,
rounded-box gradient and image pattern brushes. Colors are premultiplied before
interpolation and use the existing alpha set/blend pipeline choices. Radial brush
sizes are radii. Image patterns repeat from the user-space origin, with a custom
tile size or the image dimensions when no size is specified. Filtering wraps
inside the logical image; backing-image padding is excluded. OpenGL sampling
accounts for its bottom-first texture rows.

## Reuse with other shapes

`fill_brush_triangles(points, count, brush)` accepts untransformed user-space
coordinates, in groups of three. It applies the graphics transform and retains
separate user-space coordinates for brush evaluation. Paths and other shapes can
call this method after tessellation, sharing brush handling, shader caches,
texture upload, alpha modes and resource retention.

`fill_polygon` currently tessellates simple concave or convex polygons in either
winding order. Adjacent duplicates, closing duplicates and collinear vertices are
accepted. Self-intersections and touching nonadjacent edges are rejected.

`fill(path)` and `fill(path, brush)` tessellate one connected straight-line
contour, including line lists, polygons and rectangles. Open contours are closed
for filling, so the selected-tab path and explicitly closed hover-tab path have
the same fill behavior. Begin/end/close figure markers are respected. Both winding
orders work; for one simple contour the winding and alternate fill rules agree.
Additional/disconnected contours, holes and curved/text path items are explicitly
unsupported. Invalid intersecting geometry is rejected before any GPU drawing.
This does not implement the separate begin_path/end_path/fill_path recording API.
Target-scope offsets and graphics transforms are applied by the existing shared
brush pipeline, preserving the path's user-space gradient coordinates.

## Windows checks

Run from the repository root in an x64 Visual Studio developer shell:

```powershell
cl /nologo /EHsc /std:c++20 /W4 source/app/bred/gpu/tests/brush_fill_tests.cpp /Fe:intermediate-windows/brush_fill_tests.exe /Fo:intermediate-windows/brush_fill_tests.obj
intermediate-windows/brush_fill_tests.exe intermediate-windows/brush-fill-shaders
python source/app/bred/gpu/tests/validate_brush_fill_shaders.py intermediate-windows/brush-fill-shaders
python source/app/bred/gpu/tests/render_brush_fill_tests.py intermediate-windows/brush-fill-shaders
```

The first program checks triangulation and emits the actual shared shader source.
Validation uses `glslangValidator` from the Vulkan SDK and the Windows
`d3dcompiler_47.dll`. The render test creates a hidden WGL context and reads an
RGBA8 framebuffer; it checks ellipse coverage, alpha modes, all brush types,
pattern orientation and wrapping inside a padded image, separate geometry/brush
coordinates, a concave polygon, and gradient tabs using the production tessellator's triangles (including target offsets and translucent fills). It does not start Continuum or change its
configuration.

After editing `brush_fill_shader_source.h`, refresh the checked-in Vulkan shaders:

```powershell
python source/app/bred/gpu/tests/validate_brush_fill_shaders.py intermediate-windows/brush-fill-shaders --vulkan-output source/app-graphics3d/gpu_vulkan/shader
```

Regenerate the emitted source with the C++ program first. The three embedded
SPIR-V files are generated artifacts of the shared source, not independent brush
implementations. Rebuild `bred` and the GPU and draw2d backend libraries after
changing the shared classes.
