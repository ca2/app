// From nanoui/Screen.cpp by camilo on 2023-02-01 21:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_.h"



CLASS_DECL_AURA::user::e_mouse user_key_to_user_mouse(::user::e_key ekeyButton)
{

   ::user::e_mouse emouse = ::user::e_mouse_none;

   if (ekeyButton & ::user::e_key_left_button)
   {

      emouse |= ::user::e_mouse_left_button;

   }

   if (ekeyButton == ::user::e_key_right_button)
   {

      emouse |= ::user::e_mouse_left_button;

   }
   
   if (ekeyButton == ::user::e_key_middle_button)
   {

      emouse |= ::user::e_mouse_middle_button;

   }

   return emouse;

}




