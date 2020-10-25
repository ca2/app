#pragma once


namespace linux
{


   LRESULT CALLBACK __send_message_hook(i32, WPARAM, LPARAM);
   // void _::ca2::StandardSubclass(oswindow);
   LRESULT CALLBACK __cbt_filter_hook(i32, WPARAM, LPARAM);
   LRESULT __call_window_procedure(::user::interaction * pWnd, oswindow hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);


   class x11data;
   class  interaction_impl :
      virtual public ::user::interaction_impl
   {
   public:


      string                        m_strWindowText;
      ::user::primitive *    m_pbasewnd;
      bool                          m_bExposing;
      __pointer(x11data)                   m_px11data;
      i32                           m_iDepth;
      i32                           m_iScreen;
      bool                          m_bEnabled;

      //__pointer(::thread)                  m_pthreadDraw;
      ::rect64                      m_rectLastPos;
      tick m_tickLastPos;

      ::point                       m_pointLastMove;
      bool                          m_bMoveEvent;
      ::size                        m_sizeLastSize;
      bool                          m_bSizeEvent;
      ::tick                        m_tickLastPlacementEvent;


      interaction_impl();
      interaction_impl(::layered * pobjectContext);
      virtual ~interaction_impl();


      void linux_interaction_impl_common_construct();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      //virtual void on_delete(::object * poc);

      static const MESSAGE* PASCAL GetCurrentMessage();

      virtual void install_message_routing(::channel * pchannel) override;

      bool operator==(const ::user::interaction_impl& wnd) const;
      bool operator!=(const ::user::interaction_impl& wnd) const;

      DWORD GetStyle() const override;
      DWORD GetExStyle() const override;
      bool ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0) override;
      bool ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0) override;

      //virtual ::user::interaction * GetOwner();
      virtual void set_owner(::user::interaction * pOwnerWnd) override;

      virtual oswindow get_handle() const override;

      virtual void route_command_message(::user::command * pcommand) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual bool setWMClass(const char * psz) override;
      //void _002OnDraw(::image * pimage);

      DECL_GEN_SIGNAL(_001OnEraseBkgnd);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      //DECL_GEN_SIGNAL(_001OnProdevianSynch);


      virtual void window_show_change_visibility() override;


//#if(WINVER >= 0x0500)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      virtual ::user::interaction_impl * from_os_data(void * pdata) override;
      virtual void * get_os_data() const override;

      static user::interaction_impl * from_handle(oswindow hWnd);
      static user::interaction_impl * FromHandlePermanent(oswindow hWnd);
      //static void DeleteTempMap();
      bool Attach(oswindow hWndNew);
      oswindow Detach();

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
//      bool SubclassWindow(oswindow hWnd);
//      //bool SubclassDlgItem(UINT nID, __pointer(::interaction_impl) pParent);
//      oswindow UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
//      bool ExecuteDlgInit(const char * pszResourceName);
//
//      bool ExecuteDlgInit(LPVOID pResource);

      //virtual bool create_message_queue(::user::interaction * pinteraction, const char * lpszName) override;

//      using ::user::interaction_impl::create_window;

      // for child windows, views, panes etc
//      virtual bool create_window(
//      ::user::interaction * pinteraction,
//      const char * pszClassName,

//      const char * pszWindowName,

//      DWORD dwStyle,
//      const ::rect & rect,
//      ::user::interaction * pParentWnd,
//      id id,
//      ::create * pContext = nullptr) override;
//
//      // advanced creation (allows access to extended styles)
//      virtual bool create_window_ex(
//      ::user::interaction * pinteraction,
//      ::user::create_struct & cs,
//      ::user::interaction * pParentWnd = nullptr,
//      id id = ::id()) override;

    virtual bool _native_create_window_ex(::user::create_struct & cs) override;


//      virtual bool native_create_window_ex(
//      ::user::interaction * pinteraction,
//      ::user::create_struct & cs,
//      ::user::interaction * pParentWnd = nullptr,
//      id id = ::id());

      virtual bool DestroyWindow() override;

      // special pre-creation and ::user::interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct & cs) override;

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
//      virtual void CalcWindowRect(RECT * pClientRect, UINT nAdjustType = adjustBorder);




      void _thread_delayed_placement();

      void defer_delayed_placement();


      virtual void on_start_layout_experience(e_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(e_layout_experience elayoutexperience) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;




      virtual bool _is_window() const override;

#if(WINVER >= 0x0500)

      ::user::interaction * GetAncestor(UINT gaFlags) const;

#endif   // WINVER >= 0x0500

      LRESULT send_message(const ::id & id, WPARAM wParam = 0, lparam lparam = 0) override;

      bool post_message(const ::id & id, WPARAM wParam = 0, lparam lparam = 0) override;


//      bool SendNotifyMessage(const ::id & id, WPARAM wParam, lparam lParam);
//
//      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);
//
//      bool DragDetect(const ::point & point) const;





      // oswindow Text Functions
      void set_window_text(const char * pszString) override;

      //strsize GetWindowText(LPTSTR pszStringBuf, strsize nMaxCount);

      void get_window_text(string & str) override;
      //strsize GetWindowTextLength();
      void SetFont(::draw2d::font* pFont, bool bRedraw = TRUE);
      ::draw2d::font* GetFont();


      // oswindow size and position Functions
      virtual bool layout().is_iconic();
      //virtual bool layout().is_zoomed();
      //virtual bool layout().is_full_screen();
      //void MoveWindow(i32 x, i32 y, i32 nWidth, i32 nHeight,
        //              bool bRepaint = TRUE);
      //void MoveWindow(const ::rect & rect, bool bRepaint = TRUE);

//      i32 SetWindowRgn(HRGN hRgn, bool bRedraw);
//      i32 GetWindowRgn(HRGN hRgn);


      virtual void _001OnExitIconic() override;
      virtual void _001OnExitFullScreen() override;
      virtual void _001OnExitZoomed() override;


      //virtual bool set_window_pos(iptr z, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags);
//      virtual UINT ArrangeIconicWindows();
      //virtual bool BringWindowToTop();
//      virtual bool get_window_rect(RECT64 * prect);

  //    virtual bool _001GetWindowRect(RECT64 * prect);

      //using ::user::interaction_impl::get_client_rect;
      //virtual bool get_client_rect(RECT64 * prect);


      virtual bool has_focus() override;
      virtual bool is_active() override;

      //virtual ::point client_screen_top_left() override;

//      virtual bool _001ClientToScreen(RECT * prect);

//      virtual bool _001ClientToScreen(LPPOINT ppoint);

//      virtual bool _001ClientToScreen(RECT64 * prect);

//      virtual bool _001ClientToScreen(POINT64 * ppoint);

//      virtual bool _001ScreenToClient(RECT * prect);

//      virtual bool _001ScreenToClient(LPPOINT ppoint);

//      virtual bool _001ScreenToClient(RECT64 * prect);

//      virtual bool _001ScreenToClient(POINT64 * ppoint);


      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);


      // Coordinate Mapping Fufnctions
//      virtual void MapWindowPoints(::user::interaction * pwndTo, LPPOINT pPoint, UINT nCount);
//
//      virtual void MapWindowPoints(::user::interaction * pwndTo, RECT * prect);


      // Update/Painting Functions
//      virtual ::draw2d::graphics * GetDC();
//      virtual ::draw2d::graphics * GetWindowDC();
//      virtual bool ReleaseDC(::image * pimage);
//      virtual void Print(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const;
//      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, DWORD dwFlags) const;

//      virtual void UpdateWindow();
//      virtual void SetRedraw(bool bRedraw = TRUE);
//      virtual bool GetUpdateRect(RECT * prect, bool bErase = FALSE);
//
//      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE);
//      virtual void Invalidate(bool bErase = TRUE);
//      virtual void InvalidateRect(const ::rect & rect, bool bErase = TRUE);
//
//      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE);
//      virtual void ValidateRect(const ::rect & rect);
//
//      virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual bool display(::edisplay edisplay) override;

//      virtual bool WfiOnStartDock();
//      virtual void WfiOnDock(edisplay edisplay);
//      virtual void prodevian_prepare_down();
//      virtual void prodevian_prepare_up();
//      virtual void WfiOnRestore();
//      virtual void WfiOnMinimize(bool bNoActivate);
//      virtual void WfiOnMaximize();
//      virtual void WfiOnFullScreen();
//      virtual void WfiOnExitFullScreen();
//      virtual void WfiOnClose();
//      virtual void WfiOnNotifyIcon();


      //virtual bool _is_window_visible() override;
      //virtual void ShowOwnedPopups(bool bShow = TRUE);

      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, DWORD flags);
      //virtual bool LockWindowUpdate();
      //virtual void UnlockWindowUpdate();
//      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,
//                                ::draw2d::region* prgnUpdate = nullptr,
//                                UINT flags = RDW_INVALIDATE | RDW_ERASE);
      // xxx      virtual bool EnableScrollBar(i32 nSBFlags, UINT nArrowFlags = ESB_ENABLE_BOTH);

      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

//
//      //virtual bool DrawAnimatedRects(i32 idAni, CONST LPRECTprcFrom, CONST LPRECTlprcTo);
//
//      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const rect & prc, UINT uFlags);
//
//
//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(DWORD tick, DWORD dwFlags);
//
//#endif   // WINVER >= 0x0500
//
//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, UINT nFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501

      // Layered oswindow
//
//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
//                                       ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500
//
//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501
//

//      // Timer Functions
//      virtual bool SetTimer(uptr uEvent, UINT nElapse, PFN_TIMER pfnTimer);
//      virtual bool KillTimer(uptr uEvent);

      // oswindow State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = TRUE);

      // the active ::user::interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow() override;
      virtual ::user::interaction * SetActiveWindow() override;

      // the foreground ::user::interaction_impl applies only to top-level windows (frame windows)
      virtual bool SetForegroundWindow() override;
      //static::user::interaction * PASCAL GetForegroundWindow();
//
//      virtual id SetDlgCtrlId(id id);
//      virtual id GetDlgCtrlId();



      // capture and focus apply to all windows
      //virtual ::user::interaction * GetCapture() override;
      //virtual bool SetCapture(::user::interaction * pinterface = nullptr) override;
      //virtual bool ReleaseCapture() override;
      //virtual ::user::interaction * get_capture();
      virtual ::user::interaction * GetFocus() override;
      virtual bool SetFocus() override;

      static::user::interaction * PASCAL get_desktop_window();

      // Obsolete and non-portable APIs - not recommended for new code
//      virtual void CloseWindow();
//      virtual bool OpenIcon();

      // Dialog-Box Item Functions
      // (NOTE: Dialog-Box Items/Controls are not necessarily in dialog boxes!)
//      virtual void CheckDlgButton(i32 nIDButton, UINT nCheck);
//      virtual void CheckRadioButton(i32 nIDFirstButton, i32 nIDLastButton,
//                                    i32 nIDCheckButton);
//      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton, i32 nIDLastButton);
//      virtual i32 DlgDirList(LPTSTR pPathSpec, i32 nIDListBox,
//
//                             i32 nIDStaticPath, UINT nFileType);
//      virtual i32 DlgDirListComboBox(LPTSTR pPathSpec, i32 nIDComboBox,
//
//                                     i32 nIDStaticPath, UINT nFileType);
//      virtual bool DlgDirSelect(LPTSTR pString, i32 nSize, i32 nIDListBox);
//
//      virtual bool DlgDirSelectComboBox(LPTSTR pString, i32 nSize, i32 nIDComboBox);


      //virtual UINT GetChildByIdInt(i32 nID, bool * pTrans = nullptr, bool bSigned = TRUE) const;

      //virtual i32 GetChildByIdText(i32 nID, LPTSTR pStr, i32 nMaxCount) const;

      //virtual i32 GetChildByIdText(i32 nID, string & rectString) const;
//      virtual ::user::interaction * GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const;
//      virtual ::user::interaction * GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious = FALSE) const;
//      virtual UINT IsDlgButtonChecked(i32 nIDButton) const;
//      virtual LRESULT SendDlgItemMessage(i32 nID, const ::id & id, WPARAM wParam = 0, LPARAM lParam = 0);
//      virtual void SetDlgItemInt(i32 nID, UINT nValue, bool bSigned = TRUE);
//      virtual void SetDlgItemText(i32 nID, const char * pszString);


//      // Scrolling Functions
//      virtual i32 GetScrollPos(i32 nBar) const;
//      virtual void GetScrollRange(i32 nBar, LPINT pMinPos, LPINT lpMaxPos) const;
//
//      virtual void ScrollWindow(i32 xAmount, i32 yAmount,
//                                const ::rect & rectClient = nullptr,
//                                const ::rect & rectClip = nullptr);
//
//      virtual i32 SetScrollPos(i32 nBar, i32 nPos, bool bRedraw = TRUE);
//      virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos,
//                                  bool bRedraw = TRUE);
//      virtual void ShowScrollBar(UINT nBar, bool bShow = TRUE);
//      virtual void EnableScrollBarCtrl(i32 nBar, bool bEnable = TRUE);
//      //      virtual CScrollBar* GetScrollBarCtrl(i32 nBar) const;
//      // return sibling scrollbar control (or nullptr if none)
//
//      virtual i32 ScrollWindowEx(i32 dx, i32 dy,
//                                 const rect & pRectScroll, const rect & lpRectClip,
//
//                                 ::draw2d::region* prgnUpdate, RECT * pRectUpdate, UINT flags);

      //xxx      virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo,

      //xxx         bool bRedraw = TRUE);
      //xxx      virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, UINT nMask = SIF_ALL);

//      virtual i32 GetScrollLimit(i32 nBar);
//
//      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point);
//      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point, UINT nFlags);
//      static::user::interaction * PASCAL FindWindow(const char * pszClassName, const char * pszWindowName);
//
//      static::user::interaction * FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * pszWindow);
//
//
//      virtual ::user::interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
//      virtual ::user::interaction * GetTopWindow() const;
//
//      virtual ::user::interaction * GetWindow(UINT nCmd);
//
//      virtual bool IsChild(::user::interaction *  pWnd);
//      virtual ::user::interaction * GetParent();
//      using ::user::interaction_impl::SetParent;
//      ::user::interaction * SetParent(::user::interaction * pWndNewParent);
//      static::user::interaction * PASCAL oswindowFromPoint(const ::point & point);


      //virtual i32 message_box(const char * pszText, const char * pszcaption = nullptr, UINT nType = MB_OK) override;




      virtual bool prodevian_update_screen() override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      DECL_GEN_SIGNAL(_001OnSetCursor);



      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual void message_handler(::message::base * pbase) override;

      virtual void default_window_procedure(::message::base * pbase);

      virtual void PostNcDestroy() override;

      virtual void on_final_release() override;

      //static void get_app_wnda(user::oswindow_array & wnda);

      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex, LONG_PTR lValue) override;

      //void _001OnTriggerMouseInside();


      //::user::interaction * get_next(bool bIgnoreChildren, i32 * piLevel);

      void show_task(bool bShow) override;

      virtual void non_top_most_upper_window_rects(::rect_array& recta) override;

   };


} // namespace linux




