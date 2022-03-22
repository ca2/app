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
      , virtual public ::user::notify_icon_listener
   {
   public:


      bool                                               m_bCreated;
      string                                             m_strId;
      __pointer(::user::interaction)               m_puserinteractionNotify;
      //__pointer(notify_icon_listener)                 m_plistener;
      __pointer_array(::user::interaction)         m_userinteractionaHidden;
      __pointer(::windowing::icon)                 m_piconCurrent;


      notify_icon();
      ~notify_icon() override;


      virtual void add_hidden_window(::user::interaction * puserinteraction);

      virtual void destroy_notify_icon();

      virtual void modify_icon(::windowing::icon * picon);

      //virtual void create_notify_icon(::u32 atom, notify_icon_listener * plistener, ::windowing::icon * picon);

      virtual void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon);

      bool step() override;


      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      void on_command(::message::command * pcommand) override;


      virtual int _get_notification_area_action_count() override;
      virtual const char * _get_notification_area_action_name(int iIndex) override;
      virtual const char * _get_notification_area_action_id(int iIndex) override;
      virtual const char * _get_notification_area_action_label(int iIndex) override;
      virtual const char * _get_notification_area_action_accelerator(int iIndex) override;
      virtual const char * _get_notification_area_action_description(int iIndex) override;
      virtual void call_notification_area_action(const char * pszId) override;


   };


} // namespace user



