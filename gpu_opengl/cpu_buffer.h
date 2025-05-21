#pragma once


#include "aura/graphics/gpu/cpu_buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL cpu_buffer :
      virtual public ::gpu::cpu_buffer
   {
   public:


      //__creatable_from_base(buffer, ::gpu::buffer);


      cpu_buffer();
      ~cpu_buffer() override;


      //void set_size(const ::int_size & size) override;


      void gpu_read() override;
      void gpu_write() override;
      


   };


} // namespace gpu_opengl



