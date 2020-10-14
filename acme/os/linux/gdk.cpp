#include "framework.h"
#include "acme/id.h"
#include "_.h"
#include "acme/os/x11/_x11.h"
#include <gio/gio.h>
#include <gtk/gtk.h>


namespace user
{


   bool gsettings_get(string & str, const char * pszSchema, const char * pszKey)
   {

      char * psz = gsettings_get_malloc(pszSchema, pszKey);

      if(psz == nullptr)
      {

         return false;

      }

      try
      {

         str = psz;

      }
      catch(...)
      {

      }

      try
      {

         ::free(psz);

      }
      catch(...)
      {

      }

      return true;

   }


}


namespace user
{


   bool g_bGInitialized = false;


   pthread_mutex_t g_mutexG;


   bool gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue)
   {

      if(pszSchema == nullptr)
      {

         return false;

      }

      if(pszKey == nullptr)
      {

         return false;

      }

      if(pszValue == nullptr)
      {

         return false;

      }

      if(!os_defer_init_gtk())
      {

         return false;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return false;

      }

      gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);

      if (settings != nullptr)
      {

         g_object_unref (settings);

      }

      return bOk;

   }


   bool gsettings_sync()
   {

      if(!os_defer_init_gtk())
      {

         return false;

      }

      g_settings_sync ();

      return true;

   }


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey)
   {

      if(pszSchema == nullptr)
      {

         return nullptr;

      }

      if(pszKey == nullptr)
      {

         return nullptr;

      }

      if(!os_defer_init_gtk())
      {

         return nullptr;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return nullptr;

      }

      gchar * pgchar = g_settings_get_string (settings, pszKey);

      if(pgchar == nullptr)
      {

         g_object_unref (settings);

         return nullptr;

      }

      char * psz = strdup(pgchar);

      g_free (pgchar);

      g_object_unref (settings);

      return psz;

   }


   e_desktop g_edesktop = desktop_none;


   e_desktop get_edesktop()
   {

      if(g_edesktop == desktop_none)
      {

         initialize_edesktop();

      }

      return g_edesktop;

   }


   void initialize_edesktop()
   {

      g_edesktop = calc_edesktop();

   }


   e_desktop calc_edesktop()
   {

      const char * pszDesktop = getenv("XDG_CURRENT_DESKTOP");

//      utsname name;
//
//      memset(&name, 0, sizeof(utsname));
//
//      uname(&name);

      if(pszDesktop != nullptr)
      {

         if(strcasecmp(pszDesktop, "Unity") == 0)
         {

            return desktop_unity_gnome;

         }

      }

      if(strcasecmp(pszDesktop, "ubuntu:gnome") == 0)
      {

         return desktop_ubuntu_gnome;

      }
      else if(is_dir("/etc/xdg/lubuntu"))
      {

         return desktop_lxde;

      }
      else if(file_exists("/usr/bin/xfconf-query"))
      {

         return desktop_xfce;

      }
      else if(file_exists("/usr/bin/mate-about"))
      {

         return desktop_mate;

      }
      else if(file_exists("/usr/bin/unity"))
      {

         return desktop_unity_gnome;

      }

      return desktop_gnome;

   }


   void wallpaper_change_notification (GSettings   *settings,             const gchar *key,             gpointer     data)
   {

      system_call_update(id_wallpaper_change);

   }


   GAction * g_pactionWallpaper = nullptr;


   bool g_enable_wallpaper_change_notification(const char * pszSchema, const char * pszKey)
   {

      if(!g_bGInitialized)
      {

         return false;

      }

      pmutex_lock lock(&g_mutexG);

      if(g_pactionWallpaper != nullptr)
      {

         return true;

      }

      GSettings * settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return false;

      }

      g_pactionWallpaper = g_settings_create_action (settings, pszKey);

      g_object_unref (settings);

      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK (wallpaper_change_notification), nullptr);

      return true;

   }


   void g_defer_init()
   {

      if(g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = true;

      pthread_mutex_init(&g_mutexG, nullptr);

   }


   void g_defer_term()
   {

      if(!g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = false;

      if(g_pactionWallpaper != nullptr)
      {

         g_object_unref(g_pactionWallpaper);

         g_pactionWallpaper = nullptr;

      }

      pthread_mutex_destroy(&g_mutexG);

   }



   bool _os_calc_dark_mode()
   {

      string strTheme = ::os::get_os_desktop_theme();

      return strTheme.contains_ci("dark");

   }


   ::set g_bLastDarkMode;


   void os_calc_dark_mode()
   {

      bool bDarkMode = _os_calc_dark_mode();

      if(g_bLastDarkMode != bDarkMode)
      {

         ::user::set_app_dark_mode(bDarkMode);

         ::user::set_system_dark_mode(bDarkMode);

         g_bLastDarkMode = bDarkMode;

         ::update_notification_task::set_modified(id_dark_mode);

         x11_kick_idle();

      }

   }


} // namespace user


namespace os
{

   string get_os_desktop_theme()
   {

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      string strTheme;

      bool bOk = false;

      switch (::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         bOk = ::user::gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme");

         break;

      case ::user::desktop_mate:

         bOk = ::user::gsettings_get(strTheme, "org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      return strTheme;

   }


   string get_wallpaper(::index iIndex)
   {

      // wall-changer sourceforge.net contribution

      bool bOk = false;

      string strWallpaper;

      switch (::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         bOk = ::user::gsettings_get(strWallpaper, "org.gnome.desktop.background", "picture-uri");

         break;

      case ::user::desktop_mate:

         bOk = ::user::gsettings_get(strWallpaper, "org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      ::str::begins_eat_ci(strWallpaper, "file://");

      return strWallpaper;

   }


} // namespace os


bool g_bInitGtk = false;


::estatus g_estatusInitGtk = ::error_none;


::estatus os_defer_init_gtk()
{

   if(!g_bInitGtk)
   {

      g_bInitGtk = true;

      if(!gtk_init_check(process_get_pargc(), process_get_pargv()))
      {

         g_estatusInitGtk = ::error_failed;

      }
      else
      {

         g_estatusInitGtk = ::success;

      }

   }

   return g_estatusInitGtk;

}





