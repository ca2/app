#pragma once


class CLASS_DECL_AURA timer_event:
   virtual public timer
{
public:


   manual_reset_happening   m_ev;


   timer_event(::aura::timer_array * ptimera, ::i32 iTimer);
   virtual ~timer_event();


   virtual bool wait(::i32 ::duration);


   virtual bool on_timer() override;


};






