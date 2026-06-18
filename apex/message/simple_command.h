#pragma once


#include "message.h"


namespace message
{


   class CLASS_DECL_APEX simple_command : 
      public ::message::message
   {
   public:


      simple_command();

      void set(enum_simple_command esimplecommand) { m_wparam = esimplecommand; }

      inline enum_simple_command command() { return m_wparam.raw_cast<enum_simple_command>(); }


   };


} // namespace message



