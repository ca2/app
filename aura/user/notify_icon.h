#pragma once


namespace user
{


   class notify_icon_listener;


   class CLASS_DECL_AURA notify_icon :
#ifdef WINDOWS_DESKTOP
      virtual public ::user::interaction
#else
      virtual public ::channel
#endif
   {
   public:


      enum e_message
      {

         MessageNotifyIcon = WM_USER + 100,

      };


      ::u32                                           m_uiId;
      bool                                            m_bCreated;
      string                                          m_strId;
      __pointer(notify_icon_listener)                 m_plistener;
      __pointer_array(::user::interaction)         m_userinteractionaHidden;
      __pointer(::windowing::icon)                 m_piconCurrent;


      notify_icon();
      ~notify_icon() override;


      virtual ::e_status add_hidden_window(::user::interaction * puserinteraction);

      virtual ::e_status destroy_notify_icon();

      virtual ::e_status modify_icon(::windowing::icon * picon);

      virtual ::e_status create_notify_icon(::u32 id, notify_icon_listener * plistener, ::windowing::icon * picon);

      ::e_status step() override;


      void route_command_message(::message::command* pcommand) override;

      
      void on_command_message(::message::command * pcommand) override;


      virtual int _get_notification_area_action_count() ;
      virtual const char * _get_notification_area_action_name(int iIndex) ;
      virtual const char * _get_notification_area_action_id(int iIndex) ;
      virtual const char * _get_notification_area_action_label(int iIndex) ;
      virtual const char * _get_notification_area_action_accelerator(int iIndex) ;
      virtual const char * _get_notification_area_action_description(int iIndex) ;
      virtual void call_notification_area_action(const char * pszId) ;


   };


} // namespace user



