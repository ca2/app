// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "button.h"
#include "still.h"
#include "acme/nano/graphics/icon.h"
#include "acme/nano/graphics/device.h"
#include "acme/windowing/window.h"
#include "acme/user/user/mouse.h"
#include "acme/user/micro/theme.h"



namespace micro
{


   still::~still()
   {

   }



   void still::on_draw(::nano::graphics::device * pmicrodevice)
   {

      if (m_picon)
      {

         pmicrodevice->draw(m_picon, 0, 0, m_rectangle.width(), m_rectangle.height());


         return;

      }

      ::pointer<::nano::graphics::pen>ppenBorder;

      if (acme_windowing_window()->m_pacmeuserinteractionHover == this
         || acme_windowing_window()->m_pacmeuserinteractionFocus == this)
      {

         ppenBorder = micro_theme()->m_ppenBorderFocus;

      }
      else
      {

         ppenBorder = micro_theme()->m_ppenBorder;

      }

      wstring wstrText(m_strText);

      rectangle_i32 rectangleText(m_rectangle);

      rectangleText.inflate(1);

      pmicrodevice->draw_text123(
         m_strText,
         rectangleText,
         e_align_center,
         e_draw_text_single_line,
         micro_theme()->m_pbrushWindow,
         m_bHyperlink ? (has_capture() ?
            micro_theme()->m_pbrushHyperlinkHover :
            micro_theme()->m_pbrushHyperlink) : micro_theme()->m_pbrushText,
         micro_theme()->m_pfont);

   }


   void still::on_char(int iChar)
   {

      if (iChar == '\r' || iChar == ' ')
      {

         ::pointer < ::micro::elemental > pelemental;

         pelemental = acme_windowing_window()->acme_user_interaction();

         if (pelemental)
         {

            pelemental->on_click(m_atom, nullptr);

         }

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

         if (acme_windowing_window()->m_pacmeuserinteractionHover == this)
         {

            auto r = m_rectangle;

            r += acme_windowing_window()->m_rectangle.top_left();

            if (!r.contains(pmouse->m_pointAbsolute))
            {

               acme_windowing_window()->m_pacmeuserinteractionHover = nullptr;

               acme_windowing_window()->redraw();

            }

         }
         else
         {

            acme_windowing_window()->m_pacmeuserinteractionHover = this;

            acme_windowing_window()->redraw();

         }

      }

   }


   bool still::is_focusable()
   {

      return m_bHyperlink;

   }


   void still::resize_to_fit()
   {

      if (m_picon)
      {

         m_rectangle.set_size(m_picon->size());

         return;

      }


      ::micro::elemental::resize_to_fit();

      //
      //   auto pdevice = __create < ::nano::graphics::device >();
      //
      //   auto size = pdevice->get_text_extents(m_strText, acme_windowing_window()->m_pfont);
      //
      //   m_rectangle.right() = m_rectangle.left() + size.cx();
      //
      //   m_rectangle.bottom() = m_rectangle.top() + size.cy();
      //
   }



} // namespace micro


