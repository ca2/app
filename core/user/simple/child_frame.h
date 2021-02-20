#pragma once


class CLASS_DECL_CORE simple_child_frame :
   virtual public simple_frame_window
{
public:


   simple_child_frame();
   virtual ~simple_child_frame();


   virtual void route_command_message(::message::command * pcommand) override;
   virtual bool pre_create_window(::user::system * pusersystem) override;


   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


};



