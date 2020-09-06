#pragma once


namespace user
{


   class CLASS_DECL_BASE frame_window :
      virtual public ::user::frame,
      virtual public ::user::box
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

      __pointer_array(::user::control_bar)      m_barptra; // array of all control bars that have this interaction_impl as their dock site

      bool                                      m_bAutoWindowFrame;
      bool                                      m_bWindowFrame;
      bool                                      m_bLayered;
      i32                                       m_iFrameData;
      ::id                                      m_idHelp;         // xxx mrs
      ::user::impact_system *                   m_pdocumenttemplate;

      i32                                       m_nWindow;  // general purpose interaction_impl number - display as ":n"
      // -1 => unknown, 0 => only interaction_impl viewing ::user::document
      // 1 => first of many windows viewing ::user::document, 2=> second

      HMENU                      m_hMenuDefault;       // default menu resource for this frame
      HACCEL                     m_hAccelTable;       // accelerator table
      u32                   m_dwPromptContext;    // current help prompt action_context for message box
      bool                       m_bHelpMode;           // if TRUE, then Shift+F1 help mode is active
      ::user::frame_window *     m_pNextFrameWnd; // next frame_window in cast global list
      ::rect                     m_rectBorder;         // for OLE border space negotiation

      i32                    m_nShowDelay;           // SW_ command for delay show/hide

      bool                       m_bFrameMoveEnable;


      string                     m_strMatterHelp;             // Help ID (0 for none, see HID_BASE_RESOURCE)
      UINT                       m_nIDTracking;         // tracking command ID or string IDS
      UINT                       m_nIDLastMessage;      // last displayed message string IDS
      ::user::impact *           m_pviewActive;       // current active ::user::impact
      UINT                       m_cModalStack;         // BeginModalState depth
      ::user::interaction_ptra   m_uiptraDisable;       // windows disabled because of BeginModalState
      HMENU                      m_hMenuAlt;           // menu to update to (nullptr means default)
      bool                       m_bInRecalcLayout;     // avoid recursion in on_layout
      ::type                     m_pFloatingFrameClass;

      UINT                       m_nIdleFlags;          // set of bit flags for idle processing

      ::user::impact *           m_pviewMain;



      frame_window();
      virtual ~frame_window();


      void common_construct();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dc) const override;


      virtual void install_message_routing(::channel * pchannel) override;

      virtual ::id get_topic_view_id();
      virtual bool set_topic_view_by_id(const ::id & id);


      virtual void update_active_document(::update * pupdate);
      virtual void update_active_document(const ::id & id);


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnQueryEndSession);

      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnSysCommand);


      virtual void OnInitialFrameUpdate(bool bMakeVisible);


      virtual void SetBorderRect(const ::rect & rect);
      virtual void GetBorderRect(RECT * prect);

      virtual bool _001IsFrameWnd();

      virtual void NotifyFloatingWindows(u32 dwFlags);

      virtual string get_window_default_matter() override;
      virtual ::user::interaction::e_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command * psimplecommand) override;
      virtual void on_command(::user::command * pcommand) override;



      virtual bool on_set_parent(::user::interaction * puiParent) override;

      virtual void defer_synch_layered();
      virtual bool calc_layered();



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      bool LoadAccelTable(const char * pszResourceName);

      virtual bool create_window(const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect = nullptr, ::user::interaction * puiParent = nullptr, const char * pszMenuName = nullptr, u32 dwExStyle = 0, ::create * pcreate = nullptr);


      virtual bool LoadFrame(const char * pszMatter,
                             u32 dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                             ::user::interaction * puiParent = nullptr,
                             ::create * pcreate = nullptr);

      virtual ::user::document * GetActiveDocument();

      virtual ::user::impact * GetActiveView() const override;           // active ::user::impact or nullptr
      virtual void SetActiveView(::user::impact * pViewNew, bool bNotify = TRUE);
      // active ::user::impact or nullptr, bNotify == FALSE if focus should not be set

      // Active frame (for frames within frames -- MDI)
      virtual __pointer(::user::frame_window) GetActiveFrame();

      // For customizing the default messages on the status bar
      virtual void GetMessageString(UINT nID, string & rMessage) const;

      bool m_bAutoMenuEnable;
      // TRUE => menu items without handlers will be disabled

      bool IsTracking() const;

      // Operations
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void ActivateFrame(::edisplay edisplay = display_undefined) override;
      virtual void InitialUpdateFrame(::user::document * pDoc, bool bMakeVisible);
      virtual void InitialFramePosition(bool bForceRestore = false) override;

      // to set text of standard status bar
      void SetMessageText(const char * pszText);

      void SetMessageText(UINT nID);

      ::user::control_bar* GetControlBar(UINT nID);

      // frame interaction_impl based modality
      virtual void BeginModalState();
      virtual void EndModalState();
      bool InModalState() const;
      void ShowOwnedWindows(bool bShow);


      virtual __pointer(::user::interaction) GetMessageBar();

      // border space negotiation
      enum BorderCmd { borderGet = 1, borderRequest = 2, borderSet = 3 };
      virtual bool NegotiateBorderSpace(UINT nBorderCmd, RECT * pRectBorder);

      virtual bool on_create_client(::user::create_struct * pcs, ::create * pcreate);

      void OnContextHelp();   // for Shift+F1 help
      void OnUpdateControlBarMenu(::user::command* pCmdUI);
      bool OnBarCheck(UINT nID);

      virtual bool LoadToolBar(id idToolBar, const char * pszToolBar, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) override;

      
      virtual void on_command_message(::user::command * pcommand) override;
      virtual void route_command_message(::user::command* pcommand) override;

      virtual void on_update_frame_title(bool bAddToTitle);
      virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
      virtual HACCEL GetDefaultAccelerator();
      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
      void DelayUpdateFrameTitle();
      void DelayRecalcLayout(bool bNotify = TRUE);

      // for Shift+F1 help support
      bool CanEnterHelpMode();
      virtual void ExitHelpMode() override;


      void UpdateFrameTitleForDocument(const char * pszDocName);

      virtual bool pre_create_window(::user::create_struct& cs) override;
      //virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual void PostNcDestroy() override;   // default to delete this.
      i32 OnCreateHelper(::user::create_struct * pcs, ::create * pcreate);

      //void BringToTop(::edisplay edisplay) override;
      // bring interaction_impl to top for SW_ commands which affect z-order

      // implementation helpers for Shift+F1 help mode
      bool ProcessHelpMsg(MESSAGE & msg, u32 * pContext);
      oswindow SetHelpCapture(const ::point & point, bool * pbDescendant);

      // frame_window list management
      void AddFrameWnd();
      void RemoveFrameWnd();

      friend class interaction_impl;  // for access to m_bModalDisable
      friend class CReBar; // for access to m_bInRecalcLayout


      void OnClose();
      LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
      LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
      LRESULT OnHelpPromptAddr(WPARAM wParam, LPARAM lParam);
      //void OnIdleUpdateCmdUI(::message::message * pmessage);
      void OnEnterIdle(UINT nWhy, __pointer(::user::interaction) pWho);
      void OnSetFocus(__pointer(::user::interaction) pOldWnd);
      void OnSize(UINT nType, i32 cx, i32 cy);
      bool OnEraseBkgnd(::image * pimage);
      //void OnActivate(UINT nState, __pointer(::user::interaction) pWndOther, bool bMinimized);
      //bool OnNcActivate(bool bActive);
      void OnSysCommand(UINT nID, LPARAM lParam);
      bool OnQueryEndSession();
      void OnEndSession(bool bEnding);
#ifdef WINDOWS_DESKTOP
      virtual void OnDropFiles(HDROP hDropInfo);
#endif
      bool OnSetCursor(__pointer(::user::interaction) pwindow, UINT nHitTest, UINT message);
      //LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
      //LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
      LRESULT OnActivateTopLevel(WPARAM wParam, LPARAM lParam);
      void OnEnable(bool bEnable);
      void OnPaletteChanged(__pointer(::user::interaction) pFocusWnd);
      bool OnQueryNewPalette();
      virtual LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
      virtual LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
      virtual LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);







      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void on_control_event(::user::control_event * pevent) override;


      __pointer(::user::interaction) WindowDataGetWnd();



      friend class user;
      virtual void AddControlBar(::user::control_bar *pBar);
      virtual void RemoveControlBar(::user::control_bar *pBar);


      void data_on_after_change(::message::message * pmessage);


      virtual bool has_command_handler(::user::command * pcommand) override;


   };


} // namespace user




