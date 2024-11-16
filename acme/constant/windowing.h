// From acme/constant/user.h by
//    camilo on 2024-10-05 20:14 <3ThomasBorregaardSorensen!!
#pragma once


namespace windowing
{


   // wall-changer sourceforge.net contribution
   enum enum_operating_ambient
   {

      // please note that the row of these must match the row of the corresponding combobox in Preferences Dialog.
      e_operating_ambient_none,
      e_operating_ambient_unknown,
      e_operating_ambient_gnome,
      e_operating_ambient_kde,
      e_operating_ambient_unity,
      e_operating_ambient_xfce,
      e_operating_ambient_lxde,
      e_operating_ambient_mate,
      e_operating_ambient_ubuntu,
      e_operating_ambient_windows,
      e_operating_ambient_cinnamon,
      e_operating_ambient_ios
   };

   enum enum_toolkit
   {

      e_toolkit_none,
      e_toolkit_unknown,
      e_toolkit_win32,
      e_toolkit_gtk3,
      e_toolkit_gtk4,
      e_toolkit_kde5,
      e_toolkit_kde6,
      e_toolkit_appkit,
      e_toolkit_uikit,
      e_toolkit_android,

   };


   enum enum_windowing
   {

      e_windowing_none,
      e_windowing_win32,
      e_windowing_x11,
      e_windowing_xcb,
      e_windowing_macos,
      e_windowing_wayland,

   };




   enum enum_display_type
   {

      e_display_type_none,
      e_display_type_system = 100,
      e_display_type_x11 = 1000,
      e_display_type_xcb = 2000,
      e_display_type_wayland = 3000,

   };


} // namespace windowing



