#pragma once


class CLASS_DECL_ACME timer_callback :
   virtual public ::context_object
{
public:


   __pointer(::layered)       m_puserinteraction;


   virtual bool on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();


   virtual bool remove_timer(::timer* ptimer);


   inline ::user::interaction* user_interaction() { return __user_interaction(m_puserinteraction); }

};



