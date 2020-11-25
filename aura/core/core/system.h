#pragma once


namespace aura
{


   class CLASS_DECL_AURA system :
      virtual public ::aura::system
   {
   public:


      //index                                        m_iNewEdge;

#ifdef WINDOWS_DESKTOP

      ::u32                                         m_uiWindowsTaskbarCreatedMessage;

#endif

      ::mutex                                        m_mutex;
      __pointer(::filehandler::handler)                   m_pfilehandler;


      ::mutex                                        m_mutexDelete;


//    class ::aura::stra                           m_stra;
//    class ::aura::service                        m_service;


      class ::aura::patch   *                      m_ppatch;

//      __pointer(::aura::run_start_installer)              m_prunstartinstaller;

      //__pointer(::aura::session::map)                     m_pbergedgemap;
      //__pointer_array(::aura::session)                         m_planesessionptra;

      __pointer(class ::aura::history)                    m_phistory;

      //      ::sockets::net                               m_net;
      //      __pointer(::aura::filehandler::handler)  m_spfilehandler;


      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      //bool                                         m_bInitApplication;
      //bool                                         m_bInitApplicationResult;
      //bool                                         m_bProcessInitialize;
      //bool                                         m_bProcessInitializeResult;

      strid_map < ::apex::library * >              m_idmapCreateViewLibrary;

      __pointer_array(::apex::library)                         m_libraryspa;

#ifdef _UWP
      
      Agile < Windows::UI::Core::CoreWindow >      m_window;

#endif


      system();
      virtual ~system();

      virtual ::estatus  initialize_system(::layered * pobjectContext, app_core * pappcore) override;

      virtual void discard_to_factory(__pointer(object) pca);

      virtual bool is_system() const override;

      virtual ::estatus process_init() override;

      virtual ::estatus init2() override;

      virtual ::estatus init_system() override;

      virtual void term() override;

      virtual void term_system() override;


      //virtual i32 main();
      ///virtual ::estatus InitApplication() override;

      virtual ::estatus init() override;
      virtual ::estatus init1() override;
      //virtual ::estatus init3() override;

      //virtual ::estatus bergedge_start() override;


      virtual ::estatus initialize_rich_text();


      //virtual index get_new_bergedge(application_bias * pbiasCreation = nullptr);

      //__pointer_array(::aura::session) &    planesessionptra();


      //virtual bool base_support() override;


      DECL_GEN_SIGNAL(on_application_signal);


      bool set_history(::aura::history * phistory);


      __pointer(::apex::library) on_get_library(const char * pszLibrary) override;


      //virtual ::aura::session *  get_platform(index iEdge,application_bias * pbiasCreation = nullptr);


      virtual void on_request(::create * pcreate) override;

      //      virtual __pointer(::handler) handler();





      //virtual i32 main();

      virtual void on_allocation_error(const ::string & str, ::object * pobjectSometimes) override;

      //virtual __pointer(::aura::session) on_create_session() override;


//      ::aura::stra                           & stra();
      //    ::aura::service                        & service();
      ::aura::history                        & hist();

      class ::aura::patch                    & patch();

      //::http::system                         & http();

      ::filehandler::handler                 & filehandler();








      bool sync_load_url(string & str,const char * pszUrl,::account::user * puser = nullptr,::http::cookies * pcookies = nullptr);





//      u32 guess_code_page(const string & str);

#ifdef _UWP

      virtual bool get_window_rect(RECT32 * prect);


#endif

      //virtual void post_fork_uri(const char * pszUri,application_bias * papplicationbias);

      

//      virtual bool wait_twf(millis tickTimeout = U32_INFINITE_TIMEOUT);








      virtual string get_host_location_url();

      virtual ::estatus add_view_library(::apex::library * plibrary);

      //virtual void get_cursor_pos(POINT32 * ppoint);



      virtual ::estatus do_request(::create * pcommand) override;


      void assert_valid() const override;
      void dump(dump_context & action_context) const override;


      virtual ::estatus     main() override;
      virtual void hist_hist(const char * psz) override;


      virtual ::type get_pane_tab_view_type_info();
      virtual ::type get_simple_frame_window_type_info();
      virtual ::type get_simple_child_frame_type_info();

      virtual void on_start_find_applications_from_cache() override;
      virtual void on_end_find_applications_from_cache(stream & is) override;

      virtual void on_end_find_applications_to_cache(stream & os) override;

      virtual void on_map_application_library(::apex::library & library) override;

      virtual void on_graphics_ready() override;



      //system();
      //virtual ~system();


      ///virtual ::estatus initialize_system(::object* pobjectContext, app_core* pappcore) override;


      //virtual ::estatus process_init() override;
      //virtual void term_system() override;

      //virtual __pointer(::aura::session) on_create_session() override;

      virtual void set_active_guie(::user::interaction* pinteraction);
      virtual void set_focus_guie(::user::interaction* pinteraction);



      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      //virtual int install_canvas_increment_mode() override;



      virtual ::u32 get_monitor_color_temperature(index iMonitor);
      virtual bool adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dwGamma);
      virtual bool get_monitor_rect(index iMonitor, RECT32* prect) override;

      virtual ::count get_monitor_count() override;

      bool get_wkspace_rect(index iWkspace, RECT32* prect) override;


      //virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
      //virtual ::user::interaction * ui_from_handle(void * pdata) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;



      //virtual bool initialize_native_window1() override;


   };


} // namespace aura








// void CLASS_DECL_AURA __start_core_system_main(::base::system * psystem);

#ifdef _UWP

CLASS_DECL_AURA int app_core_main(const char * psz);

#endif

