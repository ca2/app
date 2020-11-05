#pragma once


namespace uwp
{


   CLASS_DECL_AXIS LRESULT CALLBACK __send_message_hook(int, WPARAM, LPARAM);
   //CLASS_DECL_AXIS void _gen::StandardSubclass(oswindow);
   CLASS_DECL_AXIS LRESULT CALLBACK __cbt_filter_hook(int, WPARAM, LPARAM);
   CLASS_DECL_AXIS LRESULT __call_window_procedure(::user::interaction * pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

   ref class directx_framework_view;

   class CLASS_DECL_AXIS interaction_impl :
      virtual public ::user::interaction_impl
   {
   public:

      directx_framework_view ^                     m_frameworkview;
      ::user::message_queue_listener *          m_plistener;
      string                                    m_strWindowText;
      //::image_pointer              m_pimage;
      //::image_pointer              m_spimageMultAlphaWork;
      pointd                                    m_pointLastMouseMove;
      double                                    m_dAccumulatedMouseMoveDistance;
      tick                                      m_tickLastMouseMove;
      Agile < Windows::UI::Core::CoreWindow >   m_window;
      ::thread *                                m_pthreadDraw;
      ::user::primitive* m_pbasewnd;
      ::user::interaction* m_pguieCapture;

      int_ptr_to_int_ptr                        m_mapLong;
      ::mutex                                     m_mutexQueue;
      manual_reset_event                        m_evQueue;
      __pointer_array(::message::base)                      m_messageaQueue;


      interaction_impl();
      interaction_impl(::layered * pobjectContext);
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


      LONG_PTR get_window_long_ptr(i32 nIndex) const;
      LONG_PTR set_window_long_ptr(i32 nIndex, LONG_PTR lValue);

      static const MSG* GetCurrentMessage();

      virtual void install_message_routing(::channel * pchannel);

      bool operator==(const ::user::interaction_impl& wnd) const;
      bool operator!=(const ::user::interaction_impl& wnd) const;

      u32 GetStyle() const;
      u32 GetExStyle() const;
      bool ModifyStyle(u32 dwRemove, u32 dwAdd, UINT nFlags = 0);
      bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, UINT nFlags = 0);

      //virtual ::user::interaction * GetOwner();
      //virtual ::user::interaction * SetOwner(::user::interaction * pOwnerWnd);

      virtual oswindow _get_handle();

      virtual void route_command_message(::user::command * pcommand) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      void _002OnDraw(::image * pimage);

      DECL_GEN_SIGNAL(_001OnEraseBkgnd);
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
      bool SubclassDlgItem(UINT nID, ::user::interaction_impl * pParent);
      oswindow UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      bool ExecuteDlgInit(const char * lpszResourceName);
      bool ExecuteDlgInit(LPVOID lpResource);


      virtual ::estatus update_graphics_resources() override;

      // for child windows, views, panes etc
      //virtual bool create_window(::user::interaction * pinteraction, const char * lpszClassName,const char * lpszWindowName,u32 dwStyle,const RECT & rect,::user::interaction * pParentWnd,id id, ::create * pcreate = nullptr) override;

      virtual bool _native_create_window_ex(::user::create_struct& cs);


      //virtual bool CreateEx(u32 dwExStyle, const char * lpszClassName,
      //                      const char * lpszWindowName, u32 dwStyle,
      //                      int x, int y, int nWidth, int nHeight,
      //                      oswindow hWndParent, id id, LPVOID lpParam = nullptr);

      //virtual bool CreateEx(u32 dwExStyle, const char * lpszClassName,
      //                      const char * lpszWindowName, u32 dwStyle,
      //                      const RECT& rect,
      //                      ::user::interaction* pParentWnd, id id,
      //                      LPVOID lpParam = nullptr);

      virtual bool DestroyWindow();

      // special pre-creation and ::user::interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct& cs);

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);


      // get immediate child with given ID
      //      using ::user::interaction::GetDlgItem;
      void GetDlgItem(id id, oswindow* phWnd) const;

      //virtual bool IsWindow() const;

#if(WINVER >= 0x0500)

      ::user::interaction_impl * GetAncestor(UINT gaFlags) const override;

#endif   // WINVER >= 0x0500

      LRESULT send_message(const ::id & id, WPARAM wParam = 0, lparam lParam = nullptr);
      bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = nullptr);

      bool SendNotifyMessage(const ::id & id, WPARAM wParam, LPARAM lParam);
      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      bool DragDetect(POINT pt) const;



      // Window Text Functions
      void set_window_text(const char * lpszString) override;
      //strsize get_window_text(char * lpszStringBuf, strsize nMaxCount) override;
      void get_window_text(string & rString) override;
      //strsize get_window_text_length() override;
      void SetFont(::draw2d::font* pFont, bool bRedraw = TRUE);
      ::draw2d::font* GetFont();


      // Window size and position Functions
      //virtual bool layout().is_iconic();
      //virtual bool layout().is_zoomed();
      //void MoveWindow(int x, int y, int nWidth, int nHeight, bool bRepaint = TRUE);
      //void MoveWindow(LPCRECT lpRect, bool bRepaint = TRUE);
      //int SetWindowRgn(HRGN hRgn, bool bRedraw);
      //int GetWindowRgn(HRGN hRgn);


      //virtual bool set_window_pos(iptr z, int x, int y, int cx, int cy, UINT nFlags);
      virtual UINT ArrangeIconicWindows();
      virtual bool BringWindowToTop();
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

      //      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      //    virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::user::interaction_impl * pwndTo, LPPOINT lpPoint, UINT nCount);
      virtual void MapWindowPoints(::user::interaction_impl * pwndTo, LPRECT lpRect);

      // Update/Painting Functions
      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      virtual bool ReleaseDC(::image * pimage);
      virtual void Print(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      //virtual bool GetUpdateRect(LPRECT lpRect, bool bErase = FALSE);
      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE);
      //virtual void Invalidate(bool bErase = TRUE);
      //virtual void InvalidateRect(LPCRECT lpRect, bool bErase = TRUE);
      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE);
      //virtual void ValidateRect(LPCRECT lpRect);
      //virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool ShowWindow(int nCmdShow);
      virtual void _001WindowMaximize();
      virtual void _001WindowRestore();
      virtual bool is_window_visible();
      virtual void ShowOwnedPopups(bool bShow = TRUE);

      virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, u32 flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();
      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,
                                ::draw2d::region* prgnUpdate = nullptr,
                                UINT flags = RDW_INVALIDATE | RDW_ERASE);
      //      virtual bool EnableScrollBar(int nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);

      virtual bool DrawAnimatedRects(int idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo);
      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, LPCRECT lprc, UINT uFlags);

#if(WINVER >= 0x0500)

      virtual bool AnimateWindow(tick tick, u32 dwFlags);

#endif   // WINVER >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, UINT nFlags) const;

#endif   // _WIN32_WINNT >= 0x0501

      // Layered Window

#if(_WIN32_WINNT >= 0x0500)

      virtual bool SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, u32 dwFlags);
      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
                                       ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, u32 dwFlags);

#endif   // _WIN32_WINNT >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, u32 *pdwFlags) const;

#endif   // _WIN32_WINNT >= 0x0501


      // Timer Functions
      virtual bool SetTimer(UINT_PTR uEvent, UINT nElapse, PFN_TIMER pfnTimer);
      virtual bool KillTimer(uptr uEvent);

      // Window State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = TRUE);

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
      virtual void CheckDlgButton(int nIDButton, UINT nCheck);
      virtual void CheckRadioButton(int nIDFirstButton, int nIDLastButton,
                                    int nIDCheckButton);
      virtual int GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton);
      /*virtual int DlgDirList(__inout_z char * lpPathSpec, __in int nIDListBox,
      __in int nIDStaticPath, __in UINT nFileType);
      virtual int DlgDirListComboBox(__inout_z char * lpPathSpec, __in int nIDComboBox,
      __in int nIDStaticPath, __in UINT nFileType);
      virtual bool DlgDirSelect(__out_ecount_z(nSize) char * lpString, __in int nSize, __in int nIDListBox);
      virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) char * lpString, __in int nSize, __in int nIDComboBox);*/

      virtual UINT GetDlgItemInt(int nID, BOOL * lpTrans = nullptr, bool bSigned = TRUE) const;
      //      virtual int GetDlgItemText(__in int nID, __out_ecount_part_z(nMaxCount, return + 1) char * lpStr, __in int nMaxCount) const;
      //    virtual int GetDlgItemText(int nID, string & rString) const;
      virtual ::user::interaction_impl * GetNextDlgGroupItem(::user::interaction_impl * pWndCtl, bool bPrevious = FALSE) const;
      virtual ::user::interaction_impl * GetNextDlgTabItem(::user::interaction_impl * pWndCtl, bool bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(int nIDButton) const;
      virtual LRESULT SendDlgItemMessage(int nID, const ::id & id, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual void SetDlgItemInt(int nID, UINT nValue, bool bSigned = TRUE);
      virtual void SetDlgItemText(int nID, const char * lpszString);

      // Scrolling Functions
      virtual int GetScrollPos(int nBar) const;
      virtual void GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const;
      //virtual void ScrollWindow(int xAmount, int yAmount,
      //                          LPCRECT lpRect = nullptr,
      //                          LPCRECT lpClipRect = nullptr);
      virtual int SetScrollPos(int nBar, int nPos, bool bRedraw = TRUE);
      virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos,
                                  bool bRedraw = TRUE);
      virtual void ShowScrollBar(UINT nBar, bool bShow = TRUE);
      virtual void EnableScrollBarCtrl(int nBar, bool bEnable = TRUE);
//      virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
      // return sibling scrollbar control (or nullptr if none)

      //virtual int ScrollWindowEx(int dx, int dy,
      //                           LPCRECT lpRectScroll, LPCRECT lpRectClip,
      //                           ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
      //      virtual bool SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo,
      //       bool bRedraw = TRUE);
      //      virtual bool GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
      virtual int GetScrollLimit(int nBar);

      //#if defined(WINDOWS_DESKTOP) && (WINVER >= 0x0500)

      // virtual bool GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;

      //#endif   // WINVER >= 0x0500

      // Window Access Functions
      virtual ::user::interaction *  ChildWindowFromPoint(POINT point);
      virtual ::user::interaction *  ChildWindowFromPoint(POINT point, UINT nFlags);
      static __pointer(::user::interaction_impl) FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static __pointer(::user::interaction_impl) FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      //      virtual ::user::interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
      virtual ::user::interaction *  GetTopWindow();

      virtual ::user::interaction *  GetWindow(UINT nCmd);
      virtual ::user::interaction *  GetLastActivePopup();

      virtual bool IsChild(::user::interaction *   pWnd);
      virtual ::user::interaction *  GetParent();
      using ::user::interaction_impl::SetParent;
//      ::user::interaction *  SetParent(::user::interaction *  pWndNewParent);
      static __pointer(::user::interaction_impl) WindowFromPoint(POINT point);

      // Alert Functions

      bool FlashWindow(bool bInvert);

      //virtual int message_box(const char * lpszText, const char * lpszCaption = nullptr, UINT nType = MB_OK);


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(u32 dwFlags, UINT  uCount, tick tickTimeout);

#endif   // WINVER >= 0x0500

      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow hWndNext);
      virtual oswindow SetClipboardViewer();
      virtual bool OpenClipboard();
      static ::user::interaction_impl * GetClipboardOwner();
      static ::user::interaction_impl * GetClipboardViewer();
      static ::user::interaction_impl * GetOpenClipboardWindow();

      // Caret Functions
      static point GetCaretPos();
      static void SetCaretPos(POINT point);
      virtual void HideCaret();
      virtual void ShowCaret();

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = TRUE);

      // icon Functions
      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
      virtual HICON GetIcon(bool bBigIcon) const;

      // Context Help Functions
      virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      virtual u32 GetWindowContextHelpId() const;

      // Dialog Data support
      //virtual bool UpdateData(bool bSaveAndValidate = TRUE);
      // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
      void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler);
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      virtual id RunModalLoop(u32 dwFlags = 0) override;
      virtual bool ContinueModal() override;
      virtual void EndModalLoop(id nResult) override;
      //virtual void EndAllModalLoops(id nResult);

      // Window-Management message handler member functions
      virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual bool OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      void OnActivate(UINT nState, ::user::interaction_impl * pWndOther, bool bMinimized);
      void OnActivateApp(bool bActive, u32 dwThreadID);
      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      void OnCancelMode();
      void OnChildActivate();
      void OnClose();
      void OnContextMenu(::user::interaction_impl * pWnd, point pos);
      //      bool OnCopyData(::user::interaction_impl * pWnd, COPYDATASTRUCT* pCopyDataStruct);
      DECL_GEN_SIGNAL(_001OnCreate);


      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction_impl * pWnd, UINT nCtlColor);

      DECL_GEN_SIGNAL(_001OnDestroy);
      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      void OnEnterIdle(UINT nWhy, ::user::interaction_impl * pWho);
      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      //    bool OnHelpInfo(HELPINFO* lpHelpInfo);
      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnKillFocus(::user::interaction_impl * pNewWnd);
      LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::user::menu* pMenu);
      void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      void OnMove(int x, int y);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      void OnParentNotify(const ::id & id, LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::user::interaction_impl * pOldWnd);
      void OnShowWindow(bool bShow, UINT nStatus);
      void OnSize(UINT nType, int cx, int cy);
      void OnTCard(UINT idAction, u32 dwActionData);
      //      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      //    void OnWindowPosChanged(WINDOWPOS* lpwndpos);

      void OnChangeUIState(UINT nAction, UINT nUIElement);
      void OnUpdateUIState(UINT nAction, UINT nUIElement);
      UINT OnQueryUIState();

      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      //      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(LPCREATESTRUCT lpCreateStruct);

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
      //      void OnDropFiles(HDROP hDropInfo);
      void OnPaletteIsChanging(::user::interaction_impl * pRealizeWnd);
      void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysCommand(UINT nID, LPARAM lParam);
      void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnCompacting(UINT nCpuTime);
      void OnDevModeChange(char * lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::user::interaction_impl * pFocusWnd);
      void OnSpoolerStatus(UINT nStatus, UINT nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(UINT uFlags, const char * lpszSection);
      void OnWinIniChange(const char * lpszSection);

      // Input message handler member functions
      void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      //    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnLButtonDblClk(UINT nFlags, const ::point & point);
      void OnLButtonDown(UINT nFlags, const ::point & point);
      void OnLButtonUp(UINT nFlags, const ::point & point);
      void OnMButtonDblClk(UINT nFlags, const ::point & point);
      void OnMButtonDown(UINT nFlags, const ::point & point);
      void OnMButtonUp(UINT nFlags, const ::point & point);
      int OnMouseActivate(::user::interaction_impl * pDesktopWnd, UINT nHitTest, const ::id & id);
      void OnMouseMove(UINT nFlags, const ::point & point);
      bool OnMouseWheel(UINT nFlags, short zDelta, const ::point & point);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      void OnRButtonDblClk(UINT nFlags, const ::point & point);
      void OnRButtonDown(UINT nFlags, const ::point & point);
      void OnRButtonUp(UINT nFlags, const ::point & point);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      void OnTimer(uptr uEvent);

      // Initialization message handler member functions
      void OnInitMenu(::user::menu* pMenu);
      void OnInitMenuPopup(::user::menu* pPopupMenu, UINT nIndex, bool bSysMenu);

      // Clipboard message handler member functions
      void OnAskCbFormatName(__in UINT nMaxCount, __out_ecount_z(nMaxCount) char * lpszString);
      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::user::interaction_impl * pClipAppWnd, UINT nSBCode, UINT nPos);
      void OnPaintClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(UINT nFormat);
      void OnSizeClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hRect);
      void OnVScrollClipboard(::user::interaction_impl * pClipAppWnd, UINT nSBCode, UINT nPos);

      // control message handler member functions
      //      int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //    void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //  void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
      UINT OnGetDlgCode();
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
      void OnSizing(UINT nSide, LPRECT lpRect);
      void OnMoving(UINT nSide, LPRECT lpRect);
      void OnCaptureChanged(::user::interaction_impl * pWnd);
      bool OnDeviceChange(UINT nEventType, dword_ptr dwData);

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
      virtual void message_handler(::message::base * pbase);
      //virtual bool OnWndMsg(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
      LRESULT Default();
      virtual LRESULT DefWindowProc(const ::id & id, WPARAM wParam, lparam lParam);

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      // for notifications from parent
      virtual bool OnChildNotify(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      // return TRUE if parent should not process this message
      bool ReflectChildNotify(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static bool ReflectLastMsg(oswindow hWndChild, LRESULT* pResult = nullptr);

      virtual bool CheckAutoCenter();
      static bool GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
                               HBRUSH hbrGray, COLORREF clrText);


      // helper routines for implementation
      bool HandleFloatingSysCommand(UINT nID, LPARAM lParam);
      //bool IsTopParentActive();
      void ActivateTopParent();
      virtual void WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage);
      virtual bool is_frame_window(); // is_kind_of(System.template type_info < frame_window > ()))
      virtual void on_final_release();
      static bool ModifyStyle(oswindow hWnd, u32 dwRemove, u32 dwAdd,
                              UINT nFlags);
      static bool ModifyStyleEx(oswindow hWnd, u32 dwRemove, u32 dwAdd,
                                UINT nFlags);
      static void _FilterToolTipMessage(MSG* pMsg, ::user::interaction_impl * pWnd);
      bool _EnableToolTips(bool bEnable, UINT nFlag);
      static oswindow GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp();

      //UINT m_nFlags;      // see WF_ flags above

      //      WNDPROC m_pfnSuper; // for subclassing of controls
      static const UINT m_nMsgDragList;
      int m_nModalResult; // for return values from ::user::interaction_impl::RunModalLoop

      ::draw2d::font * m_pfont;

      friend class frame_window;

      // for creating dialogs and dialog-like windows
      bool CreateDlg(const char * lpszTemplateName, ::user::interaction_impl * pParentWnd);
      //bool CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::user::interaction_impl * pParentWnd,
      // HINSTANCE hInst);


      // implementation of message dispatch/hooking
      CLASS_DECL_AXIS friend LRESULT CALLBACK __send_message_hook(int, WPARAM, LPARAM);
      //CLASS_DECL_AXIS friend void _gen::StandardSubclass(oswindow);
      CLASS_DECL_AXIS friend LRESULT CALLBACK __cbt_filter_hook(int, WPARAM, LPARAM);
      CLASS_DECL_AXIS friend LRESULT __call_window_procedure(::user::interaction * pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM, LPARAM);
      LRESULT OnDragList(WPARAM, LPARAM);

      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lParam);


      static void get_app_wnda(user::oswindow_array & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      virtual LONG GetWindowLong(int nIndex);
      virtual LONG SetWindowLong(int nIndex, LONG lValue);

      virtual void _001BaseWndInterfaceMap();


      // void _001UpdateWindow();
      virtual bool has_focus() override;
      virtual bool is_active() override;


      void _001OnTriggerMouseInside();


      Agile < Windows::UI::Core::CoreWindow > get_os_window();

      void set_view_port_org(::image * pimage);

      void offset_view_port_org(LPRECT lprectScreen);

      virtual void queue_message_handler(::message::base * pbase) override;

      virtual bool _is_window() const override;

      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd) override;

      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;

      virtual bool is_text_composition_active() override;

      virtual void set_input_content_rect(const rect& rect);
      virtual void set_input_selection_rect(const rect& rect);

      virtual rect get_input_content_rect();
      virtual rect get_input_selection_rect();


   };


} // namespace uwp



