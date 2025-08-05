#pragma once


#include "aura/user/user/main_window.h"
#include "aura/user/user/notify_icon_listener.h"



namespace user
{


   class CLASS_DECL_BERG frame_window :
      virtual public ::user::main_window,
      virtual public ::user::notify_icon_listener
   {
   public:


      enum EColumn
      {

         ColumnWindowRect

      };

      // idle update of frame ::account::user interface
      enum IdleFlags
      {

         idleMenu = 1,
         idleTitle = 2,
         idleNotify = 4,
         idleLayout = 8

      };

      pointer_array < ::user::control_bar >        m_controlbara; // array of all control bars that have this interaction_impl as their dock site

      //bool                                       m_bAutoWindowFrame;
      ::logic::boolean                             m_bWindowFrame;
      bool                                         m_bLayered;
      int                                          m_iFrameData;
      ::atom                                       m_atomHelp;         // xxx mrs
      ::user::impact_system *                      m_pimpactsystem;
      ::int_rectangle                              m_rectangleHosting;

      int                                          m_nWindow;  // general purpose interaction_impl number - display as ":n"
//      // -1 => unknown, 0 => only interaction_impl viewing ::user::document
//      // 1 => first of many windows viewing ::user::document, 2=> second
//#ifdef WINDOWS_DESKTOP
//    HMENU                                        m_hMenuDefault;       // default menu resource for this frame
//    HACCEL                                       m_hAccelTable;       // accelerator table
//#endif
      unsigned int                                          m_dwPromptContext;    // current help prompt action_context for message box
      bool                                         m_bHelpMode;           // if true, then Shift+F1 help mode is active
      ::user::frame_window *                       m_pNextFrameWnd; // next frame_window in cast global list
      ::int_rectangle                              m_rectangleBorder;         // for OLE border space negotiation

      int                                          m_nShowDelay;           // SW_ command for delay show/hide

      bool                                         m_bFrameMoveEnable;
      //bool                                         m_bNeedRepositionBars;


      string                                       m_strMatterHelp;             // Help ID (0 for none, see HID_BASE_RESOURCE)
      unsigned int                                        m_nIDTracking;         // tracking command ID or string IDS
      unsigned int                                        m_nIDLastMessage;      // last displayed message string IDS
      ::user::impact *                             m_pviewActive;       // current active ::user::impact
      unsigned int                                        m_cModalStack;         // BeginModalState depth
      ::pointer<::user::interaction_ptra>                    m_puiptraDisable;       // windows disabled because of BeginModalState
//#ifdef WINDOWS_DESKTOP
//      HMENU                                      m_hMenuAlt;           // menu to update to (nullptr means default)
//#endif
      bool                                         m_bInRecalcLayout;     // avoid recursion in on_layout
      ::type_atom                                  m_typeatomFloatingFrame;

   unsigned int                                           m_nIdleFlags;          // set of bit flags for idle processing

      ::user::impact *                                m_pviewMain;
      atom_map < ::pointer<::user::toolbar >>     m_mapToolbar;



      frame_window();
      ~frame_window() override;


      // ::berg::application * get_app();
      // ::berg::session * get_session();
      // ::berg::system * get_system();
      // ::berg::user * user() override;


      void common_construct();


      // void assert_ok() const override;
//      virtual void dump(dump_context & dc) const override;

      //lresult send_create_message() override;


      virtual bool create_bars();
      
      
      void install_message_routing(::channel * pchannel) override;

      virtual ::atom get_topic_impact_id();
      virtual bool set_topic_impact_by_id(const ::atom & atom);


      virtual void update_active_document(::topic * ptopic);
      virtual void update_active_document(const ::atom & atom);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnQueryEndSession);

      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnNcActivate);
      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);





      virtual void enable_frame_experience(bool bEnable = true);


      virtual void OnInitialFrameUpdate(bool bMakeVisible);


      virtual void SetBorderRect(const ::int_rectangle & rectangle);
      virtual void GetBorderRectangle(::int_rectangle * prectangle);

      virtual bool _001IsFrameWnd();

      //virtual void NotifyFloatingWindows(unsigned int dwFlags);

      string get_window_default_matter() override;
      //virtual ::user::interaction::enum_type get_window_type() override;


      void on_simple_command(::message::simple_command * psimplecommand) override;
      void on_command(::message::command * pcommand) override;


      bool handle_command(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;


      bool on_set_parent(::user::interaction_base * puiParent) override;

      //virtual void defer_synch_layered();
      //virtual bool calc_layered();


      void _001OnNcDraw(::draw2d::graphics_pointer &pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      bool LoadAccelTable(const ::scoped_string & scopedstrResourceName);

      //virtual bool create_interaction(const ::scoped_string & scopedstrClassName, const ::scoped_string & scopedstrWindowName, unsigned int uStyle, const ::int_rectangle & rectangle = nullptr, ::user::interaction * puiParent = nullptr, const ::scoped_string & scopedstrMenuName = nullptr, unsigned int dwExStyle = 0, ::request * prequest = nullptr);

      
      ::string calculate_data_key() override;


      virtual bool LoadFrame(const ::scoped_string & scopedstrMatter,
                             //unsigned int dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                              unsigned int dwDefaultStyle = FWS_ADDTOTITLE,
                              ::user::interaction * puiParent = nullptr,
                              ::user::system * pcreate = nullptr);

      virtual ::user::document * get_active_document();


      void add_control_bar(::user::control_bar * pcontrolbar) override;
      void erase_control_bar(::user::control_bar * pcontrolbar) override;


      void show_control_bar(::user::control_bar * pcontrolbar) override;
      void hide_control_bar(::user::control_bar * pcontrolbar) override;


      virtual ::pointer<toolbar>get_toolbar(const ::atom & idToolBar, bool bCreate = true, const ::scoped_string & scopedstrToolbar = nullptr, unsigned int dwCtrlStyle = TBSTYLE_FLAT, unsigned int uStyle = CBRS_ALIGN_TOP, const ::type_atom & typeatom = "user::toolbar");


      virtual ::pointer<toolbar>create_toolbar(const ::atom & idToolbar, const ::scoped_string & scopedstrToolbar = nullptr, unsigned int dwCtrlStyle = TBSTYLE_FLAT, unsigned int uStyle = CBRS_ALIGN_TOP, const ::type_atom & typeatom = "user::toolbar") ;

      //   template < class TOOLBAR >
      // bool load_toolbar(atom idToolBar, const ::scoped_string & scopedstrToolBar,unsigned int dwCtrlStyle = TBSTYLE_FLAT,unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
      template < class TOOLBAR >
      void load_toolbar(const ::atom & idToolbar, const ::scoped_string & scopedstrToolbar = nullptr, unsigned int dwCtrlStyle = TBSTYLE_FLAT, unsigned int uStyle = CBRS_ALIGN_TOP);


      //   virtual bool load_toolbar(atom idToolBar, const ::scoped_string & scopedstrToolBar, unsigned int dwCtrlStyle = TBSTYLE_FLAT, unsigned int uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) override
      //   {
      //      return load_toolbar < ::user::toolbar >(idToolBar, pszToolBar, dwCtrlStyle, uStyle);
      //   }

//      virtual void load_toolbar(const ::atom & idToolbar, const ::scoped_string & scopedstrToolBar = nullptr, unsigned int dwCtrlStyle = TBSTYLE_FLAT,unsigned int uStyle = CBRS_ALIGN_TOP);
//      {
//
//         return load_toolbar < ::user::toolbar >(idToolbar, strToolBar, dwCtrlStyle, uStyle);
//
//      }


      ::user::interaction * get_active_impact() override;           // active ::user::impact or nullptr
      void set_active_impact(::user::impact * pImpactNew, bool bNotify = true) override;
      // active ::user::impact or nullptr, bNotify == false if focus should not be set

      // Active frame (for frames within frames -- MDI)
      virtual ::pointer<::user::frame_window>GetActiveFrame();

      // For customizing the default messages on the status bar
      virtual void GetMessageString(unsigned int nID, string & rMessage) const;

      bool m_bAutoMenuEnable;
      // true => menu items without handlers will be disabled

      bool IsTracking() const;

      
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;
      void ActivateFrame(::e_display edisplay = e_display_undefined) override;
      virtual void prepare_frame(::user::document * pdocument, bool bMakeVisible);
      //bool _001FancyInitialFramePlacement(bool bForceRestore = false) override;

      // to set text of standard status bar
      //void SetMessageText(const ::scoped_string & scopedstrText);

      //void SetMessageText(unsigned int nID);

      ::user::control_bar* GetControlBar(unsigned int nID);

      // frame interaction_impl based modality
      virtual void BeginModalState();
      virtual void EndModalState();
      bool InModalState() const;
      void ShowOwnedWindows(bool bShow);


      virtual ::pointer<::user::interaction>GetMessageBar();

      // border space negotiation
      enum BorderCmd { borderGet = 1, borderRequest = 2, borderSet = 3 };
      virtual bool NegotiateBorderSpace(unsigned int nBorderCmd, ::int_rectangle * pRectBorder);

      virtual bool on_create_client(::user::system * pusersystem);

      void OnContextHelp();   // for Shift+F1 help
      void OnUpdateControlBarMenu(::message::command* pCmdUI);
      bool OnBarCheck(unsigned int nID);


      
      //virtual void on_command(::message::command * pcommand) override;
      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      virtual void on_update_frame_title(bool bAddToTitle);

//#ifdef WINDOWS_DESKTOP
//      virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
//      virtual HACCEL GetDefaultAccelerator();
//#endif
      virtual void pre_translate_message(::message::message * pmessage) override;

//#ifdef WINDOWS_DESKTOP
//      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
//#endif
      void DelayUpdateFrameTitle();
      void DelayRecalcLayout(bool bNotify = true);

      // for Shift+F1 help support
      bool CanEnterHelpMode();
      virtual void ExitHelpMode() override;


      void UpdateFrameTitleForDocument(const ::scoped_string & scopedstrDocName);

      virtual bool pre_create_window(::user::system * pusersystem) override;
      //virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      void destroy() override;   // default to delete this.
      int OnCreateHelper(::user::system * pusersystem);

      //void BringToTop(::e_display edisplay) override;
      // bring interaction_impl to top for SW_ commands which affect z-order

      // implementation helpers for Shift+F1 help mode
      bool ProcessHelpMsg(MESSAGE & msg, unsigned int * pContext);
      ::oswindow SetHelpCapture(const ::int_point & point, bool * pbDescendant);

      // frame_window list management
      void AddFrameWnd();
      void RemoveFrameWnd();

      //friend class interaction_impl;  // for access to m_bModalDisable
      friend class CReBar; // for access to m_bInRecalcLayout


      void OnClose();
      //LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
      //LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
      //LRESULT OnHelpPromptAddr(WPARAM wParam, LPARAM lParam);
      //void OnIdleUpdateCmdUI(::message::message * pmessage);
      //void OnEnterIdle(unsigned int nWhy, ::pointer<::user::interaction>pWho);
      void OnSetFocus(::pointer<::user::interaction>pOldWnd);
      void OnSize(unsigned int nType, int cx, int cy);
      bool OnEraseBkgnd(::image::image *pimage);
      //void OnActivate(unsigned int nState, ::pointer<::user::interaction>pWndOther, bool bMinimized);
      //bool OnNcActivate(bool bActive);
      //void OnSysCommand(unsigned int nID, LPARAM lParam);
      bool OnQueryEndSession();
      void OnEndSession(bool bEnding);
//#ifdef WINDOWS_DESKTOP
//      virtual void OnDropFiles(HDROP hDropInfo);
//#endif
      bool OnSetCursor(::pointer<::user::interaction>pwindow, unsigned int nHitTest, const ::atom & atom);
      //LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
      //LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
      //LRESULT OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
      void OnEnable(bool bEnable);
      void OnPaletteChanged(::pointer<::user::interaction>pFocusWnd);
      bool OnQueryNewPalette();
      //virtual LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
      //virtual LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
      //virtual LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);
      //LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      ::pointer<::user::interaction>WindowDataGetWnd();



      friend class user;


      void data_on_after_change(::message::message * pmessage);


      virtual bool has_command_handler(::message::command * pcommand) override;


      ::int_rectangle hosting_rectangle(::user::enum_layout elayout = ::user::e_layout_design) override;


   };


} // namespace user




