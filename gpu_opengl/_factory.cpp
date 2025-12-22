#include "framework.h"
#include "_gpu_opengl.h"
#include "approach.h"
#include "block.h"
#include "command_buffer.h"
#include "context.h"
#include "cpu_buffer.h"
//#include "cube.h"
#include "device.h"
#include "frame_buffer.h"
#include "full_screen_quad.h"
#include "hdr_texture.h"
#include "input_layout.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "object.h"
#include "offscreen_render_target.h"
#include "pixmap.h"
#include "program.h"
#include "renderer.h"
#include "shader.h"
#include "swap_chain.h"
#include "texture.h"
#include "gltf/mesh.h"
#include "gltf/model.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/pixmap.h"
#include "bred/gpu/frame_ephemeral.h"
#include "bred/gpu/frame_storage.h"
#include "gpu/full_screen_quad.h"
//#include "ibl/brdf_convolution_framebuffer.h"
#include "ibl/diffuse_irradiance_map.h"
#include "ibl/equirectangular_cubemap.h"
#include "ibl/specular_map.h"
//#include "ibl/cubemap_framebuffer.h"
//#include "ibl/aaa_mipmap_cubemap_framebuffer.h"
//#include "ibl/hdri_cube.h"


#if defined(WINDOWS_DESKTOP)

#include "device_win32.h"

#else

#include "device_egl.h"

#endif

//BEGIN_FACTORY(gpu_opengl)
//FACTORY_ITEM(::opengl::opengl)
//FACTORY_ITEM(::opengl::program)
//FACTORY_ITEM(::opengl::shader)
//FACTORY_ITEM(::opengl::buffer)
//END_FACTORY()


__FACTORY_EXPORT void gpu_opengl_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::gpu_opengl::approach, ::gpu::approach >();
   pfactory->add_factory_item < ::gpu_opengl::context, ::gpu::context >();
   //pfactory->add_factory_item < ::gpu_opengl::program, ::gpu::program >();
   pfactory->add_factory_item < ::gpu_opengl::shader, ::gpu::shader >();
   pfactory->add_factory_item < ::gpu_opengl::cpu_buffer, ::gpu::cpu_buffer >();
   pfactory->add_factory_item < ::gpu_opengl::renderer, ::gpu::renderer >();

   pfactory->add_factory_item < ::gpu_opengl::object, ::gpu::object >();

   pfactory->add_factory_item < ::gpu_opengl::texture, ::gpu::texture >();

   pfactory->add_factory_item < ::gpu_opengl::frame_buffer >();

   pfactory->add_factory_item < ::gpu::layer >();

   pfactory->add_factory_item < ::gpu::frame >();

   pfactory->add_factory_item < ::gpu_opengl::input_layout, ::gpu::input_layout >();

#if defined(WINDOWS_DESKTOP)

   pfactory->add_factory_item < ::gpu_opengl::device_win32, ::gpu::device >();

#else

   pfactory->add_factory_item < ::gpu_opengl::device_egl, ::gpu::device >();

#endif

   pfactory->add_factory_item < ::gpu_opengl::offscreen_render_target, ::gpu::render_target >();
   pfactory->add_factory_item < ::gpu_opengl::swap_chain, ::gpu::swap_chain >();
   pfactory->add_factory_item < ::gpu_opengl::command_buffer, ::gpu::command_buffer >();
   //pfactory->add_factory_item < ::gpu_opengl::pixmap, ::gpu::pixmap >();
   pfactory->add_factory_item <  ::gpu::pixmap >();
   pfactory->add_factory_item < ::gpu_opengl::model_buffer, ::gpu::model_buffer >();


   pfactory->add_factory_item<::gpu_opengl::block, ::gpu::block>();
   pfactory->add_factory_item < ::gpu_opengl::memory_buffer, ::gpu::memory_buffer >();
   pfactory->add_factory_item < ::gpu::frame_ephemeral >();
   pfactory->add_factory_item < ::gpu::frame_storage >();

   //pfactory->add_factory_item < ::gpu_opengl::cube, ::gpu::cube >();
   //pfactory->add_factory_item < ::gpu::cube >();
   //pfactory->add_factory_item < ::gpu_opengl::full_screen_quad, ::gpu::full_screen_quad >();
   pfactory->add_factory_item < ::gpu::full_screen_quad >();
   //pfactory->add_factory_item < ::gpu_opengl::hdr_texture, ::gpu::hdr_texture >();
   pfactory->add_factory_item < ::gpu_opengl::ibl::diffuse_irradiance_map, ::gpu::ibl::diffuse_irradiance_map >();
   pfactory->add_factory_item < ::gpu_opengl::ibl::specular_map, ::gpu::ibl::specular_map >();
   //pfactory->add_factory_item < ::gpu_opengl::ibl::aaa_mipmap_cubemap_framebuffer, ::gpu::ibl::aaa_mipmap_cubemap_framebuffer>();
   //pfactory->add_factory_item < ::gpu::ibl::mipmap_cubemap_framebuffer>();
   ////pfactory->add_factory_item < ::gpu_opengl::ibl::cubemap_framebuffer, ::gpu::ibl::cubemap_framebuffer>();
   //pfactory->add_factory_item < ::gpu_opengl::ibl::cubemap_framebuffer, ::gpu::ibl::cubemap_framebuffer>();
   //pfactory->add_factory_item <  ::gpu::ibl::cubemap_framebuffer>();
   pfactory->add_factory_item < ::gpu_opengl::ibl::equirectangular_cubemap, ::gpu::ibl::equirectangular_cubemap>();
   //pfactory->add_factory_item < ::gpu_opengl::ibl::brdf_convolution_framebuffer, ::gpu::ibl::brdf_convolution_framebuffer>();
   //pfactory->add_factory_item < ::gpu_opengl::ibl::hdri_cube, ::gpu::ibl::hdri_cube>();
   pfactory->add_factory_item<::gpu_opengl::gltf::mesh, ::gpu::gltf::mesh>();
   pfactory->add_factory_item<::gpu_opengl::gltf::model, ::gpu::gltf::model>();
}



