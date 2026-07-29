#include "framework.h"
#include "aaa_cpu_buffer.h"
#include "context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/aaa_target.h"
//#include "_.h"
//#include "_gpu.h"
//#include "_defer.h"


namespace gpu
{


   aaa_cpu_buffer::aaa_cpu_buffer()
   {

      defer_create_synchronization();

   }


   aaa_cpu_buffer::~aaa_cpu_buffer()
   {

   }


   void aaa_cpu_buffer::initialize_cpu_buffer(::gpu::context * pgpucontext)
   {

      m_pgpucontext = pgpucontext;

   }


   void aaa_cpu_buffer::set_size(const ::i32_size & size)
   {

      defer_construct_newø(m_pimagetarget);

      m_pimagetarget->set_size(size);

      if (m_pimagetarget->m_pimage.nok())
      {

         throw ::exception(error_resource);

      }

   }


   ::image::aaa_target* aaa_cpu_buffer::get_image_target()
   {

      if (!m_pimagetarget)
      {

         defer_construct_newø(m_pimagetarget);

      }

      return m_pimagetarget;

   }


   void aaa_cpu_buffer::gpu_read()
   {

      if (m_pimagetarget->m_pimage.nok())
      {

         return;

      }

   }


   void aaa_cpu_buffer::gpu_write()
   {

      if (m_pimagetarget->m_pimage.nok())
      {

         return;

      }


   }


   void aaa_cpu_buffer::set_pixels(const void* p, ::i32 w, ::i32 h, ::i32 s, bool bYSwap)
   {

      m_pimagetarget->set_image_pixels((const ::image32_t*)p, w, h, s, bYSwap);

   }


} // namespace gpu



