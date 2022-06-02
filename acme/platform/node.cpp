//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "acme/id.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/user/nano/_nano.h"


CLASS_DECL_ACME void exception_message_box(::object* pobject, ::exception& exception, const ::string& strMoreDetails);


namespace acme
{


   node::node()
   {

      //m_bUserDarkMode = false;

      m_uNodeFlags = 0;

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


      m_pWindowingWin32Node = nullptr;

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


   void node::call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
   {

      throw ::interface_only();

      ///throw ::interface_only();

   }
  

   void node::initialize(::object * pobject)
   {

      /*auto estatus = */ ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      
      initialize_memory_counter();

      //return estatus;

   }


   string node::audio_get_default_library_name()
   {

      return "";

   }


   string node::multimedia_audio_get_default_library_name()
   {

      return "audio_alsa";

   }


   string node::multimedia_audio_mixer_get_default_library_name()
   {

      return "audio_mixer_alsa";

   }


   string node::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "music_midi_alsa";

   }


   void node::_launch_macos_app(const ::string & pszAppFolder)
   {
      
      throw ::interface_only();
      
      //throw ::interface_only();
      
   }


   void node::_launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs)
   {
      
      throw ::interface_only();
   
      //throw ::interface_only();
      
   }



   void node::on_initialize_object()
   {

      /*auto estatus = */ ::object::on_initialize_object();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_psystem->m_pacmenode = this;

      //return estatus;

   }

   
   void node::initialize_memory_counter()
   {

      ::initialize_memory_counter(this);

   }


   void node::system_main()
   {

      /* auto estatus =*/ m_psystem->main();

      //g_psystem->m_bIsReadyForUserInteraction = true;
      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void node::_will_finish_launching()
   {

      //return ::success;

   }


   void node::reboot()
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void node::implement(__pointer(::acme::node) & pnode, __pointer(class ::system) & psystem)
   {

      //      auto psystem = m_psystem;
      //
      //      auto estatus = psystem->main();
      //
      //      if (!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      return estatus;

      /*auto estatus = */ system_main();



      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void node::install_crash_dump_reporting(const string & strModuleNameWithTheExeExtension)
   {




   }





   //void node::defer_()
   //{
   //   
   //   return ::success;

   //}









   //::file::path node::roaming()
   //{

   //   return "";

   //}


   //::file::path node::program_data()
   //{

   //   return "";

   //}


#ifdef WINDOWS_DESKTOP


   void node::register_dll(const ::file::path& pathDll)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


#endif


   ::file::path node::module_path_source()
   {

      if (m_pathModule.has_char())
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


   bool node::is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      ::file::path path;

      path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

      strBuild = m_psystem->m_pacmefile->as_string(path);

      return strBuild.has_char();

   }


   void node::set_application_installed(const ::file::path & pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      ::file::path path;

      path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

      m_psystem->m_pacmefile->put_contents(path, pszBuild);

   }


   ::file::path node::application_installer_folder(const ::file::path & pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      string strFolder = pathExe.folder();

      strFolder.replace_with("", ":");

      return m_psystem->m_pacmedirectory->ca2roaming() / "appdata" / strFolder / strAppId / pszPlatform / pszConfiguration / pszLocale / pszSchema;

   }


   ::file::path node::get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration)
   {

      auto pathLastRun = get_last_run_application_path(strAppId);

      if (pathLastRun.has_char() && m_psystem->m_pacmefile->exists(pathLastRun))
      {

         return pathLastRun;

      }

      ::file::path pathFolder;

      pathFolder = m_psystem->m_pacmedirectory->stage(strAppId, pszPlatform, pszConfiguration);

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

      if (iSlash > 0)
      {

         auto iOpenParenthesis = strAppId.find('(', iSlash + 1);

         if (iOpenParenthesis > iSlash + 1)
         {

            auto iCloseParenthesis = strAppId.find('(', iOpenParenthesis + 1);

            if (iCloseParenthesis > iOpenParenthesis + 1)
            {

               strAppId = strAppId.Left(iOpenParenthesis) + strAppId.Mid(iCloseParenthesis + 1);

            }

         }

      }

      ::file::path pathFile = m_psystem->m_pacmedirectory->local() / "appdata" / strAppId / "last_run_path.txt";

      const char * pszPathFile = pathFile;

      INFORMATION("node::get_last_run_application_path_file pathFile:" << pathFile);

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


   void node::set_last_run_application_path(const ::string & strAppId)
   {

      ::file::path path = m_psystem->m_pacmefile->module();

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      const char * pszPath = path;

      INFORMATION("node::set_last_run_application_path_file path:" << path);

      return m_psystem->m_pacmefile->put_contents(pathFile, path);

   }


   ::e_status node::is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
   {

      return ::success;

   }


   void node::install_keyboard_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


   void node::uninstall_keyboard_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


   ::e_status node::is_mouse_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
   {

      return ::success;

   }

   void node::install_mouse_hook(::matter * pmatterListener)
   {

      //return ::success;

   }



   void node::uninstall_mouse_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


   ::file::path node::_module_path()
   {

      return "";

   }


   void node::datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time)
   {

      throw ::interface_only();
      //throw ::interface_only();

   }


   int node::node_init_check(int *pi, char *** ppz)
   {

      return -1;

   }


   void node::start_node()
   {

      //return ::success;

   }


   void node::install_sigchld_handler()
   {

      //return ::success;

   }


   ::color::color node::get_system_color(enum_system_color esystemcolor)
   {

      throw ::interface_only();

      return argb(0, 0, 0, 0);

   }


   bool node::dark_mode() const 
   { 
      
      return m_bDarkMode; 
   
   }

   
   ::color::color node::background_color() const 
   {
      
      return m_colorBackground; 
   
   }


   double node::luminance() const 
   { 
      
      return m_dLuminance; 
   
   }


   void node::background_color(const ::color::color & color)
   {

      if (m_colorBackground == color)
      {

         return;

      }

      m_colorBackground = color;

      m_dLuminance = m_colorBackground.get_luminance();

      m_bDarkMode = m_dLuminance < 0.5;

      on_operating_system_user_color_change();

   }



   int node::get_simple_ui_darkness()
   {

      return m_iWeatherDarkness;

   }


   void node::set_simple_ui_darkness(int iWeatherDarkness)
   {

      m_iWeatherDarkness = iWeatherDarkness;

   }

   void node::fetch_user_color()
   {

   }


   void node::on_operating_system_user_theme_change()
   {


   }


   void node::on_operating_system_user_color_change()
   {


   }


   void node::on_operating_system_font_list_change()
   {


   }



   //double node::get_user_luminance()
   //{

   //   return m_dUserLuminance;

   //}


   //void node::set_system_app_luminance(double dLuminance)
   //{

   //   m_dSystemLuminance = dLuminance;

   //}



   string node::os_get_user_theme()
   {

      return "";

   }


   void node::os_set_user_theme(const ::string & strUserTheme)
   {

      throw ::interface_only();

      //throw ::interface_only();

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


   void node::node_post(const ::procedure & procedure)
   {

//      defer_create_mutex();
//
//      synchronous_lock synchronouslock(mutex());
//
//      m_routineaPost.add(routine);

   }


   void node::node_send(const ::procedure & procedure)
   {

      __send_procedure(this, &node::node_post, procedure);

   }


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


  bool node::should_launch_on_node(::topic * ptopic)
  {

      return false;

  }


  bool node::defer_launch_on_node(::topic * ptopic)
  {

      bool bShouldLaunchOnNode = should_launch_on_node(ptopic);

      if(!bShouldLaunchOnNode)
      {

         return false;

      }

      bool bLaunchedOnNode = launch_on_node(ptopic);

      if(!bLaunchedOnNode)
      {

         return false;

      }

      return true;

  }


  bool node::launch_on_node(::topic * ptopic)
  {

      return false;

  }


  string node::get_user_name()
  {


     return "";

  }


  ::color::color node::get_simple_ui_color(::enum_element eelement, ::user::enum_state estate)
  {

     ::color::color color;

     if (eelement == ::e_element_background)
     {

        if (dark_mode())
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

        if (dark_mode())
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


 

   void node::browse_for_folder(::file::path & pathFolder)
   {

      throw ::interface_only();
     
      //throw ::interface_only();

   }


   void node::browse_for_file(::file::path & path)
   {

      throw ::interface_only();
     
      //throw ::interface_only();

   }


   double node::get_time_zone()
   {

      return 0.;

   }


//void node::get_system_time_as_file_time(file_time_t * pfile_time)
   //{

   //   throw ::interface_only();

   //}


   //void node::file_time_to_system_time(system_time_t * psystemtime, const file_time_t * pfile_time)
   //{

   //   throw ::interface_only();

   //}


   //void node::system_time_to_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
   //{

   //   throw ::interface_only();

   //}


   //void node::system_time_to_file_time(file_time_t * pfile_time, const system_time_t * psystemtime)
   //{

   //   throw ::interface_only();

   //}


   //void node::time_to_system_time(system_time_t * psystem_time, const time_t * ptime)
   //{

   //   throw ::interface_only();

   //}


   //void node::time_to_file_time(file_time_t * pfile_time, const time_t * ptime)
   //{

   //   throw ::interface_only();

   //}


   string node::font_name(enum_font efont)
   {

      if(efont == e_font_sans)
      {

         return FONT_SANS;

      }
      else if(efont == e_font_sans_ex)
      {

         return FONT_SANS_EX;

      }
      else if(efont == e_font_sans_fx)
      {

         return FONT_SANS_FX;

      }
      else if(efont == e_font_sans_ui)
      {

         return FONT_SANS_UI;

      }
      else if(efont == e_font_serif)
      {

         return FONT_SERIF;

      }
      else if(efont == e_font_serif_ex)
      {

         return FONT_SERIF_EX;

      }
      else if(efont == e_font_serif_fx)
      {

         return FONT_SERIF_FX;

      }
      else if(efont == e_font_serif_ui)
      {

         return FONT_SERIF_UI;

      }
      else if(efont == e_font_monospace)
      {

         return FONT_MONO;

      }

      return "";

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

      auto pacmedirectory = psystem->acmedir();

      auto pathFolder =  pacmedirectory->get_memory_map_base_folder_path();

      auto path = pathFolder / (strName + ".filememorymap");

      return ::move(path);

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

   enum_operating_system node::get_operating_system() const
   {

      throw ::interface_only();

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


#ifdef LINUX


   ::enum_linux_distribution node::get_linux_distribution() const
   {

      if (m_elinuxdistribution == e_linux_distribution_not_initialized)
      {

         ((node *)this)->calculate_linux_distribution();

      }

      return m_elinuxdistribution;

   }


   void node::calculate_linux_distribution()
   {

      //return ::success;

   }


#endif


#ifdef WINDOWS_DESKTOP

   
   platform_char ** node::_get_envp(wcsdup_array & a)
   {

      return nullptr;

   }


#endif


   void node::launch_app(const ::string & psz, const char ** argv, int iFlags)
   {
      
      throw ::interface_only();
      
      //throw ::interface_only();
      
   }



   void node::create_process(const ::string & pszCommandLine, u32 * pprocessID)
   {

      //throw ::interface_only();

      throw ::interface_only();
      //return false;

   }


   void node::run_silent(const ::string & strFunct, const ::string & strstrParams)
   {

      throw ::interface_only();

      //return false;

   }


   bool node::process_modules(string_array& stra, u32 processID)
   {

      throw ::interface_only();

      //return false;

   }


   bool node::load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir)
   {

      //throw ::interface_only();

      throw ::interface_only();

      return false;

   }


   id_array node::get_pids()
   {
      
      //throw ::interface_only();

      throw ::interface_only();
   
      //return id_array();
      
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
      
      //throw ::interface_only();

      throw ::interface_only();

      return "";

   }


   string node::command_line_from_pid(u32 pid)
   {
      
      //throw ::interface_only();

      throw ::interface_only();

      return "";

   }


   bool node::is_shared_library_busy(u32 processid, const string_array& stra)
   {

      throw ::interface_only();

      return false;

   }


   bool node::is_shared_library_busy(const string_array& stra)
   {

      throw ::interface_only();

      return false;

   }


   bool node::process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary)
   {

      //throw ::interface_only();

      throw ::interface_only();

      return false;

   }


   void node::shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary)
   {

      //throw ::interface_only();

      throw ::interface_only();

   }


   bool node::is_process_running(::u32 pid)
   {

      //throw ::interface_only();

      //return false;

      throw ::interface_only();

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


   void node::set_environment_variable(const ::string& pszEnvironmentVariable, const ::string& pszValue)
   {

      //throw ::interface_only();

      throw ::interface_only();

      //return

   }


#if !defined(_UWP)


   array <::serial::port_info> node::list_serial_ports()
   {

      //throw ::interface_only();

      throw ::interface_only();

      return ::array <::serial::port_info>();

   }

#endif

   string node::get_user_language()
   {

      return "";

   }


   bool node::get_application_exclusivity_security_attributes(memory & memory)
   {

      return true;

   }


   void node::register_spa_file_type(const ::string & strAppIdHandler)
   {
      
      //throw ::interface_only();

      throw ::interface_only();

      //throw ::interface_only();

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


   void node::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

      //return error_failed;

   }


   void node::get_folder_path_from_user(::file::path & pathFolder)
   {

      //throw ::interface_only();

      throw ::interface_only();

      //throw ::interface_only();

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


   void node::launch_application(::matter * pobject, const ::string & strAppId, const ::string & strParams, int iBitCount)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::shell_open(const ::file::path & path, const ::string & strParam, const ::file::path & pathFolder)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::aaa_shell_execute_async(const char * pszFile, const char * pszParams)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::aaa_shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::root_execute_async(const char * pszFile, const char * pszParams)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::on_start_system()
   {

      //return ::success;

   }


   void node::create_app_shortcut(::app * papp)
   {


   }


   void node::report_exception_to_user(::object* pobject, ::exception& exception, const ::string& strMoreDetails)
   {

      exception_message_box(this, exception, strMoreDetails);

   }


   __pointer(::conversation) node::create_new_message_box_conversation()
   {

      initialize_nano_window();

      return __create_new < ::nano_message_box >();

   }


   __pointer(::sequence < ::conversation >) node::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox)
   {

      auto psequence = __new(::sequence < ::conversation >());

      auto pmessagebox = create_new_message_box_conversation();

      psequence->m_p = pmessagebox;

      pmessagebox->m_psequence = psequence;

      pmessagebox->do_message_box(strMessage, strTitle, emessagebox);

      return psequence;

   }


   //void node::nano_message_box(::sequence < ::conversation >* psequence, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox)
   //{


   //}


    void node::shell_launch(const ::string & strAppId)
    {

       throw interface_only();

    }


    bool node::has_application_capability(::enum_application_capability ecapability) const
    {

       return m_eapplicationcapabilitya.contains(ecapability);

    }


    void node::add_application_capability(const ::enum_application_capability_array& ecapabilitya)
    {

       m_eapplicationcapabilitya.add_unique(ecapabilitya);

       on_change_application_capability();

    }


    void node::on_change_application_capability()
    {


    }


    void node::windowing_post(const ::procedure& procedure)
    {


    }


} // namespace acme



