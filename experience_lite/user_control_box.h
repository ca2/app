#pragma once


class CLASS_DECL_APP_EXPERIENCE_LITE MetaControlBox :
   virtual public ::experience::control_box
{
public:


   MetaControlBox(::object * pobject);
   virtual ~MetaControlBox();


   virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   void install_message_routing(::channel * pchannel) override;


   DECLARE_MESSAGE_HANDLER(on_message_show_window);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
   DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   void _001OnTimer(::timer * ptimer) override;


};



