#pragma once


namespace message
{


   class CLASS_DECL_APEX simple_command :
      public base
   {
   public:


      e_simple_command  m_esimplecommand;


      simple_command();


      using ::message::base::set;
      virtual void set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam) override;



   };


} // namespace message



