#include "framework.h"


timer_event::timer_event(::aura::timer_array * ptimera, int iTimer) :
   ::object(ptimera),
   timer(ptimera, iTimer)
{

}


timer_event::~timer_event()
{


}

bool timer_event::wait(int ::duration)
{

   start(::duration,false);

   m_ev.wait();

   return true;
}


bool timer_event::on_timer()
{

   m_ev.SetEvent();

   return true;

}



