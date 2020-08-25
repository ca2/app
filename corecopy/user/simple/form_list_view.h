#pragma once


class CLASS_DECL_CORE simple_form_list_view :
   virtual public ::user::show < ::user::margin < ::user::form_list > >
{
public:


   typedef ::user::show < ::user::margin < ::user::form_list > > BASE;


   simple_form_list_view();
   virtual ~simple_form_list_view();


   virtual bool pre_create_window(::user::create_struct& cs) override;


   virtual void install_message_routing(::channel * pchannel) override;


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;

   
   virtual void update(::update * pupdate) override;


};



