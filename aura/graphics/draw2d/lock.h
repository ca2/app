// Extracted from device_lock, Changed and Organized by camilo on 2021-09-04 05:46 BRT <3ThomasBS__!!
#pragma once

//#error
//
//#ifdef UNIVERSAL_WINDOWS
//
//#include "acme/operating_system/windows_common/comptr.h"
//#include <d2d1_1.h>
//
//#endif
//

#include "draw2d.h"

namespace draw2d
{
//
//
//   class CLASS_DECL_AURA device_lock
//   {
//   public:
//
////#ifdef UNIVERSAL_WINDOWS
////
////      comptr < ID2D1Multitask > m_D2DMultitask;
////
////#endif
//
//      ::platform::system * system();
//
//      device_lock(::user::interaction * pinteraction);
//      ~device_lock();
//
//
//   };


   class CLASS_DECL_AURA lock
   {
   public:

      bool m_bLocked = false;
      ::draw2d::draw2d * m_pdraw2d;

      lock(::particle* pparticle);

      ~lock();


      void unlock();

   };


} // namespace draw2d


