#pragma once


namespace axis
{


   class CLASS_DECL_AXIS application :
      virtual public ::aura::application,
      virtual public ::database::client
   {
   public:


      bool                                            m_bInitializeDataCentral;
      // bool                                            m_bAxisProcessInitialize;
      // bool                                            m_bAxisProcessInitializeResult;

      // bool                                            m_bAxisInitializeInstance;
      // bool                                            m_bAxisInitializeInstanceResult;

      // bool                                            m_bAxisInitialize1;
      // bool                                            m_bAxisInitialize1Result;

      // bool                                            m_bAxisInitialize;
      // bool                                            m_bAxisInitializeResult;

      string                                          m_strLicense;


      bool                                            m_bUpdateMatterOnInstall;


      i32                                             m_iWaitCursorCount;         // for wait cursor (>0 => waiting)


      __pointer(::simpledb::server)                          m_psimpledb;


      ::user::interaction *                           m_pwndMain;




      application();
      virtual ~application();


      virtual ::e_status     initialize(::layered * pobjectContext) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      //virtual bool app_data_get(const ::id & id, stream & os) override;
      //virtual bool app_data_set(const ::id & id, stream & is) override;

      //virtual bool app_data_set(const ::id & id, object & obj) override;
      //virtual bool app_data_get(const ::id & id, object & obj) override;

//      virtual ::e_status     interactive_credentials(::account::credentials * pcredentials) override;

      virtual string calc_data_key() override;

      virtual string load_string(const ::id & id) override;
      virtual bool load_string(string & str, const ::id & id) override;
      virtual void load_string_table() override;
      virtual bool load_cached_string(string & str, const ::id & id, bool bLoadStringTable) override;
      virtual bool load_cached_string_by_id(string & str, const ::id & id, bool bLoadStringTable) override;
      virtual void load_string_table(const string & pszApp, const string & pszId) override;



      virtual bool is_system() const override;
      virtual bool is_session() const override;
      virtual bool is_serviceable() const override;


      virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver();


      virtual ::e_status verb() override;


      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      virtual ::e_status init_application() override;

      virtual ::e_status init1() override;
      virtual ::e_status init2() override;
      virtual ::e_status init3() override;


      virtual ::e_status init() override;


      virtual ::e_status init_instance() override;


      virtual ::e_status     run() override;
      virtual ::e_status     main() override;
      virtual ::e_status     on_run() override;

      virtual ::e_status application_pre_run() override;
      //virtual bool initial_check_directrix() override;
      virtual ::e_status os_native_bergedge_start() override;





      virtual void term() override;


      virtual void term_application() override;




      virtual bool InitApplication() override;


      virtual bool do_install() override;
      virtual bool do_uninstall() override;


      virtual bool on_install() override;
      virtual bool on_uninstall() override;





      virtual bool update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative);
      virtual bool update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative, const string & strLocale, const string & strStyle);


      virtual void SetCurrentHandles() override;


      virtual bool process_exception(::exception_pointer e) override;


      //virtual __pointer(::aura::application) assert_running(const char * pszAppId) override;

      virtual bool is_running() override;



      virtual void on_request(::create * pcreate) override;



      virtual bool assert_user_logged_in() override;

      virtual string matter_as_string(const char * pszMatter, const char * pszMatter2 = nullptr);














      virtual bool do_prompt_file_name(payload & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);


      virtual void process_message_filter(i32 code, ::message::message * pmessage) override;



      virtual void DoWaitCursor(i32 nCode) override; // 0 => restore, 1=> begin, -1=> end

      virtual void _001CloseApplication() override;


      virtual string get_license_id() override;




      virtual ::e_status process_init() override;





      virtual void TermThread(HINSTANCE hInstTerm) override;


      //virtual void set_env_var(const string & payload, const string & value) override;


      virtual ::aura::printer * get_printer(const char * pszDeviceName);


      virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon) override;

      virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const override;

      virtual void on_service_request(::create * pcreate) override;

      virtual string get_mutex_name_gen() override;

      virtual ::user::primitive * window_from_os_data(void * pdata);


      virtual i32 hotplugin_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr) override;
      virtual i32 hotplugin_host_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);

      virtual void on_update_view(::user::impact * pview, ::user::impact * pviewSender, LPARAM lHint, object* pHint);

      virtual void on_control_event(::user::control_event * pevent) override;



      virtual bool on_open_document(::user::document * pdocument, payload varFile);
      virtual bool on_save_document(::user::document * pdocument, payload varFile);



      //inline ::html::html * html() { return puser->m_phtml; }

      //virtual ::html::html * create_html();

      //virtual string http_get(const string & strUrl, ::property_set & set) override;

      //virtual bool compress_ungz(const ::stream & os, const ::stream & is) override;

      ///virtual bool compress_ungz(memory_base & mem) override;
      //virtual bool compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override;

      //virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override;


      virtual bool is_local_data() override;


   };


} // namespace axis










