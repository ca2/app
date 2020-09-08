#pragma once


class CLASS_DECL_ACME timer_callback :
   virtual public ::generic
{
public:


   virtual bool on_timer(timer * ptimer);
   virtual bool timer_is_ok();

};



