#pragma once


namespace user
{


   class CLASS_DECL_AURA layout :
      virtual public ::user::primitive
   {
   public:


      // changes on windows
      // should be preferrably done in the window thread
      // (at windows desktop, the window thread, and at most other systems, at main thread)
      // otherwise race conditions may occur/
      // which can produce drawing artifacts,
      // undesired "animations" or visual glitches
      // and visibility/order problems.


      enum e_layout
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
      struct window_rect                        m_windowrect;
      struct window_rect                        m_windowrectStore;

      cflag < e_layout >                        m_eflagLayouting;
      bool                                      m_bUpdatingVisual;
      bool                                      m_bUpdateVisual;
      bool                                      m_bFillParent;
      ::rect                                    m_rectHint;
      ::rect                                    m_rectPadding;
      int                                       m_iCellPadding;
      ::size                                    m_sizeSpan;
      ::sized                                   m_sizeWeight;

      __pointer(control_descriptor)             m_pdescriptor;

      tick                                      m_tickLastDisplayChange;
      e_layout_experience                       m_elayoutexperience;


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

      //virtual ::point _client_parent_top_left() = 0;
      //virtual ::point _client_screen_top_left() = 0;


      //mutable size      m_sizeClient;
      //mutable size      m_sizeScreen;

      //mutable point     m_pointClient;
      //mutable point     m_pointScreen;
      //mutable point     m_pointParentWindow;
      //mutable point     m_pointParentClient;


      //inline auto get_client_rect64() { ::rect64 rect; get_client_rect(rect); return rect; }
      //inline auto get_window_rect64() { ::rect64 rect; get_window_rect(rect); return rect; }

      //virtual ::window_graphics* get_window_graphics();
      //virtual oswindow get_handle() const;

      //virtual bool is_composite();




      layout();
      virtual ~layout();


      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool get_window_rect(RECT32 * prect);
      class control_descriptor& descriptor();
      const class control_descriptor & descriptor() const;




      //inline ::point window_parent_top_left() { return m_pointParentWindow; }
      //inline ::point window_screen_top_left() { return m_pointScreenWindow; }
      //inline ::point client_parent_top_left() { return m_pointParentClient; }
      //inline ::point client_screen_top_left() { return m_pointScreenClient; }
      //inline ::point client_top_left() { return m_pointClient; }

      //inline ::size client_size() { return m_sizeClient; }
      //inline ::size window_size() { return m_sizeScreen; }

      //inline void _001ScreenToClient(RECT32* prect) { ::rect_sub(prect, client_screen_top_left()); }
      //inline void _001ClientToScreen(RECT32* prect) { ::rect_add(prect, client_screen_top_left()); }

      //inline void get_client_rect(RECT32* prect) { ::set_rect_point_size(prect, m_pointClient, client_size()); }
      //inline void get_window_rect(RECT32* prect) { ::set_rect_point_size(prect, m_pointScreenWindow, window_size()); }

      //inline auto get_client_rect() { ::rect rect; get_client_rect(rect); return rect; }
      //inline auto get_window_rect() { ::rect rect; get_window_rect(rect); return rect; }

      virtual void set_placement(const ::rect & rect);


      virtual bool window_is_full_screen_enabled();

      inline bool window_is_iconic() { return ::is_iconic(window_state3().m_edisplay3); }
      inline bool window_is_zoomed() { return ::is_zoomed(display_state()); }
      inline bool window_is_full_screen() { return ::is_full_screen(display_state()); }
      inline bool window_is_docked() { return ::is_docking_appearance(display_state()); }
      inline bool window_is_minimal() { return ::window_is_minimal(display_state()); }


      inline void auto_prodevian_on_show() { m_ewindowflag |= window_flag_auto_prodevian_on_show; }
      inline void clear_auto_prodevian_on_show() { m_ewindowflag -= window_flag_auto_prodevian_on_show; }
      inline bool is_auto_prodevian_on_show() { return m_ewindowflag & window_flag_auto_prodevian_on_show; }

      inline void visual_changed() { m_ewindowflag |= window_flag_visual_changed; }
      inline void clear_visual_changed() { m_ewindowflag -= window_flag_visual_changed; }
      inline bool is_visual_changed()const { return m_ewindowflag& window_flag_visual_changed; }

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

      inline const ::edisplay & display_state() const noexcept { return ui_state().m_edisplay3; }
      inline void set_display_state(const ::edisplay & edisplay) noexcept { ui_state().m_edisplay3 = edisplay; }

      inline const ::edisplay & display_request() const noexcept { return request_state().m_edisplay3; }
      inline void set_display_request(const ::edisplay & edisplay) noexcept { request_state().m_edisplay3 = edisplay; }

      inline const ::edisplay & window_display() const noexcept { return window_state3().m_edisplay3; }
      inline const ::edisplay & process_display() const noexcept { return process_state().m_edisplay3; }


      inline e_layout_experience layout_experience() const { return m_elayoutexperience; }


      inline bool is_layout_experience_active() const { return m_elayoutexperience != layout_experience_none; }


      inline bool window_is_moving() const { return m_elayoutexperience == layout_experience_moving; }
      inline bool window_is_sizing() const { return m_elayoutexperience == layout_experience_sizing; }
      inline bool window_is_docking() const { return m_elayoutexperience == layout_experience_docking; }


      inline bool is_this_visible() const noexcept
      {
         return ::is_visible(display_request());
      }

      inline bool is_window_visible() const noexcept;

      virtual bool is_this_screen_visible() const;

      inline bool is_window_screen_visible() const noexcept;


      virtual void set_initial_dim(const ::point & p, const ::size & s);
      //inline void move_to(const ::point& point) { m_pointRequest = point; visual_setup(); }
      //inline void set_size(const ::size & size) { m_sizeRequest = size; visual_setup(); }
      //inline void move_to(i32 x, i32 y) { m_pointRequest.set(x, y); visual_setup(); }
      //inline void set_size(i32 cx, i32 cy) { m_sizeRequest.set(cx, cy); visual_setup(); }
      //inline void set_dim(const ::point& point, const ::size& size) { m_pointRequest = point; m_sizeRequest = size; visual_setup(); }
      inline void move_to(const ::point & point) { request_state().m_point = point; m_bRequestReady = false; }
      inline void set_size(const ::size & size) { request_state().m_size = size; m_bRequestReady = false; }
      inline void move_to(i32 x, i32 y) { request_state().m_point.set(x, y); m_bRequestReady = false; }
      inline void set_size(i32 cx, i32 cy) { request_state().m_size.set(cx, cy); m_bRequestReady = false; }
      inline void set_dim(const ::point & point, const ::size & size) { request_state().m_point = point; request_state().m_size = size; m_bRequestReady = false; }
      inline void place(const ::rect & rect) { set_dim(rect.origin(), rect.size()); }
      inline void set_dim(i32 x, i32 y, i32 cx, i32 cy) { set_dim(::point(x, y), ::size(cx, cy)); }
      inline layout & operator =(const ::rect& rect) { place(rect); return *this; }



      inline zorder order() {  return ui_state().m_zorder; }
      inline void order(::zorder zorder) { request_state().m_zorder = zorder; m_bRequestReady = false;}


      inline void request_ready() { m_bRequestReady = true; }


      inline void order_top() { order(zorder_top); }
      inline void order_front() { order(zorder_top); }
      inline void order_top_most() { order(zorder_top_most); }
      inline void order_bottom() { order(zorder_bottom); }


      inline bool has_appearance(eappearance eappearance) { return ui_state().m_eappearance & eappearance; }
      inline void set_appearance(eappearance eappearance) { request_state().m_eappearance = eappearance; m_bRequestReady = false; }
      inline void add_appearance(eappearance eappearance) { request_state().m_eappearance |= eappearance; m_bRequestReady = false; }
      inline void remove_appearance(eappearance eappearance) { request_state().m_eappearance -= eappearance; m_bRequestReady = false; }
      inline void toggle_appearance(eappearance eappearance) { request_state().m_eappearance ^= eappearance; m_bRequestReady = false; }
      inline void clear_appearance() { request_state().m_eappearance.clear(); m_bRequestReady = false; }


      inline eappearance appearance() const { return ui_state().m_eappearance; }

      virtual bool is_request_visible() const { return ::is_visible(display_request()); }
      virtual bool display(::edisplay edisplay = display_default, ::eactivation eactivation = activation_none) override;
      virtual bool window_do_display();
      inline bool hide() { return display(display_hide); }


      virtual bool is_this_visible() override;


      virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void post_redraw(bool bAscendants = true) override;
      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);

      inline bool set_window_pos(::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         order(zorder); set_dim(x, y, cx, cy); display(edisplay, eactivation); set_need_redraw(); return true;
      }
      inline bool window_order(::zorder zorder, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         order(zorder); display(edisplay, eactivation); set_need_redraw(); return true;
      }
      virtual bool window_move(i32 x, i32 y);
      inline bool window_size(i32 cx, i32 cy, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         set_size(cx, cy); display(edisplay, eactivation); set_need_redraw(); return true;
      }
      inline bool window_place(i32 x, i32 y, i32 cx, i32 cy, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         set_dim(x, y, cx, cy); display(edisplay, eactivation); set_need_redraw(); return true;
      }
      inline bool set_window_pos(::zorder zorder, const ::point & point, const ::size & size, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         return set_window_pos(zorder, point.x, point.y, size.cx, size.cy, edisplay, eactivation);
      }
      inline bool window_move(const ::point & point)
      {
         return window_move(point.x, point.y);
      }
      inline bool window_size(const ::size & size, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         return window_size(size.cx, size.cy, edisplay, eactivation);
      }
      inline bool window_place(const ::point & point, const ::size & size, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         return window_place(point.x, point.y, size.cx, size.cy, edisplay, eactivation);
      }
      inline bool set_window_pos(::zorder zorder, const ::rect & rect, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         return set_window_pos(zorder, rect.origin(), rect.size(), edisplay, eactivation);
      }
      inline bool window_place(const ::rect & rect, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      {
         return window_place(rect.origin(), rect.size(), edisplay, eactivation);
      }



      //virtual void set_placement(const ::rect & rect);


      //virtual bool place(const ::rect & rect);

      virtual ::point get_parent_accumulated_scroll() const;

      virtual void on_add_layout(::user::layout * playout);

      virtual string get_class_style(string strClass);
      virtual bool set_class_style(string strClass, string strStyle);
      virtual void sync_style();
      virtual string get_full_style();
      virtual void load_style(string strStyle);

      inline ::point top_left() { return ui_state().m_point; }
      inline ::size size() { return ui_state().m_size; }

      inline ::point origin() { return top_left(); }
      inline ::point screen_top_left() { return ui_state().m_pointScreen; }

      inline ::i32 area() { return size().area(); }


      template < typename SIZE_SHIFTABLE >
      inline auto screen_to_client(const SIZE_SHIFTABLE & o) { return o - ::size(screen_top_left()) + ::size(get_parent_accumulated_scroll()); }


      template < typename POINT_SHIFTABLE >
      inline auto client_to_screen(const POINT_SHIFTABLE & o) { return o + screen_top_left() - ::size(get_parent_accumulated_scroll()); }


      template < typename SIZE_SHIFTABLE >
      inline auto parent_to_client(const SIZE_SHIFTABLE& o) { return o - ::size(top_left()); }


      template < typename POINT_SHIFTABLE >
      inline auto client_to_parent(const POINT_SHIFTABLE& o) { return o + top_left(); }


      template < typename POINT_OFFSETABLE >
      inline void _001ScreenToClient(POINT_OFFSETABLE & o) { o -= screen_top_left(); o+= get_parent_accumulated_scroll(); }
      template < typename POINT_OFFSETABLE >
      inline void _001ScreenToClient(POINT_OFFSETABLE * po) { _001ScreenToClient(*po); }


      template < typename POINT_OFFSETABLE >
      inline void _001ClientToScreen(POINT_OFFSETABLE & o) { o += screen_top_left(); o -= get_parent_accumulated_scroll(); }
      template < typename POINT_OFFSETABLE >
      inline void _001ClientToScreen(POINT_OFFSETABLE * po) { _001ClientToScreen(*po); }


      template < typename POINT_OFFSETABLE >
      inline void _001ParentToClient(POINT_OFFSETABLE& o) { o -= top_left(); }
      template < typename POINT_OFFSETABLE >
      inline void _001ParentToClient(POINT_OFFSETABLE* po) { _001ParentToClient(*po); }


      template < typename POINT_OFFSETABLE >
      inline void _001ClientToParent(POINT_OFFSETABLE& o) { o += top_left(); }
      template < typename POINT_OFFSETABLE >
      inline void _001ClientToParent(POINT_OFFSETABLE* po) { _001ClientToParent(*po); }

      inline void ScreenToClient(RECT32* prect) { ::rect_sub(prect, screen_top_left()); }
      inline void ScreenToClient(POINT32 * ppoint) { ::point_sub(ppoint, screen_top_left()); }


      inline void ClientToScreen(RECT32* prect) { ::rect_add(prect, screen_top_left()); }
      inline void ClientToScreen(POINT32* ppoint) { ::point_add(ppoint, screen_top_left()); }


      inline void ParentToClient(RECT32* prect) { ::rect_sub(prect, top_left()); }
      inline void ParentToClient(POINT32* ppoint) { ::point_sub(ppoint, top_left()); }


      inline void ClientToParent(RECT32* prect) { ::rect_add(prect, top_left()); }
      inline void ClientToParent(POINT32* ppoint) { ::point_add(ppoint, top_left()); }


      inline void get_client_rect(RECT32* prect) const { prect->left = 0; prect->top = 0; *(SIZE32*)&prect->right = ui_state().m_size; }
      virtual void get_window_rect(RECT32* prect) const;
      inline void window_request_rect(RECT32 * prect) const { ::set_rect_point_size(prect, request_state().m_point, request_state().m_size); }
      inline void parent_client_rect(RECT32* prect) const { ::set_rect_point_size(prect, ui_state().m_point, ui_state().m_size); }

      inline auto get_client_rect() const { ::rect rect; get_client_rect(rect); return rect; }
      inline auto get_window_rect() const { ::rect rect; get_window_rect(rect); return rect; }
      inline auto window_request_rect() const { ::rect rect; window_request_rect(rect); return rect; }
      inline auto parent_client_rect() const { ::rect rect; parent_client_rect(rect); return rect; }


      //virtual void _on_display(bool bKickIdle = true);


   };


} // namespace user


