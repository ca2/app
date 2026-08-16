// Created by camilo on 2026-07-31 16:23 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "window_attachment.h"
#include "aura/windowing/window.h"


namespace draw2d
{

   
   window_attachment::window_attachment()
   {

      //m_iCurrentFrame3 = -1;
      //m_iFrameSerial2 = -1;
      //m_iFrameCount = 1;

   }


   window_attachment::~window_attachment() 
   {
   
   
   }

   
   void window_attachment::initialize_window_attachment(::windowing::window * pwindow)
   {

      pwindow = pwindow;

   }


   ::draw2d::window_attachment * window_attachment::get(::acme::user::interaction * pacmeuserinteraction)
   {

      if (::is_null(pacmeuserinteraction))
      {

         return nullptr;

      }

      auto pacmewindowingwindow = pacmeuserinteraction->acme_windowing_window();

      if (::is_null(pacmewindowingwindow))
      {

         return nullptr;

      }

      auto pdraw2dwindowattachment = ::draw2d::window_attachment::get(pacmewindowingwindow);

      if (::is_null(pdraw2dwindowattachment))
      {

         return nullptr;

      }

      return pdraw2dwindowattachment;

   }


   ::draw2d::window_attachment * window_attachment::get(::acme::windowing::window * pacmewindowingwindow)
   {

      if (::is_null(pacmewindowingwindow))
      {

         return nullptr;

      }

      ::cast < ::windowing::window > pwindow = pacmewindowingwindow;

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      auto pdraw2dwindowattachment = pwindow->m_pdraw2dwindowattachment;

      if (::is_null(pdraw2dwindowattachment))
      {

         return nullptr;

      }

      return pdraw2dwindowattachment;

   }


} // namespace draw2d



