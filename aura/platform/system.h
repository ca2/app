#pragma once


namespace aura
{


   class CLASS_DECL_AURA system:
      virtual public ::aqua::system,
      virtual public ::aura::context
   {
   public:


//#ifdef _UWP
//
//      
//      ::universal_windows::directx_application_source ^                   m_applicationsource;
//
//
//#endif

      bool m_bAvoidFirstResponder;

      //__composite(::aura::system)                        m_psystemParent;

      // string_map < string_map < PFN_factory_exchange > > m_mapFactoryExchange;

//      __composite(::aura::estamira)                      m_pestamira;

      ::type                                             m_typePaneTabView;
#ifdef APPLE_IOS

      plane_system *                                     m_pplanesystem;

#endif

#ifdef __DEBUG

      //__composite(::dump_context)                        m_pdumpcontext;

#endif // __DEBUG

      //__composite(::sockets::sockets)                    m_psockets;


      __pointer(::windowing::window)                       m_pwindowMain;


      __pointer(::matter)                                  m_pDraw2dFactoryExchange;
      __pointer(::draw2d::draw2d)                          m_pdraw2d;

      //::file::path                                       m_pathConfig;
      //::file::path                                       m_pathCa2Roaming;

      //::mutex                                            m_mutexThread;
      //thread_map                                         m_threadmap;
      //thread_id_map                                      m_threadidmap;
      //::mutex                                            m_mutexThreadOn;
      //map < itask_t, itask_t >                        m_mapThreadOn;

      ::mutex                                            m_mutexUserChildren;
      __composite(class imaging)                         m_pimaging;

      //__composite(class ::datetime::department)          m_pdatetime;
      //__composite(::crypto::crypto)                      m_pcrypto;
      //__composite(class ::account::user_set)             m_puserset;

      //__pointer_array(service_base)                      m_serviceptra;
      //__composite(class ::xml::department)               m_pxml;
      //__composite(class ::aura::log)                     m_ptrace;
      //__composite(math::math)                            m_pmath;
      //__composite(geometry::geometry)                    m_pgeometry;

      //__composite(::aura::str)                           m_puserstr;

      //::aura::session::map                               m_sessionmap;

      __composite(::gpu::approach)                       m_pgpu;

      //::mutex                                            m_mutexLibrary;
      //string_map < __pointer(::acme::library) >          m_mapLibrary;
      //string_map < PFN_NEW_AURA_LIBRARY >                m_mapNewAuraLibrary;
      //string_map < __pointer(::acme::library) >          m_mapLibCall;



      // for lesser cooperative GUI applications
      bool                                                  m_bProdevianMouse;
      //__composite(class ::str::base64)                   m_pbase64;

      //::string_to_string                                 m_mapAppLibrary;
      //__composite(class machine_event_central)           m_pmachineeventcentral;

      //float                                              m_dpi;

      //void *                                             m_ftlibrary;

//      ::payload                                                m_varFile;
////      ::payload                                                m_
//
//      ::mutex                                 m_spmutexUserAppData;
//      ::mutex                                 m_spmutexSystemAppData;
//
//      ::mutex                                 m_spmutexMatter;
//
//      bool                                               m_bGudoNetCache;
//
//      __composite(::operating_system::department)                 m_pprocess;
//
//      __composite(::parallelization::threading)           m_pthreading;
//      ::e_display                                         m_edisplay;
//      size_t                                             m_nSafetyPoolSize; // ideal size_i32
//
//      bool                                               m_bFinalizeIfNoSessionSetting;
//      bool                                               m_bFinalizeIfNoSession;

//#ifdef _UWP
//
//      ::universal_windows::directx_framework_view ^                          m_frameworkview;
//
//#endif

//
////      __composite(::html::html)                          m_phtml;
//      __composite(::url::department)                     m_purldepartment;
//
//      __composite(::dir_system)                          m_pdirsystem;
//      __composite(::file_system)                         m_pfilesystem;
//
//      string                                             m_strInstallVersion;
//      string                                             m_strInstallPlatform;
//
//      ::duration                                               m_durationMainStart;
//      ::duration                                               m_durationAfterApplicationFirstRequest;
//
//
//
//      //::mutex                                 m_spmutexOpenweatherCity;
//
//      //string_array                                       m_straCityLo;
//      //string_array                                       m_straCity;
//      //i64_array                                          m_iaIds;
//      //double_array                                       m_daLon;
//      //double_array                                       m_daLat;
//
//      //string_map < __pointer(openweather_city) >         m_mapCity;
//
//      string                                             m_strIosHome;
//      string                                             m_strIosTemp;
//
////      __composite(::net::email_department)               m_pemaildepartment;
//
//      string_array                                            m_straCommandLineAccumul;
//      string_array                                            m_straCommandLineExtra;
//      ::duration                                               m_durationCommandLineLast;
//      int                                                m_iCommandLineDelay;
//      ::task_pointer                                m_pthreadCommandLine;
//
//
//      bool                                               m_bSystemSynchronizedCursor;
//      bool                                               m_bSystemSynchronizedScreen;
//
//#ifdef WINDOWS_DESKTOP
//
////#pragma message("at macos??")
//      raw_array < MONITORINFO >                          m_monitorinfoa;
//      raw_array < HMONITOR >                             m_hmonitora;
//      raw_array < MONITORINFO >                          m_monitorinfoaDesk;
//
//#else
//
//      rectangle_i32_array                                         m_rectangleaMonitor;
//      rectangle_i32_array                                         m_rectangleaWork;
//
//#endif
//
//    //factory_map                                    m_factorymap;

      map < ::file::path, ::image_pointer >                m_mapImage;

      //__composite(::user::window_map)                      m_pwindowmap;


      //critical_section                                   m_csEnumText;
      //string_map < i64_map < string > >                  m_mapEnumToText;
      //string_map < string_map < i64 > >                  m_mapTextToEnum;
      //task_group_map                                   m_taskgroupmap;
      //task_tool_map                                    m_tasktoolmap;


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

      enum_message                                 m_emessageWindowsTaskbarCreatedMessage;

#endif

      //::mutex                                        m_mutex;
      ////__composite(::filehandler::handler)            m_pfilehandler;


      //::mutex                                        m_mutexDelete;


      //    class ::aura::stra                           m_stra;
      //    class ::aura::service                        m_service;


      // class ::aura::patch* m_ppatch;

      //      __pointer(::aura::run_start_installer)              m_prunstartinstaller;

            //__pointer(::aura::session::map)                     m_pbergedgemap;
            //__pointer_array(::aura::session)                         m_planesessionptra;

      //__composite(class ::aura::history)                m_phistory;

      //      ::sockets::net                               m_net;
      //      __pointer(::aura::filehandler::handler)  m_spfilehandler;


      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      //bool                                         m_bInitApplication;
      //bool                                         m_bInitApplicationResult;
      //bool                                         m_bProcessInitialize;
      //bool                                         m_bProcessInitializeResult;

      strid_map < ::acme::library* >                  m_idmapCreateViewLibrary;

      __pointer_array(::acme::library)          m_libraryspa;

#ifdef _UWP

      __reference(::universal_windows::interaction_impl)            m_pimplMain;
      //Agile < ::winrt::Windows::UI::Core::CoreWindow >      m_window;

#endif

      system();
      ~system() override;


      void common_construct();

      virtual ::e_status  initialize(::object * pobject) override;

      virtual void on_add_session(::apex::session* papexsession) override;

      virtual ::e_status init() override;
      //virtual ::e_status init_instance() override;
      //virtual void term_instance() override;
      virtual ::e_status inline_init() override;
      virtual ::e_status inline_term() override;


      virtual void on_finish_launching();


//#ifdef LINUX
//
//      virtual ::e_status os_application_system_run() override;
//
//#endif


//      virtual ::e_status init_system() override;
//      virtual void term_system() override;


      virtual ::e_status system_main() override;

      virtual void term() override;

      virtual ::e_status system_prep() override;

      //::url::department                           & url()     { return m_urldepartment; }

      //::thread * get_task(itask_t itask);
      //itask_t get_thread_id(::thread * pthread);
      //void set_thread(itask_t itask, ::thread * pthread);
      //void unset_thread(itask_t itask, ::thread * pthread);

      ::aura::estamira * estamira();


      inline ::aura::session* get_session() { return m_pcontext && m_pcontext->m_papexsession ? m_pcontext->m_papexsession->m_paurasession : nullptr; }
      inline ::aura::node* node() { return m_pnode ? m_pnode->m_pauranode : nullptr; }

      inline ::gpu::approach* get_gpu() { if (!m_pgpu) create_gpu(); return m_pgpu.get(); };
      inline ::gpu::approach* gpu() { return m_pgpu.get(); };
      virtual ::e_status create_gpu();

      
      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const ::string & pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const ::string & pszVersion) override;
      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
      //virtual i32 install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      //virtual ::install::canvas * install_create_canvas();
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      //virtual int install_canvas_increment_mode();

      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const ::string & pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const ::string & pszVersion) override;
      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
      //virtual i32 install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      virtual ::e_status node_factory_exchange() override;

      virtual ::e_status process_init() override;

      virtual ::e_status init1() override;

      virtual ::e_status init2() override;

      virtual ::e_status initialize_context() override;

      //virtual ::e_status defer_xml();

      virtual __pointer(::data::node) load_xml(const ::string & pszXml) override;

      virtual ::e_status verb() override; // ambigous inheritance from ::aura::system/::axis::application


      //virtual bool is_system() const override;


      virtual string crypto_md5_text(const ::string & str) override;


      //virtual __pointer(::extended::future < ::conversation >) _message_box(oswindow oswindow, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;
      //virtual ::enum_dialog_result message_box_timeout(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future()) override;


      //virtual ::e_status create_html();

      //virtual __pointer(::aura::session) on_create_session() override;

      //virtual void on_request(::create * pcreate) override;

      //virtual void construct(const ::string & pszAppId);

      //virtual bool initialize_application() override;

      //virtual i32 exit_instance();
      //virtual bool destroy();

      virtual ::e_status destroy() override;




      //virtual bool verb();

      //virtual ::e_status main_user_async(const ::routine & routine, ::enum_priority epriority = e_priority_normal) override;


      //virtual bool process_initialize();

      //virtual bool process_init();

      //virtual bool init1();

      //virtual bool init2();

      //virtual bool is_system();



      //virtual ::aura::session * query_session(index iEdge) override;




      //virtual string dir_appmatter_locator(::object * pobject);


      //virtual void hist_hist(const ::string & psz);


      //virtual void on_request(::create * pcreate);


      //virtual u32 crc32(u32 dwPrevious, const ::string & psz);


      virtual string url_encode(const ::string & str) override;


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      virtual string get_locale_schema_dir() override;


      //virtual ::e_status     initialize_system(::object * pobject, app_core * pappcore);


      //__pointer(::thread_tools) create_thread_tools(::enum_task_tool etool);
      //thread_tools * tools(::enum_priority epriority);
      //thread_toolset * toolset(e_tool etool);

      //class ::user::window_map                     &  window_map();


      //__pointer(::acme::library) open_component_library(const ::string & pszComponent, const ::string & pszImplementation);

      //::e_status do_factory_exchange(const ::string & pszComponent, const ::string & pszImplementation);

      //::e_status set_factory_exchange(const ::string & pszComponent, const ::string & pszImplementation, PFN_factory_exchange pfnFactoryExchange);


      //class ::aura::os                             &  os();
      //class base_factory                           &  factory();


      //::aura::str                                  &  str();
      //::operating_system::department                        &  process();


      //::xml::department                            &  xml();
      //class ::str::base64                          &  base64();
      //class ::aura::log                            &  log();
      //class ::machine_event_central                &  machine_event_central();
      //inline ::parallelization::threading           *  threading() { return m_pthreading; }

      //geometry::geometry                           &  geometry()
      //{

      //   return *m_pgeometry;

      //}
      inline  class imaging & imaging() { return *m_pimaging; }

      //virtual ::sockets::sockets & sockets() { return *m_psockets; }

      //math::math                                   &  math()
      //{

      //   return *m_pmath;

      //}


      inline class ::draw2d::draw2d                * draw2d() { return m_pdraw2d; }


      //inline ::url::department                     &  url()
      //{

      //   return *m_purldepartment;   // only usable from base.dll and dependants

      //}


      //inline class ::compress_department           &  compress()
      //{

      //   return *m_pcompress;   // only usable from base.dll and dependants

      //}




      //inline ::file::system_dir & dir() { return *m_spdir; }
      //inline ::file::system_file & file() { return *m_spfile; }


      //::net::email_department                & email();

      //__pointer(::account::user_set)                userset();

      //::datetime::department                 & datetime();


      //virtual string url_encode(const ::string & str);

      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes) override;

      //::mutex * get_openweather_city_mutex();


      //virtual os_local & oslocal() override;


      template < typename T >
      inline T * cast_clone(T * p)
      {

         return ::clone(p);

      }


      //virtual ::e_status browser(string strUrl, string strBrowser, string strProfile, string strTarget) override;
      //virtual ::e_status open_profile_link(string strUrl, string strProfile, string strTarget) override;
      //virtual ::e_status open_link(string strUrl, string strProfile, string strTarget) override;
      //virtual ::e_status open_url(string strUrl, string strProfile, string strTarget) override;


      //virtual void __set_thread_on() override;

      //virtual string get_local_mutex_name(const ::string & pszAppName) override;
      //virtual string get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId) override;
      //virtual string get_global_mutex_name(const ::string & pszAppName) override;
      //virtual string get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId) override;


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

      bool on_application_menu_action(const ::string & pszCommand);


      //virtual ::e_status initialize_sockets();

      ::image_pointer get_cache_image(::object * pobject, const ::payload & payloadFile);
      ::image_pointer matter_cache_image(::object * pobject, const ::string & strMatter);

      ::image_pointer get_image(::object * pobject, const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
      ::image_pointer matter_image(::object * pobject, const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());

      //virtual bool on_get_thread_name(string& strThreadName) override;

      //virtual ::acme::library * on_get_library(const ::string & pszLibrary) override;

      //virtual ::acme::library * get_library(const ::string & pszLibrary, bool bOpenCa2 = false) override;


      //virtual ::u32 os_post_to_all_threads(const ::id & id,wparam wparam = 0,lparam lparam = 0) override;


      //virtual void session_add(index iEdge, ::apex::session * psession) overr;
      //virtual void session_erase(index iEdge);



      //virtual ::e_status init_system();

      //virtual ::e_status process_init();

      virtual ::e_status initialize_draw2d();
      //virtual ::e_status initialize_write_text();
      virtual ::e_status draw2d_factory_exchange(::factory_map * pfactorymap);
      virtual string draw2d_get_default_library_name();

      virtual bool imaging_factory_exchange(::factory_map * pfactorymap);
      virtual string imaging_get_default_library_name();

      virtual ::e_status init_thread() override;
      virtual void term_thread() override;


      virtual ::e_status thread_loop() override;

      //virtual ::e_status init();

      //virtual ::e_status init1();

      //virtual ::e_status init2();

      //virtual ::e_status post_creation_requests() override;

      //virtual void term_system();

      virtual void term2() override;

      virtual void term1() override;

      //virtual void term();

      //virtual void TermSystem() override;


      virtual void process_term() override;


      //virtual bool is_system() const override;




  /*    static inline ::id id(const ::std::type_info & info);
      static inline ::id id(const ::string & psz);
      static inline ::id id(const ::string & str);
      static inline ::id id(i64 i);
      static inline ::id_space & id();
      inline ::id id(const ::payload & payload);
      inline ::id id(const property & prop);*/


      //virtual i32 _001OnDebugReport(i32 i1, const ::string & psz1,i32 i2, const ::string & psz2, const ::string & psz3,va_list args) override;
      //virtual i32 _debug_logging_report(i32 iReportType, const ::string & pszFilename, i32 iLinenumber, const ::string & iModuleName, const ::string & pszFormat, va_list list) override;
      //virtual bool assert_failed_line(const ::string & pszFileName,i32 iLine) override;

      //virtual bool on_assert_failed_line(const ::string & pszFileName,i32 iLine) override;






      //virtual ::e_status initialize_log(const ::string & pszId) override;


      //virtual void appa_load_string_table() override;
      //virtual void appa_set_locale(const ::string & pszLocale, const ::action_context & action_context) override;
      //virtual void appa_set_schema(const ::string & pszStyle, const ::action_context & action_context) override;

      //virtual bool assert_running_global(const ::string & pszAppName, const ::string & pszId = nullptr) override;
      //virtual bool assert_running_local(const ::string & pszAppName, const ::string & pszId = nullptr) override;

      //__pointer(application) assert_running(const ::string & pszAppId);

  /*    virtual ::count get_application_count() override;
*/

      //virtual string crypto_md5_text(const ::string & str);

      //inline class ::http::system                  & http()
      //{
      //   return *m_sphttpsystem;
      //}

      //class ::crypto::crypto                       & crypto();


      //virtual ::e_status start() override;

      //virtual ::file::path local_get_matter_cache_path() override;
      //virtual ::file::path local_get_matter_cache_path(string strMatter) override;
      //virtual ::file::path local_get_matter_path() override;
      //virtual ::file::path local_get_matter_path(string strMatter) override;

      //virtual bool find_applications_from_cache() override;
      //virtual bool find_applications_to_cache(bool bSave = true) override;
      //virtual bool map_application_library(const ::string & pszLibrary) override;


      //virtual void install_progress_add_up(int iAddUp = 1) override;

      //virtual ::e_status create_session(index iEdge = 0) override;

      /*virtual __transport(::apex::session) on_create_session(index iEdge) override;

      virtual ::apex::session * session(index iEdge = 0) override;*/

      //virtual void on_request(::create * pcreate) override;

      //__pointer(regex) create_regular_expression(const ::string & pszStyle, const string& str);
      //__pointer(regex_context) create_regular_expression_context(const ::string & pszStyle, int iCount);
      //virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);


      //virtual string get_system_platform() override;
      //virtual string get_system_configuration() override;
      //virtual string get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId);




      //#ifndef _UWP

      //virtual void get_time(timeval * point_i32) override;

      //#endif

      virtual ::e_status on_start_system() override;
      //virtual void on_start_find_applications_from_cache() override;
      //virtual void on_end_find_applications_from_cache(stream & is) override;

      //virtual void on_end_find_applications_to_cache(stream & os) override;

      //virtual void on_map_application_library(::acme::library & library) override;

      //virtual void defer_check_exit();



      //virtual ::e_status do_request(::create * pcreate) override;

      //virtual void defer_check_openweather_city_list();

      //virtual openweather_city * openweather_find_city(string strQuery);
      //virtual index openweather_find_city2(string strQuery, string & strCit, i64 & iId, double & dLat, double & dLon);
      //virtual index openweather_find_city2(string strQ1, string strQ2, string & strCit, i64 & iId, double & dLat, double & dLon, bool bPrefix);

//#ifdef ANDROID
////#pragma message("at macos??")
//      virtual bool android_set_user_wallpaper(string strUrl) override;
//      virtual bool android_get_user_wallpaper(string & strUrl) override;
//
//#endif
//
//      virtual bool defer_accumulate_on_open_file(string_array stra, string strExtra) override;
//
//      virtual bool merge_accumulated_on_open_file(::create * pcreate) override;
//
//      virtual bool on_open_file(::payload payloadFile, string strExtra) override;
//
      //virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);

      //virtual bool initialize_native_window1();

      //virtual void * initialize_native_window2(const ::rectangle_i32 & rectangle);


      //virtual void on_os_text(e_os_text etext, string strText) override;

      //virtual ::user::interaction_impl * impl_from_handle(void * posdata);
      //virtual ::user::interaction * ui_from_handle(void * posdata);




      //virtual void on_extra(string str) override;

      //virtual string standalone_setting(string str) override;
      //virtual bool set_standalone_setting(string str, string strSetting) override;


      //virtual void on_event(::u64 u, ::object * pobject) override;


      virtual void on_initial_frame_position(::user::frame * pframe);

      virtual void on_graphics_ready();

      //virtual void process_machine_event_data(machine_event_data * pdata) override;



      //virtual void __tracea(enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz) const override;


      //void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);

      //void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      //::e_status     firefox(string strUrl, string strBrowser, string strProfile, string strParam);
      //::e_status     get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory);



      //virtual ::e_status  initialize_system(::object* pobject, app_core* pappcore) override;

 /*     virtual void discard_to_factory(__pointer(object) pca) override;*/

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

      //__pointer_array(::aura::session) &    planesessionptra();


      //virtual bool base_support() override;


      //DECLARE_MESSAGE_HANDLER(on_application_signal);


      //::e_status set_history(::apex::history* phistory);


      //__pointer(::acme::library) on_get_library(const ::string & pszLibrary) override;


      //virtual ::aura::session *  get_platform(index iEdge,application_bias * pbiasCreation = nullptr);


      //virtual void on_request(::create* pcreate) override;

      //      virtual __pointer(::handler) handler();





      //virtual i32 main();

      //virtual void on_allocation_error(const ::string& str, ::object* pobjectSometimes) override;

      //virtual __pointer(::aura::session) on_create_session() override;


//      ::aura::stra                           & stra();
      //    ::aura::service                        & service();
      //::aura::history& hist();

      //class ::aura::patch& patch();

      //::http::system                         & http();

      //::filehandler::handler& filehandler();


//#ifdef LINUX
//
//      virtual ::e_status defer_initialize_x11() ;
//      virtual bool sn_start_context();
//
//#endif

      ////bool sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser = nullptr, ::http::cookies* pcookies = nullptr);
      //bool sync_load_url(string& str, const ::string & pszUrl,  ::http::cookies* pcookies = nullptr);



      //      u32 guess_code_page(const ::string & str);

//#ifdef _UWP
//
//      virtual bool get_window_rect(RECTANGLE_I32* prectangle);
//
//
//#endif

      //virtual void post_fork_uri(const ::string & pszUri,application_bias * papplicationbias);



//      virtual bool wait_twf(::duration tickTimeout = U32_INFINITE_TIMEOUT);








      virtual string get_host_location_url() override;

      virtual ::e_status add_view_library(::acme::library* plibrary);

      //virtual void get_cursor_position(POINT_I32 * ppoint);



      //virtual ::e_status do_request(::create* pcommand) override;


//#ifdef _DEBUG
//
//      virtual void set_context(::context* pcontext) override;
//      virtual void set_context_thread(::thread* pthread) override;
//      virtual void set_context_app(::aura::application* pappContext) override;
//      virtual void set_context_session(::aura::session* psessionContext) override;
//      virtual void set_context_system(::aura::system* psystemContext) override;
//
//#endif


      void assert_valid() const override;
      void dump(dump_context& action_context) const override;


      virtual ::e_status     main() override;
      //virtual void hist_hist(const ::string & psz) override;


      virtual ::type get_pane_tab_view_type_info();
      virtual ::type get_simple_frame_window_type_info();
      //virtual ::type get_simple_child_frame_type_info();

      //virtual void on_start_find_applications_from_cache() override;
      //virtual void on_end_find_applications_from_cache(stream& is) override;

      //virtual void on_end_find_applications_to_cache(stream& os) override;

      //virtual void on_map_application_library(::acme::library& library) override;

      //virtual void on_graphics_ready() override;


      //::e_status _on_initialize_window_object() override;


      //system();
      //virtual ~system();


      ///virtual ::e_status initialize_system(::object* pobject, app_core* pappcore) override;


      //virtual ::e_status process_init() override;
      //virtual void term_system() override;

      //virtual __pointer(::aura::session) on_create_session() override;




      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      //virtual int install_canvas_increment_mode() override;



      //virtual ::u32 get_monitor_color_temperature(index iMonitor);
      //virtual bool adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dwGamma);
      //virtual bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle) override;

      //virtual ::count get_monitor_count() override;

      //bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle) override;


      //virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
      //virtual ::user::interaction * ui_from_handle(void * pdata) override;

      //void signal(::signal * psignal) override;

      void handle(::subject * psubject, ::context * pcontext) override;

      virtual ::e_status initialize_estamira();

      virtual void _001AddPacks(string_to_string& base64map, string& str);

      //__pointer(::extended::sequence < ::conversation >) message_box(::user::interaction * puserinteraction, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;




   };


   CLASS_DECL_AURA ::mutex * get_image_mutex();


} // namespace aura



