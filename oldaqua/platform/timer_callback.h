#pragma once


class CLASS_DECL_AQUA timer_callback :
   virtual public ::object
{
public:


   virtual bool on_timer(timer * ptimer);
   virtual bool timer_is_ok();

};



