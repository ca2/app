#pragma once


namespace user
{


   class CLASS_DECL_AURA interaction_layout :
      virtual public ::context_object
   {
   public:


      // changes on windows
      // should be preferrably done in the window thread
      // (at windows desktop, the window thread, and at most other systems, at main thread)
      // otherwise race conditions may occur/
      // which can produce drawing artifacts,
      // undesired "animations" or visual glitches
      // and visibility/order problems.


      enum e_flag
      {

         flag_creating = 1 << 0,
         flag_show_window = 1 << 1,
         flag_apply_visual = 1 << 2,

      };



      int                                       m_iStateCount;
      bool                                      m_bRequestReady;


      //class window_state *                      m_pstate;
      class window_state                        m_statea[4];
      //struct window_state                     m_stateRequest2;
      //struct window_state                     m_stateProcess2;
      //struct window_state                     m_stateOffScreen;
      //struct window_state                     m_stateScreenBuffer;
      //struct window_state                     m_stateEventScreen;


      cflag < e_flag >                          m_eflag;
      bool                                      m_bFillParent;
      ::rect                                    m_rectHint;
      ::rect                                    m_rectPadding;
      int                                       m_iCellPadding;
      ::size                                    m_sizeSpan;
      ::sized                                   m_sizeWeight;


      tick                                      m_tickLastSketchToDesign;
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


      //virtual bool _get_client_rect(RECT * prect) = 0;
      //virtual bool _get_window_rect(RECT * prect) = 0;

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




      interaction_layout();
      virtual ~interaction_layout();


      bool is_top_level() const { return m_iStateCount == layout_count_owner; }

      void create_state(int iStateCount);
      void destroy_state();


      //virtual void _001PrintBuffer(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001Print(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001DrawThis(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001DrawChildren(::draw2d::graphics_pointer& pgraphics);
      //virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;
      //virtual void _008OnDraw(::draw2d::graphics_pointer& pgraphics);
      //virtual void draw_control_background(::draw2d::graphics_pointer& pgraphics);

      //virtual void _000OnDraw(::draw2d::graphics_pointer& pgraphics) override;
      //virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics) override;

      //virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics) override;

      //virtual oswindow get_handle() const override;
      //virtual bool attach(oswindow oswindow_New);
      //virtual oswindow detach();


      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool get_window_rect(RECT * prect);
      


      //inline ::point window_parent_top_left() { return m_pointParentWindow; }
      //inline ::point window_screen_top_left() { return m_pointScreenWindow; }
      //inline ::point client_parent_top_left() { return m_pointParentClient; }
      //inline ::point client_screen_top_left() { return m_pointScreenClient; }
      //inline ::point client_top_left() { return m_pointClient; }

      //inline ::size client_size() { return m_sizeClient; }
      //inline ::size window_size() { return m_sizeScreen; }

      //inline void _001ScreenToClient(RECT* prect) { ::rect_sub(prect, client_screen_top_left()); }
      //inline void _001ClientToScreen(RECT* prect) { ::rect_add(prect, client_screen_top_left()); }

      //inline void get_client_rect(RECT* prect) { ::set_rect_point_size(prect, m_pointClient, client_size()); }
      //inline void get_window_rect(RECT* prect) { ::set_rect_point_size(prect, m_pointScreenWindow, window_size()); }

      //inline auto get_client_rect() { ::rect rect; get_client_rect(rect); return rect; }
      //inline auto get_window_rect() { ::rect rect; get_window_rect(rect); return rect; }

      //virtual void set_placement(const ::rect & rect);


      inline bool is_iconic(e_layout elayout = layout_design) const { return ::is_iconic(state(elayout).display()); }
      inline bool is_zoomed(e_layout elayout = layout_design) const { return ::is_zoomed(state(elayout).display()); }
      inline bool is_full_screen(e_layout elayout = layout_design) const { return ::is_full_screen(state(elayout).display()); }
      inline bool is_docked(e_layout elayout = layout_design) const { return ::is_docking_appearance(state(elayout).display()); }
      inline bool is_minimal(e_layout elayout = layout_design) const { return ::window_is_minimal(state(elayout).display()); }





      inline const class window_state& state(e_layout elayout) const { ASSERT(elayout >= 0 && elayout < m_iStateCount); return m_statea[elayout]; }
      inline class window_state& state(e_layout elayout) { ASSERT(elayout >= 0 && elayout < m_iStateCount); return m_statea[elayout]; }


      inline const class window_state& sketch() const { return state(layout_sketch); }
      inline class window_state& sketch() { return state(layout_sketch); }


      inline const class window_state& design() const { return state(layout_design); }
      inline class window_state& design() { return state(layout_design); }


      //inline const class window_state& bitmap() const { return state(layout_bitmap); }
      //inline class window_state& bitmap() { return state(layout_bitmap); }


      inline const class window_state& output() const { return state(layout_output); }
      inline class window_state& output() { return state(layout_output); }


      inline const class window_state & window() const { return state(layout_window); }
      inline class window_state & window() { return state(layout_window); }


      inline e_layout_experience layout_experience() const { return m_elayoutexperience; }


      inline bool is_changing() const { return m_elayoutexperience != layout_experience_none; }
      inline bool is_moving() const { return m_elayoutexperience == layout_experience_moving; }
      inline bool is_sizing() const { return m_elayoutexperience == layout_experience_sizing; }
      inline bool is_docking() const { return m_elayoutexperience == layout_experience_docking; }


      inline bool is_this_visible(e_layout elayout = layout_design) const
      {
         return ::is_visible(state(elayout).display());
      }

      inline bool is_this_screen_visible(e_layout elayout = layout_design) const
      {
         return ::is_screen_visible(state(elayout).display());
      }



      virtual void set_initial_dim(const ::point & p, const ::size & s);

//      virtual zorder order(e_layout elayout) const;


      //inline void request_ready() { m_bPendingRequest = true; }

      //inline bool pending_request() const { return request() != process(); }




      inline bool has_appearance(eappearance eappearance) const { return design().appearance() & eappearance; }
      inline void set_appearance(eappearance eappearance) { sketch() = eappearance; sketch().set_modified(); }
      inline void add_appearance(eappearance eappearance) { sketch() |= eappearance; sketch().set_modified(); }
      inline void remove_appearance(eappearance eappearance) { sketch() -= eappearance; sketch().set_modified(); }
      inline void toggle_appearance(eappearance eappearance) { sketch() ^= eappearance; sketch().set_modified(); }
      inline void clear_appearance() { sketch() = appearance_none; sketch().set_modified(); }


      //inline eappearance appearance() const { return request_state().m_eappearance; }

      //virtual void order(::zorder zorder);
      //virtual bool layout().sketch().is_visible() const;
      //virtual bool display(::edisplay edisplay = display_default, ::eactivation eactivation = activation_none) ;


//      virtual void set_ready(e_layout);
      //virtual void set_need_redraw(bool bAscendants = true);
      virtual void post_redraw(bool bAscendants = true);
      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);

      //inline bool set_window_pos(::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   order(zorder); set_dim(x, y, cx, cy); display(edisplay, eactivation); set_need_redraw(); return true;
      //}
      //inline bool window_order(::zorder zorder, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   order(zorder); display(edisplay, eactivation); set_need_redraw(); return true;
      //}
      //virtual bool window_move(i32 x, i32 y);
      //inline bool window_size(i32 cx, i32 cy, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   set_size(cx, cy); display(edisplay, eactivation); set_need_redraw(); return true;
      //}
      //inline bool window_place(i32 x, i32 y, i32 cx, i32 cy, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   set_dim(x, y, cx, cy); display(edisplay, eactivation); set_need_redraw(); return true;
      //}
      //inline bool set_window_pos(::zorder zorder, const ::point & point, const ::size & size, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   return set_window_pos(zorder, point.x, point.y, size.cx, size.cy, edisplay, eactivation);
      //}
      //inline bool window_move(const ::point & point)
      //{
      //   return window_move(point.x, point.y);
      //}
      //inline bool window_size(const ::size & size, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   return window_size(size.cx, size.cy, edisplay, eactivation);
      //}
      //inline bool window_place(const ::point & point, const ::size & size, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   return window_place(point.x, point.y, size.cx, size.cy, edisplay, eactivation);
      //}
      //inline bool set_window_pos(::zorder zorder, const ::rect & rect, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   return set_window_pos(zorder, rect.origin(), rect.size(), edisplay, eactivation);
      //}
      //inline bool window_place(const ::rect & rect, edisplay edisplay = display_default, eactivation eactivation = activation_none)
      //{
      //   return window_place(rect.origin(), rect.size(), edisplay, eactivation);
      //}



      //virtual void set_placement(const ::rect & rect);


      //virtual bool place(const ::rect & rect);

      virtual ::point get_parent_accumulated_scroll(e_layout elayout = layout_design) const;

      virtual void on_add_layout(::user::interaction_layout * playout);


      inline ::size size(e_layout elayout = layout_design) const { return state(elayout).size(); }

      inline ::point origin(e_layout elayout = layout_design) const { return state(elayout).origin();; }
      inline ::point screen_origin(e_layout elayout = layout_design) const { return state(elayout).screen_origin(); }

      inline LONG area(e_layout elayout = layout_design) const { return size(elayout).area(); }


      inline void get_client_rect(RECT* prect, e_layout elayout = layout_design) const { state(elayout).client_rect(prect); }
      inline void get_window_rect(RECT* prect, e_layout elayout = layout_design) const { state(elayout).screen_rect(prect); }
      inline void parent_client_rect(RECT* prect, e_layout elayout = layout_design) const { state(elayout).parent_client_rect(prect); }


      inline auto get_client_rect(e_layout elayout = layout_design) const { ::rect rect; get_client_rect(rect, elayout); return rect; }
      inline auto get_window_rect(e_layout elayout = layout_design) const { ::rect rect; get_window_rect(rect, elayout); return rect; }
      inline auto parent_client_rect(e_layout elayout = layout_design) const { ::rect rect; parent_client_rect(rect, elayout); return rect; }


   };


   //inline void visual_state::set_busy()
   //{

   //   sync_lock sl(m_playout->mutex());

   //   m_bBusy = true;

   //}


   //inline bool visual_state::set_ready()
   //{

   //   sync_lock sl(m_playout->mutex());

   //   if (!m_bBusy)
   //   {

   //      return false;

   //   }

   //   m_bBusy = false;

   //   return true;

   //}


} // namespace user



