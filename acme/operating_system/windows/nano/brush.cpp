//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "brush.h"
//#include "_nano.h"


namespace windows
{


   nano_brush::nano_brush()
   {

      m_pthis = this; 

   }


   nano_brush::~nano_brush()
   {

   }


   void nano_brush::update(::nano_device * pnanodevice)
   {

      if (m_bModified)
      {

         destroy();

         m_hgdiobj = ::CreateSolidBrush(win32_COLORREF(m_color));

         m_bModified = false;

      }

   }


} // namespace windows




