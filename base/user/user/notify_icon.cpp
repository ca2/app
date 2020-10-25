#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


static ::user::notify_icon * g_pnotifyiconLast = nullptr;


#ifdef LINUX

#include "aura/os/linux/appindicator.h"

#endif


namespace user
{


   notify_icon::notify_icon()
   {

      g_pnotifyiconLast = this;

#ifdef WINDOWS_DESKTOP

      m_nid.cbSize = sizeof(m_nid);

#elif defined(LINUX)

      m_pindicator = nullptr;

#endif

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

      DestroyWindow();

      if(g_pnotifyiconLast== this)
      {

         g_pnotifyiconLast = nullptr;

      }

   }


   void notify_icon::install_message_routing(::channel * pchannel)
   {

#ifdef WINDOWS_DESKTOP

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MessageNotifyIcon, pchannel, this, &notify_icon::_001OnNotifyIconMessage);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &notify_icon::_001OnDestroy);

#endif

   }


   bool notify_icon::create_notify_icon(UINT uiId, notify_icon_listener * plistener, ::draw2d::icon * pvisualicon)
   {

      if(m_bCreated)
      {

         return false;

      }

      m_strId.Format("user::notify_icon - %d", uiId);

      m_strId = "ca2-" + pvisualicon->m_strAppTrayIcon + "-" + m_strId;

#ifdef WINDOWS_DESKTOP

      if(!create_message_queue(m_strId))
      {

         return false;

      }

#endif

      m_uiId                     = uiId;

#ifdef WINDOWS_DESKTOP

      m_nid.hWnd                 = get_safe_handle();
      m_nid.uID                  = uiId;
      m_nid.hIcon                = *pvisualicon;
      m_nid.uFlags               = NIF_ICON | NIF_MESSAGE;
      m_nid.uCallbackMessage     = MessageNotifyIcon;

#elif defined(LINUX)

#elif defined(MACOS)

#elif defined(_UWP)

#elif defined(ANDROID)

#elif defined(APPLE_IOS)

#else
      __throw(todo());

#endif

      m_plistener                = plistener;

#ifdef WINDOWS_DESKTOP

      if(!Shell_NotifyIcon(NIM_ADD, &m_nid))
      {

         m_plistener = nullptr;

         DestroyWindow();

         return false;

      }

#elif defined(LINUX) && !defined(RASPBIAN)

      {

         string strAppId = pvisualicon->m_strAppTrayIcon;

         string strId(strAppId);

         string strMatterRoot = ::str::token(strId, "/");

         if(strMatterRoot.is_empty())
         {

            strMatterRoot = "app";

         }

         ::file::path pathFolder("appmatter://" + strMatterRoot);

         pathFolder /= "_matter" / strId / "_std/_std/main" ;

         string strNotifyIcon = _002Underscore(strAppId);

         ::file::path path = pathFolder / (strNotifyIcon + "_128.png");

         path = Context.defer_process_path(path);

         pathFolder = path.folder();

         main_sync([&]()
         {

            m_pindicator = ::linux::allocate_appindicator();

            m_pindicator->create(m_strId, strNotifyIcon + "_128", pathFolder, this);

         });

      }

      if(m_pindicator == nullptr)
      {

         m_plistener = nullptr;

         //DestroyWindow();

         return false;

      }

#elif defined(MACOS)

//      string strFolder;
//
//      string str1 = pvisualicon->m_strAppTrayIcon;
//
//      str1.replace("-", "_");
//
//      str1.replace("/", "_");
//
//      str1.replace("\\", "_");
//
//      string str(str1);
//
//      if(::str::begins_eat_ci(str, "app_veriwell_"))
//      {
//
//         strFolder+="app-veriwell";
//
//      }
//      else if(::str::begins_eat_ci(str, "app_core_"))
//      {
//
//         strFolder+="app-core";
//
//      }
//      else
//      {
//
//         strFolder+="app";
//
//      }
//
//      //str
//
//      strFolder+= "/appmatter/" + str;
//
//      strFolder += "/_std/_std/main/";
//
//      string strFile = "menubar-icon-22.png";
//
//      string strUrl = "https://server.ca2.cc/matter/" + strFolder + strFile;
//
//      strFile = Context.dir().appdata() / strFolder / strFile;
//
//      int iRetry = 3;
//
//      while(iRetry >= 0 && (!Context.file().exists(strFile) || Context.file().length(strFile) <= 0))
//      {
//
//         ::property_set set;
//
//         set["raw_http"] = true;
//         set["disable_common_name_cert_check"] = true;
//
//         Context.http().download(strUrl, strFile, set);
//
//         iRetry--;
//
//      }

      string strFile;

      strFile = Context.defer_process_matter_path("matter://main/menubar-icon-22.png");

      notify_icon_init(strFile);

#else

#endif

      m_bCreated = true;

      return true;

   }


   bool notify_icon::ModifyIcon(__pointer(::draw2d::icon) hicon, bool bForce)
   {

      if(!m_bCreated)
      {

         return false;

      }

      if (!bForce && hicon == m_piconCurrent)
      {

         return true;

      }

#ifdef WINDOWS_DESKTOP

      m_nid.hIcon       = (HICON) *hicon;

      m_nid.uFlags      = NIF_ICON;

      if(!Shell_NotifyIcon(NIM_MODIFY, &m_nid))
      {

         return false;

      }

      m_piconCurrent = hicon;

      return true;

#else

      __throw(todo());

#endif


   }


   void notify_icon::AddHiddenWindow(__pointer(::user::interaction) pwnd)
   {

      m_wndptraHidden.add_unique(pwnd);

   }


#ifdef WINDOWS_DESKTOP


   void notify_icon::destroy_window()
   {

      m_nid.uFlags = 0;

      if (!Shell_NotifyIcon(NIM_DELETE, &m_nid))
      {

         //return false;

      }

      ::user::interaction::destroy_window();

   }


   void notify_icon::remove_all_routes()
   {

      ::user::interaction::remove_all_routes();

   }


   void notify_icon::PostNcDestroy()
   {

      ::user::interaction::PostNcDestroy();


   }

#endif // defined(WINDOWS_DESKTOP)


   bool notify_icon::DestroyWindow()
   {

      if(!m_bCreated)
      {

         return false;

      }

      m_bCreated = false;

#ifdef WINDOWS_DESKTOP

      ::user::interaction::DestroyWindow();

      return true;


#elif defined(LINUX) && !defined(RASPBIAN)

      if(m_pindicator)
      {

         ::linux::appindicator_destroy(m_pindicator);

         m_pindicator = nullptr;

      }

      return true;

#elif defined(MACOS)

      notify_icon_destroy();

      return true;

#else


      __throw(todo());

      return true;

#endif

   }


   void notify_icon::_001OnDestroy(::message::message* pmessage)
   {

      output_debug_string("notify_icon::_001OnDestroy");

   }


   void notify_icon::_001OnNotifyIconMessage(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (pbase->m_lparam == WM_LBUTTONDOWN)
      {

         while (m_wndptraHidden.get_size() > 0)
         {

            try
            {

               __pointer(::user::interaction) pframe = (m_wndptraHidden.element_at(0));

               if (pframe != nullptr)
               {

                  pframe->display(display_normal);

               }
               else
               {

                  m_wndptraHidden.element_at(0)->display(display_normal);

               }

            }
            catch (...)
            {

            }

            m_wndptraHidden.remove_at(0);

         }

      }

      m_plistener->OnNotifyIconMessage(m_uiId, (UINT) pbase->m_lparam);

   }


   void notify_icon::notify_icon_play(const char * action)
   {


   }


   void notify_icon::step()
   {

#if defined(LINUX)

//      main_async([&]
//      {
//
//         linux_g_direct_app_indicator_step(m_pindicator);
//
//      });

#endif

   }


#if defined(LINUX) || defined(MACOS)


   int notify_icon::_get_notification_area_action_count()
   {

      return m_plistener->_get_notification_area_action_count();

   }


   const char * notify_icon::_get_notification_area_action_name(int iIndex)
   {

      return m_plistener->_get_notification_area_action_name(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_id(int iIndex)
   {

      return m_plistener->_get_notification_area_action_id(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_label(int iIndex)
   {

      return m_plistener->_get_notification_area_action_label(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_accelerator(int iIndex)
   {

      return m_plistener->_get_notification_area_action_accelerator(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_description(int iIndex)
   {

      return m_plistener->_get_notification_area_action_description(iIndex);

   }


   void notify_icon::call_notification_area_action(const char * pszId)
   {

      m_plistener->call_notification_area_action(pszId);

   }


#endif


} // namespace user



