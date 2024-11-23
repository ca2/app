// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
#include "framework.h"
#include "button.h"
#include "interchange.h"
#include "device.h"
#include "popup_button.h"

namespace nano
{

   namespace user
   {
   

void button::on_draw(::nano::graphics::device * pnanodevice)
{

   //::SelectObject(hdc, m_pinterchange->m_hbrushWindow);

   ::pointer<::nano::graphics::pen>ppenBorder;

   if (m_pinterchange->m_pchildFocus == this)
   {

      ppenBorder = m_pinterchange->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = m_pinterchange->m_ppenBorder;

   }

   pnanodevice->rectangle(m_rectangle, m_pinterchange->m_pbrushWindow, ppenBorder);

   wstring wstrText(m_strText);

   int_rectangle rectangleText(m_rectangle);

   rectangleText.deflate(4);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText, 
      e_align_center,
      e_draw_text_single_line, 
      m_pinterchange->m_pbrushWindow,
      m_pinterchange->m_pbrushText, 
      m_pinterchange->m_pfont);

}


void button::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      m_pinterchange->on_click(m_atom, nullptr);

   }

}


bool button::is_focusable()
{

   return true;

}


//void nano_still::resize_to_fit()
//{
//
//   auto pdevice = __øcreate < ::nano::graphics::device >();
//
//   auto size = pdevice->get_text_extents(m_strText, m_pinterchange->m_pfont);
//
//   m_rectangle.right() = m_rectangle.left() + size.cx();
//
//   m_rectangle.bottom() = m_rectangle.top() + size.cy();
//
//}






   } // namespace user


} // namespace nano


