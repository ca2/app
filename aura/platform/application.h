#pragma once


namespace aura
{


   class CLASS_DECL_AURA application :
      virtual public ::aqua::application,
      virtual public ::user::callback,
      virtual public ::filemanager::callback
   {
   public:


      void* m_pnativeapp;


      ::aura::application *                           m_pappParent;
      //string                                          m_strAppName;
      //string                                          m_strAppTitle;
      //string                                          m_strAppId;
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

      //__pointer(::apex::application_menu)             m_papplicationmenu;

      //__composite(::game::game)                       m_pgame;


      __composite(shell_open)                         m_pshellopen;


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

      //bool                                            m_bAgreeExit;
      //bool                                            m_bAgreeExitOk;
      //bool                                            m_bFranceExit;

      //bool                                            m_bIpi;
      //__pointer(::interprocess_intercommunication)    m_pinterprocessintercommunication;
      __pointer(service_base)                         m_pservice;

      ::mutex                                         m_mutexFrame;
      __composite(::user::interaction_array)            m_puiptraFrame;

      //e_thread                                        m_ethreadClose;

      //EExclusiveInstance                              m_eexclusiveinstance;

      //string_map < __pointer(::acme::exclusive) >     m_mapExclusive;

      //bool                                            m_bService;

      //bool                                            m_bUpdateMatterOnInstall;

      ::user::interaction *                              m_puiMainContainer;

      ::mutex                                           m_mutexMatterLocator;

      //::mutex                                         m_mutexStr;
      //string_table                                    m_stringtable;
      //string_table                                    m_stringtableStd;
      //map < id, id, string, string >                  m_stringmap;

      //id_map < __pointer(::channel) >                 m_mapNotify;

      __composite(context_image)                        m_pcontextimage;

      //bool                                            m_bInitializeDataCentral;

      //string                                          m_strLicense;

      //i32                                             m_iWaitCursorCount;         // for wait cursor (>0 => waiting)

      //__pointer(::simpledb::server)                   m_psimpledb;

      //::userex::pane_tab_view *                       m_pmainpane;


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
//      u32                                             m_dwPolicies;            // block for storing boolean system policies
//
//      // Support for Shift+F1 help mode.
//      // true if we're in SHIFT+F1 mode.
//      bool                                            m_bHelpMode;
//
//      //::userex::pane_tab_view *                       m_ppaneviewMain;
//
//      string                                          m_strProfileName;
//
//      ATOM                                            m_atomApp;
//      ATOM                                            m_atomSystemTopic;   // for DDE open
//      ::u32                                            m_nNumPreviewPages; // number of default printed pages
//
//      string                                          m_strId;

//      i32                                             m_iResourceId;

      //__composite(::experience::department)           m_pexperience;
      __composite(::aura::theme)                        m_ptheme;


      //string_array                                    m_straAppInterest;
      //string_map < oswindow, oswindow >               m_mapAppInterest;

      //i32                                             m_iGcomBackgroundUpdateMillis;


      application(const char * pszAppId = nullptr);
      virtual ~application();


      virtual ::e_status initialize(::layered * pobjectContext) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      inline ::aura::game* game() { return m_pgame->m_pauragame; }




      //virtual ::user::style* get_user_style() const;
      //virtual bool app_data_get(const ::id & id, stream & os) override;
      //virtual bool app_data_set(const ::id & id, stream & is) override;

      //virtual bool app_data_set(const ::id & id, object & obj) override;
      //virtual bool app_data_get(const ::id & id, object & obj) override;

//      virtual ::e_status     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::database::key calc_data_key() override;


      //virtual string load_podata(string strLang, bool bOnlyHeader);

      //virtual string load_string(const ::id & id) override;
      //virtual bool load_string(string & str, const ::id & id) override;
      //virtual void load_string_table() override;
      //virtual bool load_cached_string(string & str, const ::id & id, bool bLoadStringTable) override;
      //virtual bool load_cached_string_by_id(string & str, const ::id & id, bool bLoadStringTable) override;
      //virtual void load_string_table(const string & pszApp, const string & pszId) override;



      //virtual bool is_system() const override;
      //virtual bool is_session() const override;
      //virtual bool is_serviceable() const override;
      virtual string get_window_class_name(::user::enum_control_type econtroltype);

      //virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver() override;
      inline ::context_image& image() { return *m_pcontextimage; }


      virtual ::e_status verb() override;


      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      //virtual ::e_status init_application() override;

      virtual ::e_status init1() override;
      virtual ::e_status init2() override;
      virtual ::e_status init3() override;


      virtual ::e_status init() override;


      virtual ::e_status init_instance() override;


      //virtual ::e_status     run() override;
      //virtual ::e_status     main() override;
      //virtual ::e_status     on_run();

      //virtual ::e_status application_pre_run();
      //virtual bool initial_check_directrix() override;
      //virtual ::e_status os_native_bergedge_start();





      virtual void term() override;


      virtual void term_application() override;




      //virtual bool InitApplication();


      virtual bool do_install() override;
      virtual bool do_uninstall() override;


      virtual bool on_install() override;
      virtual bool on_uninstall() override;





      virtual bool update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative) override;
      virtual bool update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative, const string & strLocale, const string & strStyle) override;


      //virtual void SetCurrentHandles() override;


      //virtual ::e_status process_exception(::exception_pointer pe) override;


      //virtual __pointer(::aura::application) assert_running(const char * pszAppId) override;

      virtual bool is_running() override;



      virtual void on_request(::create * pcreate) override;



      virtual bool assert_user_logged_in() override;

      virtual string matter_as_string(const char * pszMatter, const char * pszMatter2 = nullptr) override;














      //virtual bool do_prompt_file_name(::payload & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);
      //virtual bool do_prompt_file_name(::payload& varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);
      //user virtual bool do_prompt_file_name(::payload& varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);


      virtual void process_message_filter(i32 code, ::message::message * pmessage) override;



      virtual void DoWaitCursor(i32 nCode) override; // 0 => restore, 1=> begin, -1=> end

      // virtual void _001TryCloseApplication() override;


      virtual string get_license_id() override;




      virtual ::e_status process_init() override;




//#ifdef WINDOWS_DESKTOP
//      virtual void TermThread(HINSTANCE hInstTerm) override;
//#endif

      //virtual void set_env_var(const string & payload, const string & value) override;


      virtual ::draw2d::printer * get_printer(const char * pszDeviceName);


      virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon);

      virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const;

      //virtual void on_service_request(::create * pcreate) override;

      virtual string get_mutex_name_gen() override;

      //virtual ::user::interaction * user_interaction_from_oswindow(::windowing::window * pwindow);


      //virtual i32 hotplugin_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);
      //virtual i32 hotplugin_host_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);

      //virtual void on_update_view(::user::impact * pview, ::user::impact * pviewSender, lparam lHint, object * pHint);

      virtual void on_control_event(::user::control_event* pevent) override;
      virtual void on_notify_control_event(::user::control_event* pevent);
      virtual void route_control_event(::user::control_event* pevent);



      //user virtual bool on_open_document(::user::document * pdocument, ::payload varFile);
      //user virtual bool on_save_document(::user::document * pdocument, ::payload varFile);



      //inline ::html::html * html() { return puser->m_phtml; }

      //virtual ::html::html * create_html();

      //virtual string http_get(const string & strUrl, ::property_set & set) override;

      //virtual bool compress_ungz(const ::stream & os, const ::stream & is) override;

      ///virtual bool compress_ungz(memory_base & mem) override;
      //virtual bool compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override;

      //virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override;


      virtual bool is_local_data() override;


      //application();
      //virtual ~application();


      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema);
      //virtual string get_locale_schema_dir();


      //virtual ::e_status initialize(::layered * pobjectContext) override;


      //::apex::application_menu & applicationmenu();


      //virtual ::file::path appconfig_folder() override;


      //virtual void assert_valid() const override;
      //virtual void dump(dump_context & dumpcontext) const override;


      //virtual ::file::path get_app_localconfig_folder() override;
      //virtual ::handle::ini get_ini() override;


      //virtual bool app_data_set(const ::id & id, stream & os) override;
      //virtual bool app_data_get(const ::id & id, stream & is) override;

      //virtual bool app_data_set(const ::id & id, ::object & obj) override;
      //virtual bool app_data_get(const ::id & id, ::object & obj) override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual string dialog_box(const char * pszMatter, property_set & propertyset) override;

      //virtual void application_menu_update() override;


      //virtual string calc_data_key();



      //virtual void notify_changed(const ::id & id, const ::action_context & action_context);


      //virtual ::file::path local_application_path() override;

      //virtual ::file::path local_application_home_path() override;


      virtual void finalize() override;


      //virtual void release_parents() override;
      virtual ::object * parent_property_set_holder() const override;


      //virtual bool is_set_finish() const override;


      virtual void on_change_theme() override;
      virtual string get_theme() override;


      //virtual __pointer(::acme::exclusive) get_exclusive(string str, LPSECURITY_ATTRIBUTES psa) override;
      //virtual bool exclusive_fails(string str, LPSECURITY_ATTRIBUTES psa) override;


      virtual bool start_application(bool bSynch, ::create * pcreate) override;



      //virtual void release_children() override;
      //virtual void merge_command_line(::create * pcommand);

//   virtual void merge(::handler * phandler);

      //virtual void record(::create * pcommand);

      //virtual void on_event(::u64 u, ::object * pobject) override;
      //virtual __pointer(::thread_toolset) create_thread_toolset(::enum_thread_tool etool);


      //// ca2verses
      //// os_* functions generally
      //// reserves a lot of surprises from each
      //// operating system specific behavior
      //virtual ::e_status os_message_box(::user::primitive * puiOwner, const char * pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //virtual ::e_status ui_message_box(::user::primitive * puiOwner, const char * pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
      //virtual ::e_status ui_message_box_timeout(::user::primitive * puiOwner, const char * pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeOut = duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //using ::aura::context_thread::message_box;
      //virtual ::e_status message_box(::user::primitive * puiOwner, const char * pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
      //virtual ::e_status message_box_timeout(::user::primitive * puiOwner, const char * pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeOut = duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());


      //virtual void on_file_new() override;


      //virtual string get_title() override;
      //virtual string_array get_categories() override;

      virtual void defer_create_keyboard() override;
      //virtual bool set_keyboard_layout(const char * pszPath, const ::action_context & action_context);


      //virtual bool enable_application_events(::object * pobject, bool bEnable) override;

      //virtual bool is_equal_file_path(const ::file::path & path1, const ::file::path & path2) override;


      //virtual bool process_exception(::exception_pointer pe) override;


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

      virtual ::e_status on_thread_on_idle(::thread * pthread,::i32 lCount) override;


      //virtual bool app_set(string strPath, string strValue) override;
      //virtual string app_get(string strPath, string strDefault = "") override;


      //virtual bool Ex2OnAppInstall();
      //virtual bool Ex2OnAppUninstall();

      virtual bool on_application_menu_action(const char * pszCommand);
      //virtual void _001CloseApplication();

      //virtual string get_license_id();

      //virtual string get_version() override;

//      virtual __pointer(::interprocess_intercommunication) create_interprocess_intercommunication() override;

      //virtual ::e_status process_init();
      //virtual void process_term() override;

      //virtual ::e_status impl_process_init();
      //virtual ::e_status impl_init1();
      //virtual ::e_status impl_init2();
      //virtual ::e_status impl_init3();

      //virtual void impl_process_term();
      //virtual void impl_term1();
      //virtual void impl_term2();
      //virtual void impl_term3();

      //virtual ::e_status init1();
      //virtual ::e_status init2();
      //virtual ::e_status init3();

      virtual void term1() override;
      virtual void term2() override;
      virtual void term3() override;

      //virtual ::e_status init_thread() override;
      //virtual ::e_status init_application();
      //virtual void term_application();
      //virtual void term_thread() override;

      //virtual ::e_status init_instance() override;
      virtual void term_instance() override;

      //virtual ::e_status init();
      //virtual void term();

      //virtual ::e_status notify_process_init();
      //virtual ::e_status notify_init1();
      //virtual ::e_status notify_init2();
      //virtual ::e_status notify_init3();

      //virtual void notify_term3();
      //virtual void notify_term2();
      //virtual void notify_term1();
      //virtual void notify_process_term();

      // virtual bool is_installing();
      // virtual bool is_unstalling();

      //virtual string get_version();
      //virtual ::e_status     run() override;
      //virtual ::e_status     main() override;
      //virtual ::e_status     on_run();

      virtual ::e_status on_before_launching() override;
      //virtual ::e_status os_native_bergedge_start();

      //virtual ::e_status pre_run() override;
      //virtual ::e_status application_pre_run();

      virtual void on_pos_run_thread() override;
      virtual void pos_run() override;
      virtual void application_pos_run() override;

      //virtual bool InitApplication();
      //virtual void TermApplication() override;

      //virtual bool on_install();
      //virtual bool on_uninstall();

      //virtual bool system_add_app_install(const char * pszId, const char * pszBuild) override;

      //virtual void TermThread(HINSTANCE hInstTerm);

      //virtual void SetCurrentHandles();

      //virtual void set_env_var(const string & payload,const string & value);
      //virtual ithread_t get_thread_id();


      //virtual bool _001OnDDECommand(const char * pcsz) override;

      virtual ::e_status _001InitializeShellOpen() override;
      virtual void _001OnFileNew(::message::message * pmessage) override;


      //virtual string multimedia_audio_get_default_library_name() override;
      //virtual string multimedia_audio_mixer_get_default_library_name() override;
      //virtual string veriwell_multimedia_music_midi_get_default_library_name() override;

      //virtual bool get_temp_file_name_template(string & str,const char * lpszName,const char * pszExtension,const char * pszTemplate) override;

      //virtual bool get_temp_file_name(string & str,const char * lpszName,const char * pszExtension) override;

      //service_base * get_service();
      //virtual service_base * allocate_new_service() override;
      //virtual bool init_service() override;

      //virtual bool os_create_service() override;
      //virtual bool os_remove_service() override;

      //virtual bool os_start_service() override;
      //virtual bool os_stop_service() override;

      //virtual void on_service_request(::create * pcreate);

      //virtual bool is_running();

      //virtual string get_mutex_name_gen();

      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this new additional instance creation
      //virtual ::e_status on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId) override;

      /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this new additional instance creation
//      virtual bool on_exclusive_instance_local_conflict(bool & bHandled) override;

            /// return true if this instance might continue execution
      /// bHandled true if some action was done in response to this new additional instance creation
      //virtual bool on_exclusive_instance_local_conflict_id(bool & bHandled, string strId) override;

      /// return true if the external additional instance might continue execution
      /// bHandled true if some action was done in response to the external new additional instance creation
      //virtual ::e_status on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine) override;

      //virtual void on_new_instance(string strModule, const ::id & idPid) override;

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
      //bool gudo_get(const string & strKey, TYPE & t);

      //template < typename TYPE >
      //bool gudo_set(const string & strKey, const TYPE & t);


      //virtual bool assert_user_logged_in();

      //virtual ::e_status     do_request(::create * pcreate) override;
      virtual ::e_status     call_request(::create * pcreate) override;


      //virtual void process_message(::user::message * base) override;

      //virtual void message_handler(::user::message * pusermessage) override;



      //virtual string http_get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema) override;

      //virtual void on_update_matter_locator() override;

      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema) override;
      //virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema) override;

      //virtual string get_locale_schema_dir(const string & strLocale, const string & strSchema) override;
      //virtual string get_locale_schema_dir(const string & strLocale) override;
      //virtual string get_locale_schema_dir() override;

      //virtual void set_locale(const string & pcsz, const ::action_context & action_context) override;

      //virtual void set_schema(const string & pcsz, const ::action_context & action_context) override;

      //virtual void on_set_locale(const string & pcsz, const ::action_context & action_context) override;

      //virtual void on_set_schema(const string & pcsz, const ::action_context & action_context) override;



      //virtual void fill_locale_schema(::str::international::locale_schema & localeschema) override;
      //virtual void fill_locale_schema(::str::international::locale_schema & localeschema,const string & pszLocale,const string & pszSchema) override;

      //virtual bool platform_open_by_file_extension(index iEdge, const char * pszPathName, ::create * pcreate = nullptr) override;
      //virtual bool platform_open_by_file_extension(index iEdge,::create * pcc) override;


      //virtual bool on_start_application() override;

      //virtual bool os_on_start_application() override;

      //virtual bool is_application() const override;


      //DECL_GEN_SIGNAL(_001OnAppExit);
      //virtual bool _001OnAgreeExit() override;
      //virtual void _001OnFranceExit() override;
      //virtual void _001FranceExit() override;


      //virtual string lstr(const ::id & id, string strDefault = "") override;



      //virtual bool do_install();
      //virtual bool do_uninstall();



      //void request(::create * pcommand) override;
      //void on_create(::create * pcreate) override;

//      virtual void dispatch_user_message(::user::message * pusermessage);

      //virtual void throw_not_installed();

      //virtual void play_audio(::payload varFile, bool bSynch = false);

      //virtual void post_critical_error_message(const char * pszMessage, bool bShowLog = true) override;

      //virtual void show_critical_error_log() override;

      //virtual string get_app_user_friendly_task_bar_name() override;

      //virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      //virtual bool compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);

      //virtual bool compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6);

      //virtual void interactive_credentials(::account::credentials * pcredentials) override;

      //virtual ::file::path get_executable_path() override;
      //virtual string get_executable_extension() override;
      //virtual string get_executable_title() override;
      //virtual string get_executable_appid() override;



      //virtual bool on_open_document_file(::payload varFile) override;

      //virtual string get_app_id(string wstr) override;


      //virtual void install_trace(const string & str) override;
      //virtual void install_trace(double dRate) override;
      //virtual bool register_spa_file_type() override;

      //virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration) override;
      //virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;
      //virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration) override;



      virtual bool keyboard_focus_is_focusable(const ::user::primitive * pue) override;
      virtual bool keyboard_focus_OnSetFocus(::user::primitive * pue) override;

      virtual ::user::interaction * main_window();

      virtual __pointer(::user::message) get_user_message(MESSAGE * pmsg);

      virtual bool get_frame(__pointer(::user::interaction) & pinteraction);
      virtual void add_frame(::user::interaction * pwnd);
      virtual void remove_frame(::user::interaction * pwnd);

      virtual bool send_message_to_windows(const ::id & id, wparam wparam, lparam lparam) override; // with tbs in <3

      virtual bool route_message_to_windows(::message::message * pmessage) override; // with tbs in <3


      //virtual void send_language_change_message() override;



      virtual string preferred_experience() override;


      // user virtual ::user::document * place_hold(::user::interaction * pinteraction);


      virtual bool post_message(const ::id & id, wparam wparam = 0, lparam lparam = 0) override;


      //virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon);

      //virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const;

      //virtual void on_control_event(::user::control_event * pevent);



//      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//
////      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);
//
//      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);

      virtual void on_initial_frame_position(::user::frame * pframe) override;

      virtual void on_graphics_ready() override;

      //virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);
      virtual ::type control_type_from_id(const ::id & id, ::user::enum_control_type & econtroltype);


      virtual ::id translate_property_id(const ::id & id) override;
      //virtual property fetch_property(const ::id & id) override;

      //virtual void get_time(struct timeval *point_i32) override;

      virtual void close(::apex::enum_end eend) override;


      //user virtual __pointer(::user::document) defer_create_view(string strView, ::user::interaction * puiParent, ewindowflag ewindowflag, const ::id & id = nullptr);


      virtual void HideApplication() override;


      //virtual ::e_status initialize(::layered * pobjectContext) override;

      //virtual ::e_status process_init() override;

      //virtual ::e_status init1() override; // first initialization
      //virtual ::e_status init2() override; // second initialization
      //virtual ::e_status init3() override; // third initialization and so on...

      //virtual ::e_status init() override; // last initialization

      //virtual ::e_status bergedge_start();
      //virtual ::e_status os_native_bergedge_start() override;

      //virtual void term_application() override;

      //virtual void term() override;

      //virtual ::e_status     main() override;

      //virtual ::aura::application * get_context_application() const override;

      //virtual bool is_system() const override;
      //virtual bool is_session() const override;

      virtual u32 guess_code_page(const string& str) override;

      //virtual i32 _sync_message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::u32 fuStyle) override;

      //virtual bool is_serviceable() const override;


      virtual void pre_translate_message(::message::message* pmessage) override;


      //virtual void install_message_routing(::channel* pchannel) override;


      virtual void EnableShellOpen() override;




      //virtual void _001CloseApplication() override;



      //user virtual void on_create_split_view(::user::split_view* pview);


      //virtual ::type control_type_from_id(const ::id& id, ::user::enum_control_type& econtroltype) override;


      virtual bool base_support() override;

      //virtual string sync_message_box(const string & pszMatter,property_set & propertyset) override;


      //virtual __pointer(::user::interaction) uie_from_point(const ::point_i32& point);

      //virtual bool on_application_menu_action(const char* pszCommand) override;

      //virtual bool on_install() override;
      //virtual bool on_uninstall() override;
      virtual bool on_run_install() override;
      virtual bool on_run_uninstall() override;

      DECL_GEN_SIGNAL(on_application_signal);
      DECL_GEN_SIGNAL(_001OnSwitchContextTheme);


      // open named file, trying to match a regsitered
      // document template to it.
      //virtual void on_request(::create* pcreate) override;

      // overrides for implementation
      virtual bool on_idle(::i32 lCount) override; // return true if more idle processing
      virtual void process_window_procedure_exception(::exception_pointer pe, ::message::message* pmessage) override;

      void EnableModelessEx(bool bEnable);
//#ifdef WINDOWS
//      HENHMETAFILE LoadEnhMetaFile(::u32 uResource);
//#endif
      bool GetResourceData(::u32 nID, const char* lcszType, memory& storage);

#ifdef WINDOWS
      virtual bool OnMessageWindowMessage(MESSAGE * pmsg);

#elif defined(LINUX)
      virtual bool OnX11WindowMessage(void* pev);
#endif

      bool CreateFileFromRawResource(::u32 nID, const char* lcszType, const char* pcszFilePath);

      //virtual lresult GetPaintMsgProc(i32 nCode, wparam wParam, lparam lParam) override;


      void OnUpdateRecentFileMenu(::message::command* pcommand);

      //virtual void send_app_language_changed();
      virtual void route_command_message(::message::command* pcommand) override;




      void EnableHtmlHelp();


      //virtual i32 sync_message_box_timeout(::user::primitive * puiOwner,::payload payload, const char * pszTitle, ::duration durationTimeout,::u32 fuStyle = e_message_box_ok) override;
      //virtual i32 sync_message_box(::user::primitive * puiOwner,const char * pszMessage, const char * pszTitle, ::u32 fuStyle = e_message_box_ok) override;


      //bool on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId) override;

      //virtual bool process_exception(::exception_pointer pe) override;

      //virtual bool on_uninstall() override;

      //virtual bool is_serviceable() const override;

      //virtual bool on_install() override;


      //::user::document* place_hold(::user::interaction* pinteraction) override;



      //virtual bool on_install() override;
      //virtual bool on_application_menu_action(const char * pszCommand) override;


      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle,::user::menu_item * pitem) override;

      // set regsitry key name to be used by application's
      // profile member functions; prevents writing to an INI spfile->
      void SetRegistryKey(const char* pszRegistryKey);

      void SetRegistryKey(::u32 nIDRegistryKey);


      void RegisterShellFileTypes(bool bCompat = false);

      // call after all doc templates are registered
      void UnregisterShellFileTypes();



      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
//#ifdef WINDOWS
//      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld = true);
//#endif

      //// create a DC for the system default printer.
      //::draw2d::graphics* CreatePrinterDC();


      //   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // run this cast as an embedded object.
      bool RunEmbedded();

      // run this cast as an OLE automation server.
      bool RunAutomated();

      // Parse the command line for stock options and commands.
      //   void ParseCommandLine(CCommandLineInfo& rCmdInfo);

      // React to a shell-issued command line directive.
      //   bool ProcessShellCommand(CCommandLineInfo& rCmdInfo);

      // Overridables


      // exiting
      virtual bool save_all_modified() override; // save before exit
      //virtual void HideApplication() override;
      //virtual void close(::aura::e_end eend) override; // close documents before exiting

      // Advanced: to override message boxes and other hooks
      //virtual i32 DoMessageBox(const char * pszPrompt,::u32 nType,::u32 nIDPrompt);


      // Advanced: process async DDE request
      //virtual bool OnDDECommand(LPWSTR pszCommand);


//#ifdef WINDOWS_DESKTOP
//      // Advanced: Help support
//      virtual void WinHelp(uptr dwData,::u32 nCmd = HELP_CONTEXT);
//      virtual void HtmlHelp(uptr dwData,::u32 nCmd = 0x000F);
//      virtual void WinHelpInternal(uptr dwData,::u32 nCmd = HELP_CONTEXT);
//#endif

      // Command Handlers
      // map to the following for file new/open
      void _001OnFileNew();
      void on_file_open();

      // map to the following to enable print setup
      //void OnFilePrintSetup();

      // map to the following to enable help
      //void OnContextHelp();   // shift-F1
      //void OnHelp();          // F1 (uses current action_context)
      //void OnHelpIndex();     // ID_HELP_INDEX
      //void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
      //void OnHelpUsing();     // ID_HELP_USING

      // Implementation

      //void UpdatePrinterSelection(bool bForceDefaults);
      //void SaveStdProfileSettings();  // save options to .INI file



      //void DevModeChange(char * pDeviceName);


      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      i32 get_open_document_count();

      //virtual bool do_prompt_file_name(::payload& varFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument) override;

      //void EnableModeless(bool bEnable); // to disable OLE in-place dialogs


      // helper for message boxes; can work when no application can be found
      //static i32 ShowAppMessageBox(__pointer(application)pApp,const char * pszPrompt,::u32 nType,::u32 nIDPrompt);

      //static void DoEnableModeless(bool bEnable); // to disable OLE in-place dialogs

//#ifdef WINDOWS_DESKTOP
//      // helpers for registration
//      HKEY GetSectionKey(const char* pszSection);
//
//      HKEY GetAppRegistryKey();
//#endif

      //void OnAppExit();
      //// System Policy Settings
      //virtual bool LoadSysPolicies() override; // Override to load policies other than the system policies that aura API loads.
      //bool GetSysPolicyValue(u32 dwPolicyID, bool* pbValue); // returns the policy's setting in the out parameter
      //bool _LoadSysPolicies() noexcept; // Implementation helper
      static const char gen_FileSection[];
      static const char gen_FileEntry[];
      static const char gen_PreviewSection[];
      static const char gen_PreviewEntry[];








      virtual bool does_launch_window_on_startup() override;
      virtual bool activate_app() override;

      // Hooks for your initialization code
      //virtual bool InitApplication() override;



      //virtual ::e_status init_application() override;

      //virtual ::e_status init_instance() override;


//      virtual bool process_exception(::exception_pointer pe) override;





      virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::user::system* pusersystem);




      //      virtual ::aura::file_system & file_system();
      //virtual bool _001OnDDECommand(const char* pcsz) override;

      //user virtual ::user::document* _001OpenDocumentFile(::payload varFile);
      //virtual bool on_open_document_file(::payload varFile) override;
      //DECL_GEN_SIGNAL(_001OnFileNew) override;


      //virtual string get_version();


      //virtual ::user::interaction * get_desktop_window();

      //virtual ::e_status     run() override;

      //::aura::application * get_context_system();

      //virtual bool set_keyboard_layout(const char* pszPath, const ::action_context& action_context) override;


      //::experience::department* experience();


      //virtual void on_change_theme() override;


      inline ::aura::theme* theme() { return m_ptheme.get(); }
      //virtual string get_theme() override;


      virtual ::e_status initialize_contextualized_theme() override;




      //virtual string dialog_box(const char* pszMatter, property_set& propertyset) override;

      virtual i32 track_popup_menu(const char* pszMatter, const ::point_i32& point, __pointer(::user::interaction) puie);

      virtual bool get_fs_size(string& strSize, const char* pszPath, bool& bPending) override;
      virtual bool get_fs_size(i64& i64Size, const char* pszPath, bool& bPending) override;

      virtual void set_title(const char* pszTitle) override;


      virtual bool _001CloseApplicationByUser(__pointer(::user::interaction) pwndExcept);


//#ifdef WINDOWS_DESKTOP
//
//      static BOOL CALLBACK GetAppsEnumWindowsProc(::windowing::window * pwindow, lparam lParam);
//
//#endif

      void update_app_interest();
      void ensure_app_interest();


      //virtual oswindow get_ca2_app_wnd(const char* psz) override;


      //virtual void request_create(::create * pcreate);

      //      virtual void on_exclusive_instance_local_conflict();

      //virtual i32 send_simple_command(const char* psz, void* osdataSender) override;
      //virtual i32 send_simple_command(void* osdata, const char* psz, void* osdataSender) override;

      //virtual ::aura::printer* get_printer(const char* pszDeviceName) override;


      //virtual void assert_valid() const override;
      //virtual void dump(dump_context& dumpcontext) const override;










      virtual __pointer(::apex::application) create_platform(::apex::session* psession) override;





      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/System
      //
      //::user::document * place_hold(::user::interaction * pinteraction)  override;

      /*
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, RECTANGLE_I32 * prectangle);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, RECTANGLE_I32 * prectangle);

      */


      //////////////////////////////////////////////////////////////////////////////////////////////////
      // Session/Session
      //
      //         virtual __pointer(::bergedge::view) get_view();
      //       virtual __pointer(::bergedge::document) get_document();


      //virtual ::e_status add_library(::apex::library * plibrary);

      //virtual ::e_status initialize_userex();
      //virtual ::e_status userfs_init1();
      //virtual ::e_status initialize1_experience();
      //virtual ::e_status userfs_process_init();

      //virtual __pointer(::userex::userex) create_userex();
      //virtual __pointer(::userfs::userfs) create_userfs();




      //virtual void assert_valid() const;
      //virtual void dump(dump_context & action_context) const;


      //virtual void construct();
      //virtual void construct(const char * pszId);


      //virtual void _001OnFileNew();


      //virtual void on_request(::create * pcreate);

      //__pointer(::aura::application) get_context_system();

      //virtual __pointer(::aura::application) assert_running(const char * pszAppdId);









      // pointer < ::cubebase::application >::oattrib
      // or any function needing it
      application& operator = (const application& app)
      {

         UNREFERENCED_PARAMETER(app);

         // do nothing

         return *this;

      }


      virtual void data_on_after_change(::database::client* pclient, const ::database::key& id, const ::payload & payload, ::promise::subject * psubject) override;


      //user virtual ::user::document* open_document_file(::object* pobject, const char* pszFileName);



      virtual i32 GetVisibleTopLevelFrameCountExcept(__pointer(::user::interaction) pwndExcept);
      virtual i32 GetVisibleFrameCount();

      //virtual void on_create_keyboard() override;

      //virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype) override;

      //virtual void set_form_impact_system(::user::impact_system * pdoctemplate,::user::impact_system * pdoctemplateChild,::user::impact_system * pdoctemplatePlaceHolder);

      //user ::user::document* hold(__pointer(::user::interaction) pinteraction);

      //virtual bool platform_open_by_file_extension(int iEdge,const char * pszPathName,application_bias * papplicationbias = nullptr);
      //virtual bool platform_open_by_file_extension(int iEdge,::create * pcc);


      //virtual void on_change_cur_sel(::user::tab* ptab);


      //      virtual void interactive_credentials(::account::credentials * pcredentials) override;
      //      virtual string get_cred(string & strUsername, string & strPassword, string strToken);
      //      virtual void set_cred(string strToken, const char * pszUsername, const char * pszPassword) override;
      //      virtual void set_cred_ok(string strToken, bool bOk) override;

      //user virtual void remove_document_template(::user::impact_system* pimpactsystem);

      //virtual bool _001OnAgreeExit() override;
      //virtual void _001OnFranceExit() override;

      virtual void prepare_form(id id, ::form_document* pdocument);


      virtual void report_error(::exception::exception* pexception, int iMessageFlags, const char* pszTopic) override;


      virtual bool _001CanCloseApplication() override;


      virtual bool on_close_frame_window(::user::frame* pframe) override;




      //application();
      //virtual ~application();


      //virtual ::e_status     initialize(::layered * pobjectContext) override;


      //virtual void install_message_routing(::channel * pchannel) override;

      //virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      //virtual ::e_status process_init() override;

      //virtual ::e_status init_instance() override;

      virtual ::e_status     create_impact_system() override;

      //virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype) override;
      //virtual ::type control_type_from_id(const ::id& id, ::user::enum_control_type& econtroltype) override;


      //virtual void on_create_impact(::user::impact_data* pimpactdata) override;
      //void process_message_filter(i32 code, ::message::message* pmessage) override;



      //virtual __pointer(::user::user) create_user();

      //virtual bool on_thread_on_idle(::thread* pthread, ::i32 lCount) override;



      ///virtual bool process_message() override;

      //i32 hotplugin_host_host_starter_start_sync(const char* pszCommandLine, ::aura::application* papp, ::hotplugin::host* phost, ::hotplugin::plugin* pplugin) override;


      //virtual ::form_property_set * get_form_property_set() override;



      //using ::aura::application::on_control_event;
      //using ::user::form_callback::on_control_event;


      //virtual void remove_document_template(::user::impact_system* pimpactsystem);

      //virtual void term_application() override;

      //virtual void SetCurrentHandles() override;

      //virtual ::draw2d::icon* set_icon(object* pobject, ::draw2d::icon* picon, bool bBigIcon) override;

      //virtual ::draw2d::icon* get_icon(object* pobject, bool bBigIcon) const override;

      //virtual void on_control_event(::user::control_event* pevent) override;

      virtual ::user::interaction* create_menu_interaction();

//      virtual __pointer(::user::document) defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag = e_window_flag_none, const ::id& id = nullptr) override;

      // multimedia

      virtual void on_song_added(const string& str) override;


      // programming
      //DECL_GEN_SIGNAL(on_application_signal);
      //void on_request(::create* pcreate);
      string get_visual_studio_build();


      virtual string sound_path(const char* psz) override;
      virtual string get_default_playlist_path() override;

      //virtual int_bool window_set_mouse_cursor(oswindow window, hcursor hcursor);
//      virtual icon_result load_icon(const ::payload& varFile);

//#ifdef WINDOWS_DESKTOP
//      virtual TCHAR * windows_get_system_cursor(enum_cursor ecursor);
//#endif

#ifdef LINUX
      virtual bool os_on_start_application() override;
#endif

      //virtual bool on_application_menu_action(const char * pszCommand);

   };


} // namespace aura







//CLASS_DECL_AURA ::u32 c_cdecl application_thread_procedure(LPVOID pvoid);

//typedef __pointer(::aura::application) (*LPFN_instantiate_application)(__pointer(::aura::application) pappParent, const char* pszId);

//extern CLASS_DECL_AURA LPFN_instantiate_application g_lpfn_instantiate_application;

//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_AURA BOOL LaunchAppIntoDifferentSession(const char* pszProcess, const char* pszCommand, const char* pszDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi, int iSession = -1);
//
//CLASS_DECL_AURA BOOL LaunchAppIntoSystemAcc(const char* pszProcess, const char* pszCommand, const char* pszDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi);
//
//#endif // WINDOWS_DESKTOP





