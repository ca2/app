#include "framework.h"
#include "control_box.h"
#include "acme/constant/message.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"


namespace experience_tranquillum
{


   control_box::control_box()
   {
   
      m_iDefaultButtonMargin = 1;

      m_colorBackground.set(0, 0, 0, 0);

   }


   control_box::~control_box()
   {

   }


   void control_box::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }
   

   void control_box::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if((top_level()->frame_is_transparent() && !top_level()->is_active_window()) || !top_level_frame()->m_bShowControlBox)
      {

         return;

      }

      auto rectangleX = this->rectangle();

      if (rectangleX.area() <= 0)
         return;

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      ::color::color crBackground;

      if(top_level()->frame_is_transparent())
      {

         crBackground &= ::opacity(90);

      }
      else
      {

         crBackground = m_colorBackground;

      }

      if (m_colorBackground.non_transparent())
      {

         pgraphics->fill_rectangle(rectangleX, m_colorBackground);

      }

   }


   void control_box::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }
   
   
   void control_box::on_message_create(::message::message * pmessage)
   {
         
      __øconstruct(m_pfontMarlett);

      //m_pfontMarlett->create_point_font("Marlett", 20);

      m_pfontMarlett->create_font("Marlett", 20_pt);
      
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


   void control_box::on_timer(::timer * ptimer)
   {

      ::experience::control_box::on_timer(ptimer);

   }


   void control_box::install_message_routing(::channel * pchannel)
   {

      ::experience::control_box::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_show_window, pchannel, this, &control_box::on_message_show_window);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &control_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &control_box::on_message_left_button_up);
      MESSAGE_LINK(e_message_create, pchannel, this, &control_box::on_message_create);
   //   MESSAGE_LINK(e_message_size, pchannel, this, &control_box::on_message_size);
   //   //MESSAGE_LINK(e_message_timer, pchannel, this, &control_box::on_timer);

   }


} // namespace experience_tranquillum



