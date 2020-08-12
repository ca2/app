#pragma once


namespace user
{


   class CLASS_DECL_AURA thread :
      virtual public thread
   {
   public:


      __pointer(user::interaction_pointer_array)      m_puiptra;
      __pointer(::user::interaction::timer_array)     m_ptimera;


      thread();
      virtual ~thread();


   };


} // namespace user



