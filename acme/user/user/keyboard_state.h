// Created by camilo on 2023-11-14 14:37 <3ThomasBorregaardSorensen!!
// To keyboard_state.h by camilo on 2023-11-14 18:10 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace user
{


   class CLASS_DECL_ACME keyboard_state :
      virtual public ::particle
   {
   public:


      keyboard_state();
      ~keyboard_state() override;


      virtual bool is_key_pressed(::user::enum_key ekey);
      virtual ::user::e_key_state key_state();
      virtual ::user::e_key_state key_state_with_wm_mouse_wparam(::wparam wparam);
      virtual bool is_mouse_state(::user::e_key_state ekeystate);
      virtual bool has_mouse_state(::user::e_key_state ekeystate);


   };


} // namespace user



