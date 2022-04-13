//
//  user_key_enum.h
//  base
//
//  moved from aura on 16 de Novembro de 2013
//

#pragma once


namespace user
{


   enum enum_key : ::i32
   {

      e_key_none,
      e_key_refer_to_text_member,
      e_key_0,
      e_key_1,
      e_key_2,
      e_key_3,
      e_key_4,
      e_key_5,
      e_key_6,
      e_key_7,
      e_key_8,
      e_key_9,
      e_key_a,
      e_key_b,
      e_key_c,
      e_key_d,
      e_key_e,
      e_key_f,
      e_key_g,
      e_key_h,
      e_key_i,
      e_key_j,
      e_key_k,
      e_key_l,
      e_key_m,
      e_key_n,
      e_key_o,
      e_key_p,
      e_key_q,
      e_key_r,
      e_key_s,
      e_key_t,
      e_key_u,
      e_key_v,
      e_key_w,
      e_key_x,
      e_key_y,
      e_key_z,
      e_key_semicolon,
      e_key_semicolon2,
      e_key_semicolon3,
      e_key_comma,
      e_key_dot,
      e_key_back,
      e_key_delete,
      e_key_space,
      e_key_right,
      e_key_down,
      e_key_left,
      e_key_up,
      e_key_prior,
      e_key_next,
      e_key_return,
      e_key_home,
      e_key_end,
      e_key_tab,
      e_key_capslock,
      e_key_hyphen,
      e_key_slash2,
      e_key_backslash2,
      e_key_closebracket2,
      e_key_openbracket2,
      e_key_til2,
      e_key_acute2,
      e_key_equal,
      e_key_escape,
      e_key_apostrophe2,
      e_key_numpad_0,
      e_key_numpad_1,
      e_key_numpad_2,
      e_key_numpad_3,
      e_key_numpad_4,
      e_key_numpad_5,
      e_key_numpad_6,
      e_key_numpad_7,
      e_key_numpad_8,
      e_key_numpad_9,
      e_key_print_screen,
      e_key_f1,
      e_key_f2,
      e_key_f3,
      e_key_f4,
      e_key_f5,
      e_key_f6,
      e_key_f7,
      e_key_f8,
      e_key_f9,
      e_key_f10,
      e_key_f11,
      e_key_f12,

      e_key_left_shift = 1 << 12,
      e_key_right_shift = 1 << 13,
      e_key_shift = e_key_left_shift | e_key_right_shift,
      e_key_left_control = 1 << 14,
      e_key_right_control = 1 << 15,
      e_key_control = e_key_left_control | e_key_right_control,
      e_key_left_alt = 1 << 16,
      e_key_right_alt = 1 << 17,
      e_key_alt = e_key_left_alt | e_key_right_alt,
      e_key_left_command = 1 << 18,
      e_key_right_command = 1 << 19,
      e_key_command = e_key_left_command | e_key_right_command,
      e_key_system_left_command = 1 << 20,
      e_key_system_right_command = 1 << 21,
      e_key_system_command = e_key_system_left_command | e_key_system_right_command,
      e_key_left_button = 1LL <<24,
      e_key_right_button = 1LL << 25,
      e_key_middle_button = 1LL << 26,

   };


   DECLARE_ENUMERATION(e_key, enum_key);


} // namespace user



