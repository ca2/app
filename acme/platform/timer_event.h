#pragma once


class CLASS_DECL_ACME timer_event:
   virtual public timer_task
{
public:


   manual_reset_event         m_ev;


   timer_event();
   virtual ~timer_event();


   virtual bool wait(int millis);


   virtual bool on_timer() override;


};






