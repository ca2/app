//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "sequencer.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/handler/request.h"
#include "acme/memory/counter.h"
#include "acme/platform/exclusive.h"
#include "acme/operating_system/application.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/exception/interface_only.h"
//#include "acme/primitive/collection/array.h"
//#include "acme/primitive/collection/string_array.h"
#include "acme/user/nano/button.h"
#include "acme/user/nano/message_box.h"



CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception& exception, const ::string& strMoreDetails);


//CLASS_DECL_ACME void operating_system_open_url(const ::scoped_string & scopedstrUrl);


namespace acme
{


   node::node()
   {

      //m_bUserDarkMode = false;

      m_bCallstackInitialized = false;
      m_bUpdateCallstack = false;

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

      //m_pNodeX11 = nullptr;
      //m_pNodeXcb = nullptr;

      m_pNodeGnome = nullptr;
      m_pNodeKDE = nullptr;
      m_pNodeXfce = nullptr;

      m_pNodeDesktopEnvironmentGnome = nullptr;
      m_pNodeDesktopEnvironmentKDE = nullptr;
      m_pNodeDesktopEnvironmentXfce = nullptr;


      //m_pWindowingWin32Node = nullptr;

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


   ::string node::get_file_type_identifier(const ::file::path & path)
   {
      
      return "";
      
   }


   void node::call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode)
   {

      throw ::interface_only();

      ///throw ::interface_only();

   }


   ::process_identifier_array node::module_list_file_processes_identifiers(const ::scoped_string & scopedstrAppId)
   {

      ::process_identifier_array idaPid;

#if defined(UNIVERSAL_WINDOWS)

      idaPid.add(-1);

#else

      //idaPid = pnode->get_pid_from_module_list_file(path, false);

      string_array stra;

      ::file::path pathModule;

      pathModule = acmedirectory()->roaming() / scopedstrAppId;

      pathModule /= "module_list.txt";

      string strModuleList = acmefile()->as_string(pathModule);

      stra.add_lines(strModuleList);

   repeat:

      if (stra.get_count() > 32)
      {

         stra.erase_at(0, 16);

      }

      string_array stra2;

      int_array iaPid2;

      auto psystem = acmesystem();

      auto pnode = psystem->node();

      for (auto & str : stra)
      {

         if (str.has_char())
         {

            string_array a;

            a.explode("|", str);

            if (a.get_size() >= 2)
            {

               string strProcessName = a[0];

               string strProcessId = a[1];

               int iProcessId = ansi_to_i32(strProcessId);

               stra2.case_insensitive_add_unique(strProcessName);

               string strPath = pnode->process_identifier_module_path(iProcessId);

               if (strPath.has_char())
               {

                  if (acmepath()->real_path_is_same(strPath, strProcessName))
                  {

                     idaPid.add(iProcessId);

                  }

               }

            }

         }

      }

      if (idaPid.get_count() <= 0 && stra.get_size() > 32)
      {

         goto repeat;

      }

      //for(auto & str : stra2)
      //{

      //   if(str.has_char())
      //   {

      //          iaPid.add_unique(module_path_get_pid(str));
   //
      //   }

      //}

#endif

      return idaPid;

   }


   ::pointer < ::particle > node::create_mutex()
   {

      return __create < ::mutex >();

   }
  

   void node::initialize(::particle * pparticle)
   {

      /*auto estatus = */ ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      
      initialize_memory_counter();

      //return estatus;


   }


   ::pointer < ::particle > node::create_quit_particle(::pointer<::acme::node> &  pnode, ::pointer<::acme::system> & psystem)
   {
      
      return nullptr;
      
   }


   void node::implement(::pointer<::acme::node>& pnode, ::pointer<::acme::system> & psystem)
   {
      
      m_pparticleQuit = create_quit_particle(pnode, psystem);

      if(psystem->m_pfnImplement || psystem->m_pacmeapplication->m_bConsole)
      {
         
         psystem->init_task();

         if (psystem->m_pacmeapplication->m_bSession)
         {

            psystem->m_pacmesession->init_task();

         }

         psystem->m_pacmeapplication->init_task();

         if(psystem->m_pfnImplement)
         {
            
            (*psystem->m_pfnImplement)(psystem);
            
         }
         else
         {

            auto prequest = __create_new < ::request >();

            prequest->initialize_command_line2(psystem->m_pacmeapplication->m_strCommandLine);

            psystem->m_pacmeapplication->get_property_set().merge(prequest->get_property_set());
            
            psystem->m_pacmeapplication->main();
            
         }

         psystem->m_pnode.release();
         
         return;
         
      }
      
      //acme_application_main(pApplication, argc, argv);
      
      acme_application_main(psystem);
      
      //return psystem->m_estatus;
      

      //auto estatus =
      
      //::acme::apple::node::implement(pnode, psystem);

   //         if(!estatus)
   //         {
   //
   //            return estatus;
   //
   //         }
   //
   //         return estatus;

   }


   void node::start_application(::pointer<::acme::node>& pnode, ::pointer<::acme::system>& psystem)
   {

      m_pparticleQuit = create_quit_particle(pnode, psystem);

      //if (psystem->m_pfnImplement)
      {

         psystem->init_task();

         //(*psystem->m_pfnImplement)(psystem);

         //psystem->m_pnode.release();

         //return;

      }

   //   //acme_application_main(pApplication, argc, argv);

   //   acme_application_main(psystem);

   //   //return psystem->m_estatus;


   //   //auto estatus =

   //   //::acme::apple::node::implement(pnode, psystem);

   ////         if(!estatus)
   ////         {
   ////
   ////            return estatus;
   ////
   ////         }
   ////
   ////         return estatus;

   }


   void node::acme_application_main(::acme::system * psystem)
   {

      system_main();
      
   }


   void node::_will_finish_launching()
   {
      
      
   }


   string node::audio_get_default_implementation_name()
   {

      return "";

   }


   string node::multimedia_audio_get_default_implementation_name()
   {

      return acmesystem()->implementation_name("audio", "alsa");

   }


   string node::multimedia_audio_mixer_get_default_implementation_name()
   {

      return acmesystem()->implementation_name("audio_mixer", "alsa");

   }


   string node::veriwell_multimedia_music_midi_get_default_implementation_name()
   {

      return acmesystem()->implementation_name("music_midi", "alsa");

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



   void node::on_initialize_particle()
   {

      /*auto estatus = */ ::object::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pcontext->m_pacmenode = this;

      //return estatus;

   }

   
   void node::initialize_memory_counter()
   {

      //::initialize_memory_counter(this);

   }


   void node::system_main()
   {

      /* auto estatus =*/ acmesystem()->main();

      //g_psystem->m_bIsReadyForUserInteraction = true;
      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


//   void node::_will_finish_launching()
//   {
//
//      //return ::success;
//
//   }


   void node::reboot()
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


//   void node::implement(::pointer<::acme::node>& pnode, ::pointer<::acme::system> psystem)
//   {
//
//      //      auto psystem = acmesystem();
//      //
//      //      auto estatus = psystem->main();
//      //
//      //      if (!estatus)
//      //      {
//      //
//      //         return estatus;
//      //
//      //      }
//      //
//      //      return estatus;
//
//      /*auto estatus = */ system_main();
//
//
//
//      //if(!estatus)
//      //{
//
//      //   return estatus;
//
//      //}
//
//      //return estatus;
//
//   }


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


   //__new(::pointer < ::mutex >(this, false, "Local\\ca2-appmatter")

   ::pointer < ::mutex > node::create_local_named_mutex(::particle * pparticleContext, bool bInitialOwner, const ::string & strName, security_attributes * psecurityattributes)
   {

      return nullptr;

   }


   ::pointer < ::mutex > node::create_global_named_mutex(::particle * pparticleContext, bool bInitialOwner, const ::string & strName, security_attributes * psecurityattributes)
   {

      return nullptr;

   }


   ::pointer < ::mutex > node::open_local_named_mutex(::particle * pparticleContext, const ::string & strName)
   {

      return nullptr;

   }


   ::pointer < ::mutex > node::open_global_named_mutex(::particle * pparticleContext, const ::string & strName)
   {

      return nullptr;

   }


   ::pointer < ::mutex > node::get_install_mutex(::particle *pparticleContext, const ::string &strPlatform, const ::string & strSuffix)
   {

      string strName = "::ca2::account::ccwarehouse::install::" + strPlatform + "::200010001951042219770204-11dd-ae16-0800200c7784" + strSuffix;

      return open_global_named_mutex(pparticleContext, strName);

   //__new(::install::pointer < ::mutex >(this, process_platform_name())

   }


   ::pointer < ::acme::exclusive > node::_get_exclusive(::particle * pparticleContext, const ::string & strName, security_attributes * psecurityattributes)
   {

      return nullptr;

   }


   ::pointer < ::acme::exclusive > node::get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes)
   {

      auto & pexclusive = m_mapExclusive[strName];

      if (!pexclusive)
      {

         auto pexclusiveNew = _get_exclusive(pparticleContext, strName, psecurityattributes);

         pexclusive = pexclusiveNew;

      }

      return pexclusive;

   }


   bool node::erase_exclusive(const ::string & strName)
   {

      return m_mapExclusive.erase_item(strName);

   }


   void node::release_exclusive()
   {

      m_mapExclusive.clear();

   }


   bool node::exclusive_fails(::particle * pparticleContext, const ::string & strName, security_attributes * psecurityattributes)
   {

      auto pexclusive = get_exclusive(pparticleContext, strName, psecurityattributes);

      if (!pexclusive)
      {

         return false;

      }

      return pexclusive->exclusive_fails();

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

      strBuild = acmefile()->as_string(path);

      return strBuild.has_char();

   }


   void node::set_application_installed(const ::file::path & pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      ::file::path path;

      path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

      acmefile()->put_contents(path, pszBuild);

   }


   ::file::path node::application_installer_folder(const ::file::path & pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      string strFolder = pathExe.folder();

      strFolder.replace_with("", ":");

      return acmedirectory()->ca2roaming() / "appdata" / strFolder / strAppId / pszPlatform / pszConfiguration / pszLocale / pszSchema;

   }


   ::file::path node::get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration)
   {

      auto pathLastRun = get_last_run_application_path(strAppId);

      if (pathLastRun.has_char() && acmefile()->exists(pathLastRun))
      {

         return pathLastRun;

      }

      ::file::path pathFolder;

      pathFolder = acmedirectory()->stage(strAppId, pszPlatform, pszConfiguration);

      string strName;

      strName = app_id_to_executable_name(strAppId);

      ::file::path path;

      path = pathFolder / strName;

      return path;

   }


   ::file::path node::get_last_run_application_path_file(const ::string & strAppIdParam)
   {

      string strAppId = strAppIdParam;

      auto range = strAppId();

      auto pSlash = range.find('/');

      if (::is_set(pSlash))
      {

         auto pOpenParenthesis = range(pSlash + 1).find('(');

         if (::is_set(pOpenParenthesis))
         {

            auto pCloseParenthesis = range(pOpenParenthesis + 1).find(')');

            if (::is_set(pCloseParenthesis))
            {

               strAppId = range(0, pOpenParenthesis) + range(pCloseParenthesis + 1);

            }

         }

      }

      ::file::path pathFile = acmedirectory()->roaming() / strAppId / "last_run_path.txt";

      //const ::file::path & pathFile = pathFile;

      information() << "node::get_last_run_application_path_file pathFile:" << pathFile;

      return pathFile;

   }


   ::file::path node::get_last_run_application_path(const ::string & strAppId)
   {

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      ::file::path path = acmefile()->as_string(pathFile);

      return path;

   }


   void node::set_last_run_application_path(const ::string & strAppId)
   {

      ::file::path path = acmefile()->module();

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      information() << "node::set_last_run_application_path_file path:" << path;

      return acmefile()->put_contents(pathFile, path);

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

      set_dark_mode(m_dLuminance < 0.5);

   }


   void node::set_dark_mode(bool bDark)
   {

      m_bDarkMode = bDark;

      if (m_bDarkMode)
      {

         ::output_debug_string("background_color :: Dark\n");

      }
      else
      {

         ::output_debug_string("background_color :: Lite\n");

      }

      on_operating_system_user_color_change();

   }


//   int node::get_simple_ui_darkness()
//   {
//
//      return m_iWeatherDarkness;
//
//   }
//
//
//   void node::set_simple_ui_darkness(int iWeatherDarkness)
//   {
//
//      m_iWeatherDarkness = iWeatherDarkness;
//
//   }


   void node::fetch_user_color()
   {

   }


   void node::on_operating_system_user_theme_change()
   {


   }


   void node::on_operating_system_user_color_change()
   {

      //auto psystem = acmesystem();

      //psystem->signal(id_operating_system_user_color_change);

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


   void node::os_process_user_icon_theme(string strTheme)
   {

   }


   bool node::set_wallpaper(index iScreen, string strLocalImagePath)
   {

      throw interface_only();

      //return pnode->set_wallpaper(iScreen, strLocalImagePath);

      return false;

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


   bool node::has_xcb() const
   {

      return false;

   }


   void * node::get_os_xcb_connection()
   {

      return nullptr;

   }




   void node::node_post(const ::procedure & procedure)
   {

//      defer_create_synchronization();
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      m_routineaPost.add(routine);

   }


   void node::node_send(const ::procedure & procedure)
   {

      __matter_send_procedure(this, this, &node::node_post, procedure);

   }


   void node::post_procedure(const ::procedure & procedure)
   {

      node_post(procedure);

   }


   void node::send_procedure(const ::procedure & procedure)
   {

      node_send(procedure);

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


   ::color::color node::get_default_color(::color::color color)
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


   //void node::system_time_to_earth_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
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

      auto pathFolder = acmedirectory()->get_memory_map_base_folder_path();

      auto path = pathFolder / (strName + ".filememorymap");

      return ::transfer(path);

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


   ::process_identifier node::create_process(const ::string & pszCommandLine)
   {

      throw ::interface_only();
      
      return -1;

   }


   void node::run_silent(const ::string & strFunct, const ::string & strstrParams)
   {

      throw ::interface_only();

      //return false;

   }


   ::file::path_array node::process_identifier_modules_paths(::process_identifier processidentifier)
   {

      throw ::interface_only();

      return {};

   }


   ::file::path_array node::modules_paths()
   {

      auto processidentifiera = processes_identifiers();

      ::file::path_array patha;

      for (auto processidentifier : processidentifiera)
      {

         auto pathaProcessModules = process_identifier_modules_paths(processidentifier);

         patha.case_insensitive_append_unique(pathaProcessModules);

      }

      return ::transfer(patha);

   }


   bool node::load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir)
   {

      //throw ::interface_only();

      throw ::interface_only();

      return false;

   }


   ::process_identifier_array node::processes_identifiers()
   {
      
      //throw ::interface_only();

      throw ::interface_only();
   
      //return atom_array();
      
   }


   ::process_identifier_array node::module_path_processes_identifiers(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted)
   {

      ::process_identifier_array processesidentifiers;
      
      auto processesidentifiersAll = processes_identifiers();

      for(auto & processidentifier : processesidentifiersAll)
      {

         auto path = process_identifier_module_path(processidentifier);

         if(path.case_insensitive_equals(pszModulePath))
         {

            processesidentifiers.add(processidentifier);

         }

      }

      return processesidentifiers;

   }


   string node::process_identifier_module_path(::process_identifier processidentifier)
   {
      
      //throw ::interface_only();

      throw ::interface_only();

      return "";

   }


   string node::process_identifier_command_line(::process_identifier processidentifier)
   {
      
      //throw ::interface_only();

      throw ::interface_only();

      return "";

   }


   //bool is_shared_library_busy(::process_identifier processidentifier, const string_array & stra) override;

        //bool is_shared_library_busy(const string_array & stra) override;
   
   
   //bool node::is_shared_library_busy(::process_identifier processidentifier, const string_array & stra)
   //{

   //   auto straModulesPaths = process_identifier_modules_paths(processidentifier);

   //   for (auto & strModulePath : straModulesPaths)
   //   {

   //      ::file::path path = strModulePath;

   //      if(stra.path.name() )

   //   }


   //      straSuffix.surround("\\");

   //   return ::windows::for_each_process_module(processidentifier, [&](auto & moduleentry32)
   //      {

   //      return !straSuffix.case_insensitive_suffixes(string(moduleentry32.szModule)) && !stra.case_insensitive_contains(string(moduleentry32.szModule));

   //      });

   //}


   //bool node::is_shared_library_busy(const string_array & stra)
   //{

   //   return ::acme_windows::predicate_process([&](auto pid)
   //      {

   //      return !is_shared_library_busy(pid, stra);

   //      });

   //}


   bool node::process_contains_module(string& strImage, ::process_identifier processidentifier, const ::string & pszLibrary)
   {

      //throw ::interface_only();

      throw ::interface_only();

      return false;

   }


   ::process_identifier_array node::shared_library_process(string_array& straProcesses, const ::string & pszLibrary)
   {

      //throw ::interface_only();

      throw ::interface_only();

   }


   bool node::is_process_running(::process_identifier processidentifier)
   {

      //throw ::interface_only();

      //return false;

      throw ::interface_only();

      return false;

   }


   ::string node::get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
   {

      return {};

   }


   ::string node::expand_environment_variables(const ::scoped_string & scopedstr)
   {

      return scopedstr;

   }


   void node::set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string & scopedstrValue)
   {

      throw ::interface_only();

   }


#if !defined(UNIVERSAL_WINDOWS)


   ::array <::serial::port_info> node::list_serial_ports()
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


   ::pointer < security_attributes > node::get_application_exclusivity_security_attributes()
   {

      return nullptr;

   }


   void node::register_spa_file_type(const ::string & strAppIdHandler)
   {
      
      //throw ::interface_only();

      throw ::interface_only();

      //throw ::interface_only();

   }


   bool node::low_is_app_app_admin_running(string strPlatform, string strConfiguration)
   {

      throw ::exception(todo);

//      ::install::admin_mutex smutex(this, strPlatform);
//
//      return smutex.already_exists();

return false;

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

#ifdef UNIVERSAL_WINDOWS

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

         if (acmefile()->exists(path))
         {

            return path;

         }

      }

      return pszCommand;

#endif

   }


   void node::launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::shell_open(const ::file::path & path, const ::string & strParam, const ::file::path & pathFolder)
   {

      throw ::interface_only();

   }


   void node::open_url(const ::string & strUrl)
   {

      throw ::interface_only();

      //::operating_system_open_url(strUrl);

   }


   void node::shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class ::time& timeTimeout)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   void node::on_start_system()
   {

      //return ::success;

   }


   void node::create_app_shortcut(::acme::application * papp)
   {


   }


   void node::report_exception_to_user(::particle* pparticle, ::exception& exception, const ::string& strMoreDetails)
   {

      auto psequencer = exception_message_box(exception, strMoreDetails);

      psequencer->do_synchronously();

   }


   ::pointer<::conversation>node::create_new_message_box_conversation()
   {

      initialize_nano_window();

      return __create_new < ::nano_message_box >();

   }


   pointer< ::sequencer < ::conversation > > node::create_message_box_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
   {

      auto psequencer = __new(::sequencer < ::conversation >());

      auto pmessagebox = create_new_message_box_conversation();

      psequencer->m_psequence = pmessagebox;

      pmessagebox->m_psequencer = psequencer;

      pmessagebox->initialize_conversation(strMessage, strTitle, emessagebox, strDetails);

      return psequencer;

   }


   pointer< ::sequencer < ::conversation > > node::create_message_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails)
   {

      auto psequencer = __new(::sequencer < ::conversation >());

      auto pmessage = create_new_message_conversation();

      psequencer->m_psequence = pmessage;

      pmessage->m_psequencer = psequencer;

      pmessage->initialize_conversation(strMessage, strTitle, emessagebox, strDetails);

      return psequencer;

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


    string node::get_local_mutex_name(const ::string& strAppId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.format("Local\\%s", strApp.c_str());

       return strMutex;

    }


    string node::get_local_id_mutex_name(const ::string& strAppId, const ::string& strId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.format("Local\\%s, atom:%s", strApp.c_str(), strId.c_str());

       return strMutex;

    }


    string node::get_global_mutex_name(const ::string& strAppId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.format("Global\\%s", strApp.c_str());

       return strMutex;

    }


    string node::get_global_id_mutex_name(const ::string& strAppId, const ::string& strId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.format("Global\\%s, atom:%s", strApp.c_str(), strId.c_str());

       return strMutex;

    }


   //::string node::get_callstack()
   //{
   //   
   //   return {};
   //   
   //}


::process_identifier node::current_process_identifier()
   {

      return -1;

   }
   
   
   bool node::stdin_has_input_events()
   {

      return false;

   }


   void node::flush_stdin_input_events()
   {


   }


   void node::flush_stdin()
   {


   }


   //void node::defer_initialize_callstack()
   //{


   //}


   //string node::get_callstack(const ::scoped_string & scopedstrFormat, i32 iSkip, void * caller_address, int iCount)
   //{

   //   return {};

   //}


   ::string node::get_command_line()
   {

      return {};

   }


   string node::process_version_dir_name()
   {

      return is_release_build() ? "release" : "debug";

   }


   int node::is_debug_build()
   {

#ifdef _DEBUG

      return true;

#else

      return false;

#endif


   }


   int node::is_release_build()
   {

#ifdef _DEBUG

      return false;

#else

      return true;

#endif

   }


   bool node::succeeded(const ::error_code& errorcode)
   {

      if (errorcode.m_etype == e_error_code_type_errno)
      {

         return errorcode.m_iOsError == 0;

      }
      else if (errorcode.m_etype == e_error_code_type_last_error)
      {

         return errorcode.m_iOsError == 0;

      }

      throw interface_only();

      return false;
    
   }

   bool node::failed(const ::error_code& errorcode)
   {

      return !succeeded(errorcode);

   }


#ifdef WINDOWS


   error_code node::defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
   {

      throw interface_only();

      return {};

   }


#endif


   ::file::path node::core_app_path(string strAppId)
   {

      ::file::path path = get_last_run_application_path(strAppId);

      if (path.has_char())
      {

         return path;

      }

      strAppId.find_replace("-", "_");

      strAppId.find_replace("/", "_");

      path = "C:\\acme\\time\\x64\\basis\\" + strAppId + ".exe";

      return path;

   }
   
   
   //bool node::shell_execute_async(const ::string & pszFile, const ::string & pszParams)
   //{

   //   return false;

   //}


   //bool node::shell_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout)
   //{

   //   return false;

   //}

   //
   //bool node::root_execute_async(const ::string & pszFile, const ::string & pszParams)
   //{

   //   return false;

   //}


   //bool node::root_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout)
   //{

   //   return false;

   //}


   string node::executable_title_from_appid(const string & strParam)
   {

      string str(strParam);

#ifdef WINDOWS

#ifdef CUBE

      str = "static_" + str;

#else

      str = "shared_" + str;

#endif

#endif

      str.replace_with("_", "-");

      str.replace_with("_", "/");

      return str;

   }


   void node::prepare_argc_argv(int & argc, char ** argv, char * cmd_line)
   {

      char * pPtr = nullptr;

      char * p;

      char * psz = cmd_line;

      enum enum_state
      {

         e_state_initial,

         state_quote,

         state_non_space,

      };

      enum_state e = e_state_initial;

      char quote = '\0';

      while (psz != nullptr && *psz != '\0')
      {

         if (e == e_state_initial)
         {

            if (*psz == ' ')
            {

               unicode_increment(psz);

            }
            else if (*psz == '\"')
            {

               quote = '\"';

               unicode_increment(psz);

               argv[argc++] = (char *)psz;

               e = state_quote;

            }
            else if (*psz == '\'')
            {

               quote = '\'';

               unicode_increment(psz);

               argv[argc++] = (char *)psz;

               e = state_quote;

            }
            else
            {

               argv[argc++] = (char *)psz;

               unicode_increment(psz);

               e = state_non_space;

            }

         }
         else if (e == state_quote)
         {

            if (*psz == '\\')
            {

               memory_transfer(psz, psz + 1, strlen(psz));

               unicode_increment(psz);

            }
            else if (*psz == quote)
            {

               p = unicode_next(psz);

               *psz = '\0';

               psz = p;

               e = e_state_initial;

            }
            else
            {

               unicode_increment(psz);

            }

         }
         else
         {

            if (*psz == ' ')
            {

               p = unicode_next(psz);

               *psz = '\0';

               psz = p;

               e = e_state_initial;

            }
            else
            {

               unicode_increment(psz);

            }

         }

      }

      argv[argc] = nullptr;

   }



   string node::process_platform_name()
   {

#if defined(_M_IX86)

      return "Win32";

#else

      return "x64";

#endif

   }



   string node::time_binary_platform(const ::string & strPlatformParam)
   {

      ::string strPlatform(strPlatformParam);

      strPlatform.make_lower();

      if (strPlatform == "x86" || strPlatform == "win32")
      {

         return "Win32";

      }
      else if (strPlatform == "x64" || strPlatform == "amd64")
      {

         return "x64";

      }
      else
      {

         return strPlatform;

      }

   }



   string node::process_configuration_name()
   {

#ifdef __DEBUG

      return "debug";

#else

      return "release";

#endif

   }


   int node::get_current_process_affinity_order()
   {

      return -1;

   }


   int node::get_current_process_maximum_affinity()
   {

      return -1;

   }


   ::u64 node::translate_processor_affinity(::i32 i)
   {

      return 0;

   }


   ::i32 node::get_current_processor_index()
   {

      return -1;

   }


   bool node::set_process_priority(::enum_priority epriority)
   {

      
      throw interface_only();
      
      return false;


   }


//   void node::command_system(string_array & straOutput, int & iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem, const class time & timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLines)
//   {
//
//      throw interface_only();
//
//   }


   int node::command_system(const ::scoped_string& scopedstr, const class ::time& timeOut)
   {

      throw interface_only();

      return -1;

   }


//   int node::command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction)
//   {
//
//      return command_system(scopedstr, tracefunction);
//
//   }


   int node::command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction)
   {

      throw interface_only();

      return -1;

   }


   void node::open_terminal_and_run(const ::scoped_string& scopedstr)
   {

      throw interface_only();

   }


#if !defined(WINDOWS)


   string_array node::cmdline_from_pid(::process_identifier pid)
   {

      throw interface_only();

      return {};

   }


   atom_array  node::app_get_pid(const ::string & strApp)
   {

      throw interface_only();

      return {};

   }


#endif


   void node::_node_file_dialog(::file::file_dialog * pdialog)
   {


   }


   void node::_node_folder_dialog(::file::folder_dialog * pdialog)
   {


   }


   class file_dialog : virtual public ::file::file_dialog
   {
   public:
      
      void run() override { acmenode()->_node_file_dialog(this); }
      
   };


   ::pointer < ::file::file_dialog > node::node_file_dialog()
   {
      
      return __create_new < file_dialog >();
      
   }


   class folder_dialog : virtual public ::file::folder_dialog
   {
   public:
      
      void run() override { acmenode()->_node_folder_dialog(this); }
      
   };


   ::pointer < ::file::folder_dialog > node::node_folder_dialog()
   {
      
      return __create_new < folder_dialog >();
      
   }


   ::file::path node::library_file_name(const ::scoped_string & scopedstr)
   {

      throw interface_only();

      return scopedstr;

   }


   void node::integration_factory()
   {



   }


   //void node::unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip)
   //{

   //   command_system("cmd.exe -c \"unzip \"" + pathZip + "\" -d \"" + pathFolder + "\"");

   //}


   ::string node::get_user_permanent_environment_variable(const ::scoped_string& scopedstr)
   {

      throw ::interface_only();

      return {}; 
   
   }

   
   void node::set_user_permanent_environment_variable(const ::scoped_string& scopedstr, const ::scoped_string& strPayload)
   {

      throw ::interface_only();

   }


#ifdef WINDOWS_DESKTOP


   void node::_beta_use_unicode_utf8()
   {

      throw ::interface_only();

   }


#endif


   void node::set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string& scopedstrCommand)
   {

      throw ::interface_only();

   }



   bool node::has_unix_shell_command(const ::scoped_string& scopedstrCommand)
   {

      try
      {

         ::string strCommand;

         strCommand.format("command -v %s", scopedstrCommand.c_str());

         auto iExitCode = unix_shell_command(strCommand);

         return iExitCode == 0;

      }
      catch (...)
      {

      }

      return false;

   }


//#ifdef LINUX


   int node::unix_shell_command(const ::scoped_string& scopedstrCommand, const trace_function & tracefunction)
   {
//
//      try
//      {
//
//         ::string strUnixShell;
//
//         strUnixShell = "/bin/bash";
//
//         ::string strCommand;
//
//         ::string strCommandInner;
//
//         strCommandInner = scopedstrCommand.c_str();
//
//         strCommandInner.find_replace("\"", "\\\"");
//
//         strCommand.format("\"%s\" -c \"%s\"", strUnixShell.c_str(), strCommandInner.c_str());
//
//         auto iExitCode = acmenode()->command_system(strCommand);
//
//         return iExitCode;
//
//      }
//      catch (...)
//      {
//
//      }

      return -1;

   }


   ::string node::unix_shell_command_string(const ::scoped_string & scopedstrCommand)
   {

      ::string strLog;

      auto iExitCode = unix_shell_command(scopedstrCommand, [&strLog](auto etracelevel, auto str)
      {

         strLog += ::string(str) + "\n";

      });

      return strLog;

   }


   ::string node::operating_system_store_release()
   {

      return {};
      
   }


   ::pointer <::operating_system::summary > node::operating_system_summary()
   {

      throw ::interface_only();

      return nullptr;

   }


   //void node::module_path_main_window_post_close(const ::scoped_string & scopestr)
   //{

   //}


   ::pointer < ::operating_system::application > node::module_path_application(const ::scoped_string & scopestr)
   {

      throw ::interface_only();

      return nullptr;

   }

   
   ::pointer < ::operating_system::application > node::process_identifier_application(::process_identifier processidentifier)
   {
      
      auto papplication = __create < ::operating_system::application >();
      
      papplication->open_by_process_identifier(processidentifier);
      
      return papplication;
      
   }


   ::pointer < ::operating_system::application > node::application_predicate(const ::function < bool(::operating_system::application * papplication) > & function)
   {

      auto processidentifiera = processes_identifiers();

      for (auto & processidentifier : processidentifiera)
      {

         auto papplication = __create < ::operating_system::application >();

         papplication->open_by_process_identifier(processidentifier);

         if (function(papplication))
         {

            return papplication;

         }

      }

      return nullptr;

   }


   ::string node::get_character_set_default_sample_text(enum_character_set echaracterset)
   {

      if (m_mapCharacterSetDefaultSampleText.is_empty())
      {

         load_character_set_default_sample_text();

      }

      return m_mapCharacterSetDefaultSampleText[echaracterset];

    
   }


   void node::load_character_set_default_sample_text()
   {

      throw interface_only();

   }


} // namespace acme



