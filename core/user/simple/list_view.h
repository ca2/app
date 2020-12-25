#pragma once


class CLASS_DECL_CORE simple_list_view :
   virtual public ::user::show <  ::user::form_list >
{
public:


   using BASE_TYPE = ::user::show <  ::user::form_list > ;


   simple_list_view();
   virtual ~simple_list_view();

   virtual void install_message_routing(::channel * pchannel);

   oswindow GetHandle();
   __pointer(::user::interaction) OnDrawInterfaceGetWnd();

   virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);
   virtual bool pre_create_window(::user::create_struct * pcreatestruct);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;


};



