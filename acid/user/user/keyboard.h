// Created by camilo on 2023-05-19 07:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "acid/constant/user_key.h"


namespace keyboard
{


   constexpr bool has_shift(const ::user::e_key& ekey) { return ekey & ::user::e_key_shift; }
   constexpr bool has_control(const ::user::e_key& ekey) { return ekey & ::user::e_key_control; }
   constexpr bool has_alt(const ::user::e_key& ekey) { return ekey & ::user::e_key_alt; }
   constexpr bool has_command(const ::user::e_key& ekey) { return ekey & ::user::e_key_command; }
   constexpr bool has_system_command(const ::user::e_key& ekey) { return ekey & ::user::e_key_system_command; }


   constexpr bool has_left_button(const ::user::e_key& ekey) { return ekey & ::user::e_key_left_button; }
   constexpr bool has_right_button(const ::user::e_key& ekey) { return ekey & ::user::e_key_right_button; }
   constexpr bool has_middle_button(const ::user::e_key& ekey) { return ekey & ::user::e_key_middle_button; }


   CLASS_DECL_ACID ::string key_string_with_no_modifier(::user::e_key ekey);

   CLASS_DECL_ACID ::string modifiers_groups_string(::user::e_key ekey);

   CLASS_DECL_ACID ::string key_string_with_modifiers_groups(::user::e_key ekey);

   CLASS_DECL_ACID ::user::e_key string_key_with_no_modifier(const ::scoped_string& scopedstr);

   CLASS_DECL_ACID ::user::e_key string_key_modifiers_groups(::string & strWillKeyWithNoModifiers);

   CLASS_DECL_ACID ::user::e_key string_key(const ::scoped_string & scopedstrWithNoModifiers, ::user::e_key ekeyModifier);

   CLASS_DECL_ACID ::user::e_key string_key(const ::scoped_string & scopedstr);

   CLASS_DECL_ACID bool is_equivalent_using_modifiers_groups(::user::e_key ekey1, ::user::e_key ekey2);

   CLASS_DECL_ACID ::user::e_key modifiers_groups(::user::e_key ekey);

   CLASS_DECL_ACID::user::e_key key_with_no_modifier(::user::e_key ekey);


} // keyboard



