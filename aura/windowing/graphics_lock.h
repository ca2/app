// Created by camilo from graphics/draw2d/device_lock on 2021-09-04 06:08 BRT <3ThomasBS__!!
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


namespace windowing
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
//      ::acme::system * acmesystem();
//
//      device_lock(::user::interaction * pinteraction);
//      ~device_lock();
//
//
//   };


   class CLASS_DECL_AURA graphics_lock 
   {
   public:

      
      ::pointer<::windowing::window>        m_pwindow;


      graphics_lock(::windowing::window * pwindow) :
         m_pwindow(pwindow)
      {

         if (m_pwindow)
         {

            m_pwindow->graphics_lock();

         }

      }


      ~graphics_lock()
      {

         if (m_pwindow)
         {

            m_pwindow->graphics_unlock();

         }

      }


   };


} // namespace windowing


