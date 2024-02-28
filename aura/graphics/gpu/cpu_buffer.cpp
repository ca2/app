#include "framework.h"
#include "cpu_buffer.h"
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



