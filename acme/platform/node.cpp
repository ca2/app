//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "acme/id.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"


namespace acme
{


   node::node()
   {

      m_papexnode = nullptr;
      m_pauranode = nullptr;
      m_edesktop = ::user::e_desktop_none;

      m_pAcmePosix = nullptr;
      m_pApexPosix = nullptr;
      m_pAuraPosix = nullptr;

      m_pAcmePlatform = nullptr;
      m_pApexPlatform = nullptr;
      m_pAuraPlatform = nullptr;

      m_pNodeX11 = nullptr;
      m_pNodeXcb = nullptr;

      m_pNodeGnome = nullptr;
      m_pNodeKDE = nullptr;
      m_pNodeXfce = nullptr;

      m_pNodeDesktopEnvironmentGnome = nullptr;
      m_pNodeDesktopEnvironmentKDE = nullptr;
      m_pNodeDesktopEnvironmentXfce = nullptr;

#ifdef LINUX

      m_elinuxdistribution = e_linux_distribution_not_initialized;

#endif

   }


   node::~node()
   {


   }


#ifdef _DEBUG


   i64 node::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 node::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   ::string node::get_file_type_identifier(const char * path)
   {
      
      return "";
      
   }


   ::e_status node::call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
   {

      __throw(error_interface_only);

      return error_interface_only;

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


   string node::audio_get_default_library_name()
   {

      return "";

   }


   ::e_status node::_launch_macos_app(const ::string & pszAppFolder)
   {
      
      __throw(error_interface_only);
      
      return ::error_interface_only;
      
   }


   ::e_status node::_launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs)
   {
      
      __throw(error_interface_only);
   
      return error_interface_only;
      
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

   
   enum_operating_system node::get_operating_system() const
   {

      __throw(error_interface_only);

      return e_operating_system_unknown;

   }


   ::user::enum_desktop node::get_edesktop()
   {

      if (m_edesktop == ::user::e_desktop_none)
      {

         m_edesktop = calculate_edesktop();

      }

      return m_edesktop;

   }


   ::user::enum_desktop node::calculate_edesktop()
   {

      return ::user::e_desktop_none;

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


   ::e_status node::_will_finish_launching()
   {
   
      return ::success;

   }


   ::e_status node::reboot()
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


#ifdef LINUX


   ::enum_linux_distribution node::get_linux_distribution() const
   {

      if(m_elinuxdistribution == e_linux_distribution_not_initialized)
      {

         ((node *)this)->calculate_linux_distribution();

      }

      return m_elinuxdistribution;

   }


   ::e_status node::calculate_linux_distribution()
   {

      return ::success;

   }


#endif


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


   ::file::path node::_module_path()
   {

      return "";

   }


#ifdef WINDOWS_DESKTOP

   platform_char** node::_get_envp(wcsdup_array& a)
   {

      return nullptr;

   }

#endif


   ::file::path node::module_path_source()
   {

      if(m_pathModule.has_char())
      {

         return m_pathModule;

      }

      m_pathModule = _module_path();

      return m_pathModule;

   }


   string node::app_id_to_app_name(const ::string & strAppId)
   {

      string strName;

      for (index i = 0; i < strAppId.length(); i++)
      {

         if (strAppId[i] == '-' || strAppId[i] == '/' || strAppId[i] == '\\')
         {

            strName += "_";

         }
         else
         {

            strName += strAppId[i];

         }

      }

      return strName;

   }


   string node::app_id_to_executable_name(const ::string & strAppId)
   {
      
      string strName = app_id_to_app_name(strAppId);

      return strName;

   }


   bool node::is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      ::file::path path;

      path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

      strBuild = m_psystem->m_pacmefile->as_string(path);

      return strBuild.has_char();

   }


   bool node::set_application_installed(const ::file::path& pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      ::file::path path;

      path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

      return m_psystem->m_pacmefile->put_contents(path, pszBuild);

   }


   ::file::path node::application_installer_folder(const ::file::path& pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      string strFolder = pathExe.folder();

      strFolder.replace(":", "");

      return m_psystem->m_pacmedir->ca2roaming() / "appdata" / strFolder / strAppId / pszPlatform / pszConfiguration / pszLocale / pszSchema;

   }


   ::file::path node::get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration)
   {
      
      auto pathLastRun = get_last_run_application_path(strAppId);
      
      if(pathLastRun.has_char() && m_psystem->m_pacmefile->exists(pathLastRun))
      {
         
         return pathLastRun;
         
      }

      ::file::path pathFolder;

      pathFolder = m_psystem->m_pacmedir->stage(strAppId, pszPlatform, pszConfiguration);

      string strName;

      strName = app_id_to_executable_name(strAppId);

      ::file::path path;

      path = pathFolder / strName;

      return path;

   }





   ::file::path node::get_last_run_application_path_file(const ::string & strAppIdParam)
   {

      string strAppId = strAppIdParam;

      auto iSlash = strAppId.find('/');

      if(iSlash > 0)
      {

         auto iOpenParenthesis = strAppId.find('(', iSlash + 1);

         if(iOpenParenthesis > iSlash + 1)
         {

            auto iCloseParenthesis = strAppId.find('(', iOpenParenthesis + 1);

            if(iCloseParenthesis > iOpenParenthesis + 1)
            {

               strAppId = strAppId.Left(iOpenParenthesis) + strAppId.Mid(iCloseParenthesis + 1);

            }

         }

      }

      ::file::path pathFile = m_psystem->m_pacmedir->local() / "appdata" / strAppId / "last_run_path.txt";

      return pathFile;

   }


   ::file::path node::get_last_run_application_path(const ::string & strAppId)
   {

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      auto psystem = m_psystem;

      auto pfile = psystem->m_pacmefile;

      ::file::path path = pfile->as_string(pathFile);

      return path;

   }


   ::e_status node::set_last_run_application_path(const ::string & strAppId)
   {

      ::file::path path = m_psystem->m_pacmefile->executable();

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      return m_psystem->m_pacmefile->put_contents(pathFile, path);

   }


   ::e_status node::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
   {

      return ::success;

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


   string node::get_file_icon_path(const ::string & pszPath, int iSize)
   {

      return "";

   }


   string node::get_file_content_type(const ::string & pszPath)
   {

      return "";

   }


   int node::os_launch_uri(const ::string & pszUri, char * pszError, int iBufferSize)
   {

      return -1;

   }


   void node::enable_wallpaper_change_notification()
   {


   }


   ::e_status node::node_branch(const ::routine & routine)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status node::node_sync(const ::duration & durationTimeout, const ::routine & routine)
   {

      if(is_main_thread())
      {

         auto estatus = routine();

         if(!estatus)
         {

            return estatus;

         }

         return estatus;

      }
      else
      {

         auto psignalization = __new(::promise::signalization);

         auto proutine = __routine([this, routine, psignalization]()
                                   {

                                      routine();

                                      psignalization->m_evReady.SetEvent();

                                      //::release((::matter * &)psignalization.m_p);

                                   });

         node_branch(proutine);

         if (psignalization->m_evReady.wait().failed())
         {

            return error_timeout;

         }

         return ::success;

      }

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


   void node::node_quit()
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


   ::e_status node::open_folder(const ::file::path & pathFolder)
   {

      __throw(error_interface_only);
     
      return ::error_interface_only;

   }


   ::e_status node::open_file(const ::file::path & path)
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

      auto pathFolder =  pacmedir->get_memory_map_base_folder_path();

      auto path = pathFolder / (strName + ".filememorymap");

      return ::move(path);

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

//
//#ifdef MACOS
//      
//   void node::ns_launch_app(const ::string & psz, const ::string &* argv, int iFlags)
//   {
//      
//      
//   }
//      
//#endif


   ::e_status node::launch_app(const ::string & psz, const char ** argv, int iFlags)
   {
      
      __throw(error_interface_only);
      
      return error_interface_only;
      
   }



   ::e_status node::create_process(const ::string & pszCommandLine, u32 * pprocessID)
   {

      __throw(error_interface_only);

      return false;

   }


   ::e_status node::run_silent(const ::string & strFunct, const ::string & strstrParams)
   {

      __throw(error_interface_only);

      return false;

   }


   bool node::process_modules(string_array& stra, u32 processID)
   {

      __throw(error_interface_only);

      return false;

   }


   bool node::load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir)
   {

      __throw(error_interface_only);

      return false;

   }


   id_array node::get_pids()
   {
      
      __throw(error_interface_only);
   
      return id_array();
      
   }


   id_array node::module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted)
   {
      
      id_array iaPid;

      id_array pids = get_pids();

      string strPath;

      for(auto & iCurrentPid : pids)
      {

         strPath = module_path_from_pid(iCurrentPid.i32());

         if(strPath.compare_ci(pszModulePath) == 0 )
         {

            iaPid.add(iCurrentPid);

         }

      }

      return iaPid;


   }


   string node::module_path_from_pid(u32 pid)
   {
      
      __throw(error_interface_only);

      return "";

   }


   string node::command_line_from_pid(u32 pid)
   {
      
      __throw(error_interface_only);

      return "";

   }


   bool node::is_shared_library_busy(u32 processid, const string_array& stra)
   {

      __throw(error_interface_only);

      return false;

   }


   bool node::is_shared_library_busy(const string_array& stra)
   {

      __throw(error_interface_only);

      return false;

   }


   bool node::process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary)
   {

      __throw(error_interface_only);

      return false;

   }


   void node::shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary)
   {

      __throw(error_interface_only);

   }


   bool node::is_process_running(::u32 pid)
   {

      __throw(error_interface_only);

      return false;

   }


   string node::get_environment_variable(const ::string & pszEnvironmentVariable)
   {

      return "";

   }


   string node::expand_environment_variables(const string & str)
   {

      return str;

   }


   array <::serial::port_info> node::list_serial_ports()
   {

      __throw(error_interface_only);

      return ::array <::serial::port_info>();

   }


   string node::get_user_language()
   {

      return "";

   }


   bool node::get_application_exclusivity_security_attributes(memory & memory)
   {

      return true;

   }


   ::e_status node::register_spa_file_type(const ::string & strAppIdHandler)
   {
      
      __throw(error_interface_only);

      return error_interface_only;

   }


   bool node::low_is_app_app_admin_running(string strPlatform, string strConfiguration)
   {

      ::install::admin_mutex smutex(this, strPlatform);

      return smutex.already_exists();

   }


   void node::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

      if (low_is_app_app_admin_running(strPlatform, strConfiguration))
      {

         return;

      }

      start_program_files_app_app_admin(strPlatform, strConfiguration);

   }


   ::e_status node::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

      return error_failed;

   }


   ::e_status node::get_folder_path_from_user(::file::path & pathFolder)
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }


   //::string node::expand_environment_variables(const ::string & str)
   //{

   //   return str;

   //}

   ::file::path node::command_find_path(const ::string & pszCommand)
   {

#ifdef _UWP

      return "";

#else

      string strPath = getenv("PATH");

      string_array straPath;

      straPath.explode(":", strPath);

      for (auto & str : straPath)
      {

         ::file::path path;

         path = str;

         path /= pszCommand;

         if (m_psystem->m_pacmefile->exists(path))
         {

            return path;

         }

      }

      return pszCommand;

#endif

   }


   ::e_status node::launch_application(::matter * pobject, const ::string & strAppId, const ::string & strParams, int iBitCount)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status node::shell_execute_async(const char * pszFile, const char * pszParams)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status node::shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status node::root_execute_async(const char * pszFile, const char * pszParams)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status node::root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


} // namespace acme



