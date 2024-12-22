#pragma once


namespace linux
{


   LRESULT CALLBACK __send_message_hook(int, WPARAM, LPARAM);
   // void _::ca2::StandardSubclass(oswindow);
   LRESULT CALLBACK __cbt_filter_hook(int, WPARAM, LPARAM);
   LRESULT __call_window_procedure(::user::interaction * pWnd, oswindow hWnd, unsigned int nMsg, WPARAM wParam, LPARAM lParam);


   class x11data;
   class interaction_impl :
      virtual public ::windowing::window
   {
   public:


      string                        m_strWindowText;
      ::user::interaction_base *    m_pbasewnd;
      bool                          m_bExposing;
      int                           m_iDepth;
      int                           m_iScreen;
      bool                          m_bEnabled;

      //::task_pointer                  m_pthreadDraw;
      ::rect64                      m_rectangleLastPos;
      ::duration m_durationLastPos;

      ::int_point                       m_pointLastMove;
      bool                          m_bMoveEvent;
      ::size                        m_sizeLastSize;
      bool                          m_bSizeEvent;
      ::duration                        m_durationLastPlacementEvent;


      interaction_impl();
      interaction_impl(::particle * pparticle);
      virtual ~interaction_impl();


      void linux_interaction_impl_common_construct();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //virtual void on_delete(::matter * poc);

      static const MESSAGE* PASCAL GetCurrentMessage();

      void install_message_routing(::channel * pchannel) override;

      bool operator==(const ::windowing::window& wnd) const;
      bool operator!=(const ::windowing::window& wnd) const;

      unsigned int GetStyle() const override;
      unsigned int GetExStyle() const override;
      bool ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags = 0) override;
      bool ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags = 0) override;

      //virtual ::user::interaction * get_owner();
      virtual void set_owner(::user::interaction * pOwnerWnd) override;

      virtual oswindow get_handle() const override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      DECLARE_MESSAGE_HANDLER(_001OnEraseBkgnd);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);


      virtual void window_show_change_visibility(::e_display edisplay, const ::user::activation & useractivation) override;


      virtual ::windowing::window * from_os_data(void * pdata) override;
      virtual void * get_os_data() const override;

      static user::interaction_impl * from_handle(oswindow hWnd);
      static user::interaction_impl * FromHandlePermanent(oswindow hWnd);
      //static void DeleteTempMap();
      bool Attach(oswindow hWndNew);
      oswindow Detach();

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
//      bool SubclassWindow(oswindow hWnd);
//      //bool SubclassDlgItem(unsigned int nID, ::pointer<::interaction_impl>pParent);
//      oswindow UnsubclassWindow();

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
//      bool ExecuteDlgInit(const ::scoped_string & scopedstrResourceName);
//
//      bool ExecuteDlgInit(LPVOID pResource);

      //virtual bool create_message_queue(::user::interaction * pinteraction, const char * lpszName) override;

//      using ::windowing::window::create_window;

      // for child windows, views, panes etc
//      virtual bool create_window(
//      ::user::interaction * pinteraction,
//      const ::scoped_string & scopedstrClassName,

//      const ::scoped_string & scopedstrWindowName,

//      unsigned int dwStyle,
//      const ::double_rectangle & rectangle,
//      ::user::interaction * pParentWnd,
//      atom atom,
//      ::create * pContext = nullptr) override;
//
//      // advanced creation (allows access to extended styles)
//      virtual bool create_window_ex(
//      ::user::interaction * pinteraction,
//      ::pointer<::user::system>pusersystem,
//      ::user::interaction * pParentWnd = nullptr,
//      atom atom = ::atom()) override;

    virtual bool _native_create_window_ex(::pointer<::user::system>pusersystem) override;


//      virtual bool native_create_window_ex(
//      ::user::interaction * pinteraction,
//      ::pointer<::user::system>pusersystem,
//      ::user::interaction * pParentWnd = nullptr,
//      atom atom = ::atom());

      virtual bool DestroyWindow() override;

      // special pre-creation and ::windowing::window rectangle adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem) override;

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
//      virtual void CalcWindowRect(RECT32 * pClientRect, unsigned int nAdjustType = adjustBorder);




      void _thread_delayed_placement();

      void defer_delayed_placement();


      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience) override;


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;




      virtual bool _is_window() const override;

#if(WINVER >= 0x0500)

      ::user::interaction * GetAncestor(unsigned int gaFlags) const;

#endif   // WINVER >= 0x0500

      LRESULT send_message(const ::atom & atom, WPARAM wParam = 0, lparam lparam = 0) override;

      bool post_message(const ::atom & atom, WPARAM wParam = 0, lparam lparam = 0) override;


//      bool SendNotifyMessage(const ::atom & atom, WPARAM wParam, lparam lParam);
//
//      bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);
//
//      bool DragDetect(const ::int_point & point) const;





      // oswindow Text Functions
      void set_window_text(const ::scoped_string & scopedstrString) override;

      //character_count GetWindowText(char * pszStringBuf, character_count nMaxCount);

      void get_window_text(string & str) override;
      //character_count GetWindowTextLength();
      void SetFont(::write_text::font* pFont, bool bRedraw = true);
      ::write_text::font* GetFont();


      // oswindow size and position Functions
      virtual bool node_is_iconic() override;
      //virtual bool layout().is_zoomed();
      //virtual bool layout().is_full_screen();
      //void MoveWindow(int x, int y, int nWidth, int nHeight,
        //              bool bRepaint = true);
      //void MoveWindow(const ::double_rectangle & rectangle, bool bRepaint = true);

//      int SetWindowRgn(HRGN hRgn, bool bRedraw);
//      int GetWindowRgn(HRGN hRgn);


      virtual void _001OnExitIconic() override;
      virtual void _001OnExitFullScreen() override;
      virtual void _001OnExitZoomed() override;


      //virtual bool set_window_position(iptr z, int x, int y, int cx, int cy, unsigned int nFlags);
//      virtual unsigned int ArrangeIconicWindows();
      //virtual bool BringWindowToTop();
//      virtual bool window_rectangle(RECT64 * prect);

  //    virtual bool _001GetWindowRect(RECT64 * prect);

      //using ::windowing::window::this->rectangle;
      //virtual bool this->rectangle(RECT64 * prect);


      virtual bool has_focus() override;
      virtual bool is_active() override;

      //virtual ::int_point client_screen_top_left() override;

//      virtual bool client_to_screen(RECT32 * prect);

//      virtual bool client_to_screen(POINT32 * ppoint);

//      virtual bool client_to_screen(RECT64 * prect);

//      virtual bool client_to_screen(POINT64 * ppoint);

//      virtual bool screen_to_client(RECT32 * prect);

//      virtual bool screen_to_client(POINT32 * ppoint);

//      virtual bool screen_to_client(RECT64 * prect);

//      virtual bool screen_to_client(POINT64 * ppoint);


      virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);


      // Coordinate Mapping Fufnctions
//      virtual void MapWindowPoints(::user::interaction * puserinteractionTo, POINT32 * pPoint, unsigned int nCount);
//
//      virtual void MapWindowPoints(::user::interaction * puserinteractionTo, RECT32 * prect);


      // Update/Painting Functions
//      virtual ::draw2d::graphics * GetDC();
//      virtual ::draw2d::graphics * GetWindowDC();
//      virtual bool ReleaseDC(::image::image *pimage);
//      virtual void Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const;
//      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const;

//      virtual void UpdateWindow();
//      virtual void SetRedraw(bool bRedraw = true);
//      virtual bool GetUpdateRect(RECT32 * prect, bool bErase = false);
//
//      virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
//      virtual void Invalidate(bool bErase = true);
//      virtual void InvalidateRect(const ::double_rectangle & rectangle, bool bErase = true);
//
//      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
//      virtual void ValidateRect(const ::double_rectangle & rectangle);
//
//      virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual bool display(::e_display edisplay) override;

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
      //virtual void ShowOwnedPopups(bool bShow = true);

      //virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip, unsigned int flags);
      //virtual bool LockWindowUpdate();
      //virtual void UnlockWindowUpdate();
//      virtual bool RedrawWindow(const ::double_rectangle& rectangleUpdate = nullptr,
//                                ::draw2d::region* prgnUpdate = nullptr,
//                                unsigned int flags = RDW_INVALIDATE | RDW_ERASE);
      // xxx      virtual bool EnableScrollBar(int nSBFlags, unsigned int nArrowFlags = ESB_ENABLE_BOTH);

      virtual void set_context_org(::draw2d::graphics_pointer & pgraphics) override;

//
//      //virtual bool DrawAnimatedRects(int idAni, const LPRECTprcFrom, const LPRECTlprcTo);
//
//      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics, const rectangle & prc, unsigned int uFlags);
//
//
//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(unsigned int ::duration, unsigned int dwFlags);
//
//#endif   // WINVER >= 0x0500
//
//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics, unsigned int nFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501



//      // Timer Functions
//      virtual bool SetTimer(uptr uEvent, unsigned int nElapse, PFN_TIMER pfnTimer);
//      virtual bool KillTimer(uptr uEvent);

      // oswindow State Functions
      virtual bool IsWindowEnabled();
      virtual bool EnableWindow(bool bEnable = true);

      // the active ::windowing::window applies only to top-level (frame windows)
      virtual ::user::interaction * get_active_window() override;
      virtual ::user::interaction * set_active_window() override;

      // the foreground ::windowing::window applies only to top-level windows (frame windows)
      virtual bool set_foreground_window() override;



      virtual ::user::interaction * GetFocus() override;
      virtual bool set_keyboard_focus() override;

      static::user::interaction * PASCAL get_desktop_window();


      virtual bool prodevian_update_screen() override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(_001OnPrint);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);



      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual void message_handler(::user::message * pusermessage) override;

      virtual void default_window_procedure(::user::message * pusermessage);

      virtual void post_non_client_destroy() override;

      virtual void on_final_release() override;

      //static void get_app_wnda(user::oswindow_array & wnda);

      virtual LONG_PTR get_window_long_ptr(int nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(int nIndex, LONG_PTR lValue) override;

      //void _001OnTriggerMouseInside();


      //::user::interaction * get_next(bool bIgnoreChildren, int * piLevel);

      void show_task(bool bShow) override;

      virtual void non_top_most_upper_window_rects(::int_rectangle_array& recta) override;

   };


} // namespace linux




