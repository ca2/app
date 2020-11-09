#include "framework.h"
#include "platform/platform_setup.h"
#include <limits.h>
#include "__standard_type.h"
#include "gnome.h"
#include "gnome_gnome.h"
#include "gnome_internal_glue.h"
#include "apex/message/global.h"
#include "aura/const/_const.h"
#include "acme/const/id.h"
#include "platform/_.h"
#include "aura/os/linux/appindicator.h"


// apt-get install libgtk2.0-dev
// and restart codeblocks/IDE
#include <gtk/gtk.h>
#include <sys/utsname.h>



//int uname(struct utsname *buf);
#ifndef RASPBIAN
//#ifndef MANJARO
// Manjaro libappindicator-gtk3
//#include <libappindicator3-0.1/libappindicator/app-indicator.h>
//#else // MANJARO
#include <libappindicator-0.1/libappindicator/app-indicator.h>
//#endif
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

//bool linux_g_direct_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge);
// /void linux_g_direct_app_indicator_term(AppIndicator * pindicator);
//void linux_g_direct_app_indicator_step(void * pvoidInd);



#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

//class pmutex_lock
//{
//public:
//
//   pthread_mutex_t * m_pmutex;
//
//   bool m_bLock;
//
//   pmutex_lock(pthread_mutex_t * pmutex, bool bStartLocked = true) :
//      m_pmutex(pmutex)
//   {
//
//      if(bStartLocked)
//      {
//
//         lock();
//
//
//      }
//
//
//   }
//
//   ~pmutex_lock()
//   {
//
//
//   }
//
//
//   void lock()
//   {
//
//      pthread_mutex_lock(m_pmutex);
//
//   }
//
//
//   void unlock()
//   {
//
//      pthread_mutex_unlock(m_pmutex);
//
//   }
//
//};


void os_post_quit();

#ifndef RASPBIAN

GtkWidget * linux_g_direct_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge);


static void ___extra_action(GtkAction * action, void * data)
{

   ::user_notify_icon_bridge * pi = (::user_notify_icon_bridge *) data;

   pi->call_notification_area_action(gtk_action_get_stock_id(action));

}

extern "C"
{


   static void __extra_action(GtkAction * action, gpointer data)
   {

      ___extra_action(action, data);

   }


} // extern "C"





#ifndef RASPBIAN


class gnome_appindicator :
   virtual public ::linux::appindicator
{
public:


   AppIndicator * m_pindicator;


   gnome_appindicator();
   virtual ~gnome_appindicator();


   virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge) override;
   virtual bool init(user_notify_icon_bridge * pbridge);
   virtual void close();


   //virtual bool step() override;


};


gnome_appindicator::gnome_appindicator()
{

}


gnome_appindicator::~gnome_appindicator()
{

   close();

}


void gnome_appindicator::close()
{


   if(m_pindicator == NULL)
   {

      return;

   }

   auto pindicator = m_pindicator;

   gdk_fork([pindicator]()
   {

      app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);

   });

   m_pindicator = NULL;

}

namespace linux
{


   appindicator * allocate_appindicator()
   {

      return new ::gnome_appindicator();

   }


} // namespace linux


bool gnome_appindicator::create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge)
{

   m_pindicator = app_indicator_new_with_path(pszId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);

   if(m_pindicator == nullptr)
   {

      return false;

   }

   if(!init(pbridge))
   {

      close();

      return false;

   }

   return true;

}




#endif

#endif


void safe_free(void * pfree)
{

   if(pfree == nullptr)
   {

      return;

   }

   ::free(pfree);

}

void g_safe_free(void * pfree)
{

   if(pfree == nullptr)
   {

      return;

   }

   ::g_free(pfree);

}

#ifndef RASPBIAN


bool gnome_appindicator::init(user_notify_icon_bridge * pbridge)
{

   int iCount = pbridge->_get_notification_area_action_count();

   GtkWidget *  indicator_menu = nullptr;

   if(iCount > 0)
   {


      GError * error = nullptr;

      GtkActionGroup * action_group = gtk_action_group_new ("AppActions");

      if(action_group != nullptr)
      {

         GtkActionEntry * entries = new GtkActionEntry[pbridge->_get_notification_area_action_count()];

         string strInfo;

         strInfo += "<ui>";

         strInfo += "  <popup name='IndicatorPopup'>";

         int iEntry = 0;

         for(int i = 0; i < iCount; i++)
         {

            int iIndex = i;

            const char * pszName = pbridge->_get_notification_area_action_name(iIndex);
            const char * pszId = pbridge->_get_notification_area_action_id(iIndex);
            const char * pszLabel = pbridge->_get_notification_area_action_label(iIndex);
            const char * pszAccelerator = pbridge->_get_notification_area_action_accelerator(iIndex);
            const char * pszDescription = pbridge->_get_notification_area_action_description(iIndex);

            memset(&entries[iEntry], 0, sizeof(GtkActionEntry));

            if(strcasecmp(pszName, "separator") == 0)
            {

               strInfo += "<separator/>\n";

            }
            else
            {

               entries[iEntry].name = g_strdup(pszLabel);

               strInfo += "    <menuitem action='";
               strInfo += pszLabel;
               strInfo += "' />";

               entries[iEntry].stock_id = g_strdup(pszId);

               entries[iEntry].label = g_strdup(pszName);

               //entries[iEntry].accelerator = g_strdup(pszAccelerator);

               entries[iEntry].accelerator = nullptr;

               entries[iEntry].tooltip = g_strdup(pszDescription);

               entries[iEntry].callback = G_CALLBACK (__extra_action);

               iEntry++;

            }

         }

         strInfo += "  </popup>";
         strInfo += "</ui>";

         gtk_action_group_add_actions (action_group, entries, iEntry, pbridge);

         GtkUIManager * uim = gtk_ui_manager_new ();

         bool bOk = false;

         gchar * ui_info = (gchar *) g_strdup(strInfo);

         if(uim != nullptr)
         {

            gtk_ui_manager_insert_action_group (uim, action_group, 0);

            bOk = gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error) != FALSE;

            if(!bOk)
            {

               g_message ("Failed to build menus: %s\n", error->message);

               g_error_free (error);

               error = nullptr;

            }

         }

         for(int i = 0; i < iEntry; i++)
         {

            g_safe_free((void *) entries[i].name);
            g_safe_free((void *) entries[i].stock_id);
            g_safe_free((void *) entries[i].label);
            g_safe_free((void *) entries[i].accelerator);
            g_safe_free((void *) entries[i].tooltip);

         }

         delete [] entries;

         g_safe_free(ui_info);

         if(bOk)
         {

            indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");

            app_indicator_set_menu(m_pindicator, GTK_MENU (indicator_menu));

         }

      }

   }

   app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_ACTIVE);

   return true;

}


#endif


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
         else if(strcasecmp(pszDesktop, "ubuntu:gnome") == 0)
         {

            return desktop_ubuntu_gnome;

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

      return desktop_gnome;

   }


   void wallpaper_change_notification (GSettings   *settings,             const gchar *key,             gpointer     data)
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

      pGtkIconInfo = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);

      if(pGtkIconInfo == nullptr)
      {

         return nullptr;

      }

      const char * point = gtk_icon_info_get_filename(pGtkIconInfo);

      char * psz = nullptr;

      if(point != nullptr)
      {

         psz = strdup(point);

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

   const char * point = nullptr;

   if(pszContentType != nullptr)
   {

      point = strdup(pszContentType);

   }

   return point;

}


int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
{

   gboolean ret;

   GError * error = NULL;

   g_type_init();

   ret = g_app_info_launch_default_for_uri(pszUri, NULL, &error);

   if(ret)
   {

      return true;

   }

   if(pszError != nullptr)
   {

      strncpy(pszError, error->message, iBufferSize);

   }

   return 0;

}



