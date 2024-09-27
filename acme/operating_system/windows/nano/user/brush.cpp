//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "brush.h"
//#include "_nano.h"


namespace windows
{



   namespace nano
   {


      namespace user
      {

         brush::brush()
         {

            m_pthis = this;

         }


         brush::~brush()
         {

         }


         void brush::update(::nano::graphics::device* pnanodevice)
         {

            if (m_bModified)
            {

               destroy();

               m_hgdiobj = ::CreateSolidBrush(win32_COLORREF(m_color));

               m_bModified = false;

            }

         }



      } // namespace user


   } // namespace nano


} // namespace windows




