// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSørensen
#include "framework.h"
#include "_nano.h"


void nano_button::on_draw(nano_device * pnanodevice)
{

   //::SelectObject(hdc, m_pwindow->m_hbrushWindow);

   __pointer(nano_pen) ppenBorder;

   if (m_pwindow->m_pchildFocus == this)
   {

      ppenBorder = m_pwindow->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = m_pwindow->m_ppenBorder;

   }

   pnanodevice->rectangle(m_rectangle, m_pwindow->m_pbrushWindow, ppenBorder);

   wstring wstrText(m_strText);

   rectangle_i32 rectangleText(m_rectangle);

   rectangleText.deflate(4);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText, 
      e_align_center,
      e_draw_text_single_line, 
      m_pwindow->m_pbrushWindow,
      m_pwindow->m_pbrushText, 
      m_pwindow->m_pfont);

}


void nano_button::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      m_pwindow->on_click(m_atom, INT_MIN, INT_MIN);

   }

}


bool nano_button::is_focusable() const
{

   return true;

}



//void nano_still::resize_to_fit()
//{
//
//   auto pdevice = __create < nano_device >();
//
//   auto size = pdevice->get_text_extents(m_strText, m_pwindow->m_pfont);
//
//   m_rectangle.right = m_rectangle.left + size.cx;
//
//   m_rectangle.bottom = m_rectangle.top + size.cy;
//
//}


void popup_button::on_click(const ::atom & atom, int x, int y)
{

   m_atomResult = atom;

   destroy();

}



