//
// Created by camilo on 16/02/2021. 22:00 BRT <3TBS_!!
//
#pragma once


#include "aura_posix/_.h"
#include <X11/Xlib.h>


namespace x11
{


   class CLASS_DECL_AURA display_lock
   {
   public:


      Display *         m_pdisplay;
      bool              m_bLocked;


      display_lock(Display * pdisplay, bool bInitialLock = true);
      ~display_lock();


      void lock();
      void unlock();


   };


} // namespace x11



