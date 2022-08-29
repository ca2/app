// Injected/Split in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:46 BRT
#pragma once


#include "acme/user/user/check.h"
#include "acme/user/user/text.h"
#include "acme/user/user/element.h"


namespace user
{


   class CLASS_DECL_APEX primitive :
      virtual public ::user::element,
      virtual public ::channel,
      virtual public ::source,
      virtual public ::manager
   {
   public:


      duration    m_durationFocusStart;


      primitive();
      ~primitive() override;


      void _001OnTimer(::timer * ptimer) override;


      void create_message_queue(const ::string & lpszName) override;


      ::user::interaction * get_host_window() const;

      ::user::form * get_form() override;

      ::user::form * get_parent_form() override;

      void enable_window(bool bEnable = true) override;

      void PreSubClassWindow() override;


      virtual DECLARE_MESSAGE_HANDLER(_008GetWindowText);
      virtual DECLARE_MESSAGE_HANDLER(_008GetWindowTextLength);
#ifdef WINDOWS
      virtual strsize _009GetWindowText(wchar_t * pwsz, int n);
#else
      strsize _009GetWindowText(char * psz, int n) override;
#endif
      strsize _009GetWindowTextLength() override;

      bool GetFocusRect(RECTANGLE_I32 * prectangle) override;

      void defer_update_display() override;

      
      enum_control_type get_control_type() const override;


      void add_prodevian(::matter * pmatter) override;
      void erase_prodevian(::matter * pmatter) override;
      bool is_prodevian(const ::matter * pmatter) const override;

      void display(::e_display edisplay = e_display_default, ::e_activation eactivation = e_activation_default) override;


      string get_title() override;


      void install_message_routing(::channel * pchannel) override;


      void show_software_keyboard(::user::element* pelement) override;

      void hide_software_keyboard(::user::element* pelement) override;

      void UpdateWindow() override;
      
      void Invalidate(bool bErase = true) override;

      bool has_pending_redraw_flags() override;

      void default_message_handler(::message::message * pmessage) override;

      void message_handler(::message::message * pmessage) override;

      //virtual lresult message_handler(MESSAGE * pmessage);

      void on_select() override;

      bool is_place_holder() override;

      double _001GetTopLeftWeightedOccludedOpaqueRate() override;

      virtual ::windowing::cursor * get_mouse_cursor();

      //virtual void set_cursor(enum_cursor ecursor);

      virtual void set_mouse_cursor(::windowing::cursor * pcursor);

      //virtual ::point_i32 get_cursor_position() const;

      bool _is_window() const override;

      //virtual ::i32 get_window_long(i32 nIndex) const;
      //virtual ::i32 set_window_long(i32 nIndex,::i32 lValue);

      //virtual iptr get_window_long_ptr(i32 nIndex) const;
      //virtual void set_window_long_ptr(i32 nIndex, iptr lValue);

      ::user::interaction * first_child() override;
      ::user::interaction * last_child() override;
      ::user::interaction * last_sibling() override;
      ::user::interaction * next_sibling() override;
      ::user::interaction * previous_sibling() override;
      ::user::interaction * first_sibling() override;
      ::user::interaction * next_sibling(::user::interaction * pinteraction) override;
      ::user::interaction * previous_sibling(::user::interaction * pinteraction) override;

      ::user::interaction * bottom_child() override;
      ::user::interaction * top_child() override;
      ::user::interaction * bottom_sibling() override;
      ::user::interaction * under_sibling() override;
      ::user::interaction * above_sibling() override;
      ::user::interaction * top_sibling() override;
      ::user::interaction * above_sibling(::user::interaction * pinteraction) override;
      ::user::interaction * under_sibling(::user::interaction * pinteraction) override;


      //virtual void mouse_hover_add(::user::interaction * pinterface);
      //virtual bool mouse_hover_erase(::user::interaction * pinterface);

      //virtual void _task_transparent_mouse_event();

      //void CheckAutoCenter() override;

      void track_mouse_hover() override;
      void track_mouse_leave() override;

      void update_dialog_controls(channel * ptarget) override;
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr)  override;
      atom run_modal_loop(::user::interaction * pinteraction, u32 dwFlags = 0) override;
      atom RunModalLoop(u32 dwFlags = 0)  override;
      atom _001RunModalLoop(u32 dwFlags = 0)  override;
      bool ContinueModal()  override;
      void EndModalLoop(atom nResult)  override;



      // Dialog data support
      void update_data(bool bSaveAndValidate = true) override;


      //virtual ::user::primitive * get_keyboard_focus();


      void on_set_keyboard_focus() override;
      void on_kill_keyboard_focus() override;



      void _001UpdateWindow()override;

      //virtual void window_apply_visual(const window_state & windowstate);


      void sketch_to_design(bool & bUpdateBuffer, bool & bUpdateWindow)override;

      void design_down() override;
      void design_up() override;

      void prodevian_stop() override;

      virtual void design_window_minimize(::e_activation eactivation);
      virtual void design_window_maximize();
      virtual void design_window_full_screen(const ::rectangle_i32 & rectangleHint = nullptr);
      virtual void design_window_restore(edisplay edisplay);
      virtual void design_window_dock(edisplay edisplayDock);


      void prodevian_redraw(bool bUpdateBuffer) override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience);


      virtual void on_configuration_change(::user::primitive * pprimitiveSource);


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_reposition() override;
      void on_show_window() override;

      //virtual void BringToTop(edisplay edisplay);
      //virtual bool BringWindowToTop();
//
//#ifdef WINDOWS_DESKTOP
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);
//
//#endif

      //virtual bool SendChildNotifyLastMsg(lresult* pResult = nullptr);




      void subclass_window(oswindow posdata) override;
      oswindow unsubclass_window() override;

      string get_class_name() override;

      
      void create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom = nullptr) override;


      void create_host() override;
      void create_child(::user::interaction * puserinteractionParent) override;
      void create_control(::user::interaction * puserinteractionParent, const ::atom & atom) override;

      //virtual bool create_window_ex(__pointer(::user::system) pcs, ::user::interaction * puiParent, const ::atom & atom);
      //virtual void CalcWindowRect(RECTANGLE_I32 * pClientRect,::u32 nAdjustType = adjustBorder);


      //virtual bool IsTopParentActive();
      void ActivateTopParent() override;

      void start_destroying_window() override;

      void destroy_window() override;


//#ifdef WINDOWS

  //    virtual bool RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = RDW_INVALIDATE | RDW_ERASE);

//#else


//#endif


//      virtual void UpdateWindow();
      void SetRedraw(bool bRedraw = true) override;
      bool GetUpdateRect(RECTANGLE_I32 * prectangle,bool bErase = false) override;


      void interaction_post(const ::procedure & procedure) override;


      virtual lresult send(::message::message * pmessage);
      virtual void post(::message::message * pmessage);

      lresult send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32& point = nullptr) override;

      lresult message_call(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32& point = nullptr) override;
      lresult message_call(::message::message * pmessage) override;


#ifdef LINUX

      virtual lresult send_x11_event(void * pevent); // pevent <= XEvent *

#endif

      void post_message(const ::atom & atom, wparam wparam = 0,lparam lparam = 0)override;

      void post_simple_command(const enum_simple_command & ecommand,lparam lParam = 0) override;

      //virtual bool user_post(const ::atom& atom, wparam wparam = 0, lparam lparam = 0);

      //virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool _display(edisplay edisplay);

      //virtual void SetWindowDisplayChanged();

      // timer Functions
      void SetTimer(uptr uEvent, const ::duration & durationElapse, PFN_TIMER pfnTimer, bool bPeriodic = true, void* pdata = nullptr) override;
      void KillTimer(uptr uEvent)override;



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

      atom GetDlgCtrlId() const override;
      atom SetDlgCtrlId(::atom atom) override;

//
//#ifdef WINDOWS_DESKTOP
//
//      virtual bool open_clipboard();
//      virtual bool close_clipboard();
//
//#endif



      //virtual void set_foreground_window();

      

      void edit_on_set_focus(::user::interaction* pinteraction) override;
      void edit_on_kill_focus(::user::interaction* pinteraction) override;

      void set_window_text(const ::string & pszString) override;

      strsize get_window_text(char * pszStringBuf,strsize nMaxCount) override;

      string get_window_text() override;
      void get_window_text(string & rString) override;
      strsize get_window_text_length() override;


      //virtual bool _is_window_visible();
      bool is_this_visible(enum_layout elayout) override;
      //virtual bool is_window_enabled() const;




      bool _001IsPointInside(const ::point_i32 & point) override;
      ::user::interaction * _001FromPoint(::point_i32 point,bool bTestedIfParentVisible = false) override;

      void OnLinkClick(const ::string & psz,const ::string & pszTarget = nullptr) override;

      ::user::interaction * get_child_by_name(const ::string & strName, ::index iItem = -1, i32 iLevel = -1) override;
      ::user::interaction * get_child_by_id(const ::atom & atom, ::index iItem = -1, i32 iLevel = -1) override;
      ::user::element * get_primitive_by_id(const ::atom & atom, ::index iItem = -1, i32 iLevel = -1) override;


      ::user::interaction * get_wnd() const override;
      ::user::interaction * get_wnd(::u32 nCmd) const override;
      //virtual ::user::interaction_impl * get_impl() const;
      ::thread * get_task() const override;

      virtual ::user::primitive * set_parent(::user::primitive * pinteraction);
      virtual ::user::primitive * set_owner(::user::primitive * pinteraction);




      ::user::interaction * get_parent() const override;
      ::user::interaction * get_owner() const override;
      ::user::interaction * get_parent_owner() const override;
      ::user::interaction * get_parent_or_owner() const override;
      ::user::interaction * get_top_level_owner() const override;

      ::user::interaction * _top_level() const override;

      bool is_top_level_window() const override;

      void send_message_to_descendants(const ::atom & atom, wparam wParam = 0, lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = false) override;

      void route_message_to_descendants(::message::message * pmessage) override;
      void pre_translate_message(::message::message * pmessage) override;


      virtual i32 get_descendant_level(const ::user::primitive * pinteraction) const;
      //virtual bool is_descendant(const ::user::primitive * pinteraction,bool bIncludeSelf = false) const;
       ::user::interaction * get_focusable_descendant() const override;

      void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeftOver, ::u32 nFlag = reposDefault, RECTANGLE_I32 * prectParam = nullptr, const ::rectangle_i32 & rectangleClient = nullptr, bool bStretch = true) override;

      ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags) override;


//#ifdef WINDOWS_DESKTOP
  //    virtual ::user::interaction * get_next_window(::u32 nFlag = GW_HWNDNEXT);
//#else
      //virtual ::user::interaction * get_next_window(::u32 nFlag = 0);

      ::user::interaction * get_next_sibling_window() override;

//#endif

      void set_tool_window(bool bSet = true) override;

      
      ::user::interaction * get_next_window(bool bIgnoreChildren = false, const ::user::interaction * puiInteractionStop = nullptr) const override;
      ::user::interaction * get_window(enum_next enext) const override;


      ::user::interaction * GetLastActivePopup() override;


      bool is_message_only_window() const override;

      void pre_subclass_window() override;

      void post_non_client_destroy() override;


      //virtual lresult default_window_procedure();
      //virtual void default_window_procedure(::message::message * pmessage);


      bool call_message_handler(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32 & point = nullptr,lresult * presult = nullptr) override;


      //virtual void GuieProc(::message::message * pmessage);



      //virtual bool attach(::windowing::window * pwindow_New);
      oswindow detach_window() override;


      ::windowing::window * _window() const override;
      
      //virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics);
      //virtual ::size_f64 _001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics);


      //virtual bool can_merge(::user::interaction * pinteraction);
      //virtual bool merge(::user::interaction * pinteraction);


      void _001OnTriggerMouseInside() override;

      void _000OnMouseLeave(::message::message* pmessage) override;

      //#ifdef _UWP
      //      Agile<::winrt::Windows::UI::Core::CoreWindow> get_os_window();
      //#endif


      void set_context_org(::draw2d::graphics_pointer & pgraphics) override;

      void viewport_screen_to_client(POINT_I32 * ppt) override;
      void viewport_client_to_screen(POINT_I32 * ppt) override;
      void viewport_client_to_screen(RECTANGLE_I32 * ppt) override;
      void viewport_screen_to_client(RECTANGLE_I32 * ppt) override;


      string get_window_default_matter() override;
      string get_window_icon_matter() override;
      u32 get_window_default_style() override;
      virtual enum_type get_window_type() override;


      virtual void add_child_handler(::matter * pmatter, const ::atom & idChild, bool bPriority = false) override;


      virtual void on_simple_command(::message::simple_command * psimplecommand);
      virtual void on_command(::message::command * pcommand) override;


      // Window-Management message handler member functions
      virtual bool OnCommand(::message::message * pmessage);
      virtual bool OnNotify(::message::message * pmessage);
      virtual bool OnChildNotify(::message::message * pmessage);




      bool is_selected(::data::item * pitem) override;

      //virtual __pointer(place_holder) place_hold(::user::interaction * pinteraction);

      bool has_command_handler(::message::command * pcommand) override;

      //virtual void route(::topic * ptopic, ::context * pcontext);

      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void on_notify_control_event(control_event* pevent);



      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point_i32 & point = nullptr);
      //virtual __pointer(::user::menu) track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags, const ::point_i32 & point);
      //virtual __pointer(::user::menu) track_popup_xml_menu(const ::payload & varXml, i32 iFlags, const ::point_i32 & pointScreen = nullptr, const ::size_i32& sizeMinimum = size_i32(0, 0));
      //virtual __pointer(::user::menu) track_popup_xml_menu_file(::payload payloadFile, i32 iFlags, const ::point_i32 & point = nullptr, const ::size_i32 & sizeMinimum = size_i32(0, 0));

      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage);
      //virtual __pointer(::user::menu) track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags,::message::message * pmessage);
      //virtual __pointer(::user::menu) track_popup_xml_menu_text(string strXml, i32 iFlags, ::message::message * pmessage);

      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags);
      //virtual __pointer(::user::menu) track_popup_xml_matter_menu(const ::string & pszMatter, i32 iFlags);
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


      //void show_keyboard(bool bShow = true) override;

      void keep_alive(::object * pliveobject = nullptr) override;


      bool has_pending_graphical_update() override;
      void on_after_graphical_update() override;

      void set_bitmap_source(const string & strBitmapSource) override;
      void clear_bitmap_source() override;


      virtual bool WfiOnStartDock();
      virtual void WfiOnDock(edisplay edisplay);
      virtual void WfiOnRestore();
      virtual void WfiOnMinimize(bool bNoActivate);
      virtual void WfiOnMaximize();
      virtual void WfiOnFullScreen();
      virtual void WfiOnClose();
      virtual void WfiOnNotifyIcon();

      void _001OnExitIconic() override;
      void _001OnExitFullScreen() override;
      void _001OnExitZoomed() override;

      //virtual lresult send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0);
      //virtual bool post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = 0);
      //virtual void message_handler(::message::message * pmessage);
      //virtual void pre_translate_message(::message::message * pmessage);



      virtual void on_add_owned(::user::primitive * pprimitive);




//      primitive();
  //    virtual ~primitive();


      /*virtual void pre_translate_message(::message::message * pmessage);
*/






      void set_need_redraw(bool bAscendants = true) override;
      void set_need_load_form_data() override;
      void set_need_save_form_data() override;
      void post_redraw(bool bAscendants = true) override;
      void hide() override;

      // keyboard focus
      //virtual bool on_keyboard_focus(::user::primitive * pfocus);
      void keyboard_focus_OnTimer(i32 iTimer) override;
      void keyboard_focus_OnChar(::message::message * pmessage) override;
      void keyboard_focus_OnSysChar(::message::message * pmessage) override;
      void keyboard_focus_OnKeyDown(::message::message * pmessage) override;
      void keyboard_focus_OnKeyUp(::message::message * pmessage) override;


      //template < class T >
      //__pointer(T) GetTypedParent() const;

      
      ::user::interaction * get_parent_window() const override;

      ::user::element * get_parent_primitive() const override;


      ::user::interaction * get_first_child_window() const override;


      bool keyboard_focus_is_focusable() const override;
      bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      bool keyboard_focus_OnChildKillFocus() override;
      ::user::element * keyboard_get_next_focusable(::user::element * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      //virtual primitive * get_keyboard_focus() const;
      void set_keyboard_focus() override;
      void erase_keyboard_focus() override;
      void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr) override;
      ::user::element * get_keyboard_focus() override;
      ::user::element * keyboard_set_focus_next(bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      //virtual bool has_keyboard_focus();

      // mouse focus

      void mouse_focus_OnLButtonUp(::message::message * pmessage) override;


      bool _001CanEnterScreenSaver() override;


      //virtual void _001OnTimer(::timer * ptimer);

      void on_reset_focus_start_tick() override;


      //virtual bool _is_window() const;



      //primitive();
      //virtual ~primitive();

      //inline oswindow get_safe_handle() const;

#ifdef WINDOWS_DESKTOP

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl);


      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT * puserinteractionpl);


#endif

      //virtual bool SetPlacement(const ::rectangle_i32 & rectangle, ::u32 nFlags = SWP_SHOWWINDOW);

      
      i32 get_total_page_count(::context * pcontext) override;


      void edit_on_text(string str) override;
      void edit_on_sel(strsize iBeg, strsize iEnd) override;
      void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;


      void on_text_composition(string str) override;
      void on_text_commit(string str) override;
      void on_text_composition_done() override;
      //virtual bool is_text_composition_active();

      void set_input_content_rect(const rectangle_i32& rectangle) override;
      void set_input_selection_rect(const rectangle_i32& rectangle) override;

      rectangle_i32 get_input_content_rect() override;
      rectangle_i32 get_input_selection_rect() override;

      //void InputConnectionBeginBatchEdit() override;
      //void InputConnectionEndBatchEdit() override;
      //void InputConnectionCommitText(const ::string & str, strsize iNewCursorPosition) override;
      //void InputConnectionSetComposingText(const ::string & str, strsize iNewCursorPosition) override;
      //void InputConnectionSetComposingRegion(strsize iStart, strsize iEnd) override;
      //void InputConnectionSetSelection(strsize iStart, strsize iEnd) override;
      //void InputConnectionFinishComposingText() override;

      //virtual void _001OnTimer(::timer * ptimer);

      //virtual bool enable_window(bool bEnable );

      // Text Edit
      void _001GetSel(strsize & iBeg, strsize & iEnd) const override;
      index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x) override;
      index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x) override;
      strsize plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn) override;
      strsize plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x) override;
      index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;


      void on_check_change() override;

      //virtual void set_window_text(const ::string & pszString);

      //virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context);
      //virtual void _001SetText(const ::string & strText, const ::action_context & action_context);


      ::user::element * first_child_user_primitive() override;
      ::user::element * top_user_primitive() override;
      ::user::element * under_user_primitive() override;
      ::user::element * above_user_primitive() override;
      ::user::element * next_user_primitive() override;
      ::user::element * previous_user_primitive() override;

   };



} // namespace user


