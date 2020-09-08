#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_tab_control::simple_tab_control()
{

}


simple_tab_control::~simple_tab_control()
{

}


void simple_tab_control::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::_001OnDraw(pgraphics);

}


void simple_tab_control::pre_subclass_window()
{

   ::user::interaction::pre_subclass_window();

}


void simple_tab_control::install_message_routing(::channel * pchannel)
{
   ::user::interaction::install_message_routing(pchannel);
   ::user::primitive::install_message_routing(pchannel);
}