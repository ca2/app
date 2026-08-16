#pragma once


#include "bred/gpu/buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL buffer :
      virtual public ::gpu::buffer
   {
   public:


      //__creatable_from_base(buffer, ::gpu::buffer);


      buffer();
      ~buffer() override;


      //void set_size(const ::i32_size & size) override;


      void gpu_read() override;
      void gpu_write() override;
      


   };


} // namespace gpu_opengl



