#include "framework.h"
#include "approach.h"
#include "program.h"
#include "shader.h"
#include "cpu_buffer.h"
#include "object.h"
#include "renderer.h"


//BEGIN_FACTORY(gpu_vulkan)
//FACTORY_ITEM(::vulkan::vulkan)
//FACTORY_ITEM(::vulkan::program)
//FACTORY_ITEM(::vulkan::shader)
//FACTORY_ITEM(::vulkan::buffer)
//END_FACTORY()


__FACTORY_EXPORT void gpu_vulkan_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::gpu_vulkan::approach, ::gpu::approach >();
   pfactory->add_factory_item < ::gpu_vulkan::program, ::gpu::program >();
   pfactory->add_factory_item < ::gpu_vulkan::shader, ::gpu::shader >();
   pfactory->add_factory_item < ::gpu_vulkan::cpu_buffer, ::gpu::cpu_buffer >();
   pfactory->add_factory_item < ::gpu_vulkan::renderer, ::gpu::renderer >();

   pfactory->add_factory_item < ::gpu_vulkan::object, ::gpu::object >();

}



