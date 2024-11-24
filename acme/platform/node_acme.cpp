//
// Created by camilo on 2024-10-24 00:35 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "node_acme.h"
#include "acme/constant/id.h"


namespace platform
{


   ::string acme_node_layer::get_file_type_identifier(const ::file::path& path)
   {

      return {};

   }


   void acme_node_layer::call_async(const ::string& pszPath, const ::string& pszParam, const ::string& pszDir,
                                    ::e_display edisplay, bool bPrivileged, unsigned int* puiPid)
   {
   }


   void acme_node_layer::call_sync(const ::string& pszPath, const ::string& pszParam, const ::string& pszDir,
                                   ::e_display edisplay, const class time& timeTimeout, ::property_set& set,
                                   int* piExitCode)
   {
   }


   ::process_identifier_array acme_node_layer::module_list_file_processes_identifiers(const ::scoped_string& scopedstr)
   {

      return{};
   }


   ::enum_id acme_node_layer::key_command(::user::enum_key ekey, ::user::key_state* pkeystate)
   {
      return id_none;
   }


   //idaPid = pnode->(path, false){}



   particle_pointer acme_node_layer::create_mutex()
   {
      return{};
   }


   void acme_node_layer::initialize(::particle* pparticle)
   {
   }


   void acme_node_layer::node_application_on_status(const char* pszStatus, void* p, huge_integer hi)
   {
   }


   //virtual ::particle_pointer create_quit_particle(::pointer<::platform::node>& pnode){}

   //virtual ::particle_pointer create_quit_particle(){}
   ::file::path acme_node_layer::get_default_base_integration_folder()
   {
      return{};
   }


   ///void acme_node_layer::implement(::pointer<::platform::node>& pnode, ::pointer<::platform::system> & psystem){}

   void acme_node_layer::node_main()
   {
   }


   void acme_node_layer::node_implement_main()
   {
   }


   void acme_node_layer::on_app_activated()
   {
   }


   void acme_node_layer::on_system_main()
   {
   }


   void acme_node_layer::start_application(::pointer<::platform::node>& pnode)
   {
   }


   // void acme_node_layer::acme_application_main(::platform::system* psystem)
   // {
   // }


   void acme_node_layer::_will_finish_launching()
   {
   }


   //void acme_node_layer::element_quit_post_quit(){}


   ::string acme_node_layer::audio_get_default_implementation_name()
   {
      return{};
   }


   ::string acme_node_layer::multimedia_audio_get_default_implementation_name()
   {return{};
   }


   ::string acme_node_layer::multimedia_audio_mixer_get_default_implementation_name()
   {return{};
   }


   ::string acme_node_layer::veriwell_multimedia_music_midi_get_default_implementation_name()
   {return{};
   }


   void acme_node_layer::_launch_macos_app(const ::string& pszAppFolder)
   {
   }


   void acme_node_layer::_launch_macos_app_args(const ::string& pszAppFolder, const ::string& pszArgs)
   {
   }


   //void on_initialize_particle() override{}

   void acme_node_layer::initialize_memory_counter()
   {
   }


   void acme_node_layer::system_main()
   {
   }


   void acme_node_layer::reboot()
   {
   }


   void acme_node_layer::defer_show_system_menu(::user::mouse* pmouse)
   {
   }


   void acme_node_layer::install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension)
   {
   }


   ::file::path acme_node_layer::module_path_source()
   {
      return{};

   }


   //::file::path acme_node_layer::module_path_seed(){}
   //::file::path acme_node_layer::module_path_origin(){}
   //::file::path update_module_path(){}


   ::pointer<::mutex> acme_node_layer::create_local_named_mutex(::particle* pparticleContext, bool bInitiallyOwned,
                                                                const ::string& strName,
                                                                security_attributes* psecurityattributes)
   {
      return{};

   }


   ::pointer<::mutex> acme_node_layer::create_global_named_mutex(::particle* pparticleContext, bool bInitiallyOwned,
                                                                 const ::string& strName,
                                                                 security_attributes* psecurityattributes)
   {
      return{};

   }


   ::pointer<::mutex> acme_node_layer::open_local_named_mutex(::particle* pparticleContext, const ::string& strName)
   {
      return{};

   }


   ::pointer<::mutex> acme_node_layer::open_global_named_mutex(::particle* pparticleContext, const ::string& strName)
   {
      return{};

   }


   ::pointer<::mutex> acme_node_layer::get_install_mutex(::particle* pparticleContext, const ::string& strPlatform,
                                                         const ::string& strSuffix)
   {
      return{};

   }


   ::pointer<::acme::exclusive> acme_node_layer::_get_exclusive(::particle* pparticleContext, const ::string& strName,
                                                                ::security_attributes* psecurityattributes)
   {
      return{};

   }


   ::pointer<::acme::exclusive> acme_node_layer::get_exclusive(::particle* pparticleContext, const ::string& strName,
                                                               ::security_attributes* psecurityattributes)
   {
      return{};

   }


   bool acme_node_layer::erase_exclusive(const string& strName)
   {
      return false;
   }


   void acme_node_layer::release_exclusive()
   {
   }


   bool acme_node_layer::exclusive_fails(::particle* pparticleContext, const string& strName,
                                         security_attributes* psecurityattributes)
   {
      return false;
   }


   ::string acme_node_layer::app_id_to_app_name(const ::string& strAppId)
   {
      return{};
   }


   ::string acme_node_layer::app_id_to_executable_name(const ::string& strAppId)
   {
      return{};
   }


   bool acme_node_layer::is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild,
                                                  const ::string& pszPlatform, const ::string& pszConfiguration,
                                                  const ::string& pszLocale, const ::string& pszSchema)
   {
      return false;
   }


   void acme_node_layer::set_application_installed(const ::file::path& pathExe, string strAppId,
                                                   const ::string& pszBuild,
                                                   const ::string& pszPlatform, const ::string& pszConfiguration,
                                                   const ::string& pszLocale, const ::string& pszSchema)
   {
   }


   ::file::path acme_node_layer::application_installer_folder(const ::file::path& pathExe, string strAppId,
                                                              const ::string& pszPlatform,
                                                              const ::string& pszConfiguration,
                                                              const ::string& pszLocale, const ::string& pszSchema)
   {
      return{};

   }


   ::file::path acme_node_layer::get_application_path(string strAppId, const ::string& pszPlatform,
                                                      const ::string& pszConfiguration)
   {
      return{};

   }


   ::file::path acme_node_layer::get_last_run_application_path_file(const ::string& strAppId)
   {
      return{};

   }


   ::file::path acme_node_layer::get_last_run_application_path(const ::string& strAppId)
   {
      return{};

   }


   void acme_node_layer::set_last_run_application_path(const string& strAppId)
   {
   }


   ::file::path acme_node_layer::_module_path()
   {
      return{};

   }


   //void acme_node_layer::do_windowing_system_factory(){}


   //bool acme_node_layer::memory_counter_on(){}

   //::file::path acme_node_layer::memory_counter_base_path(){}

   void acme_node_layer::datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time)
   {
   }


   int acme_node_layer::node_init_check(int* pi, char*** ppz)
   {
      return 0;
   }


   void acme_node_layer::start_node()
   {
   }


   void acme_node_layer::install_sigchld_handler()
   {
   }


   // virtual ::color::color get_system_color(enum_system_color esystemcolor){}
   //
   // //bool acme_node_layer::dark_mode() const{}
   //
   // virtual ::os_theme_colors * _new_os_theme_colors(){}
   //
   // virtual ::os_theme_colors * _get_os_theme_colors(){}
   //
   // void acme_node_layer::_fill_os_theme_colors(::os_theme_colors * pthemecolors){}
   //
   // void acme_node_layer::_set_os_theme_colors(::os_theme_colors * pthemecolors){}
   //
   // void acme_node_layer::_del_os_theme_colors(::os_theme_colors * pthemecolors){}
   //
   // void acme_node_layer::_term_os_theme_colors(){}

   //      int acme_node_layer::get_simple_ui_darkness(){}

   //      void acme_node_layer::set_simple_ui_darkness(int iWeatherDarkness){}

   //void acme_node_layer::set_dark_mode(bool bDark){}

   // void acme_node_layer::fetch_user_color(){}
   //
   // void acme_node_layer::_fetch_user_color(){}

   //void acme_node_layer::on_operating_system_user_theme_change(){}

   //void acme_node_layer::on_operating_system_user_color_change(){}

   //void acme_node_layer::on_operating_system_font_list_change(){}

   //::string acme_node_layer::os_get_user_theme(){}

   //void acme_node_layer::os_set_user_theme(const ::string & strUserTheme){}

   //void acme_node_layer::os_process_user_theme(string strTheme){}

   //void acme_node_layer::os_process_user_icon_theme(string strIconTheme){}

   bool acme_node_layer::set_wallpaper(::collection::index iScreen, string strLocalImagePath,
                                       ::windowing::display* pwindowingdisplay)
   {
      return false;
   }


   ::string acme_node_layer::get_wallpaper(::collection::index iScreen, ::windowing::display* pwindowingdisplay)
   {
      return{};
   }


   ::string acme_node_layer::get_file_icon_path(const ::string& pszPath, int iSize)
   {
      return{};
   }


   ::string acme_node_layer::get_file_content_type(const ::string& pszPath)
   {
      return{};
   }


   int acme_node_layer::os_launch_uri(const ::string& pszUri, char* pszError, int iBufferSize)
   {
      return 0;
   }


   void acme_node_layer::enable_wallpaper_change_notification()
   {
   }


   bool acme_node_layer::has_xcb()
   {
      return false;
   }


   void*  acme_node_layer::get_os_xcb_connection()
   {
      return nullptr;
   }


   bool acme_node_layer::is_wayland()
   {
      return false;
   }


   //void _user_send(const ::procedure & procedure) override{}
   //void _user_post(const ::procedure & procedure) override{}

   //void acme_node_layer::_user_send(::subparticle * psubparticle) override{}
   //void acme_node_layer::_user_post(::subparticle * psubparticle) override{}

   //void post_procedure(const ::procedure & procedure) override{}

   //void send_procedure(const ::procedure & procedure) override{}

   void acme_node_layer::defer_do_main_tasks()
   {
   }


   void acme_node_layer::user_post_quit()
   {
   }


   //void acme_node_layer::node_quit(){}

   bool acme_node_layer::should_launch_on_node(::topic* ptopic)
   {
      return false;
   }


   bool acme_node_layer::defer_launch_on_node(::topic* ptopic)
   {
      return false;
   }


   bool acme_node_layer::launch_on_node(::topic* ptopic)
   {
      return false;
   }


   ::string acme_node_layer::get_user_name()
   {
   return{};
   }


   void acme_node_layer::set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha)
   {
   }


   void acme_node_layer::browse_for_folder(::file::path& pathFolder)
   {
   }


   void acme_node_layer::browse_for_file(::file::path& path)
   {
   }


   double acme_node_layer::get_time_zone()
   {
      return 0.;
   }


   ::string acme_node_layer::font_name(enum_font efont)
   {
      return{};
   }


   //::string acme_node_layer::font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont){}


   ::string acme_node_layer::file_memory_map_path_from_name(const string& strName)
   {
      return{};
   }


   enum_operating_system acme_node_layer::get_operating_system() const
   {
      return e_operating_system_none;
   }


   //virtual ::user::enum_operating_ambient get_eoperating_ambient(){}
   //virtual ::user::enum_toolkit get_etoolkit(){}

   //virtual ::user::enum_operating_ambient calculate_edesktop(){}
   //virtual ::user::enum_toolkit calculate_etoolkit(){}

   //::string acme_node_layer::get_user_toolkit_id(){}

   void acme_node_layer::launch_app(const ::string& psz, const char** argv, int iFlags)
   {
   }


   ::file::path acme_node_layer::get_executable_path_by_app_id(const ::scoped_string& scopedstrAppId,
                                                               bool bSingleExecutableVersion)
   {
      return{};
   }


   ::file::path acme_node_layer::get_executable_path_by_app_id(const ::scoped_string& scopedstrRepos,
                                                               const ::scoped_string& scopedstrApp,
                                                               bool bSingleExecutableVersion)
   {
      return{};

   }


   void acme_node_layer::launch_app_by_app_id(const ::scoped_string& scopedstrAppId, bool bSingleExecutableVersion)
   {
   }


   ::process_identifier acme_node_layer::create_process(const ::string& pszCommandLine)
   {
      return -1;
   }


   void acme_node_layer::run_silent(const ::string& strFunct, const ::string& strstrParams)
   {
   }


   ::file::path_array acme_node_layer::process_identifier_modules_paths(::process_identifier processidentifier)
   {
      return {};
   }


   ::file::path_array acme_node_layer::modules_paths()
   {
      return {};
   }


   bool acme_node_layer::load_modules_diff(string_array& straOld, string_array& straNew, const ::string& pszExceptDir)
   {
      return false;
   }


   ::process_identifier_array acme_node_layer::processes_identifiers()
   {
      return {};
   }


   ::process_identifier_array acme_node_layer::module_path_processes_identifiers(
      const ::string& pszModulePath, bool bModuleNameIsPropertyFormatted)
   {
      return {};
   }


   ::file::path acme_node_layer::process_identifier_module_path(::process_identifier processidentifier)
   {
      return{};

   }


   ::string acme_node_layer::process_identifier_command_line(::process_identifier processidentifier)
   {
      return{};

   }


   //bool acme_node_layer::is_shared_library_busy(::process_identifier processidentifier, const string_array& stra){}

   //bool acme_node_layer::is_shared_library_busy(const string_array& stra){}

   bool acme_node_layer::process_contains_module(string& strImage, ::process_identifier processidentifier,
                                                 const ::string& pszLibrary)
   {
   return false;
   }


   ::process_identifier_array acme_node_layer::
   shared_library_process(string_array& straProcesses, const ::string& pszLibrary)
   {
      return{};
   }


   bool acme_node_layer::is_process_running(::process_identifier processidentifier)
   {
      return false;
   }


   ::string acme_node_layer::get_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable)
   {
      return{};
   }


   ::string acme_node_layer::expand_environment_variables(const ::scoped_string& scopedstr)
   {
      return{};
   }


   void acme_node_layer::set_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable,
                                                  const ::scoped_string& scopedstrValue)
   {
   }


   void acme_node_layer::unset_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable)
   {
   }


   ::string acme_node_layer::get_user_language()
   {
      return {};
   }


   ::pointer<security_attributes> acme_node_layer::get_application_exclusivity_security_attributes()
   {
      return{};
   }


   void acme_node_layer::register_spa_file_type(const ::string& strAppIdHandler)
   {
   }


   bool acme_node_layer::low_is_app_app_admin_running(string strPlatform, string strConfiguration)
   {
      return false;
   }


   void acme_node_layer::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {
   }


   void acme_node_layer::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {
   }


   void acme_node_layer::get_folder_path_from_user(::file::path& pathFolder)
   {
   }


   //::string acme_node_layer::expand_environment_variables(const ::string & str){}

   ::file::path acme_node_layer::command_find_path(const ::string& pszCommand)
   {
      return{};
   }


   void acme_node_layer::launch_application(::particle* pparticle, const ::string& strAppId, const ::string& strParams,
                                            int iBitCount)
   {
   }


   void acme_node_layer::shell_open(const ::file::path& path, const string& strParams ,
                                    const ::file::path& pathFolder)
   {
   }


   //void acme_node_layer::open_url(const ::string & strUrl){}


   void acme_node_layer::shell_execute_async(const ::scoped_string& scopedstrFile,
                                             const ::scoped_string& scopedstrParams,
                                             const ::file::path& pathWorkingDirectory)
   {
   }


   int acme_node_layer::shell_execute_sync(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams,
                                           const class time& timeTimeout,
                                           const ::file::path& pathWorkingDirectory)
   {
      return 0;
   }


   void acme_node_layer::root_execute_async(const ::scoped_string& scopedstrFile,
                                            const ::scoped_string& scopedstrParams,
                                            const ::file::path& pathWorkingDirectory)
   {
   }


   int acme_node_layer::root_execute_sync(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams,
                                          const class time& timeTimeout,
                                          const ::file::path& pathWorkingDirectory)
   {
      return 0;
   }


   //::file::path command_find_path(const ::string & pszCommand){}


   //virtual ::user::enum_operating_ambient calculate_edesktop(){}
   //
   //
   //virtual ::user::enum_operating_ambient get_eoperating_ambient(){}

   void acme_node_layer::on_start_system()
   {
   }


   void acme_node_layer::create_app_shortcut(::platform::application* papplication)
   {
   }


   void acme_node_layer::report_exception_to_user(::particle* pparticle, ::exception& exception,
                                                  const ::string& strMoreDetails)
   {
   }


   //virtual ::pointer<::conversation> create_new_message_box_conversation(){}

   //virtual ::pointer<::conversation> create_new_message_conversation(){}


   //virtual ::pointer < ::subparticle > create_message_box_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon){}


   //void acme_node_layer::::micro::message_box(::sequence < ::conversation > * psequence, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox){}

   //virtual ::pointer < ::subparticle > create_message_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon){}


   void acme_node_layer::shell_launch(const ::string& strAppId)
   {
   }


   bool acme_node_layer::has_application_capability(::enum_application_capability ecapability) const
   {
      return false;
   }


   void acme_node_layer::add_application_capability(const ::enum_application_capability_array& ecapabilitya)
   {
   }


   void acme_node_layer::on_change_application_capability()
   {
   }


   //void acme_node_layer::windowing_post(const ::procedure& procedure){}


   ::string acme_node_layer::get_local_mutex_name(const ::string& strAppId)
   {
      return{};
   }


   ::string acme_node_layer::get_local_id_mutex_name(const ::string& strAppId, const ::string& strId)
   {
      return{};
   }


   ::string acme_node_layer::get_global_mutex_name(const ::string& strAppId)
   {
      return{};
   }


   ::string acme_node_layer::get_global_id_mutex_name(const ::string& strAppId, const ::string& strId)
   {
      return{};
   }


   //      ::string acme_node_layer::get_call_stack(){}


   ::process_identifier acme_node_layer::current_process_identifier()
   {
      return 0;
   }


   bool acme_node_layer::stdin_has_input_events()
   {
      return false;
   }


   void acme_node_layer::flush_stdin_input_events()
   {
   }


   void acme_node_layer::flush_stdin()
   {
   }


   void acme_node_layer::defer_update_call_stack()
   {
   }


   //#if defined(ANDROID)
   //      ::string acme_node_layer::unwind_call_stack(const ::scoped_string & scopedstrFormat , int iSkip, int iCount){}
   //#else
   int acme_node_layer::get_call_stack_default_frame_count()
   {
      return 0;
   }


   void acme_node_layer::get_call_stack_frames(void** stack, int& frame_count)
   {
   }


   ::string acme_node_layer::get_call_stack_trace(const ::scoped_string& scopedstrFormat ,
                                                  int iSkip,
                                                  void* caller_address,
                                                  int iCount)
   {
      return{};
   }


   ::string acme_node_layer::get_call_stack_trace(void** stack, int frame_count,
                                                  const ::scoped_string& scopedstrFormat ,
                                                  int iSkip,
                                                  void* caller_address,
                                                  int iCount)
   {
      return{};
   }


   //#endif
   ::string acme_node_layer::_get_call_stack_trace(const ::scoped_string& scopedstrFormat ,
                                                   int iSkip,
                                                   void* caller_address,
                                                   int iCount)
   {
      return{};
   }


   ::string  acme_node_layer::get_command_line()
   {
      return{};
   }


   //virtual ::pointer<::acme::exclusive> get_exclusive(string str, const security_attributes & securityattributes){}


   int  acme_node_layer::get_current_processor_index()
   {
      return 0;
   }


   int  acme_node_layer::get_current_process_maximum_affinity()
   {
      return 0;
   }


   int acme_node_layer::get_current_process_affinity_order()
   {
      return 0;
   }


   huge_natural  acme_node_layer::translate_processor_affinity(int i)
   {
      return   0;
   }


   //CLASS_DECL_ACME string expand_env(string str){}
   //CLASS_DECL_ACME string xxxget_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable){}
   //CLASS_DECL_ACME string ca2_command_line(){}


   //int acme_node_layer::process_get_status(){}
   //void acme_node_layer::process_set_status(int iStatus){}
   //int acme_node_layer::* process_get_pargc(){}
   //int acme_node_layer::process_get_argc(){}


   bool acme_node_layer::set_process_priority(::enum_priority epriority)
   {
      return false;
   }


   //::string acme_node_layer::time_binary_platform(string strPlatform){}


   //
   //#if !defined(UNIVERSAL_WINDOWS)
   //
   //      //virtual int call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid){}
   //
   //      typedef int CALLSYNCONRETRY(int iTry, uptr dwParam){}
   //
   //      typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY{}
   //
   //      //CLASS_DECL_ACME unsigned int call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set){}
   //
   //#endif


   //#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
   //
   //
   //      //virtual int get_current_processor_index(){}
   //
   //      //virtual int get_current_process_maximum_affinity(){}
   //
   //      //virtual int get_current_process_affinity_order(){}
   //
   //
   //#endif


   //::string acme_node_layer::expand_env(string str){}

   //CLASS_DECL_ACME string consume_command_line_parameter(const ::string & pszCommandLine, const ::string * & pszEndPtr){}
   //CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::string & pszCommandLine, const ::string & pszParam, bool bDefault){}
   //CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam){}
   //CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam, const ::string & pszDefault){}
   //CLASS_DECL_ACME string get_command_line_parameter(const ::string & pszCommandLine, const ::string & pszParam){}


   //bool acme_node_layer::launch_command(const ::string & pszCommand){}


   ::string acme_node_layer::process_configuration_name()
   {
      return{};
   }


   ::string acme_node_layer::time_binary_platform(const string& strPlatform)
   {
      return{};
   }


   ::string acme_node_layer::process_platform_name()
   {
      return{};
   }


   //::string acme_node_layer::process_platform_name(){}
   ::string acme_node_layer::process_version_dir_name()
{
      return{};

   }


   ::file::path acme_node_layer::core_app_path(string strApp)
   {
      return{};
   }


   //bool acme_node_layer::is_shared_library_busy(::process_identifier processidentifier, const string_array & stra){}
   //bool acme_node_layer::is_shared_library_busy(const string_array & stra){}


   // bool acme_node_layer::launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount){}


   //bool acme_node_layer::shell_execute_async(const ::string & pszFile, const ::string & pszParams){}
   //bool acme_node_layer::shell_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout){}

   //bool acme_node_layer::root_execute_async(const ::string & pszFile, const ::string & pszParams){}
   //bool acme_node_layer::root_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout){}


   //CLASS_DECL_ACME bool os_init_application(){}
   //CLASS_DECL_ACME void os_term_application(){}


   ::string acme_node_layer::executable_title_from_appid(const string& strAppId)
   {
      return{};
   }


   //CLASS_DECL_ACME unsigned int get_current_process_id(){}


   //::string acme_node_layer::process_version_dir_name(){}


   int acme_node_layer::is_debug_build()
   {
      return 0;
   }


   int acme_node_layer::is_release_build()
   {
      return 0;
   }


   //bool acme_node_layer::succeeded(const ::error_code& errorcode){}
   //bool acme_node_layer::failed(const ::error_code& errorcode){}


   void acme_node_layer::_node_file_dialog(::file::file_dialog* pdialog)
   {
   }


   void acme_node_layer::_node_folder_dialog(::file::folder_dialog* pdialog)
   {
   }


   ::pointer<::file::file_dialog> acme_node_layer:: node_file_dialog()
   {
      return{};
   }


   ::pointer<::file::folder_dialog> acme_node_layer:: node_folder_dialog()
   {
      return{};
   }


   ::file::path acme_node_layer::library_file_name(const ::scoped_string& scopedstr)
   {
      return{};
   }


   ::string  acme_node_layer::default_component_implementation(const ::scoped_string& scopedstrComponentName)
   {
      return{};
   }


   void acme_node_layer::integration_factory()
   {
   }


   //void acme_node_layer::unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip){}


    ::string acme_node_layer:: get_user_permanent_environment_variable(const ::scoped_string& scopedstr)
   {
      return{};
   }


    ::string  acme_node_layer::get_system_permanent_environment_variable(const ::scoped_string& scopedstr)
   {
      return{};
   }


   void acme_node_layer::set_user_permanent_environment_variable(const ::scoped_string& scopedstr,
                                                                 const ::scoped_string& strPayload,
                                                                 bool bNoSystemNotify)
   {
   }


   void acme_node_layer::system_notify_environment_variable_change()
   {
   }


   void acme_node_layer::update_process_environment_variables()
   {
   }


   void acme_node_layer::set_user_run_once(const ::scoped_string& scopedstrLabel,
                                           const ::scoped_string& scopedstrCommand)
   {
   }


    ::string  acme_node_layer::operating_system_store_release()
   {
      return{};
   }


   ::pointer<::operating_system::summary> acme_node_layer:: operating_system_summary()
   {
      return{};
   }


   //void acme_node_layer::module_path_main_window_post_close(const ::scoped_string & scopestr){}


   ::pointer<::operating_system::application> acme_node_layer:: module_path_application(const ::scoped_string& scopestr)
   {
      return{};
   }


   ::pointer<::operating_system::application>  acme_node_layer::process_identifier_application(
      ::process_identifier processidentifier)
   {
      return{};
   }


    ::pointer<::operating_system::application> acme_node_layer:: application_predicate(
      const ::function<bool(::operating_system::application* papplication)>& function)
   {
      return{};
   }


    ::string  acme_node_layer::get_character_set_default_sample_text(enum_character_set echaracterset)
   {
      return{};
   }


   void acme_node_layer::load_character_set_default_sample_text()
   {
   }


   void acme_node_layer::play_sound(const ::file::path& path)
   {
   }


   //void acme_node_layer::speak(const ::scoped_string& scopedstr){}

   ::string acme_node_layer::operating_system_application_version()
   {
      return{};
   }


//   void acme_node_layer::application_handle(huge_integer l, void* p)
//   {
//   }


   bool acme_node_layer::is_application_running_good_effort(const ::scoped_string& scopedstrRepos,
                                                            const ::scoped_string& scopedstrApp)
   {
      return false;
   }


   bool acme_node_layer::are_framework_shared_libraries_busy(const ::scoped_string& scopedstrRepos,
                                                             const ::scoped_string& scopedstrApp)
   {
      return false;
   }


   ::string acme_node_layer::get_error_code_message(const ::error_code& errorcode)
   {
      return{};
   }


   bool acme_node_layer::defer_enumerate_protocol(::file::listing& listing)
   {
      return false;
   }


   bool acme_node_layer::defer_process_protocol_path(::file::path& path)
   {
      return false;
   }


   //void finalize() override{}

   //::string acme_node_layer::get_command_line(){}

   //void acme_node_layer::reboot(){}
   void acme_node_layer::shutdown(bool bPowerOff)
   {
   }


   void acme_node_layer::terminate_processes_by_title(const ::string& strName)
   {
   }


   //#ifdef WINDOWS
   //      ::file::path acme_node_layer::get_module_path(HMODULE hmodule){}
   //#endif

   ::process_identifier_array  acme_node_layer::module_path_processes_identifiers(const ::scoped_string& scopedstrName)
   {
      return{};
   }


   ::process_identifier_array  acme_node_layer::title_processes_identifiers(const ::scoped_string& scopedstrName)
   {
      return{};
   }


   //virtual ::process_identifier_array processes_identifiers(){}
   //::file::path acme_node_layer::process_identifier_module_path(::process_identifier dwPid){}


   //virtual ::process_identifier current_process_identifier(){}

   ::payload  acme_node_layer::connection_settings_get_auto_detect()
   {
      return{};
   }


   ::payload  acme_node_layer::connection_settings_get_auto_config_url()
   {
      return{};
   }


   void acme_node_layer::open_url_link_at_system_browser(const string& strUrl, const string& strProfile)
   {
   }


   void acme_node_layer::local_machine_set_run(const ::string& strKey, const ::file::path& pathExecutable,
                                               const ::string& strArguments, bool bSet)
   {
   }


   void acme_node_layer::local_machine_set_run_once(const ::string& strKey, const ::file::path& pathExecutable,
                                                    const ::string& strArguments, bool bSet)
   {
   }


   void acme_node_layer::current_user_set_run(const ::string& strKey, const ::file::path& pathExecutable,
                                              const ::string& strArguments, bool bSet)
   {
   }


   void acme_node_layer::current_user_set_run_once(const ::string& strKey, const ::file::path& pathExecutable,
                                                   const ::string& strArguments, bool bSet)
   {
   }


   void acme_node_layer::defer_register_ca2_plugin_for_mozilla()
   {
   }


   void acme_node_layer::file_extension_get_open_with_list_keys(string_array& straKey, const ::string& strExtension)
   {
   }


   void acme_node_layer::file_extension_get_open_with_list_commands(string_array& straCommand,
                                                                    const ::string& strExtension)
   {
   }


   void acme_node_layer::file_association_set_default_icon(const ::string& strExtension,
                                                           const ::string& strExtensionNamingClass,
                                                           const ::string& strIconPath)
   {
   }


   void acme_node_layer::file_association_set_shell_open_command(const ::string& strExtension,
                                                                 const ::string& strExtensionNamingClass,
                                                                 const ::string& strCommand, const ::string& strParam)
   {
   }


   void acme_node_layer::file_association_get_shell_open_command(const ::string& strExtension,
                                                                 string& strExtensionNamingClass, string& strCommand,
                                                                 string& strParam)
   {
   }


   void acme_node_layer::native_full_web_browser(const ::string& str)
   {
   }


   void acme_node_layer::native_modern_web_browser(const ::string& str)
   {
   }


   void acme_node_layer::enable_service()
   {
   }


   void acme_node_layer::disable_service()
   {
   }


   void acme_node_layer::start_service()
   {
   }


   void acme_node_layer::stop_service()
   {
   }


   void acme_node_layer::enable_service(const ::string& strServiceName, const ::string& strDisplayName,
                                        const ::string& strCommand, const ::string& strUser ,
                                        const ::string& strPass )
   {
   }


   void acme_node_layer::disable_service(const ::string& strServiceName)
   {
   }


   void acme_node_layer::start_service(const ::string& strServiceName)
   {
   }


   void acme_node_layer::stop_service(const ::string& strServiceName)
   {
   }


   //#ifdef WINDOWS
   //      virtual DECLSPEC_NO_RETURN void raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags = EXCEPTION_NONCONTINUABLE){}
   //#endif

   bool acme_node_layer::is_remote_session()
   {
      return false;
   }


   void acme_node_layer::set_file_status(const ::file::path& path, const ::file::file_status& status)
   {
   }


   //void acme_node_layer::edit_link_target(const ::file::path & path, const ::file::path & pathLink){}
   //void acme_node_layer::edit_link_folder(const ::file::path & path, const ::file::path & pathLink){}
   //void acme_node_layer::edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink){}
   //   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all){}
   bool acme_node_layer::has_alias_in_path(const ::scoped_string& scopedstr, bool bNoUI, bool bNoMount)
   {
      return false;

   }


   bool acme_node_layer::is_alias(const ::file::path& path)
   {
      return false;
   }


   void acme_node_layer::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
   {
   }


   //void acme_node_layer::set_dark_mode(bool bDarkMode){}

   void acme_node_layer::file_open(const ::file::path& path, const ::string& strParams ,
                                   const ::file::path& pathFolder )
   {
   }


   void acme_node_layer::hidden_start(const ::file::path& path, const ::string& strParams ,
                                      const ::file::path& pathFolder )
   {
   }


   void acme_node_layer::hidden_run(const class time& timeWait, const ::file::path& path,
                                    const ::string& strParams ,
                                    const ::file::path& pathFolder )
   {
   }


   ::string acme_node_layer::get_default_browser()
   {
      return {};
   }


   void acme_node_layer::get_default_browser(string& strId, ::file::path& path, string& strParam)
   {
   }


   void acme_node_layer::set_default_browser()
   {
   }


   void acme_node_layer::set_file_extension_mime_type(::get_file_extension_mime_type* pgetfileextensionmimetype)
   {
   }


   void acme_node_layer::set_file_extension_mime_type(string_array& straExtension, string_array& straMimeType)
   {
   }


   void acme_node_layer::register_user_auto_start(::platform::application* papplication, const string& strArguments,
                                                  bool bRegister)
   {
   }


   bool acme_node_layer::is_user_auto_start(const string& strAppId)
   {
      return false;
   }


   ::file::path acme_node_layer::get_app_path(const ::string& strApp)
   {
      return{};
   }


   void acme_node_layer::on_process_request(::request* prequest)
   {
   }


   /// set["file_filter_specs"] : string array of file extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   //void acme_node_layer::browse_file_open(property_set & set){}

   /// set["file_filter_specs"] : string array of extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   //void acme_node_layer::browse_file_save(property_set & set){}

   /// set["folder"] : in/out folder path
   //void acme_node_layer::browse_folder(property_set & set){}

   /// set["folder"] : in/out folder path
   //void acme_node_layer::browse_file_or_folder(property_set & set){}


   void acme_node_layer::list_process(::file::path_array& patha, ::process_identifier_array& uaPid)
   {
   }


   ::file::path_array list_process_path()
   {return{};
   }


   //virtual ::icon_pointer load_icon(const ::payload & payloadFile){}

   //void acme_node_layer::enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema){}

   void acme_node_layer::broadcast_environment_variable_change()
   {
   }


   void acme_node_layer::set_this_application_as_default_for_file_extension(const ::string& strExtension)
   {
   }


   string acme_node_layer::get_file_extension_mime_type(const ::string& strExtension)
   {
      return{};
   }


#ifdef LINUX

      enum_linux_distribution acme_node_layer::get_linux_distribution() const
   {

      return e_linux_distribution_unknown;
   }
//#ifdef LINUX

  //    inline enum_linux_distribution get_linux_distribution() const{}

      void acme_node_layer::calculate_linux_distribution()
   {



   }

#endif

#if !defined(WINDOWS)
      string_array acme_node_layer::cmdline_from_pid(::process_identifier processidentifier)
{
         
         return {};
         
      }


      atom_array acme_node_layer::app_get_pid(const ::string & pszModuleName)
   {
         
         return {};
         
      }

#endif


#if defined(WINDOWS)

   error_code  acme_node_layer::defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
   {

      return {};
   }

#endif

   //#ifdef WINDOWS_DESKTOP
   //
   //#endif
   //
   //
   //#endif


#ifdef WINDOWS_DESKTOP

   platform_char** acme_node_layer::_get_envp(wcsdup_array& a)
   {
      return nullptr;
   }


   void acme_node_layer::register_dll(const ::file::path& pathDll)
   {
   }


   ::e_status  acme_node_layer::_defer_beta_use_unicode_utf8()
   {
      return ::error_interface_only
      ;
   }


   ::e_status  acme_node_layer::_defer_enable_coder_mode()
   {
      return ::error_interface_only;
   }


   bool acme_node_layer::_has_beta_use_unicode_utf8()
   {
      return false;
   }


   bool acme_node_layer::_is_visual_studio_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_tortoise_git_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_msys2_installed()
   {
      return false;
   }


   //void acme_node_layer::_defer_install_msys2_package(const ::scoped_string & scopedstr){}

   //bool acme_node_layer::_has_msys2_command(const ::scoped_string & scopedstr){}

   //void acme_node_layer::_install_msys2_package(const ::scoped_string & scopedstr){}

   bool acme_node_layer::_is_strawberry_perl_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_coder_mode_enabled()
   {
      return false;
   }


   void acme_node_layer::_enable_coder_mode(bool bEnable)
   {
   }

#endif

   bool acme_node_layer::_is_code_exe_user_path_environment_variable_ok(::string* pstrCorrectPath,
                                                                        const char* pszPath)
   {
      return false;
   }

#if defined(WINDOWS_DESKTOP) || defined(MACOS) || defined(LINUX)

   bool acme_node_layer::_is_smart_git_installed()
   {
      return false;
   }

#endif

   bool acme_node_layer::_is_google_drive_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_dropbox_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_onedrive_installed()
   {
      return false;
   }


   void acme_node_layer::calculate_dropbox_installed()
   {
   }


   void acme_node_layer::calculate_onedrive_installed()
   {
   }


   bool acme_node_layer::_is_google_chrome_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_opera_browser_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_visual_studio_code_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_git_credential_manager_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_jetbrains_clion_installed()
   {
      return false;
   }


   bool acme_node_layer::_is_shell_patched()
   {
      return false;
   }

#ifndef UNIVERSAL_WINDOWS

   ::array<::serial::port_info>  acme_node_layer::list_serial_ports()
   {
      return {};
   }

#endif

   //#if !defined(UNIVERSAL_WINDOWS)
   //
   //
   //      //::string acme_node_layer::module_path_from_pid(::process_identifier processidentifier){}
   //      //virtual atom_array module_path_get_pid(const ::string & pszModuleName, bool bModuleNameIsPropertyFormatted){}
   //
   //
   //#ifndef WINDOWS
   //
   //
   //
   //#endif
   //
   //
   //#endif
   //
   //#ifndef UNIVERSAL_WINDOWS
   //      //bool acme_node_layer::process_contains_module(string & strImage, ::process_identifier processidentifier, const ::string & pszLibrary){}
   //      //void acme_node_layer::shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary){}
   //#endif
#if defined(__BSD__) || defined(__APPLE__)

      void acme_node_layer::arp_a(void *p, void(*callback)(void * p, unsigned int uIp, const char * status)){}

#endif

   ::string acme_node_layer::eol()
   {
      return{};
   }


   int acme_node_layer::building_core_count(bool bDedicatedBuilding)
   {
      return 0;
   }


   int acme_node_layer::performance_core_count()
   {
      return 1;
   }


   int acme_node_layer::efficiency_core_count()
   {
      return 1;
   }


   bool acme_node_layer::defer_component_factory(const ::scoped_string& scopedstrComponent)
   {
      return false;
   }


   void acme_node_layer::detached_command(const ::scoped_string& scopedstrCommand, const ::file::path& pathLog)
   {
   }


   //      void acme_node_layer::* fetch_windowing_system_display(){}
   //      void acme_node_layer::windowing_system_async(const ::procedure & procedure){}
   //      void acme_node_layer::windowing_system_display_error_trap_push(int i){}
   //      void acme_node_layer::windowing_system_display_error_trap_pop_ignored(int i){}


   bool acme_node_layer::_get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle& rectangle)
   {
      return false;
   }


   bool acme_node_layer::_get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle& rectangle)
   {
      return false;
   }


   void acme_node_layer::realize(::particle_pointer pparticle)
   {
   }


}
