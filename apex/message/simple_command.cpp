#include "framework.h"
#include "apex/message.h"


namespace message
{


   simple_command::simple_command()
   {

      m_id.m_emessagetype = ::message::type_user_simple_command;
      m_esimplecommand = simple_command_none;

   }


   void simple_command::set(::layered * playeredUserPrimitive, UINT uiMessage, WPARAM wparam, ::lparam lparam)
   {

      ::message::base::set(playeredUserPrimitive, uiMessage, wparam, lparam);

      m_esimplecommand = (e_simple_command)wparam;

   }


} // namespace message



