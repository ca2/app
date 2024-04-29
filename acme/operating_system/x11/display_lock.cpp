//
// Created by camilo on 16/02/2021. 22:05 BRT <3TBS_!!
//
#include "framework.h"
//#ifdef WITH_X11
//#include <X11/Xlib-xcb.h>
//#endif
#include "display_lock.h"
#include "acme/platform/system.h"


namespace x11
{


   display_lock::display_lock(Display * pdisplay, bool bInitialLock) :
      m_pdisplay(pdisplay),
      m_bLocked(false)
   {

      if(bInitialLock)
      {

         lock();

      }

   }


   display_lock::~display_lock()
   {

      unlock();

   }


   void display_lock::lock()
   {

      auto pdisplay = m_pdisplay;

      if(::is_null(pdisplay))
      {

         return;

      }

      auto pplatform = ::platform::get();

      if(::is_null(pplatform))
      {

         return;

      }

      auto psystem = pplatform->system();

      if(::is_null(psystem))
      {

         return;

      }

      if(!m_bLocked)
      {

         if(!psystem->x11_synchronization()->_wait(30_s))
         {

            return;

         }

         m_bLocked = true;

         XLockDisplay((Display *) m_pdisplay);

      }

   }


   void display_lock::unlock()
   {

      if(m_bLocked)
      {

         XUnlockDisplay((Display *) m_pdisplay);

         m_bLocked = false;

         auto pplatform = ::platform::get();

         if(::is_null(pplatform))
         {

            return;

         }

         auto psystem = pplatform->system();

         if(::is_null(psystem))
         {

            return;

         }

         psystem->x11_synchronization()->unlock();

      }

   }


} // namespace x11



