//
// Created by camilo on 12/04-April/2022. 22:07 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"
namespace acme
{

   namespace windowing
   {


      class CLASS_DECL_ACME display :
         virtual public ::object
      {
      public:


         ::int_point             m_pointCursor2;

         //enum_display_type       m_edisplaytype;

         ::string                         m_strDarkModeAnnotation;
         bool                             m_bDisplayOpened;



         display();
         ~display() override;


         virtual void open_display();


         void destroy() override;


         ::collection::count get_monitor_count();
         //virtual enum_display_type get_display_type();


         //virtual void initialize_display_type(enum_display_type edisplaytype);


         void kick_idle() override;


         virtual void display_post(const ::procedure& procedure);


         virtual void display_send(const ::procedure& procedure);


         virtual ::int_size get_main_screen_size();

         virtual void * raw_x11_display();

         //virtual void release_mouse_capture();


         virtual bool is_dark_mode_through_theming();
         virtual ::string theming_ui_name();


         virtual void enable_wallpaper_change_notification();

         virtual string get_wallpaper(::collection::index iScreen);
         virtual void set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper);


         virtual string_array get_wallpaper();
         virtual void set_wallpaper(const string_array & straWallpaper);


         virtual ::string _get_wallpaper(::collection::index iScreen);
         virtual void _set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper);


         virtual ::string get_desktop_theme();
         virtual void set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme);


         virtual string impl_get_desktop_theme();
         virtual void impl_set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme);


         virtual ::string get_desktop_icon_theme();
         virtual void set_desktop_icon_theme(const ::scoped_string & scopedtrDesktopIconTheme);


         //virtual void enable_wallpaper_change_notification();
         
      };


   } // namespace windowing


} // namespace acme
