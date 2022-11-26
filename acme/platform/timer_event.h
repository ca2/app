#pragma once


#include "timer_task.h"
#include "acme/parallelization/manual_reset_event.h"


class CLASS_DECL_ACME timer_event:
   virtual public timer_task
{
public:


   manual_reset_event         m_manualresetevent;


   timer_event();
   ~timer_event() override;


   ::e_status wait(const class time & timeWait) override;


   void on_timer() override;


};






