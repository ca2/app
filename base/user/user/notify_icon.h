#pragma once


#if defined (__APPLE__)
#include "notify_icon_mm_bridge.h"
#endif


#ifdef LINUX
namespace linux { class appindicator; }
#endif


namespace user
{


   class notify_icon_listener;


   class CLASS_DECL_BASE notify_icon :
#ifdef WINDOWS_DESKTOP
      virtual public ::user::interaction
#else
      virtual public ::object
#endif
#ifdef LINUX
      , public user_notify_icon_bridge
#elif defined (MACOS)
      , public user_notify_icon_mm_bridge
#endif
   {
   public:


      enum e_message
      {

         MessageNotifyIcon = WM_USER + 100,

      };


      UINT     m_uiId;
      bool     m_bCreated;
      string   m_strId;
#ifdef WINDOWS_DESKTOP
      NOTIFYICONDATA m_nid;
#elif defined(LINUX)
      ::linux::appindicator *       m_pindicator;
#endif
      notify_icon_listener *     m_plistener;
      __pointer_array(::user::interaction)   m_wndptraHidden;
      __pointer(draw2d::icon)           m_piconCurrent;


      notify_icon();
      virtual ~notify_icon();



      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::object::add_ref(OBJ_REF_DBG_ARGS);

      //}


      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::object::dec_ref(OBJ_REF_DBG_ARGS);

      //}

      void AddHiddenWindow(__pointer(::user::interaction) pwnd);

      #ifdef WINDOWS_DESKTOP

      virtual void remove_all_routes() override;

      virtual bool DestroyWindow() override;

      virtual void destroy_window() override;

      virtual void PostNcDestroy() override;


      #else

      virtual bool DestroyWindow();

      #endif

      bool ModifyIcon(__pointer(::draw2d::icon) picon, bool bForce = false);

      virtual bool create_notify_icon(UINT id, notify_icon_listener * plistener, ::draw2d::icon * picon);

      DECL_GEN_SIGNAL(_001OnNotifyIconMessage);
      DECL_GEN_SIGNAL(_001OnDestroy);

      void install_message_routing(::channel * pchannel) override;

      virtual void step();

#if defined(APPLE_IOS) || defined(WINDOWS_DESKTOP) || defined(ANDROID) || defined(_UWP)
      virtual void notify_icon_play(const char * action);
#else
#if defined(LINUX)
      virtual void notify_icon_play(const char * action);
#else
      virtual void notify_icon_play(const char * action) override;
#endif
      virtual int _get_notification_area_action_count() override;
      virtual bool _get_notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex) override;
      virtual void call_notification_area_action(const char * pszId) override;
#endif


   };


} // namespace user


