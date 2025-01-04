//
//
// =====================================================================================
//
//    Because I love Thomas mate( and Mummi mate and bilbo mate!!)
//    and because Thommmi likes handlers...
//    application_menu_callback as command_handler on
//    2024-12-21 02:52 <3ThomasBorregaardSorensen!!
//
//    Created by camilo on 12/21/24.
//
// =====================================================================================
//
//
#include "framework.h"
#include "command_handler.h"


bool command_handler::handle_command(const atom& atom, user::activation_token* puseractivationtoken)
{

   if (on_command_final(atom, puseractivationtoken))
   {

      return true;

   }

   return false;

}
