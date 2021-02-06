#pragma once


#include "aura/user/interaction.h"
#include "aura/user/interaction_impl.h"
#include "apex/node/macos/apex_window.h"


namespace macos
{


   CLASS_DECL_AURA LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
   CLASS_DECL_AURA LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);
   CLASS_DECL_AURA LRESULT __call_window_procedure(::user::interaction *   pWnd, oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);


   class CLASS_DECL_AURA interaction_impl :
      virtual public ::user::interaction_impl,
      virtual public ::apex_window
   {
   public:


      string                           m_strWindowText;
      ::user::primitive *              m_pbasewnd;
      bool                             m_bNeedsUpdate;
      rectangle_i64                           m_rectLastOsPlacement;
      bool                             m_bEnabled;
      millis                             m_millisLastAuraWindowDraw;


      interaction_impl();
      interaction_impl(::layered * pobjectContext);
      virtual ~interaction_impl();


      virtual void construct(oswindow hwnd);


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
      
      virtual void set_destroying() override;

      inline bool is_destroying() const { return ::apex_window::m_bDestroying || ::user::interaction_impl::m_bDestroying; }

      virtual void release_graphics_resources();
      
      virtual ::e_status update_graphics_resources() override;


      //virtual bool create_message_queue(::user::interaction * pinteraction, const char * pszName) override;

      static const MESSAGE* PASCAL GetCurrentMessage();
      virtual void install_message_routing(::channel * pchannel) override;


      ::u32 GetStyle() const override;
      ::u32 GetExStyle() const override;
      bool ModifyStyle(::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags = 0) override;
      bool ModifyStyleEx(::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags = 0) override;


      virtual ::user::interaction *  SetOwner(::user::interaction *   pOwnerWnd) override;

      virtual ::user::interaction * get_wnd() const override;

      virtual void route_command_message(::user::command * pcommand) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      void _002OnDraw(::image * pimage);


      virtual bool has_focus() override;
      virtual bool is_active() override;

      //DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnProdevianSynch);

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


      virtual void on_show_window() override;
      virtual void on_reposition() override;
      virtual void on_zorder();
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
      bool SubclassWindow(oswindow hWnd);
      //bool SubclassDlgItem(::u32 nID, ::interaction_impl * pParent);
      oswindow UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      bool ExecuteDlgInit(const char * lpszResourceName) override;
      bool ExecuteDlgInit(LPVOID lpResource) override;

      using ::user::interaction_impl::create_window;
      
      virtual bool ShowWindow(int iShow) override;
      //// for child windows, views, panes etc
      
      virtual bool create_window(::user::interaction * pinteraction, const char * lpszClassName, const char * lpszWindowName, u32 uStyle, const ::rectangle_i32 & prectangle, ::user::interaction * puiParent, id id, ::create * pcreate = nullptr) override;
      


      // advanced creation (allows access to extended styles)
      virtual bool create_window_ex(
      ::user::interaction * pinteraction,
      __pointer(::user::system) pusersystem,
      ::user::interaction * puiParent,
      id id) override;

      virtual bool _native_create_window_ex(__pointer(::user::system) pusersystem) override;

      virtual bool DestroyWindow() override;

      // special pre-creation and ::interaction_impl rectangle_i32 adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem) override;

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(RECTANGLE_I32 * lpClientRect, ::u32 nAdjustType = adjustBorder) override;



      virtual bool _is_window() const override;

#if(WINVER >= 0x0500)

      ::interaction_impl * GetAncestor(::u32 gaFlags) const;

#endif   // WINVER >= 0x0500

      LRESULT send_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0) override;
      bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0) override;

//      bool SendNotifyMessage(const ::id & id, WPARAM wParam, LPARAM lParam);
//      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);
//
//      bool DragDetect(const ::point_i32 & point) const override;



      // oswindow Text Functions
      void set_window_text(const char * lpszString) override;
      //strsize GetWindowText(char * lpszStringBuf, strsize nMaxCount);
      void get_window_text(string & str) override;
      //strsize GetWindowTextLength();
//      void SetFont(::draw2d::font* pFont, bool bRedraw = true);
      //    ::draw2d::font* GetFont();


      // oswindow size_i32 and position Functions
      virtual bool window_impl_is_iconic();
      //virtual bool window_impl_is_zoomed();
//      void MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight,
//                      bool bRepaint = true);
//      void MoveWindow(const ::rectangle_i32 & rectangle, bool bRepaint = true);
      i32 SetWindowRgn(HRGN hRgn, bool bRedraw);
      i32 GetWindowRgn(HRGN hRgn);


      //virtual bool set_window_pos(iptr z, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags);
      virtual ::u32 ArrangeIconicWindows() override;
      //virtual void BringToTop(::e_display edisplay) override;
      //virtual bool BringWindowToTop() override;
//      using ::user::interaction_impl::get_window_rect;
//      virtual bool get_window_rect(RECTANGLE_I64 * lpRect) override;
//      using ::user::interaction_impl::get_client_rect;
//      virtual bool get_client_rect(RECTANGLE_I64 * lpRect) override;

      //virtual point_f64 client_screen_top_left() override;
//        virtual bool _001ClientToScreen(RECTANGLE_I32 * lprect) override;
//        virtual bool _001ClientToScreen(POINT_I32 * lppoint) override;
//        virtual bool _001ClientToScreen(RECTANGLE_I64 * lprect) override;
//        virtual bool _001ClientToScreen(POINT_I64 * lppoint) override;
//        virtual bool _001ScreenToClient(RECTANGLE_I32 * lprect) override;
//        virtual bool _001ScreenToClient(POINT_I32 * lppoint) override;
//        virtual bool _001ScreenToClient(RECTANGLE_I64 * lprect) override;
//        virtual bool _001ScreenToClient(POINT_I64 * lppoint) override;

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);

      //virtual void MapWindowPoints(::user::interaction * pwndTo, POINT_I32 * lpPoint, ::u32 nCount);
      //virtual void MapWindowPoints(::user::interaction * pwndTo, RECTANGLE_I32 * lpRect);

      //virtual ::draw2d::graphics * GetDC();
      //virtual ::draw2d::graphics * GetWindowDC();
      //virtual bool ReleaseDC(::draw2d::graphics_pointer & pgraphics);
      //virtual void Print(::draw2d::graphics_pointer & pgraphics, ::u32 dwFlags) const override;
      //virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, ::u32 dwFlags) const override;

      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = true) override;
      virtual bool GetUpdateRect(RECTANGLE_I32 * lpRect, bool bErase = false) override;
      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false) override;
      virtual void Invalidate(bool bErase = true) override;
      virtual void InvalidateRect(const ::rectangle_i32 &rectangle, bool bErase = true) override;
      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true) override;
      virtual void ValidateRect(const ::rectangle_i32 & rectangle) override;
      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      //virtual bool display(::e_display edisplay) override;
//      virtual void window_impl_maximize();
//      virtual void window_impl_restore();
      //virtual bool window_impl_is_visible();
      virtual void ShowOwnedPopups(bool bShow = true) override;


      virtual void round_window_add_ref() override;
      virtual void round_window_dec_ref() override;


      virtual void round_window_draw(CGContextRef cgc, CGSize sizeWindow) override;
      virtual void round_window_mouse_down(int iButton, double x, double y) override;
      virtual void round_window_mouse_up(int iButton, double x, double y) override;
      virtual void round_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton) override;
      virtual void round_window_mouse_dragged(double x, double y, unsigned long iAppleMouseButton) override;
      virtual void round_window_mouse_wheel(double deltaY, double x, double y) override;
      virtual void round_window_double_click(int iButton, double x, double y) override;
      virtual bool round_window_key_down(unsigned int vk, unsigned int scan, const char * pszUtf8) override;
      virtual bool round_window_key_up(unsigned int vk, unsigned int scan) override;
      virtual bool round_window_key_down(unsigned int uiKeyCode) override;
      virtual bool round_window_key_up(unsigned int uiKeyCode) override;


      virtual void round_window_did_become_key() override;
      virtual void round_window_activate() override;
      virtual void round_window_deactivate() override;


      virtual void round_window_resized(CGRect rectangle_i32) override;
      virtual void round_window_moved(CGPoint point_i32) override;
      virtual void round_window_iconified() override;
      virtual void round_window_deiconified() override;





      virtual void round_window_on_show() override;
      virtual void round_window_on_hide() override;
      virtual void round_window_on_miniaturize() override;


      void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;
      void offset_viewport_org(RECTANGLE_I32 * lprectScreen);


      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, ::u32 flags) override;
      virtual bool LockWindowUpdate() override;
      virtual void UnlockWindowUpdate() override;
//        virtual bool RedrawWindow(const ::rectangle_i32 & rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr, ::u32 flags = RDW_INVALIDATE | RDW_ERASE);
      virtual void _001UpdateScreen() override;
      //virtual votru8id _001UpdateWindow(bool bUpdateBuffer = false) override;
      // xxx      virtual bool EnableScrollBar(i32 nSBFlags, ::u32 nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(i32 idAni, const RECTANGLE_I32 *lprcFrom, const RECTANGLE_I32 *lprcTo) override;
      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::u32 uFlags) override;

#if(WINVER >= 0x0500)

      virtual bool AnimateWindow(::u32 millis, ::u32 dwFlags);

#endif   // WINVER >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, ::u32 nFlags) const;

#endif   // _WIN32_WINNT >= 0x0501

      // Layered oswindow



      // Timer Functions
      virtual bool SetTimer(uptr uEvent, ::u32 nElapse, PFN_TIMER pfnTimer) override;
      virtual bool KillTimer(uptr uEvent) override;

      // oswindow State Functions
      virtual bool IsWindowEnabled();
      virtual bool enable_window(bool bEnable = true) override;

      virtual ::user::interaction *  GetActiveWindow() override;
      virtual ::user::interaction *  SetActiveWindow() override;

      virtual bool SetForegroundWindow() override;
      static ::user::interaction * PASCAL GetForegroundWindow();

      virtual id SetDlgCtrlId(id id) override;
      virtual id GetDlgCtrlId();



      //virtual ::user::interaction *  GetCapture();
//       virtual ::user::interaction *  SetCapture(::user::interaction *   pinterface = nullptr);
      //     virtual ::user::interaction *  ReleaseCapture();
      virtual ::user::interaction *  GetFocus() override;
      bool  SetFocus() override;

      virtual ::user::interaction *  get_desktop_window();

      virtual void CloseWindow() override;
      virtual bool OpenIcon() override;

      virtual void CheckDlgButton(i32 nIDButton, ::u32 nCheck) override;
      virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton) override;
      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton) override;
      virtual i32 DlgDirList(char * lpPathSpec, i32 nIDListBox,
                             i32 nIDStaticPath, ::u32 nFileType) override;
      virtual i32 DlgDirListComboBox(char * lpPathSpec, i32 nIDComboBox,
                                     i32 nIDStaticPath, ::u32 nFileType) override;
      virtual bool DlgDirSelect(char * lpString, i32 nSize, i32 nIDListBox) override;
      virtual bool DlgDirSelectComboBox(char * lpString, i32 nSize, i32 nIDComboBox) override;

      //virtual ::u32 GetChildByIdInt(i32 nID, bool * lpTrans = nullptr, bool bSigned = true) const;
      //virtual i32 GetChildByIdText(i32 nID, char * lpStr, i32 nMaxCount) const;
      //virtual i32 GetChildByIdText(i32 nID, string & rectString) const;
      virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      virtual ::u32 IsDlgButtonChecked(i32 nIDButton) const override;
      virtual LRESULT SendDlgItemMessage(i32 nID, const ::id & id, WPARAM wParam = 0, LPARAM lParam = 0) override;
      virtual void SetDlgItemInt(i32 nID, ::u32 nValue, bool bSigned = true) override;
      virtual void SetDlgItemText(i32 nID, const char * lpszString) override;

      // Scrolling Functions
      virtual i32 GetScrollPos(i32 nBar) const override;
      virtual void GetScrollRange(i32 nBar, LPINT lpMinPos, LPINT lpMaxPos) const override;
      virtual void ScrollWindow(i32 xAmount, i32 yAmount,
                                const RECTANGLE_I32 * prectangle = nullptr,
                                const RECTANGLE_I32 * lpClipRect = nullptr) override;
      virtual i32 SetScrollPos(i32 nBar, i32 nPos, bool bRedraw = true) override;
      virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos,
                                  bool bRedraw = true) override;
      virtual void ShowScrollBar(::u32 nBar, bool bShow = true) override;
      virtual void EnableScrollBarCtrl(i32 nBar, bool bEnable = true) override;
//      virtual CScrollBar* GetScrollBarCtrl(i32 nBar) const;
      // return sibling scrollbar control (or nullptr if none)

      virtual i32 ScrollWindowEx(i32 dx, i32 dy,
                                 const RECTANGLE_I32 * prectScroll, const RECTANGLE_I32 * lprectClip,
                                 ::draw2d::region* prgnUpdate, RECTANGLE_I32 * lpRectUpdate, ::u32 flags) override;
      //xxx      virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo,
      //xxx         bool bRedraw = true);
      //xxx      virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO lpScrollInfo, ::u32 nMask = SIF_ALL);
      virtual i32 GetScrollLimit(i32 nBar) override;

#if(WINVER >= 0x0500)

      virtual bool GetScrollBarInfo(::i32 idObject, PSCROLLBARINFO psbi) const;

#endif   // WINVER >= 0x0500

      // oswindow Access Functions
      virtual ::user::interaction *  ChildWindowFromPoint(const ::point_i32 & point) override;
      virtual ::user::interaction *  ChildWindowFromPoint(const ::point_i32 & point, ::u32 nFlags) override;
      static ::user::interaction * PASCAL FindWindow(const char * lpszClassName, const char * lpszWindowName);
      static ::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual ::user::interaction *  GetNextWindow(::u32 nFlag = GW_HWNDNEXT);
      virtual ::user::interaction *  GetTopWindow() override;

      virtual ::user::interaction *  GetWindow(::u32 nCmd);
      virtual ::user::interaction *  GetLastActivePopup() override;

      virtual bool IsChild(::user::interaction *    pWnd);
      virtual ::user::interaction * get_parent() const override;
      using ::user::interaction_impl::SetParent;
      ::user::interaction * SetParent(::user::interaction * pWndNewParent) override;
      static ::user::interaction * PASCAL oswindowFromPoint(POINT_I32 point_i32);

      // Alert Functions

      bool FlashWindow(bool bInvert);

      //virtual i32 message_box(const char * lpszText, const char * lpszCaption = nullptr, ::u32 nType = e_message_box_ok) override;


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(::u32 dwFlags, ::u32  uCount, ::u32 tickTimeout);

#endif   // WINVER >= 0x0500

      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow hWndNext) override;
      virtual oswindow  SetClipboardViewer() override;
      virtual bool OpenClipboard() override;
      static ::user::interaction * PASCAL GetClipboardOwner();
      static ::user::interaction * PASCAL GetClipboardViewer();
      static ::user::interaction * PASCAL GetOpenClipboardWindow();

      // Caret Functions
      static point_i32 PASCAL GetCaretPos();
      static void PASCAL SetCaretPos(POINT_I32 point_i32);
      virtual void HideCaret() override;
      virtual void ShowCaret() override;

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = true) override;

      // icon Functions
//      virtual HICON SetIcon(HICON hIcon, bool bBigIcon);
//      virtual HICON GetIcon(bool bBigIcon) const;

      // Context Help Functions
      virtual bool SetWindowContextHelpId(::u32 dwContextHelpId) override;
      virtual ::u32 GetWindowContextHelpId() const override;

      // Dialog Data support
      //virtual bool update_data(bool bSaveAndValidate = true);
      // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING

      void UpdateDialogControls(channel * pTarget, bool bDisableIfNoHndler) override;
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;

      void OnActivate(::u32 nState, ::user::interaction * pWndOther, bool bMinimized);
//      void OnActivateApp(bool bActive, ::u32 dwThreadID);
//      LRESULT OnActivateTopLevel(WPARAM, LPARAM);
//      void OnCancelMode();
//      void OnChildActivate();
//      void OnClose();
//      void OnContextMenu(::user::interaction * pWnd, point_i32 pos);
//      bool OnCopyData(::user::interaction * pWnd, COPYDATASTRUCT* pCopyDataStruct);


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);


      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction * pWnd, ::u32 nCtlColor);

      DECL_GEN_SIGNAL(_001OnDestroy);
//      void OnEnable(bool bEnable);
//      void OnEndSession(bool bEnding);
//      void OnEnterIdle(::u32 nWhy, ::user::interaction * pWho);
//      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
//      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//      //xxx bool OnHelpInfo(HELPINFO* lpHelpInfo);
//      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
//      void OnKillFocus(::user::interaction * pNewWnd);
//      LRESULT OnMenuChar(::u32 nChar, ::u32 nFlags, ::user::menu* pMenu);
//      void OnMenuSelect(::u32 nItemID, ::u32 nFlags, HMENU hSysMenu);
//      void OnMove(i32 x, i32 y);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
//      void OnParentNotify(const ::id & id, LPARAM lParam);
//      HCURSOR OnQueryDragIcon();
//      bool OnQueryEndSession();
//      bool OnQueryNewPalette();
//      bool OnQueryOpen();
//      void OnSetFocus(::user::interaction * pOldWnd);
//      void OnShowWindow(bool bShow, ::u32 nStatus);
//      void OnSize(::u32 nType, i32 cx, i32 cy);
//      void OnTCard(::u32 idAction, ::u32 dwActionData);
//      void OnWindowPosChanging(WINDOWPOS* lpwndpos);
//      void OnWindowPosChanged(WINDOWPOS* lpwndpos);
//
//      void OnChangeUIState(::u32 nAction, ::u32 nUIElement);
//      void OnUpdateUIState(::u32 nAction, ::u32 nUIElement);
//      ::u32 OnQueryUIState();

      // Nonclient-Area message handler member functions
//      bool OnNcActivate(bool bActive);
//      void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
//      bool OnNcCreate(::user::system * lpCreateStruct);

//      LRESULT OnNcHitTest(::point_i32 point);
//      void OnNcLButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcLButtonDown(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcLButtonUp(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcMButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcMButtonDown(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcMButtonUp(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcMouseMove(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcPaint();
//      void OnNcRButtonDblClk(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcRButtonDown(::u32 nHitTest, const ::point_i32 & point);
//      void OnNcRButtonUp(::u32 nHitTest, const ::point_i32 & point);

      // System message handler member functions
//      void OnDropFiles(HDROP hDropInfo);
//      void OnPaletteIsChanging(::user::interaction * pRealizeWnd);
//      void OnSysChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnSysCommand(::u32 nID, LPARAM lParam);
//      void OnSysDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnSysKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnSysKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnCompacting(::u32 nCpuTime);
//      void OnDevModeChange(char * lpDeviceName);
//      void OnFontChange();
//      void OnPaletteChanged(::user::interaction * pFocusWnd);
//      void OnSpoolerStatus(::u32 nStatus, ::u32 nJobs);
//      void OnSysColorChange();
//      void OnTimeChange();
//      void OnSettingChange(::u32 uFlags, const char * lpszSection);
//      void OnWinIniChange(const char * lpszSection);

//      // Input message handler member functions
//      void OnChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnDeadChar(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
////      void OnHScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
//      //    void OnVScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
//      void OnKeyDown(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnKeyUp(::u32 nChar, ::u32 nRepCnt, ::u32 nFlags);
//      void OnLButtonDblClk(::u32 nFlags, const ::point_i32 & point);
//      void OnLButtonDown(::u32 nFlags, const ::point_i32 & point);
//      void OnLButtonUp(::u32 nFlags, const ::point_i32 & point);
//      void OnMButtonDblClk(::u32 nFlags, const ::point_i32 & point);
//      void OnMButtonDown(::u32 nFlags, const ::point_i32 & point);
//      void OnMButtonUp(::u32 nFlags, const ::point_i32 & point);
//      i32 OnMouseActivate(::user::interaction * pDesktopWnd, ::u32 nHitTest, const ::id & id);
//      void OnMouseMove(::u32 nFlags, const ::point_i32 & point);
//      bool OnMouseWheel(::u32 nFlags, short zDelta, const ::point_i32 & point);
//      LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
//      void OnRButtonDblClk(::u32 nFlags, const ::point_i32 & point);
//      void OnRButtonDown(::u32 nFlags, const ::point_i32 & point);
//      void OnRButtonUp(::u32 nFlags, const ::point_i32 & point);
//      DECL_GEN_SIGNAL(_001OnSetCursor);
//      void OnTimer(uptr uEvent);

      // Initialization message handler member functions
//      void OnInitMenu(::user::menu* pMenu);
//      void OnInitMenuPopup(::user::menu* pPopupMenu, ::u32 nIndex, bool bSysMenu);

      // Clipboard message handler member functions
//      void OnAskCbFormatName(::u32 nMaxCount, char * lpszString);
//      void OnChangeCbChain(oswindow hWndRemove, oswindow hWndAfter);
//      void OnDestroyClipboard();
//      void OnDrawClipboard();
//      void OnHScrollClipboard(::user::interaction * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);
//      void OnPaintClipboard(::user::interaction * pClipAppWnd, HGLOBAL hPaintStruct);
//      void OnRenderAllFormats();
//      void OnRenderFormat(::u32 nFormat);
//      void OnSizeClipboard(::user::interaction * pClipAppWnd, HGLOBAL hRect);
//      void OnVScrollClipboard(::user::interaction * pClipAppWnd, ::u32 nSBCode, ::u32 nPos);

      // control message handler member functions
      //xxx      i32 OnCompareItem(i32 nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //xxx      void OnDeleteItem(i32 nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //xxx      void OnDrawItem(i32 nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//      ::u32 OnGetDlgCode();
      //xxx      void OnMeasureItem(i32 nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

      // MDI message handler member functions
//      void OnMDIActivate(bool bActivate,
//                         ::user::interaction * pActivateWnd, ::user::interaction * pDeactivateWnd);

      // menu loop notification messages
//      void OnEnterMenuLoop(bool bIstrack_popup_menu);
//      void OnExitMenuLoop(bool bIstrack_popup_menu);

      // Win4 messages
      //xxx      void OnStyleChanged(i32 nStyleType, LPSTYLESTRUCT lpStyleStruct);
      //xxx      void OnStyleChanging(i32 nStyleType, LPSTYLESTRUCT lpStyleStruct);
//      void OnSizing(::u32 nSide, RECTANGLE_I32 * lpRect);
//      void OnMoving(::u32 nSide, RECTANGLE_I32 * lpRect);
//      void OnCaptureChanged(::user::interaction * pWnd);
//      bool OnDeviceChange(::u32 nEventType, uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      // xxx      virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
//      virtual void BeginModalState() override;
//      virtual void EndModalState() override;

      // for translating oswindows messages in main message pump
      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void default_message_handler(::message::message * pmessage) override;

      // for processing oswindows messages
      virtual void message_handler(::message::base * pbase) override;
      //virtual bool OnWndMsg(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
//      LRESULT Default() override;
//      virtual LRESULT DefWindowProc(const ::id & id, WPARAM wParam, LPARAM lParam);

      virtual void PostNcDestroy() override;

      // for notifications from parent
//      virtual bool OnChildNotify(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
//      // return true if parent should not process this message
//      bool ReflectChildNotify(const ::id & id, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
//      static bool PASCAL ReflectLastMsg(oswindow hWndChild, LRESULT* pResult = nullptr);

//      virtual bool CheckAutoCenter() override;
//      static bool PASCAL GrayCtlColor(HDC hDC, oswindow hWnd, ::u32 nCtlColor,
//                                      HBRUSH hbrGray, color32_t clrText);


      // helper routines for implementation
//      bool HandleFloatingSysCommand(::u32 nID, LPARAM lParam) override;
//      bool IsTopParentActive() override;
//      void ActivateTopParent() override;
//      virtual void WalkPreTranslateTree(::user::interaction *   puiStop, ::message::message * pmessage);
//      virtual bool IsFrameWnd(); // is_kind_of(__type(frame_window)))
//      virtual void on_final_release() override;

      static bool ModifyStyle(oswindow hWnd, ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags);
      static bool ModifyStyleEx(oswindow hWnd, ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags);
      
//      static void PASCAL _FilterToolTipMessage(MESSAGE* pMsg, ::user::interaction * pWnd);
//      bool _EnableToolTips(bool bEnable, ::u32 nFlag) override;
//      static oswindow PASCAL GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
//      void PrepareForHelp() override;

      //::u32 m_nFlags;      // see WF_ flags above

      // xxx      WNDPROC m_pfnSuper; // for subclassing of controls
//      static const ::u32 m_nMsgDragList;
//      i32 m_nModalResult; // for return values from ::interaction_impl::RunModalLoop

//      ::draw2d::font * m_pfont;

      friend class frame_window;

      // for creating dialogs and dialog-like windows
//      bool CreateDlg(const char * lpszTemplateName, ::user::interaction * puiParent);
      //bool CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate, ::interaction_impl * puiParent,
      // HINSTANCE hInst);


      // implementation of message dispatch/hooking
//      CLASS_DECL_AURA friend LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
//      CLASS_DECL_AURA friend LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);
//      CLASS_DECL_AURA friend LRESULT __call_window_procedure(::user::interaction *   pWnd, oswindow hWnd, ::u32 nMsg, WPARAM wParam, LPARAM lParam);

      // standard message implementation
//      LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
//      LRESULT OnDisplayChange(WPARAM, LPARAM);
//      LRESULT OnDragList(WPARAM, LPARAM);

      static bool CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lParam);


      static void get_app_wnda(user::oswindow_array & wnda);

//      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      virtual ::i32 GetWindowLong(i32 nIndex);
      virtual ::i32 SetWindowLong(i32 nIndex, ::i32 lValue);

//      virtual void _001BaseWndInterfaceMap() override;


      void _001WindowMinimize();

      void _001OnTriggerMouseInside() override;

      void _001OnTimer(::timer * ptimer) override;

      virtual void _thread_prodevian();

//      virtual bool set_window_pos(class ::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags) override;

      virtual void show_task(bool bShow) override;

      //virtual void ns_main_async(dispatch_block_t block) override;

      //virtual void _001ApplyVisual() override;
      
      virtual void window_show_change_visibility();
      
      
   };


} // namespace macos



