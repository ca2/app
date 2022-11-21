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
#if defined(LINUX) || defined(FREEBSD)
      void * _m_pX11Display;
#endif

      pointer_array < monitor >      m_monitora;


      ::pointer<windowing>         m_pwindowing;
      bool                          m_bSystemSynchronizedScreen;

      index                         m_iMainMonitor;
      index                         m_iMainWorkspace;
      double                        m_dpi;


      display();
      ~display() override;


      virtual void initialize_display(::windowing::windowing * pwindowing);

      virtual iptr get_os_data() const;

      virtual window * default_root_window();


      virtual float get_dpi();

      virtual void open();

      virtual bool set_main_monitor(index iMonitor);
      //virtual ::count get_monitor_count() //;
      //virtual bool  get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle) //;

//      virtual index get_main_workspace(RECTANGLE_I32 * prectangle = nullptr) ;

      virtual bool set_main_workspace(index iWorkspace);
      //virtual ::count get_workspace_count() ;
      //virtual bool  get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle) ;

      virtual bool workspace_to_monitor(RECTANGLE_I32 & rectangle, index iMonitor, index iWorkspace);

      virtual bool monitor_to_workspace(RECTANGLE_I32 & rectangle, index iWorkspace, index iMonitor);

      virtual bool workspace_to_monitor(RECTANGLE_I32 & rectangle);

      virtual bool monitor_to_workspace(RECTANGLE_I32 & rectangle);

      //virtual ::count get_desk_monitor_count() ;
      //virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle) ;

      virtual monitor * get_monitor(index iMonitor);

      virtual void  get_monitor(rectangle_i32_array & rectaMonitor, rectangle_i32_array & rectaIntersect, const ::rectangle_i32 & rectangle);

      virtual index initial_frame_position(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bMove, ::user::interaction * pinteraction);

      virtual index _get_best_zoneing(::e_display * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bPreserveSize = false);

      virtual index get_best_monitor(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default, ::windowing::window * pwindowCursorPosition = nullptr);

      virtual index get_best_workspace(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default, ::windowing::window * pwindowCursorPosition = nullptr);

      virtual index get_good_iconify(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle);

      virtual index get_good_restore(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction, ::e_display edisplayRestore);

      virtual index get_good_move(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction);


      virtual void enum_display_monitors();

      virtual ::index get_main_monitor_index();
      virtual ::index get_main_monitor(RECTANGLE_I32 & rectangle);
      virtual ::size_i32 get_main_monitor_size();

      virtual ::size_i32 get_monitor_union_size();

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rectangle(index iMonitor, RECTANGLE_I32 & rectangle);

      virtual ::index  get_main_monitor_of_rectangle(const ::rectangle_i32 &rectangle);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 & rectangle);


      virtual index get_main_workspace(RECTANGLE_I32 & prectangle);

      virtual ::count get_workspace_count();
      virtual bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 & rectangle);

      virtual ::count get_desk_workspace_count();
      virtual bool get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32 & rectangle);

      virtual index get_ui_workspace(::user::interaction * pinteraction);



      virtual string get_wallpaper(index iScreen);
      virtual bool set_wallpaper(index iScreen, string strWallpaper);


      virtual string_array get_wallpaper();
      virtual void set_wallpaper(const string_array & strWallpaper);


      virtual string impl_get_wallpaper(index iScreen);
      virtual bool impl_set_wallpaper(index iScreen, string strWallpaper);


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



