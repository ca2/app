#pragma once


namespace message
{


   class CLASS_DECL_APEX timer : virtual public base
   {
   public:


      UINT m_nIDEvent;


      timer() { }

      using ::message::base::set;
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam);



   };



} // namespace message



