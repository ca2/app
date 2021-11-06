#include "framework.h"


extern "C" void gpu_opengl_factory_exchange(::factory_map * pfactorymap)
{


   create_factory < ::opengl::opengl, ::gpu::approach >();

   create_factory < ::opengl::program, ::gpu::program >();

   create_factory < ::opengl::shader, ::gpu::shader >();

   create_factory < ::opengl::buffer, ::gpu::buffer >();

}
