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
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDestroy);

   void on_layout(::draw2d::graphics_pointer & pgraphics);


   virtual bool get_client_rect(RECT * prect);


   virtual void install_message_routing(::channel * pchannel);

   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnMouseLeave);

};


