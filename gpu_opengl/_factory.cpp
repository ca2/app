#include "framework.h"


__FACTORY_EXPORT void gpu_opengl_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::opengl::opengl, ::gpu::approach >();
   pfactory->add_factory_item < ::opengl::program, ::gpu::program >();
   pfactory->add_factory_item < ::opengl::shader, ::gpu::shader >();
   pfactory->add_factory_item < ::opengl::buffer, ::gpu::buffer >();

}
