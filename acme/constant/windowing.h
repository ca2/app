// From acme/constant/user.h by
//    camilo on 2024-10-05 20:14 <3ThomasBorregaardSorensen!!
#pragma once


namespace windowing
{


   // wall-changer sourceforge.net contribution
   enum enum_desktop
   {

      // please note that the row of these must match the row of the corresponding combobox in Preferences Dialog.
      e_desktop_none,
      e_desktop_unknown,
      e_desktop_gnome,
      e_desktop_kde,
      e_desktop_unity,
      e_desktop_xfce,
      e_desktop_lxde,
      e_desktop_mate,
      e_desktop_ubuntu,
      e_desktop_windows,
      e_desktop_cinnamon

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



