#pragma once


namespace user
{


   class CLASS_DECL_BASE frame_window :
      virtual public ::user::main_window
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

      __pointer_array(::user::control_bar)      m_controlbara; // array of all control bars that have this interaction_impl as their dock site

      //bool                                         m_bAutoWindowFrame;
      tristate                                      m_bWindowFrame;
      bool                                         m_bLayered;
      i32                                          m_iFrameData;
      ::atom                                         m_atomHelp;         // xxx mrs
      ::user::impact_system *                      m_pdocumenttemplate;

      i32                                          m_nWindow;  // general purpose interaction_impl number - display as ":n"
//      // -1 => unknown, 0 => only interaction_impl viewing ::user::document
//      // 1 => first of many windows viewing ::user::document, 2=> second
//#ifdef WINDOWS_DESKTOP
//    HMENU                                        m_hMenuDefault;       // default menu resource for this frame
//    HACCEL                                       m_hAccelTable;       // accelerator table
//#endif
      u32                                          m_dwPromptContext;    // current help prompt action_context for message box
      bool                                         m_bHelpMode;           // if true, then Shift+F1 help mode is active
      ::user::frame_window *                       m_pNextFrameWnd; // next frame_window in cast global list
      ::rectangle_i32                              m_rectangleBorder;         // for OLE border space negotiation

      i32                                          m_nShowDelay;           // SW_ command for delay show/hide

      bool                                         m_bFrameMoveEnable;


      string                                       m_strMatterHelp;             // Help ID (0 for none, see HID_BASE_RESOURCE)
      ::u32                                        m_nIDTracking;         // tracking command ID or string IDS
      ::u32                                        m_nIDLastMessage;      // last displayed message string IDS
      ::user::impact *                             m_pviewActive;       // current active ::user::impact
      ::u32                                        m_cModalStack;         // BeginModalState depth
      ::user::interaction_ptra                     m_uiptraDisable;       // windows disabled because of BeginModalState
//#ifdef WINDOWS_DESKTOP
//      HMENU                                      m_hMenuAlt;           // menu to update to (nullptr means default)
//#endif
      bool                                         m_bInRecalcLayout;     // avoid recursion in on_layout
      ::type                                       m_pFloatingFrameClass;

   ::u32                                           m_nIdleFlags;          // set of bit flags for idle processing

      ::user::impact *                                m_pviewMain;
      id_map < __pointer(::user::toolbar) >      m_mapToolbar;



      frame_window();
      ~frame_window() override;


      inline ::base::application* get_app() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      void common_construct();


      void assert_ok() const override;
      virtual void dump(dump_context & dc) const override;

      
      virtual bool create_bars();


      void install_message_routing(::channel * pchannel) override;

      virtual ::atom get_topic_view_id();
      virtual bool set_topic_view_by_id(const ::atom & atom);


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


      virtual void SetBorderRect(const ::rectangle_i32 & rectangle);
      virtual void GetBorderRect(RECTANGLE_I32 * prectangle);

      virtual bool _001IsFrameWnd();

      //virtual void NotifyFloatingWindows(u32 dwFlags);

      virtual string get_window_default_matter() override;
      virtual ::user::interaction::enum_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command * psimplecommand) override;
      virtual void on_command(::message::command * pcommand) override;



      virtual bool on_set_parent(::user::primitive * puiParent) override;

      //virtual void defer_synch_layered();
      //virtual bool calc_layered();



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      bool LoadAccelTable(const ::string & pszResourceName);

      //virtual bool create_interaction(const ::string & pszClassName, const ::string & pszWindowName, u32 uStyle, const ::rectangle_i32 & rectangle = nullptr, ::user::interaction * puiParent = nullptr, const ::string & pszMenuName = nullptr, u32 dwExStyle = 0, ::create * pcreate = nullptr);


      virtual bool LoadFrame(const ::string & pszMatter,
                             //u32 dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                              u32 dwDefaultStyle = FWS_ADDTOTITLE,
                              ::user::interaction * puiParent = nullptr,
                              ::user::system * pcreate = nullptr);

      virtual ::user::document * get_active_document();


      void add_control_bar(::user::control_bar * pcontrolbar) override;
      void erase_control_bar(::user::control_bar * pcontrolbar) override;


      void show_control_bar(::user::control_bar * pcontrolbar) override;
      void hide_control_bar(::user::control_bar * pcontrolbar) override;


      virtual __pointer(toolbar) get_toolbar(const ::atom & idToolBar, bool bCreate = true, const ::string & strToolbar = nullptr, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = CBRS_ALIGN_TOP, const ::type & type = "user::toolbar");


      virtual __pointer(toolbar) create_toolbar(const ::atom & idToolbar, const ::string & strToolbar = nullptr, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = CBRS_ALIGN_TOP, const ::type & type = "user::toolbar") ;

      //   template < class TOOLBAR >
      // bool load_toolbar(atom idToolBar, const ::string & pszToolBar,u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
      template < class TOOLBAR >
      void load_toolbar(const ::atom & idToolbar, const ::string & strToolbar = nullptr, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = CBRS_ALIGN_TOP);


      //   virtual bool load_toolbar(atom idToolBar, const ::string & pszToolBar, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) override
      //   {
      //      return load_toolbar < ::user::toolbar >(idToolBar, pszToolBar, dwCtrlStyle, uStyle);
      //   }

//      virtual void load_toolbar(const ::atom & idToolbar, const ::string & strToolBar = nullptr, u32 dwCtrlStyle = TBSTYLE_FLAT,u32 uStyle = CBRS_ALIGN_TOP);
//      {
//
//         return load_toolbar < ::user::toolbar >(idToolbar, strToolBar, dwCtrlStyle, uStyle);
//
//      }


      ::user::interaction * get_active_view() const override;           // active ::user::impact or nullptr
      void set_active_view(::user::impact * pImpactNew, bool bNotify = true) override;
      // active ::user::impact or nullptr, bNotify == false if focus should not be set

      // Active frame (for frames within frames -- MDI)
      virtual __pointer(::user::frame_window) GetActiveFrame();

      // For customizing the default messages on the status bar
      virtual void GetMessageString(::u32 nID, string & rMessage) const;

      bool m_bAutoMenuEnable;
      // true => menu items without handlers will be disabled

      bool IsTracking() const;

      // Operations
      void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      void ActivateFrame(::e_display edisplay = e_display_undefined) override;
      virtual void prepare_frame(::user::document * pdocument, bool bMakeVisible);
      //bool _001FancyInitialFramePlacement(bool bForceRestore = false) override;

      // to set text of standard status bar
      //void SetMessageText(const ::string & pszText);

      //void SetMessageText(::u32 nID);

      ::user::control_bar* GetControlBar(::u32 nID);

      // frame interaction_impl based modality
      virtual void BeginModalState();
      virtual void EndModalState();
      bool InModalState() const;
      void ShowOwnedWindows(bool bShow);


      virtual __pointer(::user::interaction) GetMessageBar();

      // border space negotiation
      enum BorderCmd { borderGet = 1, borderRequest = 2, borderSet = 3 };
      virtual bool NegotiateBorderSpace(::u32 nBorderCmd, RECTANGLE_I32 * pRectBorder);

      virtual bool on_create_client(::user::system * pusersystem);

      void OnContextHelp();   // for Shift+F1 help
      void OnUpdateControlBarMenu(::message::command* pCmdUI);
      bool OnBarCheck(::u32 nID);


      
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


      void UpdateFrameTitleForDocument(const ::string & pszDocName);

      virtual bool pre_create_window(::user::system * pusersystem) override;
      //virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual void post_non_client_destroy() override;   // default to delete this.
      i32 OnCreateHelper(::user::system * pusersystem);

      //void BringToTop(::e_display edisplay) override;
      // bring interaction_impl to top for SW_ commands which affect z-order

      // implementation helpers for Shift+F1 help mode
      bool ProcessHelpMsg(MESSAGE & msg, u32 * pContext);
      ::oswindow SetHelpCapture(const ::point_i32 & point, bool * pbDescendant);

      // frame_window list management
      void AddFrameWnd();
      void RemoveFrameWnd();

      friend class interaction_impl;  // for access to m_bModalDisable
      friend class CReBar; // for access to m_bInRecalcLayout


      void OnClose();
      //LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
      //LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
      //LRESULT OnHelpPromptAddr(WPARAM wParam, LPARAM lParam);
      //void OnIdleUpdateCmdUI(::message::message * pmessage);
      //void OnEnterIdle(::u32 nWhy, __pointer(::user::interaction) pWho);
      void OnSetFocus(__pointer(::user::interaction) pOldWnd);
      void OnSize(::u32 nType, i32 cx, i32 cy);
      bool OnEraseBkgnd(::image * pimage);
      //void OnActivate(::u32 nState, __pointer(::user::interaction) pWndOther, bool bMinimized);
      //bool OnNcActivate(bool bActive);
      //void OnSysCommand(::u32 nID, LPARAM lParam);
      bool OnQueryEndSession();
      void OnEndSession(bool bEnding);
//#ifdef WINDOWS_DESKTOP
//      virtual void OnDropFiles(HDROP hDropInfo);
//#endif
      bool OnSetCursor(__pointer(::user::interaction) pwindow, ::u32 nHitTest, const ::atom & atom);
      //LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
      //LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
      //LRESULT OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
      void OnEnable(bool bEnable);
      void OnPaletteChanged(__pointer(::user::interaction) pFocusWnd);
      bool OnQueryNewPalette();
      //virtual LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
      //virtual LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
      //virtual LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);
      //LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);


      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      __pointer(::user::interaction) WindowDataGetWnd();



      friend class user;


      void data_on_after_change(::message::message * pmessage);


      virtual bool has_command_handler(::message::command * pcommand) override;


   };


} // namespace user




