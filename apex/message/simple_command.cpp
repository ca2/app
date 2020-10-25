#include "framework.h"
#include "apex/message.h"


namespace message
{


   simple_command::simple_command()
   {

      m_id = ::e_message_simple_command;
      m_esimplecommand = simple_command_none;

   }


   void simple_command::set(::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam)
   {

      ::message::base::set(playeredUserPrimitive, id, wparam, lparam);

      m_esimplecommand = (e_simple_command)wparam;

   }


} // namespace message



