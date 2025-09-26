#include "framework.h"
#include "simple_command.h"
#include "acme/constant/user_message.h"
#include "acme/constant/simple_command.h"


namespace message
{


   simple_command::simple_command()
   {

      m_eusermessage = ::user::e_message_simple_command;

      set(e_simple_command_none);

   }


   //void simple_command::set(oswindow oswindow, ::layered * playeredUserPrimitive, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, playeredUserPrimitive, eusermessage, wparam, lparam);

   //   m_esimplecommand = (e_simple_command)wparam.m_number;

   //}


} // namespace message



