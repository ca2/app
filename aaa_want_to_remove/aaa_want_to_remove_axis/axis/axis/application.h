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


      ::pointer<::simpledb::server>                         m_psimpledb;


      ::user::interaction *                           m_puserinteractionMain;




      application();
      ~application() override;


      virtual void     initialize(::particle * pparticle) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //virtual bool app_data_get(const ::atom & atom, stream & os) override;
      //virtual bool app_data_set(const ::atom & atom, stream & is) override;

      //virtual bool app_data_set(const ::atom & atom, object & obj) override;
      //virtual bool app_data_get(const ::atom & atom, object & obj) override;

//      virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      virtual string calc_data_key() override;

      virtual string load_string(const ::atom & atom) override;
      virtual bool load_string(string & str, const ::atom & atom) override;
      virtual void load_string_table() override;
      virtual bool load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable) override;
      virtual bool load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable) override;
      virtual void load_string_table(const string & pszApp, const string & pszId) override;



      virtual bool is_system() const override;
      virtual bool is_session() const override;
      virtual bool is_serviceable() const override;


      virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver();


      virtual void verb() override;


      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      virtual void init_application() override;

      virtual void init1() override;
      virtual void init2() override;
      virtual void init3() override;


      virtual void init() override;


      virtual void init_instance() override;


      virtual void     run() override;
      virtual void     main() override;
      virtual void     on_run() override;

      virtual void application_pre_run() override;
      //virtual bool initial_check_directrix() override;
      virtual void os_native_bergedge_start() override;





      virtual void term() override;


      virtual void term_application() override;




      virtual bool InitApplication() override;


      virtual bool do_install() override;
      virtual bool do_uninstall() override;


      virtual bool on_install() override;
      virtual bool on_uninstall() override;





      virtual bool update_appmatter(::sockets::socket_handler * handler, ::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative);
      virtual bool update_appmatter(::sockets::socket_handler * handler, ::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative, const ::string & strLocale, const ::string & strStyle);


      virtual void SetCurrentHandles() override;


      virtual bool process_exception(::exception_pointer e) override;


      //virtual ::pointer<::aura::application>assert_running(const ::string & pszAppId) override;

      virtual bool is_running() override;



      virtual void on_request(::request * prequest) override;



      virtual bool assert_user_logged_in() override;

      virtual string matter_as_string(const ::string & pszMatter, const ::string & pszMatter2 = nullptr);














      virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);


      virtual void process_message_filter(i32 code, ::message::message * pmessage) override;



      virtual void DoWaitCursor(i32 nCode) override; // 0 => restore, 1=> begin, -1=> end

      virtual void _001CloseApplication() override;


      virtual string get_license_id() override;




      virtual void process_init() override;





      virtual void TermThread(HINSTANCE hInstTerm) override;


      //virtual void set_env_var(const string & payload, const string & value) override;


      virtual ::aura::printer * get_printer(const ::string & pszDeviceName);


      virtual ::draw2d::icon * set_icon(object * pparticle, ::draw2d::icon * picon, bool bBigIcon) override;

      virtual ::draw2d::icon * get_icon(object * pparticle, bool bBigIcon) const override;

      virtual void on_service_request(::create * pcreate) override;

      virtual string get_mutex_name_gen() override;

      virtual ::user::primitive * window_from_os_data(void * pdata);


      virtual i32 hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr) override;
      virtual i32 hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr);

      virtual void on_update_impact(::user::impact * pimpact, ::user::impact * pviewSender, LPARAM lHint, object* pHint);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;



      virtual bool on_open_document(::user::document * pdocument, ::payload payloadFile);
      virtual bool on_save_document(::user::document * pdocument, ::payload payloadFile);



      //inline ::html::html * html() { return puser->m_phtml; }

      //virtual ::html::html * create_html();

      //virtual string http_get(const ::string & strUrl, ::property_set & set) override;

      //virtual bool compress_ungz(const ::stream & os, const ::stream & is) override;

      ///virtual bool compress_ungz(memory_base & mem) override;
      //virtual bool compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override;

      //virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override;


      virtual bool is_local_data() override;


   };


} // namespace axis










