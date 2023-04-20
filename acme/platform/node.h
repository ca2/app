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
//#include "acme/filesystem/filesystem/path.h"
#include "acme/operating_system/security_attributes.h"
#include "acme/platform/serial_shared.h"
////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/primitive/pointer.h"
#include "acme/primitive/collection/atom_array.h"
#include "acme/primitive/collection/string_map.h"
//#include "acme/primitive/time/time.h"

inline auto std_inline_log(enum_trace_level etracelevelInformation = e_trace_level_information)
{

   auto predicate = [&](auto etracelevel, auto & str)
   {

      ::fprintf(trace_level_FILE(etracelevel, etracelevelInformation), "%c: %s\n", trace_level_letter(etracelevel),
                ::string(str).c_str());

   };

   return predicate;

}

CLASS_DECL_ACME const char * callstack_default_format();

using enum_application_capability_array = ::comparable_array < enum_application_capability >;

namespace acme
{


   class CLASS_DECL_ACME node :
      virtual public object
   {
   protected:


#ifdef LINUX

      enum_linux_distribution                            m_elinuxdistribution;

#endif

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
      
      
      ::pointer < ::particle >                              m_pparticleQuit;
      

      bool                                                  m_bCallstackInitialized;
      bool                                                  m_bUpdateCallstack;

      //:: IDENTIFIER_PREFIX_OPERATING_SYSTEM(_node)::node *  m_pNode;


      //::windowing_win32::node *                             m_pWindowingWin32Node;
      //::windowing_universal_windows::node *                 m_pWindowingUniversalWindowsNode;


      //::windowing_x11::node *                               m_pNodeX11;
      //::windowing_xcb::node *                               m_pNodeXcb;
      ::node_gtk::node *                                    m_pNodeGtk;
      ::node_gnome::node *                                  m_pNodeGnome;
      ::node_kde::node *                                    m_pNodeKDE;
      ::node_xfce::node *                                   m_pNodeXfce;
      ::desktop_environment_gnome::node *                   m_pNodeDesktopEnvironmentGnome;
      ::desktop_environment_kde::node *                     m_pNodeDesktopEnvironmentKDE;
      ::desktop_environment_xfce::node *                    m_pNodeDesktopEnvironmentXfce;

      //bool                                                m_bUserDarkMode;

      //bool                                                m_bDarkModeSystem;
      bool                                                  m_bDarkMode;
      ::color::color                                        m_colorBackground;
      double                                                m_dLuminance;
      int                                                   m_iWeatherDarkness;
      ::file::path                                          m_pathModule;

      ::user::enum_desktop                                  m_edesktop;

      enum_application_capability_array                     m_eapplicationcapabilitya;
      string_map < ::pointer<::acme::exclusive > >          m_mapExclusive;


      node();
      ~node() override;


#ifdef _DEBUG

      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif
      
      virtual ::string get_file_type_identifier(const ::file::path & path);


      virtual void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
      virtual void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode);


      virtual ::atom_array get_pid_from_module_list_file(const ::scoped_string & scopedstr);


      //idaPid = pnode->(path, false);


      virtual ::pointer < ::particle > create_mutex();
//#ifdef LINUX
//
//      virtual enum_linux_distribution get_linux_distribution() const;
//
//#endif

      virtual void initialize(::particle * pparticle) override;
      
      
      virtual ::pointer < ::particle > create_quit_particle(::pointer<::acme::node>& pnode, ::pointer<::acme::system>& psystem);
      
      
      virtual void implement(::pointer<::acme::node>& pnode, ::pointer<::acme::system> & psystem);

      virtual void start_application(::pointer<::acme::node>& pnode, ::pointer<::acme::system>& psystem);


      virtual void acme_application_main(::acme::system * psystem);
      virtual void _will_finish_launching();
      
      
      //virtual void element_quit_post_quit();


      virtual string audio_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();


      virtual void _launch_macos_app(const ::string & pszAppFolder);
  
      virtual void _launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs);

      void on_initialize_particle() override;

      virtual void initialize_memory_counter();

      virtual void system_main();

      virtual void reboot();


      virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension);


#ifdef WINDOWS_DESKTOP

      virtual void register_dll(const ::file::path& pathDll);

#endif


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

      virtual ::color::color background_color() const;

      virtual double luminance() const;

      virtual void background_color(const ::color::color & color);

      virtual int get_simple_ui_darkness();

      virtual void set_simple_ui_darkness(int iWeatherDarkness);

      virtual void fetch_user_color();

      virtual void on_operating_system_user_theme_change();

      virtual void on_operating_system_user_color_change();

      virtual void on_operating_system_font_list_change();

      virtual string os_get_user_theme();

      virtual void os_set_user_theme(const ::string & strUserTheme);

      virtual void os_process_user_theme(string strTheme);

      virtual bool set_wallpaper(index iScreen, string strLocalImagePath);

      virtual string get_wallpaper(index iScreen);

      virtual string get_file_icon_path(const ::string & pszPath, int iSize);

      virtual string get_file_content_type(const ::string & pszPath);

      virtual int os_launch_uri(const ::string & pszUri, char * pszError = NULL, int iBufferSize = 0);

      virtual void enable_wallpaper_change_notification();

      virtual bool has_xcb() const;

      virtual void * get_os_xcb_connection();

      virtual void node_post(const ::procedure & procedure);

      virtual void node_send(const ::procedure & procedure);

      void post_procedure(const ::procedure & procedure) override;

      void send_procedure(const ::procedure & procedure) override;

      virtual void node_post_quit();

      virtual void node_quit();

      virtual bool should_launch_on_node(::topic * ptopic);

      virtual bool defer_launch_on_node(::topic * ptopic);

      virtual bool launch_on_node(::topic * ptopic);


      virtual string get_user_name();

      virtual ::color::color get_simple_ui_color(::enum_element eelement, ::user::enum_state estate = ::user::e_state_none);

      virtual ::color::color get_default_color(::u64 u);

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

#ifdef LINUX

      inline enum_linux_distribution get_linux_distribution() const;

      virtual void calculate_linux_distribution();

#endif


#ifdef WINDOWS_DESKTOP

      virtual platform_char** _get_envp(wcsdup_array& a);

#endif
      
      
      virtual void launch_app(const ::string & psz, const char ** argv, int iFlags);

      virtual ::process_identifier create_process(const ::string & pszCommandLine);

      virtual void run_silent(const ::string & strFunct, const ::string & strstrParams);

      virtual bool process_modules(string_array& stra, ::process_identifier processidentifier);

      virtual bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir);

      virtual ::process_identifier_array processes_identifiers();

      virtual ::process_identifier_array module_path_processes_identifiers(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted);

      virtual string process_identifier_module_path(::process_identifier processidentifier);

      virtual string process_identifier_command_line(::process_identifier processidentifier);

      virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array& stra);

      virtual bool is_shared_library_busy(const string_array& stra);

      virtual bool process_contains_module(string& strImage, ::process_identifier processidentifier, const ::string & pszLibrary);

      virtual ::process_identifier_array shared_library_process(string_array& straProcesses, const ::string & pszLibrary);

      virtual bool is_process_running(::process_identifier processidentifier);

      virtual string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);

      virtual string expand_environment_variables(const ::scoped_string & scopedstr);

      virtual void set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string& scopedstrValue);

#ifndef UNIVERSAL_WINDOWS

      virtual ::array <::serial::port_info> list_serial_ports();

#endif


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
      virtual void open_url(const ::string & strUrl);


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


      virtual void windowing_post(const ::procedure& procedure);


      virtual string get_local_mutex_name(const ::string & strAppId);
      virtual string get_local_id_mutex_name(const ::string & strAppId, const ::string & strId);
      virtual string get_global_mutex_name(const ::string & strAppId);
      virtual string get_global_id_mutex_name(const ::string & strAppId, const ::string & strId);

      


//      virtual ::string get_callstack();


      virtual ::process_identifier current_process_identifier();


      virtual bool stdin_has_input_events();
      virtual void flush_stdin_input_events();
      virtual void flush_stdin();


      virtual void defer_update_callstack();
//#if defined(ANDROID)
//      virtual string unwind_callstack(const ::scoped_string & scopedstrFormat = callstack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
//#else
      virtual string get_callstack(const ::scoped_string & scopedstrFormat = callstack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1);
//#endif




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







#if !defined(UNIVERSAL_WINDOWS)

      //virtual i32 call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

      typedef i32 CALLSYNCONRETRY(i32 iTry, uptr dwParam);

      typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

      //CLASS_DECL_ACME u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set);

#endif


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

#if !defined(UNIVERSAL_WINDOWS)


      //virtual string module_path_from_pid(::process_identifier processidentifier);
      //virtual atom_array module_path_get_pid(const ::string & pszModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

      virtual string_array cmdline_from_pid(::process_identifier processidentifier);
      virtual atom_array app_get_pid(const ::string & pszModuleName);


#endif


#endif

#ifndef UNIVERSAL_WINDOWS
      //virtual bool process_contains_module(string & strImage, ::::process_identifier processidentifier, const ::string & pszLibrary);
      //virtual void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary);
#endif



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



      virtual void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);




      //virtual void command_system(string_array & straOutput, int & iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem = e_command_system_none, const class ::time & waitTimeout = ::time::infinity(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr);
      virtual int command_system(const ::scoped_string & scopedstr, const trace_function & tracefunction = nullptr);


      //virtual string process_version_dir_name();



      virtual int is_debug_build();


      virtual int is_release_build();


      virtual bool succeeded(const ::error_code& errorcode);
      virtual bool failed(const ::error_code& errorcode);


#ifdef WINDOWS

      virtual error_code defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE = false);

#endif
      

      virtual void _node_file_dialog(::file::file_dialog * pdialog);
      virtual void _node_folder_dialog(::file::folder_dialog * pdialog);

      
      virtual ::pointer < ::file::file_dialog > node_file_dialog();
      virtual ::pointer < ::file::folder_dialog > node_folder_dialog();




      virtual ::file::path library_file_name(const ::scoped_string & scopedstr);


      virtual void integration_factory();


      //virtual void unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip);


      virtual ::string get_user_permanent_environment_variable(const ::scoped_string& scopedstr);
      virtual void set_user_permanent_environment_variable(const ::scoped_string& scopedstr, const ::scoped_string& strPayload);


#ifdef WINDOWS_DESKTOP

      virtual void _beta_use_unicode_utf8();

#endif


      virtual void set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string & scopedstrCommand);


      virtual bool has_unix_shell_command(const ::scoped_string& scopedstrCommand);

      virtual int unix_shell_command(const ::scoped_string& scopedstrCommand, const trace_function & tracefunction = nullptr);

      virtual ::string unix_shell_command_string(const ::scoped_string & scopedstrCommand);

      virtual ::string operating_system_store_release();

      virtual ::pointer <::operating_system::summary > operating_system_summary();
      

      //virtual void module_path_main_window_post_close(const ::scoped_string & scopestr);


      virtual ::pointer < ::operating_system::application > module_path_application(const ::scoped_string & scopestr);


   };


} // namespace linux



