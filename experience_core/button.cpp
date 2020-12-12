#include "framework.h"


namespace experience
{


   namespace aura
   {


      button::button() :
         m_spregion(e_create)
      {

      }


      button::~button()
      {

      }


      void button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
      {

      }


      void button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
      {

         ::user::interaction::_001OnClip(pgraphics);

      }


      void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         millis t1 = millis::now();

         if ((GetTopLevel()->frame_is_transparent() && !GetTopLevel()->is_active()) || !GetTopLevelFrame()->m_bShowControlBox)
         {

            return;

         }

         millis d1 = t1.elapsed();

         if (d1 > 50)
         {

            CINFO(prodevian) ("is_activeis_activeis_active more than 50ms user::button wndframe_core");

         }

         auto rectClient = get_client_rect();

         if (rectClient.is_empty())
         {

            return;

         }

         color32_t crText = ARGB(255, 255, 255, 255);

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_anti_alias_8x4);

         if (m_pcontrolbox)
         {

            if (!is_window_enabled())
            {

               pgraphics->set(m_pcontrolbox->m_brushButtonBackDisabled);

               pgraphics->set(m_pcontrolbox->m_penButtonBackDisabled);

               crText = m_pcontrolbox->m_crButtonForeDisabled;

            }
            else if (hover_item().is_set())
            {

               pgraphics->set(m_pcontrolbox->m_brushButtonBackSel);

               pgraphics->set(m_pcontrolbox->m_penButtonBackSel);

               crText = m_pcontrolbox->m_crButtonForeSel;

            }
            else if (has_focus())
            {

               pgraphics->set(m_pcontrolbox->m_brushButtonBackFocus);

               pgraphics->set(m_pcontrolbox->m_penButtonBackFocus);

               crText = m_pcontrolbox->m_crButtonForeFocus;

            }
            else
            {

               pgraphics->set(m_pcontrolbox->m_brushButtonBack);

               pgraphics->set(m_pcontrolbox->m_penButtonBack);

               crText = m_pcontrolbox->m_crButtonFore;

            }

         }

         ::rect rectEllipse(rectClient);

         rectEllipse.deflate(0, 0, 2, 2);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->fill_ellipse(rectEllipse);

         pgraphics->draw_ellipse(rectEllipse);

         if (m_estockicon == stock_icon_none)
         {

            string str;

            get_window_text(str);

            pgraphics->set_font(this);

            pgraphics->set_text_color(crText);

            pgraphics->draw_text(str, rectClient, e_align_center, e_draw_text_single_line);

         }
         else
         {

            ::draw2d::brush_pointer brush(e_create);

            if (brush && pgraphics->get_current_pen())
            {

               brush->create_solid(pgraphics->get_current_pen()->m_color);

            }

            pgraphics->set(brush);

            ::draw2d::pen_pointer pen(e_create);

            pen->create_solid(1.0f, __acolor(255, 255, 255, 255));

            pgraphics->set(pen);

            ::rect rectIcon(rectEllipse);

            rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

            pgraphics->draw_stock_icon(rectIcon, m_estockicon);

         }

         millis d2 = t1.elapsed();

         if (d2 > 50)
         {

            CINFO(prodevian)( "(d2) more than 50ms user::button wndframe_core");

         }

      }


      void button::install_message_routing(::channel *pframewindow)
      {

         ::experience::button::install_message_routing(pframewindow);

      }


      void button::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         auto rectClient = get_client_rect();

         m_spregion->create_oval(rectClient);

      }


      void button::on_hit_test(::user::item & item)
      {

         sync_lock sl(mutex());

         if (m_spregion.is_null())
         {

            item = ::user::e_element_none;

            return;

         }

         if (!m_spregion->contains(item.m_pointHitTest))
         {

            item = ::user::e_element_none;

            return;

         }

         item = ::user::e_element_client;

      }


      bool button::keyboard_focus_is_focusable()
      {

         return false;

      }


   } // namespace aura


} // namespace experience



