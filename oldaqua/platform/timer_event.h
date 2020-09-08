#pragma once


class CLASS_DECL_AQUA timer_event:
   virtual public timer
{
public:


   manual_reset_event   m_ev;


   timer_event(::aqua::timer_array * ptimera, int iTimer);
   virtual ~timer_event();


   virtual bool wait(int millis);


   virtual bool on_timer() override;


};






