#pragma once


class CLASS_DECL_CORE simple_form_list_view :
   virtual public ::user::show < ::user::margin < ::user::form_list > >
{
public:


   typedef ::user::show < ::user::margin < ::user::form_list > > BASE;


   simple_form_list_view();
   virtual ~simple_form_list_view();


   virtual bool pre_create_window(::user::system * pusersystem) override;


   void install_message_routing(::channel * pchannel) override;


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;

   
   virtual void handle(::topic * ptopic, ::context * pcontext) override;


};



