#pragma once


#include "timer_task.h"


class CLASS_DECL_ACME timer_event:
   virtual public timer_task
{
public:


   manual_reset_event         m_manualresetevent;


   timer_event();
   ~timer_event() override;


   virtual bool wait(const class ::wait & wait);


   virtual bool on_timer() override;


};






