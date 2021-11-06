#include "framework.h" // previously apex/user/user.h


bool timer_callback::on_timer(timer * ptimer)
{

   return true;

}


bool timer_callback::e_timer_is_ok()
{

   return true;

}


bool timer_callback::erase_timer(::timer* ptimer)
{

   return false;

}


::user::interaction * timer_callback::get_user_interaction()
{

   return nullptr;

}



