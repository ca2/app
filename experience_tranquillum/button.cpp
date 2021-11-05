﻿#include "framework.h"


namespace experience
{


   namespace tranquillum
   {

   
      button::button()
      {

      }


      button::~button()
      {

      }

      void button::_001OnClip(::draw2d::graphics_pointer & pgraphics)
      {

         ::experience::button::_001OnClip(pgraphics);

      }

      void button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
      {

      }


      void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if ((get_top_level()->frame_is_transparent() && !get_top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
         {

            return;

         }

         ::rectangle_i32 rectangleClient;

         ::user::interaction::get_client_rect(rectangleClient);

         if (rectangleClient.area() <= 0)
            return;

         color32_t crText;

         pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

         if (!is_window_enabled())
         {

            pgraphics->set(m_pcontrolbox->m_pbrushButtonBackDisabled);

            pgraphics->set(m_pcontrolbox->m_ppenButtonBackDisabled);

            crText = m_pcontrolbox->m_colorButtonForeDisabled;

         }
         else if (m_itemHover.is_set())
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

         ::rectangle_i32 rectangleEllipse(rectangleClient);

         //auto rW = get_window_rect();

         rectangleEllipse.deflate(0, 0, 2, 2);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleClient, pgraphics->m_pbrush->m_color);

         //pgraphics->FillEllipse(rectangleEllipse);

         //pgraphics->DrawEllipse(rectangleEllipse);

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

            m_pbrush->create_solid(::is_set(pgraphics->get_current_pen())
                                  ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

            pgraphics->set(m_pbrush);

            m_ppen->create_solid(1.0, ::is_set(pgraphics->get_current_pen())
                                ? pgraphics->get_current_pen()->m_color : argb(255, 255, 255, 255));

            pgraphics->set(m_ppen);

            ::rectangle_i32 rectangleIcon(rectangleEllipse);

            rectangleIcon.deflate(rectangleIcon.width() / 4, rectangleIcon.height() / 4);

            pgraphics->draw_stock_icon(rectangleIcon, m_estockicon);

            //pgraphics->FillSolidRect(rectangleEllipse, argb(255, 255, 255, 255));

         }

      }


      void button::install_message_routing(::channel * pchannel)
      {

         ::experience::button::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_show_window, pchannel, this, &button::on_message_show_window);

      }


      void button::on_message_show_window(::message::message * pmessage)
      {


         __pointer(::message::show_window) pshowwindow(pmessage);


         if (pshowwindow->m_bShow)
         {

            if (m_estockicon == e_stock_icon_restore)
            {

               output_debug_string("restore button is being shown");

            }

         }


      }


      void button::on_layout(::draw2d::graphics_pointer & pgraphics)
      {

         __construct(m_spregion);
         __construct(m_ppen);
         __construct(m_pbrush);
         
         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         m_spregion->create_ellipse(rectangleClient);

      }


      void button::on_hit_test(::item & item)
      {

         synchronous_lock synchronouslock(mutex());

         if (m_spregion.is_null())
         {

            item = ::e_element_none;

            return;

         }

         if (!m_spregion->contains(item.m_pointHitTest))
         {

            item = ::e_element_none;

            return;

         }

         item = ::e_element_client;

      }


      bool button::keyboard_focus_is_focusable() const
      {

         //return false && ::user::button::keyboard_focus_is_focusable();

         return false;


      }


   } // namespace tranquillum


} // namespace experience



