#include "framework.h"


timer_event::timer_event(::aura::timer_array * ptimera, ::i32 iTimer) :
   ::object(ptimera),
   timer(ptimera, iTimer)
{

}


timer_event::~timer_event()
{


}

bool timer_event::wait(::i32 ::duration)
{

   start(::duration,false);

   m_ev.wait();

   return true;
}


bool timer_event::on_timer()
{

   m_ev.set_happening();

   return true;

}



