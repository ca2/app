#include "framework.h"
#include "timer_event.h"


timer_event::timer_event()
{

}


timer_event::~timer_event()
{


}


bool timer_event::wait(const class ::wait & wait)
{

   start(wait,false);

   m_manualresetevent.wait();

   return true;

}


bool timer_event::on_timer()
{

   m_manualresetevent.SetEvent();

   return true;

}



