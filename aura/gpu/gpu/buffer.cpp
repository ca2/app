#include "framework.h"
#include "_.h"
#include "_gpu.h"
#include "aura/graphics/image/image.h"
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

      if (!::is_ok(m_pimage))
      {

         return;

      }


   }


   void buffer::gpu_write()
   {

      if (!::is_ok(m_pimage))
      {

         return;

      }


   }


} // namespace gpu



