#pragma once


namespace message
{


   class CLASS_DECL_AURA timer :
      virtual public base
   {
   public:


      ::u32 m_uEvent;


      timer() {}

      using ::message::base::set;
      virtual void set(::user::primitive* pwnd, const ::id & id, WPARAM wparam, ::lparam lparam);



   };



} // namespace message



