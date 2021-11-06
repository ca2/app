#pragma once


namespace user
{


   e_desktop get_edesktop();

   bool gsettings_set(const ::string & pszSchema, const ::string & pszKey, const ::string & pszValue);

   bool gsettings_sync();

   char * gsettings_get_malloc(const ::string & pszSchema, const ::string & pszKey);

   bool g_enable_wallpaper_change_notification(const ::string & pszSchema, const ::string & pszKey);

   void g_defer_init();

   void g_defer_term();


} // namespace user
