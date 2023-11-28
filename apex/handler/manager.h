// Created by camilo on day after ThomasBirthday2021 21:07
#pragma once




/// manager is originator of signals
class CLASS_DECL_APEX manager :
   virtual public ::object
{
public:


   ::pointer<signal_map>                                 m_psignalmap;



   manager();
   ~manager() override;


#ifdef _DEBUG


   i64 increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;
   i64 decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;
   i64 release(REFERENCING_DEBUGGING_PARAMETERS) override;

#endif


   virtual class ::signal * get_signal(const ::atom& atom);
   virtual class ::signal * get_signal(const ::atom & atom, const ::action_context & actioncontext);
   
   virtual void add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal);
   
   virtual void erase_signal_handler(const ::signal_handler::base * pbase);

   //virtual void erase_signal_handlers(::particle * ppparticle);

   // <3ThomasBorregaardSorensen handle...!!
   virtual void signal(const ::atom & atom);
   virtual void signal(const ::atom & atom, const ::action_context & actioncontext);


   virtual void on_property_changed(property * pproperty, const ::action_context & actioncontext) override;


   virtual void destroy_signal_handling();


//   virtual void erase_signal_handler(const ::signal_handler & signalhandler);




};


