#pragma once


#include "base/user/experience/frame_window.h"


class CLASS_DECL_BASE simple_frame_window :
   virtual public ::experience::frame_window
{
public:


   //bool                                            m_bDefaultNotifyIcon2 : 1;
   bool                                            m_bShowTask : 1;
   bool                                            m_bFramePayloadFlags : 1;
   bool                                            m_bProdevianFrame : 1;
   bool                                            m_bFirstShow : 1;
   bool                                            m_bPendingSaveWindowRect : 1;
   bool                                            m_bTransparentFrameEnable : 1;
   bool                                            m_bCustomFrameBefore : 1;
   bool                                            m_bToolbar : 1;
   bool                                            m_bHideOnCloseMessage : 1;
   ::pointer<::user::tool_window>                  m_ptoolwindowFont;
   class ::time                                      m_timeLastSaveWindowRect;
   class ::time                                      m_timeLastSaveWindowRectRequest;
   ::image::image_pointer                                 m_pimageBk;
   ::int_rectangle                                 m_FullScreenWindowRect;
   ::pointer<::image::fastblur>                   m_pfastblur;
   ::image::image_pointer                                 m_pimageBlur;
   ::user::enum_translucency                       m_etranslucencyFrame;
   ::image::image_pointer                                 m_pimageAlpha;
   ::string                                        m_strDataKeyFrame;
   ::pointer<::windowing::icon>                    m_piconNotify;
   ::pointer<::user::notify_icon>                  m_pnotifyicon;
   ::payload                                       m_varFrame;
   ::pointer<::task>                               m_ptask_save_window_placement;
   ::user::tab_impact *                            m_ptabimpact;


   simple_frame_window();
   ~simple_frame_window() override;


   virtual void initialize(::particle * pparticle) override;
   
   
   ::user::notify_icon * notify_icon() override;


   virtual bool has_notify_icon();

   
   void on_system_command(const ::e_system_command & esystemcommand) override;


   virtual void enable_default_notification_icon(bool bEnableDefaultNotificationIcon = true);


   ::user::enum_translucency get_translucency(::user::style* pstyle) override;


   virtual void task_save_window_placement();
   virtual void task_intensive_save_window_placement();

   virtual void defer_save_window_placement() override;

   virtual void default_notify_icon_topic(::user::activation_token * puseractivationtoken);
   virtual bool would_display_notify_icon();


   bool keyboard_focus_is_focusable() override;

   bool create_bars() override;
   void on_create_bars() override;

   void _on_configure_notify_unlocked(const ::int_rectangle & rectangle) override;

   void install_message_routing(::channel * pchannel) override;

   virtual bool on_before_set_parent(::pointer<::user::interaction>pframewindow);
   bool on_set_parent(::user::interaction_base * puiParent) override;
   void on_after_set_parent() override;

   
   //void raw_rectangle(::int_rectangle & rectangle, ::user::enum_layout elayout = ::user::e_layout_sketch) override;
   ::int_rectangle rectangle(::user::enum_layout elayout = ::user::e_layout_sketch) override;


   virtual bool is_application_main_window();

   bool GetCustomFrame();
   void SetCustomFrame(bool bCustom);
   void SetBorderRect(const ::int_rectangle & rectangle) override;
   void GetBorderRectangle(::int_rectangle * prectangle) override;

   ::color::color get_border_main_body_color() override;

   void ImpactOnActivateFrame(::pointer<::user::impact>pimpact, unsigned int user, ::pointer<::user::interaction>frame);

   virtual void ToggleFullScreen();
   void WfiOnFullScreen() override;
   

   void _001OnAfterEnterFullScreen() override;
   
   
   void _001OnAfterExitFullScreen() override;


   virtual void show_control_bars(const ::e_display & edisplay = e_display_normal, bool bLeaveFullScreenBarsOnHide = false);

   bool _001OnBeforeEnterAppearance() override;
   void initialize_frame_window_experience() override;


   //void _001OnAfterExitAppearance() override;

   virtual void WfiToggleShow();

   bool window_is_notify_icon_enabled() override;
   void OnUpdateControlBarMenu(::message::command * pcommand);

   void WindowDataSaveWindowRectangle() override;
   bool WindowDataLoadWindowRectangle() override;
   //bool WindowDataLoadWindowRectangle(bool bForceRestore = false, bool bInitialFramePosition = false) override;

   using ::experience::frame_window::frame_experience;
   virtual ::pointer < ::experience::frame > frame_experience();

   //virtual bool LoadFrame(const ::string & pszMatter, unsigned int dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, ::user::interaction * puiParent = nullptr, ::user::system * pusersystem = nullptr) override;

   virtual bool LoadFrame(const ::string & pszMatter, unsigned int dwDefaultStyle = FWS_ADDTOTITLE, ::user::interaction * puiParent = nullptr, ::user::system * pusersystem = nullptr) override;

   void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

   //virtual bool LoadToolBar(::type sptype,atom idToolBar, const ::string & pszToolBar,unsigned int dwCtrlStyle = TBSTYLE_FLAT,unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);



   //bool _001FancyInitialFramePlacement(bool bForceRestore = false) override;
   virtual void on_frame_position();

   ::pointer<::user::interaction>WindowDataGetWnd();
   void on_layout(::draw2d::graphics_pointer & pgraphics) override;
   void on_reposition() override;
   void ActivateFrame(::e_display edisplay = e_display_undefined) override;
   bool on_create_client(::user::system * pusersystem) override;

   bool pre_create_window(::user::system * pusersystem) override;
   void pre_translate_message(::message::message * pmessage) override;

   void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   bool _000OnBeforeDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void draw_frame_and_control_box_over(::draw2d::graphics_pointer & pgraphics);

   void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
   virtual void draw_frame(::draw2d::graphics_pointer & pgraphics);


   void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


   //void command_handler(const ::atom & atom) override;


   virtual bool _001CanEnterScreenSaver() override;

   DECLARE_MESSAGE_HANDLER(on_message_create);
   DECLARE_MESSAGE_HANDLER(_001OnDdeInitiate);
   DECLARE_MESSAGE_HANDLER(on_message_destroy);
   DECLARE_MESSAGE_HANDLER(on_message_move);
   DECLARE_MESSAGE_HANDLER(on_message_size);
   DECLARE_MESSAGE_HANDLER(on_message_close);
   DECLARE_MESSAGE_HANDLER(on_message_show_window);
   DECLARE_MESSAGE_HANDLER(_001OnImpactFullScreen);
   DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateImpactFullScreen);
   DECLARE_MESSAGE_HANDLER(_001OnToggleCustomFrame);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateToggleCustomFrame);
   DECLARE_MESSAGE_HANDLER(_001OnToggleTransparentFrame);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateToggleTransparentFrame);
   DECLARE_MESSAGE_HANDLER(_001OnGetMinMaxInfo);
   DECLARE_MESSAGE_HANDLER(on_message_app_exit);
   DECLARE_MESSAGE_HANDLER(_001OnNotifyIconTopic);
   DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
   DECLARE_MESSAGE_HANDLER(_001OnActivate);
   DECLARE_MESSAGE_HANDLER(_001OnActivateApp);
   DECLARE_MESSAGE_HANDLER(on_message_display_change);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateNotifyIcon);
   DECLARE_MESSAGE_HANDLER(_001OnKey);
   DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);


   virtual void _000OnMouseLeave(::message::message* pmessage) override;

   virtual bool updown_get_up_enable() override;
   virtual bool updown_get_down_enable() override;


   virtual class mini_dock_frame_window* CreateFloatingFrame(unsigned int uStyle);
   //virtual void NotifyFloatingWindows(unsigned int dwFlags) override;


   virtual void design_down() override;
   virtual void design_up() override;


   //virtual bool calc_layered() override;


   virtual string get_window_default_matter() override;


   // void assert_ok() const override;
   // void dump(dump_context & dumpcontext) const override;


   void OnHScroll(unsigned int nSBCode, unsigned int nPos, ::user::scroll_bar* pScrollBar);
   void OnVScroll(unsigned int nSBCode, unsigned int nPos, ::user::scroll_bar* pScrollBar);
   virtual void on_simple_command(::message::simple_command * psimplecommand) override;

//#ifdef WINDOWS_DESKTOP
//   virtual void OnDropFiles(HDROP hDropInfo);
//   virtual bool OnQueryEndSession();
//   virtual void OnEndSession(bool bEnding);
//#endif


   //LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam) override;
   //LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam) override;
   //LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam) override;

   void _001OnQueryEndSession(::message::message * pmessage);

   void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

   void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

   virtual void data_on_after_change(::message::message * pmessage);

   virtual void _on_show_window() override;

   virtual void on_after_graphical_update() override;

   void prepare_frame(::user::document * pdocument,bool bMakeVisible) override;

   virtual void on_timer(::timer * ptimer) override;

   virtual bool frame_is_transparent() override;




   virtual void OnInitialFrameUpdate(bool bMakeVisible) override;

   virtual void OnUpdateToolWindow(bool bVisible);

   virtual void show_task(bool bShow);

   //virtual void defer_set_icon();

   using ::user::frame_window::get_color;

   virtual void on_select_user_style();


   virtual void defer_create_notification_icon();

   virtual void call_notification_area_action(const ::atom & atom, ::user::activation_token * puseractivationtoken);

   //virtual void OnNotifyIconContextMenu(const ::atom & idNotifyIcon);
   //virtual void OnNotifyIconLButtonDblClk(const ::atom& idNotifyIcon);
   //virtual void OnNotifyIconLButtonDown(const ::atom& idNotifyIcon);

   virtual void notification_area_action(const ::atom & atom, ::user::activation_token * puseractivationtoken);

   //virtual string notification_area_get_xml_menu();

   void on_update_notify_icon_menu(::collection::index & iNotifyIconIndex) override;

   virtual void on_update_notify_icon_menu_header(::collection::index & iNotifyIconItem);

   virtual void on_update_notify_icon_menu_top(::collection::index & iNotifyIconItem);

   virtual void on_update_notify_icon_menu_main(::collection::index & iNotifyIconItem);

   virtual void on_update_notify_icon_menu_bottom(::collection::index & iNotifyIconItem);

   virtual void on_update_notify_icon_menu_footer(::collection::index & iNotifyIconItem);

};



