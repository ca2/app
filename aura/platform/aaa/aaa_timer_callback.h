#pragma once


class CLASS_DECL_AURA timer_callback :
   virtual public ::object
{
public:


   virtual bool on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();

};



