#pragma once


namespace user
{


   class CLASS_DECL_AURA item
   {
   public:


      e_element         m_eelement;
      ::index           m_iItem;
      ::index           m_iSubItem;
      ::index           m_iListItem;

      
      item(e_element eelement = ::user::element_none, ::index iItem = -1, ::index iSubItem = -1, ::index iListItem = -1)
      {
         
         m_eelement = ::user::element_none;

         m_iItem = iItem >= 0 ? iItem : m_eelement != ::user::element_none ? 0 : iItem;

         m_iSubItem = iSubItem;

         m_iSubItem = iListItem;

      }

      operator bool() const { return m_eelement != ::user::element_none; }

      operator e_element() const { return m_eelement; }

   };


   enum e_interaction
   {

      interaction_wfi_up_down_loading = 1 << 0,
      interaction_wfi_up_tool_window = 1 << 1,

   };


   class CLASS_DECL_AURA interaction:
      virtual public layout,
      virtual public primitive,
      virtual public ::timer_callback
   {
   public:


      enum e_non_client
      {

         non_client_background = 1,
         non_client_focus_rect = 2,

      };

      enum e_updown
      {
         updown_normal_frame,
         updown_none,
         updown_up,
         updown_down,
      };


      class draw_select
      {
      public:

         interaction *           m_puserinteraction;
         ::draw2d::graphics *    m_pgraphics;

         draw_select(interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics) :
            m_puserinteraction(pinteraction),
            m_pgraphics(pgraphics)
         {

            // m_puserinteraction->select_user_schema();

            m_puserinteraction->select(pgraphics);

            pgraphics->m_puserinteraction = pinteraction;

         }

         ~draw_select()
         {
            m_puserinteraction->select(nullptr);
         }

      };

      ::user::e_element                   m_eelementHover;

      ::size                              m_sizeRestoreBroad;

      ::size                              m_sizeRestoreCompact;

      e_control_type                      m_econtroltype;

      flags < e_non_client >              m_flagNonClient;

      bool                                m_bMouseHover;

      int                                 m_iMouseMoveSkipCount;
      int                                 m_iMouseMoveSkipSquareDistance;
      ::tick                              m_tickMouseMoveSkip;
      ::point                             m_pointMouseMoveSkip;
      ::tick                              m_tickMouseMovePeriod;
      bool                                m_bMouseMovePending;
      ::point                             m_pointMouseMove;
      bool                                m_bRedraw;
      tick                                m_tickLastRedraw;
      ::id                                m_idView;

      ::user::form *                      m_pform;
      ::user::form *                      m_pformParent;
      ::user::layout *                    m_playout;
      //point                               m_pointCursor;
      e_color                             m_ecolorBackground;
      bool                                m_bWorkspaceFullScreen;
      point                               m_pointScroll;
      bool                                m_bHideOnTransparentFrame;
      bool                                m_bOffScreenRender;
      bool                                m_bMoveWindow;
      bool                                m_bVoidPaint;
      bool                                m_bRedrawing;
      bool                                m_bLockWindowUpdate;
      bool                                m_bLayoutEnable;
      bool                                m_bNeedLayout;
      bool                                m_bReposition;
      bool                                m_bRedrawOnVisible;

      bool                                m_bSaveWindowRect;
      bool                                m_bEnableSaveWindowRect2;

      bool                                m_bShowSoftwareKeyboard;
      ::user::primitive *                 m_pelementalSoftwareKeyboard;
      index                               m_iSoftwareKeyboardEventId;

      alpha_source *                      m_palphasource;

      i32                             m_iItemHeight;

      point                               m_pointMoveCursor;

      bool                                m_bDefaultWalkPreTranslateParentTree;

      ::aura::drawable *                  m_pdrawableBackground;
      bool                                m_bBackgroundBypass;

      tick                                m_tickLastFullUpdate;
      bool                                m_bSizeMove;
      tick                                m_tickLastVisualChange;

      __pointer(primitive_impl)           m_pimpl;
      __pointer(interaction_impl)                m_pimpl2;
      interaction *                       m_puserinteraction;

      interaction_ptra                    m_uiptraOwned;
      interaction_pointer_array                     m_uiptraChild;
      string                              m_strName;
      interaction *                       m_puiOwner;
      u64                                 m_uiUserInteractionFlags;
      bool                                m_bCursorInside;
      e_cursor                            m_ecursor;
      bool                                m_bRectOk;
      __pointer(::aura::session)                 get_context_session();
      bool                                m_bMessageWindow;

      //bool                                m_bCreated;

      //bool                                m_bVisible;
      //bool                                m_bRecalcVisible;

      string                              m_strWindowText;

      bool                                m_bModal;
      ::thread *                          m_pthreadModal;

      __pointer(::thread)                        m_pthreadUserInteraction;

      id                                  m_idModalResult; // for return values from interaction_impl::RunModalLoop

      i32                             m_nModalResult; // for return values from ::interaction_impl::RunModalLoop

      __pointer(interaction)                     m_ptooltip;

      /// The menu_item this user_interaction (window)
      /// represents (this window is a button [a menu button],
      /// this window is a checkbox [a menu checkbox],
      /// this window is a player/view [a menu picture/video/chat?!])
      __pointer(menu_item)                       m_pmenuitemThis;

      __pointer_array(menu)                           m_menuaGuest;


      bool                                m_bWfiUpDownTarget;



      interaction();
      interaction(::object * pobject);
      virtual ~interaction();


      void user_interaction_common_construct();

      bool is_ok()
      {

         return ::is_set(this)
            && m_pimpl.is_set()
            && (m_ewindowflag & window_flag_is_window)
            && !m_pimpl->m_bDestroying;

      }

      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      virtual bool create_control(class control_descriptor * pdescriptor);


      virtual bool add_control(arguments arguments);


      inline bool is_graphical() const { return !m_bMessageWindow && m_ewindowflag & window_flag_graphical; }


      virtual bool child_set_unique_id(::user::interaction * pinteraction);

      virtual string default_id_prefix() const;

      tooltip *         get_tooltip();

      virtual double get_rotate();
      virtual ::user::form * get_form();

      virtual ::user::form * get_parent_form();

      virtual ::user::interaction * get_bind_ui();



      //virtual bool defer_check_layout();
      //virtual bool check_need_layout();
      //virtual void clear_need_layout();
      //virtual void set_need_layout(bool bAscendants = true);
      //virtual void set_need_redraw(bool bAscendants = true) override;
      //virtual void layout();

      //virtual bool ZOrder(class zorder zorder);

      //virtual bool defer_check_layout();
      //virtual bool check_need_layout();
      //virtual void clear_need_layout();

      virtual bool should_save_window_rect();
      virtual bool WindowDataSaveWindowRect();
      virtual bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false);


      virtual void on_defer_display();

      virtual bool defer_display();
      virtual bool prodevian_display();
      virtual bool prodevian_appearance();
      virtual bool prodevian_zorder();
      virtual bool prodevian_reposition();
      virtual bool prodevian_layout();


      virtual void prodevian_stop() override;

      virtual void prodevian_redraw() override;

      virtual void _001OnAfterAppearance();


      virtual void defer_place(const ::rect & rectRequest);


      virtual void set_reposition(bool bSetThis = true);
      virtual void set_need_layout(bool bAscendants = true);
      virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void post_redraw(bool bAscendants = true) override;
      virtual void show_window();

      virtual void prodevian_update_visual(bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void _001UpdateWindow() override;
      virtual void window_apply_visual(const struct window_state & windowstate) override;


      virtual void prodevian_prepare_window_minimize(::eactivation eactivation) override;
      virtual void prodevian_prepare_window_maximize() override;
      virtual void prodevian_prepare_window_full_screen(const ::rect & rectHint = nullptr) override;
      virtual void prodevian_prepare_window_restore(edisplay edisplay) override;
      virtual void prodevian_prepare_window_dock(edisplay edisplay) override;



      inline bool set_prodevian() { return add_prodevian(this); }
      inline bool clear_prodevian() { return remove_prodevian(this); }

      virtual bool add_prodevian(::context_object * pobject) override;
      virtual bool remove_prodevian(::context_object * pobject) override;
      inline bool has_prodevian() const noexcept;


      virtual bool is_frame_window();


      virtual bool create_message_queue(const char * lpszName) override;


      virtual bool has_text_input();
      virtual COLORREF get_action_hover_border_color();

      virtual bool kick_queue();

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

      virtual bool initialize_native_window(::user::native_window_initialize * pinitialize) override;

#endif

      virtual bool contains_user_interaction(::user::interaction * pinteraction, bool bRecursive = true) const;


      virtual void on_select() override;

      virtual bool is_place_holder() override;

      virtual e_cursor get_cursor();
      virtual bool set_cursor(e_cursor ecursor);


      virtual bool is_left_button_pressed();
      virtual bool has_action_hover();


      virtual ::index current_item();

      virtual ::user::e_element get_hover_element();
      virtual ::index get_hover_item();


      virtual bool _is_window() const override;
      inline bool is_window() const { return m_ewindowflag & window_flag_is_window; }

      virtual void ExitHelpMode();

      virtual void on_control_event(::message::base * pbase);

      virtual LONG get_window_long(i32 nIndex) const override;
      virtual LONG set_window_long(i32 nIndex,LONG lValue) override;

      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex,LONG_PTR lValue) override;

      virtual bool on_before_set_parent(::user::interaction * pinterface);
      virtual bool on_set_parent(::user::interaction * pinterface);
      virtual void on_after_set_parent();

      virtual ::user::primitive * first_child_elemental() override;
      virtual ::user::primitive * top_elemental() override;
      virtual ::user::primitive * under_elemental() override;
      virtual ::user::primitive * above_elemental() override;
      virtual ::user::primitive * next_elemental() override;
      virtual ::user::primitive * previous_elemental() override;



      virtual ::user::interaction * first_child() override;
      virtual ::user::interaction * last_child() override;
      virtual ::user::interaction * last_sibling() override;
      virtual ::user::interaction * next_sibling() override;
      virtual ::user::interaction * previous_sibling() override;
      virtual ::user::interaction * first_sibling() override;
      virtual ::user::interaction * next_sibling(::user::interaction * pinteraction) override;
      virtual ::user::interaction * previous_sibling(::user::interaction * pinteraction) override;


      virtual void mouse_hover_add(::user::interaction * pinterface) override;
      virtual bool mouse_hover_remove(::user::interaction * pinterface) override;


      template < typename TYPE >
      TYPE * typed_descedant(::user::interaction * puiExclude = nullptr)
      {

         for (auto & pinteraction : m_uiptraChild)
         {

            if (pinteraction != puiExclude)
            {

               TYPE * point = dynamic_cast < TYPE * > (pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }


         }

         for (auto & pinteraction : m_uiptraChild)
         {

            if (pinteraction != puiExclude)
            {

               TYPE * point = pinteraction->typed_descedant < TYPE >(pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }


         }

         return nullptr;

      }


      template < typename TYPE >
      __pointer(TYPE) & _001TypedWindow(__pointer(TYPE) &sp)
      {

         return sp = _001TypedWindow<TYPE>();

      }


      template < typename TYPE >
      TYPE * _001TypedWindow() // search descedants first, then ascendants descedants.
      {

         ::user::interaction * pinteraction = this;

         ::user::interaction * puiExclude = nullptr;

         while (pinteraction != nullptr)
         {

            TYPE * point = pinteraction->typed_descedant < TYPE >(puiExclude);

            if (point != nullptr)
            {

               return point;

            }

            puiExclude = pinteraction;

            pinteraction = pinteraction->GetParent();

            if (pinteraction == nullptr)
            {

               return nullptr;

            }

            point = dynamic_cast < TYPE * > (pinteraction);

            if (point != nullptr)
            {

               return point;

            }

         }

         return nullptr;

      }


      virtual bool CheckAutoCenter() override;

      virtual void track_mouse_hover() override;
      virtual void track_mouse_leave() override;

      // dialog support
      virtual void update_dialog_controls(channel * ptarget) override;
      virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;
      virtual void _001Emphasize(int cx, int cy);
      virtual id   run_modal_loop(::user::interaction * pinteraction,u32 dwFlags = 0) override;
      virtual id   RunModalLoop(u32 dwFlags = 0) override;
      virtual id   _001RunModalLoop(u32 dwFlags = 0) override;
      virtual bool ContinueModal() override;
      virtual void EndModalLoop(id nResult) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true) override;


      virtual ::user::interaction * get_os_focus_uie();


      virtual bool on_keyboard_focus(::user::primitive * pfocus) override;

      virtual void get_child_rect(RECT* prect);

      inline auto get_child_rect() { ::rect rect(no_init); get_child_rect(&rect); return rect; }

      //using ::user::primitive::get_client_rect;
      //using ::user::primitive::get_window_rect;

      virtual bool scroll_bar_get_client_rect(RECT * prect);

      //virtual bool _get_client_rect(RECT64 * prect) override;
      //virtual bool _get_window_rect(RECT64 * prect) override;

      //virtual bool client_to_screen(RECTD * prect) override;

      //virtual bool client_to_screen(RECT * prect) override;

      //virtual bool client_to_screen(RECT64 * prect) override;

      //virtual bool client_to_screen(POINTD * ppoint) override;

      //virtual bool client_to_screen(LPPOINT ppoint) override;

      //virtual bool client_to_screen(POINT64 * ppoint) override;

      //virtual bool screen_to_client(RECT * prect) override;

      //virtual bool screen_to_client(RECTD * prect) override;

      //virtual bool screen_to_client(RECT64 * prect) override;

      //virtual bool screen_to_client(LPPOINT ppoint) override;

      //virtual bool screen_to_client(POINTD * ppoint) override;

      //virtual bool screen_to_client(POINT64 * prect) override;




      //virtual bool set_window_pos(class zorder zorder, const ::rect & rect, UINT nFlags = 0) override;
      //virtual bool set_window_pos(class zorder zorder, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags = 0) override;

      //virtual bool defer_set_window_pos(class zorder zorder, const ::rect & rect, UINT nFlags) override; // only set_windows_pos if get_parent()->screen_to_client(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(RECT * prect) override;

      //virtual bool defer_set_window_pos(class zorder zorder,i32 x,i32 y,i32 cx,i32 cy,UINT nFlags) override; // only set_windows_pos if get_parent()->screen_to_client(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(RECT * prect) override;

      //virtual i32 SetWindowRgn(HRGN hRgn,bool bRedraw) override;
      //virtual i32 GetWindowRgn(HRGN hRgn) override;

      virtual void on_visual_applied();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_reposition() override;
      virtual void on_show_window() override;
      virtual void _on_show_window();
      //virtual void defer_is_window_visible_recursive();

      virtual void _do_show_window() override;

      virtual void defer_save_window_placement();

      //virtual void BringToTop(::edisplay edisplay) override;
      //virtual bool BringWindowToTop() override;

#ifdef WINDOWS_DESKTOP
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);

#endif

      //virtual bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);


      virtual bool pre_create_window(::user::create_struct& cs) override;


      virtual bool subclass_window(oswindow posdata) override;
      virtual oswindow unsubclass_window() override;


      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_control(class ::user::control_descriptor * pdescriptor);

      virtual bool create_window(::user::interaction *pparent, const ::id & id) override;
      virtual bool create_window(const char * pszClassName, const char * pszWindowName,u32 uStyle, ::user::interaction * puiParent, const ::id & id, ::create * pcreate = nullptr) override;

      virtual bool create_window_ex(::user::create_struct & cs, ::user::interaction * puiParent = nullptr, const ::id & id = ::id()) override;
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(RECT * pClientRect,UINT nAdjustType = adjustBorder) override;


      virtual bool IsTopParentActive() override;
      virtual void ActivateTopParent() override;

      virtual bool DestroyWindow() override;

      virtual void destroy_window() override;

      virtual void set_finish() override;
      virtual void finalize() override;


#ifdef WINDOWS

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,
                                ::draw2d::region* prgnUpdate = nullptr,
                                UINT flags = RDW_INVALIDATE | RDW_ERASE) override;

#else

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,
                                ::draw2d::region* prgnUpdate = nullptr,
                                UINT flags = 0) override;

#endif


      virtual void register_drop_target();




      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = TRUE) override;
      virtual bool GetUpdateRect(RECT * prect,bool bErase = FALSE) override;

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE) override;
      virtual void Invalidate(bool bErase = TRUE) override;
      virtual void InvalidateRect(const ::rect & rect,bool bErase = TRUE) override;

      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE) override;
      virtual void ValidateRect(const ::rect & rect) override;

      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      virtual void ShowOwnedPopups(bool bShow = TRUE) override;


      virtual u32 GetStyle() const override;
      virtual u32 GetExStyle() const override;
      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;
      virtual LRESULT Default() override;

      virtual LRESULT send(::message::base * pbase) override;
      virtual bool post(::message::base * pbase) override;
      virtual LRESULT send_message(UINT uiMessage,WPARAM wparam = 0,lparam lparam = 0) override;

      virtual LRESULT message_call(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0) override;
      virtual LRESULT message_call(message::base * base) override;


#ifdef LINUX

      virtual LRESULT send_x11_event(void * pevent); // XEvent *

#endif

      virtual bool post_message(UINT message,WPARAM wParam = 0,lparam lParam = 0) override;

      virtual bool post_object(UINT message, WPARAM wParam, lparam lParam);

      //virtual bool post_simple_command(e_simple_command ecommand,lparam lParam = 0) override;


      //virtual bool display(::edisplay edisplay = display_normal) override;
      //inline bool display(bool bDisplay = true) { return display((::edisplay) (bDisplay ? display_normal : display_none)); }

      virtual void SetWindowDisplayChanged() override;

      // timer Functions
      virtual bool set_timer(uptr nIDEvent, ::duration durationElapse, PFN_TIMER pfnTimer = nullptr);
      virtual bool SetTimer(uptr nIDEvent,UINT nElapse,PFN_TIMER pfnTimer = nullptr) override;
      virtual bool KillTimer(uptr nIDEvent) override;

      virtual bool is_this_enabled() override;
      virtual bool enable_window(bool bEnable = TRUE) override;

      virtual void _001Print(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      // drawn after children
      virtual void _008CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool is_custom_draw();

      virtual id GetDlgCtrlId() const override;
      virtual id SetDlgCtrlId(::id id) override;


      virtual bool SetCapture(::user::interaction * pinteraction = nullptr) override;
      virtual bool ReleaseCapture() override;
      virtual ::user::interaction * GetCapture() override;


      virtual bool has_focus() override;
      virtual bool SetFocus() override;
      virtual ::user::interaction * GetFocus() override;
      virtual bool SetForegroundWindow() override;
      virtual bool is_active() override;
      virtual interaction * GetActiveWindow() override;
      virtual interaction * SetActiveWindow() override;


      virtual void on_calc_size(calc_size * pcalcsize);

      virtual void walk_pre_translate_tree(::message::message * pmessage, ::user::interaction * puiStop = nullptr);

      virtual void set_window_text(const char * pszString) override;


      strsize _009GetWindowText(char * psz, int n) override;
      virtual strsize _009GetWindowTextLength() override;

      virtual strsize get_window_text(char * pszStringBuf,strsize nMaxCount) override;

      virtual string get_window_text() override;
      virtual void get_window_text(string & rectString) override;
      virtual strsize get_window_text_length() override;

      //virtual void _001SetText(const string & str, const ::action_context & action_context) override;

      virtual void install_message_routing(::channel * pchannel) override;

      //void user_interaction_update_visibility_cache(bool bVisible);
//#ifdef _DEBUG
      //bool is_window_visible();
//#else
//      inline bool is_window_visible()
//      {
//
//         if (m_ewindowflag & window_flag_recalc_visible)
//         {
//
//            m_ewindowflag -= flag_recalc_visible;
//
//            m_ewindowflag.add(window_flag_visible, _is_window_visible());
//
//         }
//
//         return m_ewindowflag & window_flag_visible;
//
//      }
//#endif

      //virtual bool _is_window_visible() override;

      virtual void _000OnMouseLeave(::message::message* pmessage) override;

      virtual void _000OnMouse(::message::mouse * pmouse);
      virtual void _000OnThisMouse(::message::mouse * pmouse);
      virtual void _000OnChildrenMouse(::message::mouse * pmouse);
      virtual void _000OnKey(::message::key * pkey);
      virtual void _000OnDrag(::message::drag_and_drop * pdrag);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseEnter);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      virtual void _001OnTimer(::timer * ptimer) override;
      virtual bool on_timer(::timer * ptimer) override;
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnCommand);
      DECL_GEN_SIGNAL(_001OnSimpleCommand);
      //DECL_GEN_SIGNAL(_001OnSetSchema);



      virtual DECL_GEN_SIGNAL(_002OnLButtonDown);
      virtual DECL_GEN_SIGNAL(_002OnLButtonUp);
      virtual DECL_GEN_SIGNAL(_002OnMouseMove);
      virtual DECL_GEN_SIGNAL(_002OnMouseEnter);
      virtual DECL_GEN_SIGNAL(_002OnMouseLeave);
      virtual DECL_GEN_SIGNAL(_002OnKeyDown);
      virtual DECL_GEN_SIGNAL(_002OnKeyUp);
      virtual DECL_GEN_SIGNAL(_002OnTimer);


      DECL_GEN_SIGNAL(_001OnBaseWndGetProperty);


      virtual LRESULT _001BaseWndGetProperty(EProperty eproperty,LPARAM lparam);




      virtual bool _001IsPointInside(::point point) override;
      virtual ::user::interaction * _001FromPoint(::point point,bool bTestedIfParentVisible = false) override;

      virtual void OnLinkClick(const char * psz,const char * pszTarget = nullptr) override;

      virtual void pre_translate_message(::message::message * pmessage) override;


      ::user::interaction * get_child_by_name(const char * lpszName,i32 iLevel = -1);
      ::user::interaction * get_child_by_id(id id,i32 iLevel = -1);


      virtual bool IsAscendant(const interaction * puiIsAscendant) const override;
      virtual bool IsParent(const interaction * puiIsParent) const override;
      virtual bool IsChild(const interaction * puiIsChild) const override;
      virtual bool IsDescendant(const interaction * puiIsDescendant) const override;

      virtual ::user::primitive * get_wnd_elemental() const override;
      virtual ::user::interaction * get_wnd() const override;
      virtual ::user::interaction * get_wnd(UINT nCmd) const override;

      virtual ::user::interaction * SetParent(::user::interaction * pinteraction) override;
      virtual ::user::interaction * SetOwner(::user::interaction * pinteraction) override;

      virtual ::user::primitive * get_parent() const override;

      virtual ::user::interaction * GetTopWindow() const override;
      virtual ::user::interaction * GetParent() const override;
      virtual ::user::interaction * GetTopLevel() const override;
      virtual ::user::interaction * GetParentTopLevel() const override;
      virtual ::user::interaction * EnsureTopLevel() override;
      virtual ::user::interaction * EnsureParentTopLevel() override;
      virtual ::user::interaction * GetOwner() const override;
      virtual ::user::interaction * GetParentOwner() const override;
      virtual ::user::interaction * GetParentOrOwner() const override;
      virtual ::user::interaction * GetTopLevelOwner() const override;
      virtual ::user::frame * GetFrame() const override;
      virtual ::user::frame * GetParentFrame() const override;
      virtual ::user::frame * GetTopLevelFrame() const override;
      virtual ::user::frame * GetParentTopLevelFrame() const override;
      virtual ::user::frame * EnsureParentFrame() override;
      virtual ::user::frame * GetOwnerFrame() const override;

      virtual void send_message_to_descendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE) override;

      virtual void route_message_to_descendants(::message::message * pmessage) override;


      virtual i32 get_descendant_level(::user::interaction * pinteraction) override;
      virtual bool is_descendant(::user::interaction * pinteraction,bool bIncludeSelf = false) override;

      virtual oswindow GetParentHandle() const;

      virtual ::user::interaction * get_focusable_descendant(::user::interaction * pinteraction = nullptr) override;

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, ::id idLeftOver, UINT nFlag = reposDefault, RECT * prectParam = nullptr, const ::rect & rectClient = nullptr, bool bStretch = true) override;

      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point,UINT nFlags) override;

#ifdef WINDOWS_DESKTOP
      virtual ::user::interaction * get_next_window(UINT nFlag = GW_HWNDNEXT);
#else
      virtual ::user::interaction * get_next_window(UINT nFlag = 0) override;
#endif

      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * get_next(bool bIgnoreChildren = false,i32 * piLevel = nullptr) override;

      virtual ::user::interaction * GetLastActivePopup() override;

      virtual bool is_message_only_window() const override;

      virtual void pre_subclass_window() override;

      virtual void PostNcDestroy() override;

      virtual LRESULT DefWindowProc(UINT uiMessage, WPARAM wparam, lparam lparam) override;


      //virtual LRESULT call_message_handler(UINT message, WPARAM wparam, lparam lparam) override;

      //virtual void pre_translate_message(::message::base * pbase);

      virtual void message_handler(::message::base * pbase) override;
      virtual LRESULT message_handler(LPMESSAGE pmessage) override;

      virtual void GuieProc(::message::message * pmessage) override;

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;


      virtual oswindow get_handle() const override;
      virtual bool attach(oswindow oswindow_New) override;
      virtual oswindow detach() override;

      virtual void * get_os_data() const;


      template < class T >
      __pointer(T) GetTypedParent() const
      {

         ASSERT_VALID(this);

         __pointer(T) point;

         ::user::interaction * puiParent = GetParent();  // start with one parent up

         while(puiParent != nullptr)
         {

            point = puiParent;

            if(point.is_set())
            {

               return point;

            }

            puiParent = puiParent->GetParent();

         }

         return nullptr;

      }


      virtual bool can_merge(::user::interaction * pinteraction) override;
      virtual bool merge(::user::interaction * pinteraction) override;







      virtual void _001OnTriggerMouseInside() override;

      //#ifdef _UWP
      //      Agile<Windows::UI::Core::CoreWindow> get_os_window();
      //#endif

      virtual bool window_is_notify_icon_enabled();
      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;


//      virtual pointd client_screen_top_left() override;

      virtual void viewport_screen_to_client(POINT * ppt) override;
      virtual void viewport_client_to_screen(POINT * ppt) override;
      virtual void viewport_client_to_screen(RECT * ppt) override;
      virtual void viewport_screen_to_client(RECT * ppt) override;


      virtual string get_window_default_matter() override;
      virtual string get_window_icon_matter() override;
      virtual u32 get_window_default_style() override;
      virtual e_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command * psimplecommand) override;
      virtual void on_command(::user::command * pcommand) override;


      // Window-Management message handler member functions
      virtual bool OnCommand(::message::base * pbase) override;
      virtual bool OnNotify(::message::base * pbase) override;
      virtual bool OnChildNotify(::message::base * pbase) override;



      virtual bool is_selected(::data::item * pitem) override;

      virtual __pointer(place_holder) place_hold(::user::interaction * pinteraction) override;

#if defined(_UWP) && defined(__cplusplus_winrt)
      static Agile<Windows::UI::Core::CoreWindow>(*s_get_os_window)(interaction * pinteraction);
      Agile<Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static Agile<Windows::UI::Core::CoreWindow> get_os_window(interaction * pinteraction)
      {
         return (*s_get_os_window)(pinteraction);
      }
      static Agile<Windows::UI::Core::CoreWindow> get_os_window_default(interaction * pinteraction)
      {
         UNREFERENCED_PARAMETER(pinteraction);
         return nullptr;
      }
#endif
      virtual bool has_command_handler(::user::command * pcommand) override;



      virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags, const ::point & point) override;
      virtual __pointer(::user::menu) track_popup_menu(::xml::node * pnode,i32 iFlags, const ::point & point, const ::size & sizeMinimum = nullptr) override;

      virtual bool track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags,const ::point & point) override;
      virtual __pointer(::user::menu) track_popup_xml_string_menu(var varXml, i32 iFlags, const ::point & point, const ::size & sizeMinimum = nullptr) override;

      virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags,::message::message * pmessage) override;
      virtual bool track_popup_menu(::xml::node * pnode,i32 iFlags,::message::message * pmessage) override;

      virtual bool track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags,::message::message * pmessage) override;

      virtual bool track_popup_menu(::user::menu_item * pitem,i32 iFlags) override;
      virtual bool track_popup_menu(::xml::node * pnode,i32 iFlags) override;

      virtual bool track_popup_xml_matter_menu(const char * pszMatter,i32 iFlags) override;


      virtual void _001OnExitIconic() override;
      virtual void _001OnExitFullScreen() override;


      virtual bool _001OnBeforeAppearance();
      virtual bool _001OnExitAppearance();


      virtual void on_start_layout_experience(e_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(e_layout_experience elayoutexperience) override;

      //virtual edisplay get_display() override;
      //virtual edisplay get_previous_display() override;

      //virtual bool set_appearance(edisplay edisplay) override;
      //virtual bool set_previous_display(edisplay edisplay) override;


      virtual void show_keyboard(bool bShow = true) override;

      virtual void keep_alive(::object * pliveobject = nullptr) override;

      virtual ::user::interaction * best_top_level_parent(RECT * prect);


      virtual index get_zoneing(::rect * prect, const ::rect & rect, edisplay edisplay);

      virtual edisplay initial_restore_display();

      virtual index calculate_broad_and_compact_restore(RECT * prectWkspace = nullptr, SIZE * psizeMin = nullptr, const ::rect & rectHint = nullptr);

      virtual void reset_window_state();

      virtual index make_zoneing(RECT * prect, const ::rect & rect = nullptr, bool bSet = false, ::edisplay * pedisplay = nullptr, ::eactivation eactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index best_zoneing(RECT * prect, const ::rect & rect = nullptr, bool bSet = false, ::edisplay * pedisplay = nullptr, ::eactivation eactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index best_monitor(RECT * prect, const ::rect & rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index best_wkspace(RECT * prect, const ::rect & rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index good_restore(RECT * prect, const ::rect & rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top, edisplay edisplay = display_restore);
      virtual index good_iconify(RECT * prect, const ::rect & rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);

      virtual index good_move(RECT * prect, const ::rect & rect = nullptr, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index get_best_zoneing(edisplay & edisplay, ::rect * prect, const ::rect & rectRequest = ::rect(), bool bPreserveSize = false);
      virtual index get_best_wkspace(::rect * prect, const ::rect& rect, ::eactivation eactivation = activation_none);

      virtual bool get_rect_normal(RECT * prect);



      virtual void set_viewport_offset_x(int x);
      virtual void set_viewport_offset_y(int y);
      virtual void set_viewport_offset(int x,int y);
      virtual void offset_viewport_offset_x(int x);
      virtual void offset_viewport_offset_y(int y);
      virtual void offset_viewport_offset(int x, int y);
      virtual bool validate_viewport_offset(point & point);
      virtual void on_change_viewport_offset();
      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics);
      virtual ::point get_viewport_offset();
      virtual ::size get_total_size();
      virtual void on_change_view_size();
      virtual ::size get_page_size();
      virtual ::point get_parent_viewport_offset();
      virtual ::point get_ascendant_viewport_offset();
      virtual void get_margin_rect(RECT * prectMargin);

      virtual int get_final_x_scroll_bar_width();
      virtual int get_final_y_scroll_bar_width();


      virtual bool is_system_message_window();

      //virtual ::user::style * get_user_style() override;
//      virtual ::user::style * parent_userstyle() override;

//      bool set(::draw2d::graphics_pointer & pgraphics, e_font efont);

      /*

      static __pointer(::message::base) peek_message(LPMESSAGE pmsg,::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);

      static __pointer(::message::base) get_message(LPMESSAGE pmsg,::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax);

      static __pointer(::message::base) peek_message(::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      static __pointer(::message::base) get_message(::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax);

      virtual __pointer(::message::base) peek_message(LPMESSAGE pmsg,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);

      virtual __pointer(::message::base) get_message(LPMESSAGE pmsg,UINT wMsgFilterMin,UINT wMsgFilterMax);

      virtual __pointer(::message::base) peek_message(UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      virtual __pointer(::message::base) get_message(UINT wMsgFilterMin,UINT wMsgFilterMax);

      */


      //__pointer(::message::base) get_message_base(UINT uiMessage, WPARAM wparam, lparam lparam);



      //void transfer_from(::aura::timer_array & ta, interaction * pinteraction);

      virtual window_graphics * get_window_graphics() override;

      virtual bool is_composite() override;

      virtual ::size get_window_minimum_size();



      // Up Down Target();


      virtual void UpDownTargetAttach(::user::interaction * pupdown);
      virtual void UpDownTargetDetach(::user::interaction * pupdown);

      virtual bool OnUpDownTargetAttach(::user::interaction * pupdown);
      virtual bool OnUpDownTargetDetach(::user::interaction * pupdown);


      virtual string calc_window_class();


      virtual void user_interaction_on_destroy();
      virtual void user_interaction_on_hide();





      virtual void on_remove_child(::user::interaction * pinteraction);
      virtual void on_remove_place_holder_child(::user::interaction * pinteraction);
      virtual void on_hide_child(::user::interaction * pinteraction);
      virtual void on_hide_place_holder_child(::user::interaction * pinteraction);



      virtual void _001GetXScrollInfo(scroll_info & info);
      virtual void _001GetYScrollInfo(scroll_info & info);
      virtual void layout_scroll_bar();

      // view support
      using primitive::update;
      virtual void update(::update * pupdate) override;

      virtual void keyboard_focus_OnKeyDown(::message::message * pmessage) override;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      virtual bool keyboard_focus_OnChildKillFocus() override;

      virtual bool get_child(__pointer(::user::interaction) & pinteraction);
      virtual bool rget_child(__pointer(::user::interaction) & pinteraction);


      virtual ::user::primitive * get_focus_elemental();
      virtual bool set_focus_elemental(::user::primitive * pelemental);


      virtual bool is_descendant_of(::user::interaction * puiAscendantCandidate, bool bIncludeSelf);
      virtual bool is_ascendant_of(::user::interaction * puiDescendantCandidate, bool bIncludeSelf);

      virtual bool is_descendant_of_or_owned_by(::user::interaction * puiAscendantCandidate, bool bIncludeSelf);
      virtual bool is_ascendant_or_owner_of(::user::interaction * puiDescendantCandidate, bool bIncludeSelf);

      virtual bool show_tooltip(const string & str,bool bError);

      virtual bool layout_tooltip(bool bForceShow = false);

      virtual bool hide_tooltip();

      virtual bool frame_is_transparent();

      virtual double get_alpha();



      virtual void destruct() override;



      virtual void defer_notify_mouse_move();

      virtual void defer_notify_mouse_move(bool & bPointInside, point & pointLast);

      virtual bool has_pending_graphical_update() override;

      virtual bool enable_transparent_mouse_events(bool bEnable = true);

      virtual void check_transparent_mouse_events();


      virtual void redraw_add(::object * pobject);

      virtual void redraw_remove(::object * pobject);

      virtual bool has_redraw();

      virtual void on_after_graphical_update() override;


      virtual void _001OnDeiconify(edisplay edisplay);

      virtual void update(::update * pupdate);

      //virtual bool is_this_visible() override;

      virtual bool on_click(const ::user::item & item) override;
      virtual bool _001OnRightClick(uptr nFlag, const ::point & point);


      virtual int width();
      virtual int height();

      virtual int client_width();
      virtual int client_height();

      virtual ::sized get_size();
      virtual ::sized get_client_size();

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics);

      virtual void wait_redraw();

      virtual bool has_pending_redraw_flags() override;


      virtual void set_ipc_copy(bool bSet = true) override;


      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the style_base pure function overrides
      // that way, if some styled class overriding any style_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pstylebase compositor
      // to implement the utility functions
      //virtual bool _001GetMainFrameTranslucency(::user::e_translucency & etranslucency);


      using style::select_text_color;
      virtual bool select_text_color(::draw2d::graphics_pointer & pgraphics, e_color ecolor = color_text);
      using style::select_solid_brush;
      virtual bool select_solid_brush(::draw2d::graphics_pointer & pgraphics, e_color ecolor);
      using style::set;
      virtual bool set(::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);

      virtual bool select_text_color(e_color ecolor = color_text);
      virtual bool select_solid_brush(e_color ecolor);
      virtual bool set(e_font efont = font_default);

      virtual void defer_show_software_keyboard(::user::primitive * pelemental, bool bShow, string str, strsize iBeg, strsize iEnd);

      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd);

      //using style::_001GetColor;
      //virtual COLORREF           _001GetColor(e_color ecolor, COLORREF crDefault = 0);
      //using style::_001GetFont;
      //virtual ::draw2d::font_pointer  _001GetFont(e_font efont, ::draw2d::font * pfont = nullptr);
      //using style::_001GetTranslucency;
      //virtual e_translucency     _001GetTranslucency(e_element eelement = element_none, e_translucency etranslucencyDefault = translucency_undefined);
      //using style::_001GetFlag;
      //virtual bool               _001GetFlag(::user::e_flag eflag, bool bDefault = false);
      //using style::_001GetRect;
      //virtual const rect &               _001GetRect(::user::e_rect erect, ::rect rectDefault = nullptr);
      //using style::_001GetInt;
      //virtual int                _001GetInt(::user::e_int eint, int iDefault = 0);
      //using style::_001GetDouble;
      //virtual double             _001GetDouble(::user::e_double edouble, double dDefault = 0.0);

      //using style::_001IsBackgroundBypass;
      //virtual bool _001IsBackgroundBypass(e_element eelement = element_none);
      //using style::_001IsTransparent;
      //virtual bool _001IsTransparent(e_element eelement = element_none);
      //using style::_001IsTranslucent;
      //virtual bool _001IsTranslucent(e_element eelement = element_none);
      //using style::_001HasTranslucency;
      //virtual bool _001HasTranslucency(e_element eelement = element_none);

      //// e_style composition
      //using style::style_color;
      //virtual bool style_color(COLORREF & cr, e_color ecolor);
      //using style::style_font;
      //virtual bool style_font(::draw2d::font_pointer & sp, e_font efont);
      //using style::style_translucency;
      //virtual bool style_translucency(e_translucency & etranslucency, e_element eelement);
      //using style::style_flag;
      //virtual bool style_flag(bool & bSet, ::user::e_flag eflag);
      //using style::style_rect;
      //virtual bool style_rect(const rect & & rect, ::user::e_rect erect);
      //using style::style_int;
      //virtual bool style_int(int & i, ::user::e_int eint);
      //using style::style_double;
      //virtual bool style_double(double & i, ::user::e_double edouble);


      virtual void set_stock_icon(e_stock_icon eicon);
      virtual e_stock_icon get_stock_icon();

      virtual e_control_type get_control_type() override;

      virtual void nextstyle(style_context * pcontext) override;

      virtual void post_runnable(::object * pobjectRunnable);
      virtual void prodevian_runnable(::object * pobjectRunnable);

      virtual void send_runnable(::object * pobjectRunnable, ::duration durationTimeout = ::duration::infinite());

      template < typename PRED >
      void post_pred(PRED pred)
      {

         post_runnable(__runnable(pred));

      }

      template < typename PRED >
      void prodevian_pred(PRED pred)
      {

         prodevian_runnable(__runnable(pred));

      }

      template < typename PRED >
      void pred(PRED pred)
      {

         post_pred(pred);

      }

      template < typename PRED >
      void send_pred(PRED pred, ::duration durationTimeout = ::duration::infinite())
      {

         send_runnable(__runnable(pred), durationTimeout);

      }

      //virtual void _on_display(bool bKickIdle = true) override;

      //virtual void kick_idle(e_message emessage) override;




   };


   inline bool layout::is_window_visible() const noexcept
   {

      if (m_pdescriptor.is_null())
      {

         return false;

      }

      return m_pdescriptor->m_puserinteractionParent != NULL && !m_pdescriptor->m_puserinteractionParent->is_window_visible() ? false : is_this_visible();

   }

   inline bool layout::is_window_screen_visible() const noexcept
   {

      return m_pdescriptor->m_puserinteractionParent != NULL && !m_pdescriptor->m_puserinteractionParent->is_window_screen_visible() ? false : is_this_screen_visible();

   }

} // namespace user

// timer_ui works correctly when timer is originated from SetTimer call
//inline ::user::interaction * timer_ui(::timer * ptimer)
//{
//
//   return (::user::interaction *) ptimer->m_pvoidData;
//
//}



CLASS_DECL_AURA ::user::interaction * oswindow_interaction(oswindow oswindow);


