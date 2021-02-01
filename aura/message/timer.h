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
      virtual void set(oswindow oswindow, ::user::primitive* pwnd, const ::id & id, wparam wparam, ::lparam lparam);



   };



} // namespace message



