#include "framework.h"
#include "apex/message.h"


namespace message
{


   simple_command::simple_command()
   {

      m_atom = ::e_message_simple_command;

      set(e_simple_command_none);

   }


   //void simple_command::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, playeredUserPrimitive, atom, wparam, lparam);

   //   m_esimplecommand = (e_simple_command)wparam.m_number;

   //}


} // namespace message



