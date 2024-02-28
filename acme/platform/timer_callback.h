#pragma once


//#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_ACME timer_callback :
   virtual public ::particle
{
public:


   typedef uptr_map < ::pointer<::timer >>MAP;

   MAP                                       m_timermap;


   timer_callback();
   ~timer_callback() override;


   virtual void on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();


   virtual void erase_timer(::timer* ptimer);

   virtual ::user::interaction * get_user_interaction();

   
};



