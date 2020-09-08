#pragma once


namespace android
{



   class CLASS_DECL_AURA interaction_impl:
      virtual public ::user::interaction_impl
   {
   public:


      string                                    m_strWindowText;
      ::user::primitive *                       m_pbasewnd;
      bool                                      m_bUpdateGraphics;
      size                                      m_size;
      point                                     m_point;
      static const UINT                         m_nMsgDragList;
      edisplay                                  m_edisplayLayout;
      ::thread *                                m_pthreadDraw;
      int                                       m_iSoftwareKeyboardScroll;


      interaction_impl();
      virtual ~interaction_impl();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      //bool create_message_queue(::user::interaction * pinteraction, const char * pszName) override;

      //virtual bool create_native_window(::user::native_window_initialize * pinitialize) override;


      virtual void install_message_routing(::channel * pchannel) override;

      bool operator==(const ::user::interaction_impl& wnd) const;
      bool operator!=(const ::user::interaction_impl& wnd) const;

      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;

      virtual void route_command_message(::user::command * pcommand) override;

      void _002OnDraw(::image * pimage);

      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnProdevianSynch);

      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      void OnWindowPosChanged(WINDOWPOS* lpwndpos);

      virtual void win_update_graphics();

#if(WINVER >= 0x0500)

      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;

#endif   // WINVER >= 0x0500

      virtual ::user::interaction_impl * from_os_data(void * pdata) override;
      virtual void * get_os_data() const override;

      static ::user::interaction_impl * from_handle(oswindow oswindow);
      static ::user::interaction * ui_from_handle(oswindow oswindow);

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
      //bool subclass_window(oswindow oswindow);
      //bool SubclassDlgItem(UINT nID,::user::interaction * pParent);
      //oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const char * lpszResourceName);
      //bool ExecuteDlgInit(LPVOID lpResource);

      // for child windows, views, panes etc
      virtual bool create_window(::user::interaction * pinteraction, const char * lpszClassName, const char * lpszWindowName, u32 dwStyle, const ::rect & rect, ::user::interaction * pParentWnd, id id, ::create * pcreate = nullptr) override;

      // for top level windows and/or special features
      virtual bool create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction * puiParent = nullptr, ::id id = ::id()) override;

      // for top level windows and/or special features
      virtual bool _native_create_window_ex(::user::create_struct& cs) override;

      virtual bool DestroyWindow() override;

      // special pre-creation and interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct& cs) override;

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType = adjustBorder) override;

      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;

      virtual void edit_on_kill_focus(::user::interaction* pinteraction) override;

      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd) override;

      using ::user::interaction_impl::get_child_by_id;
      void get_child_by_id(id id,oswindow* poswindow_) const;

      //virtual bool IsWindow() const;

      // oswindow State Functions
      //virtual bool IsWindowEnabled();
      //virtual bool EnableWindow(bool bEnable = TRUE);

      // the active ::user::interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow() override;
      virtual ::user::interaction * SetActiveWindow() override;


      LRESULT send_message(UINT message,WPARAM wParam = 0,lparam lParam = 0) override;
      bool post_message(UINT message,WPARAM wParam = 0,lparam lParam = 0) override;

      bool SendNotifyMessage(UINT message,WPARAM wParam,lparam lParam) override;
      //bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      //bool DragDetect(POINT pt) const;

      //virtual void RedrawWindow(UINT nFlags = 0) override;

      // Window Text Functions
      virtual void set_window_text(const char * lpszString) override;
      virtual strsize get_window_text(char * lpszStringBuf, strsize nMaxCount) override;
      virtual void get_window_text(string & rString) override;
      virtual strsize get_window_text_length() override;


      // Window size and position Functions
      //virtual bool layout().is_iconic();
      //virtual bool layout().is_zoomed();
      //i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //i32 GetWindowRgn(HRGN hRgn);

      //using ::user::interaction_impl::set_window_pos;
      //virtual bool set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,UINT nFlags = SWP_SHOWWINDOW);
      //virtual UINT ArrangeIconicWindows();
      //virtual void BringToTop(int nCmdShow);
      //virtual bool BringWindowToTop();
      //using ::user::interaction_impl::get_window_rect;
      //virtual bool get_window_rect(RECT64 * lpRect);
      //using ::user::interaction_impl::get_client_rect;
      //virtual bool get_client_rect(RECT64 * lpRect);

      //virtual bool _001ClientToScreen(LPRECT lprect);
      //virtual bool _001ClientToScreen(LPPOINT lppoint);
      //virtual bool _001ClientToScreen(RECT64 * lprect);
      //virtual bool _001ClientToScreen(POINT64 * lppoint);
      //virtual bool _001ScreenToClient(LPRECT lprect);
      //virtual bool _001ScreenToClient(LPPOINT lppoint);
      //virtual bool _001ScreenToClient(RECT64 * lprect);
      //virtual bool _001ScreenToClient(POINT64 * lppoint);

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);

      //virtual void MapWindowPoints(::user::interaction * pwndTo,LPPOINT lpPoint,UINT nCount);
      //virtual void MapWindowPoints(::user::interaction * pwndTo,LPRECT lpRect);

      //virtual void Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;
      //virtual void PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;

      //virtual void UpdateWindow();
      //virtual void SetRedraw(bool bRedraw = TRUE);
      //virtual bool GetUpdateRect(LPRECT lpRect,bool bErase = FALSE);
      //virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE);
      //virtual void Invalidate(bool bErase = TRUE);
      //virtual void InvalidateRect(LPCRECT lpRect,bool bErase = TRUE);
      //virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE);
      //virtual void ValidateRect(LPCRECT lpRect);
      //virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool ShowWindow(i32 nCmdShow) override;
//      virtual void _001WindowMinimize();
      //virtual void _001WindowMaximize();
      //    virtual void _001WindowFullScreen();
      //virtual void _001WindowRestore();
      virtual bool _is_window() const override;
      virtual bool is_window_visible();
      virtual void ShowOwnedPopups(bool bShow = TRUE) override;

      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      //virtual bool ReleaseDC(::image * pimage);
      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip,u32 flags);
      virtual bool LockWindowUpdate() override;
      virtual void UnlockWindowUpdate() override;
      //virtual bool RedrawWindow(LPCRECT lpRectUpdate = nullptr,
        //                        ::draw2d::region* prgnUpdate = nullptr,
          //                      UINT flags = RDW_INVALIDATE | RDW_ERASE);
      //virtual bool EnableScrollBar(i32 nSBFlags,UINT nArrowFlags = 0);

      //virtual bool DrawAnimatedRects(i32 idAni,CONST RECT *lprcFrom,CONST RECT *lprcTo);
      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,LPCRECT lprc,UINT uFlags);




      // timer Functions
      //virtual bool SetTimer(uptr nIDEvent,UINT nElapse, PFN_TIMER pfnTimer);
      //virtual bool KillTimer(uptr nIDEvent);


      // the foreground interaction_impl applies only to top-level windows (frame windows)
      virtual bool SetForegroundWindow() override;
      virtual ::user::interaction * GetForegroundWindow();



      // capture and focus apply to all windows
      //static ::user::interaction * s_GetCapture();
      //virtual ::user::interaction * SetCapture(::user::interaction * pinterface = nullptr);
      //virtual ::user::interaction * ReleaseCapture();
      //virtual ::user::interaction * GetCapture();
      virtual bool SetFocus() override;

      virtual bool has_focus() override;
      virtual bool is_active() override;

      virtual ::user::interaction * GetFocus() override;

      virtual ::user::interaction * get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow() override;
      virtual bool OpenIcon() override;

      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(i32 nIDButton, UINT nCheck) override;
      virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton) override;
      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton) override;
      virtual i32 DlgDirList(LPTSTR lpPathSpec, i32 nIDListBox, i32 nIDStaticPath, UINT nFileType) override;
      virtual i32 DlgDirListComboBox(LPTSTR lpPathSpec, i32 nIDComboBox, i32 nIDStaticPath, UINT nFileType) override;
      virtual bool DlgDirSelect(LPTSTR lpString, i32 nSize, i32 nIDListBox) override;
      virtual bool DlgDirSelectComboBox(LPTSTR lpString, i32 nSize, i32 nIDComboBox) override;

      //virtual UINT GetChildByIdInt(i32 nID, bool * lpTrans = nullptr, bool bSigned = TRUE) const;
      //virtual i32 GetChildByIdText(i32 nID, LPTSTR lpStr, i32 nMaxCount) const;
      //virtual i32 GetChildByIdText(i32 nID, string & rString) const;
      //virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const;
      //virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(i32 nIDButton) const override;
      virtual LRESULT SendDlgItemMessage(i32 nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0) override;
      virtual void SetDlgItemInt(i32 nID, UINT nValue, bool bSigned = TRUE) override;
      virtual void SetDlgItemText(i32 nID, const char * lpszString) override;


      // Scrolling Functions
      virtual i32 GetScrollPos(i32 nBar) const override;
      virtual void GetScrollRange(i32 nBar,LPINT lpMinPos,LPINT lpMaxPos) const override;
      virtual void ScrollWindow(i32 xAmount,i32 yAmount, LPCRECT lpRect = nullptr, LPCRECT lpClipRect = nullptr) override;
      virtual i32 SetScrollPos(i32 nBar,i32 nPos,bool bRedraw = TRUE) override;
      virtual void SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos, bool bRedraw = TRUE) override;
      virtual void ShowScrollBar(UINT nBar,bool bShow = TRUE) override;
      virtual void EnableScrollBarCtrl(i32 nBar,bool bEnable = TRUE) override;

      virtual i32 ScrollWindowEx(i32 dx,i32 dy,
                                 LPCRECT lpRectScroll,LPCRECT lpRectClip,
                                 ::draw2d::region* prgnUpdate,LPRECT lpRectUpdate,UINT flags) override;
      //virtual bool SetScrollInfo(i32 nBar,LPSCROLLINFO lpScrollInfo,
      //   bool bRedraw = TRUE);
      //virtual bool GetScrollInfo(i32 nBar,LPSCROLLINFO lpScrollInfo,UINT nMask = SIF_ALL);
      virtual i32 GetScrollLimit(i32 nBar) override;

#if(WINVER >= 0x0500)

      virtual bool GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const;

#endif   // WINVER >= 0x0500

      // Window Access Functions
      virtual ::user::interaction * ChildWindowFromPoint(POINT point);
      virtual ::user::interaction * ChildWindowFromPoint(POINT point,UINT nFlags);
      static ::user::interaction * FindWindow(const char * lpszClassName,const char * lpszWindowName);
      static ::user::interaction * FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow);

      virtual ::user::interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
      virtual ::user::interaction * GetTopWindow() const override;

      //virtual ::user::interaction * GetWindow(UINT nCmd);
      virtual ::user::interaction * GetLastActivePopup() override;

      //virtual bool IsChild(::user::interaction *  pWnd);
      //virtual ::user::interaction * GetParent();
      //using ::user::interaction_impl::SetParent;
      //::user::interaction * SetParent(::user::interaction * pWndNewParent);
      //static::user::interaction * PASCAL oswindowFromPoint(POINT point);


      //virtual ::user::interaction * SetOwner(::user::interaction * pWndNewParent);
      //virtual ::user::interaction * GetOwner() const;

      //virtual bool FlashWindow(bool bInvert);

      //virtual i32 message_box(const char * lpszText,const char * lpszCaption = nullptr,UINT nType = MB_OK) override;


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(u32 dwFlags,UINT  uCount,tick tickTimeout);

#endif   // WINVER >= 0x0500

      // Clipboard Functions
      //virtual bool ChangeClipboardChain(oswindow oswindow_Next);
      //virtual ::oswindow  SetClipboardViewer();
      //virtual bool OpenClipboard();
      //static ::user::interaction * GetClipboardOwner();
      //static ::user::interaction * GetClipboardViewer();
      //static ::user::interaction * GetOpenClipboardWindow();


      //static point GetCaretPos();
      //static void SetCaretPos(POINT point);
      //virtual void HideCaret() override;
      //virtual void ShowCaret() override;

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = TRUE) override;

      // icon Functions
      //virtual HICON SetIcon(HICON hIcon,bool bBigIcon);
      //virtual HICON GetIcon(bool bBigIcon) const;

      // Context Help Functions
      virtual bool SetWindowContextHelpId(u32 dwContextHelpId) override;
      virtual u32 GetWindowContextHelpId() const override;

      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = TRUE);
      // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
      virtual void WinHelp(uptr dwData,UINT nCmd = 0);
      //virtual void HtmlHelp(uptr dwData, UINT nCmd = 0x000F);
      virtual void WinHelpInternal(uptr dwData,UINT nCmd = 0);



      // dialog support
      void UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler) override;
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;

      virtual bool OnCommand(::message::base * pbase) override;
      virtual bool OnNotify(::message::base * pbase) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual bool SubclassWindow(oswindow hWnd);
      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics,::user::interaction * pwindow,UINT nCtlColor);

      DECL_GEN_SIGNAL(_001OnDestroy);
      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnKillFocus(::user::interaction * pNewWnd);
      LRESULT OnMenuChar(UINT nChar,UINT nFlags,::user::menu* pMenu);
      void OnMenuSelect(UINT nItemID,UINT nFlags,HMENU hSysMenu);
      void OnMove(i32 x,i32 y);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      void OnParentNotify(UINT message,LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::user::interaction *);
      void OnShowWindow(bool bShow,UINT nStatus);
      void OnSize(UINT nType,i32 cx,i32 cy);
      void OnTCard(UINT idAction,u32 dwActionData);

      void OnChangeUIState(UINT nAction,UINT nUIElement);
      void OnUpdateUIState(UINT nAction,UINT nUIElement);
      UINT OnQueryUIState();

      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      void OnNcCalcSize(bool bCalcValidRects,NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(::user::create_struct * lpCreateStruct);

      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      LRESULT OnNcHitTest(::point point);
      void OnNcLButtonDblClk(UINT nHitTest, const ::point & point);
      void OnNcLButtonDown(UINT nHitTest, const ::point & point);
      void OnNcLButtonUp(UINT nHitTest, const ::point & point);
      void OnNcMButtonDblClk(UINT nHitTest, const ::point & point);
      void OnNcMButtonDown(UINT nHitTest, const ::point & point);
      void OnNcMButtonUp(UINT nHitTest, const ::point & point);
      void OnNcMouseMove(UINT nHitTest, const ::point & point);
      void OnNcPaint();
      void OnNcRButtonDblClk(UINT nHitTest, const ::point & point);
      void OnNcRButtonDown(UINT nHitTest, const ::point & point);
      void OnNcRButtonUp(UINT nHitTest, const ::point & point);

      // System message handler member functions
      void OnDropFiles(HDROP hDropInfo);
      void OnPaletteIsChanging(::user::interaction * pRealizeWnd);
      void OnSysChar(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnSysCommand(UINT nID,LPARAM lParam);
      void OnSysDeadChar(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnSysKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnSysKeyUp(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnCompacting(UINT nCpuTime);
      void OnDevModeChange(LPTSTR lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::user::interaction * pFocusWnd);
      void OnSpoolerStatus(UINT nStatus,UINT nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(UINT uFlags,const char * lpszSection);
      void OnWinIniChange(const char * lpszSection);

      // Input message handler member functions
      void OnChar(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnDeadChar(UINT nChar,UINT nRepCnt,UINT nFlags);
      //      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      //    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnKeyUp(UINT nChar,UINT nRepCnt,UINT nFlags);
      void OnLButtonDblClk(UINT nFlags, const ::point & point);
      void OnLButtonDown(UINT nFlags, const ::point & point);
      void OnLButtonUp(UINT nFlags, const ::point & point);
      void OnMButtonDblClk(UINT nFlags, const ::point & point);
      void OnMButtonDown(UINT nFlags, const ::point & point);
      void OnMButtonUp(UINT nFlags, const ::point & point);
      i32 OnMouseActivate(::user::interaction * pDesktopWnd,UINT nHitTest,UINT message);
      void OnMouseMove(UINT nFlags, const ::point & point);
      bool OnMouseWheel(UINT nFlags,i16 zDelta, const ::point & point);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam,LPARAM lParam);
      void OnRButtonDblClk(UINT nFlags, const ::point & point);
      void OnRButtonDown(UINT nFlags, const ::point & point);
      void OnRButtonUp(UINT nFlags, const ::point & point);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      void OnTimer(uptr nIDEvent);

      // Initialization message handler member functions
      void OnInitMenu(::user::menu* pMenu);
      void OnInitMenuPopup(::user::menu* pPopupMenu,UINT nIndex,bool bSysMenu);

      // Clipboard message handler member functions
      void OnAskCbFormatName(UINT nMaxCount,LPTSTR lpszString);
      void OnChangeCbChain(oswindow oswindow_Remove,oswindow oswindow_After);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::user::interaction * pClipAppWnd,UINT nSBCode,UINT nPos);
      void OnPaintClipboard(::user::interaction * pClipAppWnd,HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(UINT nFormat);
      void OnSizeClipboard(::user::interaction * pClipAppWnd,HGLOBAL hRect);
      void OnVScrollClipboard(::user::interaction * pClipAppWnd,UINT nSBCode,UINT nPos);

      // control message handler member functions
      //i32 OnCompareItem(i32 nIDCtl,LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //void OnDeleteItem(i32 nIDCtl,LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //void OnDrawItem(i32 nIDCtl,LPDRAWITEMSTRUCT lpDrawItemStruct);
      UINT OnGetDlgCode();
      //void OnMeasureItem(i32 nIDCtl,LPMEASUREITEMSTRUCT lpMeasureItemStruct);

      // MDI message handler member functions
      void OnMDIActivate(bool bActivate,
                         ::user::interaction * pActivateWnd,::user::interaction * pDeactivateWnd);

      // menu loop notification messages
      void OnEnterMenuLoop(bool bIstrack_popup_menu);
      void OnExitMenuLoop(bool bIstrack_popup_menu);

      // Win4 messages
      void OnStyleChanged(i32 nStyleType,LPSTYLESTRUCT lpStyleStruct);
      void OnStyleChanging(i32 nStyleType,LPSTYLESTRUCT lpStyleStruct);
      void OnSizing(UINT nSide,LPRECT lpRect);
      void OnMoving(UINT nSide,LPRECT lpRect);
      void OnCaptureChanged(::user::interaction * pwindow);
      bool OnDeviceChange(UINT nEventType,uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      //virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState() override;
      virtual void EndModalState() override;

      // for translating Windows messages in main message pump
      virtual void pre_translate_message(::message::message * pmessage) override;


      // for processing Windows messages
      virtual void message_handler(::message::base * pbase) override;


      // for handling default processing
      LRESULT Default();
      virtual LRESULT DefWindowProc(UINT message,WPARAM wParam,lparam lParam);

      virtual void PostNcDestroy() override;

      // for notifications from parent
      //virtual bool OnChildNotify(::message::base * pbase);
      // return TRUE if parent should not process this message
      //virtual bool ReflectChildNotify(::message::base * pbase);
      //static bool ReflectMessage(oswindow oswindow_Child,::message::base * pbase);

      // Implementation
      virtual bool CheckAutoCenter() override;
      //virtual bool GrayCtlColor(HDC hDC,oswindow oswindow,UINT nCtlColor,
      //                          HBRUSH hbrGray,COLORREF clrText);


      // helper routines for implementation
      //bool HandleFloatingSysCommand(UINT nID, LPARAM lParam) override;
      bool IsTopParentActive() override;
      void ActivateTopParent() override;
      //virtual void WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage);
      virtual bool is_frame_window(); // is_kind_of(__type(frame_window)))
      virtual void on_final_release() override;
      static bool ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      static bool ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      //static void PASCAL _FilterToolTipMessage(MESSAGE* pMsg, ::user::interaction * pWnd);
      bool _EnableToolTips(bool bEnable, UINT nFlag) override;
      //static oswindow PASCAL GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp() override;


      friend class frame_window;

      bool CreateDlg(const char * lpszTemplateName,::user::interaction * pParentWnd);


      //CLASS_DECL_AURA friend LRESULT CALLBACK __send_message_hook(i32,WPARAM,LPARAM);
      //CLASS_DECL_AURA friend LRESULT CALLBACK __cbt_filter_hook(i32,WPARAM,LPARAM);

      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam,LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM,LPARAM);
      LRESULT OnDragList(WPARAM,LPARAM);

      bool CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lparam);


      static void get_app_wnda(user::oswindow_array & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      //virtual LONG get_window_long(i32 nIndex) const;
      //virtual LONG set_window_long(i32 nIndex,LONG lValue);
      //virtual LONG_PTR get_window_long_ptr(i32 nIndex) const;
      //virtual LONG_PTR set_window_long_ptr(i32 nIndex,LONG_PTR lValue);

      virtual void _001BaseWndInterfaceMap() override;




      void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      //string calc_icon_window_class(u32 dwDefaultStyle,const char * pszMatter);
      //string calc_window_class();

      void on_set_parent(::user::interaction * pinteraction);

      ::user::interaction * FromHandlePermanent(oswindow oswindow);

      bool Attach(oswindow hWndNew);
      virtual oswindow Detach();
      //virtual bool get_rect_normal(LPRECT lprect);
      virtual oswindow UnsubclassWindow();
//      virtual void register_drop_target();

      //virtual void WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage);
      virtual bool SendChildNotifyLastMsg(LRESULT* pResult);

      virtual oswindow get_handle() const override;

      //virtual void MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight, bool bRepaint);
      //virtual void MoveWindow(LPCRECT lpRect, bool bRepaint = TRUE);

      virtual id SetDlgCtrlId(id id) override;
      virtual id GetDlgCtrlId();


      virtual LONG GetWindowLong(i32 nIndex);
      virtual LONG SetWindowLong(i32 nIndex, LONG lValue);


      virtual void SetFont(::draw2d::font* pfont, bool bRedraw);
      virtual void set_owner(::user::interaction * pOwnerWnd) override;
      virtual ::draw2d::font* GetFont();





      void _001OnTriggerMouseInside() override;


      ::user::interaction * get_next(bool bIgnoreChildren, i32 * piLevel) override;
      virtual bool on_keyboard_focus(::user::primitive * pfocus) override;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      virtual bool keyboard_focus_OnChildKillFocus() override;


      virtual bool has_pending_graphical_update()override;

   };


} // namespace android





