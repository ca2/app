#pragma once


#include "bred/gpu/aaa_cpu_buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL aaa_cpu_buffer :
      virtual public ::gpu::aaa_cpu_buffer
   {
   public:


      //__creatable_from_base(buffer, ::gpu::buffer);


      aaa_cpu_buffer();
      ~aaa_cpu_buffer() override;


      //void set_size(const ::i32_size & size) override;


      void gpu_read() override;
      void gpu_write() override;
      


   };


} // namespace gpu_opengl



