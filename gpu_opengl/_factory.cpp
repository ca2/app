#include "framework.h"
#include "approach.h"
#include "command_buffer.h"
#include "context.h"
#include "cpu_buffer.h"
#include "device.h"
#include "frame_buffer.h"
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
#include "bred/gpu/frame.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/pixmap.h"
#include "bred/gpu/frame_ephemeral.h"
#include "bred/gpu/frame_storage.h"


#if defined(WINDOWS_DESKTOP)

#include "device_win32.h"

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

#endif

   pfactory->add_factory_item < ::gpu_opengl::offscreen_render_target, ::gpu::render_target >();
   pfactory->add_factory_item < ::gpu_opengl::swap_chain, ::gpu::swap_chain >();
   pfactory->add_factory_item < ::gpu_opengl::command_buffer, ::gpu::command_buffer >();
   //pfactory->add_factory_item < ::gpu_opengl::pixmap, ::gpu::pixmap >();
   pfactory->add_factory_item <  ::gpu::pixmap >();
   pfactory->add_factory_item < ::gpu_opengl::model_buffer, ::gpu::model_buffer >();


   pfactory->add_factory_item < ::gpu_opengl::memory_buffer, ::gpu::memory_buffer >();
   pfactory->add_factory_item < ::gpu::frame_ephemeral >();
   pfactory->add_factory_item < ::gpu::frame_storage >();

}



