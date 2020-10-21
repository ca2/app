#pragma once


class CLASS_DECL_APEX timer_callback :
   virtual public ::object
{
public:


   __pointer(::layered)       m_puserinteraction;


   virtual bool on_timer(timer * ptimer);
   virtual bool e_timer_is_ok();


   inline ::user::interaction* user_interaction() { return __user_interaction(m_puserinteraction); }

};



