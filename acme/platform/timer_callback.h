#pragma once


class CLASS_DECL_ACME timer_callback :
   virtual public ::matter
{
public:


   virtual bool on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();


   virtual bool erase_timer(::timer* ptimer);

   virtual ::user::interaction * get_user_interaction();

   
};



