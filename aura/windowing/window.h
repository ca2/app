// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA window :
      virtual public ::channel,
      virtual public osdata_array
   {
   public:


      bool                                      m_bMessageOnlyWindow : 1;


      void *                                    m_pWindow;
      void *                                    m_pWindow2;

      __pointer(::windowing::display)           m_pdisplay;
      __pointer(::user::interaction_impl)       m_pimpl;
      string                                    m_strDebug;
      __pointer(::message_queue)                m_pmessagequeue;
      millis                                    m_millisLastMouseMove;
      __pointer(::windowing::window)            m_pwindowParent;
      ::point_i32                               m_point;
      ::size_i32                                m_size;
      __pointer(::windowing::windowing)         m_pwindowing;


      window();
      virtual ~window();


      void user_common_construct();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      inline ::aura::application* get_application() const;
      inline ::aura::session* get_session() const;
      inline ::aura::system* get_system() const;


      virtual void install_message_routing(::channel * pchannel);


      virtual ::e_status create_window(::user::interaction_impl * pimpl);


      virtual ::e_status set_keyboard_focus();

      virtual ::e_status set_mouse_capture();

      virtual ::e_status set_active_window();


      virtual bool has_mouse_capture() const;
      virtual bool has_keyboard_focus() const;

      virtual ::color::color screen_pixel(int x, int y) const;

      virtual ::windowing::display * display();

      oswindow get_oswindow() const { return (::oswindow) get_os_data(); }
      void set_oswindow(oswindow oswindow);

      inline ::windowing::windowing * windowing() { return m_pwindowing; }
      inline ::windowing::windowing * windowing() const { return m_pwindowing.m_p; }


      virtual ::e_status exit_iconify();

      virtual ::e_status full_screen(const::rectangle_i32 & rectangle = nullptr);

      virtual ::e_status exit_full_screen();

      virtual ::e_status exit_zoomed();

      virtual ::e_status destroy_window();

      virtual ::e_status show_window(const ::e_display & edisplay, const ::e_activation & eactivation);

      virtual void set_user_interaction(::user::interaction *pinteraction);

      virtual void post_nc_destroy();

      virtual bool is_child_of(const window * pwindowAscendantCandidate) const; // or descendant
      
      
      virtual ::windowing::window * get_parent() const;
      virtual oswindow get_parent_oswindow() const;
      virtual ::e_status set_parent(::windowing::window * pwindowNewParent);

      
      virtual ::windowing::window * get_owner() const;
      virtual oswindow get_owner_oswindow() const;
      virtual ::e_status set_owner(::windowing::window * pwindowNewOwner);


      virtual bool is_iconic();
      virtual bool is_zoomed();
      virtual bool is_window();
      virtual bool is_window_visible();
      

      virtual bool _001ClientToScreen(POINT_I32 * ppoint);

      virtual bool _001ScreenToClient(POINT_I32 * ppoint);


      virtual bool on_set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags);

      virtual bool set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      virtual bool _set_window_pos(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);

      virtual bool is_destroying();


      virtual void activate_top_parent();




      virtual void message_handler(::message::message* pusermessage);


      virtual void route_command_message(::message::command * pcommand);

      virtual void present();

      virtual void on_visual_applied();


      virtual void win_update_graphics();

      virtual lresult send_message(const ::id & id, wparam wParam = 0, lparam lParam = nullptr);

      virtual bool post_message(const ::id & id, wparam wParam = 0, lparam lParam = nullptr);


      virtual void set_window_text(const char * pszString);

      virtual strsize get_window_text(char * pszStringBuf, strsize nMaxCount);

      virtual void get_window_text(string & rectString);
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


      virtual bool RedrawWindow(const ::rectangle_i32 & rectUpdate = nullptr, ::draw2d::region * prgnUpdate = nullptr, ::u32 flags = 0);

      // Window State Functions
      virtual bool is_this_enabled();
      virtual bool enable_window(bool bEnable = true);

      // the active interaction_impl applies only to top-level (frame windows)
      virtual ::user::interaction * GetActiveWindow();
      virtual ::user::interaction * SetActiveWindow();

      // the foreground interaction_impl applies only to top-level windows (frame windows)
      virtual ::e_status set_foreground_window();
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

      virtual ::e_status set_icon(::windowing::icon * picon);
      virtual __pointer(::windowing::icon) get_icon() const;


      virtual ::e_status set_mouse_cursor(::windowing::cursor * pcursor);


      virtual ::e_status set_tool_window(bool bSet);


      void set_viewport_org(::draw2d::graphics_pointer & pgraphics);


      void on_set_parent(::user::interaction * pinteraction);


      virtual bool get_rect_normal(RECTANGLE_I32 * prectangle);
      virtual void window_show_change_visibility(::e_display edisplay, ::e_activation eactivation);


      virtual void non_top_most_upper_window_rects(::rectangle_i32_array & recta);

      virtual void default_message_handler(::message::message * pmessage);

      virtual void track_mouse_hover();


      virtual void _task_transparent_mouse_event();


      virtual float get_dpi_for_window();


      virtual float point_dpi(float points);

      virtual float y_dpi(float y);
      virtual float x_dpi(float x);

      virtual float dpiy(float y);
      virtual float dpix(float x);


      virtual void on_redraw_window(::u32 flags);


      virtual void show_task(bool bShowTask);


      virtual void update_screen();
      virtual void window_show();
      
      virtual ::e_status frame_toggle_restore();


   };


} // namespace windowing


inline bool operator == (const ::windowing::window & window1, const ::windowing::window & window2)
{

   return window1.get_oswindow() == window2.get_oswindow();

}

inline bool operator != (const ::windowing::window & window1, const ::windowing::window & window2)
{

   return !operator==(window1, window2);

}


