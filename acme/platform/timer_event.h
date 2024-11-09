#pragma once


#include "timer_task.h"
#include "acme/parallelization/manual_reset_happening.h"


class CLASS_DECL_ACME timer_event:
   virtual public timer_task
{
public:


   manual_reset_happening         m_manualresethappening;


   timer_event();
   ~timer_event() override;


   ::e_status wait(const class time & timeWait) override;


   void on_timer() override;


};






