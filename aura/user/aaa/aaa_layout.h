#pragma once


namespace user
{


   class CLASS_DECL_AURA layout :
      virtual public ::user::interaction_base
   {
   public:


      // changes on windows
      // should be preferrably done in the window thread
      // (at windows desktop, the window thread, and at most other systems, at main thread)
      // otherwise race conditions may occur/
      // which can produce drawing artifacts,
      // undesired "animations" or visual glitches
      // and visibility/order problems.


      enum enum_layout
      {

         layout_creating = 1 << 0,
         layout_show_window = 1 << 1,
         layout_apply_visual = 1 << 2,

      };


      ewindowflag                               m_ewindowflag;

      bool                                      m_bRequestReady;
      struct window_state                       m_statePrevious2;
      struct window_state                       m_stateRequest2;
      struct window_state                       m_stateProcess2;
      struct window_state                       m_state2;
      struct window_state                       m_stateWindow3;
      struct window_rect                        m_windowrectangle;
      struct window_rect                        m_windowrectangleStore;

      cflag < enum_layout >                        m_eflagLayouting;
      bool                                      m_bUpdatingVisual;
      bool                                      m_bUpdateVisual;
      bool                                      m_bFillParent;
      ::double_rectangle                                    m_rectangleHint;
      ::double_rectangle                                    m_rectanglePadding;
      int                                       m_iCellPadding;
      ::size                                    m_sizeSpan;
      ::double_size                                   m_sizeWeight;

      ::pointer<control_descriptor>            m_pdescriptor;

      ::duration                                      m_durationLastDisplayChange;
      enum_layout_experience                       m_elayoutexperience;


      //mutable size                            m_sizeClient;
      //mutable size                            m_sizeScreen;

      //mutable point                           m_pointParentWindow; // window position in parent window coordinates
      //mutable point                           m_pointParentClient; // client position in parent window coordinates
      //mutable point                           m_pointScreenWindow; // window position in screen coordinates
      //mutable point                           m_pointScreenClient; // client position in screen coordinates

      //// in ca2 code until 2019 and maybe until much later always null
      //mutable point                           m_pointClient; // client position in window non-client coordinates



      //draw_interface();
      //virtual ~draw_interface();


      //virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      //virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);

      //virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);


      //virtual bool _get_client_rect(RECT32 * prect) = 0;
      //virtual bool _get_window_rect(RECT32 * prect) = 0;

      //virtual ::int_point _client_parent_top_left() = 0;
      //virtual ::int_point _client_screen_top_left() = 0;


      //mutable size      m_sizeClient;
      //mutable size      m_sizeScreen;

      //mutable point     m_pointClient;
      //mutable point     m_pointScreen;
      //mutable point     m_pointParentWindow;
      //mutable point     m_pointParentClient;


      //inline auto get_client_rect64() { ::rect64 rectangle; this->rectangle(rectangle); return rectangle; }
      //inline auto get_window_rect64() { ::rect64 rectangle; window_rectangle(rectangle); return rectangle; }

      //virtual ::window_graphics* get_window_graphics();
      //virtual oswindow get_handle() const;

      //virtual bool is_composite();




      layout();
      virtual ~layout();


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool window_rectangle(RECT32 * prect);
      class control_descriptor& descriptor();
      const class control_descriptor & descriptor() const;




      //inline ::int_point window_parent_top_left() { return m_pointParentWindow; }
      //inline ::int_point window_screen_top_left() { return m_pointScreenWindow; }
      //inline ::int_point client_parent_top_left() { return m_pointParentClient; }
      //inline ::int_point client_screen_top_left() { return m_pointScreenClient; }
      //inline ::int_point client_top_left() { return m_pointClient; }

      //inline ::size client_size() { return m_sizeClient; }
      //inline ::size window_size() { return m_sizeScreen; }

      //inline void screen_to_client(RECT32* prect) { ::rect_sub(prect, client_screen_top_left()); }
      //inline void client_to_screen(RECT32* prect) { ::rect_add(prect, client_screen_top_left()); }

      //inline void this->rectangle(RECT32* prect) { ::set_rect_point_size(prect, m_pointClient, client_size()); }
      //inline void window_rectangle(RECT32* prect) { ::set_rect_point_size(prect, m_pointScreenWindow, window_size()); }

      //inline auto this->rectangle() { ::double_rectangle rectangle; this->rectangle(rectangle); return rectangle; }
      //inline auto window_rectangle() { ::double_rectangle rectangle; window_rectangle(rectangle); return rectangle; }

      virtual void set_placement(const ::double_rectangle & rectangle);


      virtual bool window_is_full_screen_enabled();

      inline bool window_is_iconic() { return ::is_iconic(window_state3().m_edisplay3); }
      inline bool window_is_zoomed() { return ::is_zoomed(display_state()); }
      inline bool window_is_full_screen() { return ::is_full_screen(display_state()); }
      inline bool window_is_docked() { return ::is_docking_appearance(display_state()); }
      inline bool window_is_minimal() { return ::window_is_minimal(display_state()); }


      inline void fps_interest_on_show() { m_ewindowflag |= e_window_flag_auto_prodevian_on_show; }
      inline void clear_auto_prodevian_on_show() { m_ewindowflag -= e_window_flag_auto_prodevian_on_show; }
      inline bool is_auto_prodevian_on_show() { return m_ewindowflag & e_window_flag_auto_prodevian_on_show; }

      inline void visual_changed() { m_ewindowflag |= e_window_flag_visual_changed; }
      inline void clear_visual_changed() { m_ewindowflag -= e_window_flag_visual_changed; }
      inline bool is_visual_changed()const { return m_ewindowflag& e_window_flag_visual_changed; }

      inline const struct window_state & ui_state() const { return m_state2; }
      inline struct window_state & ui_state() { return m_state2; }
      inline void set_ui_state(const struct window_state & state) { m_state2 = state; }

      inline const struct window_state & request_state() const { return m_stateRequest2; }
      inline struct window_state & request_state() { return m_stateRequest2; }
      inline void set_request_state(const struct window_state & state) { m_stateRequest2 = state; }

      inline const struct window_state & process_state() const { return m_stateProcess2; }
      inline struct window_state & process_state() { return m_stateProcess2; }
      inline void set_process_state(const struct window_state & state) { m_stateProcess2 = state; }

      inline const struct window_state & window_state3() const { return m_stateWindow3; }
      inline struct window_state & window_state3() { return m_stateWindow3; }
      inline void set_window_state3(const struct window_state & state) { m_stateWindow3 = state; }

      inline const ::e_display & display_state() const noexcept { return ui_state().m_edisplay3; }
      inline void set_display_state(const ::e_display & edisplay) noexcept { ui_state().m_edisplay3 = edisplay; }

      inline const ::e_display & display_request() const noexcept { return request_state().m_edisplay3; }
      inline void set_display_request(const ::e_display & edisplay) noexcept { request_state().m_edisplay3 = edisplay; }

      inline const ::e_display & window_display() const noexcept { return window_state3().m_edisplay3; }
      inline const ::e_display & process_display() const noexcept { return process_state().m_edisplay3; }


      inline enum_layout_experience layout_experience() const { return m_elayoutexperience; }


      inline bool is_layout_experience_active() const { return m_elayoutexperience != e_layout_experience_none; }


      inline bool window_is_moving() const { return m_elayoutexperience == e_layout_experience_moving; }
      inline bool window_is_sizing() const { return m_elayoutexperience == e_layout_experience_sizing; }
      inline bool window_is_docking() const { return m_elayoutexperience == e_layout_experience_docking; }


      inline bool is_this_visible() const noexcept
      {
         return ::is_visible(display_request());
      }

      inline bool is_window_visible() const noexcept;

      virtual bool is_this_screen_visible() const;

      inline bool is_window_screen_visible() const noexcept;


      virtual void set_initial_dim(const ::int_point & p, const ::size & s);
      //inline void move_to(const ::int_point& point) { m_pointRequest = point; visual_setup(); }
      //inline void set_size(const ::size & size) { m_sizeRequest = size; visual_setup(); }
      //inline void move_to(int x, int y) { m_pointRequest.set(x, y); visual_setup(); }
      //inline void set_size(int cx, int cy) { m_sizeRequest.set(cx, cy); visual_setup(); }
      //inline void set_dim(const ::int_point& point, const ::size& size) { m_pointRequest = point; m_sizeRequest = size; visual_setup(); }
      inline void move_to(const ::int_point & point) { request_state().m_point = point; m_bRequestReady = false; }
      inline void set_size(const ::size & size) { request_state().m_size = size; m_bRequestReady = false; }
      inline void move_to(int x, int y) { request_state().m_point.set(x, y); m_bRequestReady = false; }
      inline void set_size(int cx, int cy) { request_state().m_size.set(cx, cy); m_bRequestReady = false; }
      inline void set_dim(const ::int_point & point, const ::size & size) { request_state().m_point = point; request_state().m_size = size; m_bRequestReady = false; }
      inline void place(const ::double_rectangle & rectangle) { set_dim(rectangle.origin(), rectangle.size()); }
      inline void set_dim(int x, int y, int cx, int cy) { set_dim(::int_point(x, y), ::size(cx, cy)); }
      inline layout & operator =(const ::double_rectangle& rectangle) { place(rectangle); return *this; }



      inline zorder order() {  return ui_state().m_zorder; }
      inline void order(::zorder zorder) { request_state().m_zorder = zorder; m_bRequestReady = false;}


      inline void request_ready() { m_bRequestReady = true; }


      inline void order_top() { order(e_zorder_top); }
      inline void order_front() { order(e_zorder_top); }
      inline void order_top_most() { order(e_zorder_top_most); }
      inline void order_bottom() { order(e_zorder_bottom); }


      inline bool has_appearance(eappearance eappearance) { return ui_state().m_eappearance & eappearance; }
      inline void set_appearance(eappearance eappearance) { request_state().m_eappearance = eappearance; m_bRequestReady = false; }
      inline void add_appearance(eappearance eappearance) { request_state().m_eappearance |= eappearance; m_bRequestReady = false; }
      inline void erase_appearance(eappearance eappearance) { request_state().m_eappearance -= eappearance; m_bRequestReady = false; }
      inline void toggle_appearance(eappearance eappearance) { request_state().m_eappearance ^= eappearance; m_bRequestReady = false; }
      inline void clear_appearance() { request_state().m_eappearance.clear(); m_bRequestReady = false; }


      inline eappearance appearance() const { return ui_state().m_eappearance; }

      virtual bool is_request_visible() const { return ::is_visible(display_request()); }
      virtual bool display(::e_display edisplay = e_display_default, const ::user::activation & useractivation = {}) override;
      virtual bool window_do_display();
      inline bool hide() { return display(e_display_hide); }


      virtual bool is_this_visible() override;


      virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void post_redraw(bool bAscendants = true) override;
      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);

      inline bool set_window_position(::zorder zorder, int x, int y, int cx, int cy, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         order(zorder); set_dim(x, y, cx, cy); display(edisplay, useractivation); set_need_redraw(); return true;
      }
      inline bool window_order(::zorder zorder, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         order(zorder); display(edisplay, useractivation); set_need_redraw(); return true;
      }
      virtual bool window_move(int x, int y);
      inline bool window_size(int cx, int cy, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         set_size(cx, cy); display(edisplay, useractivation); set_need_redraw(); return true;
      }
      inline bool window_place(int x, int y, int cx, int cy, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         set_dim(x, y, cx, cy); display(edisplay, useractivation); set_need_redraw(); return true;
      }
      inline bool set_window_position(::zorder zorder, const ::int_point & point, const ::size & size, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         return set_window_position(zorder, point.x(), point.y(), size.cx(), size.cy(), edisplay, useractivation);
      }
      inline bool window_move(const ::int_point & point)
      {
         return window_move(point.x(), point.y());
      }
      inline bool window_size(const ::size & size, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         return window_size(size.cx(), size.cy(), edisplay, useractivation);
      }
      inline bool window_place(const ::int_point & point, const ::size & size, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         return window_place(point.x(), point.y(), size.cx(), size.cy(), edisplay, useractivation);
      }
      inline bool set_window_position(::zorder zorder, const ::double_rectangle & rectangle, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         return set_window_position(zorder, rectangle.origin(), rectangle.size(), edisplay, useractivation);
      }
      inline bool window_place(const ::double_rectangle & rectangle, edisplay edisplay = e_display_default, useractivation useractivation = ::user::e_activation_default)
      {
         return window_place(rectangle.origin(), rectangle.size(), edisplay, useractivation);
      }



      //virtual void set_placement(const ::double_rectangle & rectangle);


      //virtual bool place(const ::double_rectangle & rectangle);

      virtual ::int_point get_parent_accumulated_scroll() const;

      virtual void on_add_layout(::user::layout * playout);

      virtual string get_class_style(string strClass);
      virtual bool set_class_style(string strClass, string strStyle);
      virtual void sync_style();
      virtual string get_full_style();
      virtual void load_style(string strStyle);

      inline ::int_point top_left() { return ui_state().m_point; }
      inline ::size size() { return ui_state().m_size; }

      inline ::int_point origin() { return top_left(); }
      inline ::int_point screen_top_left() { return ui_state().m_pointScreen; }

      inline int area() { return size().area(); }


      template < typename SIZE_SHIFTABLE >
      inline auto screen_to_client(const SIZE_SHIFTABLE & o) { return o - ::size(screen_top_left()) + ::size(get_parent_accumulated_scroll()); }


      template < typename POINT_SHIFTABLE >
      inline auto client_to_screen(const POINT_SHIFTABLE & o) { return o + screen_top_left() - ::size(get_parent_accumulated_scroll()); }


      template < typename SIZE_SHIFTABLE >
      inline auto parent_to_client(const SIZE_SHIFTABLE& o) { return o - ::size(top_left()); }


      template < typename POINT_SHIFTABLE >
      inline auto client_to_parent(const POINT_SHIFTABLE& o) { return o + top_left(); }


      template < typename POINT_OFFSETABLE >
      inline void screen_to_client(POINT_OFFSETABLE & o) { o -= screen_top_left(); o+= get_parent_accumulated_scroll(); }
      template < typename POINT_OFFSETABLE >
      inline void screen_to_client(POINT_OFFSETABLE * po) { screen_to_client(*po); }


      template < typename POINT_OFFSETABLE >
      inline void client_to_screen(POINT_OFFSETABLE & o) { o += screen_top_left(); o -= get_parent_accumulated_scroll(); }
      template < typename POINT_OFFSETABLE >
      inline void client_to_screen(POINT_OFFSETABLE * po) { client_to_screen(*po); }


      template < typename POINT_OFFSETABLE >
      inline void _001ParentToClient(POINT_OFFSETABLE& o) { o -= top_left(); }
      template < typename POINT_OFFSETABLE >
      inline void _001ParentToClient(POINT_OFFSETABLE* po) { _001ParentToClient(*po); }


      template < typename POINT_OFFSETABLE >
      inline void _001ClientToParent(POINT_OFFSETABLE& o) { o += top_left(); }
      template < typename POINT_OFFSETABLE >
      inline void _001ClientToParent(POINT_OFFSETABLE* po) { _001ClientToParent(*po); }

      inline void screen_to_client(RECT32* prect) { ::rect_sub(prect, screen_top_left()); }
      inline void screen_to_client(POINT32 * ppoint) { ::point_sub(ppoint, screen_top_left()); }


      inline void client_to_screen(RECT32* prect) { ::rect_add(prect, screen_top_left()); }
      inline void client_to_screen(POINT32* ppoint) { ::point_add(ppoint, screen_top_left()); }


      inline void ParentToClient(RECT32* prect) { ::rect_sub(prect, top_left()); }
      inline void ParentToClient(POINT32* ppoint) { ::point_sub(ppoint, top_left()); }


      inline void ClientToParent(RECT32* prect) { ::rect_add(prect, top_left()); }
      inline void ClientToParent(POINT32* ppoint) { ::point_add(ppoint, top_left()); }


      inline void this->rectangle(RECT32* prect) const { prect->left() = 0; prect->top() = 0; *(SIZE32*)&prect->right() = ui_state().m_size; }
      virtual void window_rectangle(RECT32* prect) const;
      inline void window_request_rect(RECT32 * prect) const { ::set_rect_point_size(prect, request_state().m_point, request_state().m_size); }
      inline void parent_client_rectangle(RECT32* prect) const { ::set_rect_point_size(prect, ui_state().m_point, ui_state().m_size); }

      inline auto this->rectangle() const { ::double_rectangle rectangle; this->rectangle(rectangle); return rectangle; }
      inline auto window_rectangle() const { ::double_rectangle rectangle; window_rectangle(rectangle); return rectangle; }
      inline auto window_request_rect() const { ::double_rectangle rectangle; window_request_rect(rectangle); return rectangle; }
      inline auto parent_client_rectangle() const { ::double_rectangle rectangle; parent_client_rectangle(rectangle); return rectangle; }


      //virtual void _on_display(bool bKickIdle = true);


   };


} // namespace user


