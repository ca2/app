"""Exercise the shared GLSL on a hidden WGL context (Windows, no Python packages).

Run brush_fill_tests <sources-dir> first; pass that directory as the sole argument.
The window stays hidden; all assertions read an RGBA8 framebuffer.
"""
import ctypes as C
from ctypes import wintypes as W
from pathlib import Path
import sys

sources = Path(sys.argv[1])
user, gdi, gl = C.WinDLL('user32'), C.WinDLL('gdi32'), C.WinDLL('opengl32')
ptr, uint, integer, floating = C.c_void_p, C.c_uint, C.c_int, C.c_float

def native(dll, name, result, *args):
    fn = getattr(dll, name)
    fn.restype, fn.argtypes = result, args
    return fn

create_window = native(user, 'CreateWindowExW', ptr, W.DWORD, W.LPCWSTR, W.LPCWSTR,
    W.DWORD, integer, integer, integer, integer, ptr, ptr, ptr, ptr)
window = create_window(0, 'STATIC', 'GPU brush test', 0x80000000, 0, 0, 64, 64, None, None, None, None)
assert window, 'CreateWindowExW'
dc = native(user, 'GetDC', ptr, ptr)(window)

class PixelFormat(C.Structure):
    _fields_ = [('size', W.WORD), ('version', W.WORD), ('flags', W.DWORD),
        ('pixelType', C.c_ubyte), ('colorBits', C.c_ubyte), ('redBits', C.c_ubyte),
        ('redShift', C.c_ubyte), ('greenBits', C.c_ubyte), ('greenShift', C.c_ubyte),
        ('blueBits', C.c_ubyte), ('blueShift', C.c_ubyte), ('alphaBits', C.c_ubyte),
        ('alphaShift', C.c_ubyte), ('accumBits', C.c_ubyte), ('accumRedBits', C.c_ubyte),
        ('accumGreenBits', C.c_ubyte), ('accumBlueBits', C.c_ubyte), ('accumAlphaBits', C.c_ubyte),
        ('depthBits', C.c_ubyte), ('stencilBits', C.c_ubyte), ('auxBuffers', C.c_ubyte),
        ('layerType', C.c_ubyte), ('reserved', C.c_ubyte), ('layerMask', W.DWORD),
        ('visibleMask', W.DWORD), ('damageMask', W.DWORD)]

pfd = PixelFormat()
pfd.size, pfd.version, pfd.flags, pfd.colorBits, pfd.alphaBits = C.sizeof(pfd), 1, 0x24, 32, 8
fmt = native(gdi, 'ChoosePixelFormat', integer, ptr, ptr)(dc, C.byref(pfd))
assert fmt and native(gdi, 'SetPixelFormat', W.BOOL, ptr, integer, ptr)(dc, fmt, C.byref(pfd))
context = native(gl, 'wglCreateContext', ptr, ptr)(dc)
assert context and native(gl, 'wglMakeCurrent', W.BOOL, ptr, ptr)(dc, context)
address = native(gl, 'wglGetProcAddress', ptr, C.c_char_p)

def api(name, result, *args):
    location = address(name.encode())
    if location and location not in (1, 2, 3, C.c_void_p(-1).value):
        return C.WINFUNCTYPE(result, *args)(location)
    return native(gl, name, result, *args)

get_string = api('glGetString', C.c_char_p, uint)
print('Rendering on', get_string(0x1F01).decode(), get_string(0x1F02).decode())
create_shader = api('glCreateShader', uint, uint)
shader_source = api('glShaderSource', None, uint, integer, ptr, ptr)
compile_shader = api('glCompileShader', None, uint)
get_shader = api('glGetShaderiv', None, uint, uint, ptr)
shader_log = api('glGetShaderInfoLog', None, uint, integer, ptr, ptr)
create_program = api('glCreateProgram', uint)
attach = api('glAttachShader', None, uint, uint)
link = api('glLinkProgram', None, uint)
get_program = api('glGetProgramiv', None, uint, uint, ptr)
program_log = api('glGetProgramInfoLog', None, uint, integer, ptr, ptr)
use = api('glUseProgram', None, uint)
location = api('glGetUniformLocation', integer, uint, C.c_char_p)
uniform4 = api('glUniform4f', None, integer, floating, floating, floating, floating)
uniform1 = api('glUniform1i', None, integer, integer)

def program(pattern):
    result = create_program()
    for suffix, stage in [('vert', 0x8B31), ('frag', 0x8B30)]:
        shader = create_shader(stage)
        text = (sources / ('gl_' + ('pattern' if pattern else 'plain') + '.' + suffix)).read_bytes()
        source = C.c_char_p(text)
        shader_source(shader, 1, C.byref(source), None)
        compile_shader(shader)
        status, log = integer(), C.create_string_buffer(8192)
        get_shader(shader, 0x8B81, C.byref(status))
        shader_log(shader, len(log), None, log)
        assert status.value, log.value.decode()
        attach(result, shader)
    link(result)
    status, log = integer(), C.create_string_buffer(8192)
    get_program(result, 0x8B82, C.byref(status))
    program_log(result, len(log), None, log)
    assert status.value, log.value.decode()
    return result

plain, pattern = program(False), program(True)
# The production bulk uploader must accept shared properties optimized out of
# an individual variant, while retaining offsets for the active properties.
assert location(plain, b'brushData1') == -1
assert location(plain, b'textureInformation') == -1
assert location(pattern, b'brushColor0') == -1
assert location(pattern, b'brushColor1') == -1
gen_texture = api('glGenTextures', None, integer, ptr)
bind_texture = api('glBindTexture', None, uint, uint)
image = api('glTexImage2D', None, uint, integer, integer, integer, integer, integer, uint, uint, ptr)
parameter = api('glTexParameteri', None, uint, uint, integer)

def texture(width, height, pixels=None):
    tex = uint()
    gen_texture(1, C.byref(tex))
    bind_texture(0x0DE1, tex)
    image(0x0DE1, 0, 0x8058, width, height, 0, 0x1908, 0x1401, pixels)
    parameter(0x0DE1, 0x2801, 0x2601)
    parameter(0x0DE1, 0x2800, 0x2601)
    return tex

target = texture(64, 64)
fbo = uint()
api('glGenFramebuffers', None, integer, ptr)(1, C.byref(fbo))
api('glBindFramebuffer', None, uint, uint)(0x8D40, fbo)
api('glFramebufferTexture2D', None, uint, uint, uint, uint, integer)(0x8D40, 0x8CE0, 0x0DE1, target, 0)
assert api('glCheckFramebufferStatus', uint, uint)(0x8D40) == 0x8CD5
api('glViewport', None, integer, integer, integer, integer)(0, 0, 64, 64)
vao, vbo = uint(), uint()
api('glGenVertexArrays', None, integer, ptr)(1, C.byref(vao))
api('glBindVertexArray', None, uint)(vao)
api('glGenBuffers', None, integer, ptr)(1, C.byref(vbo))
api('glBindBuffer', None, uint, uint)(0x8892, vbo)
for index in range(2):
    api('glEnableVertexAttribArray', None, uint)(index)
    api('glVertexAttribPointer', None, uint, integer, uint, W.BOOL, integer, ptr)(index, 2, 0x1406, False, 16, index * 8)
clear_color = api('glClearColor', None, floating, floating, floating, floating)
clear = api('glClear', None, uint)
read = api('glReadPixels', None, integer, integer, integer, integer, uint, uint, ptr)
enable, disable = api('glEnable', None, uint), api('glDisable', None, uint)
buffer_data = api('glBufferData', None, uint, C.c_ssize_t, ptr, uint)
draw = api('glDrawArrays', None, uint, integer, integer)

def render(mode=0, ellipse=False, data=(0, 0, 0, 0), color0=(1, 0, 0, 1),
           color1=(0, 0, 1, 1), tex=None, tile=(2, 2), blend=False, background=(0, 0, 0, 0),
           user_offset=(0, 0), vertices=None, shape=(32, 32, 24, 12)):
    shader = pattern if tex else plain
    use(shader)
    settings = dict(brushColor0=color0, brushColor1=color1, brushData0=data,
        brushData1=(1, 1, 2, 2), textureInformation=(0.25, 0.25, 0, 0),
        fillShape=shape, brushParameters=(mode, int(ellipse), 4, 0))
    if tex:
        settings['brushData0'] = (*tile, 0, 0)
        bind_texture(0x0DE1, tex)
        uniform1(location(shader, b'uTexture'), 0)
    for name, values in settings.items():
        uniform4(location(shader, name.encode()), *values)
    if blend:
        enable(0x0BE2)
        api('glBlendFunc', None, uint, uint)(1, 0x0303)
    else:
        disable(0x0BE2)
    clear_color(*background)
    clear(0x4000)
    vertices = vertices or [(0, 0), (64, 0), (64, 64), (0, 0), (64, 64), (0, 64)]
    values = []
    for x, y in vertices:
        values.extend((x / 32 - 1, y / 32 - 1, x + user_offset[0], y + user_offset[1]))
    vertex_data = (floating * len(values))(*values)
    buffer_data(0x8892, C.sizeof(vertex_data), vertex_data, 0x88E0)
    draw(4, 0, len(vertices))
    pixels = (C.c_ubyte * (64 * 64 * 4))()
    read(0, 0, 64, 64, 0x1908, 0x1401, pixels)
    assert api('glGetError', uint)() == 0
    return lambda x, y: tuple(pixels[(y * 64 + x) * 4 + c] / 255 for c in range(4))

def near(actual, expected, tolerance=0.015):
    assert all(abs(a-b) <= tolerance for a, b in zip(actual, expected)), (actual, expected)

p = render(ellipse=True, background=(0, 1, 0, 1))
near(p(32, 32), (1, 0, 0, 1))
near(p(8, 20), (0, 1, 0, 1))  # Quad corners must leave destination intact in alpha-set mode.
assert 0.05 < p(55, 32)[3] < 0.99  # Antialiased ellipse edge.
p = render(color0=(0.5, 0, 0, 0.5), blend=True, background=(0, 0, 1, 1))
near(p(20, 20), (0.5, 0, 0.5, 1))
p = render(1, data=(16, 0, 48, 0))
near(p(0, 20), (1, 0, 0, 1))
near(p(63, 20), (0, 0, 1, 1))
near(p(31, 20), (0.515625, 0, 0.484375, 1))
p = render(1, data=(16, 0, 16, 0))
near(p(32, 32), (1, 0, 0, 1))  # Degenerate linear gradient.
p = render(2, data=(32.5, 32.5, 16, 8))
near(p(32, 32), (1, 0, 0, 1))
near(p(48, 32), (0, 0, 1, 1))
near(p(32, 40), (0, 0, 1, 1))
p = render(4, data=(16, 16, 32, 32))
near(p(32, 32), (1, 0, 0, 1))
near(p(0, 0), (0, 0, 1, 1))
p = render(1, data=(16, 0, 48, 0), user_offset=(-16, 0))
near(p(47, 20), (0.515625, 0, 0.484375, 1))  # Geometry and brush coordinates remain separate.

# A 2x2 logical image inside a magenta 4x4 atlas, matching a padded GPU image.
atlas = bytearray([255, 0, 255, 255] * 16)
colors = [(255, 0, 0, 255), (0, 255, 0, 255), (0, 0, 255, 255), (255, 255, 255, 255)]
for (x, y), color in zip([(1, 1), (2, 1), (1, 2), (2, 2)], colors):
    atlas[((3 - y) * 4 + x) * 4:((3 - y) * 4 + x + 1) * 4] = bytes(color)
atlas_data = (C.c_ubyte * len(atlas)).from_buffer(atlas)
tex = texture(4, 4, atlas_data)
p = render(tex=tex)
near(p(0, 0), (1, 0, 0, 1))
near(p(1, 0), (0, 1, 0, 1))
near(p(0, 1), (0, 0, 1, 1))
near(p(1, 1), (1, 1, 1, 1))
near(p(2, 0), p(0, 0))
p = render(tex=tex, user_offset=(-2, -2))
near(p(0, 0), (1, 0, 0, 1))
p = render(tex=tex, tile=(4, 4))
near(p(0, 0), p(4, 0))
assert p(0, 0)[1] > 0.1  # Bilinear filtering blends wrapped logical pixels, never atlas padding.

# Every brush also passes through ellipse coverage, including textured fills.
for settings in [dict(), dict(mode=1, data=(16, 0, 48, 0)),
                 dict(mode=2, data=(32, 32, 16, 8)),
                 dict(mode=4, data=(16, 16, 32, 32)), dict(tex=tex)]:
    p = render(ellipse=True, **settings)
    assert p(32, 32)[3] == 1 and p(8, 20)[3] == 0

# Reuse the same brush shader for a concave L polygon already tessellated by the C++ tests.
l_shape = [(0, 0), (48, 0), (48, 16), (0, 0), (48, 16), (16, 16),
           (0, 0), (16, 16), (16, 48), (0, 0), (16, 48), (0, 48)]
p = render(1, data=(0, 0, 48, 0), vertices=l_shape)
assert p(8, 32)[3] == 1 and p(32, 32)[3] == 0
# Render the production tessellator's tab triangles, rather than a hand-built mesh.
tab_vertices = [tuple(map(float, line.split())) for line in (sources / 'tab_triangles.txt').read_text().splitlines()]
p = render(1, data=(8, 8, 8, 48), vertices=tab_vertices)
near(p(20, 12), (0.8875, 0, 0.1125, 1))
near(p(20, 42), (0.1375, 0, 0.8625, 1))
assert p(54, 10)[3] == 0 and p(4, 24)[3] == 0  # Sloped corner and outside the tab.
# Moving geometry/target origin must preserve user-space gradient evaluation.
shifted = [(x + 3, y + 2) for x, y in tab_vertices]
p = render(1, data=(8, 8, 8, 48), vertices=shifted, user_offset=(-3, -2))
near(p(23, 14), (0.8875, 0, 0.1125, 1))
# A translucent path must cover each interior pixel exactly once.
p = render(color0=(0.5, 0, 0, 0.5), blend=True, vertices=tab_vertices, background=(0, 0, 1, 1))
near(p(20, 24), (0.5, 0, 0.5, 1))
print('PASS: ellipse coverage, alpha set/blend, all brushes, transforms, concave polygon, tessellated gradient tabs')
native(gl, 'wglMakeCurrent', W.BOOL, ptr, ptr)(None, None)
native(gl, 'wglDeleteContext', W.BOOL, ptr)(context)
native(user, 'ReleaseDC', integer, ptr, ptr)(window, dc)
native(user, 'DestroyWindow', W.BOOL, ptr)(window)
