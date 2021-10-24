#pragma once


class CLASS_DECL_AURA timer_event:
   virtual public timer
{
public:


   manual_reset_event   m_ev;


   timer_event(::aura::timer_array * ptimera, int iTimer);
   virtual ~timer_event();


   virtual bool wait(int ::duration);


   virtual bool on_timer() override;


};






