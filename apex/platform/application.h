// application back to apex namespace by camilo on 2022-09-17 18:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "context.h"
//#include "application_exit.h"
#include "acme/constant/exclusive_instance.h"
#include "apex/database/client.h"
#include "apex/networking/application/application_handler.h"
//#include "acme/parallelization/semaphore.h"
#include "apex/platform/context.h"
#include "acme/platform/application.h"
//#include "acme/prototype/mathematics/scalar.h"
#include "apex/progress/real.h"


namespace apex
{


   class CLASS_DECL_APEX application :
      virtual public ::platform::application,
      virtual public ::apex::context,
      virtual public scalar_source,
      virtual public ::database::client,
      virtual public ::networking::application_handler
   {
   public:


      //       //__creatable(application);
      //
      //       void * m_pnativeapp;
      //
      //       ::string m_strNetworkingApplicationHostname;
      //       //class application_impl *                     m_pappimpl;
      //
      //       // 2020-01-25: removing from ::apex::system, placing here (at ::context)
      //       // 2020-07-23: now at ::application
      //       ::pointer<::user::language_map>              m_puserlanguagemap;
      //
      //       //::pointer<::apex::application>             m_pappParent;
      //       string                                       m_strBaseSupportId;
      //       string                                       m_strDatabaseAppId;
      //       string                                       m_strRelativeFolder;
      //       string                                       m_strInstallTraceLabel;
      //       string                                       m_strInstallBuild;
      //       string                                       m_strHttpUserAgentToken;
      //       string                                       m_strHttpUserAgentVersion;
      //       bool                                         m_bRequiresInstallation;
      //
      //       bool                                         m_bReadStringTable;
      //
      //       ::pointer<class ::application_menu>          m_papplicationmenu;
      //       //::pointer<::apex::menu>                 m_pmainmenu;
      //
      //       //::pointer<::game::game>                    m_pgame;
      //
      //       ::pointer<::user::interaction_base>                 m_puiCurrent;
      //       bool                                         m_bContextTheme;
      //
      // // #if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
      // //       bool                                         m_bSnLauncheeSetup;
      // // #endif
      //       //semaphore                                    m_semCompiler;
      //       // former ::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV
      //       string_array                                 m_straActivationMessage;
      //
      //       ::u32                                        m_dwInstallGoodToCheckAgain;
      //
      //       bool                                         m_bAppHasInstallerProtected;
      //       bool                                         m_bAppHasInstallerChangedProtected;
      //       ::pointer<::install::installer>              m_pinstaller;
      //
      //       particle_address_array                       m_particleaddressaEventHook;
      //
      //       bool                                         m_bAttendedFirstRequest;
      //
      //       //bool                                       m_bAgreeExit;
      //       //bool                                       m_bAgreeExitOk;
      //       //bool                                       m_bFranceExit;
      //
      //       bool                                         m_bEnableAutoStartOption;
      //       bool                                         m_bInterprocessCommunication;
      //       ::pointer<::interprocess::communication>     m_pinterprocesscommunication;
      //       ::pointer<::interprocess::handler>           m_pinterprocesshandler;
      //       //::pointer<service>                         m_pservice;
      //
      //       //::string_array                               m_straInterprocessCommunicationPendingHandleUri;
      //
      //
      //       // apex commented
      //       //::pointer < ::mutex >                                         m_pmutexFrame;
      //       //::pointer<::user::interaction_pointer_array> m_puiptraFrame;
      //
      //       enum_thread_context                          m_ethreadcontextClose;
      //
      //       enum_exclusive_instance                      m_eexclusiveinstance;
      //
      //       bool                                         m_bService;
      //
      //       bool                                         m_bUpdateMatterOnInstall;
      //
      //       //::user::interaction *                      m_puiMainContainer;
      //
      //       string_table                                 m_stringtable;
      //       string_table                                 m_stringtableStd;
      //       atom_map < string >                            m_stringmap;
      //
      //       atom_map < ::pointer<::channel >>              m_mapNotify;
      //
      //       string                                       m_strLicense;
      //
      //       i32                                          m_iWaitCursorCount;         // for wait cursor (>0 => waiting)
      //
      //       //::pointer<::simpledb::server>              m_psimpledb;
      //
      //       //::userex::pane_tab_impact *                m_pmainpane;
      //
      //
      //       string                                       m_strHelpFilePath;
      //
      //       //#ifdef WINDOWS
      //       //
      //       //      HGLOBAL                                         m_hDevMode;             // printer Dev Mode
      //       //      HGLOBAL                                         m_hDevNames;            // printer Device Names
      //       //
      //       //#endif
      //
      //       u32                                          m_dwPromptContext;        // help action_context override for message box
      //       // LKG
      //       u32                                          m_dwPolicies;            // block for storing boolean system policies
      //
      //       // Support for Shift+F1 help mode.
      //       // true if we're in SHIFT+F1 mode.
      //       bool                                         m_bHelpMode;
      //
      //       //::userex::pane_tab_impact *                m_ppaneimpactMain;
      //
      //       string                                       m_strProfileName;
      //
      //       //#ifdef WINDOWS
      //       //      ATOM                                 m_atomApp;
      //       //      ATOM                                 m_atomSystemTopic;   // for DDE open
      //       //#endif
      //
      //       ::u32                                        m_nNumThumbnailPages; // number of default printed pages
      //
      //       string                                       m_strId;
      //
      //       i32                                          m_iResourceId;
      //
      //       //::pointer<::experience::department>        m_pexperience;
      //       //::pointer<::apex::theme>                   m_ptheme;
      //
      //
      //       string_array                                 m_straAppInterest;
      //
      //       ::pointer<::service_handler>                 m_pservicehandler;
      //
      //       ::pointer<::networking::application>         m_pnetworkingapplication;
      //
      //       ::string_map < ::pointer < ::fs::folder_sync > >  m_fsfoldersyncmap;

      application();


      ~application() override;


#ifdef DEBUG

      ::i64 increment_reference_count() override;
      ::i64 decrement_reference_count() override;

#endif
      void initialize(::particle* pparticle) override;


      void on_set_platform() override;


      virtual ::file::path cloud_protocol();


      //void on_initialize_application(::main* pmain) override;
      //// void assert_ok() const override;
      //// void dump(dump_context & dumpcontext) const override;
      void main() override;

      virtual string __get_text(string str);


      ::pointer<::fs::folder_sync> fs_folder_sync(const ::scoped_string& scopedstr);


      //virtual void process_command_line(command_line* pcommandline);


      //virtual ::user::style* get_user_style() const;
      //virtual bool app_data_get(const ::atom & atom, stream & os) override;
      //virtual bool app_data_set(const ::atom & atom, stream & is) override;

      //virtual bool app_data_set(const ::atom & atom, object & obj) override;
      //virtual bool app_data_get(const ::atom & atom, object & obj) override;

      //      virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::database::key calc_data_key() override;


      //virtual string load_podata(string strLang, bool bOnlyHeader);

      virtual string load_string(const ::atom& atom);


      virtual bool load_string(string& str, const ::atom& atom);


      virtual void load_string_table();


      virtual bool load_cached_string(string& str, const ::atom& atom, bool bLoadStringTable);


      virtual bool load_cached_string_by_id(string& str, const ::atom& atom, bool bLoadStringTable);


      virtual void load_string_table(const string& pszApp, const string& pszId);


      virtual bool is_application() const override;


      virtual bool is_system() const override;


      virtual bool is_session() const override;


      bool is_service() const override;


      bool is_user_service() const override;


      virtual ::pointer<::service> create_service();


      virtual void on_service_request(::request* prequest);


      //virtual ::simpledb::server * simpledb();
      virtual ::database::server* dataserver();


      //virtual void verb();


      virtual bool Ex2OnAppInstall();


      virtual bool Ex2OnAppUninstall();


      //virtual void init_application();

      void init1() override;


      void init2() override;


      void init3() override;


      void init() override;


      void init_instance() override;


      virtual void defer_interprocess_communication();


      virtual void run() override;


      //virtual void     main() override;
      virtual void on_run();


      void destroy() override;


      //virtual bool initial_check_directrix() override;
      void os_native_bergedge_start() override;


      //virtual bool on_application_menu_action(const ::string & pszCommand);


      void term() override;


      void term_application() override;


      void show_about_box() override;


      virtual ::pointer<::innate_ui::icon> innate_ui_icon(const ::size_i32& size);


      virtual void init_fs_set(::fs::set* pfsset);


      //virtual bool InitApplication();


      void do_install() override;


      void do_uninstall() override;


      void on_install() override;


      void on_uninstall() override;


      virtual void enable_service();


      virtual void disable_service();


      virtual void update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path& pszRoot,
                                    const string& pszRelative);


      virtual void update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path& pszRoot,
                                    const string& pszRelative, const ::string& strLocale, const ::string& strStyle);


      //virtual void SetCurrentHandles() override;

      //virtual void france_exit();


      virtual void process_exception(const ::exception& e) override;


      //virtual ::pointer<::apex::application>assert_running(const ::string & pszAppId) override;

      virtual bool is_running();


      //bool pump_runnable() override;

      virtual void add_activation_message(const ::string& strMessage);


      virtual bool has_activation_message() const;


      virtual void handle_posted_activation_message();

      bool task_iteration() override;




      //virtual void on_request(::request * prequest) override;


      virtual bool assert_user_logged_in();


      virtual string matter_as_string(const ::string& pszMatter, const ::string& pszMatter2 = nullptr);


      //virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);
      //virtual bool do_prompt_file_name(::payload& payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);
      //user virtual bool do_prompt_file_name(::payload& payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);


      virtual void process_message_filter(i32 code, ::message::message * pmessage) override;


      virtual void DoWaitCursor(i32 nCode); // 0 => restore, 1=> begin, -1=> end

      void _001TryCloseApplication() override;


      virtual void _001CloseApplication();


      virtual bool try_close_application();


      virtual bool can_close_application();


      virtual void close_application();


      virtual string get_license_id();


      void process_init() override;


      virtual string get_mutex_name_gen();


      //virtual ::user::interaction * user_interaction_from_oswindow(::windowing::window * pwindow);


      virtual void hotplugin_host_starter_start_sync(const ::string& pszCommandLine, ::apex::application* papp,
                                                     hotplugin::host* phost, hotplugin::plugin* pplugin = nullptr);


      virtual void hotplugin_host_host_starter_start_sync(const ::string& pszCommandLine, ::apex::application* papp,
                                                          hotplugin::host* phost, hotplugin::plugin* pplugin = nullptr);


      //virtual bool is_local_data() override;

      class ::application_menu* application_menu() override;


      virtual ::file::path appconfig_folder();


      //// void assert_ok() const override;
      //// void dump(dump_context & dumpcontext) const override;


      //virtual bool app_data_set(const ::atom & atom, stream & os);
      //virtual bool app_data_get(const ::atom & atom, stream & is);

      virtual bool app_data_set(const ::atom& atom, ::object& obj);


      virtual bool app_data_get(const ::atom& atom, ::object& obj);


      void install_message_routing(::channel* pchannel) override;


      virtual string dialog_box(const ::string& pszMatter, property_set& propertyset);


      virtual void application_menu_update();


      //virtual string calc_data_key();


      //virtual void notify_changed(const ::atom & atom, const ::action_context & action_context);


      virtual ::file::path local_application_path();


      virtual ::file::path local_application_home_path();


      //virtual void destroy() override;


      //virtual void release_parents() override;
      ::property_object* parent_property_set_holder() const override;


      //virtual bool is_set_finish() const override;


      virtual void on_change_theme();


      virtual string get_theme();


      //virtual bool start_application(::request * prequest);


      //virtual void release_children() override;
      //virtual void merge_command_line(::create * pcommand);

      //   virtual void merge(::handler * phandler);

      //virtual void record(::create * pcommand);

      //virtual void on_event(::u64 u, ::particle * pparticle) override;
      //virtual ::pointer<::thread_toolset>create_thread_toolset(::enum_task_tool etool);


      //// ca2verses
      //// os_* functions generally
      //// reserves a lot of surprises from each
      //// operating system specific behavior
      //virtual void auto pmessagebox = __initialize_new ::message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());

      //pmessagebox->sync();


      //virtual void ui_message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
      //virtual void ui_message_box_timeout(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const class ::time& timeTimeOut = time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //using ::platform::context::message_box;
      //virtual void message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
      //virtual void message_box_timeout(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const class ::time& timeTimeOut = time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      virtual void on_file_new();


      virtual string title();


      virtual string_array get_categories();


      virtual void defer_create_keyboard();


      //virtual bool set_keyboard_layout(const ::string & pszPath, const ::action_context & action_context);


      virtual bool enable_application_events(::particle* pparticle, bool bEnable);


      virtual bool is_equal_file_path(const ::file::path& path1, const ::file::path& path2);


      //virtual bool process_exception(const ::exception & e) override;


      void set_has_installer(bool bSet);


      //virtual ::file::path defer_process_path(::file::path path);
      //virtual ::file::path full_process_path(::file::path path);

      //virtual void DoWaitCursor(i32 nCode); // 0 => restore, 1=> begin, -1=> end
      //virtual void show_wait_cursor(bool bShow = true);


      //virtual void process_message_filter(i32 code,::message::message * pmessage) override;

      virtual void on_thread_on_idle(::thread * pthread, ::i32 lCount) override;


      virtual void app_set(string strPath, string strValue);


      virtual string app_get(string strPath, string strDefault = "");


      //virtual bool Ex2OnAppInstall();
      //virtual bool Ex2OnAppUninstall();

      //virtual bool on_application_menu_action(const ::string & pszCommand);
      //virtual void _001CloseApplication();

      //virtual string get_license_id();

      virtual string get_version();


      //virtual ::pointer < ::interprocess::handler > create_interprocess_handler();

      //virtual void process_init();
      void process_term() override;


      //virtual void impl_process_init();
      //virtual void impl_init1();
      //virtual void impl_init2();
      //virtual void impl_init3();

      //virtual void impl_process_term();
      //virtual void impl_term1();
      //virtual void impl_term2();
      //virtual void impl_term3();

      //virtual void init1();
      //virtual void init2();
      //virtual void init3();

      void term1() override;


      void term2() override;


      void term3() override;


      virtual void init_task() override;


      //virtual void init_application();
      //virtual void term_application();
      virtual void term_task() override;


      //virtual void init_instance() override;
      void term_instance() override;


      //virtual void init();
      //virtual void term();

      virtual void notify_process_init();


      virtual void notify_init1();


      virtual void notify_init2();


      virtual void notify_init3();


      virtual void notify_term3();


      virtual void notify_term2();


      virtual void notify_term1();


      virtual void notify_process_term();


      // virtual bool is_installing();
      // virtual bool is_unstalling();

      //virtual string get_version();
      //virtual void     run() override;
      //virtual void     main() override;
      //virtual void     on_run();

      void on_before_launching() override;


      //virtual void os_native_bergedge_start();

      // virtual void pre_run();
      //virtual void application_pre_run();

      virtual void on_pos_run_thread() override;
      virtual void pos_run() override;
      virtual void application_pos_run() override;


      //virtual bool InitApplication();
      //virtual void TermApplication();

      //virtual bool on_install();
      //virtual bool on_uninstall();

      virtual bool system_add_app_install(const ::string& pszId, const ::string& pszBuild);


      //virtual void TermThread(HINSTANCE hInstTerm);

      //virtual void SetCurrentHandles();

      //virtual void set_env_var(const string & payload,const string & value);
      //virtual itask_t get_thread_id();


      virtual bool _001OnDDECommand(const ::string& pcsz);


      virtual void _001InitializeShellOpen();


      virtual void _001OnFileNew(::message::message* pmessage);


      virtual void get_temp_file_name_template(string& str, const ::string& lpszName, const ::string& pszExtension,
                                               const ::string& pszTemplate);


      virtual void get_temp_file_name(string& str, const ::string& lpszName, const ::string& pszExtension);


      inline ::service_handler* service_handler() const { return m_pservicehandler; }

      //virtual void on_service_request(::request * prequest);

      //virtual bool is_running();

      //virtual string get_mutex_name_gen();


      void ___property_set_test_001();


      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this ___new additional instance creation
      virtual void on_exclusive_instance_conflict(::request* prequest, bool& bHandled,
                                                  enum_exclusive_instance eexclusive, string strId);


      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this ___new additional instance creation
      virtual void on_exclusive_instance_local_conflict(::request* prequest, bool& bHandled);


      /// return true if this instance might continue execution
/// bHandled true if some action was done in response to this ___new additional instance creation
      virtual void on_exclusive_instance_local_conflict_id(::request* prequest, bool& bHandled, string strId);


      virtual void on_exclusive_instance_global_conflict(::request* prequest, bool& bHandled);


      /// return true if the external additional instance might continue execution
      /// bHandled true if some action was done in response to the external aaa_memory_new additional instance creation
      virtual void on_additional_local_instance(bool& bHandled, string strModule, int iPid, string strCommandLine);


      virtual void on_new_instance(string strModule, const ::atom& idPid);


      virtual string get_local_mutex_id();


      virtual string get_global_mutex_id();


      //virtual ::pointer< ::mutex > get_local_mutex();
      //virtual ::pointer< ::mutex > get_global_mutex();

      virtual string get_local_mutex_name();


      virtual string get_local_id_mutex_name();


      virtual string get_global_mutex_name();


      virtual string get_global_id_mutex_name();


      virtual bool check_exclusive(::request* prequest, bool& bHandled);


      virtual bool erase_exclusive(const ::string& strId);


      virtual bool exclusive_fails(const ::string& str, security_attributes* psecurityattributes = nullptr);


      virtual bool exclusive_erase(const ::string& str);


      virtual void release_exclusive();


      bool on_set_scalar(enum_scalar escalar, ::number number, int iFlags) override;


      ::number get_scalar_minimum(enum_scalar escalar) override;


      ::number get_scalar(enum_scalar escalar) override;


      ::number get_scalar_maximum(enum_scalar escalar) override;


      //bool safe_is_running();


      //virtual void on_request(::request * prequest) override;

      // name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
      // get/set serializables to user directory
      //template < typename TYPE >
      //bool gudo_get(const ::string & strKey, TYPE & t);

      //template < typename TYPE >
      //bool gudo_set(const ::string & strKey, const TYPE & t);


      //virtual bool assert_user_logged_in();

      void request(::request* prequest) override;


      //virtual void call_request(::request * prequest) override;


      //virtual void process_message(::user::message * base) override;

      virtual void message_handler(::message::message* pmessage) override;


      virtual string http_get_locale_schema(const ::string& pszUrl, const ::string& pszLocale,
                                            const ::string& pszSchema);


      //virtual void on_update_matter_locator() override;

      virtual bool platform_open_by_file_extension(::collection::index iEdge, const ::string& pszPathName,
                                                   ::request* prequest = nullptr);


      virtual bool platform_open_by_file_extension(::collection::index iEdge, ::request* prequest);


      virtual bool on_start_application();


      //#if !defined(LINUX)
      //
      //      virtual bool os_on_start_application();
      //
      //#endif

      DECLARE_MESSAGE_HANDLER(on_message_app_exit);


      DECLARE_MESSAGE_HANDLER(on_message_close);


      DECLARE_MESSAGE_HANDLER(on_command_display_about);


      // //virtual bool _001OnAgreeExit();


      //virtual void request_exit_application();
      //virtual void can_exit_application();
      void exit_application() override;


      //virtual void _001FranceExit();


      //virtual string lstr(const ::atom & atom, string strDefault = "") override;


      //virtual bool do_install();
      //virtual bool do_uninstall();


      //void request(::create * pcommand) override;
      //void on_create(::request * prequest) override;

      //      virtual void dispatch_user_message(::user::message * pusermessage);

      //virtual void throw_not_installed();

      //virtual void play_audio(::payload payloadFile, bool bSynch = false);

      virtual void post_critical_error_message(const ::string& pszMessage, bool bShowLog = true);


      virtual void show_critical_error_log();


      virtual string get_app_user_friendly_task_bar_name();


      //void signal(::signal * psignal) override;
      //void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual bool compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);

      //virtual bool compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6);

      //virtual void interactive_credentials(::account::credentials * pcredentials) override;

      virtual ::file::path get_executable_path();


      virtual string get_executable_extension();


      virtual string get_executable_title();


      virtual string get_executable_appid();


      virtual bool on_open_document_file(::payload payloadFile);


      virtual string get_app_id(string wstr);


      virtual void install_trace(const ::string& str);


      virtual void install_trace(double dRate);


      virtual void register_application_as_spa_file_type_handler();


      //virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration);
      //virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration);
      // virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration);


      virtual bool keyboard_focus_is_focusable(const ::user::interaction_base* pue);


      virtual bool keyboard_focus_OnSetFocus(::user::interaction_base* pue);


      //virtual ::user::interaction * main_window();

      //         virtual ::pointer<::user::message>get_message_base(MESSAGE * pmsg) override;


      //virtual bool get_frame(::pointer<::user::interaction>& pinteraction);
      //virtual void add_frame(::user::interaction * puserinteraction);
      //virtual void erase_frame(::user::interaction * puserinteraction);

      virtual bool send_message_to_windows(const ::atom& atom, wparam wparam, lparam lparam); // with tbs in <3

      virtual bool route_message_to_windows(::message::message* pmessage); // with tbs in <3


      virtual void send_language_change_message();


      // apex commented
      //virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


      virtual string preferred_experience();


      // user virtual ::user::document * place_hold(::user::interaction * pinteraction);


      virtual void post_message(const ::atom& atom, wparam wParam = {}, lparam lParam = 0) override;


      //virtual ::image::icon * set_icon(object * pparticle, ::image::icon * picon, bool bBigIcon);

      //virtual ::image::icon * get_icon(object * pparticle, bool bBigIcon) const;

      //virtual void handle(::topic * ptopic, ::context * pcontext);


      //      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
      //
      ////      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);
      //
      //      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);

      //virtual void on_initial_frame_position(::user::frame * pframe);

      //virtual void on_graphics_ready();

      //virtual ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);
      // apex commented
      //virtual ::type_atom control_type_from_id(const ::atom & atom, ::user::enum_control_type & econtroltype);


      //virtual ::atom translate_property_id(const ::atom & atom) override;
      //virtual property fetch_property(const ::atom & atom) override;

      //virtual void get_time(micro_time * pmicrotime);


      virtual void close(::enum_exit eexit);


      //user virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom = nullptr);


      virtual void HideApplication();


      //virtual void initialize(::particle * pparticle) override;

      //virtual void process_init() override;

      //virtual void init1() override; // first initialization
      //virtual void init2() override; // second initialization
      //virtual void init3() override; // third initialization and so on...

      //virtual void init() override; // last initialization

      //virtual void bergedge_start();
      //virtual void os_native_bergedge_start() override;

      //virtual void term_application() override;

      //virtual void term() override;

      //virtual void     main() override;

      //virtual ::application * get_app() const override;


      //virtual u32 guess_code_page(const string& str);

      //virtual i32 _sync_message_box(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 fuStyle) override;


      virtual void pre_translate_message(::message::message* pmessage) override;


      //virtual void install_message_routing(::channel* pchannel) override;


      //virtual void EnableShellOpen();


      //virtual void _001CloseApplication() override;


      //user virtual void on_create_split_impact(::user::split_impact* pimpact);


      //virtual ::type_atom control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype) override;


      // virtual bool base_support();

      //virtual string sync_message_box(const string & pszMatter,property_set & propertyset) override;


      //virtual ::pointer<::user::interaction>uie_from_point(const ::point_i32& point);

      //virtual bool on_application_menu_action(const ::string & pszCommand) override;

      //virtual bool on_install() override;
      //virtual bool on_uninstall() override;
      virtual bool on_run_install();


      virtual bool on_run_uninstall();


      DECLARE_MESSAGE_HANDLER(on_application_signal);


      DECLARE_MESSAGE_HANDLER(_001OnSwitchContextTheme);


      // open named file, trying to match a regsitered
      // document template to it.
      //virtual void on_request(::create* pcreate) override;

      //for implementation
      virtual bool on_idle(::i32 lCount); // return true if more idle processing
      virtual void process_window_procedure_exception(const ::exception& e, ::message::message* pmessage) override;


      //      void EnableModelessEx(bool bEnable);
      ////#ifdef WINDOWS
      ////      HENHMETAFILE LoadEnhMetaFile(::u32 uResource);
      ////#endif
      //      bool GetResourceData(::u32 nID, const ::string & lcszType, memory& storage);

      //#ifdef WINDOWS
      //      virtual bool OnMessageWindowMessage(MESSAGE * pmsg);
      //
      //#elif defined(LINUX)
      //      virtual bool OnX11WindowMessage(void* pev);
      //#endif

      //bool CreateFileFromRawResource(::u32 nID, const ::string & lcszType, const ::string & pcszFilePath);

      //virtual LRESULT GetPaintMsgProc(i32 nCode, WPARAM wParam, LPARAM lParam);


      //void OnUpdateRecentFileMenu(::message::command* pcommand);

      //virtual void send_app_language_changed();
      void route_command(::message::command* pcommand, bool bRouteToKeyDescendant = false) override;


      //virtual pointer< ::extended::future < ::conversation > > message_box(::user::interaction * puserinteraction, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;
      //virtual ::enum_dialog_result message_box_timeout(const ::string & pszMessage, const ::string & pszTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future()) override;


      //void EnableHtmlHelp();


      //virtual i32 sync_message_box_timeout(::user::interaction_base * puiOwner,::payload payload, const ::string & pszTitle, class ::time timeTimeout,::u32 fuStyle = e_message_box_ok) override;
      //virtual i32 sync_message_box(::user::interaction_base * puiOwner,const ::string & pszMessage, const ::string & pszTitle, ::u32 fuStyle = e_message_box_ok) override;


      //bool on_exclusive_instance_conflict(bool & bHandled, enum_exclusive_instance eexclusive, string strId) override;

      //virtual bool process_exception(const ::exception & e) override;

      //virtual bool on_uninstall() override;

      //virtual bool on_install() override;


      //::user::document* place_hold(::user::interaction* pinteraction) override;


      //virtual bool on_install() override;
      //virtual bool on_application_menu_action(const ::string & pszCommand) override;


      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style_pointer & pstyle,::menu::item * pitem) override;

      // set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      //void SetRegistryKey(const ::string & pszRegistryKey);

      //void SetRegistryKey(::u32 nIDRegistryKey);


      //void RegisterShellFileTypes(bool bCompat = false);

      //// call after all doc templates are registered
      //void UnregisterShellFileTypes();

      //
      //#ifdef WINDOWS
      //      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
      //      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld = true);
      //#endif

      // create a DC for the system default printer.
      //::draw2d::graphics* CreatePrinterDC();


      //   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // run this cast as an embedded object.
      //bool RunEmbedded();

      // run this cast as an OLE automation server.
      //bool RunAutomated();

      // Parse the command line for stock options and commands.
      //   void ParseCommandLine(CCommandLineInfo& rCmdInfo);

      // React to a shell-issued command line directive.
      //   bool ProcessShellCommand(CCommandLineInfo& rCmdInfo);

      // Overridables


      // exiting
      virtual bool save_all_modified(); // save before exit
      //virtual void HideApplication() override;
      //virtual void close(::apex::e_end eend) override; // close documents before exiting

      // Advanced: to override message boxes and other hooks
      //virtual i32 DoMessageBox(const ::string & pszPrompt,::u32 nType,::u32 nIDPrompt);


      // Advanced: process async DDE request
      //virtual bool OnDDECommand(LPWSTR pszCommand);

      void _001OnFileNew();


      void on_file_open();


      virtual bool does_launch_window_on_startup();


      virtual bool activate_app();


      virtual void initialize_contextualized_theme();


      virtual bool get_fs_size(string& strSize, const ::string& pszPath, bool& bPending);


      virtual bool get_fs_size(i64& i64Size, const ::string& pszPath, bool& bPending);


      virtual void set_title(const ::string& pszTitle);


      void update_app_interest();


      void ensure_app_interest();


      //      virtual ::pointer<::apex::application>create_platform(::apex::session* psession);


      virtual ::pointer<::progress::real> show_progress(::user::interaction* puiParent, const ::string& strTitle,
                                                        ::collection::count iProgressCount);


      virtual void userfs_init1();


      virtual void userfs_process_init();


      void data_on_after_change(::database::client* pclient, const ::scoped_string& scopedstr,
                                ::topic* ptopic) override;


      virtual void report_error(const ::exception& e, int iMessageFlags, const ::string& pszTopic);


      virtual void create_impact_system();


      virtual void on_song_added(const string& str);


      //string get_visual_studio_build();


      virtual string sound_path(const ::string& psz);


      virtual string get_default_playlist_path();


      virtual string as_string(const ::payload& payload);

#if defined(LINUX) || defined(__BSD__)

      virtual string get_wm_class() const;

#endif


      virtual void on_create_app_shortcut();


      virtual void create_app_shortcut();


      virtual class ::networking::application* networking_application(
         ::networking::application_handler* papplicationhandlerCreateNetworkApplication = nullptr);


      virtual void create_networking_application(const ::scoped_string& scopedstrHostName,
                                                 ::networking::application_handler*
                                                    papplicationhandlerCreateNetworkApplication = nullptr);


      ::e_status on_html_response(::networking::application_socket* psocket, ::string& strHtml, const ::string& strUrl,
                                  const ::property_set& setPost) override;


      bool _handle_uri(const ::string& strUri) override;


      //bool on_interprocess_handle(const ::scoped_string & scopedstrUri) override;

      bool on_application_menu_action(const ::atom& atom) override;


   };


} // namespace apex
