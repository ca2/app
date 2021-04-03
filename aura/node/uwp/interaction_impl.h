#pragma once


namespace uwp
{


   CLASS_DECL_AURA LRESULT CALLBACK __send_message_hook(int, WPARAM, LPARAM);
   //CLASS_DECL_AURA void _gen::StandardSubclass(oswindow);
   CLASS_DECL_AURA LRESULT CALLBACK __cbt_filter_hook(int, WPARAM, LPARAM);
   CLASS_DECL_AURA LRESULT __call_window_procedure(::user::interaction * pWnd, oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);

   
   ref class directx_framework_view;


   class CLASS_DECL_AURA interaction_impl :
      virtual public ::user::interaction_impl
   {
   public:


      directx_framework_view ^                                          m_pframeworkview;
      ::user::message_queue_listener *                                  m_plistener;
      bool                                                              m_bNotifyLayoutCompletedPending;
      string                                                            m_strWindowText;
      point_f64                                                            m_pointLastMouseMove;
      //point_f64                                                            m_pointCursor;
      double                                                            m_dAccumulatedMouseMoveDistance;
      millis                                                              m_millisLastMouseMove;
      Agile < Windows::ApplicationModel::Core::CoreApplicationView >    m_view;
      Agile < Windows::UI::ViewManagement::ApplicationView >            m_applicationview;
      Agile < Windows::UI::Core::CoreWindow >                           m_window;
      ::thread *                                                        m_pthreadDraw;
      ::user::primitive *                                               m_pbasewnd;
      ::user::interaction *                                             m_pguieCapture;

      iptr_to_iptr                                                m_mapLong;
      ::mutex                                                           m_mutexQueue;
      manual_reset_event                                                m_evQueue;
      __pointer_array(::user::message)                                  m_messageaQueue;


      interaction_impl();
      interaction_impl(::object * pobject);
      virtual ~interaction_impl();


      virtual void construct(oswindow hwnd);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool has_pending_graphical_update();
      virtual void on_after_graphical_update();

      //virtual void on_delete(matter * poc);

      //virtual oswindow get_handle() const;

      virtual ::user::interaction * get_wnd() const;

      //bool create_message_queue(::user::interaction * pinteraction, const char * pszName);

      //virtual bool create_native_window(::user::native_window_initialize * pinitialize) override;


      virtual iptr get_window_long_ptr(i32 nIndex) const override;
      virtual iptr set_window_long_ptr(i32 nIndex, iptr lValue) override;

      static const MSG* GetCurrentMessage();

      virtual void install_message_routing(::channel * pchannel);

      bool operator==(const ::user::interaction_impl& wnd) const;
      bool operator!=(const ::user::interaction_impl& wnd) const;

      u32 GetStyle() const;
      u32 GetExStyle() const;
      bool ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0);
      bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0);

      //virtual ::user::interaction * get_owner();
      //virtual ::user::interaction * SetOwner(::user::interaction * pOwnerWnd);

      virtual oswindow _get_handle();

      virtual void route_command_message(::message::command * pcommand) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual ::e_status main_async(const ::routine & routine, e_priority epriority = priority_normal);

      void _002OnDraw(::image * pimage);

      void on_layout(::draw2d::graphics_pointer & pgraphics);


      //DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      // DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnProdevianSynch);

      DECL_GEN_SIGNAL(_001OnSetFocus);

      DECL_GEN_SIGNAL(_001OnKillFocus);

      
#if(WINVER >= 0x0500)

      //      bool GetWindowInfo(PWINDOWINFO pwi) const;
      //    bool GetTitleBarInfo(PTITLEBARINFO pti) const;

#endif   // WINVER >= 0x0500

      //      virtual ::user::interaction_impl * from_os_data(void * pdata);
      //    virtual void * get_os_data() const;

      //      static interaction_impl * from_handle(oswindow hWnd);
      //    static interaction_impl * FromHandlePermanent(oswindow hWnd);
      //static void DeleteTempMap();
      //      bool Attach(oswindow hWndNew);
      //    oswindow Detach();

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window();
      bool SubclassWindow(oswindow hWnd);
      bool SubclassDlgItem(::u32 nID, ::user::interaction_impl * pParent);
      oswindow UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      bool ExecuteDlgInit(const char * lpszResourceName);
      bool ExecuteDlgInit(LPVOID lpResource);


      virtual bool is_composite() override;


      virtual ::e_status update_graphics_resources() override;

      // for child windows, views, panes etc
      //virtual bool create_window(::user::interaction * pinteraction, const char * lpszClassName,const char * lpszWindowName,u32 dwStyle,const RECTANGLE_I32 & rectangle,::user::interaction * pParentWnd,id id, ::create * pcreate = nullptr) override;

      virtual bool _native_create_window_ex(__pointer(::user::system) pcs);


      virtual ::point_i32 get_cursor_position() const;


      //virtual bool CreateEx(u32 dwExStyle, const char * lpszClassName,
      //                      const char * lpszWindowName, u32 dwStyle,
      //                      int x, int y, int nWidth, int nHeight,
      //                      oswindow hWndParent, id id, LPVOID lpParam = nullptr);

      //virtual bool CreateEx(u32 dwExStyle, const char * lpszClassName,
      //                      const char * lpszWindowName, u32 dwStyle,
      //                      const RECTANGLE_I32& rectangle,
      //                      ::user::interaction* pParentWnd, id id,
      //                      LPVOID lpParam = nullptr);

      virtual bool DestroyWindow();

      // special pre-creation and ::user::interaction_impl rectangle_i32 adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(RECTANGLE_I32 * lpClientRect, ::u32 nAdjustType = adjustBorder);


      // get immediate child with given ID
      //      using ::user::interaction::GetDlgItem;
      void GetDlgItem(id id, oswindow* phWnd) const;

      //virtual bool IsWindow() const;

#if(WINVER >= 0x0500)

      ::user::interaction_impl * GetAncestor(::u32 gaFlags) const override;

#endif   // WINVER >= 0x0500

      LRESULT send_message(const ::id & id, WPARAM wParam = 0, lparam lParam = nullptr);
      bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = nullptr);

      bool SendNotifyMessage(const ::id & id, WPARAM wParam, LPARAM lParam);
      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      bool DragDetect(POINT_I32 pt) const;



      // Window Text Functions
      void set_window_text(const char * lpszString) override;
      //strsize get_window_text(char * lpszStringBuf, strsize nMaxCount) override;
      void get_window_text(string & rString) override;
      //strsize get_window_text_length() override;
      void SetFont(::write_text::font* pFont, bool bRedraw = true);
      ::write_text::font* GetFont();


      // Window size_i32 and position Functions
      //virtual bool layout().is_iconic();
      //virtual bool layout().is_zoomed();
      //void MoveWindow(int x, int y, int nWidth, int nHeight, bool bRepaint = true);
      //void MoveWindow(const RECTANGLE_I32 * lpRect, bool bRepaint = true);
      //int SetWindowRgn(HRGN hRgn, bool bRedraw);
      //int GetWindowRgn(HRGN hRgn);


      //virtual bool set_window_position(iptr z, int x, int y, int cx, int cy, ::u32 nFlags);
      virtual ::u32 ArrangeIconicWindows();
      virtual bool BringWindowToTop();
      //using ::user::interaction_impl::get_window_rect;
      //virtual bool get_window_rect(RECTANGLE_I64 * lpRect);
      //using ::user::interaction_impl::get_client_rect;
      //virtual bool get_client_rect(RECTANGLE_I64 * lpRect);

      //virtual bool _001ClientToScreen(RECTANGLE_I32 * lprect);
      //virtual bool _001ClientToScreen(POINT_I32 * lppoint);
      //virtual bool _001ClientToScreen(RECTANGLE_I64 * lprect);
      //virtual bool _001ClientToScreen(POINT_I64 * lppoint);
      //virtual bool _001ScreenToClient(RECTANGLE_I32 * lprect);
      //virtual bool _001ScreenToClient(POINT_I32 * lppoint);
      //virtual bool _001ScreenToClient(RECTANGLE_I64 * lprect);
      //virtual bool _001ScreenToClient(POINT_I64 * lppoint);

      //      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpuserinteractionpl);
      //    virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpuserinteractionpl);

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::user::interaction_impl * puserinteractionTo, POINT_I32 * lpPoint, ::u32 nCount);
      virtual void MapWindowPoints(::user::interaction_impl * puserinteractionTo, RECTANGLE_I32 * lpRect);

      // Update/Painting Functions
      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      virtual bool ReleaseDC(::image * pimage);
      virtual void Print(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      //virtual bool GetUpdateRect(RECTANGLE_I32 * lpRect, bool bErase = false);
      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      //virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const RECTANGLE_I32 * lpRect, bool bErase = true);
      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const RECTANGLE_I32 * lpRect);
      //virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool ShowWindow(int nCmdShow);
      virtual void _001WindowMaximize();
      virtual void _001WindowRestore();
      virtual bool is_window_visible();
      virtual void ShowOwnedPopups(bool bShow = true);

      virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, u32 flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();
      virtual bool RedrawWindow(const ::rectangle_i32& rectUpdate = nullptr,
                                ::draw2d::region* prgnUpdate = nullptr,
                                ::u32 flags = RDW_INVALIDATE | RDW_ERASE);
      //      virtual bool EnableScrollBar(int nSBFlags, ::u32 nArrowFlags = ESB_ENABLE_BOTH);

      virtual bool DrawAnimatedRects(int idAni, const RECTANGLE_I32 *lprcFrom, const RECTANGLE_I32 *lprcTo);
      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const RECTANGLE_I32 * lprc, ::u32 uFlags);

#if(WINVER >= 0x0500)

      virtual bool AnimateWindow(millis millis, u32 dwFlags);

#endif   // WINVER >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, ::u32 nFlags) const;

#endif   // _WIN32_WINNT >= 0x0501

      // Layered Window



      // Timer Functions
      virtual bool SetTimer(UINT_PTR uEvent, ::u32 nElapse, PFN_TIMER pfnTimer);
      virtual bool KillTimer(uptr uEvent);

      // Window State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = true);

      // the active ::user::interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction *  GetActiveWindow();
      virtual ::user::interaction *  SetActiveWindow();

      // the foreground ::user::interaction_impl applies only to top-level windows (frame windows)
      virtual bool SetForegroundWindow();
      static __pointer(::user::interaction_impl) GetForegroundWindow();

      virtual id SetDlgCtrlId(id id);
      virtual id GetDlgCtrlId();



      // capture and focus apply to all windows
      //virtual ::user::interaction *  GetCapture();
      //virtual ::user::interaction *  SetCapture(::user::interaction *  pinterface = nullptr);
      //virtual ::user::interaction *  ReleaseCapture();
      //virtual ::user::interaction *  GetCapture();
      virtual ::user::interaction *  GetFocus();
      virtual bool  SetFocus() override;

      static ::user::interaction *  get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow();
      virtual bool OpenIcon();

      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(int nIDButton, ::u32 nCheck);
      virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton,
                                    int nIDCheckButton);
      virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton);
      /*virtual int DlgDirList(__inout_z char * lpPathSpec, __in int nIDListBox,
      __in int nIDStaticPath, __in ::u32 nFileType);
      virtual int DlgDirListComboBox(__inout_z char * lpPathSpec, __in int nIDComboBox,
      __in int nIDStaticPath, __in ::u32 nFileType);
      virtual bool DlgDirSelect(__out_ecount_z(nSize) char * lpString, __in int nSize, __in int nIDListBox);
      virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) char * lpString, __in int nSize, __in int nIDComboBox);*/

      virtual ::u32 GetDlgItemInt(int nID, BOOL * lpTrans = nullptr, bool bSigned = true) const;
      //      virtual int GetDlgItemText(__in int nID, __out_ecount_part_z(nMaxCount, return + 1) char * lpStr, __in int nMaxCount) const;
      //    virtual int GetDlgItemText(int nID, string & rString) const;
      virtual ::user::interaction_impl * GetNextDlgGroupItem(::user::interaction_impl * pWndCtl, bool bPrevious = false) const;
      virtual ::user::interaction_impl * GetNextDlgTabItem(::user::interaction_impl * pWndCtl, bool bPrevious = false) const;
      virtual ::u32 IsDlgButtonChecked(int nIDButton) const;
      virtual LRESULT SendDlgItemMessage(int nID, const ::id & id, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual void SetDlgItemInt(int nID, ::u32 nValue, bool bSigned = true);
      virtual void SetDlgItemText(int nID, const char * lpszString);

      // Scrolling Functions
      virtual int GetScrollPos(int nBar) const;
      virtual void GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
      //virtual void ScrollWindow(int xAmount, int yAmount,
      //                          const RECTANGLE_I32 * lpRect = nullptr,
      //                          const RECTANGLE_I32 * lpClipRect = nullptr);
      virtual int SetScrollPos(int nBar, int nPos, bool bRedraw = true);
      virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
                                  bool bRedraw = true);
      virtual void ShowScrollBar(::u32 nBar, bool bShow = true);
      virtual void EnableScrollBarCtrl(int nBar, bool bEnable = true);
//      virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
      // return sibling scrollbar control (or nullptr if none)

      //virtual int ScrollWindowEx(int dx, int dy,
      //                           const RECTANGLE_I32 * lpRectScroll, const RECTANGLE_I32 * lpRectClip,
      //                           ::draw2d::region* prgnUpdate, RECTANGLE_I32 * lpRectUpdate, ::u32 flags);
      //      virtual bool SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo,
      //       bool bRedraw = true);
      //      virtual bool GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, ::u32 nMask = SIF_ALL);
      virtual int GetScrollLimit(int nBar);

      //#if defined(WINDOWS_DESKTOP) && (WINVER >= 0x0500)

      // virtual bool GetScrollBarInfo(::i32 idObject, PSCROLLBARINFO psbi) const;

      //#endif   // WINVER >= 0x0500

      // Window Access Functions
      virtual ::user::interaction *  ChildWindowFromPoint(POINT_I32 point_i32);
      virtual ::user::interaction *  ChildWindowFromPoint(POINT_I32 point, ::u32 nFlags);
      static __pointer(::user::interaction_impl) FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static __pointer(::user::interaction_impl) FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      //      virtual ::user::interaction * GetNextWindow(::u32 nFlag = GW_HWNDNEXT);
      virtual ::user::interaction *  GetTopWindow();

      virtual ::user::interaction *  GetWindow(::u32 nCmd);
      virtual ::user::interaction *  GetLastActivePopup();

      virtual bool IsChild(::user::interaction *   pWnd);
      virtual ::user::interaction *  get_parent() const override;
      using ::user::interaction_impl::set_parent;
//      ::user::interaction *  SetParent(::user::interaction *  pWndNewParent);
      static __pointer(::user::interaction_impl) WindowFromPoint(POINT_I32 point_i32);

      // Alert Functions

      bool FlashWindow(bool bInvert);

      //virtual int message_box(const char * lpszText, const char * lpszCaption = nullptr, ::u32 nType = e_message_box_ok);


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(u32 dwFlags, ::u32  uCount, millis tickTimeout);

#endif   // WINVER >= 0x0500

      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow hWndNext);
      virtual oswindow SetClipboardViewer();
      virtual bool OpenClipboard();
      static ::user::interaction_impl * GetClipboardOwner();
      static ::user::interaction_impl * GetClipboardViewer();
      static ::user::interaction_impl * GetOpenClipboardWindow();

      // Caret Functions
      static point_i32 GetCaretPos();
      static void SetCaretPos(POINT_I32 point_i32);
      virtual void HideCaret();
      virtual void ShowCaret();

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = true);

      // icon Functions
      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
      virtual HICON GetIcon(bool bBigIcon) const;

      // Context Help Functions
      virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      virtual u32 GetWindowContextHelpId() const;

      // Dialog Data support
      //virtual bool UpdateData(bool bSaveAndValidate = true);
      // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
      void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler);
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      //virtual id RunModalLoop(u32 dwFlags = 0) override;
      virtual bool ContinueModal() override;
      virtual void EndModalLoop(id nResult) override;
      //virtual void EndAllModalLoops(id nResult);

      // Window-Management message handler member functions
      virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual bool OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      void OnActivate(::u32 nState, ::user::interaction_impl * pWndOther, bool bMinimized);
      void OnActivateApp(bool bActive, u32 dwThreadID);
      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      void OnCancelMode();
      void OnChildActivate();
      void OnClose();
      void OnContextMenu(::user::interaction_impl * pWnd, point_i32 pos);
      //      bool OnCopyData(::user::interaction_impl * pWnd, COPYDATASTRUCT* pCopyDataStruct);
      DECL_GEN_SIGNAL(on_message_create);


      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction_impl * pWnd, ::u32 nCtlColor);

      DECL_GEN_SIGNAL(_001OnDestroy);
      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      void OnEnterIdle(::u32 nWhy, ::user::interaction_impl * pWho);
      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      //    bool OnHelpInfo(HELPINFO* lpHelpInfo);
      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnKillFocus(::user::interaction_impl * pNewWnd);
      //LRESULT OnMenuChar(::u32 nChar, ::u32 nFlags, ::user::menu* pMenu);
      void OnMenuSelect(::u32 nItemID, ::u32 nFlags, HMENU hSysMenu);
      void OnMove(int x, int y);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      void OnParentNotify(::u32 message, LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::user::interaction_impl * pOldWnd);
      void OnShowWindow(bool bShow, ::u32 nStatus);
      void OnSize(::u32 nType, int cx, int cy);
      void OnTCard(::u32 idAction, u32 dwActionData);
      //      void OnWindowPosChanging(WINDOWPOS* lpuserinteractionpos);
      //    void OnWindowPosChanged(WINDOWPOS* lpuserinteractionpos);

      void OnChangeUIState(::u32 nAction, ::u32 nUIElement);
      void OnUpdateUIState(::u32 nAction, ::u32 nUIElement);
      ::u32 OnQueryUIState();

      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      //      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(LPCREATESTRUCT lpCreateStruct);

      LRESULT OnNcHitTest(::point_i32 point);
      void OnNcLButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      void OnNcLButtonDown(::u32 nHitTest, const ::point_i32 & point);
      void OnNcLButtonUp(::u32 nHitTest, const ::point_i32 & point);
      void OnNcMButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      void OnNcMButtonDown(::u32 nHitTest, const ::point_i32 & point);
      void OnNcMButtonUp(::u32 nHitTest, const ::point_i32 & point);
      void OnNcMouseMove(::u32 nHitTest, const ::point_i32 & point);
      void OnNcPaint();
      void OnNcRButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
      void OnNcRButtonDown(::u32 nHitTest, const ::point_i32 & point);
      void OnNcRButtonUp(::u32 nHitTest, const ::point_i32 & point);

      // ::aura::get_system() message handler member functions
      //      void OnDropFiles(HDROP hDropInfo);
      void OnPaletteIsChanging(::user::interaction_impl * pRealizeWnd);
      void OnSysChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnSysCommand(::u32 nID, LPARAM lParam);
      void OnSysDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnSysKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnSysKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnCompacting(::u32 nCpuTime);
      void OnDevModeChange(char * lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::user::interaction_impl * pFocusWnd);
      void OnSpoolerStatus(::u32 nStatus, ::u32 nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(::u32 uFlags, const char * lpszSection);
      void OnWinIniChange(const char * lpszSection);

      // Input message handler member functions
      void OnChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnHScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      //    void OnVScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      void OnKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
      void OnLButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      void OnLButtonDown(::u32 nFlags, const ::point_i32 & point);
      void OnLButtonUp(::u32 nFlags, const ::point_i32 & point);
      void OnMButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      void OnMButtonDown(::u32 nFlags, const ::point_i32 & point);
      void OnMButtonUp(::u32 nFlags, const ::point_i32 & point);
      int OnMouseActivate(::user::interaction_impl * pDesktopWnd, ::u32 nHitTest, const ::id & id);
      void OnMouseMove(::u32 nFlags, const ::point_i32 & point);
      bool OnMouseWheel(::u32 nFlags, short zDelta, const ::point_i32 & point);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      void OnRButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      void OnRButtonDown(::u32 nFlags, const ::point_i32 & point);
      void OnRButtonUp(::u32 nFlags, const ::point_i32 & point);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      void OnTimer(uptr uEvent);

      // Initialization message handler member functions
      //void OnInitMenu(::user::menu* pMenu);
      //void OnInitMenuPopup(::user::menu* pPopupMenu, ::u32 nIndex, bool bSysMenu);

      // Clipboard message handler member functions
      void OnAskCbFormatName(__in ::u32 nMaxCount, __out_ecount_z(nMaxCount) char * lpszString);
      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::user::interaction_impl * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);
      void OnPaintClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(::u32 nFormat);
      void OnSizeClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hRect);
      void OnVScrollClipboard(::user::interaction_impl * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);

      // control message handler member functions
      //      int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //    void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //  void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
      ::u32 OnGetDlgCode();
      //void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

      // MDI message handler member functions
      void OnMDIActivate(bool bActivate,
                         ::user::interaction_impl * pActivateWnd, ::user::interaction_impl * pDeactivateWnd);

      // menu loop notification messages
      void OnEnterMenuLoop(bool bIstrack_popup_menu);
      void OnExitMenuLoop(bool bIstrack_popup_menu);

      // Win4 messages
      //      void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
      //    void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
      void OnSizing(::u32 nSide, RECTANGLE_I32 * lpRect);
      void OnMoving(::u32 nSide, RECTANGLE_I32 * lpRect);
      void OnCaptureChanged(::user::interaction_impl * pWnd);
      bool OnDeviceChange(::u32 nEventType, dword_ptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      //      virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void DoDataExchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState();
      virtual void EndModalState();

      // for translating Windows messages in main message pump
      virtual void pre_translate_message(::message::message * pmessage);


      // for processing Windows messages
      virtual void message_handler(::user::message * pusermessage);
      //virtual bool OnWndMsg(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
      LRESULT Default();
      virtual LRESULT DefWindowProc(::u32 message, WPARAM wParam, lparam lParam);

      // for custom cleanup after e_message_ncdestroy
      virtual void PostNcDestroy();

      // for notifications from parent
      virtual bool OnChildNotify(::u32 message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      // return true if parent should not process this message
      bool ReflectChildNotify(::u32 message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static bool ReflectLastMsg(oswindow hWndChild, LRESULT* pResult = nullptr);

      virtual bool CheckAutoCenter();
      static bool GrayCtlColor(HDC hDC, oswindow hWnd, ::u32 nCtlColor,
                               HBRUSH hbrGray, color32_t clrText);


      // helper routines for implementation
      bool HandleFloatingSysCommand(::u32 nID, LPARAM lParam);
      //bool IsTopParentActive();
      void ActivateTopParent();
      virtual void WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage);
      virtual bool is_frame_window(); // is_kind_of(::aura::get_system()->template type_info < frame_window > ()))
      virtual void on_final_release();
      //static void _FilterToolTipMessage(MSG* pMsg, ::user::interaction_impl * pWnd);
      bool _EnableToolTips(bool bEnable, ::u32 nFlag);
      static oswindow GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp();

      //::u32 m_nFlags;      // see WF_ flags above

      //      WNDPROC m_pfnSuper; // for subclassing of controls
      static const ::u32 m_nMsgDragList;
      int m_nModalResult; // for return values from ::user::interaction_impl::RunModalLoop

      ::write_text::font * m_pfont;

      friend class frame_window;

      // for creating dialogs and dialog-like windows
      bool CreateDlg(const char * lpszTemplateName, ::user::interaction_impl * pParentWnd);
      //bool CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::user::interaction_impl * pParentWnd,
      // HINSTANCE hInst);


      // implementation of message dispatch/hooking
      CLASS_DECL_AURA friend LRESULT CALLBACK __send_message_hook(int, WPARAM, LPARAM);
      //CLASS_DECL_AURA friend void _gen::StandardSubclass(oswindow);
      CLASS_DECL_AURA friend LRESULT CALLBACK __cbt_filter_hook(int, WPARAM, LPARAM);
      CLASS_DECL_AURA friend LRESULT __call_window_procedure(::user::interaction * pWnd, oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);

      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM, LPARAM);
      LRESULT OnDragList(WPARAM, LPARAM);

      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lParam);


      static void get_app_wnda(user::oswindow_array & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      virtual ::i32 GetWindowLong(int nIndex);
      virtual ::i32 SetWindowLong(int nIndex, ::i32 lValue);

      virtual void _001BaseWndInterfaceMap();


      // void _001UpdateWindow();
      virtual bool has_focus() override;
      virtual bool is_active() override;


      virtual void _001UpdateScreen() override;

      void _001OnTriggerMouseInside();


      Agile < Windows::UI::Core::CoreWindow > get_os_window();

      void set_view_port_org(::image * pimage);

      void offset_view_port_org(RECTANGLE_I32 * lprectScreen);

      virtual void queue_message_handler(::user::message * pusermessage) override;

      virtual bool _is_window() const override;

      virtual ::e_status show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd) override;

      virtual ::e_status hide_software_keyboard(::user::primitive * pprimitive) override;

      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;

      virtual bool is_text_composition_active() override;

      virtual void set_input_content_rect(const rectangle_i32& rectangle);
      virtual void set_input_selection_rect(const rectangle_i32& rectangle);

      virtual rectangle_i32 get_input_content_rect();
      virtual rectangle_i32 get_input_selection_rect();


   };


} // namespace uwp



inline ::uwp::interaction_impl * __uwp_user_interaction_impl(::layered * playered)
{

   return (::uwp::interaction_impl *)playered->layer(LAYERED_OS_USER_INTERACTION_IMPL);

}


