#pragma once


namespace message
{


   class CLASS_DECL_AURA timer :
      virtual public ::user::message
   {
   public:


      ::u32 m_uEvent;


      timer() {}

      using ::user::message::set;
      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam) override;



   };



} // namespace message



