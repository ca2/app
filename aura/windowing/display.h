// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


#include "acme/windowing/display.h"
#include "acme/prototype/geometry2d/_collection.h"
////#include "acme/prototype/prototype/object.h"


namespace windowing
{

   // X11 contribution : a display may contain more than one monitor

   class CLASS_DECL_AURA display :
      virtual public ::acme::windowing::display
   {
   public:


      pointer_array < monitor >        m_monitora;


      bool                             m_bSystemSynchronizedScreen;

      ::collection::index              m_iMainMonitor;
      ::collection::index              m_iMainWorkspace;
      double                           m_dpi;

      ::int_rectangle_array_base            m_rectangleaWorkAreas;



      display();
      ~display() override;

      
      void on_initialize_particle() override;


      virtual void open_display() override;
      virtual void finalize_display();

      virtual iptr get_os_data() const;

      virtual window * default_root_window();


      virtual float get_dpi();

      //void open_display() override;
      virtual void close_display();

      void destroy() override;

      virtual bool set_main_monitor(::collection::index iMonitor);
      //virtual ::collection::count get_monitor_count() //;
      //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::i32_rectangle * prectangle) //;

//      virtual ::collection::index get_main_workspace(::i32_rectangle * prectangle = nullptr) ;

      virtual bool set_main_workspace(::collection::index iWorkspace);
      //virtual ::collection::count get_workspace_count() ;
      //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::i32_rectangle * prectangle) ;

      virtual bool workspace_to_monitor(::i32_rectangle & rectangle, ::collection::index iMonitor, ::collection::index iWorkspace);

      virtual bool monitor_to_workspace(::i32_rectangle & rectangle, ::collection::index iWorkspace, ::collection::index iMonitor);

      virtual bool workspace_to_monitor(::i32_rectangle & rectangle);

      virtual bool monitor_to_workspace(::i32_rectangle & rectangle);

      //virtual ::collection::count get_desk_monitor_count() ;
      //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::i32_rectangle * prectangle) ;

      virtual bool has_readily_gettable_absolute_pointer_position() const;

      // dynamically get mouse cursor absolute position (also set it to m_pointCursor2 member).
      virtual ::i32_point get_mouse_cursor_position();

      virtual ::i32_point _get_mouse_cursor_position();

      virtual monitor * get_monitor(::collection::index iMonitor);
      virtual monitor * ømonitor(::collection::index iMonitor);
      void _on_monitor(int iIndex, const ::i32_rectangle & rectangle, const ::i32_rectangle & rectangleWorkspace) override;

      virtual monitor * monitor_hit_test(const ::i32_point & point);

      virtual monitor * get_best_monitor(const ::i32_rectangle & rectangle);

      virtual void  get_monitor(int_rectangle_array_base & rectaMonitor, int_rectangle_array_base & rectaIntersect, const ::i32_rectangle & rectangle);

      virtual ::collection::index initial_frame_position(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, bool bMove, ::user::interaction * pinteraction);

      virtual ::collection::index _get_best_zoneing(::e_display * pedisplay, ::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, bool bPreserveSize = false);

      virtual ::collection::index get_best_monitor(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, const ::user::activation & useractivation = {}, ::user::interaction * puserinteractionCursorPosition = nullptr);

      virtual ::collection::index get_best_workspace(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, const ::user::activation & useractivation = {}, ::user::interaction * puserinteractionCursorPosition = nullptr);

      virtual ::collection::index get_good_iconify(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle);

      virtual ::collection::index get_good_restore(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, ::user::interaction * pinteraction, ::e_display edisplayRestore);

      virtual ::collection::index get_good_move(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, ::user::interaction * pinteraction);

      virtual bool is_like_maximized(const ::i32_rectangle& rectangleWorkspace, const ::i32_rectangle& rectangle);

      virtual bool is_like_full_screen(const ::i32_rectangle& rectangleMonitor, const ::i32_rectangle& rectangle);

      virtual void enum_display_monitors();

      virtual ::collection::index get_main_monitor_index();
      virtual ::collection::index get_main_monitor(::i32_rectangle & rectangle);
      virtual ::i32_size get_main_monitor_size();
      
      ::i32_size get_main_screen_size() override;

      virtual ::i32_rectangle get_monitor_union_rectangle();

      virtual ::collection::count get_monitor_count();
      virtual bool get_monitor_rectangle(::collection::index iMonitor, ::i32_rectangle & rectangle);
      virtual bool _get_monitor_rectangle(::collection::index iMonitor, ::i32_rectangle & rectangle);

      virtual ::collection::index  get_main_monitor_of_rectangle(const ::i32_rectangle &rectangle);

      virtual ::collection::count get_desk_monitor_count();
      virtual bool get_desk_monitor_rect(::collection::index iMonitor, ::i32_rectangle & rectangle);


      virtual ::collection::index get_main_workspace(::i32_rectangle & prectangle);

      ///virtual ::collection::count get_workspace_count();
      
      virtual bool get_zoomed_window_site(::collection::index iWorkspace, ::i32_rectangle & rectangle);
      
      virtual int get_zoomed_title_bar_height();
      
      virtual bool get_workspace_rectangle(::collection::index iWorkspace, ::i32_rectangle & rectangle);
      virtual bool _get_workspace_rectangle(::collection::index iWorkspace, ::i32_rectangle & rectangle);

      //virtual ::collection::count get_desk_workspace_count();
      virtual bool get_desk_workspace_rect(::collection::index iWorkspace, ::i32_rectangle & rectangle);

      virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction);





      virtual bool would_be_docked(const ::i32_rectangle & rectangleWouldBeSnapped);

      virtual bool would_be_docked_in_monitor(const ::i32_rectangle & rectangleWouldBeSnapped, const ::i32_rectangle & rectangleMonitor);

      virtual bool would_be_restored(const ::i32_rectangle & rectangleWouldBeRestored);

      virtual bool would_be_restored_in_monitor(const ::i32_rectangle & rectangleWouldBeRestored, const ::i32_rectangle & rectangleMonitor);

void * raw_x11_display() override;
   };


} // namespace windowing



