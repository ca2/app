#pragma once


namespace apex
{


   class CLASS_DECL_APEX system:
      virtual public ::app_core,
      virtual public ::system,
      virtual public ::apex::context
#ifndef WINDOWS
      ,virtual public ::exception_translator
#endif
   {
   public:


      __composite(::dump_context)                        m_pdumpcontext;

      __composite(::sockets::sockets)                    m_psockets;

      __composite(::crypto::crypto)                      m_pcrypto;

      ::apex::session::map                               m_sessionmap;

      __composite(class machine_event_central)           m_pmachineeventcentral;

      __pointer(::mutex)                                 m_pmutexUserAppData;
      __pointer(::mutex)                                 m_pmutexSystemAppData;

      __pointer(::mutex)                                 m_pmutexMatter;

      __composite(::operating_system::department)        m_pprocess;

      __composite(::parallelization::threading)          m_pthreading;
      size_t                                             m_nSafetyPoolSize; // ideal size_i32

      bool                                               m_bFinalizeIfNoSessionSetting;
      bool                                               m_bFinalizeIfNoSession;

      __composite(::dir_system)                          m_pdirsystem;
      __composite(::file_system)                         m_pfilesystem;

      ::duration                                         m_durationMainStart;
      ::duration                                         m_durationAfterApplicationFirstRequest;

      string_array                                       m_straCommandLineAccumul;
      string_array                                       m_straCommandLineExtra;
      ::duration                                         m_durationCommandLineLast;
      int                                                m_iCommandLineDelay;
      
      bool                                               m_bSystemSynchronizedCursor;
      bool                                               m_bSystemSynchronizedScreen;

      
      //task_group_map                                   m_taskgroupmap;
      //task_tool_map                                    m_tasktoolmap;


      __composite(class ::apex::history)                m_phistory;


      system();
      ~system() override;


      void common_construct();


#ifdef _DEBUG


      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      void initialize(::object * pobject) override;

      void install_message_routing(::channel * pchannel) override;

      void system_construct(const class ::main & main) override;


#ifdef WINDOWS_DESKTOP

#elif defined(_UWP)

      void system_construct(const ::string_array & stra);

#else

      void system_construct(const ::string & pszCommandLine, const ::e_display& edisplay = ::e_display_none);
      void system_construct(os_local* poslocal, const ::e_display& edisplay = ::e_display_none);

#endif

      virtual void __thread_init() override;


      virtual ::application* get_main_application() override;


      virtual void init();
      //virtual void init_instance() override;
      //virtual void term_instance() override;
      virtual void inline_init() override;
      virtual void inline_term() override;

      //void on_pre_run_task() override;

      virtual void init_system() override;
      virtual void term_system();

      virtual void on_system_construct() override;

      virtual void on_start_system() override;

      virtual void system_main() override;

      virtual void term();


      DECLARE_MESSAGE_HANDLER(on_message_erase_session);


      virtual string get_application_server_name();

      //virtual ::acme::library* lib(const ::string & psz);
      //CLASS_DECL_APEX::acme::library* lib(const ::string & psz);
      //
      //template < typename FUNCTION >
      //FUNCTION library_function(const ::string & pszLibrary)
      //{

      //   return lib(pszLibrary)->get<decltype(&entry)>(#entry))

      //}

      //inline ::apex::session* get_session() const
      //{

      //   return m_psessionMain;

      //}


      virtual bool task_get_run() const override;


      virtual void create_os_node() override;


      //::thread * get_task(itask_t itask);
      //itask_t get_thread_id(::thread * pthread);
      //void set_thread(itask_t itask, ::thread * pthread);
      //void unset_thread(itask_t itask, ::thread * pthread);
      //::url::department & url() { return m_urldepartment; }


      //inline ::gpu::approach* get_gpu() { if (!m_pgpu) create_gpu(); return m_pgpu.get(); };
      //inline ::gpu::approach* gpu() { return m_pgpu.get(); };
      //virtual void create_gpu();


      //::task_group * task_group(::enum_priority epriority = ::e_priority_none);

      //::task_tool * task_tool(::enum_task_tool etool);


      //virtual __pointer(::topic) new_subject(const MESSAGE& message);

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
      //virtual i32 install_start(const ::string & pszCommandLine,const ::string & pszBuild) override;
      //virtual i32 install_progress_app_add_up(int iAddUp = 1) override;

      inline ::apex::node * node() { return m_pnode ? m_pnode->m_papexnode : nullptr; }

      //virtual ::layered * get_layered_window(oswindow oswindow);

      virtual __pointer(::factory::factory) & node_factory() override;

      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2();

      virtual void post_initial_request() override;

      virtual void initialize_context() override;

      //virtual void defer_xml();

      virtual __pointer(::data::node) load_xml(const ::string & pszXml);

      virtual void verb() override; // ambigous inheritance from ::apex::system/::axis::application


      virtual bool is_system() const override;


      virtual string crypto_md5_text(const ::string & str);


      //virtual void start() override;

      //virtual void create_html();

      //virtual __pointer(::apex::session) on_create_session() override;

      virtual void on_request(::create * pcreate) override;

      //virtual void construct(const ::string & pszAppId);

      //virtual bool initialize_application() override;

      //virtual i32 exit_instance();
      //virtual bool destroy();

      virtual void destroy() override;


      virtual void process_exit_status(::object* pobject, const ::e_status & estatus);


      //virtual bool verb();





      //virtual bool process_initialize();

      //virtual bool process_init();

      //virtual bool init1();

      //virtual bool init2();

      //virtual bool is_system();






      //virtual ::apex::session * query_session(index iEdge) override;




      //virtual string dir_appmatter_locator(::object * pobject);


      virtual void hist_hist(const ::string & psz);


      //virtual void on_request(::create * pcreate);


      //virtual u32 crc32(u32 dwPrevious, const ::string & psz);


      virtual string url_encode(const ::string & str);


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      virtual string get_locale_schema_dir() override;


      //virtual void     initialize_system(::object * pobject, app_core * pappcore);


      //__pointer(::thread_tools) create_thread_tools(::enum_task_tool etool);
      //thread_tools * tools(::enum_priority epriority);
      //thread_toolset * toolset(e_tool etool);

      // apex commented
      //class ::user::window_map                     &  window_map();


      //void ([a-z0-9_]+)_factory(const ::string & pszComponent, const ::string & pszImplementation, ::fac);

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


      ::operating_system::department                        &  process();

      //using acme::system::process;

      class ::machine_event_central                &  machine_event_central();
      inline ::parallelization::threading           *  threading() { return m_pthreading; }


      //inline  class imaging & imaging() { return *m_pimaging; }

      virtual ::sockets::sockets & sockets() { return *m_psockets; }

      //math::math                                   &  math()
      //{

      //   return *m_pmath;

      //}

      // apex commented
      //inline class ::draw2d::draw2d                & draw2d() { return *m_pdraw2d; }



      //inline class ::compress_department           &  compress()
      //{

      //   return *m_pcompress;   // only usable from base.dll and dependants

      //}




      //inline ::file::system_dir & dir() { return *m_spdir; }
      //inline ::file::system_file & file() { return *m_spfile; }


      //::net::email_department                & email();

      //__pointer(::account::user_set)                userset();

      //virtual string url_encode(const ::string & str);

      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes);

      //::mutex * get_openweather_city_mutex();


      //virtual os_local & oslocal();


      template < typename T >
      inline T * cast_clone(T * p)
      {

         return ::clone(p);

      }


      virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget);
      virtual void open_profile_link(string strUrl, string strProfile, string strTarget) override;


      virtual void __set_thread_on() override;

      virtual string get_local_mutex_name(const ::string & pszAppName);
      virtual string get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId);
      virtual string get_global_mutex_name(const ::string & pszAppName);
      virtual string get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId);


      //template < class T >
      //::type * type_info()
      //{

      //   return get_type_info(typeid(T));

      //}


      //virtual ::type * get_type_info(const ::std::type_info & info);

      //::type * get_type_info(const ::atom & idType)
      //{

      //   if(idType.is_empty())
      //      return nullptr;

      //   synchronous_lock synchronouslock(&m_mutexFactory);

      //   return m_typemap[idType].m_p;

      //}


      //virtual void discard_to_factory(::object * pca);

      //bool on_application_menu_action(const ::string & pszCommand);


      virtual void initialize_sockets();


      virtual bool on_get_task_name(string& strTaskName) override;

      //virtual ::acme::library * get_library(const ::string & pszLibrary, bool bOpenCa2 = false);

      
      //virtual __pointer(::acme::library) get_library(const ::string& str);


      virtual ::u32 os_post_to_all_threads(const ::atom & atom,wparam wparam = 0,lparam lparam = 0);


      virtual void on_add_session(::apex::session* psession);
      virtual void add_session(index iEdge, ::apex::session * psession);
      virtual void erase_session(index iEdge);



      //virtual void init_system();

      //virtual void process_init();

      //virtual void init_draw2d();
      //virtual void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
      //virtual string draw2d_get_default_library_name();

      //virtual bool ([a-z0-9_]+)_factory(::factory::factory * pfactory);
      //virtual string imaging_get_default_library_name();

      virtual void init_thread() override;
      virtual void term_thread() override;


      //virtual void post_to_all_threads(const ::atom& atom, wparam wparam, lparam lparam);


      virtual void thread_loop() override;

      //virtual void init();

      //virtual void init1();

      //virtual void init2();

      virtual void post_creation_requests();

      //virtual void term_system();

      virtual void term2();

      virtual void term1();

      //virtual void term();

      virtual void TermSystem() override;


      virtual void process_term();


      //virtual bool is_system() const override;





      virtual i32 _001OnDebugReport(i32 i1,const ::string & psz1,i32 i2,const ::string & psz2,const ::string & psz3,va_list args);
      virtual i32 _debug_logging_report(i32 iReportType, const ::string & pszFilename, i32 iLinenumber, const ::string & iModuleName, const ::string & pszFormat, va_list list);
      virtual bool assert_failed_line(const ::string & pszFileName,i32 iLine);

      virtual bool on_assert_failed_line(const ::string & pszFileName,i32 iLine);






      virtual void initialize_log(const ::string & pszId);


      virtual void appa_load_string_table();
      virtual void appa_set_locale(const ::string & pszLocale, const ::action_context & action_context);
      virtual void appa_set_schema(const ::string & pszStyle, const ::action_context & action_context);

      virtual bool assert_running_global(const ::string & pszAppName,const ::string & pszId = nullptr);
      virtual bool assert_running_local(const ::string & pszAppName,const ::string & pszId = nullptr);

      //__pointer(application) assert_running(const ::string & pszAppId);

      virtual ::count get_application_count();


      //virtual string crypto_md5_text(const ::string & str);

      //inline class ::http::system                  & http()
      //{
      //   return *m_sphttpsystem;
      //}


      class ::crypto::crypto * crypto();


      virtual ::file::path local_get_matter_cache_path();
      virtual ::file::path local_get_matter_cache_path(string strMatter);
      virtual ::file::path local_get_matter_path();
      virtual ::file::path local_get_matter_path(string strMatter);

      //virtual bool find_applications_from_cache();
      //virtual bool find_applications_to_cache(bool bSave = true);
      //virtual bool map_application_library(const ::string & pszLibrary);


      virtual void install_progress_add_up(int iAddUp = 1);

      virtual void create_session(index iEdge = 0);

      virtual __pointer(::apex::session) on_create_session(index iEdge);

      virtual ::apex::session * session(index iEdge = 0);

      //virtual void on_request(::create * pcreate) override;

      //virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);


      virtual string get_system_platform();
      virtual string get_system_configuration();
      //virtual string get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId);



      virtual void on_start_find_applications_from_cache();
      virtual void on_end_find_applications_from_cache(stream & is);

      virtual void on_end_find_applications_to_cache(stream & os);

      virtual void on_map_application_library(::acme::library & library);

      //virtual void defer_check_exit();



      virtual void do_request(::create * pcreate) override;

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
      
      void on_open_file(const ::string & pszFile) override;

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
      virtual void set_standalone_setting(string str, string strSetting);


      //virtual void on_event(::u64 u, ::object * pobject) override;


      //virtual void on_initial_frame_position(::user::frame * pframe);

      //virtual void on_graphics_ready();

      virtual void process_machine_event_data(machine_event_data * pdata);



      //void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const override;


      virtual string get_user_language();
      virtual void set_user_language(::application * papp, index iSel);
      virtual void set_user_language(::application * papp, string strLang);

      void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);

      //      void commander(string strUrl, string strWeather, string strUser, ::file::path path, string strParam);

      void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      void     firefox(string strUrl, string strBrowser, string strProfile, string strParam);
      //void     get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory);



      //virtual void  initialize_system(::object* pobject, app_core* pappcore) override;

      virtual void discard_to_factory(__pointer(object) pca);

      //virtual bool is_system() const override;

      //virtual void process_init() override;

      //virtual void init2() override;

      //virtual void init_system() override;

      //virtual void term() override;

      //virtual void term_system() override;


      //virtual i32 main();
      ///virtual void InitApplication() override;

      //virtual void init() override;
      //virtual void init1() override;
      //virtual void init3() override;

      //virtual void bergedge_start() override;


      //virtual void initialize_rich_text();


      //virtual index get_new_bergedge(application_bias * pbiasCreation = nullptr);

      //__pointer_array(::apex::session) &    planesessionptra();


      //virtual bool base_support() override;


      DECLARE_MESSAGE_HANDLER(on_application_signal);


      void set_history(::apex::history* phistory);


      //__pointer(::acme::library) on_get_library(const ::string & pszLibrary) override;


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

      //virtual void defer_initialize_x11();
      //virtual bool sn_start_context();

#endif




      //bool sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser = nullptr, ::http::cookies* pcookies = nullptr);
      bool sync_load_url(string& str, const ::string & pszUrl,  ::http::cookies* pcookies = nullptr);





      //      u32 guess_code_page(const ::string & str);

#ifdef _UWP

      virtual bool get_window_rect(RECTANGLE_I32* prectangle);


#endif

      //virtual void post_fork_uri(const ::string & pszUri,application_bias * papplicationbias);



//      virtual bool wait_twf(::duration tickTimeout = U32_INFINITE_TIMEOUT);








      virtual string get_host_location_url();

      //virtual void add_view_library(::acme::library* plibrary);

      //virtual void get_cursor_position(POINT_I32 * ppoint);

      virtual bool is_thread() const override;

      //virtual void do_request(::create* pcommand) override;



      void assert_ok() const override;
      void dump(dump_context& action_context) const override;


      void     main() override;
      //virtual void hist_hist(const ::string & psz) override;


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


      ///virtual void initialize_system(::object* pobject, app_core* pappcore) override;


      //virtual void process_init() override;
      //virtual void term_system() override;

      //virtual __pointer(::apex::session) on_create_session() override;

      //virtual void set_active_guie(::user::interaction* pinteraction);
      //virtual void set_focus_guie(::user::interaction* pinteraction);



      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);
      //virtual int install_canvas_increment_mode() override;


      virtual bool do_events() override;


      void post_quit_to_all_threads();
      void post_to_all_threads(const ::atom& atom, wparam wparam, lparam lparam);

      //virtual bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle) override;

      //virtual ::count get_monitor_count() override;

      //bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle) override;


      //virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
      //virtual ::user::interaction * ui_from_handle(void * pdata) override;
      
      void dump_command_line_and_environment_variables_to_file();

      void system_id_update(::i64 iUpdate, ::i64 iPayload) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant) override;

      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::context * pcontext) override;

      // virtual void on_command_create(::create* pcreate);

      //virtual bool initialize_native_window1() override;

      //virtual ::acme::library* load_library(const ::string & pszLibrary);

      virtual void application_main(int argc, char *argv[], const ::string & pszCommandLine);

      virtual int console_end(::e_status estatus);


      //virtual __pointer(::extended::future < ::conversation >) message_box(::user::interaction * puserinteraction, const ::string & pszText, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;


      virtual void get_public_internet_domain_extension_list(string_array& stra) override;


   };


   //CLASS_DECL_APEX ::mutex * get_image_mutex();

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
//#define SET_ENUM_TEXT(enum_value) psystem->set_enum_text(enum_value, TOSTRING(enum_value))


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

CLASS_DECL_APEX int app_core_main(const ::string & psz);

#endif

