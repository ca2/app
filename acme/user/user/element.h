// Injected/Split in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:46 BRT
#pragma once


#include "command_update_target.h"
#include "conversation.h"
#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/primitive/geometry2d/rectangle_array.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "item.h"


namespace user
{


   enum enum_window_type
   {

      e_window_type_window,
      e_window_type_frame,
      e_window_type_impact

   };



   enum enum_next
   {

      e_next_sibling,
      e_next_proper,

   };


   class CLASS_DECL_ACME element :
      virtual public ::user::command_update_target,
      virtual public ::conversation
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


      //class ::time                           m_timeFocusStart;
      bool                                         m_bUserElementOk;
      ::user::primitive *                          m_puserprimitive;
      ::user::interaction *                        m_puserinteraction;
      //pointer< pointer_array < ::user::item > >    m_puseritema;

      
      ::item_pointer                               m_pitemCurrent;
      ::item_pointer                               m_pitemHover;
      //::user<::item_pointer>                     m_puseritemHoverMouse;
      ::item_pointer                               m_pitemPressed;
      ::item_array                                 m_itema;
      //map < ITEM, ::index >                        m_itemmap;
      ::user::item_map                             m_useritemmap;


      element();
      ~element() override;


      virtual void _001OnTimer(::timer * ptimer);


      virtual void create_message_queue(const ::string & lpszName);


      //virtual void set_config_per_second(::frequency dConfigFps);
      //virtual ::frequency get_config_per_second();
      //virtual ::frequency get_output_per_second();


      //::pointer<::message::message>get_message(const ::atom & atom, wparam wparam, lparam lparam) override;


      ::user::interaction * get_host_window();

      virtual ::user::form * get_form();

      virtual ::user::form * get_parent_form();

      virtual ::user::element * get_form_user_element();

      virtual ::user::element * get_parent_form_user_element();

      void enable_window(bool bEnable = true) override;

      virtual void PreSubClassWindow();


//#ifdef WINDOWS
//      virtual strsize _009GetWindowText(wchar_t * pwsz, int n);
//#else
//      virtual strsize _009GetWindowText(char * psz, int n);
//#endif
//      virtual strsize _009GetWindowTextLength();

      virtual bool GetFocusRect(::rectangle_i32 & rectangle);


      virtual void defer_update_display();

      virtual ::count item_count() const;
      
      virtual ::item * item_at(::index iIndex);

      virtual void default_set_item_at(::index iIndex, ::item * pitem);

      virtual ::item_pointer default_add_item(::item * pitem);

      virtual ::user::item * user_item_at(::index iIndex);

      virtual ::index item_index(const ::item * pitem);

      virtual ::user::item * user_item(const ::item * pitem);
      
      virtual ::index item_index_by_atom(const ::atom & atom) const;

      virtual bool is_item_pressed_by_atom(const ::atom & atom) const;

      virtual bool is_item_hover_by_atom(const ::atom & atom) const;
      
      virtual bool is_item_pressed_by_index(::index iIndex) const;
      
      virtual bool is_item_hover_by_index(::index iIndex) const;
      
      virtual enum_control_type get_control_type() const;


      virtual void add_prodevian(::matter * pmatter);
      virtual void erase_prodevian(::matter * pmatter);
      virtual bool is_prodevian(const ::matter * pmatter) const;

      virtual void display(::e_display edisplay = e_display_default, ::e_activation eactivation = e_activation_default);


      virtual string get_title();


      virtual void show_software_keyboard(::user::element * pelement);

      virtual void hide_software_keyboard(::user::element * pelement);

      //virtual void UpdateWindow();
      
      //svirtual void Invalidate(bool bErase = true);

      virtual bool has_pending_redraw_flags();

      virtual void default_message_handler(::message::message * pmessage);

      virtual void message_handler(::message::message * pmessage);

      //virtual lresult message_handler(MESSAGE * pmessage);

      virtual void on_select();

      virtual bool is_place_holder();

      virtual double _001GetTopLeftWeightedOccludedOpaqueRate();


      virtual bool _is_window() const;

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


      //virtual void mouse_hover_add(::user::interaction * pinterface);
      //virtual bool mouse_hover_erase(::user::interaction * pinterface);

      //virtual void _task_transparent_mouse_event();

      virtual void CheckAutoCenter();

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();

      virtual void update_dialog_controls(channel * ptarget);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr);
      virtual atom run_modal_loop(::user::interaction * pinteraction, u32 dwFlags = 0);
      virtual atom RunModalLoop(u32 dwFlags = 0);
      virtual atom _001RunModalLoop(u32 dwFlags = 0);
      virtual bool ContinueModal();
      virtual void EndModalLoop(atom nResult);



      // Dialog data support
      virtual void update_data(bool bSaveAndValidate = true);


      //virtual ::user::element * get_keyboard_focus();


      virtual void on_set_keyboard_focus();
      virtual void on_kill_keyboard_focus();



      virtual void _001UpdateWindow();

      virtual void queue_selection_synchronization();

      //virtual void window_apply_visual(const window_state & windowstate);

      //virtual void sketch_to_layout();
      //virtual void layout_to_design(bool & bUpdateBuffer, bool & bUpdateWindow);

      virtual void design_down();
      virtual void design_up();

      virtual void prodevian_stop();



      virtual void prodevian_redraw(bool bUpdateBuffer);

      virtual void on_configuration_change(::user::element * pprimitiveSource);


      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition();
      virtual void on_show_window();

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




      virtual void subclass_window(oswindow posdata);
      virtual oswindow unsubclass_window();

      virtual string get_class_name();

      
      virtual void create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom = nullptr);


      virtual void create_host();
      virtual void create_child(::user::interaction * puserinteractionParent);
      virtual void create_control(::user::interaction * puserinteractionParent, const ::atom & atom);

      //virtual void create_window_ex(::pointer<::user::system>pcs, ::user::interaction * puiParent, const ::atom & atom);
      //virtual void CalcWindowRect(::rectangle_i32 * pClientRect,::u32 nAdjustType = adjustBorder);


      //virtual bool IsTopParentActive();
      virtual void ActivateTopParent();

      virtual void start_destroying_window();

      virtual void destroy_window();


//#ifdef WINDOWS

  //    virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = RDW_INVALIDATE | RDW_ERASE);

//#else


//#endif


//      virtual void UpdateWindow();
      //virtual void SetRedraw(bool bRedraw = true);
      //virtual bool GetUpdateRect(::rectangle_i32 * prectangle,bool bErase = false);


      virtual void interaction_post(const ::procedure & procedure);


      //virtual lresult send(::message::message * pmessage);
      //virtual bool post(::message::message * pmessage);

      virtual lresult send_message(const ::atom & atom, wparam wparam = {}, lparam lparam = 0, const ::point_i32 & point = {});

      virtual lresult message_call(const ::atom & atom, wparam wparam = {}, lparam lparam = 0, const ::point_i32 & point = {});
      virtual lresult message_call(::message::message * pmessage);


#ifdef LINUX

      virtual lresult send_x11_event(void * pevent); // pevent <= XEvent *

#endif

      virtual void post_message(const ::atom & atom, wparam wparam = {}, lparam lparam = 0);

      virtual void post_simple_command(const enum_simple_command & ecommand,lparam lParam = 0);

      //virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags = 0);
      //virtual bool _display(::e_display edisplay);

      //virtual void SetWindowDisplayChanged();

      // timer Functions
      virtual void SetTimer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer, bool bPeriodic = true, void* pdata = nullptr);
      virtual void KillTimer(uptr uEvent);


      virtual bool is_host_top_level();


      virtual bool is_ascendant(element * puiIsAscendant, bool bIncludeSelf);
      virtual bool is_parent(element * puiIsParent);
      virtual bool is_child(element * puiIsChild);
      virtual bool is_descendant(element * puiIsDescendant, bool bIncludeSelf);

      virtual bool is_descendant_of_or_owned_by(::user::element * puiAscendantCandidate, bool bIncludeSelf);
      virtual bool is_ascendant_or_owner_of(::user::element * puiDescendantCandidate, bool bIncludeSelf);

      virtual bool is_ascendant_of(element * puiIsDescendant, bool bIncludeSelf);
      virtual bool is_parent_of(element * puiIsChild);
      virtual bool is_child_of(element * puiIsParent);
      virtual bool is_descendant_of(element * puiIsAscendant, bool bIncludeSelf);

      virtual atom GetDlgCtrlId() const;
      virtual atom SetDlgCtrlId(const ::atom & atom);

//
//#ifdef WINDOWS_DESKTOP
//
//      virtual bool open_clipboard();
//      virtual bool close_clipboard();
//
//#endif



      //virtual void set_foreground_window();

      

      virtual void edit_on_set_focus(::user::interaction* pinteraction);
      virtual void edit_on_kill_focus(::user::interaction* pinteraction);

      virtual void set_window_text(const ::string & psz);
      virtual void set_window_text_source(const ::a_string_function & astringfunction);

      virtual strsize get_window_text(char * pszStringBuf,strsize nMaxCount);

      virtual string get_window_text();
      virtual void get_window_text(string & rString);
      virtual strsize get_window_text_length();


      //virtual bool _is_window_visible();
      virtual bool is_this_visible(enum_layout elayout);
      //virtual bool is_window_enabled() const;




      virtual bool _001IsPointInside(const ::point_i32 & point);
      virtual ::user::interaction * _001FromPoint(::point_i32 point,bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const ::string & psz,const ::string & pszTarget = nullptr);

      virtual ::user::interaction * get_child_by_name(const ::string & strName, ::index iItem = -1, i32 iLevel = -1);
      virtual ::user::interaction * get_child_by_id(const ::atom & atom, ::index iItem = -1, i32 iLevel = -1);
      virtual ::user::element * get_primitive_by_id(const ::atom & atom, ::index iItem = -1, i32 iLevel = -1);


      virtual ::user::interaction * get_wnd();
      virtual ::user::interaction * get_wnd(::u32 nCmd);
      //virtual ::user::interaction_impl * get_impl() const;
      virtual ::task * get_task() override;

      virtual ::user::element * set_parent(::user::element * pinteraction);
      virtual ::user::element * set_owner(::user::element * pinteraction);




      virtual ::user::interaction * get_parent();
      virtual ::user::interaction * get_owner();
      virtual ::user::interaction * get_parent_owner();
      virtual ::user::interaction * get_parent_or_owner();
      virtual ::user::interaction * get_top_level_owner();


      virtual ::user::interaction * _top_level();


      virtual bool is_top_level_window();

      virtual void send_message_to_descendants(const ::atom & atom, wparam wParam = {}, lparam lParam = 0, bool bDeep = true, bool bOnlyPerm = false);

      virtual void route_message_to_descendants(::message::message * pmessage);
      virtual void pre_translate_message(::message::message * pmessage);


      virtual i32 get_descendant_level(::user::element * puserelement);
      //virtual bool is_descendant(const ::user::element * pinteraction,bool bIncludeSelf = false) const;
      virtual ::user::interaction * get_focusable_descendant();

      virtual void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeftOver, ::u32 nFlag = reposDefault, ::rectangle_i32 * prectParam = nullptr, const ::rectangle_i32 & rectangleClient = {}, bool bStretch = true);

      virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point);
      virtual ::user::interaction * ChildWindowFromPoint(const ::point_i32 & point,::u32 nFlags);


//#ifdef WINDOWS_DESKTOP
  //    virtual ::user::interaction * get_next_window(::u32 nFlag = GW_HWNDNEXT);
//#else
      //virtual ::user::interaction * get_next_window(::u32 nFlag = 0);

      virtual ::user::interaction * get_next_sibling_window();

//#endif

      virtual void set_tool_window(bool bSet = true);

      
      virtual ::user::interaction * get_next_window(bool bIgnoreChildren = false, ::user::interaction * puiInteractionStop = nullptr);
      virtual ::user::interaction * get_window(enum_next enext);


      virtual ::user::interaction * GetLastActivePopup();


      virtual bool is_message_only_window();

      virtual void pre_subclass_window();

      virtual void post_non_client_destroy();


      //virtual lresult default_window_procedure();
      //virtual void default_window_procedure(::message::message * pmessage);


      //virtual bool call_message_handler(const ::atom & atom, wparam wparam = {}, lparam lparam = 0, const ::point_i32 & point = {}, lresult * presult = nullptr);


      //virtual void GuieProc(::message::message * pmessage);



      //virtual bool attach(::windowing::window * pwindow_New);
      virtual oswindow detach_window();


      virtual ::windowing::window * window();
      
      //virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics);
      //virtual ::size_f64 _001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics);


      //virtual bool can_merge(::user::interaction * pinteraction);
      //virtual bool merge(::user::interaction * pinteraction);


      //virtual void _001OnTriggerMouseInside();

      virtual void _000OnMouseLeave(::message::message* pmessage);

      //#ifdef UNIVERSAL_WINDOWS
      //      Agile<::winrt::Windows::UI::Core::CoreWindow> get_os_window();
      //#endif


      virtual void set_context_org(::draw2d::graphics_pointer & pgraphics);

      virtual void viewport_screen_to_client(::point_i32 & point);
      virtual void viewport_client_to_screen(::point_i32 & point);
      virtual void viewport_client_to_screen(::rectangle_i32 & point);
      virtual void viewport_screen_to_client(::rectangle_i32 & point);


      virtual string get_window_default_matter();
      virtual string get_window_icon_matter();
      virtual u32 get_window_default_style();
      virtual enum_window_type get_window_type();


      virtual void add_child_handler(const ::signal_handler& signalhandler, const ::atom & idChild, bool bPriority = false);





      virtual bool is_selected(::data::item * pitem);

      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void on_notify_control_event(control_event* pevent);



      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point_i32 & point = {});
      //virtual ::pointer<::user::menu>track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags, const ::point_i32 & point);
      //virtual ::pointer<::user::menu>track_popup_xml_menu(const ::payload & varXml, i32 iFlags, const ::point_i32 & pointScreen = nullptr, const ::size_i32& sizeMinimum = size_i32(0, 0));
      //virtual ::pointer<::user::menu>track_popup_xml_menu_file(::payload payloadFile, i32 iFlags, const ::point_i32 & point = {}, const ::size_i32 & sizeMinimum = size_i32(0, 0));

      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage);
      //virtual ::pointer<::user::menu>track_popup_xml_matter_menu(const ::string & pszMatter,i32 iFlags,::message::message * pmessage);
      //virtual ::pointer<::user::menu>track_popup_xml_menu_text(string strXml, i32 iFlags, ::message::message * pmessage);

      //virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags);
      //virtual ::pointer<::user::menu>track_popup_xml_matter_menu(const ::string & pszMatter, i32 iFlags);
      //virtual ::pointer<::user::menu>track_popup_xml_menu_text(string strXml,i32 iFlags);


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


      //virtual void show_keyboard(bool bShow = true);

      virtual void keep_alive(::object * pliveobject = nullptr);


      virtual bool has_pending_graphical_update();
      virtual void on_after_graphical_update();


      virtual void set_bitmap_source(const string & strBitmapSource);
      virtual void clear_bitmap_source();


      virtual bool _001OnBeforeEnterIconic();
      virtual bool _001OnBeforeEnterNormal();
      virtual bool _001OnBeforeEnterZoomed();
      virtual bool _001OnBeforeEnterFullScreen();


      virtual bool _001OnBeforeEnterAppearance();


      virtual void _001OnAfterEnterIconic();
      virtual void _001OnAfterEnterNormal();
      virtual void _001OnAfterEnterZoomed();
      virtual void _001OnAfterEnterFullScreen();


      virtual void _001OnAfterEnterAppearance();


      virtual bool _001OnBeforeExitIconic();
      virtual bool _001OnBeforeExitNormal();
      virtual bool _001OnBeforeExitZoomed();
      virtual bool _001OnBeforeExitFullScreen();


      virtual bool _001OnBeforeExitAppearance();


      virtual void _001OnAfterExitIconic();
      virtual void _001OnAfterExitNormal();
      virtual void _001OnAfterExitZoomed();
      virtual void _001OnAfterExitFullScreen();


      virtual void _001OnAfterExitAppearance();


      //virtual lresult send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0);
      //virtual bool post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = 0);
      //virtual void message_handler(::message::message * pmessage);
      //virtual void pre_translate_message(::message::message * pmessage);



      virtual void on_add_owned(::user::element * pprimitive);




//      element();
  //    virtual ~element();


      /*virtual void pre_translate_message(::message::message * pmessage);
*/

      virtual float preferred_dpi_x();

      virtual float preferred_dpi_y();

      virtual float preferred_density();





      virtual void set_need_redraw(const ::rectangle_i32_array & rectangleaScreenNeedRedraw = {}, ::draw2d::graphics * pgraphics = nullptr, ::function < void() > function = nullptr, bool bAscendants = true);
      virtual void set_need_load_form_data();
      virtual void set_need_save_form_data();
      virtual void post_redraw(bool bAscendants = true);
      virtual void hide();

      // keyboard focus
      //virtual bool on_keyboard_focus(::user::element * pfocus);
      virtual void keyboard_focus_OnTimer(i32 iTimer);
      virtual void keyboard_focus_OnChar(::message::message * pmessage);
      virtual void keyboard_focus_OnSysChar(::message::message * pmessage);
      virtual void keyboard_focus_OnKeyDown(::message::message * pmessage);
      virtual void keyboard_focus_OnKeyUp(::message::message * pmessage);



      template < class T >
      pointer < T > get_typed_parent()
      {

         ASSERT_VALID(this);

         pointer < T > p;

         auto puiParent = get_parent_primitive();  // start with one parent up

         while (puiParent != nullptr)
         {

            p = puiParent;

            if (p.is_set())
            {

               return p;

            }

            puiParent = puiParent->get_parent_primitive();

         }

         return nullptr;

      }

      virtual ::user::interaction * get_parent_window();

      virtual ::user::element * get_parent_primitive();

      virtual ::user::primitive_impl* get_primitive_impl();

      virtual ::user::interaction * get_first_child_window();


      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew);
      virtual bool keyboard_focus_OnChildKillFocus();
      virtual element * keyboard_get_next_focusable(element * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false);
      //virtual element * get_keyboard_focus() const;
      virtual void set_keyboard_focus();
      virtual void erase_keyboard_focus();
      virtual void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr);
      virtual ::user::element * get_keyboard_focus();
      virtual element * keyboard_set_focus_next(bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false);
      //virtual bool has_keyboard_focus();

      // mouse focus

      virtual void mouse_focus_OnLButtonUp(::message::message * pmessage);


      virtual bool _001CanEnterScreenSaver();


      //virtual void _001OnTimer(::timer * ptimer);

      virtual void on_reset_focus_start_tick();


      //virtual bool _is_window() const;



      //element();
      //virtual ~element();

      //inline oswindow get_safe_handle() const;

#ifdef WINDOWS_DESKTOP

      //virtual bool GetWindowPlacement(WINDOWPLACEMENT * puserinteractionpl);


      //virtual bool SetWindowPlacement(const WINDOWPLACEMENT * puserinteractionpl);


#endif

      //virtual bool SetPlacement(const ::rectangle_i32 & rectangle, ::u32 nFlags = SWP_SHOWWINDOW);

      
      virtual i32 get_total_page_count(::context * pcontext);


      virtual void edit_on_text(string str);
      virtual void edit_on_sel(strsize iBeg, strsize iEnd);
      virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;


      virtual void on_text_composition(string str);
      virtual void on_text_commit(string str);
      virtual void on_text_composition_done();
      //virtual bool is_text_composition_active();

      virtual void set_input_content_rect(const rectangle_i32& rectangle);
      virtual void set_input_selection_rect(const rectangle_i32& rectangle);

      virtual rectangle_i32 get_input_content_rect();
      virtual rectangle_i32 get_input_selection_rect();

      virtual bool InputConnectionBeginBatchEdit(bool bSuper);
      virtual bool InputConnectionEndBatchEdit(bool bSuper);
      virtual bool InputConnectionCommitText(const ::string & str, strsize iNewCursorPosition, bool bSuper);
      virtual bool InputConnectionDeleteSurroundingText(strsize iBeforeLength, strsize iAfterLength, bool bSuper);
      virtual bool InputConnectionSetComposingText(const ::string & str, strsize iNewCursorPosition, bool bSuper);
      virtual bool InputConnectionSetComposingRegion(strsize iStart, strsize iEnd, bool bSuper);
      virtual bool InputConnectionSetSelection(strsize iStart, strsize iEnd, bool bSuper);
      virtual bool InputConnectionFinishComposingText(bool bSuper);

      //virtual void _001OnTimer(::timer * ptimer);

      //virtual bool enable_window(bool bEnable );

      // Text Edit
      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) override;
      virtual void _001GetSel(strsize& iBeg, strsize& iEnd, strsize & iComposingStart, strsize & iComposingEnd);
      virtual index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel);
      virtual index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x);
      virtual index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel);
      virtual index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x);
      virtual strsize plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn);
      virtual strsize plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x);
      virtual index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel);


      //virtual void set_window_text(const ::string & pszString);

      //virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context);
      //virtual void _001SetText(const ::string & strText, const ::action_context & action_context);

      virtual ::user::element * first_child_user_primitive();
      virtual ::user::element * top_user_primitive();
      virtual ::user::element * under_user_primitive();
      virtual ::user::element * above_user_primitive();
      virtual ::user::element * next_user_primitive();
      virtual ::user::element * previous_user_primitive();

   
      virtual void pick_single_file(
         const ::array < ::file::file_dialog_filter > & filedialogfiltera,
         const ::function < void(const ::file::path &) >& function,
         bool save);


      virtual void pick_multiple_file(
         const ::array < ::file::file_dialog_filter >& filedialogfiltera,
         const ::function < void(const ::file::path_array &) >& function);


      virtual void pick_single_folder(
         const ::function < void(const ::file::path &) >& function);

      virtual bool update_impact();
      virtual bool on_impact_update();
      virtual bool on_before_impact_update();
      virtual void on_after_impact_update();

   };



} // namespace user


