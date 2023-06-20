#pragma once


#include "aura/graphics/gpu/buffer.h"


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL buffer :
      virtual public ::gpu::buffer
   {
   public:


      //__creatable_from_base(buffer, ::gpu::buffer);


      buffer();
      ~buffer() override;


      void gpu_read() override;
      void gpu_write() override;
      


   };


} // namespace opengl



