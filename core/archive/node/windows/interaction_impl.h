#pragma once


#include <Shobjidl.h>
#include <Shellapi.h>



namespace windows
{


   //CLASS_DECL_AURA LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
   //CLASS_DECL_AURA LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);


   class CLASS_DECL_AURA interaction_impl :
      virtual public ::user::interaction_impl,
      virtual public IDropTarget
   {
   public:

      bool                                      m_bFocusImpl;
      bool                                      m_bSystemCaret;

      ::rect                                    m_rectLast;

      bool                                      m_bUpdateGraphics;

      size                                      m_size;

      point                                     m_point;

      ::user::primitive *                m_pbasewnd;

      u32                                       m_uiLastRedrawRequest;

      IDropTargetHelper *                       m_piDropHelper;

      bool                                      m_bUseDnDHelper;

      WNDPROC                                   m_pfnSuper;          // for subclassing of controls

      edisplay                                  m_edisplayLayout;
      rect64                                    m_rectLastPos;
      tick                                      m_tickLastPos;
      string                                    m_strDebug;

      ::point                                   m_pointCursor;



      


      interaction_impl();
      interaction_impl(::object * pobject);
      virtual ~interaction_impl();


      void user_common_construct();

      //virtual bool set_window_pos(::user::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags = SWP_SHOWWINDOW) override;

      virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

      virtual ULONG STDMETHODCALLTYPE AddRef(void);

      virtual ULONG STDMETHODCALLTYPE Release(void);

      virtual HRESULT STDMETHODCALLTYPE DragEnter(
      /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
      /* [in] */ DWORD grfKeyState,
      /* [in] */ POINTL point,
      /* [out][in] */ __RPC__inout DWORD *pdwEffect);

      virtual HRESULT STDMETHODCALLTYPE DragOver(
      /* [in] */ DWORD grfKeyState,
      /* [in] */ POINTL point,
      /* [out][in] */ __RPC__inout DWORD *pdwEffect);

      virtual HRESULT STDMETHODCALLTYPE DragLeave(void);

      virtual HRESULT STDMETHODCALLTYPE Drop(
      /* [unique][in] */ __RPC__in_opt IDataObject *pDataObj,
      /* [in] */ DWORD grfKeyState,
      /* [in] */ POINTL point,
      /* [out][in] */ __RPC__inout DWORD *pdwEffect);


      virtual void construct(oswindow oswindow);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      //bool create_message_queue(::user::interaction * pinteraction, const char * lpszName);

      //virtual const MSG* GetCurrentMessage();

      //virtual ::estatus update_graphics_resources();


      virtual bool __windows_message_bypass(HWND oswindow, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult);

      virtual void install_message_routing(::channel * pchannel);

      bool operator==(const interaction_impl& wnd) const;
      bool operator!=(const interaction_impl& wnd) const;

      virtual u32 GetStyle() const;
      virtual u32 GetExStyle() const;
      virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, UINT nFlags = 0);
      virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, UINT nFlags = 0);

      //virtual ::user::interaction * get_owner();
      //virtual void set_owner(::user::interaction * pOwnerWnd);

      virtual void route_command_message(::user::command * pcommand) override;

      //void _002OnDraw(::image * pimage);

      virtual void present();

      //virtual void defer_start_prodevian();

      virtual bool set_icon(::draw2d::icon * picon, bool bSmall) override;

      virtual void on_visual_applied() override;

      //virtual void window_apply_visual(const ::user::window_state & windowstate) override;

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnDwmNcRenderingChanged);
      DECL_GEN_SIGNAL(_001OnProdevianSynch);
      DECL_GEN_SIGNAL(_001OnWindowPosChanging);
      DECL_GEN_SIGNAL(_001OnWindowPosChanged);
      DECL_GEN_SIGNAL(_001OnGetMinMaxInfo);
      DECL_GEN_SIGNAL(_001OnEnable);


      virtual void win_update_graphics();

#if(WINVER >= 0x0500)

      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;

#endif   // WINVER >= 0x0500

      //      virtual ::user::interaction * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      //      virtual ::user::interaction * from_handle(oswindow oswindow);

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window();
      bool subclass_window(oswindow oswindow);
      bool SubclassDlgItem(UINT nID, ::user::interaction_impl * pParent);
      oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const char * pszResourceName);

      //bool ExecuteDlgInit(LPVOID pResource);


      // for child windows, views, panes etc
      //virtual bool create_window(::user::interaction * pinteraction, const char * pszClassName,const char * pszWindowName,u32 dwStyle,const ::rect & rect,::user::interaction * pParentWnd,id id, ::create * pcreate = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction * puiParent, id id) override;

      virtual bool _native_create_window_ex(::user::create_struct & cs);

      virtual bool destroy_impl_only() override;
      virtual bool DestroyWindow() override;

      virtual void destroy_window() override;

      // special pre-creation and interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct& cs);

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(RECT * pClientRect, UINT nAdjustType = adjustBorder);



      // get immediate child with given ID
      using ::user::interaction_impl::get_child_by_id;
      void get_child_by_id(id id, oswindow* poswindow_) const;

      virtual bool _is_window() const override;

//#if(WINVER >= 0x0500)
//
//      ::user::interaction_impl * GetAncestor(UINT gaFlags) const;
//
//#endif   // WINVER >= 0x0500

      LRESULT send_message(UINT message, WPARAM wParam = 0, lparam lParam = nullptr);

      bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = nullptr);


      bool SendNotifyMessage(UINT message, WPARAM wParam, lparam lParam);

      //bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      bool DragDetect(const ::point & point) const;



      // Window Text Functions
      virtual void set_window_text(const char * pszString) override;

      virtual strsize get_window_text(char * pszStringBuf, strsize nMaxCount) override;

      virtual void get_window_text(string & rectString) override;
      virtual strsize get_window_text_length() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      //virtual void on_reposition() override;
      //virtual void on_show_window() override;
      //virtual void on_zorder() override;

      //virtual void clear_need_layout() override;
      //virtual void clear_need_translation() override;
      //virtual void clear_show_flags() override;
      //virtual void clear_need_zorder() override;


      //virtual bool set_window_pos(iptr z, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags = SWP_SHOWWINDOW);


      // Window size and position Functions
      virtual bool layout().is_iconic();
      virtual bool layout().is_zoomed();
      //i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //i32 GetWindowRgn(HRGN hRgn);

      virtual UINT ArrangeIconicWindows();
      //virtual void BringToTop(::edisplay edisplay);
      //virtual bool BringWindowToTop();
      //using ::user::interaction_impl::get_window_rect;
      //virtual bool get_window_rect(RECT64 * prect);

      //using ::user::interaction_impl::get_client_rect;
      //virtual bool get_client_rect(RECT64 * prect);


      virtual void rects_from_os();
      virtual bool window_rect_from_os(RECT * prect);
      virtual bool client_rect_from_os(RECT * prect);



      //virtual pointd client_screen_top_left() override;


      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);


      virtual void MapWindowPoints(::user::interaction_impl * pwndTo, LPPOINT pPoint, UINT nCount);

      virtual void MapWindowPoints(::user::interaction_impl * pwndTo, RECT * prect);


      virtual void Print(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const;

      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      virtual bool GetUpdateRect(RECT * prect, bool bErase = FALSE);

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE);
      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(LPCRECT rect, bool bErase = TRUE);

      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE);
      virtual void ValidateRect(LPCRECT rect);

      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool display(::edisplay edisplay);


      virtual void prodevian_prepare_window_minimize(::eactivation eactivation) override;
      virtual void prodevian_prepare_window_maximize() override;
      virtual void prodevian_prepare_window_full_screen(const ::rect & rectHint = nullptr) override;
      virtual void prodevian_prepare_window_restore(edisplay edisplay) override;


      //virtual bool _is_window_visible() override;
      virtual void ShowOwnedPopups(bool bShow = TRUE);

      virtual __pointer(::draw2d::graphics) GetDCEx(::draw2d::region* prgnClip, u32 flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      virtual bool RedrawWindow(const ::rect & rectUpdate = nullptr, 
         ::draw2d::region* prgnUpdate = nullptr,
         UINT flags = RDW_INVALIDATE | RDW_ERASE);

      virtual bool EnableScrollBar(i32 nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);

      //virtual bool DrawAnimatedRects(i32 idAni, CONST LPRECTprcFrom, CONST LPRECTlprcTo);

      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const rect & prc, UINT uFlags);


//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(tick tick, u32 dwFlags);
//
//#endif   // WINVER >= 0x0500
//
//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, UINT nFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501
//
      // Layered Window

//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, u32 dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
//                                       ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, u32 dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500

//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, u32 *pdwFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501


      // timer Functions
//      virtual bool SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer);
      //    virtual bool KillTimer(uptr nIDEvent);

      // Window State Functions
      virtual bool is_this_enabled();
      virtual bool enable_window(bool bEnable = TRUE);

      // the active interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      virtual bool SetForegroundWindow();
      virtual ::user::interaction * GetForegroundWindow();



      virtual bool SetFocus();


      virtual bool has_focus() override;
      virtual bool is_active() override;

      virtual ::user::interaction * GetFocus();

      virtual ::user::interaction * get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for new code
      virtual void CloseWindow();
      virtual bool OpenIcon();

      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(i32 nIDButton, UINT nCheck);
      virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton);
      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton);
      virtual i32 DlgDirList(__inout_z LPTSTR pPathSpec, __in i32 nIDListBox,

                             __in i32 nIDStaticPath, __in UINT nFileType);
      virtual i32 DlgDirListComboBox(__inout_z LPTSTR pPathSpec, __in i32 nIDComboBox,

                                     __in i32 nIDStaticPath, __in UINT nFileType);
      virtual bool DlgDirSelect(__out_ecount_z(nSize) LPTSTR pString, __in i32 nSize, __in i32 nIDListBox);

      virtual bool DlgDirSelectComboBox(__out_ecount_z(nSize) LPTSTR pString, __in i32 nSize, __in i32 nIDComboBox);


      virtual UINT GetChildByIdInt(i32 nID, BOOL * pTrans = nullptr, bool bSigned = TRUE) const;

      virtual i32 GetChildByIdText(__in i32 nID, __out_ecount_part_z(nMaxCount, return +1) LPTSTR pStr, __in i32 nMaxCount) const;

      virtual i32 GetChildByIdText(i32 nID, string & rectString) const;
      //virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const;
      //virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(i32 nIDButton) const;
      virtual LRESULT SendDlgItemMessage(i32 nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      virtual void SetDlgItemInt(i32 nID, UINT nValue, bool bSigned = TRUE);
      virtual void SetDlgItemText(i32 nID, const char * pszString);


      // Scrolling Functions
      virtual i32 GetScrollPos(i32 nBar) const;
      virtual void GetScrollRange(i32 nBar, LPINT pMinPos, LPINT lpMaxPos) const;

      virtual void ScrollWindow(i32 xAmount, i32 yAmount,
         LPCRECT rect = nullptr,

         LPCRECT pClipRect = nullptr);

      virtual i32 SetScrollPos(i32 nBar, i32 nPos, bool bRedraw = TRUE);
      virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos,
                                  bool bRedraw = TRUE);
      virtual void ShowScrollBar(UINT nBar, bool bShow = TRUE);
      virtual void EnableScrollBarCtrl(i32 nBar, bool bEnable = TRUE);

      virtual i32 ScrollWindowEx(i32 dx, i32 dy,
         LPCRECT pRectScroll, LPCRECT lpRectClip,

                                 ::draw2d::region* prgnUpdate, RECT * pRectUpdate, UINT flags);

      virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo,

                                 bool bRedraw = TRUE);
      virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, UINT nMask = SIF_ALL);

      virtual i32 GetScrollLimit(i32 nBar);

//#if(WINVER >= 0x0500)
//
//      virtual bool GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const;
//
//#endif   // WINVER >= 0x0500

      // Window Access Functions
      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point);
      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point, UINT nFlags);
      ///      virtual ::user::interaction_impl * FindWindow(const char * pszClassName,const char * pszWindowName);

      //   virtual ::user::interaction_impl * FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * pszWindow);

      //virtual ::point64 _client_parent_top_left() override;
      //virtual ::point64 _client_screen_top_left() override;

      virtual ::user::interaction * get_next_window(UINT nFlag = GW_HWNDNEXT);
      virtual ::user::interaction * GetTopWindow() const;

      virtual ::user::interaction * GetWindow(UINT nCmd) const;
      virtual ::user::interaction * GetLastActivePopup() const;

      virtual ::user::interaction * GetParent() const;
      virtual ::user::interaction * SetParent(::user::interaction * pWndNewParent);
      //      virtual ::user::interaction * WindowFromPoint(const ::point & point);


      virtual ::user::interaction * SetOwner(::user::interaction * pWndNewParent);
      virtual ::user::interaction * GetOwner() const;

      // virtual bool FlashWindow(bool bInvert);

      //virtual void message_box(const char * pszText, const char * pszTitle = nullptr, UINT nType = MB_OK, const function_arg & functionarg = function_arg());


//
//#if(WINVER >= 0x0500)
//
//      virtual bool FlashWindowEx(u32 dwFlags, UINT  uCount, tick tickTimeout);
//
//#endif   // WINVER >= 0x0500
//
      // Clipboard Functions
      virtual bool ChangeClipboardChain(oswindow oswindow_Next);
      virtual ::oswindow  SetClipboardViewer();
      virtual bool OpenClipboard();
      virtual ::user::interaction * GetClipboardOwner();
      virtual ::user::interaction * GetClipboardViewer();
      virtual ::user::interaction * GetOpenClipboardWindow();

      virtual point GetCaretPos();
      virtual void SetCaretPos(const ::point & point);
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
      //virtual bool update_data(bool bSaveAndValidate = TRUE);
      // data wnd must be same type as this

      //// Help Command Handlers
      //void OnHelp();          // F1 (uses current action_context)
      //void OnHelpIndex();     // ID_HELP_INDEX
      //void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      //void OnHelpUsing();     // ID_HELP_USING
      //virtual void WinHelp(uptr dwData, UINT nCmd = HELP_CONTEXT);
      ////virtual void HtmlHelp(uptr dwData, UINT nCmd = 0x000F);
      //virtual void WinHelpInternal(uptr dwData, UINT nCmd = HELP_CONTEXT);



      // dialog support
      //void UpdateDialogControls(channel* pTarget, bool bDisableIfNoHndler);
      //void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      ////virtual id   RunModalLoop(u32 dwFlags = 0,::object * pliveobject = nullptr);
      //virtual bool ContinueModal() override;
      //virtual void EndModalLoop(id nResult) override;
      //virtual void EndAllModalLoops(id nResult);

      // Window-Management message handler member functions
      virtual bool OnCommand(::message::base * pbase);
      virtual bool OnNotify(::message::base * pbase);

      //void OnActivate(UINT nState, ::user::interaction_impl * pWndOther, bool bMinimized);
      //void OnActivateApp(bool bActive, u32 dwThreadID);
      //LRESULT OnActivateTopLevel(WPARAM, LPARAM);
      //void OnCancelMode();
      //void OnChildActivate();
      //void OnClose();
      //void OnContextMenu(::user::interaction_impl * pwindow, point pos);
      //bool OnCopyData(::user::interaction_impl * pwindow, COPYDATASTRUCT* pCopyDataStruct);

      //HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics, ::user::interaction_impl * pwindow, UINT nCtlColor);


      //void OnEnable(bool bEnable);
      //void OnEndSession(bool bEnding);
      //void OnEnterIdle(UINT nWhy, ::user::interaction_impl * pWho);
      //bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //void OnGetMinMaxInfo(MINMAXINFO* pMMI);

      //bool OnHelpInfo(HELPINFO* pHelpInfo);

      //void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      //LRESULT OnMenuChar(UINT nChar, UINT nFlags, ::user::menu* pMenu);
      //void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
      //void OnMove(i32 x, i32 y);
      //void OnParentNotify(UINT message, LPARAM lParam);
      //HCURSOR OnQueryDragIcon();
      //bool OnQueryEndSession();
      //bool OnQueryNewPalette();
      //bool OnQueryOpen();
      //void OnShowWindow(bool bShow, UINT nStatus);
      //void OnSize(UINT nType, i32 cx, i32 cy);
      //void OnTCard(UINT idAction, u32 dwActionData);

      //void OnChangeUIState(UINT nAction, UINT nUIElement);
      //void OnUpdateUIState(UINT nAction, UINT nUIElement);
      //UINT OnQueryUIState();

      //// Nonclient-Area message handler member functions
      //bool OnNcActivate(bool bActive);
      //void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS* pncsp);

      //bool OnNcCreate(::user::create_struct * pCreateStruct);

      //LRESULT OnNcHitTest(const ::point & point);
      //void OnNcLButtonDblClk(UINT nHitTest, const ::point & point);
      //void OnNcLButtonDown(UINT nHitTest, const ::point & point);
      //void OnNcLButtonUp(UINT nHitTest, const ::point & point);
      //void OnNcMButtonDblClk(UINT nHitTest, const ::point & point);
      //void OnNcMButtonDown(UINT nHitTest, const ::point & point);
      //void OnNcMButtonUp(UINT nHitTest, const ::point & point);
      //void OnNcMouseMove(UINT nHitTest, const ::point & point);
      //void OnNcPaint();
      //void OnNcRButtonDblClk(UINT nHitTest, const ::point & point);
      //void OnNcRButtonDown(UINT nHitTest, const ::point & point);
      //void OnNcRButtonUp(UINT nHitTest, const ::point & point);

      //// System message handler member functions
      //void OnDropFiles(HDROP hDropInfo);
      //void OnPaletteIsChanging(::user::interaction_impl * pRealizeWnd);
      //void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnSysCommand(UINT nID, LPARAM lParam);
      //void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnCompacting(UINT nCpuTime);
      //void OnDevModeChange(__in_z LPTSTR pDeviceName);

      //void OnFontChange();
      //void OnPaletteChanged(::user::interaction_impl * pFocusWnd);
      //void OnSpoolerStatus(UINT nStatus, UINT nJobs);
      //void OnSysColorChange();
      //void OnTimeChange();
      //void OnSettingChange(UINT uFlags, const char * pszSection);

      //void OnWinIniChange(const char * pszSection);


      //// Input message handler member functions
      //void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
      ////      void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      ////    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
      //void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
      //void OnLButtonDblClk(UINT nFlags, const ::point & point);
      //void OnLButtonDown(UINT nFlags, const ::point & point);
      //void OnLButtonUp(UINT nFlags, const ::point & point);
      //void OnMButtonDblClk(UINT nFlags, const ::point & point);
      //void OnMButtonDown(UINT nFlags, const ::point & point);
      //void OnMButtonUp(UINT nFlags, const ::point & point);
      //i32 OnMouseActivate(::user::interaction_impl * pDesktopWnd, UINT nHitTest, UINT message);
      //void OnMouseMove(UINT nFlags, const ::point & point);
      //bool OnMouseWheel(UINT nFlags, i16 zDelta, const ::point & point);
      //LRESULT OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam);
      //void OnRButtonDblClk(UINT nFlags, const ::point & point);
      //void OnRButtonDown(UINT nFlags, const ::point & point);
      //void OnRButtonUp(UINT nFlags, const ::point & point);
      //void OnTimer(uptr nIDEvent);

      //// Initialization message handler member functions
      //void OnInitMenu(::user::menu* pMenu);
      //void OnInitMenuPopup(::user::menu* pPopupMenu, UINT nIndex, bool bSysMenu);

      //// Clipboard message handler member functions
      //void OnAskCbFormatName(__in UINT nMaxCount, __out_ecount_z(nMaxCount) LPTSTR pszString);

      //void OnChangeCbChain(oswindow oswindow_Remove, oswindow oswindow_After);
      //void OnDestroyClipboard();
      //void OnDrawClipboard();
      //void OnHScrollClipboard(::user::interaction_impl * pClipAppWnd, UINT nSBCode, UINT nPos);
      //void OnPaintClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hPaintStruct);
      //void OnRenderAllFormats();
      //void OnRenderFormat(UINT nFormat);
      //void OnSizeClipboard(::user::interaction_impl * pClipAppWnd, HGLOBAL hRect);
      //void OnVScrollClipboard(::user::interaction_impl * pClipAppWnd, UINT nSBCode, UINT nPos);

      //// control message handler member functions
      //i32 OnCompareItem(i32 nIDCtl, LPCOMPAREITEMSTRUCT pCompareItemStruct);

      //void OnDeleteItem(i32 nIDCtl, LPDELETEITEMSTRUCT pDeleteItemStruct);

      //void OnDrawItem(i32 nIDCtl, LPDRAWITEMSTRUCT pDrawItemStruct);

      //UINT OnGetDlgCode();

      // MDI message handler member functions
      //void OnMDIActivate(bool bActivate,
      //                   ::user::interaction_impl * pActivateWnd, ::user::interaction_impl * pDeactivateWnd);

      // menu loop notification messages
      //void OnEnterMenuLoop(bool bIstrack_popup_menu);
      //void OnExitMenuLoop(bool bIstrack_popup_menu);

      //// Win4 messages
      //void OnStyleChanged(i32 nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnStyleChanging(i32 nStyleType, LPSTYLESTRUCT pStyleStruct);

      //void OnSizing(UINT nSide, RECT * prect);

      //void OnMoving(UINT nSide, RECT * prect);

      //void OnCaptureChanged(::user::interaction_impl * pwindow);
      //bool OnDeviceChange(UINT nEventType, uptr dwData);

      // Overridables and other helpers (for implementation of derived classes)
      // for deriving from a standard control
      virtual WNDPROC* GetSuperWndProcAddr();

      // for dialog data exchange and validation
      //      virtual void do_data_exchange(CDataExchange* pDX);

      // for modality
      virtual void BeginModalState();
      virtual void EndModalState();

      // for translating Windows messages in Main message pump
      virtual void pre_translate_message(::message::message * pmessage);


      virtual void default_message_handler(::message::message * pmessage) override;
      virtual void message_handler(::message::base * pbase);


      //virtual bool OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

      // for handling default processing
      //LRESULT Default();
      //virtual void default_window_procedure(::message::message * pmessage) override;


      virtual void PostNcDestroy();

      // for notifications from parent
      virtual bool OnChildNotify(::message::base * pbase);
      // return TRUE if parent should not process this message
      virtual bool ReflectChildNotify(::message::base * pbase);
      virtual bool ReflectMessage(oswindow oswindow_Child, ::message::base * pbase);

      // Implementation
      //virtual bool CheckAutoCenter();
      //virtual bool GrayCtlColor(HDC hDC, oswindow oswindow, UINT nCtlColor,
      //                          HBRUSH hbrGray, COLORREF clrText);


      // helper routines for implementation
      bool HandleFloatingSysCommand(UINT nID, LPARAM lParam);
      bool IsTopParentActive();
      void ActivateTopParent();
      virtual void on_final_release();
      virtual bool ModifyStyle(oswindow oswindow, u32 dwRemove, u32 dwAdd, UINT nFlags);
      virtual bool ModifyStyleEx(oswindow oswindow, u32 dwRemove, u32 dwAdd, UINT nFlags);
      //virtual void _FilterToolTipMessage(MSG* pMsg,::user::interaction_impl * pwindow);
      //bool _EnableToolTips(bool bEnable, UINT nFlag);
      virtual oswindow get_safe_owner(::oswindow oswindow, ::oswindow * pWndTop);
      //void PrepareForHelp();


      friend class frame_window;

      bool CreateDlg(const char * pszTemplateName, ::user::interaction_impl * pParentWnd);



      //CLASS_DECL_AURA friend LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
      //CLASS_DECL_AURA friend LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);

      // standard message implementation
      //LRESULT OnNTCtlColor(WPARAM wParam, LPARAM lParam);
      //LRESULT OnDisplayChange(WPARAM, LPARAM);
      //LRESULT OnDragList(WPARAM, LPARAM);



      virtual void get_app_wnda(user::oswindow_array & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      virtual LONG get_window_long(i32 nIndex) const;
      virtual LONG set_window_long(i32 nIndex, LONG lValue);
      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex, LONG_PTR lValue);


      void _001OnTriggerMouseInside();

      void set_viewport_org(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(RECT * prect);
      virtual void register_drop_target();
      virtual void show_task(bool bShow);
      virtual void window_show_change_visibility() override;


      virtual void non_top_most_upper_window_rects(::rect_array& recta) override;


   };


} // namespace windows





