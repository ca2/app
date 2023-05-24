#pragma once


#include "interaction_layout.h"
#include "prodevian.h"
#include "drawable.h"
#include "acme/exception/status.h"
#include "acme/user/user/drag_client.h"
#include "acme/primitive/collection/string_map.h"
#include "acme/platform/timer_callback.h"
#include "acme/platform/flags.h"
#include "acme/primitive/time/frequency.h"
#include "acme/user/user/e_window_flag.h"
#include "apex/database/key.h"
#include "apex/message/command.h"
#include "apex/user/primitive.h"


namespace user
{


   class CLASS_DECL_AURA interaction :
      virtual public ::user::primitive,
      virtual public ::user::drawable,
      virtual public ::timer_callback,
      virtual public ::user::drag_client
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


      enum enum_non_client
      {

         e_non_client_background = 1,
         e_non_client_focus_rect = 2,
         e_non_client_hover_rect = 4,

      };


      enum enum_updown
      {

         e_updown_normal_frame,
         e_updown_none,
         e_updown_up,
         e_updown_down,

      };


      
      bool                                         m_bExtendOnParent;
      bool                                         m_bExtendOnParentIfClientOnly;
      bool                                         m_bToolWindow;
      bool                                         m_bMessageWindow;
      
      bool                                         m_bCompositedFrameWindow;
      bool                                         m_bEdgeGestureDisableTouchWhenFullscreen;
      bool                                         m_bVisible;
      bool                                         m_bMouseHoverOnCapture;

      //bool                                         m_bMouseHover;
      bool                                         m_bClickDefaultMouseHandling;
      bool                                         m_bHoverDefaultMouseHandling;
      bool                                         m_bEditDefaultHandling;

      bool                                         m_bKeyboardMultipleSelectionDefaultHandling;
      bool                                         m_bDataUpdateDefaultHandling;
      bool                                         m_bParentScrollX;
      bool                                         m_bParentScrollY;

      bool                                         m_bUserInteractionHost;
      bool                                         m_bEnableDragClient;
      bool                                         m_bEnableDragResize;
      bool                                         m_bDerivedHeight;

      bool                                         m_bSketchToDesignLayout;
      bool                                         m_bTransparent;
      bool                                         m_bCreated;
      bool                                         m_bSubclassed;
      
      bool                                         m_bClipRectangle;
      bool                                         m_bLayoutModified;
      bool                                         m_bCustomWindowProc;
      bool                                         m_bControlExCommandEnabled;

      bool                                         m_bIdBound;
      bool                                         m_bOverdraw;
      bool                                         m_bFullScreen;
      bool                                         m_bModal;

      bool                                         m_bNeedRedraw;
      bool                                         m_bNeedLayout;
      bool                                         m_bReposition;
      bool                                         m_bUpdatingVisual;

      bool                                         m_bUpdateVisual;
      bool                                         m_bMouseMovePending;
      bool                                         m_bNeedLoadFormData;
      bool                                         m_bNeedSaveFormData;

      bool                                         m_bWorkspaceFullScreen;
      bool                                         m_bHideOnTransparentFrame;
      bool                                         m_bOffScreenRender;
      bool                                         m_bMoveWindow;

      bool                                         m_bVoidPaint;
      bool                                         m_bRedrawing;
      bool                                         m_bRedrawOnVisible;
      bool                                         m_bSaveWindowRect;

      bool                                         m_bEnableSaveWindowRect2;
      bool                                         m_bShowSoftwareKeyboard;
      bool                                         m_bUserInteractionSetFinish;
      bool                                         m_bDefaultWalkPreTranslateParentTree;

      bool                                         m_bBackgroundBypass;
      bool                                         m_bSizeMove;
      bool                                         m_bCursorInside;
      bool                                         m_bRectOk;

      bool                                         m_bWfiUpDownTarget;
      bool                                         m_bPendingZorder;
      bool                                         m_bPadding001;
      bool                                         m_bPadding002;
      
      bool                                         m_bBarDragScrollLeftButtonDown;

      bool                                         m_bEnableHorizontalBarDragScroll;
      bool                                         m_bHorizontalBarDragScrollingActive;

      bool                                         m_bEnableVerticalBarDragScroll;
      bool                                         m_bVerticalBarDragScrollingActive;

      ::point_i32                                  m_pointBarDragScrollLeftButtonDown;
      ::point_i32                                  m_pointBarDragScroll;
      ::point_i32                                  m_pointBarDragScrollStart;
      ::point_i32                                  m_pointBarDragScrollMax;
      ::size_i32                                   m_sizeBarDragScroll;

      ::oswindow                                   m_oswindow;

      enum_text_wrap                               m_etextwrap;

      ::pointer<::user::interaction_scaler>       m_pinteractionScaler;

      bool                                         m_bUpdateBufferPending;

      //::oswindow                                   m_oswindow;
      e_window_flag                                m_ewindowflag;
      bool                                         m_bAutomaticallyStoreWindowRectangle;
      bool                                         m_bPendingSaveWindowRectangle;
      bool                                         m_bLoadingWindowRectangle;


      bool                                         m_bVisualChanged;

      // <3ThomasBorreggardSørensen_!!
      ::pointer<::matter>                          m_pmatterCommandHandler;

      ::user::interaction::enum_updown             m_eupdown;

   public:

      index                                        m_iItem;
      index                                        m_iSubItem;
      index                                        m_iListItem;
      index                                        m_iColumn;

      atom                                        m_uiText;
      ::type                                    m_type;
      atom                                        m_atomPrivateDataSection;
      //::atom                                      m_atomTranslated;
      enum_control_type                         m_econtroltype;

      enum_control_ddx                          m_eddx;
      ::string                                  m_strDataKey20;
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

      ::user::interaction *                     m_puserinteractionTopLevel;
      ::user::frame *                           m_puserframeTopLevel;
      ::user::frame *                           m_puserframeParent;
      ::windowing::window *                     m_pwindow;


      ::rectangle                               m_rectangleClip;
      ::pointer<::aura::draw_context>          m_pdrawcontext;

      ::draw2d::path_pointer                    m_pathFocusRect1;
      ::draw2d::path_pointer                    m_pathFocusRect2;
      ::draw2d::path_pointer                    m_pathFocusRect3;
      ::draw2d::path_pointer                    m_pathFocusRect4;

      
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

      // control member variables END

      string                                       m_strInteractionTag;

      ::index                                      m_iIndex;
      ::size_i32                                   m_sizeRestoreBroad;
      ::size_i32                                   m_sizeRestoreCompact;
      enumeration < enum_non_client >              m_flagNonClient;
      int                                          m_iMouseMoveSkipCount;
      int                                          m_iMouseMoveSkipSquareDistance;
      class ::time                                   m_timeMouseMoveSkip;
      ::point_i32                                  m_pointMouseMoveSkip;
      class ::time                                   m_timeMouseMovePeriod;
      ::point_i32                                  m_pointMouseMove;
      class ::time                                   m_timeLastRedraw;
      ::atom                                       m_atomImpact;
      ::color::color                               m_colorBackground;
      point_i32                                    m_pointScroll;
      // if high frequency mouse transfer notification is required
      // create a fast path/low latency callback system
      class ::time                                   m_timeMouseMove;
      class ::time                                   m_timeMouseMoveIgnore;
      double                                       m_dItemHeight;
      point_i32                                    m_pointMoveCursor;
      class ::time                                   m_timeLastFullUpdate;
      class ::time                                   m_timeLastVisualChange;
      string                                       m_strName;
      u64                                          m_uiUserInteractionFlags;
      ::pointer<::windowing::cursor>              m_pcursor;
      string                                       m_strWindowText2;
      ::a_string_function                          m_astringfunctionWindowText;

      atom                                           m_atomModalResult; // for return values from interaction_impl::RunModalLoop
      i32                                          m_nModalResult; // for return values from ::interaction_impl::RunModalLoop



      //interaction_draw2d *                         m_pinteractiondraw2d;

      /// The menu_item this user_interaction (window)
      /// represents (this window is a button [a menu button],
      /// this window is a m_pcheckbox [a menu m_pcheckbox],
      /// this window is a player/impact [a menu picture/video/chat?!])


      // references
      ::pointer<::file::insert_item>            m_pitemComposing;
      ::pointer<::thread>                       m_pthreadUserInteraction;
      ::pointer<::user::interaction>            m_puserinteractionParent;
      ::pointer<::user::interaction>            m_pupdowntarget;
      ::task_pointer                            m_ptaskModal;
      ::pointer<interaction>                    m_puserinteractionOwner;

      // ownership
      ::pointer<::user::system>                 m_pusersystem;
   protected:
      ::user::interaction_layout                m_layout;
   public:
      //::pointer<drag_move>                        m_pdragmove;
      ::pointer<::draw2d::graphics_call_array>    m_pgraphicscalla;
      ::pointer<::user::interaction>              m_puserinteractionCustomWindowProc;
      ::pointer<::user::interaction>              m_puiLabel;
      ::pointer<::user::form>                     m_pform;
      ::pointer<alpha_source>                     m_palphasource;
      //::pointer<::aura::drawable>                 m_pdrawableBackground;
      ::pointer<primitive_impl>                   m_pprimitiveimpl;
      ::pointer<interaction_impl>                 m_pinteractionimpl;
      ::pointer<primitive_pointer_array>          m_puserinteractionpointeraOwned;
      ::pointer<interaction_array>                m_puserinteractionpointeraChild;
      ::pointer<interaction>                      m_ptooltip;
      ::pointer<::object>                         m_pmenuitem;
      pointer_array < interaction >                 m_menua;
      ::pointer<::appearance::appearance>         m_pappearance;
      bool                                         m_bEmptyAreaIsClientArea;


      interaction();
      ~interaction() override;

      void user_interaction_common_construct();

      virtual void on_create_user_interaction();

      void on_initialize_particle() override;

      virtual bool is_branch_current() const override;


      bool is_ready_to_quit() const override;


      virtual void set_appearance(::appearance::appearance * pappearance);
      virtual ::appearance::appearance * get_appearance();


      virtual bool is_sandboxed();


      //class control_descriptor& descriptor();
      //const class control_descriptor& descriptor();
      ::aura::application * get_app();
      ::aura::session * get_session();
      //::aura::system * acmesystem();
      ::aura::context * context();

      bool _001CanEnterScreenSaver() override;

      virtual void _001Maximize();

      virtual void _001Restore();

      virtual void _001Minimize();

      //void enable_drag_move();

      virtual void set_restored_rectangle(const ::rectangle_i32 & rectangleRestored);

      
      virtual void set_position(const ::point_i32 & point, enum_layout elayout = e_layout_sketch);
      virtual void set_size(const ::size_i32 & size, enum_layout elayout = e_layout_sketch);
      virtual void set_width(::i32 width, enum_layout elayout = e_layout_sketch);
      virtual void set_height(::i32 height, enum_layout elayout = e_layout_sketch);
      /// @brief shift left position changing size
      /// @param left left position
      /// @param elayout elayout to change
      virtual void shift_left(::i32 left, enum_layout elayout = e_layout_sketch);
      /// @brief  sets right position maintaining size
      /// @param right right position
      /// @param elayout elayout to change
      virtual void set_right(::i32 right, enum_layout elayout = e_layout_sketch);

      /// @brief sets top position maintaining size
      /// @param top top position
      /// @param elayout elayout to change
      virtual void set_top(::i32 top, enum_layout elayout = e_layout_sketch);
      
      virtual bool on_set_position(const ::point_i32 & point, enum_layout elayout);
      virtual bool on_set_size(const ::size_i32 & size, enum_layout elayout);

      //virtual interaction_draw2d * get_draw2d();
      double point_dpi(double d) override;
      double dpiy(double d) override;


      virtual float get_dpi_for_window();

      virtual float get_density_for_window();


      virtual ::string calculate_data_key();

      virtual ::string get_data_key(const ::scoped_string & scopedstrAppend);

      

         //}
         //else
         //{

         //fFontSize = pgraphics->m_puserinteraction->get_window()->dpiy((float)m_dFontSize);


      //::windowing::window * window();

      virtual ::windowing::windowing * windowing();

      virtual ::windowing::display * get_display();

      virtual ::user::interaction * get_host_window();

      virtual ::user::interaction_impl * get_window_impl();

      virtual ::item_pointer get_user_item(const ::item & item);

      virtual ::user::enum_state get_user_state();

      virtual bool has_hover();

      virtual bool has_link();

      virtual pointer_array < interaction > * children();


      inline iterator proper_children() { return {this, e_next_proper, this}; }


      const class ::user::interaction_layout& const_layout() const { return m_layout; }
      class ::user::interaction_layout& layout() { return m_layout; }

      double screen_scaler();
      double font_scaler();


      //void clear();
      void control_descriptor_common_construct();
      //bool operator == (const control_descriptor & control_descriptor);
      //control_descriptor & operator = (const control_descriptor & control_descriptor);
      virtual enum_control_type get_control_type() const override;
      virtual void set_control_type(enum_control_type e_control);
      virtual void add_function(enum_control_function enum_control_function);
      virtual void erase_function(enum_control_function enum_control_function);
      virtual bool has_function(enum_control_function enum_control_function);
      virtual enum_control_data_type get_data_type();
      virtual void set_data_type(enum_control_data_type enum_control_data_type);
      virtual void set_ddx_dbflags(const ::scoped_string & scopedstr, iptr value);

      //index find_control(::user::interaction * pinteraction);

      //::pointer<interaction>alloc();
      
      
      


      virtual void queue_graphics_call(const ::function<void(::draw2d::graphics_pointer&) > & function);

      void process_graphics_call_queue(::draw2d::graphics_pointer & pgraphics);

      //void process_call(::draw2d::graphics_pointer & pgraphics, const call & call);



      //virtual void task_on_term(::task* pthread) override;


      //virtual void main_async(const ::procedure & procedure, enum_priority epriority = e_priority_normal);


      //virtual void enumerate_composite(matter_array& a) override;

      virtual bool is_user_thread();

      virtual void interaction_send(const ::procedure & procedure);

      virtual void interaction_post(const ::procedure & procedure) override;

      virtual void windowing_send(const ::procedure& procedure);

      virtual void windowing_post(const ::procedure& procedure);



      inline void auto_prodevian_on_show() { m_ewindowflag |= e_window_flag_auto_prodevian_on_show; }
      inline void clear_auto_prodevian_on_show() { m_ewindowflag -= e_window_flag_auto_prodevian_on_show; }
      inline bool is_auto_prodevian_on_show() { return m_ewindowflag & e_window_flag_auto_prodevian_on_show; }

      //inline void visual_changed() { m_ewindowflag |= e_window_flag_visual_changed; }
      //inline void clear_visual_changed() { m_ewindowflag -= e_window_flag_visual_changed; }
      //inline bool is_visual_changed()const { return m_ewindowflag & e_window_flag_visual_changed; }


      bool is_ok() const
      {

         return ::is_set(this) && m_pprimitiveimpl.is_set();

      }

      virtual string get_class_style(string strClass);
      virtual void set_class_style(string strClass, string strStyle);
      virtual void sync_style();
      virtual string get_full_style();
      virtual void load_style(string strStyle);


      virtual::e_display window_stored_display();
      virtual::e_display window_previous_display();


      virtual void set_window_previous_display(::e_display edisplayPrevious);


      virtual int get_derived_height(int iWidth);
      virtual int get_derived_width(int iHeight);


      virtual bool is_full_screen_enabled();
      inline bool is_full_screen() { return m_bFullScreen; }
      virtual bool _is_full_screen();

      virtual bool get_element_rect(::rectangle_i32 & rectangle, enum_element eelement);


      virtual status < rectangle_i32 > rectangle(enum_element eelement)
      {

          ::rectangle_i32 rectangle;

          if (!get_element_rect(rectangle, eelement))
          {

              return ::error_failed;

          }

          return rectangle;

      }


      virtual enum_element get_default_element();
      virtual ::write_text::font_pointer get_font(::user::style * pstyle, enum_element eelement, ::user::enum_state estate = e_state_none);
      inline ::write_text::font_pointer get_font(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_font(pstyle, get_default_element(), estate); }
      virtual enum_translucency get_translucency(::user::style* pstyle);
      virtual int get_int(::user::style* pstyle, enum_int eint, ::user::enum_state estate = e_state_none, int iDefault = 0);
      virtual double get_double(::user::style* pstyle, enum_double edouble, ::user::enum_state estate = e_state_none, double dDefault = 0.);
      virtual status < ::rectangle_f64 > get_border(::user::style* pstyle, enum_element eelement, ::user::enum_state estate = e_state_none);
      inline status < ::rectangle_f64 > get_border(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_border(pstyle, get_default_element(), estate); }
      virtual status < ::rectangle_f64 > get_padding(::user::style* pstyle, enum_element eelement, ::user::enum_state elayout = e_state_none);
      inline status < ::rectangle_f64 > get_padding(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_padding(pstyle, get_default_element(), estate); }
      virtual status < ::rectangle_f64 > get_margin(::user::style* pstyle, enum_element eelement, ::user::enum_state estate = e_state_none);
      inline status < ::rectangle_f64 > get_margin(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_margin(pstyle, get_default_element(), estate); }
      virtual status < ::color::color > get_color(::user::style* pstyle, enum_element eelement, ::user::enum_state elayout = e_state_none);
      inline status < ::color::color > get_color(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_color(pstyle, get_default_element(), estate); }

      virtual ::user::e_flag get_draw_flags(::user::style* pstyle);

      virtual ::user::enum_state get_state();

      virtual ::user::style* get_style();

      virtual ::user::style * get_style(::draw2d::graphics_pointer& pgraphics);

      inline ::user::style * get_style(::user::style * pstyle)
      {

         return pstyle ? pstyle : pstyle = get_style();

      }

      virtual void on_tsf_activate(bool bActivate);

      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom);


//      virtual bool add_control(arguments arguments);


      inline bool is_graphical() const { return !m_bMessageWindow && m_ewindowflag & e_window_flag_graphical; }


      virtual ::particle * mutex_draw();


      //virtual bool AddControlBar(::user::control_bar* pcontrolbar);
      //virtual bool RemoveControlBar(::user::control_bar* pcontrolbar);

      // updown
      virtual bool wfi_is_up();
      virtual bool wfi_is_down();
      virtual bool wfi_has_up_down();
      // end updown



      virtual void child_set_unique_id(::user::interaction* pinteraction);

      virtual string default_id_prefix();

      interaction * get_tooltip();

      void set_tool_window(bool bSet = true) override;

      virtual double get_rotate();
      ::user::form * get_form() override;
      ::user::form * get_parent_form() override;
      ::user::element * get_form_user_element() override;
      ::user::element * get_parent_form_user_element() override;

      ::user::interaction * get_user_interaction() override;

      ::particle * get_taskpool_container() override;

      //task_pointer defer_fork(const ::atom& atom, const matter_pointer& pmatter);

      virtual void set_place_child_title(const ::string & pszTitle);

      virtual ::user::primitive * get_bind_ui();

      virtual string get_display_tag();


      void on_set_finish() override;


      void destroy() override;
      void delete_this() override;


      virtual void display_system_minimize();


      //void window_move(i32 x, i32 y) override;


      //auto prodevian() { return __new(::prodevian(this)); }

      virtual bool should_save_window_rectangle();
      
      virtual bool FancyWindowDataLoadWindowRectangle(bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool WindowDataLoadWindowRectangle();
      virtual void WindowDataSaveWindowRectangle();

      virtual void on_defer_display();

      virtual bool display_sketch_to_design();
      virtual void design_display();
      virtual void design_appearance();
      virtual void design_zorder();
      virtual void design_reposition();
      virtual void design_layout(::draw2d::graphics_pointer & pgraphics);


      virtual void display_restored();
      virtual void display_zoomed();
      virtual void display_iconic();
      virtual void display_restore();
      virtual void display_notify_icon();

      
      virtual void design_restored();
      virtual void design_iconic();
      virtual void design_window_minimize(::e_activation eactivation) override;
      virtual void design_window_maximize() override;
      virtual void design_window_full_screen(const ::rectangle_i32& rectangleHint = nullptr) override;
      virtual void design_window_restore(::e_display edisplay) override;
      virtual void design_window_dock(::e_display edisplay) override;


      virtual ::size_i32 preferred_size(::draw2d::graphics_pointer & pgraphics);


      virtual void prodevian_stop() override;

      virtual void prodevian_redraw(bool bUpdateBuffer) override;

      //virtual void _001OnAfterAppearance();


      virtual void defer_restore(const ::rectangle_i32& rectangleRequest);
      ::property_object * parent_property_set_holder() const override;


      float preferred_dpi_x() override;
      float preferred_dpi_y() override;
      float preferred_density() override;

      
      virtual void add_appearance(::e_appearance eappearance, enum_layout elayout = e_layout_sketch);
      virtual void erase_appearance(::e_appearance eappearance, enum_layout elayout = e_layout_sketch);
      virtual void toggle_appearance(::e_appearance eappearance, enum_layout elayout = e_layout_sketch);


      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);
      virtual void set_need_layout(bool bAscendants = true);
      //void set_need_layout() { m_bNeedLayout = true; }
      void set_need_redraw(const ::rectangle_i32& rectangleNeedRedraw = {}, bool bAscendants = true) override;
      virtual bool needs_to_draw(::draw2d::graphics * pgraphics, const ::rectangle_i32& rectangleNeedsToDraw = {});
      virtual void set_need_load_form_data() override;
      virtual void set_need_save_form_data() override;
      //virtual bool commit_sketch();
      virtual void post_redraw(bool bAscendants = true) override;
      virtual bool should_redraw_on_mouse_activate();
      virtual bool should_redraw_on_mouse_hover();
      virtual bool should_redraw_on_hover(::item * pitem);
      virtual void show_window();


      ///virtual bool is_sketch_to_design_locked();

      
      virtual void clear_activation(enum_layout elayout = e_layout_design);
      
      virtual void set_display(::e_display edisplay = e_display_default, enum_layout elayout = e_layout_design);
      
      virtual void set_layout_state(const layout_state & state, enum_layout elayout = e_layout_design);

      virtual void set_activation(::e_activation eactivation, enum_layout elayout = e_layout_sketch);

      virtual void display(::e_display edisplay = e_display_default, ::e_activation eactivation = ::e_activation_default) override;


      virtual bool check_child_zorder();

      virtual ::zorder zorder(enum_layout elayout = e_layout_design);
      virtual void order(::zorder zorder);

      inline void order_top() { order(e_zorder_top); }
      inline void order_front() { order(e_zorder_top); }
      inline void order_top_most() { order(e_zorder_top_most); }
      inline void order_bottom() { order(e_zorder_bottom); }


      //virtual void sketch_to_design(::draw2d::graphics_pointer & pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void sketch_to_design(bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void _001UpdateWindow() override;
      //virtual void window_apply_visual(const class layout_state& windowstate) override;



      virtual void frame_experience_restore();
      
      virtual ::user::notify_icon * notify_icon();

      virtual void on_update_notify_icon_menu(::index & iNotifyIconIndex);
      
      virtual void on_app_activated();

      virtual void frame_restore();

      virtual void frame_occlude();
      
      virtual void frame_toggle_restore();
      
      virtual void display_previous_restore();

      // Client Rect : e_layout_design : Design/_001OnDraw time
      virtual void input_client_rectangle(::rectangle_i32 & rect, enum_layout elayout = e_layout_sketch);


      virtual void client_rectangle(::rectangle_i32 & rect, enum_layout elayout = e_layout_sketch);
      virtual ::rectangle_i32 client_rectangle(enum_layout elayout = e_layout_sketch);


      virtual ::rectangle_i32 parent_client_rectangle(enum_layout elayout = e_layout_sketch);
      virtual ::point_i32 position(enum_layout elayout = e_layout_sketch);
      virtual ::size_i32 size(enum_layout elayout = e_layout_sketch);
      virtual ::i32 top(enum_layout elayout = e_layout_sketch);
      virtual ::i32 left(enum_layout elayout = e_layout_sketch);
      virtual ::i32 right(enum_layout elayout = e_layout_sketch);
      virtual ::i32 bottom(enum_layout elayout = e_layout_sketch);


      virtual void window_rectangle(::rectangle_i32 & rect, enum_layout elayout = e_layout_sketch);
      virtual ::rectangle_i32 window_rectangle(enum_layout elayout = e_layout_sketch);


      inline void set_prodevian() { return add_prodevian(this); }
      inline void clear_prodevian() { return erase_prodevian(this); }
      inline bool is_prodevian() const { return is_prodevian(this); }


      void add_prodevian(::matter * pmatter) override;
      void erase_prodevian(::matter * pmatter) override;
      bool is_prodevian(const ::matter * pmatter) const override;
      bool has_prodevian() const noexcept;


      virtual bool is_frame_window();
      bool is_this_visible(enum_layout elayout = e_layout_design) override;

      virtual bool sketch_on_display();


      //bool is_this_visible(enum_layout elayout = e_layout_design);
      bool is_this_screen_visible(enum_layout elayout = e_layout_design);

      bool is_window_visible(enum_layout elayout = e_layout_design);
      bool is_window_screen_visible(enum_layout elayout = e_layout_design);


      virtual void create_message_queue(const ::string & strName) override;

      virtual ::pointer<::message::message>get_message(const ::atom & atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype = ::message::e_prototype_none) override;

      virtual bool has_text_input();

      virtual void kick_queue();

      virtual bool contains_user_interaction(::user::interaction* pinteraction, bool bRecursive = true);


      virtual void on_select() override;

      virtual bool is_place_holder() override;

      virtual ::frequency get_output_per_second();


      virtual ::pointer<::windowing::cursor>get_mouse_cursor(enum_cursor ecursor);

      virtual ::windowing::cursor * get_mouse_cursor() override;

      virtual ::point_i32 get_cursor_position();

      virtual void set_cursor_position(const ::point_i32 & pointCursor);

      virtual void release_mouse_capture();


      inline void defer_graphics(::draw2d::graphics_pointer & pgraphics)
      {

         if (!pgraphics) pgraphics = create_memory_graphics();

      }

      virtual ::draw2d::graphics_pointer create_memory_graphics();


      virtual double _001GetDefaultFontHeight(::draw2d::graphics_pointer & pgraphics);

      //virtual void set_cursor(enum_cursor ecursor) override;


      virtual void set_mouse_cursor(::windowing::cursor * pcursor) override;


      //virtual ::point_i32 get_cursor_position() override;


      virtual bool is_left_button_pressed();


      virtual void set_current_item(item * pitem, const ::action_context & action_context);
      virtual ::item_pointer current_item();


      virtual ::item_pointer hover_item();


      virtual bool _is_window() const override;
      inline bool is_window() const { return m_ewindowflag & e_window_flag_is_window; }

      virtual void ExitHelpMode();

      //virtual ::i32 get_window_long(i32 nIndex) override;
      //virtual ::i32 set_window_long(i32 nIndex, ::i32 lValue) override;

      //virtual iptr get_window_long_ptr(i32 nIndex) override;
      //virtual void set_window_long_ptr(i32 nIndex, iptr lValue) override;

      virtual bool on_before_set_parent(::user::primitive * pinterface);
      virtual bool on_set_parent(::user::primitive * pinterface);
      virtual bool on_add_child(::user::interaction * puserinteractionChild);
      virtual void on_after_set_parent();


      virtual bool on_set_owner(::user::primitive * pinterface);


      ::user::element * first_child_user_primitive() override;
      ::user::element * top_user_primitive() override;
      ::user::element * under_user_primitive() override;
      ::user::element * above_user_primitive() override;
      ::user::element * next_user_primitive() override;
      ::user::element * previous_user_primitive() override;


      virtual ::user::interaction* first_child() override;
      virtual ::user::interaction* last_child() override;
      virtual ::user::interaction* last_sibling() override;
      virtual ::user::interaction* next_sibling() override;
      virtual ::user::interaction* previous_sibling() override;
      virtual ::user::interaction* first_sibling() override;
      virtual ::user::interaction* next_sibling(::user::interaction* pinteraction) override;
      virtual ::user::interaction* previous_sibling(::user::interaction* pinteraction) override;


      virtual void mouse_hover_add(::user::interaction* pinterface);
      virtual bool mouse_hover_erase(::user::interaction* pinterface);

      virtual i32 get_wheel_scroll_delta();

      template < typename TYPE >
      TYPE * typed_descendant(::user::interaction * puiExclude = nullptr)
      {

         auto puserinteractionpointeraChild = children();

         if (!puserinteractionpointeraChild)
         {

            return nullptr;

         }

         for (auto & pinteraction : *puserinteractionpointeraChild)
         {

            if (pinteraction != puiExclude)
            {

               TYPE * point = dynamic_cast <TYPE *> (pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }

         }

         for (auto & pinteraction : *puserinteractionpointeraChild)
         {

            if (pinteraction != puiExclude)
            {

               TYPE * point = pinteraction->typed_descendant < TYPE >(pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }

         }

         return nullptr;

      }


      template < typename CHILD >
      inline bool get_typed_child(CHILD *& pchild, ::i32 iLevel = -1, ::user::interaction * puiExclude = nullptr)
      {

         auto puserinteractionpointeraChild = children();

         if (!puserinteractionpointeraChild)
         {

            return false;

         }

         for (auto & pinteraction : *puserinteractionpointeraChild)
         {

            if (pinteraction != puiExclude)
            {

               auto pchildCandidate = dynamic_cast <CHILD *> (pinteraction.m_p);

               if (pchildCandidate != nullptr)
               {

                  pchild = pchildCandidate;

                  return true;

               }

            }

         }

         if (iLevel < 0 || iLevel > 0)
         {

            for (auto & pinteraction : *puserinteractionpointeraChild)
            {

               if (pinteraction != puiExclude)
               {

                  if(pinteraction->get_typed_child(pchild, iLevel - 1, puiExclude))
                  {

                     return true;

                  }

               }

            }

         }

         return false;

      }


      template < typename TYPE >
      ::pointer<TYPE> _001TypedWindow(::pointer<TYPE> & p)
      {

         return p = _001TypedWindow<TYPE>();

      }


      template < typename TYPE >
      TYPE* _001TypedWindow() // search descedants first, then ascendants descedants.
      {

         ::user::interaction* pinteraction = this;

         ::user::interaction* puiExclude = nullptr;

         while (pinteraction != nullptr)
         {

            TYPE* point = pinteraction->typed_descendant < TYPE >(puiExclude);

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


      //virtual void CheckAutoCenter() override;

      virtual void track_mouse_hover() override;
      virtual void track_mouse_leave() override;


      virtual void update_dialog_controls(channel* ptarget) override;
      virtual void CenterWindow(::user::interaction* pAlternateOwner = nullptr) override;
      virtual void _001Emphasize(int cx, int cy);
      virtual atom   run_modal_loop(::user::interaction* pinteraction, u32 dwFlags = 0) override;
      virtual atom   RunModalLoop(u32 dwFlags = 0) override;
      virtual atom   _001RunModalLoop(u32 dwFlags = 0) override;
      virtual bool ContinueModal() override;
      virtual void EndModalLoop(atom nResult) override;


      void update_data(bool bSaveAndValidate = true) override;


      virtual ::user::interaction* get_os_focus_uie();


      virtual bool pre_message_handler(::message::key*& puserkey, bool& bKeyMessage, ::message::message* pmessage);


      //virtual void on_set_keyboard_focus() override;
      //virtual void on_kill_keyboard_focus() override;


      ::user::element * get_keyboard_focus() override;


      element * keyboard_set_focus_next(bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      //virtual primitive * keyboard_set_focus_next(primitive * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      

      virtual void get_child_rect(::rectangle_i32 & rectangle);

      inline auto get_child_rect() { ::rectangle_i32 rectangle(e_no_initialize); get_child_rect(rectangle); return rectangle; }

      virtual bool scroll_bar_get_client_rect(::rectangle_i32 & rectangle);

      virtual void window_show();
      virtual void on_visual_applied();

      virtual ::size_f64 _001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics);
      virtual ::size_f64 _001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_reposition() override;
      virtual void on_show_window() override;
      virtual void _on_show_window();
      
      virtual void on_drag_scroll_layout(::draw2d::graphics_pointer & pgraphics);

      virtual void window_show_change_visibility();

      virtual void defer_save_window_placement();

//#ifdef WINDOWS_DESKTOP
//
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);
//
//#endif


      virtual bool pre_create_window(::user::system * pusersystem);


      //void subclass_window(oswindow posdata) override;
      //virtual oswindow unsubclass_window() override;


      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_interaction(class ::user::control_descriptor * pdescriptor);

      virtual void create_host() override;
      virtual void create_child(::user::interaction * pparent) override;

      // virtual bool create_interaction(const ::string & pszClassName, const ::string & pszWindowName, u32 uStyle, ::user::interaction * puiParent, ::request * prequest = nullptr) override;

      //virtual bool create_window_ex(::pointer<::user::system>pcs, ::user::interaction* puiParent = nullptr, const ::atom& atom = ::atom()) override;
      //enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      //virtual void CalcWindowRect(::rectangle_i32* pClientRect, ::u32 nAdjustType = adjustBorder) override;


      virtual bool IsTopParentActive();
      virtual void ActivateTopParent() override;



      virtual void start_destroying_window() override;

      virtual void destroy_window() override;

      //virtual void on_finish() override;

      //virtual void set_finish_composites(::property_object* pcontextobjectFinish) override;

      void on_destroy() override;

      //void destroy() override;

      void notify_on_destroy(::property_object* pcontextobjectFinish) override;

      //virtual void destroy() override;


//#ifdef WINDOWS
//
//      virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr,
//         ::draw2d::region* prgnUpdate = nullptr,
//         ::u32 flags = RDW_INVALIDATE | RDW_ERASE) override;
//
//#else

      virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr,
         ::draw2d::region* prgnUpdate = nullptr,
         ::u32 flags = 0);

//#endif


      virtual void register_drop_target();




      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = true) override;
      virtual bool GetUpdateRect(::rectangle_i32* prectangle, bool bErase = false) override;

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true) override;
      virtual void InvalidateRect(const ::rectangle_i32& rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      virtual void ValidateRect(const ::rectangle_i32& rectangle);

      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = true);


      virtual bool is_composite() override;

      //virtual u32 GetStyle() override;
      //virtual u32 GetExStyle() override;
      //virtual void ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0) override;
      //virtual void ModifyStyleEx(u32 dwRemove, u32 dwAdd, ::u32 nFlags = 0) override;

      using ::user::primitive::send;
      virtual lresult send(::message::message* pmessage) override;
      void post(::message::message* pmessage) override;
      virtual lresult send_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32& point = nullptr) override;

      virtual lresult message_call(const ::atom & atom, wparam wparam = 0, lparam lparam = 0, const ::point_i32& point = nullptr) override;
      virtual lresult message_call(::message::message * pmessage) override;


#ifdef LINUX

      virtual lresult send_x11_event(void* pevent) override; // XEvent *

#endif

      virtual void post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = 0) override;

      virtual void post_object(const ::atom & atom, wparam wParam, lparam lParam);


      //virtual void user_post(const ::atom& atom, wparam wParam = 0, lparam lParam = 0) override;

      //virtual void SetWindowDisplayChanged() override;


      virtual void call_and_set_timer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer = nullptr);
      virtual void set_timer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void* pdata = nullptr);
      virtual void SetTimer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void* pdata = nullptr) override;
      virtual void KillTimer(uptr uEvent) override;

//      virtual void enable_window(bool bEnable = true) override;

      //virtual void process_queue(::draw2d::graphics_pointer & pgraphics);

      virtual void do_graphics(::draw2d::graphics_pointer & pgraphics);
      virtual void on_graphics(::draw2d::graphics_pointer & pgraphics);
      void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) ;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) ;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _008CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnNcClip(::draw2d::graphics_pointer& pgraphics);
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) ;

      virtual bool is_custom_draw();

      virtual atom GetDlgCtrlId() const override;
      virtual atom SetDlgCtrlId(const ::atom & atom) override;

//#ifdef WINDOWS_DESKTOP
//
//      virtual void open_clipboard() override;
//      virtual void close_clipboard() override;
//
//#endif

      virtual bool is_active_window();

      virtual bool has_mouse_capture();
      virtual void set_mouse_capture();

      virtual bool has_keyboard_focus();
      void set_keyboard_focus() override;
      void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr) override;

      virtual void set_foreground_window();
      virtual void set_active_window();

      virtual void bring_to_front();

      virtual bool is_window_enabled();
      inline bool is_this_window_enabled()  { return m_ewindowflag.is(e_window_flag_enable); }
      void enable_window(bool bEnable = true) override;

      virtual void on_calc_size(calc_size* pcalcsize);

      virtual void walk_pre_translate_tree(::message::message* pmessage, ::user::interaction* puiStop = nullptr);


      bool edit_undo() override;

      virtual void edit_on_text(string str) override;
      virtual void edit_on_sel(strsize iBeg, strsize iEnd) override;

      void get_text_composition_area(::rectangle_i32 & r) override;
      virtual void on_text_composition(string str) override;
      virtual void on_text_composition_done() override;

      //void is_text_composition_active() override;

      virtual int on_text_composition_message(int iMessage);

      void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

      virtual void set_window_text(const ::string & pszString) override;
      virtual void set_window_text_source(const ::a_string_function & astringfunction) override;
      virtual void clear_window_text_source();

      virtual void on_set_window_text();

//#ifdef WINDOWS
//      strsize _009GetWindowText(wchar_t * pwsz, int n) override;
//#else
//      strsize _009GetWindowText(char * psz, int n) override;
//#endif
//      virtual strsize _009GetWindowTextLength() override;

      //virtual strsize get_window_text(char* pszStringBuf, strsize nMaxCount) override;

      //virtual ::string _get_window_text();
      virtual string get_window_text() override;
      //virtual void get_window_text(string& rectangleString) override;
      //virtual strsize get_window_text_length() override;

      virtual ::user::frame* frame();
      inline ::user::interaction * top_level() { return m_puserinteractionTopLevel; }
      inline ::user::frame * top_level_frame() { return m_puserframeTopLevel; }
      inline ::user::frame * parent_frame() { return m_puserframeParent; }
      virtual ::user::frame* get_owner_frame();

      ::user::interaction * _top_level() override;
      virtual ::user::frame * _top_level_frame();
      virtual ::user::frame * _parent_frame();


      //virtual ::handler* get_user_callback();

      virtual void defer_set_icon();

      virtual void set_windowing_icon(::windowing::icon* picon);

      virtual ::windowing::icon* get_windowing_icon();
      virtual ::draw2d::icon* get_draw_icon();



      //virtual void set_cursor(::windowing::cursor* pcursor);

      ::graphics::graphics* get_window_graphics() override;

      //virtual void _001PrintBuffer(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001Print(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001DrawThis(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001DrawChildren(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics);
      //virtual void _008OnDraw(::draw2d::graphics_pointer& pgraphics);
      //virtual void draw_control_background(::draw2d::graphics_pointer& pgraphics);
      //virtual void _000OnDraw(::draw2d::graphics_pointer& pgraphics) override;

      void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics) override;
      void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics) override;

      
      //virtual ::oswindow _oswindow();


      inline ::oswindow get_safe_oswindow();
      inline ::oswindow oswindow() { return m_oswindow; }


      //virtual ::windowing::window * window();


      //virtual void RedrawWindow(const ::rectangle_i32& rectangleUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr, ::u32 flags = 0);
      //virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      ////      virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const ::rectangle_i32& rectangle, bool bErase = true);

      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const ::rectangle_i32& rectangle);

      //virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual void ShowOwnedPopups(bool bShow = true);


      //virtual void route(::topic * ptopic, ::context * pcontext);
      //void handle(::topic * ptopic, ::context * pcontext) override;


      /*void pre_create_window(::user::system* pusersystem);*/
      using ::user::primitive::handle;
      void handle(::topic * ptopic, ::context * pcontext) override;



      virtual void install_message_routing(::channel* pchannel) override;
      virtual void prio_install_message_routing(::channel* pchannel);


      virtual void _000OnMouseLeave(::message::message* pmessage) override;

      //virtual void _000OnMouse(::message::mouse* pmouse);
      //virtual void _000OnThisMouse(::message::mouse* pmouse);
      //virtual void _000OnChildrenMouse(::message::mouse* pmouse);
      virtual void _000OnKey(::message::key* pkey);
      virtual void _000OnDrag(::message::drag_and_drop* pdrag);

      



      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);

      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);

      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_enter);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_wheel);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);


      // drag_client
      void drag_set_capture() override;
      ::point_i32 on_drag_start(::user::drag * pdrag) override;
      bool drag_shift(::user::drag * pdrag) override;
      bool drag_hover(::user::drag * pdrag) override;
      void drag_release_capture() override;
      void drag_set_cursor(::user::drag * pdrag) override;


      void _001OnTimer(::timer* ptimer) override;
      void on_timer(::timer* ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_character);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_user_post);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
      DECLARE_MESSAGE_HANDLER(on_message_close);
      //DECLARE_MESSAGE_HANDLER(_001OnCommand);
      DECLARE_MESSAGE_HANDLER(on_message_simple_command);
      DECLARE_MESSAGE_HANDLER(on_message_need_load_form_data);
      DECLARE_MESSAGE_HANDLER(on_message_need_save_form_data);
      DECLARE_MESSAGE_HANDLER(on_message_display_change);
      DECLARE_MESSAGE_HANDLER(on_message_subject);


      //virtual DECLARE_MESSAGE_HANDLER(_002OnLButtonDown);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnLButtonUp);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnMouseMove);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnMouseEnter);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnMouseLeave);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnKeyDown);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnKeyUp);
      //virtual DECLARE_MESSAGE_HANDLER(_002OnTimer);

      DECLARE_MESSAGE_HANDLER(_001OnTextComposition);


      bool _001IsPointInside(const ::point_i32 & point) override;

      virtual rectangle_i32 screen_rect();

      virtual bool _001IsPointInsideInline(const ::point_i32 & point);
      virtual bool _001IsClientPointInsideInline(const ::point_i32 & point);
      virtual  bool _001IsParentClientPointInsideInline(const ::point_i32 & point);

      ::user::interaction* _001FromPoint(::point_i32 point, bool bTestedIfParentVisible = false) override;

      void OnLinkClick(const ::string & psz, const ::string & pszTarget = nullptr) override;

      void pre_translate_message(::message::message* pmessage) override;


      ::user::interaction * get_child_by_name(const ::string & strName, ::index iItem = -1, i32 iLevel = -1) override;
      ::user::interaction * get_child_by_id(const atom & atom, ::index iItem = -1, i32 iLevel = -1) override;
      ::user::element * get_primitive_by_id(const atom & atom, ::index iItem, i32 iLevel) override;

      
      ::user::interaction* child_from_point(const ::point_i32& point, ::i32 iLevel = -1, const ::user::interaction_array * pinteractionaExclude = nullptr);


      bool is_ascendant(element * puiIsAscendant, bool bIncludeSelf) override;
      bool is_parent(element * puiIsParent) override;
      bool is_child(element * puiIsChild)  override;
      bool is_descendant(element * puiIsDescendant, bool bIncludeSelf) override;

      virtual bool is_ascendant(::user::controller * pcontroller, bool bIncludeSelf) ;
      virtual bool contains(element* puiIsChild) ;

      virtual bool recursively_contains(element* puiIsChild, bool bIncludeSelf);

      ::user::interaction* get_wnd() override;
      ::user::interaction* get_wnd(::u32 nCmd) override;

      ::user::primitive * set_parent(::user::primitive * pinteraction) override;
      ::user::primitive * set_owner(::user::primitive * pinteraction) override;

      void on_add_owned(::user::primitive * pprimitive) override;

      ::user::interaction * get_parent_window() override;

      ::user::interaction * get_first_child_window() override;


      inline bool is_hosted() { return m_ewindowflag & e_window_flag_hosted; }
      inline bool is_top_level()  { return m_ewindowflag & e_window_flag_top_level; }
      inline bool is_root()  { return m_ewindowflag & e_window_flag_root; }

      bool is_host_top_level() override;

      ::user::element * get_parent_primitive() override;

      ::user::interaction* get_parent() override;
      ::user::interaction* get_owner() override;
      ::user::interaction* get_parent_owner() override;
      ::user::interaction* get_parent_or_owner() override;
      ::user::interaction* get_top_level_owner() override;
      
      //virtual bool is_host_top_level();

      //virtual ::user::frame* get_parent_frame() override;
      //virtual ::user::frame* get_owner_frame() override;


      //void clear_cache(bool bRecursive = true);


      //virtual ::user::frame * frame() override;
      //virtual ::user::frame * top_level_frame() override;


      void send_message_to_descendants(const ::atom & atom, wparam wParam = 0, lparam lParam = 0, bool bDeep = true, bool bOnlyPerm = false) override;

      void route_message_to_descendants(::message::message* pmessage) override;


      i32 get_descendant_level(::user::element * puserelement) override;


      //virtual bool is_descendant(const ::user::primitive * pinteraction, bool bIncludeSelf = false) override;

      ::oswindow GetParentHandle();

      ::user::interaction* get_focusable_descendant() override;

      virtual void show_control_bar(::user::control_bar * pcontrolbar);
      virtual void hide_control_bar(::user::control_bar * pcontrolbar);

      void RepositionBars(::u32 nIDFirst = 0, ::u32 nIDLast = 0xffff, ::atom idLeftOver = FIRST_PANE, ::u32 nFlag = reposDefault, ::rectangle_i32* prectParam = nullptr, const ::rectangle_i32& rectangleClient = nullptr, bool bStretch = true) override;

      virtual ::user::interaction* ChildWindowFromPoint(const ::point_i32& point) override;
      virtual ::user::interaction* ChildWindowFromPoint(const ::point_i32& point, ::u32 nFlags) override;

      virtual ::user::interaction* get_next_sibling_window() override;

      ::user::interaction * get_next_window(bool bIgnoreChildren = false, ::user::interaction * puiInteractionStop = nullptr) override;
      ::user::interaction * get_window(enum_next enext) override;

      ::user::interaction* GetLastActivePopup() override;

      bool is_message_only_window() override;

      void pre_subclass_window() override;

      void post_non_client_destroy() override;


      void default_message_handler(::message::message * pmessage) override;


      void message_handler(::message::message* pmessage) override;
      //virtual lresult message_handler(MESSAGE * pmessage) override;

      //virtual void GuieProc(::message::message* pmessage) override;

      //virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;


      //inline oswindow get_oswindow() const { return m_oswindow; }
      //virtual bool attach(::windowing::window * pwindow_New) override;
      ::oswindow detach_window() override;


      ::windowing::window * window() override;
      //virtual ::windowing::window * _window() override;

      virtual ::user::copydesk * copydesk();

      virtual void* get_os_data();


      virtual bool can_merge(::user::interaction* pinteraction);
      virtual bool merge(::user::interaction* pinteraction);


      //virtual void _001OnTriggerMouseInside() override;


      virtual bool window_is_notify_icon_enabled();
      virtual void set_context_org(::draw2d::graphics_pointer & pgraphics) override;


      virtual void viewport_screen_to_client(::point_i32 & point) override;
      virtual void viewport_client_to_screen(::point_i32 & point) override;
      virtual void viewport_client_to_screen(::rectangle_i32 & rect) override;
      virtual void viewport_screen_to_client(::rectangle_i32 & rect) override;


      virtual string get_window_default_matter() override;
      virtual string get_window_icon_matter() override;
      virtual u32 get_window_default_style() override;
      //virtual enum_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command* psimplecommand) override;
      virtual void on_command(::message::command* pcommand) override;


      virtual bool OnCommand(::message::message* pmessage) override;
      virtual bool OnNotify(::message::message* pmessage) override;
      virtual bool OnChildNotify(::message::message* pmessage) override;


      virtual bool is_selected(::data::item* pitem) override;

      //virtual ::pointer<place_holder>place_hold(::user::interaction* pinteraction) override;

#if defined(UNIVERSAL_WINDOWS) && defined(__cplusplus_winrt)
      static Agile<::winrt::Windows::UI::Core::CoreWindow>(*s_get_os_window)(interaction* pinteraction);
      Agile<::winrt::Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static Agile<::winrt::Windows::UI::Core::CoreWindow> get_os_window(interaction* pinteraction)
      {
         return (*s_get_os_window)(pinteraction);
      }
      static Agile<::winrt::Windows::UI::Core::CoreWindow> get_os_window_default(interaction* pinteraction)
      {
         __UNREFERENCED_PARAMETER(pinteraction);
         return nullptr;
      }
#endif

      //// <3ThomasBorregaardSørensen__!! (I need to suck you, and take care of you, both front and back and middle but it ought to be unexplored by else...)
      void handle_command(const ::atom& atom) override;

      virtual bool has_command_handler(::message::command* pcommand) override;



      //virtual void track_popup_menu(::user::menu_item* pitem, i32 iFlags, const ::point_i32& point) override;
      //virtual ::pointer<::user::menu>track_popup_xml_menu(const ::payload & varXml, i32 iFlags, const ::point_i32& pointScreen = nullptr, const ::size_i32& sizeMinimum = nullptr) override;

      bool _001OnBeforeEnterIconic() override;
      bool _001OnBeforeEnterNormal() override;
      bool _001OnBeforeEnterZoomed() override;
      bool _001OnBeforeEnterFullScreen() override;


      bool _001OnBeforeEnterAppearance() override;


      void _001OnAfterEnterIconic() override;
      void _001OnAfterEnterNormal() override;
      void _001OnAfterEnterZoomed() override;
      void _001OnAfterEnterFullScreen() override;


      void _001OnAfterEnterAppearance() override;


      bool _001OnBeforeExitIconic() override;
      bool _001OnBeforeExitNormal() override;
      bool _001OnBeforeExitZoomed() override;
      bool _001OnBeforeExitFullScreen() override;


      bool _001OnBeforeExitAppearance() override;


      void _001OnAfterExitIconic() override;
      void _001OnAfterExitNormal() override;
      void _001OnAfterExitZoomed() override;
      void _001OnAfterExitFullScreen() override;


      void _001OnAfterExitAppearance() override;


      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience) override;


      virtual void on_configuration_change(::user::primitive * pprimitiveSource) override;


      //virtual void show_keyboard(bool bShow = true) override;


      virtual void keep_alive(::object* pliveobject = nullptr) override;

      //virtual void move_to(const ::point_i32& point);
      //virtual void set_size(const ::size_i32& size);
      //virtual void move_to(i32 x, i32 y);
      //virtual void set_size(i32 cx, i32 cy);
      //virtual void set_dim(const ::point_i32& point, const ::size_i32& size);
      virtual void place(const ::rectangle_i32& rectangle, enum_layout elayout = e_layout_sketch);
      inline void set_placement(i32 x, i32 y, i32 cx, i32 cy, enum_layout elayout = e_layout_sketch)
      {
         
         place(::rectangle_i32_dimension(x, y, cx, cy));
         
      }
      virtual interaction& operator =(const ::rectangle_i32& rectangle);

      virtual void place_rate_or_size(const ::rectangle_f64 & rectangle);


      virtual void activation(::e_activation eactivation);


      virtual void display_child(const ::rectangle_i32 & rectangle);
      inline void display_child(::i32 x, ::i32 y, ::i32 cx, ::i32 cy)
      {

         display_child(rectangle_i32_dimension(x, y, cx, cy));

      }


      virtual ::user::interaction* best_top_level_parent(::rectangle_i32 & rectangle);

      //virtual void window_rectangle(::rectangle_i32 * prectangle) override;

      virtual index get_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_display edisplay);

      virtual ::e_display initial_restore_display();

      // returns less than zero if no preferred restore
      // otherwise returns the preferred restore 
      // rectangle and its monitor index
      virtual ::index get_preferred_restore(::rectangle_i32 & rectanglePreferredRestore);

      virtual bool calculate_window_rectangle_in_main_monitor(::rectangle_i32 & rectangle, const ::rectangle_f64 & rectangleOptionalRateOrSize);

      virtual index calculate_broad_and_compact_restore(::rectangle_i32 * prectWorkspace = nullptr, const ::size_i32 & sizeMin = nullptr, const ::rectangle_i32& rectangleHint = nullptr);

       //virtual void reset_window_state();

      virtual index make_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleHint = nullptr, bool bSet = false, ::e_display* pedisplay = nullptr, ::e_activation eactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index best_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleHint = nullptr, bool bSet = false, ::e_display* pedisplay = nullptr, ::e_activation eactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index best_monitor(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleHint = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index best_workspace(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleHint = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index good_restore(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleHint = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top, ::e_display edisplay = e_display_restore);
      virtual index good_iconify(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleHint = nullptr, bool bSet = false, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);

      virtual index good_move(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle = nullptr, ::e_activation eeactivation = e_activation_default, ::zorder zorder = e_zorder_top);
      virtual index get_best_zoneing(::e_display& edisplay, ::rectangle_i32* prectangle, const ::rectangle_i32& rectangleRequest = ::rectangle_i32(), bool bPreserveSize = false);
      virtual index get_best_workspace(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation = e_activation_default);


      virtual index get_best_monitor(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation = e_activation_default);


      virtual void get_rect_normal(::rectangle_i32* prectangle);


      virtual ::user::scroll_bar* get_horizontal_scroll_bar();
      virtual ::user::scroll_bar* get_vertical_scroll_bar();

      virtual ::user::scroll_data* get_horizontal_scroll_data();
      virtual ::user::scroll_data* get_vertical_scroll_data();


      virtual void set_context_offset_x(::draw2d::graphics_pointer & pgraphics, int x);
      virtual void set_context_offset_y(::draw2d::graphics_pointer & pgraphics, int y);
      virtual void set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y);
      virtual void offset_context_offset_x(::draw2d::graphics_pointer & pgraphics, int x);
      virtual void offset_context_offset_y(::draw2d::graphics_pointer & pgraphics, int y);
      virtual void offset_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y);
      virtual bool validate_context_offset(point_i32& point);
      virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics);
      virtual void on_context_offset(::draw2d::graphics_pointer & pgraphics);
      virtual ::point_i32 get_context_offset();
      virtual ::size_f64 get_total_size();
      virtual void on_change_impact_size(::draw2d::graphics_pointer & pgraphics);
      virtual ::size_f64 get_page_size();
      virtual void set_total_size(const ::size_f64& size);
      virtual void set_page_size(const ::size_f64& size);
      virtual ::point_i32 get_parent_accumulated_scroll(enum_layout elayout = e_layout_design);
      virtual ::point_i32 get_parent_context_offset();
      virtual ::point_i32 get_ascendant_context_offset();
      virtual void get_margin_rect(::rectangle_i32* prectMargin);

      virtual int get_final_x_scroll_bar_width();
      virtual int get_final_y_scroll_bar_width();


      virtual bool is_system_message_window();


      virtual ::size_i32 get_window_minimum_size();


      virtual void UpDownTargetAttach(::user::interaction* pupdown);
      virtual void UpDownTargetDetach(::user::interaction* pupdown);

      virtual bool OnUpDownTargetAttach(::user::interaction* pupdown);
      virtual bool OnUpDownTargetDetach(::user::interaction* pupdown);


      virtual string calc_window_class();


      virtual void user_interaction_on_destroy();
      virtual void user_interaction_on_hide();


      virtual void hide() override;






      virtual void on_erase_child(::user::interaction* pinteraction);
      virtual void on_erase_place_holder_child(::user::interaction* pinteraction);
      virtual void on_hide_child(::user::interaction* pinteraction);
      virtual void on_hide_place_holder_child(::user::interaction* pinteraction);


      void _001GetSel(strsize& iBeg, strsize& iEnd) override;

      
      virtual bool set_sel_by_name(const ::string & strName);
      virtual string get_sel_by_name();
      virtual string get_hover_by_name();
      virtual void ensure_sel_visible();
      
      
      virtual void set_sel_color(const ::color::hls & hls);
      virtual ::color::hls get_sel_color();
      

      virtual void get_horizontal_scroll_info(scroll_info& info);
      virtual void get_vertical_scroll_info(scroll_info& info);
      virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics);


      //void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void keyboard_focus_OnKeyDown(::message::message* pmessage) override;
      //void keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      //void keyboard_focus_OnChildKillFocus() override;

      virtual bool get_child(::pointer<::user::interaction> & pinteraction);
      virtual bool rget_child(::pointer<::user::interaction> & pinteraction);



      //template < typename CHILD >
      //inline ::pointer<CHILD>get_typed_child();

      template < typename CHILD >
      inline ::pointer<CHILD>get_typed_child()
      {

         CHILD * pchild = nullptr;

         if (!get_typed_child(pchild))
         {

            return {};

         }

         return pchild;

      }


      virtual enum_input_type preferred_input_type();

      //virtual ::user::primitive * get_keyboard_focus();
      //virtual void set_keyboard_focus(::user::primitive* pprimitive);
      //virtual void erase_keyboard_focus(::user::primitive * pprimitive);

      //virtual void erase_keyboard_focus() override;


      bool is_descendant_of(::user::element * puiAscendantCandidate, bool bIncludeSelf) override;
      bool is_ascendant_of(::user::element * puiDescendantCandidate, bool bIncludeSelf) override;

      bool is_descendant_of_or_owned_by(::user::element * puiAscendantCandidate, bool bIncludeSelf) override;
      bool is_ascendant_or_owner_of(::user::element * puiDescendantCandidate, bool bIncludeSelf) override;

      virtual void show_tooltip(const string& str, bool bError);

      virtual void layout_tooltip(bool bForceShow = false);

      virtual void hide_tooltip();

      virtual bool frame_is_transparent();

      virtual bool has_translucency();

      virtual double get_alpha();

      virtual string get_class_name() override;

#ifdef WINDOWS_DESKTOP

      virtual void _task_transparent_mouse_event();

#endif

      virtual void destruct() override;



      //virtual void mouse_hover_step(::message::mouse * pmouse);
      //virtual void mouse_hover_step(point_i32 & pointLast);

      //virtual void mouse_hover_move(bool& bPointInside, point_i32& pointLast);

      bool has_pending_graphical_update() override;

      virtual void enable_transparent_mouse_events(bool bEnable = true);

      virtual void check_transparent_mouse_events();


      virtual void redraw_add(::particle * pparticle);

      virtual void redraw_erase(::particle * pparticle);

      virtual bool has_redraw();

      virtual void on_after_graphical_update() override;


      virtual void _001OnDeiconify(::e_display edisplay);


      virtual ::e_status is_edit_delete_enabled();
      virtual bool on_edit_delete(const ::action_context& action_context);


      virtual bool on_click_generation(::item * pitem);
      virtual bool on_right_click_generation(::item * pitem);


      virtual bool on_click(::item * pitem);
      virtual bool on_right_click(::item * pitem);


      virtual int width();
      virtual int height();

      virtual int client_width();
      virtual int client_height();

      virtual ::size_f64 get_size();
      virtual ::size_f64 get_client_size();

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics);

      virtual void wait_redraw();

      virtual bool has_pending_redraw_flags() override;


      virtual void set_bitmap_source(const string & strBitmapFileTitle) override;
      virtual void clear_bitmap_source() override;


      //void install_click_default_mouse_handling(::channel* pchannel);
      //void install_hover_default_mouse_handling(::channel* pchannel);
      //void install_update_data_message_routing(::channel * pchannel);


      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_middle_button_up);


      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);


      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;
      virtual void edit_on_kill_focus(::user::interaction* pinteraction) override;


      virtual void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);


      virtual bool on_action(const ::string & pszId);

      bool keyboard_focus_is_focusable() override;

      //virtual bool simple_on_control_event(::message::message* pmessage, ::enum_topic etopic);

      ::item_pointer hit_test(::user::mouse * pmouse, e_zorder ezorder) override;

      //using ::aura::drawable::hit_test;
      ::item_pointer hit_test(const ::point_i32 & point, e_zorder ezorder) override;

      //using ::aura::drawable::on_hit_test;
      ::item_pointer on_hit_test(const ::point_i32 & point, e_zorder ezorder) override;


      virtual ::item_pointer on_items_hit_test(const ::point_i32& point, e_zorder ezorder);

      virtual ::item_pointer on_default_bottom_right_resize_hit_test(const ::point_i32& point, e_zorder ezorder);

      virtual ::item_pointer on_default_full_client_area_hit_test(const ::point_i32& point, e_zorder ezorder);

      //virtual bool update_hover(const ::point_i32 & point, bool bAvoidRedraw = true);
      virtual ::item_pointer update_hover(::user::mouse * pmouse, e_zorder ezorder);
      //virtual ::item_pointer update_hover(::user::mouse * pmouse, e_zorder ezorder);


      virtual bool is_mouse_hover() const;

      //virtual bool get_rectangle(::item * pitem);

      //inline auto rectangle(::item * pitem) { get_rect((::item *) pitem); return pitem->m_rectangle; }

      virtual void add_user_item(::item * pitem);

      virtual void _001DrawItems(::draw2d::graphics_pointer & pgraphics);


      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item * pitem, const ::user::e_state & estate);






      // control member function BEGIN
      //
      //
      //
      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //void create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;
      //virtual elayout get_state() override;
      //bool _003IsCustomMessage();
      //::user::primitive* _003GetCustomMessageWnd();
      //virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;
      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
      //virtual bool has_function(enum_control_function econtrolfunction);
      //virtual enum_control_type get_control_type();
      //virtual void _003CallCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pitem);
      //virtual bool _003CallCustomWindowProc(::pointer<::user::interaction>puserinteraction, const ::atom & atom, wparam wparam, lparam lparam, lresult& lresult);
      //virtual void _003OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pitem);
      //virtual void _003CustomWindowProc(::message::message* pmessage);
      //virtual form_list * get_form_list();
      //virtual bool _001IsPointInside(::point_i32 point) override;
      //control null() { return control(); }
      //bool Validate(string& str);
      bool get_data(::pointer<::user::interaction>puserinteraction, ::payload& payload);
      //void SetEditItem(index iItem);
      //void SetEditSubItem(index iItem);
      //index GetEditSubItem();
      // index GetEditItem();
      //virtual ::user::interaction * ControlExGetWnd();
      //using ::user::box::client_rectangle;
      //virtual bool client_rectangle(::rectangle_i32 * prectangle) override;
      //using ::user::box::window_rectangle;
      //virtual bool window_rectangle(::rectangle_i32 * prectangle) override;
      //bool operator == (const class ::user::control_descriptor& descriptor);
      //bool operator == (const class control& control);
      virtual bool IsControlCommandEnabled();
      virtual void EnableControlCommand(bool bEnable);
      //virtual void BaseControlExOnMouseMove(::u32 nFlags, const ::point_i32 & point);
      //virtual ::item_pointer on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;
      //DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      //DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(_001OnEnable);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditDelete);
      DECLARE_MESSAGE_HANDLER(_001OnEditDelete);
      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      //virtual void route(::topic * ptopic, ::context * pcontext) override;
      //virtual void on_notify_control_event(control_event* pevent) override;
      //void handle(::topic * ptopic, ::context * pcontext) override;
      //virtual bool simple_on_control_event(::message::message * pmessage, ::enum_topic etopic) override;
      //virtual void walk_pre_translate_tree(::message::message * pmessage,::pointer<::user::interaction>puiStop);
      //virtual bool get_element_rect(::rectangle_i32* prectangle, enum_element eelement);
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


      virtual void show_software_keyboard(::user::element * pelement) override;
      virtual void hide_software_keyboard(::user::element * pelement) override;


      virtual void set_stock_icon(enum_stock_icon eicon);
      virtual enum_stock_icon get_stock_icon();


      //virtual void post_procedure(const ::procedure & procedure) override;
      virtual void prodevian_post_procedure(const ::procedure & procedure);


      //void send_procedure(const ::procedure & procedure) override;


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
      void send_predicate(PRED pred, class ::time timeTimeout = ::time::infinite())
      {

         send_method(__routine(pred), timeTimeout);

      }*/

      //virtual void initial_frame_placement();

      //virtual bool _001FancyInitialFramePlacement(bool bForceRestore = false);

      //virtual bool _001FancyInitialFramePlacement(::rectangle_i32 * lprect, const rectangle_f64 & rectangleOptionalRateOrSize = {0., 0., 0., 0.});

      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;

      virtual point_i32 screen_origin(enum_layout elayout = e_layout_design);
      virtual point_i32 host_origin(enum_layout elayout = e_layout_design);


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _screen_to_client(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::size_i32(get_parent_accumulated_scroll(elayout)) - ::size_i32(screen_origin(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_screen(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::size_i32(screen_origin(elayout)) - ::size_i32(get_parent_accumulated_scroll(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _parent_to_client(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s - ::size_i32(m_layout.origin(elayout)); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_parent(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + ::size_i32(m_layout.origin(elayout)); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _host_to_client(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::size_i32(get_parent_accumulated_scroll(elayout)) - ::size_i32(host_origin(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_host(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::size_i32(host_origin(elayout)) - ::size_i32(get_parent_accumulated_scroll(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _host_to_client_no_scroll(OFFSETABLE& o, const SOURCE& s, enum_layout elayout = e_layout_design) const { o = s - ::size_i32(host_origin(elayout)); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_host_no_scroll(OFFSETABLE& o, const SOURCE& s, enum_layout elayout = e_layout_design) const { o = s + ::size_i32(host_origin(elayout)); }




      //template < typename OFFSETABLE >
      //inline void screen_to_client(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _screen_to_client(o, o); }


      //template < typename OFFSETABLE >
      //inline void client_to_screen(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _client_to_screen(o, o); }


      //template < typename OFFSETABLE >
      //inline void parent_to_client(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _parent_to_client(o, o); }


      //template < typename OFFSETABLE >
      //inline void client_to_parent(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _client_to_parent(o, o); }


      //template < typename OFFSETABLE >
      //inline void host_to_client(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _host_to_client(o, o); }


      //template < typename OFFSETABLE >
      //inline void client_to_host(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _client_to_host(o, o); }


      //template < typename OFFSETABLE >
      //inline void host_to_client_no_scroll(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _host_to_client_no_scroll(o, o); }


      //template < typename OFFSETABLE >
      //inline void client_to_host_no_scroll(OFFSETABLE& o, enum_layout elayout = e_layout_design) const { _client_to_host_no_scroll(o, o); }





      //template < typename GEOMETRY >
      //inline GEOMETRY _001ScreenToClient(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _screen_to_client(g, s); return g; }


      //template < typename GEOMETRY >
      //inline GEOMETRY _001ClientToScreen(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _client_to_screen(g, s); return g; }



      //template < typename GEOMETRY >
      //inline GEOMETRY _001ParentToClient(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _parent_to_client(g, s); return g; }


      //template < typename GEOMETRY >
      //inline GEOMETRY _001ClientToParent(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _client_to_parent(g, s); return g; }


      //template < typename GEOMETRY >
      //inline GEOMETRY _001HostToClient(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _host_to_client(g, s); return g; }


      //template < typename GEOMETRY >
      //inline GEOMETRY _001ClientToHost(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _client_to_host(g, s); return g; }

      
      virtual ::shift_i32 screen_to_client(enum_layout elayout = e_layout_design);
      virtual ::shift_i32 client_to_screen(enum_layout elayout = e_layout_design);
      virtual ::shift_i32 parent_to_client(enum_layout elayout = e_layout_design);
      virtual ::shift_i32 client_to_parent(enum_layout elayout = e_layout_design);
      virtual ::shift_i32 host_to_client(enum_layout elayout = e_layout_design);
      virtual ::shift_i32 client_to_host(enum_layout elayout = e_layout_design);


      //template < typename GEOMETRY >
      //inline GEOMETRY _001HostToClientNoScroll(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _host_to_client_no_scroll(g, s); return g; }


      //template < typename GEOMETRY >
      //inline GEOMETRY _001ClientToHostNoScroll(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _client_to_host_no_scroll(g, s); return g; }

      inline bool _001HasHorizontalBarDragScrolling() const { return m_pointBarDragScrollMax.x() > 0; }
      inline bool _001HasVerticalBarDragScrolling() const { return m_pointBarDragScrollMax.y() > 0; }
      
      
//      virtual void pick_single_file(
//         const ::array < ::pair < ::string, ::string > >& filetypes,
//         const ::function < void(const ::file::path &) >& function,
//         bool save);
//
//
//      virtual void pick_multiple_file(
//         const ::array < ::pair < ::string, ::string > > & filetypes,
//         const ::function < void(const ::file::path_array &) >& function);
//     
//      virtual void pick_single_folder(
//         //const ::array < ::pair < ::string, ::string > >& filetypes,
//                              const ::function < void(const ::file::path &) >& function);
//                              //,       bool save);

      
      


   };


   class control_cmd_ui : public ::message::command
   {
   public:


      id_to_id      m_mapControlCommand;


      control_cmd_ui();


      virtual void enable(bool bOn);
      virtual void SetCheck(i32 nCheck);
      virtual void SetText(const ::string & pszText);

      atom GetControlCommand(atom atom);

   };


   inline ::oswindow interaction::get_safe_oswindow()
   {

      if (::is_null(this))
      {

         return nullptr;

      }

      return this->oswindow();

   }


   //class lock_sketch_to_design
   //{
   //public:

   //   ::user::interaction * m_puserinteraction;

   //   lock_sketch_to_design(::user::interaction * puserinteraction) :
   //   m_puserinteraction(puserinteraction)
   //   {
   //      m_puserinteraction->m_bLockSketchToDesign = true;

   //   }
   //   ~lock_sketch_to_design()
   //   {

   //      m_puserinteraction->m_bLockSketchToDesign = false;

   //   }

   //};


   //compile_time_assert((offsetof(::user::interaction, m_oswindow) & 4) == 0);



} // namespace user






