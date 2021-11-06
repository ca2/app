#include "framework.h"


namespace experience
{


   namespace core
   {


      button::button()
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

         ::duration t1 = ::duration::now();

         if ((get_top_level()->frame_is_transparent() && !get_top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
         {

            return;

         }

         ::duration d1 = t1.elapsed();

         if (d1 > 50_ms)
         {

            CATEGORY_INFORMATION(prodevian, "is_activeis_activeis_active more than 50ms user::button wndframe_core");

         }

         auto rectangleClient = get_client_rect();

         if (rectangleClient.is_empty())
         {

            return;

         }

         ::color::color crText = argb(255, 255, 255, 255);

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_anti_alias_8x4);

         if (m_pcontrolbox)
         {

            if (!is_window_enabled())
            {

               pgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

               pgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

               crText = m_pcontrolbox->m_colorButtonForeDisabled;

            }
            else if (hover_item().is_set())
            {

               pgraphics->set(m_pcontrolbox->m_pbrushButtonBackSel);

               pgraphics->set(m_pcontrolbox->m_ppenButtonBackSel);

               crText = m_pcontrolbox->m_colorButtonForeSel;

            }
            else if (has_keyboard_focus())
            {

               pgraphics->set(m_pcontrolbox->m_pbrushButtonBackFocus);

               pgraphics->set(m_pcontrolbox->m_ppenButtonBackFocus);

               crText = m_pcontrolbox->m_colorButtonForeFocus;

            }
            else
            {

               pgraphics->set(m_pcontrolbox->m_pbrushButtonBack);

               pgraphics->set(m_pcontrolbox->m_ppenButtonBack);

               crText = m_pcontrolbox->m_colorButtonFore;

            }

         }

         ::rectangle_i32 rectangleEllipse(rectangleClient);

         rectangleEllipse.deflate(0, 0, 2, 2);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_ellipse(rectangleEllipse);

         pgraphics->draw_ellipse(rectangleEllipse);

         if (m_estockicon == e_stock_icon_none)
         {

            string str;

            get_window_text(str);

            pgraphics->set_font(this, ::e_element_none);

            pgraphics->set_text_color(crText);

            pgraphics->draw_text(str, rectangleClient, e_align_center, e_draw_text_single_line);

         }
         else
         {

            auto pbrush = __create < ::draw2d::brush >();

            if (pbrush && pgraphics->get_current_pen())
            {

               pbrush->create_solid(pgraphics->get_current_pen()->m_color);

            }

            pgraphics->set(pbrush);

            auto ppen = __create < ::draw2d::pen > ();

            ppen->create_solid(1.0f, __acolor(255, 255, 255, 255));

            pgraphics->set(ppen);

            ::rectangle_i32 rectangleIcon(rectangleEllipse);

            rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

            pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

         }

         ::duration d2 = t1.elapsed();

         if (d2 > 50_ms)
         {

            CATEGORY_INFORMATION(prodevian, "(d2) more than 50ms user::button wndframe_core");

         }

      }


      void button::install_message_routing(::channel *pframewindow)
      {

         ::experience::button::install_message_routing(pframewindow);

      }


      void button::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         auto rectangleClient = get_client_rect();

         __defer_construct(m_pregion);

         m_pregion->create_ellipse(rectangleClient);

      }



      bool button::keyboard_focus_is_focusable() const
      {

         return false;

      }


   } // namespace core


} // namespace experience



