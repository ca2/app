#include "framework.h" // previously apex/user/user.h
#include "timer.h"
#include "timer_callback.h"


timer_callback::timer_callback()
{


}


timer_callback::~timer_callback()
{

   for(auto & ptimer : m_timera)
   {

      if(ptimer && ptimer->m_ptimercallback == this)
      {

         ptimer->m_ptimercallback.release();

      }

   }

}


void timer_callback::on_timer(timer * ptimer)
{

   // return true;

}


bool timer_callback::e_timer_is_ok()
{

   return true;

}


void timer_callback::erase_timer(::timer* ptimer)
{

   //return false;

}


::user::interaction * timer_callback::get_user_interaction()
{

   return nullptr;

}



