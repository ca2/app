#pragma once


namespace apex
{


   class CLASS_DECL_APEX system:
      virtual public ::app_core,
      virtual public class ::system,
      virtual public ::apex::context
#ifndef WINDOWS
      ,virtual public ::exception_translator
#endif
   {
   public:


      __reference(::application)                   m_papplicationStartup;

      __composite(::apex::system)                        m_psystemParent;

      // apex commented
      //__composite(::apex::audio)                         m_paudio;

      // apex commented
      //__composite(::apex::multimedia)                    m_pmultimedia;

      string_map < string_map < PFN_factory > > m_mapFactoryExchange;

      // __composite(::apex::estamira)                      m_pestamira;

      //::type                                             m_typePaneTabView;
#ifdef APPLE_IOS

      plane_system *                                     m_pplanesystem;

#endif

#ifdef __DEBUG

      __composite(::dump_context)                        m_pdumpcontext;

#endif // __DEBUG

      __composite(::sockets::sockets)                    m_psockets;

      // apex commented
      //::object *                                         m_pDraw2dFactoryExchange;
      // apex commented
      //__pointer(::draw2d::draw2d)                        m_pdraw2d;

      ::file::path                                       m_pathConfig;
      ::file::path                                       m_pathCa2Roaming;


      ::mutex                                            m_mutexUserChildren;
      //__composite(class imaging)                         m_pimaging;

      __composite(class ::datetime::department)          m_pdatetime;
      __composite(::crypto::crypto)                      m_pcrypto;
      //__composite(class ::account::user_set)             m_puserset;

      //__composite_array(service_base)                    m_serviceptra;
      
      __composite_array(service)                         m_servicecompositea;

      __composite(class ::apex::log)                     m_ptrace;

      // apex commented
      //__composite(math::math)                            m_pmath;

      __composite(geometry::geometry)                    m_pgeometry;

      __composite(::apex::str)                           m_puserstr;

      ::apex::session::map                               m_sessionmap;

      //__composite(::gpu::approach)                       m_pgpu;

      ::mutex                                            m_mutexLibrary;
      ::apex::library_map                                m_mapLibrary;
      string_map < PFN_NEW_APEX_LIBRARY >                m_mapNewApexLibrary;
      ::apex::library_map                                m_mapLibCall;

      ::mutex                                            m_mutexContainerizedLibrary;
      ::string_map < ::apex::library_map >               m_mapContainerizedLibrary;


      // for lesser cooperative GUI applications
      //bool                                               m_bProdevianMouse;
      __composite(class ::str::base64)                   m_pbase64;

      ::string_to_string                                 m_mapAppLibrary;
      __composite(class machine_event_central)           m_pmachineeventcentral;

      float                                              m_dpi;

      //void *                                           m_ftlibrary;

      ::payload                                          m_varFile;
//    ::payload                                          m_

      __pointer(::mutex)                                 m_pmutexUserAppData;
      __pointer(::mutex)                                 m_pmutexSystemAppData;

      __pointer(::mutex)                                 m_pmutexMatter;

      //bool
      m_bGudoNetCache;

      __composite(::operating_system::department)                 m_pprocess;

      __composite(::parallelization::threading)           m_pthreading;
      ::e_display                                         m_edisplay;
      size_t                                             m_nSafetyPoolSize; // ideal size_i32

      bool                                               m_bFinalizeIfNoSessionSetting;
      bool                                               m_bFinalizeIfNoSession;


//      __composite(::html::html)                          m_phtml;
      __composite(::url::department)                     m_purldepartment;

      __composite(::dir_system)                          m_pdirsystem;
      __composite(::file_system)                         m_pfilesystem;

      string                                             m_strInstallVersion;
      string                                             m_strInstallPlatform;

      ::duration                                               m_durationMainStart;
      ::duration                                               m_durationAfterApplicationFirstRequest;

      //::mutex                                 m_spmutexOpenweatherCity;

      //string_array                                       m_straCityLo;
      //string_array                                       m_straCity;
      //i64_array                                          m_iaIds;
      //double_array                                       m_daLon;
      //double_array                                       m_daLat;

      //string_map < __pointer(openweather_city) >         m_mapCity;

      string                                             m_strIosHome;
      string                                             m_strIosTemp;

//      __composite(::net::email_department)               m_pemaildepartment;

      string_array                                            m_straCommandLineAccumul;
      string_array                                            m_straCommandLineExtra;
      ::duration                                               m_durationCommandLineLast;
      int                                                m_iCommandLineDelay;
      ::task_pointer                                m_pthreadCommandLine;


      bool                                               m_bSystemSynchronizedCursor;
      bool                                               m_bSystemSynchronizedScreen;




      task_group_map                                   m_taskgroupmap;
      task_tool_map                                    m_tasktoolmap;


      //stridsp(type)                                      m_typemap;
      //::string_to_string                               m_mapAppLibrary;
      //string_to_int_to_string                            m_mapEnumToName;
      //string_to_string_to_int                            m_mapNameToEnum;
      //string_array                                       m_straCityLo;
      //string_array                                       m_straCity;
      //i64_array                                          m_iaIds;
      //double_array                                       m_daLon;
      //double_array                                       m_daLat;

      //string_map < __pointer(::acme::library) >          m_mapLibrary;

      //string_map < __pointer(openweather_city) >                   m_mapCity;


      //system_heap(::object* pobject)
      //{

      //}


      //index                                        m_iNewEdge;

#ifdef WINDOWS_DESKTOP

      ::u32                                         m_uiWindowsTaskbarCreatedMessage;

#endif

      ::mutex                                        m_mutex;
      //__composite(::filehandler::handler)            m_pfilehandler;


      ::mutex                                        m_mutexDelete;


      //    class ::apex::stra                           m_stra;
      //    class ::apex::service                        m_service;


      // class ::apex::patch* m_ppatch;

      //      __pointer(::apex::run_start_installer)              m_prunstartinstaller;

            //__pointer(::apex::session::map)                     m_pbergedgemap;
            //__pointer_array(::apex::session)                         m_planesessionptra;

      __composite(class ::apex::history)                m_phistory;

      //      ::sockets::net                               m_net;
      //      __pointer(::apex::filehandler::handler)  m_spfilehandler;


      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      //bool                                         m_bInitApplication;
      //bool                                         m_bInitApplicationResult;
      //bool                                         m_bProcessInitialize;
      //bool                                         m_bProcessInitializeResult;

      //strid_map < ::acme::library* >              m_idmapCreateViewLibrary;

      //__pointer_array(::acme::library)                         m_libraryspa;

#ifdef _UWP

      Agile < ::winrt::Windows::UI::Core::CoreWindow >      m_window;

#endif



      system();
      virtual ~system();


      void common_construct();

      virtual ::e_status  initialize(::object * pobject) override;


      virtual ::application* get_main_application() override;


      virtual ::e_status init();
      //virtual ::e_status init_instance() override;
      //virtual void term_instance() override;
      virtual ::e_status inline_init() override;
      virtual ::e_status inline_term() override;

      virtual ::e_status init_system();
      virtual void term_system();

      virtual ::e_status on_system_construct();

      virtual ::e_status on_start_system();

      virtual ::e_status start();

      virtual void term();

      virtual string get_application_server_name();

      virtual ::acme::library* lib(const char* psz);
      //CLASS_DECL_APEX::acme::library* lib(const char* psz);
      //
      //template < typename FUNCTION >
      //FUNCTION library_function(const char* pszLibrary)
      //{

      //   return lib(pszLibrary)->get<decltype(&entry)>(#entry))

      //}


      virtual bool task_get_run() const override;


      virtual ::e_status create_os_node() override;


      //::thread * get_task(itask_t itask);
      //itask_t get_thread_id(::thread * pthread);
      //void set_thread(itask_t itask, ::thread * pthread);
      //void unset_thread(itask_t itask, ::thread * pthread);
      //::url::department & url() { return m_urldepartment; }


      //inline ::gpu::approach* get_gpu() { if (!m_pgpu) create_gpu(); return m_pgpu.get(); };
      //inline ::gpu::approach* gpu() { return m_pgpu.get(); };
      //virtual ::e_status create_gpu();


      //::task_group * task_group(::enum_priority epriority = ::e_priority_none);

      //::task_tool * task_tool(::enum_task_tool etool);


      virtual __pointer(::subject) new_subject(const MESSAGE& message);

      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const char * pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const char * pszVersion) override;
      //virtual string install_get_latest_build_number(const char * pszVersion) override;
      //virtual i32 install_start(const char * pszCommandLine, const char * pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      //virtual ::install::canvas * install_create_canvas();
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      //virtual int install_canvas_increment_mode();

      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const char * pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const char * pszVersion) override;
      //virtual string install_get_latest_build_number(const char * pszVersion) override;
      //virtual i32 install_start(const char * pszCommandLine,const char * pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      //inline ::apex::node * node() { return (::apex::node *) m_pnode->layer(LAYERED_APEX); }

      //virtual ::layered * get_layered_window(oswindow oswindow);


      virtual ::e_status process_init();

      virtual ::e_status init1();

      virtual ::e_status init2();

      //virtual ::e_status defer_xml();

      virtual __pointer(::data::node) load_xml(const char * pszXml);

      virtual ::e_status verb() override; // ambigous inheritance from ::apex::system/::axis::application


      virtual bool is_system() const override;


      virtual string crypto_md5_text(const ::string & str);


      //virtual ::e_status start() override;

      //virtual ::e_status create_html();

      //virtual __pointer(::apex::session) on_create_session() override;

      virtual void on_request(::create * pcreate) override;

      //virtual void construct(const char * pszAppId);

      //virtual bool initialize_application() override;

      //virtual i32 exit_instance();
      //virtual bool destroy();

      virtual ::e_status destroy() override;




      //virtual bool verb();





      //virtual bool process_initialize();

      //virtual bool process_init();

      //virtual bool init1();

      //virtual bool init2();

      //virtual bool is_system();






      //virtual ::apex::session * query_session(index iEdge) override;




      //virtual string dir_appmatter_locator(::object * pobject);


      virtual void hist_hist(const char * psz);


      //virtual void on_request(::create * pcreate);


      //virtual u32 crc32(u32 dwPrevious, const char * psz);


      virtual string url_encode(const ::string & str);


      void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      virtual string get_locale_schema_dir() override;


      //virtual ::e_status     initialize_system(::object * pobject, app_core * pappcore);


      //__pointer(::thread_tools) create_thread_tools(::enum_task_tool etool);
      //thread_tools * tools(::enum_priority epriority);
      //thread_toolset * toolset(e_tool etool);

      // apex commented
      //class ::user::window_map                     &  window_map();


      __pointer(::acme::library) open_component_library(const char* pszComponent, const char* pszImplementation);

      ::e_status ([a-z0-9_]+)_factory(const char* pszComponent, const char* pszImplementation);

      __pointer(::acme::library) open_containerized_component_library(const char * pszComponent, const char * pszImplementation);

      ::extended::transport < ::acme::library > ([a-z0-9_]+)_factory(const char * pszComponent, const char * pszImplementation);

      ::e_status ([a-z0-9_]+)_factory(const char* pszComponent, const char * pszImplementation, PFN_factory pfnFactoryExchange);

      // apex commented
      //virtual void defer_audio();

      // apex commented
      //virtual ::apex::audio * defer_get_audio();

      // apex commented
      //virtual void defer_multimedia();

      // apex commented
      //virtual ::apex::multimedia * defer_get_multimedia();

      //class ::apex::os                             &  os();
      //class base_factory                           &  factory_item();


      ::apex::str                                  &  str();
      ::operating_system::department                        &  process();

      //using acme::system::process;

      class ::str::base64                          &  base64();
      class ::apex::log                            &  log();
      class ::machine_event_central                &  machine_event_central();
      inline ::parallelization::threading           *  threading() { return m_pthreading; }

      geometry::geometry                           &  geometry()
      {

         return *m_pgeometry;

      }
      //inline  class imaging & imaging() { return *m_pimaging; }

      virtual ::sockets::sockets & sockets() { return *m_psockets; }

      //math::math                                   &  math()
      //{

      //   return *m_pmath;

      //}

      // apex commented
      //inline class ::draw2d::draw2d                & draw2d() { return *m_pdraw2d; }


      inline ::url::department                     &  url()
      {

         return *m_purldepartment;   // only usable from base.dll and dependants

      }


      //inline class ::compress_department           &  compress()
      //{

      //   return *m_pcompress;   // only usable from base.dll and dependants

      //}




      //inline ::file::system_dir & dir() { return *m_spdir; }
      //inline ::file::system_file & file() { return *m_spfile; }


      //::net::email_department                & email();

      //__pointer(::account::user_set)                userset();

      ::datetime::department                 & datetime();


      //virtual string url_encode(const ::string & str);

      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes);

      //::mutex * get_openweather_city_mutex();


      //virtual os_local & oslocal();


      template < typename T >
      inline T * cast_clone(T * p)
      {

         return ::clone(p);

      }


      virtual ::e_status browser(string strUrl, string strBrowser, string strProfile, string strTarget);
      virtual ::e_status open_profile_link(string strUrl, string strProfile, string strTarget) override;


      virtual void __set_thread_on() override;

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName, const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName, const char * pszId);


      //template < class T >
      //::type * type_info()
      //{

      //   return get_type_info(typeid(T));

      //}


      //virtual ::type * get_type_info(const ::std::type_info & info);

      //::type * get_type_info(const ::id & idType)
      //{

      //   if(idType.is_empty())
      //      return nullptr;

      //   synchronous_lock synchronouslock(&m_mutexFactory);

      //   return m_typemap[idType].m_p;

      //}


      //virtual void discard_to_factory(::object * pca);

      //bool on_application_menu_action(const char * pszCommand);


      virtual ::e_status initialize_sockets();


      virtual bool on_get_task_name(string& strTaskName) override;

      virtual ::acme::library * on_get_library(const char * pszLibrary);

      virtual ::acme::library * get_library(const char * pszLibrary, bool bOpenCa2 = false);


      virtual ::u32 os_post_to_all_threads(const ::id & id,wparam wparam = 0,lparam lparam = 0);


      virtual void session_add(index iEdge, ::apex::session * psession);
      virtual void session_erase(index iEdge);




      //virtual ::e_status init_system();

      //virtual ::e_status process_init();

      //virtual ::e_status init_draw2d();
      //virtual ::e_status ([a-z0-9_]+)_factory(::factory::factory * pfactory);
      //virtual string draw2d_get_default_library_name();

      //virtual bool ([a-z0-9_]+)_factory(::factory::factory * pfactory);
      //virtual string imaging_get_default_library_name();

      virtual ::e_status init_thread() override;
      virtual void term_thread() override;


      //virtual void post_to_all_threads(const ::id& id, wparam wparam, lparam lparam);


      virtual ::e_status thread_loop() override;

      //virtual ::e_status init();

      //virtual ::e_status init1();

      //virtual ::e_status init2();

      virtual ::e_status post_creation_requests();

      //virtual void term_system();

      virtual void term2();

      virtual void term1();

      //virtual void term();

      virtual void TermSystem();


      virtual void process_term();


      //virtual bool is_system() const override;





      virtual i32 _001OnDebugReport(i32 i1,const char * psz1,i32 i2,const char * psz2,const char * psz3,va_list args);
      virtual i32 _debug_logging_report(i32 iReportType, const char * pszFilename, i32 iLinenumber, const char * iModuleName, const char * pszFormat, va_list list);
      virtual bool assert_failed_line(const char * pszFileName,i32 iLine);

      virtual bool on_assert_failed_line(const char * pszFileName,i32 iLine);






      virtual ::e_status initialize_log(const char * pszId);


      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale, const ::action_context & action_context);
      virtual void appa_set_schema(const char * pszStyle, const ::action_context & action_context);

      virtual bool assert_running_global(const char * pszAppName,const char * pszId = nullptr);
      virtual bool assert_running_local(const char * pszAppName,const char * pszId = nullptr);

      //__pointer(application) assert_running(const char * pszAppId);

      virtual ::count get_application_count();


      //virtual string crypto_md5_text(const ::string & str);

      //inline class ::http::system                  & http()
      //{
      //   return *m_sphttpsystem;
      //}

      class ::crypto::crypto                       & crypto();


      virtual ::file::path local_get_matter_cache_path();
      virtual ::file::path local_get_matter_cache_path(string strMatter);
      virtual ::file::path local_get_matter_path();
      virtual ::file::path local_get_matter_path(string strMatter);

      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache(bool bSave = true);
      virtual bool map_application_library(const char * pszLibrary);


      virtual void install_progress_add_up(int iAddUp = 1);

      virtual ::e_status create_session(index iEdge = 0);

      virtual __transport(::apex::session) on_create_session(index iEdge);

      virtual ::apex::session * session(index iEdge = 0);

      //virtual void on_request(::create * pcreate) override;

      virtual __pointer(regex) create_regular_expression(const char * pszStyle, const string& str);
      virtual __pointer(regex_context) create_regular_expression_context(const char* pszStyle, int iCount);
      //virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);


      virtual string get_system_platform();
      virtual string get_system_configuration();
      //virtual string get_latest_build_number(const char * pszConfiguration, const char * pszAppId);




      //#ifndef _UWP

      virtual void get_time(micro_duration * pmicroduration);

      //#endif


      virtual void on_start_find_applications_from_cache();
      virtual void on_end_find_applications_from_cache(stream & is);

      virtual void on_end_find_applications_to_cache(stream & os);

      virtual void on_map_application_library(::acme::library & library);

      //virtual void defer_check_exit();



      virtual ::e_status do_request(::create * pcreate) override;

      //virtual void defer_check_openweather_city_list();

      //virtual openweather_city * openweather_find_city(string strQuery);
      //virtual index openweather_find_city2(string strQuery, string & strCit, i64 & iId, double & dLat, double & dLon);
      //virtual index openweather_find_city2(string strQ1, string strQ2, string & strCit, i64 & iId, double & dLat, double & dLon, bool bPrefix);

#ifdef ANDROID
//#pragma message("at macos??")
      virtual bool android_set_user_wallpaper(string strUrl);
      virtual bool android_get_user_wallpaper(string & strUrl);

#endif

      virtual bool defer_accumulate_on_open_file(string_array stra, string strExtra);

      virtual bool merge_accumulated_on_open_file(::create * pcreate);

      virtual bool on_open_file(::payload payloadFile, string strExtra);

      // apex commented
      //virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);

      //virtual bool initialize_native_window1();

      //virtual void * initialize_native_window2(const ::rectangle_i32 & rectangle);


      virtual void on_os_text(e_os_text etext, string strText);

      // apex commented
      //virtual ::user::interaction_impl * impl_from_handle(void * posdata);
      //virtual ::user::interaction * ui_from_handle(void * posdata);


      //void enum_display_monitors();
//
//#if defined(WINDOWS)
//      //#pragma message("at macos??")
//      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, RECTANGLE_I32 * prcMonitor, LPARAM dwData);
//
//      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, RECTANGLE_I32 * prcMonitor);
//
//#endif


      virtual void on_extra(string str);

      virtual string standalone_setting(string str);
      virtual bool set_standalone_setting(string str, string strSetting);


      //virtual void on_event(::u64 u, ::object * pobject) override;


      virtual void on_initial_frame_position(::user::frame * pframe);

      virtual void on_graphics_ready();

      virtual void process_machine_event_data(machine_event_data * pdata);



      virtual void __tracea(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz) override;


      virtual string get_user_language();
      virtual bool set_user_language(::application * papp, index iSel);
      virtual bool set_user_language(::application * papp, string strLang);

      void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);

      //      void commander(string strUrl, string strWeather, string strUser, ::file::path path, string strParam);

      void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      ::e_status     firefox(string strUrl, string strBrowser, string strProfile, string strParam);
      ::e_status     get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory);



      //virtual ::e_status  initialize_system(::object* pobject, app_core* pappcore) override;

      virtual void discard_to_factory(__pointer(object) pca);

      //virtual bool is_system() const override;

      //virtual ::e_status process_init() override;

      //virtual ::e_status init2() override;

      //virtual ::e_status init_system() override;

      //virtual void term() override;

      //virtual void term_system() override;


      //virtual i32 main();
      ///virtual ::e_status InitApplication() override;

      //virtual ::e_status init() override;
      //virtual ::e_status init1() override;
      //virtual ::e_status init3() override;

      //virtual ::e_status bergedge_start() override;


      //virtual ::e_status initialize_rich_text();


      //virtual index get_new_bergedge(application_bias * pbiasCreation = nullptr);

      //__pointer_array(::apex::session) &    planesessionptra();


      //virtual bool base_support() override;


      DECLARE_MESSAGE_HANDLER(on_application_signal);


      ::e_status set_history(::apex::history* phistory);


      //__pointer(::acme::library) on_get_library(const char* pszLibrary) override;


      //virtual ::apex::session *  get_platform(index iEdge,application_bias * pbiasCreation = nullptr);


      //virtual void on_request(::create* pcreate) override;

      //      virtual __pointer(::handler) handler();





      //virtual i32 main();

      //virtual void on_allocation_error(const ::string& str, ::object* pobjectSometimes) override;

      //virtual __pointer(::apex::session) on_create_session() override;


//      ::apex::stra                           & stra();
      //    ::apex::service                        & service();
      ::apex::history& hist();

      //class ::apex::patch& patch();

      //::http::system                         & http();

      //::filehandler::handler& filehandler();




#ifdef LINUX

      //virtual ::e_status defer_initialize_x11();
      //virtual bool sn_start_context();

#endif




      //bool sync_load_url(string& str, const char* pszUrl, ::account::user* puser = nullptr, ::http::cookies* pcookies = nullptr);
      bool sync_load_url(string& str, const char* pszUrl,  ::http::cookies* pcookies = nullptr);





      //      u32 guess_code_page(const ::string & str);

#ifdef _UWP

      virtual bool get_window_rect(RECTANGLE_I32* prectangle);


#endif

      //virtual void post_fork_uri(const char * pszUri,application_bias * papplicationbias);



//      virtual bool wait_twf(::duration tickTimeout = U32_INFINITE_TIMEOUT);








      virtual string get_host_location_url();

      //virtual ::e_status add_view_library(::acme::library* plibrary);

      //virtual void get_cursor_position(POINT_I32 * ppoint);

      virtual bool is_thread() const override;

      //virtual ::e_status do_request(::create* pcommand) override;



      void assert_valid() const override;
      void dump(dump_context& action_context) const override;


      virtual ::e_status     main() override;
      //virtual void hist_hist(const char* psz) override;


      //virtual void defer_calc_os_dark_mode();

      //virtual ::type get_pane_tab_view_type_info();
      //virtual ::type get_simple_frame_window_type_info();
      //virtual ::type get_simple_child_frame_type_info();

      //virtual void on_start_find_applications_from_cache() override;
      //virtual void on_end_find_applications_from_cache(stream& is) override;

      //virtual void on_end_find_applications_to_cache(stream& os) override;

      //virtual void on_map_application_library(::acme::library& library) override;

      //virtual void on_graphics_ready() override;



      //system();
      //virtual ~system();


      ///virtual ::e_status initialize_system(::object* pobject, app_core* pappcore) override;


      //virtual ::e_status process_init() override;
      //virtual void term_system() override;

      //virtual __pointer(::apex::session) on_create_session() override;

      //virtual void set_active_guie(::user::interaction* pinteraction);
      //virtual void set_focus_guie(::user::interaction* pinteraction);



      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      //virtual int install_canvas_increment_mode() override;


      virtual bool do_events();


      void post_quit_to_all_threads();
      void post_to_all_threads(const ::id& id, wparam wparam, lparam lparam);

      //virtual bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle) override;

      //virtual ::count get_monitor_count() override;

      //bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle) override;


      //virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
      //virtual ::user::interaction * ui_from_handle(void * pdata) override;

      virtual void on_subject(::subject * psubject) override;
      virtual void handle(::subject * psubject, ::context * pcontext) override;

      // virtual void on_command_create(::create* pcreate);

      //virtual bool initialize_native_window1() override;

      //virtual ::acme::library* load_library(const char* pszLibrary);

      virtual void application_main(int argc, char *argv[], const char * pszCommandLine);

      virtual int console_end(::e_status estatus);


      virtual __pointer(::extended::future < ::conversation >) message_box(const char* pszText, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;


   };


   CLASS_DECL_APEX ::mutex * get_image_mutex();

} // namespace apex






//#ifndef __DEBUG
//
//#include "apex/inline/factory_item.cpp"
//
//#endif // __DEBUG



//CLASS_DECL_APEX ::apex::system * create_apex_system(app_core * pappcore);
CLASS_DECL_APEX ::apex::system * create_apex_system();




#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define finish(::property_object * pobject)(enum_value) psystem->set_enum_text(enum_value, TOSTRING(enum_value))


//
//
//inline ::traits & traits(::object * p)
//{
//
//   auto traits = psystem->m_traits[p];
//
//   if (traits.m_pobjectTrait != p)
//   {
//
//      traits.m_pobjectTrait = p;
//
//   }
//
//   return traits;
//
//}






// void CLASS_DECL_APEX __start_core_system_main(::base::system * psystem);

#ifdef _UWP

CLASS_DECL_APEX int app_core_main(const char* psz);

#endif

