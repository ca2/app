// Created by camilo on day after ThomasBirthday2021 21:07
#pragma once


#include "signal.h"


/// manager is originator of signals
class CLASS_DECL_APEX manager :
   virtual public ::object
{
public:


   ::pointer<signal_map>                                m_psignalmap;

   static critical_section                               s_criticalsection;
   // todo implement keyset
   // a hashmap of just the key (but not a value)
   // like std::set?
   static ::set < manager_pointer >                      s_managerset;
   static bool                                           s_bDestroyAll;


   manager();
   ~manager() override;


#ifdef _DEBUG


   i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


   virtual class ::signal * get_signal(const ::atom& atom, const ::action_context& actioncontext = ::action_context());


   // <3ThomasBorregaardSørensen handle...!!
   virtual void signal(const ::atom & atom, const ::action_context & actioncontext = ::action_context());


   virtual void on_property_changed(property * pproperty, const ::action_context & actioncontext) override;


   virtual void destroy_signal_handling();


   virtual void erase_signal_handler(const ::signal_handler & signalhandler);


   static bool __s_may_run_signal_handling();

   static void __s_erase_signal_handler_from_any_source(const ::signal_handler& signalhandler);

   static void __s_erase_signal_handler(const ::signal_handler& signalhandler);

   static void __s_post_destroy_signal_handling();


};


