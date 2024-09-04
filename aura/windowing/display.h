// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


#include "acme/primitive/geometry2d/_collection.h"
////#include "acme/primitive/primitive/object.h"


namespace windowing
{

   // X11 contribution : a display may contain more than one monitor

   class CLASS_DECL_AURA display :
      virtual public ::object
   {
   public:


      void * m_pDisplay;
      void * m_pDisplay2;
#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
      void * _m_pX11Display;
#endif

      pointer_array < monitor >      m_monitora;


      ::pointer<windowing>         m_pwindowing;
      bool                          m_bSystemSynchronizedScreen;

      ::collection::index                         m_iMainMonitor;
      ::collection::index                         m_iMainWorkspace;
      double                        m_dpi;

      ::rectangle_i32_array         m_rectangleaWorkAreas;
      ::string                      m_strDarkModeAnnotation;
      ::point_i32                   m_pointCursor2;



      display();
      ~display() override;


      virtual void initialize_display(::windowing::windowing * pwindowing);
      virtual void finalize_display();

      virtual iptr get_os_data() const;

      virtual window * default_root_window();


      virtual float get_dpi();

      virtual void open_display();
      virtual void close_display();

      virtual bool set_main_monitor(::collection::index iMonitor);
      //virtual ::collection::count get_monitor_count() //;
      //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 * prectangle) //;

//      virtual ::collection::index get_main_workspace(::rectangle_i32 * prectangle = nullptr) ;

      virtual bool set_main_workspace(::collection::index iWorkspace);
      //virtual ::collection::count get_workspace_count() ;
      //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::rectangle_i32 * prectangle) ;

      virtual bool workspace_to_monitor(::rectangle_i32 & rectangle, ::collection::index iMonitor, ::collection::index iWorkspace);

      virtual bool monitor_to_workspace(::rectangle_i32 & rectangle, ::collection::index iWorkspace, ::collection::index iMonitor);

      virtual bool workspace_to_monitor(::rectangle_i32 & rectangle);

      virtual bool monitor_to_workspace(::rectangle_i32 & rectangle);

      //virtual ::collection::count get_desk_monitor_count() ;
      //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::rectangle_i32 * prectangle) ;

      virtual bool has_readily_gettable_absolute_pointer_position() const;

      // dynamically get mouse cursor absolute position (also set it to m_pointCursor2 member).
      virtual ::point_i32 get_mouse_cursor_position();

      virtual ::point_i32 _get_mouse_cursor_position();

      virtual monitor * get_monitor(::collection::index iMonitor);

      virtual monitor * monitor_hit_test(const ::point_i32 & point);

      virtual monitor * get_best_monitor(const ::rectangle_i32 & rectangle);

      virtual void  get_monitor(rectangle_i32_array & rectaMonitor, rectangle_i32_array & rectaIntersect, const ::rectangle_i32 & rectangle);

      virtual ::collection::index initial_frame_position(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bMove, ::user::interaction * pinteraction);

      virtual ::collection::index _get_best_zoneing(::e_display * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bPreserveSize = false);

      virtual ::collection::index get_best_monitor(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default, ::user::interaction * puserinteractionCursorPosition = nullptr);

      virtual ::collection::index get_best_workspace(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default, ::user::interaction * puserinteractionCursorPosition = nullptr);

      virtual ::collection::index get_good_iconify(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle);

      virtual ::collection::index get_good_restore(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction, ::e_display edisplayRestore);

      virtual ::collection::index get_good_move(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction);

      virtual bool is_like_maximized(const ::rectangle_i32& rectangleWorkspace, const ::rectangle_i32& rectangle);

      virtual bool is_like_full_screen(const ::rectangle_i32& rectangleMonitor, const ::rectangle_i32& rectangle);

      virtual void enum_display_monitors();

      virtual ::collection::index get_main_monitor_index();
      virtual ::collection::index get_main_monitor(::rectangle_i32 & rectangle);
      virtual ::size_i32 get_main_monitor_size();

      virtual ::rectangle_i32 get_monitor_union_rectangle();

      virtual ::collection::count get_monitor_count();
      virtual bool get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 & rectangle);
      virtual bool _get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 & rectangle);

      virtual ::collection::index  get_main_monitor_of_rectangle(const ::rectangle_i32 &rectangle);

      virtual ::collection::count get_desk_monitor_count();
      virtual bool get_desk_monitor_rect(::collection::index iMonitor, ::rectangle_i32 & rectangle);


      virtual ::collection::index get_main_workspace(::rectangle_i32 & prectangle);

      virtual ::collection::count get_workspace_count();
      
      virtual bool get_zoomed_window_site(::collection::index iWorkspace, ::rectangle_i32 & rectangle);
      
      virtual int get_zoomed_title_bar_height();
      
      virtual bool get_workspace_rectangle(::collection::index iWorkspace, ::rectangle_i32 & rectangle);
      virtual bool _get_workspace_rectangle(::collection::index iWorkspace, ::rectangle_i32 & rectangle);

      virtual ::collection::count get_desk_workspace_count();
      virtual bool get_desk_workspace_rect(::collection::index iWorkspace, ::rectangle_i32 & rectangle);

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

      virtual bool would_be_docked(const ::rectangle_i32 & rectangleWouldBeSnapped);

      virtual bool would_be_docked_in_monitor(const ::rectangle_i32 & rectangleWouldBeSnapped, const ::rectangle_i32 & rectangleMonitor);

      virtual bool would_be_restored(const ::rectangle_i32 & rectangleWouldBeRestored);

      virtual bool would_be_restored_in_monitor(const ::rectangle_i32 & rectangleWouldBeRestored, const ::rectangle_i32 & rectangleMonitor);


   };


} // namespace windowing



