#include "framework.h"
#include "buffer.h"
#include "aura/graphics/image/image.h"
//#include "_.h"
//#include "_gpu.h"
//#include "_defer.h"


namespace gpu
{


   buffer::buffer()
   {

      defer_create_synchronization();

   }


   buffer::~buffer()
   {

   }


   void buffer::gpu_read()
   {

      if (m_pimage->nok())
      {

         return;

      }


   }


   void buffer::gpu_write()
   {

      if (m_pimage->nok())
      {

         return;

      }


   }


} // namespace gpu



