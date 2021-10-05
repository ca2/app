#include "framework.h"


timer_event::timer_event()
 {

}


timer_event::~timer_event()
{


}

bool timer_event::wait(int millisecond)
{

   start(millisecond,false);

   m_ev.wait();

   return true;
}


bool timer_event::on_timer()
{

   m_ev.SetEvent();

   return true;

}



