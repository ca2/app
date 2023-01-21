#pragma once


namespace android
{



   class CLASS_DECL_CORE interaction_impl:
      virtual public ::user::interaction_impl
   {
   public:


      string                                    m_strWindowText;
      ::user::primitive *                       m_pbasewnd;
      bool                                      m_bUpdateGraphics;
      size_i32                                      m_size;
      point_i32                                     m_point;
      static const ::u32                         m_nMsgDragList;
      edisplay                                  m_edisplayLayout;
      ::thread *                                m_pthreadDraw;
      int                                       m_iSoftwareKeyboardScroll;


      interaction_impl();
      virtual ~interaction_impl();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      //bool create_message_queue(::user::interaction * pinteraction, const ::string & pszName) override;

      //virtual bool create_native_window(::user::native_window_initialize * pinitialize) override;


      void install_message_routing(::channel * pchannel) override;

      bool operator==(const ::user::interaction_impl& wnd) const;
      bool operator!=(const ::user::interaction_impl& wnd) const;

      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      void _002OnDraw(::image * pimage);

      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(_001OnProdevianSynch);

      void OnWindowPosChanging(WINDOWPOS* lpuserinteractionpos);
      void OnWindowPosChanged(WINDOWPOS* lpuserinteractionpos);

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
      //bool SubclassDlgItem(::u32 nID,::user::interaction * pParent);
      //oswindow unsubclass_window();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //bool ExecuteDlgInit(const ::string & lpszResourceName);
      //bool ExecuteDlgInit(LPVOID lpResource);

      // for child windows, views, panes etc
      virtual bool create_window(::user::interaction * pinteraction, const ::string & lpszClassName, const ::string & lpszWindowName, u32 dwStyle, const ::rectangle_i32 & rectangle, ::user::interaction * pParentWnd, atom atom, ::request * prequest = nullptr) override;

      // for top level windows and/or special features
      virtual bool create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pusersystem, ::user::interaction * puiParent = nullptr, ::atom atom = ::atom()) override;

      // for top level windows and/or special features
      virtual bool _native_create_window_ex(::user::system& cs) override;

      virtual bool DestroyWindow() override;

      // special pre-creation and interaction_impl rectangle_i32 adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem) override;

      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(RECTANGLE_I32 * lpClientRect,::u32 nAdjustType = adjustBorder) override;

      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;

      virtual void edit_on_kill_focus(::user::interaction* pinteraction) override;

      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd) override;

      using ::user::interaction_impl::get_child_by_id;
      void get_child_by_id(atom atom,oswindow* poswindow_) const;

      //virtual bool IsWindow() const;

      // oswindow State Functions
      //virtual bool IsWindowEnabled();
      //virtual bool EnableWindow(bool bEnable = true);

      // the active ::user::interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow() override;
      virtual ::user::interaction * SetActiveWindow() override;


      LRESULT send_message(const ::atom & atom,WPARAM wParam = 0,lparam lParam = 0) override;
      bool post_message(const ::atom & atom,WPARAM wParam = 0,lparam lParam = 0) override;

      bool SendNotifyMessage(const ::atom & atom,WPARAM wParam,lparam lParam) override;
      //bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      //bool DragDetect(POINT_I32 pt) const;

      //virtual void RedrawWindow(::u32 nFlags = 0) override;

      // Window Text Functions
      virtual void set_window_text(const ::string & lpszString) override;
      virtual strsize get_window_text(char * lpszStringBuf, strsize nMaxCount) override;
      virtual void get_window_text(string & rString) override;
      virtual strsize get_window_text_length() override;


      // Window size_i32 and position Functions
      //virtual bool layout().is_iconic();
      //virtual bool layout().is_zoomed();
      //i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //i32 GetWindowRgn(HRGN hRgn);

      //using ::user::interaction_impl::set_window_position;
      //virtual bool set_window_position(iptr z,i32 x,i32 y,i32 cx,i32 cy,::u32 nFlags = SWP_SHOWWINDOW);
      //virtual ::u32 ArrangeIconicWindows();
      //virtual void BringToTop(int nCmdShow);
      //virtual bool BringWindowToTop();
      //using ::user::interaction_impl::window_rectangle;
      //virtual bool window_rectangle(RECTANGLE_I64 * lpRect);
      //using ::user::interaction_impl::client_rectangle;
      //virtual bool client_rectangle(RECTANGLE_I64 * lpRect);

      //virtual bool client_to_screen(RECTANGLE_I32 * lprect);
      //virtual bool client_to_screen(POINT_I32 * lppoint);
      //virtual bool client_to_screen(RECTANGLE_I64 * lprect);
      //virtual bool client_to_screen(POINT_I64 * lppoint);
      //virtual bool screen_to_client(RECTANGLE_I32 * lprect);
      //virtual bool screen_to_client(POINT_I32 * lppoint);
      //virtual bool screen_to_client(RECTANGLE_I64 * lprect);
      //virtual bool screen_to_client(POINT_I64 * lppoint);

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpuserinteractionpl);
      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpuserinteractionpl);

      //virtual void MapWindowPoints(::user::interaction * puserinteractionTo,POINT_I32 * lpPoint,::u32 nCount);
      //virtual void MapWindowPoints(::user::interaction * puserinteractionTo,RECTANGLE_I32 * lpRect);

      //virtual void Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;
      //virtual void PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;

      //virtual void UpdateWindow();
      //virtual void SetRedraw(bool bRedraw = true);
      //virtual bool GetUpdateRect(RECTANGLE_I32 * lpRect,bool bErase = false);
      //virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = false);
      //virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const RECTANGLE_I32 * lpRect,bool bErase = true);
      //virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = true);
      //virtual void ValidateRect(const RECTANGLE_I32 * lpRect);
      //virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual bool ShowWindow(i32 nCmdShow) override;
//      virtual void _001WindowMinimize();
      //virtual void _001WindowMaximize();
      //    virtual void _001WindowFullScreen();
      //virtual void _001WindowRestore();
      virtual bool _is_window() const override;
      virtual bool is_window_visible();
      virtual void ShowOwnedPopups(bool bShow = true) override;

      virtual ::draw2d::graphics * GetDC();
      virtual ::draw2d::graphics * GetWindowDC();
      //virtual bool ReleaseDC(::image * pimage);
      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip,u32 flags);
      virtual bool LockWindowUpdate() override;
      virtual void UnlockWindowUpdate() override;
      //virtual bool RedrawWindow(const RECTANGLE_I32 * lpRectUpdate = nullptr,
        //                        ::draw2d::region* prgnUpdate = nullptr,
          //                      ::u32 flags = RDW_INVALIDATE | RDW_ERASE);
      //virtual bool EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags = 0);

      //virtual bool DrawAnimatedRects(i32 idAni,const RECTANGLE_I32 *lprcFrom,const RECTANGLE_I32 *lprcTo);
      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,const RECTANGLE_I32 * lprc,::u32 uFlags);




      // timer Functions
      //virtual bool SetTimer(uptr uEvent,::u32 nElapse, PFN_TIMER pfnTimer);
      //virtual bool KillTimer(uptr uEvent);


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

      // Obsolete and non-portable APIs - not recommended for memory_new code
      virtual void CloseWindow() override;
      virtual bool OpenIcon() override;

      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
      virtual void CheckDlgButton(i32 nIDButton, ::u32 nCheck) override;
      virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton, i32 nIDCheckButton) override;
      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton) override;
      virtual i32 DlgDirList(char * lpPathSpec, i32 nIDListBox, i32 nIDStaticPath, ::u32 nFileType) override;
      virtual i32 DlgDirListComboBox(char * lpPathSpec, i32 nIDComboBox, i32 nIDStaticPath, ::u32 nFileType) override;
      virtual bool DlgDirSelect(char * lpString, i32 nSize, i32 nIDListBox) override;
      virtual bool DlgDirSelectComboBox(char * lpString, i32 nSize, i32 nIDComboBox) override;

      //virtual ::u32 GetChildByIdInt(i32 nID, bool * lpTrans = nullptr, bool bSigned = true) const;
      //virtual i32 GetChildByIdText(i32 nID, char * lpStr, i32 nMaxCount) const;
      //virtual i32 GetChildByIdText(i32 nID, string & rString) const;
      //virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      //virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = false) const;
      virtual ::u32 IsDlgButtonChecked(i32 nIDButton) const override;
      virtual LRESULT SendDlgItemMessage(i32 nID, const ::atom & atom, WPARAM wParam = 0, LPARAM lParam = 0) override;
      virtual void SetDlgItemInt(i32 nID, ::u32 nValue, bool bSigned = true) override;
      virtual void SetDlgItemText(i32 nID, const ::string & lpszString) override;


      // Scrolling Functions
      virtual i32 GetScrollPos(i32 nBar) const override;
      virtual void GetScrollRange(i32 nBar,LPINT lpMinPos,LPINT lpMaxPos) const override;
      virtual void ScrollWindow(i32 xAmount,i32 yAmount, const RECTANGLE_I32 * lpRect = nullptr, const RECTANGLE_I32 * lpClipRect = nullptr) override;
      virtual i32 SetScrollPos(i32 nBar,i32 nPos,bool bRedraw = true) override;
      virtual void SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos, bool bRedraw = true) override;
      virtual void ShowScrollBar(::u32 nBar,bool bShow = true) override;
      virtual void EnableScrollBarCtrl(i32 nBar,bool bEnable = true) override;

      virtual i32 ScrollWindowEx(i32 Δx,i32 Δy,
                                 const RECTANGLE_I32 * lpRectScroll,const RECTANGLE_I32 * lpRectClip,
                                 ::draw2d::region* prgnUpdate,RECTANGLE_I32 * lpRectUpdate,::u32 flags) override;
      //virtual bool SetScrollInfo(i32 nBar,LPSCROLLINFO lpScrollInfo,
      //   bool bRedraw = true);
      //virtual bool GetScrollInfo(i32 nBar,LPSCROLLINFO lpScrollInfo,::u32 nMask = SIF_ALL);
      virtual i32 GetScrollLimit(i32 nBar) override;

#if(WINVER >= 0x0500)

      virtual bool GetScrollBarInfo(::i32 idObject,PSCROLLBARINFO psbi) const;

#endif   // WINVER >= 0x0500

      // Window Access Functions
      virtual ::user::interaction * ChildWindowFromPoint(POINT_I32 point_i32);
      virtual ::user::interaction * ChildWindowFromPoint(POINT_I32 point,::u32 nFlags);
      static ::user::interaction * FindWindow(const ::string & lpszClassName, const ::string & lpszWindowName);
      static ::user::interaction * FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter, const ::string & lpszClass, const ::string & lpszWindow);

      virtual ::user::interaction * GetNextWindow(::u32 nFlag = GW_HWNDNEXT);
      virtual ::user::interaction * GetTopWindow() const override;

      //virtual ::user::interaction * GetWindow(::u32 nCmd);
      virtual ::user::interaction * GetLastActivePopup() override;

      //virtual bool IsChild(::user::interaction *  pWnd);
      //virtual ::user::interaction * get_parent();
      //using ::user::interaction_impl::SetParent;
      //::user::interaction * SetParent(::user::interaction * pWndNewParent);
      //static::user::interaction * PASCAL oswindowFromPoint(POINT_I32 point_i32);


      //virtual ::user::interaction * SetOwner(::user::interaction * pWndNewParent);
      //virtual ::user::interaction * get_owner() const;

      //virtual bool FlashWindow(bool bInvert);

      //virtual i32 message_box(const ::string & lpszText, const ::string & lpszCaption = nullptr,::u32 nType = e_message_box_ok) override;


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(u32 dwFlags,::u32  uCount,class ::time tickTimeout);

#endif   // WINVER >= 0x0500

      // Clipboard Functions
      //virtual bool ChangeClipboardChain(oswindow oswindow_Next);
      //virtual ::oswindow  SetClipboardViewer();
      //virtual bool OpenClipboard();
      //static ::user::interaction * GetClipboardOwner();
      //static ::user::interaction * GetClipboardViewer();
      //static ::user::interaction * GetOpenClipboardWindow();


      //static point_i32 GetCaretPos();
      //static void SetCaretPos(POINT_I32 point_i32);
      //virtual void HideCaret() override;
      //virtual void ShowCaret() override;

      // Shell Interaction Functions
      virtual void DragAcceptFiles(bool bAccept = true) override;

      // icon Functions
      //virtual HICON SetIcon(HICON hIcon,bool bBigIcon);
      //virtual HICON GetIcon(bool bBigIcon) const;

      // Context Help Functions
      virtual bool SetWindowContextHelpId(u32 dwContextHelpId) override;
      virtual u32 GetWindowContextHelpId() const override;

       support
      //virtual bool update_data(bool bSaveAndValidate = true);
      // data wnd must be same type as this

      // Help Command Handlers
      void OnHelp();          // F1 (uses current action_context)
      void OnHelpIndex();     // ID_HELP_INDEX
      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      void OnHelpUsing();     // ID_HELP_USING
      virtual void WinHelp(uptr dwData,::u32 nCmd = 0);
      //virtual void HtmlHelp(uptr dwData, ::u32 nCmd = 0x000F);
      virtual void WinHelpInternal(uptr dwData,::u32 nCmd = 0);



      // dialog support
      void UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler) override;
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;

      virtual bool OnCommand(::user::message * pusermessage) override;
      virtual bool OnNotify(::user::message * pusermessage) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual bool SubclassWindow(oswindow hWnd);
      HBRUSH OnCtlColor(::draw2d::graphics_pointer & pgraphics,::user::interaction * pwindow,::u32 nCtlColor);

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      void OnEnable(bool bEnable);
      void OnEndSession(bool bEnding);
      bool OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
      void OnIconEraseBkgnd(::draw2d::graphics_pointer & pgraphics);
      void OnKillFocus(::user::interaction * pNewWnd);
      LRESULT OnMenuChar(::u32 nChar,::u32 nFlags,::user::menu* pMenu);
      void OnMenuSelect(::u32 nItemID,::u32 nFlags,HMENU hSysMenu);
      void OnMove(i32 x,i32 y);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(_001OnPrint);
      void OnParentNotify(const ::atom & atom,LPARAM lParam);
      HCURSOR OnQueryDragIcon();
      bool OnQueryEndSession();
      bool OnQueryNewPalette();
      bool OnQueryOpen();
      void OnSetFocus(::user::interaction *);
      void OnShowWindow(bool bShow,::u32 nStatus);
      void OnSize(::u32 nType,i32 cx,i32 cy);
      void OnTCard(::u32 idAction,u32 dwActionData);

      void OnChangeUIState(::u32 nAction,::u32 nUIElement);
      void OnUpdateUIState(::u32 nAction,::u32 nUIElement);
      ::u32 OnQueryUIState();

      // Nonclient-Area message handler member functions
      bool OnNcActivate(bool bActive);
      void OnNcCalcSize(bool bCalcValidRects,NCCALCSIZE_PARAMS* lpncsp);
      bool OnNcCreate(::user::system * lpCreateStruct);

      DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
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

      // System message handler member functions
      void OnDropFiles(HDROP hDropInfo);
      void OnPaletteIsChanging(::user::interaction * pRealizeWnd);
      void OnSysChar(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnSysCommand(::u32 nID,LPARAM lParam);
      void OnSysDeadChar(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnSysKeyDown(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnSysKeyUp(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnCompacting(::u32 nCpuTime);
      void OnDevModeChange(char * lpDeviceName);
      void OnFontChange();
      void OnPaletteChanged(::user::interaction * pFocusWnd);
      void OnSpoolerStatus(::u32 nStatus,::u32 nJobs);
      void OnSysColorChange();
      void OnTimeChange();
      void OnSettingChange(::u32 uFlags, const ::string & lpszSection);
      void OnWinIniChange(const ::string & lpszSection);

      // Input message handler member functions
      void OnChar(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnDeadChar(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      //      void OnHScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      //    void OnVScroll(::u32 nSBCode, ::u32 nPos, CScrollBar* pScrollBar);
      void OnKeyDown(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnKeyUp(::u32 nChar,::u32 nRepCnt,::u32 nFlags);
      void OnLButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      void OnLButtonDown(::u32 nFlags, const ::point_i32 & point);
      void OnLButtonUp(::u32 nFlags, const ::point_i32 & point);
      void OnMButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      void OnMButtonDown(::u32 nFlags, const ::point_i32 & point);
      void OnMButtonUp(::u32 nFlags, const ::point_i32 & point);
      i32 OnMouseActivate(::user::interaction * pDesktopWnd,::u32 nHitTest,const ::atom & atom);
      void OnMouseMove(::u32 nFlags, const ::point_i32 & point);
      bool OnMouseWheel(::u32 nFlags,i16 zDelta, const ::point_i32 & point);
      LRESULT OnRegisteredMouseWheel(WPARAM wParam,LPARAM lParam);
      void OnRButtonDblClk(::u32 nFlags, const ::point_i32 & point);
      void OnRButtonDown(::u32 nFlags, const ::point_i32 & point);
      void OnRButtonUp(::u32 nFlags, const ::point_i32 & point);
      //DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      void OnTimer(uptr uEvent);

      // Initialization message handler member functions
      void OnInitMenu(::user::menu* pMenu);
      void OnInitMenuPopup(::user::menu* pPopupMenu,::u32 nIndex,bool bSysMenu);

      // Clipboard message handler member functions
      void OnAskCbFormatName(::u32 nMaxCount,char * lpszString);
      void OnChangeCbChain(oswindow oswindow_Remove,oswindow oswindow_After);
      void OnDestroyClipboard();
      void OnDrawClipboard();
      void OnHScrollClipboard(::user::interaction * pClipAppWnd,::u32 nSBCode,::u32 nPos);
      void OnPaintClipboard(::user::interaction * pClipAppWnd,HGLOBAL hPaintStruct);
      void OnRenderAllFormats();
      void OnRenderFormat(::u32 nFormat);
      void OnSizeClipboard(::user::interaction * pClipAppWnd,HGLOBAL hRect);
      void OnVScrollClipboard(::user::interaction * pClipAppWnd,::u32 nSBCode,::u32 nPos);

      // control message handler member functions
      //i32 OnCompareItem(i32 nIDCtl,LPCOMPAREITEMSTRUCT lpCompareItemStruct);
      //void OnDeleteItem(i32 nIDCtl,LPDELETEITEMSTRUCT lpDeleteItemStruct);
      //void OnDrawItem(i32 nIDCtl,LPDRAWITEMSTRUCT lpDrawItemStruct);
      ::u32 OnGetDlgCode();
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
      void OnSizing(::u32 nSide,RECTANGLE_I32 * lpRect);
      void OnMoving(::u32 nSide,RECTANGLE_I32 * lpRect);
      void OnCaptureChanged(::user::interaction * pwindow);
      bool OnDeviceChange(::u32 nEventType,uptr dwData);

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
      virtual void message_handler(::user::message * pusermessage) override;


      // for handling default processing
      LRESULT Default();
      virtual LRESULT DefWindowProc(const ::atom & atom,WPARAM wParam,lparam lParam);

      virtual void post_non_client_destroy() override;

      // for notifications from parent
      //virtual bool OnChildNotify(::user::message * pusermessage);
      // return true if parent should not process this message
      //virtual bool ReflectChildNotify(::user::message * pusermessage);
      //static bool ReflectMessage(oswindow oswindow_Child,::user::message * pusermessage);

      
      virtual bool CheckAutoCenter() override;
      //virtual bool GrayCtlColor(HDC hDC,oswindow oswindow,::u32 nCtlColor,
      //                          HBRUSH hbrGray,color32_t clrText);


      // helper routines for implementation
      //bool HandleFloatingSysCommand(::u32 nID, LPARAM lParam) override;
      bool IsTopParentActive() override;
      void ActivateTopParent() override;
      //virtual void WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage);
      virtual bool is_frame_window(); // is_kind_of(__type(frame_window)))
      virtual void on_final_release() override;
      static bool ModifyStyle(oswindow hWnd, ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags);
      static bool ModifyStyleEx(oswindow hWnd, ::u32 dwRemove, ::u32 dwAdd, ::u32 nFlags);
      //static void PASCAL _FilterToolTipMessage(MESSAGE* pMsg, ::user::interaction * pWnd);
      bool _EnableToolTips(bool bEnable, ::u32 nFlag) override;
      //static oswindow PASCAL GetSafeOwner_(oswindow hWnd, oswindow* pWndTop);
      void PrepareForHelp() override;


      friend class frame_window;

      bool CreateDlg(const ::string & lpszTemplateName,::user::interaction * pParentWnd);


      //CLASS_DECL_BASE friend LRESULT CALLBACK __send_message_hook(i32,WPARAM,LPARAM);
      //CLASS_DECL_BASE friend LRESULT CALLBACK __cbt_filter_hook(i32,WPARAM,LPARAM);

      // standard message implementation
      LRESULT OnNTCtlColor(WPARAM wParam,LPARAM lParam);
      LRESULT OnDisplayChange(WPARAM,LPARAM);
      LRESULT OnDragList(WPARAM,LPARAM);

      bool CALLBACK GetAppsEnumWindowsProc(oswindow hwnd, lparam lparam);


      static void get_app_wnda(user::oswindow_array & wnda);

      virtual void _001DeferPaintLayeredWindowBackground(HDC hdc);

      //virtual ::i32 get_window_long(i32 nIndex) const;
      //virtual ::i32 set_window_long(i32 nIndex,::i32 lValue);
      //virtual LONG_PTR get_window_long_ptr(i32 nIndex) const;
      //virtual LONG_PTR set_window_long_ptr(i32 nIndex,LONG_PTR lValue);

      virtual void _001BaseWndInterfaceMap() override;




      void set_context_org(::draw2d::graphics_pointer & pgraphics) override;

      //string calc_icon_window_class(u32 dwDefaultStyle, const ::string & pszMatter);
      //string calc_window_class();

      void on_set_parent(::user::interaction * pinteraction);

      ::user::interaction * FromHandlePermanent(oswindow oswindow);

      bool Attach(oswindow hWndNew);
      virtual oswindow Detach();
      //virtual bool get_rect_normal(RECTANGLE_I32 * lprect);
      virtual oswindow UnsubclassWindow();
//      virtual void register_drop_target();

      //virtual void WalkPreTranslateTree(::user::interaction * puiStop, ::message::message * pmessage);
      virtual bool SendChildNotifyLastMsg(LRESULT* pResult);

      virtual oswindow get_handle() const override;

      //virtual void MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight, bool bRepaint);
      //virtual void MoveWindow(const RECTANGLE_I32 * lpRect, bool bRepaint = true);

      virtual atom SetDlgCtrlId(atom atom) override;
      virtual atom GetDlgCtrlId();


      virtual ::i32 GetWindowLong(i32 nIndex);
      virtual ::i32 SetWindowLong(i32 nIndex, ::i32 lValue);


      virtual void SetFont(::write_text::font* pfont, bool bRedraw);
      virtual void set_owner(::user::interaction * pOwnerWnd) override;
      virtual ::write_text::font* GetFont();





      void _001OnTriggerMouseInside() override;


      ::user::interaction * get_next(bool bIgnoreChildren, i32 * piLevel) override;
      virtual bool on_keyboard_focus(::user::primitive * pfocus) override;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      virtual bool keyboard_focus_OnChildKillFocus() override;


      virtual bool has_pending_graphical_update()override;

   };


} // namespace android





