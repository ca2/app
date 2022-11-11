#pragma once


#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_ACME timer_callback :
   virtual public ::particle
{
public:


   virtual void on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();


   virtual void erase_timer(::timer* ptimer);

   virtual ::user::interaction * get_user_interaction();

   
};



