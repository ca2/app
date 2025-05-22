#pragma once


#include "aura/graphics/gpu/program.h"


namespace gpu_vulkan
{


   class CLASS_DECL_GPU_VULKAN program :
      virtual public ::gpu::program
   {
   public:


      //__creatable_from_base(program, ::gpu::program);


      program();
      ~program() override;


      void create_program(::particle * pparticle, const string& strVertex, const string& strFragment, const string& strGeometry = "") override;


   };


} // namespace gpu_vulkan


