// Injected/Split in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:46 BRT
#pragma once


//#include "container.h"
//#include "acme/user/user/check.h"
//#include "acme/user/user/text.h"
#include "acme/user/user/interaction_base.h"
#include "apex/handler/manager.h"
#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_APEX prototype :
      virtual public ::user::interaction_base,
      virtual public ::channel,
      //virtual public ::source,
      virtual public ::manager
      //, virtual public ::user::container
   {
   public:


      class ::time            m_timeFocusStart;


      prototype();
      ~prototype() override;


      void destroy() override;


      void _001OnTimer(::timer * ptimer) override;


      void create_message_queue(const ::string & lpszName) override;


      ::user::interaction * get_host_user_interaction() override;

      ::user::form * get_form() override;

      ::user::form * get_parent_form() override;

      void enable_window(bool bEnable = true) override;

      void PreSubClassWindow() override;


      virtual DECLARE_MESSAGE_HANDLER(_008GetWindowText);
      virtual DECLARE_MESSAGE_HANDLER(_008GetWindowTextLength);
//#ifdef WINDOWS
//      virtual strsize _009GetWindowText(wchar_t * pwsz, int n);
//#else
//      strsize _009GetWindowText(char * psz, int n) override;
//#endif
//      strsize _009GetWindowTextLength() override;

      bool GetFocusRect(::rectangle_i32 & rectangle) override;

      void defer_update_display() override;

      
      enum_control_type get_control_type() const override;


      //void add_fps_interest(::particle * pparticle) override;
      //void erase_fps_interest(::particle * pparticle) override;
      //bool is_fps_interest(const ::particle * pparticle) const override;

      void display(::e_display edisplay = e_display_default, ::e_activation eactivation = e_activation_default) override;


      string get_title() override;


      void install_message_routing(::channel * pchannel) override;


      void show_software_keyboard(::user::element * pelement) override;

      void hide_software_keyboard(::user::element * pelement) override;

      //void UpdateWindow() override;
      
      //void Invalidate(bool bErase = true) override;

      bool has_pending_redraw_flags() override;

      void default_message_handler(::message::message * pmessage) override;

      void message_handler(::message::message * pmessage) override;

      //virtual lresult message_handler(MESSAGE * pmessage);

      void on_select() override;

      bool is_place_holder() override;

      double _001GetTopLeftWeightedOccludedOpaqueRate() override;

      virtual ::windowing::cursor * get_mouse_cursor();

      //virtual void set_cursor(enum_cursor ecursor);

      virtual void set_default_mouse_cursor(::windowing::cursor * pcursor);

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


      //virtual ::user::prototype * get_keyboard_focus();


      void on_set_keyboard_focus() override;
      void on_kill_keyboard_focus() override;



      void _001UpdateWindow()override;

      //virtual void window_apply_visual(const window_state & windowstate);

      //void sketch_to_layout()override;
      //void layout_to_design(bool & bUpdateBuffer, bool & bUpdateWindow)override;

      void design_down() override;
      void design_up() override;

      void fps_interest_stop() override;

      virtual void design_window_minimize(::e_activation eactivation);
      virtual void design_window_maximize();
      virtual void design_window_full_screen(const ::rectangle_i32 & rectangleHint = {});
      virtual void design_window_normal(e_display edisplay);
      virtual void design_window_dock(e_display edisplayDock);


      //void graphics_thread_post_redraw(bool bUpdateBuffer) override;

      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience);


      virtual void on_configuration_change(::user::prototype * pprimitiveSource);


      //void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_reposition() override;
      void on_show_window() override;

      //virtual void BringToTop(::e_display edisplay);
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


      //void create_host(enum_parallelization eparallelization) override;
      void create_host() override;
      void create_child(::user::interaction * puserinteractionParent) override;
      void create_control(::user::interaction * puserinteractionParent, const ::atom & atom) override;

      //virtual bool create_window_ex(::pointer<::user::system>pcs, ::user::interaction * puiParent, const ::atom & atom);
      //virtual void CalcWindowRect(::rectangle_i32 * pClientRect,::u32 nAdjustType = adjustBorder);


      //virtual bool IsTopParentActive();
      void ActivateTopParent() override;

      void start_destroying_window() override;

      void destroy_window() override;


//#ifdef WINDOWS

  //    virtual bool RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = RDW_INVALIDATE | RDW_ERASE);

//#else


//#endif


//      virtual void UpdateWindow();
      //void SetRedraw(bool bRedraw = true) override;
      //bool GetUpdateRect(::rectangle_i32 * prectangle,bool bErase = false) override;


      void host_post(const ::procedure & procedure) override;


//      virtual lresult send(::message::message * pmessage);
      virtual void post_message(::message::message * pmessage);

      lresult send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32 & point = {}) override;
      lresult send_message(::message::message * pmessage) override;

      lresult message_call(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32 & point = {}) override;
      lresult message_call(::message::message * pmessage) override;

      
      void on_message(::message::message * pmessage) override;
      

#ifdef LINUX

      virtual lresult send_x11_event(void * pevent); // pevent <= XEvent *

#endif

      void message_handler(const ::atom & atom, wparam wparam = 0, lparam lparam = 0)override;

      void post_message(const ::atom & atom, wparam wparam = 0,lparam lparam = 0)override;

      void post_simple_command(const enum_simple_command & ecommand,lparam lParam = 0) override;

      //virtual bool user_post(const ::atom& atom, wparam wparam = 0, lparam lparam = 0);

      //virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool _display(::e_display edisplay);

      //virtual void SetWindowDisplayChanged();

      // timer Functions
      void SetTimer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer, bool bPeriodic = true, void* pdata = nullptr) override;
      void KillTimer(uptr uEvent)override;



      virtual bool is_ascendant(const prototype * puiIsAscendant, bool bIncludeSelf) const;
      virtual bool is_parent(const prototype * puiIsParent) const;
      virtual bool is_child(const prototype * puiIsChild) const;
      virtual bool is_descendant(const prototype * puiIsDescendant, bool bIncludeSelf) const;

      virtual bool is_descendant_of_or_owned_by(const ::user::prototype * puiAscendantCandidate, bool bIncludeSelf) const;
      virtual bool is_ascendant_or_owner_of(const ::user::prototype * puiDescendantCandidate, bool bIncludeSelf) const;

      virtual bool is_ascendant_of(const prototype * puiIsDescendant, bool bIncludeSelf) const;
      virtual bool is_parent_of(const prototype * puiIsChild) const; 
      virtual bool is_child_of(const prototype * puiIsParent) const; 
      virtual bool is_descendant_of(const prototype * puiIsAscendant, bool bIncludeSelf) const; 

      atom GetDlgCtrlId() const override;
      atom SetDlgCtrlId(const ::atom & atom) override;

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
      void set_window_text_source(const ::a_string_function & function) override;

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

      ::user::interaction * get_child_by_name(const ::string & strName, ::collection::index iItem = -1, i32 iLevel = -1) override;
      ::user::interaction * get_child_by_id(const ::atom & atom, ::collection::index iItem = -1, i32 iLevel = -1) override;
      ::user::element * get_primitive_by_id(const ::atom & atom, ::collection::index iItem = -1, i32 iLevel = -1) override;


      ::user::interaction * get_wnd() override;
      ::user::interaction * get_wnd(::u32 nCmd) override;
      //virtual ::user::interaction_impl * get_impl() const;
      ::task * get_task() override;

      virtual ::user::prototype * set_parent(::user::prototype * pinteraction);
      virtual ::user::prototype * set_owner(::user::prototype * pinteraction);




      ::user::interaction * get_parent() override;
      ::user::interaction * get_owner() override;
      ::user::interaction * get_parent_owner() override;
      ::user::interaction * get_parent_or_owner() override;
      ::user::interaction * get_top_level_owner() override;

      ::user::interaction * _top_level() override;

      bool is_top_level_window() override;

      void send_message_to_descendants(const ::atom & atom, wparam wParam = 0, lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = false) override;

      void route_message_to_descendants(::message::message * pmessage) override;
      void pre_translate_message(::message::message * pmessage) override;


      i32 get_descendant_level(::user::element * puserelement) override;
      //virtual bool is_descendant(const ::user::prototype * pinteraction,bool bIncludeSelf = false) const;
       ::user::interaction * get_focusable_descendant() override;

      void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeftOver, ::u32 nFlag = reposDefault, ::rectangle_i32 * prectParam = nullptr, const ::rectangle_i32 & rectangleX = {
         }, bool bStretch = true) override;

      ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags) override;


//#ifdef WINDOWS_DESKTOP
  //    virtual ::user::interaction * get_next_window(::u32 nFlag = GW_HWNDNEXT);
//#else
      //virtual ::user::interaction * get_next_window(::u32 nFlag = 0);

      ::user::interaction * get_next_sibling_window() override;

//#endif

      void set_tool_window(bool bSet = true) override;

      
      ::user::interaction * get_next_window(bool bIgnoreChildren = false, ::user::interaction * puiInteractionStop = nullptr) override;
      ::user::interaction * get_window(enum_next enext) override;


      ::user::interaction * GetLastActivePopup() override;


      bool is_message_only_window() override;

      void pre_subclass_window() override;

      void post_non_client_destroy() override;


      //virtual lresult default_window_procedure();
      //virtual void default_window_procedure(::message::message * pmessage);


      //bool call_message_handler(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32 & point = {},lresult * presult = nullptr) override;


      //virtual void GuieProc(::message::message * pmessage);



      //virtual bool attach(::windowing::window * pwindow_New);
      oswindow detach_window() override;


      ::windowing::window * window() override;
      
      //virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics);
      //virtual ::size_f64 _001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics);


      //virtual bool can_merge(::user::interaction * pinteraction);
      //virtual bool merge(::user::interaction * pinteraction);


      //void _001OnTriggerMouseInside() override;

      void _000OnMouseLeave(::message::message* pmessage) override;

      //#ifdef UNIVERSAL_WINDOWS
      //      Agile<::winrt::Windows::UI::Core::CoreWindow> get_os_window();
      //#endif


      void set_context_org(::draw2d::graphics_pointer & pgraphics) override;

      void viewport_screen_to_client(::sequence2_i32 & sequence) override;
      void viewport_client_to_screen(::sequence2_i32 & sequence) override;
      void viewport_client_to_screen(::rectangle_i32 & rectangle) override;
      void viewport_screen_to_client(::rectangle_i32 & rectangle) override;


      string get_window_default_matter() override;
      string get_window_icon_matter() override;
      u32 get_window_default_style() override;
      //virtual enum_type get_window_type() override;


      virtual void add_child_handler(::particle * pparticle, const ::atom & atomChild, bool bPriority = false) override;


      virtual void on_simple_command(::message::simple_command * psimplecommand);
      virtual void on_command(::message::command * pcommand) override;


      // Window-Management message handler member functions
      virtual bool OnCommand(::message::message * pmessage);
      virtual bool OnNotify(::message::message * pmessage);
      virtual bool OnChildNotify(::message::message * pmessage);




      bool is_selected(::data::item * pitem) override;

      //virtual ::pointer<place_holder>place_hold(::user::interaction * pinteraction);

      bool has_command_handler(::message::command * pcommand) override;

      //virtual void route(::topic * ptopic, ::context * pcontext);

      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void on_notify_control_event(control_event* pevent);



      //virtual void exit_iconify();
      //virtual void exit_full_screen();


      //virtual void defer_exit_iconify();
      //virtual void defer_exit_full_screen();


      //virtual void window_enable_full_screen(bool bEnable = true);
      //virtual bool layout().is_full_screen();
      //virtual bool window_is_full_screen_enabled();
      //virtual bool onscreen_is_zoomed();
      //virtual bool onscreen_is_iconic();

      //virtual bool display(::e_display edisplay);

      //virtual edisplay get_display();
      //virtual edisplay get_previous_display();


      //virtual bool defer_set_appearance(::e_display edisplay);
      //virtual bool set_appearance(::e_display edisplay);
      //virtual bool set_previous_display(::e_display edisplay);


      //void show_keyboard(bool bShow = true) override;

      void keep_alive(::object * pliveobject = nullptr) override;


      //bool has_pending_graphical_update() override;
      void on_after_graphical_update() override;

      void set_bitmap_source(const string & strBitmapSource) override;
      void clear_bitmap_source() override;


      virtual bool WfiOnStartDock();
      virtual void WfiOnDock(e_display edisplay);
      virtual void WfiOnRestore();
      virtual void WfiOnMinimize(bool bNoActivate);
      virtual void WfiOnMaximize();
      virtual void WfiOnFullScreen();
      virtual void WfiOnClose();
      virtual void WfiOnNotifyIcon();

      //bool _001OnBeforeExitIconic() override;
      //bool _001OnBeforeExitFullScreen() override;
      //bool _001OnBeforeExitZoomed() override;

      //virtual lresult send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0);
      //virtual bool post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = 0);
      //virtual void message_handler(::message::message * pmessage);
      //virtual void pre_translate_message(::message::message * pmessage);



      virtual void on_add_owned(::user::prototype * pprimitive);




//      prototype();
  //    virtual ~prototype();


      /*virtual void pre_translate_message(::message::message * pmessage);
*/






      //void set_need_redraw(bool bAscendants = true) override;
      void set_need_load_form_data() override;
      void set_need_save_form_data() override;
      void post_redraw(bool bAscendants = true) override;
      void hide() override;

      // keyboard focus
      //virtual bool on_keyboard_focus(::user::prototype * pfocus);
      void keyboard_focus_OnTimer(i32 iTimer) override;
      void keyboard_focus_OnChar(::message::message * pmessage) override;
      void keyboard_focus_OnSysChar(::message::message * pmessage) override;
      void keyboard_focus_OnKeyDown(::message::message * pmessage) override;
      void keyboard_focus_OnKeyUp(::message::message * pmessage) override;


      //template < class T >
      //pointer < T > get_typed_parent() const;

      
      ::user::interaction * get_parent_window() override;

      ::user::element * get_parent_primitive() override;


      ::user::interaction * get_first_child_window() override;


      bool keyboard_focus_is_focusable() override;
      bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      bool keyboard_focus_OnChildKillFocus() override;
      ::user::element * keyboard_get_next_focusable(::user::element * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      //virtual prototype * get_keyboard_focus() const;
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



      //prototype();
      //virtual ~prototype();

      //inline oswindow get_safe_handle() const;

#ifdef WINDOWS_DESKTOP

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl);


      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT * puserinteractionpl);


#endif

      //virtual bool SetPlacement(const ::rectangle_i32 & rectangle, ::u32 nFlags = SWP_SHOWWINDOW);

      
      i32 get_total_page_count(::context * pcontext) override;


      void edit_on_text(string str) override;
      void edit_on_sel(strsize iBeg, strsize iEnd) override;
      void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) override;


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
      //void get_text_selection(strsize & iBeg, strsize & iEnd) const override;
      ::collection::index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      ::collection::index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x) override;
      ::collection::index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      ::collection::index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x) override;
      strsize plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn) override;
      strsize plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, i32 x) override;
      ::collection::index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;


      //void on_check_changed() override;

      //virtual void set_window_text(const ::string & pszString);

      //virtual void set_check(enum_check echeck, const ::action_context & action_context);
      //virtual void set_text(const ::string & strText, const ::action_context & action_context);


      ::user::element * first_child_user_primitive() override;
      ::user::element * top_user_primitive() override;
      ::user::element * under_user_primitive() override;
      ::user::element * above_user_primitive() override;
      ::user::element * next_user_primitive() override;
      ::user::element * previous_user_primitive() override;

   };



} // namespace user


