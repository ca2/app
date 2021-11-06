#pragma once


namespace message
{


   class CLASS_DECL_APEX timer : 
      virtual public base
   {
   public:


      ::u32 m_uEvent;


      timer() { }

      using ::user::message::set;
      virtual void set(::user::primitive * puserinteraction, const ::id & id, WPARAM wparam, ::lparam lparam);



   };



} // namespace message



