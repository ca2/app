//
// Created by camilo on 2024-10-24 22:26 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/constant/application_capability.h"
#include "acme/constant/element.h"
#include "acme/exception/__string.h"
#include "acme/operating_system/security_attributes.h"
#include "acme/platform/serial_shared.h"
//#include "acme/exception/status.h"
////#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/prototype/pointer.h"
#include "acme/prototype/collection/atom_array.h"
#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/time/time.h"
#include "shell.h"


namespace platform

{

   struct CLASS_DECL_ACME acme_node_layer_t
   {

      //bool m_bDropboxCalculated;
      //bool m_bDropbox;
      //::file::path m_pathDropbox;


      bool m_bOneDriveCalculated;
      bool m_bOneDrive;
      ::file::path m_pathOneDrive;


   protected:


      //::procedure_array            m_routineaPost;


   public:


      union
      {

         unsigned long long m_uNodeFlags;

         bool m_bHasNodePostedSystemInitialRequest: 1;

      };


      htask m_htaskSystem;
      //::apex::node* m_papexnode;
      //::aura::node* m_pauranode;

      //::acme_posix::node* m_pAcmePosix;
      //::apex_posix::node* m_pApexPosix;
      //::aura_posix::node* m_pAuraPosix;

      //::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::node* m_pAcmePlatform;
      //::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(apex_)::node* m_pApexPlatform;
      //::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)::node* m_pAuraPlatform;


      //::particle_pointer                              m_pparticleQuit;


      //::particle_pointer                              m_pparticleStandardIOSynchronization;


      bool m_bCallStackInitialized;
      bool m_bUpdateCallStack;


      string m_strTheme;
      string m_strIconTheme;

      map_base<enum_character_set, ::string> m_mapCharacterSetDefaultSampleText;
      string_map_base<enum_character_set> m_mapCharacterSetEnum;

      ::os_theme_colors* m_pthemecolors;

      //:: IDENTIFIER_PREFIX_OPERATING_SYSTEM(_node)::node *  m_pNode;


      //::windowing_win32::node *                             m_pWindowingWin32Node;
      //::windowing_universal_windows::node *                 m_pWindowingUniversalWindowsNode;


      //::windowing_x11::node *                               m_pNodeX11;
      //::windowing_xcb::node *                               m_pNodeXcb;
      //::node_gtk3::node* m_pNodeGtk3;
      //::node_gtk4::node* m_pNodeGtk4;
      //::node_gtk_based::node* m_pNodeGtkBased;
      //::node_kde5::node* m_pNodeKDE5;
      //::node_kde6::node* m_pNodeKDE6;
      //::node_xfce::node* m_pNodeXfce;
      //::operating_ambient_gtk_based::node* m_pNodeDesktopEnvironmentGtkBased;
      //::desktop_environment_kde::node* m_pNodeDesktopEnvironmentKDE;
      //::desktop_environment_xfce::node* m_pNodeDesktopEnvironmentXfce;

      //bool                                                m_bUserDarkMode;

      //bool                                                  m_bOperatingSystemDarkMode;
      //int                                                   m_iWeatherDarkness;
      ::file::path m_pathModule;


      enum_application_capability_array m_eapplicationcapabilitya;
      string_map_base<::pointer<::acme::exclusive>> m_mapExclusive;


   };


   class CLASS_DECL_ACME acme_node_layer
   {
   public:


      virtual ::string get_file_type_identifier(const ::file::path& path);


      virtual void call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir,
                              ::e_display edisplay, bool bPrivileged, unsigned int* puiPid = nullptr);


      virtual void call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir,
                             ::e_display edisplay, const class time& timeTimeout, ::property_set & set, int* piExitCode);


      virtual ::process_identifier_array module_list_file_processes_identifiers(const ::scoped_string& scopedstr);


      virtual ::enum_id key_command(::user::enum_key ekey, ::user::key_state* pkeystate);
      //virtual ::file::path synchronously_request_document_folder();

      virtual void notify_system_started();
      //idaPid = pnode->(path, false);


      virtual ::particle_pointer create_mutex();


      virtual void initialize(::particle* pparticle);


      virtual void node_application_on_status(const_char_pointer pszStatus, void* p = nullptr, long long hi = 0);


      //virtual ::particle_pointer create_quit_particle(::pointer<::platform::node>& pnode);

      //virtual ::particle_pointer create_quit_particle();
      virtual ::file::path get_default_base_integration_folder();


      ///virtual void implement(::pointer<::platform::node>& pnode, ::pointer<::platform::system> & psystem);

      virtual void node_main();


      virtual void node_implement_main();


      virtual void on_app_activated(::user::activation_token * puseractivationtoken);


      virtual void on_system_main();


      virtual void start_application(::pointer<::platform::node>& pnode);


      //virtual void acme_application_main(::platform::system* psystem);


      virtual void _will_finish_launching();
      
      virtual void _did_finish_launching();


      //virtual void element_quit_post_quit();


      virtual string audio_get_default_implementation_name();


      virtual string multimedia_audio_get_default_implementation_name();


      virtual string multimedia_audio_mixer_get_default_implementation_name();


      virtual string veriwell_multimedia_music_midi_get_default_implementation_name();


      virtual void _launch_macos_app(const ::scoped_string & scopedstrAppFolder);


      virtual void _launch_macos_app_args(const ::scoped_string & scopedstrAppFolder, const ::scoped_string & scopedstrArgs);


      //void on_initialize_particle() override;

      virtual void initialize_memory_counter();


      virtual void system_main();


      virtual void reboot();


      virtual void defer_show_system_menu(::user::mouse* pmouse);


      virtual void install_crash_dump_reporting(const ::scoped_string & scopedstrModuleNameWithTheExeExtension);


      virtual ::file::path module_path_source();


      //virtual ::file::path module_path_seed();
      //virtual ::file::path module_path_origin();
      //::file::path update_module_path();


      virtual ::pointer<::mutex> create_local_named_mutex(::particle* pparticleContext, bool bInitiallyOwned,
                                                          const ::scoped_string & scopedstrName,
                                                          security_attributes* psecurityattributes = nullptr);


      virtual ::pointer<::mutex> create_global_named_mutex(::particle* pparticleContext, bool bInitiallyOwned,
                                                           const ::scoped_string & scopedstrName,
                                                           security_attributes* psecurityattributes = nullptr);


      virtual ::pointer<::mutex> open_local_named_mutex(::particle* pparticleContext, const ::scoped_string & scopedstrName);


      virtual ::pointer<::mutex> open_global_named_mutex(::particle* pparticleContext, const ::scoped_string & scopedstrName);


      virtual ::pointer<::mutex> get_install_mutex(::particle* pparticleContext, const ::scoped_string & scopedstrPlatform,
                                                   const ::scoped_string & scopedstrSuffix);


      virtual ::pointer<::acme::exclusive> _get_exclusive(::particle* pparticleContext, const ::scoped_string & scopedstrName,
                                                          ::security_attributes* psecurityattributes = nullptr);


      virtual ::pointer<::acme::exclusive> get_exclusive(::particle* pparticleContext, const ::scoped_string & scopedstrName,
                                                         ::security_attributes* psecurityattributes = nullptr);


      virtual bool erase_exclusive(const ::scoped_string & scopedstrName);


      virtual void release_exclusive();


      virtual bool exclusive_fails(::particle* pparticleContext, const ::scoped_string & scopedstrName,
                                   security_attributes* psecurityattributes = nullptr);


      virtual string app_id_to_app_name(const ::scoped_string & scopedstrAppId);


      virtual string app_id_to_executable_name(const ::scoped_string & scopedstrAppId);


      virtual bool is_application_installed(const ::file::path& pathExe, const ::scoped_string & scopedstrAppId, string& strBuild,
                                            const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration,
                                            const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


      virtual void set_application_installed(const ::file::path& pathExe, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrBuild,
                                             const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration,
                                             const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


      virtual ::file::path application_installer_folder(const ::file::path& pathExe, const ::scoped_string & scopedstrAppId,
                                                        const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration,
                                                        const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);


      virtual ::file::path get_application_path(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform,
                                                const ::scoped_string & scopedstrConfiguration);


      virtual ::file::path get_last_run_application_path_file(const ::scoped_string & scopedstrAppId);


      virtual ::file::path get_last_run_application_path(const ::scoped_string & scopedstrAppId);


      virtual void set_last_run_application_path(const ::scoped_string & scopedstrAppId);


      virtual ::file::path _module_path();


      //virtual void do_windowing_system_factory();


      //virtual bool memory_counter_on();

      //virtual ::file::path memory_counter_base_path();

      virtual void datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time);


      virtual int node_init_check(int* pi, char*** ppz);


      virtual void start_node();


      virtual void install_sigchld_handler();


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

      //virtual void os_set_user_theme(const ::scoped_string & scopedstrUserTheme);

      //virtual void os_process_user_theme(const ::scoped_string & scopedstrTheme);

      //virtual void os_process_user_icon_theme(const ::scoped_string & scopedstrIconTheme);

//      virtual bool set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrLocalImagePath,
//                                 ::acme::windowing::display* pwindowingdisplay);
//
//
//      virtual string get_wallpaper(::collection::index iScreen, ::acme::windowing::display* pwindowingdisplay);


      virtual string get_file_icon_path(const ::scoped_string & scopedstrPath, int iSize);


      virtual string get_file_content_type(const ::scoped_string & scopedstrPath);


      virtual int os_launch_uri(const ::scoped_string & scopedstrUri, char* pszError = NULL, int iBufferSize = 0);


//      virtual void enable_wallpaper_change_notification();


      virtual bool has_xcb();


      virtual void* get_os_xcb_connection();


      virtual bool is_wayland();


      //void _user_send(const ::procedure & procedure) override;
      //void _user_post(const ::procedure & procedure) override;

      //virtual void _user_send(::subparticle * psubparticle) override;
      //virtual void _user_post(::subparticle * psubparticle) override;

      //void post_procedure(const ::procedure & procedure) override;

      //void send_procedure(const ::procedure & procedure) override;

      virtual void defer_do_main_tasks();


      //virtual void user_post_quit();


      //virtual void node_quit();

      virtual bool should_launch_on_node(::topic* ptopic);


      virtual bool defer_launch_on_node(::topic* ptopic);


      virtual bool launch_on_node(::topic* ptopic);


      virtual string get_user_name();


      virtual void set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha);


      virtual void browse_for_folder(::file::path& pathFolder);


      virtual void browse_for_file(::file::path& path);


      virtual double get_time_zone();


      virtual string font_name(enum_font efont);


      //virtual string font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);


      virtual string file_memory_map_path_from_name(const ::scoped_string & scopedstrName);


      virtual enum_operating_system get_operating_system() const;


      //virtual ::user::enum_operating_ambient get_eoperating_ambient();
      //virtual ::user::enum_toolkit get_etoolkit();

      //virtual ::user::enum_operating_ambient calculate_edesktop();
      //virtual ::user::enum_toolkit calculate_etoolkit();

      //virtual ::string get_user_toolkit_id();

      virtual void launch_app(const ::scoped_string & scopedstr, const_char_pointer *argv, int iFlags);


      virtual ::file::path get_executable_path_by_app_id(const ::scoped_string& scopedstrAppId,
                                                         bool bSingleExecutableVersion);


      virtual ::file::path get_executable_path_by_app_id(const ::scoped_string& scopedstrRepos,
                                                         const ::scoped_string& scopedstrApp,
                                                         bool bSingleExecutableVersion);


      virtual void launch_app_by_app_id(const ::scoped_string& scopedstrAppId, bool bSingleExecutableVersion);


      virtual ::process_identifier create_process(const ::scoped_string & scopedstrCommandLine);


      virtual void run_silent(const ::scoped_string & scopedstrFunct, const ::scoped_string & scopedstrstrParams);


      virtual ::file::path_array_base process_identifier_modules_paths(::process_identifier processidentifier);


      virtual ::file::path_array_base modules_paths();


      virtual bool load_modules_diff(string_array_base& straOld, string_array_base& straNew, const ::scoped_string & scopedstrExceptDir);


      virtual ::process_identifier_array processes_identifiers();


      virtual ::process_identifier_array module_path_processes_identifiers(
         const ::scoped_string & scopedstrModulePath, bool bModuleNameIsPropertyFormatted);


      virtual ::file::path process_identifier_module_path(::process_identifier processidentifier);


      virtual string process_identifier_command_line(::process_identifier processidentifier);


      //virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array_base& stra);

      //virtual bool is_shared_library_busy(const string_array_base& stra);

      virtual bool process_contains_module(string& strImage, ::process_identifier processidentifier,
                                           const ::scoped_string & scopedstrLibrary);


      virtual ::process_identifier_array
      shared_library_process(string_array_base& straProcesses, const ::scoped_string & scopedstrLibrary);


      virtual bool is_process_running(::process_identifier processidentifier);


      virtual string get_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable);


      virtual string expand_environment_variables(const ::scoped_string& scopedstr);


      virtual void set_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable,
                                            const ::scoped_string& scopedstrValue);


      virtual void unset_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable);


      virtual string get_user_language();


      virtual ::pointer<security_attributes> get_application_exclusivity_security_attributes();


      virtual void register_spa_file_type(const ::scoped_string & scopedstrAppIdHandler);


      virtual bool low_is_app_app_admin_running(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);


      virtual void defer_start_program_files_app_app_admin(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);


      virtual void start_program_files_app_app_admin(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);


      virtual void get_folder_path_from_user(::file::path& pathFolder);


      //virtual ::string expand_environment_variables(const ::scoped_string & scopedstr);

      virtual ::file::path command_find_path(const ::scoped_string & scopedstrCommand);


      virtual void launch_application(::particle* pparticle, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrParams,
                                      int iBitCount);


      virtual void shell_open(const ::file::path& path, const ::scoped_string & scopedstrParams = "",
                              const ::file::path& pathFolder = {});


      //virtual void open_url(const ::scoped_string & scopedstrUrl);


      virtual void shell_execute_async(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams,
                                       const ::file::path& pathWorkingDirectory = {});


      virtual int shell_execute_sync(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams,
                                     const class time& timeTimeout = 1_minute,
                                     const ::file::path& pathWorkingDirectory = {});


      virtual void root_execute_async(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams,
                                      const ::file::path& pathWorkingDirectory = {});


      virtual int root_execute_sync(const ::scoped_string& scopedstrFile, const ::scoped_string& scopedstrParams,
                                    const class time& timeTimeout = 1_minute,
                                    const ::file::path& pathWorkingDirectory = {});


      //::file::path command_find_path(const ::scoped_string & scopedstrCommand);


      //virtual ::user::enum_operating_ambient calculate_edesktop();
      //
      //
      //virtual ::user::enum_operating_ambient get_eoperating_ambient();

      virtual void on_start_system();


      virtual void create_app_shortcut(::platform::application* papplication);


      virtual void report_exception_to_user(::particle* pparticle, ::exception& exception,
                                            const ::scoped_string & scopedstrMoreDetails);


      //virtual ::pointer<::conversation> create_new_message_box_conversation();

      //virtual ::pointer<::conversation> create_new_message_conversation();


      //virtual ::pointer < ::subparticle > create_message_box_sequencer(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon);


      //virtual void ::micro::message_box(::sequence < ::conversation > * psequence, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box& emessagebox);

      //virtual ::pointer < ::subparticle > create_message_sequencer(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon);


      virtual void shell_launch(const ::scoped_string & scopedstrAppId);


      virtual bool has_application_capability(::enum_application_capability ecapability) const;


      virtual void add_application_capability(const ::enum_application_capability_array& ecapabilitya);


      virtual void on_change_application_capability();


      //virtual void windowing_post(const ::procedure& procedure);


      virtual string get_local_mutex_name(const ::scoped_string & scopedstrAppId);


      virtual string get_local_id_mutex_name(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrId);


      virtual string get_global_mutex_name(const ::scoped_string & scopedstrAppId);


      virtual string get_global_id_mutex_name(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrId);


      //      virtual ::string get_call_stack();


      virtual ::process_identifier current_process_identifier();


      virtual bool stdin_has_input_events();


      virtual void flush_stdin_input_events();


      virtual void flush_stdin();


      virtual void defer_update_call_stack();


      //#if defined(__ANDROID__)
      //      virtual string unwind_call_stack(const ::scoped_string & scopedstrFormat = call_stack_default_format(), int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, int iCount = -1);
      //#else
      virtual int get_call_stack_default_frame_count();


      virtual void get_call_stack_frames(void** stack, int& frame_count);


      virtual string get_call_stack_trace(const ::scoped_string& scopedstrFormat = call_stack_default_format(),
                                          int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr,
                                          int iCount = -1);


      virtual string get_call_stack_trace(void** stack, int frame_count,
                                          const ::scoped_string& scopedstrFormat = call_stack_default_format(),
                                          int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr,
                                          int iCount = -1);


      //#endif
      virtual string _get_call_stack_trace(const ::scoped_string& scopedstrFormat = call_stack_default_format(),
                                           int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr,
                                           int iCount = -1);


      virtual string _get_call_stack_trace(void** stack, int frame_count,
                                            const ::scoped_string& scopedstrFormat = call_stack_default_format(),
                                            int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr,
                                            int iCount = -1);


        virtual ::string get_command_line();


      //virtual ::pointer<::acme::exclusive> get_exclusive(const ::scoped_string & scopedstr, const security_attributes & securityattributes = nullptr);


      virtual int get_current_processor_index();


      virtual int get_current_process_maximum_affinity();


      virtual int get_current_process_affinity_order();


      virtual unsigned long long translate_processor_affinity(int i);


      //CLASS_DECL_ACME string expand_env(const ::scoped_string & scopedstr);
      //CLASS_DECL_ACME string xxxget_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable);
      //CLASS_DECL_ACME string ca2_command_line();


      //virtual int process_get_status();
      //virtual void process_set_status(int iStatus);
      //virtual int * process_get_pargc();
      //virtual int process_get_argc();


      virtual bool set_process_priority(::enum_priority epriority);


      //virtual string time_binary_platform(const ::scoped_string & scopedstrPlatform);


      //
      //#if !defined(UNIVERSAL_WINDOWS)
      //
      //      //virtual int call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid = nullptr);
      //
      //      typedef int CALLSYNCONRETRY(int iTry, uptr dwParam);
      //
      //      typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;
      //
      //      //CLASS_DECL_ACME unsigned int call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set);
      //
      //#endif


      //#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__)
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


      //virtual string expand_env(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME string consume_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const ::string * & pszEndPtr);
      //CLASS_DECL_ACME bool is_command_line_parameter_true(string& strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, bool bDefault = false);
      //CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam);
      //CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDefault);
      //CLASS_DECL_ACME string get_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam);


      //virtual bool launch_command(const ::scoped_string & scopedstrCommand);


      virtual string process_configuration_name();


      virtual string time_binary_platform(const ::scoped_string & scopedstrPlatform);


      virtual string process_platform_name();


      //virtual string process_platform_name();
      virtual string process_version_dir_name();


      virtual ::file::path core_app_path(const ::scoped_string & scopedstrApp);


      //virtual bool is_shared_library_busy(::process_identifier processidentifier, const string_array_base & stra);
      //virtual bool is_shared_library_busy(const string_array_base & stra);


      // virtual bool launch_application(::particle * pparticle, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrParams, int iBitCount);


      //virtual bool shell_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams);
      //virtual bool shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout = 1_minute);

      //virtual bool root_execute_async(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams);
      //virtual bool root_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, const class time & timeTimeout = 1_minute);


      //CLASS_DECL_ACME bool os_init_application();
      //CLASS_DECL_ACME void os_term_application();


      virtual string executable_title_from_appid(const ::scoped_string & scopedstrAppId);


      //CLASS_DECL_ACME unsigned int get_current_process_id();


      //virtual string process_version_dir_name();


      virtual int is_debug_build();


      virtual int is_release_build();


      //virtual bool succeeded(const ::error_code& errorcode);
      //virtual bool failed(const ::error_code& errorcode);


      virtual void _node_file_dialog(::file::file_dialog* pdialog);


      virtual void _node_folder_dialog(::file::folder_dialog* pdialog);


      virtual ::pointer<::file::file_dialog> node_file_dialog();


      virtual ::pointer<::file::folder_dialog> node_folder_dialog();


      virtual ::file::path library_file_name(const ::scoped_string& scopedstr);


      virtual ::string default_component_implementation(const ::scoped_string& scopedstrComponentName);


      virtual void integration_factory();


      //virtual void unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip);


      virtual ::string get_user_permanent_environment_variable(const ::scoped_string& scopedstr);


      virtual ::string get_system_permanent_environment_variable(const ::scoped_string& scopedstr);


      virtual void set_user_permanent_environment_variable(const ::scoped_string& scopedstr,
                                                           const ::scoped_string& strPayload,
                                                           bool bNoSystemNotify = false);


      virtual void system_notify_environment_variable_change();


      virtual void update_process_environment_variables();


      virtual void set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string& scopedstrCommand);


      virtual ::string operating_system_store_release();


      virtual ::pointer<::operating_system::summary> operating_system_summary();


      //virtual void module_path_main_window_post_close(const ::scoped_string & scopestr);


      virtual ::pointer<::operating_system::application> module_path_application(const ::scoped_string& scopestr);


      virtual ::pointer<::operating_system::application> process_identifier_application(
         ::process_identifier processidentifier);


      virtual ::pointer<::operating_system::application> application_predicate(
         const ::function<bool(::operating_system::application* papplication)>& function);


      virtual ::string get_character_set_default_sample_text(enum_character_set echaracterset);


      virtual void load_character_set_default_sample_text();


      virtual void play_sound(const ::file::path& path);


      //virtual void speak(const ::scoped_string& scopedstr);

      virtual ::string operating_system_application_version();




      virtual bool is_application_running_good_effort(const ::scoped_string& scopedstrRepos,
                                                      const ::scoped_string& scopedstrApp);


      virtual bool are_framework_shared_libraries_busy(const ::scoped_string& scopedstrRepos,
                                                       const ::scoped_string& scopedstrApp);
                                                       
      virtual bool are_any_shared_libraries_mapped(const ::file::path_array_base & patha);


      virtual ::string get_error_code_message(const ::error_code& errorcode);


      virtual bool defer_enumerate_protocol(::file::listing_base& listing);


      virtual bool defer_process_protocol_path(::file::path& path);


      //void finalize() override;

      //virtual string get_command_line();

      //virtual void reboot();
      virtual void shutdown(bool bPowerOff);


      virtual void terminate_processes_by_title(const ::scoped_string & scopedstrName);


      //#ifdef WINDOWS
      //      virtual ::file::path get_module_path(HMODULE hmodule);
      //#endif

      virtual ::process_identifier_array module_path_processes_identifiers(const ::scoped_string& scopedstrName);


      virtual ::process_identifier_array title_processes_identifiers(const ::scoped_string& scopedstrName);


      //virtual ::process_identifier_array processes_identifiers();
      //virtual ::file::path process_identifier_module_path(::process_identifier dwPid);


      //virtual ::process_identifier current_process_identifier();

      virtual ::payload connection_settings_get_auto_detect();


      virtual ::payload connection_settings_get_auto_config_url();

      virtual void open_internet_link_in_browser(const ::scoped_string& scopedstrUrl,
                                                 const ::scoped_string& scopedstrBrowser,
                                                 const ::scoped_string& scopedstrProfile = {}, const ::scoped_string & scopedstrTarget = {});

      virtual void open_internet_link(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrProfile = {}, const ::scoped_string & scopedstrTarget = {});


      virtual void local_machine_set_run(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable,
                                         const ::scoped_string & scopedstrArguments, bool bSet);


      virtual void local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable,
                                              const ::scoped_string & scopedstrArguments, bool bSet);


      virtual void current_user_set_run(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable,
                                        const ::scoped_string & scopedstrArguments, bool bSet);


      virtual void current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path& pathExecutable,
                                             const ::scoped_string & scopedstrArguments, bool bSet);


      virtual void defer_register_ca2_plugin_for_mozilla();


      virtual void file_extension_get_open_with_list_keys(string_array_base& straKey, const ::scoped_string& scopedstrExtension);


      virtual void file_extension_get_open_with_list_commands(string_array_base& straCommand, const ::scoped_string& scopedstrExtension);


      virtual void file_association_set_default_icon(const ::scoped_string& scopedstrExtension,
                                                     const ::scoped_string& scopedstrExtensionNamingClass,
                                                     const ::file::path & pathIconPath);


      virtual void file_association_set_shell_open_command(const ::scoped_string& scopedstrExtension,
                                                           const ::scoped_string& scopedstrExtensionNamingClass,
                                                           const ::file::path & pathExecutable,
                                                           const ::scoped_string & scopedstrParam);


      virtual void file_association_get_shell_open_command(const ::scoped_string& scopedstrExtension,
                                                           string& strExtensionNamingClass, string& strCommand,
                                                           string& strParam);


      virtual void native_full_web_browser(const ::scoped_string & scopedstr);


      virtual void native_modern_web_browser(const ::scoped_string & scopedstr);


      virtual void enable_service();


      virtual void disable_service();


      virtual void start_service();


      virtual void stop_service();


      virtual void enable_service(const ::scoped_string & scopedstrServiceName, const ::scoped_string & scopedstrDisplayName,
                                  const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrUser = "",
                                  const ::scoped_string & scopedstrPass = "");


      virtual void disable_service(const ::scoped_string & scopedstrServiceName);


      virtual void start_service(const ::scoped_string & scopedstrServiceName);


      virtual void stop_service(const ::scoped_string & scopedstrServiceName);


      //#ifdef WINDOWS
      //      virtual DECLSPEC_NO_RETURN void raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags = EXCEPTION_NONCONTINUABLE);
      //#endif

      virtual bool is_remote_session();


      virtual void set_file_status(const ::file::path& path, const ::file::file_status& status);


      //virtual void edit_link_target(const ::file::path & path, const ::file::path & pathLink);
      //virtual void edit_link_folder(const ::file::path & path, const ::file::path & pathLink);
      //virtual void edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink);
      //   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);
      virtual bool has_alias_in_path(const ::scoped_string& scopedstr, bool bNoUI = false, bool bNoMount = false);


      virtual bool is_alias(const ::file::path& path);


      virtual void initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch);


      //virtual void set_dark_mode(bool bDarkMode);

      virtual void file_open(const ::file::path& path, const ::scoped_string & scopedstrParams = "",
                             const ::file::path& pathFolder = "");


      virtual void hidden_start(const ::file::path& path, const ::scoped_string & scopedstrParams = "",
                                const ::file::path& pathFolder = "");


      virtual void hidden_run(const class time& timeWait, const ::file::path& path, const ::scoped_string & scopedstrParams = "",
                              const ::file::path& pathFolder = "");


      virtual string get_default_browser();


      virtual void get_default_browser(string& strId, ::file::path& path, string& strParam);


      virtual void set_default_browser();


      virtual void set_file_extension_mime_type(::get_file_extension_mime_type* pgetfileextensionmimetype);


      virtual void set_file_extension_mime_type(string_array_base& straExtension, string_array_base& straMimeType);


      virtual void register_user_auto_start(::platform::application* papplication, const ::scoped_string & scopedstrArguments,
                                            bool bRegister);


      virtual bool is_user_auto_start(const ::scoped_string & scopedstrAppId);


      virtual ::file::path get_app_path(const ::scoped_string & scopedstrApp);


      virtual void on_process_request(::request* prequest);


      /// set["file_filter_specs"] : string array of file extensions (with dot)
      /// set["file_filter_names"] : string array of the file extensions titles
      /// set["default_file_extension"] : default file extension (with dot)
      /// set["folder"] : folder path
      /// set["file_name"] : in/out file name
      //virtual void browse_file_open(::property_set & set);

      /// set["file_filter_specs"] : string array of extensions (with dot)
      /// set["file_filter_names"] : string array of the file extensions titles
      /// set["default_file_extension"] : default file extension (with dot)
      /// set["folder"] : folder path
      /// set["file_name"] : in/out file name
      //virtual void browse_file_save(::property_set & set);

      /// set["folder"] : in/out folder path
      //virtual void browse_folder(::property_set & set);

      /// set["folder"] : in/out folder path
      //virtual void browse_file_or_folder(::property_set & set);


      virtual void list_process(::file::path_array_base& patha, ::process_identifier_array& uaPid);


      ::file::path_array_base list_process_path();


      //virtual ::icon_pointer load_icon(const ::payload & payloadFile);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

      virtual void broadcast_environment_variable_change();


      virtual void set_this_application_as_default_for_file_extension(const ::scoped_string & scopedstrExtension);


      string get_file_extension_mime_type(const ::scoped_string & scopedstrExtension);


#ifdef LINUX

      virtual enum_linux_distribution get_linux_distribution() const;
//#ifdef LINUX

  //    inline enum_linux_distribution get_linux_distribution() const;

      virtual void calculate_linux_distribution();

#endif

#if !defined(WINDOWS)
      virtual string_array_base cmdline_from_pid(::process_identifier processidentifier);
      virtual atom_array app_get_pid(const ::scoped_string & scopedstrModuleName);

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


      virtual ::e_status _defer_enable_coder_mode();


      virtual bool _has_beta_use_unicode_utf8();


      virtual bool _is_visual_studio_installed();


      virtual bool _is_tortoise_git_installed();


      virtual bool _is_msys2_installed();


      //virtual void _defer_install_msys2_package(const ::scoped_string & scopedstr);

      //virtual bool _has_msys2_command(const ::scoped_string & scopedstr);

      //virtual void _install_msys2_package(const ::scoped_string & scopedstr);

      virtual bool _is_strawberry_perl_installed();


      virtual bool _is_coder_mode_enabled();


      virtual void _enable_coder_mode(bool bEnable = true);

#endif

      virtual bool _is_code_exe_user_path_environment_variable_ok(::string* pstrCorrectPath = nullptr,
                                                                  const_char_pointer pszPath = nullptr);

#if defined(WINDOWS_DESKTOP) || defined(MACOS) || defined(LINUX)

      virtual bool _is_smart_git_installed();

#endif

      virtual bool _is_google_drive_installed();


      //virtual bool _is_dropbox_installed();


      virtual bool _is_onedrive_installed();


      //virtual void calculate_dropbox_installed();


      virtual void calculate_onedrive_installed();


      virtual bool _is_google_chrome_installed();


      virtual bool _is_opera_browser_installed();


      virtual bool _is_visual_studio_code_installed();


      virtual bool _is_git_credential_manager_installed();


      virtual bool _is_jetbrains_clion_installed();


      virtual bool _is_shell_patched();

#ifndef UNIVERSAL_WINDOWS

      virtual ::array<::serial::port_info> list_serial_ports();

#endif

      //#if !defined(UNIVERSAL_WINDOWS)
      //
      //
      //      //virtual string module_path_from_pid(::process_identifier processidentifier);
      //      //virtual atom_array module_path_get_pid(const ::scoped_string & scopedstrModuleName, bool bModuleNameIsPropertyFormatted = true);
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
      //      //virtual bool process_contains_module(string & strImage, ::process_identifier processidentifier, const ::scoped_string & scopedstrLibrary);
      //      //virtual void shared_library_process(dword_array & dwa, string_array_base & straProcesses, const ::scoped_string & scopedstrLibrary);
      //#endif
#if defined(__BSD__) || defined(__APPLE__)

      virtual void arp_a(void *p, void(*callback)(void * p, unsigned int uIp, const_char_pointer status));

#endif

      virtual ::string eol();


      virtual int building_core_count(bool bDedicatedBuilding);


      virtual int performance_core_count();


      virtual int efficiency_core_count();


      virtual bool defer_component_factory(const ::scoped_string& scopedstrComponent);


      virtual void detached_command(const ::scoped_string& scopedstrCommand, const ::file::path& pathLog);


      //      virtual void * fetch_windowing_system_display();
      //      virtual void windowing_system_async(const ::procedure & procedure);
      //      virtual void windowing_system_display_error_trap_push(int i);
      //      virtual void windowing_system_display_error_trap_pop_ignored(int i);


      virtual bool _get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle& rectangle);


      virtual bool _get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle& rectangle);


      virtual void realize(::particle_pointer pparticle);


      virtual ::string get_computer_name();


      virtual ::string system_name();
      virtual ::string system_release();
      virtual ::string system_architecture();


      virtual void protocol_set_data(const ::file::path & path, const ::block & block);
      virtual ::memory protocol_get_data(const ::file::path & path);


      virtual void on_protocol_set_data(const ::scoped_string & scopedstrProtocol, const ::scoped_string & scopedstrPath, const ::block & block);
      virtual ::memory on_protocol_get_data(const ::scoped_string & scopedstrProtocol, const ::scoped_string & scopedstrPath);


      virtual void post_media_store_operation(::data::block * pdatablock);


   };


} // namespace platform
