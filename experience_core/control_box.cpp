#include "framework.h"


namespace experience
{


   namespace core
   {


      control_box::control_box()
      {


      }


      control_box::~control_box()
      {

      }


      void control_box::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
      {


      }

      void control_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
      {

         if((get_top_level()->frame_is_transparent() && !get_top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
         {

            return;

         }

         auto rectClient = get_client_rect();

         if (rectClient.is_empty())
         {

            return;

         }

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         color32_t crBackground;

         if(get_top_level()->frame_is_transparent())
         {

            crBackground = argb(90,colorref_get_r_value(m_colorBackground),colorref_get_g_value(m_colorBackground),colorref_get_b_value(m_colorBackground));

         }
         else
         {

            crBackground = m_colorBackground;

         }

         pgraphics->fill_rectangle(rectClient, crBackground);

      }


      void control_box::_001OnShowWindow(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

      }


      void control_box::on_message_left_button_down(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

      }


      void control_box::on_message_left_button_up(::message::message * pmessage)
      {

         UNREFERENCED_PARAMETER(pmessage);

      }


      void control_box::_001OnTimer(::timer * ptimer)
      {

         ::experience::control_box::_001OnTimer(ptimer);

      }


      void control_box::install_message_routing(::channel *pframewindow)
      {

         ::experience::control_box::install_message_routing(pframewindow);

         MESSAGE_LINK(e_message_show_window, pframewindow, this, &control_box::_001OnShowWindow);
         MESSAGE_LINK(e_message_left_button_down, pframewindow, this, &control_box::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pframewindow, this, &control_box::on_message_left_button_up);

      }


      i32 control_box::calc_button_size(::draw2d::graphics_pointer & pgraphics)
      {

         return 26;

      }


      ::rectangle_i32 control_box::get_button_margin(enum_button ebutton)
      {

         if (e_button_close == ebutton)
         {

            return ::rectangle_i32(1, 4, 4, 4);

         }

         return ::rectangle_i32(1, 4, 2, 4);

      }


   } // namespace core


} // namespace experience



