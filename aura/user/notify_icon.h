#pragma once


//#if defined (__APPLE__)
//#include "notify_icon_mm_bridge.h"
//#endif


//#ifdef LINUX
#include "apex/user/notify_icon_bridge.h"
//namespace linux { class appindicator; }
//#endif


namespace user
{


   class notify_icon_listener;


   class CLASS_DECL_AURA notify_icon :
#ifdef WINDOWS_DESKTOP
      virtual public ::user::interaction
#else
      virtual public ::object
#endif
   {
   public:


      enum e_message
      {

         MessageNotifyIcon = WM_USER + 100,

      };


      //__pointer(user_notify_icon_bridge)           m_pbridge;
      ::u32                                        m_uiId;
      bool                                         m_bCreated;
      string                                       m_strId;
//#ifdef WINDOWS_DESKTOP
//      NOTIFYICONDATA m_nid;
//#elif defined(LINUX)
//      ::linux::appindicator *       m_pindicator;
//#endif
      __pointer(notify_icon_listener)              m_plistener;
      __pointer_array(::user::interaction)      m_wndptraHidden;
      __pointer(::windowing::icon)                 m_piconCurrent;


      notify_icon();
      virtual ~notify_icon();


      void AddHiddenWindow(__pointer(::user::interaction) puserinteraction);

      //#ifdef WINDOWS_DESKTOP

      //virtual void erase_all_routes() override;

      //virtual bool DestroyWindow() override;

      //virtual void destroy_window() override;

      //virtual void PostNcDestroy() override;


      //#else

      //virtual bool DestroyWindow();

      //#endif

      virtual ::e_status destroy_notify_icon();

      bool modify_icon(::windowing::icon * picon);

      virtual bool create_notify_icon(::u32 id, notify_icon_listener * plistener, ::windowing::icon * picon);

      //DECLARE_MESSAGE_HANDLER(_001OnNotifyIconMessage);
      //DECLARE_MESSAGE_HANDLER(_001OnDestroy);

      //void install_message_routing(::channel * pchannel) override;

      virtual ::e_status step() override;

//#if defined(APPLE_IOS) || defined(WINDOWS_DESKTOP) || defined(ANDROID) || defined(_UWP)
//      virtual void notify_icon_play(const char * action);
//#else
//#if defined(LINUX)
//      virtual void notify_icon_play(const char * action);
//#else
//      virtual void notify_icon_play(const char * action) override;
//#endif
//#ifndef WINDOWS_DESKTOP
      virtual int _get_notification_area_action_count() ;
      virtual const char * _get_notification_area_action_name(int iIndex) ;
      virtual const char * _get_notification_area_action_id(int iIndex) ;
      virtual const char * _get_notification_area_action_label(int iIndex) ;
      virtual const char * _get_notification_area_action_accelerator(int iIndex) ;
      virtual const char * _get_notification_area_action_description(int iIndex) ;
      virtual void call_notification_area_action(const char * pszId) ;
//#endif
      //virtual void notify_icon_init(const char * pszFile);

//#endif


   };


} // namespace user



