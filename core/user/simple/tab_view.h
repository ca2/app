#pragma once



class CLASS_DECL_CORE simple_tab_view :
   virtual public ::user::show < ::user::tab >
{
public:


   simple_tab_view();
   virtual ~simple_tab_view();

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;


   DECLARE_MESSAGE_HANDLER(_001OnSize);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(_001OnDestroy);

   void on_layout(::draw2d::graphics_pointer & pgraphics);


   virtual bool get_client_rect(RECTANGLE_I32 * prectangle);


   virtual void install_message_routing(::channel * pchannel);

   DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);

};


