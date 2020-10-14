#pragma once



CLASS_DECL_ACME int get_simple_ui_darkness();
CLASS_DECL_ACME void set_simple_ui_darkness(int iDarkness);
CLASS_DECL_ACME color get_simple_ui_color(::user::e_element eelement, ::user::estate estate = ::user::e_state_none);


namespace user
{

   CLASS_DECL_ACME void set_system_dark_mode(bool bDark);
   CLASS_DECL_ACME void set_app_dark_mode(bool bDark);
   CLASS_DECL_ACME bool is_system_dark_mode();
   CLASS_DECL_ACME bool is_app_dark_mode();
   CLASS_DECL_ACME ::color get_system_app_background_color();
   CLASS_DECL_ACME void set_system_app_background_color(::color color);
   CLASS_DECL_ACME double get_system_app_luminance();
   CLASS_DECL_ACME void set_system_app_luminance(double dLuminance);


   CLASS_DECL_ACME void os_calc_dark_mode();


} // namespace user



