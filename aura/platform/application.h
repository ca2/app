#pragma once


#include "context.h"


namespace aura
{


   class CLASS_DECL_AURA application :
      virtual public ::aqua::application,
      virtual public ::aura::context,
      virtual public ::filemanager::callback
   {
   public:


      //__creatable_from_base(application, ::apex::application);


      void* m_pnativeapp;


      ::aura::application *                           m_pappParent;
      //string                                          m_strAppName;
      //string                                          m_strAppTitle;
      //string                                          m_XstrAppId;
      //string                                          m_strBaseSupportId;
      //string                                          m_strRoot;
      //string                                          m_strDomain;
      //string                                          m_strLibraryName;
      //string                                          m_strRelativeFolder;
      //string                                          m_strBuild;
      //string                                          m_strInstallToken;
      //string                                          m_strInstallTraceLabel;
      //string                                          m_strInstallBuild;
      //string                                          m_strHttpUserAgentToken;
      //string                                          m_strHttpUserAgentVersion;
      //string_array                                    m_straAppCategory;
      //bool                                            m_bLicense;
      //bool                                            m_bRequiresInstallation;

      //bool                                            m_bReadStringTable;

      //::pointer<::application_menu>            m_pappmenu;

      //::pointer<::game::game>                      m_pgame;
      ::pointer<::user::interaction>               m_puserinteractionMain;

      ::pointer<shell_open>                        m_pshellopen;


      ::user::primitive *                             m_puiCurrent;
      //bool                                            m_bContextTheme;

#ifdef LINUX
      bool                                            m_bSnLauncheeSetup;
#endif
      semaphore                                       m_semCompiler;
      // former ::aura::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV

      ::u32                                           m_dwInstallGoodToCheckAgain;

      //bool                                            m_bAppHasInstallerProtected;
      //bool                                            m_bAppHasInstallerChangedProtected;
      //::install::installer *                          m_pinstaller;

      reference_addressa                              m_objectptraEventHook;

      ::mutex                                           m_mutexFrame;
      ::pointer<::user::interaction_array>           m_puserinteractiona;
      ::pointer<::user::interaction_array>           m_puserinteractionaFrame;

      //e_thread                                        m_ethreadClose;

      //EExclusiveInstance                              m_eexclusiveinstance;

      //string_map < ::pointer<::acme::exclusive >>    m_mapExclusive;

      //bool                                            m_bService;

      //bool                                            m_bUpdateMatterOnInstall;

      ::user::interaction *                              m_puiMainContainer;

      ::mutex                                           m_mutexMatterLocator;

      //::mutex                                         m_mutexStr;
      //string_table                                    m_stringtable;
      //string_table                                    m_stringtableStd;
      //map < atom, atom, string, string >                  m_stringmap;

      //id_map < ::pointer<::channel >>                m_mapNotify;

      //::pointer<context_image>                       m_pcontextimage;

      //bool                                            m_bInitializeDataCentral;

      //string                                          m_strLicense;

      //i32                                             m_iWaitCursorCount;         // for wait cursor (>0 => waiting)

      //::pointer<::simpledb::server>                  m_psimpledb;

      //::userex::pane_tab_impact *                       m_pmainpane;


//      string                                          m_strHelpFilePath;
//
//#ifdef WINDOWS
//
//      HGLOBAL                                         m_hDevMode;             // printer Dev Mode
//      HGLOBAL                                         m_hDevNames;            // printer Device Names
//
//#endif
//
//      u32                                             m_dwPromptContext;        // help action_context override for message box
//      // LKG
//      u32                                             m_dwPolicies;            // block for storing tristate system policies
//
//      // Support for Shift+F1 help mode.
//      // true if we're in SHIFT+F1 mode.
//      bool                                            m_bHelpMode;
//
//      //::userex::pane_tab_impact *                       m_ppaneimpactMain;
//
//      string                                          m_strProfileName;
//
//      ATOM                                            m_atomApp;
//      ATOM                                            m_atomSystemTopic;   // for DDE open
//      ::u32                                            m_nNumThumbnailPages; // number of default printed pages
//
//      string                                          m_strId;

//      i32                                             m_iResourceId;

      //::pointer<::experience::department>          m_pexperience;
      ::pointer<::aura::theme>                       m_ptheme;


      //string_array                                    m_straAppInterest;
      //string_map < oswindow, oswindow >               m_mapAppInterest;

      //i32                                             m_iGcomBackgroundUpdateMillis;


      application();
      ~application() override;


      virtual void initialize(::object * pobject) override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual void enumerate_composite(matter_array& a);

      ::aura::game* game();


      virtual void _001CloseApplication() override;


      //virtual ::user::style* get_user_style() const;
      //virtual bool app_data_get(const ::atom & atom, stream & os) override;
      //virtual bool app_data_set(const ::atom & atom, stream & is) override;

      //virtual bool app_data_set(const ::atom & atom, object & obj) override;
      //virtual bool app_data_get(const ::atom & atom, object & obj) override;

//      virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::database::key calc_data_key() override;


      //virtual string load_podata(string strLang, bool bOnlyHeader);

      //virtual string load_string(const ::atom & atom) override;
      //virtual bool load_string(string & str, const ::atom & atom) override;
      //virtual void load_string_table() override;
      //virtual bool load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable) override;
      //virtual bool load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable) override;
      //virtual void load_string_table(const string & pszApp, const string & pszId) override;



      //virtual bool is_system() const override;
      //virtual bool is_session() const override;
      //virtual bool is_serviceable() const override;
      virtual string get_window_class_name(::user::enum_control_type econtroltype);

      //virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver() override;
      //inline ::context_image& image() { return *m_pcontextimage; }


      virtual void verb() override;


      inline ::aura::session* get_session() { return m_pcontext && m_pcontext->m_papexsession ? m_pcontext->m_papexsession->m_paurasession : nullptr; }
      inline ::aura::system* get_system();



      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      //virtual void init_application() override;

      virtual void init1() override;
      virtual void init2() override;
      virtual void init3() override;


      virtual void init() override;


      virtual void init_instance() override;


      //virtual void     run() override;
      //virtual void     main() override;
      //virtual void     on_run();

      //virtual void application_pre_run();
      //virtual bool initial_check_directrix() override;
      //virtual void os_native_bergedge_start();





      virtual void term() override;


      virtual void term_application() override;




      //virtual bool InitApplication();


      virtual void do_install() override;
      virtual void do_uninstall() override;


      virtual void on_install() override;
      virtual void on_uninstall() override;


      virtual void update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative) override;
      virtual void update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative, const ::string & strLocale, const ::string & strStyle) override;

      //virtual void SetCurrentHandles() override;


      //virtual void process_exception(const ::exception & e) override;


      //virtual ::pointer<::aura::application>assert_running(const ::string & pszAppId) override;

      virtual bool is_running() override;



      virtual void on_request(::create * pcreate) override;



      virtual bool assert_user_logged_in() override;

      virtual string matter_as_string(const ::string & pszMatter, const ::string & pszMatter2 = nullptr) override;














      //virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);
      //virtual bool do_prompt_file_name(::payload& payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);
      //user virtual bool do_prompt_file_name(::payload& payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);


      virtual void process_message_filter(i32 code, ::message::message * pmessage) override;



      virtual void DoWaitCursor(i32 nCode) override; // 0 => restore, 1=> begin, -1=> end

      // virtual void _001TryCloseApplication() override;


      virtual string get_license_id() override;




      virtual void process_init() override;




//#ifdef WINDOWS_DESKTOP
//      virtual void TermThread(HINSTANCE hInstTerm) override;
//#endif

      //virtual void set_env_var(const string & payload, const string & value) override;


      virtual ::draw2d::printer * get_printer(const ::string & pszDeviceName);


      virtual ::draw2d::icon * set_icon(::object * pobject, ::draw2d::icon * picon, bool bBigIcon);

      virtual ::draw2d::icon * get_icon(::object * pobject, bool bBigIcon) const;

      //virtual void on_service_request(::create * pcreate) override;

      virtual string get_mutex_name_gen() override;

      //virtual ::user::interaction * user_interaction_from_oswindow(::windowing::window * pwindow);


      //virtual i32 hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);
      //virtual i32 hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);

      //virtual void on_update_impact(::user::impact * pimpact, ::user::impact * pviewSender, lparam lHint, object * pHint);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      //virtual void on_notify_control_event(::user::control_event* pevent);
      //virtual void route(::topic * ptopic, ::context * pcontext);



      //user virtual bool on_open_document(::user::document * pdocument, ::payload payloadFile);
      //user virtual bool on_save_document(::user::document * pdocument, ::payload payloadFile);



      //inline ::html::html * html() { return puser->m_phtml; }

      //virtual ::html::html * create_html();

      //virtual string http_get(const ::string & strUrl, ::property_set & set) override;

      //virtual bool compress_ungz(const ::stream & os, const ::stream & is) override;

      ///virtual bool compress_ungz(memory_base & mem) override;
      //virtual bool compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override;

      //virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override;


      virtual bool is_local_data() override;


      //application();
      //~application() override;


      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema);
      //virtual string get_locale_schema_dir();


      //virtual void initialize(::object * pobject) override;


      //::application_menu & applicationmenu();


      //virtual ::file::path appconfig_folder() override;


      //void assert_ok() const override;
      //void dump(dump_context & dumpcontext) const override;


      //virtual ::file::path get_app_localconfig_folder() override;
      //virtual ::handle::ini get_ini() override;


      //virtual bool app_data_set(const ::atom & atom, stream & os) override;
      //virtual bool app_data_get(const ::atom & atom, stream & is) override;

      //virtual bool app_data_set(const ::atom & atom, ::object & obj) override;
      //virtual bool app_data_get(const ::atom & atom, ::object & obj) override;

      void install_message_routing(::channel * pchannel) override;

      virtual string dialog_box(const ::string & pszMatter, property_set & propertyset) override;

      //virtual void application_menu_update() override;


      //virtual string calc_data_key();



      //virtual void notify_changed(const ::atom & atom, const ::action_context & action_context);


      //virtual ::file::path local_application_path() override;

      //virtual ::file::path local_application_home_path() override;


      virtual void destroy() override;


      //virtual void release_parents() override;
      ::property_object * parent_property_set_holder() const override;


      //virtual bool is_set_finish() const override;


      virtual void on_change_theme() override;
      virtual string get_theme() override;


      //virtual ::pointer<::acme::exclusive>get_exclusive(string str, LPSECURITY_ATTRIBUTES psa) override;
      //virtual bool exclusive_fails(string str, LPSECURITY_ATTRIBUTES psa) override;


      //virtual bool start_application(bool bSynch, ::create * pcreate) override;



      //virtual void release_children() override;
      //virtual void merge_command_line(::create * pcommand);

//   virtual void merge(::handler * phandler);

      //virtual void record(::create * pcommand);

      //virtual void on_event(::u64 u, ::object * pobject) override;
      //virtual ::pointer<::thread_toolset>create_thread_toolset(::enum_task_tool etool);


      //// ca2verses
      //// os_* functions generally
      //// reserves a lot of surprises from each
      //// operating system specific behavior
      //virtual void message_box_synchronous(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //virtual void ui_message_box(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
      //virtual void ui_message_box_timeout(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeOut = duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //using ::aura::context_thread::message_box;
      //virtual void message_box(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
      //virtual void message_box_timeout(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeOut = duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //virtual void on_file_new() override;


      //virtual string get_title() override;
      //virtual string_array get_categories() override;

      virtual void defer_create_keyboard() override;
      //virtual bool set_keyboard_layout(const ::string & pszPath, const ::action_context & action_context);


      //virtual bool enable_application_events(::object * pobject, bool bEnable) override;

      //virtual bool is_equal_file_path(const ::file::path & path1, const ::file::path & path2) override;


      //virtual bool process_exception(const ::exception & e) override;


      //virtual bool is_system() const override;
      //virtual bool is_session() const override;
      //virtual bool is_serviceable() const;
      //virtual bool is_user_service() const override;

      //void set_has_installer(bool bSet);



      //virtual ::file::path defer_process_path(::file::path path);
      //virtual ::file::path full_process_path(::file::path path);

      //virtual void DoWaitCursor(i32 nCode); // 0 => restore, 1=> begin, -1=> end
      //virtual void show_wait_cursor(bool bShow = true) override;



      //virtual void process_message_filter(i32 code,::message::message * pmessage) override;

      virtual void on_thread_on_idle(::thread * pthread,::i32 lCount) override;


      //virtual bool app_set(string strPath, string strValue) override;
      //virtual string app_get(string strPath, string strDefault = "") override;


      //virtual bool Ex2OnAppInstall();
      //virtual bool Ex2OnAppUninstall();

      bool on_application_menu_action(const ::string & pszCommand) override;
      //virtual void _001CloseApplication();

      //virtual string get_license_id();

      //virtual string get_version() override;

//      virtual ::pointer<::interprocess::communication>create_interprocess_communication() override;

      //virtual void process_init();
      //virtual void process_term() override;

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

      virtual void term1() override;
      virtual void term2() override;
      virtual void term3() override;

      //virtual void init_thread() override;
      //virtual void init_application();
      //virtual void term_application();
      //virtual void term_thread() override;

      //virtual void init_instance() override;
      virtual void term_instance() override;

      //virtual void init();
      //virtual void term();

      //virtual void notify_process_init();
      //virtual void notify_init1();
      //virtual void notify_init2();
      //virtual void notify_init3();

      //virtual void notify_term3();
      //virtual void notify_term2();
      //virtual void notify_term1();
      //virtual void notify_process_term();

      // virtual bool is_installing();
      // virtual bool is_unstalling();

      //virtual string get_version();
      //virtual void     run() override;
      //virtual void     main() override;
      //virtual void     on_run();

      virtual void on_before_launching() override;
      //virtual void os_native_bergedge_start();

      //virtual void pre_run() override;
      //virtual void application_pre_run();

      virtual void on_pos_run_thread() override;
      virtual void pos_run() override;
      virtual void application_pos_run() override;

      //virtual bool InitApplication();
      //virtual void TermApplication() override;

      //virtual bool on_install();
      //virtual bool on_uninstall();

      //virtual bool system_add_app_install(const ::string & pszId, const ::string & pszBuild) override;

      //virtual void TermThread(HINSTANCE hInstTerm);

      //virtual void SetCurrentHandles();

      //virtual void set_env_var(const string & payload,const string & value);
      //virtual itask_t get_thread_id();


      //virtual bool _001OnDDECommand(const ::string & pcsz) override;

      virtual void _001InitializeShellOpen() override;
      virtual void _001OnFileNew(::message::message * pmessage) override;


      //virtual string multimedia_audio_get_default_library_name() override;
      //virtual string multimedia_audio_mixer_get_default_library_name() override;
      //virtual string veriwell_multimedia_music_midi_get_default_library_name() override;

      //virtual bool get_temp_file_name_template(string & str, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate) override;

      //virtual bool get_temp_file_name(string & str, const ::string & lpszName, const ::string & pszExtension) override;

      //service_base * get_service();
      //virtual service_base * allocate_new_service() override;
      //virtual bool init_service() override;

      //virtual bool os_create_service() override;
      //virtual bool os_erase_service() override;

      //virtual bool os_start_service() override;
      //virtual bool os_stop_service() override;

      //virtual void on_service_request(::create * pcreate);

      //virtual bool is_running();

      //virtual string get_mutex_name_gen();

      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this memory_new additional instance creation
      //virtual void on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId) override;

      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this memory_new additional instance creation
//      virtual bool on_exclusive_instance_local_conflict(bool & bHandled) override;

            /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this memory_new additional instance creation
      //virtual bool on_exclusive_instance_local_conflict_id(bool & bHandled, string strId) override;

      /// return true if the external additional instance might continue execution
      /// bHandled true if some action was done in response to the external memory_new additional instance creation
      //virtual void on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine) override;

      //virtual void on_new_instance(string strModule, const ::atom & idPid) override;

      //virtual string get_local_mutex_id() override;
      //virtual string get_global_mutex_id() override;

      //virtual ::mutex * get_local_mutex();
      //virtual ::mutex * get_global_mutex();

      //virtual string get_local_mutex_name() override;
      //virtual string get_local_id_mutex_name() override;
      //virtual string get_global_mutex_name() override;
      //virtual string get_global_id_mutex_name() override;

      //virtual bool check_exclusive(bool & bHandled) override;
      //virtual bool release_exclusive() override;

      //virtual void on_set_scalar(e_scalar escalar,i64 iValue,int iFlags) override;
      //virtual void get_scalar_minimum(e_scalar escalar,i64 & i) override;
      //virtual void get_scalar(e_scalar escalar,i64 & i) override;
      //virtual void get_scalar_maximum(e_scalar escalar,i64 & i) override;



      //bool safe_is_running();


      //virtual void on_request(::create * pcreate) override;

      //// name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
      //// get/set serializables to user directory
      //template < typename TYPE >
      //bool gudo_get(const ::string & strKey, TYPE & t);

      //template < typename TYPE >
      //bool gudo_set(const ::string & strKey, const TYPE & t);


      //virtual bool assert_user_logged_in();

      //virtual void     do_request(::create * pcreate) override;
      virtual void call_request(::create * pcreate) override;


      //virtual void process_message(::user::message * base) override;

      //virtual void message_handler(::user::message * pusermessage) override;



      //virtual string http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema) override;

      //virtual void on_update_matter_locator() override;

      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      //virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;

      //virtual string get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema) override;
      //virtual string get_locale_schema_dir(const ::string & strLocale) override;
      //virtual string get_locale_schema_dir() override;

      //virtual void set_locale(const string & pcsz, const ::action_context & action_context) override;

      //virtual void set_schema(const string & pcsz, const ::action_context & action_context) override;

      //virtual void on_set_locale(const string & pcsz, const ::action_context & action_context) override;

      //virtual void on_set_schema(const string & pcsz, const ::action_context & action_context) override;



      //virtual void fill_locale_schema(::text::international::locale_schema & localeschema) override;
      //virtual void fill_locale_schema(::text::international::locale_schema & localeschema,const string & pszLocale,const string & pszSchema) override;

      //virtual bool platform_open_by_file_extension(index iEdge, const ::string & pszPathName, ::create * pcreate = nullptr) override;
      //virtual bool platform_open_by_file_extension(index iEdge,::create * pcc) override;


      //virtual bool on_start_application() override;

      //virtual bool os_on_start_application() override;

      //virtual bool is_application() const override;


      //DECLARE_MESSAGE_HANDLER(on_message_app_exit);
      //virtual bool _001OnAgreeExit() override;
      //virtual void france_exit() override;
      //virtual void _001FranceExit() override;


      //virtual string lstr(const ::atom & atom, string strDefault = "") override;



      //virtual bool do_install();
      //virtual bool do_uninstall();



      //void request(::create * pcommand) override;
      //void on_create(::create * pcreate) override;

//      virtual void dispatch_user_message(::user::message * pusermessage);

      //virtual void throw_not_installed();

      //virtual void play_audio(::payload payloadFile, bool bSynch = false);

      //virtual void post_critical_error_message(const ::string & pszMessage, bool bShowLog = true) override;

      //virtual void show_critical_error_log() override;

      //virtual string get_app_user_friendly_task_bar_name() override;

      //void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual bool compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);

      //virtual bool compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6);

      //virtual void interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::file::path get_executable_path() override;
      //virtual string get_executable_extension() override;
      //virtual string get_executable_title() override;
      //virtual string get_executable_appid() override;



      //virtual bool on_open_document_file(::payload payloadFile) override;

      //virtual string get_app_id(string wstr) override;


      //virtual void install_trace(const ::string & str) override;
      //virtual void install_trace(double dRate) override;
      //virtual bool register_spa_file_type() override;

      //virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration) override;
      //virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;
      //virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;



      virtual bool keyboard_focus_is_focusable(const ::user::primitive * pue) override;
      virtual bool keyboard_focus_OnSetFocus(::user::primitive * pue) override;

      virtual ::user::interaction * main_window();


      virtual bool is_sandboxed();



      virtual ::pointer<::user::message>get_user_message(MESSAGE * pmsg);

      virtual bool get_frame(::pointer<::user::interaction>& pinteraction);
      virtual void add_user_interaction(::user::interaction * puserinteraction);
      virtual void erase_user_interaction(::user::interaction * puserinteraction);

      virtual bool send_message_to_windows(const ::atom & atom, wparam wparam, lparam lparam) override; // with tbs in <3

      virtual bool route_message_to_windows(::message::message * pmessage) override; // with tbs in <3


      //virtual void send_language_change_message() override;



      virtual string preferred_experience() override;


      // user virtual ::user::document * place_hold(::user::interaction * pinteraction);


      virtual void post_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0) override;


      //virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon);

      //virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const;

      //virtual void handle(::topic * ptopic, ::context * pcontext);



//      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//
////      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);
//
//      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);

      virtual void on_initial_frame_position(::user::frame * pframe);

      virtual void on_graphics_ready();

      //virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);
      virtual ::type control_type_from_id(const ::atom & atom, ::user::enum_control_type & econtroltype);


      virtual ::atom translate_property_id(const ::atom & atom) override;
      //virtual property fetch_property(const ::atom & atom) override;

      //virtual void get_time(struct timeval *point_i32) override;

      virtual void close(::apex::enum_end eend) override;


      //user virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction * puiParent, ewindowflag ewindowflag, const ::atom & atom = nullptr);


      virtual void HideApplication() override;


      //virtual void initialize(::object * pobject) override;

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

      //virtual ::aura::application * get_app() const override;

      //virtual bool is_system() const override;
      //virtual bool is_session() const override;

      //virtual u32 guess_code_page(const string& str) override;

      //virtual i32 _sync_message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 fuStyle) override;

      //virtual bool is_serviceable() const override;


      virtual void pre_translate_message(::message::message* pmessage) override;


      //virtual void EnableShellOpen() override;



      //virtual bool base_support() override;

      virtual bool on_run_install() override;
      virtual bool on_run_uninstall() override;

      DECLARE_MESSAGE_HANDLER(on_application_signal);
      DECLARE_MESSAGE_HANDLER(_001OnSwitchContextTheme);


      virtual bool on_idle(::i32 lCount) override; // return true if more idle processing
      virtual void process_window_procedure_exception(const ::exception & e, ::message::message* pmessage) override;

//      void EnableModelessEx(bool bEnable);
//      bool GetResourceData(::u32 nID, const ::string & lcszType, memory& storage);

//#ifdef WINDOWS
//      virtual bool OnMessageWindowMessage(MESSAGE * pmsg);
//
//#elif defined(LINUX)
//      virtual bool OnX11WindowMessage(void* pev);
//#endif

      bool CreateFileFromRawResource(::u32 nID, const ::string & lcszType, const ::string & pcszFilePath);

      void OnUpdateRecentFileMenu(::message::command* pcommand);

      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      //virtual void EnableHtmlHelp();

      // set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      virtual void SetRegistryKey(const ::string & pszRegistryKey);

      virtual void SetRegistryKey(::u32 nIDRegistryKey);


      virtual void RegisterShellFileTypes(bool bCompat = false);

      // call after all doc templates are registered
      void UnregisterShellFileTypes();

      // run this cast as an embedded object.
      // virtual bool RunEmbedded();

      // run this cast as an OLE automation server.
      //virtual bool RunAutomated();

      // exiting
      bool save_all_modified() override; // save before exit
    
      virtual void _001OnFileNew();
      virtual void on_file_open();

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      //virtual ::count get_open_document_count();

      //static const char gen_FileSection[];
      //static const char gen_FileEntry[];
      //static const char gen_ThumbnailSection[];
      //static const char gen_ThumbnailEntry[];




      virtual bool does_launch_window_on_startup() override;
      virtual bool activate_app() override;





      virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::user::system* pusersystem);




      inline ::aura::theme* theme() { return m_ptheme.get(); }
      

      virtual void initialize_contextualized_theme() override;



      virtual i32 track_popup_menu(const ::string & pszMatter, const ::point_i32& point, ::pointer<::user::interaction>puserelement);

      virtual bool get_fs_size(string& strSize, const ::string & pszPath, bool& bPending) override;
      virtual bool get_fs_size(i64& i64Size, const ::string & pszPath, bool& bPending) override;

      virtual void set_title(const ::string & pszTitle) override;


      virtual bool _001CloseApplicationByUser(::pointer<::user::interaction>puserinteractionExcept);

      void update_app_interest();
      void ensure_app_interest();


      virtual bool is_system() const override;
      virtual bool is_session() const override;






//      virtual ::pointer<::apex::application>create_platform(::apex::session* psession) override;




      void data_on_after_change(::database::client* pclient, const ::database::key& atom, const ::payload & payload, ::topic * ptopic) override;


      virtual i32 GetVisibleTopLevelFrameCountExcept(::pointer<::user::interaction>puserinteractionExcept);
      virtual i32 GetVisibleFrameCount();

      virtual void prepare_form(atom atom, ::form_document* pformdocument);


      void report_error(const ::exception & exception, int iMessageFlags, const ::string & pszTopic) override;


      bool can_close_application() override;


      virtual bool on_close_frame_window(::user::frame* pframe);


      void create_impact_system() override;

      virtual ::user::interaction* create_menu_interaction();

      void on_song_added(const string& str) override;


      virtual string get_visual_studio_build();


      string sound_path(const ::string & psz) override;
      string get_default_playlist_path() override;

      
#if defined(LINUX) || defined(FREEBSD)

      bool os_on_start_application() override;

#endif



   };


} // namespace aura







//CLASS_DECL_AURA ::u32 c_cdecl application_thread_procedure(LPVOID pvoid);

//typedef ::pointer<::aura::application>(*LPFN_instantiate_application)(::pointer<::aura::application>appParent, const ::string & pszId);

//extern CLASS_DECL_AURA LPFN_instantiate_application g_lpfn_instantiate_application;

//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_AURA BOOL LaunchAppIntoDifferentSession(const ::string & pszProcess, const ::string & pszCommand, const ::string & pszDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi, int iSession = -1);
//
//CLASS_DECL_AURA BOOL LaunchAppIntoSystemAcc(const ::string & pszProcess, const ::string & pszCommand, const ::string & pszDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi);
//
//#endif // WINDOWS_DESKTOP





