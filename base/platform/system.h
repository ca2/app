#pragma once


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system
   {
   public:





//      __pointer(::aura::application)                     m_papplicationStartup;
//
//      __composite(::aura::system)                        m_psystemParent;
//
//      __composite(::aura::audio)                         m_paudio;
//
//      __composite(::aura::multimedia)                    m_pmultimedia;
//
//      // __composite(::aura::estamira)                      m_pestamira;
//
//      ::type                                             m_typePaneTabImpact;
//#ifdef APPLE_IOS
//
//      plane_system *                                     m_pplanesystem;
//
//#endif
//
//#ifdef __DEBUG
//
//      __composite(::dump_context)                        m_pdumpcontext;
//
//#endif // __DEBUG
//
//      __composite(::sockets::sockets)                    m_psockets;
//
//      ::object *                                         m_pDraw2dFactoryExchange;
//      __pointer(::draw2d::draw2d)                        m_pdraw2d;
//
//      ::file::path                                       m_pathConfig;
//      ::file::path                                       m_pathCa2Roaming;
//
//      ::mutex                                            m_mutexThread;
//      thread_map                                         m_threadmap;
//      thread_id_map                                      m_threadidmap;
//      ::mutex                                            m_mutexThreadOn;
//      map < itask_t, itask_t >                        m_mapThreadOn;
//
//      ::mutex                                            m_mutexUserChildren;
//      __composite(class imaging)                         m_pimaging;
//
//      __composite(class ::datetime::department)          m_pdatetime;
//      __composite(::crypto::crypto)                      m_pcrypto;
//      __composite(class ::account::user_set)             m_puserset;
//
//      __pointer_array(service_base)                      m_serviceptra;
//      __composite(class ::xml::department)               m_pxml;
//      __composite(class ::aura::log)                     m_ptrace;
//      __composite(math::math)                            m_pmath;
//      __composite(geometry::geometry)                    m_pgeometry;
//
//      __composite(::aura::str)                           m_puserstr;
//
//      ::aura::session::map                               m_sessionmap;
//
//      __composite(::gpu::approach)                       m_pgpu;
//
//      ::mutex                                            m_mutexLibrary;
//      string_map < __pointer(::acme::library) >          m_mapLibrary;
//      string_map < PFN_NEW_BASE_LIBRARY >                m_mapNewAuraLibrary;
//      string_map < __pointer(::acme::library) >          m_mapLibCall;
//
//
//
//      // for lesser cooperative GUI applications
//      bool                                               m_bProdevianMouse;
//      static ::atom                                        idEmpty;
//      __composite(class ::str::base64)                   m_pbase64;
//
//      ::string_to_string                                 m_mapAppLibrary;
//      __composite(class machine_event_central)           m_pmachineeventcentral;
//
//      static system *                                    g_p;
//
//      float                                              m_dpi;
//
//      void *                                             m_ftlibrary;
//
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
//
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
//      ::mutex                                 m_spmutexOpenweatherCity;
//
//      string_array                                       m_straCityLo;
//      string_array                                       m_straCity;
//      i64_array                                          m_iaIds;
//      double_array                                       m_daLon;
//      double_array                                       m_daLat;
//
//      string_map < __pointer(openweather_city) >         m_mapCity;
//
//      string                                             m_strIosHome;
//      string                                             m_strIosTemp;
//
//      __composite(::net::email_department)               m_pemaildepartment;
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
//      // 2020-01-25: removing from here (::aura::system), placing at ::context
//      //__pointer(::user::language_map)                    m_puserlanguagemap;
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
//      //factory                                      m_factorymap;
//
//      keymap < ::file::path, ::image_pointer >           m_mapImage;
//
//      __composite(::user::window_map)                    m_pwindowmap;
//
//
//      critical_section                                   m_csEnumText;
//      string_map < i64_map < string > >                  m_mapEnumToText;
//      string_map < string_map < i64 > >                  m_mapTextToEnum;
//      task_group_map                                   m_taskgroupmap;
//      task_tool_map                                    m_tasktoolmap;
//
//
//      //stridsp(type)                                      m_typemap;
//      //::string_to_string                               m_mapAppLibrary;
//      //string_to_int_to_string                            m_mapEnumToName;
//      //string_to_string_to_int                            m_mapNameToEnum;
//      //string_array                                       m_straCityLo;
//      //string_array                                       m_straCity;
//      //i64_array                                          m_iaIds;
//      //double_array                                       m_daLon;
//      //double_array                                       m_daLat;
//
//      //string_map < __pointer(::acme::library) >          m_mapLibrary;
//
//      //string_map < __pointer(openweather_city) >                   m_mapCity;
//
//
//      //system_heap(::object* pobject)
//      //{
//
//      //}
//
//
//      //index                                        m_iNewEdge;
//
//#ifdef WINDOWS_DESKTOP
//
//      ::u32                                         m_emessageWindowsTaskbarCreatedMessage;
//
//#endif
//
//      ::mutex                                        m_mutex;
//      //__composite(::filehandler::handler)            m_pfilehandler;
//
//
//      ::mutex                                        m_mutexDelete;
//
//
//      //    class ::aura::stra                           m_stra;
//      //    class ::aura::service                        m_service;
//
//
//      class ::aura::patch *                           m_ppatch;
//
//      //      __pointer(::aura::run_start_installer)              m_prunstartinstaller;
//
//            //__pointer(::aura::session::map)                     m_pbergedgemap;
//            //__pointer_array(::aura::session)                         m_planesessionptra;
//
//      __composite(class ::aura::history)                m_phistory;
//
//      //      ::sockets::net                               m_net;
//      //      __pointer(::aura::filehandler::handler)  m_spfilehandler;
//
//
//      // certain instantiators like npca2plugin and iexca2plugin rely
//      // on the functionality of these variables cached information,
//      // to avoid multiple initialization.
//      //bool                                         m_bInitApplication;
//      //bool                                         m_bInitApplicationResult;
//      //bool                                         m_bProcessInitialize;
//      //bool                                         m_bProcessInitializeResult;
//
//      strid_map < ::acme::library* >              m_idmapCreateImpactLibrary;
//
//      __pointer_array(::acme::library)                         m_libraryspa;
//
//#ifdef _UWP
//
//      Agile < ::winrt::Windows::UI::Core::CoreWindow >      m_window;
//
//#endif
//
//
//
      system();
      virtual ~system();
//
//
      void common_construct();
//
      virtual void initialize(::object * pobject) override;

      virtual void on_add_session(::apex::session * papexsession) override;
//
//      virtual void init();
//      //virtual void init_instance() override;
//      //virtual void term_instance() override;
//      virtual void inline_init() override;
//      virtual void inline_term() override;
//
//      virtual void init_system();
//      virtual void term_system();
//
//      virtual void term();
//
//      //::url::department                           & url()     { return m_urldepartment; }
//
//      ::thread * get_task(itask_t itask);
//      itask_t get_thread_id(::thread * pthread);
//      void set_thread(itask_t itask, ::thread * pthread);
//      void unset_thread(itask_t itask, ::thread * pthread);
//
//      inline ::gpu::approach* get_gpu() { if (!m_pgpu) create_gpu(); return m_pgpu.get(); };
//      inline ::gpu::approach* gpu() { return m_pgpu.get(); };
//      virtual void create_gpu();
//
//      ::task_group * task_group(::enum_priority epriority = ::e_priority_none);
//
//      ::task_tool * task_tool(::enum_task_tool etool);
//
//
//      //virtual string install_get_platform() override;
//      //virtual void install_set_platform(const ::string & pszPlatform) override;
//      //virtual string install_get_version() override;
//      //virtual void install_set_version(const ::string & pszVersion) override;
//      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
//      //virtual i32 install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
//      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;
//
//      //virtual ::install::canvas * install_create_canvas();
//      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
//      //virtual int install_canvas_increment_mode();
//
//      //virtual string install_get_platform() override;
//      //virtual void install_set_platform(const ::string & pszPlatform) override;
//      //virtual string install_get_version() override;
//      //virtual void install_set_version(const ::string & pszVersion) override;
//      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
//      //virtual i32 install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
//      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;
//
//      virtual void process_init();
//
//      virtual void init1();
//
//      virtual void init2();
//
//      virtual void defer_xml();
//
//
//      virtual void verb() override; // ambigous inheritance from ::aura::system/::axis::application
//
//
//      virtual bool is_system() const override;
//
//
//      virtual string crypto_md5_text(const ::string & str);
//
//
//      //virtual void create_html();
//
//      //virtual __pointer(::aura::session) on_create_session() override;
//
//      virtual void on_request(::create * pcreate) override;
//
//      //virtual void construct(const ::string & pszAppId);
//
//      //virtual bool initialize_application() override;
//
//      //virtual i32 exit_instance();
//      //virtual bool destroy();
//
//
//
//
//
//
//      //virtual bool verb();
//
//
//
//
//
//      //virtual bool process_initialize();
//
//      //virtual bool process_init();
//
//      //virtual bool init1();
//
//      //virtual bool init2();
//
//      //virtual bool is_system();
//
//
//
//
//
//
//      //virtual ::aura::session * query_session(index iEdge) override;
//
//
//
//
//      //virtual string dir_appmatter_locator(::object * pobject);
//
//
//      virtual void hist_hist(const ::string & psz);
//
//
//      //virtual void on_request(::create * pcreate);
//
//
//      //virtual u32 crc32(u32 dwPrevious, const ::string & psz);
//
//
//      virtual string url_encode(const ::string & str);
//
//
//      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
//      virtual string get_locale_schema_dir() override;
//
//
//      //virtual void     initialize_system(::object * pobject, app_core * pappcore);
//
//
//      //__pointer(::thread_tools) create_thread_tools(::enum_task_tool etool);
//      //thread_tools * tools(::enum_priority epriority);
//      //thread_toolset * toolset(e_tool etool);
//
//      class ::user::window_map                     &  window_map();
//
//
//      virtual void defer_audio();
//
//      virtual ::aura::audio * defer_get_audio();
//
//      virtual void defer_multimedia();
//
//      virtual ::aura::multimedia * defer_get_multimedia();
//
//      //class ::aura::os                             &  os();
//      //class base_factory                           &  factory_item();
//
//
//      ::aura::str                                  &  str();
//      ::operating_system::department                        &  process();
//
//
//      ::xml::department                            &  xml();
//      class ::str::base64                          &  base64();
//      class ::aura::log                            &  log();
//      class ::machine_event_central                &  machine_event_central();
//      inline ::parallelization::threading           *  threading() { return m_pthreading; }
//
//      geometry::geometry                           &  geometry()
//      {
//
//         return *m_pgeometry;
//
//      }
//      inline  class imaging & imaging() { return *m_pimaging; }
//
//      virtual ::sockets::sockets & sockets() { return *m_psockets; }
//
//      math::math                                   &  math()
//      {
//
//         return *m_pmath;
//
//      }
//
//
//      inline class ::draw2d::draw2d                & draw2d() { return *m_pdraw2d; }
//
//
//      inline ::url::department                     &  url()
//      {
//
//         return *m_purldepartment;   // only usable from base.dll and dependants
//
//      }
//
//
//      //inline class ::compress_department           &  compress()
//      //{
//
//      //   return *m_pcompress;   // only usable from base.dll and dependants
//
//      //}
//
//
//
//
//      //inline ::file::system_dir & dir() { return *m_spdir; }
//      //inline ::file::system_file & file() { return *m_spfile; }
//
//
//      ::net::email_department                & email();
//
//      __pointer(::account::user_set)                userset();
//
//      ::datetime::department                 & datetime();
//
//
//      //virtual string url_encode(const ::string & str);
//
//      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes);
//
//      ::mutex * get_openweather_city_mutex();
//
//
//      virtual os_local & oslocal();
//
//
//      template < typename T >
//      inline T * cast_clone(T * point_i32)
//      {
//
//         return ::clone(point);
//
//      }
//
//
//      virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget);
//      virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
//
//
//      virtual void __set_thread_on() override;
//
//      virtual string get_local_mutex_name(const ::string & pszAppName);
//      virtual string get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId);
//      virtual string get_global_mutex_name(const ::string & pszAppName);
//      virtual string get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId);
//
//
//      //template < class T >
//      //::type * type_info()
//      //{
//
//      //   return get_type_info(typeid(T));
//
//      //}
//
//
//      //virtual ::type * get_type_info(const ::std::type_info & info);
//
//      //::type * get_type_info(const ::atom & idType)
//      //{
//
//      //   if(idType.is_empty())
//      //      return nullptr;
//
//      //   synchronous_lock synchronouslock(&m_mutexFactory);
//
//      //   return m_typemap[idType].m_p;
//
//      //}
//
//
//      //virtual void discard_to_factory(::object * pca);
//
//      bool on_application_menu_action(const ::string & pszCommand);
//
//
//      virtual void initialize_sockets();
//
//      ::image_pointer get_cache_image(::object * pobject, const ::payload & payloadFile);
//      ::image_pointer matter_cache_image(::object * pobject, const ::string & strMatter);
//
//      ::image_pointer get_image(::object * pobject, const ::payload & payloadFile, bool bCache = true, bool bSync = false);
//      ::image_pointer matter_image(::object * pobject, const ::string & strMatter, bool bCache = true, bool bSync = false);
//
//      virtual bool on_get_thread_name(string& strThreadName) override;
//
//      virtual ::acme::library * on_get_library(const ::string & pszLibrary);
//
//      virtual ::acme::library * get_library(const ::string & pszLibrary, bool bOpenCa2 = false);
//
//
//      virtual ::u32 os_post_to_all_threads(const ::atom & atom,wparam wparam = 0,lparam lparam = 0);
//
//
//      virtual void session_add(index iEdge, ::aura::session * psession);
//      virtual void session_erase(index iEdge);
//
//
//
//
//      //virtual void init_system();
//
//      //virtual void process_init();
//
//      virtual void init_draw2d();
//      virtual bool ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//      virtual string draw2d_get_default_library_name();
//
//      virtual bool ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//      virtual string imaging_get_default_library_name();
//
//      virtual void init_thread() override;
//      virtual void term_thread() override;
//
//
//      virtual void thread_loop() override;
//
//      //virtual void init();
//
//      //virtual void init1();
//
//      //virtual void init2();
//
//      virtual void initial_check_directrix();
//
//      //virtual void term_system();
//
//      virtual void term2();
//
//      virtual void term1();
//
//      //virtual void term();
//
//      virtual void TermSystem();
//
//
//      virtual void process_term();
//
//
//      //virtual bool is_system() const override;
//
//
//
//
//      static inline ::atom atom(const ::std::type_info & info);
//      static inline ::atom atom(const ::string & psz);
//      static inline ::atom atom(const ::string & str);
//      static inline ::atom atom(i64 i);
//      static inline ::atom_space & atom();
//      inline ::atom atom(const ::payload & payload);
//      inline ::atom atom(const property & prop);
//
//
//      virtual i32 _001OnDebugReport(i32 i1, const ::string & psz1,i32 i2, const ::string & psz2, const ::string & psz3,va_list args);
//      virtual i32 _debug_logging_report(i32 iReportType, const ::string & pszFilename, i32 iLinenumber, const ::string & iModuleName, const ::string & pszFormat, va_list list);
//      virtual bool assert_failed_line(const ::string & pszFileName,i32 iLine);
//
//      virtual bool on_assert_failed_line(const ::string & pszFileName,i32 iLine);
//
//
//
//
//
//
//      virtual void initialize_log(const ::string & pszId);
//
//
//      virtual void appa_load_string_table();
//      virtual void appa_set_locale(const ::string & pszLocale, const ::action_context & action_context);
//      virtual void appa_set_schema(const ::string & pszStyle, const ::action_context & action_context);
//
//      virtual bool assert_running_global(const ::string & pszAppName, const ::string & pszId = nullptr);
//      virtual bool assert_running_local(const ::string & pszAppName, const ::string & pszId = nullptr);
//
//      //__pointer(application) assert_running(const ::string & pszAppId);
//
//      virtual ::count get_application_count();
//
//
//      //virtual string crypto_md5_text(const ::string & str);
//
//      //inline class ::http::system                  & http()
//      //{
//      //   return *m_sphttpsystem;
//      //}
//
//      class ::crypto::crypto                       & crypto();
//
//      virtual void * & ftlibrary();
//
//      virtual ::file::path local_get_matter_cache_path();
//      virtual ::file::path local_get_matter_cache_path(string strMatter);
//      virtual ::file::path local_get_matter_path();
//      virtual ::file::path local_get_matter_path(string strMatter);
//
//      virtual bool find_applications_from_cache();
//      virtual bool find_applications_to_cache(bool bSave = true);
//      virtual bool map_application_library(const ::string & pszLibrary);
//
//
//      virtual void install_progress_add_up(int iAddUp = 1);
//
//      virtual void create_session(index iEdge = 0);
//
//      virtual __pointer(::aura::session) on_create_session(index iEdge);
//
//      virtual ::aura::session * session(index iEdge = 0);
//
//      //virtual void on_request(::create * pcreate) override;
//
//      __pointer(regex) compile_pcre(const string& str);
//      __pointer(regex_context) create_pcre_context(int iCount);
//      virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);
//
//
//      virtual string get_system_platform();
//      virtual string get_system_configuration();
//      //virtual string get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId);
//
//
//
//
//      //#ifndef _UWP
//
//      virtual void get_time(timeval * point_i32);
//
//      //#endif
//
//
//      virtual void on_start_find_applications_from_cache();
//      virtual void on_end_find_applications_from_cache(stream & is);
//
//      virtual void on_end_find_applications_to_cache(stream & os);
//
//      virtual void on_map_application_library(::acme::library & library);
//
//      //virtual void defer_check_exit();
//
//
//
//      virtual void do_request(::create * pcreate) override;
//
//      virtual void defer_check_openweather_city_list();
//
//      virtual openweather_city * openweather_find_city(string strQuery);
//      virtual index openweather_find_city2(string strQuery, string & strCit, i64 & iId, double & dLat, double & dLon);
//      virtual index openweather_find_city2(string strQ1, string strQ2, string & strCit, i64 & iId, double & dLat, double & dLon, bool bPrefix);
//
//#ifdef ANDROID
////#pragma message("at macos??")
//      virtual bool android_set_user_wallpaper(string strUrl);
//      virtual bool android_get_user_wallpaper(string & strUrl);
//
//#endif
//
//      virtual bool defer_accumulate_on_open_file(string_array stra, string strExtra);
//
//      virtual bool merge_accumulated_on_open_file(::create * pcreate);
//
//      virtual bool on_open_file(::payload payloadFile, string strExtra);
//
//      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);
//
//      //virtual bool initialize_native_window1();
//
//      //virtual void * initialize_native_window2(const ::rectangle_i32 & rectangle);
//
//
//      virtual void on_os_text(e_os_text etext, string strText);
//
//      virtual ::user::interaction_impl * impl_from_handle(void * posdata);
//      virtual ::user::interaction * ui_from_handle(void * posdata);
//
//      void enum_display_monitors();
//
//#if defined(WINDOWS)
//      //#pragma message("at macos??")
//      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, RECTANGLE_I32 * prcMonitor, LPARAM dwData);
//
//      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, RECTANGLE_I32 * prcMonitor);
//
//#endif
//
//      virtual index get_main_monitor(RECTANGLE_I32 * prectangle = nullptr);
//
//      virtual ::count get_monitor_count();
//      virtual bool  get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle);
//
//      virtual ::count get_desk_monitor_count();
//      virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle);
//
//
//      virtual index get_main_workspace(RECTANGLE_I32 * prectangle = nullptr);
//
//      virtual ::count get_workspace_count();
//      virtual bool  get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle);
//
//      virtual ::count get_desk_workspace_count();
//      virtual bool  get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32 * prectangle);
//
//      virtual index get_ui_workspace(::user::interaction * pinteraction);
//
//      virtual void on_extra(string str);
//
//      virtual string standalone_setting(string str);
//      virtual bool set_standalone_setting(string str, string strSetting);
//
//
//      //virtual void on_event(::u64 u, ::object * pobject) override;
//
//
//      virtual void on_initial_frame_position(::user::frame * pframe);
//
//      virtual void on_graphics_ready();
//
//      virtual void process_machine_event_data(machine_event_data * pdata);
//
//
//
//      virtual void __tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz) override;
//
//
//      virtual string get_user_language();
//      virtual bool set_user_language(::aura::application * papp, index iSel);
//      virtual bool set_user_language(::aura::application * papp, string strLang);
//
//      void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);
//
//      //      void commander(string strUrl, string strWeather, string strUser, ::file::path path, string strParam);
//
//      void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);
//
//      void     firefox(string strUrl, string strBrowser, string strProfile, string strParam);
//      void     get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory);
//
//
//
//      //virtual void  initialize_system(::object* pobject, app_core* pappcore) override;
//
//      virtual void discard_to_factory(__pointer(object) pca);
//
//      //virtual bool is_system() const override;
//
//      //virtual void process_init() override;
//
//      //virtual void init2() override;
//
//      //virtual void init_system() override;
//
//      //virtual void term() override;
//
//      //virtual void term_system() override;
//
//
//      //virtual i32 main();
//      ///virtual void InitApplication() override;
//
//      //virtual void init() override;
//      //virtual void init1() override;
//      //virtual void init3() override;
//
//      //virtual void bergedge_start() override;
//
//
//      //virtual void initialize_rich_text();
//
//
//      //virtual index get_new_bergedge(application_bias * pbiasCreation = nullptr);
//
//      //__pointer_array(::aura::session) &    planesessionptra();
//
//
//      //virtual bool base_support() override;
//
//
//      DECLARE_MESSAGE_HANDLER(on_application_signal);
//
//
//      void set_history(::aura::history* phistory);
//
//
//      //__pointer(::acme::library) on_get_library(const ::string & pszLibrary) override;
//
//
//      //virtual ::aura::session *  get_platform(index iEdge,application_bias * pbiasCreation = nullptr);
//
//
//      //virtual void on_request(::create* pcreate) override;
//
//      //      virtual __pointer(::handler) handler();
//
//
//
//
//
//      //virtual i32 main();
//
//      //virtual void on_allocation_error(const ::string& str, ::object* pobjectSometimes) override;
//
//      //virtual __pointer(::aura::session) on_create_session() override;
//
//
////      ::aura::stra                           & stra();
//      //    ::aura::service                        & service();
//      ::aura::history& hist();
//
//      class ::aura::patch& patch();
//
//      //::http::system                         & http();
//
//      //::filehandler::handler& filehandler();
//
//
//
//
//
//
//
//
//      bool sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser = nullptr, ::http::cookies* pcookies = nullptr);
//
//
//
//
//
//      //      u32 guess_code_page(const ::string & str);
//
//#ifdef _UWP
//
//      virtual bool get_window_rect(RECTANGLE_I32* prectangle);
//
//
//#endif
//
//      //virtual void post_fork_uri(const ::string & pszUri,application_bias * papplicationbias);
//
//
//
////      virtual bool wait_twf(::duration tickTimeout = U32_INFINITE_TIMEOUT);
//
//
//
//
//
//
//
//
//      virtual string get_host_location_url();
//
//      virtual void add_view_library(::acme::library* plibrary);
//
//      //virtual void get_cursor_position(POINT_I32 * ppoint);
//
//
//
//      //virtual void do_request(::create* pcommand) override;
//
//
//#ifdef _DEBUG
//
//      virtual void set_context(::context* pcontext) override;
//      virtual void set_context_thread(::thread* pthread) override;
//      virtual void set_context_app(::aura::application* pappContext) override;
//      virtual void set_context_session(::aura::session* psessionContext) override;
//      virtual void set_context_system(::aura::system* psystemContext) override;
//
//#endif
//
//
//      void assert_ok() const override;
//      void dump(dump_context& action_context) const override;
//
//
//      virtual void     main() override;
//      //virtual void hist_hist(const ::string & psz) override;
//
//
//      virtual ::type get_pane_tab_view_type_info();
//      virtual ::type get_simple_frame_window_type_info();
//      //virtual ::type get_simple_child_frame_type_info();
//
//      //virtual void on_start_find_applications_from_cache() override;
//      //virtual void on_end_find_applications_from_cache(stream& is) override;
//
//      //virtual void on_end_find_applications_to_cache(stream& os) override;
//
//      //virtual void on_map_application_library(::acme::library& library) override;
//
//      //virtual void on_graphics_ready() override;
//
//
//
//      //system();
//      //virtual ~system();
//
//
//      ///virtual void initialize_system(::object* pobject, app_core* pappcore) override;
//
//
//      //virtual void process_init() override;
//      //virtual void term_system() override;
//
//      //virtual __pointer(::aura::session) on_create_session() override;
//
//      virtual void set_active_guie(::user::interaction* pinteraction);
//      virtual void set_focus_guie(::user::interaction* pinteraction);
//
//
//
//      //virtual ::install::canvas * install_create_canvas() override;
//      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
//      //virtual int install_canvas_increment_mode() override;
//
//
//
//      virtual ::u32 get_monitor_color_temperature(index iMonitor);
//      virtual bool adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dwGamma);
//      //virtual bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle) override;
//
//      //virtual ::count get_monitor_count() override;
//
//      //bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle) override;
//
//
//      //virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
//      //virtual ::user::interaction * ui_from_handle(void * pdata) override;
//
//      virtual void handle(::topic * ptopic, ::context * pcontext) override;
//
//      // virtual void on_command_create(::create* pcreate);
//
//      //virtual bool initialize_native_window1() override;
//
//      //virtual ::acme::library* load_library(const ::string & pszLibrary);

   };

   //CLASS_DECL_BASE ::mutex * get_image_mutex();



} // namespace base







//
////CLASS_DECL_BASE ::aura::system * create_aura_system(app_core * pappcore);
//CLASS_DECL_BASE ::aura::system * create_aura_system();
//
//
//template < typename ENUM >
//inline void set_enum_text(ENUM e, const ::string & psz)
//{
//
//   auto psystem = ::get_context_system();
//
//   critical_section_lock synchronouslock(&psystem->m_csEnumText);
//
//   psystem->m_mapEnumToText[typeid(e).name()][(i64)e] = psz;
//
//   psystem->m_mapTextToEnum[typeid(e).name()][psz] = (i64)e;
//
//}
//
//
//template < typename ENUM >
//inline string enum_text(ENUM e)
//{
//
//   auto psystem = ::get_context_system();
//
//   critical_section_lock synchronouslock(&psystem->m_csEnumText);
//
//   return psystem->m_mapEnumToText[typeid(e).name()][(i64)e];
//
//}
//
//
//template < class ENUM >
//inline ENUM text_enum(ENUM & e, const ::string & psz, ENUM eDefault = (ENUM)0)
//{
//
//   auto psystem = ::get_context_system();
//
//   critical_section_lock synchronouslock(&psystem->m_csEnumText);
//
//   i64 iValue;
//
//   if (psystem->m_mapTextToEnum[typeid(e).name()].lookup(psz, iValue))
//   {
//
//      e = (ENUM)iValue;
//
//   }
//   else
//   {
//
//      e = eDefault;
//
//   }
//
//   return e;
//
//}
//
//
//template < class ENUM, ENUM edefault = 0>
//inline base_enum < ENUM, edefault > & text_enum(base_enum < ENUM, edefault > & b, const ::string & psz, ENUM eDefault = edefault)
//{
//
//   return b = text_enum(b.m_evalue, psz, eDefault);
//
//}
//
//
//template < class ENUM, ENUM edefault = 0>
//inline string enum_text(const base_enum < ENUM, edefault > & b)
//{
//
//   return enum_text(b.m_evalue, (i64)(ENUM)b);
//
//}
//
//
//#define STRINGIFY(x) #x
//#define TOSTRING(x) STRINGIFY(x)
//#define SET_ENUM_TEXT(enum_value) set_enum_text(enum_value, TOSTRING(enum_value))
//
//
////
////
////inline ::traits & traits(::object * p)
////{
////
////   auto traits = psystem->m_traits[p];
////
////   if (traits.m_pobjectTrait != p)
////   {
////
////      traits.m_pobjectTrait = p;
////
////   }
////
////   return traits;
////
////}
//
//
//
//
//
//
//// void CLASS_DECL_BASE __start_core_system_main(::base::system * psystem);
//
//#ifdef _UWP
//
//CLASS_DECL_BASE int app_core_main(const ::string & psz);
//
//#endif
//
