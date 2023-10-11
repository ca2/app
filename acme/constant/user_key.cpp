//
// Created by camilo on 2023-10-10 21:56 <3ThomasBorregaardSorensen!!.
//
#include "framework.h"
#include "user_key.h"


::string as_string(::user::enum_key ekey)
{

   ::string str;

   switch(ekey)
   {
      case ::user::e_key_up:
         str = "user::e_key_up"; break;
      default:
         str.format("%d", (::i32)ekey);

   }

   return str;

}
