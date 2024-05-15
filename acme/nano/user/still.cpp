// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "still.h"
#include "window.h"
#include "device.h"
#include "button.h"
#include "acme/user/user/mouse.h"



namespace nano
{

namespace user
{


still::~still()
{

}



void still::on_draw(::nano::user::device * pnanodevice)
{

   ::pointer<::nano::user::pen>ppenBorder;

   if (m_pnanowindow->m_pchildHover == this || m_pnanowindow->m_pchildFocus == this)
   {

      ppenBorder = m_pnanowindow->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = m_pnanowindow->m_ppenBorder;

   }

   wstring wstrText(m_strText);

   rectangle_i32 rectangleText(m_rectangle);

   rectangleText.inflate(1);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText,
      e_align_center,
      e_draw_text_single_line,
      m_pnanowindow->m_pbrushWindow,
      m_bHyperlink ? (has_capture() ?
         m_pnanowindow->m_pbrushHyperlinkHover :
         m_pnanowindow->m_pbrushHyperlink) : m_pnanowindow->m_pbrushText,
      m_pnanowindow->m_pfont);

}


void still::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      m_pnanowindow->on_click(m_atom, nullptr);

   }

}


void still::on_mouse_move(::user::mouse * pmouse)
{

   if (m_bHyperlink)
   {

      if (m_pnanowindow->m_pchildHover == this)
      {

         auto r = m_rectangle;

         r += m_pnanowindow->m_rectangle.top_left();

         if (!r.contains(pmouse->m_pointAbsolute))
         {

            m_pnanowindow->m_pchildHover = nullptr;

            m_pnanowindow->redraw();

         }

      }
      else
      {

         m_pnanowindow->m_pchildHover = this;

         m_pnanowindow->redraw();

      }

   }

}


bool still::is_focusable() const
{

   return m_bHyperlink;

}


//void still::resize_to_fit()
//{
//
//   auto pdevice = __create < ::nano::user::device >();
//
//   auto size = pdevice->get_text_extents(m_strText, m_pnanowindow->m_pfont);
//
//   m_rectangle.right() = m_rectangle.left() + size.cx();
//
//   m_rectangle.bottom() = m_rectangle.top() + size.cy();
//
//}



   } // namespace user


} // namespace nano


