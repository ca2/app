#include "framework.h"
#include "timer_event.h"


timer_event::timer_event()
{

}


timer_event::~timer_event()
{


}


::e_status timer_event::wait(const class time & timeWait)
{

   start_timer_task(timeWait,false);

   return m_manualresethappening.wait();

}


void timer_event::on_timer()
{

   m_manualresethappening.set_happening();

   //return true;

}



