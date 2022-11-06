//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//

// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#pragma once


#include "acme/constant/element.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/operating_system/security_attributes.h"
#include "acme/platform/serial_shared.h"
#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/atom_array.h"
#include "acme/primitive/collection/string_map.h"


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
      
      
      ::pointer<::particle>                                 m_pparticleQuit;
      

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
      
      virtual ::string get_file_type_identifier(const char * path);


      virtual void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
      virtual void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set, int * piExitCode);


//#ifdef LINUX
//
//      virtual enum_linux_distribution get_linux_distribution() const;
//
//#endif

      virtual void initialize(::particle * pparticle) override;
      
      
      virtual ::pointer<::particle>create_quit_element(::pointer<::acme::node> & pnode, ::pointer<::acme::system> & psystem);
      
      
      virtual void implement(::pointer<::acme::node>& pnode, ::pointer<::acme::system> & psystem);

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

      virtual void create_process(const ::string & pszCommandLine, u32 * pprocessID);

      virtual void run_silent(const ::string & strFunct, const ::string & strstrParams);

      virtual bool process_modules(string_array& stra, u32 processID);

      virtual bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir);

      virtual atom_array get_pids();

      virtual atom_array module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted);

      virtual string module_path_from_pid(u32 pid);

      virtual string command_line_from_pid(u32 pid);

      virtual bool is_shared_library_busy(u32 processid, const string_array& stra);

      virtual bool is_shared_library_busy(const string_array& stra);

      virtual bool process_contains_module(string& strImage, ::u32 processID, const ::string & pszLibrary);

      virtual void shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & pszLibrary);

      virtual bool is_process_running(::u32 pid);

      virtual string get_environment_variable(const ::string & pszEnvironmentVariable);

      virtual string expand_environment_variables(const string & str);

      virtual void set_environment_variable(const ::string& pszEnvironmentVariable, const ::string& pszValue);

#ifndef _UWP

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


      virtual void shell_execute_async(const char * pszFile, const char * pszParams);
      virtual void shell_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = minute());

      virtual void root_execute_async(const char * pszFile, const char * pszParams);
      virtual void root_execute_sync(const char * pszFile, const char * pszParams, ::duration durationTimeout = minute());


      //::file::path command_find_path(const ::string & pszCommand);


      //virtual ::user::enum_desktop calculate_edesktop();
      //
      //
      //virtual ::user::enum_desktop get_edesktop();

      virtual void on_start_system();


      virtual void create_app_shortcut(::acme::application * papplication);


      virtual void report_exception_to_user(::object* pparticle, ::exception& exception, const ::string& strMoreDetails);


      virtual ::pointer<::conversation>create_new_message_box_conversation();

      virtual ::pointer<::conversation>create_new_message_conversation();


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


      virtual ::i64 get_current_process_id();


      virtual bool stdin_has_input_events();
      virtual void flush_stdin_input_events();
      virtual void flush_stdin();


      virtual void defer_initialize_callstack();
#if defined(ANDROID)
      virtual string unwind_callstack(const char * pszFormat = callstack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
#else
      virtual string get_callstack(const char * pszFormat = callstack_default_format(), i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1);
#endif




      virtual ::string get_command_line();


      //virtual ::pointer<::acme::exclusive> get_exclusive(string str, const security_attributes & securityattributes = nullptr);

      
      virtual i32 get_current_processor_index();
      virtual i32 get_current_process_maximum_affinity();
      virtual i32 get_current_process_affinity_order();
      virtual ::u64 translate_processor_affinity(::i32 i);

      //CLASS_DECL_ACME string expand_env(string str);
      //CLASS_DECL_ACME string xxxget_environment_variable(const char * pszEnvironmentVariable);
      //CLASS_DECL_ACME string ca2_command_line();




      //virtual int process_get_status();
      //virtual void process_set_status(int iStatus);
      //virtual int * process_get_pargc();
      //virtual int process_get_argc();


      virtual bool set_process_priority(::enum_priority epriority);




      //virtual string time_binary_platform(string strPlatform);







#if !defined(_UWP)

      //virtual i32 call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);

      typedef i32 CALLSYNCONRETRY(i32 iTry, uptr dwParam);

      typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

      //CLASS_DECL_ACME u32 call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set);

#endif


//#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
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

#if !defined(_UWP)


      //virtual string module_path_from_pid(unsigned int pid);
      //virtual atom_array module_path_get_pid(const ::string & pszModuleName, bool bModuleNameIsPropertyFormatted = true);


#ifndef WINDOWS

      virtual string_array cmdline_from_pid(unsigned int pid);
      virtual atom_array app_get_pid(const ::string & pszModuleName);


#endif


#endif

#ifndef _UWP
      //virtual bool process_contains_module(string & strImage, ::u32 processID, const ::string & pszLibrary);
      //virtual void shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary);
#endif



      //virtual bool is_shared_library_busy(u32 processid, const string_array & stra);
      //virtual bool is_shared_library_busy(const string_array & stra);


      // virtual bool launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount);



      virtual bool shell_execute_async(const ::string & pszFile, const ::string & pszParams);
      virtual bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, const ::duration & durationTimeout = 1_minute);

      virtual bool root_execute_async(const ::string & pszFile, const ::string & pszParams);
      virtual bool root_execute_sync(const ::string & pszFile, const ::string & pszParams, const ::duration & durationTimeout = 1_minute);


      //CLASS_DECL_ACME bool os_init_application();
      //CLASS_DECL_ACME void os_term_application();



      virtual string executable_title_from_appid(const string & strAppId);


      //CLASS_DECL_ACME ::u32 get_current_process_id();



      virtual void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);




      virtual void command_system(string_array & straOutput, int & iExitCode, const char * psz, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr);


      //virtual string process_version_dir_name();



      virtual int is_debug_build();


      virtual int is_release_build();



   };


} // namespace linux



