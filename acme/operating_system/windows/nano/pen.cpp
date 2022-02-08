//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/user/nano/_nano.h"
#include "_nano.h"


namespace windows
{


   nano_pen::nano_pen()
   {

      m_pthis = this;

   }


   nano_pen::~nano_pen()
   {

   }


   void nano_pen::update(::nano_device * pnanodevice)
   {

      if (m_bModified)
      {

         destroy();

         m_hgdiobj = ::CreatePen(PS_SOLID, m_iWidth, m_color.get_COLORREF());

         m_bModified = false;

      }

   }


} // namespace windows



