#pragma once


namespace user
{

   enum enum_next
   {

      e_next_sibling,
      e_next_proper,


   };


   class CLASS_DECL_AURA primitive :
      virtual public channel,
      virtual public ::user::callback,
      virtual public ::aura::drawable,
      virtual public ::user::check,
      virtual public ::user::text
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

      enum enum_type
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


      bool                          m_bFocus;
      millis                        m_millisFocusStart;
      bool                          m_bUserPrimitiveOk;


      primitive();
      virtual ~primitive();


      virtual ::user::callback* get_user_callback();


      virtual void _001OnTimer(::timer * ptimer);


      virtual bool create_message_queue(const char * lpszName);


      virtual void set_config_fps(double dConfigFps);
      virtual double get_config_fps();
      virtual double get_output_fps();


      __pointer(::message::base) get_message_base(oswindow oswindow, const ::id & id, WPARAM wparam, lparam lparam) override;


      virtual ::user::interaction* get_host_window() const;


      virtual bool enable_window(bool bEnable = true);
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void PreSubClassWindow();


      virtual DECL_GEN_SIGNAL(_008GetWindowText);
      virtual DECL_GEN_SIGNAL(_008GetWindowTextLength);
#ifdef WINDOWS
      virtual strsize _009GetWindowText(wchar_t * pwsz, int n);
#else
      virtual strsize _009GetWindowText(char * psz, int n);
#endif
      virtual strsize _009GetWindowTextLength();

      virtual bool GetFocusRect(RECT32 * prect);

      virtual void defer_update_display();

      
      virtual enum_control_type get_control_type() const;


      virtual bool add_prodevian(::context_object * pobject);
      virtual bool remove_prodevian(::context_object * pobject);

      virtual bool display(::e_display edisplay = e_display_default, ::e_activation eactivation = e_activation_default);

      
      virtual string get_title();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual ::e_status show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd);

      virtual ::e_status hide_software_keyboard(::user::primitive * pprimitive);

      virtual void UpdateWindow();
      
      virtual void Invalidate(bool bErase = TRUE);

      virtual bool has_pending_redraw_flags();

      virtual bool set_icon(::draw2d::icon * picon, bool bSmall);

      virtual void default_message_handler(::message::message * pmessage);

      virtual void message_handler(::message::base * pbase);

      virtual LRESULT message_handler(LPMESSAGE pmessage);

      virtual void on_select();

      virtual bool is_place_holder();

      virtual double _001GetTopLeftWeightedOccludedOpaqueRate();

      virtual e_cursor get_cursor();

      virtual bool set_cursor(e_cursor ecursor);

      virtual ::point get_cursor_pos() const;

      virtual bool _is_window() const;

      virtual ::i32 get_window_long(i32 nIndex) const;
      virtual ::i32 set_window_long(i32 nIndex,::i32 lValue);

      virtual iptr get_window_long_ptr(i32 nIndex) const;
      virtual iptr set_window_long_ptr(i32 nIndex, iptr lValue);

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

      virtual void update_dialog_controls(channel * ptarget);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      virtual id run_modal_loop(::user::interaction * pinteraction, u32 dwFlags = 0);
      virtual id RunModalLoop(u32 dwFlags = 0);
      virtual id _001RunModalLoop(u32 dwFlags = 0);
      virtual bool ContinueModal();
      virtual void EndModalLoop(id nResult);


      virtual void route_control_event(::user::control_event* pevent);
      virtual void on_control_event(::user::control_event * pevent) override;

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true);


      virtual ::user::primitive * get_keyboard_focus();


      virtual bool on_keyboard_focus(::user::primitive * pfocus);



      virtual void _001UpdateWindow();

      //virtual void window_apply_visual(const window_state & windowstate);


      virtual void sketch_to_design(::draw2d::graphics_pointer& pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow);

      virtual void design_down();
      virtual void design_up();

      virtual void prodevian_stop();

      virtual void sketch_prepare_window_minimize(::e_activation eactivation);
      virtual void sketch_prepare_window_maximize();
      virtual void sketch_prepare_window_full_screen(const ::rect & rectHint = nullptr);
      virtual void sketch_prepare_window_restore(edisplay edisplay);
      virtual void sketch_prepare_window_dock(edisplay edisplayDock);


      virtual void prodevian_redraw(bool bUpdateBuffer);

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience);


      virtual void on_configuration_change(::user::primitive * pprimitiveSource);


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();
      virtual void on_show_window();

      //virtual void BringToTop(edisplay edisplay);
      //virtual bool BringWindowToTop();

#ifdef WINDOWS_DESKTOP
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);

#endif

      //virtual bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);


      virtual bool pre_create_window(::user::system * pusersystem);


      virtual bool subclass_window(oswindow posdata);
      virtual oswindow unsubclass_window();

      virtual string get_class_name();

      
      virtual bool create_interaction(::user::interaction * puserinteractionParent, const ::id & id = nullptr);


      virtual bool create_host();
      virtual bool create_child(::user::interaction * puserinteractionParent);
      virtual bool create_control(::user::interaction * puserinteractionParent, const ::id & id);

      //virtual bool create_window_ex(__pointer(::user::system_struct) pcs, ::user::interaction * puiParent, const ::id & id);
      virtual void CalcWindowRect(RECT32 * pClientRect,::u32 nAdjustType = adjustBorder);


      virtual bool IsTopParentActive();
      virtual void ActivateTopParent();

      virtual bool DestroyWindow();

      virtual void destroy_window();


#ifdef WINDOWS

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = RDW_INVALIDATE | RDW_ERASE);

#else

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = 0);

#endif


//      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      virtual bool GetUpdateRect(RECT32 * prect,bool bErase = FALSE);

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE);
//      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(const ::rect & rect,bool bErase = TRUE);

      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE);
      virtual void ValidateRect(const ::rect & rect);

      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = TRUE);


      virtual u32 GetStyle() const;
      virtual u32 GetExStyle() const;


      virtual ::e_status main_async(const ::promise::routine & routine, e_priority epriority = priority_normal);


      //using ::channel::send;
      virtual LRESULT send(::message::base * pbase);
      virtual bool post(::message::base * pbase);

      virtual LRESULT send_message(const ::id & id, WPARAM wparam = 0, lparam lparam = 0);

      virtual LRESULT message_call(const ::id & id, WPARAM wparam = 0, lparam lparam = 0);
      virtual LRESULT message_call(::message::base * pbase);


#ifdef LINUX

      virtual LRESULT send_x11_event(void * pevent); // pevent <= XEvent *

#endif

      virtual bool post_message(const ::id & id,WPARAM wParam = 0,lparam lParam = 0);

      virtual bool post_simple_command(const e_simple_command & ecommand,lparam lParam = 0);

      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool _display(edisplay edisplay);

      //virtual void SetWindowDisplayChanged();

      // timer Functions
      virtual bool SetTimer(uptr uEvent, ::millis millisElapse, PFN_TIMER pfnTimer);
      virtual bool KillTimer(uptr uEvent);

      virtual void _001PrintBuffer(::draw2d::graphics_pointer & pgraphics);
      virtual void _001Print(::draw2d::graphics_pointer & pgraphics);
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics);
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics);


      virtual bool is_ascendant(const primitive * puiIsAscendant, bool bIncludeSelf) const;
      virtual bool is_parent(const primitive * puiIsParent) const;
      virtual bool is_child(const primitive * puiIsChild) const;
      virtual bool is_descendant(const primitive * puiIsDescendant, bool bIncludeSelf) const;

      virtual bool is_descendant_of_or_owned_by(const ::user::primitive * puiAscendantCandidate, bool bIncludeSelf) const;
      virtual bool is_ascendant_or_owner_of(const ::user::primitive * puiDescendantCandidate, bool bIncludeSelf) const;

      virtual bool is_ascendant_of(const primitive * puiIsDescendant, bool bIncludeSelf) const;
      virtual bool is_parent_of(const primitive * puiIsChild) const; 
      virtual bool is_child_of(const primitive * puiIsParent) const; 
      virtual bool is_descendant_of(const primitive * puiIsAscendant, bool bIncludeSelf) const; 

      virtual id GetDlgCtrlId() const;
      virtual id SetDlgCtrlId(::id id);


#ifdef WINDOWS_DESKTOP

      virtual bool open_clipboard();
      virtual bool close_clipboard();

#endif


      virtual bool SetCapture(::user::interaction * pinteraction = nullptr);
      virtual bool ReleaseCapture();
      virtual ::user::interaction * GetCapture();


      



      virtual bool has_focus();
      virtual bool SetFocus();
      virtual bool SetForegroundWindow();
      virtual bool is_active();
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();


      virtual void edit_on_set_focus(::user::interaction* pinteraction);
      virtual void edit_on_kill_focus(::user::interaction* pinteraction);

      virtual void set_window_text(const char * pszString);

      virtual strsize get_window_text(char * pszStringBuf,strsize nMaxCount);

      virtual string get_window_text();
      virtual void get_window_text(string & rString);
      virtual strsize get_window_text_length();


      //virtual bool _is_window_visible();
      virtual bool is_this_visible(enum_layout elayout);
      virtual bool is_window_enabled() const;
      virtual bool is_this_enabled() const;




      virtual bool _001IsPointInside(::point point);
      virtual ::user::interaction * _001FromPoint(::point point,bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz,const char * pszTarget = nullptr);

      ::user::interaction * get_child_by_name(const char * lpszName,i32 iLevel = -1);
      ::user::interaction * get_child_by_id(id id,i32 iLevel = -1);


      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction * get_wnd(::u32 nCmd) const;
      virtual ::user::interaction_impl * get_impl() const;
      virtual ::thread * get_task() const;

      virtual ::user::primitive * set_parent(::user::primitive * pinteraction);
      virtual ::user::primitive * set_owner(::user::primitive * pinteraction);


      virtual ::user::frame * frame() const;
      virtual ::user::frame * top_level_frame() const;


      virtual ::user::interaction * get_parent() const;
      virtual ::user::interaction * get_top_level() const;
      virtual ::user::interaction * get_owner() const;
      virtual ::user::interaction * get_parent_owner() const;
      virtual ::user::interaction * get_parent_or_owner() const;
      virtual ::user::interaction * get_top_level_owner() const;
      virtual ::user::frame * get_parent_frame() const;
      virtual ::user::frame * get_owner_frame() const;

      virtual bool is_top_level_window() const;

      virtual void send_message_to_descendants(const ::id & id,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE);

      virtual void route_message_to_descendants(::message::message * pmessage);
      virtual void pre_translate_message(::message::message * pmessage);


      virtual i32 get_descendant_level(const ::user::primitive * pinteraction) const;
      //virtual bool is_descendant(const ::user::primitive * pinteraction,bool bIncludeSelf = false) const;
      virtual ::user::interaction * get_focusable_descendant() const;

      virtual void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::id idLeftOver, ::u32 nFlag = reposDefault, RECT32 * prectParam = nullptr, const ::rect & rectClient = nullptr, bool bStretch = true);

      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point);
      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point,::u32 nFlags);


//#ifdef WINDOWS_DESKTOP
  //    virtual ::user::interaction * get_next_window(::u32 nFlag = GW_HWNDNEXT);
//#else
      //virtual ::user::interaction * get_next_window(::u32 nFlag = 0);

      virtual ::user::interaction * get_next_sibling_window();

//#endif

      virtual ::e_status set_tool_window(bool bSet = true);

      
      virtual ::user::interaction * get_next_window(bool bIgnoreChildren = false, const ::user::interaction * puiInteractionStop = nullptr) const;
      virtual ::user::interaction * get_window(enum_next enext) const;


      virtual ::user::interaction * GetLastActivePopup();


      virtual bool is_message_only_window() const;

      virtual void pre_subclass_window();

      virtual void PostNcDestroy();


      //virtual LRESULT default_window_procedure();
      //virtual void default_window_procedure(::message::message * pbase);


      virtual bool call_message_handler(const ::id & id, WPARAM wparam = 0, lparam lparam = 0, LRESULT * presult = nullptr);


      virtual void GuieProc(::message::message * pmessage);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;


      oswindow get_safe_handle() const;
      virtual oswindow get_handle() const override;
      virtual bool attach(oswindow oswindow_New);
      virtual oswindow detach();

      
      virtual ::sized _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics);
      virtual ::sized _001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics);


      virtual bool can_merge(::user::interaction * pinteraction);
      virtual bool merge(::user::interaction * pinteraction);


      virtual void _001OnTriggerMouseInside();

      virtual void _000OnMouseLeave(::message::message* pmessage);

      //#ifdef _UWP
      //      Agile<Windows::UI::Core::CoreWindow> get_os_window();
      //#endif


      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics);

      virtual void viewport_screen_to_client(POINT32 * ppt);
      virtual void viewport_client_to_screen(POINT32 * ppt);
      virtual void viewport_client_to_screen(RECT32 * ppt);
      virtual void viewport_screen_to_client(RECT32 * ppt);


      virtual string get_window_default_matter();
      virtual string get_window_icon_matter();
      virtual u32 get_window_default_style();
      virtual enum_type get_window_type();


      virtual void on_simple_command(::message::simple_command * psimplecommand);
      virtual void on_command(::user::command * pcommand) override;


      // Window-Management message handler member functions
      virtual bool OnCommand(::message::base * pbase);
      virtual bool OnNotify(::message::base * pbase);
      virtual bool OnChildNotify(::message::base * pbase);



      virtual bool is_selected(::data::item * pitem);

      //virtual __pointer(place_holder) place_hold(::user::interaction * pinteraction);

      virtual bool has_command_handler(::user::command * pcommand) override;



      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point & point = nullptr);
      //virtual __pointer(::user::menu) track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags, const ::point & point);
      //virtual __pointer(::user::menu) track_popup_xml_menu(const ::payload & varXml, i32 iFlags, const ::point & pointScreen = nullptr, const ::size& sizeMinimum = size(0, 0));
      //virtual __pointer(::user::menu) track_popup_xml_menu_file(::payload varFile, i32 iFlags, const ::point & point = nullptr, const ::size & sizeMinimum = size(0, 0));

      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage);
      //virtual __pointer(::user::menu) track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags,::message::message * pmessage);
      //virtual __pointer(::user::menu) track_popup_xml_menu_text(string strXml, i32 iFlags, ::message::message * pmessage);

      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags);
      //virtual __pointer(::user::menu) track_popup_xml_matter_menu(const char * pszMatter, i32 iFlags);
      //virtual __pointer(::user::menu) track_popup_xml_menu_text(string strXml,i32 iFlags);


      //virtual void exit_iconify();
      //virtual void exit_full_screen();


      //virtual void defer_exit_iconify();
      //virtual void defer_exit_full_screen();


      //virtual void window_enable_full_screen(bool bEnable = true);
      //virtual bool layout().is_full_screen();
      //virtual bool window_is_full_screen_enabled();
      //virtual bool onscreen_is_zoomed();
      //virtual bool onscreen_is_iconic();

      //virtual bool display(edisplay edisplay);

      //virtual edisplay get_display();
      //virtual edisplay get_previous_display();


      //virtual bool defer_set_appearance(edisplay edisplay);
      //virtual bool set_appearance(edisplay edisplay);
      //virtual bool set_previous_display(edisplay edisplay);


      virtual void show_keyboard(bool bShow = true);

      virtual void keep_alive(::object * pliveobject = nullptr);


      virtual ::graphics::graphics * get_window_graphics() override;


      virtual bool is_composite() override;


      //virtual void _user_message_handler(::message::message * pmessage);

      //virtual PFN_DISPATCH_MESSAGE_HANDLER _calc_user_message_handler();

      virtual bool has_pending_graphical_update();
      virtual void on_after_graphical_update();

      virtual void set_bitmap_source(string strBitmapSource);
      virtual void clear_bitmap_source();


      virtual bool WfiOnStartDock();
      virtual void WfiOnDock(edisplay edisplay);
      virtual void WfiOnRestore();
      virtual void WfiOnMinimize(bool bNoActivate);
      virtual void WfiOnMaximize();
      virtual void WfiOnFullScreen();
      virtual void WfiOnClose();
      virtual void WfiOnNotifyIcon();

      virtual void _001OnExitIconic();
      virtual void _001OnExitFullScreen();
      virtual void _001OnExitZoomed();

      //virtual LRESULT send_message(const ::id & id, WPARAM wparam = 0, lparam lparam = 0);
      //virtual bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0);
      //virtual void message_handler(::message::base * pbase);
      //virtual void pre_translate_message(::message::base * pbase);



      virtual void on_add_owned(::user::primitive * pprimitive);




//      primitive();
  //    virtual ~primitive();


      /*virtual void pre_translate_message(::message::message * pmessage);
*/



      virtual void set_need_redraw(bool bAscendants = true);
      virtual void set_need_load_form_data();
      virtual void set_need_save_form_data();
      virtual void post_redraw(bool bAscendants = true);
      virtual bool hide();

      // keyboard focus
      //virtual bool on_keyboard_focus(::user::primitive * pfocus);
      virtual void keyboard_focus_OnTimer(i32 iTimer);
      virtual void keyboard_focus_OnChar(::message::message * pmessage);
      virtual void keyboard_focus_OnSysChar(::message::message * pmessage);
      virtual void keyboard_focus_OnKeyDown(::message::message * pmessage);
      virtual void keyboard_focus_OnKeyUp(::message::message * pmessage);


      template < class T >
      __pointer(T) GetTypedParent() const;

      
      virtual ::user::interaction * get_parent_window() const;


      virtual ::user::interaction * get_first_child_window() const;


      virtual bool keyboard_focus_is_focusable() const;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew);
      virtual bool keyboard_focus_OnChildKillFocus();
      virtual primitive * keyboard_get_next_focusable(primitive * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false);
      virtual primitive * get_keyboard_focus() const;
      virtual ::e_status set_keyboard_focus();
      virtual ::e_status remove_keyboard_focus();
      virtual ::e_status clear_keyboard_focus();
      virtual primitive * keyboard_set_focus_next(bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false);
      //virtual bool has_focus();

      // mouse focus

      virtual void mouse_focus_OnLButtonUp(::message::message * pmessage);


      virtual bool _001CanEnterScreenSaver();


      //virtual void _001OnTimer(::timer * ptimer);

      virtual void on_reset_focus_start_tick();


      //virtual bool _is_window() const;



      interaction * m_puiThis;


      //primitive();
      //virtual ~primitive();

      //inline oswindow get_safe_handle() const;

#ifdef WINDOWS_DESKTOP

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT * pwndpl);


      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT * pwndpl);


#endif

      //virtual bool SetPlacement(const ::rect & rect, ::u32 nFlags = SWP_SHOWWINDOW);

      
      virtual i32 get_total_page_count(::promise::context * pcontext);


      virtual void edit_on_text(string str);
      virtual void edit_on_sel(strsize iBeg, strsize iEnd);
      virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context);


      virtual void on_text_composition(string str);
      virtual void on_text_commit(string str);
      virtual void on_text_composition_done();
      virtual bool is_text_composition_active();

      virtual void set_input_content_rect(const rect& rect);
      virtual void set_input_selection_rect(const rect& rect);

      virtual rect get_input_content_rect();
      virtual rect get_input_selection_rect();

      virtual void InputConnectionBeginBatchEdit();
      virtual void InputConnectionEndBatchEdit();
      virtual void InputConnectionCommitText(const string & str, strsize iNewCursorPosition);
      virtual void InputConnectionSetComposingText(const string & str, strsize iNewCursorPosition);
      virtual void InputConnectionSetComposingRegion(strsize iStart, strsize iEnd);
      virtual void InputConnectionSetSelection(strsize iStart, strsize iEnd);
      virtual void InputConnectionFinishComposingText();

      //virtual void _001OnTimer(::timer * ptimer);

      //virtual bool enable_window(bool bEnable );

      // Text Edit
      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const override;
      virtual index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel);
      virtual index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x);
      virtual index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel);
      virtual index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x);
      virtual strsize plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn);
      virtual strsize plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x);
      virtual index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel);


      //virtual void set_window_text(const char * pszString);

      //virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context);
      //virtual void _001SetText(const string & strText, const ::action_context & action_context);

      virtual ::user::primitive * first_child_user_primitive();
      virtual ::user::primitive * top_user_primitive();
      virtual ::user::primitive * under_user_primitive();
      virtual ::user::primitive * above_user_primitive();
      virtual ::user::primitive * next_user_primitive();
      virtual ::user::primitive * previous_user_primitive();

   };



   inline oswindow primitive::get_safe_handle() const
   {

      if (::is_null(this))
      {

         return nullptr;

      }

      return get_handle();

   }


} // namespace user


