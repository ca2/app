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


   DECL_GEN_SIGNAL(_001OnSize);
   DECL_GEN_SIGNAL(on_message_create);
   DECL_GEN_SIGNAL(_001OnDestroy);

   void on_layout(::draw2d::graphics_pointer & pgraphics);


   virtual bool get_client_rect(RECTANGLE_I32 * prectangle);


   virtual void install_message_routing(::channel * pchannel);

   DECL_GEN_SIGNAL(on_message_left_button_up);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnMouseLeave);

};


