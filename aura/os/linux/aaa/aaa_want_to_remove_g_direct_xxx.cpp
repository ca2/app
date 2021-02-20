#include "gnome.h"
#include "gtk_things/gnome_internal_glue.h"
#include "aura/message/message_global.h"
#include "platform/platform/platform.h"
#include "aura/const/_const.h"
#include "acme/const/id.h"

// apt-get install libgtk2.0-dev
// and restart codeblocks/IDE
#include <gtk/gtk.h>
#include <sys/utsname.h>

//int uname(struct utsname *buf);
#ifndef RASPBIAN
#ifndef MANJARO
#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#else // MANJARO
#include <libappindicator-0.1/libappindicator/app-indicator.h>
#endif
#endif

#include <malloc.h>

#include <time.h>

#include <new>

#include <gio/gio.h>

#include <string.h>

//#include <dirent.h>
#include <sys/stat.h>
//
//#endif



class pmutex_lock
{
public:

   pthread_mutex_t * mutex();

   bool m_bLock;

   pmutex_lock(pthread_mutex_t * pmutex, bool bStartLocked = true) :
      mutex()(pmutex)
   {

      if(bStartLocked)
      {

         lock();


      }


   }

   ~pmutex_lock()
   {


   }

   void lock()
   {

      pthread_mutex_lock(mutex());

   }
   void unlock()
   {

      pthread_mutex_unlock(mutex());

   }

};


void os_post_quit();

#ifndef RASPBIAN

GtkWidget * linux_g_direct_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge);




static void extra_action (GSimpleAction * simple, GVariant * parameter, gpointer user_data)
{

   ::user_notify_icon_bridge * pi = (::user_notify_icon_bridge *) user_data;

   gsize s = 0;

   const gchar * pszId  = g_variant_get_string(parameter, &s);

   pi->call_notification_area_action(pszId);

}


extern "C"
{



   static void __extra_action(GSimpleAction *simple,
                       GVariant      *parameter,
                       gpointer       user_data)
   {

      extra_action(simple, parameter, user_data);

   }


} // extern "C"









void * linux_g_direct_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge)
{

   AppIndicator * pindicator = app_indicator_new_with_path(pszId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);

   if(pindicator == nullptr)
   {

      return nullptr;

   }

   if(!linux_g_direct_app_indicator_init(pindicator, pbridge))
   {

      linux_g_direct_app_indicator_term(pindicator);

      return nullptr;

   }

   return pindicator;

}




void linux_g_direct_app_indicator_term(void * pvoidInd)
{

   AppIndicator * pindicator = (AppIndicator *) pvoidInd;

   app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);

}

#endif


void safe_free(void * pfree)
{

   if(pfree == nullptr)
   {

      return;

   }

   ::free(pfree);

}


#ifndef RASPBIAN

GtkWidget * linux_g_direct_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge)
{

   AppIndicator * m_pappindicator = pindicator;

   int iCount = pbridge->_get_notification_area_action_count();

   GtkWidget *  indicator_menu = nullptr;

   if(iCount > 0)
   {

      GMenu * menu = g_menu_new ();

      GMenu * section = g_menu_new ();

      g_menu_append_section (G_MENU(menu), NULL, G_MENU_MODEL(section));

      int iEntry = 0;

      for(int i = 0; i < iCount; i++)
      {

         char * pszName = nullptr;
         char * pszId = nullptr;
         char * pszLabel = nullptr;
         char * pszAccelerator = nullptr;
         char * pszDescription = nullptr;

         int iIndex = i;

         pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, iIndex);


         if(strcasecmp(pszName, "separator") == 0)
         {

            g_object_unref (section);

            section = g_menu_new ();

            g_menu_append_section (G_MENU(menu), NULL, G_MENU_MODEL(section));

         }
         else
         {

            GMenuItem * item = g_menu_item_new (pszLabel, NULL);
            //g_menu_item_set_icon (item, defensive_icon);
            g_menu_append_item (section, item);
            GVariant * v = g_variant_new_string(pszId);
            g_menu_item_set_action_and_target_value(item, "indicator.action", v);

//               entries[iEntry].name = pszLabel;
//
//               strcat(ui_info, "    <menuitem action='");
//               strcat(ui_info, pszLabel);
//               strcat(ui_info, "' />");
//
//               entries[iEntry].stock_id = pszId;
//
//               entries[iEntry].label = pszName;
//
//               entries[iEntry].accelerator = pszAccelerator;
//
//               entries[iEntry].tooltip = pszDescription;
//
//               entries[iEntry].callback = G_CALLBACK (__extra_action);

               iEntry++;


            }

            safe_free((void *) pszName);
            safe_free((void *) pszId);
            safe_free((void *) pszLabel);
            safe_free((void *) pszAccelerator);
            safe_free((void *) pszDescription);
         }

         g_object_unref (section);

         GSimpleActionGroup * actiongroup = g_simple_action_group_new ();

         const GActionEntry entries[] = {
            { "extra_action",         __extra_action              }
         };

         g_action_map_add_action_entries (G_ACTION_MAP (actiongroup), entries, G_N_ELEMENTS (entries), NULL);

//         GtkUIManager * uim = gtk_ui_manager_new ();

//         indicator_menu = gtk_ui_manager_get_widget (uim, "/u/IndicatorPopup");

         GtkWidget * pmenu = gtk_menu_new_from_model(G_MENU_MODEL(menu));

         gtk_widget_insert_action_group(pmenu, "indicator", G_ACTION_GROUP(actiongroup));

         app_indicator_set_menu(m_pappindicator, GTK_MENU(pmenu));

         //g_object_unref(pmenu);

         //g_object_unref(menu);

      }


   app_indicator_set_status(m_pappindicator, APP_INDICATOR_STATUS_ACTIVE);

   return indicator_menu;

}


//GtkWidget * linux_g_direct_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge)
//{
//
//   AppIndicator * m_pappindicator = pindicator;
//
//   int iCount = pbridge->_get_notification_area_action_count();
//
//   section = g_menu_new ();
//item = g_menu_item_new ("Expelliarmus", "app.expelliarmus");
//g_menu_item_set_icon (item, defensive_icon);
//g_menu_append_item (section, item);
//g_menu_append_section (menu, "Defensive Charms", section);
//g_object_unref (section);
//
//
//   GtkWidget *  indicator_menu = nullptr;
//
//   if(iCount > 0)
//      //if(false)
//   {
//
//
//      GError * error = nullptr;
//
//      GtkActionGroup * action_group = gtk_action_group_new ("AppActions");
//
//      if(action_group != nullptr)
//      {
//
//
//         GtkActionEntry * entries = new GtkActionEntry[pbridge->_get_notification_area_action_count()];
//
//         gchar * ui_info = (gchar *) malloc(1024 * 1024);
//
//         strcpy(ui_info, "<u>");
//         strcat(ui_info, "  <popup name='IndicatorPopup'>");
//
//         int iEntry = 0;
//
//         for(int i = 0; i < iCount; i++)
//         {
//
//            char * pszName = nullptr;
//            char * pszId = nullptr;
//            char * pszLabel = nullptr;
//            char * pszAccelerator = nullptr;
//            char * pszDescription = nullptr;
//
//            int iIndex = i;
//
//            pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, iIndex);
//
//            if(strcasecmp(pszName, "separator") == 0)
//            {
//
//               strcat(ui_info, "<separator/>\n");
//
//               safe_free(pszName);
//
//            }
//            else
//            {
//
//               entries[iEntry].name = pszLabel;
//
//               strcat(ui_info, "    <menuitem action='");
//               strcat(ui_info, pszLabel);
//               strcat(ui_info, "' />");
//
//               entries[iEntry].stock_id = pszId;
//
//               entries[iEntry].label = pszName;
//
//               entries[iEntry].accelerator = pszAccelerator;
//
//               entries[iEntry].tooltip = pszDescription;
//
//               entries[iEntry].callback = G_CALLBACK (__extra_action);
//
//               iEntry++;
//
//            }
//
//         }
//
//         strcat(ui_info, "  </popup>");
//         strcat(ui_info, "</u>");
//
//         gtk_action_group_add_actions (action_group, entries, iEntry, pbridge);
//
//         GtkUIManager * uim = gtk_ui_manager_new ();
//
//         bool bOk = false;
//
//         if(uim != nullptr)
//         {
//
//            gtk_ui_manager_insert_action_group (uim, action_group, 0);
//
//            bOk = gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error) != false;
//
//            if(!bOk)
//            {
//
//               g_message ("Failed to build menus: %s\n", error->message);
//
//               g_error_free (error);
//
//               error = nullptr;
//
//            }
//
//         }
//
//         for(int i = 0; i < iEntry; i++)
//         {
//
//            safe_free((void *) entries[i].name);
//            safe_free((void *) entries[i].stock_id);
//            safe_free((void *) entries[i].label);
//            safe_free((void *) entries[i].accelerator);
//            safe_free((void *) entries[i].tooltip);
//
//         }
//
//         delete [] entries;
//
//         free(ui_info);
//
//         if(bOk)
//         {
//
//            indicator_menu = gtk_ui_manager_get_widget (uim, "/u/IndicatorPopup");
//
//            app_indicator_set_menu(m_pappindicator, GTK_MENU (indicator_menu));
//
//         }
//
//      }
//
//   }
//
//   app_indicator_set_status(m_pappindicator, APP_INDICATOR_STATUS_ACTIVE);
//
//   return indicator_menu;
//
//}
//

#endif


//GtkMenuItem * linux_g_direct_data::get_menu_item_close()
//{
//
//   GtkMenuItem * pmenuitemClose = nullptr;
//
//   GList * l = gtk_container_get_children(GTK_CONTAINER(m_pmenu));
//
//   GtkWidget * pwidget = (GtkWidget *)l->data;
//
//   g_list_free1(l);
//
//   pmenuitemClose = GTK_MENU_ITEM(pwidget);
//
//   return pmenuitemClose;
//
//}



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

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return nullptr;

      }

      gchar * pgchar = g_settings_get_string (settings, pszKey);

      if(pgchar == nullptr)
      {

         g_free (pgchar);

         g_object_unref (settings);

         return nullptr;

      }

      char * psz = strdup(pgchar);

      g_free (pgchar);

      g_object_unref (settings);

      return psz;

   }


   e_desktop g_edesktop = desktop_gnome;


   e_desktop get_edesktop()
   {

      return g_edesktop;

   }


   void initialize_edesktop()
   {

      g_edesktop = calc_edesktop();

   }


   e_desktop calc_edesktop()
   {

      const char * pszDesktop = getenv("XDG_CURRENT_DESKTOP");

      utsname name;

      memset(&name, 0, sizeof(utsname));

      uname(&name);

      if(pszDesktop != nullptr)
      {

         if(strcasecmp(pszDesktop, "Unity") == 0)
         {

            return desktop_unity_gnome;

         }

      }

      if(is_dir("/etc/xdg/lubuntu"))
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
      else if(strcasecmp(pszDesktop, "ubuntu:gnome") == 0)
      {

         return desktop_ubuntu_gnome;

      }

      return desktop_gnome;

   }


   void wallpaper_change_notification (GSettings * settings, const gchar * key, gpointer data)
   {

      c_post_system_event(id_wallpaper_change);

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


} // namespace user



const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize)
{

   GFile * pfile = g_file_new_for_path (pszPath);

   if(pfile == nullptr)
   {

      return nullptr;

   }

   GError * perror = nullptr;

   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);

   if(pfileinfo == nullptr)
   {

      return nullptr;

   }

   /* you'd have to use g_loadable_icon_load to get the actual icon */
   GIcon * picon = g_file_info_get_icon (pfileinfo);

   if(picon == nullptr)
   {

      return nullptr;

   }

   if(G_IS_FILE_ICON(G_OBJECT(picon)))
   {

      GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));

      if(pfileicon == nullptr)
      {

         return nullptr;

      }

      GFile * pfileIcon = g_file_icon_get_file(pfileicon);

      if(pfileIcon == nullptr)
      {

         return nullptr;

      }

      char * psz = strdup(g_file_get_path(pfileIcon));

      return psz;

   }
   else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
   {

      GtkIconInfo *pGtkIconInfo;

      GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();

      if(pGtkIconTheme == nullptr)
      {

         return nullptr;

      }

      pGtkIconInfo=gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);

      if(pGtkIconInfo == nullptr)
      {

         return nullptr;

      }

      const char * p = gtk_icon_info_get_filename(pGtkIconInfo);

      char * psz = nullptr;

      if(p != nullptr)
      {

         psz = strdup(p);

      }

      return psz;

   }

   return nullptr;

}


const char * linux_g_direct_get_file_content_type(const char * pszPath)
{

   GFile * pfile = g_file_new_for_path (pszPath);

   if(pfile == nullptr)
   {

      return nullptr;

   }

   GError * perror = nullptr;

   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);

   if(pfileinfo == nullptr)
   {

      return nullptr;

   }

   const char * pszContentType = g_file_info_get_content_type (pfileinfo);

   const char * p = nullptr;

   if(pszContentType != nullptr)
   {

      p = strdup(pszContentType);

   }

   return p;

}




