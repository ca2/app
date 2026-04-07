//
// Created by camilo on 2026-04-07 02:34 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "OperatingSystemHookListener.h"


namespace subsystem
{



   bool OperatingSystemHookListener::operating_system_hook_on_keyboard_message(::lresult & lresult, ::user::enum_message emessage, int iVkCode, ::lparam lparam)
   {

      return false;

   }

} // namespace subsystem
