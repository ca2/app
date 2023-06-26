#pragma once


#include "layout_state.h"


namespace user
{


   class CLASS_DECL_AURA interaction_layout
   {
   public:


      // changes on windows
      // should be preferrably done in the window thread
      // (at windows desktop, the window thread, and at most other systems, at main thread)
      // otherwise race conditions may occur/
      // which can produce drawing artifacts,
      // undesired "animations" or visual glitches
      // and visibility/order problems.


      enum enum_flag
      {

         flag_creating = 1 << 0,
         flag_show_window = 1 << 1,
         flag_apply_visual = 1 << 2,

      };



      int                                       m_iStateCount;
      bool                                      m_bRequestReady;


      //class layout_state *                      m_pstate;
      //class layout_state                        m_statea[5];
      class layout_state                        m_statea[5];
      //struct layout_state                     m_stateRequest2;
      //struct layout_state                     m_stateProcess2;
      //struct layout_state                     m_stateOffScreen;
      //struct layout_state                     m_stateScreenBuffer;
      //struct layout_state                     m_stateEventScreen;


      enumeration < enum_flag >                          m_eflag;
      bool                                      m_bFillParent;
      ::rectangle_i32                                    m_rectangleHint;
      ::rectangle_i32                                    m_rectanglePadding;
      int                                       m_iCellPadding;
      ::size_i32                                    m_sizeSpan;
      ::size_f64                                   m_sizeWeight;


      class ::time                                      m_timeLastSketchToDesign;
      enum_layout_experience                       m_elayoutexperience;


      //mutable size_i32                            m_sizeClient;
      //mutable size_i32                            m_sizeScreen;

      //mutable point_i32                           m_pointParentWindow; // window position in parent window coordinates
      //mutable point_i32                           m_pointParentClient; // client position in parent window coordinates
      //mutable point_i32                           m_pointScreenWindow; // window position in screen coordinates
      //mutable point_i32                           m_pointScreenClient; // client position in screen coordinates

      //// in ca2 code until 2019 and maybe until much later always null
      //mutable point_i32                           m_pointClient; // client position in window non-client coordinates



      //draw_interface();
      //virtual ~draw_interface();


      //virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      //virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);

      //virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics);


      //virtual bool _get_client_rect(::rectangle_i32 * prectangle) = 0;
      //virtual bool _get_window_rect(::rectangle_i32 * prectangle) = 0;

      //virtual ::point_i32 _client_parent_top_left() = 0;
      //virtual ::point_i32 _client_screen_top_left() = 0;


      //mutable size_i32      m_sizeClient;
      //mutable size_i32      m_sizeScreen;

      //mutable point_i32     m_pointClient;
      //mutable point_i32     m_pointScreen;
      //mutable point_i32     m_pointParentWindow;
      //mutable point_i32     m_pointParentClient;


      //inline auto get_client_rect64() { ::rectangle_i64 rectangle_i32; client_rectangle(rectangle); return rectangle; }
      //inline auto get_window_rect64() { ::rectangle_i64 rectangle_i32; window_rectangle(rectangle); return rectangle; }

      //virtual ::window_graphics* get_window_graphics();
      //virtual oswindow get_handle() const;

      //virtual bool is_composite();




      interaction_layout();
      ~interaction_layout();


      bool is_top_level() const { return m_iStateCount == e_layout_count_owner; }

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
      //virtual bool attach(::windowing::window * pwindow_New);
      //virtual oswindow detach();


      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool window_rectangle(::rectangle_i32 * prectangle);



      //inline ::point_i32 window_parent_top_left() { return m_pointParentWindow; }
      //inline ::point_i32 window_screen_top_left() { return m_pointScreenWindow; }
      //inline ::point_i32 client_parent_top_left() { return m_pointParentClient; }
      //inline ::point_i32 client_screen_top_left() { return m_pointScreenClient; }
      //inline ::point_i32 client_top_left() { return m_pointClient; }

      //inline ::size_i32 client_size() { return m_sizeClient; }
      //inline ::size_i32 window_size() { return m_sizeScreen; }

      //inline void screen_to_client(::rectangle_i32* prectangle) { ::rect_sub(prectangle, client_screen_top_left()); }
      //inline void client_to_screen(::rectangle_i32* prectangle) { ::rect_add(prectangle, client_screen_top_left()); }

      //inline void client_rectangle(::rectangle_i32* prectangle) { ::set_rect_point_size(prectangle, m_pointClient, client_size()); }
      //inline void window_rectangle(::rectangle_i32* prectangle) { ::set_rect_point_size(prectangle, m_pointScreenWindow, window_size()); }

      //inline auto client_rectangle() { ::rectangle_i32 rectangle; client_rectangle(rectangle); return rectangle; }
      //inline auto window_rectangle() { ::rectangle_i32 rectangle; window_rectangle(rectangle); return rectangle; }

      //virtual void set_placement(const ::rectangle_i32 & rectangle);


      inline bool is_iconic(enum_layout elayout = e_layout_design) const { return ::is_iconic(state(elayout).display()); }
      inline bool is_zoomed(enum_layout elayout = e_layout_design) const { return ::is_zoomed(state(elayout).display()); }
      inline bool is_full_screen(enum_layout elayout = e_layout_design) const { return ::is_full_screen(state(elayout).display()); }
      inline bool is_docked(enum_layout elayout = e_layout_design) const { return ::is_docking_appearance(state(elayout).display()); }
      inline bool is_minimal(enum_layout elayout = e_layout_design) const { return ::window_is_minimal(state(elayout).display()); }


      friend class interaction;
      friend class box;
      
   protected:

      inline class layout_state& state(enum_layout elayout) { ASSERT(elayout >= 0 && elayout < m_iStateCount); return m_statea[elayout]; }
      inline class layout_state& sketch() { return state(e_layout_sketch); }
      inline class layout_state& design() { return state(e_layout_design); }
      inline class layout_state& normal() { return state(e_layout_normal); }
      inline class layout_state& output() { return state(e_layout_output); }
      inline class layout_state & window() { return state(e_layout_window); }
      virtual void set_initial_dim(const ::point_i32 & p, const ::size_i32 & s);

      inline void set_appearance(e_appearance eappearance) { sketch() = eappearance; }
      inline void add_appearance(e_appearance eappearance) { sketch() |= eappearance; }
      inline void erase_appearance(e_appearance eappearance) { sketch() -= eappearance; }
      inline void toggle_appearance(e_appearance eappearance) { sketch() ^= eappearance; }
      inline void clear_appearance() { sketch() = e_appearance_none; }
      virtual void post_redraw(bool bAscendants = true);
      virtual void set_reposition(bool bSetThis = true);
      virtual void _set_reposition(bool bSetThis = true);

   public:
      
      inline const class layout_state& state(enum_layout elayout) const { ASSERT(elayout >= 0 && elayout < m_iStateCount); return m_statea[elayout]; }

      inline const class layout_state& sketch() const { return state(e_layout_sketch); }


      inline const class layout_state& design() const { return state(e_layout_design); }


      inline const class layout_state& normal() const { return state(e_layout_normal); }

      //inline const class layout_state& bitmap() const { return state(e_layout_bitmap); }
      //inline class layout_state& bitmap() { return state(e_layout_bitmap); }


      inline const class layout_state& output() const { return state(e_layout_output); }


      inline const class layout_state & window() const { return state(e_layout_window); }


      inline enum_layout_experience layout_experience() const { return m_elayoutexperience; }


      inline bool is_changing() const { return m_elayoutexperience != e_layout_experience_none; }
      inline bool is_moving() const { return m_elayoutexperience == e_layout_experience_moving; }
      inline bool is_sizing() const { return m_elayoutexperience == e_layout_experience_sizing; }
      inline bool is_docking() const { return m_elayoutexperience == e_layout_experience_docking; }


      inline bool is_this_visible(enum_layout elayout = e_layout_design) const
      {
         return ::is_visible(state(elayout).display());
      }

      inline bool is_this_screen_visible(enum_layout elayout = e_layout_design) const
      {
         return ::is_screen_visible(state(elayout).display());
      }




//      virtual zorder order(enum_layout elayout) const;


      //inline void request_ready() { m_bPendingRequest = true; }

      //inline bool pending_request() const { return request() != process(); }


      inline bool has_appearance(e_appearance eappearance) const { return design().appearance() & eappearance; }



      virtual ::point_i32 get_parent_accumulated_scroll(enum_layout elayout = e_layout_design) const;

      virtual void on_add_layout(::user::interaction_layout * playout);


      inline ::size_i32 size(enum_layout elayout = e_layout_design) const { return state(elayout).size(); }

      inline ::point_i32 origin(enum_layout elayout = e_layout_design) const { return state(elayout).origin(); }

      inline ::i32 area(enum_layout elayout = e_layout_design) const { return this->size(elayout).area(); }


      //inline void raw_rectangle(::rectangle_i32 & rectangle, enum_layout elayout = e_layout_design) const { state(elayout).raw_rectangle(rectangle); }
      //inline void parent_raw_rectangle(::rectangle_i32 & rectangle, enum_layout elayout = e_layout_design) const { state(elayout).parent_raw_rectangle(rectangle); }


      inline ::rectangle_i32 raw_rectangle(enum_layout elayout = e_layout_design) const { return state(elayout).raw_rectangle(); }
      inline ::rectangle_i32 parent_raw_rectangle(enum_layout elayout = e_layout_design) const { return state(elayout).parent_raw_rectangle(); }


   };


   //inline void visual_state::set_busy()
   //{

   //   synchronous_lock synchronouslock(m_playout->synchronization());

   //   m_bBusy = true;

   //}


   //inline bool visual_state::set_ready()
   //{

   //   synchronous_lock synchronouslock(m_playout->synchronization());

   //   if (!m_bBusy)
   //   {

   //      return false;

   //   }

   //   m_bBusy = false;

   //   return true;

   //}


} // namespace user



