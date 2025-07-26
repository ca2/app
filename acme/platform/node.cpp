//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
//#include "sequencer.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/constant/id.h"
#include "acme/exception/status.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/handler/request.h"
#include "acme/memory/counter.h"
#include "acme/platform/exclusive.h"
#include "acme/operating_system/application.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/exception/interface_only.h"
//#include "acme/prototype/collection/array.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/button.h"
#include "acme/user/micro/message_box.h"
#include "acme/user/micro/user.h"
#include "acme/user/user/os_theme_colors.h"
#include "acme/windowing/windowing.h"
#include "filesystem/filesystem/listing.h"

#ifdef WINDOWS_DESKTOP

__FACTORY_EXPORT void nano_http_wininet_factory(::factory::factory * pfactory);
__FACTORY_EXPORT void nano_compress_windows_factory(::factory::factory * pfactory);

#endif

//namespace nano{namespace  user{
//::user::enum_operating_ambient calculate_edesktop();
//}//namespace user
//   }//namespace nano
//
::string errno_error_message(int iError);

#if REFERENCING_DEBUGGING
CLASS_DECL_ACME::reference_referer* refdbg_get_top_referer();
CLASS_DECL_ACME::subparticle* refdbg_get_track_allocation();
#endif


CLASS_DECL_ACME void exception_message_box(::particle * pparticle, ::exception& exception, const ::string& strMoreDetails);
CLASS_DECL_ACME ::string as_string(::windowing::enum_toolkit etoolkit);

//CLASS_DECL_ACME void operating_system_open_url(const ::scoped_string & scopedstrUrl);

int get_processor_count();


namespace platform
{


   node::node()
   {

      //m_bUserDarkMode = false;

      //m_bDropboxCalculated = false;

      //m_bDropbox = false;

      m_bOneDriveCalculated = false;

      m_bOneDrive = false;

      m_bCallStackInitialized = false;
      m_bUpdateCallStack = false;

      m_uNodeFlags = 0;

      //m_papexnode = nullptr;
      //m_pauranode = nullptr;
      //m_edesktop = ::user::e_operating_ambient_none;
      //m_etoolkit = ::user::e_toolkit_none;

      //m_pAcmePosix = nullptr;
      //m_pApexPosix = nullptr;
      //m_pAuraPosix = nullptr;

      //m_pAcmePlatform = nullptr;
      //m_pApexPlatform = nullptr;
      //m_pAuraPlatform = nullptr;

      //m_pNodeX11 = nullptr;
      //m_pNodeXcb = nullptr;

      //m_pNodeGtk3 = nullptr;
      //m_pNodeGtk4 = nullptr;
      //m_pNodeGtkBased = nullptr;

      //m_pNodeXfce = nullptr;

      //m_pNodeKDE5 = nullptr;
      //m_pNodeKDE6 = nullptr;

      //m_pNodeDesktopEnvironmentGtkBased = nullptr;
      //m_pNodeDesktopEnvironmentKDE = nullptr;
      //m_pNodeDesktopEnvironmentXfce = nullptr;


      //m_pWindowingWin32Node = nullptr;

      //m_bOperatingSystemDarkMode = false;

      m_pthemecolors = nullptr;

//#if defined(WITH_X11)
  //    m_pvoidX11Display = nullptr;
    //  m_estatusInitializeX11 = error_not_initialized;
//#endif


   }


   node::~node()
   {


   }


#ifdef _DEBUG


   long long node::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long node::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

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

      pathModule = directory_system()->roaming() / scopedstrAppId;

      pathModule /= "module_list.txt";

      string strModuleList = file_system()->as_string(pathModule);

      stra.add_lines(strModuleList);

   repeat:

      if (stra.get_count() > 32)
      {

         stra.erase_at(0, 16);

      }

      string_array stra2;

      ::int_array iaPid2;

      auto psystem = system();

      auto pnode = psystem->node();

      for (auto & str : stra)
      {

         if (str.has_character())
         {

            string_array a;

            a.explode("|", str);

            if (a.get_size() >= 2)
            {

               string strProcessName = a[0];

               string strProcessId = a[1];

               int iProcessId = ansi_to_int(strProcessId);

               stra2.case_insensitive_add_unique(strProcessName);

               string strPath = pnode->process_identifier_module_path(iProcessId);

               if (strPath.has_character())
               {

                  if (path_system()->real_path_is_same(strPath, strProcessName))
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

      //   if(str.has_character())
      //   {

      //          iaPid.add_unique(module_path_get_pid(str));
   //
      //   }

      //}

#endif

      return idaPid;

   }


   ::enum_id node::key_command(::user::enum_key ekey, ::user::key_state* pkeystate)
   {

      return ::id_none;

   }


   void node::defer_add_to_system_recent_file_list(const ::file::path& pathNew)
   {


   }


   ::particle_pointer node::create_mutex()
   {

      return __øcreate < ::mutex >();

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


   void node::node_application_on_status(const char * pszStatus, void * p, long long hi)
   {
      
      
   }


   //::particle_pointer node::create_quit_particle(::pointer<::platform::node> &  pnode, ::pointer<::platform::system> & psystem)
   //{
   //   
   //   return nullptr;
   //   
   //}


   void node::node_implement_main()
   {

      //m_pparticleQuit = create_quit_particle(pnode);

      auto psystem = system();

      psystem->m_papplication->__task_init();

      psystem->init_task();

      if (application()->m_bSession)
      {

         session()->init_task();

      }

      psystem->m_papplication->init_task();

      if (psystem->m_pfnImplement)
      {

         (*psystem->m_pfnImplement)(application());

      }
      else
      {

         auto prequest = __create_new < ::request >();

         prequest->initialize_command_line2(::system()->m_strCommandLine);

         psystem->m_papplication->property_set().merge(prequest->property_set());

         psystem->m_papplication->main();

      }

      //::system::->m_pnode.release();

   }


   ::file::path node::get_default_base_integration_folder()
   {

      return directory_system()->home() / "integration/_____";

   }


   //::file::path node::___fonts_folder()
   //{

   //   throw interface_only();

   //   return {};

   //}


   void node::node_main()
   {
      

      auto psystem = system();

      if (psystem->m_pfnImplement || ::system()->is_console())
      {

         node_implement_main();

         return;

      }

      on_start_system();

      on_system_main();

   }


   void node::on_start_system()
   {

      //system()->defer_post_initial_request();

      if(!::system()->is_console())
      {

         system()->m_htask = nullptr;

         system()->m_itask = nullptr;

         system()->branch_synchronously({.m_ptaskhandler = system()->acme_windowing()});
         //system()->acme_windowing()->on_start_system();

      }

   }


   void node::on_app_activated(::user::activation_token * puseractivationtoken)
   {
      
      
   }


   void node::on_system_main()
   {

      ///system()->main();

      application()->on_system_main();

   }


   //void node::start_application(::pointer<::platform::node>& pnode, ::pointer<::platform::system>& psystem)
   void node::start_application(::pointer<::platform::node> & pnode)
   {

      //m_pparticleQuit = create_quit_particle(pnode, psystem);

      auto psystem = system();

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


   // void node::acme_application_main(::platform::system * psystem)
   // {

   //    system_main();
      
   // }


   void node::_will_finish_launching()
   {
      
      
   }


   void node::_did_finish_launching()
   {
      
      
   }


   string node::audio_get_default_implementation_name()
   {

      return "";

   }


   string node::multimedia_audio_get_default_implementation_name()
   {

      return system()->implementation_name("audio", "alsa");

   }


   string node::multimedia_audio_mixer_get_default_implementation_name()
   {

      return system()->implementation_name("audio_mixer", "alsa");

   }


   string node::veriwell_multimedia_music_midi_get_default_implementation_name()
   {

      return system()->implementation_name("music_midi", "alsa");

   }


   void node::defer_register_server_library(const ::platform::uuid & uuid, const ::file::path & path)
   {

      throw ::interface_only();

   }



   void node::defer_unregister_server_library(const ::platform::uuid & uuid, const ::file::path & path)
   {

      throw ::interface_only();

   }


   bool node::is_server_library_registered(::file::path & path, const ::platform::uuid & uuid)
   {

      throw ::interface_only();

      return false;

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

      //m_papplication->m_pnode = this;

      //return estatus;

   }

   
   void node::initialize_memory_counter()
   {

      //::initialize_memory_counter(this);

   }


   void node::system_main()
   {

      /* auto estatus =*/ system()->canonical_system_main();

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


//   void node::implement(::pointer<::platform::node>& pnode, ::pointer<::platform::system> psystem)
//   {
//
//      //      auto psystem = system();
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


   //void node::do_windowing_system_factory()
   //{

   //   ::string strUserToolkit = ::windowing::get_user_toolkit_id();

   //   if(strUserToolkit.has_character())
   //   {

   //      auto pfactory = system()->factory("windowing_system", strUserToolkit);

   //      pfactory->merge_to_global_factory();

   //   }

   //}



   void node::defer_show_system_menu(::user::mouse * pmouse)
   {


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

      if (m_pathModule.has_character())
      {

         return m_pathModule;

      }

      m_pathModule = _module_path();

      return m_pathModule;

   }


   //__allocate < ::pointer < ::mutex > >(this, false, "Local\\ca2-appmatter")

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

   //__allocate< ::install::pointer < ::mutex > >(this, process_platform_name()

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

      for (::collection::index i = 0; i < strAppId.length(); i++)
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

      strBuild = file_system()->as_string(path);

      return strBuild.has_character();

   }


   void node::set_application_installed(const ::file::path & pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      ::file::path path;

      path = application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

      file_system()->put_contents(path, pszBuild);

   }


   ::file::path node::application_installer_folder(const ::file::path & pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema)
   {

      string strFolder = pathExe.folder();

      strFolder.replace_with("", ":");

      return directory_system()->ca2roaming() / "appdata" / strFolder / strAppId / pszPlatform / pszConfiguration / pszLocale / pszSchema;

   }


   ::file::path node::get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration)
   {

      auto pathLastRun = get_last_run_application_path(strAppId);

      if (pathLastRun.has_character() && file_system()->exists(pathLastRun))
      {

         return pathLastRun;

      }

      ::file::path pathFolder;

      pathFolder = directory_system()->stage(strAppId, pszPlatform, pszConfiguration);

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

      ::file::path pathFile = directory_system()->roaming() / strAppId / "last_run_path.txt";

      //const ::file::path & pathFile = pathFile;

      information() << "node::get_last_run_application_path_file pathFile:" << pathFile;

      return pathFile;

   }


   ::file::path node::get_last_run_application_path(const ::string & strAppId)
   {

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      ::file::path path = file_system()->as_string(pathFile);

      return path;

   }


   void node::set_last_run_application_path(const ::string & strAppId)
   {

      ::file::path path = file_system()->module();

      ::file::path pathFile = get_last_run_application_path_file(strAppId);

      information() << "node::set_last_run_application_path_file path:" << path;

      return file_system()->put_contents(pathFile, path);

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




   // bool node::dark_mode() const
   // {
   //
   //    return m_bOperatingSystemDarkMode;
   //
   // }
   //

   // ::os_theme_colors * node::_new_os_theme_colors()
   // {
   //
   //    return ___new os_theme_colors();
   //
   // }
   //
   //
   // ::os_theme_colors * node::_get_os_theme_colors()
   // {
   //
   //    if(!m_pthemecolors)
   //    {
   //
   //       _fetch_user_color();
   //
   //    }
   //
   //    return m_pthemecolors;
   //
   // }



   // void node::_fill_os_theme_colors(::os_theme_colors * pthemecolors)
   // {
   //
   //    pthemecolors->m_colorBack = argb(255, 255, 255, 255);
   //    pthemecolors->m_colorFace = argb(255, 128, 128, 128);
   //    pthemecolors->m_colorFore = argb(255, 0, 0, 0);
   //
   // }
   //
   //
   // void node::_set_os_theme_colors(::os_theme_colors * pthemecolors)
   // {
   //
   //    m_pthemecolors = pthemecolors;
   //
   // }
   //
   //
   // void node::_del_os_theme_colors(::os_theme_colors * pthemecolors)
   // {
   //
   //    delete pthemecolors;
   //
   // }


   // void node::_term_os_theme_colors()
   // {
   //
   //    if(m_pthemecolors)
   //    {
   //
   //       _del_os_theme_colors(m_pthemecolors);
   //
   //       m_pthemecolors = nullptr;
   //
   //    }
   //
   // }
   //
   //
   // void node::_fetch_user_color()
   // {
   //
   //    if(m_pthemecolors)
   //    {
   //
   //       _del_os_theme_colors(m_pthemecolors);
   //
   //       m_pthemecolors = nullptr;
   //
   //    }
   //
   //    {
   //
   //       auto pthemecolors = _new_os_theme_colors();
   //
   //       _fill_os_theme_colors(pthemecolors);
   //
   //       _set_os_theme_colors(pthemecolors);
   //
   //    }
   //
   // }


   // void node::fetch_user_color()
   // {
   //
   //
   //
   //    _fetch_user_color();
   //
   //    auto pthemecolors = _get_os_theme_colors();
   //
   //    auto colorBack = pthemecolors->m_colorBack;
   //
   //    system()->background_color(colorBack);
   //
   //    m_bOperatingSystemDarkMode = colorBack.get_luminance() < 0.5;
   //
   // }


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


//   void node::fetch_user_color()
//   {
//
//   }


   // void node::on_operating_system_user_theme_change()
   // {
   //
   //
   // }
   //
   //
   // void node::on_operating_system_user_color_change()
   // {
   //
   //    //auto psystem = system();
   //
   //    //psystem->signal(id_operating_system_user_color_change);
   //
   // }
   //
   //
   // void node::on_operating_system_font_list_change()
   // {
   //
   //
   // }



   //double node::get_user_luminance()
   //{

   //   return m_dUserLuminance;

   //}


   //void node::set_system_app_luminance(double dLuminance)
   //{

   //   m_dSystemLuminance = dLuminance;

   //}



   // string node::os_get_user_theme()
   // {
   //
   //    return "";
   //
   // }


   // void node::os_set_user_theme(const ::string & strUserTheme)
   // {
   //
   //    throw ::interface_only();
   //
   //    //throw ::interface_only();
   //
   // }


   // void node::os_process_user_theme(string strTheme)
   // {
   //
   // }
   //
   //
   // void node::os_process_user_icon_theme(string strTheme)
   // {
   //
   // }


//   bool node::set_wallpaper(::collection::index iScreen, string strLocalImagePath, ::acme::windowing::display * pwindowingdisplay)
//   {
//
//      throw interface_only();
//
//      //return pnode->set_wallpaper(iScreen, strLocalImagePath);
//
//      return false;
//
//   }
//
//
//   string node::get_wallpaper(::collection::index iScreen, ::acme::windowing::display * pwindowingdisplay)
//   {
//
//      return "";
//
//   }


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


//   void node::enable_wallpaper_change_notification()
//   {
//
//
//   }


   bool node::has_xcb()
   {

      return false;

   }


   void * node::get_os_xcb_connection()
   {

      return nullptr;

   }


   bool node::is_wayland()
   {

      string strWaylandDisplay(get_environment_variable("WAYLAND_DISPLAY"));

      return strWaylandDisplay.has_character();

   }


   void node::_user_send(const ::procedure & procedure)
   {

      if(::is_main_thread())
      {

         procedure();

         return;

      }

      auto phappening = __allocate manual_reset_happening();

      user_post([ procedure, phappening ]
      {

         procedure();

         phappening->set_happening();

      });

      if(!phappening->wait(procedure.timeout()))
      {

         throw ::exception(error_timeout);

      }

   }


   void node::defer_do_main_tasks()
   {


   }


   // void node::user_post_quit()
   // {
   //
   //
   // }


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


   void node::set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha)
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


   //void node::file_time_to_system_time(system_time * psystemtime, const file_time_t * pfile_time)
   //{

   //   throw ::interface_only();

   //}


   //void node::system_time_to_earth_time(posix_time * ptime, const system_time & systemtime, int nDST)
   //{

   //   throw ::interface_only();

   //}


   //void node::system_time_to_file_time(file_time_t * pfile_time, const system_time & systemtime)
   //{

   //   throw ::interface_only();

   //}


   //void node::time_to_system_time(system_time * psystem_time, const posix_time * ptime)
   //{

   //   throw ::interface_only();

   //}


   //void node::time_to_file_time(file_time_t * pfile_time, const posix_time * ptime)
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

      auto pathFolder = directory_system()->get_memory_map_base_folder_path();

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


   //::user::enum_operating_ambient node::get_eoperating_ambient()
   //{

   //   if (m_edesktop == ::user::e_operating_ambient_none)
   //   {

   //      m_edesktop = calculate_edesktop();

   //   }

   //   return m_edesktop;

   //}


   //::user::enum_operating_ambient node::calculate_edesktop()
   //{

   //   return ::micro::calculate_edesktop();

   //}


   //::user::enum_toolkit node::get_etoolkit()
   //{

   //   if (m_etoolkit == ::user::e_toolkit_none)
   //   {

   //      m_etoolkit = calculate_etoolkit();

   //   }

   //   return m_etoolkit;

   //}


   //::user::enum_toolkit node::calculate_etoolkit()
   //{

   //   return ::micro::calculate_etoolkit();

   //}




#ifdef LINUX


   ::enum_linux_distribution node::get_linux_distribution() const
   {

      throw ::interface_only();

      return e_linux_distribution_unknown;

   }


   void node::calculate_linux_distribution()
   {

      //return ::success;

   }


#endif


   ::string node::display_file_path(const ::file::path & path)
   {

      return path;

   }


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


   ::file::path node::get_executable_path_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion)
   {

      ::string_array stra;

      stra.explode("/", scopedstrAppId);

      if(stra.get_count() != 2)
      {

         throw exception(error_invalid_parameter);

      }

      return get_executable_path_by_app_id(stra[0], stra[1], bSingleExecutableVersion);

   }


   ::file::path node::get_executable_path_by_app_id(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp, bool bSingleExecutableVersion)
   {

      string strName = scopedstrRepos + "_" + scopedstrApp;

      strName.find_replace("-", "_");

      ::file::path path;

#if defined(WINDOWS)

      if (bSingleExecutableVersion)
      {

         strName = "static_" + strName + ".exe";

      }
      else
      {

         strName = "shared_" + strName + ".exe";

      }

#elif defined(LINUX) || defined(__BSD__)

      strName = "_" + strName;

#endif

//#ifdef WINDOWS
//
//      auto pathFolder = directory_system()->roaming() / scopedstrRepos / scopedstrApp / "x64" ;
//
//      path = pathFolder / strName;
//
//      return path;
//
//#else

      auto pathFolder = directory_system()->home();

      path = pathFolder / "application" / scopedstrRepos / scopedstrApp / "binary" / strName;
      
#ifdef MACOS
      
      path /= "Contents/MacOS" / scopedstrApp;

#endif

      return path;

//#endif


//#endif

   }


   void node::launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion)
   {

      throw ::interface_only();

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
	   
	   printf_line("node::process_identifier_modules_paths THROW INTERFACE ONLY");

      throw ::interface_only();

      return {};

   }


   ::file::path_array node::modules_paths()
   {

      auto processidentifiera = processes_identifiers();

      ::file::path_array patha;

      for (auto processidentifier : processidentifiera)
      {
         
         informationf("processidentifier=%lld", processidentifier);

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


   ::file::path node::process_identifier_module_path(::process_identifier processidentifier)
   {
      
      //throw ::interface_only();

      throw ::interface_only();

      return {};

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


   void node::unset_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
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

         if (file_system()->exists(path))
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


   void node::open_internet_link_in_browser(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrProfile
                                            , const ::scoped_string & scopedstrTarget)
   {

      open_internet_link(scopedstrUrl, scopedstrProfile, scopedstrTarget);

   }


void node::open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile
                                         , const ::scoped_string & scopedstrTarget)
{

   open_internet_link_in_browser(scopedstrUrl, {}, scopedstrProfile, scopedstrTarget);

}

   void node::shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const ::file::path& pathWorkingDirectory)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   int node::shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout, const ::file::path& pathWorkingDirectory)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

      return -1;

   }


   void node::root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const ::file::path& pathWorkingDirectory)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

   }


   int node::root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class ::time& timeTimeout, const ::file::path& pathWorkingDirectory)
   {

      //throw ::interface_only();

      //throw ::interface_only();

      throw ::interface_only();

      return -1;

   }


   void node::create_app_shortcut(::platform::application * papp)
   {


   }


   void node::report_exception_to_user(::particle* pparticle, ::exception& exception, const ::string& strMoreDetails)
   {

      send(__initialize_new ::message_box(exception, strMoreDetails));

   }


   //::pointer<::conversation>node::create_new_message_box_conversation()
   //{

   //   system()->do_graphics_and_windowing_system_factory();

   //   return __create_new < ::micro::message_box >();

   //}


   //::pointer < ::subparticle > node::create_message_box_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
   //{

   //   //auto psequencer = __create_new < ::sequencer < ::conversation > >();

   //   auto pmessageboxconversation = create_new_message_box_conversation();

   //   //psequencer->m_psequence = pmessagebox;

   //   //pmessagebox->m_psequencer = psequencer;

   //   pmessageboxconversation->initialize_conversation(strMessage, strTitle, emessagebox, strDetails, picon);

   //   return pmessageboxconversation;

   //}


   //::pointer < ::subparticle > node::create_message_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
   //{

   //   ///auto psequencer = __create_new < ::sequencer < ::conversation > >();

   //   auto pmessageconversation = create_new_message_conversation();

   //   //psequencer->m_psequence = pmessage;

   //   //pmessage->m_psequencer = psequencer;

   //   pmessageconversation->initialize_conversation(strMessage, strTitle, emessagebox, strDetails, picon);

   //   return pmessageconversation;

   //}


   //void node::micro::message_box(::sequence < ::conversation >* psequence, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox)
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

       m_eapplicationcapabilitya.append_unique(ecapabilitya);

       on_change_application_capability();

    }


    void node::on_change_application_capability()
    {


    }


    //void node::windowing_post(const ::procedure& procedure)
    //{


    //}


    string node::get_local_mutex_name(const ::string& strAppId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.formatf("Local\\%s", strApp.c_str());

       return strMutex;

    }


    string node::get_local_id_mutex_name(const ::string& strAppId, const ::string& strId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.formatf("Local\\%s, atom:%s", strApp.c_str(), strId.c_str());

       return strMutex;

    }


    string node::get_global_mutex_name(const ::string& strAppId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.formatf("Global\\%s", strApp.c_str());

       return strMutex;

    }


    string node::get_global_id_mutex_name(const ::string& strAppId, const ::string& strId)
    {

       string strApp(strAppId);

       strApp.find_replace(".", "_");

       strApp.find_replace("-", "_");

       strApp.find_replace("/", "_");

       string strMutex;

       strMutex.formatf("Global\\%s, atom:%s", strApp.c_str(), strId.c_str());

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


   //string node::get_callstack(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
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


   //bool node::succeeded(const ::error_code& errorcode)
   //{

   //   if (errorcode.m_etype == e_error_code_type_errno)
   //   {

   //      return errorcode.m_iOsError == 0;

   //   }
   //   else if (errorcode.m_etype == e_error_code_type_last_error)
   //   {

   //      return errorcode.m_iOsError == 0;

   //   }

   //   throw interface_only();

   //   return false;
   // 
   //}

   //bool node::failed(const ::error_code& errorcode)
   //{

   //   return !succeeded(errorcode);

   //}


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

      if (path.has_character())
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

#ifdef _DEBUG

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


   unsigned long long node::translate_processor_affinity(int i)
   {

      return 0;

   }


   int node::get_current_processor_index()
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




//   int node::command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction)
//   {
//
//      return command_system(scopedstr, tracefunction);
//
//   }

   
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
      
      void run() override { node()->_node_file_dialog(this); }
      
   };


   ::pointer < ::file::file_dialog > node::node_file_dialog()
   {
      
      return __create_new < file_dialog >();
      
   }


   class folder_dialog : virtual public ::file::folder_dialog
   {
   public:
      
      void run() override { node()->_node_folder_dialog(this); }
      
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


   ::string node::default_component_implementation(const ::scoped_string & scopedstrComponentName)
   {

      if(scopedstrComponentName == "nano_archive")
      {

         return "libarchive";

      }
      else if(scopedstrComponentName == "nano_http")
      {

#if defined(FREEBSD)

#if defined(CUBE)

         return "command_line";

#else

         return "libcurl";

#endif

#elif defined(LINUX)
       
         return "libcurl";

#elif defined(WINDOWS_DESKTOP)

         return "wininet";

#endif
         
      }
      else if(scopedstrComponentName == "nano_user")
      {

         ::string strUserToolkit = ::windowing::get_user_toolkit_id();

         return strUserToolkit;

      }
      else if (scopedstrComponentName == "nano_graphics")
      {

#if defined(UNIVERSAL_WINDOWS)
         return "direct2d";
#endif

      }

      return {};

   }


bool node::defer_component_factory(const ::scoped_string & scopedstrComponent)
{

#ifdef WINDOWS_DESKTOP

   if (scopedstrComponent == "nano_http")
   {

      auto pfactory = __allocate::factory::factory();

      nano_http_wininet_factory(pfactory);

      pfactory->merge_to_global_factory();

      return true;

   }
      else if (scopedstrComponent == "nano_compress")
      {

         auto pfactory = __allocate::factory::factory();

         nano_compress_windows_factory(pfactory);

         pfactory->merge_to_global_factory();

         return true;

      }

#endif

   return false;

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

   
   ::string node::get_system_permanent_environment_variable(const ::scoped_string& scopedstr)
   {

      throw ::interface_only();

      return {};

   }


   void node::set_user_permanent_environment_variable(const ::scoped_string& scopedstr, const ::scoped_string& strPayload, bool bNoSystemNotify)
   {

      throw ::interface_only();

   }


   void node::system_notify_environment_variable_change()
   {


   }


   void node::update_process_environment_variables()
   {


   }


#ifdef WINDOWS_DESKTOP


   ::e_status node::_defer_beta_use_unicode_utf8()
   {

      throw ::interface_only();

      return ::success;

   }


   ::e_status node::_defer_enable_coder_mode()
   {

      if (_is_coder_mode_enabled())
      {

         return ::success_already_enabled;

      }

      _enable_coder_mode();

      return ::success;

   }


   bool node::_has_beta_use_unicode_utf8()
   {

      return true;

   }


   bool node::_is_visual_studio_installed()
   {

      return false;

   }


   bool node::_is_tortoise_git_installed()
   {

      return false;

   }


   bool node::_is_msys2_installed()
   {

      return false;

   }


   bool node::_is_strawberry_perl_installed()
   {

      return false;

   }




   bool node::_is_coder_mode_enabled()
   {

      throw interface_only();

      return false;

   }


   void node::_enable_coder_mode(bool bEnable)
   {

      throw interface_only();

   }


#endif

   bool node::_is_code_exe_user_path_environment_variable_ok(::string* pstrCorrectPath, const char * pszPath)
   {

      throw interface_only();

      return false;

   }

#if defined(WINDOWS_DESKTOP) || defined(MACOS) || defined(LINUX)


bool node::_is_smart_git_installed()
{

   return false;

}


#endif


   bool node::_is_google_drive_installed()
   {

      return false;

   }


   //bool node::_is_dropbox_installed()
   //{

   //   if (!m_bDropboxCalculated)
   //   {
   //      
   //      __check_refdbg

   //      calculate_dropbox_installed();

   //      __check_refdbg

   //   }

   //   return m_bDropbox;

   //}


   //void node::calculate_dropbox_installed()
   //{

   //   m_bDropbox = false;

   //   m_pathDropbox.empty();

   //   m_bDropboxCalculated = true;

   //   __check_refdbg

   //   ::file::path pathNetworkPayload = file()->dropbox_info_network_payload();

   //   __check_refdbg

   //   if (!file()->exists(pathNetworkPayload))
   //   {

   //      if (::system()->is_desktop_system())
   //      {

   //         auto pathHome = directory()->home();

   //         auto pathTxt = pathHome / "dropbox.txt";

   //         if (file()->exists(pathTxt))
   //         {

   //            string strPath = file()->safe_get_string(pathTxt);

   //            strPath.trim();

   //            if (strPath.has_character() && directory()->is(strPath))
   //            {

   //               m_pathDropbox = strPath;

   //               m_bDropbox = true;

   //            }

   //         }

   //      }
   //      else
   //      {

   //         m_pathDropbox.empty();

   //      }

   //   }
   //   else
   //   {

   //      __check_refdbg

   //      string strNetworkPayload = file()->as_string(pathNetworkPayload);

   //      __check_refdbg

   //      {

   //         ::property_set set;

   //         __check_refdbg

   //         set.parse_network_payload(strNetworkPayload);

   //         __check_refdbg

   //         m_pathDropbox = set["personal"]["path"];

   //      }

   //      __check_refdbg

   //      if (directory()->is(m_pathDropbox))
   //      {

   //         m_bDropbox = true;

   //      }

   //      __check_refdbg

   //   }

   //   __check_refdbg

   //   m_bDropboxCalculated = true;

   //}


   bool node::_is_onedrive_installed()
   {

      if (!m_bOneDriveCalculated)
      {

         calculate_onedrive_installed();

      }

      return m_bOneDrive;

   }


   void node::calculate_onedrive_installed()
   {


   }


   bool node::_is_google_chrome_installed()
   {

      return false;

   }


   bool node::_is_opera_browser_installed()
   {

      return false;

   }


   bool node::_is_visual_studio_code_installed()
   {

      return false;

   }


   bool node::_is_git_credential_manager_installed()
   {

      return false;

   }


   bool node::_is_shell_patched()
   {

      return _is_code_exe_user_path_environment_variable_ok();

   }


   bool node::_is_jetbrains_clion_installed()
   {

      return false;

   }


   void node::set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string& scopedstrCommand)
   {

      throw ::interface_only();

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
      
      auto papplication = __øcreate < ::operating_system::application >();
      
      papplication->open_by_process_identifier(processidentifier);
      
      return papplication;
      
   }


   ::pointer < ::operating_system::application > node::application_predicate(const ::function < bool(::operating_system::application * papplication) > & function)
   {

      auto processidentifiera = processes_identifiers();

      for (auto & processidentifier : processidentifiera)
      {

         auto papplication = __øcreate < ::operating_system::application >();

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


   void node::play_sound(const ::file::path& path)
   {

      throw interface_only();

   }


//   void node::speak(const ::scoped_string& scopedstr)
//   {
//
//      throw interface_only();
//
//   }


   ::string node::operating_system_application_version()
   {
      
      return "";
      
   }


//   void node::application_handle(long long l, void * p)
//   {
//
//      
//   }


#if defined(__BSD__) || defined(__APPLE__)

   void node::arp_a(void *p, void(*callback)(void * addr, unsigned int uIp, const char * status))
   {
      
      
   }

#endif


#if !defined(ANDROID)

   string node::_get_call_stack_trace(const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
   {
      
      int frame_count = get_call_stack_default_frame_count();

      if(frame_count <= 0)
      {
         
         // essentially disabled;
         
         return {};
         
      }
      
      memory memory;
      
      memory.set_size(frame_count * sizeof(void *));
      
      void ** stack = (void **) memory.data();
      
      get_call_stack_frames(stack, frame_count);
      
      ::string strCallStack = get_call_stack_trace(stack, frame_count, scopedstrFormat, iSkip);
      
      return strCallStack;
   
   }


   string node::_get_call_stack_trace(void ** stack, int frame_count, const ::scoped_string& scopedstrFormat , int iSkip , void* caller_address, int iCount)
   {

      ::string strCallStack = get_call_stack_trace(stack, frame_count, scopedstrFormat, iSkip);

      return strCallStack;

   }

#endif


bool node::is_application_running_good_effort(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp)
{
   
   return are_framework_shared_libraries_busy(scopedstrRepos, scopedstrApp);
   
}


bool node::are_framework_shared_libraries_busy(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp)
{

   string_array stra;

   stra.add(this->library_file_name("acme"));
   stra.add(this->library_file_name("apex"));
   stra.add(this->library_file_name("aqua"));
   stra.add(this->library_file_name("aura"));

   ::file::path_array patha;

   ::file::path pathBin = directory_system()->home() / "application" / scopedstrRepos / scopedstrApp / "binary";

   patha = pathBin / stra;
   
   if(are_any_shared_libraries_mapped(patha))
   {
      
      return true;
      
   }
   

   //auto pathaSystem = this->modules_paths();

   //for (auto & pathSystem : pathaSystem)
   //{
      
      //informationf("pathSystem : %s", pathSystem.c_str());

      //for (auto & path : patha)
      //{

         //if (pathSystem.case_insensitive_contains("SecurityHealthSSO"))
         //{

            //printf_line("SHSSO");

         //}

         //if (path_system()->real_path_is_same(pathSystem, path))
         //{

            //return true;

         //}

      //}

   //}

   return false;

}


bool node::are_any_shared_libraries_mapped(const ::file::path_array & patha)
{

   auto pathaSystem = this->modules_paths();

   for (auto & pathSystem : pathaSystem)
   {
      
      informationf("pathSystem : %s", pathSystem.c_str());

      for (auto & path : patha)
      {

         if (pathSystem.case_insensitive_contains("SecurityHealthSSO"))
         {

            printf_line("SHSSO");

         }

         if (path_system()->real_path_is_same(pathSystem, path))
         {

            return true;

         }

      }

   }

   return false;

}

   ::string node::get_error_code_message(const ::error_code & errorcode)
   {

      if(errorcode.m_etype == e_error_code_type_errno)
      {

         return errno_error_message((int) errorcode.m_iOsError);

      }

      return {};

   }


   bool node::defer_enumerate_protocol(::file::listing& listing)
   {
      
      return false;
      
   }


   bool node::defer_process_protocol_path(::file::path & path)
   {
   
      return false;
      
   }


   void node::destroy()
   {

      ::acme::shell::destroy();

   }


//   string node::get_command_line()
//   {
//
//      throw ::interface_only("this is an interface");
//
//      return "";
//
//   }


   void node::shutdown(bool bIfPowerOff)
   {

      __UNREFERENCED_PARAMETER(bIfPowerOff);

      throw ::interface_only("this is an interface");

      //return false;

   }


//   void node::reboot()
//   {
//
//      throw ::interface_only("this is an interface");
//
//      //return false;
//
//   }


   void node::terminate_processes_by_title(const ::string & lpszName)
   {

      __UNREFERENCED_PARAMETER(lpszName);

      throw ::interface_only("this is an interface");

   }


   ::process_identifier_array node::module_path_processes_identifiers(const ::scoped_string & scopedstrName)
   {

      __UNREFERENCED_PARAMETER(scopedstrName);

      throw ::interface_only("this is an interface");

      return {};

   }


   ::process_identifier_array node::title_processes_identifiers(const ::scoped_string & scopedstrName)
   {

      __UNREFERENCED_PARAMETER(scopedstrName);

      throw ::interface_only("this is an interface");

      return {};

   }


//   ::process_identifier node::current_process_identifier()
//   {
//
//      throw ::interface_only("this is an interface");
//
//      return -1;
//
//   }
//
//
//   ::file::path node::process_identifier_module_path(::process_identifier dwPid)
//   {
//
//      __UNREFERENCED_PARAMETER(dwPid);
//
//      throw ::interface_only("this is an interface");
//
//      return {};
//
//   }
//
//
//   ::process_identifier_array node::processes_identifiers()
//   {
//
//      return node()->processes_identifiers();
//
//   }


//#ifdef WINDOWS
//
//   ::file::path node::get_module_path(HMODULE hmodule)
//   {
//      __UNREFERENCED_PARAMETER(hmodule);
//      throw ::interface_only("this is an interface");
//   }
//
//#endif



   ::payload node::connection_settings_get_auto_detect()
   {

      return success;

   }


   ::payload node::connection_settings_get_auto_config_url()
   {

      return error_failed;

   }

//
//   void node::link_open(const string & strUrl, const string & strProfile)
//   {
//
//      node()->open_url(strUrl);
//
////      file_open(strUrl);
//      //{
//
//      //   return error_failed;
//
//      //}
//
//      //return success;
//
//   }


   void node::local_machine_set_run(const ::string & pszKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pathExecutable);

      //return false;

   }


   void node::local_machine_set_run_once(const ::string & pszKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pathExecutable);

      //return false;

   }


   void node::current_user_set_run(const ::string & pszKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pathExecutable);

      //return false;

   }


   void node::current_user_set_run_once(const ::string & pszKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pathExecutable);

      //return false;

   }


   void node::defer_register_ca2_plugin_for_mozilla()
   {

      //return false;

   }


   void node::file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension)
   {

      __UNREFERENCED_PARAMETER(straKey);
      __UNREFERENCED_PARAMETER(pszExtension);

      //return false;

   }


   void node::file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension)
   {

      __UNREFERENCED_PARAMETER(straCommand);
      __UNREFERENCED_PARAMETER(pszExtension);

      //return false;

   }


   void node::file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::file::path & pathIcon)
   {

      __UNREFERENCED_PARAMETER(pszExtension);
      __UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      __UNREFERENCED_PARAMETER(pathIcon);

      //return false;

   }


   void node::file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::file::path & pathExecutable, const ::string & pszParam)
   {

      __UNREFERENCED_PARAMETER(pszExtension);
      __UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      __UNREFERENCED_PARAMETER(pathExecutable);
      __UNREFERENCED_PARAMETER(pszParam);

      //return false;

   }


   void node::file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      __UNREFERENCED_PARAMETER(pszExtension);
      __UNREFERENCED_PARAMETER(strExtensionNamingClass);
      __UNREFERENCED_PARAMETER(strCommand);
      __UNREFERENCED_PARAMETER(strParam);

      //return false;

   }


   /// Windows (IE), macOS (Safari), Linux (Firefox, oder...)
   /// Remark: it is not default browser (necessarily)
   void node::native_full_web_browser(const ::string & pcsz)

   {

      throw ::not_implemented();

      //return false;

   }

   /// Windows (Edge), fallback to native_full_web_browser
   /// Remark: it is not default browser (necessarily)
   void node::native_modern_web_browser(const ::string & pcsz)

   {

      native_full_web_browser(pcsz);


   }


   void node::enable_service()
   {


      throw ::interface_only();


      //return false;


   }


   void node::disable_service()
   {


      throw ::interface_only();


      //return false;


   }


   void node::start_service()
   {


      throw ::interface_only();


      //return false;


   }


   void node::stop_service()
   {


      throw ::interface_only();


      //return false;


   }


   void node::enable_service(const ::string & strServiceName,const ::string & strDisplayName,const ::string & strCommand,const ::string & strUser,const ::string & strPass)
   {


      throw ::interface_only();


   }


   void node::disable_service(const ::string & strServiceName)
   {


      throw ::interface_only();


   }


   void node::start_service(const ::string & strServiceName)
   {


      throw ::interface_only();


   }


   void node::stop_service(const ::string & strServiceName)
   {


      throw ::interface_only();


   }


//#ifdef WINDOWS
//
//   DECLSPEC_NO_RETURN void node::raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags)
//   {
//
//
//   }
//
//#endif


   bool node::is_remote_session()
   {

      return false;

   }


   void node::set_file_status(const ::file::path & path, const ::file::file_status& status)
   {

      throw ::interface_only();

   }


   //void node::edit_link_target(const ::file::path & path, const ::file::path & pathLink)
   //{

   //   throw ::exception(error_interface_only);

   //}


   //void node::edit_link_folder(const ::file::path & path, const ::file::path & pathLink)
   //{

   //   throw ::exception(error_interface_only);

   //}


   //void node::edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink)
   //{

   //   throw ::exception(error_interface_only);

   //}


//   ::pointer < ::file::link > node::resolve_link(const ::file::path & path, ::file::e_link elink)
//   {
//
//      if(path.case_insensitive_ends(".desktop"))
//      {
//
//         auto stra = file()->lines(path);
//
//         stra.case_insensitive_filter_begins("exec=");
//
//         if(stra.get_size() <= 0)
//         {
//
//            return nullptr;
//
//         }
//
//         auto plink = __create_new < ::file::link >();
//
//         string strLink = stra[0];
//
//         strLink.case_insensitive_begins_eat("exec=");
//
//         while(true)
//         {
//
//            bool bAte = false;
//
//            if(strLink.case_insensitive_ends_eat("%u"))
//            {
//
//               bAte = true;
//
//            }
//
//            if(!bAte)
//            {
//
//               break;
//
//            }
//
//         }
//
//         strLink.trim();
//
//         strLink.trim("\"");
//
//         strLink.trim("\'");
//
//         plink->m_pathFolder = ::file::path(strLink).folder();
//
//         plink->m_pathTarget = strLink;
//
//         return plink;
//
//      }
//      else
//      {
//
//
//#ifndef WINDOWS
//
//
//#if 0
//
//
//
//      if (::is_null(psz))
//      {
//
//         return false;
//
//      }
//
//
//
//
//      char* pszRealPath = ::realpath(psz, NULL);
//
//      if (pszRealPath == NULL)
//      {
//
//         return false;
//
//      }
//
//      if (strcmp(psz, pszRealPath) == 0)
//      {
//
//         ::free(pszRealPath);
//
//         return false;
//
//      }
//
//      try
//      {
//
//         path = pszRealPath;
//
//      }
//      catch (...)
//      {
//
//      }
//
//      ::free(pszRealPath);
//
//      return true;
//
//   }
//
//#else
//
//         auto plink = __create_new < ::file::link >();
//         
//         string strLink;
//
//         char * psz = strLink.get_buffer(4096);
//
//         int count = (int) readlink(path, psz, 4096);
//
//         if (count < 0)
//         {
//
//            strLink.release_buffer(0);
//
//            if (elink & ::file::e_link_target)
//            {
//
//               plink->m_pathTarget = path;
//
//            }
//
//            if(elink & ::file::e_link_folder)
//            {
//
//               plink->m_pathFolder = ::file::path(strLink).folder();
//
//            }
//
//            return plink;
//
//         }
//
//         strLink.release_buffer(count);
//
//         if (elink & ::file::e_link_target)
//         {
//
//            plink->m_pathTarget = path;
//
//         }
//
//         if (elink & ::file::e_link_folder)
//         {
//
//            plink->m_pathFolder = ::file::path(strLink).folder();
//
//         }
//
//         return plink;
//
//#endif
//
//#endif
//
//      }
//
//      return nullptr;
//
//   }


   bool node::has_alias_in_path(const ::scoped_string & scopedstr, bool bNoUI, bool bNoMount)
   {

      ::file::path pathSource(scopedstr);

      ::file::path_array patha;

      ///::file::path_array pathaRelative;

      ascendants_path(pathSource, patha, nullptr);

      for (::collection::index i = 0; i < patha.get_count(); i++)
      {

         ::file::path path = patha[i];

         if (is_alias(path))
         {

            return true;

         }

      }

      return false;

   }


   bool node::is_alias(const ::file::path & path)
   {

      return m_papplication->os_is_alias(path);

   }


   void node::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
   {


   }


   // void node::set_dark_mode(bool bDarkMode)
   // {
   //
   //    throw ::interface_only();
   //
   //    //node()->set_dark_mode(bDarkMode);
   //
   // }


   void node::file_open(const ::file::path & pathTarget, const ::string & strParams, const ::file::path & pathFolder)
   {

      throw ::interface_only();

   }


   void node::hidden_start(const ::file::path& pathTarget, const ::string& strParams, const ::file::path& pathFolder)
   {

      throw ::interface_only();

   }


   void node::hidden_run(const class time & timeWait, const ::file::path& pathTarget, const ::string& strParams, const ::file::path& pathFolder)
   {

      throw ::interface_only();

   }


   string node::get_default_browser()
   {

      string strId;

      ::file::path path;

      string strParam;

      get_default_browser(strId, path, strParam);

      //if (!)
      //{

      //   return "";

      //}

      return strId;

   }


   void node::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      __UNREFERENCED_PARAMETER(strId);
      __UNREFERENCED_PARAMETER(path);
      __UNREFERENCED_PARAMETER(strParam);

      //return false;

   }


   void node::set_default_browser()
   {

      //return false;

   }


   void node::set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype)
   {

   }


   void node::set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType)
   {

      __UNREFERENCED_PARAMETER(straExtension);
      __UNREFERENCED_PARAMETER(straMimeType);

      //return false;

   }


   void node::register_user_auto_start(::platform::application * papplication, const string & strArguments, bool bRegister)
   {

      throw interface_only();

   }


   bool node::is_user_auto_start(const string & strAppId)
   {

      throw interface_only();

      return false;

   }


   ::file::path node::get_app_path(const ::string & strApp)
   {

      return strApp;

   }


   void node::on_process_request(::request * prequest)
   {

      request(prequest);

   }


   //void node::browse_file_open(::property_set & set)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //void node::browse_file_save(::property_set & set)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   //void node::browse_folder(::property_set & set)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}

   //
   //void node::browse_file_or_folder(::property_set & set)
   //{

   //   throw ::interface_only();

   //   //return false;

   //}


   void node::list_process(::file::path_array& patha, ::process_identifier_array& uaPid)
   {

      ASSERT(sizeof(unsigned int) == sizeof(unsigned int));

      uaPid = this->processes_identifiers();

      patha.set_size(uaPid.get_count());

      for (::collection::index i = 0; i < uaPid.get_count(); i++)
      {

         patha[i] = process_identifier_module_path(uaPid[i]);

      }

   }


   ::file::path_array node::list_process_path()
   {

      ::file::path_array patha;

      ::process_identifier_array uaPid;

      list_process(patha, uaPid);

      return patha;

   }


   void node::broadcast_environment_variable_change()
   {

      //return ::success_none;

   }


   void node::set_this_application_as_default_for_file_extension(const ::string& strExtension)
   {


   }


   string node::get_file_extension_mime_type(const ::string & strExtension)
   {

      if (strExtension == "iso")
      {
         return "application/octetstream";
      }
      else if (strExtension == "mp3")
      {
         return "audio/mpeg";
      }
      else if (strExtension == "exe")
      {
         return "application/x-msdownload";
      }
      else if (strExtension == "spa")
      {
         return "application/x-spa";
      }
      else if (strExtension == "mid")
      {
         return "audio/midi";
      }
      else if (strExtension == "js")
      {
         return "text/javascript";
      }
      else if (strExtension == "css")
      {
         return "text/css";
      }
      else if (strExtension == "xpi")
      {
         return "application/x-xpinstall";
      }
      else if (strExtension == "ttf")
      {
         return "font/ttf";
      }
      else if (strExtension == "ogv")
      {
         return "video/ogg";
      }
      else if (strExtension == "mp4")
      {
         return "video/mp4";
      }
      else if (strExtension == "webm")
      {
         return "video/webm";
      }
      else if (strExtension == "zip")
      {
         return "application/x-zip-compressed";
      }
      else if (strExtension == "crx")
      {
         return "application/x-chrome-extension";
      }
      else if (strExtension == "swf")
      {
         return "application/x-shockwave-flash";
      }
      else if (strExtension == "cab")
      {
         return "application/vnd.ms-cab-compressed";
      }
      else if (strExtension == "jar")
      {
         return "application/x-jar";
      }
      else if (strExtension == "jpg")
      {
         return "image/jpeg";
      }
      else if (strExtension == "webp")
      {
         return "image/webp";
      }
      else if (strExtension == "png")
      {
         return "image/png";
      }
      else if (strExtension == "gif")
      {
         return "image/gif";
      }
      else if (strExtension == "svg")
      {
         return "image/svg+xml";
      }
      else if (strExtension == "ttf")
      {
         return "application/x-font-ttf";
      }
      else if (strExtension == "otf")
      {
         return "application/x-font-opentype";
      }
      else if (strExtension == "woff")
      {
         return "application/x-font-woff";
      }
      else if (strExtension == "eot")
      {
         return "application/vnd.ms-fontobject";
      }
      else if (strExtension == "md5")
      {
         return "text/plain";
      }
      else if (strExtension == "html")
      {
         return "text/html";
      }
      else if (strExtension == "htm")
      {
         return "text/html";
      }
      else if (strExtension == "rdf")
      {
         return "application/rdf+xml";
      }
      else if (strExtension == "raw")
      {
         return "application/x-cd-image;application/x-raw-disk-image;";
      }
      else
      {
         return "";
      }

   }

   
   ::string node::eol()
   {

      return "\n";

   }



   
   int node::building_core_count(bool bDedicatedBuilder)
   {

      if (bDedicatedBuilder)
      {

         return performance_core_count();

      }
      else
      {

         return minimum_maximum(
            1, 
            performance_core_count() - 1,
            performance_core_count() * 3 / 4);

      }

   }


   int node::performance_core_count()
   {

      return ::get_processor_count();

   }


   int node::efficiency_core_count()
   {

      return 0;

   }


   void node::detached_command(const ::scoped_string & scopedstrCommand, const ::file::path & pathLog)
   {



   }


//   void * node::fetch_windowing_system_display()
//   {
//
//      return nullptr;
//
//   }
//
//
//   void node::windowing_system_async(const ::procedure &procedure)
//   {
//
//
//   }
//
//
//   void node::windowing_system_display_error_trap_push(int i)
//   {
//
//
//   }
//
//
//   void node::windowing_system_display_error_trap_pop_ignored(int i)
//   {
//
//
//   }


  /* enum_windowing node::calculate_ewindowing()
   {

      return e_windowing_none;

   }*/


   bool node::_get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle)
   {

      return false;

   }


   bool node::_get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle)
   {

      return false;

   }


   void node::realize(::particle_pointer pparticle)
   {


   }


   ::string node::dynamic_library_prefix()
   {

      return {};

   }


   ::string node::dynamic_library_suffix()
   {

      throw interface_only();

      return {};

   }


   ::file::path node::get_font_path_from_name(const ::scoped_string& scopedstrName)
   {

      auto p = m_mapFont.plookup(scopedstrName);

      if (!p)
      {

         m_mapFont[scopedstrName].m_path = _get_font_path_from_name(scopedstrName);

         p = m_mapFont.plookup(scopedstrName);

      }

      if (!p)
      {
      
         return {};

      }

      return p->m_element2.m_path;

   }


   ::file::path node::_get_font_path_from_name(const ::scoped_string& scopedstrName)
   {

      return {};

   }

} // namespace platform


void node_application_send_status(const char * pszStatus, void * p, long long hi)
{
   
   system()->node()->node_application_on_status(pszStatus, p, hi);
   
}



