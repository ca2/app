#include "framework.h"


MetaControlBox::MetaControlBox(::particle * pparticle) :
   object(pparticle),
   ::user::interaction(pparticle),
   ::experience::control_box(pparticle)
{
   m_iDefaultButtonMargin = 0;

   m_pfontMarlett->create_point_font("Marlett", 24);

}


MetaControlBox::~MetaControlBox()
{

}


void MetaControlBox::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
{


}

void MetaControlBox::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   if(get_top_level()->frame_is_transparent() && !get_top_level()->is_active())
   {

      return;

   }

   auto rectangleX = this->rectangle();

   if (rectangleX.area() <= 0)
      return;

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   color32_t crBackground;

   if(get_top_level()->frame_is_transparent())
   {

      crBackground = argb(84,color32_u8_red(m_colorBackground),color32_u8_green(m_colorBackground),color32_u8_blue(m_colorBackground));

   }
   else
   {

      crBackground = m_colorBackground;

   }

   pgraphics->fill_rectangle(rectangleX, m_colorBackground);

}


void MetaControlBox::on_message_show_window(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}

void MetaControlBox::on_message_left_button_down(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}

void MetaControlBox::on_message_left_button_up(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   set_need_redraw();

}



void MetaControlBox::_001OnTimer(::timer * ptimer)
{

   ::experience::control_box::_001OnTimer(ptimer);

}


void MetaControlBox::install_message_routing(::channel * pchannel)
{

   ::experience::control_box::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_show_window, pchannel, this, &MetaControlBox::on_message_show_window);
   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &MetaControlBox::on_message_left_button_down);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &MetaControlBox::on_message_left_button_up);
//   MESSAGE_LINK(e_message_size, pchannel, this, &MetaControlBox::on_message_size);
//   //MESSAGE_LINK(e_message_timer, pchannel, this, &MetaControlBox::_001OnTimer);

}

