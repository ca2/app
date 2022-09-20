// Extracted from device_lock, Changed and Organized by camilo on 2021-09-04 05:46 BRT <3ThomasBS__!!
#pragma once

//#error
//
//#ifdef _UWP
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
////#ifdef _UWP
////
////      comptr < ID2D1Multitask > m_D2DMultitask;
////
////#endif
//
//      ::acme::system * m_psystem;
//
//      device_lock(::user::interaction * pinteraction);
//      ~device_lock();
//
//
//   };


   class CLASS_DECL_AURA lock
   {
   public:


      ::draw2d::draw2d * m_pdraw2d;

      lock(::object * pobject)
      {

         m_pdraw2d = pobject->m_psystem->m_paurasystem->draw2d();

         m_pdraw2d->lock_device();

      }

      ~lock()
      {

         m_pdraw2d->unlock_device();

      }

   };


} // namespace draw2d


