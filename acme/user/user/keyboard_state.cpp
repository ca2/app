// Created by camilo on 2023-11-14 14:37 <3ThomasBorregaardSorensen!!
// To keyboard_state.cpp by camilo on 2023-11-14 18:10 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "keyboard_state.h"


namespace user
{

   keyboard_state::keyboard_state() {} 


   keyboard_state::~keyboard_state() {}   


   bool keyboard_state::is_key_pressed(::user::enum_key ekey)
   {

      return false;

   }


   ::user::e_key_state keyboard_state::key_state()
   {

      throw ::interface_only();

      return ::user::e_key_state_none;

   }


     ::user::e_key_state keyboard_state::key_state_with_wm_mouse_wparam(::wparam wparam)
   {

        throw ::interface_only();

      return ::user::e_key_state_none;
   }


   bool keyboard_state::is_mouse_state(::user::e_key_state ekeystate)
   {

      return (key_state() & ::user::e_key_state_mouse_mask) == ekeystate;

   }
   bool keyboard_state::has_mouse_state(::user::e_key_state ekeystate)
   {

      return key_state() & ekeystate;

   }


} // namespace user


