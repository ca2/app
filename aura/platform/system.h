#pragma once


#include "context.h"
#include "aqua/platform/system.h"


namespace aura
{


   class CLASS_DECL_AURA system:
      virtual public ::aqua::system
         //,
      //virtual public ::aura::context
   {
   public:

      //
      // bool                                              m_bAvoidFirstResponder;
      //
      // ::type_atom                                       m_typeatomPaneTabImpact;
      //
      // ::pointer<::windowing::window>                    m_pwindowMain;
      //
      //
      // ::factory::factory_pointer                        m_pfactoryDraw2d;
      // ::pointer<::draw2d::draw2d>                       m_pdraw2d;
      //
      // double                                            m_dDpi;
      //
      // ::pointer < ::mutex >                             m_pmutexUserChildren;
      // ::pointer<class ::image::imaging>                 m_pimaging;
      //
      // ::pointer<::gpu::approach>                        m_pgpu;
      //
      // bool                                              m_bProdevianMouse;
      //
      //
      // string_map < ::image::image_pointer >             m_mapImage;
      //
      // ::pointer<::hardware::devices>                    m_phardwaredevices;
      //




      system();
      ~system() override;


      void common_construct();

      //void on_set_platform() override;

      void on_initialize_particle() override;

      void on_add_session(::platform::session* papexsession) override;

      void init() override;
      //virtual void init_instance() override;
      //virtual void term_instance() override;
      void inline_init() override;
      void inline_term() override;

      void TermSystem() override;

      virtual void on_finish_launching() override;


//#ifdef LINUX
//
//      virtual void os_application_system_run() override;
//
//#endif


//      virtual void init_system() override;
//      virtual void term_system() override;


      virtual void system_main() override;

      virtual void term() override;

      //virtual void system_prep() override;

      //::url::url                           & url()     { return m_urldepartment; }

      //::thread * get_task(itask_t itask);
      //itask_t get_thread_id(::thread * pthread);
      //void set_thread(itask_t itask, ::thread * pthread);
      //void unset_thread(itask_t itask, ::thread * pthread);

      ::aura::estamira * estamira() override;

       ::hardware::devices* hardware_devices() override;

      void defer_initialize_hardware_devices() override;



      //::aura::session* get_session();
      //::aura::node* node();

       ::gpu::approach* get_gpu() override;
       ::gpu::approach* gpu() override; 
      void create_gpu() override;

      
      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const ::string & pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const ::string & pszVersion) override;
      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
      //virtual int install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
      //virtual int install_progress_app_add_up(int iAddUp = 1) override;

      //virtual ::install::canvas * install_create_canvas();
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      //virtual int install_canvas_increment_mode();

      //virtual string install_get_platform() override;
      //virtual void install_set_platform(const ::string & pszPlatform) override;
      //virtual string install_get_version() override;
      //virtual void install_set_version(const ::string & pszVersion) override;
      //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
      //virtual int install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
      //virtual int install_progress_app_add_up(int iAddUp = 1) override;

      virtual ::factory::factory * node_factory() override;

      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2() override;

      //virtual void initialize_context() override;

      //virtual void defer_xml();
       
      
      //void node_will_finish_launching() override;
      
      
      //void windowing_post_quit() override;
      

      virtual ::pointer<::data::node>load_xml(const ::string & pszXml) override;

      virtual void verb() override; // ambigous inheritance from ::aura::system/::axis::application


      //virtual bool is_system() const override;


      virtual string crypto_md5_text(const ::string & str) override;


      //virtual pointer< ::extended::future < ::conversation > > _message_box(oswindow oswindow, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;
      //virtual ::enum_dialog_result message_box_timeout(const ::string & pszMessage, const ::string & pszTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future()) override;


      //virtual void create_html();

      //virtual ::pointer<::aura::session>on_create_session() override;

      //virtual void on_request(::request * prequest) override;

      //virtual void construct(const ::string & pszAppId);

      //virtual bool initialize_application() override;

      //virtual int exit_instance();
      //virtual bool destroy();

      virtual void destroy() override;




      //virtual bool verb();

      //virtual void main_user_async(const ::procedure & procedure, ::enum_priority epriority = e_priority_normal) override;


      //virtual bool process_initialize();

      //virtual bool process_init();

      //virtual bool init1();

      //virtual bool init2();

      //virtual bool is_system();



      //virtual ::aura::session * query_session(::collection::index iEdge) override;




      //virtual string dir_appmatter_locator(::particle * pparticle);


      //virtual void hist_hist(const ::string & psz);


      //virtual void on_request(::request * prequest) override;


      //virtual unsigned int crc32(unsigned int dwPrevious, const ::string & psz);


      //virtual string ::url::encode(const ::string & str) override;


      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      //virtual string get_locale_schema_dir() override;


      //virtual void     initialize_system(::particle * pparticle, app_core * pappcore);


      //::pointer<::thread_tools>create_thread_tools(::enum_task_tool etool);
      //thread_tools * tools(::enum_priority epriority);
      //thread_toolset * toolset(e_tool etool);

      //class ::user::window_map                     &  window_map();


      //::pointer<::acme::library>open_component_library(const ::string & pszComponent, const ::string & pszImplementation);

      //void ([a-z0-9_]+)_factory(const ::string & pszComponent, const ::string & pszImplementation);

      //void ([a-z0-9_]+)_factory(const ::string & pszComponent, const ::string & pszImplementation, PFN_factory pfnFactoryExchange);


      //class ::aura::os                             &  os();
      //class base_factory                           &  factory_item();


      //::aura::str                                  &  str();
      //::operating_system::department                        &  process();


      //::xml::department                            &  xml();
      //class ::base64                          &  base64();
      //class ::aura::log                            &  log();
      //class ::machine_event_central                &  machine_event_central();
      //inline ::parallelization::threading           *  threading() { return m_pthreading; }

      //geometry::geometry                           &  geometry()
      //{

      //   return *m_pgeometry;

      //}
      //inline  class imaging & imaging() { return *m_pimaging; }

      //virtual ::sockets::sockets & sockets() { return *m_psockets; }

      //math::math                                   &  math()
      //{

      //   return *m_pmath;

      //}


      class ::draw2d::draw2d * draw2d() override;

      class ::write_text::write_text * write_text() override;
      
      
      class ::image::imaging * imaging() override;


      //inline ::url::url                     &  url()
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

      //::pointer<::account::user_set>               userset();

      //::datetime::datetime                 & datetime();


      //virtual string ::url::encode(const ::string & str);

      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes) override;

      //::pointer< ::mutex > get_openweather_city_mutex();


      template < typename T >
      inline T * cast_clone(T * p)
      {

         return ::clone(p);

      }


      //virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget) override;
      //virtual void open_profile_link(string strUrl, string strProfile, string strTarget) override;
      //virtual void open_link(string strUrl, string strProfile, string strTarget) override;
      //virtual void open_url(string strUrl, string strProfile, string strTarget) override;


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


      //virtual ::type_atom * get_type_info(const ::std::type_info & info);

      //::type * get_type_info(const ::atom & idType)
      //{

      //   if(idType.is_empty())
      //      return nullptr;

      //   synchronous_lock synchronouslock(m_pmutexFactory);

      //   return m_typemap[idType].m_p;

      //}


      //virtual void discard_to_factory(::object * pca);

      bool on_application_menu_action(const ::string & pszCommand);


      //virtual void initialize_sockets();


      //virtual bool on_get_thread_name(string& strThreadName) override;

      //virtual ::acme::library * on_get_library(const ::string & pszLibrary) override;

      //virtual ::acme::library * get_library(const ::string & pszLibrary, bool bOpenCa2 = false) override;


      //virtual unsigned int os_post_to_all_threads(const ::atom & atom,wparam wparam = 0,lparam lparam = 0) override;


      //virtual void session_add(::collection::index iEdge, ::apex::session * psession) overr;
      //virtual void session_erase(::collection::index iEdge);



      //virtual void init_system();

      //virtual void process_init();

      virtual void initialize_draw2d() override;
         virtual void initialize_imaging();
      //virtual void initialize_write_text();
      virtual ::factory::factory * draw2d_factory() override;
      virtual ::string draw2d_get_default_implementation_name() override;

      virtual ::factory::factory * imaging_factory() override;
      virtual ::string imaging_get_default_implementation_name() override;

      virtual void init_task() override;
      virtual void term_task() override;


      //virtual void thread_loop() override;

      //virtual void init();

      //virtual void init1();

      //virtual void init2();

      //virtual void post_creation_requests() override;

      //virtual void term_system();

      virtual void term2() override;

      virtual void term1() override;

      //virtual void term();

      //virtual void TermSystem() override;


      virtual void process_term() override;


      //virtual bool is_system() const override;




  /*    static inline ::atom atom(const ::std::type_info & info);
      static inline ::atom atom(const ::string & psz);
      static inline ::atom atom(const ::string & str);
      static inline ::atom atom(huge_integer i);
      static inline ::atom_space & atom();
      inline ::atom atom(const ::payload & payload);
      inline ::atom atom(const property & prop);*/


      //virtual int _001OnDebugReport(int i1, const ::string & psz1,int i2, const ::string & psz2, const ::string & psz3,va_list args) override;
      //virtual int _debug_logging_report(int iReportType, const ::string & pszFilename, int iLinenumber, const ::string & iModuleName, const ::string & pszFormat, va_list list) override;
      //virtual bool assert_failed_line(const ::string & pszFileName,int iLine) override;

      //virtual bool on_assert_failed_line(const ::string & pszFileName,int iLine) override;






      //virtual void initialize_log(const ::string & pszId) override;


      //virtual void appa_load_string_table() override;
      //virtual void appa_set_locale(const ::string & pszLocale, const ::action_context & action_context) override;
      //virtual void appa_set_schema(const ::string & pszStyle, const ::action_context & action_context) override;

      //virtual bool assert_running_global(const ::string & pszAppName, const ::string & pszId = nullptr) override;
      //virtual bool assert_running_local(const ::string & pszAppName, const ::string & pszId = nullptr) override;

      //::pointer<application>assert_running(const ::string & pszAppId);

  /*    virtual ::collection::count get_application_count() override;
*/

      //virtual string crypto_md5_text(const ::string & str);

      //inline class ::http::system                  & http()
      //{
      //   return *m_sphttpsystem;
      //}

      //class ::crypto::crypto                       & crypto();


      //virtual void start() override;

      //virtual ::file::path local_get_matter_cache_path() override;
      //virtual ::file::path local_get_matter_cache_path(string strMatter) override;
      //virtual ::file::path local_get_matter_path() override;
      //virtual ::file::path local_get_matter_path(string strMatter) override;

      //virtual bool find_applications_from_cache() override;
      //virtual bool find_applications_to_cache(bool bSave = true) override;
      //virtual bool map_application_library(const ::string & pszLibrary) override;


      //virtual void install_progress_add_up(int iAddUp = 1) override;

      //virtual void create_session(::collection::index iEdge = 0) override;

      /*virtual ::pointer<::apex::session>on_create_session(::collection::index iEdge) override;

      virtual ::apex::session * session(::collection::index iEdge = 0) override;*/

      //virtual void on_request(::request * prequest) override;

      //::pointer<regex>create_regular_expression(const ::string & pszStyle, const string& str);
      //::pointer<regex_context>create_regular_expression_context(const ::string & pszStyle, int iCount);
      //virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);


      //virtual string get_system_platform() override;
      //virtual string get_system_configuration() override;
      //virtual string get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId);




      //#ifndef UNIVERSAL_WINDOWS

      //virtual void get_time(timeval * int_point) override;

      //#endif

      virtual void on_start_system() override;
      //virtual void on_start_find_applications_from_cache() override;
      //virtual void on_end_find_applications_from_cache(stream & is) override;

      //virtual void on_end_find_applications_to_cache(stream & os) override;

      //virtual void on_map_application_library(::acme::library & library) override;

      //virtual void defer_check_exit();



      //virtual void do_request(::request * prequest) override;

      //virtual void defer_check_openweather_city_list();

      //virtual openweather_city * openweather_find_city(string strQuery);
      //virtual ::collection::index openweather_find_city2(string strQuery, string & strCit, huge_integer & iId, double & dLat, double & dLon);
      //virtual ::collection::index openweather_find_city2(string strQ1, string strQ2, string & strCit, huge_integer & iId, double & dLat, double & dLon, bool bPrefix);

//#ifdef ANDROID
////#pragma message("at macos??")
//      virtual bool android_set_user_wallpaper(string strUrl) override;
//      virtual bool android_get_user_wallpaper(string & strUrl) override;
//
//#endif
//
//      virtual bool defer_accumulate_on_open_file(string_array stra, string strExtra) override;
//
//      virtual bool merge_accumulated_on_open_file(::request * prequest) override;
//
//      virtual bool on_open_file(::payload payloadFile, string strExtra) override;
//
      //virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);

      //virtual bool initialize_native_window1();

      //virtual void * initialize_native_window2(const ::int_rectangle & rectangle);


      //virtual void on_os_text(e_os_text etext, string strText) override;

      //virtual ::windowing::window * impl_from_handle(void * posdata);
      //virtual ::user::interaction * ui_from_handle(void * posdata);




      //virtual void on_extra(string str) override;

      //virtual string standalone_setting(string str) override;
      //virtual bool set_standalone_setting(string str, string strSetting) override;


      //virtual void on_event(huge_natural u, ::particle * pparticle) override;


      virtual void on_initial_frame_position(::user::frame_interaction * pframe) override;

      virtual void on_graphics_ready() override;

      //virtual void process_machine_event_data(machine_event_data * pdata) override;



      //virtual void __tracea(enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, int iLine, const ::string & psz) const override;


      //void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);

      //void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      //void     firefox(string strUrl, string strBrowser, string strProfile, string strParam);
      //void     get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory);



      //virtual void  initialize_system(::object* pparticle, app_core* pappcore) override;

 /*     virtual void discard_to_factory(::pointer<object>pca) override;*/

      //virtual bool is_system() const override;

      //virtual void process_init() override;

      //virtual void init2() override;

      //virtual void init_system() override;

      //virtual void term() override;

      //virtual void term_system() override;


      //virtual int main();
      ///virtual void InitApplication() override;

      //virtual void init() override;
      //virtual void init1() override;
      //virtual void init3() override;

      //virtual void bergedge_start() override;


      //virtual void initialize_rich_text();


      //virtual ::collection::index get_new_bergedge(application_bias * pbiasCreation = nullptr);

      //pointer_array < ::aura::session > &    planesessionptra();


      //virtual bool base_support() override;


      //DECLARE_MESSAGE_HANDLER(on_application_signal);


      //void set_history(::apex::history* phistory);


      //::pointer<::acme::library>on_get_library(const ::string & pszLibrary) override;


      //virtual ::aura::session *  get_platform(::collection::index iEdge,application_bias * pbiasCreation = nullptr);


      //virtual void on_request(::create* pcreate) override;

      //      virtual ::pointer<::handler>handler();





      //virtual int main();

      //virtual void on_allocation_error(const ::string& str, ::object* pobjectSometimes) override;

      //virtual ::pointer<::aura::session>on_create_session() override;


//      ::aura::stra                           & stra();
      //    ::aura::service                        & service();
      //::aura::history& hist();

      //class ::aura::patch& patch();

      //::http::system                         & http();

      //::filehandler::handler& filehandler();


//#ifdef LINUX
//
//      virtual void deferx_initializex_x11() ;
//      virtual bool sn_start_context();
//
//#endif

      ////bool sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser = nullptr, ::http::cookies* pcookies = nullptr);
      //bool sync_load_url(string& str, const ::string & pszUrl,  ::http::cookies* pcookies = nullptr);



      //      unsigned int guess_code_page(const ::string & str);

//#ifdef UNIVERSAL_WINDOWS
//
//      virtual bool window_rectangle(::int_rectangle* prectangle);
//
//
//#endif

      //virtual void post_fork_uri(const ::string & pszUri,application_bias * pappbias);



//      virtual bool wait_twf(class ::time tickTimeout = U32_INFINITE_TIMEOUT);








      virtual string get_host_location_url() override;

//      virtual void add_impact_library(::acme::library* plibrary);

      //virtual void get_cursor_position(::int_point * ppoint);



      //virtual void do_request(::create* pcommand) override;


//#ifdef _DEBUG
//
//      virtual void set_context(::context* pcontext) override;
//      virtual void set_context_thread(::thread* pthread) override;
//      virtual void set_context_app(::aura::application* pappContext) override;
//      virtual void set_context_session(::aura::session* psessionContext) override;
//      virtual void set_context_system(::aura::system* psystemContext) override;
//
//#endif


      // void assert_ok() const override;
      //void dump(dump_context& action_context) const override;


      virtual void     main() override;
      //virtual void hist_hist(const ::string & psz) override;


      virtual ::type_atom get_pane_tab_impact_type_info() override;
      virtual ::type_atom get_simple_frame_window_type_info() override;
      //virtual ::type_atom get_simple_child_frame_type_info();

      //virtual void on_start_find_applications_from_cache() override;
      //virtual void on_end_find_applications_from_cache(stream& is) override;

      //virtual void on_end_find_applications_to_cache(stream& os) override;

      //virtual void on_map_application_library(::acme::library& library) override;

      //virtual void on_graphics_ready() override;


      //void _on_initialize_window_object() override;


      //system();
      //virtual ~system();


      ///virtual void initialize_system(::object* pparticle, app_core* pappcore) override;


      //virtual void process_init() override;
      //virtual void term_system() override;

      //virtual ::pointer<::aura::session>on_create_session() override;




      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
      //virtual int install_canvas_increment_mode() override;



      //virtual unsigned int get_monitor_color_temperature(::collection::index iMonitor);
      //virtual bool adjust_monitor(::collection::index iMonitor, unsigned int dwTemperature, double dBrightness, double dwGamma);
      //virtual bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle* prectangle) override;

      //virtual ::collection::count get_monitor_count() override;

      //bool get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle* prectangle) override;


      //virtual ::windowing::window * impl_from_handle(void * pdata) override;
      //virtual ::user::interaction * ui_from_handle(void * pdata) override;

      //void signal(::signal * psignal) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void initialize_estamira() override;

      virtual void _001AddPacks(string_to_string& base64map, string& str) override;

      //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;

      //void windowing_send(const ::procedure & procedure) override;
      //void windowing_post(const ::procedure & procedure) override;


      //::string implementation_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)


      void do_graphics_and_windowing_system_factory() override;


   };


   //CLASS_DECL_AURA ::pointer< ::mutex > get_image_mutex();


} // namespace aura



