#include "framework.h"
#include "acme/id.h"
#include "_.h"
#include "acme/os/x11/_x11.h"
#include <gio/gio.h>
#include <gtk/gtk.h>


void __copy(::color & color, const GdkRGBA & rgba)
{

   color.set(rgba.red, rgba.green, rgba.blue, rgba.alpha);

}

void __gtk_style_context_get_color(GtkStyleContext *context, GtkStateFlags state, const char * pszProperty, ::color & color)
{

   GdkRGBA * prgba = nullptr;

   gtk_style_context_get (context, state, pszProperty, &prgba, NULL);

   __copy(color, *prgba);

   gdk_rgba_free (prgba);

}


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


   void wallpaper_change_notification (GSettings * settings, const gchar * key, gpointer data)
   {

      System.process_subject(id_wallpaper_change);

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




   ::logic::bit g_bitLastDarkMode;



   //void os_calc_user_theme()
   //{

//      string strTheme = _os_calc_user_theme();
//
//      if(System.m_strOsUserTheme != strTheme)
//      {
//
//         System.m_strOsUserTheme = strTheme;
//
//         System.set_modified(id_os_user_theme);
//
//         x11_kick_idle();
//
//      }
//
//   }


} // namespace user


namespace user
{


   bool g_bInitializedUserTheme = false;

   string _os_get_user_theme()
   {

      if(!g_bInitializedUserTheme)
      {

         g_bInitializedUserTheme = true;

         System.start_subject_handling(id_os_user_theme);

      }

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


namespace user
{


   ::user::os_theme_colors * new_os_theme_colors(string strTheme)
   {

      auto pthemecolors = new ::user::os_theme_colors;

      GtkStyleContext *pstylecontext = gtk_style_context_new();

      GtkCssProvider *pprovider = gtk_css_provider_get_named(strTheme, nullptr);

      gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);

      {

         GtkWidget *pdialog = gtk_dialog_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pdialog);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorBack);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorFore);

         gtk_widget_destroy(pdialog);

      }

      {

         GtkWidget *pbutton = gtk_button_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pbutton);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFace);

         double dAlpha = pthemecolors->m_colorFace.get_a_rate();

         if(dAlpha < 0.95)
         {

            pthemecolors->m_colorFace.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_PRELIGHT,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFaceHover);

         dAlpha = pthemecolors->m_colorFaceHover.get_a_rate();

         if(dAlpha < 0.95)
         {

            pthemecolors->m_colorFaceHover.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_ACTIVE,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFacePress);

         dAlpha = pthemecolors->m_colorFacePress.get_a_rate();

         if(dAlpha < 0.95)
         {

            pthemecolors->m_colorFacePress.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorButton);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_PRELIGHT,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorButtonHover);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_BORDER_COLOR,
                 pthemecolors->m_colorBorder);


//         pthemecolors->m_colorBorderHover4 = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover4.blend(pthemecolors->m_colorBack, 0.8);


         gtk_widget_destroy(pbutton);

      }

      {

         GtkWidget *pwidget = gtk_list_box_row_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pwidget);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_SELECTED,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorBorderHover);

         pthemecolors->m_colorBorderPress = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover1 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover1.blend(pthemecolors->m_colorBack, 0.3);

         pthemecolors->m_colorBorderHover2 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover2.blend(pthemecolors->m_colorBack, 0.6);

         pthemecolors->m_colorBorderHover3 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover3.blend(pthemecolors->m_colorBack, 0.9);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_SELECTED,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorButtonPress);

         gtk_widget_destroy(pwidget);

      }

      return pthemecolors;

   }


   CLASS_DECL_ACME void _os_process_user_theme(string strTheme)
   {

      os_calc_dark_mode();

      _os_process_user_theme_color(strTheme);

   }


   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme)
   {

      auto pthemecolors = new_os_theme_colors(strTheme);

      auto pthemecolorsOld = ::user::os_get_theme_colors();

      if(!pthemecolorsOld || memcmp(pthemecolors, pthemecolorsOld, sizeof(::user::os_theme_colors)))
      {

         ::user::os_set_theme_colors(pthemecolors);

//         auto psubject = System.subject(id_os_user_theme);
//
//         psubject->m_esubject = e_subject_deliver;
//
//         System.process(psubject);

      }
      else
      {

         ::acme::del(pthemecolors);

      }

   }



   bool _os_calc_dark_mode()
   {

      auto pthemecolors = ::user::os_get_theme_colors();

      if(!pthemecolors)
      {

         string strTheme = _os_get_user_theme();

         pthemecolors = new_os_theme_colors(strTheme);

         ::user::os_set_theme_colors(pthemecolors);

      }

      auto dLuminance = pthemecolors->m_colorBack.get_luminance();

      return dLuminance < 0.5;

   }


   void os_calc_dark_mode()
   {

      bool bDarkMode = _os_calc_dark_mode();

      if(g_bitLastDarkMode != bDarkMode)
      {

         ::user::set_app_dark_mode(bDarkMode);

         ::user::set_system_dark_mode(bDarkMode);

         g_bitLastDarkMode = bDarkMode;

         System.deliver(id_os_dark_mode);

         x11_kick_idle();

      }

   }

} // namespace user



