#pragma once


////#include "core/user/user/_component.h"
#include "core/user/user/form_list.h"
#include "base/user/user/show.h"


class CLASS_DECL_CORE simple_list_impact :
   virtual public ::user::show <  ::user::form_list >
{
public:


   using BASE_TYPE = ::user::show <  ::user::form_list > ;


   simple_list_impact();
   ~simple_list_impact() override;


   // void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;


   void install_message_routing(::channel * pchannel) override;


};



