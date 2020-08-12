#include "framework.h"


MetaControlBox::MetaControlBox(::object * pobject) :
object(pobject),
::user::interaction(pobject),
::experience::control_box(pobject)
{
   

}


MetaControlBox::~MetaControlBox()
{

}


void MetaControlBox::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
{


}

void MetaControlBox::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   if(GetTopLevel()->frame_is_transparent() && GetTopLevel() != GetActiveWindow())
   {

      return;

   }

   ::rect rectClient;

   GetClientRect(rectClient);

   if (rectClient.area() <= 0)
      return;

   

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   COLORREF crBackground;

   if(GetTopLevel()->frame_is_transparent())
   {

      crBackground = ARGB(84,colorref_get_r_value(m_crBackground),colorref_get_g_value(m_crBackground),colorref_get_b_value(m_crBackground));

   }
   else
   {

      crBackground = m_crBackground;

   }

   pgraphics->FillSolidRect(rectClient, crBackground);

}


void MetaControlBox::_001OnShowWindow(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}

void MetaControlBox::_001OnLButtonDown(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}

void MetaControlBox::_001OnLButtonUp(::message::message * pmessage)
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

   IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &MetaControlBox::_001OnShowWindow);
   IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &MetaControlBox::_001OnLButtonDown);
   IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &MetaControlBox::_001OnLButtonUp);
   IGUI_MSG_LINK(WM_SIZE, pchannel, this, &MetaControlBox::_001OnSize);

}



