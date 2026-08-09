// Recreated from cpu_buffer by camilo on 2026-08-05 03:07 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap.h"
#include "bred/gpu/context_object.h"


namespace gpu
{


   class CLASS_DECL_BRED buffer :
      virtual public ::gpu::context_object
   {
   public:


      //::memory                         m_memory;
      //::pixmap                         m_pixmap;
      ::pixmap_pointer                 m_ppixmap;
      //::gpu::context_pointer         m_pgpucontext;


      buffer();
      ~buffer() override;


      virtual void initialize_buffer(::gpu::context * pgpucontext);


      virtual void set_size(const ::i32_size & size);


      virtual ::pixmap * pixmap();


      virtual void gpu_read();
      virtual void gpu_write();

      
      virtual void set_pixels(const void * p, ::i32 w, ::i32 h, ::i32 s, bool bYSwap);




   };


} // namespace gpu



