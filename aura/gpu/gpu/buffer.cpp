#include "framework.h"
#include "_.h"
#include "_gpu.h"
#include "aura/graphics/draw2d/_draw2d.h"


namespace gpu
{


   buffer::buffer()
   {

      defer_create_mutex();

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



