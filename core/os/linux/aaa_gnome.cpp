#include "framework.h"
#include "gtk_things/gnome_gnome.h"
#include "aura/os/linux/appindicator.h"


namespace user
{


   bool gsettings_get(string & str, const ::string & pszSchema, const ::string & pszKey)
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


namespace linux
{


   void appindicator_destroy(appindicator * pindicator)
   {

      delete pindicator;

   }

} // namespace linux

namespace os
{

   string os_get_user_theme()
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

      case ::user::desktop_mate:

         bOk = ::user::gsettings_get(strTheme, "org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

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

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

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




