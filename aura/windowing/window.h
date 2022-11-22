// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


#include "apex/message/channel.h"
#include "acme/primitive/collection/osdata_array.h"
#include "acme/primitive/geometry2d/_collection.h"


namespace windowing
{


   class CLASS_DECL_AURA window :
      virtual public ::channel,
      virtual public osdata_array
   {
   public:


      bool                                      m_bMessageOnlyWindow : 1;


      ::sandbox_windowing::window *             m_psandboxwindowingwindow;
      void *                                    m_pWindow4;

      ::pointer<::windowing::display>          m_pdisplay;
      ::pointer<::user::interaction_impl>      m_puserinteractionimpl;
      string                                    m_strDebug;
      ::pointer<::message_queue>               m_pmessagequeue;
      ::duration                                m_durationLastMouseMove;
      ::pointer<::windowing::window>           m_pwindowParent;
      ::point_i32                               m_point;
      ::size_i32                                m_size;
      ::pointer<::windowing::icon>             m_picon;
      ::pointer<::windowing::windowing>        m_pwindowing;
      ::pointer<::user::copydesk>            m_pcopydesk;
      ::point_i32                               m_pointCursor;
      ::oswindow                                m_oswindow;


      window();
      ~window() override;


      void user_common_construct();


      void on_initialize_particle() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      ::aura::application* get_app();
      ::aura::session* get_session();
      ::aura::system* get_system();


      void install_message_routing(::channel * pchannel) override;


      virtual void create_window(::user::interaction_impl * pimpl);


      virtual void set_cursor_position(const ::point_i32 & pointCursor);

      virtual void get_cursor_position(POINT_I32 * ppointCursor);

      inline ::point_i32 get_cursor_position() { ::point_i32 point; get_cursor_position(&point); return point; }


      //virtual bool defer_set_icon();

      virtual double get_top_margin();
      

      virtual void set_keyboard_focus();

      virtual void set_mouse_capture();

      virtual void set_active_window();

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

      inline ::oswindow oswindow() const { return m_oswindow; }
      void set_oswindow(::oswindow oswindow);

      inline ::windowing::windowing * windowing() { return m_pwindowing; }
      inline ::windowing::windowing * windowing() const { return m_pwindowing.m_p; }


      virtual void exit_iconify();

      virtual void full_screen(const::rectangle_i32 & rectangle = nullptr);

      virtual void exit_full_screen();

      virtual void exit_zoomed();

      virtual void destroy_window();

      void on_destroy() override;

      virtual void show_window(const ::e_display & edisplay, const ::e_activation & eactivation);

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
      

      virtual bool client_to_screen(POINT_I32 * ppoint);

      virtual bool screen_to_client(POINT_I32 * ppoint);


      virtual bool on_set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide);

      virtual bool set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide);
      virtual bool _set_window_pos(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide);

      virtual bool is_destroying();


      virtual void activate_top_parent();


      void message_handler(::message::message* pusermessage) override;


      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      virtual void present();

      virtual void on_visual_applied();


      virtual void win_update_graphics();

      virtual lresult send_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr);

      virtual bool post_message(const ::atom & atom, wparam wParam = 0, lparam lParam = nullptr);


      virtual void set_window_text(const ::string & pszString);

      virtual strsize get_window_text(char * pszStringBuf, strsize nMaxCount);

      virtual void get_window_text(string & rectangleString);
      virtual strsize get_window_text_length();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      virtual ::u32 ArrangeIconicWindows();

      virtual void rects_from_os();
      virtual bool window_rect_from_os(RECTANGLE_I32 * prectangle);
      virtual bool client_rect_from_os(RECTANGLE_I32 * prectangle);


      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = true);
      virtual bool GetUpdateRect(RECTANGLE_I32 * prectangle, bool bErase = false);

      virtual i32 GetUpdateRgn(::draw2d::region * pRgn, bool bErase = false);
      virtual void Invalidate(bool bErase = true);
      virtual void InvalidateRect(const RECTANGLE_I32 * rectangle, bool bErase = true);

      virtual void InvalidateRgn(::draw2d::region * pRgn, bool bErase = true);
      virtual void ValidateRect(const RECTANGLE_I32 * rectangle_i32);

      virtual void ValidateRgn(::draw2d::region * pRgn);


      virtual void ShowOwnedPopups(bool bShow = true);

      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();


      virtual bool RedrawWindow(const ::rectangle_i32 & rectangleUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = 0);

      // Window State Functions
      virtual bool is_this_enabled();
      virtual bool enable_window(bool bEnable = true);

      // the active interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      virtual void set_foreground_window();
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


      virtual ::point_i32 get_mouse_cursor_position();


      virtual void set_tool_window(bool bSet);


      void set_context_org(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(RECTANGLE_I32 * prectangle);
      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation);


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


      virtual void update_screen();
      virtual void window_show();
      
      virtual void frame_toggle_restore();

      virtual void window_send(const ::procedure & procedure);
      virtual void window_post(const ::procedure & procedure);

      bool is_branch_current() const override;

      
      itask_t get_itask() const;


      virtual void on_touch_down(int x, int y);
      virtual void on_touch_drag(int x, int y);
      virtual void on_touch_up(int x, int y);

      virtual void on_size(int w, int h);

      virtual void on_text(const ansichar * pansisz, strsize length);
      virtual void on_text(const wd16char * pwd16sz, strsize length);
      virtual void on_text(const wd32char * pwd32sz, strsize length);


      inline bool operator == (const ::windowing::window & window) const
      {

         return oswindow() == window.oswindow();

      }


      inline bool operator != (const ::windowing::window & window) const
      {

         return !operator == (window);

      }


   };


} // namespace windowing


