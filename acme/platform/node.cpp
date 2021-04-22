//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "acme/id.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_dir.h"


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


   string node::audio_get_default_library_name()
   {

      return "";

   }


   ::e_status node::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      initialize_memory_counter();

      return estatus;

   }


   ::e_status node::on_initialize_object()
   {

      auto estatus = ::object::on_initialize_object();

      if (!estatus)
      {

         return estatus;

      }

      m_psystem->m_pacmenode = this;

      return estatus;

   }


   void node::initialize_memory_counter()
   {

      ::initialize_memory_counter(this);

   }


   ::e_status node::system_main()
   {

      auto estatus = m_psystem->main();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status node::on_start_system()
   {

      return ::success;

   }


   //::file::path node::roaming()
   //{

   //   return "";

   //}


   //::file::path node::program_data()
   //{

   //   return "";

   //}


#ifdef WINDOWS


   ::e_status node::register_dll(const ::file::path& pathDll)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


#endif


   void node::install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension)
   {




   }

   ::e_status node::datetime_to_filetime(::filetime_t* pfiletime, const ::datetime::time& time)
   {

      return error_interface_only;
   }


   int node::node_init_check(int *pi, char *** ppz)
   {

      return -1;

   }


   ::e_status node::start_node()
   {

      return ::success;

   }


   ::color::color node::get_system_color(enum_system_color esystemcolor)
   {

      __throw(error_interface_only);

      return argb(0, 0, 0, 0);

   }





   bool node::_os_calc_app_dark_mode()
   {

      return _os_calc_system_dark_mode();

   }


   bool node::_os_calc_system_dark_mode()
   {

      return _os_calc_app_dark_mode();

   }


   void node::defer_initialize_dark_mode()
   {

      if (m_bLastDarkModeApp.is_set() && m_bLastDarkModeSystem.is_set())
      {

         return;

      }

      node_sync(10_s, __routine([this]()
                          {

                             os_calc_user_dark_mode();

                          }));

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

      auto pnode = get_system()->node();

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


   void node::node_branch(const ::routine & routine)
   {

   }


   void node::node_sync(const ::duration & durationTimeout, const ::routine & routine)
   {

      auto proutine = __sync_routine(routine);

      node_fork(proutine);

      proutine->sync_wait(durationTimeout);

   }


//   void node::user_fork(const ::routine & routine)
//   {
//
//
//   }


//   void node::user_sync(const ::duration & durationTimeout, const ::routine & routine)
//   {
//
//      auto proutine = __sync_routine(routine);
//
//      user_fork(proutine);
//
//      proutine->sync_wait(durationTimeout);
//
//   }


   void node::node_post_quit()
   {


   }


//   void node::enum_display_monitors(::aura::session * psession)
//   {
//
//
//   }


   void node::os_post_quit()
   {

   }


  bool node::should_launch_on_node(::subject::subject * psubject)
  {

      return false;

  }


  bool node::defer_launch_on_node(::subject::subject * psubject)
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


  bool node::launch_on_node(::subject::subject * psubject)
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


   double node::get_time_zone()
   {

      return 0.;

   }


   //::e_status node::get_system_time(system_time_t * psystemtime)
   //{

   //   __throw(error_interface_only);

   //   return error_interface_only;

   //}


   //::e_status node::file_time_to_local_file_time(filetime_t *, filetime_t const*)
   //{

   //   __throw(error_interface_only);

   //   return error_interface_only;

   //}


   ::e_status node::open_folder(::file::path & pathFolder)
   {

      __throw(error_interface_only);
     
      return ::error_interface_only;

   }


   //::e_status node::get_system_time_as_file_time(filetime_t * pfiletime)
   //{

   //   return ::error_interface_only;

   //}


   //::e_status node::file_time_to_system_time(system_time_t * psystemtime, const filetime_t * pfiletime)
   //{

   //   return ::error_interface_only;

   //}


   //::e_status node::system_time_to_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
   //{

   //   return error_interface_only;

   //}


   //::e_status node::system_time_to_file_time(filetime_t * pfiletime, const system_time_t * psystemtime)
   //{

   //   return error_interface_only;

   //}


   //::e_status node::time_to_system_time(system_time_t * psystem_time, const time_t * ptime)
   //{

   //   return error_interface_only;

   //}


   //::e_status node::time_to_file_time(filetime_t * pfiletime, const time_t * ptime)
   //{

   //   return error_interface_only;

   //}


   string node::font_name(enum_font efont)
   {

//      auto psystem = m_psystem;
//
//#ifdef WINDOWS
//
//      return windows_font_name(efont);
//
//#elif defined(LINUX)
//
//      auto elinuxdistribution = psystem->get_linux_distribution();
//
//      return linux_font_name(elinuxdistribution, efont);
//
//#else

      return "sans-serif";

//#endif

   }


   ::e_status node::install_sigchld_handler()
   {

      return ::success;

   }


   //string node::font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont)
   //{

   //   switch (eoperatingsystem)
   //   {
   //   case e_operating_system_windows:
   //   {

   //      return windows_font_name(efont);

   //   }
   //   case e_operating_system_linux:
   //   {

   //      auto elinuxdistribution = (::enum_linux_distribution)iVariant;

   //      return linux_font_name(elinuxdistribution, efont);

   //   }
   //   default:
   //   {

   //      return "sans-serif";

   //   }

   //   }

   //}

   
   string node::file_memory_map_path_from_name(const string& strName)
   {

      auto psystem = m_psystem;

      auto pacmedir = psystem->acmedir();

      auto pathFolder = pacmedir->get_memory_map_base_folder_path();

      auto path = pathFolder / (strName + ".filememorymap");

      return path;

   }


   string node::multimedia_audio_mixer_get_default_library_name()
   {

      return "audio_mixer_alsa";

   }


   string node::multimedia_audio_get_default_library_name()
   {

      return "audio_alsa";

   }


   string node::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "music_midi_alsa";

   }


} // namespace acme



