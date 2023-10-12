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
      case ::user::e_key_back:       str = "user::e_key_back"; break;
      case ::user::e_key_return:       str = "user::e_key_return"; break;
      case ::user::e_key_down:       str = "user::e_key_down"; break;
      case ::user::e_key_left:       str = "user::e_key_left"; break;
      case ::user::e_key_right:       str = "user::e_key_right"; break;
      case ::user::e_key_up:       str = "user::e_key_up"; break;
      case ::user::e_key_home:     str = "user::e_key_home"; break;
      case ::user::e_key_end:     str = "user::e_key_end"; break;
      case ::user::e_key_page_down:     str = "user::e_key_page_down"; break;
      case ::user::e_key_page_up:     str = "user::e_key_page_up"; break;
      default:
         str.format("%d", (::i32)ekey);

   }

   return str;

}
