#pragma once


namespace message
{


   class CLASS_DECL_AQUA simple_command :
      public base
   {
   public:


      e_simple_command  m_esimplecommand;


      simple_command();


      using ::message::base::set;
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam);



   };


} // namespace message



