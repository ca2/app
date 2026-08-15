// Recreated from cpu_buffer by camilo on 2026-08-05 03:16 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "buffer.h"
#include "context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/aaa_target.h"
//#include "_.h"
//#include "_gpu.h"
//#include "_defer.h"


namespace gpu
{


   buffer::buffer()
   {

   }


   buffer::~buffer()
   {

   }


   void buffer::initialize_buffer(::gpu::context * pgpucontext)
   {

      initialize_gpu_context_object(pgpucontext);

      defer_create_synchronization();



   }


   void buffer::set_size(const ::i32_size & size)
   {

      defer_construct_newø(m_ppixmap);

      m_ppixmap->create_as_descriptor(size);

      if (m_ppixmap.nok())
      {

         throw ::exception(error_resource);

      }

   }


   ::pixmap * buffer::pixmap()
   {

      if (!m_ppixmap)
      {

         defer_construct_newø(m_ppixmap);

      }

      return m_ppixmap;

   }


   void buffer::gpu_read()
   {

      if (m_ppixmap.nok())
      {

         return;

      }

   }


   void buffer::gpu_write()
   {

      if (m_ppixmap.nok())
      {

         return;

      }


   }


   void buffer::set_pixels(const void* p, ::i32 w, ::i32 h, ::i32 s, bool bYSwap)
   {

      //m_ppixmap->set_image_pixels((const ::image32_t*)p, w, h, s, bYSwap);

   }


} // namespace gpu



