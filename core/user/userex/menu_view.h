#pragma once


class CLASS_DECL_CORE menu_view :
   virtual public ::user::form_view
{
public:


   menu_view();


   void handle(::subject * psubject, ::context * pcontext);
   //virtual void handle(::subject * psubject, ::context * pcontext);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   void _001OnTimer(::timer * ptimer);
   //DECLARE_MESSAGE_HANDLER(_001OnUser123);
   void install_message_routing(::channel * pchannel) override;


};
















