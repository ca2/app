//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "brush.h"
//#include "_nano.h"


namespace windows
{


   ::nano::user::brush::nano::user::brush()
   {

      m_pthis = this; 

   }


   ::nano::user::brush::~::nano::user::brush()
   {

   }


   void ::nano::user::brush::update(::nano::user::device * pnanodevice)
   {

      if (m_bModified)
      {

         destroy();

         m_hgdiobj = ::CreateSolidBrush(win32_COLORREF(m_color));

         m_bModified = false;

      }

   }


} // namespace windows




