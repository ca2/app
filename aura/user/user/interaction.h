#pragma once


#include "interaction_layout.h"
#include "drawable.h"
#include "scroll_state.h"
#include "acme/exception/status.h"
#include "acme/user/user/drag_client.h"
#include "acme/prototype/collection/string_map.h"
#include "acme/platform/timer_callback.h"
#include "acme/platform/flags.h"
#include "acme/prototype/geometry2d/shift.h"
#include "acme/prototype/time/frequency.h"
#include "acme/user/user/activation.h"
#include "acme/user/user/e_window_flag.h"
//#include "apex/database/key.h"
#include "apex/message/command.h"
#include "apex/user/user/interaction_base.h"


namespace user
{

   enum enum_keyboard_mode
   {

      e_keyboard_mode_none,
      e_keyboard_mode_reposition,
      e_keyboard_mode_resize,

   };


   struct set_need_redraw
   {

      ::int_rectangle_array_base      m_rectangleaNeedRedraw;
      function<void()>           m_function;
      bool                       m_bAscendants;

   };


#define for_user_interaction_children(puserinteraction, puserinteractionParent) \
   for ( \
   auto puserinteraction = (puserinteractionParent)->first_child(); \
   ::is_set(puserinteraction); \
   puserinteraction = (puserinteractionParent)->next_sibling(puserinteraction) \
      )


#define rear_for_user_interaction_children(puserinteraction, puserinteractionParent) \
   for ( \
   auto puserinteraction = (puserinteractionParent)->last_child(); \
   ::is_set(puserinteraction); \
   puserinteraction = (puserinteractionParent)->previous_sibling(puserinteraction) \
      )


   class CLASS_DECL_AURA interaction :
      virtual public ::user::interaction_base,
      virtual public ::user::drawable,
      virtual public ::timer_callback//,
      //virtual public ::user::drag_client
      //, virtual public ::graphics::output_purpose
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


      //::pointer < ::windowing::window >         m_pwindow;


      bool                                      m_bFocus : 1;
      bool                                      m_bDestroyOnHide : 1;
      bool                                      m_bTrackMouseLeave : 1;

      ::logic::boolean                          m_bExtendOnParent;
      ::logic::boolean                          m_bExtendOnParentIfOnlyClient;
      ::logic::boolean                          m_bExtendOnParentHostingArea;
      bool                                      m_bToolWindow;
      //bool                                      m_bMessageWindow;
      ::logic::boolean                          m_bLockGraphicalUpdate;

      e_interaction                             m_einteraction;

      e_element                                 m_eelementMain;

      bool                                      m_bCompositedFrameWindow;
      bool                                      m_bEdgeGestureDisableTouchWhenFullscreen;
      //bool                                      m_bScreenVisible;
      bool                                      m_bMouseHoverOnCapture;

      enum_keyboard_mode                        m_ekeyboardmode;
      ::int_size                                m_sizeInitialResizeOffset;
      //bool                                      m_bMouseHover;
      bool                                      m_bDefaultClickHandling;
      bool                                      m_bDefaultMouseHoverHandling;
      bool                                      m_bDefaultParentMouseMessageHandling;

      bool                                      m_bDefaultEditHandling;

      bool                                      m_bDefaultKeyboardMultipleSelectionHandling;
      bool                                      m_bDefaultDataUpdateHandling;
      bool                                      m_bParentScrollX;
      bool                                      m_bParentScrollY;

      bool                                      m_bUserInteractionHost;
      bool                                      m_bEnableDragClient;
      bool                                      m_bEnableDragResize;
      bool                                      m_bEnableDefaultControlBox;
      bool                                      m_bDerivedHeight;

      bool                                      m_bLadingToLayout;
      bool                                      m_bContextOffsetLadingToLayout;
      bool                                      m_bTransparent;
      bool                                      m_bCreated;
      bool                                      m_bSubclassed;
      
      bool                                      m_bClipRectangle;
      bool                                      m_bLayoutModified;
      bool                                      m_bCustomWindowProc;
      bool                                      m_bControlExCommandEnabled;

      bool                                      m_bUpdateBuffer; // internal offscreen buffer
      bool                                      m_bUpdateWindow; // window frame
      bool                                      m_bUpdateScreen; // screen buffer

      bool                                      m_bIdBound;
      bool                                      m_bOverdraw;
      bool                                      m_bFullScreen;
      bool                                      m_bModal;

      bool                                      m_bNeedRedraw;
      ::logic::boolean                          m_bNeedPerformLayout;
      bool                                      m_bNeedLayout;
      //bool                                      m_bNeedCheckChildrenLayout;
      bool                                      m_bReposition;
      bool                                      m_bUpdatingVisual;
      bool                                      m_bOnDraw;

      //bool                                      m_bUpdateVisual;
      bool                                      m_bMouseMovePending;
      bool                                      m_bNeedLoadFormData;
      bool                                      m_bNeedSaveFormData;

      bool                                      m_bWorkspaceFullScreen;
      bool                                      m_bHideOnTransparentFrame;
      bool                                      m_bOffScreenRender;
      bool                                      m_bMoveWindow;

      bool                                      m_bVoidPaint;
      bool                                      m_bRedrawing;
      bool                                      m_bRedrawOnVisible;
      bool                                      m_bSaveWindowRect;

      bool                                      m_bEnableSaveWindowRect2;
      bool                                      m_bShowSoftwareKeyboard;
      bool                                      m_bUserInteractionSetFinish;
      bool                                      m_bDefaultWalkPreTranslateParentTree;

      bool                                      m_bBackgroundBypass;
      bool                                      m_bSizeMove;
      bool                                      m_bCursorInside;
      bool                                      m_bRectOk;

      bool                                      m_bWfiUpDownTarget;
      bool                                      m_bPendingChildrenZorder;
      bool                                      m_bPadding001;
      bool                                      m_bPadding002;
      
      bool                                      m_bBarDragScrollLeftButtonDown;

      bool                                      m_bEnableHorizontalBarDragScroll;
      bool                                      m_bHorizontalBarDragScrollingActive;

      bool                                      m_bEnableVerticalBarDragScroll;
      bool                                      m_bVerticalBarDragScrollingActive;

      ::int_point                               m_pointBarDragScrollLeftButtonDown;
      ::int_point                               m_pointBarDragScroll;
      ::int_point                               m_pointBarDragScrollStart;
      ::int_point                               m_pointBarDragScrollMax;
      ::int_size                                m_sizeBarDragScroll;

      enum_text_wrap                            m_etextwrap;

      ::pointer<::user::interaction_scaler>     m_pinteractionScaler;

      bool                                      m_bUpdateBufferPending;

      //::oswindow                              m_oswindow;
      e_window_flag                             m_ewindowflag;
      bool                                      m_bAutomaticallyStoreWindowRectangle;
      bool                                      m_bPendingSaveWindowRectangle;
      bool                                      m_bLoadingWindowRectangle;


      ::int_rectangle                           m_rectangleMargin1;

::pointer < ::message::mouse > m_pmousePendingBackUpdateHover;
      ::draw2d::graphics * m_pgraphicsInternalPriority = nullptr;
      //bool                                      m_bVisualChanged;

      // <3ThomasBorreggardSoerensen_!!
      ::pointer<::matter>                       m_pmatterCommandHandler;

      ::user::interaction::enum_updown          m_eupdown;

      class ::time                              m_timeLastIgnoredSketchToLading;
      bool                                      m_bIgnoringSketchToLading;

   public:

      ::collection::index                                     m_iEditItem;
      ::collection::index                                     m_iEditSubItem;
      // index                                     m_iListItem;
      ::collection::index                                     m_iColumn;

      atom                                      m_uiText;
      ::platform::type                          m_type;
      atom                                      m_atomPrivateDataSection;
      //::atom                                  m_atomTranslated;
      enum_control_type                         m_econtroltype;

      enum_control_ddx                          m_eddx;
      ::string                                  m_strDataKey20;
      int                                       m_iDataValue;
      flags < enum_control_function >           m_flagsfunction;
      enum_control_data_type                    m_edatatype;
      ::int_rectangle                           m_rectangle;
      ::property_set                            m_setValue;
      int                                       m_iSubItemDisableCheckBox;
      int                                       m_iSubItemDuplicateCheckBox;
      ::int_array_base                               m_iaSubItemDuplicate;
      ::int_array_base                               m_iaSubItemDisable;

      string                                    m_strClass;
      string_to_string_base                          m_mapClassStyle;
      string                                    m_strStyle;
      ::property_set                            m_setStyle;

      //::user::interaction *                     m_puserinteractionTopLevel;
      //::user::frame_interaction *                           m_puserframeTopLevel;
      //::user::frame_interaction *                           m_puserframeParent;
      bool                                      m_bAutoResize;
      bool                                      m_bNeedAutoResizePerformLayout;


      ::double_rectangle                           m_rectangleClip;
      ::pointer<::aura::draw_context>           m_pdrawcontext;

      ::draw2d::path_pointer                    m_pathFocusRect1;
      ::draw2d::path_pointer                    m_pathFocusRect2;
      ::draw2d::path_pointer                    m_pathFocusRect3;
      ::draw2d::path_pointer                    m_pathFocusRect4;
      procedure                                 m_procedureOnAfterCreate;
      ::task_pointer                            m_ptaskTransparentMouseEvents;


      ::function < bool(::user::interaction *, ::item *, ::user::activation_token * puseractivationtoken) > m_callbackOnClick;

      
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

      string                                    m_strInteractionTag;

      ::collection::index                                   m_iIndex;
      ::int_rectangle                           m_rectangleRestoreBroad;
      ::int_rectangle                           m_rectangleRestoreCompact;
      enumeration < enum_non_client >           m_flagNonClient;
      class ::time                              m_timeLastRedraw;
      ::atom                                    m_atomImpact;
      ::status < ::color::color >               m_statuscolorBackground;
      ::status < ::color::color >               m_statuscolorText;
      //int_point                                 m_pointScroll;
      double                                    m_dItemHeight;
      int_point                                 m_pointMoveCursor;
      class ::time                              m_timeLastFullUpdate;
      class ::time                              m_timeLastVisualChange;
      string                                    m_strName;
      unsigned long long                                       m_uiUserInteractionFlags;
      ::pointer<::windowing::cursor>            m_pcursorDefault;
      string                                    m_strWindowText2;
      ::a_string_function                       m_astringfunctionWindowText;

      atom                                      m_atomModalResult; // for return values from interaction_impl::RunModalLoop
      int                                       m_nModalResult; // for return values from ::interaction_impl::RunModalLoop



      //interaction_draw2d *                    m_pinteractiondraw2d;

      /// The ::menu::item this user_interaction (window)
      /// represents (this window is a button [a menu button],
      /// this window is a m_pcheckbox [a menu m_pcheckbox],
      /// this window is a player/impact [a menu picture/video/chat?!])


      // references
      ::pointer<::file::insert_item>            m_pitemComposing;
      //::pointer<::thread>                       m_pthreadUserInteraction;
      ::pointer<::user::interaction>            m_puserinteractionParent;
      ::pointer<::user::interaction>            m_pupdowntarget;
      ::task_pointer                            m_ptaskModal;

      // ownership
      ::pointer<::user::system>                    m_pusersystem;
   protected:
      ::user::interaction_layout                   m_layout;
   public:
      //::pointer<drag_move>                       m_pdragmove;
      ::pointer<::draw2d::graphics_call_array>     m_pgraphicscalla;
      ::pointer<::user::interaction>               m_puserinteractionCustomWindowProc;
      ::pointer<::user::interaction>               m_puiLabel;
      ::pointer<::user::form>                      m_pform;
      ::pointer<alpha_source>                      m_palphasource;
      //::pointer<::aura::drawable>                m_pdrawableBackground;
      //::pointer<prototype_impl>                    m_pprimitiveimpl;
      //::pointer<interaction_impl>                  m_pinteractionimpl;
      ::pointer<interaction_array>                 m_puserinteractionpointeraOwned;
      //::pointer<interaction_array>                 m_puserinteractionpointeraChild;
      ::pointer<interaction>                       m_ptooltip;
      ::pointer<::object>                          m_pmenuitem;
      pointer_array < interaction >                m_menua;
      ::pointer<::appearance::appearance>          m_pappearance;
      bool                                         m_bEmptyAreaIsClientArea;
      ::enum_display                               m_edisplayOwnedBeforeHidden;
      //::item_pointer                               m_pitemClient;
      ::array < struct set_need_redraw >           m_setneedredrawa;
      ::logic::boolean                             m_bNeedFullRedrawOnResize;
      ::logic::boolean                             m_bLockSketchToDesign;


      interaction();
      ~interaction() override;

      void user_interaction_common_construct();

      //virtual void on_create_user_interaction();

      void on_initialize_particle() override;

      virtual bool is_branch_current() const override;


      bool is_ready_to_quit() const override;


      virtual void set_appearance(::appearance::appearance * pappearance);
      virtual ::appearance::appearance * get_appearance();


      virtual bool is_sandboxed();


      ::user::thread * user_thread();



      //class control_descriptor& descriptor();
      //const class control_descriptor& descriptor();
      // ::aura::application * get_app();
      // ::aura::session * get_session();
      // //::aura::system * system();
      // ::aura::context * context();


      ::user::interaction * user_interaction() override;

      bool _001CanEnterScreenSaver() override;

      virtual void _001Maximize();

      virtual void _001Restore();

      virtual void _001Minimize();

      virtual void on_display_restore(::user::activation_token * puseractivationtoken);

      virtual void on_display_task_list(::user::activation_token * puseractivationtoken);

      virtual void on_system_command(const ::e_system_command & esystemcommand);
      //void enable_drag_move();

//      virtual void set_restored_rectangle(const ::int_rectangle & rectangleRestored);

      /// <summary>
      ///  
      /// </summary>
      /// <param name="point"></param>
      /// <param name="elayout"></param>
      /// <param name="pgraphics"></param>
      /// <returns>true if position has changed</returns>
      virtual bool set_position(const ::int_point & point, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      /// <summary>
   /// 
   /// </summary>
   /// <param name="size"></param>
   /// <param name="elayout"></param>
   /// <param name="pgraphics"></param>
   /// <returns>true if size has changed</returns>
      virtual bool set_size(const ::int_size & size, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      virtual void _set_size(const ::int_size & size, enum_layout elayout = e_layout_sketch);
      virtual void set_width(int width, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      virtual void set_height(int height, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      /// @brief shift left position changing size
      /// @param left left position
      /// @param elayout elayout to change
      virtual void shift_left(int left, enum_layout elayout = e_layout_sketch, ::draw2d::graphics* pgraphics = nullptr);
      /// @brief  sets right position maintaining size
      /// @param right right position
      /// @param elayout elayout to change
      virtual void set_right(int right, enum_layout elayout = e_layout_sketch, ::draw2d::graphics* pgraphics = nullptr);

      /// @brief sets top position maintaining size
      /// @param top top position
      /// @param elayout elayout to change
      virtual void set_top(int top, enum_layout elayout = e_layout_sketch, ::draw2d::graphics* pgraphics = nullptr);
      
      virtual bool on_set_position(::int_point & point, enum_layout elayout);
      virtual bool on_set_size(::int_size & size, enum_layout elayout);

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


      //inline oswindow get_oswindow() const { return m_oswindow; }
      //virtual bool attach(::windowing::window * pwindow_New) override;
      ::oswindow detach_window() override;


      ::windowing::window * window() override;
      virtual ::windowing::window * _window();
      virtual void * get_os_data();

      ::windowing::windowing * windowing();

      virtual ::windowing::display * get_display();

      virtual ::user::interaction * get_host_user_interaction() override;

      //virtual ::windowing::window * get_host_user_interaction_impl();

      virtual ::user::enum_state get_user_state();

      virtual bool has_hover();

      virtual bool has_link();

      virtual pointer_array < ::acme::user::interaction > * children();


      inline iterator proper_children() { return {this, e_next_proper, this}; }


      const class ::user::interaction_layout& const_layout() const { return m_layout; }
      class ::user::interaction_layout& layout() { return m_layout; }

      virtual bool is_past_reposition_request(const ::int_point & point);
      virtual bool is_past_resizing_request(const ::int_size & size);

      double screen_scaler();
      double font_scaler();


      //void clear();
      void control_descriptor_common_construct();
      //bool operator == (const control_descriptor & control_descriptor);
      //control_descriptor & operator = (const control_descriptor & control_descriptor);
      virtual enum_control_type get_control_type() override;
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

      bool _is_set() const override;

      virtual bool is_user_thread();

      //virtual void interaction_send(const ::procedure & procedure);

      //virtual void interaction_post(const ::procedure & procedure) override;

      virtual void host_send(const ::procedure& procedure);

      void host_post(const ::procedure& procedure) override;

      void _user_send(const ::procedure & procedure) override;
      void _user_post(const ::procedure & procedure) override;

      void _main_send(const ::procedure & procedure) override;
      void _main_post(const ::procedure & procedure) override;

      //post_continuation main_async() override;

      //inline void fps_interest_on_show() { m_ewindowflag |= e_window_flag_fps_interest_on_show; }
      //inline void clear_fps_interest_on_show() { m_ewindowflag -= e_window_flag_fps_interest_on_show; }
      //inline bool is_fps_interest_on_show() { return m_ewindowflag & e_window_flag_fps_interest_on_show; }


      virtual void add(::graphics::output_purpose * poutputpurpose);
      virtual void erase(::graphics::output_purpose * poutputpurpose);
      virtual void add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose);
      virtual void erase_graphical_output_purpose(::particle * pparticle);
      //virtual ::graphics::enum_output_purpose most_demanding_graphical_output_purpose() const;
      virtual bool has_screen_output_purpose();
      virtual bool has_graphical_output_purpose();
      virtual bool has_fps_output_purpose();

//
//      inline void set_fps_interest() { return add_fps_interest(this); }
//      inline void clear_fps_interest() { return erase_fps_interest(this); }
//      inline bool is_fps_interest() const { return is_fps_interest(this); }
//
//
      void add_fps_interest(::particle * pparticle) override;
      void erase_fps_interest(::particle * pparticle) override;
      bool is_fps_interest(::particle * pparticle) override;
//      bool has_fps_interest() const noexcept;
//

      //inline void visual_changed() { m_ewindowflag |= e_window_flag_visual_changed; }
      //inline void clear_visual_changed() { m_ewindowflag -= e_window_flag_visual_changed; }
      //inline bool is_visual_changed()const { return m_ewindowflag & e_window_flag_visual_changed; }


      virtual bool is_ok();

      virtual string get_class_style(const ::scoped_string & scopedstrClass);
      virtual void set_class_style(const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrStyle);
      virtual void sync_style();
      virtual string get_full_style();
      virtual void load_style(const ::scoped_string & scopedstrStyle);


      virtual::e_display window_stored_display();
      virtual::e_display _window_previous_display();
      virtual::e_display window_previous_display();


      virtual void set_window_previous_display(::e_display edisplayPrevious);


      virtual int get_derived_height(int iWidth);
      virtual int get_derived_width(int iHeight);


      virtual bool is_full_screen_enabled();
      inline bool is_full_screen() { return m_bFullScreen; }
      virtual bool _is_full_screen();

      
      virtual bool get_element_rectangle(::int_rectangle & rectangle, enum_element eelement);
      
      
      virtual ::double_rectangle user_item_rectangle(::user::item * puseritem, ::user::enum_layout elayout);
      virtual ::double_rectangle _user_item_rectangle(::user::item * puseritem, ::user::enum_layout elayout);


      virtual status < int_rectangle > item_rectangle(::item * pitem, ::user::enum_layout elayout);
      virtual ::draw2d::path_pointer item_graphics_path(::item * pitem);


      virtual status < int_rectangle > rectangle(enum_element eelement)
      {

          ::int_rectangle rectangle;

          if (!get_element_rectangle(rectangle, eelement))
          {

              return ::error_failed;

          }

          return rectangle;

      }


      virtual enum_element get_default_element();
      virtual ::write_text::font_pointer get_font(::user::style * pstyle, enum_element eelement, ::user::enum_state estate = e_state_none);
      inline ::write_text::font_pointer get_font(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_font(pstyle, get_default_element(), estate); }
      virtual enum_translucency get_translucency(::user::style* pstyle);
      using ::user::interaction_base::get_int;
      virtual int get_int(::user::style* pstyle, enum_int eint, ::user::enum_state estate = e_state_none, int iDefault = 0);
      virtual double get_double(::user::style* pstyle, enum_double edouble, ::user::enum_state estate = e_state_none, double dDefault = 0.);
      virtual status < ::double_rectangle > get_border(::user::style* pstyle, enum_element eelement, ::user::enum_state estate = e_state_none);
      inline status < ::double_rectangle > get_border(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_border(pstyle, get_default_element(), estate); }
      virtual status < ::double_rectangle > get_padding(::user::style* pstyle, enum_element eelement, ::user::enum_state elayout = e_state_none);
      inline status < ::double_rectangle > get_padding(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_padding(pstyle, get_default_element(), estate); }
      virtual status < ::double_rectangle > get_margin(::user::style* pstyle, enum_element eelement, ::user::enum_state estate = e_state_none);
      inline status < ::double_rectangle > get_margin(::user::style* pstyle, ::user::enum_state estate = e_state_none) { return get_margin(pstyle, get_default_element(), estate); }
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
      virtual void create_window() override;
       virtual void _create_window() override;
      void create_window_object() override;
      void on_create_window_object() override;


      virtual ::pointer < ::user::thread > create_user_thread();
      virtual ::pointer < ::user::graphics_thread > create_user_graphics_thread();
//      virtual void create_graphics_thread();



      inline bool is_graphical() const { return !m_bMessageOnlyWindow && m_ewindowflag & e_window_flag_graphical; }


      virtual ::particle * mutex_draw();


      int_rectangle get_rectangle() override;



      //virtual bool AddControlBar(::user::control_bar* pcontrolbar);
      //virtual bool RemoveControlBar(::user::control_bar* pcontrolbar);

      virtual bool has_compulsory_window_manager_decorations();
      virtual bool should_show_platform_control_box();

      virtual bool should_inline_notify_context_menu();


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

      virtual void set_place_child_title(const ::scoped_string & scopedstrTitle);

      virtual ::user::interaction_base * get_bind_ui();

      virtual string get_display_tag();


      void on_set_finish() override;


      void destroy() override;
      void delete_this() override;
      virtual void hide_and_then_destroy();


      virtual void display_system_minimize();


      //void window_move(int x, int y) override;


      //auto fps_interest() { return øallocate ::fps_interest(this); }

      virtual bool should_save_window_rectangle();
      
      virtual bool FancyWindowDataLoadWindowRectangle(bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool WindowDataLoadWindowRectangle();
      virtual void WindowDataSaveWindowRectangle();

      virtual void on_defer_display();

      virtual bool display_lading_to_layout();
      virtual void layout_display();
      virtual void layout_appearance();
      virtual void layout_children_zorder();
      virtual void layout_reposition();
      virtual bool layout_layout(::draw2d::graphics_pointer & pgraphics);


      virtual void display_visible_trying_to_restore_last_visible(const ::user::activation & useractivation);
      virtual void display_strictly_previous(const ::user::activation & useractivation);
      virtual void display_stored_state();
      virtual void display_normal(::e_display edisplay, const ::user::activation & useractivation);
      virtual void display_docked(::e_display edisplay, const ::user::activation & useractivation);
      virtual void display_zoomed();
      virtual void display_iconic();
      virtual void display_full_screen(::collection::index iMonitor, const ::user::activation & useractivation);
      virtual void display_notify_icon();

      
      virtual void design_window_stored_state();
      virtual void design_window_iconic();
      virtual void design_window_minimize(const ::user::activation & useractivation) override;
      virtual void design_window_maximize() override;
      virtual void design_window_full_screen(const ::int_rectangle& rectangleHint = {}) override;
      virtual void design_window_normal(::e_display edisplay) override;
      virtual void design_window_dock(::e_display edisplay) override;


      virtual ::int_size preferred_size(::draw2d::graphics_pointer & pgraphics);


      virtual bool is_display_like_maximized();

      virtual bool is_display_like_full_screen();


      //virtual void graphics_thread_stop() override;

      //virtual void graphics_thread_redraw(bool bUpdateBuffer) override;

      //virtual void _001OnAfterAppearance();


      //virtual void constrain_window_boundaries(::int_rectangle& rectangleRequest);
      ::property_object * parent_property_set_holder() const override;


      float preferred_dpi_x() override;
      float preferred_dpi_y() override;
      float preferred_density() override;

      
      virtual void add_appearance(::e_appearance eappearance, enum_layout elayout = e_layout_sketch);
      virtual void erase_appearance(::e_appearance eappearance, enum_layout elayout = e_layout_sketch);
      virtual void toggle_appearance(::e_appearance eappearance, enum_layout elayout = e_layout_sketch);


      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);
      virtual void set_need_perform_layout();
      virtual void set_need_layout();
      virtual void set_recalculate_clip_rectangle();
      //void set_need_layout() { m_bNeedLayout = true; }
      void set_need_redraw(const ::int_rectangle_array_base& rectangleNeedRedraw = {}, ::draw2d::graphics * pgraphics = nullptr, ::function < void() > function= nullptr, bool bAscendants = true) override;
      virtual bool needs_to_draw(::draw2d::graphics * pgraphics, const ::int_rectangle& rectangleNeedsToDraw = {});
      virtual void set_need_load_form_data() override;
      virtual void set_need_save_form_data() override;
      //virtual bool commit_sketch();
      virtual void post_redraw(bool bAscendants = true) override;
      virtual bool should_redraw_on_mouse_activate();
      virtual bool should_redraw_on_mouse_hover();
      virtual bool should_redraw_on_hover(::item * pitem);
      //virtual void show_window();


      ///virtual bool is_sketch_to_design_locked();

      
      virtual void reset_pending(enum_layout elayout = e_layout_sketch);

      virtual void set_impact_update_going_on(enum_layout elayout = e_layout_sketch);

      virtual void set_display(::e_display edisplay, enum_layout elayout = e_layout_sketch);
      
      virtual void set_layout_state(const layout_state & state, enum_layout elayout = e_layout_sketch);

      virtual void set_activation(const ::user::activation & useractivation, enum_layout elayout = e_layout_sketch);

      virtual void display(::e_display edisplay = e_display_normal, const ::user::activation & useractivation = {}) override;


      virtual void sort_children_by_zorder(::user::interaction_array & interactiona);

      virtual ::collection::index child_zorder(::user::interaction * puserinteraction);

      virtual bool check_children_zorder();

      virtual ::zorder zorder(enum_layout elayout = e_layout_design);
      virtual void order(::zorder zorder);

      inline void order_top() { order(e_zorder_top); }
      inline void order_front() { order(e_zorder_top); }
      inline void order_top_most() { order(e_zorder_top_most); }
      inline void order_bottom() { order(e_zorder_bottom); }


      //virtual void sketch_to_design(::draw2d::graphics_pointer & pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void sketch_to_lading();
      virtual void lading_to_layout(bool & bUpdateBuffer, bool & bUpdateWindow);
      virtual void layout_to_design();
      virtual void _001UpdateWindow() override;
      //virtual void window_apply_visual(const class layout_state& windowstate) override;


      virtual void frame_experience_restore(const ::user::activation & useractivation = {});
      
      virtual ::user::notify_icon * notify_icon();

      virtual void on_update_notify_icon_menu(::collection::index & iNotifyIconIndex);
      
      virtual void on_app_activated(::user::activation_token * puseractivationtoken);

      virtual void frame_restore(::user::activation_token * puseractivationtoken);

      virtual void frame_occlude();
      
      virtual void frame_toggle_restore(::user::activation_token * puseractivationtoken, bool bDisplayPreviousOnRestore = false);
      
      virtual void display_previous_restore();

      // Client Rect : e_layout_design : Design/_001OnDraw time
      virtual void input_client_rectangle(::int_rectangle & rect, enum_layout elayout = e_layout_design);

      //virtual void raw_rectangle(::int_rectangle & rect, enum_layout elayout = e_layout_design);
      virtual ::int_rectangle raw_rectangle(enum_layout elayout = e_layout_design);

      //virtual void this->rectangle(::int_rectangle & rect, enum_layout elayout = e_layout_design);
      virtual ::int_rectangle rectangle(enum_layout elayout = e_layout_design);
      virtual ::int_rectangle client2_rectangle(enum_layout elayout = e_layout_design);
      virtual ::int_rectangle hosting_rectangle(enum_layout elayout = e_layout_design);
      virtual ::int_rectangle host_rectangle(enum_layout elayout = e_layout_design);
      virtual ::int_rectangle screen_rectangle(enum_layout elayout = e_layout_design);



      virtual ::int_rectangle parent_client_rectangle(enum_layout elayout = e_layout_design);
      virtual ::int_point position(enum_layout elayout = e_layout_design);
      virtual ::int_size size(enum_layout elayout = e_layout_design);
      virtual int top(enum_layout elayout = e_layout_design);
      virtual int left(enum_layout elayout = e_layout_design);
      virtual int right(enum_layout elayout = e_layout_design);
      virtual int bottom(enum_layout elayout = e_layout_design);


      virtual void window_rectangle(::int_rectangle & rect, enum_layout elayout = e_layout_design);
      virtual ::int_rectangle window_rectangle(enum_layout elayout = e_layout_design);

      virtual ::int_rectangle outer_frame();


      virtual bool is_frame_window();
      virtual bool is_impact();
      virtual bool is_menu() const;
      bool is_this_visible(enum_layout elayout = e_layout_design) override;
      //bool is_this_screen_visible() override;
      virtual bool should_draw();

//      virtual bool is_there_graphics_output_interest() const;

      virtual bool sketch_on_display();


      //bool is_this_visible(enum_layout elayout = e_layout_design);
      bool is_this_screen_visible(enum_layout elayout = e_layout_design);

      bool is_window_visible(enum_layout elayout = e_layout_design);
      bool is_window_screen_visible(enum_layout elayout = e_layout_design);

      virtual void user_mouse_initialize_cursor(::user::mouse* pmouse, ::windowing::cursor* pcursor);
      virtual void user_mouse_set_cursor(::user::mouse* pmouse, ::windowing::cursor* pcursor);
      virtual ::windowing::cursor* user_mouse_get_cursor(::user::mouse* pmouse);


      virtual void route_as_parent_mouse_message(::message::mouse * pmouse);
      virtual bool on_mouse_message(::message::mouse * pmouse);

      virtual bool on_child_from_point_mouse_message_routing(::message::mouse * pmouse);

      virtual void create_message_queue(const ::scoped_string & scopedstrName) override;

      virtual ::pointer<::message::message>get_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, ::user::enum_message_prototype eprototype = ::user::e_message_prototype_none) override;

      virtual bool has_text_input();

      virtual void kick_queue();

      virtual bool contains_user_interaction(::user::interaction* pinteraction, bool bRecursive = true);


      virtual void on_select() override;

      virtual bool is_place_holder() override;

      virtual ::frequency get_output_per_second();




      inline void defer_graphics(::draw2d::graphics_pointer & pgraphics)
      {

         if (!pgraphics) pgraphics = create_memory_graphics();

      }

      virtual ::draw2d::graphics_pointer create_memory_graphics();


      virtual double _001GetDefaultFontHeight(::draw2d::graphics_pointer & pgraphics);

      //virtual void set_cursor(enum_cursor ecursor) override;


      void set_default_mouse_cursor(::windowing::cursor * pcursor) override;


      //virtual ::int_point get_cursor_position() override;


      virtual bool is_left_button_pressed();


      virtual void set_current_item(::item * pitem, const ::action_context & action_context);
      virtual ::item_pointer current_item();


      //virtual ::item_pointer stock_item(::enum_element eelement);


      //virtual ::item_pointer hover_item();


      virtual bool _is_window() const override;
      inline bool is_window() const { return (m_ewindowflag & e_window_flag_is_window)
         && (m_ewindowflag & e_window_flag_window_created); }

      virtual void ExitHelpMode();

      //virtual int get_window_long(int nIndex) override;
      //virtual int set_window_long(int nIndex, int lValue) override;

      //virtual iptr get_window_long_ptr(int nIndex) override;
      //virtual void set_window_long_ptr(int nIndex, iptr lValue) override;

      virtual bool on_before_set_parent(::user::interaction_base * pinterface);
      virtual bool on_set_parent(::user::interaction_base * pinterface);
      virtual bool on_add_child(::user::interaction * puserinteractionChild);
      virtual void on_after_set_parent();


      virtual bool on_set_owner(::user::interaction_base * pinterface);


      ::user::element * first_child_user_element() override;
      ::user::element * top_user_element() override;
      ::user::element * under_user_element() override;
      ::user::element * above_user_element() override;
      ::user::element * next_user_element() override;
      ::user::element * previous_user_element() override;


      virtual ::particle * children_synchronization();


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

      virtual int get_wheel_scroll_delta();

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

         for (auto & pacmeuserinteraction : *puserinteractionpointeraChild)
         {

            ::cast < ::user::interaction> pinteraction = pacmeuserinteraction;

            if (::is_null(pinteraction))
            {

               continue;

            }

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
      inline bool get_typed_child(CHILD *& pchild, int iLevel = -1, ::user::interaction * puiExclude = nullptr)
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

            for (auto & pacmeuserinteraction : *puserinteractionpointeraChild)
            {

               ::cast < ::user::interaction > pinteraction = pacmeuserinteraction;

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
      //virtual atom   run_modal_loop(::user::interaction* pinteraction, unsigned int dwFlags = 0) override;
      //virtual atom   RunModalLoop(unsigned int dwFlags = 0) override;
      //virtual atom   _001RunModalLoop(unsigned int dwFlags = 0) override;
      //virtual bool ContinueModal() override;
      //virtual void EndModalLoop(atom nResult) override;


      void update_data(bool bSaveAndValidate = true) override;


      virtual ::user::interaction* get_os_focus_uie();


      virtual bool pre_message_handler(::message::key*& puserkey, bool& bKeyMessage, ::message::message* pmessage);


      //virtual void on_set_keyboard_focus() override;
      //virtual void on_kill_keyboard_focus() override;


      ::user::element * get_keyboard_focus() override;


      element * keyboard_set_focus_next(bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      //virtual prototype * keyboard_set_focus_next(prototype * pfocus = nullptr, bool bSkipChild = false, bool bSkipSiblings = false, bool bSkipParent = false) override;
      

      virtual void get_child_rect(::int_rectangle & rectangle);

      inline auto get_child_rect() { ::int_rectangle rectangle(no_initialize_t{}); get_child_rect(rectangle); return rectangle; }

      virtual bool scroll_bar_get_client_rect(::int_rectangle & rectangle);


      virtual ::double_size get_fitting_size(::draw2d::graphics_pointer & pgraphics);
      virtual ::double_size get_adjusted_fitting_size(::draw2d::graphics_pointer & pgraphics);
      virtual ::double_size get_preferred_size(::draw2d::graphics_pointer & pgraphics);
      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics);


      virtual void _extend_on_parent(::draw2d::graphics_pointer & pgraphics);
      virtual void _extend_on_parent_hosting_area(::draw2d::graphics_pointer & pgraphics);


      virtual void top_down_prefix();
      virtual bool should_perform_layout(::draw2d::graphics_pointer & pgraphics);
      virtual bool need_on_perform_layout(::draw2d::graphics_pointer & pgraphics);
      /// returns true if parent may need to perform layout
      /// the parent may need to perform layout if
      ///    - during perform_layout the position and/or size of
      ///      the user::interaction has changed.
      virtual bool perform_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics);
      /// returns true if parent may need to perform layout
      /// the parent may need to perform layout if
      ///    - during on_perform_layout the position and/or size of
      ///      the user::interaction has changed.
      virtual bool on_perform_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_items_layout(::draw2d::graphics_pointer & pgraphics, ::collection::index iIdContainer, ::item_array * pitema);
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      virtual void on_reposition() override;
      //virtual void on_show_window() override;
      virtual void _on_show_window();
      
      virtual void on_drag_scroll_layout(::draw2d::graphics_pointer & pgraphics);

      //virtual void _window_show_change_visibility_locked();
      //virtual void _window_show_change_visibility_unlocked();
      //virtual void _window_request_presentation_locked();
      //virtual void _window_request_presentation_unlocked();
      //virtual void on_configure_notifyvisual_applied();
      virtual void _on_configure_notify_unlocked(const ::int_rectangle & rectangle);
      virtual void _on_reposition_notify_unlocked(const ::int_point & point);


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
      virtual void create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom = nullptr);

      //virtual void create_host(enum_parallelization eparallelization) override;
      //virtual void create_host();
      virtual void create_child(::user::interaction * pparent) override;
      virtual bool _create_child(::user::interaction * puserinteractionParent);
      virtual void defer_create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom = nullptr);

      virtual void create_control(::user::interaction * puserinteractionParent, const ::atom & atom);
      ////void create_host(enum_parallelization eparallelization) override;
      //void create_host() override;
      //void create_child(::user::interaction * puserinteractionParent) override;
      //void create_control(::user::interaction * puserinteractionParent, const ::atom & atom) override;

      
      virtual void on_finished_window_creation();
      
      
      /// returns true if set_need_redraw was posted
      virtual bool defer_post_pending_set_need_redraw();
      
      /// returns true if set_need_redraw was posted
      virtual bool post_pending_set_need_redraw();

      // virtual bool create_interaction(const ::scoped_string & scopedstrClassName, const ::scoped_string & scopedstrWindowName, unsigned int uStyle, ::user::interaction * puiParent, ::request * prequest = nullptr) override;

      //virtual bool create_window_ex(::pointer<::user::system>pcs, ::user::interaction* puiParent = nullptr, const ::atom& atom = ::atom()) override;
      //enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      //virtual void CalcWindowRect(::int_rectangle* pClientRect, unsigned int nAdjustType = adjustBorder) override;


      virtual bool IsTopParentActive();
      virtual void ActivateTopParent() override;



      //virtual void start_destroying_window() override;

      virtual void destroy_window() override;

      virtual void _destroy_window();

      virtual void destroy_children();

      //virtual void set_children_to_destroy_unlocked();

      //virtual void erase_children();
      virtual void destroy_child(::user::interaction * puserinteraction);


      //virtual void on_finish() override;

      //virtual void set_finish_composites(::property_object* pcontextobjectFinish) override;

      void on_destroy() override;

      //void destroy() override;

      void notify_on_destroy(::property_object* pcontextobjectFinish) override;

      //virtual void destroy() override;


//#ifdef WINDOWS
//
//      virtual void RedrawWindow(const ::int_rectangle& rectangleUpdate = nullptr,
//         ::draw2d::region* prgnUpdate = nullptr,
//         unsigned int flags = RDW_INVALIDATE | RDW_ERASE) override;
//
//#else

      virtual void RedrawWindow(const ::int_rectangle& rectangleUpdate = {},
         ::draw2d::region* prgnUpdate = nullptr,
         unsigned int flags = 0);

//#endif


      virtual void register_drop_target();




      //virtual void UpdateWindow() override;
      //virtual void SetRedraw(bool bRedraw = true) override;
      //virtual bool GetUpdateRect(::int_rectangle* prectangle, bool bErase = false) override;

      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      //virtual void Invalidate(bool bErase = true) override;
      //virtual void InvalidateRect(const ::int_rectangle& rectangle, bool bErase = true);

      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const ::int_rectangle& rectangle);

      //virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual void ShowOwnedPopups(bool bShow = true);


      virtual bool is_composite() override;

      //virtual unsigned int GetStyle() override;
      //virtual unsigned int GetExStyle() override;
      //virtual void ModifyStyle(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags = 0) override;
      //virtual void ModifyStyleEx(unsigned int dwRemove, unsigned int dwAdd, unsigned int nFlags = 0) override;

      void post_message(::message::message* pmessage) override;
      
      lresult send_message(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}, const ::int_point & point = {}) override;
      lresult send_message(::message::message* pmessage) override;

      //virtual lresult send_create_message();

      lresult message_call(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}, const ::int_point & point = {}) override;
      lresult message_call(::message::message * pmessage) override;

      
      void on_message(::message::message * pmessage) override;
      

#ifdef LINUX

      lresult send_x11_event(void* phappening) override; // XEvent *

#endif

      lresult message_handler(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}) override;

      virtual lresult call_route_message(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {});

      virtual void on_default_window_procedure(::message::message * pmessage);

      void post_message(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}) override;

      virtual void post_object(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {});


      //virtual void user_post(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}) override;

      //virtual void SetWindowDisplayChanged() override;


      //virtual void call_and_set_timer(uptr uEvent, const class time& timeElapse, const ::procedure& procedure = {}, bool bPeriodic = true);
      void set_timer(uptr uEvent, const class time& timeElapse, const ::procedure& procedure = {}, bool bPeriodic = true) override;
      //virtual void set_timer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void* pdata = nullptr) override;
      //virtual void kill_timer(uptr uEvent) override;

//      virtual void enable_window(bool bEnable = true) override;


      virtual ::user::drawable * get_drawable();

      //virtual void process_queue(::draw2d::graphics_pointer & pgraphics);

      //virtual void do_graphics(::draw2d::graphics_pointer & pgraphics);
      //virtual void on_graphics(::draw2d::graphics_pointer & pgraphics);


      virtual void defer_do_graphics(::draw2d::graphics_pointer & pgraphics);
      virtual void defer_do_layout(::draw2d::graphics_pointer & pgraphics);
      void _000TopCallOnLayout(::draw2d::graphics_pointer& pgraphics);
      void _000TopCallOnDraw(::draw2d::graphics_pointer & pgraphics);
      void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _000OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) ;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) ;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _008CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnTopNcClip(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnNcClip(::draw2d::graphics_pointer& pgraphics);
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) ;



      virtual bool is_custom_draw();

      virtual void design_to_window();

      virtual atom GetDlgCtrlId() const override;
      virtual atom SetDlgCtrlId(const ::atom & atom) override;

//#ifdef WINDOWS_DESKTOP
//
//      virtual void open_clipboard() override;
//      virtual void close_clipboard() override;
//
//#endif

      virtual bool is_active_window();


      virtual ::pointer<::windowing::cursor>get_mouse_cursor(enum_cursor ecursor);
      virtual ::windowing::cursor * get_mouse_cursor() override;

      virtual ::int_point absolute_mouse_cursor_position();
      virtual ::int_point host_mouse_cursor_position();
      virtual ::int_point mouse_cursor_position();
      //virtual void set_cursor_position(const ::int_point & pointCursor);

      bool has_mouse_capture() override;
      void set_mouse_capture() override;
      bool defer_release_mouse_capture() override;


      //virtual bool has_keyboard_focus();
      virtual bool should_show_keyboard_focus();
      void set_keyboard_focus() override;
      //void clear_keyboard_focus() override;
      //void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr) override;
      virtual void on_set_keyboard_focus();
      virtual void on_kill_keyboard_focus();


      virtual void set_foreground_window(::user::activation_token * puseractivationtoken);
      virtual void set_active_window();

      virtual void bring_to_front();

      virtual bool is_window_enabled();
      inline bool is_this_window_enabled()  { return m_ewindowflag.is(e_window_flag_enable); }
      void enable_window(bool bEnable = true) override;

      //virtual void on_calc_size(calc_size* pcalcsize);

      virtual void walk_pre_translate_tree(::message::message* pmessage, ::user::interaction* puiStop = nullptr);


      virtual bool edit_undo();


      virtual void edit_on_text(const ::scoped_string & scopedstr) override;
      virtual void edit_on_sel(character_count iBeg, character_count iEnd) override;

      //void get_text_composition_area(::int_rectangle & r) override;
      virtual void on_text_composition(const ::scoped_string & scopedstr) override;
      virtual void on_text_composition_done() override;

      //void is_text_composition_active() override;

      virtual int on_text_composition_message(int iMessage);

      void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext) override;
      //void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) override;
      virtual void get_text_composition_area(::int_rectangle & rectangle);


      virtual void set_window_text(const ::scoped_string & scopedstrString) override;
      virtual void set_window_text_source(const ::a_string_function & astringfunction) override;
      virtual void clear_window_text_source();

      virtual void on_set_window_text();

//#ifdef WINDOWS
//      character_count _009GetWindowText(wchar_t * pwsz, int n) override;
//#else
//      character_count _009GetWindowText(char * psz, int n) override;
//#endif
//      virtual character_count _009GetWindowTextLength() override;

      //virtual character_count get_window_text(char* pszStringBuf, character_count nMaxCount) override;

      //virtual ::string _get_window_text();
      virtual string get_window_text() override;
      //virtual void get_window_text(string& rectangleString) override;
      //virtual character_count get_window_text_length() override;

      virtual ::user::frame_interaction* frame();
      virtual ::user::interaction * top_level();
      virtual ::user::frame_interaction * top_level_frame();
      virtual ::user::frame_interaction * parent_frame();
      virtual ::user::frame_interaction* get_owner_frame();
      virtual ::user::interaction* top_owner();

      ::user::interaction * _top_level() override;
      virtual ::user::frame_interaction * _top_level_frame();
      virtual ::user::frame_interaction * _parent_frame();
      virtual ::user::interaction* _top_owner();


      //virtual ::handler* get_user_callback();

      virtual void defer_set_icon();

      virtual void set_windowing_icon(::windowing::icon* picon);

      virtual ::windowing::icon* get_windowing_icon();
      virtual ::image::icon* get_draw_icon();



      //virtual void set_cursor(::windowing::cursor* pcursor);

      ::graphics::graphics* get_window_graphics() override;

      virtual ::draw2d::graphics_pointer get_internal_draw2d_graphics();

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
      virtual ::oswindow oswindow();


      //virtual ::windowing::window * window();


      //virtual void RedrawWindow(const ::int_rectangle& rectangleUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr, unsigned int flags = 0);
      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      ////      virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const ::int_rectangle& rectangle, bool bErase = true);

      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const ::int_rectangle& rectangle);

      //virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual void ShowOwnedPopups(bool bShow = true);


      //virtual void route(::topic * ptopic, ::handler_context * phandlercontext);
      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      /*void pre_create_window(::user::system* pusersystem);*/
      using ::user::interaction_base::handle;
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      void on_after_impact_update() override;


      virtual void install_message_routing(::channel* pchannel) override;
      virtual void prio_install_message_routing(::channel* pchannel);


      virtual void _000OnMouseLeave(::message::message* pmessage) override;

      //virtual void _000OnMouse(::message::mouse* pmouse);
      //virtual void _000OnThisMouse(::message::mouse* pmouse);
      //virtual void _000OnChildrenMouse(::message::mouse* pmouse);
      virtual void _000OnKey(::message::key* pkey);
      virtual void _000OnDrag(::message::drag_and_drop* pdrag);

      

      DECLARE_MESSAGE_HANDLER(on_message_parent_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_parent_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_parent_mouse_move);

      
      virtual void on_message_left_button_down_handle_keyboard_focus(::message::message * pmessage);
      
      
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
      bool on_drag_start(::int_point & pointStart, ::user::mouse * pmouse, ::item * pitem) override;
      ::int_point drag_mouse_cursor_position(::item* pitem, const ::int_point & point) override;
      bool drag_shift(::item * pitem, ::user::mouse * pmouse) override;
      //virtual bool on_drag_shift_element_client(::item * pitem, ::user::mouse * pmouse);
      bool drag_hover(::item * pitem) override;
      void drag_release_capture() override;
      void drag_set_cursor(::item * pitem, ::user::mouse * pmouse) override;

      
      virtual void set_text_and_selection(const ::scoped_string & scopedstr, character_count iSelStart, character_count iSelEnd, const ::action_context & actioncontext);

      //virtual void on_size_change_request(const ::int_rectangle & rectanglePrevious);

      //void on_timer(::timer* ptimer) override;
      void on_timer(::timer* ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_character);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_destroy);
      //DECLARE_MESSAGE_HANDLER(on_message_user_post);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_reposition);
      DECLARE_MESSAGE_HANDLER(on_message_prio_create);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_after_create);
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


      bool _001IsPointInside(const ::int_point & point) override;

      virtual bool _001IsPointInsideInline(const ::int_point & point, enum_layout elayout = e_layout_design);
      virtual bool _001IsClientPointInsideInline(const ::int_point & point);
      virtual bool _001IsParentClientPointInsideInline(const ::int_point & point, enum_layout elayout = e_layout_design);

      ::user::interaction* _001FromPoint(::int_point point, bool bTestedIfParentVisible = false) override;

      void OnLinkClick(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTarget = nullptr) override;

      void pre_translate_message(::message::message* pmessage) override;


      ::user::interaction * get_child_by_name(const ::scoped_string & scopedstrName, ::collection::index iItem = -1, int iLevel = -1) override;
      ::user::interaction * get_child_by_id(const atom & atom, ::collection::index iItem = -1, int iLevel = -1) override;
      ::user::element * get_primitive_by_id(const atom & atom, ::collection::index iItem, int iLevel) override;

      
      ::user::interaction* child_from_point(const ::int_point& point, int iLevel = -1, const ::user::interaction_array * pinteractionaExclude = nullptr);
      ::user::interaction * _child_from_point(const ::int_point & point, const ::user::interaction_array * pinteractionaExclude = nullptr);


      bool is_ascendant(element * puiIsAscendant, bool bIncludeSelf) override;
      bool is_parent(element * puiIsParent) override;
      bool is_child(element * puiIsChild)  override;
      bool is_descendant(element * puiIsDescendant, bool bIncludeSelf) override;

      virtual bool is_ascendant(::user::controller * pcontroller, bool bIncludeSelf) ;
      virtual bool contains(element* puiIsChild) ;

      virtual bool recursively_contains(element* puiIsChild, bool bIncludeSelf);

      ::user::interaction* get_wnd() override;
      ::user::interaction* get_wnd(unsigned int nCmd) override;

      ::user::interaction_base * set_parent(::user::interaction_base * pinteraction) override;
      ::user::interaction_base * set_owner(::user::interaction_base * pinteraction) override;

      //virtual void __defer_set_owner_to_impl();

      void on_add_owned(::user::interaction_base * pprimitive) override;

      //::user::interaction * get_parent_window() override;

      ::user::interaction * get_first_child_window() override;


      inline bool is_hosted() const { return m_ewindowflag & e_window_flag_hosted; }
      inline bool is_top_level() const  { return m_ewindowflag & e_window_flag_top_level; }
      inline bool is_root() const  { return m_ewindowflag & e_window_flag_root; }

      bool is_host_top_level() override;


      bool task_get_run() const override;

      ::user::element * get_parent_primitive() override;

      ::user::interaction* get_parent() override;
      ::user::interaction* get_owner() override;
      ::user::interaction* get_parent_owner() override;
      ::user::interaction* get_parent_or_owner() override;
      ::user::interaction* get_top_level_owner() override;
      

      ::user::interaction * owner_interaction();
      ::windowing::window * owner_window();


      //virtual bool is_host_top_level();

      //virtual ::user::frame_interaction* get_parent_frame() override;
      //virtual ::user::frame_interaction* get_owner_frame() override;


      //void clear_cache(bool bRecursive = true);


      //virtual ::user::frame_interaction * frame() override;
      //virtual ::user::frame_interaction * top_level_frame() override;


      void send_message_to_descendants(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {}, bool bDeep = true, bool bOnlyPerm = false) override;

      void route_message_to_descendants(::message::message* pmessage) override;


      int get_descendant_level(::user::element * puserelement) override;


      //virtual bool is_descendant(const ::user::interaction_base * pinteraction, bool bIncludeSelf = false) override;

      ::oswindow GetParentHandle();

      ::user::interaction* get_focusable_descendant() override;

      virtual void show_control_bar(::user::control_bar * pcontrolbar);
      virtual void hide_control_bar(::user::control_bar * pcontrolbar);

      void RepositionBars(unsigned int nIDFirst = 0, unsigned int nIDLast = 0xffff, ::atom idLeftOver = FIRST_PANE, unsigned int nFlag = reposDefault, ::int_rectangle* prectParam = nullptr, const ::int_rectangle& rectangleX = {
         }, bool bStretch = true) override;

      virtual ::user::interaction* ChildWindowFromPoint(const ::int_point& point) override;
      virtual ::user::interaction* ChildWindowFromPoint(const ::int_point& point, unsigned int nFlags) override;

      virtual ::user::interaction* get_next_sibling_window() override;

      ::user::interaction * get_next_window(bool bIgnoreChildren = false, ::user::interaction * puiInteractionStop = nullptr) override;
      ::user::interaction * get_window(enum_next enext) override;

      ::user::interaction* GetLastActivePopup() override;

      bool is_message_only_window() override;

      void pre_subclass_window() override;

      //void post_non_client_destroy() override;


      void default_message_handler(::message::message * pmessage) override;


      void message_handler(::message::message* pmessage) override;
      //virtual lresult message_handler(MESSAGE * pmessage) override;

      //virtual void GuieProc(::message::message* pmessage) override;

      //virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;



      virtual ::user::copydesk * copydesk();



      virtual bool can_merge(::user::interaction* pinteraction);
      virtual bool merge(::user::interaction* pinteraction);


      //virtual void _001OnTriggerMouseInside() override;


      virtual bool window_is_notify_icon_enabled();
      virtual void set_context_org(::draw2d::graphics_pointer & pgraphics) override;


      virtual void viewport_screen_to_client(::int_sequence2 & sequence) override;
      virtual void viewport_client_to_screen(::int_sequence2 & sequence) override;
      virtual void viewport_client_to_screen(::int_rectangle & rect) override;
      virtual void viewport_screen_to_client(::int_rectangle & rect) override;


      virtual void _raw_client_to_screen(::int_point & point);
      virtual void _raw_screen_to_client(::int_point & point);



      virtual string get_window_default_matter() override;
      virtual string get_window_icon_matter() override;
      virtual unsigned int get_window_default_style() override;
      //virtual enum_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command* psimplecommand) override;
      virtual void on_command(::message::command* pcommand) override;


      virtual bool OnCommand(::message::message* pmessage) override;
      virtual bool OnNotify(::message::message* pmessage) override;
      virtual bool OnChildNotify(::message::message* pmessage) override;


      virtual bool is_selected(::item* pitem) override;

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

      //// <3ThomasBorregaardSorensen__!! (I need to suck you, and take care of you, both front and back and middle but it ought to be unexplored by else...)
      void handle_command(const ::atom& atom) override;

      virtual bool has_command_handler(::message::command* pcommand) override;




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


      virtual void on_configuration_change(::user::interaction_base * pprimitiveSource) override;


      //virtual void show_keyboard(bool bShow = true) override;


      void ping() override;

      //virtual void move_to(const ::int_point& point);
      //virtual void set_size(const ::int_size& size);
      //virtual void move_to(int x, int y);
      //virtual void set_size(int cx, int cy);
      //virtual void set_dim(const ::int_point& point, const ::int_size& size);
      virtual void place_set_need_redraw(const ::int_rectangle & rectangleAfter, const ::int_rectangle & rectangleBefore, ::draw2d::graphics * pgraphics);
      virtual void place(const ::int_rectangle& rectangle, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      virtual void place(int x, int y, int w, int h, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      //inline void set_placement(int x, int y, int cx, int cy, enum_layout elayout = e_layout_sketch)
      //{
      //   
      //   place(::int_rectangle_dimension(x, y, cx, cy));
      //   
      //}
      virtual interaction& operator =(const ::int_rectangle& rectangle);

      virtual void place_rate_or_size(const ::double_rectangle & rectangle);


      virtual void activation(const ::user::activation & useractivation);


      virtual void display_child(const ::int_rectangle & rectangle, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr);
      inline void display_child(int x, int y, int cx, int cy, enum_layout elayout = e_layout_sketch, ::draw2d::graphics * pgraphics = nullptr)
      {

         display_child(int_rectangle_dimension(x, y, cx, cy), elayout, pgraphics);

      }


      virtual ::user::interaction* best_top_level_parent(::int_rectangle & rectangle);

      //virtual void window_rectangle(::int_rectangle * prectangle) override;

      virtual ::collection::index get_zoneing(::int_rectangle* prectangle, const ::int_rectangle& rectangle, ::e_display edisplay);

      virtual ::e_display initial_restore_display();

      // returns less than zero if no preferred restore
      // otherwise returns the preferred restore 
      // rectangle and its monitor index
      virtual ::collection::index get_preferred_restore(::int_rectangle & rectanglePreferredRestore);

      virtual bool calculate_window_rectangle_in_main_monitor(::int_rectangle & rectangle, const ::double_rectangle & rectangleOptionalRateOrSize);

      virtual ::collection::index calculate_broad_and_compact_restore(::int_rectangle * prectWorkspace = nullptr, const ::int_size & sizeMin = {}, const ::int_rectangle& rectangleHint = {
         });

       //virtual void reset_window_state();





      virtual ::collection::index make_zoneing(::int_rectangle* prectangle, const ::int_rectangle& rectangleHint = {}, bool bSet = false, ::e_display* pedisplay = nullptr, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top);
      virtual ::collection::index best_zoneing(::int_rectangle* prectangle, const ::int_rectangle& rectangleHint = {}, bool bSet = false, ::e_display* pedisplay = nullptr, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top);
      virtual ::collection::index best_monitor(::int_rectangle* prectangle, const ::int_rectangle& rectangleHint = {}, bool bSet = false, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top);
      virtual ::collection::index best_workspace(::int_rectangle* prectangle, const ::int_rectangle& rectangleHint = {}, bool bSet = false, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top);
      virtual ::collection::index good_restore(::int_rectangle* prectangle, const ::int_rectangle& rectangleHint = {}, bool bSet = false, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top, ::e_display edisplay = e_display_normal);
      virtual ::collection::index good_iconify(::int_rectangle* prectangle, const ::int_rectangle& rectangleHint = {}, bool bSet = false, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top);

      virtual ::collection::index good_move(::int_rectangle* prectangle, const ::int_rectangle& rectangle = {}, const ::user::activation & useractivation = {}, ::zorder zorder = e_zorder_top);
      virtual ::collection::index get_best_zoneing(::e_display& edisplay, ::int_rectangle* prectangle, const ::int_rectangle& rectangleRequest = ::int_rectangle(), bool bPreserveSize = false);
      virtual ::collection::index get_best_workspace(::int_rectangle* prectangle, const ::int_rectangle& rectangle, const ::user::activation & useractivation = {});


      virtual ::collection::index get_best_monitor(::int_rectangle* prectangle, const ::int_rectangle& rectangle, const ::user::activation & useractivation = {});


      virtual void get_rect_normal(::int_rectangle* prectangle);



      //virtual void set_context_offset_x(::draw2d::graphics_pointer & pgraphics, int x);
      //virtual void set_context_offset_y(::draw2d::graphics_pointer & pgraphics, int y);
      //virtual void set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y);
      //virtual void on_change_context_offset(::draw2d::graphics_pointer & pgraphics);
      virtual void on_context_offset(::draw2d::offset_context & offsetcontext);
      virtual ::double_size get_total_size(::user::enum_layout elayout = ::user::e_layout_design);
      virtual ::double_size get_page_size(::user::enum_layout elayout = ::user::e_layout_design);
      virtual ::double_point get_context_offset(::user::enum_layout elayout = ::user::e_layout_design);
      virtual double get_context_offset_x(::user::enum_layout elayout = ::user::e_layout_design);
      virtual double get_context_offset_y(::user::enum_layout elayout = ::user::e_layout_design);
      virtual void on_would_change_total_size(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void on_change_scroll_state(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void set_total_size(const ::double_size & size, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void set_page_size(const ::double_size& size, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void set_context_offset(const ::double_point & point, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void set_scroll_tracking_x(double x, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void set_scroll_tracking_y(double y, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void set_context_offset_x(double x, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void set_context_offset_y(double y, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void offset_context_offset(const ::double_size & size, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void offset_context_offset_x(double cx, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void offset_context_offset_y(double cy, ::user::enum_layout = ::user::e_layout_sketch);
      virtual void constrain_context_offset(double_point & point, ::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void on_change_context_offset(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void on_context_offset_layout(::draw2d::graphics_pointer & pgraphics);
      //virtual void on_context_offset(::draw2d::graphics_pointer & pgraphics);
      virtual ::double_point get_parent_accumulated_scroll(enum_layout elayout = e_layout_design);
      virtual ::double_point get_accumulated_scroll(enum_layout elayout = e_layout_design);
      virtual ::double_point get_scroll(enum_layout elayout = e_layout_design);
      virtual ::double_point get_parent_context_offset();
      virtual ::double_point get_ascendant_context_offset();
      virtual void get_margin_rect(::int_rectangle* prectMargin);

      virtual int get_final_scroll_bar_x_thickness(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual int get_final_scroll_bar_y_thickness(::user::enum_layout elayout = ::user::e_layout_sketch);


      virtual void synthesize_scroll_state_x(scroll_state & scrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void synthesize_scroll_state_y(scroll_state & scrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch);
      //virtual void layout_scroll_bar(::draw2d::graphics_pointer & pgraphics);
      virtual void layout_scroll_bar(::user::enum_layout elayout = ::user::e_layout_sketch);

      virtual ::user::scroll_bar * get_scroll_bar_x();
      virtual ::user::scroll_bar * get_scroll_bar_y();

      virtual scroll_state get_scroll_state_x(::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual scroll_state get_scroll_state_y(::user::enum_layout elayout = ::user::e_layout_sketch);

      virtual void set_scroll_state_x(const scroll_state & scrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch);
      virtual void set_scroll_state_y(const scroll_state & scrollstate, ::user::enum_layout elayout = ::user::e_layout_sketch);

      virtual void set_scroll_dimension(const ::int_size & size, ::user::enum_layout elayout = ::user::e_layout_sketch);

      inline bool _001HasBarXDragScrolling() const { return m_pointBarDragScrollMax.x > 0; }
      inline bool _001HasBarYDragScrolling() const { return m_pointBarDragScrollMax.y > 0; }


      //virtual double get_x_scroll();
      //virtual double get_y_scroll();

      virtual bool is_system_message_window();


      ::int_size get_window_minimum_size() override;

      virtual ::int_rectangle get_window_normal_stored_rectangle();
      virtual ::int_rectangle get_window_broad_stored_rectangle();
      virtual ::int_rectangle get_window_compact_stored_rectangle();

      virtual void set_window_normal_stored_rectangle(const ::int_rectangle & rectangle);

      virtual void UpDownTargetAttach(::user::interaction* pupdown);
      virtual void UpDownTargetDetach(::user::interaction* pupdown);

      virtual bool OnUpDownTargetAttach(::user::interaction* pupdown);
      virtual bool OnUpDownTargetDetach(::user::interaction* pupdown);


      virtual string calc_window_class();


      virtual void user_interaction_on_destroy();
      virtual void user_interaction_on_hide();


      virtual void show() override;
      virtual void hide() override;

      //virtual ::pointer_array < ::user::interaction > synchronized_get_children();





      virtual void on_erase_child(::user::interaction* pinteraction);
      virtual void on_erase_place_holder_child(::user::interaction* pinteraction);
      virtual void on_hide_child(::user::interaction* pinteraction);
      virtual void on_hide_place_holder_child(::user::interaction* pinteraction);


      void get_text_selection(character_count& iBeg, character_count& iEnd) const override;

      
      virtual bool set_sel_by_name(const ::scoped_string & scopedstrName);
      virtual string get_sel_by_name();
      virtual string get_hover_by_name();
      virtual void ensure_sel_visible();
      
      
      virtual void set_sel_color(const ::color::hls & hls);
      virtual ::color::hls get_sel_color();
      



      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual void keyboard_focus_OnKeyDown(::message::message* pmessage) override;
      //void keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      //void keyboard_focus_OnChildKillFocus() override;

      //virtual bool get_child(::pointer<::user::interaction> & pinteraction);
      //virtual bool rget_child(::pointer<::user::interaction> & pinteraction);


      


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

      //virtual ::user::interaction_base * get_keyboard_focus();
      //virtual void set_keyboard_focus(::user::interaction_base* pprimitive);
      //virtual void erase_keyboard_focus(::user::interaction_base * pprimitive);

      //virtual void erase_keyboard_focus() override;


      bool is_descendant_of(::user::element * puiAscendantCandidate, bool bIncludeSelf) override;
      bool is_ascendant_of(::user::element * puiDescendantCandidate, bool bIncludeSelf) override;

      bool is_descendant_of_or_owned_by(::user::element * puiAscendantCandidate, bool bIncludeSelf) override;
      bool is_ascendant_or_owner_of(::user::element * puiDescendantCandidate, bool bIncludeSelf) override;

      virtual void show_tooltip(const ::scoped_string & scopedstr, bool bError);

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
      //virtual void mouse_hover_step(int_point & pointLast);

      //virtual void mouse_hover_move(bool& bPointInside, int_point& pointLast);

      //bool has_pending_graphical_update() override;

      virtual void enable_transparent_mouse_events(bool bEnable = true);

      virtual void check_transparent_mouse_events();


      virtual void redraw_add(::particle * pparticle);

      virtual void redraw_erase(::particle * pparticle);

      virtual bool has_redraw();

      virtual void on_after_graphical_update() override;


      virtual void _001OnDeiconify(::user::activation_token * puseractivationtoken, ::e_display edisplay);


      virtual ::e_status is_edit_delete_enabled();
      virtual bool on_edit_delete(const ::action_context& action_context);


      virtual bool on_click_generation(::item * pitem, ::user::mouse * pmouse);
      virtual bool on_right_click_generation(::item * pitem, ::user::mouse * pmouse);


      virtual bool on_click(::item * pitem, ::user::mouse * pmouse);
      virtual bool on_right_click(::item * pitem, ::user::mouse * pmouse);


      virtual int width(enum_layout elayout = e_layout_design);
      virtual int height(enum_layout elayout = e_layout_design);

      virtual int client_width(enum_layout elayout = e_layout_design);
      virtual int client_height(enum_layout elayout = e_layout_design);

      virtual ::double_size get_size(enum_layout elayout = e_layout_design);
      virtual ::double_size get_client_size(enum_layout elayout = e_layout_design);

      //virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics);

      virtual void wait_redraw();

      virtual bool has_pending_redraw_flags() override;

      virtual bool is_window_resizing();
      virtual bool is_window_repositioning();
      virtual bool is_window_docking();

      virtual void set_bitmap_source(const ::scoped_string & scopedstrBitmapFileTitle) override;
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
      virtual void simple_ui_draw_border(::draw2d::graphics_pointer & pgraphics);


      virtual bool on_action(const ::scoped_string & scopedstrId);

      bool keyboard_focus_is_focusable() override;

      //virtual bool simple_on_control_event(::message::message* pmessage, ::enum_topic etopic);

      virtual ::item_pointer hit_test(::user::mouse * pmouse, e_zorder ezorder);

      virtual ::item_pointer hit_test(const ::int_point & point, e_zorder ezorder);

      virtual ::item_pointer on_hit_test(const ::int_point & point, e_zorder ezorder);

      ::item_pointer parent_client_hit_test(const ::int_point & point, e_zorder ezorder) override;

      ::item_pointer parent_client_on_hit_test(const ::int_point & point, e_zorder ezorder) override;

      virtual bool item_contains(::item * pitem, const ::int_point & point);

      virtual ::item_pointer on_items_hit_test(const ::int_point& point, e_zorder ezorder);
      virtual ::item_pointer on_items_hit_test(const ::int_point & point, e_zorder ezorder, ::collection::index iIdContainer, ::item_array * pitema);

      virtual void defer_setup_default_bottom_right_resize_user_item();

      virtual void defer_setup_default_client_area_user_item();
      
      virtual void setup_default_client_area_user_item();

///      virtual ::item_pointer on_default_full_client_area_hit_test(const ::int_point & point, e_zorder ezorder);

      //virtual bool update_hover(const ::int_point & point, bool bAvoidRedraw = true);
      virtual ::item_pointer update_hover(::message::mouse * pmouse, e_zorder ezorder);
      virtual ::item_pointer update_hover_according_to_last_hover_update(e_zorder ezorder);
      //virtual ::item_pointer update_hover(::user::mouse * pmouse, e_zorder ezorder);
      virtual void defer_update_hover(::draw2d::graphics_pointer & pgraphics);
      virtual void on_update_hover(::item * pitem);

      virtual bool is_mouse_hover() const;

      //virtual bool get_rectangle(::item * pitem);

      //inline auto rectangle(::item * pitem) { get_rect((::item *) pitem); return pitem->m_rectangle; }

      //virtual ::user::item * add_user_item(::item * pitem);

      //virtual ::user::item * _add_user_item(::item * pitem);

//      virtual ::item_pointer add_user_item(::item * pitem);

      virtual void _001DrawItems(::draw2d::graphics_pointer & pgraphics);

      virtual void _001DrawItems(::draw2d::graphics_pointer & pgraphics, ::collection::index iIdContainer, ::item_array * pitema);

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item & item, const ::user::e_state & estate);


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
      //::user::interaction_base* _003GetCustomMessageWnd();
      //virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;
      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
      //virtual bool has_function(enum_control_function econtrolfunction);
      //virtual enum_control_type get_control_type();
      //virtual void _003CallCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pitem);
      //virtual bool _003CallCustomWindowProc(::pointer<::user::interaction>puserinteraction, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, lresult& lresult);
      //virtual void _003OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::aura::draw_context* pitem);
      //virtual void _003CustomWindowProc(::message::message* pmessage);
      //virtual form_list * get_form_list();
      //virtual bool _001IsPointInside(::int_point point) override;
      //control null() { return control(); }
      //bool Validate(string& str);
      bool get_data(::pointer<::user::interaction>puserinteraction, ::payload& payload);
      
      virtual ::data::data * _get_data(const ::atom & atom);

      //void SetEditItem(::collection::index iItem);
      //void SetEditSubItem(::collection::index iItem);
      //index GetEditSubItem();
      // index GetEditItem();
      //virtual ::user::interaction * ControlExGetWnd();
      //using ::user::box::this->rectangle;
      //virtual bool this->rectangle(::int_rectangle * prectangle) override;
      //using ::user::box::window_rectangle;
      //virtual bool window_rectangle(::int_rectangle * prectangle) override;
      //bool operator == (const class ::user::control_descriptor& descriptor);
      //bool operator == (const class control& control);
      virtual bool IsControlCommandEnabled();
      virtual void EnableControlCommand(bool bEnable);
      //virtual void BaseControlExOnMouseMove(unsigned int nFlags, const ::int_point & point);
      //virtual ::item_pointer on_hit_test(const ::int_point & point, ::user::e_zorder ezorder) override;
      //DECLARE_MESSAGE_HANDLER(on_message_create);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      //DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      //DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(_001OnEnable);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditDelete);
      DECLARE_MESSAGE_HANDLER(_001OnEditDelete);
      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      //virtual void route(::topic * ptopic, ::handler_context * phandlercontext) override;
      //virtual void on_notify_control_event(control_event* phappening) override;
      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      //virtual bool simple_on_control_event(::message::message * pmessage, ::enum_topic etopic) override;
      //virtual void walk_pre_translate_tree(::message::message * pmessage,::pointer<::user::interaction>puiStop);
      //virtual bool get_element_rectangle(::int_rectangle* prectangle, enum_element eelement);
      virtual void get_simple_drop_down_open_arrow_polygon(double_point_array& pointa);
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




      void _post(const ::procedure & procedure) override;
      //virtual void fps_interest_post_procedure(const ::procedure & procedure);


      //void send_procedure(const ::procedure & procedure) override;


   /*   template < typename PRED >
      void post_predicate(PRED pred)
      {

         post_method(__routine(pred));

      }*/


 /*     template < typename PRED >
      void graphics_thread_post_predicate(PRED pred)
      {

         graphics_thread_schedule(__routine(pred));

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

      //virtual bool _001FancyInitialFramePlacement(::int_rectangle * lprect, const double_rectangle & rectangleOptionalRateOrSize = {0., 0., 0., 0.});

      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;

      virtual int_point screen_origin(enum_layout elayout = e_layout_design);
      virtual int_point host_origin(enum_layout elayout = e_layout_design);


      virtual void set_opacity(double dOpacity);

      //::item_pointer get_child_as_item(::collection::index iIndex) override;
      //::collection::count get_child_as_item_count() override;

      ::user::interaction * child_at(::collection::index iIndex);


      virtual void on_item_selected(::item* pitem);
      void on_item_hover(::item* pitem) override;


      ::item_pointer hover_item() override;


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _screen_to_client(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::int_size(get_parent_accumulated_scroll(elayout)) - ::int_size(screen_origin(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_screen(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::int_size(screen_origin(elayout)) - ::int_size(get_parent_accumulated_scroll(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _parent_to_client(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s - ::int_size(m_layout.origin(elayout)); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_parent(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + ::int_size(m_layout.origin(elayout)); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _host_to_client(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::int_size(get_parent_accumulated_scroll(elayout)) - ::int_size(host_origin(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_host(OFFSETABLE& o, const SOURCE & s, enum_layout elayout = e_layout_design) const { o = s + (::int_size(host_origin(elayout)) - ::int_size(get_parent_accumulated_scroll(elayout))); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _host_to_client_no_scroll(OFFSETABLE& o, const SOURCE& s, enum_layout elayout = e_layout_design) const { o = s - ::int_size(host_origin(elayout)); }


      //template < typename OFFSETABLE, typename SOURCE >
      //inline void _client_to_host_no_scroll(OFFSETABLE& o, const SOURCE& s, enum_layout elayout = e_layout_design) const { o = s + ::int_size(host_origin(elayout)); }




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

      
      virtual ::shift_int screen_to_client(enum_layout elayout = e_layout_design);
      virtual ::shift_int client_to_screen(enum_layout elayout = e_layout_design);
      virtual ::shift_int parent_to_client(enum_layout elayout = e_layout_design);
      virtual ::shift_int client_to_parent(enum_layout elayout = e_layout_design);
      virtual ::shift_int host_to_client(enum_layout elayout = e_layout_design);
      virtual ::shift_int client_to_host(enum_layout elayout = e_layout_design);
      virtual ::shift_int host_to_raw(enum_layout elayout = e_layout_design);
      virtual ::shift_int raw_to_host(enum_layout elayout = e_layout_design);


      //template < typename GEOMETRY >
      //inline GEOMETRY _001HostToClientNoScroll(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _host_to_client_no_scroll(g, s); return g; }


      //template < typename GEOMETRY >
      //inline GEOMETRY _001ClientToHostNoScroll(const GEOMETRY& s, enum_layout elayout = e_layout_design) const { GEOMETRY g; _client_to_host_no_scroll(g, s); return g; }

      
      
//      virtual void pick_single_file(
//         const ::array < ::pair < ::string, ::string > >& filetypes,
//         const ::function < void(const ::file::path &) >& function,
//         bool save);
//
//
//      virtual void pick_multiple_file(
//         const ::array < ::pair < ::string, ::string > > & filetypes,
//         const ::function < void(const ::file::path_array_base &) >& function);
//     
//      virtual void pick_single_folder(
//         //const ::array < ::pair < ::string, ::string > >& filetypes,
//                              const ::function < void(const ::file::path &) >& function);
//                              //,       bool save);

      
      
      bool on_impact_update() override;

      void window_restore() override;
      void window_minimize() override;
      void window_maximize() override;

      void on_control_box_close() override;
      void on_control_box_minimize() override;
      void on_control_box_zoom() override;

   };


   class control_cmd_ui : public ::message::command
   {
   public:


      id_to_id_base      m_mapControlCommand;


      control_cmd_ui();


      virtual void enable(bool bOn);
      virtual void SetCheck(int nCheck);
      virtual void SetText(const ::scoped_string & scopedstrText);

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


   class lock_sketch_to_design
   {
   public:

      ::user::interaction * m_puserinteraction;

      lock_sketch_to_design(::user::interaction * puserinteraction) :
      m_puserinteraction(puserinteraction)
      {
         m_puserinteraction->m_bLockSketchToDesign = true;

      }
      ~lock_sketch_to_design()
      {

         m_puserinteraction->m_bLockSketchToDesign = false;

      }

   };


   //compile_time_assert((offsetof(::user::interaction, m_oswindow) & 4) == 0);



} // namespace user






