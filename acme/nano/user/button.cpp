// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
#include "framework.h"
#include "button.h"
#include "popup_button.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/user/theme.h"
#include "acme/nano/windowing/window.h"


namespace nano
{


   namespace user
   {
   

void button::on_draw(::nano::graphics::device * pnanodevice)
{

   //::SelectObject(hdc, m_pinterchange->m_hbrushWindow);

   ::pointer<::nano::graphics::pen>ppenBorder;

   if (nano_windowing_window()->m_pnanouserinteractionFocus == this)
   {

      ppenBorder = nano_user_theme()->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = nano_user_theme()->m_ppenBorder;

   }

   pnanodevice->rectangle(m_rectangle, nano_user_theme()->m_pbrushWindow, ppenBorder);

   wstring wstrText(m_strText);

   rectangle_i32 rectangleText(m_rectangle);

   rectangleText.deflate(4);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText, 
      e_align_center,
      e_draw_text_single_line, 
      nano_user_theme()->m_pbrushWindow,
      nano_user_theme()->m_pbrushText,
      nano_user_theme()->m_pfont);

}


void button::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      ::pointer < ::nano::user::elemental > pelemental;

      pelemental = nano_windowing_window()->nano_user_interaction();

      if (pelemental)
      {

         pelemental->on_click(m_atom, nullptr);

      }

   }

}


bool button::is_focusable()
{

   return true;

}


//void nano_still::resize_to_fit()
//{
//
//   auto pdevice = __create < ::nano::graphics::device >();
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


