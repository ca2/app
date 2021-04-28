#pragma once


class CLASS_DECL_CORE menu_view :
   virtual public ::user::form_view
{
public:


   menu_view();


   void on_subject(::subject::subject * psubject, ::subject::context * pcontext);
   virtual void on_control_event(::user::control_event * pevent);
   DECLARE_MESSAGE_HANDLER(on_message_create);
   void _001OnTimer(::timer * ptimer);
   //DECLARE_MESSAGE_HANDLER(_001OnUser123);
   virtual void install_message_routing(::channel * pchannel);


};
















