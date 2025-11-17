// From acme/constant/user.h by
//    camilo on 2024-10-05 20:14 <3ThomasBorregaardSorensen!!
#pragma once


namespace windowing
{


   // wall-changer sourceforge.net contribution
   enum enum_operating_ambient : long long
   {

      // please note that the row of these must match the row of the corresponding combobox in Preferences Dialog.
      e_operating_ambient_none,
      e_operating_ambient_unknown,
      e_operating_ambient_gnome,
      e_operating_ambient_kde,
      e_operating_ambient_unity,
      e_operating_ambient_xfce,
      e_operating_ambient_lxde,
      e_operating_ambient_lxqt,
      e_operating_ambient_labwc,
      e_operating_ambient_mate,
      e_operating_ambient_ubuntu,
      e_operating_ambient_universal_windows,
      e_operating_ambient_windows,
      e_operating_ambient_cinnamon,
      e_operating_ambient_ios,
      e_operating_ambient_macos,
      e_operating_ambient_android


   };


   enum enum_toolkit : long long
   {

      e_toolkit_none,
      e_toolkit_unknown,
      e_toolkit_win32,
      e_toolkit_gtk3,
      e_toolkit_gtk4,
      e_toolkit_kde5,
      e_toolkit_kde6,
      e_toolkit_lxq2,
      e_toolkit_lxq1,
      e_toolkit_appkit,
      e_toolkit_uikit,
      e_toolkit_android,
      e_toolkit_universal_windows,


   };
   

   enum enum_windowing : long long
   {

      e_windowing_unknown = -1,
      e_windowing_none,
      e_windowing_win32,
      e_windowing_x11,
      e_windowing_xcb,
      e_windowing_macos,
      e_windowing_wayland,

   };


   enum enum_display_type : long long
   {

      e_display_type_none,
      e_display_type_system = 100,
      e_display_type_x11 = 1000,
      e_display_type_xcb = 2000,
      e_display_type_wayland = 3000,

   };


   enum enum_bias : long long
   {

      e_bias_unknown = -1,
      e_bias_none = 0,
      e_bias_linux_mint_x_cinnamon_22_1,

   };


} // namespace windowing



