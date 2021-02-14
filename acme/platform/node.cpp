//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "acme/id.h"


namespace acme
{


   node::node()
   {

      m_papexnode = nullptr;
      m_pauranode = nullptr;
      m_edesktop = ::user::e_desktop_none;

   }


   node::~node()
   {


   }


   int node::node_init_check(int *pi, char *** ppz)
   {

      return -1;

   }


   void node::os_application_system_run()
   {


   }


   ::color::color node::get_system_color(enum_system_color esystemcolor)
   {

      __throw(interface_only_exception());

      return argb(0, 0, 0, 0);

   }


   enum_operating_system node::get_operating_system() const
   {

      return e_operating_system_none;

   }


   enum_linux_distribution node::get_linux_distribution() const
   {

      return e_linux_distribution_unknown;

   }


   ::user::enum_desktop node::calc_edesktop()
   {

      return user::e_desktop_none;

   }


   ::user::enum_desktop node::get_edesktop()
   {

      if (m_edesktop == ::user::e_desktop_none)
      {

         m_edesktop = calc_edesktop();

      }

      return m_edesktop;

   }



   bool node::_os_calc_app_dark_mode()
   {

      return false;

   }


   bool node::_os_calc_system_dark_mode()
   {

      return false;

   }


   void node::defer_initialize_dark_mode()
   {

      if (m_bLastDarkModeApp.is_set() && m_bLastDarkModeSystem.is_set())
      {

         return;

      }

      os_calc_user_dark_mode();

   }


   ::e_status node::set_system_dark_mode1(bool bSet)
   {


      return ::success;

   }


   ::e_status node::set_app_dark_mode1(bool bSet)
   {

      return ::success;

   }


   ::e_status node::set_internal_system_dark_mode(bool bDark)
   {

      m_bLastDarkModeApp = bDark;

      return ::success;

   }


   ::e_status node::set_internal_app_dark_mode(bool bDark)
   {

      m_bLastDarkModeApp = bDark;

      return ::success;

   }


   bool node::is_system_dark_mode()
   {

      if (m_bLastDarkModeSystem.is_empty())
      {

         os_calc_user_dark_mode();

      }

      return m_bLastDarkModeSystem;

   }

   
   bool node::is_app_dark_mode()
   {

      if (m_bLastDarkModeApp.is_empty())
      {

         defer_initialize_dark_mode();

      }

      return m_bLastDarkModeApp;

   }


   ::color::color node::get_system_app_background_color()
   {

      return m_colorSystemAppBackground;

   }


   void node::set_system_app_background_color(::color::color color)
   {

      m_colorSystemAppBackground = color;

   }


   double node::get_system_app_luminance()
   {

      return m_dSystemLuminance;

   }


   void node::set_system_app_luminance(double dLuminance)
   {

      m_dSystemLuminance = dLuminance;

   }


   int node::get_simple_ui_darkness()
   {

      return m_iWeatherDarkness;

   }


   void node::set_simple_ui_darkness(int iWeatherDarkness)
   {

      m_iWeatherDarkness = iWeatherDarkness;

   }


   void node::os_calc_user_dark_mode()
   {

      bool bDarkModeApp = _os_calc_app_dark_mode();

      bool bDarkModeSystem = _os_calc_system_dark_mode();

      if(m_bLastDarkModeApp != bDarkModeApp
      || m_bLastDarkModeSystem != bDarkModeSystem)
      {

         m_bLastDarkModeApp = bDarkModeApp;

         m_bLastDarkModeSystem = bDarkModeSystem;

         System.deliver(id_os_dark_mode);

         on_os_dark_mode_change();

      }

   }


   void node::on_os_dark_mode_change()
   {


   }


   string node::os_get_user_theme()
   {

      return "";

   }


   bool node::os_set_user_theme(const ::string & strUserTheme)
   {

      return false;

   }


   void node::os_process_user_theme(string strTheme)
   {



   }


   bool node::set_wallpaper(index iScreen, string strLocalImagePath)
   {

      auto pnode = Node;

      if(::is_null(pnode))
      {

         return false;

      }

      return pnode->set_wallpaper(iScreen, strLocalImagePath);

   }


   string node::get_wallpaper(index iScreen)
   {

      return "";

   }


   string node::get_file_icon_path(const char * pszPath, int iSize)
   {

      return "";

   }


   string node::get_file_content_type(const char * pszPath)
   {

      return "";

   }


   int node::os_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
   {

      return -1;

   }


   void node::enable_wallpaper_change_notification()
   {


   }


   void node::node_fork(const ::promise::routine & routine)
   {

   }


   void node::node_sync(const ::duration & durationTimeout, const ::promise::routine & routine)
   {

      auto proutine = __sync_routine(routine);

      node_fork(proutine);

      proutine->sync_wait(durationTimeout);

   }


   void node::user_fork(const ::promise::routine & routine)
   {


   }


   void node::user_sync(const ::duration & durationTimeout, const ::promise::routine & routine)
   {

      auto proutine = __sync_routine(routine);

      user_fork(proutine);

      proutine->sync_wait(durationTimeout);

   }


   void node::node_post_quit()
   {


   }


   void node::enum_display_monitors(::aura::session * psession)
   {


   }


   void node::os_post_quit()
   {

   }


  bool node::should_launch_on_node(::promise::subject * psubject)
  {

      return false;

  }


  bool node::defer_launch_on_node(::promise::subject * psubject)
  {

      bool bShouldLaunchOnNode = should_launch_on_node(psubject);

      if(!bShouldLaunchOnNode)
      {

         return false;

      }

      bool bLaunchedOnNode = launch_on_node(psubject);

      if(!bLaunchedOnNode)
      {

         return false;

      }

      return true;

  }


  bool node::launch_on_node(::promise::subject * psubject)
  {

      return false;

  }


  string node::get_user_name()
  {


     return "";

  }


  ::color::color node::get_simple_ui_color(::user::enum_element eelement, ::user::enum_state estate)
  {

     ::color::color color;

     if (eelement == ::user::e_element_background)
     {

        if (is_app_dark_mode())
        {

           color = argb(255, 0x50, 0x50, 0x58);

        }
        else
        {

           color = argb(255, 0xcd, 0xcd, 0xc8);

        }

     }
     else
     {

        if (is_app_dark_mode())
        {

           color = argb(255, 255, 255, 255);

        }
        else
        {

           color = argb(255, 49, 50, 42);

        }

     }

      return color;

   }


   ::color::color node::get_default_color(::u64 u )
   {

      return argb(255, 0, 0, 0);

   }


   void node::set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha)
   {


   }


   ::e_status node::get_system_time_as_file_time(filetime_t * pfiletime)
   {

      return ::error_interface_only;

   }


   ::e_status node::file_time_to_system_time(system_time_t * psystemtime, const filetime * pfiletime)
   {

      return ::error_interface_only;

   }


   double node::get_time_zone()
   {

      return 0.;

   }


   ::e_status node::get_system_time(system_time_t * psystemtime)
   {

      __throw(interface_only_exception());

      return error_interface_only;

   }


   ::e_status node::file_time_to_local_file_time(filetime*, filetime const*)
   {

      __throw(interface_only_exception());

      return error_interface_only;

   }


   ::e_status node::open_folder(::file::path & pathFolder)
   {

      __throw(interface_only_exception());
     
      return ::error_interface_only;

   }


} // namespace acme



