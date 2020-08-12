#pragma once


namespace user
{

   // wall-changer sourceforge.net contribution
   enum e_desktop
   {

      // please note that the row of these must match the row of the corresponding combobox in Preferences Dialog.
      desktop_unity_gnome,
      desktop_gnome,
      desktop_xfce,
      desktop_lxde,
      desktop_mate,
      desktop_ubuntu_gnome,

   };


   e_desktop get_edesktop();

   bool gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue);

   int gsettings_get(char * pszValue, int iSize, const char * pszSchema, const char * pszKey);

   void initialize_edesktop();

   e_desktop calc_edesktop();


} // namespace user
