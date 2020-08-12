#pragma once


namespace user
{


   class CLASS_DECL_AURA primitive :
      virtual public elemental,
      virtual public style
   {
   public:


      enum RepositionFlags
      {

         reposDefault = 0,
         reposQuery = 1,
         reposExtra = 2,
         reposNoPosLeftOver = 0x8000

      };


      enum EProperty
      {

         PropertyBaseWndInterface = 0,
         PropertyDrawBaseWndInterface

      };


      enum EGeneralEvent
      {

         GeneralEventPosCreate1,
         GeneralEventPosCreate2,
         GeneralEventPosCreate3,
         GeneralEventPosCreate4,
         GeneralEventPosCreate5

      };

      enum e_type
      {

         type_window,
         type_frame,
         type_view

      };

      enum EOptimize
      {

         OptimizeNone,
         OptimizeThis

      };

      enum AdjustType
      {

         adjustBorder = 0,
         adjustOutside = 1

      };


      primitive();
      primitive(::object * pobject);
      virtual ~primitive();


      virtual void _001OnTimer(::timer * ptimer) override;


      virtual bool create_message_queue(const char * lpszName);

      virtual void set_config_fps(double dConfigFps);
      virtual double get_config_fps();
      virtual double get_output_fps();

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

      virtual bool initialize_native_window(::user::native_window_initialize * pinitialize);

#endif

      __pointer(::message::base) get_message_base(UINT uiMessage, WPARAM wparam, lparam lparam);



      virtual bool enable_window(bool bEnable = true) override;
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void PreSubClassWindow();


      virtual DECL_GEN_SIGNAL(_008GetWindowText);
      virtual DECL_GEN_SIGNAL(_008GetWindowTextLength);
      virtual strsize _009GetWindowText(char * psz, int n);
      virtual strsize _009GetWindowTextLength();

      //virtual pointd client_screen_top_left();

      //virtual bool GetFocusRect(RECT * prect);

      //using ::user::primitive::get_client_rect;
      //using ::user::primitive::get_window_rect;

      //virtual bool _get_client_size(SIZE * psize) override;
      //virtual bool _get_window_size(SIZE * psize) override;

      //virtual bool SetPlacement(const ::rect & rect,UINT nFlags = SWP_SHOWWINDOW) override;


      virtual bool add_prodevian(::context_object * pobject);
      virtual bool remove_prodevian(::context_object * pobject);



      //virtual bool defer_set_window_pos(iptr z,i32 x,i32 y,i32 cx,i32 cy,UINT nFlags); // only set_windows_pos if GetParent()->screen_to_client(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(RECT * prect);

      //virtual i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual i32 GetWindowRgn(HRGN hRgn);


      virtual void install_message_routing(::channel * pchannel) override;

//      virtual void _on_start_user_message_handler() override;


      virtual void UpdateWindow();
      virtual void Invalidate(bool bErase = TRUE);

      virtual bool has_pending_redraw_flags();


      virtual bool RedrawOptimize(RECT * prectOut,const rect & lpcrect1,const rect & lpcrect2);

      virtual void RedrawOptimize(rect_array & array);

      void Optimize008(::user::oswindow_tree::Array & oswindowtreea, const ::rect & rect);

      EOptimize Optimize008(::user::oswindow_tree::Array & oswindowtreea, HRGN hrgn);

      EOptimize Optimize008(::user::oswindow_tree & oswindowtree, HRGN hrgn);



      void TwfGetWndArray(::user::interaction_pointer_array & wndpa);
      void TwfGetWndArray(::user::oswindow_array & oswindowa);

      virtual bool Redraw(rect_array & recta);
      virtual bool Redraw(const ::rect & rect = nullptr, ::draw2d::region * prgn = nullptr);

      virtual bool Redraw(::draw2d::graphics_pointer & pgraphics);

      void _001BaseWndInterfaceMap();

      virtual void message_handler(::message::base * pbase) override;
      virtual LRESULT message_handler(LPMESSAGE pmessage);

      virtual void on_select();

      virtual bool is_place_holder();

      e_cursor get_cursor();
      void set_cursor(e_cursor ecursor);


//      void set_timer(__pointer_array(::aura::timer_item) timera);


      virtual bool _is_window() const override;

      virtual LONG get_window_long(i32 nIndex) const;
      virtual LONG set_window_long(i32 nIndex,LONG lValue);

      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex,LONG_PTR lValue);



      virtual ::user::interaction * first_child();
      virtual ::user::interaction * last_child();
      virtual ::user::interaction * last_sibling();
      virtual ::user::interaction * next_sibling();
      virtual ::user::interaction * previous_sibling();
      virtual ::user::interaction * first_sibling();
      virtual ::user::interaction * next_sibling(::user::interaction * pinteraction);
      virtual ::user::interaction * previous_sibling(::user::interaction * pinteraction);

      virtual ::user::interaction * bottom_child();
      virtual ::user::interaction * top_child();
      virtual ::user::interaction * bottom_sibling();
      virtual ::user::interaction * under_sibling();
      virtual ::user::interaction * above_sibling();
      virtual ::user::interaction * top_sibling();
      virtual ::user::interaction * above_sibling(::user::interaction * pinteraction);
      virtual ::user::interaction * under_sibling(::user::interaction * pinteraction);




      virtual void mouse_hover_add(::user::interaction * pinterface);
      virtual bool mouse_hover_remove(::user::interaction * pinterface);


      virtual bool CheckAutoCenter();

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();

      // dialog support
      virtual void update_dialog_controls(channel * ptarget);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      virtual id   run_modal_loop(::user::interaction * pinteraction, u32 dwFlags = 0);
      virtual id   RunModalLoop(u32 dwFlags = 0);
      virtual id   _001RunModalLoop(u32 dwFlags = 0);
      virtual bool ContinueModal();
      virtual void EndModalLoop(id nResult);

      virtual void on_control_event(::user::control_event * pevent) override;

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true);


      virtual ::user::interaction * GetFocus();


      virtual bool on_keyboard_focus(::user::primitive * pfocus) override;



      virtual void _001UpdateWindow();
      virtual void window_apply_visual(const window_state & windowstate);


      virtual bool prodevian_update_visual();

      virtual void prodevian_stop();

      virtual void prodevian_prepare_window_minimize(::eactivation eactivation);
      virtual void prodevian_prepare_window_maximize();
      virtual void prodevian_prepare_window_full_screen(const ::rect & rectHint = nullptr);
      virtual void prodevian_prepare_window_restore(edisplay edisplay);
      virtual void prodevian_prepare_window_dock(edisplay edisplayDock);


      virtual void prodevian_redraw();

      virtual void on_start_layout_experience(e_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(e_layout_experience elayoutexperience);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();
      virtual void on_show_window();

      virtual void _do_show_window();

      //virtual void BringToTop(edisplay edisplay);
      //virtual bool BringWindowToTop();

#ifdef WINDOWS_DESKTOP
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);

#endif

      //virtual bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);


      virtual bool pre_create_window(::user::create_struct& cs);


      virtual bool subclass_window(oswindow posdata);
      virtual oswindow unsubclass_window();


      virtual bool create_window(::user::interaction * pparent, const ::id & id);
      virtual bool create_window(const char * pszClassName, const char * pszWindowName,u32 uStyle, ::user::interaction * puiParent, const ::id & id, ::create * pcreate = nullptr);

      virtual bool create_window_ex(::user::create_struct & cs, ::user::interaction * puiParent, const ::id & id);
      virtual void CalcWindowRect(RECT * pClientRect,UINT nAdjustType = adjustBorder);


      virtual bool IsTopParentActive();
      virtual void ActivateTopParent();

      virtual bool DestroyWindow();

      virtual void destroy_window();


#ifdef WINDOWS

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, UINT flags = RDW_INVALIDATE | RDW_ERASE);

#else

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, UINT flags = 0);

#endif


//      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      virtual bool GetUpdateRect(RECT * prect,bool bErase = FALSE);

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE);
//      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(const ::rect & rect,bool bErase = TRUE);

      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE);
      virtual void ValidateRect(const ::rect & rect);

      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = TRUE);


      virtual u32 GetStyle() const;
      virtual u32 GetExStyle() const;
      virtual LRESULT Default();

      virtual LRESULT send(::message::base * pbase);
      virtual bool post(::message::base * pbase);

      virtual LRESULT send_message(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0) override;

      virtual LRESULT message_call(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0);
      virtual LRESULT message_call(::message::base * pbase);


#ifdef LINUX

      virtual LRESULT send_x11_event(void * pevent); // pevent <= XEvent *

#endif

      virtual bool post_message(UINT message,WPARAM wParam = 0,lparam lParam = 0) override;

      virtual bool post_simple_command(const esimplecommand & ecommand,lparam lParam = 0);


      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,UINT nFlags = 0);
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags = 0);
      //virtual bool _display(edisplay edisplay);

      virtual void SetWindowDisplayChanged();

      // timer Functions
      virtual bool SetTimer(uptr nIDEvent,UINT nElapse,PFN_TIMER pfnTimer);
      virtual bool KillTimer(uptr nIDEvent);

      virtual void _001Print(::draw2d::graphics_pointer & pgraphics);
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics);
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics);


      virtual bool IsAscendant(const interaction * puiIsAscendant) const;
      virtual bool IsParent(const interaction * puiIsParent) const;
      virtual bool IsChild(const interaction * puiIsChild) const;
      virtual bool IsDescendant(const interaction * puiIsDescendant) const;


      virtual id GetDlgCtrlId() const;
      virtual id SetDlgCtrlId(::id id);

      virtual bool SetCapture(::user::interaction * pinteraction = nullptr);
      virtual bool ReleaseCapture();
      virtual ::user::interaction * GetCapture();



      virtual bool has_focus() override;
      virtual bool SetFocus();
      virtual bool SetForegroundWindow();
      virtual bool is_active();
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();


      virtual void set_window_text(const char * pszString) override;

      virtual strsize get_window_text(char * pszStringBuf,strsize nMaxCount);

      virtual string get_window_text();
      virtual void get_window_text(string & rString);
      virtual strsize get_window_text_length();


      //virtual bool _is_window_visible();
      //virtual bool is_this_visible();
      virtual bool is_window_enabled();
      virtual bool is_this_enabled();




      virtual bool _001IsPointInside(::point point);
      virtual ::user::interaction * _001FromPoint(::point point,bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz,const char * pszTarget = nullptr);

      ::user::interaction * get_child_by_name(const char * lpszName,i32 iLevel = -1);
      ::user::interaction * get_child_by_id(id id,i32 iLevel = -1);


      virtual ::user::interaction * get_wnd() const override;
      virtual ::user::interaction * get_wnd(UINT nCmd) const;
      virtual ::user::interaction_impl * get_impl() const override;
      virtual ::thread * get_thread() const;

      virtual ::user::interaction * SetParent(::user::interaction * pinteraction);
      virtual ::user::interaction * SetOwner(::user::interaction * pinteraction);


      virtual ::user::interaction * GetTopWindow() const;
      virtual ::user::interaction * GetParent() const override;
      virtual ::user::interaction * GetTopLevel() const;
      virtual ::user::interaction * GetParentTopLevel() const;
      virtual ::user::interaction * EnsureTopLevel();
      virtual ::user::interaction * EnsureParentTopLevel();
      virtual ::user::interaction * GetOwner() const;
      virtual ::user::interaction * GetParentOwner() const;
      virtual ::user::interaction * GetParentOrOwner() const;
      virtual ::user::interaction * GetTopLevelOwner() const;
      virtual ::user::frame * GetFrame() const;
      virtual ::user::frame * GetParentFrame() const;
      virtual ::user::frame * GetTopLevelFrame() const;
      virtual ::user::frame * GetParentTopLevelFrame() const;
      virtual ::user::frame * EnsureParentFrame();
      virtual ::user::frame * GetOwnerFrame() const;



      virtual void send_message_to_descendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE);

      virtual void route_message_to_descendants(::message::message * pmessage);
      virtual void pre_translate_message(::message::message * pmessage) override;


      virtual i32 get_descendant_level(::user::interaction * pinteraction);
      virtual bool is_descendant(::user::interaction * pinteraction,bool bIncludeSelf = false);
      virtual ::user::interaction * get_focusable_descendant(::user::interaction * pinteraction = nullptr);

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, ::id idLeftOver, UINT nFlag = reposDefault, RECT * prectParam = nullptr, const ::rect & rectClient = nullptr, bool bStretch = true);

      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point);
      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point,UINT nFlags);


#ifdef WINDOWS_DESKTOP
      virtual ::user::interaction * get_next_window(UINT nFlag = GW_HWNDNEXT);
#else
      virtual ::user::interaction * get_next_window(UINT nFlag = 0);
#endif

      virtual ::user::interaction * get_next(bool bIgnoreChildren = false,i32 * piLevel = nullptr);

      virtual ::user::interaction * GetLastActivePopup();

      virtual bool is_message_only_window() const;

      virtual void pre_subclass_window();

      virtual void PostNcDestroy();

      virtual LRESULT DefWindowProc(UINT uiMessage, WPARAM wparam, lparam lparam);


      virtual LRESULT call_message_handler(UINT uiMessage, WPARAM wparam, lparam lparam);


      virtual void GuieProc(::message::message * pmessage);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;


      oswindow get_safe_handle() const;
      virtual oswindow get_handle() const override;
      virtual bool attach(oswindow oswindow_New);
      virtual oswindow detach();


      virtual bool can_merge(::user::interaction * pinteraction);
      virtual bool merge(::user::interaction * pinteraction);


      virtual void _001OnTriggerMouseInside();

      virtual void _000OnMouseLeave(::message::message* pmessage);

      //#ifdef _UWP
      //      Agile<Windows::UI::Core::CoreWindow> get_os_window();
      //#endif


      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics);

      virtual void viewport_screen_to_client(POINT * ppt);
      virtual void viewport_client_to_screen(POINT * ppt);
      virtual void viewport_client_to_screen(RECT * ppt);
      virtual void viewport_screen_to_client(RECT * ppt);


      virtual string get_window_default_matter();
      virtual string get_window_icon_matter();
      virtual u32 get_window_default_style();
      virtual e_type get_window_type();


      virtual void on_simple_command(::message::simple_command * psimplecommand);
      virtual void on_command(::user::command * pcommand) override;


      // Window-Management message handler member functions
      virtual bool OnCommand(::message::base * pbase);
      virtual bool OnNotify(::message::base * pbase);
      virtual bool OnChildNotify(::message::base * pbase);



      virtual bool is_selected(::data::item * pitem);

      virtual __pointer(place_holder) place_hold(::user::interaction * pinteraction);

      virtual bool has_command_handler(::user::command * pcommand) override;



      virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point & point);
      virtual __pointer(::user::menu) track_popup_menu(::xml::node * pnode,i32 iFlags, const ::point & point, const ::size & sizeMinimum = size(0, 0));

      virtual bool track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags, const ::point & point);
      virtual __pointer(::user::menu) track_popup_xml_string_menu(var varXml, i32 iFlags, const ::point & point, const ::size& sizeMinimum = size(0, 0));

      virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage);
      virtual bool track_popup_menu(::xml::node * pnode,i32 iFlags,::message::message * pmessage);

      virtual bool track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags,::message::message * pmessage);

      virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags);
      virtual bool track_popup_menu(::xml::node * pnode,i32 iFlags);

      virtual bool track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags);


      //virtual void exit_iconify();
      //virtual void exit_full_screen();


      //virtual void defer_exit_iconify();
      //virtual void defer_exit_full_screen();


      //virtual void window_enable_full_screen(bool bEnable = true);
      //virtual bool window_is_full_screen();
      //virtual bool window_is_full_screen_enabled();
      //virtual bool window_is_zoomed();
      //virtual bool window_is_iconic();

      //virtual bool display(edisplay edisplay);

      //virtual edisplay get_display();
      //virtual edisplay get_previous_display();


      //virtual bool defer_set_appearance(edisplay edisplay);
      //virtual bool set_appearance(edisplay edisplay);
      //virtual bool set_previous_display(edisplay edisplay);


      virtual void show_keyboard(bool bShow = true);

      virtual void keep_alive(::object * pliveobject = nullptr);


      virtual window_graphics * get_window_graphics() override;


      virtual bool is_composite() override;


      //virtual void _user_message_handler(::message::message * pmessage);

      //virtual PFN_DISPATCH_MESSAGE_HANDLER _calc_user_message_handler();

      virtual bool has_pending_graphical_update();
      virtual void on_after_graphical_update();

      virtual void set_ipc_copy(bool bSet = true);


      virtual bool WfiOnStartDock();
      virtual void WfiOnDock(edisplay edisplay);
      virtual void prodevian_prepare_down();
      virtual void prodevian_prepare_up();
      virtual void WfiOnRestore();
      virtual void WfiOnMinimize(bool bNoActivate);
      virtual void WfiOnMaximize();
      virtual void WfiOnFullScreen();
      virtual void WfiOnClose();
      virtual void WfiOnNotifyIcon();

      virtual void _001OnExitIconic();
      virtual void _001OnExitFullScreen();
      virtual void _001OnExitZoomed();


   };


} // namespace user



