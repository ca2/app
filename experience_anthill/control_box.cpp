#include "framework.h"


namespace experience
{


   namespace anthill
   {


      control_box::control_box()
      {

         m_iDefaultButtonMargin = 0;

         m_pfontMarlett->create_point_font("Marlett", 24);

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

         ::rectangle_i32 rectangleClient = get_client_rect();

         if (rectangleClient.is_empty())
         {
      
            return;
      
         }

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         color32_t crBackground;

         if(get_top_level()->frame_is_transparent())
         {

            crBackground = m_colorBackground & 100_opacity;

         }
         else
         {

            crBackground = m_colorBackground;

         }

         if (m_colorBackground.is_ok())
         {

            pgraphics->fill_rectangle(rectangleClient, m_colorBackground);

         }

      }


      void control_box::on_message_show_window(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

      }


      void control_box::on_message_left_button_down(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

      }


      void control_box::on_message_left_button_up(::message::message * pmessage)
      {

         __UNREFERENCED_PARAMETER(pmessage);

         set_need_redraw();

      }


      void control_box::_001OnTimer(::timer * ptimer)
      {

         ::experience::control_box::_001OnTimer(ptimer);

      }


      void control_box::install_message_routing(::channel * pchannel)
      {

         ::experience::control_box::install_message_routing(pchannel);

         MESSAGE_LINK(e_message_show_window, pchannel, this, &control_box::on_message_show_window);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &control_box::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_up, pchannel, this, &control_box::on_message_left_button_up);

      }


   } // namespace anthill


} // namespace experience



