
// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/handler/handler.h"
#include "system_acme.h"
#include "system_apex.h"
#include "system_aqua.h"
#include "system_aura.h"
#include "system_axis.h"
#include "system_core.h"


namespace platform
{

   /// For GUI applications:
   /// Never let system and other "system" threads (like session, application)
   /// be the main thread object.
   /// Maybe better thought, always make acme_windowing the main thread object
   /// at a GUI application.
   ///
   /// For console applications:
   /// Abandon idea of doing GUI interaction. This implies never creating
   /// windowing component at console applications. GUI interaction
   /// requires at least one GUI thread which is a heavy overhead
   /// for a console application. This implies that even system
   /// provided ways of doing GUI interaction, like MessageBox
   /// at Windows, should be avoided as it can trigger a GUI
   /// interaction requirement for other operating systems.
   class CLASS_DECL_ACME system :
      virtual public ::platform::platform,
      virtual public ::handler::handler,
      virtual public ::platform::acme_system_layer_t,
      virtual public ::platform::apex_system_layer_t,
      virtual public ::platform::aqua_system_layer_t,
      virtual public ::platform::aura_system_layer_t,
      virtual public ::platform::axis_system_layer_t,
      virtual public ::platform::core_system_layer_t,
      virtual public ::platform::acme_system_layer,
      virtual public ::platform::apex_system_layer,
      virtual public ::platform::aqua_system_layer,
      virtual public ::platform::aura_system_layer,
      virtual public ::platform::axis_system_layer,
      virtual public ::platform::core_system_layer,
      virtual public ::task
   {
   public:


      static ::platform::system *            s_p;
      //::pointer < ::platform::system  >      m_psystemComposite;





      system();
      ~system() override;

      virtual ::particle * matter_mutex() override;
      virtual ::particle * http_download_mutex() override;

      virtual ::string_array * http_download_array() override;
      virtual ::string_array * http_exists_array() override;

      virtual class ::time * file_listing_cache_time() override;

      //void on_set_platform() override;


      ::task_message_queue * task_message_queue() override;


      ::thread_storage * thread_storage(const class ::task_index & taskindex) override;
      ::thread_storage * _thread_storage_unlocked(const class ::task_index & taskindex) override;


      void on_initialize_particle() override;


      virtual void process_machine_event_data(machine_event_data * pdata) override;

      void do_operating_ambient_factory() override;

      void do_graphics_and_windowing_factory() override;

      virtual void application_main(::platform::application * papplication);

      virtual void initialize_layer();

      virtual enum_trace_level get_trace_level() override;
      //void os_construct();

      virtual void initialize_matter() override;
      

#ifdef _DEBUG


      long long increment_reference_count() override;


      long long decrement_reference_count() override;


#endif


      virtual void create_task_message_queue();
      virtual void destroy_task_message_queue();


      ::task* get_task(const class ::task_index & taskindex);
      //itask get_task_id(const ::task* ptask);
      //void set_task(const class ::task_index & taskindex, ::task* ptask);
      //void unset_task(const class ::task_index & taskindex, ::task* ptask);
      void set_task(::task* ptask);
      void unset_task(::task* ptask);

      virtual bool is_task_set(const class ::task_index & taskindex);
      //virtual bool is_active(::task * ptask);
      //virtual void set_task_on(const class ::task_index & taskindex);
      //virtual void set_task_off(const class ::task_index & taskindex);


      virtual ::mathematics::mathematics * mathematics() override;

      virtual ::image::imaging * imaging() override;

      // #if defined(WITH_X11) || defined(WITH_XCB)
      //       virtual ::particle * x11_synchronization();
      // #endif

      virtual ::networking::networking * networking() override;

      virtual ::platform::node * node() override;

      virtual class ::base64 * base64() override;

      virtual ::xml::xml * xml() override;

      virtual ::file::watcher * file_watcher() const override;

      virtual ::file_system * file_system() const;

      virtual ::directory_system * directory_system() const;

      virtual ::path_system * path_system() const;

      ::platform::system_factory * system_factory() override;

      ::xml::xml * _xml() override;

      ::geometry::geometry * geometry() override;

      ::datetime::datetime * datetime() override;

      ::text::table * texttable() override;

      ::internet::internet * internet() override;
      ::url::url_context * url() override;

      ::particle * ui_destroyed_synchronization() override;

      ::nano::nano * nano() override;

      ::micro::user * micro_user() override;
      ::acme::windowing::windowing * acme_windowing() override;
      ::windowing::windowing * windowing() override;

      ::component * component(const ::scoped_string & scopedstrComponent)override;

      ::string component_path(const ::scoped_string & scopedstrComponent) override;

      void defer_innate_ui() override;

      ::innate_ui::innate_ui * innate_ui() override;

      //virtual nano::nano * nano()

      class ::manager_room * manager_room() override;

      ::crypto::crypto * crypto() override;

     //virtual ::acme::acme * acme() const ;

     virtual::prototype::prototype * prototype() override;

      virtual ::draw2d::draw2d * draw2d() override;
      virtual ::write_text::write_text * write_text() override;

      //virtual ::windowing::windowing_base * windowing_base();

      //virtual ::http_system * http_system();

      virtual string get_system_platform() override;
      virtual string get_system_configuration() override;





      virtual void defer_audio() override;

      virtual bool has_audio() override;

      virtual void init1() override;

      virtual void init2() override;

      //void set_current_handles() override;

      virtual void TermSystem() override;


      virtual void erase_from_any_hook(::matter * pmatter) override;


      virtual void create_os_node(::platform::application * papplication) override;

      virtual string os_get_user_theme() override;


      template < typename BASE_TYPE >
      ::pointer<BASE_TYPE> create(const ::string & strComponent, const ::string & strImplementation)
      {

#if REFERENCING_DEBUGGING

         auto preferer = ::allocator::pop_referer();

#endif

         auto & pfactory = this->factory(strComponent, strImplementation);

         if (!pfactory)
         {

            throw ::exception(error_resource);

         }

#if REFERENCING_DEBUGGING

         ::allocator::_push_referer(preferer);

#endif

         auto p = pfactory->__call__create< BASE_TYPE >(this);

         if (!p)
         {

            return p;

         }

         return p;

      }


      virtual unsigned int crc32(unsigned int uCrc, const ::block & block) override;


      virtual void create_session(::collection::index iEdge = 0) override;

      virtual ::pointer<::platform::session>on_create_session(::collection::index iEdge) override;

      virtual ::platform::session * session(::collection::index iEdge = 0) override;


      virtual void add_session(::collection::index iEdge, ::platform::session * psession) override;
      virtual void on_add_session(::platform::session * psession) override;
      virtual void erase_session(::collection::index iEdge) override;


      void on_request(::request * prequest) override;


      void process_exit_status(::particle * pparticle, const ::e_status & estatus);


      virtual ::platform::application * get_main_app() override;


      virtual ::factory::factory * folder_factory() override;


      //using main::system_construct;


      virtual void system_construct(::platform::application * pacmeapplicationStartup) override;

#ifdef WINDOWS_DESKTOP

      void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, int nCmdShow);

#elif defined(UNIVERSAL_WINDOWS)

      void system_construct(const ::string_array & stra);

      //#else

         //void system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif

      virtual void speak(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrLang = "en-us", enum_gender egender = e_gender_none) override;


      virtual ::factory::factory * node_factory() override;


      virtual void inline_init() override;
      virtual void inline_term() override;


      virtual void process_init() override;


      ///virtual void call_init_system() override;


      virtual void init_system() override;
      virtual void term_system() override;


       //virtual void on_start_system() override;


      virtual void defer_post_initial_request() override;


      virtual void canonical_system_main() override;

      virtual void system_main() override;


      //void on_pre_run_task() override;


      virtual void on_branch_system_from_main_thread_startup(::task_handler * ptaskhandler) override;


      void main() override;


      virtual ::pointer<::platform::application> new_app(const ::scoped_string & scopedstrAppId) override;


      virtual void end() override;


      virtual void on_end() override;


      virtual void report_system_instance() override;

      //using ::manager::on_subject;
      //virtual void on_subject(::topic * ptopic) override;

      virtual class ::time get_update_poll_time(const ::atom & atom) override;


      virtual ::acme::library * on_get_library(const ::string & pszLibrary) override;




      //virtual ::pointer<::acme::library> & library(const ::string &strComponent, const ::string &strImplementation);


      virtual void open_profile_link(string strUrl, string strProfile, string strTarget) override;
      virtual void open_link(string strUrl, string strProfile, string strTarget) override;
      virtual void open_url(string strUrl, string strProfile, string strTarget) override;


      bool _handle_uri(const ::block & block) override;


      //void __tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const override;


      //virtual void main_user_async(const ::procedure & procedure, ::enum_priority epriority = e_priority_normal);

      //virtual void main_user_sync(const ::procedure & procedure, const class time & time = one_minute(), enum_priority epriority = e_priority_normal);


      void init_task() override;
      void term_task() override;


      string __get_text(const string & str) override;

#ifdef LINUX

      //!!!      virtual void deferx_initializex_x11();

#endif


   //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;


   //virtual void on_initialize_window_object();
   //virtual void _on_initialize_window_object();

//
//   template < typename ENUM >
//   inline void set_enum_text(ENUM e, const ::string &psz)
//   {
//
//      critical_section_lock synchronouslock(&m_csEnumText);
//
//      m_mapEnumToText[typeid(e).name()][(long long)e] = psz;
//
//      m_mapTextToEnum[typeid(e).name()][psz] = (long long)e;
//
//   }

//
//   template < typename ENUM >
//   inline string enum_text(ENUM e)
//   {
//
//      critical_section_lock synchronouslock(&m_csEnumText);
//
//      return m_mapEnumToText[typeid(e).name()][(long long)e];
//
//   }

//
//   template < class ENUM >
//   inline ENUM text_enum(ENUM& e, const ::string &psz, ENUM eDefault = (ENUM)0)
//   {
//
//      critical_section_lock lock(&m_csEnumText);
//
//      long long iValue;
//
//      if (m_mapTextToEnum[typeid(e).name()].lookup(psz, iValue))
//      {
//
//         e = (ENUM)iValue;
//
//      }
//      else
//      {
//
//         e = eDefault;
//
//      }
//
//      return e;
//
//   }
//
//
//   template < class ENUM, ENUM edefault = 0>
//   inline base_enum < ENUM, edefault >& text_enum(base_enum < ENUM, edefault >& b, const ::string &psz, ENUM eDefault = edefault)
//   {
//
//      return b = text_enum(b.m_evalue, psz, eDefault);
//
//   }

//
//   template < class ENUM, ENUM edefault = 0>
//   inline string enum_text(const base_enum < ENUM, edefault >& b)
//   {
//
//      return enum_text(b.m_evalue, (long long)(ENUM)b);
//
//   }


      ::task_group * task_group(::enum_priority epriority = ::e_priority_none);

      ::task_tool * task_tool(::enum_task_tool etool);



      static inline ::atom atom(const ::std::type_info & info);
      static inline ::atom atom(const ::scoped_string & scopedstr);
      static inline ::atom atom(const string & str);
      static inline ::atom atom(long long i);
      //static inline ::atom_space & atom();
      inline ::atom atom(const ::payload & payload);
      inline ::atom atom(const property & prop);

      virtual void check_exit() override;

      virtual ::regular_expression_pointer create_regular_expression(const ::string & pszStyle, const string & str) override;
      //virtual ::pointer<::regular_expression::context> create_regular_expression_context(const ::string &pszStyle, int iCount);
      virtual ::pointer<::regular_expression::context> get_regular_expression_context(const ::string & pszStyle) override;

      virtual ::regular_expression_pointer compile_pcre(const string & str) override;
      virtual ::pointer<::regular_expression::context> get_pcre_context() override;
      //virtual int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)

      virtual void get_public_internet_domain_extension_list(string_array & stra) override;
      virtual ::string fetch_public_internet_domain_extension_list_text() override;

      void system_id_update(int iUpdate, long long iPayload) override;

      void handle(::topic * ptopic, ::context * pcontext) override;
      
      void call_message(const ::enum_message & emessage, ::wparam wparam, ::lparam lparam, ::particle* pparticle) override;
    

      //virtual void add_handler(::particle * pmatter, bool bPriority = false);

      //virtual void add_signal_handler(const ::signal_handler & signalhandler, const ::atom & atomSignal) override;

      //virtual void erase_signal_handler(::signal_handler::base * pbase) override;

      //virtual void erase_signal_handlers(::particle * ppparticle);

      virtual void node_will_finish_launching() override;

      virtual void on_open_untitled_file() override;

      virtual void on_open_file(const ::string & pszFile) override;

      //template < typename BASE_TYPE >
      //::pointer<BASE_TYPE> create(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
      //{

      //   auto plibrary = ([a-z0-9_]+)_factory(pszComponent, pszImplementation);

      //   if (!plibrary)
      //   {

      //      return error_not_found;

      //   }

      //   auto p = plibrary->create<BASE_TYPE>();

      //   if (!p)
      //   {

      //      return error_not_found;

      //   }

      //   return p;

      //}


      ::pointer < ::compress>    _new_compress(const ::scoped_string & scopedstrImplementation);
      ::pointer < ::uncompress>  _new_uncompress(const ::scoped_string & scopedstrImplementation);

      ::pointer < ::compress>    new_zlib_compress();
      ::pointer < ::uncompress>  new_zlib_uncompress();

      virtual void _compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation) override;
      virtual void _uncompress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation, transfer_progress_function transferprogressfunction = {}) override;

      virtual void zlib_compress(const ::payload & payloadTarget, const ::payload & payloadSource) override;
      virtual void zlib_uncompress(const ::payload & payloadTarget, const ::payload & payloadSource, transfer_progress_function transferprogressfunction = {}) override;

      virtual bool fast_is_decompressable_folder(const ::file::path & path) override;

      //virtual void windowing_send(const ::procedure & procedure);
      //virtual void windowing_post(const ::procedure & procedure);


      void _post(const ::procedure & procedure) override;


      bool _handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;


      //virtual void windowing_post_quit();

      virtual string get_latest_deployment_number(const ::string & strBranch) override;


      void destroy() override;





      //CLASS_DECL_ACME ::acme::library * lib(const ::scoped_string & scopedstr);



      //::file::path library_file_name(const ::string& str);


      //template < typename ENTRY >
      //ENTRY* library_call(const ::scoped_string & scopedstrLibrary, const ::scoped_string & scopedstrEntry)
      //{

      //   return lib(pszLibrary)->get<decltype(&ENTRY)>(pszEntry));

      //}

//#define LIBCALL(library, entry)  (system()->lib(#library)->get<decltype(&entry)>(#entry))


      virtual ::string implementation_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation) override;
      virtual ::string library_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation) override;


      //class ::crypto::crypto * crypto();


      virtual ::file::path local_get_matter_cache_path() override;
      virtual ::file::path local_get_matter_cache_path(string strMatter) override;
      virtual ::file::path local_get_matter_path() override;
      virtual ::file::path local_get_matter_path(string strMatter) override;

      virtual void install_progress_add_up(int iAddUp = 1) override;


      virtual ::string get_application_server_name() override;


      virtual ::color::color background_color() const override;

      virtual double luminance() const override;

      virtual void set_background_color(const ::color::color & color) override;


      virtual bool dark_mode() const override;
      virtual class ::time dark_mode_time() const override;
      virtual void set_dark_mode_time(const class ::time & time) override;
      virtual void on_application_dark_mode_change() override;

      //      virtual int get_simple_ui_darkness();

      //      virtual void set_simple_ui_darkness(int iWeatherDarkness);

      virtual void set_dark_mode(bool bDark) override;

      virtual ::color::color get_simple_ui_color(::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) override;

      virtual ::color::color get_default_color(::color::color color) override;


      // #if defined(WITH_X11)
      //       virtual void x11_sync(const ::procedure & procedure);
      //       virtual void x11_async(const ::procedure & procedure);
      // #endif

      virtual bool defer_component_factory(const ::scoped_string & scopedstrComponent) override;
      virtual bool _defer_component_factory(const ::scoped_string & scopedstrComponent) override;

      //::pointer < ::message_box > & realize(::pointer < ::message_box > & pmessagebox);

      //::pointer < ::message_box > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

      //::pointer < ::message_box > exception_message_box(const ::exception & exception, const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

      //::pointer < ::message_box > message_console(const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

      //::pointer < ::message_box > exception_message_console(const ::exception & exception, const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);



//       // ::aura::system
//
//
//       void common_construct();
//
//       //void on_set_platform() override;
//
//       //void on_initialize_particle() override;
//
//       ///void on_add_session(::platform::session * papexsession) override;
//
//       virtual void init();
//       //virtual void init_instance() override;
//       //virtual void term_instance() override;
//       //void inline_init() override;
//       //void inline_term() override;
//
//       //void TermSystem() override;
//
//       virtual void on_finish_launching();
//
//
//       //#ifdef LINUX
//       //
//       //      virtual void os_application_system_run() override;
//       //
//       //#endif
//
//
//       //      virtual void init_system() override;
//       //      virtual void term_system() override;
//
//
//       //virtual void system_main() override;
//
//       virtual void term();
//
//       //virtual void system_prep() override;
//
//       //::url::url                           & url()     { return m_urldepartment; }
//
//       //::thread * get_task(itask itask);
//       //itask get_thread_id(::thread * pthread);
//       //void set_thread(itask itask, ::thread * pthread);
//       //void unset_thread(itask itask, ::thread * pthread);
//
//       virtual ::aura::estamira * estamira();
//
//       virtual ::hardware::devices * hardware_devices();
//
//       virtual void defer_initialize_hardware_devices();
//
//
//
//       ::aura::session * get_session();
//       //::aura::node * node();
//
//       virtual ::gpu::approach * get_gpu();
//       virtual  ::gpu::approach * gpu();
//       virtual void create_gpu();
//
//
//       //virtual string install_get_platform() override;
//       //virtual void install_set_platform(const ::string & pszPlatform) override;
//       //virtual string install_get_version() override;
//       //virtual void install_set_version(const ::string & pszVersion) override;
//       //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
//       //virtual int install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
//       //virtual int install_progress_app_add_up(int iAddUp = 1) override;
//
//       //virtual ::install::canvas * install_create_canvas();
//       //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
//       //virtual int install_canvas_increment_mode();
//
//       //virtual string install_get_platform() override;
//       //virtual void install_set_platform(const ::string & pszPlatform) override;
//       //virtual string install_get_version() override;
//       //virtual void install_set_version(const ::string & pszVersion) override;
//       //virtual string install_get_latest_build_number(const ::string & pszVersion) override;
//       //virtual int install_start(const ::string & pszCommandLine, const ::string & pszBuild) override;
//       //virtual int install_progress_app_add_up(int iAddUp = 1) override;
//
//       //virtual ::pointer<::factory::factory> & node_factory() override;
//
//       //virtual void process_init() override;
//
//       //virtual void init1() override;
//
//       //virtual void init2() override;
//
//       //virtual void initialize_system();
//
//       //virtual void defer_xml();
//
//
//       //void node_will_finish_launching() override;
//
//
//       //void windowing_post_quit() override;
//
//
//       virtual ::pointer<::data::node>load_xml(const ::string & pszXml);
//
//       virtual void verb(); // ambigous inheritance from ::aura::system/::axis::application
//
//
//       //virtual bool is_system() const override;
//
//
//       virtual string crypto_md5_text(const ::string & str);
//
//
//       //virtual pointer< ::extended::future < ::conversation > > _message_box(oswindow oswindow, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;
//       //virtual ::enum_dialog_result message_box_timeout(const ::string & pszMessage, const ::string & pszTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future()) override;
//
//
//       //virtual void create_html();
//
//       //virtual ::pointer<::aura::session>on_create_session() override;
//
//       //virtual void on_request(::request * prequest) override;
//
//       //virtual void construct(const ::string & pszAppId);
//
//       //virtual bool initialize_application() override;
//
//       //virtual int exit_instance();
//       //virtual bool destroy();
//
//       //virtual void destroy() override;
//
//
//
//
//       //virtual bool verb();
//
//       //virtual void main_user_async(const ::procedure & procedure, ::enum_priority epriority = e_priority_normal) override;
//
//
//       //virtual bool process_initialize();
//
//       //virtual bool process_init();
//
//       //virtual bool init1();
//
//       //virtual bool init2();
//
//       //virtual bool is_system();
//
//
//
//       //virtual ::aura::session * query_session(::collection::index iEdge) override;
//
//
//
//
//       //virtual string dir_appmatter_locator(::particle * pparticle);
//
//
//       //virtual void hist_hist(const ::string & psz);
//
//
//       //virtual void on_request(::request * prequest) override;
//
//
//       //virtual unsigned int crc32(unsigned int dwPrevious, const ::string & psz);
//
//
//       //virtual string ::url::encode(const ::string & str) override;
//
//
//       //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
//       //virtual string get_locale_schema_dir() override;
//
//
//       //virtual void     initialize_system(::particle * pparticle, app_core * pappcore);
//
//
//       //::pointer<::thread_tools>create_thread_tools(::enum_task_tool etool);
//       //thread_tools * tools(::enum_priority epriority);
//       //thread_toolset * toolset(e_tool etool);
//
//       //class ::user::window_map                     &  window_map();
//
//
//       //::pointer<::acme::library>open_component_library(const ::string & pszComponent, const ::string & pszImplementation);
//
//       //void ([a-z0-9_]+)_factory(const ::string & pszComponent, const ::string & pszImplementation);
//
//       //void ([a-z0-9_]+)_factory(const ::string & pszComponent, const ::string & pszImplementation, PFN_factory pfnFactoryExchange);
//
//
//       //class ::aura::os                             &  os();
//       //class base_factory                           &  factory_item();
//
//
//       //::aura::str                                  &  str();
//       //::operating_system::department                        &  process();
//
//
//       //::xml::department                            &  xml();
//       //class ::base64                          &  base64();
//       //class ::aura::log                            &  log();
//       //class ::machine_event_central                &  machine_event_central();
//       //inline ::parallelization::threading           *  threading() { return m_pthreading; }
//
//       //geometry::geometry                           &  geometry()
//       //{
//
//       //   return *m_pgeometry;
//
//       //}
//       //inline  class imaging & imaging() { return *m_pimaging; }
//
//       //virtual ::sockets::sockets & sockets() { return *m_psockets; }
//
//       //math::math                                   &  math()
//       //{
//
//       //   return *m_pmath;
//
//       //}
//
//
//       //class ::draw2d::draw2d * draw2d() const override;
//
//       //class ::write_text::write_text * write_text() const override;
//
//
//       //class ::image::imaging * imaging() override;
//
//
//       //inline ::url::url                     &  url()
//       //{
//
//       //   return *m_purldepartment;   // only usable from base.dll and dependants
//
//       //}
//
//
//       //inline class ::compress_department           &  compress()
//       //{
//
//       //   return *m_pcompress;   // only usable from base.dll and dependants
//
//       //}
//
//
//
//
//       //inline ::file::system_dir & dir() { return *m_spdir; }
//       //inline ::file::system_file & file() { return *m_spfile; }
//
//
//       //::net::email_department                & email();
//
//       //::pointer<::account::user_set>               userset();
//
//       //::datetime::datetime                 & datetime();
//
//
//       //virtual string ::url::encode(const ::string & str);
//
//       virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes);
//
//       //::pointer< ::mutex > get_openweather_city_mutex();
//
//
//       template < typename T >
//       inline T * cast_clone(T * p)
//       {
//
//          return ::clone(p);
//
//       }
//
//
//       //virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget) override;
//       //virtual void open_profile_link(string strUrl, string strProfile, string strTarget) override;
//       //virtual void open_link(string strUrl, string strProfile, string strTarget) override;
//       //virtual void open_url(string strUrl, string strProfile, string strTarget) override;
//
//
//       //virtual void __set_thread_on() override;
//
//       //virtual string get_local_mutex_name(const ::string & pszAppName) override;
//       //virtual string get_local_id_mutex_name(const ::string & pszAppName, const ::string & pszId) override;
//       //virtual string get_global_mutex_name(const ::string & pszAppName) override;
//       //virtual string get_global_id_mutex_name(const ::string & pszAppName, const ::string & pszId) override;
//
//
//       //template < class T >
//       //::type * type_info()
//       //{
//
//       //   return get_type_info(typeid(T));
//
//       //}
//
//
//       //virtual ::type_atom * get_type_info(const ::std::type_info & info);
//
//       //::type * get_type_info(const ::atom & idType)
//       //{
//
//       //   if(idType.is_empty())
//       //      return nullptr;
//
//       //   synchronous_lock synchronouslock(m_pmutexFactory);
//
//       //   return m_typemap[idType].m_p;
//
//       //}
//
//
//       //virtual void discard_to_factory(::object * pca);
//
//       bool on_application_menu_action(const ::string & pszCommand);
//
//
//       //virtual void initialize_sockets();
//
//
//       //virtual bool on_get_thread_name(string& strThreadName) override;
//
//       //virtual ::acme::library * on_get_library(const ::string & pszLibrary) override;
//
//       //virtual ::acme::library * get_library(const ::string & pszLibrary, bool bOpenCa2 = false) override;
//
//
//       //virtual unsigned int os_post_to_all_threads(const ::atom & atom,const ::wparam & wparam = {},const ::lparam & lparam = {}) override;
//
//
//       //virtual void session_add(::collection::index iEdge, ::apex::session * psession) overr;
//       //virtual void session_erase(::collection::index iEdge);
//
//
//
//       //virtual void init_system();
//
//       //virtual void process_init();
//
//       virtual void initialize_draw2d();
//       //virtual void initialize_write_text();
//       virtual ::pointer<::factory::factory> & draw2d_factory();
//       virtual ::string draw2d_get_default_implementation_name();
//
//       virtual ::pointer<::factory::factory> & imaging_factory();
//       virtual ::string imaging_get_default_implementation_name();
//
//       //virtual void init_task() override;
//       //virtual void term_task() override;
//
//
//       virtual void thread_loop();
//
//       //virtual void init();
//
//       //virtual void init1();
//
//       //virtual void init2();
//
//       //virtual void post_creation_requests() override;
//
//       //virtual void term_system();
//
//       virtual void term2();
//
//       virtual void term1();
//
//       //virtual void term();
//
//       //virtual void TermSystem() override;
//
//
//       virtual void process_term();
//
//
//       //virtual bool is_system() const override;
//
//
//
//
//   /*    static inline ::atom atom(const ::std::type_info & info);
//       static inline ::atom atom(const ::string & psz);
//       static inline ::atom atom(const ::string & str);
//       static inline ::atom atom(long long i);
//       static inline ::atom_space & atom();
//       inline ::atom atom(const ::payload & payload);
//       inline ::atom atom(const property & prop);*/
//
//
//       //virtual int _001OnDebugReport(int i1, const ::string & psz1,int i2, const ::string & psz2, const ::string & psz3,va_list args) override;
//       //virtual int _debug_logging_report(int iReportType, const ::string & pszFilename, int iLinenumber, const ::string & iModuleName, const ::string & pszFormat, va_list list) override;
//       //virtual bool assert_failed_line(const ::string & pszFileName,int iLine) override;
//
//       //virtual bool on_assert_failed_line(const ::string & pszFileName,int iLine) override;
//
//
//
//
//
//
//       //virtual void initialize_log(const ::string & pszId) override;
//
//
//       //virtual void appa_load_string_table() override;
//       //virtual void appa_set_locale(const ::string & pszLocale, const ::action_context & action_context) override;
//       //virtual void appa_set_schema(const ::string & pszStyle, const ::action_context & action_context) override;
//
//       //virtual bool assert_running_global(const ::string & pszAppName, const ::string & pszId = nullptr) override;
//       //virtual bool assert_running_local(const ::string & pszAppName, const ::string & pszId = nullptr) override;
//
//       //::pointer<application>assert_running(const ::string & pszAppId);
//
//   /*    virtual ::collection::count get_application_count() override;
// */
//
// //virtual string crypto_md5_text(const ::string & str);
//
// //inline class ::http::system                  & http()
// //{
// //   return *m_sphttpsystem;
// //}
//
// //class ::crypto::crypto                       & crypto();
//
//
// //virtual void start() override;
//
// //virtual ::file::path local_get_matter_cache_path() override;
// //virtual ::file::path local_get_matter_cache_path(string strMatter) override;
// //virtual ::file::path local_get_matter_path() override;
// //virtual ::file::path local_get_matter_path(string strMatter) override;
//
// //virtual bool find_applications_from_cache() override;
// //virtual bool find_applications_to_cache(bool bSave = true) override;
// //virtual bool map_application_library(const ::string & pszLibrary) override;
//
//
// //virtual void install_progress_add_up(int iAddUp = 1) override;
//
// //virtual void create_session(::collection::index iEdge = 0) override;
//
// /*virtual ::pointer<::apex::session>on_create_session(::collection::index iEdge) override;
//
// virtual ::apex::session * session(::collection::index iEdge = 0) override;*/
//
// //virtual void on_request(::request * prequest) override;
//
// //::pointer<regex>create_regular_expression(const ::string & pszStyle, const string& str);
// //::pointer<regex_context>create_regular_expression_context(const ::string & pszStyle, int iCount);
// //virtual int pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount);
//
//
// //virtual string get_system_platform() override;
// //virtual string get_system_configuration() override;
// //virtual string get_latest_build_number(const ::string & pszConfiguration, const ::string & pszAppId);
//
//
//
//
// //#ifndef UNIVERSAL_WINDOWS
//
// //virtual void get_time(timeval * int_point) override;
//
// //#endif
//
//       //virtual void on_start_system() override;
//       //virtual void on_start_find_applications_from_cache() override;
//       //virtual void on_end_find_applications_from_cache(stream & is) override;
//
//       //virtual void on_end_find_applications_to_cache(stream & os) override;
//
//       //virtual void on_map_application_library(::acme::library & library) override;
//
//       //virtual void defer_check_exit();
//
//
//
//       //virtual void do_request(::request * prequest) override;
//
//       //virtual void defer_check_openweather_city_list();
//
//       //virtual openweather_city * openweather_find_city(string strQuery);
//       //virtual ::collection::index openweather_find_city2(string strQuery, string & strCit, long long & iId, double & dLat, double & dLon);
//       //virtual ::collection::index openweather_find_city2(string strQ1, string strQ2, string & strCit, long long & iId, double & dLat, double & dLon, bool bPrefix);
//
// //#ifdef ANDROID
// ////#pragma message("at macos??")
// //      virtual bool android_set_user_wallpaper(string strUrl) override;
// //      virtual bool android_get_user_wallpaper(string & strUrl) override;
// //
// //#endif
// //
// //      virtual bool defer_accumulate_on_open_file(string_array stra, string strExtra) override;
// //
// //      virtual bool merge_accumulated_on_open_file(::request * prequest) override;
// //
// //      virtual bool on_open_file(::payload payloadFile, string strExtra) override;
// //
//       //virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);
//
//       //virtual bool initialize_native_window1();
//
//       //virtual void * initialize_native_window2(const ::int_rectangle & rectangle);
//
//
//       //virtual void on_os_text(e_os_text etext, string strText) override;
//
//       //virtual ::windowing::window * impl_from_handle(void * posdata);
//       //virtual ::user::interaction * ui_from_handle(void * posdata);
//
//
//
//
//       //virtual void on_extra(string str) override;
//
//       //virtual string standalone_setting(string str) override;
//       //virtual bool set_standalone_setting(string str, string strSetting) override;
//
//
//       //virtual void on_event(unsigned long long u, ::particle * pparticle) override;
//
//
//       virtual void on_initial_frame_position(::user::frame_interaction * pframe);
//
//       virtual void on_graphics_ready();
//
//       //virtual void process_machine_event_data(machine_event_data * pdata) override;
//
//
//
//       //virtual void __tracea(enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, int iLine, const ::string & psz) const override;
//
//
//       //void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);
//
//       //void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);
//
//       //void     firefox(string strUrl, string strBrowser, string strProfile, string strParam);
//       //void     get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory);
//
//
//
//       //virtual void  initialize_system(::object* pparticle, app_core* pappcore) override;
//
//  /*     virtual void discard_to_factory(::pointer<object>pca) override;*/
//
//       //virtual bool is_system() const override;
//
//       //virtual void process_init() override;
//
//       //virtual void init2() override;
//
//       //virtual void init_system() override;
//
//       //virtual void term() override;
//
//       //virtual void term_system() override;
//
//
//       //virtual int main();
//       ///virtual void InitApplication() override;
//
//       //virtual void init() override;
//       //virtual void init1() override;
//       //virtual void init3() override;
//
//       //virtual void bergedge_start() override;
//
//
//       //virtual void initialize_rich_text();
//
//
//       //virtual ::collection::index get_new_bergedge(application_bias * pbiasCreation = nullptr);
//
//       //pointer_array < ::aura::session > &    planesessionptra();
//
//
//       //virtual bool base_support() override;
//
//
//       //DECLARE_MESSAGE_HANDLER(on_application_signal);
//
//
//       //void set_history(::apex::history* phistory);
//
//
//       //::pointer<::acme::library>on_get_library(const ::string & pszLibrary) override;
//
//
//       //virtual ::aura::session *  get_platform(::collection::index iEdge,application_bias * pbiasCreation = nullptr);
//
//
//       //virtual void on_request(::create* pcreate) override;
//
//       //      virtual ::pointer<::handler>handler();
//
//
//
//
//
//       //virtual int main();
//
//       //virtual void on_allocation_error(const ::string& str, ::object* pobjectSometimes) override;
//
//       //virtual ::pointer<::aura::session>on_create_session() override;
//
//
// //      ::aura::stra                           & stra();
//       //    ::aura::service                        & service();
//       //::aura::history& hist();
//
//       //class ::aura::patch& patch();
//
//       //::http::system                         & http();
//
//       //::filehandler::handler& filehandler();
//
//
// //#ifdef LINUX
// //
// //      virtual void deferx_initializex_x11() ;
// //      virtual bool sn_start_context();
// //
// //#endif
//
//       ////bool sync_load_url(string& str, const ::string & pszUrl, ::account::user* puser = nullptr, ::http::cookies* pcookies = nullptr);
//       //bool sync_load_url(string& str, const ::string & pszUrl,  ::http::cookies* pcookies = nullptr);
//
//
//
//       //      unsigned int guess_code_page(const ::string & str);
//
// //#ifdef UNIVERSAL_WINDOWS
// //
// //      virtual bool window_rectangle(::int_rectangle* prectangle);
// //
// //
// //#endif
//
//       //virtual void post_fork_uri(const ::string & pszUri,application_bias * pappbias);
//
//
//
// //      virtual bool wait_twf(class ::time tickTimeout = U32_INFINITE_TIMEOUT);
//
//
//
//
//
//
//
//
//       virtual string get_host_location_url();
//
//       //      virtual void add_impact_library(::acme::library* plibrary);
//
//             //virtual void get_cursor_position(::int_point * ppoint);
//
//
//
//             //virtual void do_request(::create* pcommand) override;
//
//
//       //#ifdef _DEBUG
//       //
//       //      virtual void set_context(::context* pcontext) override;
//       //      virtual void set_context_thread(::thread* pthread) override;
//       //      virtual void set_context_app(::aura::application* pappContext) override;
//       //      virtual void set_context_session(::aura::session* psessionContext) override;
//       //      virtual void set_context_system(::aura::system* psystemContext) override;
//       //
//       //#endif
//
//
//             // void assert_ok() const override;
//             //void dump(dump_context& action_context) const override;
//
//
//       //virtual void     main() override;
//       //virtual void hist_hist(const ::string & psz) override;
//
//
//       virtual ::type_atom get_pane_tab_impact_type_info();
//       virtual ::type_atom get_simple_frame_window_type_info();
//       //virtual ::type_atom get_simple_child_frame_type_info();
//
//       //virtual void on_start_find_applications_from_cache() override;
//       //virtual void on_end_find_applications_from_cache(stream& is) override;
//
//       //virtual void on_end_find_applications_to_cache(stream& os) override;
//
//       //virtual void on_map_application_library(::acme::library& library) override;
//
//       //virtual void on_graphics_ready() override;
//
//
//       //void _on_initialize_window_object() override;
//
//
//       //system();
//       //virtual ~system();
//
//
//       ///virtual void initialize_system(::object* pparticle, app_core* pappcore) override;
//
//
//       //virtual void process_init() override;
//       //virtual void term_system() override;
//
//       //virtual ::pointer<::aura::session>on_create_session() override;
//
//
//
//
//       //virtual ::install::canvas * install_create_canvas() override;
//       //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);
//       //virtual int install_canvas_increment_mode() override;
//
//
//
//       //virtual unsigned int get_monitor_color_temperature(::collection::index iMonitor);
//       //virtual bool adjust_monitor(::collection::index iMonitor, unsigned int dwTemperature, double dBrightness, double dwGamma);
//       //virtual bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle* prectangle) override;
//
//       //virtual ::collection::count get_monitor_count() override;
//
//       //bool get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle* prectangle) override;
//
//
//       //virtual ::windowing::window * impl_from_handle(void * pdata) override;
//       //virtual ::user::interaction * ui_from_handle(void * pdata) override;
//
//       //void signal(::signal * psignal) override;
//
//       //void handle(::topic * ptopic, ::context * pcontext) override;
//
//       virtual void initialize_estamira();
//
//       virtual void _001AddPacks(string_to_string & base64map, string & str);
//
//       //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;
//
//       //void windowing_send(const ::procedure & procedure) override;
//       //void windowing_post(const ::procedure & procedure) override;
//
//
//       //::string implementation_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
//
//
//       //void do_graphics_and_windowing_system_factory() override;
//
//



   };



} // namespace platform



inline ::platform::system * system()
{

   return ::platform::system::s_p;

}


