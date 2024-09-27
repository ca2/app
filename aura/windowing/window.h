// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


#include "apex/message/channel.h"
#include "acme/prototype/collection/osdata_array.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/windowing/window_base.h"


namespace windowing
{


   class CLASS_DECL_AURA window :
      virtual public ::channel,
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
         ::point_i32                               m_pointMouseMoveSkip;
         class ::time                              m_timeMouseMovePeriod;
         ::point_i32                               m_pointMouseMove;
         class ::time                              m_timeMouseMove;
         class ::time                              m_timeMouseMoveIgnore;
         //bool                                      m_bMouseMovePending;
         
      };

      bool                                      m_bMessageOnlyWindow : 1;


      ::sandbox_windowing::window *             m_psandboxwindowingwindow;
      void *                                    m_pWindow4;

      ::pointer<::windowing::display>           m_pdisplay;
      ::pointer<::user::interaction_impl>       m_puserinteractionimpl;
      string                                    m_strDebug;
      ::pointer<::message_queue>                m_pmessagequeue;
      class ::time                              m_timeLastMouseMove;
      ::pointer<::windowing::window>            m_pwindowParent;

      mouse_reposition_throttling               m_mouserepositionthrottling;
      
      ::pointer<::windowing::icon>              m_picon;
      ::pointer<::windowing::windowing>         m_pwindowing;
      ::pointer<::user::copydesk>               m_pcopydesk;
      ::pointer<::windowing::cursor>            m_pcursor;
      //::oswindow                                m_oswindow;
      bool                                      m_bUpdateScreenSynchronously;
      
      bool                                      m_bActiveWindow;
      bool                                      m_bKeyboardFocus;
      ::pointer < class placement_log >         m_pplacementlog;
      ::pointer < ::particle >                  m_pparticleChildrenSynchronization;

      window();
      ~window() override;


      void user_common_construct();

      void on_initialize_particle() override;

      
      virtual void window_on_activate();
      virtual void window_on_deactivate();
      virtual void window_on_set_keyboard_focus();
      virtual void window_on_kill_keyboard_focus();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      ::aura::application* get_app();
      ::aura::session* get_session();
      //::aura::system* system();


      void install_message_routing(::channel * pchannel) override;

      
      virtual void call_create_window(::user::interaction_impl * puserinteractionimpl);

      //virtual void create_window(::user::interaction_impl * pimpl);
      
      virtual void create_window();

      virtual void on_finished_window_creation();


      //virtual void set_cursor_position(const ::point_i32 & pointCursor);

      //virtual void get_cursor_position(::point_i32 * ppointCursor);

      //inline ::point_i32 get_cursor_position() { ::point_i32 point; get_cursor_position(&point); return point; }


      //virtual bool defer_set_icon();

      virtual class placement_log* placement_log();

      virtual double get_top_margin();
      

      virtual void set_keyboard_focus();
      virtual void _set_keyboard_focus_unlocked();

      virtual void set_mouse_capture();
      virtual bool defer_release_mouse_capture();

      virtual void bring_to_front();

      virtual void switch_to_this_window(bool b);

      virtual void graphics_lock();
      virtual void graphics_unlock();


      virtual bool has_mouse_capture() const;
      virtual bool has_keyboard_focus() const;

      virtual ::color::color screen_pixel(int x, int y) const;

      virtual bool is_full_screen() const;

      virtual ::windowing::display * display();

      virtual ::user::copydesk * copydesk();

      virtual ::oswindow oswindow() const;
      virtual void set_oswindow(::oswindow oswindow);
      virtual void _set_oswindow(::oswindow oswindow);


      

      inline ::windowing::windowing * windowing() { return m_pwindowing; }
      inline ::windowing::windowing * windowing() const { return m_pwindowing.m_p; }


      virtual void exit_iconify();

      virtual void full_screen(const::rectangle_i32 & rectangle = {});

      virtual void exit_full_screen();

      virtual void exit_zoomed();

      virtual void destroy_window();

      void on_destroy() override;

      //virtual void show_window(const ::e_display & edisplay, const ::e_activation & eactivation);

      //virtual void _show_window_unlocked(const ::e_display & edisplay, const ::e_activation & eactivation);

      virtual void set_user_interaction(::user::interaction *pinteraction);

      virtual void post_non_client_destroy();

      virtual bool is_child_of(const window * pwindowAscendantCandidate) const; // or descendant
      
      
      virtual ::windowing::window * get_parent() const;
      virtual ::oswindow get_parent_oswindow() const;
      virtual void set_parent(::windowing::window * pwindowNewParent);



      
      virtual ::windowing::window * get_owner() const;
      virtual ::oswindow get_owner_oswindow() const;
      virtual void set_owner(::windowing::window * pwindowNewOwner);


      virtual bool is_iconic();
      virtual bool is_zoomed();
      virtual bool is_window();
      virtual bool is_window_visible();

      virtual bool _is_iconic_unlocked();
      virtual bool _is_window_visible_unlocked();
      

      virtual bool client_to_screen(::point_i32 * ppoint);

      virtual bool screen_to_client(::point_i32 * ppoint);


      virtual bool on_set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay);

      virtual bool set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay);
      virtual bool _set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay, ::u32 nOverrideFlags = 0);

      virtual bool configure_window_unlocked();
      virtual bool strict_set_window_position_unlocked(bool & bChangedPosition, bool & bChangedSize);
      virtual bool strict_set_window_position_unlocked(bool & bChangedPosition, bool & bChangedSize, const ::rectangle_i32 & rectangle);
      virtual bool full_set_window_position_unlocked();
      virtual bool _set_window_position_unlocked(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay);
      virtual bool _configure_window_unlocked(const class ::zorder& zorder, const ::e_activation& eactivation, bool bNoZorder, ::e_display edisplay);
      virtual bool _strict_set_window_position_unlocked(i32 x, i32 y, i32 cx, i32 cy, bool bNoMove, bool bNoSize);

      virtual bool is_destroying();


      virtual void activate_top_parent();


      void message_handler(::message::message* pusermessage) override;


      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      virtual void present();

      //virtual bool presentation_complete();


      //virtual void on_visual_applied();

      virtual void _on_configure_notify_unlocked(const ::rectangle_i32 & rectangle);
      virtual void _on_reposition_notify_unlocked(const ::point_i32 & point);


      virtual void win_update_graphics();

      virtual lresult send_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr);

      virtual void post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr);


      virtual void set_window_text(const ::scoped_string & scopedstr);

      //::string get_window_text() override;

      //virtual void get_window_text(string & rectangleString);
      //virtual strsize get_window_text_length();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual ::u32 ArrangeIconicWindows();

      virtual void rects_from_os();
      virtual bool window_rect_from_os(::rectangle_i32 * prectangle);
      virtual bool client_rect_from_os(::rectangle_i32 * prectangle);


      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      virtual bool GetUpdateRect(::rectangle_i32 * prectangle, bool bErase = false);

      virtual i32 GetUpdateRgn(::draw2d::region * pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true);
      virtual void InvalidateRect(const ::rectangle_i32 * rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region * pRgn, bool bErase = true);
      virtual void ValidateRect(const ::rectangle_i32 * rectangle_i32);

      virtual void ValidateRgn(::draw2d::region * pRgn);


      virtual void ShowOwnedPopups(bool bShow = true);

      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();


      virtual bool RedrawWindow(const ::rectangle_i32 & rectangleUpdate = {}, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = 0);

      // Window State Functions
      virtual bool is_this_enabled();
      virtual void enable_window(bool bEnable = true);

      // the active interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * get_active_window();
      virtual void set_active_window();
      virtual void _set_active_window_unlocked();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      virtual void set_foreground_window();
      virtual void _set_foreground_window_unlocked();
      virtual ::user::interaction * get_foreground_window();

      virtual bool is_active_window() const;

      virtual ::user::interaction * get_desktop_window();


      virtual ::windowing::window * get_next_window(::u32 nFlag = 0);
      virtual ::windowing::window * get_top_window() const;

      virtual ::windowing::window * get_window(::u32 nCmd) const;
      virtual ::windowing::window * get_last_active_popup() const;


      virtual point_i32 GetCaretPos();
      virtual void SetCaretPos(const ::point_i32 & point);
      virtual void HideCaret();
      virtual void ShowCaret();

      virtual void DragAcceptFiles(bool bAccept = true);


      virtual ::pointer<::windowing::icon>load_icon(const ::payload& payloadFile);


      virtual void set_icon(::windowing::icon * picon);
      virtual ::pointer<::windowing::icon>get_icon() const;


      virtual void set_mouse_cursor(::windowing::cursor * pcursor);
      virtual ::windowing::cursor * get_mouse_cursor();


      //virtual ::point_i32 get_mouse_cursor_host_position();
      
      //virtual ::point_i32 get_mouse_cursor_absolute_position();


      virtual void set_tool_window(bool bSet);


      void set_context_org(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(::rectangle_i32 * prectangle);
      virtual void _window_show_change_visibility(::e_display edisplay, ::e_activation eactivation);


      virtual void non_top_most_upper_window_rects(::rectangle_i32_array & recta);

      virtual void default_message_handler(::message::message * pmessage);

      virtual void track_mouse_hover();


      virtual void _task_transparent_mouse_event();


      virtual float get_dpi_for_window();

      virtual float get_density_for_window();


      virtual float point_dpi(float points);

      virtual float y_dpi(float y);
      virtual float x_dpi(float x);

      virtual float dpiy(float y);
      virtual float dpix(float x);


      virtual void on_redraw_window(::u32 flags);


      virtual void show_task(bool bShowTask);


      virtual void __update_graphics_buffer();
      //virtual void window_request_presentation();

      //virtual void _window_request_presentation_locked();
      //virtual void _window_request_presentation_set_window_position_unlocked(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide);
      
      virtual void frame_toggle_restore();

      void user_send(const ::procedure & procedure) override;
      void user_post(const ::procedure & procedure) override;

      bool is_branch_current() const override;

      
      itask_t get_itask() const;


      virtual void on_touch_down(int xHost, int yHost, int xAbsolute, int yAbsolute);
      virtual void on_touch_drag(int xHost, int yHost, int xAbsolute, int yAbsolute);
      virtual void on_touch_up(int xHost, int yHost, int xAbsolute, int yAbsolute);

      virtual void on_size(int w, int h);

      virtual void on_text(const ::ansi_character * pansisz, strsize length);
      virtual void on_text(const ::wd16_character * pwd16sz, strsize length);
      virtual void on_text(const ::wd32_character * pwd32sz, strsize length);


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

      virtual bool defer_perform_entire_reposition_process(::user::mouse * pmouse);

      virtual bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse);

      virtual void on_destruct_mouse_message(::message::mouse * pmouse);


      ::trace_statement & trace_statement_prefix(::trace_statement & statement) const override;


      bool is_satellite_window() override;
      bool is_windowing_popup() override;
      ::point_i32 windowing_popup_origin() override;
      ::size_i32 windowing_popup_size() override;
      void _on_windowing_close_window() override;
      ::windowing::window_base * owner_window() override;
      ::string get_window_text() override;


      virtual void defer_show_system_menu(::user::mouse * pmouse);

      virtual void pick_browse(const ::function < void(const ::file::path & path) > & callback);
      virtual void pick_media(const char * pszMediaType);
      virtual void on_prompt_write_file(::user::controller * pusercontroller);


      virtual void set_opacity(double dOpacity);

      void window_restore() override;
      void window_minimize() override;
      void window_maximize() override;

      void destroy() override;

      virtual void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem);


      void main_send(const ::procedure & procedure) override;

   };


} // namespace windowing


