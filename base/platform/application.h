#pragma once


namespace base
{


   enum e_end
   {

      end_close,
      end_app,
      end_session,
      end_system

   };


   class CLASS_DECL_BASE application :
      virtual public ::axis::application,
      virtual public ::user::form_callback,
      virtual public ::user::impact_creator,
      virtual public ::filemanager::callback,
      virtual public ::user::document_manager_container
   {
   public:


      //__pointer(::aura::application_menu)       m_papplicationmenu;


      application();
      ~application() override;


      virtual void initialize(::object * pobject) override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      inline ::base::system* get_system() const;
      inline ::base::session* get_session() const;


      virtual __pointer(::user::document) defer_create_view(string strImpact, ::user::interaction* puiParent = nullptr, ewindowflag ewindowflag = ::ewindowflag(), const ::id& id = ::id());

///*
//
//
//      virtual string __get_text(string str) override;
//
//      virtual ::user::style* get_user_style() const;
//      //virtual bool app_data_get(const ::id & id, stream & os) override;
//      //virtual bool app_data_set(const ::id & id, stream & is) override;
//
//      //virtual bool app_data_set(const ::id & id, object & obj) override;
//      //virtual bool app_data_get(const ::id & id, object & obj) override;
//
////      virtual void     interactive_credentials(::account::credentials * pcredentials) override;
//
//      virtual ::database::key calc_data_key() override;
//
//
//      //virtual string load_podata(string strLang, bool bOnlyHeader);
//
//      virtual string load_string(const ::id & id);
//      virtual bool load_string(string & str, const ::id & id);
//      virtual void load_string_table();
//      virtual bool load_cached_string(string & str, const ::id & id, bool bLoadStringTable);
//      virtual bool load_cached_string_by_id(string & str, const ::id & id, bool bLoadStringTable);
//      virtual void load_string_table(const string & pszApp, const string & pszId);
//
//
//
//      virtual bool is_system() const override;
//      virtual bool is_session() const override;
//      virtual bool is_serviceable() const;
//
//
//      virtual ::simpledb::server * simpledb();
//      virtual ::database::server * dataserver();
//
//
//      virtual void verb() override;
//
//
//      virtual bool Ex2OnAppInstall();
//      virtual bool Ex2OnAppUninstall();
//
//      virtual void init_application();
//
//      virtual void init1();
//      virtual void init2();
//      virtual void init3();
//
//
//      virtual void init();
//
//
//      virtual void init_instance();
//
//
//      virtual void     run() override;
//      virtual void     main() override;
//      virtual void     on_run();
//
//      virtual void application_pre_run();
//      //virtual bool initial_check_directrix() override;
//      virtual void os_native_bergedge_start();
//
//
//
//
//
//      virtual void term();
//
//
//      virtual void term_application();
//
//
//
//
//      virtual bool InitApplication();
//
//
//      virtual bool do_install();
//      virtual bool do_uninstall();
//
//
//      virtual bool on_install();
//      virtual bool on_uninstall();
//
//
//
//
//
//      virtual bool update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative);
//      virtual bool update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative, const ::string & strLocale, const ::string & strStyle);
//
//
//      //virtual void SetCurrentHandles() override;
//
//
//      virtual bool process_exception(const ::exception & e) override;
//
//
//      //virtual __pointer(::aura::application) assert_running(const ::string & pszAppId) override;
//
//      virtual bool is_running();
//
//
//
//      virtual void on_request(::create * pcreate) override;
//
//
//
//      virtual bool assert_user_logged_in();
//
//      virtual string matter_as_string(const ::string & pszMatter, const ::string & pszMatter2 = nullptr);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//      virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);
//
//
//      virtual void process_message_filter(i32 code, ::message::message * pmessage) override;
//
//
//
//      virtual void DoWaitCursor(i32 nCode); // 0 => restore, 1=> begin, -1=> end
//
//      virtual void _001CloseApplication();
//
//
//      virtual string get_license_id();
//
//
//
//
//      virtual void process_init();
//
//
//
//
//
//      virtual void TermThread(HINSTANCE hInstTerm);
//
//
//      //virtual void set_env_var(const string & payload, const string & value) override;
//
//
//      virtual ::aura::printer * get_printer(const ::string & pszDeviceName);
//
//
//      virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon);
//
//      virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const;
//
//      virtual void on_service_request(::create * pcreate);
//
//      virtual string get_mutex_name_gen();
//
//      //virtual ::user::interaction * user_interaction_from_oswindow(oswindow oswindow);
//
//
//      virtual i32 hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);
//      virtual i32 hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);
//
//      virtual void on_update_view(::user::impact * pview, ::user::impact * pviewSender, LPARAM lHint, object * pHint);
//
//      virtual void handle(::topic * ptopic, ::context * pcontext) override;
//      virtual void on_notify_control_event(::user::control_event* pevent);
//      virtual void route(::topic * ptopic, ::context * pcontext);
//
//
//
//      virtual bool on_open_document(::user::document * pdocument, ::payload payloadFile);
//      virtual bool on_save_document(::user::document * pdocument, ::payload payloadFile);
//
//
//
//      //inline ::html::html * html() { return puser->m_phtml; }
//
//      //virtual ::html::html * create_html();
//
//      //virtual string http_get(const ::string & strUrl, ::property_set & set) override;
//
//      //virtual bool compress_ungz(const ::stream & os, const ::stream & is) override;
//
//      ///virtual bool compress_ungz(memory_base & mem) override;
//      //virtual bool compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override;
//
//      //virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override;
//
//
//      virtual bool is_local_data() override;
//
//
//      //application();
//      //~application() override;
//
//
//      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema);
//      //virtual string get_locale_schema_dir();
//
//
//      //virtual void initialize(::object * pobject) override;
//
//
//      application_menu & applicationmenu();
//
//
//      virtual ::file::path appconfig_folder();
//
//
//      //void assert_valid() const override;
//      //void dump(dump_context & dumpcontext) const override;
//
//
//      virtual ::file::path get_app_localconfig_folder();
//      virtual ::handle::ini get_ini();
//
//
//      virtual bool app_data_set(const ::id & id, stream & os);
//      virtual bool app_data_get(const ::id & id, stream & is);
//
//      virtual bool app_data_set(const ::id & id, ::object & obj);
//      virtual bool app_data_get(const ::id & id, ::object & obj);
//
//      void install_message_routing(::channel * pchannel) override;
//
//      virtual string dialog_box(const ::string & pszMatter, property_set & propertyset);
//
//      virtual void application_menu_update();
//
//
//      //virtual string calc_data_key();
//
//
//
//      //virtual void notify_changed(const ::id & id, const ::action_context & action_context);
//
//
//      virtual ::file::path local_application_path();
//
//      virtual ::file::path local_application_home_path();
//
//
//      virtual void destroy() override;
//
//
//      //virtual void release_parents() override;
//      virtual ::object * parent_property_set_holder() const override;
//
//
//      virtual bool is_set_finish() const override;
//
//
//      virtual void on_change_theme();
//      virtual string get_theme();
//
//
//      virtual __pointer(::acme::exclusive) get_exclusive(string str, LPSECURITY_ATTRIBUTES psa);
//      virtual bool exclusive_fails(string str, LPSECURITY_ATTRIBUTES psa);
//
//
//      virtual bool start_application(bool bSynch, ::create * pcreate);
//
//
//
//      //virtual void release_children() override;
//      //virtual void merge_command_line(::create * pcommand);
//
////   virtual void merge(::handler * phandler);
//
//      //virtual void record(::create * pcommand);
//
//      //virtual void on_event(::u64 u, ::object * pobject) override;
//      //virtual __pointer(::thread_toolset) create_thread_toolset(::enum_task_tool etool);
//
//
//      //// ca2verses
//      //// os_* functions generally
//      //// reserves a lot of surprises from each
//      //// operating system specific behavior
//      //virtual void os_message_box(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
//
//
//      //virtual void ui_message_box(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
//      //virtual void ui_message_box_timeout(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeOut = duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
//
//
//      //using ::aura::context_thread::message_box;
//      //virtual void message_box(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
//      //virtual void message_box_timeout(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeOut = duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback());
//
//
//      virtual void on_file_new();
//
//
//      virtual string get_title();
//      virtual string_array get_categories();
//
//      virtual void on_create_keyboard();
//      virtual bool set_keyboard_layout(const ::string & pszPath, const ::action_context & action_context);
//
//
//      virtual bool enable_application_events(::object * pobject, bool bEnable);
//
//      virtual bool is_equal_file_path(const ::file::path & path1, const ::file::path & path2);
//
//
//      //virtual bool process_exception(const ::exception & e) override;
//
//
//      //virtual bool is_system() const override;
//      //virtual bool is_session() const override;
//      //virtual bool is_serviceable() const;
//      virtual bool is_user_service() const;
//
//      void set_has_installer(bool bSet);
//
//
//
//      //virtual ::file::path defer_process_path(::file::path path);
//      //virtual ::file::path full_process_path(::file::path path);
//
//      //virtual void DoWaitCursor(i32 nCode); // 0 => restore, 1=> begin, -1=> end
//      virtual void show_wait_cursor(bool bShow = true);
//
//
//
//      //virtual void process_message_filter(i32 code,::message::message * pmessage) override;
//
//      virtual bool on_thread_on_idle(::thread * pthread,::i32 lCount) override;
//
//
//      virtual bool app_set(string strPath, string strValue);
//      virtual string app_get(string strPath, string strDefault = "");
//
//
//      //virtual bool Ex2OnAppInstall();
//      //virtual bool Ex2OnAppUninstall();
//
//      virtual bool on_application_menu_action(const ::string & pszCommand);
//      //virtual void _001CloseApplication();
//
//      //virtual string get_license_id();
//
//      virtual string get_version();
//
//      virtual __pointer(::interprocess_intercommunication) create_interprocess_intercommunication();
//
//      //virtual void process_init();
//      virtual void process_term();
//
//      //virtual void impl_process_init();
//      //virtual void impl_init1();
//      //virtual void impl_init2();
//      //virtual void impl_init3();
//
//      //virtual void impl_process_term();
//      //virtual void impl_term1();
//      //virtual void impl_term2();
//      //virtual void impl_term3();
//
//      //virtual void init1();
//      //virtual void init2();
//      //virtual void init3();
//
//      virtual void term1();
//      virtual void term2();
//      virtual void term3();
//
//      virtual void init_thread() override;
//      //virtual void init_application();
//      //virtual void term_application();
//      virtual void term_thread() override;
//
//      //virtual void init_instance() override;
//      virtual void term_instance();
//
//      //virtual void init();
//      //virtual void term();
//
//      virtual void ca_process_init();
//      virtual void ca_init1();
//      virtual void ca_init2();
//      virtual void ca_init3();
//
//      virtual void ca_term3();
//      virtual void ca_term2();
//      virtual void ca_term1();
//      virtual void ca_process_term();
//
//      // virtual bool is_installing();
//      // virtual bool is_unstalling();
//
//      //virtual string get_version();
//      //virtual void     run() override;
//      //virtual void     main() override;
//      //virtual void     on_run();
//
//      virtual void initial_check_directrix();
//      //virtual void os_native_bergedge_start();
//
//      virtual void pre_run();
//      //virtual void application_pre_run();
//
//      virtual void on_pos_run_thread() override;
//      virtual void pos_run();
//      virtual void application_pos_run();
//
//      //virtual bool InitApplication();
//      virtual void TermApplication();
//
//      //virtual bool on_install();
//      //virtual bool on_uninstall();
//
//      virtual bool system_add_app_install(const ::string & pszId, const ::string & pszBuild);
//
//      //virtual void TermThread(HINSTANCE hInstTerm);
//
//      //virtual void SetCurrentHandles();
//
//      //virtual void set_env_var(const string & payload,const string & value);
//      //virtual itask_t get_thread_id();
//
//
//      virtual bool _001OnDDECommand(const ::string & pcsz);
//
//      virtual void _001EnableShellOpen();
//      virtual void _001OnFileNew(::message::message * pmessage);
//
//
//      virtual string multimedia_audio_get_default_library_name();
//      virtual string multimedia_audio_mixer_get_default_library_name();
//      virtual string veriwell_multimedia_music_midi_get_default_library_name();
//
//      virtual bool get_temp_file_name_template(string & str, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate);
//
//      virtual bool get_temp_file_name(string & str, const ::string & lpszName, const ::string & pszExtension);
//
//      service_base * get_service();
//      virtual service_base * allocate_new_service();
//      virtual bool init_service();
//
//      virtual bool os_create_service();
//      virtual bool os_erase_service();
//
//      virtual bool os_start_service();
//      virtual bool os_stop_service();
//
//      //virtual void on_service_request(::create * pcreate);
//
//      //virtual bool is_running();
//
//      //virtual string get_mutex_name_gen();
//
//      /// return true if this instance might continue execution
//      /// bHandled true if some action was done in response to this new additional instance creation
//      virtual bool on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId);
//
//      /// return true if this instance might continue execution
//      /// bHandled true if some action was done in response to this new additional instance creation
//      virtual bool on_exclusive_instance_local_conflict(bool & bHandled);
//
//            /// return true if this instance might continue execution
//      /// bHandled true if some action was done in response to this new additional instance creation
//      virtual bool on_exclusive_instance_local_conflict_id(bool & bHandled, string strId);
//
//      /// return true if the external additional instance might continue execution
//      /// bHandled true if some action was done in response to the external new additional instance creation
//      virtual bool on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine);
//
//      virtual void on_new_instance(string strModule, const ::id & idPid);
//
//      virtual string get_local_mutex_id();
//      virtual string get_global_mutex_id();
//
//      //virtual ::mutex * get_local_mutex();
//      //virtual ::mutex * get_global_mutex();
//
//      virtual string get_local_mutex_name();
//      virtual string get_local_id_mutex_name();
//      virtual string get_global_mutex_name();
//      virtual string get_global_id_mutex_name();
//
//      virtual bool check_exclusive(bool & bHandled);
//      virtual bool release_exclusive();
//
//      virtual void on_set_scalar(e_scalar escalar,i64 iValue,int iFlags) override;
//      virtual void get_scalar_minimum(e_scalar escalar,i64 & i) override;
//      virtual void get_scalar(e_scalar escalar,i64 & i) override;
//      virtual void get_scalar_maximum(e_scalar escalar,i64 & i) override;
//
//
//
//      bool safe_is_running();
//
//
//      //virtual void on_request(::create * pcreate) override;
//
//      // name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
//      // get/set serializables to user directory
//      template < typename TYPE >
//      bool gudo_get(const ::string & strKey, TYPE & t);
//
//      template < typename TYPE >
//      bool gudo_set(const ::string & strKey, const TYPE & t);
//
//
//      //virtual bool assert_user_logged_in();
//
//      virtual void     do_request(::create * pcreate) override;
//      virtual void     call_request(::create * pcreate) override;
//
//
//      virtual void process_message(::user::message * base) override;
//
//      virtual void message_handler(::user::message * pusermessage) override;
//
//
//
//      virtual string http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema);
//
//      //virtual void on_update_matter_locator() override;
//
//      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
//      virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema);
//
//      virtual string get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema);
//      virtual string get_locale_schema_dir(const ::string & strLocale);
//      virtual string get_locale_schema_dir() override;
//
//      virtual void set_locale(const string & pcsz, const ::action_context & action_context);
//
//      virtual void set_schema(const string & pcsz, const ::action_context & action_context);
//
//      virtual void on_set_locale(const string & pcsz, const ::action_context & action_context);
//
//      virtual void on_set_schema(const string & pcsz, const ::action_context & action_context);
//
//
//
//      virtual void fill_locale_schema(::text::international::locale_schema & localeschema);
//      virtual void fill_locale_schema(::text::international::locale_schema & localeschema,const string & pszLocale,const string & pszSchema);
//
//      virtual bool platform_open_by_file_extension(index iEdge, const ::string & pszPathName, ::create * pcreate = nullptr);
//      virtual bool platform_open_by_file_extension(index iEdge,::create * pcc);
//
//
//      virtual bool on_start_application();
//
//      virtual bool os_on_start_application();
//
//      virtual bool is_application() const override;
//
//
//      DECLARE_MESSAGE_HANDLER(on_message_app_exit);
//      virtual bool _001OnAgreeExit();
//      virtual void france_exit();
//      virtual void _001FranceExit();
//
//
//      virtual string lstr(const ::id & id, string strDefault = "") override;
//
//
//
//      //virtual bool do_install();
//      //virtual bool do_uninstall();
//
//
//
//      //void request(::create * pcommand) override;
//      //void on_create(::create * pcreate) override;
//
////      virtual void dispatch_user_message(::user::message * pusermessage);
//
//      //virtual void throw_not_installed();
//
//      //virtual void play_audio(::payload payloadFile, bool bSynch = false);
//
//      virtual void post_critical_error_message(const ::string & pszMessage, bool bShowLog = true);
//
//      virtual void show_critical_error_log();
//
//      virtual string get_app_user_friendly_task_bar_name();
//
//      virtual void handle(::topic * ptopic, ::context * pcontext) override;
//
//      //virtual bool compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);
//
//      //virtual bool compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6);
//
//      virtual void interactive_credentials(::account::credentials * pcredentials) override;
//
//      virtual ::file::path get_executable_path();
//      virtual string get_executable_extension();
//      virtual string get_executable_title();
//      virtual string get_executable_appid();
//
//
//
//      virtual bool on_open_document_file(::payload payloadFile);
//
//      virtual string get_app_id(string wstr);
//
//
//      virtual void install_trace(const ::string & str);
//      virtual void install_trace(double dRate);
//      virtual bool register_spa_file_type();
//
//      virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration);
//      virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration);
//      virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration);
//
//
//
//      virtual bool keyboard_focus_is_focusable(::user::primitive * pue);
//      virtual bool keyboard_focus_OnSetFocus(::user::primitive * pue);
//
//      virtual ::user::interaction * main_window();
//
////         virtual __pointer(::user::message) get_message_base(MESSAGE * pmsg) override;
//
//
//      virtual bool get_frame(__pointer(::user::interaction) & pinteraction);
//      virtual void add_frame(::user::interaction * puserinteraction);
//      virtual void erase_frame(::user::interaction * puserinteraction);
//
//      virtual bool send_message_to_windows(const ::id & id, wparam wparam, lparam lparam); // with tbs in <3
//
//      virtual bool route_message_to_windows(::message::message * pmessage); // with tbs in <3
//
//
//      virtual void send_language_change_message();
//
//
//      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);
//
//
//      virtual string preferred_experience();
//
//
      virtual ::user::document * place_hold(::user::interaction * pinteraction);
//
//
//      virtual bool post_message(const ::id & id, WPARAM wParam = 0, lparam lParam = 0) override;
//
//
//      //virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon);
//
//      //virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const;
//
//      //virtual void handle(::topic * ptopic, ::context * pcontext);
//
//
//
//      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//
//      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);
//
//      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);
//
//      virtual void on_initial_frame_position(::user::frame * pframe);
//
//      virtual void on_graphics_ready();
//
//      //virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype);
//      virtual ::type control_type_from_id(const ::id & id, ::user::enum_control_type & econtroltype);
//
//
//      virtual ::id translate_property_id(const ::id & id) override;
//      //virtual property fetch_property(const ::id & id) override;
//
//      virtual void get_time(struct timeval *point_i32);
//
//      virtual void close(e_end eend);
//
//
//      virtual __pointer(::user::document) defer_create_view(string strImpact, ::user::interaction * puiParent, ewindowflag ewindowflag, const ::id & id = nullptr);
//
//
//      virtual void HideApplication();
//
//
//      //virtual void initialize(::object * pobject) override;
//
//      //virtual void process_init() override;
//
//      //virtual void init1() override; // first initialization
//      //virtual void init2() override; // second initialization
//      //virtual void init3() override; // third initialization and so on...
//
//      //virtual void init() override; // last initialization
//
//      //virtual void bergedge_start();
//      //virtual void os_native_bergedge_start() override;
//
//      //virtual void term_application() override;
//
//      //virtual void term() override;
//
//      //virtual void     main() override;
//
//      //virtual ::aura::application * get_application() const override;
//
//      //virtual bool is_system() const override;
//      //virtual bool is_session() const override;
//
//      virtual u32 guess_code_page(const string& str);
//
//      //virtual i32 _sync_message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 fuStyle) override;
//
//      //virtual bool is_serviceable() const override;
//
//
//      virtual void pre_translate_message(::message::message* pmessage) override;
//
//
//      //virtual void install_message_routing(::channel* pchannel) override;
//
//
//      virtual void EnableShellOpen();
//
//
//
//
//      //virtual void _001CloseApplication() override;
//
//
//
      virtual void on_create_split_view(::user::split_view* pview);
//
//
//      //virtual ::type control_type_from_id(const ::id& id, ::user::enum_control_type& econtroltype) override;
//
//
//      virtual bool base_support();
//
//      //virtual string sync_message_box(const string & pszMatter,property_set & propertyset) override;
//
//
//      virtual __pointer(::user::interaction) uie_from_point(const ::point_i32& point);
//
//      //virtual bool on_application_menu_action(const ::string & pszCommand) override;
//
//      //virtual bool on_install() override;
//      //virtual bool on_uninstall() override;
//      virtual bool on_run_install();
//      virtual bool on_run_uninstall();
//
//      DECLARE_MESSAGE_HANDLER(on_application_signal);
//      DECLARE_MESSAGE_HANDLER(_001OnSwitchContextTheme);
//
//
//      // open named file, trying to match a regsitered
//      // document template to it.
//      //virtual void on_request(::create* pcreate) override;
//
//      // overrides for implementation
//      virtual bool on_idle(::i32 lCount); // return true if more idle processing
//      virtual void process_window_procedure_exception(const ::exception & e, ::message::message* pmessage) override;
//
//      void EnableModelessEx(bool bEnable);
//#ifdef WINDOWS
//      HENHMETAFILE LoadEnhMetaFile(::u32 uResource);
//#endif
//      bool GetResourceData(::u32 nID, const ::string & lcszType, memory& storage);
//
//#ifdef WINDOWS
//      virtual bool OnMessageWindowMessage(MESSAGE * pmsg);
//
//#elif defined(LINUX)
//      virtual bool OnX11WindowMessage(void* pev);
//#endif
//
//      bool CreateFileFromRawResource(::u32 nID, const ::string & lcszType, const ::string & pcszFilePath);
//
//      virtual LRESULT GetPaintMsgProc(i32 nCode, WPARAM wParam, LPARAM lParam);
//
//
//      void OnUpdateRecentFileMenu(::message::command* pcommand);
//
//      //virtual void send_app_language_changed();
//      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
//
//
//
//
//      void EnableHtmlHelp();
//
//
//      //virtual i32 sync_message_box_timeout(::user::primitive * puiOwner,::payload payload, const ::string & pszTitle, ::duration durationTimeout,::u32 fuStyle = e_message_box_ok) override;
//      //virtual i32 sync_message_box(::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 fuStyle = e_message_box_ok) override;
//
//
//      //bool on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId) override;
//
//      //virtual bool process_exception(const ::exception & e) override;
//
//      //virtual bool on_uninstall() override;
//
//      //virtual bool is_serviceable() const override;
//
//      //virtual bool on_install() override;
//
//
//      //::user::document* place_hold(::user::interaction* pinteraction) override;
//
//
//
//      //virtual bool on_install() override;
//      //virtual bool on_application_menu_action(const ::string & pszCommand) override;
//
//
//      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle,::user::menu_item * pitem) override;
//
//      // set regsitry key name to be used by application's
//      // profile member functions; prevents writing to an INI spfile->
//      void SetRegistryKey(const ::string & pszRegistryKey);
//
//      void SetRegistryKey(::u32 nIDRegistryKey);
//
//
//      void RegisterShellFileTypes(bool bCompat = false);
//
//      // call after all doc templates are registered
//      void UnregisterShellFileTypes();
//
//
//
//      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
//      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld = true);
//
//      // create a DC for the system default printer.
//      ::draw2d::graphics* CreatePrinterDC();
//
//
//      //   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);
//
//      // run this cast as an embedded object.
//      bool RunEmbedded();
//
//      // run this cast as an OLE automation server.
//      bool RunAutomated();
//
//      // Parse the command line for stock options and commands.
//      //   void ParseCommandLine(CCommandLineInfo& rCmdInfo);
//
//      // React to a shell-issued command line directive.
//      //   bool ProcessShellCommand(CCommandLineInfo& rCmdInfo);
//
//      // Overridables
//
//
//      // exiting
//      virtual bool save_all_modified(); // save before exit
//      //virtual void HideApplication() override;
//      //virtual void close(::aura::e_end eend) override; // close documents before exiting
//
//      // Advanced: to override message boxes and other hooks
//      //virtual i32 DoMessageBox(const ::string & pszPrompt,::u32 nType,::u32 nIDPrompt);
//
//
//      // Advanced: process async DDE request
//      //virtual bool OnDDECommand(LPWSTR pszCommand);
//
//
////#ifdef WINDOWS_DESKTOP
////      // Advanced: Help support
////      virtual void WinHelp(uptr dwData,::u32 nCmd = HELP_CONTEXT);
////      virtual void HtmlHelp(uptr dwData,::u32 nCmd = 0x000F);
////      virtual void WinHelpInternal(uptr dwData,::u32 nCmd = HELP_CONTEXT);
////#endif
//
//      // Command Handlers
//      // map to the following for file new/open
//      void _001OnFileNew();
//      void on_file_open();
//
//      // map to the following to enable print setup
//      void OnFilePrintSetup();
//
//      // map to the following to enable help
//      void OnContextHelp();   // shift-F1
//      void OnHelp();          // F1 (uses current action_context)
//      void OnHelpIndex();     // ID_HELP_INDEX
//      void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
//      void OnHelpUsing();     // ID_HELP_USING
//
//      // Implementation
//
//      void UpdatePrinterSelection(bool bForceDefaults);
//      void SaveStdProfileSettings();  // save options to .INI file
//
//
//
//      void DevModeChange(char * pDeviceName);
//
//
//      // Finds number of opened document items owned by templates
//      // registered with the doc manager.
//      i32 get_open_document_count();
//
//      //virtual bool do_prompt_file_name(::payload& payloadFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument) override;
//
//      void EnableModeless(bool bEnable); // to disable OLE in-place dialogs
//
//
//      // helper for message boxes; can work when no application can be found
//      //static i32 ShowAppMessageBox(__pointer(application)pApp, const ::string & pszPrompt,::u32 nType,::u32 nIDPrompt);
//
//      static void DoEnableModeless(bool bEnable); // to disable OLE in-place dialogs
//
//#ifdef WINDOWS_DESKTOP
//      // helpers for registration
//      HKEY GetSectionKey(const ::string & pszSection);
//
//      HKEY GetAppRegistryKey();
//#endif
//
//      void OnAppExit();
//      // System Policy Settings
//      virtual bool LoadSysPolicies(); // Override to load policies other than the system policies that aura API loads.
//      bool GetSysPolicyValue(u32 dwPolicyID, bool* pbValue); // returns the policy's setting in the out parameter
//      bool _LoadSysPolicies() noexcept; // Implementation helper
//      static const char gen_FileSection[];
//      static const char gen_FileEntry[];
//      static const char gen_PreviewSection[];
//      static const char gen_PreviewEntry[];
//
//
//
//
//
//
//
//
//      virtual bool does_launch_window_on_startup();
//      virtual bool activate_app();
//
//      // Hooks for your initialization code
//      //virtual bool InitApplication() override;
//
//
//
//      //virtual void init_application() override;
//
//      //virtual void init_instance() override;
//
//
////      virtual bool process_exception(const ::exception & e) override;
//
//
//
//
//
//      virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);
//
//
//
//
//      //      virtual ::aura::file_system & file_system();
//      //virtual bool _001OnDDECommand(const ::string & pcsz) override;
//
//      virtual ::user::document* _001OpenDocumentFile(::payload payloadFile);
//      //virtual bool on_open_document_file(::payload payloadFile) override;
//      //DECLARE_MESSAGE_HANDLER(_001OnFileNew) override;
//
//
//      //virtual string get_version();
//
//
//      virtual ::user::interaction * get_desktop_window();
//
//      //virtual void     run() override;
//
//      //::aura::application * get_context_system();
//
//      //virtual bool set_keyboard_layout(const ::string & pszPath, const ::action_context& action_context) override;
//
//
//      //::experience::department* experience();
//
//
//      //virtual void on_change_theme() override;
//
//
//      inline ::aura::theme* theme() { return m_ptheme.get(); }
//      //virtual string get_theme() override;
//
//
//      virtual void initialize_contextualized_theme();
//
//
//
//
//      //virtual string dialog_box(const ::string & pszMatter, property_set& propertyset) override;
//
//      virtual i32 track_popup_menu(const ::string & pszMatter, const ::point_i32& point, __pointer(::user::interaction) puie);
//
//      virtual bool get_fs_size(string& strSize, const ::string & pszPath, bool& bPending);
//      virtual bool get_fs_size(i64& i64Size, const ::string & pszPath, bool& bPending);
//
//      virtual void set_title(const ::string & pszTitle);
//
//
//      virtual bool _001CloseApplicationByUser(__pointer(::user::interaction) puserinteractionExcept);
//
//
//#ifdef WINDOWS_DESKTOP
//
//      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam);
//
//#endif
//
//      void update_app_interest();
//      void ensure_app_interest();
//
//
//      virtual oswindow get_ca2_app_wnd(const ::string & psz);
//
//
//      //virtual void request_create(::create * pcreate);
//
//      //      virtual void on_exclusive_instance_local_conflict();
//
//      virtual i32 send_simple_command(const ::string & psz, void* osdataSender);
//      virtual i32 send_simple_command(void* osdata, const ::string & psz, void* osdataSender);
//
//      //virtual ::aura::printer* get_printer(const ::string & pszDeviceName) override;
//
//
//      //void assert_valid() const override;
//      //virtual void dump(dump_context& dumpcontext) const override;
//
//
//
//
//
//
//
//
//
//
//      virtual __pointer(::aura::application) create_platform(::aura::session* psession) override;
//
//
//
//
//
//      //////////////////////////////////////////////////////////////////////////////////////////////////
//      // System/System
//      //
//      //::user::document * place_hold(::user::interaction * pinteraction)  override;
//
//      /*
//      virtual ::count get_monitor_count();
//      virtual bool  get_monitor_rectangle(index i, RECTANGLE_I32 * prectangle);
//
//      virtual ::count get_desk_monitor_count();
//      virtual bool  get_desk_monitor_rect(index i, RECTANGLE_I32 * prectangle);
//
//      */
//
//
//      //////////////////////////////////////////////////////////////////////////////////////////////////
//      // Session/Session
//      //
//      //         virtual __pointer(::bergedge::impact) get_view();
//      //       virtual __pointer(::bergedge::document) get_document();
//
//
//      //virtual void add_library(::acme::library * plibrary);
//
//      //virtual void initialize_userex();
//virtual void userfs_init1();
////virtual void initialize1_experience();
//virtual void userfs_process_init();
//
////virtual __pointer(::userex::userex) create_userex();
////virtual __pointer(::userfs::userfs) create_userfs();
//
//
//
//
////void assert_valid() const override;
////virtual void dump(dump_context & action_context) const;
//
//
////virtual void construct();
////virtual void construct(const ::string & pszId);
//
//
////virtual void _001OnFileNew();
//
//
////virtual void on_request(::create * pcreate);
//
////__pointer(::aura::application) get_context_system();
//
////virtual __pointer(::aura::application) assert_running(const ::string & pszAppdId);
//
//
//
//
//
//
//
//
//
//// pointer < ::cubebase::application >::oattrib
//// or any function needing it
//application& operator = (const application& app)
//{
//
//   __UNREFERENCED_PARAMETER(app);
//
//   // do nothing
//
//   return *this;
//
//}
//
//
//virtual void data_on_after_change(::database::client* pclient, const ::database::key& id, const ::payload & payload, ::update* pupdate) override;
//
//
//virtual ::user::document* open_document_file(::object* pobject, const ::string & pszFileName);
//
//
//
//virtual i32 GetVisibleTopLevelFrameCountExcept(__pointer(::user::interaction) puserinteractionExcept);
//virtual i32 GetVisibleFrameCount();
//
////virtual void on_create_keyboard() override;
//
////virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype) override;
//
////virtual void set_form_impact_system(::user::impact_system * pdoctemplate,::user::impact_system * pdoctemplateChild,::user::impact_system * pdoctemplatePlaceHolder);
//
//::user::document* hold(__pointer(::user::interaction) pinteraction);
//
////virtual bool platform_open_by_file_extension(int iEdge, const ::string & pszPathName,application_bias * papplicationbias = nullptr);
////virtual bool platform_open_by_file_extension(int iEdge,::create * pcc);
//
//
virtual void on_change_cur_sel(::user::tab* ptab);
//
//
////      virtual void interactive_credentials(::account::credentials * pcredentials) override;
////      virtual string get_cred(string & strUsername, string & strPassword, string strToken);
////      virtual void set_cred(string strToken, const ::string & pszUsername, const ::string & pszPassword) override;
////      virtual void set_cred_ok(string strToken, bool bOk) override;
//
//virtual void erase_document_template(::user::impact_system* pimpactsystem);
//
////virtual bool _001OnAgreeExit() override;
////virtual void france_exit() override;
//
//virtual void prepare_form(id id, ::form_document* pdocument);
//
//
//virtual void report_error(::exception* pexception, int iMessageFlags, const ::string & pszTopic);
//
//
//
//virtual bool on_close_frame_window(::user::frame* pframe);
//
//
//
//
////application();
////~application() override;
//
//
////virtual void     initialize(::object * pobject) override;
//
//
////void install_message_routing(::channel * pchannel) override;
//
////virtual void handle(::topic * ptopic, ::context * pcontext) override;
//
////virtual void process_init() override;
//
////virtual void init_instance() override;
//
virtual void     create_impact_system() override;
//
////virtual ::type user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype) override;
////virtual ::type control_type_from_id(const ::id& id, ::user::enum_control_type& econtroltype) override;
//
//
virtual void on_create_impact(::user::impact_data* pimpactdata) override;
////void process_message_filter(i32 code, ::message::message* pmessage) override;
//
//
//
////virtual __pointer(::user::user) create_user();
//
////virtual bool on_thread_on_idle(::thread* pthread, ::i32 lCount) override;
//
//
//
//virtual bool process_message() override;
//
////i32 hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application* papp, ::hotplugin::host* phost, ::hotplugin::plugin* pplugin) override;
//
//
////virtual ::form_property_set * get_form_property_set() override;
//
//
//
////using ::aura::application::handle_event;
//using ::user::form_callback::handle_event;
//
//
////virtual void erase_document_template(::user::impact_system* pimpactsystem);
//
////virtual void term_application() override;
//
////virtual void SetCurrentHandles() override;
//
////virtual ::draw2d::icon* set_icon(object* pobject, ::draw2d::icon* picon, bool bBigIcon) override;
//
////virtual ::draw2d::icon* get_icon(object* pobject, bool bBigIcon) const override;
//
////virtual void handle(::topic * ptopic, ::context * pcontext) override;
//
//virtual ::user::interaction* create_menu_interaction();
//
////      virtual __pointer(::user::document) defer_create_view(string strImpact, ::user::interaction* puiParent, ewindowflag ewindowflag = e_window_flag_none, const ::id& id = nullptr) override;
//
//      // multimedia
//
//virtual void on_song_added(const string& str);
//
//
//// programming
////DECLARE_MESSAGE_HANDLER(on_application_signal);
////void on_request(::create* pcreate);
//string get_visual_studio_build();
//
//
//virtual string sound_path(const ::string & psz);
//virtual string get_default_playlist_path();
//
//
//
//*/

//
//CLASS_DECL_BASE ::u32 c_cdecl application_thread_procedure(LPVOID pvoid);
//
//typedef __pointer(::aura::application) (*LPFN_instantiate_application)(__pointer(::aura::application) pappParent, const ::string & pszId);
//
//extern CLASS_DECL_BASE LPFN_instantiate_application g_lpfn_instantiate_application;
//
//#ifdef WINDOWS_DESKTOP
//
//CLASS_DECL_BASE BOOL LaunchAppIntoDifferentSession(const ::string & pszProcess, const ::string & pszCommand, const ::string & pszDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi, int iSession = -1);
//
//CLASS_DECL_BASE BOOL LaunchAppIntoSystemAcc(const ::string & pszProcess, const ::string & pszCommand, const ::string & pszDir, STARTUPINFO* psi, PROCESS_INFORMATION* ppi);
//
//#endif // WINDOWS_DESKTOP
//
//
//
//
//
      virtual void close(::apex::enum_end eend) override;


      virtual void on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context) override;


   };


} // namespace base

