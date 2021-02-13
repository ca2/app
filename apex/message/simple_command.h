#pragma once


namespace message
{


   class CLASS_DECL_APEX simple_command :
      public ::message::message
   {
   public:


      simple_command();

      void set(enum_simple_command esimplecommand) { m_wparam.m_number = esimplecommand; }

      inline enum_simple_command command() { return (enum_simple_command) m_wparam.m_number; }


   };


} // namespace message



