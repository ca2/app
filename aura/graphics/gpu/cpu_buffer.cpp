#include "framework.h"
#include "cpu_buffer.h"
#include "context.h"
#include "aura/graphics/image/image.h"
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

      //m_pbuffer->m_pimage = image()->create_image(size);

      m_pixmap.create(m_memory, size);

      if (m_pixmap.nok())
      {

         throw ::exception(error_resource);

      }

   }



   void cpu_buffer::gpu_read()
   {

      if (m_pixmap.nok())
      {

         return;

      }


   }


   void cpu_buffer::gpu_write()
   {

      if (m_pixmap.nok())
      {

         return;

      }


   }


} // namespace gpu



