#pragma once


#include  "_const.h"


#include  "_const_key.h"


namespace user
{

   using estate = cflag < enum_state >;
   using eelement = cflag < e_element >;

   CLASS_DECL_ACME COLORREF get_system_app_background_color();

   CLASS_DECL_ACME bool is_system_dark_mode();

   CLASS_DECL_ACME bool is_app_dark_mode();

} // namespace user


CLASS_DECL_ACME int get_simple_ui_darkness();
CLASS_DECL_ACME void set_simple_ui_darkness(int iDarkness);
CLASS_DECL_ACME color get_simple_ui_color(::user::e_element eelement, ::user::estate estate = ::user::e_state_none);



