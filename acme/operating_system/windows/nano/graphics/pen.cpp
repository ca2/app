//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pen.h"
//#include "_nano.h"


namespace windows
{



   namespace nano
   {


      namespace graphics
      {

         pen::pen()
         {

            m_pthis = this;

         }


         pen::~pen()
         {

         }


         void pen::update(::nano::graphics::device* pnanodevice)
         {

            if (m_bModified)
            {

               destroy();

               m_hgdiobj = ::CreatePen(PS_SOLID, m_iWidth, win32_COLORREF(m_color));

               m_bModified = false;

            }

         }



      } // namespace graphics


   } // namespace nano


} // namespace windows



