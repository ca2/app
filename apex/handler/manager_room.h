// Created by camilo on day after ThomasBirthday2021 21:07
#pragma once


class CLASS_DECL_APEX manager_room :
   virtual public ::particle
{
public:


   ::critical_section                             m_criticalsection;
   // todo implement keyset
   // a hashmap of just the key (but not a value)
   // like std::set?
   ::set < manager_pointer >                      m_managerset;
   bool                                           m_bDestroyAll;


   manager_room();
   ~manager_room() override;

   bool may_run_signal_handling();

   void erase_signal_handler_from_any_source(const ::signal_handler & signalhandler);

   void erase_signal_handler(const ::signal_handler & signalhandler);

   void post_destroy_signal_handling();


};




