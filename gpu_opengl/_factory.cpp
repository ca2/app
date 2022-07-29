#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


//BEGIN_FACTORY(gpu_opengl)
//FACTORY_ITEM(::opengl::opengl)
//FACTORY_ITEM(::opengl::program)
//FACTORY_ITEM(::opengl::shader)
//FACTORY_ITEM(::opengl::buffer)
//END_FACTORY()


__FACTORY_EXPORT void gpu_opengl_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::opengl::opengl, ::gpu::approach >();
   pfactory->add_factory_item < ::opengl::program, ::gpu::program >();
   pfactory->add_factory_item < ::opengl::shader, ::gpu::shader >();
   pfactory->add_factory_item < ::opengl::buffer, ::gpu::buffer >();

}



