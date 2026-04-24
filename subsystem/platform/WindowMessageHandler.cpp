// Created by camilo on 2026-04-24 11:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "WindowMessageHandler.h"


namespace subsystem
{

   WindowMessageHandler::WindowMessageHandler() {}

   WindowMessageHandler:: ~WindowMessageHandler()
   {
   }

      // This function must return true if a message has been processed.
   bool WindowMessageHandler::processMessage(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
   {

      return false;
   }


} // namespace subsystem




