#pragma once


#include "base/user/user/tab.h"
#include "base/user/user/show.h"


class CLASS_DECL_CORE simple_tab_impact :
   virtual public ::user::show < ::user::tab >
{
public:


   simple_tab_impact();
   ~simple_tab_impact() override;

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

   // void assert_ok() const override;
   // void dump(dump_context & dumpcontext) const override;


   DECLARE_MESSAGE_HANDLER(on_message_size);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);

   void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   void client_rectangle(RECTANGLE_I32 & rectangle, ::user::enum_layout elayout = ::user::e_layout_sketch) override;


   void install_message_routing(::channel * pchannel) override;

   DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);


};



