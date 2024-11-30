#include "framework.h"
#include "control_box.h"
#include "acme/constant/message.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/graphics/draw2d/graphics.h"


namespace experience_nanoui
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

      if ((top_level()->frame_is_transparent() && !top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::color::color crBackground;

      if (top_level()->frame_is_transparent())
      {

         crBackground = m_colorBackground & ::opacity(90);

      }
      else
      {

         crBackground = m_colorBackground;

      }

      pgraphics->fill_rectangle(rectangleX, crBackground);

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

   }


   void control_box::on_timer(::timer * ptimer)
   {

      ::experience::control_box::on_timer(ptimer);

   }


   void control_box::install_message_routing(::channel * pframewindow)
   {

      ::experience::control_box::install_message_routing(pframewindow);

      MESSAGE_LINK(e_message_show_window, pframewindow, this, &control_box::on_message_show_window);
      MESSAGE_LINK(e_message_left_button_down, pframewindow, this, &control_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pframewindow, this, &control_box::on_message_left_button_up);

   }


   int control_box::calculate_button_size(::draw2d::graphics_pointer & pgraphics)
   {

      return 26;

   }


   ::int_rectangle control_box::get_button_margin(::experience::enum_button ebutton)
   {

      if (::experience::e_button_close == ebutton)
      {

         return ::int_rectangle(1, 4, 4, 4);

      }

      return ::int_rectangle(1, 4, 2, 4);

   }


} // namespace experience_nanoui



