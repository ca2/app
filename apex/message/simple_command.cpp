#include "framework.h"
#include "simple_command.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"


namespace message
{


   simple_command::simple_command()
   {

      m_emessage = ::e_message_simple_command;

      set(e_simple_command_none);

   }


   //void simple_command::set(oswindow oswindow, ::layered * playeredUserPrimitive, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, playeredUserPrimitive, emessage, wparam, lparam);

   //   m_esimplecommand = (e_simple_command)wparam.m_number;

   //}


} // namespace message



