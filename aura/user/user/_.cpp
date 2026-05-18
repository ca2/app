// From nanoui/Screen.cpp by camilo on 2023-02-01 21:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/constant/user_key.h"



CLASS_DECL_AURA::user::e_button_state user_key_to_button_state(::user::e_key ekeyButton)
{

   if (ekeyButton == ::user::e_key_left_button)
   {

      return ::user::e_button_state_left;

   }
   else if(ekeyButton == ::user::e_key_right_button)
   {

      return ::user::e_button_state_right;

   }
   else if (ekeyButton == ::user::e_key_middle_button)
   {

      return::user::e_button_state_middle;

   }

   return ::user::e_button_state_none;

}




