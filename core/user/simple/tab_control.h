#pragma once


#include "base/user/user/tab.h"


class CLASS_DECL_CORE simple_tab_control :
   virtual public ::user::tab
{
public:


   simple_tab_control();
   ~simple_tab_control() override;


   void pre_subclass_window() override;

   void install_message_routing(::channel * pchannel) override;

   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


};



