// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


#include "apex/message/channel.h"
#include "acme/prototype/collection/osdata_array.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size.h"
#include "apex/windowing/window_base.h"
//#include "primitive_impl.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/redraw.h"
#include "acme/prototype/collection/list.h"
#include "acme/prototype/geometry2d/_collection.h"


namespace windowing
{


   class CLASS_DECL_AURA window :
      virtual public osdata_array,
      virtual public ::windowing::window_base
   {
   public:
      
      struct mouse_reposition_throttling
      {
         
         // if high frequency mouse transfer notification is required
         // create a fast path/low latency callback system
         int                                       m_iMouseMoveSkipCount;
         int                                       m_iMouseMoveSkipSquareDistance;
         class ::time                              m_timeMouseMoveSkip;
         ::int_point                               m_pointMouseMoveSkip;
         class ::time                              m_timeMouseMovePeriod;
         ::int_point                               m_pointMouseMove;
         class ::time                              m_timeMouseMove;
         class ::time                              m_timeMouseMoveIgnore;
         //bool                                      m_bMouseMovePending;
         
      };

      union
      {
         struct
         {
            bool                                      m_bQuitGraphicsOnHide : 1;
            bool                                      m_bDestroyWindowOnHide : 1;
            bool                                      m_bTryCloseApplicationOnHide : 1;

         };
         unsigned char m_uOnHide = {};
      };

      bool                                      m_bMessageOnlyWindow : 1;

      ::sandbox_windowing::window *             m_psandboxwindowingwindow;
      //void *                                    m_pWindow4;

      //::pointer<::windowing::display>           m_pdisplay;
      ::pointer<::user::interaction>            m_puserinteraction;
      string                                    m_strDebug;
      ::pointer<::message_queue>                m_pmessagequeue;
      class ::time                              m_timeLastMouseMove;
      ::cast < ::windowing::window >            m_pwindowParent;
      ::string                                  m_strBitmapSource;
      mouse_reposition_throttling               m_mouserepositionthrottling;

      ::pointer<::windowing::icon>              m_picon;
      //::pointer<::windowing::windowing>         m_pwindowing;
      ::pointer<::user::copydesk>               m_pcopydesk;
      ::pointer<::windowing::cursor>            m_pcursor;
      //::oswindow                                m_oswindow;
      bool                                      m_bUpdateScreenSynchronously;
      class ::time                              m_timeLastDrawGuard1;
      
      bool                                      m_bActiveWindow;
      bool                                      m_bKeyboardFocus;
      ::pointer < class placement_log >         m_pplacementlog;
      ::particle_pointer                        m_pparticleChildrenSynchronization;

#if defined(WINDOWS_DESKTOP) && !defined(ENABLE_TEXT_SERVICES_FRAMEWORK)
      //HIMC                                    m_himc;
#endif
      bool                                      m_bEatSizeEvent;
      bool                                      m_bEatMoveEvent;
      bool                                      m_bTransparentMouseEvents;
      //bool                                      m_bOfflineRender;

      bool                                      m_bCursorRedraw;
      bool                                      m_bLockWindowUpdate;
      bool                                      m_bOkToUpdateScreen;
      bool                                      m_bScreenRelativeMouseMessagePosition;

      bool                                      m_bTranslateMouseMessageCursor;
      bool                                      m_bComposite;
      bool                                      m_bUpdateGraphics;
      bool                                      m_bPointInside;

      bool                                      m_bPendingRedraw;
      bool                                      m_bPadding1;
      bool                                      m_bPadding2;
      bool                                      m_bPadding3;

      ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)::interaction_impl * m_pImpl2;
      ::int_rectangle                           m_rectangleWindowScreen;
      ::int_rectangle                           m_rectangleXScreen;
      int                                       m_iState1;
      unsigned int                                     m_uCodePage;
      int                                       m_iLangId;
      class ::time                              m_timeLastExposureAddUp;
      ::pointer<::user::graphics_thread>        m_pgraphicsthread;
      ::pointer<::user::thread>                 m_puserthread;
      pointer_array < ::graphics::output_purpose > m_graphicaloutputpurposea;
      //string                                    m_strBitmapSource;
      //::pointer<::windowing::windowing>         m_pwindowing;
      ::frequency                               m_frequencyProdevianFramesPerSecond;
      ::frequency                               m_frequencyNominalFramesPerSecond;
      ::frequency                               m_frequencyOutputFramesPerSecond;
      int_point                                 m_pointMouseMove;
      //::int_size                              m_sizeDrawnAAA;
      ::int_size                                m_sizeSetWindowSizeRequest;
      particle_array                            m_particleaRedraw;

      //::int_rectangle                           m_rectangleUpdateBuffer;
      ::thread_pointer                          m_pthreadMouseLeave;

      ::list < ::pointer<::message::message >> m_messagelist;

      ::int_point                               m_pointInside;
      //::user::interaction_base *                       m_pprimitiveFocus;
      ::pointer<::user::element>               m_pelementSoftwareKeyboard;

      ::pointer<::user::interaction>            m_puserinteractionOwner;

      int_point                                 m_point;
      int_size                                  m_size;

      //native_window *                         m_pwindow;

      ::pointer<::graphics::graphics>           m_pgraphicsgraphics;
      ::pointer<::draw2d::graphics>             m_pdraw2dgraphics;

      ::pointer < ::mutex >                     m_pmutexDraw;
      ::pointer < ::mutex >                     m_pmutexRedraw;

      ::user::interaction_ptra                  m_userinteractionaMouseHover;

      unsigned int                                     m_uiMessage;
      wparam                                    m_wparam;
      lparam                                    m_lparam;
      lparam                                    m_lparamLastMouseMove;

      bool                                      m_bUpdateBufferPending;

      ::pointer<::user::interaction>            m_puserinteractionMouseCapture;
      ::pointer<::user::interaction>            m_puserinteractionKeyboardFocus;
      ::pointer<::user::interaction>            m_puserinteractionKeyboardFocusRequest;
      /// message handling helper besides (possibly duplicate of) m_puserinteractionKeyboardFocusRequest
      ::pointer<::user::interaction>            m_puserinteractionKeyboardGainingFocusIfAny;
      ::pointer<::user::interaction>            m_puserinteractionToKillKeyboardFocus;

      class ::time                              m_timeLastRedraw;
      ::user::interaction_array                 m_userinteractionaHideOnConfigurationChange;

      class ::time                              m_timeDeviceDrawBeg;
      class ::time                              m_timeDeviceDrawEnd;
      class ::time                              m_timeLastDeviceDraw;

      ::int_size                                m_sizeDrawnBuffer;

      //      ::int_rectangle_array                     m_rectangleaNeedRedraw;
      ::pointer_array < ::user::redraw_item > m_redrawitema;

      ::pointer < ::user::interaction >         m_puiLastLButtonDown;
      ::item_pointer                            m_pitemLButtonDown;

      bool                                      m_bDoingGraphics;


      ::int_size                                m_sizeLastBuffer;

      //::windowing::window * m_pinteractionimpl;
      //::user::interaction_child * m_pinteractionchild;


      iptr_to_iptr                              m_iptrmap;

      bool                                      m_bUserImplCreated;
      bool                                      m_bDrawFlagsReady;
      bool                                      m_bDestroyImplOnly;
      //bool                                    m_bDestroying;
      int                                       m_iPendingRectMatch;
      //::pointer<::user::interaction>            m_puserinteraction;
      ::pointer<::user::box>                    m_puserbox;
      bool                                      m_bIgnoreSizeEvent;
      bool                                      m_bIgnoreMoveEvent;
      ::auto_pointer < critical_section >       m_pcsDisplay;

      const char * m_pszInteractionImplBaseDebug;

      //bool                                      m_bPendingRedraw;
      unsigned int                                       m_uiLastRedraw;
      bool                                      m_bUpdatingBuffer;

      ::int_rectangle                           m_rectangle;



      window();
      ~window() override;


      void user_common_construct();

      void on_initialize_particle() override;

      virtual void window_set_keyboard_focus();
      virtual void window_kill_keyboard_focus();

         virtual void on_set_focus_to_child();
      
      virtual void window_on_activate();
      virtual void window_on_deactivate();
      virtual void window_on_set_keyboard_focus();
      virtual void window_on_kill_keyboard_focus();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      // ::aura::application* get_app();
      // ::aura::session* get_session();
      // //::aura::system* system();
      //

      void install_message_routing(::channel * pchannel) override;

      
      //virtual void call_create_window(::windowing::window * pwindow);

      //virtual void create_window(::windowing::window * pimpl);
      
      void create_window() override;

      void _create_window() override;

      virtual void create_graphics_thread();

      virtual void on_finished_window_creation();


      virtual void process_messages();


      virtual void do_graphics();
      virtual void _001OnNcClip(::draw2d::graphics_pointer & pgraphics);
      virtual void defer_do_graphics(::draw2d::graphics_pointer & pgraphics);


      //virtual void set_cursor_position(const ::int_point & pointCursor);

      //virtual void get_cursor_position(::int_point * ppointCursor);

      //inline ::int_point get_cursor_position() { ::int_point point; get_cursor_position(&point); return point; }


      //virtual bool defer_set_icon();

      virtual class placement_log* placement_log();

      virtual double get_top_margin();
      

      void set_keyboard_focus() override;
      virtual void _set_keyboard_focus_unlocked();


      // implementation foreseeing Windows with its mouse capture state per thread and
      // also providing fallback default internal (own process state) implementation.
      void set_mouse_capture() override;
      // implementation foreseeing Windows with its mouse capture state per thread and
      // also providing fallback default internal (own process state) implementation.
      bool has_mouse_capture() override;
      // implementation foreseeing Windows with its mouse capture state per thread and
      // also providing fallback default internal (own process state) implementation.
      bool is_mouse_captured() override;
      // implementation foreseeing Windows with its mouse capture state per thread and
      // also providing fallback default internal (own process state) implementation.
      void release_mouse_capture() override;
      // implementation foreseeing Windows with its mouse capture state per thread and
      // also providing fallback default internal (own process state) implementation.
      bool defer_release_mouse_capture() override;


      virtual void bring_to_front();

      virtual void switch_to_this_window(bool b);

      virtual void graphics_lock();
      virtual void graphics_unlock();


      //virtual bool has_mouse_capture() const;
      bool has_keyboard_focus() override;

      virtual ::color::color screen_pixel(int x, int y);

      virtual bool is_full_screen();

      virtual ::windowing::display * display();

      virtual ::user::copydesk * copydesk();

      virtual ::oswindow oswindow() const;
      virtual void set_oswindow(::oswindow oswindow);
      virtual void _set_oswindow(::oswindow oswindow);


      

      virtual ::windowing::windowing * windowing();


      ::user::interaction * user_interaction() override;


      //inline ::windowing::windowing * windowing() const { return m_pwindowing.m_p; }


      void exit_iconify() override;

      void full_screen(const::int_rectangle & rectangle = {}) override;

      void exit_full_screen() override;

      void exit_zoomed() override;

      void destroy_window() override;

      void on_destroy() override;

      //virtual void show_window(const ::e_display & edisplay, const ::user::e_activation & useractivation);

      //virtual void _show_window_unlocked(const ::e_display & edisplay, const ::user::e_activation & useractivation);

      //void set_user_interaction(::acme::user::interaction *pinteraction) override;

      //void post_non_client_destroy() override;

      virtual bool is_child_of(const window * pwindowAscendantCandidate) const; // or descendant
      
      
      //virtual ::windowing::window * window_get_parent();
      //virtual ::oswindow get_parent_oswindow();
      virtual void set_parent(::windowing::window * pwindowNewParent);



      
      virtual ::windowing::window * window_get_owner();
      virtual ::oswindow get_owner_oswindow();
      virtual void set_owner(::windowing::window * pwindowNewOwner);


      bool is_iconic() override;
      virtual bool is_zoomed();
      bool is_window() override;
      bool is_window_visible() override;

      virtual bool _is_iconic_unlocked();
      virtual bool _is_window_visible_unlocked();
      

      bool client_to_screen(::int_point * ppoint) override;

      bool screen_to_client(::int_point * ppoint) override;


      virtual bool on_set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay);

      virtual bool set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay);
      virtual bool _set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay, unsigned int nOverrideFlags = 0);

      virtual bool configure_window_unlocked();
      virtual bool strict_set_window_position_unlocked(bool & bChangedPosition, bool & bChangedSize);
      virtual bool strict_set_window_position_unlocked(bool & bChangedPosition, bool & bChangedSize, const ::int_rectangle & rectangle);
      virtual bool set_window_position_unlocked();
      virtual bool _set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay);
      virtual void _set_window_position_unchanged();
      virtual bool _configure_window_unlocked(const class ::zorder& zorder, const ::user::activation& useractivation, bool bNoZorder, ::e_display edisplay);
      virtual bool _strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize);

      bool is_destroying() override;


      virtual void activate_top_parent();


      void message_handler(::message::message* pusermessage) override;

      virtual void do_message_handler(::message::message * pusermessage);


      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      virtual void present();

      //virtual bool presentation_complete();


      //virtual void on_visual_applied();

      virtual void _on_configure_notify_unlocked(const ::int_rectangle & rectangle);
      virtual void _on_reposition_notify_unlocked(const ::int_point & point);


      virtual void win_update_graphics();

      virtual lresult send_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr);

      void post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr) override;


      void set_window_text(const ::scoped_string & scopedstr) override;

      //::string get_window_text() override;

      //virtual void get_window_text(string & rectangleString);
      //virtual character_count get_window_text_length();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual unsigned int ArrangeIconicWindows();

      virtual void rects_from_os();
      virtual bool window_rect_from_os(::int_rectangle * prectangle);
      virtual bool client_rect_from_os(::int_rectangle * prectangle);


      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      virtual bool GetUpdateRect(::int_rectangle * prectangle, bool bErase = false);

      virtual int GetUpdateRgn(::draw2d::region * pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true);
      virtual void InvalidateRect(const ::int_rectangle * rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region * pRgn, bool bErase = true);
      virtual void ValidateRect(const ::int_rectangle * int_rectangle);

      virtual void ValidateRgn(::draw2d::region * pRgn);


      virtual void ShowOwnedPopups(bool bShow = true);

      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();


      virtual bool RedrawWindow(const ::int_rectangle & rectangleUpdate = {}, ::draw2d::region * prgnUpdate = nullptr, unsigned int flags = 0);

      // Window State Functions
      virtual bool is_this_enabled();
      void enable_window(bool bEnable = true) override;

      // the active interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * get_active_window();
      void set_active_window() override;
      virtual void _set_active_window_unlocked();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      void set_foreground_window() override;
      virtual void _set_foreground_window_unlocked();
      virtual ::user::interaction * get_foreground_window();

      virtual bool is_active_window() override;

      virtual ::user::interaction * get_desktop_window();


      virtual ::windowing::window * get_next_window(unsigned int nFlag = 0);
      virtual ::windowing::window * get_top_window();

      virtual ::windowing::window * get_window(unsigned int nCmd);
      virtual ::windowing::window * get_last_active_popup();


      virtual int_point GetCaretPos();
      virtual void SetCaretPos(const ::int_point & point);
      virtual void HideCaret();
      virtual void ShowCaret();

      virtual void DragAcceptFiles(bool bAccept = true);


      virtual ::pointer<::windowing::icon>load_icon(const ::payload& payloadFile);


      virtual void set_icon(::windowing::icon * picon);
      virtual ::pointer<::windowing::icon>get_icon() const;


      void set_mouse_cursor(::windowing::cursor * pcursor) override;
      virtual ::windowing::cursor * get_mouse_cursor();


      //virtual ::int_point get_mouse_cursor_host_position();
      
      //virtual ::int_point get_mouse_cursor_absolute_position();


      void set_tool_window(bool bSet) override;


      void set_context_org(::draw2d::graphics_pointer & pgraphics) override;


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(::int_rectangle * prectangle);
      virtual void _window_show_change_visibility(::e_display edisplay, const ::user::activation & useractivation);


      virtual void non_top_most_upper_window_rects(::int_rectangle_array & recta);

      void default_message_handler(::message::message * pmessage) override;

      void track_mouse_hover() override;


      virtual void _task_transparent_mouse_event();


      virtual float get_dpi_for_window();

      virtual float get_density_for_window();


      virtual float point_dpi(float points);

      virtual float y_dpi(float y);
      virtual float x_dpi(float x);

      virtual float dpiy(float y);
      virtual float dpix(float x);


      virtual void on_redraw_window(unsigned int flags);


      virtual void show_task(bool bShowTask);


      virtual void __update_graphics_buffer();
      //virtual void window_request_presentation();

      //virtual void _window_request_presentation_locked();
      //virtual void _window_request_presentation_set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::e_activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide);
      
      virtual void frame_toggle_restore(::user::activation_token * puseractivationtoken);

      void _user_send(const ::procedure & procedure) override;
      void _user_post(const ::procedure & procedure) override;

      bool is_branch_current() const override;

      
      itask_t get_itask() const;


      virtual void on_touch_down(int xHost, int yHost, int xAbsolute, int yAbsolute);
      virtual void on_touch_drag(int xHost, int yHost, int xAbsolute, int yAbsolute);
      virtual void on_touch_up(int xHost, int yHost, int xAbsolute, int yAbsolute);

      virtual void on_size(int w, int h);

      virtual void on_text(const ::ansi_character * pansisz, character_count length);
      virtual void on_text(const ::wd16_character * pwd16sz, character_count length);
      virtual void on_text(const ::wd32_character * pwd32sz, character_count length);


      inline bool operator == (const ::windowing::window & window) const
      {

         return oswindow() == window.get_os_data();

      }


      inline bool operator != (const ::windowing::window & window) const
      {

         return !operator == (window);

      }

      //virtual void window_do_graphics_thread_step();

      virtual void window_update_screen();

      bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

      bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;

      virtual void on_destruct_mouse_message(::message::mouse * pmouse);


      ::trace_statement & trace_statement_prefix(::trace_statement & statement) const override;


      bool is_satellite_window() override;
      bool is_windowing_popup() override;
      ::int_point windowing_popup_origin() override;
      ::int_size windowing_popup_size() override;
      void _on_windowing_close_window() override;
      ::acme::windowing::window * owner_window() override;
      ::string get_window_text() override;


      void defer_show_system_menu(::user::mouse * pmouse) override;

      virtual void pick_browse(const ::function < void(const ::file::path & path) > & callback);
      virtual void pick_media(const char * pszMediaType);
      virtual void on_prompt_write_file(::user::controller * pusercontroller);


      virtual void set_opacity(double dOpacity);

      void window_restore() override;
      void window_minimize() override;
      void window_maximize() override;

      // void on_window_deiconified() override;
      // void on_window_activated() override;
      // void on_window_iconified() override;
      // void on_window_deactivated() override;


      void destroy() override;

      void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem) override;


      void _main_send(const ::procedure & procedure) override;
      void _main_post(const ::procedure & procedure) override;



      //      // void assert_ok() const override;
      //      // void dump(dump_context & dumpcontext) const override;


            //virtual void sketch_to_layout(::graphics::buffer_item * pbufferitem);


      virtual void set_prodevian_frames_per_second(::frequency frequencyProdevianFramesPerSecond);
      virtual void set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond);
      virtual void set_per_second(::frequency frequencyFramesPerSecond);
      virtual ::frequency get_prodevian_frames_per_second();
      virtual ::frequency get_nominal_frames_per_second();
      virtual ::frequency get_output_per_second();

      //void user_common_construct();

      //void on_initialize_particle() override;

      virtual bool __windows_message_bypass(::windowing::window * pwindow, unsigned int message, wparam wparam, lparam lparam, lresult & lresult);

      //void install_message_routing(::channel * pchannel) override;

      //void default_message_handler(::message::message * pusermessage) override;

      virtual void on_tsf_activate(bool bActivate);

      virtual ::pointer< ::mutex > draw_mutex();

      //::windowing::window * get_user_interaction_impl() override;

      virtual void post_message(::message::message * pusermessage);


      void set_bitmap_source(const string & strBitmapSource) override;
      void clear_bitmap_source() override;


      virtual void update_graphics_resources();



      //void queue_message_handler(::message::message * pmessage) override;


      void process_message();


      //bool is_there_graphics_output_interest() const override;


      //void set_tool_window(bool bSet) override;


      //virtual void create_host(::user::interaction * pinteraction, enum_parallelization eparallelization);

      //virtual void create_host(::user::interaction * pinteraction);

      //virtual ::color::color screen_pixel(int x, int y) const;
      //void interaction_post(const ::procedure & procedure) override;

      //virtual void user_call(const ::procedure & procedure);

      // call these from window
      //virtual void set_keyboard_focus();
      virtual void set_mouse_capture(::user::interaction * puserinteraction);
      virtual bool defer_release_mouse_capture(::user::interaction * puserinteraction);
      //virtual void set_active_window();
      //virtual void set_foreground_window();


      virtual bool on_keyboard_focus(::user::interaction_base * pfocus);
      virtual bool keyboard_focus_OnKillFocus(::oswindow oswindowNew) override;
      virtual bool keyboard_focus_OnChildKillFocus() override;

      //      virtual void on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus);
      //      virtual void on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus);

      virtual void on_final_set_keyboard_focus();

      virtual void on_final_kill_keyboard_focus();

      virtual bool has_pending_focus();

      virtual bool set_pending_focus();

      virtual bool clear_pending_focus();

      //void create_message_queue(::user::interaction * pinteraction, const ::string & lpszName) override;

      //virtual bool create_native_window(::user::native_window_initialize * pinitialize) override;
      //virtual void set_destroying();

      virtual void _000OnMouseLeave(::message::message * pmessage) override;
      //virtual void _008OnMouse(::message::mouse * pmouse);
      //virtual void _001BaseWndInterfaceMap();

      //virtual void prio_install_message_routing(::channel * pchannel) override;
      //virtual void last_install_message_routing(::channel * pchannel) override;

      //bool operator==(const interaction_impl& wnd) const;
      //bool operator!=(const interaction_impl& wnd) const;

      //virtual unsigned int GetStyle() const override;
      //virtual unsigned int GetExStyle() const override;
      //virtual bool ModifyStyle(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0) override;
      //virtual bool ModifyStyleEx(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0) override;


      //virtual void set_icon(::windowing::icon * picon);
      //virtual ::pointer<::windowing::icon>get_icon() const;


      virtual void mouse_hover_add(::user::interaction * pinterface);
      virtual bool mouse_hover_erase(::user::interaction * pinterface);


      //void _task_transparent_mouse_event() override;


      //virtual void track_mouse_hover() override;
      //virtual void track_mouse_leave() override;

      virtual void _on_mouse_move_step(const ::int_point & pointCursor, ::user::enum_layout elayoutChild = ::user::e_layout_design, bool bMouseLeave = false);


      virtual void defer_check_mouse_leave(::user::enum_layout elayoutWindow, ::user::enum_layout elayoutChild);


      //virtual void mouse_hover_step(const __status < ::int_point > & statusPointCursor);

      virtual void add(::graphics::output_purpose * pgraphicaloutputpurpose);
      virtual void erase(::graphics::output_purpose * pgraphicaloutputpurpose);
      virtual void add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose);
      virtual void erase_graphical_output_purpose(::particle * pparticle);
      virtual bool has_particle_fps_purpose(::particle * pparticle);
      virtual ::graphics::enum_output_purpose most_demanding_graphical_output_purpose();
      virtual bool has_screen_output_purpose();
      virtual bool has_offscreen_output_purpose();
      virtual bool has_graphical_output_purpose();
      virtual bool has_fps_output_purpose();

      //virtual void fps_interest_stop();


      //virtual ::user::interaction * get_owner();
      //::user::interaction_base * set_owner(::user::interaction_base * pprimitiveOwner) override;

      bool has_pending_redraw_flags() override;

      virtual ::windowing::window * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      //bool attach(::windowing::window * pwindow_New) override;
      //oswindow detach() override;

      //virtual void destroy() override;

      //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      DECLARE_MESSAGE_HANDLER(_002OnDraw);

      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(on_prio_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(_001OnApplyVisual);


      //void on_configure(const ::int_rectangle & rectangle) override;
      virtual void _on_configure(const ::int_rectangle & rectangle);


      DECLARE_MESSAGE_HANDLER(on_message_reposition);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnDestroyWindow);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      //DECLARE_MESSAGE_HANDLER(_001OnRedraw);
      //DECLARE_MESSAGE_HANDLER(_001OnDoShowWindow);


//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      bool GetWindowInfo(PWINDOWINFO pwi) const;
//      bool GetTitleBarInfo(PTITLEBARINFO pti) const;
//
//#endif   // WINVER >= 0x0500

      // subclassing/unsubclassing functions
      void pre_subclass_window() override;
      //virtual bool subclass_window(::windowing::window * pwindow) override;
      //virtual bool SubclassDlgItem(unsigned int nID, ::windowing::window * pParent);
      //virtual oswindow unsubclass_window() override;

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      //virtual bool ExecuteDlgInit(const ::string & pszResourceName);

      //virtual bool ExecuteDlgInit(void * pResource);





      //using ::user::interaction_base::create_interaction;
      //using ::user::interaction_base::create_window_ex;


      // for child windows, views, panes etc
      //virtual bool create_interaction(::user::interaction * pinteraction, unsigned int uExStyle, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction_base * puiParent, ::request * prequest = nullptr) override;


      // advanced creation (allows access to extended styles)
      //virtual bool create_window_ex(::user::interaction * pinteraction, ::pointer<::user::system>pcs, ::user::interaction_base * puiParent, atom atom) override;

      //virtual bool create_interaction() override;


      //virtual bool _native_create_window(::user::interaction * pinteraction, ::windowing::window * pwindow);


      //virtual bool _native_create_window_ex(::pointer<::user::system>pusersystem);

      //virtual bool _native_create_window_ex(::pointer<::user::system>pusersystem);

      //virtual bool create_host();

      //virtual void operating_system_create_host(::enum_parallelization eparrallelization);

      virtual void operating_system_create_host();

      //virtual void _create_window(::enum_parallelization eparrallelization);
      //virtual void _create_window();

      virtual void native_create_host_alternate();


      virtual void destroy_impl_only();
      virtual void start_destroying_window();
      //virtual void destroy_window();

      // special pre-creation and interaction_impl int_rectangle adjustment hooks
      virtual bool pre_create_window(::user::system * pusersystem);

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      //virtual void CalcWindowRect(::int_rectangle * pClientRect,unsigned int nAdjustType = adjustBorder) override;

      //inline ::windowing::window * window() const { return m_pwindow; }
      //inline ::windowing::windowing * windowing() const { return m_pwindowing; }



//      bool _is_window() override;

//#if(WINVER >= 0x0500)
//
//      virtual ::windowing::window * GetAncestor(unsigned int gaFlags) const;
//
//#endif   // WINVER >= 0x0500
//
      lresult send_message(const ::atom & atom, ::wparam wParam = 0, ::lparam lParam = 0, const ::int_point & point = {}) override;

      lresult send_message(::message::message * pmessage) override;


      //#ifdef LINUX
      //
      //      virtual lresult send_x11_event(void * phappening) override; // XEvent *
      //
      //#endif


      //void post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = 0) override;


      //virtual bool SendNotifyMessage(unsigned int message,wparam wParam,lparam lParam);

      //virtual bool SendChildNotifyLastMsg(lresult* pResult = nullptr);

      //virtual bool DragDetect(const ::int_point & point) const;



      // Window Text Functions
      //virtual void set_window_text(const ::string & pszString) override;

      //void on_set_window_text() override;

      //character_count get_window_text(char * pszStringBuf, character_count nMaxCount) override;

      //void get_window_text(string & rString) override;
      //character_count get_window_text_length() override;


      // Window int_size and position Functions
      virtual bool window_is_iconic();
      virtual bool window_is_zoomed();
      //virtual int SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual int GetWindowRgn(HRGN hRgn);

      //using ::user::interaction_base::set_window_position;
      //virtual bool set_window_position(class zorder zorder, int x, int y, int cx,int cy, unsigned int nFlags = SWP_SHOWWINDOW) override;
      //virtual unsigned int ArrangeIconicWindows() override;
      //virtual bool BringWindowToTop() override;

//#ifdef WINDOWS_DESKTOP
//      virtual bool GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl);
//
//      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl);
//
//#endif

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::int_point * pPoint, unsigned int nCount);

      virtual void MapWindowPoints(::windowing::window * puserinteractionTo, ::int_rectangle * prectangle);


      virtual void Print(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics, unsigned int dwFlags) const;

      //void UpdateWindow() override;
      //void SetRedraw(bool bRedraw = true) override;
      ////virtual bool GetUpdateRect(::int_rectangle * prectangle,bool bErase = false) override;

      ////int GetUpdateRgn(::draw2d::region* pRgn,bool bErase = false) override;
      //virtual void Invalidate(bool bErase = true) override;
      //void InvalidateRect(const ::int_rectangle & rectangle,bool bErase = true) override;

      //void InvalidateRgn(::draw2d::region* pRgn,bool bErase = true) override;
      //void ValidateRect(const ::int_rectangle & rectangle) override;

      //void ValidateRgn(::draw2d::region* pRgn) override;
      ////virtual bool display(::e_display edisplay) override;
      ////virtual bool _is_window_visible() override;
      //void ShowOwnedPopups(bool bShow = true) override;

      //virtual ::pointer<::draw2d::graphics>GetDCEx(::draw2d::region* prgnClip,unsigned int flags);
      //virtual void LockWindowUpdate();
      //virtual void UnlockWindowUpdate();


      // try calling prodevian things from prodevian... he is not much called...
      //void graphics_thread_update_screen() override;

      // try calling prodevian things from prodevian... is he ever called...
      //void graphics_thread_redraw(bool bUpdateBuffer) override;

//#ifdef WINDOWS
//
//      virtual bool RedrawWindow(const ::int_rectangle & rectangleUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,unsigned int flags = RDW_INVALIDATE | RDW_ERASE);
//
//#else

      //void RedrawWindow(const ::int_rectangle & rectangleUpdate = {}, ::draw2d::region * prgnUpdate = nullptr, unsigned int flags = 0) override;

      //#endif


      //#ifdef WINDOWS_DESKTOP
      //
      //      virtual bool EnableScrollBar(int nSBFlags,unsigned int nArrowFlags = ESB_ENABLE_BOTH);
      //
      //#else

            //virtual void EnableScrollBar(int nSBFlags,unsigned int nArrowFlags = 3);

      //#endif


            //virtual ::int_point get_cursor_position() const override;

      //void set_mouse_cursor(::windowing::cursor * pcursor) override;

      //virtual void set_cursor(enum_cursor ecursor) override;

      //virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,const int_rectangle & prc,unsigned int uFlags);


//#if(WINVER >= 0x0500)
//
//      virtual bool AnimateWindow(const class time & time,unsigned int dwFlags);
//
//#endif


//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics,unsigned int nFlags) const;
//
//#endif


//#if(_WIN32_WINNT >= 0x0500)
//
//      virtual bool SetLayeredWindowAttributes(::color::color crKey,unsigned char bAlpha,unsigned int dwFlags);
//      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst,::int_point *pptDst,::int_size *psize,::draw2d::graphics * pDCSrc,::int_point *pptSrc,::color::color crKey,BLENDFUNCTION *pblend,unsigned int dwFlags);
//
//#endif   // _WIN32_WINNT >= 0x0500

//#if(_WIN32_WINNT >= 0x0501)
//
//      virtual bool GetLayeredWindowAttributes(::color::color *pcrKey,unsigned char *pbAlpha,unsigned int *pdwFlags) const;
//
//#endif   // _WIN32_WINNT >= 0x0501
//


      //virtual bool is_window_enabled() const override;
      //void enable_window(bool bEnable = true) override;





      //virtual void CheckDlgButton(int nIDButton,unsigned int nCheck);
      //virtual void CheckRadioButton(int nIDFirstButton,int nIDLastButton,
      //                              int nIDCheckButton);
      //virtual int GetCheckedRadioButton(int nIDFirstButton,int nIDLastButton);
      //virtual int DlgDirList(char * pPathSpec,int nIDListBox,

      //                       int nIDStaticPath,unsigned int nFileType);
      //virtual int DlgDirListComboBox(char * pPathSpec,int nIDComboBox,

      //                               int nIDStaticPath,unsigned int nFileType);
      //virtual bool DlgDirSelect(char * pString,int nSize,int nIDListBox);

      //virtual bool DlgDirSelectComboBox(char * pString,int nSize,int nIDComboBox);


      //virtual unsigned int GetChildByIdInt(int nID,bool* pTrans = nullptr,bool bSigned = true) const;

      //virtual int GetChildByIdText(int nID,char * pStr,int nMaxCount) const;

      //virtual int GetChildByIdText(int nID,string & rString) const;
      //virtual ::windowing::window * GetNextDlgGroupItem(::windowing::window * pWndCtl,bool bPrevious = false) const;
      //virtual ::windowing::window * GetNextDlgTabItem(::windowing::window * pWndCtl,bool bPrevious = false) const;
      //virtual unsigned int IsDlgButtonChecked(int nIDButton) const;
      //virtual lresult SendDlgItemMessage(int nID,unsigned int message,wparam wParam = 0,lparam lParam = 0);
      //virtual void SetDlgItemInt(int nID,unsigned int nValue,bool bSigned = true);
      //virtual void SetDlgItemText(int nID, const ::string & pszString);


      //virtual int GetScrollPos(int nBar) const;
      //virtual void GetScrollRange(int nBar, int * pMinPos, int * lpMaxPos) const;
      //virtual void ScrollWindow(int xAmount,int yAmount,
      //   const ::int_rectangle * rectangle = nullptr,
      //   const ::int_rectangle * pClipRect = nullptr);

      //virtual int SetScrollPos(int nBar,int nPos,bool bRedraw = true);
      //virtual void SetScrollRange(int nBar, int nMinPos, int nMaxPos, bool bRedraw = true);
      //virtual void ShowScrollBar(unsigned int nBar,bool bShow = true);
      //virtual void EnableScrollBarCtrl(int nBar,bool bEnable = true);

      //virtual int ScrollWindowEx(int Δx,int Δy, const ::int_rectangle * prectScroll, const ::int_rectangle * lprectClip, ::draw2d::region* prgnUpdate, ::int_rectangle * prectUpdate, unsigned int flags);


//#ifdef WINDOWS_DESKTOP
//
//      virtual bool SetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, bool bRedraw = true);
//      virtual bool GetScrollInfo(int nBar, LPSCROLLINFO pScrollInfo, unsigned int nMask = SIF_ALL);
//
//#endif


      //virtual int GetScrollLimit(int nBar);

//#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)
//
//      virtual bool GetScrollBarInfo(int idObject,PSCROLLBARINFO psbi) const;
//
//#endif   // WINVER >= 0x0500

      virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags) override;

      //#ifdef WINDOWS_DESKTOP
        //    virtual ::user::interaction * get_next_window(unsigned int nFlag = GW_HWNDNEXT);
      //#else
      //      virtual ::user::interaction * get_next_window(unsigned int nFlag = 0) override;
      //#endif



      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * GetLastActivePopup() override;

      //bool FlashWindow(bool bInvert);

      //virtual int message_box(const ::string & pszText, const ::string & pszCaption = nullptr,unsigned int nType = e_message_box_ok);


//#if(WINVER >= 0x0500)
//
//      // virtual bool FlashWindowEx(unsigned int dwFlags, unsigned int  uCount, class ::time tickTimeout);
//
//#endif   // WINVER >= 0x0500

      //virtual bool ChangeClipboardChain(::windowing::window * pwindow_Next);
      //virtual oswindow SetClipboardImpacter();
      //virtual bool OpenClipboard();

      //virtual void HideCaret();
      //virtual void ShowCaret();

      //virtual void DragAcceptFiles(bool bAccept = true);

      //virtual bool SetWindowContextHelpId(unsigned int dwContextHelpId);
      //virtual unsigned int GetWindowContextHelpId() const;


      void update_data(bool bSaveAndValidate = true) override;


      void UpdateDialogControls(channel * pTarget, bool bDisableIfNoHndler);
      void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_pos_create);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(_001OnPrint);
      DECLARE_MESSAGE_HANDLER(_001OnCaptureChanged);
      DECLARE_MESSAGE_HANDLER(_001OnPrioCreate);

#ifdef WINDOWS_DESKTOP

      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanged);

#endif




      virtual void BeginModalState();
      virtual void EndModalState();

      virtual void pre_translate_message(::message::message * pmessage) override;

      //virtual void message_handler(::message::message * pusermessage) override;
      virtual void _message_handler(::message::message * pusermessage);
      //virtual lresult default_window_procedure() override;
      virtual void default_window_procedure(::message::message * pmessage);


      virtual bool on_mouse_message(::message::mouse * pmouse);


      //virtual void post_non_client_destroy() override;
      //virtual bool OnChildNotify(::message::message * pusermessage) override;
      virtual bool ReflectChildNotify(::message::message * pusermessage);
      //virtual void CheckAutoCenter() override;


      virtual bool HandleFloatingSysCommand(unsigned int nID, lparam lParam);
      //bool IsTopParentActive() override;
      void ActivateTopParent() override;
      virtual void on_final_release();


      //virtual bool _EnableToolTips(bool bEnable,unsigned int nFlag);
      //virtual void PrepareForHelp();


      // for creating dialogs and dialog-like windows
      //virtual bool CreateDlg(const ::string & pszTemplateName, ::windowing::window * puiParent);

      //virtual bool CreateDlgIndirect(LPCDLGTEMPLATE pDialogTemplate, ::windowing::window * puiParent,

      // HINSTANCE hInst);



      //// standard message implementation
      //lresult OnNTCtlColor(wparam wParam,lparam lParam);
      //lresult OnDisplayChange(wparam,lparam);
      //lresult OnDragList(wparam,lparam);

      virtual void _001DeferPaintLayeredWindowBackground(::image::image * pimage);

      virtual void _001OnDeferPaintLayeredWindowBackground(::image::image * pimage);

      //virtual int get_window_long(int nIndex) const override;
      //virtual int set_window_long(int nIndex,int lValue) override;
      //virtual iptr get_window_long_ptr(int nIndex) const override;
      //virtual iptr set_window_long_ptr(int nIndex, iptr lValue) override;

      //virtual interaction_impl * get_impl() const;

      virtual void _001UpdateWindow() override;


      // deprecated schedule window visual
      //virtual void start_window_visual() override;
      //virtual void sketch_to_design(::draw2d::graphics_pointer& pgraphics, bool & bUpdateBuffer, bool & bUpdateWindow) override;
      //virtual void do_graphics();
      //void _001OnNcClip(::draw2d::graphics_pointer & pgraphics) override;
      //void defer_do_graphics(::draw2d::graphics_pointer & pgraphics) override;
      //void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics) override;
      // call window window_update_screen_buffer
      //virtual void _001UpdateScreen();
      //virtual void window_apply_visual(const window_state & windowstate) override;


      //virtual void update_graphics_resources();


      //virtual void set_handle(::windowing::window * pwindow);


      //::oswindow oswindow() const;


      //::graphics::graphics * get_window_graphics() override;


      //bool is_composite() override;


      void set_finish() override;


      //void top_down_prefix() override;

      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_start_layout_experience(enum_layout_experience elayoutexperience) override;

      //virtual void on_configuration_change(::user::interaction_base * pprimitiveSource) override;

      ::user::element * get_keyboard_focus() override;
      //virtual void set_keyboard_focus(::user::interaction_base * pprimitive) override;
      //virtual void erase_keyboard_focus(::user::interaction_base * pprimitive) override;
      //void clear_keyboard_focus(::user::primitive_impl * pprimitiveimplGainingFocusIfAny = nullptr) override;
      //virtual void impl_set_keyboard_focus(::user::interaction_base * pprimitive) override;
      //virtual void impl_erase_keyboard_focus(::user::interaction_base * pprimitive) override;
      //virtual void impl_clear_keyboard_focus() override;

      //virtual void redraw_add(::particle * pparticle) override;
      //virtual void redraw_erase(::particle * pparticle) override;
      //virtual bool has_redraw() override;
      virtual ::particle * mutex_redraw();

      //virtual void _001OnTriggerMouseInside() override;

      //bool has_pending_graphical_update() override;

      virtual void on_after_graphical_update() override;

      //virtual bool is_this_visible(enum_layout elayout) override;

      //void _window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation) override;

      //void _window_request_presentation_locked() override;
      //void _window_request_presentation_unlocked() override;




      virtual void ShowWindow(const ::e_display & edisplay);

      //virtual bool check_need_layout() override;
//virtual void clear_need_layout() override;
      //virtual void set_need_layout() override;

      //virtual bool window_move(int x, int y) override;

      //virtual bool check_show_flags() override;

      //virtual void on_visual_applied();

      virtual void set_need_redraw(const ::int_rectangle_array & rectangleaHostNeedRedraw = {}, function<void()> function = nullptr, bool bAscendants = true);
      //virtual bool needs_to_draw(const ::int_rectangle& rectangleHostNeedsToDraw, ::draw2d::graphics_pointer & pgraphics);
      void post_redraw(bool bAscendants = true) override;


      //virtual void user_interaction_on_hide() override;

      void show_software_keyboard(::user::element * pelement) override;

      void hide_software_keyboard(::user::element * pelement) override;


      // Occlusion and Translucency
      virtual bool is_occluded();
      virtual huge_integer approximate_occlusion_area();
      virtual double approximate_occlusion_rate();
      virtual huge_integer approximate_occlusion_area_except_self_transparent();
      virtual double approximate_occlusion_rate_except_self_transparent();
      virtual huge_integer _001GetTopLeftWeightedOccludedOpaqueArea();
      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;
      virtual huge_integer _001GetTopLeftWeightedArea();
      virtual huge_integer _001GetRectTopLeftWeightedArea(const ::int_rectangle & rect);

      virtual huge_integer opaque_area(const ::int_rectangle & rect);
      virtual void approximate_occlusion_rects(int_rectangle_array & raTest);

      virtual huge_integer opaque_area();

      /// from top to bottom
      //virtual void non_top_most_upper_window_rects(::int_rectangle_array & recta);


      virtual void android_fill_plasma(const void * pixels, int width, int height, int stride, huge_integer time_ms);

      //void set_opacity(double dOpacity) override;


      // ::user::primitive_impl


      inline critical_section * cs_display() { return m_pcsDisplay; }
      //virtual ::windowing::window * get_user_interaction_impl();
      //virtual ::user::interaction_child * get_user_interaction_child();


      //::aura::application * get_app();
      //::aura::session * get_session();
      //::aura::system* system();

      void set_user_interaction(::acme::user::interaction * pacmeuserinteraction) override;
      void set_user_thread(::user::thread * puserthread) override;
      void set_user_graphics_thread(::user::graphics_thread * pusergraphicsthread) override;


      virtual void prio_install_message_routing(::channel * pchannel);
      virtual void last_install_message_routing(::channel * pchannel);

      //virtual void default_message_handler(::message::message * pusermessage);

      virtual void queue_message_handler(::message::message * pmessage);


      virtual ::pointer<::message::message>get_message(const ::atom & atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype = ::message::e_prototype_none) override;


      //virtual void enable_window(bool bEnable = true);




      //virtual void create_host(::user::interaction * puserinteraction, enum_parallelization eparallelization);

      //virtual void create_host(::user::interaction * puserinteraction);
      virtual void create_child(::user::interaction * puserinteraction, ::user::interaction_base * puserprimitiveParent);


      //virtual void defer_do_graphics(::draw2d::graphics_pointer & pgraphics);


      virtual void top_down_prefix();
      //virtual bool check_need_layout();
      //virtual void clear_need_layout();
      virtual void set_need_layout();
      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics);
      void on_reposition() override;
      virtual void on_layout_reposition();

      virtual void on_show_window();


      ::oswindow detach_window() override;

      //void destroy() override;

      //virtual void _window_show_change_visibility_locked();
      //virtual void _window_show_change_visibility_unlocked(::e_display edisplay, const ::user::activation & useractivation);
      //virtual void _window_request_presentation_locked();
      //virtual void _window_request_presentation_unlocked();

      virtual void create_message_queue(::user::interaction * pinteraction, const ::string & lpszName);

      //virtual void graphics_thread_update_screen();

      //virtual void RepositionBars(unsigned int nIDFirst, unsigned int nIDLast, ::atom nIdLeftOver, unsigned int nFlag = reposDefault, ::int_rectangle * prectParam = nullptr, const ::int_rectangle & rectangleX = nullptr, bool bStretch = true);

      virtual void window_move(int x, int y);


      virtual void on_configure(const ::int_rectangle & rectangle);
      //\virtual void on_resize(const ::int_size & size);




      //virtual void set_bitmap_source(const string & strBitmapSource);
      //virtual void clear_bitmap_source();

      //virtual void set_tool_window(bool bSet);

      virtual void interaction_post(const ::procedure & procedure);

      //virtual void _000OnMouseLeave(::message::message * pmessage);

      //virtual void track_mouse_hover();
      virtual void track_mouse_leave() override;



      //virtual void add(::graphics::output_purpose * poutputpurpose);
      //virtual void erase(::graphics::output_purpose * poutputpurpose);
      //virtual void add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose);
      //virtual void erase_graphical_output_purpose(::particle * pparticle);
      //virtual bool has_particle_fps_purpose(::particle * pparticle);
      ////virtual ::graphics::enum_output_purpose most_demanding_graphical_output_purpose() const;
      //virtual bool has_screen_output_purpose() const;
      //virtual bool has_graphical_output_purpose() const;
      //virtual bool has_fps_output_purpose() const;

      //virtual void add_fps_interest(::particle* pparticle);
      //virtual void erase_fps_interest(::particle * pparticle);
      //virtual bool is_fps_interest(const ::particle * pparticle) const;


      //virtual void fps_interest_stop();


      virtual ::user::interaction_base * set_owner(::user::interaction_base * pprimitiveOwner);


      //virtual bool has_pending_redraw_flags();


      //      virtual void add(::graphics::output_purpose * pgraphicaloutputpurpose);
      //      virtual void add_graphical_output_interest(::particle * pparticle, ::graphics::enum_output_purpose epurpose);
      //      virtual void erase_graphical_output_interest(::particle * pparticle);
      //      virtual bool does_particle_has_fps_interest(const ::particle * pparticle) const;
      //      virtual ::graphics::enum_output_purpose most_demanding_graphical_output_purpose() const;
      //      virtual bool has_screen_graphical_output_purpose() const;
      //      virtual bool has_graphical_output_purpose() const;
      //      virtual bool has_fps_graphical_output_purpose() const;


      //virtual void pre_subclass_window();


      //virtual void destroy_impl_only();
      //virtual void start_destroying_window();
      //virtual void destroy_window();


      //virtual bool _is_window();


      //virtual ::lresult send_message(const ::atom & atom, ::wparam wparam = 0, ::lparam lparam = 0, const ::int_point & point = {});

      //virtual ::lresult send_message(::message::message * pmessage);

      using ::channel::message_handler;

      virtual lresult message_handler(const ::atom & atom, wparam wparam = 0, lparam lparam = 0) override;


      //virtual void post_message(const ::atom & atom, wparam wparam = 0, ::lparam lparam = 0);

      //virtual void post_message(::message::message * pusermessage);

      //virtual void set_window_text(const ::string& pszString);

      virtual void on_set_window_text();


      //virtual character_count get_window_text(char* pszStringBuf, character_count nMaxCount);


      //virtual void get_window_text(string& rString);


      //virtual character_count get_window_text_length();


      //virtual void UpdateWindow();
      //virtual void SetRedraw(bool bRedraw = true);


      //virtual void graphics_thread_redraw(bool bUpdateBuffer);


      //virtual void set_mouse_cursor(::windowing::cursor * pcursor);


      //virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point);
      //virtual ::user::interaction * ChildWindowFromPoint(const ::int_point & point, unsigned int nFlags);


      //virtual ::user::interaction * GetLastActivePopup();


      //virtual void update_data(bool bSaveAndValidate = true);


      //virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr);


      virtual bool OnChildNotify(::message::message * pusermessage);


      //virtual void ActivateTopParent();


      //virtual void _001UpdateWindow();


      virtual void on_start_layout_experience(enum_layout_experience elayoutexperience);
      virtual void on_end_layout_experience(enum_layout_experience elayoutexperience);


      virtual void on_configuration_change(::user::interaction_base * pprimitiveSource);


      //virtual ::user::element* get_keyboard_focus();


      virtual void _001OnAfterExitIconic() override;
      virtual void _001OnAfterExitNormal() override;
      virtual void _001OnAfterExitZoomed() override;
       virtual void _001OnAfterExitFullScreen() override;


      //virtual void _001OnTriggerMouseInside();


      virtual bool has_pending_graphical_update();


      //virtual void on_after_graphical_update();


      virtual bool is_this_visible(::user::enum_layout elayout) override;


      //virtual void post_redraw(bool bAscendants = true);


      //virtual double _001GetTopLeftWeightedOccludedOpaqueRate();


      //virtual ::windowing::window* get_window() const;


      //virtual bool keyboard_focus_OnKillFocus(::oswindow oswindowNew);
      //virtual bool keyboard_focus_OnChildKillFocus();


      virtual void edit_on_set_focus(::user::interaction * pinteraction) override;


      virtual void edit_on_kill_focus(::user::interaction * pinteraction) override;


      //virtual void show_software_keyboard(::user::element * pelement);
      //virtual void hide_software_keyboard(::user::element * pelement);


      virtual ::user::interaction * get_child_by_id(const ::atom & atom, ::collection::index iItem = -1, int iLevel = -1) override;


      //virtual void set_need_redraw(const ::int_rectangle_array & rectangleaNeedRedraw = {}, function<void()> function = nullptr, bool bAscendants = true);


      //virtual bool RedrawWindow(const ::int_rectangle & rectangleUpdate = {}, ::draw2d::region * prgnUpdate = nullptr, unsigned int flags = 0);


      //virtual int GetUpdateRgn(::draw2d::region* pRgn, bool bErase = false);
      //virtual void Invalidate(bool bErase = true);
      //virtual void InvalidateRect(const ::int_rectangle& rectangle, bool bErase = true);

      //virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = true);
      //virtual void ValidateRect(const ::int_rectangle& rectangle);

      //virtual void ValidateRgn(::draw2d::region* pRgn);
      //virtual void ShowOwnedPopups(bool bShow = true);


      virtual ::graphics::graphics * get_window_graphics();
      virtual bool is_composite();


      //virtual void _task_transparent_mouse_event();

      //virtual void _001OnNcClip(::draw2d::graphics_pointer & pgraphics);
      //virtual void _000CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics);


      virtual ::user::interaction * get_wnd() override;


      virtual void set_origin(::draw2d::graphics_pointer & pgraphics);


      virtual void viewport_screen_to_client(::sequence2_int & sequence) override;
      virtual void viewport_client_to_screen(::sequence2_int & sequence) override;
      virtual void viewport_client_to_screen(::int_rectangle & rectangle) override;
      virtual void viewport_screen_to_client(::int_rectangle & rectangle) override;


      //virtual unsigned int GetStyle() const;
      //virtual unsigned int GetExStyle() const;
      //virtual void ModifyStyle(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0);
      //virtual void ModifyStyleEx(unsigned int dwRemove,unsigned int dwAdd,unsigned int nFlags = 0);

      //virtual int get_window_long(int nIndex) const;
      //virtual int set_window_long(int nIndex,int lValue);

      //virtual iptr get_window_long_ptr(int nIndex) const;
      //virtual void set_window_long_ptr(int nIndex, iptr lValue);

      virtual atom GetDlgCtrlId() const override;
      virtual ::atom SetDlgCtrlId(const ::atom & atom) override;

      virtual ::user::interaction * first_child() override;
       virtual ::user::interaction * top_child() override;
      virtual ::user::interaction * under_sibling() override;
      virtual ::user::interaction * above_sibling() override;

      virtual ::user::interaction * above_sibling(::user::interaction * pinteraction) override;
      virtual ::user::interaction * under_sibling(::user::interaction * pinteraction) override;


      //virtual unsigned int ArrangeIconicWindows();
      //virtual void BringToTop(::e_display edisplay);
      //virtual bool BringWindowToTop();


      virtual bool is_ascendant(::user::element * puiIsAscendant, bool bIncludeSelf) override;
      virtual bool is_parent(::user::element * puiIsParent) override;
      virtual bool is_child(::user::element * puiIsChild) override;
      virtual bool is_descendant(::user::element * puiIsDescendant, bool bIncludeSelf) override;


      //      virtual ::user::interaction * get_wnd();
      virtual ::user::interaction * get_wnd(unsigned int nCmd) override;


      virtual ::user::frame_interaction * frame();
      virtual ::user::frame_interaction * top_level_frame();


      //virtual ::user::interaction * GetTopWindow() const;
      //virtual ::user::interaction * get_parent();
      //virtual ::user::interaction * top_level();
      //virtual ::user::interaction * GetParentTopLevel() const;
      //virtual ::user::interaction * EnsureTopLevel();
      //virtual ::user::interaction * EnsureParentTopLevel();
      virtual ::user::interaction * get_owner() override;
      virtual ::user::interaction * get_parent_owner() override;
      virtual ::user::interaction * get_parent_or_owner() override;
      virtual ::user::interaction * get_top_level_owner() override;
      inline ::user::frame_interaction * parent_frame();
      //virtual ::user::frame_interaction * GetParentTopLevelFrame() const;
      //virtual ::user::frame_interaction * EnsureParentFrame();


      virtual lresult message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::int_point & point = {}) override;
      virtual lresult message_call(::message::message * pmessage) override;

      virtual void send_message_to_descendants(const ::atom & atom, wparam wParam = 0, lparam lParam = 0, bool bDeep = true, bool bOnlyPerm = false) override;



      //virtual void pre_translate_message(::message::message * pmessage);


      //virtual bool is_active() const;

      //virtual bool has_capture() const;
      //virtual bool set_capture(::user::interaction * pinteraction = nullptr);
      //virtual ::user::interaction * get_capture() const;

      //virtual bool has_keyboard_focus() const;
      //virtual bool set_keyboard_focus(::user::interaction * pinteraction = nullptr) ;
      //virtual ::user::interaction * get_keyboard_focus() const ;




      //virtual bool get_rect_normal(::int_rectangle * prectangle);


      //virtual void SetTimer(uptr uEvent, const class ::time & millisElapse, PFN_TIMER pfnTimer = nullptr, bool bPeriodic = true, void * pdata = nullptr) override;
      //virtual void KillTimer(uptr uEvent) override;



      //void on_timer(::timer * ptimer) override;

      virtual bool IsTopParentActive();

      //virtual void destroy_impl_only();
      //void start_destroying_window();


      //virtual void defer_start_fps_interest();
      //virtual void _defer_start_fps_interest();


      //virtual void mouse_hover_add(::user::interaction * pinterface);
      //virtual bool mouse_hover_erase(::user::interaction * pinterface);


      virtual void register_drop_target();


      //::windowing::window * window();


      //virtual ::user::element * get_keyboard_focus();
      virtual void set_keyboard_focus(::user::interaction * puserinteraction);
      virtual void erase_keyboard_focus(::user::interaction * puserinteraction);
      virtual void clear_keyboard_focus(::user::interaction * puserinteractionGainingFocusIfAny = nullptr);
      virtual void impl_set_keyboard_focus(::user::interaction * puserinteraction);
      virtual void impl_erase_keyboard_focus(::user::interaction * puserinteraction);
      virtual void impl_clear_keyboard_focus();


      //virtual void post_message(const ::atom & atom, ::wparam wparam = 0, lparam lparam = 0);

      //virtual void post_non_client_destroy();

      //void display(::display edisplay);

      //DECLARE_MESSAGE_HANDLER(_001OnPrioCreate);
      //DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_destroy);

      //virtual void show_task(bool bShow);

      virtual void redraw_add(::particle * pparticle);
      virtual void redraw_erase(::particle * pparticle);
      virtual bool has_redraw();


      virtual void user_interaction_on_hide();


#ifdef LINUX


      virtual lresult send_x11_event(void * phappening);


#endif


      virtual void _raw_client_to_screen(::int_point & point);
      virtual void _raw_screen_to_client(::int_point & point);


      //::trace_statement & trace_statement_prefix(::trace_statement & statement) const override;


      //void user_send(const ::procedure & procedure) override;
      //void user_post(const ::procedure & procedure) override;

      //void main_send(const ::procedure & procedure) override;
      //void main_post(const ::procedure & procedure) override;

      //virtual void set_opacity(double dOpacity);

      ::windowing::window * windowing_window() override;

         virtual bool on_configure_unlocked_timer();

   };


   //class CLASS_DECL_AURA guie_message_wnd :
   //   virtual public interaction_impl
   //{
   //public:


   //   ::user::interaction * m_puiForward;


   //   guie_message_wnd(::property_object * pparticle);


   //   virtual void message_handler(::message::message * pmessage);


   //}; // guie_message_wnd



   class device_draw_life_time
   {
   public:
      
      
      ::windowing::window * m_pimpl;
      
      
      device_draw_life_time(::windowing::window * pimpl) :
      m_pimpl(pimpl)
      {
         
         m_pimpl->m_timeDeviceDrawBeg.Now();
         
      }
      
      
      ~device_draw_life_time()
      {
         
         m_pimpl->m_timeDeviceDrawEnd.Now();
         
      }
      
   };


} // namespace windowing


