#include "framework.h"
#include "approach.h"
#include "context.h"
#include "cpu_buffer.h"
#include "device.h"
#include "device_win32.h"
#include "frame_buffer.h"
#include "object.h"
#include "offscreen_render_target.h"
#include "program.h"
#include "renderer.h"
#include "shader.h"
#include "swap_chain.h"
#include "texture.h"


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

#if defined(WINDOWS_DESKTOP)

   pfactory->add_factory_item < ::gpu_opengl::device_win32, ::gpu::device >();

#endif

   pfactory->add_factory_item < ::gpu_opengl::offscreen_render_target, ::gpu::render_target >();
   pfactory->add_factory_item < ::gpu_opengl::swap_chain, ::gpu::swap_chain >();


}



