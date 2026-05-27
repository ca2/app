// Created by camilo on 2022-02-06 09:28 <3ThomasBorregaardSorensen
#include "framework.h"
#include "button.h"
#include "still.h"
#include "acme/nano/graphics/icon.h"
#include "acme/nano/graphics/context.h"
#include "acme/windowing/window.h"
#include "acme/user/user/mouse.h"
#include "acme/user/micro/theme.h"



namespace micro
{


   still::~still()
   {

   }


   void still::on_draw(::nano::graphics::context * pgraphicscontext)
   {

            wstring wstrText(m_strText);


            if (m_strText.contains("Operating"))
            {

               information("Operating1");
               //return;

            }


      if (m_picon)
      {

         pgraphicscontext->draw(m_picon, 0, 0, m_rectangle.width(), m_rectangle.height());

         return;

      }

      //::pointer<::nano::graphics::pen>ppenBorder;

      //if (acme_windowing_window()->m_pacmeuserinteractionHover == this
      //   || has_keyboard_focus())
      //{

      //   ppenBorder = micro_theme()->m_ppenBorderFocus;

      //}
      //else
      //{

      //   ppenBorder = micro_theme()->m_ppenBorder;

      //}

      ::pointer<::nano::graphics::brush> pbrushText;
      ::pointer<::nano::graphics::font> pfontText;

      if (m_bHyperlink)
      {

         if (acme_windowing_window()->m_pacmeuserinteractionHover == this)
         {

            pbrushText = micro_theme()->m_pbrushHyperlinkHover;

            pfontText = micro_theme()->m_pfontHyperlinkHover;

            information("still hyperlink hover");

         }
         else
         {

            pbrushText = micro_theme()->m_pbrushHyperlink;

            pfontText = micro_theme()->m_pfontHyperlink;

            information("still hyperlink");

         }

      }
      else
      {

         pbrushText = micro_theme()->m_pbrushText;

         pfontText = micro_theme()->m_pfont;

      }

      i32_rectangle rectangleText(m_rectangle.size());

      rectangleText.inflate(1);



      pgraphicscontext->draw_text123(
         m_strText,
         rectangleText,
         e_align_center,
         e_draw_text_single_line,
         micro_theme()->m_pbrushWindow,
         pbrushText,
         pfontText);

   }


   void still::on_char(::i32 iChar)
   {

      if (iChar == '\r' || iChar == ' ')
      {

         ::pointer < ::micro::elemental > pelemental;

         pelemental = acme_windowing_window()->acme_user_interaction();

         if (pelemental)
         {

            pelemental->on_click(id(), nullptr);

         }

      }

   }


   void still::set_icon(::nano::graphics::icon * picon)
   {

      m_picon = picon;

   }


   void still::on_mouse_enter()
   {

      //if (m_bHyperlink)
      //{

      //   if (acme_windowing_window()->m_pacmeuserinteractionHover == this)
      //   {

      //      auto r = m_rectangle;

      //      r += acme_windowing_window()->m_rectangle.top_left();

      //      if (!r.contains(pmouse->m_pointAbsolute))
      //      {

      //         acme_windowing_window()->m_pacmeuserinteractionHover = nullptr;

      //         acme_windowing_window()->redraw();

      //      }

      //   }
      //   else
      //   {

      //      acme_windowing_window()->m_pacmeuserinteractionHover = this;

      information("still::on_mouse_enter");
            acme_windowing_window()->redraw();

      //   }

      //}
      
   }

   //   void still::fore_on_mouse_move(::user::mouse *pmouse)
   //{

   //   if (m_bHyperlink)
   //   {

   //      if (acme_windowing_window()->m_pacmeuserinteractionHover == this)
   //      {

   //         auto r = m_rectangle;

   //         r += acme_windowing_window()->m_rectangle.top_left();

   //         if (!r.contains(pmouse->m_pointAbsolute))
   //         {

   //            acme_windowing_window()->m_pacmeuserinteractionHover = nullptr;

   //            acme_windowing_window()->redraw();
   //         }
   //      }
   //      else
   //      {

   //         acme_windowing_window()->m_pacmeuserinteractionHover = this;

   //         acme_windowing_window()->redraw();
   //      }
   //   }
   //}


   void still::on_mouse_leave()
   {

      //if (m_bHyperlink)
      //{

      //   if (acme_windowing_window()->m_pacmeuserinteractionHover == this)
      //   {

      //      auto r = m_rectangle;

      //      r += acme_windowing_window()->m_rectangle.top_left();

      //      if (!r.contains(pmouse->m_pointAbsolute))
      //      {

      //         acme_windowing_window()->m_pacmeuserinteractionHover = nullptr;

      //         acme_windowing_window()->redraw();
      //      }
      //   }
      //   else
      //   {

      //      acme_windowing_window()->m_pacmeuserinteractionHover = this;

      information("still::on_mouse_leave");
            acme_windowing_window()->redraw();
         //}
      //}
   }

   bool still::is_keyboard_focusable()
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
      //   auto pdevice = createø < ::nano::graphics::context >();
      //
      //   auto size = pdevice->get_text_extents(m_strText, acme_windowing_window()->m_pfont);
      //
      //   m_rectangle.right = m_rectangle.left + size.cx;
      //
      //   m_rectangle.bottom = m_rectangle.top + size.cy;
      //
   }



} // namespace micro


