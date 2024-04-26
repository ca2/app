//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//

// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#pragma once

#include "acme/constant/application_capability.h"
#include "acme/constant/element.h"
#include "acme/exception/__string.h"
#include "acme/operating_system/security_attributes.h"
#include "acme/platform/serial_shared.h"
//#include "acme/exception/status.h"
////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/primitive/pointer.h"
#include "acme/primitive/collection/atom_array.h"
#include "acme/primitive/collection/string_map.h"
//#include "acme/primitive/time/time.h"
#include "shell.h"

struct os_theme_colors;
namespace file { class set; }
namespace windowing { class display; }
class get_file_extension_mime_type;

using enum_application_capability_array = ::comparable_array < enum_application_capability >;

namespace acme
{


   class CLASS_DECL_ACME node :
      virtual public ::acme::shell
   {
   protected:



   //::procedure_array            m_routineaPost;


   public:


      union
      {

         ::u64                                              m_uNodeFlags;

         bool                                               m_bHasNodePostedSystemInitialRequest : 1;

      };

      htask_t                                               m_htaskSystem;
      ::apex::node *                                        m_papexnode;
      ::aura::node *                                        m_pauranode;

      ::acme_posix::node *                                  m_pAcmePosix;
      ::apex_posix::node *                                  m_pApexPosix;
      ::aura_posix::node *                                  m_pAuraPosix;

      :: IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::node *  m_pAcmePlatform;
      :: IDENTIFIER_SUFFIX_OPERATING_SYSTEM(apex_)::node *  m_pApexPlatform;
      :: IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)::node *  m_pAuraPlatform;
      
      
      //::pointer < ::particle >                              m_pparticleQuit;


      //::pointer < ::particle >                              m_pparticleStandardIOSynchronization;
      

      bool                                                  m_bCallStackInitialized;
      bool                                                  m_bUpdateCallStack;


      string                                                m_strTheme;
      string                                                m_strIconTheme;

      map < enum_character_set, ::string >                  m_mapCharacterSetDefaultSampleText;
      string_map < enum_character_set >                     m_mapCharacterSetEnum;

      ::os_theme_colors *                                   m_pthemecolors;

      //:: IDENTIFIER_PREFIX_OPERATING_SYSTEM(_node)::node *  m_pNode;


      //::windowing_win32::node *                             m_pWindowingWin32Node;
      //::windowing_universal_windows::node *                 m_pWindowingUniversalWindowsNode;


      //::windowing_x11::node *                               m_pNodeX11;
      //::windowing_xcb::node *                               m_pNodeXcb;
      ::node_gtk3::node *                                   m_pNodeGtk3;
      ::node_gtk4::node *                                   m_pNodeGtk4;
      ::node_gnome::node *                                  m_pNodeGnome;
      ::node_kde5::node *                                   m_pNodeKDE5;
      ::node_kde6::node *                                   m_pNodeKDE6;
      ::node_xfce::node *                                   m_pNodeXfce;
      ::desktop_environment_gnome::node *                   m_pNodeDesktopEnvironmentGnome;
      ::desktop_environment_kde::node *                     m_pNodeDesktopEnvironmentKDE;
      ::desktop_environment_xfce::node *                    m_pNodeDesktopEnvironmentXfce;

      //bool                                                m_bUserDarkMode;

      bool                                                  m_bOperatingSystemDarkMode;
      //int                                                   m_iWeatherDarkness;
      ::file::path                                          m_pathModule;

      ::user::enum_desktop                                  m_edesktop;

      enum_application_capability_array                     m_eapplicationcapabilitya;
      string_map < ::pointer<::acme::exclusive > >          m_mapExclusive;
#if defined(WITH_X11)
      void *                                                m_pvoidX11Display;
      ::e_status                                            m_estatusInitializeX11;
#endif

      node();
      ~node() override;


#ifdef _DEBUG

      i64 increment_reference_count() override;
      i64 decrement_reference_count() override;

#endif
      
      virtual ::string get_file_type_identifier(const ::file::path & path);


      virtual void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
      virtual void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode);


      virtual ::process_identifier_array module_list_file_processes_identifiers(const ::scoped_string & scopedstr);


      virtual ::enum_id key_command(::user::enum_key ekey, ::user::key_state* pkeystate);
      //idaPid = pnode->(path, false);


      virtual ::pointer < ::particle > create_mutex();


      virtual void initialize(::particle * pparticle) override;
      
      virtual void node_application_on_status(const char * pszStatus, void * p = nullptr, long long ll = 0);
      //virtual ::pointer < ::particle > create_quit_particle(::pointer<::acme::node>& pnode);

      //virtual ::pointer < ::particle > create_quit_particle();
      virtual ::file::path get_default_base_integration_folder();
      
      ///virtual void implement(::pointer<::acme::node>& pnode, ::pointer<::acme::system> & psystem);

      virtual void node_main();
      virtual void node_implement_main();

      
      virtual void on_system_main();


      virtual void start_application(::pointer<::acme::node> & pnode);


      virtual void acme_application_main(::acme::system * psystem);
      virtual void _will_finish_launching();
      
      //virtual void element_quit_post_quit();


      virtual string audio_get_default_implementation_name();
      virtual string multimedia_audio_get_default_implementation_name();
      virtual string multimedia_audio_mixer_get_default_implementation_name();
      virtual string veriwell_multimedia_music_midi_get_default_implementation_name();


      virtual void _launch_macos_app(const ::string & pszAppFolder);
  
      virtual void _launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs);

      void on_initialize_particle() override;

      virtual void initialize_memory_counter();

      virtual void system_main();

      virtual void reboot();


      virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension);


      virtual ::file::path module_path_source();
      //virtual ::file::path module_path_seed();
      //virtual ::file::path module_path_origin();
      //::file::path update_module_path();


      virtual ::pointer < ::mutex > create_local_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::string & strName, security_attributes * psecurityattributes = nullptr);
      virtual ::pointer < ::mutex > create_global_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::string & strName, security_attributes * psecurityattributes = nullptr);


      virtual ::pointer < ::mutex > open_local_named_mutex(::particle * pparticleContext, const ::string & strName);
      virtual ::pointer < ::mutex > open_global_named_mutex(::particle * pparticleContext, const ::string & strName);


      virtual ::pointer < ::mutex > get_install_mutex(::particle * pparticleContext, const ::string & strPlatform, const ::string & strSuffix);

      virtual ::pointer < ::acme::exclusive > _get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes = nullptr);

      virtual ::pointer < ::acme::exclusive > get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes = nullptr);

      virtual bool erase_exclusive(const string & strName);

      virtual void release_exclusive();

      virtual bool exclusive_fails(::particle * pparticleContext, const string & strName, security_attributes * psecurityattributes = nullptr);
    

      virtual string app_id_to_app_name(const ::string & strAppId);
      virtual string app_id_to_executable_name(const ::string & strAppId);


      virtual bool is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema);
      virtual void set_application_installed(const ::file::path& pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema);


      virtual ::file::path application_installer_folder(const ::file::path& pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema);
      virtual ::file::path get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration);


      virtual ::file::path get_last_run_application_path_file(const ::string & strAppId);
      virtual ::file::path get_last_run_application_path(const ::string & strAppId);
      virtual void  set_last_run_application_path(const string& strAppId);


      virtual ::file::path _module_path();


      //virtual bool memory_counter_on();

      //virtual ::file::path memory_counter_base_path();

      virtual void datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time);



      virtual int node_init_check(int * pi, char *** ppz);

      virtual void start_node();

      virtual void install_sigchld_handler();

      virtual ::color::color get_system_color(enum_system_color esystemcolor);

      virtual bool dark_mode() const;

      virtual ::os_theme_colors * _new_os_theme_colors();

      virtual ::os_theme_colors * _get_os_theme_colors();

      virtual void _fill_os_theme_colors(::os_theme_colors * pthemecolors);

      virtual void _set_os_theme_colors(::os_theme_colors * pthemecolors);

      virtual void _del_os_theme_colors(::os_theme_colors * pthemecolors);

      virtual void _term_os_theme_colors();

//      virtual int get_simple_ui_darkness();

//      virtual void set_simple_ui_darkness(int iWeatherDarkness);

      virtual void set_dark_mode(bool bDark);

      virtual void fetch_user_color();

      virtual void _fetch_user_color();

      virtual void on_operating_system_user_theme_change();

      virtual void on_operating_system_user_color_change();

      virtual void on_operating_system_font_list_change();

      virtual string os_get_user_theme();

      virtual void os_set_user_theme(const ::string & strUserTheme);

      virtual void os_process_user_theme(string strTheme);

      virtual void os_process_user_icon_theme(string strIconTheme);

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath, ::windowing::display * pwindowingdisplay);

      virtual string get_wallpaper(index iScreen);

      virtual string get_file_icon_path(const ::string & pszPath, int iSize);

      virtual string get_file_content_type(const ::string & pszPath);

      virtual int os_launch_uri(const ::string & pszUri, char * pszError = NULL, int iBufferSize = 0);

      virtual void enable_wallpaper_change_notification();

      virtual bool has_xcb();

      virtual void * get_os_xcb_connection();

      virtual bool is_wayland();

      virtual void user_post(const ::procedure & procedure) override;

      virtual void user_send(const ::procedure & procedure) override;

      //void post_procedure(const ::procedure & procedure) override;

      //void send_procedure(const ::procedure & procedure) override;

      virtual void defer_do_main_tasks();

      virtual void user_post_quit();

      //virtual void node_quit();

      virtual bool should_launch_on_node(::topic * ptopic);

      virtual bool defer_launch_on_node(::topic * ptopic);

      virtual bool launch_on_node(::topic * ptopic);


      virtual string get_user_name();

      virtual ::color::color get_simple_ui_color(::enum_element eelement, ::user::enum_state estate = ::user::e_state_none);

      virtual ::color::color get_default_color(::color::color color);

      virtual void set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha);


      virtual void browse_for_folder(::file::path & pathFolder);
      virtual void browse_for_file(::file::path & path);


      virtual double get_time_zone();


      virtual string font_name(enum_font efont);


      //virtual string font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);


      virtual string file_memory_map_path_from_name(const string& strName);

      virtual enum_operating_system get_operating_system() const;

      virtual ::user::enum_desktop get_edesktop();

      virtual ::user::enum_desktop calculate_edesktop();


      virtual void launch_app(const ::string & psz, const char ** argv, int iFlags);

      virtual ::file::path get_executable_path_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion);
      virtual ::file::path get_executable_path_by_app_id(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp, bool bSingleExecutableVersion);
      virtual void launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion);

      virtual ::process_identifier create_process(const ::string & pszCommandLine);

      virtual void run_silent(const ::string & strFunct, const ::string & strstrParams);

      virtual ::file::path_array process_identifier_modules_paths(::process_identifier processidentifier);

      virtual ::file::path_array modules_paths();

      virtual bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir);

      virtual ::process_identifier_array processes_identifiers();

      virtual ::process_identifier_array module_path_processes_identifiers(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted);

      virtual ::file::path process_identifier_module_path(::process_identifier processidentifier);

      virtual string process_identifier_command_line(::process_identifier processidentifier);

      //virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array& stra);

      //virtual bool is_shared_library_busy(const string_array& stra);

      virtual bool process_contains_module(string& strImage, ::process_identifier processidentifier, const ::string & pszLibrary);

      virtual ::process_identifier_array shared_library_process(string_array& straProcesses, const ::string & pszLibrary);

      virtual bool is_process_running(::process_identifier processidentifier);

      virtual string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);

      virtual string expand_environment_variables(const ::scoped_string & scopedstr);

      virtual void set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string& scopedstrValue);

      virtual void unset_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);

      virtual string get_user_language();


      virtual ::pointer < security_attributes > get_application_exclusivity_security_attributes();

      virtual void register_spa_file_type(const ::string & strAppIdHandler);

      virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration);
      virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration);
      virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration);

      virtual void get_folder_path_from_user(::file::path & pathFolder);


      //virtual ::string expand_environment_variables(const ::string & str);

      virtual ::file::path command_find_path(const ::string & pszCommand);



      virtual void launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount);


      virtual void shell_open(const ::file::path & path, const string & strParams = "", const ::file::path & pathFolder = {});
      //virtual void open_url(const ::string & strUrl);


      virtual void shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams);
      virtual void shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout = 1_minute);

      virtual void root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams);
      virtual void root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout = 1_minute);


      //::file::path command_find_path(const ::string & pszCommand);


      //virtual ::user::enum_desktop calculate_edesktop();
      //
      //
      //virtual ::user::enum_desktop get_edesktop();

      virtual void on_start_system();


      virtual void create_app_shortcut(::acme::application * papplication);


      virtual void report_exception_to_user(::particle* pparticle, ::exception& exception, const ::string& strMoreDetails);


      virtual ::pointer<::conversation> create_new_message_box_conversation();

      virtual ::pointer<::conversation> create_new_message_conversation();


      virtual pointer< ::sequencer < ::conversation > > create_message_box_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails);


      //virtual void nano_message_box(::sequence < ::conversation > * psequence, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox);

      virtual pointer< ::sequencer < ::conversation > > create_message_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails);



      virtual void shell_launch(const ::string & strAppId);


      virtual bool has_application_capability(::enum_application_capability ecapability) const;
      virtual void add_application_capability(const ::enum_application_capability_array& ecapabilitya);
      virtual void on_change_application_capability();


      //virtual void windowing_post(const ::procedure& procedure);


      virtual string get_local_mutex_name(const ::string & strAppId);
      virtual string get_local_id_mutex_name(const ::string & strAppId, const ::string & strId);
      virtual string get_global_mutex_name(const ::string & strAppId);
      virtual string get_global_id_mutex_name(const ::string & strAppId, const ::string & strId);

      


//      virtual ::string get_call_stack();


      virtual ::process_identifier current_process_identifier();


      virtual bool stdin_has_input_events();
      virtual void flush_stdin_input_events();
      virtual void flush_stdin();


      virtual void defer_update_call_stack();
//#if defined(ANDROID)
//      virtual string unwind_call_stack(const ::scoped_string & scopedstrFormat = call_stack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
//#else
      virtual int get_call_stack_default_frame_count();
      virtual void get_call_stack_frames(void ** stack, int & frame_count);
      virtual string get_call_stack_trace(const ::scoped_string & scopedstrFormat = call_stack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1);
      virtual string get_call_stack_trace(void ** stack, int frame_count, const ::scoped_string& scopedstrFormat = call_stack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr, int iCount = -1);
//#endif
      virtual string _get_call_stack_trace(const ::scoped_string & scopedstrFormat = call_stack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1);




      virtual ::string get_command_line();


      //virtual ::pointer<::acme::exclusive> get_exclusive(string str, const security_attributes & securityattributes = nullptr);

      
      virtual i32 get_current_processor_index();
      virtual i32 get_current_process_maximum_affinity();
      virtual i32 get_current_process_affinity_order();
      virtual ::u64 translate_processor_affinity(::i32 i);

      //CLASS_DECL_ACME string expand_env(string str);
      //CLASS_DECL_ACME string xxxget_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);
      //CLASS_DECL_ACME string ca2_command_line();


      //virtual int process_get_status();
      //virtual void process_set_status(int iStatus);
      //virtual int * process_get_pargc();
      //virtual int process_get_argc();


      virtual bool set_process_priority(::enum_priority epriority);




      //virtual string time_binary_platform(string strPlatform);






//
//#if !defined(UNIVERSAL_WINDOWS)
//
//      //virtual i32 call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
//
//      typedef i32 CALLSYNCONRETRY(i32 iTry, uptr dwParam);
//
//      typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;
//
//      //CLASS_DECL_ACME u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set);
//
//#endif


//#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//
//
//      //virtual i32 get_current_processor_index();
//
//      //virtual i32 get_current_process_maximum_affinity();
//
//      //virtual i32 get_current_process_affinity_order();
//
//
//#endif


      //virtual string expand_env(string str);

      //CLASS_DECL_ACME string consume_command_line_parameter(const ::string & pszCommandLine, const ::string * & pszEndPtr);
      //CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::string & pszCommandLine, const ::string & pszParam, bool bDefault = false);
      //CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam);
      //CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::string & pszCommandLine, const ::string & pszParam, const ::string & pszDefault);
      //CLASS_DECL_ACME string get_command_line_parameter(const ::string & pszCommandLine, const ::string & pszParam);


      //virtual bool launch_command(const ::string & pszCommand);


      virtual string process_configuration_name();

      virtual string time_binary_platform(const string & strPlatform);
      virtual string process_platform_name();
      //virtual string process_platform_name();
      virtual string process_version_dir_name();

      virtual ::file::path core_app_path(string strApp);




      //virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array & stra);
      //virtual bool is_shared_library_busy(const string_array & stra);


      // virtual bool launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount);



      //virtual bool shell_execute_async(const ::string & pszFile, const ::string & pszParams);
      //virtual bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout = 1_minute);

      //virtual bool root_execute_async(const ::string & pszFile, const ::string & pszParams);
      //virtual bool root_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout = 1_minute);


      //CLASS_DECL_ACME bool os_init_application();
      //CLASS_DECL_ACME void os_term_application();



      virtual string executable_title_from_appid(const string & strAppId);


      //CLASS_DECL_ACME ::u32 get_current_process_id();




      //virtual string process_version_dir_name();



      virtual int is_debug_build();


      virtual int is_release_build();


      //virtual bool succeeded(const ::error_code& errorcode);
      //virtual bool failed(const ::error_code& errorcode);


      virtual void _node_file_dialog(::file::file_dialog * pdialog);
      virtual void _node_folder_dialog(::file::folder_dialog * pdialog);

      
      virtual ::pointer < ::file::file_dialog > node_file_dialog();
      virtual ::pointer < ::file::folder_dialog > node_folder_dialog();




      virtual ::file::path library_file_name(const ::scoped_string & scopedstr);


      virtual void integration_factory();


      //virtual void unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip);


      virtual ::string get_user_permanent_environment_variable(const ::scoped_string& scopedstr);
      virtual void set_user_permanent_environment_variable(const ::scoped_string& scopedstr, const ::scoped_string& strPayload, bool bNoSystemNotify = false);


      virtual void set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string & scopedstrCommand);


      virtual ::string operating_system_store_release();

      virtual ::pointer <::operating_system::summary > operating_system_summary();
      

      //virtual void module_path_main_window_post_close(const ::scoped_string & scopestr);


      virtual ::pointer < ::operating_system::application > module_path_application(const ::scoped_string & scopestr);

      virtual ::pointer < ::operating_system::application > process_identifier_application(::process_identifier processidentifier);

      virtual ::pointer < ::operating_system::application > application_predicate(const ::function < bool(::operating_system::application * papplication) > & function);


      virtual ::string get_character_set_default_sample_text(enum_character_set echaracterset);
      virtual void load_character_set_default_sample_text();


      virtual void play_sound(const ::file::path& path);

      virtual void speak(const ::scoped_string& scopedstr);

      virtual ::string operating_system_application_version();
      

      virtual void application_handle(long long l, void * p);


      virtual bool is_application_running_good_effort(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp);


      virtual bool are_framework_shared_libraries_busy(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp);


      virtual ::string get_error_code_message(const ::error_code & errorcode);
      
      
      virtual bool defer_enumerate_protocol(::file::listing& listing);

      virtual bool defer_process_protocol_path(::file::path & path);


   void finalize() override;

   //virtual string get_command_line();

   //virtual void reboot();
   virtual void shutdown(bool bPowerOff);

   virtual void terminate_processes_by_title(const ::string & strName);

//#ifdef WINDOWS
//      virtual ::file::path get_module_path(HMODULE hmodule);
//#endif

   virtual ::process_identifier_array module_path_processes_identifiers(const ::scoped_string & scopedstrName);
   virtual ::process_identifier_array title_processes_identifiers(const ::scoped_string & scopedstrName);
   //virtual ::process_identifier_array processes_identifiers();
   //virtual ::file::path process_identifier_module_path(::process_identifier dwPid);


   //virtual ::process_identifier current_process_identifier();

   virtual ::payload connection_settings_get_auto_detect();
   virtual ::payload connection_settings_get_auto_config_url();

   virtual void open_url_link_at_system_browser(const string & strUrl, const string & strProfile = {});

   virtual void local_machine_set_run(const ::string & strKey, const ::file::path & pathExecutable, const ::string& strArguments, bool bSet);
   virtual void local_machine_set_run_once(const ::string & strKey, const ::file::path & pathExecutable, const ::string& strArguments, bool bSet);
   virtual void current_user_set_run(const ::string & strKey, const ::file::path & pathExecutable, const ::string & strArguments, bool bSet);
   virtual void current_user_set_run_once(const ::string & strKey, const ::file::path & pathExecutable, const ::string& strArguments, bool bSet);

   virtual void defer_register_ca2_plugin_for_mozilla();


   virtual void file_extension_get_open_with_list_keys(string_array & straKey, const ::string & strExtension);
   virtual void file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & strExtension);

   virtual void file_association_set_default_icon(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strIconPath);
   virtual void file_association_set_shell_open_command(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strCommand, const ::string & strParam);
   virtual void file_association_get_shell_open_command(const ::string & strExtension, string & strExtensionNamingClass, string & strCommand, string & strParam);

   virtual void native_full_web_browser(const ::string & str);


   virtual void native_modern_web_browser(const ::string & str);


   virtual void enable_service();

   virtual void disable_service();

   virtual void start_service();

   virtual void stop_service();

   virtual void enable_service(const ::string & strServiceName, const ::string & strDisplayName, const ::string & strCommand, const ::string & strUser = "", const ::string & strPass = "");

   virtual void disable_service(const ::string & strServiceName);

   virtual void start_service(const ::string & strServiceName);

   virtual void stop_service(const ::string & strServiceName);

//#ifdef WINDOWS
//      virtual DECLSPEC_NO_RETURN void raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
//#endif

   virtual bool is_remote_session();

   virtual void set_file_status(const ::file::path & path, const ::file::file_status& status);

   //virtual void edit_link_target(const ::file::path & path, const ::file::path & pathLink);
   //virtual void edit_link_folder(const ::file::path & path, const ::file::path & pathLink);
   //virtual void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink);
//   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);
   virtual bool has_alias_in_path(const ::scoped_string & scopedstr, bool bNoUI = false, bool bNoMount = false);
   virtual bool is_alias(const ::file::path & path);

   virtual void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch);

   //virtual void set_dark_mode(bool bDarkMode);

   virtual void file_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "");
   virtual void hidden_start(const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "");
   virtual void hidden_run(const class time & timeWait, const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "");

   virtual string get_default_browser();

   virtual void get_default_browser(string & strId, ::file::path & path, string & strParam);

   virtual void set_default_browser();

   virtual void set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype);

   virtual void set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType);

   virtual void register_user_auto_start(::acme::application * papplication, const string & strArguments, bool bRegister);

   virtual bool is_user_auto_start(const string & strAppId);

   virtual ::file::path get_app_path(const ::string & strApp);

   virtual void on_process_request(::request * prequest);

   /// set["file_filter_specs"] : string array of file extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   //virtual void browse_file_open(property_set & set);

   /// set["file_filter_specs"] : string array of extensions (with dot)
   /// set["file_filter_names"] : string array of the file extensions titles
   /// set["default_file_extension"] : default file extension (with dot)
   /// set["folder"] : folder path
   /// set["file_name"] : in/out file name
   //virtual void browse_file_save(property_set & set);

   /// set["folder"] : in/out folder path
   //virtual void browse_folder(property_set & set);

   /// set["folder"] : in/out folder path
   //virtual void browse_file_or_folder(property_set & set);


   virtual void list_process(::file::path_array & patha, ::process_identifier_array& uaPid);


   ::file::path_array list_process_path();

   //virtual ::icon_pointer load_icon(const ::payload & payloadFile);

   //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

   virtual void broadcast_environment_variable_change();


   virtual void set_this_application_as_default_for_file_extension(const ::string& strExtension);


   string get_file_extension_mime_type(const ::string & strExtension);


#ifdef LINUX

      virtual enum_linux_distribution get_linux_distribution() const;
//#ifdef LINUX

  //    inline enum_linux_distribution get_linux_distribution() const;

      virtual void calculate_linux_distribution();

#endif

#if !defined(WINDOWS)
      virtual string_array cmdline_from_pid(::process_identifier processidentifier);
      virtual atom_array app_get_pid(const ::string & pszModuleName);

#endif


#if defined(WINDOWS)

      virtual error_code defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE = false);

#endif
      
      //#ifdef WINDOWS_DESKTOP
//
//#endif
//
//
//#endif


#ifdef WINDOWS_DESKTOP

      virtual platform_char** _get_envp(wcsdup_array& a);

      virtual void register_dll(const ::file::path& pathDll);

      virtual ::e_status _defer_beta_use_unicode_utf8();

      virtual bool _has_beta_use_unicode_utf8();

      virtual bool _is_visual_studio_installed();

      virtual bool _is_code_exe_user_path_environment_variable_ok(::string *pstrCorrectPath=nullptr);

#endif


#ifndef UNIVERSAL_WINDOWS

      virtual ::array <::serial::port_info> list_serial_ports();

#endif

//#if !defined(UNIVERSAL_WINDOWS)
//
//
//      //virtual string module_path_from_pid(::process_identifier processidentifier);
//      //virtual atom_array module_path_get_pid(const ::string & pszModuleName, bool bModuleNameIsPropertyFormatted = true);
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
//      //virtual bool process_contains_module(string & strImage, ::process_identifier processidentifier, const ::string & pszLibrary);
//      //virtual void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary);
//#endif
#if defined(__BSD__)

      virtual void arp_a(void *p, void(*callback)(void * p, ::u32 uIp, const char * status));

#endif

      virtual ::string eol();

#if defined(WITH_X11)
      virtual ::e_status x11_defer_initialize();
      virtual ::e_status x11_initialize();
      virtual void * x11_get_display();
      virtual void x11_sync(const ::procedure & procedure);
      virtual void x11_async(const ::procedure & procedure);
      virtual void x11_display_error_trap_push(int i);
      virtual void x11_display_error_trap_pop_ignored(int i);
#endif


   };


} // namespace linux



