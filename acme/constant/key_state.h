//
// Created by camilo on 2026-05-27 17:14 BRT < 3ThomasBorregaardSørensen_!! Mummi!! Bilbo!!
// Merged from button_state.h on 2026-05-27 17:47 BRT < 3ThomasBorregaardSørensen_!! Mummi!! Bilbo!!
//
#pragma once


namespace user
{


   enum enum_key_state
   {

      e_key_state_none = 0,
      e_key_state_left = 1, // MK_LBUTTON
      e_key_state_right = 2, // MK_RBUTTON
      e_key_state_shift = 4, // MK_SHIFT
      e_key_state_control = 8, // MK_CONTROL
      e_key_state_middle = 16, // MK_MBUTTON
      e_key_state_x1 = 32, // MK_XBUTTON1
      e_key_state_x2 = 64, // MK_XBUTTON2

      e_key_state_left_shift = 1 << 7,
      e_key_state_right_shift = 1 << 8,
      e_key_state_left_control = 1 << 9,
      e_key_state_right_control = 1 << 10,
      e_key_state_left_alt = 1 << 11,
      e_key_state_right_alt = 1 << 12,
      e_key_state_left_command = 1 << 13,
      e_key_state_right_command = 1 << 14,
      e_key_state_system_left_command = 1 << 15,
      e_key_state_system_right_command = 1 << 16,

   };


} // namespace user
