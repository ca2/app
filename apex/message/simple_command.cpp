#include "framework.h"
#include "apex/message.h"


namespace message
{


   simple_command::simple_command()
   {

      m_id = ::e_message_simple_command;

      set(e_simple_command_none);

   }


   //void simple_command::set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam)
   //{

   //   ::user::message::set(oswindow, playeredUserPrimitive, id, wparam, lparam);

   //   m_esimplecommand = (e_simple_command)wparam.m_number;

   //}


} // namespace message



