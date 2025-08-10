#pragma once


//#include "apex/platform/session.h"
//#include "apex/platform/context.h"
//#include "acme/constant/os_text.h"
#include "acme/platform/system.h"
#include "apex/parallelization/thread.h"


namespace apex
{


   class CLASS_DECL_APEX system :
      virtual public ::platform::system,
      virtual public ::thread
      //virtual public ::platform::context
   {
   public:


      //
      //
      // #ifndef WINDOWS
      //
      //
      //       ::pointer<::exception_translator>                 m_pexceptiontranslator;
      //
      //
      // #endif
      //
      //       ::pointer < ::file::watcher >                      m_pfilewatcher;
      //       //::pointer<::dump_context>                       m_pdumpcontext;
      //
      //       ::pointer<::networking::networking>             m_pnetworking;
      //
      //       //::pointer<::crypto::crypto>                     m_pcrypto;
      //
      //       ::pointer<class machine_event_central>           m_pmachinehappeningcentral;
      //
      //       ::pointer < ::mutex >                                m_pmutexUserAppData;
      //       ::pointer < ::mutex >                                m_pmutexSystemAppData;
      //
      //       ::pointer<::operating_system::department>       m_poperatingsystem;
      //
      //       ::pointer<::parallelization::threading>         m_pthreading;
      //       size_t                                             m_nSafetyPoolSize; // ideal int_size
      //
      //
      //       ::pointer < ::input::input >                       m_pinput;
      //
      //       string_array_base                                       m_straCommandLineAccumul;
      //       string_array_base                                       m_straCommandLineExtra;
      //       class ::time                                         m_timeCommandLineLast;
      //       int                                                m_iCommandLineDelay;
      //
      //       bool                                               m_bSystemSynchronizedCursor;
      //       bool                                               m_bSystemSynchronizedScreen;
      //
      //
      //       ::pointer < ::manager_room >           m_pmanagerroom;
      //
      //       ::pointer<class ::apex::history>                m_phistory;
      //

      system();


      ~system() override;


      //void on_set_platform() override;


      void common_construct();


#ifdef _DEBUG


      long long increment_reference_count() override;


      long long decrement_reference_count() override;


#endif


      void on_initialize_particle() override;


      void install_message_routing(::channel* pchannel) override;


      void system_construct(::platform::application* papplication) override;


      //virtual void _compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation) override;
      //virtual void _uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation, transfer_progress_function transferprogressfunction = {}) override;

      void defer_innate_ui() override;


      //#ifdef WINDOWS_DESKTOP
      //
      //#elif defined(UNIVERSAL_WINDOWS)
      //
      //      void system_construct(const ::string_array_base & stra);
      //
      //#else
      //
      //      void system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display& edisplay = ::e_display_none);
      //
      //#endif

      void do_operating_ambient_factory() override;


      //virtual void __task_init() override;


      ::string component_path(const ::scoped_string& scopedstrComponent) override;


      class ::manager_room* manager_room() override;


      virtual ::platform::application* get_main_app() override;


      virtual void init() override;


      void inline_init() override;


      void inline_term() override;


      //void init_system() override;
      void term_system() override;


      virtual void on_system_construct();


      void on_start_system() override;


      void system_main() override;


      virtual void term() override;


      //DECLARE_MESSAGE_HANDLER(on_message_erase_session);

      string get_application_server_name() override;


      bool task_get_run() const override;


      [[nodiscard]] class ::handler::signal* signal(const ::atom& atom) override;


      //void create_os_node() override;

      //::apex::node * node();


      ::file::watcher* file_watcher() const override;


      virtual ::input::input* input() override;


      virtual ::factory::factory* node_factory() override;


      virtual void process_init() override;


      virtual void init1() override;


      virtual void init2() override;


      //void defer_post_initial_request() override;

      //void post_request(::request* prequest);

      //virtual void initialize_context() override;


      virtual ::pointer<::data::node> load_xml(const ::scoped_string& scopedstrXml) override;


      //virtual void verb() override; // ambigous inheritance from ::apex::system/::axis::application


      //virtual bool is_system() const override;


      void initialize_crypto() override;


      virtual string crypto_md5_text(const ::scoped_string& scopedstr) override;


      void on_request(::request* prequest) override;


      void destroy() override;


      virtual void process_exit_status(::object* pparticle, const ::e_status& estatus) override;


      virtual void hist_hist(const ::scoped_string& scopedstr) override;


      //virtual string ::url::encode(const ::scoped_string & scopedstr);


      //virtual void locale_schema_matter(string_array_base & stra, const string_array_base & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      //virtual string get_locale_schema_dir() override;

      ::operating_system::department* operating_system() override;


      class ::machine_event_central* machine_event_central() override;


      ::parallelization::threading* threading() override;


      virtual ::networking::networking* networking() override;


      virtual void on_allocation_error(const ::scoped_string& scopedstrName, ::object* pobjectSometimes) override;


      template<typename T>
      inline T* cast_clone(T* p)
      {

         return ::clone(p);

      }


      virtual void open_internet_link_in_browser(const ::scoped_string& scopedstrUrl,
                                                 const ::scoped_string& scopedstrBrowser,
                                                 const ::scoped_string& scopedstrProfile,
                                                 const ::scoped_string& scopedstrTarget) override;


      virtual void open_internet_link(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrProfile,
                                      const ::scoped_string& scopedstrTarget) override;


      //virtual void __set_thread_on() override;

      //virtual string get_local_mutex_name(const ::scoped_string & scopedstrAppName);
      //virtual string get_local_id_mutex_name(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrId);
      //virtual string get_global_mutex_name(const ::scoped_string & scopedstrAppName);
      //virtual string get_global_id_mutex_name(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrId);


      virtual void initialize_networking() override;


      virtual bool on_get_task_name(string& strTaskName) override;


      unsigned int os_post_to_all_threads(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {}) override;


      //virtual void init_task() override;
      //virtual void term_task() override;


      //virtual void thread_loop() override;


      //virtual void post_pending_requests();


      virtual void term2() override;


      virtual void term1() override;


      virtual void TermSystem() override;


      virtual void process_term() override;


      virtual int _001OnDebugReport(int i1, const ::scoped_string& scopedstr1, int i2,
                                    const ::scoped_string& scopedstr2, const ::scoped_string& scopedstr3,
                                    va_list args) override;


      virtual int _debug_logging_report(int iReportType, const ::scoped_string& scopedstrFilename, int iLinenumber,
                                        const ::scoped_string& scopedstrModuleName, const_char_pointer pszFormat,
                                        va_list list) override;


      virtual bool assert_failed_line(const ::scoped_string& scopedstrFileName, int iLine) override;


      virtual bool on_assert_failed_line(const ::scoped_string& scopedstrFileName, int iLine) override;


      virtual void initialize_log(const ::scoped_string& scopedstrId) override;


      virtual void appa_load_string_table() override;


      virtual void appa_set_locale(const ::scoped_string& scopedstrLocale,
                                   const ::action_context& action_context) override;


      virtual void
      appa_set_schema(const ::scoped_string& scopedstrStyle, const ::action_context& action_context) override;


      virtual bool assert_running_global(const ::scoped_string& scopedstrAppName,
                                         const ::scoped_string& scopedstrId = nullptr) override;


      virtual bool assert_running_local(const ::scoped_string& scopedstrAppName,
                                        const ::scoped_string& scopedstrId = nullptr) override;


      virtual ::collection::count get_application_count() override;


      void install_progress_add_up(int iAddUp = 1) override;


      virtual void on_start_find_applications_from_cache() override;


      //virtual void on_end_find_applications_from_cache(stream & is);

      //virtual void on_end_find_applications_to_cache(stream & os);

      virtual void on_map_application_library(::acme::library& library) override;


      //void request(::request * prequest) override;


      //#ifdef __ANDROID__
      ////#pragma message("at macos??")
      //      virtual bool android_set_user_wallpaper(const ::scoped_string & scopedstrUrl);
      //      virtual bool android_get_user_wallpaper(string & strUrl);
      //
      //#endif

      virtual bool defer_accumulate_on_open_file(string_array_base stra, const ::scoped_string & scopedstrExtra) override;


      //virtual bool merge_accumulated_on_open_file(::request * prequest);

      virtual bool on_open_file(::payload payloadFile, const ::scoped_string & scopedstrExtra) override;


      void on_open_file(const ::scoped_string& scopedstrFile) override;


      virtual void on_os_text(enum_os_text etext, const ::scoped_string & scopedstrText) override;


      virtual void on_extra(const ::scoped_string & scopedstr) override;


      virtual string standalone_setting(const ::scoped_string & scopedstr) override;


      virtual void set_standalone_setting(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSetting) override;


      virtual void process_machine_event_data(machine_event_data* pdata) override;


      virtual string get_user_language() override;


      virtual void set_user_language(::apex::application* papp, ::collection::index iSel) override;


      virtual void set_user_language(::apex::application* papp, const ::scoped_string & scopedstrLang) override;


      void chromium(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrId, ::file::path path, const ::scoped_string & scopedstrProfile,
                    const ::scoped_string & scopedstrParam) override;


      void defer_create_firefox_profile(::file::path pathFirefox, const ::scoped_string & scopedstrProfileName,
                                        ::file::path pathProfile) override;


      void firefox(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrParam) override;


      virtual void discard_to_factory(::pointer<object> pca) override;


      //DECLARE_MESSAGE_HANDLER(on_application_signal);


      void set_history(::apex::history* phistory) override;


      ::apex::history* hist() override;


      bool sync_load_url(string& str, const ::scoped_string& scopedstrUrl,
                         ::http::cookies* pcookies = nullptr) override;


      //
      //
      //
      //
      //#ifdef UNIVERSAL_WINDOWS
      //
      //      virtual bool window_rectangle(::int_rectangle* prectangle);
      //
      //
      //#endif
      //


      string get_host_location_url() override;


      bool is_thread_class() const override;


      // void assert_ok() const override;
      //void dump(dump_context& action_context) const override;

      void main() override;


      //bool do_tasks() override;


      void post_quit_to_all_threads() override;


      void post_to_all_threads(::enum_message emessage, ::wparam wparam, ::lparam lparam) override;


      void dump_command_line_and_environment_variables_to_file() override;


      //void system_id_update(long long iUpdate, long long iPayload) override;

      //void add_handler(::particle * pmatter, bool bPriority = false) override;

      //void add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal) override;

      //void erase_signal_handler(::signal_handler::base * pbase) override;

      //void erase_signal_handlers(::particle * pparticle) override;

      void route_command(::message::command* pcommand, bool bRouteToKeyDescendant) override;


      void handle(::topic* ptopic, ::handler_context* phandlercontext) override;


      bool _handle_uri(const ::scoped_string& scopedstr) override;


      using ::platform::system::application_main;


      virtual void application_main(int argc, char* argv[], const ::scoped_string& scopedstrCommandLine) override;


      virtual int console_end(::e_status estatus) override;


      //virtual void get_public_internet_domain_extension_list(string_array_base& stra) override;


      ::string fetch_public_internet_domain_extension_list_text() override;


      void on_application_dark_mode_change() override;


   };


   //CLASS_DECL_APEX ::pointer< ::mutex > get_image_mutex();

} // namespace apex


//#ifndef _DEBUG
//
//#include "apex/inline/factory_item.cpp"
//
//#endif // __DEBUG


//CLASS_DECL_APEX ::apex::system * create_apex_system(app_core * pappcore);
CLASS_DECL_APEX ::apex::system* create_apex_system();


//#define STRINGIFY(x) #x
//#define TOSTRING(x) STRINGIFY(x)
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


// void CLASS_DECL_APEX __start_core_system_main(::berg::system * psystem);

//#ifdef UNIVERSAL_WINDOWS
//
//CLASS_DECL_APEX int app_core_main(const ::scoped_string & scopedstr);
//
//#endif
