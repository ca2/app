//
// Created by camilo on 2024-10-24 18:19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "platform.h"
#include "context.h"
#include "acme/constant/os_text.h"
#include "acme/prototype/prototype/factory.h"


namespace platform
{


   struct apex_system_layer_t
   {


//
//#ifndef WINDOWS
//
//
//      ::pointer<::exception_translator>                 m_pexceptiontranslator;
//
//
//#endif

      ::pointer < ::file::watcher >                         m_pfilewatcher;
      //::pointer<::dump_context>                           m_pdumpcontext;

      ::pointer<::networking::networking>                   m_pnetworking;

      //::pointer<::crypto::crypto>                         m_pcrypto;

      ::pointer<class machine_event_central>                m_pmachinehappeningcentral;

      ::pointer < ::mutex >                                 m_pmutexUserAppData;
      ::pointer < ::mutex >                                 m_pmutexSystemAppData;

      ::pointer<::operating_system::department>             m_poperatingsystem;

      ::pointer<::parallelization::threading>               m_pthreading;
      size_t                                                m_nSafetyPoolSize; // ideal int_size


      ::pointer < ::input::input >                          m_pinput;

      ::pointer < ::factory::factory >                      m_pfactoryCrypto;

      string_array                                          m_straCommandLineAccumul;
      string_array                                          m_straCommandLineExtra;
      class ::time                                          m_timeCommandLineLast;
      int                                                   m_iCommandLineDelay;

      bool                                                  m_bSystemSynchronizedCursor;
      bool                                                  m_bSystemSynchronizedScreen;


      ::pointer < ::manager_room >                          m_pmanagerroom;

      ::pointer<class ::apex::history>                      m_phistory;


   };



   class CLASS_DECL_ACME apex_system_layer
   {
   public:




      //virtual void _compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation) override;
      //virtual void _uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation, transfer_progress_function transferprogressfunction = {}) override;

      virtual void defer_innate_ui();


#ifdef WINDOWS_DESKTOP

#elif defined(UNIVERSAL_WINDOWS)

      void system_construct(const ::string_array & stra);

#else

      void system_construct(const ::string & pszCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif

      //virtual void __task_init();


      virtual class ::manager_room * manager_room();

      virtual ::platform::application * get_main_app();


      // virtual void init();
      //
      // virtual void inline_init();
      // virtual void inline_term();
      //
      //
      // virtual void init_system();
      // virtual void term_system();
      //
      // virtual void on_system_construct();
      //
      // virtual void on_start_system();
      //
      // virtual void system_main();
      //
      // virtual void term();

      //DECLARE_MESSAGE_HANDLER(on_message_erase_session);

      virtual string get_application_server_name();

      //virtual bool task_get_run() const;

      
      virtual void create_os_node();

      
      //::apex::node * node();


      virtual ::file::watcher * file_watcher() const;


      virtual ::input::input * input();


      virtual ::factory::factory * node_factory();

      // virtual void process_init();
      //
      // virtual void init1();
      //
      // virtual void init2();

      void defer_post_initial_request();

      //void post_request(::request* prequest);

      //virtual void initialize_context();


      virtual ::pointer<::data::node>load_xml(const ::string & pszXml);

      //virtual void verb(); // ambigous inheritance from ::apex::system/::axis::application


      //virtual bool is_system() const;


      virtual string crypto_md5_text(const ::string & str);



      // void on_request(::request * prequest);
      //
      // void destroy();
      //
      
      virtual void initialize_crypto();
      

      virtual void process_exit_status(::object* pparticle, const ::e_status & estatus);


      virtual void hist_hist(const ::string & psz);



      //virtual string ::url::encode(const ::string & str);


      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      //virtual string get_locale_schema_dir();

      virtual ::operating_system::department * operating_system();

      virtual class ::machine_event_central * machine_event_central();
      virtual ::parallelization::threading           *  threading();


      virtual ::networking::networking * networking();


      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes);



      virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget);
      virtual void open_profile_link(string strUrl, string strProfile, string strTarget);


      //virtual void __set_thread_on();

      //virtual string get_local_mutex_name(const ::string & pszAppName);
      //virtual string get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId);
      //virtual string get_global_mutex_name(const ::string & pszAppName);
      //virtual string get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId);


      virtual void initialize_networking();

      //
      // virtual bool on_get_task_name(string& strTaskName);
      //


      virtual unsigned int os_post_to_all_threads(const ::atom & atom, wparam wparam = {}, lparam lparam = 0);


      //
      //
      //
      // virtual void init_task();
      // virtual void term_task();
      //
      //
      //
      // virtual void thread_loop();
      //
      //
      // virtual void post_pending_requests();
      //
      //
      // virtual void term2();
      //
      // virtual void term1();
      //
      //
      // virtual void TermSystem();
      //
      //
      // virtual void process_term();
      //





      virtual int _001OnDebugReport(int i1,const ::string & psz1,int i2,const ::string & psz2,const ::string & psz3,va_list args);
      virtual int _debug_logging_report(int iReportType, const ::string & pszFilename, int iLinenumber, const ::string & iModuleName, const char * pszFormat, va_list list);
      virtual bool assert_failed_line(const ::string & pszFileName,int iLine);

      virtual bool on_assert_failed_line(const ::string & pszFileName,int iLine);






      virtual void initialize_log(const ::string & pszId);


      virtual void appa_load_string_table();
      virtual void appa_set_locale(const ::string & pszLocale, const ::action_context & action_context);
      virtual void appa_set_schema(const ::string & pszStyle, const ::action_context & action_context);

      virtual bool assert_running_global(const ::string & pszAppName,const ::string & pszId = nullptr);
      virtual bool assert_running_local(const ::string & pszAppName,const ::string & pszId = nullptr);


      virtual ::collection::count get_application_count();






      virtual void install_progress_add_up(int iAddUp = 1);







      virtual void on_start_find_applications_from_cache();
      //virtual void on_end_find_applications_from_cache(stream & is);

      //virtual void on_end_find_applications_to_cache(stream & os);

      virtual void on_map_application_library(::acme::library & library);


      //void request(::request * prequest) override;


#ifdef ANDROID
//#pragma message("at macos??")
      virtual bool android_set_user_wallpaper(string strUrl);
      virtual bool android_get_user_wallpaper(string & strUrl);

#endif

      virtual bool defer_accumulate_on_open_file(string_array stra, string strExtra);

      //virtual bool merge_accumulated_on_open_file(::request * prequest);

      virtual bool on_open_file(::payload payloadFile, string strExtra);

      virtual void on_open_file(const ::string & pszFile);


      virtual void on_os_text(enum_os_text etext, string strText);



      virtual void on_extra(string str);

      virtual string standalone_setting(string str);
      virtual void set_standalone_setting(string str, string strSetting);


      virtual void process_machine_event_data(machine_event_data * pdata);

      virtual string get_user_language();
      virtual void set_user_language(::apex::application * papp, ::collection::index iSel);
      virtual void set_user_language(::apex::application * papp, string strLang);

      virtual void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);


      virtual void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      virtual void     firefox(string strUrl, string strBrowser, string strProfile, string strParam);




      virtual void discard_to_factory(::pointer<object>pca);



      //DECLARE_MESSAGE_HANDLER(on_application_signal);


      virtual void set_history(::apex::history* phistory);




      virtual ::apex::history * hist();



      virtual bool sync_load_url(string& str, const ::string & pszUrl,  ::http::cookies* pcookies = nullptr);





#ifdef UNIVERSAL_WINDOWS

      virtual bool window_rectangle(::int_rectangle* prectangle);


#endif







      virtual string get_host_location_url();

      // virtual bool is_thread() const;
      //
      //
      //
      // // void assert_ok() const override;
      // //void dump(dump_context& action_context) const override;
      //
      // virtual void main();


      //virtual bool do_tasks();


      virtual void post_quit_to_all_threads();
      virtual void post_to_all_threads(const ::atom& atom, wparam wparam, lparam lparam);


      virtual void dump_command_line_and_environment_variables_to_file();

      virtual void system_id_update(huge_integer iUpdate, huge_integer iPayload);


      [[nodiscard]] virtual class ::handler::signal * signal(const ::atom& atom);


      // virtual void add_handler(::particle * pmatter);
      //
      // virtual void add_signal_handler(::matter * pmatter, const ::atom & atomSignal);
      //
      // virtual void add_signal_handler(const ::signal_handler & signalhandler, const ::atom & atomSignal);
      //
      // virtual void erase_signal_handler(::matter * pmatter);
      //
      // virtual void erase_signal_handler(::signal_handler::base * pbase);

      //void erase_signal_handlers(::particle * pparticle) override;

      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant);

      virtual void handle(::topic * ptopic, ::context * pcontext);

      virtual bool _handle_uri(const ::block & block);

      virtual void application_main(int argc, char *argv[], const ::string & pszCommandLine);

      virtual int console_end(::e_status estatus);


      //virtual void get_public_internet_domain_extension_list(string_array& stra) override;


      ::string fetch_public_internet_domain_extension_list_text();

      virtual void on_application_dark_mode_change() ;



   };



} // namespace platform

