// From graphics.cpp by camilo on 2026-07-31 20:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "buffer_item.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/window.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/image.h"


namespace graphics
{


   //::draw2d::graphics_lease buffer_item::acquire_graphics()
   //{

   //   return ::transfer(m_pimageBufferItem->acquire_graphics());

   //}


   //::draw2d::graphics_pointer buffer_item::owned_graphics()
   ::draw2d::graphics_lease buffer_item::acquire_graphics()
   {

      if (m_pgraphicsBufferItem)
      {

         return { system()->draw2d(), m_pgraphicsBufferItem, nullptr, true };

      }
      else
      {

         return ::transfer(m_pimageBufferItem->acquire_graphics());

      }

      //if (pgraphics)
      //{

      //   pgraphics->m_egraphics = m_egraphics;

      //}

      //if (!pgraphics->m_callbackImage32CpuBuffer)
      //{

      //   pgraphics->m_callbackImage32CpuBuffer = [this](const ::image32_t * pimage32, ::i32 cx, ::i32 cy, ::i32 scan)
      //      {

      //         //_synchronous_lock synchronouslock(this->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //         m_pimage2->image32()->copy(cx, cy, m_pimage2->m_iScan, pimage32, scan);

      //      };

      //}

      //return ::transfer(pgraphics);

   }





   void buffer_item::switch_to_draw()
   {

      m_egraphics = e_graphics_draw;

      //owned_graphics();

      //m_pimageBufferItem->set_owned_graphics();


   }


   void buffer_item::destroy()
   {

      ::particle::destroy();

      m_pmutex.release();

      m_pimageBufferItem.defer_destroy_and_release();

      //m_pgraphicsBufferItem.release();

      //m_pwindowbuffer.release();

   }


} // namespace graphics



