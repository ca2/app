// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardS�rensen
#include "framework.h"
#include "_nano.h"


nano_still::~nano_still()
{


}


void nano_still::on_draw(nano_device * pnanodevice)
{

   __pointer(nano_pen) ppenBorder;

   if (m_pwindow->m_pchildHover == this || m_pwindow->m_pchildFocus == this)
   {

      ppenBorder = m_pwindow->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = m_pwindow->m_ppenBorder;

   }

   wstring wstrText(m_strText);

   rectangle_i32 rectangleText(m_rectangle);

   rectangleText.inflate(1);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText,
      e_align_center,
      e_draw_text_single_line,
      m_pwindow->m_pbrushWindow,
      m_bHyperlink ? (has_capture() ?
         m_pwindow->m_pbrushHyperlinkHover :
         m_pwindow->m_pbrushHyperlink) : m_pwindow->m_pbrushText,
      m_pwindow->m_pfont);

}


void nano_still::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      m_pwindow->on_click(m_atom);

   }

}


void nano_still::on_mouse_move(int x, int y)
{

   if (m_bHyperlink)
   {

      if (m_pwindow->m_pchildHover == this)
      {

         auto r = m_rectangle;

         r += m_pwindow->m_rectangle.top_left();

         if (!r.contains(::point_i32(x, y)))
         {

            m_pwindow->m_pchildHover = nullptr;

            m_pwindow->redraw();

         }

      }
      else
      {

         m_pwindow->m_pchildHover = this;

         m_pwindow->redraw();

      }

   }

}


bool nano_still::is_focusable() const
{

   return m_bHyperlink;

}


void nano_still::resize_to_fit()
{

   auto pdevice = __create < nano_device >();

   auto size = pdevice->get_text_extents(m_strText, m_pwindow->m_pfont);

   m_rectangle.right = m_rectangle.left + size.cx;

   m_rectangle.bottom = m_rectangle.top + size.cy;

}
