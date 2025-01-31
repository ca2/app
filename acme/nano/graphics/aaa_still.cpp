// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "icon.h"
#include "still.h"
#include "interchange.h"
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



void still::on_draw(::nano::graphics::device * pnanodevice)
{

   if(m_picon)
   {

      pnanodevice->draw(m_picon, 0, 0, m_rectangle.width(), m_rectangle.height());


      return;

   }

   ::pointer<::nano::graphics::pen>ppenBorder;

   if (m_pinterchange->m_pchildHover == this || m_pinterchange->m_pchildFocus == this)
   {

      ppenBorder = m_pinterchange->m_ppenBorderFocus;

   }
   else
   {

      ppenBorder = m_pinterchange->m_ppenBorder;

   }

   wstring wstrText(m_strText);

   int_rectangle rectangleText(m_rectangle);

   rectangleText.inflate(1);

   pnanodevice->draw_text123(
      m_strText,
      rectangleText,
      e_align_center,
      e_draw_text_single_line,
      m_pinterchange->m_pbrushWindow,
      m_bHyperlink ? (has_capture() ?
         m_pinterchange->m_pbrushHyperlinkHover :
         m_pinterchange->m_pbrushHyperlink) : m_pinterchange->m_pbrushText,
      m_pinterchange->m_pfont);

}


void still::on_char(int iChar)
{

   if (iChar == '\r' || iChar == ' ')
   {

      m_pinterchange->on_click(id(), nullptr);

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

      if (m_pinterchange->m_pchildHover == this)
      {

         auto r = m_rectangle;

         r += m_pinterchange->m_rectangle.top_left();

         if (!r.contains(pmouse->m_pointAbsolute))
         {

            m_pinterchange->m_pchildHover = nullptr;

            m_pinterchange->redraw();

         }

      }
      else
      {

         m_pinterchange->m_pchildHover = this;

         m_pinterchange->redraw();

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


child::resize_to_fit();

//
//   auto pdevice = __øcreate < ::nano::graphics::device >();
//
//   auto size = pdevice->get_text_extents(m_strText, m_pinterchange->m_pfont);
//
//   m_rectangle.right() = m_rectangle.left() + size.cx();
//
//   m_rectangle.bottom() = m_rectangle.top() + size.cy();
//
}



   } // namespace user


} // namespace nano


