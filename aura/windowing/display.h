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

      ::int_rectangle_array            m_rectangleaWorkAreas;
      ::string                         m_strDarkModeAnnotation;



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
      //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle) //;

//      virtual ::collection::index get_main_workspace(::int_rectangle * prectangle = nullptr) ;

      virtual bool set_main_workspace(::collection::index iWorkspace);
      //virtual ::collection::count get_workspace_count() ;
      //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle * prectangle) ;

      virtual bool workspace_to_monitor(::int_rectangle & rectangle, ::collection::index iMonitor, ::collection::index iWorkspace);

      virtual bool monitor_to_workspace(::int_rectangle & rectangle, ::collection::index iWorkspace, ::collection::index iMonitor);

      virtual bool workspace_to_monitor(::int_rectangle & rectangle);

      virtual bool monitor_to_workspace(::int_rectangle & rectangle);

      //virtual ::collection::count get_desk_monitor_count() ;
      //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle * prectangle) ;

      virtual bool has_readily_gettable_absolute_pointer_position() const;

      // dynamically get mouse cursor absolute position (also set it to m_pointCursor2 member).
      virtual ::int_point get_mouse_cursor_position();

      virtual ::int_point _get_mouse_cursor_position();

      virtual monitor * get_monitor(::collection::index iMonitor);

      virtual monitor * monitor_hit_test(const ::int_point & point);

      virtual monitor * get_best_monitor(const ::int_rectangle & rectangle);

      virtual void  get_monitor(int_rectangle_array & rectaMonitor, int_rectangle_array & rectaIntersect, const ::int_rectangle & rectangle);

      virtual ::collection::index initial_frame_position(::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bMove, ::user::interaction * pinteraction);

      virtual ::collection::index _get_best_zoneing(::e_display * pedisplay, ::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bPreserveSize = false);

      virtual ::collection::index get_best_monitor(::int_rectangle * prectangle, const ::int_rectangle & rectangle, const ::user::activation & useractivation = {}, ::user::interaction * puserinteractionCursorPosition = nullptr);

      virtual ::collection::index get_best_workspace(::int_rectangle * prectangle, const ::int_rectangle & rectangle, const ::user::activation & useractivation = {}, ::user::interaction * puserinteractionCursorPosition = nullptr);

      virtual ::collection::index get_good_iconify(::int_rectangle * prectangle, const ::int_rectangle & rectangle);

      virtual ::collection::index get_good_restore(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction, ::e_display edisplayRestore);

      virtual ::collection::index get_good_move(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction);

      virtual bool is_like_maximized(const ::int_rectangle& rectangleWorkspace, const ::int_rectangle& rectangle);

      virtual bool is_like_full_screen(const ::int_rectangle& rectangleMonitor, const ::int_rectangle& rectangle);

      virtual void enum_display_monitors();

      virtual ::collection::index get_main_monitor_index();
      virtual ::collection::index get_main_monitor(::int_rectangle & rectangle);
      virtual ::int_size get_main_monitor_size();
      
      ::int_size get_main_screen_size() override;

      virtual ::int_rectangle get_monitor_union_rectangle();

      virtual ::collection::count get_monitor_count();
      virtual bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle);
      virtual bool _get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle);

      virtual ::collection::index  get_main_monitor_of_rectangle(const ::int_rectangle &rectangle);

      virtual ::collection::count get_desk_monitor_count();
      virtual bool get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle & rectangle);


      virtual ::collection::index get_main_workspace(::int_rectangle & prectangle);

      ///virtual ::collection::count get_workspace_count();
      
      virtual bool get_zoomed_window_site(::collection::index iWorkspace, ::int_rectangle & rectangle);
      
      virtual int get_zoomed_title_bar_height();
      
      virtual bool get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle);
      virtual bool _get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle);

      //virtual ::collection::count get_desk_workspace_count();
      virtual bool get_desk_workspace_rect(::collection::index iWorkspace, ::int_rectangle & rectangle);

      virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction);



      virtual string get_wallpaper(::collection::index iScreen);
      virtual bool set_wallpaper(::collection::index iScreen, string strWallpaper);


      virtual string_array get_wallpaper();
      virtual void set_wallpaper(const string_array & strWallpaper);


      virtual string impl_get_wallpaper(::collection::index iScreen);
      virtual bool impl_set_wallpaper(::collection::index iScreen, string strWallpaper);


      virtual string os_get_user_theme();
      virtual bool set_os_desktop_theme(string strTheme);


      virtual string impl_get_os_desktop_theme();
      virtual bool impl_set_os_desktop_theme(string strTheme);


      virtual void enable_wallpaper_change_notification();

      virtual bool would_be_docked(const ::int_rectangle & rectangleWouldBeSnapped);

      virtual bool would_be_docked_in_monitor(const ::int_rectangle & rectangleWouldBeSnapped, const ::int_rectangle & rectangleMonitor);

      virtual bool would_be_restored(const ::int_rectangle & rectangleWouldBeRestored);

      virtual bool would_be_restored_in_monitor(const ::int_rectangle & rectangleWouldBeRestored, const ::int_rectangle & rectangleMonitor);

void * raw_x11_display() override;
   };


} // namespace windowing



