#pragma once

class CLASS_DECL_CORE simple_tab_control :
   virtual public ::user::interaction,
   virtual public ::user::tab
{
public:


   simple_tab_control();
   virtual ~simple_tab_control();


   virtual void pre_subclass_window();

   void install_message_routing(::channel * pchannel) override;

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

};

