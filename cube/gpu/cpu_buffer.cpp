#include "framework.h"
#include "cpu_buffer.h"
#include "context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/target.h"
//#include "_.h"
//#include "_gpu.h"
//#include "_defer.h"


namespace gpu
{


   cpu_buffer::cpu_buffer()
   {

      defer_create_synchronization();

   }


   cpu_buffer::~cpu_buffer()
   {

   }


   void cpu_buffer::initialize_cpu_buffer(::gpu::context * pgpucontext)
   {

      m_pgpucontext = this;

   }


   void cpu_buffer::set_size(const ::int_size & size)
   {

      __defer_construct_new(m_pimagetarget);

      m_pimagetarget->set_size(size);

      if (m_pimagetarget->m_pimage.nok())
      {

         throw ::exception(error_resource);

      }

   }



   void cpu_buffer::gpu_read()
   {

      if (m_pimagetarget->m_pimage.nok())
      {

         return;

      }


   }


   void cpu_buffer::gpu_write()
   {

      if (m_pimagetarget->m_pimage.nok())
      {

         return;

      }


   }


   void cpu_buffer::set_pixels(const void* p, int w, int h, int s)
   {

      m_pimagetarget->set_image_pixels((const ::image32_t*)p, w, h, s);

   }


} // namespace gpu



