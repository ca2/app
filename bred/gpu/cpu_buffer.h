#pragma once


#include "acme/graphics/image/pixmap.h"


namespace gpu
{


   class CLASS_DECL_BRED cpu_buffer :
      virtual public ::object
   {
   public:


      //::memory                         m_memory;
      //::pixmap                         m_pixmap;
      ::pointer < ::image::target >    m_pimagetarget;
      ::pointer < ::gpu::context >     m_pgpucontext;


      cpu_buffer();
      ~cpu_buffer() override;


      virtual void initialize_cpu_buffer(::gpu::context * pgpucontext);


      virtual void set_size(const ::int_size & size);


      virtual ::image::target* get_image_target();


      virtual void gpu_read();
      virtual void gpu_write();

      
      virtual void set_pixels(const void * p, int w, int h, int s, bool bYSwap);




   };


} // namespace gpu



