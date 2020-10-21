#pragma once


class CLASS_DECL_APEX timer_event:
   virtual public threaded_timer
{
public:


   manual_reset_event         m_ev;


   timer_event(::apex::timer_array * ptimera, int iTimer);
   virtual ~timer_event();


   virtual bool wait(int millis);


   virtual bool on_timer() override;


};






