#pragma once


#include "session.h"
#include "context.h"
#include "acme/constant/os_text.h"
#include "acme/platform/system.h"
#include "apex/parallelization/threading.h"


namespace apex
{


   class CLASS_DECL_APEX system:
      virtual public ::acme::system,
      virtual public ::apex::context
   {
   public:




#ifndef WINDOWS


      ::pointer<::exception_translator>                 m_pexceptiontranslator;


#endif

      //::pointer<::dump_context>                       m_pdumpcontext;

      ::pointer<::networking::networking>             m_pnetworking;

      //::pointer<::crypto::crypto>                     m_pcrypto;

      ::pointer<class machine_event_central>           m_pmachineeventcentral;

      ::pointer < ::mutex >                                m_pmutexUserAppData;
      ::pointer < ::mutex >                                m_pmutexSystemAppData;

      ::pointer < ::mutex >                                m_pmutexMatter;

      ::pointer<::operating_system::department>       m_poperatingsystem;

      ::pointer<::parallelization::threading>         m_pthreading;
      size_t                                             m_nSafetyPoolSize; // ideal size_i32




      string_array                                       m_straCommandLineAccumul;
      string_array                                       m_straCommandLineExtra;
      class ::time                                         m_timeCommandLineLast;
      int                                                m_iCommandLineDelay;
      
      bool                                               m_bSystemSynchronizedCursor;
      bool                                               m_bSystemSynchronizedScreen;

      

      ::pointer<class ::apex::history>                m_phistory;


      system();
      ~system() override;


      void common_construct();


#ifdef _DEBUG


      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      void initialize(::particle * pparticle) override;

      void install_message_routing(::channel * pchannel) override;

      void system_construct(::acme::application * papplication) override;


#ifdef WINDOWS_DESKTOP

#elif defined(_UWP)

      void system_construct(const ::string_array & stra);

#else

      void system_construct(const ::string & pszCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif

      virtual void __task_init() override;


      virtual ::acme::application * get_main_app() override;


      virtual void init();

      virtual void inline_init() override;
      virtual void inline_term() override;


      virtual void init_system() override;
      virtual void term_system();

      virtual void on_system_construct();

      virtual void on_start_system() override;

      virtual void system_main() override;

      virtual void term();


      DECLARE_MESSAGE_HANDLER(on_message_erase_session);


      virtual string get_application_server_name();



      virtual bool task_get_run() const override;


      virtual void create_os_node() override;


      ::apex::node * node();


      virtual ::pointer<::factory::factory>& node_factory() override;

      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2() override;

      void defer_post_initial_request() override;

      //void post_request(::request* prequest);

      virtual void initialize_context() override;


      virtual ::pointer<::data::node>load_xml(const ::string & pszXml);

      virtual void verb() override; // ambigous inheritance from ::apex::system/::axis::application


      virtual bool is_system() const override;


      virtual string crypto_md5_text(const ::string & str);



      void on_request(::request * prequest) override;

      void destroy() override;


      virtual void process_exit_status(::object* pparticle, const ::e_status & estatus);


      virtual void hist_hist(const ::string & psz);



      //virtual string ::url::encode(const ::string & str);


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      virtual string get_locale_schema_dir() override;

      ::operating_system::department                        &  operating_system();

      class ::machine_event_central                &  machine_event_central();
      inline ::parallelization::threading           *  threading() { return m_pthreading; }


      virtual ::networking::networking * networking() { return m_pnetworking; }


      virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes);




      template < typename T >
      inline T * cast_clone(T * p)
      {

         return ::clone(p);

      }


      virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget);
      virtual void open_profile_link(string strUrl, string strProfile, string strTarget) override;


      virtual void __set_thread_on() override;

      //virtual string get_local_mutex_name(const ::string & pszAppName);
      //virtual string get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId);
      //virtual string get_global_mutex_name(const ::string & pszAppName);
      //virtual string get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId);


      virtual void initialize_networking();


      virtual bool on_get_task_name(string& strTaskName) override;



      virtual ::u32 os_post_to_all_threads(const ::atom & atom, wparam wparam = {}, lparam lparam = 0);





      virtual void init_task() override;
      virtual void term_task() override;



      virtual void thread_loop() override;


      virtual void post_pending_requests();


      virtual void term2();

      virtual void term1();


      virtual void TermSystem() override;


      virtual void process_term();






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


      virtual ::count get_application_count();




      class ::crypto::crypto * crypto();


      virtual ::file::path local_get_matter_cache_path();
      virtual ::file::path local_get_matter_cache_path(string strMatter);
      virtual ::file::path local_get_matter_path();
      virtual ::file::path local_get_matter_path(string strMatter);


      virtual void install_progress_add_up(int iAddUp = 1);




      virtual string get_system_platform();
      virtual string get_system_configuration();



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
      
      void on_open_file(const ::string & pszFile) override;


      virtual void on_os_text(enum_os_text etext, string strText);



      virtual void on_extra(string str);

      virtual string standalone_setting(string str);
      virtual void set_standalone_setting(string str, string strSetting);


      virtual void process_machine_event_data(machine_event_data * pdata);

      virtual string get_user_language();
      virtual void set_user_language(::apex::application * papp, index iSel);
      virtual void set_user_language(::apex::application * papp, string strLang);

      void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);


      void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      void     firefox(string strUrl, string strBrowser, string strProfile, string strParam);




      virtual void discard_to_factory(::pointer<object>pca);



      DECLARE_MESSAGE_HANDLER(on_application_signal);


      void set_history(::apex::history* phistory);




      ::apex::history& hist();



      bool sync_load_url(string& str, const ::string & pszUrl,  ::http::cookies* pcookies = nullptr);





#ifdef _UWP

      virtual bool get_window_rect(RECTANGLE_I32* prectangle);


#endif







      virtual string get_host_location_url();

      virtual bool is_thread() const override;



      // void assert_ok() const override;
      //void dump(dump_context& action_context) const override;


      void     main() override;


      virtual bool do_events() override;


      void post_quit_to_all_threads();
      void post_to_all_threads(const ::atom& atom, wparam wparam, lparam lparam);


      void dump_command_line_and_environment_variables_to_file();

      void system_id_update(::i64 iUpdate, ::i64 iPayload) override;

      void add_handler(::matter * pmatter, bool bPriority = false) override;

      void add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal) override;

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      bool _handle_uri(const ::string & str) override;

      virtual void application_main(int argc, char *argv[], const ::string & pszCommandLine);

      virtual int console_end(::e_status estatus);


      virtual void get_public_internet_domain_extension_list(string_array& stra) override;

      
   };


   //CLASS_DECL_APEX ::pointer< ::mutex > get_image_mutex();

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

