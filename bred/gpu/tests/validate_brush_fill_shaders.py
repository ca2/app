"""Validate emitted brush-fill shaders; optionally refresh Vulkan's embedded SPIR-V.
Run brush_fill_tests <output-dir> first to emit the actual shared shader sources.
"""
import argparse
import ctypes
from ctypes import wintypes
from pathlib import Path
import shutil
import struct
import subprocess

parser=argparse.ArgumentParser()
parser.add_argument('sources',type=Path)
parser.add_argument('--vulkan-output',type=Path)
args=parser.parse_args()
compiler=shutil.which('glslangValidator')
if not compiler: raise SystemExit('glslangValidator is required')
for source in sorted(args.sources.glob('gl_*')):
    if source.suffix in ('.vert','.frag'):
        subprocess.run([compiler,'-S',source.suffix[1:],str(source)],check=True)
for source in sorted(args.sources.glob('vk_*')):
    if source.suffix in ('.vert','.frag'):
        subprocess.run([compiler,'-V','--target-env','vulkan1.0',str(source),'-o',str(source)+'.spv'],check=True)

# Validate the same HLSL with the native Direct3D 11/12 shader compiler.
dll=ctypes.WinDLL('d3dcompiler_47.dll')
compile_shader=dll.D3DCompile
compile_shader.argtypes=[ctypes.c_void_p,ctypes.c_size_t,ctypes.c_char_p,ctypes.c_void_p,ctypes.c_void_p,
    ctypes.c_char_p,ctypes.c_char_p,wintypes.UINT,wintypes.UINT,ctypes.POINTER(ctypes.c_void_p),ctypes.POINTER(ctypes.c_void_p)]
compile_shader.restype=ctypes.c_long

def blob_bytes(blob):
    table=ctypes.cast(blob,ctypes.POINTER(ctypes.POINTER(ctypes.c_void_p))).contents
    data=ctypes.WINFUNCTYPE(ctypes.c_void_p,ctypes.c_void_p)(table[3])(blob)
    size=ctypes.WINFUNCTYPE(ctypes.c_size_t,ctypes.c_void_p)(table[4])(blob)
    return ctypes.string_at(data,size)
def release(blob):
    if blob:
        table=ctypes.cast(blob,ctypes.POINTER(ctypes.POINTER(ctypes.c_void_p))).contents
        ctypes.WINFUNCTYPE(wintypes.ULONG,ctypes.c_void_p)(table[2])(blob)
for source in sorted(args.sources.glob('hlsl_*')):
    data=source.read_bytes(); code=ctypes.c_void_p(); error=ctypes.c_void_p()
    profile=b'vs_5_0' if source.suffix=='.vert' else b'ps_5_0'
    result=compile_shader(data,len(data),str(source).encode(),None,None,b'main',profile,0,0,ctypes.byref(code),ctypes.byref(error))
    try:
        if result<0: raise RuntimeError(f'{source}: {blob_bytes(error).decode()}')
    finally:
        release(code); release(error)

if args.vulkan_output:
    args.vulkan_output.mkdir(parents=True,exist_ok=True)
    for name,source in [('_001BrushFill.vert','vk_plain.vert'),('_001BrushFill.frag','vk_plain.frag'),('_001BrushPattern.frag','vk_pattern.frag')]:
        data=(args.sources/(source+'.spv')).read_bytes()
        words=struct.unpack('<'+'I'*(len(data)//4),data)
        text='// Generated from bred/gpu/brush_fill_shader_source.h by validate_brush_fill_shaders.py.\n'
        text+='\n'.join(', '.join(f'0x{word:08x}' for word in words[i:i+8])+',' for i in range(0,len(words),8))+'\n'
        (args.vulkan_output/(name+'.spv.inl')).write_bytes(text.replace('\n','\r\n').encode())
print('GLSL, Vulkan SPIR-V, and Direct3D HLSL brush-fill variants validated')
