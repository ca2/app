#include "framework.h"
#include "control_box.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/frame_interaction.h"


namespace experience_anthill
{


   control_box::control_box()
   {

      m_iDefaultButtonMargin = 0;

   }


   control_box::~control_box()
   {

   }


   void control_box::set_button_color_system_default_001()
   {

      m_pbrushButtonBack->create_solid(argb(0, 0, 0, 0));
      m_pbrushButtonBackSel->create_solid(argb(0, 0, 0, 0));
      m_pbrushButtonBackFocus->create_solid(argb(0, 0, 0, 0));
      m_pbrushButtonBackDisabled->create_solid(argb(200, 160, 160, 160));

      m_ppenButtonBack->create_solid(2, argb(255, 255, 255, 255));
      m_ppenButtonBackSel->create_solid(2, argb(255, 150, 255, 170));
      m_ppenButtonBackFocus->create_solid(2, argb(0, 0, 0, 0));
      m_ppenButtonBackDisabled->create_solid(2, argb(0, 0, 0, 0));

      m_colorButtonFore = argb(255, 255, 255, 255);
      m_colorButtonForeSel = argb(255, 150, 255, 170);
      m_colorButtonForeFocus = argb(255, 255, 255, 255);
      m_colorButtonForeDisabled = argb(200, 100, 100, 100);

   }


   void control_box::install_message_routing(::channel * pchannel)
   {

      ::experience::control_box::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &control_box::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &control_box::on_message_show_window);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &control_box::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &control_box::on_message_left_button_up);

   }


   void control_box::on_message_create(::message::message * pmessage)
   {

      __øconstruct(m_pfontMarlett);

      m_pfontMarlett->create_font("Marlett", 32_px);

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


   void control_box::on_timer(::timer * ptimer)
   {

      ::experience::control_box::on_timer(ptimer);

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

      ::int_rectangle rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      color32_t crBackground;

      if (top_level()->frame_is_transparent())
      {

         crBackground = m_colorBackground & 100_opacity;

      }
      else
      {

         crBackground = m_colorBackground;

      }

      if (m_colorBackground.is_ok())
      {

         pgraphics->fill_rectangle(rectangleX, m_colorBackground);

      }

   }


} // namespace experience_anthill



