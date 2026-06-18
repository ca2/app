// Created by camilo on 2023-05-19 07:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/user_key.h"
#include "acme/user/key/state.h"


namespace keyboard
{


   //constexpr ::i32_boolean has_shift(const ::user::e_key& ekey) { return ekey & ::user::e_key_shift; }
   //constexpr ::i32_boolean has_control(const ::user::e_key& ekey) { return ekey & ::user::e_key_control; }
   //constexpr ::i32_boolean has_alt(const ::user::e_key& ekey) { return ekey & ::user::e_key_alt; }
   //constexpr ::i32_boolean has_command(const ::user::e_key& ekey) { return ekey & ::user::e_key_command; }
   //constexpr ::i32_boolean has_system_command(const ::user::e_key& ekey) { return ekey & ::user::e_key_system_command; }


   //constexpr bool has_left_button(const ::user::e_key& ekey) { return ekey & ::user::e_key_left_button; }
   //constexpr bool has_right_button(const ::user::e_key& ekey) { return ekey & ::user::e_key_right_button; }
   //constexpr bool has_middle_button(const ::user::e_key& ekey) { return ekey & ::user::e_key_middle_button; }


   CLASS_DECL_ACME ::string user_key_as_string(const ::user::e_key & ekey);

   CLASS_DECL_ACME ::string modifiers_groups_string(const ::user::e_key & ekey);

   CLASS_DECL_ACME ::string key_string_with_modifiers_groups(const ::user::e_key & ekey, const ::key::e_state & ekeystate);

   CLASS_DECL_ACME ::user::e_key string_as_user_key(const ::scoped_string& scopedstr);

   CLASS_DECL_ACME ::user::e_key string_key_state_groups(::string & strWillKeyWithNoModifiers);

   //CLASS_DECL_ACME ::user::e_key string_key(const ::scoped_string & scopedstrWithNoModifiers, ::key::e_state ekeyModifier);

   //CLASS_DECL_ACME ::user::e_key string_key(const ::scoped_string & scopedstr);

   //CLASS_DECL_ACME bool is_equivalent_using_modifiers_groups(::user::e_key ekey1, ::user::e_key ekey2);

   //CLASS_DECL_ACME ::user::e_key modifiers_groups(const ::user::e_key & ekey);

   //CLASS_DECL_ACME::user::e_key key_with_no_modifier(const ::user::e_key & ekey);


} // keyboard



