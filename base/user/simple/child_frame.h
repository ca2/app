#pragma once


#include "base/user/simple/frame_window.h"


class CLASS_DECL_BASE simple_child_frame :
   virtual public simple_frame_window
{
public:


   simple_child_frame();
   ~simple_child_frame() override;


   void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


};



