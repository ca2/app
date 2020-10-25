#pragma once


#include "round_window.h"
#include "aura/user/user/interaction_impl.h"


namespace ios
{


   CLASS_DECL_AXIS LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
   CLASS_DECL_AXIS LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);
   CLASS_DECL_AXIS LRESULT __call_window_procedure(::user::interaction *   pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);


   class CLASS_DECL_AXIS interaction_impl :
      virtual public ::user::interaction_impl,
      virtual public ::round_window
   {
   public:

      
      string                           m_strWindowText;
      ::user::primitive *              m_pbasewnd;
      bool                             m_bNeedsUpdate;
      ::rect                           m_rectLastPos;
      tick                             m_tickLastPos;
      int                              m_iSoftwareKeyboardScroll;


      interaction_impl();
      interaction_impl(::layered * pobjectContext);
      virtual ~interaction_impl();


      virtual void construct(oswindow hwnd);

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool round_window_become_first_responder() override;

      //virtual bool create_message_queue(::user::interaction * pinteraction,const char * pszName) override;

      static const MESSAGE* PASCAL GetCurrentMessage();

      virtual void install_message_routing(::channel * pchannel) override;

      virtual ::user::interaction *  SetOwner(::user::interaction *   pOwnerWnd) override;

      virtual ::user::interaction * get_wnd() const override;

      virtual void route_command_message(::user::command * pcommand) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      void _002OnDraw(::draw2d::graphics_pointer & pgraphics);



#if(WINVER >= 0x0500)

      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;

#endif   // WINVER >= 0x0500

      virtual ::user::interaction_impl * from_os_data(void * pdata) override;
      virtual void * get_os_data() const override;

      static ::user::interaction_impl * from_handle(oswindow hWnd);
      static ::user::interaction_impl * FromHandlePermanent(oswindow hWnd);
      //static void DeleteTempMap();
      bool Attach(oswindow hWndNew);
      oswindow Detach();

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
      bool SubclassWindow(oswindow hWnd);
      //bool SubclassDlgItem(UINT nID, ::interaction_impl * pParent);
      oswindow UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      bool ExecuteDlgInit(const char * lpszResourceName) override;
      bool ExecuteDlgInit(LPVOID lpResource) override;

      using ::user::interaction_impl::create_window;
      // for child windows, views, panes etc
      virtual bool create_window(::user::interaction * pinteraction, const char * pszClassName,const char * pszWindowName,u32 uStyle,const ::rect & rect,::user::interaction * puiParent,id id, ::create * pcreate = nullptr) override;

      // advanced creation (allows access to extended styles)
      virtual bool create_window_ex(
      ::user::interaction * pinteraction,
      ::user::create_struct & cs,
      ::user::interaction * puiParent,
      id id) override;

      virtual bool _native_create_window_ex(::user::create_struct& cs) override;

      virtual bool DestroyWindow() override;

      // special pre-creation and ::interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct& cs) override;

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder) override;

      
      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;
      virtual void edit_on_kill_focus(::user::interaction* pinteraction) override;


      virtual bool _is_window() const override;
      
      virtual void queue_message_handler(::message::base * pbase) override;
      
      virtual void on_host_message_handler(::message::base * pbase);


#if(WINVER >= 0x0500)

      ::interaction_impl * GetAncestor(UINT gaFlags) const;

#endif   // WINVER >= 0x0500

//      LRESULT send_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0) override;
  //    bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0) override;

      bool SendNotifyMessage(const ::id & id, WPARAM wParam, LPARAM lParam);
      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      //bool DragDetect(POINT point) const override;



      // oswindow Text Functions
      void set_window_text(const char * lpszString) override;
      //strsize GetWindowText(LPTSTR lpszStringBuf, strsize nMaxCount);
      void get_window_text(string & str) override;
      //strsize GetWindowTextLength() override;
      //      void SetFont(::draw2d::font* pFont, bool bRedraw = TRUE);
      //    ::draw2d::font* GetFont();

      virtual void defer_update_text_view();

      // oswindow size and position Functions
      //virtual bool layout().is_iconic() override;
      //virtual bool layout().is_zoomed() override;
//      void MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight,
//                      bool bRepaint = TRUE);
//      void MoveWindow(const ::rect & rect, bool bRepaint = TRUE);
      i32 SetWindowRgn(HRGN hRgn, bool bRedraw);
      i32 GetWindowRgn(HRGN hRgn);


      //virtual bool set_window_pos(iptr z, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags) override;
      virtual UINT ArrangeIconicWindows() override;
      //virtual void BringToTop(::display edisplay) override;
      //virtual bool BringWindowToTop() override;
      //using ::user::interaction_impl::get_window_rect;
      //virtual bool get_window_rect(RECT64 * lpRect) override;
      //using ::user::interaction_impl::get_client_rect;
      //virtual bool get_client_rect(RECT64 * lpRect) override;

      //virtual bool _001ClientToScreen(LPRECT lprect) override;
      //virtual bool _001ClientToScreen(LPPOINT lppoint) override;
      //virtual bool _001ClientToScreen(RECT64 * lprect) override;
      //virtual bool _001ClientToScreen(POINT64 * lppoint) override;
      //virtual bool _001ScreenToClient(LPRECT lprect) override;
      //virtual bool _001ScreenToClient(LPPOINT lppoint) override;
      //virtual bool _001ScreenToClient(RECT64 * lprect) override;
      //virtual bool _001ScreenToClient(POINT64 * lppoint) override;

      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);

      virtual void MapWindowPoints(::user::interaction * pwndTo, LPPOINT lpPoint, UINT nCount);
      virtual void MapWindowPoints(::user::interaction * pwndTo, LPRECT lpRect);

      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      virtual bool ReleaseDC(::draw2d::graphics_pointer & pgraphics);
      virtual void Print(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const override;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const override;

      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = TRUE) override;
      virtual bool GetUpdateRect(LPRECT lpRect, bool bErase = FALSE) override;
      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE) override;
      virtual void Invalidate(bool bErase = TRUE) override;
      virtual void InvalidateRect(const ::rect & rect, bool bErase = TRUE) override;
      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE) override;
      virtual void ValidateRect(const ::rect & rect) override;
      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      virtual bool ShowWindow(i32 nCmdShow) override;
//      virtual void _001WindowMaximize() override;
//      virtual void _001WindowRestore() override;
//      virtual bool is_window_visible() override;
      virtual void ShowOwnedPopups(bool bShow = TRUE) override;

      virtual void round_window_draw(CGContextRef cgc, i32 cx, i32 cy) override;
      virtual void round_window_mouse_down(double x, double y) override;
      virtual void round_window_mouse_up(double x, double y) override;
      virtual void round_window_mouse_moved(double x, double y) override;
      virtual void round_window_mouse_dragged(double x, double y) override;
//      virtual bool round_window_key_down(unsigned int uiKeyCode);
//      virtual bool round_window_key_up(unsigned int uiKeyCode);


      virtual bool SetFocus() override;

      virtual bool has_focus() override;
      virtual bool is_active() override;


      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;
      void offset_viewport_org(LPRECT lprectScreen);


      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, DWORD flags) override;
      virtual bool LockWindowUpdate() override;
      virtual void UnlockWindowUpdate() override;
//      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr, UINT flags = RDW_INVALIDATE | RDW_ERASE) override;
      // xxx      virtual bool EnableScrollBar(i32 nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(i32 idAni, CONST RECT *lprcFrom, CONST RECT *lprcTo) override;
      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, LPCRECT lprc, UINT uFlags) override;

#if(WINVER >= 0x0500)

      virtual bool AnimateWindow(DWORD tick, DWORD dwFlags);

#endif   // WINVER >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, UINT nFlags) const;

#endif   // _WIN32_WINNT >= 0x0501

      // Layered oswindow

#if(_WIN32_WINNT >= 0x0500)

      virtual bool SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
                                       ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);

#endif   // _WIN32_WINNT >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const;

#endif   // _WIN32_WINNT >= 0x0501


      // Timer Functions
      virtual bool SetTimer(uptr uEvent, UINT nElapse, PFN_TIMER pfnTimer) override;
      virtual bool KillTimer(uptr uEvent) override;

      // oswindow State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = TRUE);

      virtual ::user::interaction *  GetActiveWindow() override;
      virtual ::user::interaction *  SetActiveWindow() override;

      virtual bool SetForegroundWindow() override;
      static ::user::interaction * PASCAL GetForegroundWindow();

      virtual id SetDlgCtrlId(id id) override;
      virtual id GetDlgCtrlId();



      //virtual ::user::interaction *  GetCapture() override;
      virtual ::user::interaction *  GetFocus() override;

      virtual ::user::interaction *  get_desktop_window();

      virtual void CloseWindow() override;
      virtual bool OpenIcon() override;

      virtual void CheckDlgButton(i32 nIDButton, UINT nCheck) override;
      virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton) override;
      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton) override;
      virtual i32 DlgDirList(LPTSTR lpPathSpec, i32 nIDListBox,
                             i32 nIDStaticPath, UINT nFileType) override;
      virtual i32 DlgDirListComboBox(LPTSTR lpPathSpec, i32 nIDComboBox,
                                     i32 nIDStaticPath, UINT nFileType) override;
      virtual bool DlgDirSelect(LPTSTR lpString, i32 nSize, i32 nIDListBox) override;
      virtual bool DlgDirSelectComboBox(LPTSTR lpString, i32 nSize, i32 nIDComboBox) override;

      //virtual UINT GetChildByIdInt(i32 nID, bool * lpTrans = nullptr, bool bSigned = TRUE) const;
      //virtual i32 GetChildByIdText(i32 nID, LPTSTR lpStr, i32 nMaxCount) const;
      //virtual i32 GetChildByIdText(i32 nID, string & rectString) const;
      virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const ;
      virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const ;
      virtual UINT IsDlgButtonChecked(i32 nIDButton) const override;
      virtual LRESULT SendDlgItemMessage(i32 nID, const ::id & id, WPARAM wParam = 0, LPARAM lParam = 0) override;
      virtual void SetDlgItemInt(i32 nID, UINT nValue, bool bSigned = TRUE) override;
      virtual void SetDlgItemText(i32 nID, const char * lpszString) override;

      // Scrolling Functions
      virtual i32 GetScrollPos(i32 nBar) const override;
      virtual void GetScrollRange(i32 nBar, LPINT lpMinPos, LPINT lpMaxPos) const override;
//      virtual void ScrollWindow(i32 xAmount, i32 yAmount,
//                                const ::rect & rect = nullptr,
//                                LPCRECT lpClipRect = nullptr) override;
      virtual i32 SetScrollPos(i32 nBar, i32 nPos, bool bRedraw = TRUE) override;
      virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos,
                                  bool bRedraw = TRUE) override;
      virtual void ShowScrollBar(UINT nBar, bool bShow = TRUE) override;
      virtual void EnableScrollBarCtrl(i32 nBar, bool bEnable = TRUE) override;
      //      virtual CScrollBar* GetScrollBarCtrl(i32 nBar) const;
      // return sibling scrollbar control (or nullptr if none)

//      virtual i32 ScrollWindowEx(i32 dx, i32 dy,
//                                 const ::rect & rectScroll, const ::rect & rectClip,
//                                 ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags) override;
      //xxx      virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo,
      //xxx         bool bRedraw = TRUE);
      //xxx      virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo, UINT nMask = SIF_ALL);
      virtual i32 GetScrollLimit(i32 nBar) override;

#if(WINVER >= 0x0500)

      virtual bool GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;

#endif   // WINVER >= 0x0500

      // oswindow Access Functions
//      virtual ::user::interaction *  child_window_from_point(POINT point) override;
  //    virtual ::user::interaction *  ChildWindowFromPoint(POINT point, UINT nFlags) override;
      static ::user::interaction * PASCAL FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static ::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual ::user::interaction *  GetNextWindow(UINT nFlag = GW_HWNDNEXT);
      virtual ::user::interaction *  GetTopWindow() override;

      virtual ::user::interaction *  GetWindow(UINT nCmd);
      virtual ::user::interaction *  GetLastActivePopup() override;

      //virtual bool IsChild(::user::interaction *    pWnd);
      virtual ::user::interaction * GetParent() const override;
      using ::user::interaction_impl::SetParent;
      ::user::interaction * SetParent(::user::interaction * pWndNewParent) override;
      static ::user::interaction * PASCAL oswindowFromPoint(POINT point);

      // Alert Functions

      bool FlashWindow(bool bInvert);

//      virtual i32 message_box(const char * lpszText, const char * lpszCaption = nullptr, UINT nType = MB_OK) override;


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD tickTimeout);

#endif   // WINVER >= 0x0500

      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow hWndNext) override;
      virtual oswindow  SetClipboardViewer() override;
      virtual bool OpenClipboard() override;
      static ::user::interaction * PASCAL GetClipboardOwner();
      static ::user::interaction * PASCAL GetClipboardViewer();
      static ::user::interaction * PASCAL GetOpenClipboardWindow();

      // Caret Functions
      static point PASCAL GetCaretPos();
      static void PASCAL SetCaretPos(POINT point);
      virtual void HideCaret() override;
      virtual void ShowCaret() override;

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = TRUE) override;

      // icon Functions
      //      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
      //      virtual HICON GetIcon(bool bBigIcon) const;

      // Context Help Functions
      virtual bool SetWindowContextHelpId(DWORD dwContextHelpId) override;
      virtual DWORD GetWindowContextHelpId() const override;

      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = TRUE);
      // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING


      void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler) override;
      void CenterWindow(::user::interaction *   pAlternateOwner = nullptr) override;

      // oswindow-Management message handler member functions
      virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
      virtual bool OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      void OnActivate(UINT nState, ::user::interaction * pWndOther, bool bMinimized);
      void OnActivateApp(bool bActive, DWORD dwThreadID);
      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      void OnCancelMode();
      void OnChildActivate();
      void OnClose();
      void OnContextMenu(::user::interaction * pWnd, point pos);
      bool OnCopyData(::user::interaction * pWnd, COPYDATASTRUCT* pCopyDataStruct);


      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction * pWnd, UINT nCtlColor);

      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      void OnEnterIdle(UINT nWhy, ::user::interaction * pWho);
      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      //xxx bool OnHelpInfo(HELPINFO* lpHelpInfo);
      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::user::menu* pMenu);
      void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      void OnMove(i32 x, i32 y);



      void OnParentNotify(const ::id & id, LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::user::interaction * pOldWnd);
      void OnShowWindow(bool bShow, UINT nStatus);
      void OnSize(UINT nType, i32 cx, i32 cy);
      void OnTCard(UINT idAction, DWORD dwActionData);
      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
      void OnWindowPosChanged(WINDOWPOS* lpwndpos);

      void OnChangeUIState(UINT nAction, UINT nUIElement);
      void OnUpdateUIState(UINT nAction, UINT nUIElement);
      UINT OnQueryUIState();

      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(::user::create_struct * lpCreateStruct);
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
      void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysCommand(UINT nID, LPARAM lParam);
      void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      void OnCompacting(UINT nCpuTime);
      void OnDevModeChange(LPTSTR lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::user::interaction * pFocusWnd);
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
      i32 OnMouseActivate(::user::interaction * pDesktopWnd, UINT nHitTest, const ::id & id);
      void OnMouseMove(UINT nFlags, const ::point & point);
      bool OnMouseWheel(UINT nFlags, short zDelta, const ::point & point);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      void OnRButtonDblClk(UINT nFlags, const ::point & point);
      void OnRButtonDown(UINT nFlags, const ::point & point);
      void OnRButtonUp(UINT nFlags, const ::point & point);
      void OnTimer(uptr uEvent);

      // Initialization message handler member functions
      void OnInitMenu(::user::menu* pMenu);
      void OnInitMenuPopup(::user::menu* pPopupMenu, UINT nIndex, bool bSysMenu);

      // Clipboard message handler member functions
      void OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString);
      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::user::interaction * pClipAppWnd, UINT nSBCode, UINT nPos);
      void OnPaintClipboard(::user::interaction * pClipAppWnd, HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(UINT nFormat);
      void OnSizeClipboard(::user::interaction * pClipAppWnd, HGLOBAL hRect);
      void OnVScrollClipboard(::user::interaction * pClipAppWnd, UINT nSBCode, UINT nPos);

      // control message handler member functions
      //xxx      i32 OnCompareItem(i32 nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //xxx      void OnDeleteItem(i32 nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //xxx      void OnDrawItem(i32 nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
      UINT OnGetDlgCode();
      //xxx      void OnMeasureItem(i32 nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

      // MDI message handler member functions
      void OnMDIActivate(bool bActivate,
                         ::user::interaction * pActivateWnd, ::user::interaction * pDeactivateWnd);

      // menu loop notification messages
      void OnEnterMenuLoop(bool bIstrack_popup_menu);
      void OnExitMenuLoop(bool bIstrack_popup_menu);

      // Win4 messages
      //xxx      void OnStyleChanged(i32 nStyleType, LPSTYLESTRUCT lpStyleStruct);
      //xxx      void OnStyleChanging(i32 nStyleType, LPSTYLESTRUCT lpStyleStruct);
      void OnSizing(UINT nSide, LPRECT lpRect);
      void OnMoving(UINT nSide, LPRECT lpRect);
      void OnCaptureChanged(::user::interaction * pWnd);
      bool OnDeviceChange(UINT nEventType, uptr dwData);

      DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnProdevianSynch);
      DECL_GEN_SIGNAL(_001OnDestroy);

      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      DECL_GEN_SIGNAL(_001OnCaptureChanged);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);

      //virtual void prodevian_task() override;

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      // xxx      virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState() override;
      virtual void EndModalState() override;

      // for translating oswindows messages in main message pump
      virtual void pre_translate_message(::message::message * pmessage) override;


      // for processing oswindows messages
      virtual void message_handler(::message::base * pbase) override;
      //virtual bool OnWndMsg(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
//      LRESULT Default() override;
  //    virtual LRESULT DefWindowProc(const ::id & id, WPARAM wParam, ::lparam lParam) override;

      virtual void PostNcDestroy() override;

      // for notifications from parent
      virtual bool OnChildNotify(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      // return TRUE if parent should not process this message
      bool ReflectChildNotify(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
      static bool PASCAL ReflectLastMsg(oswindow hWndChild, LRESULT* pResult = nullptr);

      virtual bool CheckAutoCenter() override;
      static bool PASCAL GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
                                      HBRUSH hbrGray, COLORREF clrText);


      // helper routines for implementation
      bool HandleFloatingSysCommand(UINT nID, LPARAM lParam) override;
      bool IsTopParentActive() override;
      void ActivateTopParent() override;
      virtual void WalkPreTranslateTree(::user::interaction *, ::message::message * pmessage);
      virtual bool IsFrameWnd(); // is_kind_of(__type(frame_window)))
      virtual void on_final_release() override;
//      static bool PASCAL ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      //    static bool PASCAL ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
      static void PASCAL _FilterToolTipMessage(MESSAGE* pMsg, ::user::interaction * pWnd);
      bool _EnableToolTips(bool bEnable, UINT nFlag) override;
      static oswindow PASCAL GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp() override;


      bool CreateDlg(const char * lpszTemplateName, ::user::interaction * puiParent);


      CLASS_DECL_AXIS friend LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
      CLASS_DECL_AXIS friend LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);
      CLASS_DECL_AXIS friend LRESULT __call_window_procedure(::user::interaction *   pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM, LPARAM);
      LRESULT OnDragList(WPARAM, LPARAM);

      static bool CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lParam);


      static void get_app_wnda(user::oswindow_array & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      virtual LONG GetWindowLong(i32 nIndex);
      virtual LONG SetWindowLong(i32 nIndex, LONG lValue);

      virtual void _001BaseWndInterfaceMap() override;


      //void _001UpdateWindow(bool bUpdateBuffer) override;
      //void _001UpdateWindow() override;
      void _001UpdateScreen() override;


      void _001OnTriggerMouseInside() override;

      void _001OnTimer(::timer * ptimer) override;

      virtual int round_window_get_x() override;
      virtual int round_window_get_y() override;

      
      virtual void round_window_become_key() override;

      virtual bool round_window_key_down(::user::e_key ekey) override;
      virtual bool round_window_key_up(::user::e_key ekey) override;
      virtual bool round_window_on_text(const char * pszText, long iSelBeg, long iSelEnd) override;
      virtual bool round_window_on_sel_text(long iBeg, long iEnd) override;
      virtual long round_window_edit_hit_test(int x, int y) override;
      virtual bool round_window_edit_caret_rect(CGRect * prect, long iSel) override;
      
      
      virtual void round_window_resized(int cx, int cy) override;
      virtual void round_window_moved(CGPoint point) override;


      virtual void round_window_on_show() override;
      virtual void round_window_on_hide() override;

      virtual void round_window_activate() override;
      virtual void round_window_deactivate() override;


      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd) override;


      virtual bool has_pending_graphical_update() override;
      

   };


} // namespace ios




