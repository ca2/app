#include "framework.h"
#include "platform/platform_setup.h"
#include <limits.h>
#include "__standard_type.h"
#include "gnome.h"
#include "gnome_gnome.h"
#include "gnome_internal_glue.h"
#include "apex/message/global.h"
#include "apex/const/_const.h"
#include "apex/const/id.h"
#include "platform/_.h"
//#include "apex/os/linux/appindicator.h"


// apt-get install libgtk2.0-dev
// and restart codeblocks/IDE
#include <gtk/gtk.h>
#include <sys/utsname.h>



//int uname(struct utsname *buf);
#ifndef RASPBIAN
//#ifndef MANJARO
// Manjaro libappindicator-gtk3
#include <libappindicator3-0.1/libappindicator/app-indicator.h>
//#include <libappindicator-0.1/libappindicator/app-indicator.h>
//#else // MANJARO
//#include <libappindicator-0.1/libappindicator/app-indicator.h>
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
//

void os_post_quit();


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



