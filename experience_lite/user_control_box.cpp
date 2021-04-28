#include "framework.h"


MetaControlBox::MetaControlBox(::object * pobject) :
   object(pobject),
   ::user::interaction(pobject),
   ::experience::control_box(pobject)
{
   m_iDefaultButtonMargin = 0;

   m_fontMarlett->create_point_font("Marlett", 24);

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

   ::rectangle_i32 rectClient;

   get_client_rect(rectClient);

   if (rectClient.area() <= 0)
      return;

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   color32_t crBackground;

   if(get_top_level()->frame_is_transparent())
   {

      crBackground = argb(84,colorref_get_r_value(m_colorBackground),colorref_get_g_value(m_colorBackground),colorref_get_b_value(m_colorBackground));

   }
   else
   {

      crBackground = m_colorBackground;

   }

   pgraphics->fill_rectangle(rectClient, m_colorBackground);

}


void MetaControlBox::_001OnShowWindow(::message::message * pmessage)
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

   MESSAGE_LINK(e_message_show_window, pchannel, this, &MetaControlBox::_001OnShowWindow);
   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &MetaControlBox::on_message_left_button_down);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &MetaControlBox::on_message_left_button_up);
//   MESSAGE_LINK(e_message_size, pchannel, this, &MetaControlBox::_001OnSize);
//   //MESSAGE_LINK(e_message_timer, pchannel, this, &MetaControlBox::_001OnTimer);

}

