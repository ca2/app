#include "framework.h"
#include "timer_event.h"


timer_event::timer_event()
{

}


timer_event::~timer_event()
{


}


::e_status timer_event::wait(const class ::wait & wait)
{

   start(wait,false);

   return m_manualresetevent.wait();

}


void timer_event::on_timer()
{

   m_manualresetevent.SetEvent();

   //return true;

}



