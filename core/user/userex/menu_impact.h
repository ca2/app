#pragma once


#include "base/user/form/impact.h"


class CLASS_DECL_CORE menu_impact :
   virtual public ::user::form_impact
{
public:


   menu_impact();


   void handle(::topic * ptopic, ::context * pcontext) override;
   //virtual void handle(::topic * ptopic, ::context * pcontext);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   void _001OnTimer(::timer * ptimer) override;
   //DECLARE_MESSAGE_HANDLER(_001OnUser123);
   void install_message_routing(::channel * pchannel) override;


};
















