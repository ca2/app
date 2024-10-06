// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "button.h"
#include "still.h"
#include "acme/nano/graphics/icon.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/windowing/window.h"
#include "acme/user/user/mouse.h"
#include "acme/nano/user/theme.h"



namespace nano
{

namespace user
{


still::~still()
{

}



void still::on_draw(::nano::graphics::device * pnanodevice)
{

   if(m_picon)
   {

      pnanodevice->draw(m_picon, 0, 0, m_rectangle.width(), m_rectangle.height());


      return;

   }

   ::pointer<::nano::graphics::pen>ppenBorder;

   if (nano_windowing_window()->m_pnanouserinteractionHover == this
      || nano_windowing_window()->m_pnanouserinteractionFocus == this)
   {

      ppenBorder = nano_user_theme()->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = nano_user_theme()->m_ppenBorder;

   }

   wstring wstrText(m_strText);

   rectangle_i32 rectangleText(m_rectangle);

   rectangleText.inflate(1);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText,
      e_align_center,
      e_draw_text_single_line,
      nano_user_theme()->m_pbrushWindow,
      m_bHyperlink ? (has_capture() ?
         nano_user_theme()->m_pbrushHyperlinkHover :
         nano_user_theme()->m_pbrushHyperlink) : nano_user_theme()->m_pbrushText,
      nano_user_theme()->m_pfont);

}


void still::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      nano_windowing_window()->nano_user_interaction()->on_click(m_atom, nullptr);

   }

}


void still::set_icon(::nano::graphics::icon * picon)
{

   m_picon = picon;

}


void still::on_mouse_move(::user::mouse * pmouse)
{

   if (m_bHyperlink)
   {

      if (nano_windowing_window()->m_pnanouserinteractionHover == this)
      {

         auto r = m_rectangle;

         r += nano_windowing_window()->m_rectangle.top_left();

         if (!r.contains(pmouse->m_pointAbsolute))
         {

            nano_windowing_window()->m_pnanouserinteractionHover = nullptr;

            nano_windowing_window()->redraw();

         }

      }
      else
      {

         nano_windowing_window()->m_pnanouserinteractionHover = this;

         nano_windowing_window()->redraw();

      }

   }

}


bool still::is_focusable()
{

   return m_bHyperlink;

}


void still::resize_to_fit()
{

   if(m_picon)
   {

      m_rectangle.set_size(m_picon->size());

      return;

   }


::nano::user::interaction::resize_to_fit();

//
//   auto pdevice = __create < ::nano::graphics::device >();
//
//   auto size = pdevice->get_text_extents(m_strText, nano_windowing_window()->m_pfont);
//
//   m_rectangle.right() = m_rectangle.left() + size.cx();
//
//   m_rectangle.bottom() = m_rectangle.top() + size.cy();
//
}



   } // namespace user


} // namespace nano


