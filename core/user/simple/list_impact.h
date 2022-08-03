#pragma once


class CLASS_DECL_CORE simple_list_view :
   virtual public ::user::show <  ::user::form_list >
{
public:


   using BASE_TYPE = ::user::show <  ::user::form_list > ;


   simple_list_view();
   ~simple_list_view() override;


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;


   void install_message_routing(::channel * pchannel) override;


};



