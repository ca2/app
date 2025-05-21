#include "framework.h"
#include "opengl.h"
#include "program.h"
#include "shader.h"
#include "cpu_buffer.h"
#include "object.h"


//BEGIN_FACTORY(gpu_opengl)
//FACTORY_ITEM(::opengl::opengl)
//FACTORY_ITEM(::opengl::program)
//FACTORY_ITEM(::opengl::shader)
//FACTORY_ITEM(::opengl::buffer)
//END_FACTORY()


__FACTORY_EXPORT void gpu_opengl_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::gpu_opengl::opengl, ::gpu::approach >();
   pfactory->add_factory_item < ::gpu_opengl::program, ::gpu::program >();
   pfactory->add_factory_item < ::gpu_opengl::shader, ::gpu::shader >();
   pfactory->add_factory_item < ::gpu_opengl::cpu_buffer, ::gpu::cpu_buffer >();

   pfactory->add_factory_item < ::gpu_opengl::object, ::gpu::object >();

}



