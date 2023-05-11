#pragma once


#include "base/user/user/statusbar.h"


class CLASS_DECL_BASE simple_status_bar :
   public ::user::status_bar
{
public:
   
   
   simple_status_bar();
   ~simple_status_bar() override;


   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


};



