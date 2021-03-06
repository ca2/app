#pragma once


namespace user
{


   class CLASS_DECL_AURA interaction :
      virtual public ::user::primitive,
      virtual public ::timer_callback,
      virtual public ::conversation
   {
   public:


      class iterator
      {
      public:

         
         enum_next                  m_enext;
         ::user::interaction *      m_puserinteraction;
         ::user::interaction *      m_puserinteractionStop;


         iterator(const iterator & iterator) :
            m_puserinteraction(iterator.m_puserinteraction),
            m_puserinteractionStop(iterator.m_puserinteractionStop),
            m_enext(iterator.m_enext)
         {

         }


         iterator(::user::interaction * puserinteraction, enum_next enext, ::user::interaction * puserinteractionStop = nullptr) :
            m_puserinteraction(puserinteraction),
            m_enext(enext),
            m_puserinteractionStop(nullptr)
         {

         }

         ::user::interaction * operator *() { return m_puserinteraction; }

         ::user::interaction * operator *() const { return m_puserinteraction; }

         iterator begin()
         {

            return *this;

         }

         bool operator != (const iterator & iterator) const
         {

            return m_puserinteraction != iterator.m_puserinteraction;

         }

         iterator end()
         {

            return { m_puserinteractionStop, m_enext, m_puserinteractionStop };

         }


         iterator & operator ++()
         {

            m_puserinteraction = m_puserinteraction->get_window(m_enext);

            return *this;

         }

         iterator operator ++(int)
         {

            auto piterator = *this;

            m_puserinteraction = m_puserinteraction->get_window(m_enext);

            return piterator;

         }


      };


      enum e_non_client
      {

         non_client_background = 1,
         non_client_focus_rect = 2,
         non_client_hover_rect = 4,

      };


      enum e_updown
      {

         updown_normal_frame,
         updown_none,
         updown_up,
         updown_down,

      };

      //union
      //{

      //   struct
      //   {

            bool              m_bExtendOnParent : 1;
            bool              m_bExtendOnParentIfClientOnly : 1;

            bool              m_bToolWindow : 1;
            bool              m_bMessageWindow : 1;
            bool              m_bCompositedFrameWindow : 1;

            bool              m_bEdgeGestureDisableTouchWhenFullscreen : 1;
            bool              m_bVisible : 1;

            bool              m_bMouseHoverOnCapture : 1;
            bool              m_bTrackMouseLeave : 1;
            bool              m_bMouseHover : 1;
            bool              m_bSimpleUIDefaultMouseHandling : 1;
            bool              m_bSimpleUIDefaultMouseHandlingLeftButtonDownCapture : 1;


            //bool              m_bIsWindow : 1;
            //bool              m_bEnable : 1;
            //bool              m_bFocus : 1;
            //bool              m_bActive : 1;
            //bool              m_bRedrawInQueue : 1;
            //bool              m_bVisualChanged : 1;
            //bool              m_bAutoProdevianOnShow : 1;
            //bool              m_bOnShowWindowVisible : 1;
            //bool              m_bOnShowWindowScreenVisible : 1;
            //bool              m_bSatelliteWindow : 1;
            //bool              m_bGraphical : 1;
            //bool              m_bDisableWindowPlacementSnapping : 1;
            //bool              m_bEmbeddedProdevian : 1;
            //bool              m_bArbitraryPositioning : 1;
            //bool              m_bDesktopWindow : 1;
            //bool              m_bDockWindow : 1;
            //bool              m_bLoadWindowRectOnImpl : 1;
            //bool              m_bWindowCreated : 1;
            //bool              m_bUpdown : 1;
            //bool              m_bPostponeVisualUpdate : 1;
            //bool              m_bMiniaturizable : 1;
            //bool              m_bAutoStoreWindowRect : 1;
            //bool              m_bPendingSaveWindowRect : 1;
            //bool              m_bLoadingWindowRect : 1;
            //bool              m_bMainFrame : 1;
            //bool              m_bDestroying : 1;
            //bool              m_bNotVisible : 1;
            //bool              m_bSatelliteWindowIfChild : 1;
            //bool              m_bEmbeddedProdevianIfChild : 1;

      //   }
      //   i64    m_iaFlags[2];

      //};

      oswindow                                     m_oswindow;
      ewindowflag                                  m_ewindowflag;
      bool                                         m_bDerivedHeight;

      //__pointer(::future < ::id >)       m_pprocess;
      __pointer(::user::system)                    m_pusersystem;
      __pointer(::user::interaction)               m_puserinteractionParent;


      // updown
      __pointer(::user::interaction)               m_pupdowntarget;
      ::user::interaction::e_updown                m_eupdown;
      //end updown
      //__pointer(control_descriptor)                m_pdescriptor;
      __pointer(shape_array)                       m_pshapeaClip;

      ::user::interaction_layout                   m_layout;

      //index                                     m_iControl;
      index                                        m_iItem;
      index                                        m_iSubItem;
      index                                        m_iListItem;
      index                                        m_iColumn;
      //__pointer(::user::interaction)            m_puserinteraction;
      //__pointer(::user::interaction)            m_puserinteractionParent;
      __pointer(::user::interaction_layout)     m_playout;
      //index_map < __pointer(interaction) >      m_controlmap;

      __pointer(graphics_call_array)            m_pgraphicscalla;
      //id                                        m_id;
      id                                        m_uiText;
      ::type                                    m_type;
      id                                        m_idPrivateDataSection;
      bool                                      m_bTransparent;
      enum_control_type                         m_econtroltype;
      bool                                      m_bCreated;
      bool                                      m_bSubclassed;
      enum_control_ddx                          m_eddx;
      ::database::key                           m_datakey;
      int                                       m_iDataValue;
      flags < enum_control_function >           m_flagsfunction;
      enum_control_data_type                    m_edatatype;
      ::rectangle_i32                                    m_rectangle;
      property_set                              m_setValue;
      int                                       m_iSubItemDisableCheckBox;
      int                                       m_iSubItemDuplicateCheckBox;
      int_array                                 m_iaSubItemDuplicate;
      int_array                                 m_iaSubItemDisable;

      string                                    m_strClass;
      string_to_string                          m_mapClassStyle;
      string                                    m_strStyle;
      property_set                              m_setStyle;





      //bool                                    m_bOnSetFinish;

      //class draw_select
      //{
      //public:

      //   interaction* m_puserinteraction;
      //   ::draw2d::graphics* m_pgraphics;

      //   draw_select(interaction* pinteraction, ::draw2d::graphics_pointer & pgraphics) :
      //      m_puserinteraction(pinteraction),
      //      m_pgraphics(pgraphics)
      //   {

      //      m_puserinteraction->select(pgraphics);

      //      pgraphics->m_puserinteraction = pinteraction;

      //   }

      //   ~draw_select()
      //   {
      //      m_puserinteraction->select(nullptr);
      //   }

      //};

      bool                                         m_bLayoutModified;

      // control member variables BEGIN
      __pointer(::aura::draw_context)              m_pdrawcontext;
      __pointer(::user::interaction)               m_pwndCustomWindowProc;
      bool                                         m_bCustomWindowProc;
      // index                                        m_iEditItem;
      bool                                         m_bControlExCommandEnabled;
      __pointer(::user::interaction)               m_puiLabel;
      bool                                         m_bIdBound;
      // control member variables END

      string                                       m_strInteractionTag;

      __pointer_array(::user::item)           m_useritema;
      bool                                         m_bOverdraw;
      ::index                                      m_iIndex;
      ::user::item                                 m_itemLButtonDown;
      ::user::item                                 m_itemCurrent;
      ::user::item                                 m_itemHover;
      ::user::item                                 m_itemHoverMouse;
      ::user::item                                 m_itemPressed;
      ::size_i32                                       m_sizeRestoreBroad;
      ::size_i32                                       m_sizeRestoreCompact;
      enumeration < e_non_client >                       m_flagNonClient;
      int                                          m_iMouseMoveSkipCount;
      int                                          m_iMouseMoveSkipSquareDistance;
      ::millis                                     m_millisMouseMoveSkip;
      ::point_i32                                      m_pointMouseMoveSkip;
      ::millis                                     m_millisMouseMovePeriod;
      bool                                         m_bMouseMovePending;
      ::point_i32                                      m_pointMouseMove;
      bool                                         m_bNeedLoadFormData;
      bool                                         m_bNeedSaveFormData;
      millis                                         m_millisLastRedraw;
      ::id                                         m_idView;
      __pointer(::user::form)                      m_pform;
      ::color::color                                      m_colorBackground;
      bool                                         m_bWorkspaceFullScreen;
      point_i32                                        m_pointScroll;
      bool                                         m_bHideOnTransparentFrame;
      bool                                         m_bOffScreenRender;
      bool                                         m_bMoveWindow;
      bool                                         m_bVoidPaint;
      bool                                         m_bRedrawing;
      bool                                         m_bLockWindowUpdate;
      bool                                         m_bLayoutEnable;
      bool                                         m_bRedrawOnVisible;
      bool                                         m_bSaveWindowRect;
      bool                                         m_bEnableSaveWindowRect2;
      bool                                         m_bShowSoftwareKeyboard;
      bool                                         m_bUserInteractionSetFinish;
      //bool                                       m_bFreeHandMouseMove; this is the default
      // if high frequency mouse move notification is required
      // create a fast path/low latency callback system
      ::millis                                     m_millisMouseMove;
      ::millis                                     m_millisMouseMoveIgnore;
      __pointer(alpha_source)                      m_palphasource;
      double                                       m_dItemHeight;
      point_i32                                        m_pointMoveCursor;
      bool                                         m_bDefaultWalkPreTranslateParentTree;
      __pointer(::aura::drawable)                  m_pdrawableBackground;
      bool                                         m_bBackgroundBypass;
      millis                                       m_millisLastFullUpdate;
      bool                                         m_bSizeMove;
      millis                                       m_millisLastVisualChange;
      __reference(::file::insert_item)             m_pitemComposing;
      __pointer(primitive_impl)                    m_pimpl;
      __pointer(interaction_impl)                  m_pimpl2;
      //__pointer(interaction)                       m_puserinteraction;
      primitive_ptra                               m_uiptraOwned;
      __pointer(interaction_array)                 m_puiptraChild;
      string                                       m_strName;
      __pointer(interaction)                       m_puserinteractionOwner;
      u64                                          m_uiUserInteractionFlags;
      bool                                         m_bCursorInside;
      enum_cursor                                  m_ecursor;
      bool                                         m_bRectOk;
      bool                                         m_bParentScroll;
      string                                       m_strWindowText;
      bool                                         m_bModal;
      __pointer(::thread)                          m_pthreadModal;
      __reference(::thread)                        m_pthreadUserInteraction;
      id                                           m_idModalResult; // for return values from interaction_impl::RunModalLoop
      i32                                          m_nModalResult; // for return values from ::interaction_impl::RunModalLoop
      __pointer(interaction)                       m_ptooltip;

      bool                                         m_bNeedRedraw;
      bool                                         m_bNeedLayout;
      bool                                         m_bReposition;
      bool                                         m_bUpdatingVisual;
      bool                                         m_bUpdateVisual;



      ::draw2d::path_pointer                       m_pathFocusRect1;
      ::draw2d::path_pointer                       m_pathFocusRect2;
      ::draw2d::path_pointer                       m_pathFocusRect3;
      ::draw2d::path_pointer                       m_pathFocusRect4;


      /// The menu_item this user_interaction (window)
      /// represents (this window is a button [a menu button],
      /// this window is a checkbox [a menu checkbox],
      /// this window is a player/view [a menu picture/video/chat?!])
      __pointer(object)                            m_pmenuitem;
      __pointer_array(interaction)                 m_menua;
      bool                                         m_bWfiUpDownTarget;




      interaction();
      virtual ~interaction();



      void user_interaction_common_construct();

      virtual void on_create_user_interaction();

      //class control_descriptor& descriptor();
      //const class control_descriptor& descriptor() const;

      virtual bool _001CanEnterScreenSaver();

      virtual bool _001Maximize();

      virtual bool _001Restore();

      virtual bool _001Minimize();

      virtual ::windowing::window * window() const;

      virtual ::windowing::windowing * windowing() const;

      ::user::interaction * get_host_window() const override;

      ::user::item * get_user_item(const ::user::item& item);

      virtual ::user::enum_state get_user_state() const;

      virtual bool has_hover() const;

      virtual bool has_link() const;


      inline iterator proper_children() { return {this, e_next_proper, this}; }


      const class ::user::interaction_layout& layout() const { return m_layout; }
      class ::user::interaction_layout& layout() { return m_layout; }


      //void clear();
      void control_descriptor_common_construct();
      //bool operator == (const control_descriptor & control_descriptor) const;
      //control_descriptor & operator = (const control_descriptor & control_descriptor);
      virtual enum_control_type get_control_type() const override;
      void set_control_type(enum_control_type e_control);
      void add_function(enum_control_function enum_control_function);
      void remove_function(enum_control_function enum_control_function);
      bool has_function(enum_control_function enum_control_function);
      enum_control_data_type get_data_type();
      void set_data_type(enum_control_data_type enum_control_data_type);
      void set_ddx_dbflags(::database::key datakey, iptr value);

      //index find_control(::user::interaction * pinteraction);

      __pointer(interaction) alloc();


      template < typename PRED >
      void queue_graphics_call(PRED pred)
      {

         synchronization_lock synchronizationlock(mutex());

         __defer_construct_new(m_pgraphicscalla);

         m_pgraphicscalla->add(__new(graphics_call< PRED >(pred)));

      }

      void process_graphics_call_queue(::draw2d::graphics_pointer & pgraphics);

      //void process_call(::draw2d::graphics_pointer & pgraphics, const call & call);



      //virtual void task_on_term(::task* pthread) override;


      //virtual ::e_status main_async(const ::routine & routine, e_priority epriority = priority_normal);


      virtual ::e_status main_sync(const ::routine & routine, const ::duration & duration = one_minute(), e_priority epriority = priority_normal);

      virtual ::e_status main_async(const ::routine & routine, e_priority epriority = priority_normal) override;


      inline void auto_prodevian_on_show() { m_ewindowflag |= e_window_flag_auto_prodevian_on_show; }
      inline void clear_auto_prodevian_on_show() { m_ewindowflag -= e_window_flag_auto_prodevian_on_show; }
      inline bool is_auto_prodevian_on_show() { return m_ewindowflag & e_window_flag_auto_prodevian_on_show; }

      inline void visual_changed() { m_ewindowflag |= e_window_flag_visual_changed; }
      inline void clear_visual_changed() { m_ewindowflag -= e_window_flag_visual_changed; }
      inline bool is_visual_changed()const { return m_ewindowflag & e_window_flag_visual_changed; }


      bool is_ok()
      {

         return ::is_set(this)
            && m_pimpl.is_set()
            && (m_ewindowflag & e_window_flag_is_window)
            && !m_pimpl->m_bDestroying;

      }

      virtual string get_class_style(string strClass);
      virtual bool set_class_style(string strClass, string strStyle);
      virtual void sync_style();
      virtual string get_full_style();
      virtual void load_style(string strStyle);


      virtual::e_display window_stored_display() const;
      virtual::e_display window_previous_display() const;


      virtual int get_derived_height(int iWidth);
      virtual int get_derived_width(int iHeight);


      virtual bool is_full_screen_enabled() const;

      virtual bool get_element_rect(RECTANGLE_I32* prectangle, enum_element eelement);


      virtual status < rectangle_i32 > rectangle(enum_element eelement)
      {

          ::rectangle_i32 rectangle;

          if (!get_element_rect(rectangle, eelement))
          {

              return ::error_failed;

          }

          return rectangle;

      }


      virtual enum_element get_default_element() const;
      virtual ::write_text::font_pointer get_font(style * pstyle, enum_element eelement, ::user::enum_state estate = e_state_none) const;
      inline ::write_text::font_pointer get_font(style* pstyle, ::user::enum_state estate = e_state_none) const { return get_font(pstyle, get_default_element(), estate); }
      virtual enum_translucency get_translucency(style* pstyle) const;
      virtual int get_int(style* pstyle, enum_int eint, ::user::enum_state estate = e_state_none, int iDefault = 0) const;
      virtual double get_double(style* pstyle, enum_double edouble, ::user::enum_state estate = e_state_none, double dDefault = 0.) const;
      virtual status < ::rectangle_f64 > get_border(style* pstyle, enum_element eelement, ::user::enum_state estate = e_state_none) const;
      inline status < ::rectangle_f64 > get_border(style* pstyle, ::user::enum_state estate = e_state_none) const { return get_border(pstyle, get_default_element(), estate); }
      virtual status < ::rectangle_f64 > get_padding(style* pstyle, enum_element eelement, ::user::enum_state elayout = e_state_none) const;
      inline status < ::rectangle_f64 > get_padding(style* pstyle, ::user::enum_state estate = e_state_none) const { return get_padding(pstyle, get_default_element(), estate); }
      virtual status < ::rectangle_f64 > get_margin(style* pstyle, enum_element eelement, ::user::enum_state estate = e_state_none) const;
      inline status < ::rectangle_f64 > get_margin(style* pstyle, ::user::enum_state estate = e_state_none) const { return get_margin(pstyle, get_default_element(), estate); }
      virtual status < ::color::color > get_color(style* pstyle, enum_element eelement, ::user::enum_state elayout = e_state_none) const;
      inline status < ::color::color > get_color(style* pstyle, ::user::enum_state estate = e_state_none) const { return get_color(pstyle, get_default_element(), estate); }

      virtual eflag get_draw_flags(style* pstyle) const;

      virtual ::user::enum_state get_state() const;

      virtual ::user::style* get_style() const;

      inline ::user::style* get_style(::draw2d::graphics_pointer& pgraphics) const
      {

         return pgraphics ? get_style(pgraphics->m_puserstyle) : get_style();

      }


      inline ::user::style * get_style(::user::style * pstyle) const
      {

         return pstyle ? pstyle : pstyle = get_style();

      }

      virtual void on_tsf_activate(bool bActivate);

      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::id & id);


//      virtual bool add_control(arguments arguments);


      inline bool is_graphical() const { return !m_bMessageWindow && m_ewindowflag & e_window_flag_graphical; }


      virtual ::synchronization_object * mutex_draw();


      //virtual bool AddControlBar(::user::control_bar* pcontrolbar);
      //virtual bool RemoveControlBar(::user::control_bar* pcontrolbar);

      // updown
      virtual bool wfi_is_up();
      virtual bool wfi_is_down();
      virtual bool wfi_is_up_down();
      // end updown


      virtual bool child_set_unique_id(::user::interaction* pinteraction);

      virtual string default_id_prefix() const;

      interaction * get_tooltip();

      virtual ::e_status set_tool_window(bool bSet = true) override;

      virtual double get_rotate();
      virtual ::user::form * get_form();
      virtual ::user::form * get_parent_form();

      virtual ::user::interaction * get_user_interaction();

      virtual matter* get_taskpool_container() override;

      //task_pointer defer_fork(const ::id& id, const matter_pointer& pmatter);

      virtual void set_place_child_title(const char* pszTitle);

      virtual ::user::primitive * get_bind_ui();

      virtual string get_display_tag();

      virtual void on_finalize() override;
      virtual void delete_this() override;


      virtual void display_system_minimize();


      //virtual bool window_move(i32 x, i32 y) override;


      auto prodevian() { return __new(::prodevian(this)); }

      virtual bool should_save_window_rect();
      virtual bool WindowDataSaveWindowRect();
      virtual bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false);


      virtual void on_defer_display();

      virtual bool defer_design_display();
      virtual bool design_display();
      virtual bool design_appearance();
      virtual bool design_zorder();
      virtual bool design_reposition();
      virtual bool design_layout(::draw2d::graphics_pointer & pgraphics);




      virtual void prodevian_stop() override;

      virtual void prodevian_redraw(bool bUpdateBuffer) override;

      virtual void _001OnAfterAppearance();


      virtual void defer_restore(const ::rectangle_i32& rectRequest);
      ::object * parent_property_set_holder() const override;

      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);
      virtual void set_need_layout(bool bAscendants = true);
      //void set_need_layout() { m_bNeedLayout = true; }
      virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void set_need_load_form_data() override;
      virtual void set_need_save_form_data() override;
      //virtual bool commit_sketch();
      virtual void post_redraw(bool bAscendants = true) override;
      virtual void show_window();





      virtual void start_layout();
      virtual void set_layout_ready();


      virtual bool is_layout_modified() const;
      virtual bool is_layout_ready() const;


      virtual bool display(::e_display edisplay = e_display_default, ::e_activation eactivation = ::e_activation_default) override;

      virtual ::zorder zorder(enum_layout elayout = e_layout_design) const;
      virtual void order(::zorder zorder);

      inline void order_top() { order(e_zorder_top); }
      inline void order_front() { order(e_zorder_top); }
      inline void order_top_most() { order(e_zorder_top_most); }
      inline void order_bottom() { order(e_zorder_bottom); }


      virtual void sketch_to_design(::draw2d::graphics_pointer & pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void _001UpdateWindow() override;
      //virtual void window_apply_visual(const class window_state& windowstate) override;


      virtual void sketch_prepare_window_minimize(::e_activation eactivation) override;
      virtual void sketch_prepare_window_maximize() override;
      virtual void sketch_prepare_window_full_screen(const ::rectangle_i32& rectHint = nullptr) override;
      virtual void sketch_prepare_window_restore(edisplay edisplay) override;
      virtual void sketch_prepare_window_dock(edisplay edisplay) override;


      inline void get_client_rect(RECTANGLE_I32 * lprect, enum_layout elayout = e_layout_design) const { layout().state(elayout).client_rect(lprect); }
      inline ::rectangle_i32 get_client_rect(enum_layout elayout = e_layout_design) const { return layout().state(elayout).client_rect(); }


      virtual void get_window_rect(RECTANGLE_I32 * lprect, enum_layout elayout = e_layout_design) const { *lprect = get_window_rect(elayout); }
      virtual ::rectangle_i32 get_window_rect(enum_layout elayout = e_layout_design) const;


      inline bool set_prodevian() { return add_prodevian(this); }
      inline bool clear_prodevian() { return remove_prodevian(this); }

      virtual bool add_prodevian(::context_object* pobject) override;
      virtual bool remove_prodevian(::context_object* pobject) override;
      inline bool has_prodevian() const noexcept;


      virtual bool is_frame_window();
      virtual bool is_this_visible(enum_layout elayout = e_layout_design) override;

      virtual bool sketch_on_display();


      inline bool is_this_visible(enum_layout elayout = e_layout_design) const;
      inline bool is_this_screen_visible(enum_layout elayout = e_layout_design) const;

      inline bool is_window_visible(enum_layout elayout = e_layout_design) const;
      inline bool is_window_screen_visible(enum_layout elayout = e_layout_design) const;


      virtual bool create_message_queue(const char* lpszName) override;


      virtual bool has_text_input();

      virtual bool kick_queue();

      virtual bool contains_user_interaction(::user::interaction* pinteraction, bool bRecursive = true) const;


      virtual void on_select() override;

      virtual bool is_place_holder() override;

      
      virtual enum_cursor get_cursor() override;


      virtual ::e_status set_cursor(enum_cursor ecursor) override;


      virtual ::e_status set_cursor(::windowing::cursor * pcursor);


      //virtual ::point_i32 get_cursor_position() const override;


      virtual bool is_left_button_pressed() const;


      virtual void set_current_item(const ::user::item & item, const ::action_context & action_context);
      virtual ::user::item current_item();


      virtual ::user::item hover_item();


      virtual bool _is_window() const override;
      inline bool is_window() const { return m_ewindowflag & e_window_flag_is_window; }

      virtual void ExitHelpMode();

      //virtual ::i32 get_window_long(i32 nIndex) const override;
      //virtual ::i32 set_window_long(i32 nIndex, ::i32 lValue) override;

      //virtual iptr get_window_long_ptr(i32 nIndex) const override;
      //virtual ::e_status set_window_long_ptr(i32 nIndex, iptr lValue) override;

      virtual bool on_before_set_parent(::user::primitive * pinterface);
      virtual bool on_set_parent(::user::primitive * pinterface);
      virtual void on_after_set_parent();


      virtual bool on_set_owner(::user::primitive * pinterface);





      virtual ::user::primitive * first_child_user_primitive() override;
      virtual ::user::primitive * top_user_primitive() override;
      virtual ::user::primitive * under_user_primitive() override;
      virtual ::user::primitive * above_user_primitive() override;
      virtual ::user::primitive * next_user_primitive() override;
      virtual ::user::primitive * previous_user_primitive() override;



      virtual ::user::interaction* first_child() override;
      virtual ::user::interaction* last_child() override;
      virtual ::user::interaction* last_sibling() override;
      virtual ::user::interaction* next_sibling() override;
      virtual ::user::interaction* previous_sibling() override;
      virtual ::user::interaction* first_sibling() override;
      virtual ::user::interaction* next_sibling(::user::interaction* pinteraction) override;
      virtual ::user::interaction* previous_sibling(::user::interaction* pinteraction) override;


      virtual void mouse_hover_add(::user::interaction* pinterface) override;
      virtual bool mouse_hover_remove(::user::interaction* pinterface) override;

      virtual i32 get_wheel_scroll_delta();

      template < typename TYPE >
      TYPE* typed_descedant(::user::interaction* puiExclude = nullptr)
      {

         auto puiptraChild = m_puiptraChild;

         if (!puiptraChild)
         {

            return nullptr;

         }

         for (auto& pinteraction : puiptraChild->interactiona())
         {

            if (pinteraction != puiExclude)
            {

               TYPE* point = dynamic_cast <TYPE*> (pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }


         }

         //auto puiptraChild = m_puiptraChild;

         for (auto& pinteraction :puiptraChild->interactiona())
         {

            if (pinteraction != puiExclude)
            {

               TYPE* point = pinteraction->typed_descedant < TYPE >(pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }


         }

         return nullptr;

      }


      template < typename TYPE >
      __pointer(TYPE)& _001TypedWindow(__pointer(TYPE)& sp)
      {

         return sp = _001TypedWindow<TYPE>();

      }


      template < typename TYPE >
      TYPE* _001TypedWindow() // search descedants first, then ascendants descedants.
      {

         ::user::interaction* pinteraction = this;

         ::user::interaction* puiExclude = nullptr;

         while (pinteraction != nullptr)
         {

            TYPE* point = pinteraction->typed_descedant < TYPE >(puiExclude);

            if (point != nullptr)
            {

               return point;

            }

            puiExclude = pinteraction;

            pinteraction = pinteraction->get_parent();

            if (pinteraction == nullptr)
            {

               return nullptr;

            }

            point = dynamic_cast <TYPE*> (pinteraction);

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


      virtual void update_dialog_controls(channel* ptarget) override;
      virtual void CenterWindow(::user::interaction* pAlternateOwner = nullptr) override;
      virtual void _001Emphasize(int cx, int cy);
      virtual id   run_modal_loop(::user::interaction* pinteraction, u32 dwFlags = 0) override;
      virtual id   RunModalLoop(u32 dwFlags = 0) override;
      virtual id   _001RunModalLoop(u32 dwFlags = 0) override;
      virtual bool ContinueModal() override;
      virtual void EndModalLoop(id nResult) override;


      virtual void route_control_event(::user::control_event* pevent) override;

      virtual void on_control_event(::message::message* pmessage);

      virtual void on_notify_control_event(control_event* pevent);

      virtual void on_control_event(::user::control_event* pevent) override;


      virtual bool update_data(bool bSaveAndValidate = true) override;


      virtual ::user::interaction* get_os_focus_uie();


      virtual void on_set_keyboard_focus() override;
      virtual void on_kill_keyboard_focus() override;


      virtual ::user::primitive * get_keyboard_focus() override;


      virtual primitive * keyboard_set_focus_next(bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      //virtual primitive * keyboard_set_focus_next(primitive * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      

      virtual void get_child_rect(RECTANGLE_I32* prectangle);

      inline auto get_child_rect() { ::rectangle_i32 rectangle(e_no_initialize); get_child_rect(&rectangle); return rectangle; }

      virtual bool scroll_bar_get_client_rect(RECTANGLE_I32* prectangle);

      virtual void on_visual_applied();

      virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics) override;
      virtual ::size_f64 _001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_reposition() override;
      virtual void on_show_window() override;
      virtual void _on_show_window();

      virtual void window_show_change_visibility();

      virtual void defer_save_window_placement();

//#ifdef WINDOWS_DESKTOP
//
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);
//
//#endif


      virtual bool pre_create_window(::user::system * pusersystem) override;


      virtual bool subclass_window(oswindow posdata) override;
      virtual oswindow unsubclass_window() override;


      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_interaction(class ::user::control_descriptor * pdescriptor);

      virtual ::e_status create_host() override;
      virtual ::e_status create_child(::user::interaction * pparent) override;

      // virtual bool create_interaction(const char * pszClassName, const char * pszWindowName, u32 uStyle, ::user::interaction * puiParent, ::create * pcreate = nullptr) override;

      //virtual bool create_window_ex(__pointer(::user::system) pcs, ::user::interaction* puiParent = nullptr, const ::id& id = ::id()) override;
      //enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      //virtual void CalcWindowRect(RECTANGLE_I32* pClientRect, ::u32 nAdjustType = adjustBorder) override;


      virtual bool IsTopParentActive() override;
      virtual void ActivateTopParent() override;



      virtual bool DestroyWindow() override;

      virtual void destroy_window() override;

      virtual void on_finish() override;

      virtual ::e_status set_finish_composites(::context_object * pcontextobjectFinish) override;

      virtual ::e_status finish(::context_object * pcontextobjectFinish = nullptr) override;

      virtual void notify_on_finish(::context_object * pcontextobjectFinish) override;

      virtual void finalize() override;


//#ifdef WINDOWS
//
//      virtual bool RedrawWindow(const ::rectangle_i32& rectUpdate = nullptr,
//         ::draw2d::region* prgnUpdate = nullptr,
//         ::u32 flags = RDW_INVALIDATE | RDW_ERASE) override;
//
//#else

      virtual bool RedrawWindow(const ::rectangle_i32& rectUpdate = nullptr,
         ::draw2d::region* prgnUpdate = nullptr,
         ::u32 flags = 0) override;

//#endif


      virtual void register_drop_target();




      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = true) override;
      virtual bool GetUpdateRect(RECTANGLE_I32* prectangle, bool bErase = false) override;

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false) override;
      virtual void Invalidate(bool bErase = true) override;
      virtual void InvalidateRect(const ::rectangle_i32& rectangle, bool bErase = true) override;

      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true) override;
      virtual void ValidateRect(const ::rectangle_i32& rectangle) override;

      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      virtual void ShowOwnedPopups(bool bShow = true) override;


      //virtual u32 GetStyle() const override;
      //virtual u32 GetExStyle() const override;
      //virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0) override;
      //virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0) override;

      using ::user::primitive::send;
      virtual lresult send(::message::message* pmessage) override;
      virtual bool post(::message::message* pmessage) override;
      virtual lresult send_message(const ::id & id, wparam wparam = 0, lparam lparam = 0) override;

      virtual lresult message_call(const ::id & id, wparam wparam = 0, lparam lparam = 0) override;
      virtual lresult message_call(::message::message * pmessage) override;


#ifdef LINUX

      virtual lresult send_x11_event(void* pevent) override; // XEvent *

#endif

      virtual bool post_message(const ::id & id, wparam wParam = 0, lparam lParam = 0) override;

      virtual bool post_object(const ::id & id, wparam wParam, lparam lParam);


      //virtual void SetWindowDisplayChanged() override;


      virtual bool call_and_set_timer(uptr uEvent, ::millis millisElapse, PFN_TIMER pfnTimer = nullptr);
      virtual bool set_timer(uptr uEvent, ::millis millisElapse, PFN_TIMER pfnTimer = nullptr);
      virtual bool SetTimer(uptr uEvent, ::millis millisElapse, PFN_TIMER pfnTimer = nullptr) override;
      virtual bool KillTimer(uptr uEvent) override;

//      virtual bool enable_window(bool bEnable = true) override;

      //virtual void process_queue(::draw2d::graphics_pointer & pgraphics);

      virtual void _001PrintBuffer(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001Print(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _008CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool is_custom_draw();

      virtual id GetDlgCtrlId() const override;
      virtual id SetDlgCtrlId(::id id) override;

//#ifdef WINDOWS_DESKTOP
//
//      virtual bool open_clipboard() override;
//      virtual bool close_clipboard() override;
//
//#endif

      virtual bool is_active_window() const;

      virtual bool has_mouse_capture() const;
      virtual bool set_mouse_capture();

      virtual bool has_keyboard_focus() const;
      virtual ::e_status set_keyboard_focus();

      virtual ::e_status set_foreground_window();
      virtual ::e_status set_active_window();

      virtual bool is_window_enabled() const;
      inline bool is_this_window_enabled() const { return m_ewindowflag.is(e_window_flag_enable); }
      virtual bool enable_window(bool bEnable = true);

      virtual void on_calc_size(calc_size* pcalcsize);

      virtual void walk_pre_translate_tree(::message::message* pmessage, ::user::interaction* puiStop = nullptr);


      virtual bool edit_undo();

      virtual void edit_on_text(string str) override;
      virtual void edit_on_sel(strsize iBeg, strsize iEnd) override;

      virtual void get_text_composition_area(::rectangle_i32 & r);
      virtual void on_text_composition(string str) override;
      virtual void on_text_composition_done() override;

      //virtual bool is_text_composition_active() override;

      virtual int on_text_composition_message(int iMessage);

      virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context);

      virtual void set_window_text(const char* pszString) override;

#ifdef WINDOWS
      strsize _009GetWindowText(wchar_t * pwsz, int n) override;
#else
      strsize _009GetWindowText(char * psz, int n) override;
#endif
      virtual strsize _009GetWindowTextLength() override;

      virtual strsize get_window_text(char* pszStringBuf, strsize nMaxCount) override;

      virtual string get_window_text() override;
      virtual void get_window_text(string& rectString) override;
      virtual strsize get_window_text_length() override;


      virtual void install_message_routing(::channel* pchannel) override;


      virtual void _000OnMouseLeave(::message::message* pmessage) override;

      //virtual void _000OnMouse(::message::mouse* pmouse);
      //virtual void _000OnThisMouse(::message::mouse* pmouse);
      //virtual void _000OnChildrenMouse(::message::mouse* pmouse);
      virtual void _000OnKey(::message::key* pkey);
      virtual void _000OnDrag(::message::drag_and_drop* pdrag);

      virtual void prio_install_message_routing(::channel *pchannel);


      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseEnter);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);


      virtual void _001OnTimer(::timer* ptimer) override;
      virtual bool on_timer(::timer* ptimer) override;
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPostUser);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnClose);
      //DECL_GEN_SIGNAL(_001OnCommand);
      DECL_GEN_SIGNAL(_001OnSimpleCommand);
      DECL_GEN_SIGNAL(_001OnNeedLoadFormData);
      DECL_GEN_SIGNAL(_001OnNeedSaveFormData);
      DECL_GEN_SIGNAL(_001OnDisplayChange);


      virtual DECL_GEN_SIGNAL(_002OnLButtonDown);
      virtual DECL_GEN_SIGNAL(_002OnLButtonUp);
      virtual DECL_GEN_SIGNAL(_002OnMouseMove);
      virtual DECL_GEN_SIGNAL(_002OnMouseEnter);
      virtual DECL_GEN_SIGNAL(_002OnMouseLeave);
      virtual DECL_GEN_SIGNAL(_002OnKeyDown);
      virtual DECL_GEN_SIGNAL(_002OnKeyUp);
      virtual DECL_GEN_SIGNAL(_002OnTimer);

      DECL_GEN_SIGNAL(_001OnTextComposition);


      virtual bool _001IsPointInside(const ::point_i32 & point) override;

      inline bool _001IsPointInsideInline(const ::point_i32 & point) { return layout().sketch().screen_rect().contains(point); }
      inline bool _001IsClientPointInsideInline(const ::point_i32 & point) { return layout().sketch().client_rect().contains(point); }
      inline bool _001IsParentClientPointInsideInline(const ::point_i32 & point) { return layout().sketch().parent_client_rect().contains(point); }

      virtual ::user::interaction* _001FromPoint(::point_i32 point, bool bTestedIfParentVisible = false) override;

      virtual void OnLinkClick(const char* psz, const char* pszTarget = nullptr) override;

      virtual void pre_translate_message(::message::message* pmessage) override;


      ::user::interaction * get_child_by_name(const char* lpszName, i32 iLevel = -1);
      ::user::interaction * get_child_by_id(id id, i32 iLevel = -1);
      ::user::interaction * child_from_point(const ::point_i32 & point);


      virtual bool is_ascendant(const primitive * puiIsAscendant, bool bIncludeSelf) const override;
      virtual bool is_parent(const primitive * puiIsParent) const override;
      virtual bool is_child(const primitive * puiIsChild) const override;
      virtual bool is_descendant(const primitive * puiIsDescendant, bool bIncludeSelf) const override;

      virtual bool is_ascendant(const ::user::controller * pcontroller, bool bIncludeSelf) const;
      virtual bool contains(const primitive* puiIsChild) const;

      virtual bool recursively_contains(const primitive* puiIsChild, bool bIncludeSelf) const;

      virtual ::user::interaction* get_wnd() const override;
      virtual ::user::interaction* get_wnd(::u32 nCmd) const override;

      virtual ::user::primitive * set_parent(::user::primitive * pinteraction) override;
      virtual ::user::primitive * set_owner(::user::primitive * pinteraction) override;

      virtual void on_add_owned(::user::primitive * pprimitive) override;

      virtual ::user::interaction * get_parent_window() const override;

      virtual ::user::interaction * get_first_child_window() const override;


      virtual bool is_host_window() const;
      virtual bool is_host_top_level() const;
      virtual bool is_os_host() const;


      virtual ::user::interaction* get_parent() const override;
      virtual ::user::interaction* get_top_level() const override;
      virtual ::user::interaction* get_owner() const override;
      virtual ::user::interaction* get_parent_owner() const override;
      virtual ::user::interaction* get_parent_or_owner() const override;
      virtual ::user::interaction* get_top_level_owner() const override;
      

      virtual ::user::frame* get_parent_frame() const override;
      virtual ::user::frame* get_owner_frame() const override;


      //void clear_cache(bool bRecursive = true) const;


      virtual ::user::frame * frame() const override;
      virtual ::user::frame * top_level_frame() const override;


      virtual void send_message_to_descendants(const ::id & id, wparam wParam = 0, lparam lParam = 0, bool bDeep = true, bool bOnlyPerm = false) override;

      virtual void route_message_to_descendants(::message::message* pmessage) override;


      virtual i32 get_descendant_level(const ::user::primitive * pinteraction) const override;


      //virtual bool is_descendant(const ::user::primitive * pinteraction, bool bIncludeSelf = false) const override;

      virtual oswindow GetParentHandle() const;

      virtual ::user::interaction* get_focusable_descendant() const override;

      virtual void RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::id idLeftOver, ::u32 nFlag = reposDefault, RECTANGLE_I32* prectParam = nullptr, const ::rectangle_i32& rectClient = nullptr, bool bStretch = true) override;

      virtual ::user::interaction* ChildWindowFromPoint(const ::point_i32& point) override;
      virtual ::user::interaction* ChildWindowFromPoint(const ::point_i32& point, ::u32 nFlags) override;

      virtual ::user::interaction* get_next_sibling_window() override;

      virtual ::user::interaction * get_next_window(bool bIgnoreChildren = false, const ::user::interaction * puiInteractionStop = nullptr) const override;
      virtual ::user::interaction * get_window(enum_next enext) const override;

      virtual ::user::interaction* GetLastActivePopup() override;

      virtual bool is_message_only_window() const override;

      virtual void pre_subclass_window() override;

      virtual void PostNcDestroy() override;


      virtual void default_message_handler(::message::message * pmessage) override;


      virtual void message_handler(::message::message* pmessage) override;
      //virtual lresult message_handler(MESSAGE * pmessage) override;

      virtual void GuieProc(::message::message* pmessage) override;

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;


      inline oswindow get_oswindow() const { return m_oswindow; }
      //virtual bool attach(::windowing::window * pwindow_New) override;
      virtual oswindow detach() override;


      virtual windowing::window * get_window() const override;


      virtual void* get_os_data() const;


      virtual bool can_merge(::user::interaction* pinteraction) override;
      virtual bool merge(::user::interaction* pinteraction) override;


      virtual void _001OnTriggerMouseInside() override;


      virtual bool window_is_notify_icon_enabled();
      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      virtual ::e_status set_icon(::windowing::icon * picon) override;

      virtual void viewport_screen_to_client(POINT_I32* ppt) override;
      virtual void viewport_client_to_screen(POINT_I32* ppt) override;
      virtual void viewport_client_to_screen(RECTANGLE_I32* ppt) override;
      virtual void viewport_screen_to_client(RECTANGLE_I32* ppt) override;


      virtual string get_window_default_matter() override;
      virtual string get_window_icon_matter() override;
      virtual u32 get_window_default_style() override;
      virtual enum_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command* psimplecommand) override;
      virtual void on_command(::message::command* pcommand) override;


      virtual bool OnCommand(::message::message* pmessage) override;
      virtual bool OnNotify(::message::message* pmessage) override;
      virtual bool OnChildNotify(::message::message* pmessage) override;


      virtual bool is_selected(::data::item* pitem) override;

      //virtual __pointer(place_holder) place_hold(::user::interaction* pinteraction) override;

#if defined(_UWP) && defined(__cplusplus_winrt)
      static Agile<Windows::UI::Core::CoreWindow>(*s_get_os_window)(interaction* pinteraction);
      Agile<Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static Agile<Windows::UI::Core::CoreWindow> get_os_window(interaction* pinteraction)
      {
         return (*s_get_os_window)(pinteraction);
      }
      static Agile<Windows::UI::Core::CoreWindow> get_os_window_default(interaction* pinteraction)
      {
         UNREFERENCED_PARAMETER(pinteraction);
         return nullptr;
      }
#endif
      virtual bool has_command_handler(::message::command* pcommand) override;



      //virtual bool track_popup_menu(::user::menu_item* pitem, i32 iFlags, const ::point_i32& point) override;
      //virtual __pointer(::user::menu) track_popup_xml_menu(const ::payload & varXml, i32 iFlags, const ::point_i32& pointScreen = nullptr, const ::size_i32& sizeMinimum = nullptr) override;


      virtual void _001OnExitIconic() override;
      virtual void _001OnExitFullScreen() override;


      virtual bool _001OnBeforeAppearance();
      virtual bool _001OnExitAppearance();


      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience) override;


      virtual void on_configuration_change(::user::primitive * pprimitiveSource) override;


      virtual void show_keyboard(bool bShow = true) override;


      virtual void keep_alive(::object* pliveobject = nullptr) override;

      virtual void move_to(const ::point_i32& point);
      virtual void set_size(const ::size_i32& size);
      virtual void move_to(i32 x, i32 y);
      virtual void set_size(i32 cx, i32 cy);
      virtual void set_dim(const ::point_i32& point, const ::size_i32& size);
      virtual void place(const ::rectangle_i32& rectangle);
      virtual void set_dim(i32 x, i32 y, i32 cx, i32 cy);
      virtual interaction& operator =(const ::rectangle_i32& rectangle);


      virtual void activation(::e_activation eactivation);


      virtual void display_child(const ::rectangle_i32 & rectangle);


      virtual ::user::interaction* best_top_level_parent(RECTANGLE_I32* prectangle);

      //virtual void get_window_rect(RECTANGLE_I32 * prectangle) const override;

      virtual index get_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, edisplay edisplay);

      virtual edisplay initial_restore_display();



      virtual index calculate_broad_and_compact_restore(RECTANGLE_I32* prectWorkspace = nullptr, SIZE_I32* psizeMin = nullptr, const ::rectangle_i32& rectHint = nullptr);

       //virtual void reset_window_state();

      virtual index make_zoneing(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, bool bSet = false, ::e_display* pedisplay = nullptr, ::e_activation eactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index best_zoneing(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, bool bSet = false, ::e_display* pedisplay = nullptr, ::e_activation eactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index best_monitor(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index best_workspace(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index good_restore(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top, edisplay edisplay = e_display_restore);
      virtual index good_iconify(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);

      virtual index good_move(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle = nullptr, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index get_best_zoneing(edisplay& edisplay, ::rectangle_i32* prectangle, const ::rectangle_i32& rectRequest = ::rectangle_i32(), bool bPreserveSize = false);
      virtual index get_best_workspace(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation = e_activation_default);

      virtual bool get_rect_normal(RECTANGLE_I32* prectangle);


      virtual scroll_bar* get_horizontal_scroll_bar();
      virtual scroll_bar* get_vertical_scroll_bar();

      virtual scroll_data* get_horizontal_scroll_data();
      virtual scroll_data* get_vertical_scroll_data();


      virtual void set_viewport_offset_x(::draw2d::graphics_pointer & pgraphics, int x);
      virtual void set_viewport_offset_y(::draw2d::graphics_pointer & pgraphics, int y);
      virtual void set_viewport_offset(::draw2d::graphics_pointer & pgraphics, int x, int y);
      virtual void offset_viewport_offset_x(::draw2d::graphics_pointer & pgraphics, int x);
      virtual void offset_viewport_offset_y(::draw2d::graphics_pointer & pgraphics, int y);
      virtual void offset_viewport_offset(::draw2d::graphics_pointer & pgraphics, int x, int y);
      virtual bool validate_viewport_offset(point_i32& point);
      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics);
      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics);
      virtual ::point_i32 get_viewport_offset();
      virtual ::size_f64 get_total_size();
      virtual void on_change_view_size(::draw2d::graphics_pointer & pgraphics);
      virtual ::size_f64 get_page_size();
      virtual ::e_status set_total_size(const ::size_f64& size);
      virtual ::e_status set_page_size(const ::size_f64& size);
      virtual ::point_i32 get_parent_accumulated_scroll(enum_layout elayout = e_layout_design) const;
      virtual ::point_i32 get_parent_viewport_offset() const;
      virtual ::point_i32 get_ascendant_viewport_offset() const;
      virtual void get_margin_rect(RECTANGLE_I32* prectMargin);

      virtual int get_final_x_scroll_bar_width();
      virtual int get_final_y_scroll_bar_width();


      virtual bool is_system_message_window();


      virtual ::graphics::graphics * get_window_graphics() override;

      virtual bool is_composite() override;

      virtual ::size_i32 get_window_minimum_size();


      virtual void UpDownTargetAttach(::user::interaction* pupdown);
      virtual void UpDownTargetDetach(::user::interaction* pupdown);

      virtual bool OnUpDownTargetAttach(::user::interaction* pupdown);
      virtual bool OnUpDownTargetDetach(::user::interaction* pupdown);


      virtual string calc_window_class();


      virtual void user_interaction_on_destroy();
      virtual void user_interaction_on_hide();


      virtual bool hide() override;






      virtual void on_remove_child(::user::interaction* pinteraction);
      virtual void on_remove_place_holder_child(::user::interaction* pinteraction);
      virtual void on_hide_child(::user::interaction* pinteraction);
      virtual void on_hide_place_holder_child(::user::interaction* pinteraction);


      virtual void _001GetSel(strsize& iBeg, strsize& iEnd) const override;


      virtual void get_horizontal_scroll_info(scroll_info& info);
      virtual void get_vertical_scroll_info(scroll_info& info);
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics);


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;


      virtual void keyboard_focus_OnKeyDown(::message::message* pmessage) override;
      //virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      //virtual bool keyboard_focus_OnChildKillFocus() override;

      virtual bool get_child(__pointer(::user::interaction)& pinteraction);
      virtual bool rget_child(__pointer(::user::interaction)& pinteraction);


      template < typename CHILD >
      inline bool get_typed_child(CHILD*& pchild);

      template < typename CHILD >
      inline __pointer(CHILD) get_typed_child();

      virtual enum_input_type preferred_input_type() const;

      //virtual ::user::primitive * get_keyboard_focus();
      //virtual ::e_status set_keyboard_focus(::user::primitive* pprimitive);
      //virtual ::e_status remove_keyboard_focus(::user::primitive * pprimitive);

      //virtual ::e_status set_keyboard_focus() override;
      //virtual ::e_status remove_keyboard_focus() override;
      //virtual ::e_status clear_keyboard_focus() override;


      virtual bool is_descendant_of(const ::user::primitive * puiAscendantCandidate, bool bIncludeSelf) const override;
      virtual bool is_ascendant_of(const ::user::primitive * puiDescendantCandidate, bool bIncludeSelf) const override;

      virtual bool is_descendant_of_or_owned_by(const ::user::primitive * puiAscendantCandidate, bool bIncludeSelf) const override;
      virtual bool is_ascendant_or_owner_of(const ::user::primitive * puiDescendantCandidate, bool bIncludeSelf) const override;

      virtual bool show_tooltip(const string& str, bool bError);

      virtual bool layout_tooltip(bool bForceShow = false);

      virtual bool hide_tooltip();

      virtual bool frame_is_transparent();

      virtual double get_alpha();

#ifdef WINDOWS_DESKTOP

      virtual void _task_transparent_mouse_event();

#endif

      virtual void destruct() override;



      //virtual void mouse_hover_step(::message::mouse * pmouse);
      //virtual void mouse_hover_step(point_i32 & pointLast);

      //virtual void mouse_hover_move(bool& bPointInside, point_i32& pointLast);

      virtual bool has_pending_graphical_update() override;

      virtual bool enable_transparent_mouse_events(bool bEnable = true);

      virtual void check_transparent_mouse_events();


      virtual void redraw_add(::context_object * pobject);

      virtual void redraw_remove(::context_object * pobject);

      virtual bool has_redraw();

      virtual void on_after_graphical_update() override;


      virtual void _001OnDeiconify(edisplay edisplay);




      virtual bool on_click(const ::user::item & item);
      virtual bool on_right_click(const ::user::item & item);


      virtual int width();
      virtual int height();

      virtual int client_width();
      virtual int client_height();

      virtual ::size_f64 get_size();
      virtual ::size_f64 get_client_size();

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics);

      virtual void wait_redraw();

      virtual bool has_pending_redraw_flags() override;


      virtual void set_bitmap_source(string strBitmapFileTitle) override;
      virtual void clear_bitmap_source() override;


      void install_simple_ui_default_mouse_handling(::channel* pchannel);
      void install_update_data_message_routing(::channel * pchannel);


      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnMButtonUp);


      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;
      virtual void edit_on_kill_focus(::user::interaction* pinteraction) override;


      virtual void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);


      virtual bool on_action(const char* pszId);

      virtual bool keyboard_focus_is_focusable() const override;

      virtual bool simple_on_control_event(::message::message* pmessage, ::user::enum_event eevent);

      using ::aura::drawable::hit_test;
      virtual void hit_test(::user::item& item, const ::point_i32 & point) override;

      using ::aura::drawable::on_hit_test;
      virtual void on_hit_test(::user::item & item) override;

      virtual bool update_hover(const ::point_i32 & point, bool bAvoidRedraw = true);
      virtual bool update_hover(::message::mouse * pmouse, bool bAvoidRedraw = true);

      virtual bool get_rect(::user::item& item);

      inline auto rectangle(const ::user::item& item) { get_rect((::user::item &) item); return item.m_rectangle; }

      virtual __pointer(::user::item) add_user_item(const ::user::item & item);

      virtual void _001DrawItems(::draw2d::graphics_pointer & pgraphics);


      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item * pitem);


      // control member function BEGIN
      //
      //
      //
      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::id & id) override;
      //virtual elayout get_state() const override;
      //bool _003IsCustomMessage();
      //::user::primitive* _003GetCustomMessageWnd();
      //virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;
      virtual void route_command_message(::message::command* pcommand) override;
      virtual bool has_function(enum_control_function econtrolfunction) const;
      //virtual enum_control_type get_control_type() const;
      //virtual void _003CallCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pitem);
      //virtual bool _003CallCustomWindowProc(__pointer(::user::interaction) pwnd, const ::id & id, wparam wparam, lparam lparam, lresult& lresult);
      //virtual void _003OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pitem);
      //virtual void _003CustomWindowProc(::message::message* pmessage);
      //virtual form_list * get_form_list();
      //virtual bool _001IsPointInside(::point_i32 point) override;
      //control null() { return control(); }
      //bool Validate(string& str);
      bool get_data(__pointer(::user::interaction) pwnd, ::payload& payload);
      //void SetEditItem(index iItem);
      //void SetEditSubItem(index iItem);
      //index GetEditSubItem();
      // index GetEditItem();
      //virtual ::user::interaction * ControlExGetWnd();
      //using ::user::box::get_client_rect;
      //virtual bool get_client_rect(RECTANGLE_I32 * prectangle) override;
      //using ::user::box::get_window_rect;
      //virtual bool get_window_rect(RECTANGLE_I32 * prectangle) override;
      //bool operator == (const class ::user::control_descriptor& descriptor) const;
      //bool operator == (const class control& control) const;
      virtual bool IsControlCommandEnabled();
      virtual void EnableControlCommand(bool bEnable);
      //virtual void BaseControlExOnMouseMove(::u32 nFlags, const ::point_i32 & point);
      //virtual void on_hit_test(::user::item & item) override;
      //DECL_GEN_SIGNAL(on_message_create);
      //DECL_GEN_SIGNAL(_001OnMouseMove);
      //DECL_GEN_SIGNAL(_001OnMouseLeave);
      //DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnEnable);
      //DECL_GEN_SIGNAL(_001OnSetFocus);
      //DECL_GEN_SIGNAL(_001OnKillFocus);
      //virtual void route_control_event(::user::control_event* pevent) override;
      //virtual void on_notify_control_event(control_event* pevent) override;
      //virtual void on_control_event(::user::control_event* pevent) override;
      //virtual bool simple_on_control_event(::message::message * pmessage, ::user::enum_event eevent) override;
      //virtual void walk_pre_translate_tree(::message::message * pmessage,__pointer(::user::interaction) puiStop);
      //virtual bool get_element_rect(RECTANGLE_I32* prectangle, enum_element eelement);
      virtual void get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa);
      // control member functions END



      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the style_base pure function overrides
      // that way, if some styled class overriding any style_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pstylebase compositor
      // to implement the utility functions
      // virtual bool _001GetMainFrameTranslucency(::user::enum_translucency & etranslucency);


      //using style::select_text_color;
      //virtual bool select_text_color(::draw2d::graphics_pointer & pgraphics, e_color ecolor = color_text);
      //using style::select_solid_brush;
      //virtual bool select_solid_brush(::draw2d::graphics_pointer & pgraphics, e_color ecolor);
      //using style::set;
      //virtual bool set(::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);


      //virtual bool select_text_color(e_color ecolor = color_text);
      //virtual bool select_solid_brush(e_color ecolor);
      //virtual bool set(e_font efont = font_default);


      virtual ::e_status show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd) override;
      virtual ::e_status hide_software_keyboard(::user::primitive * pprimitive) override;


      virtual void set_stock_icon(e_stock_icon eicon);
      virtual e_stock_icon get_stock_icon();


      virtual void post_routine(const ::routine & routine);
      virtual void prodevian_post_routine(const ::routine & routine);


      virtual void send_routine(const ::routine & routine, ::duration durationTimeout = ::duration::infinite());


   /*   template < typename PRED >
      void post_predicate(PRED pred)
      {

         post_method(__routine(pred));

      }*/


 /*     template < typename PRED >
      void prodevian_post_predicate(PRED pred)
      {

         prodevian_schedule(__routine(pred));

      }*/


      //template < typename PRED >
      //void pred(PRED pred)
      //{

      //   post_predicate(pred);

      //}


   /*   template < typename PRED >
      void send_predicate(PRED pred, ::duration durationTimeout = ::duration::infinite())
      {

         send_method(__routine(pred), durationTimeout);

      }*/

      bool _001InitialFramePosition();

      bool _001InitialFramePosition(RECTANGLE_I32 * lprect, const rectangle_f64 & rectOptionalRateOrSize = {0., 0., 0., 0.});

      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;



      template < typename SIZE_SHIFTABLE >
      inline auto screen_to_client(const SIZE_SHIFTABLE& o, enum_layout elayout = e_layout_design) { return o - ::size_i32(layout().screen_origin(elayout)) + ::size_i32(get_parent_accumulated_scroll(elayout)); }


      template < typename POINT_SHIFTABLE >
      inline auto client_to_screen(const POINT_SHIFTABLE& o, enum_layout elayout = e_layout_design) { return o + layout().screen_origin(elayout) - ::size_i32(get_parent_accumulated_scroll(elayout)); }


      template < typename SIZE_SHIFTABLE >
      inline auto parent_to_client(const SIZE_SHIFTABLE& o, enum_layout elayout = e_layout_design) { return o - ::size_i32(layout().origin(elayout)); }


      template < typename POINT_SHIFTABLE >
      inline auto client_to_parent(const POINT_SHIFTABLE& o, enum_layout elayout = e_layout_design) { return o + layout().origin(elayout); }


      template < typename POINT_OFFSETABLE >
      inline void _001ScreenToClient(POINT_OFFSETABLE& o, enum_layout elayout = e_layout_design) { o -= layout().screen_origin(elayout); o += get_parent_accumulated_scroll(elayout); }
      template < typename POINT_OFFSETABLE >
      inline void _001ScreenToClient(POINT_OFFSETABLE* po, enum_layout elayout = e_layout_design) { _001ScreenToClient(*po, elayout); }


      template < typename POINT_OFFSETABLE >
      inline void _001ClientToScreen(POINT_OFFSETABLE& o, enum_layout elayout = e_layout_design) { o += layout().screen_origin(elayout); o -= get_parent_accumulated_scroll(elayout); }
      template < typename POINT_OFFSETABLE >
      inline void _001ClientToScreen(POINT_OFFSETABLE* po, enum_layout elayout = e_layout_design) { _001ClientToScreen(*po, elayout); }


      template < typename POINT_OFFSETABLE >
      inline void _001HostToClient(POINT_OFFSETABLE& o, enum_layout elayout = e_layout_design) { o -= layout().host_origin(elayout); o += get_parent_accumulated_scroll(elayout); }
      template < typename POINT_OFFSETABLE >
      inline void _001HostToClient(POINT_OFFSETABLE* po, enum_layout elayout = e_layout_design) { _001HostToClient(*po, elayout); }


      template < typename POINT_OFFSETABLE >
      inline void _001ClientToHost(POINT_OFFSETABLE& o, enum_layout elayout = e_layout_design) { o += layout().host_origin(elayout); o -= get_parent_accumulated_scroll(elayout); }
      template < typename POINT_OFFSETABLE >
      inline void _001ClientToHost(POINT_OFFSETABLE* po, enum_layout elayout = e_layout_design) { _001ClientToHost(*po, elayout); }


      template < typename POINT_OFFSETABLE >
      inline void _001ParentToClient(POINT_OFFSETABLE& o, enum_layout elayout = e_layout_design) { o -= layout().origin(elayout); }
      template < typename POINT_OFFSETABLE >
      inline void _001ParentToClient(POINT_OFFSETABLE* po, enum_layout elayout = e_layout_design) { _001ParentToClient(*po, elayout); }


      template < typename POINT_OFFSETABLE >
      inline void _001ClientToParent(POINT_OFFSETABLE& o, enum_layout elayout = e_layout_design) { o += layout().origin(elayout); }
      template < typename POINT_OFFSETABLE >
      inline void _001ClientToParent(POINT_OFFSETABLE* po, enum_layout elayout = e_layout_design) { _001ClientToParent(*po, elayout); }

      inline void ScreenToClient(RECTANGLE_I32* prectangle, enum_layout elayout = e_layout_design) { ::rect_sub(prectangle, layout().screen_origin(elayout)); }
      inline void ScreenToClient(POINT_I32* ppoint, enum_layout elayout = e_layout_design) { ::point_sub(ppoint, layout().screen_origin(elayout)); }


      inline void ClientToScreen(RECTANGLE_I32* prectangle, enum_layout elayout = e_layout_design) { ::rect_add(prectangle, layout().screen_origin(elayout)); }
      inline void ClientToScreen(POINT_I32* ppoint, enum_layout elayout = e_layout_design) { ::point_add(ppoint, layout().screen_origin(elayout)); }


      inline void ParentToClient(RECTANGLE_I32* prectangle, enum_layout elayout = e_layout_design) { ::rect_sub(prectangle, layout().origin(elayout)); }
      inline void ParentToClient(POINT_I32* ppoint, enum_layout elayout = e_layout_design) { ::point_sub(ppoint, layout().origin(elayout)); }


      inline void ClientToParent(RECTANGLE_I32* prectangle, enum_layout elayout = e_layout_design) { ::rect_add(prectangle, layout().origin(elayout)); }
      inline void ClientToParent(POINT_I32* ppoint, enum_layout elayout = e_layout_design) { ::point_add(ppoint, layout().origin(elayout)); }


   };





   class control_cmd_ui : public ::message::command
   {
   public:


      id_to_id      m_mapControlCommand;


      control_cmd_ui();


      virtual void enable(bool bOn);
      virtual void SetCheck(i32 nCheck);
      virtual void SetText(const char* pszText);

      id GetControlCommand(id id);

   };


} // namespace user


// e_timer_ui works correctly when timer is originated from SetTimer call
//inline ::user::interaction * e_timer_ui(::timer * ptimer)
//{
//
//   return (::user::interaction *) ptimer->m_pvoidData;
//
//}



//CLASS_DECL_AURA::user::interaction* oswindow_interaction(::windowing::window * pwindow);



