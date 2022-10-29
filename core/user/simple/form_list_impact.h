#pragma once


#include "base/user/user/margin.h"
#include "core/user/user/form_list.h"
#include "base/user/user/show.h"


class CLASS_DECL_CORE simple_form_list_impact :
   virtual public ::user::show < ::user::margin < ::user::form_list > >
{
public:


   typedef ::user::show < ::user::margin < ::user::form_list > > BASE;


   simple_form_list_impact();
   virtual ~simple_form_list_impact();


   virtual bool pre_create_window(::user::system * pusersystem) override;


   void install_message_routing(::channel * pchannel) override;


   // void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;

   
   virtual void handle(::topic * ptopic, ::context * pcontext) override;


};



