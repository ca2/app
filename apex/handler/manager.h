// Created by camilo on day after ThomasBirthday2021 21:07
#pragma once


#include "apex/handler/_.h"

/// manager is originator of signals
class CLASS_DECL_APEX manager :
   virtual public ::object
{
public:


   ::pointer<::handler::signal_map>                                 m_psignalmap;



   manager();
   ~manager() override;


#ifdef _DEBUG


   long long increment_reference_count() override;
   long long decrement_reference_count() override;
   long long release() override;

#endif


   void destroy() override;


   [[nodiscard]] virtual class ::handler::signal * signal(const ::atom& atom);
   [[nodiscard]] virtual class ::handler::signal * signal(const ::atom & atom, const ::action_context & actioncontext);

   //virtual void add_handler(::matter * pmatter, const ::atom & atomSignal);
   //virtual void add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal);

   virtual void erase_handler(::object * pobject);
   virtual void erase_signal_handler(const ::signal_handler::base * pbase);

   //virtual void erase_signal_handlers(::particle * ppparticle);

   // <3ThomasBorregaardSorensen handle...!!
   virtual void send_signal(const ::atom & atom);
   virtual void send_signal(const ::atom & atom, const ::action_context & actioncontext);


   virtual void on_property_changed(::property * pproperty, const ::action_context & actioncontext) override;


   virtual void destroy_signal_handling();


//   virtual void erase_signal_handler(const ::signal_handler & signalhandler);




};


