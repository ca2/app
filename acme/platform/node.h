//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//

// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#pragma once


#include "node_acme.h"
#include "node_apex.h"
#include "node_aqua.h"
#include "node_aura.h"

namespace platform
{


   class CLASS_DECL_ACME node :
      virtual public ::acme::shell,
      virtual public ::platform::acme_node_layer_t,
      virtual public ::platform::apex_node_layer_t,
      virtual public ::platform::aqua_node_layer_t,
      virtual public ::platform::aura_node_layer_t,
      virtual public ::platform::acme_node_layer,
      virtual public ::platform::apex_node_layer,
      virtual public ::platform::aqua_node_layer,
      virtual public ::platform::aura_node_layer
   {
   public:

   //       bool                          m_bDropboxCalculated;
   //       bool                          m_bDropbox;
   //       ::file::path                  m_pathDropbox;
   //
   //
   //       bool                          m_bOneDriveCalculated;
   //       bool                          m_bOneDrive;
   //       ::file::path                  m_pathOneDrive;
   //
   // protected:
   //
   //
   //
   //
   // //::procedure_array            m_routineaPost;
   //
   //
   // public:
   //
   //
   //    union
   //    {
   //
   //       unsigned long long                                              m_uNodeFlags;
   //
   //       bool                                               m_bHasNodePostedSystemInitialRequest : 1;
   //
   //    };
   //
   //    htask                                               m_htaskSystem;
   //    ::apex::node *                                        m_papexnode;
   //    ::aura::node *                                        m_pauranode;
   //
   //    ::acme_posix::node *                                  m_pAcmePosix;
   //    ::apex_posix::node *                                  m_pApexPosix;
   //    ::aura_posix::node *                                  m_pAuraPosix;
   //
   //    :: IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::node *  m_pAcmePlatform;
   //    :: IDENTIFIER_SUFFIX_OPERATING_SYSTEM(apex_)::node *  m_pApexPlatform;
   //    :: IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)::node *  m_pAuraPlatform;
   //
   //
   //    //::particle_pointer                              m_pparticleQuit;
   //
   //
   //    //::particle_pointer                              m_pparticleStandardIOSynchronization;
   //
   //
   //    bool                                                  m_bCallStackInitialized;
   //    bool                                                  m_bUpdateCallStack;
   //
   //
   //    string                                                m_strTheme;
   //    string                                                m_strIconTheme;
   //
   //    map < enum_character_set, ::string >                  m_mapCharacterSetDefaultSampleText;
   //    string_map < enum_character_set >                     m_mapCharacterSetEnum;
   //
   //    ::os_theme_colors *                                   m_pthemecolors;
   //
   //    //:: IDENTIFIER_PREFIX_OPERATING_SYSTEM(_node)::node *  m_pNode;
   //
   //
   //    //::windowing_win32::node *                             m_pWindowingWin32Node;
   //    //::windowing_universal_windows::node *                 m_pWindowingUniversalWindowsNode;
   //
   //
   //    //::windowing_x11::node *                               m_pNodeX11;
   //    //::windowing_xcb::node *                               m_pNodeXcb;
   //    ::node_gtk3::node *                                   m_pNodeGtk3;
   //    ::node_gtk4::node *                                   m_pNodeGtk4;
   //    ::node_gtk_based::node *                              m_pNodeGtkBased;
   //    ::node_kde5::node *                                   m_pNodeKDE5;
   //    ::node_kde6::node *                                   m_pNodeKDE6;
   //    ::node_xfce::node *                                   m_pNodeXfce;
   //    ::operating_ambient_gtk_based::node *               m_pNodeDesktopEnvironmentGtkBased;
   //    ::desktop_environment_kde::node *                     m_pNodeDesktopEnvironmentKDE;
   //    ::desktop_environment_xfce::node *                    m_pNodeDesktopEnvironmentXfce;
   //
   //    //bool                                                m_bUserDarkMode;
   //
   //    //bool                                                  m_bOperatingSystemDarkMode;
   //    //int                                                   m_iWeatherDarkness;
   //    ::file::path                                          m_pathModule;
   //
   //
   //    enum_application_capability_array                     m_eapplicationcapabilitya;
   //    string_map < ::pointer<::acme::exclusive > >          m_mapExclusive;

      node();
      ~node() override;


#ifdef _DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif

      virtual ::string get_file_type_identifier(const ::file::path & path) override;


      virtual void call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr) override;
      virtual void call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set, int * piExitCode) override;


      virtual ::process_identifier_array module_list_file_processes_identifiers(const ::scoped_string & scopedstr) override;


      virtual ::enum_id key_command(::user::enum_key ekey, ::user::key_state* pkeystate) override;
      //idaPid = pnode->(path, false);


      virtual ::particle_pointer create_mutex() override;


      virtual void initialize(::particle * pparticle) override;

      virtual void node_application_on_status(const char * pszStatus, void * p = nullptr, long long hi = 0) override;
      //virtual ::particle_pointer create_quit_particle(::pointer<::platform::node>& pnode);

      //virtual ::particle_pointer create_quit_particle();
      virtual ::file::path get_default_base_integration_folder() override;


      ///virtual void implement(::pointer<::platform::node>& pnode, ::pointer<::platform::system> & psystem);

      void node_main() override;
      void node_implement_main() override;


      void on_app_activated(::user::activation_token * puseractivationtoken) override;

      void on_system_main() override;


      void start_application(::pointer<::platform::node> & pnode) override;


      //void acme_application_main(::platform::system * psystem) override;
      void _will_finish_launching() override;

      //virtual void element_quit_post_quit();


      string audio_get_default_implementation_name() override;
      string multimedia_audio_get_default_implementation_name() override;
      string multimedia_audio_mixer_get_default_implementation_name() override;
      string veriwell_multimedia_music_midi_get_default_implementation_name() override;


      virtual void defer_register_server_library(const ::platform::uuid & uuid, const ::file::path & path);
      virtual void defer_unregister_server_library(const ::platform::uuid & uuid, const ::file::path & path);
      virtual bool is_server_library_registered(::file::path & path, const ::platform::uuid & uuid);


      void _launch_macos_app(const ::string & pszAppFolder) override;

      void _launch_macos_app_args(const ::string & pszAppFolder, const ::string & pszArgs) override;

      void on_initialize_particle() override;

      void initialize_memory_counter() override;

      void system_main() override;

      void reboot() override;

      void defer_show_system_menu(::user::mouse * pmouse) override;
      void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension) override;


      ::file::path module_path_source() override;
      //virtual ::file::path module_path_seed();
      //virtual ::file::path module_path_origin();
      //::file::path update_module_path();


      ::pointer < ::mutex > create_local_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::string & strName, security_attributes * psecurityattributes = nullptr) override;
      ::pointer < ::mutex > create_global_named_mutex(::particle * pparticleContext, bool bInitiallyOwned, const ::string & strName, security_attributes * psecurityattributes = nullptr) override;


      ::pointer < ::mutex > open_local_named_mutex(::particle * pparticleContext, const ::string & strName) override;
      ::pointer < ::mutex > open_global_named_mutex(::particle * pparticleContext, const ::string & strName) override;


      ::pointer < ::mutex > get_install_mutex(::particle * pparticleContext, const ::string & strPlatform, const ::string & strSuffix) override;

      ::pointer < ::acme::exclusive > _get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes = nullptr) override;

      ::pointer < ::acme::exclusive > get_exclusive(::particle * pparticleContext, const ::string & strName, ::security_attributes * psecurityattributes = nullptr) override;

      bool erase_exclusive(const string & strName) override;

      void release_exclusive() override;

      bool exclusive_fails(::particle * pparticleContext, const string & strName, security_attributes * psecurityattributes = nullptr) override;


      string app_id_to_app_name(const ::string & strAppId) override;
      string app_id_to_executable_name(const ::string & strAppId) override;


      bool is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;
      void set_application_installed(const ::file::path& pathExe, string strAppId, const ::string & pszBuild, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;


      ::file::path application_installer_folder(const ::file::path& pathExe, string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration, const ::string & pszLocale, const ::string & pszSchema) override;
      ::file::path get_application_path(string strAppId, const ::string & pszPlatform, const ::string & pszConfiguration) override;


      ::file::path get_last_run_application_path_file(const ::string & strAppId) override;
      ::file::path get_last_run_application_path(const ::string & strAppId) override;
      void  set_last_run_application_path(const string& strAppId) override;


      virtual ::file::path _module_path() override;

      //virtual void do_windowing_system_factory();


      //virtual bool memory_counter_on();

      //virtual ::file::path memory_counter_base_path();

      virtual void datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time) override;



      virtual int node_init_check(int * pi, char *** ppz) override;

      virtual void start_node() override;

      virtual void install_sigchld_handler() override;

      // virtual ::color::color get_system_color(enum_system_color esystemcolor);
      //
      // //virtual bool dark_mode() const;
      //
      // virtual ::os_theme_colors * _new_os_theme_colors();
      //
      // virtual ::os_theme_colors * _get_os_theme_colors();
      //
      // virtual void _fill_os_theme_colors(::os_theme_colors * pthemecolors);
      //
      // virtual void _set_os_theme_colors(::os_theme_colors * pthemecolors);
      //
      // virtual void _del_os_theme_colors(::os_theme_colors * pthemecolors);
      //
      // virtual void _term_os_theme_colors();

//      virtual int get_simple_ui_darkness();

//      virtual void set_simple_ui_darkness(int iWeatherDarkness);

      //virtual void set_dark_mode(bool bDark);

      // virtual void fetch_user_color();
      //
      // virtual void _fetch_user_color();

      //virtual void on_operating_system_user_theme_change();

      //virtual void on_operating_system_user_color_change();

      //virtual void on_operating_system_font_list_change();

      //virtual string os_get_user_theme();

      //virtual void os_set_user_theme(const ::string & strUserTheme);

      //virtual void os_process_user_theme(string strTheme);

      //virtual void os_process_user_icon_theme(string strIconTheme);

      virtual string get_file_icon_path(const ::string & pszPath, int iSize) override;

      virtual string get_file_content_type(const ::string & pszPath) override;

      virtual int os_launch_uri(const ::string & pszUri, char * pszError = NULL, int iBufferSize = 0) override;

      //virtual void enable_wallpaper_change_notification() override;

      virtual bool has_xcb() override;

      virtual void * get_os_xcb_connection() override;

      virtual bool is_wayland() override;

      void _user_send(const ::procedure & procedure) override;
      void _user_post(const ::procedure & procedure) override;

      //virtual void _user_send(::subparticle * psubparticle) override;
      //virtual void _user_post(::subparticle * psubparticle) override;

      //void post_procedure(const ::procedure & procedure) override;

      //void send_procedure(const ::procedure & procedure) override;

      virtual void defer_do_main_tasks() override;

      //virtual void user_post_quit() override;

      //virtual void node_quit();

      virtual bool should_launch_on_node(::topic * ptopic) override;

      virtual bool defer_launch_on_node(::topic * ptopic) override;

      virtual bool launch_on_node(::topic * ptopic) override;


      virtual string get_user_name() override;


      virtual void set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha) override;


      virtual void browse_for_folder(::file::path & pathFolder) override;
      virtual void browse_for_file(::file::path & path) override;


      virtual double get_time_zone() override;


      virtual string font_name(enum_font efont) override;


      //virtual string font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);


      virtual string file_memory_map_path_from_name(const string& strName) override;

      virtual enum_operating_system get_operating_system() const override;

      //virtual ::user::enum_operating_ambient get_eoperating_ambient();
      //virtual ::user::enum_toolkit get_etoolkit();

      //virtual ::user::enum_operating_ambient calculate_edesktop();
      //virtual ::user::enum_toolkit calculate_etoolkit();

      //virtual ::string get_user_toolkit_id();

      virtual void launch_app(const ::string & psz, const char ** argv, int iFlags) override;

      virtual ::file::path get_executable_path_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion) override;
      virtual ::file::path get_executable_path_by_app_id(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp, bool bSingleExecutableVersion) override;
      virtual void launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion) override;

      virtual ::process_identifier create_process(const ::string & pszCommandLine) override;

      virtual void run_silent(const ::string & strFunct, const ::string & strstrParams) override;

      virtual ::file::path_array process_identifier_modules_paths(::process_identifier processidentifier) override;

      virtual ::file::path_array modules_paths() override;

      virtual bool load_modules_diff(string_array& straOld, string_array& straNew, const ::string & pszExceptDir) override;

      virtual ::process_identifier_array processes_identifiers() override;

      virtual ::process_identifier_array module_path_processes_identifiers(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted) override;

      virtual ::file::path process_identifier_module_path(::process_identifier processidentifier) override;

      virtual string process_identifier_command_line(::process_identifier processidentifier) override;

      //virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array& stra);

      //virtual bool is_shared_library_busy(const string_array& stra);

      virtual bool process_contains_module(string& strImage, ::process_identifier processidentifier, const ::string & pszLibrary) override;

      virtual ::process_identifier_array shared_library_process(string_array& straProcesses, const ::string & pszLibrary) override;

      virtual bool is_process_running(::process_identifier processidentifier) override;

      virtual string get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;

      virtual string expand_environment_variables(const ::scoped_string & scopedstr) override;

      virtual void set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string& scopedstrValue) override;

      virtual void unset_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable) override;

      virtual string get_user_language() override;


      virtual ::pointer < security_attributes > get_application_exclusivity_security_attributes() override;

      virtual void register_spa_file_type(const ::string & strAppIdHandler) override;

      virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration) override;
      virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;
      virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;

      virtual void get_folder_path_from_user(::file::path & pathFolder) override;


      //virtual ::string expand_environment_variables(const ::string & str);

      virtual ::file::path command_find_path(const ::string & pszCommand) override;



      virtual void launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount) override;


       virtual void shell_open(const ::file::path & path, const string & strParams = "", const ::file::path & pathFolder = {}) override;
      //virtual void open_url(const ::string & strUrl);


      virtual void shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const ::file::path& pathWorkingDirectory = {}) override;
      virtual int shell_execute_sync(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams, const class time& timeTimeout = 1_minute, const ::file::path& pathWorkingDirectory = {}) override;

      virtual void root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const ::file::path& pathWorkingDirectory = {}) override;
      virtual int root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout = 1_minute, const ::file::path& pathWorkingDirectory = {}) override;


      //::file::path command_find_path(const ::string & pszCommand);


      //virtual ::user::enum_operating_ambient calculate_edesktop();
      //
      //
      //virtual ::user::enum_operating_ambient get_eoperating_ambient();

      virtual void on_start_system() override;


      virtual void create_app_shortcut(::platform::application * papplication) override;


      virtual void report_exception_to_user(::particle* pparticle, ::exception& exception, const ::string& strMoreDetails) override;


      //virtual ::pointer<::conversation> create_new_message_box_conversation();

      //virtual ::pointer<::conversation> create_new_message_conversation();


      //virtual ::pointer < ::subparticle > create_message_box_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon);


      //virtual void ::micro::message_box(::sequence < ::conversation > * psequence, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox);

      //virtual ::pointer < ::subparticle > create_message_sequencer(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon);



      virtual void shell_launch(const ::string & strAppId) override;


      virtual bool has_application_capability(::enum_application_capability ecapability) const override;
      virtual void add_application_capability(const ::enum_application_capability_array& ecapabilitya) override;
      virtual void on_change_application_capability() override;


      //virtual void windowing_post(const ::procedure& procedure);


      virtual string get_local_mutex_name(const ::string & strAppId) override;
      virtual string get_local_id_mutex_name(const ::string & strAppId, const ::string & strId) override;
      virtual string get_global_mutex_name(const ::string & strAppId) override;
       virtual string get_global_id_mutex_name(const ::string & strAppId, const ::string & strId) override;




//      virtual ::string get_call_stack();


      virtual ::process_identifier current_process_identifier() override;


      virtual bool stdin_has_input_events() override;
      virtual void flush_stdin_input_events() override;
      virtual void flush_stdin() override;


      virtual void defer_update_call_stack() override;
//#if defined(ANDROID)
//      virtual string unwind_call_stack(const ::scoped_string & scopedstrFormat = call_stack_default_format(), int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
//#else
      virtual int get_call_stack_default_frame_count() override;
      virtual void get_call_stack_frames(void ** stack, int & frame_count) override;
      virtual string get_call_stack_trace(const ::scoped_string & scopedstrFormat = call_stack_default_format(), int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1) override;
      virtual string get_call_stack_trace(void ** stack, int frame_count, const ::scoped_string& scopedstrFormat = call_stack_default_format(), int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr, int iCount = -1) override;
//#endif
      virtual string _get_call_stack_trace(const ::scoped_string & scopedstrFormat = call_stack_default_format(), int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, int iCount = -1) override;




      virtual ::string get_command_line() override;


      //virtual ::pointer<::acme::exclusive> get_exclusive(string str, const security_attributes & securityattributes = nullptr);


      virtual int get_current_processor_index() override;
      virtual int get_current_process_maximum_affinity() override;
      virtual int get_current_process_affinity_order() override;
      virtual unsigned long long translate_processor_affinity(int i) override;

      //CLASS_DECL_ACME string expand_env(string str);
      //CLASS_DECL_ACME string xxxget_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);
      //CLASS_DECL_ACME string ca2_command_line();


      //virtual int process_get_status();
      //virtual void process_set_status(int iStatus);
      //virtual int * process_get_pargc();
      //virtual int process_get_argc();


      virtual bool set_process_priority(::enum_priority epriority) override;




      //virtual string time_binary_platform(string strPlatform);






//
//#if !defined(UNIVERSAL_WINDOWS)
//
//      //virtual int call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
//
//      typedef int CALLSYNCONRETRY(int iTry, uptr dwParam);
//
//      typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;
//
//      //CLASS_DECL_ACME unsigned int call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set);
//
//#endif


//#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//
//
//      //virtual int get_current_processor_index();
//
//      //virtual int get_current_process_maximum_affinity();
//
//      //virtual int get_current_process_affinity_order();
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


      virtual string process_configuration_name() override;

      virtual string time_binary_platform(const string & strPlatform) override;
      virtual string process_platform_name() override;
      //virtual string process_platform_name();
      virtual string process_version_dir_name() override;

      virtual ::file::path core_app_path(string strApp) override;




      //virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array & stra);
      //virtual bool is_shared_library_busy(const string_array & stra);


      // virtual bool launch_application(::particle * pparticle, const ::string & strAppId, const ::string & strParams, int iBitCount);



      //virtual bool shell_execute_async(const ::string & pszFile, const ::string & pszParams);
      //virtual bool shell_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout = 1_minute);

      //virtual bool root_execute_async(const ::string & pszFile, const ::string & pszParams);
      //virtual bool root_execute_sync(const ::string & pszFile, const ::string & pszParams, const class time & timeTimeout = 1_minute);


      //CLASS_DECL_ACME bool os_init_application();
      //CLASS_DECL_ACME void os_term_application();



      virtual string executable_title_from_appid(const string & strAppId) override;


      //CLASS_DECL_ACME unsigned int get_current_process_id();




      //virtual string process_version_dir_name();



      virtual int is_debug_build() override;


      virtual int is_release_build() override;


      //virtual bool succeeded(const ::error_code& errorcode);
      //virtual bool failed(const ::error_code& errorcode);


      virtual void _node_file_dialog(::file::file_dialog * pdialog) override;
      virtual void _node_folder_dialog(::file::folder_dialog * pdialog) override;


      virtual ::pointer < ::file::file_dialog > node_file_dialog() override;
      virtual ::pointer < ::file::folder_dialog > node_folder_dialog() override;




      ::file::path library_file_name(const ::scoped_string & scopedstr) override;


      ::string default_component_implementation(const ::scoped_string & scopedstrComponentName) override;

      void integration_factory() override;


      //virtual void unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip);


      ::string get_user_permanent_environment_variable(const ::scoped_string& scopedstr) override;
      ::string get_system_permanent_environment_variable(const ::scoped_string& scopedstr) override;
      void set_user_permanent_environment_variable(const ::scoped_string& scopedstr, const ::scoped_string& strPayload, bool bNoSystemNotify = false) override;

      void system_notify_environment_variable_change() override;

      void update_process_environment_variables() override;


      void set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string & scopedstrCommand) override;


      ::string operating_system_store_release() override;

      ::pointer <::operating_system::summary > operating_system_summary() override;


      //virtual void module_path_main_window_post_close(const ::scoped_string & scopestr);

      ::pointer < ::operating_system::application > module_path_application(const ::scoped_string & scopestr) override;

      ::pointer < ::operating_system::application > process_identifier_application(::process_identifier processidentifier) override;

      ::pointer < ::operating_system::application > application_predicate(const ::function < bool(::operating_system::application * papplication) > & function) override;


      ::string get_character_set_default_sample_text(enum_character_set echaracterset) override;
      void load_character_set_default_sample_text() override;


      void play_sound(const ::file::path& path) override;

      //virtual void speak(const ::scoped_string& scopedstr);

      ::string operating_system_application_version() override;


      bool is_application_running_good_effort(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp) override;


      bool are_framework_shared_libraries_busy(const ::scoped_string & scopedstrRepos, const ::scoped_string & scopedstrApp) override;
      
      bool are_any_shared_libraries_mapped(const ::file::path_array & patha) override;


      ::string get_error_code_message(const ::error_code & errorcode) override;


      bool defer_enumerate_protocol(::file::listing& listing) override;

      bool defer_process_protocol_path(::file::path & path) override;


   void destroy() override;

   //virtual string get_command_line();

   //virtual void reboot();
   void shutdown(bool bPowerOff) override;

   void terminate_processes_by_title(const ::string & strName) override;

//#ifdef WINDOWS
//      virtual ::file::path get_module_path(HMODULE hmodule);
//#endif

   ::process_identifier_array module_path_processes_identifiers(const ::scoped_string & scopedstrName) override;
   ::process_identifier_array title_processes_identifiers(const ::scoped_string & scopedstrName) override;
   //virtual ::process_identifier_array processes_identifiers();
   //virtual ::file::path process_identifier_module_path(::process_identifier dwPid);


   //virtual ::process_identifier current_process_identifier();

   ::payload connection_settings_get_auto_detect() override;
   ::payload connection_settings_get_auto_config_url() override;

   void open_url_link_at_system_browser(const string & strUrl, const string & strProfile = {}) override;

   void local_machine_set_run(const ::string & strKey, const ::file::path & pathExecutable, const ::string& strArguments, bool bSet) override;
   void local_machine_set_run_once(const ::string & strKey, const ::file::path & pathExecutable, const ::string& strArguments, bool bSet) override;
   void current_user_set_run(const ::string & strKey, const ::file::path & pathExecutable, const ::string & strArguments, bool bSet) override;
   void current_user_set_run_once(const ::string & strKey, const ::file::path & pathExecutable, const ::string& strArguments, bool bSet) override;

   void defer_register_ca2_plugin_for_mozilla() override;


   void file_extension_get_open_with_list_keys(string_array & straKey, const ::string & strExtension) override;
   void file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & strExtension) override;

   void file_association_set_default_icon(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strIconPath) override;
   void file_association_set_shell_open_command(const ::string & strExtension, const ::string & strExtensionNamingClass, const ::string & strCommand, const ::string & strParam) override;
   void file_association_get_shell_open_command(const ::string & strExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

   void native_full_web_browser(const ::string & str) override;


   void native_modern_web_browser(const ::string & str) override;


   void enable_service() override;

   void disable_service() override;

   void start_service() override;

   void stop_service() override;

   void enable_service(const ::string & strServiceName, const ::string & strDisplayName, const ::string & strCommand, const ::string & strUser = "", const ::string & strPass = "") override;

   void disable_service(const ::string & strServiceName) override;

   void start_service(const ::string & strServiceName) override;

   void stop_service(const ::string & strServiceName) override;

//#ifdef WINDOWS
//      virtual DECLSPEC_NO_RETURN void raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
//#endif

   bool is_remote_session() override;

   void set_file_status(const ::file::path & path, const ::file::file_status& status) override;

   //virtual void edit_link_target(const ::file::path & path, const ::file::path & pathLink);
   //virtual void edit_link_folder(const ::file::path & path, const ::file::path & pathLink);
   //virtual void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink);
//   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);
   bool has_alias_in_path(const ::scoped_string & scopedstr, bool bNoUI = false, bool bNoMount = false) override;
   bool is_alias(const ::file::path & path) override;

   void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch) override;

   //virtual void set_dark_mode(bool bDarkMode);

   void file_open(const ::file::path & path, const ::string & strParams = "", const ::file::path & pathFolder = "") override;
   void hidden_start(const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "") override;
   void hidden_run(const class time & timeWait, const ::file::path& path, const ::string& strParams = "", const ::file::path& pathFolder = "") override;

   string get_default_browser() override;

   void get_default_browser(string & strId, ::file::path & path, string & strParam) override;

   void set_default_browser() override;

   void set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype) override;

   void set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType) override;

   void register_user_auto_start(::platform::application * papplication, const string & strArguments, bool bRegister) override;

   bool is_user_auto_start(const string & strAppId) override;

   ::file::path get_app_path(const ::string & strApp) override;

   void on_process_request(::request * prequest) override;

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


   void list_process(::file::path_array & patha, ::process_identifier_array& uaPid) override;


   ::file::path_array list_process_path();

   //virtual ::icon_pointer load_icon(const ::payload & payloadFile);

   //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

   void broadcast_environment_variable_change() override;


   void set_this_application_as_default_for_file_extension(const ::string& strExtension) override;


   string get_file_extension_mime_type(const ::string & strExtension);


#ifdef LINUX

      virtual enum_linux_distribution get_linux_distribution() const;
//#ifdef LINUX

  //    inline enum_linux_distribution get_linux_distribution() const;

      virtual void calculate_linux_distribution();

#endif

#if !defined(WINDOWS)
      string_array cmdline_from_pid(::process_identifier processidentifier) override;
      atom_array app_get_pid(const ::string & pszModuleName) override;

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

      virtual ::string display_file_path(const ::file::path & path);


#ifdef WINDOWS_DESKTOP

      virtual platform_char** _get_envp(wcsdup_array& a);

      virtual void register_dll(const ::file::path& pathDll);

      virtual ::e_status _defer_beta_use_unicode_utf8();

      virtual ::e_status _defer_enable_coder_mode();

      virtual bool _has_beta_use_unicode_utf8();

      virtual bool _is_visual_studio_installed();

      virtual bool _is_tortoise_git_installed();

      virtual bool _is_msys2_installed();

      //virtual void _defer_install_msys2_package(const ::scoped_string & scopedstr);

      //virtual bool _has_msys2_command(const ::scoped_string & scopedstr);

      //virtual void _install_msys2_package(const ::scoped_string & scopedstr);

      bool _is_strawberry_perl_installed();


      bool _is_coder_mode_enabled();

      void _enable_coder_mode(bool bEnable = true);

#endif

      bool _is_code_exe_user_path_environment_variable_ok(::string *pstrCorrectPath=nullptr, const char * pszPath = nullptr) override;

#if defined(WINDOWS_DESKTOP) || defined(MACOS) || defined(LINUX)

      bool _is_smart_git_installed() override;

#endif

      bool _is_google_drive_installed() override;

      //bool _is_dropbox_installed() override;

      bool _is_onedrive_installed() override;

      //void calculate_dropbox_installed() override;

      void calculate_onedrive_installed() override;

      bool _is_google_chrome_installed() override;

      bool _is_opera_browser_installed() override;

      bool _is_visual_studio_code_installed() override;

      bool _is_git_credential_manager_installed() override;

      bool _is_jetbrains_clion_installed() override;

      bool _is_shell_patched() override;

#ifndef UNIVERSAL_WINDOWS

      ::array <::serial::port_info> list_serial_ports() override;

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
#if defined(__BSD__) || defined(__APPLE__)

      void arp_a(void *p, void(*callback)(void * p, unsigned int uIp, const char * status)) override;

#endif

      ::string eol() override;


      int building_core_count(bool bDedicatedBuilding) override;
      int performance_core_count() override;
      int efficiency_core_count() override;

      bool defer_component_factory(const ::scoped_string & scopedstrComponent) override;

      void detached_command(const ::scoped_string & scopedstrCommand, const ::file::path & pathLog) override;

//      virtual void * fetch_windowing_system_display();
//      virtual void windowing_system_async(const ::procedure & procedure);
//      virtual void windowing_system_display_error_trap_push(int i);
//      virtual void windowing_system_display_error_trap_pop_ignored(int i);




      bool _get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle) override;
      bool _get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle) override;

      void realize(::particle_pointer pparticle) override;
      virtual ::string dynamic_library_suffix();

   };


} // namespace linux



