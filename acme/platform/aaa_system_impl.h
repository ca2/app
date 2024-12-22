// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "platform.h"
//#include "acme.h"
#include "context.h"
#include "system.h"
#include "application_flags.h"
#include "acme/constant/gender.h"
#include "acme/parallelization/_types.h"
#include "acme/prototype/collection/map.h"
#include "acme/prototype/prototype/factory.h"
namespace acme
{
   class system_factory;

}
namespace innate_ui
{


   class innate_ui;


} // namespace innate_ui
namespace hardware
{

   class devices;

} // namespace hardware

namespace aura
{

   class estamira;

} // namespace aura

class manager_room;


namespace acme
{


   class system_factory;


   class CLASS_DECL_ACME system :
      //virtual public ::object,
      virtual public ::platform::system
      //,
      //virtual public ::task,
      //virtual public ::plane_system
   {
   public:


//       //static ::platform::system * s_p;
//
//       //::APPLICATION_FLAGS                      m_applicationflags;
//       //::platform::platform * m_pplatform;
//
//
//       //::aqua::system* m_paquasystem;
//       //::aura::system* m_paurasystem;
//       //::axis::system* m_paxissystem;
//       //::base::system* m_pbasesystem;
//       //::bred::system* m_pbredsystem;
//       //::core::system* m_pcoresystem;
//
//
//       ::platform::session_map                               m_sessionmap;
//
//
//       bool                                            m_bFinalizeIfNoSessionSetting;
//       bool                                            m_bFinalizeIfNoSession;
//
//       ::pointer < ::mathematics::mathematics >        m_pmathematics;
//       // FROM MAIN (Now APPLICATION_FLAGS : merged on other classes?)
//
//       bool                                            m_bGraphicsAndWindowingSystemInitialized;
//
//       ::int_sz* m_pintstringLanguageResourceMap;
//       int                              m_iMatterFromHttpCache;
//
//       const char* m_pszMain;
//
//       bool                                                  m_bDarkMode;
//       ::color::color                                        m_colorBackground;
//       double                                                m_dLuminance;
//       ::pointer < ::innate_ui::innate_ui >                  m_pinnateui;
//
//       ::pointer < ::micro::user >                           m_pmicrouser;
//       ::pointer < ::acme::windowing::windowing >            m_pacmewindowing;
//       ::factory::factory_pointer                            m_pfactoryAcmeWindowing;
//
//       // END FROM MAIN (Now APPLICATION_FLAGS)
//
//       // FROM ::main (Now main2)
//
//       ::file::path                              m_pathCacheDirectory;
//       class ::time                              m_timeStart;
//       class ::time                              m_timeAfterApplicationFirstRequest;
//
//       int                                       m_iExitCode = 0;
//       enum_trace_level                          m_etracelevelMinimum;
//       ::pointer < ::platform::system_factory >      m_psystemfactory;
//       // END FROM ::main (Now main2)
//
//
//       //::pointer<::platform::application>     application();
//       // ::pointer<::platform::application>     application();
//
//
//       //::pointer<main_hold_base>                                         m_pmainholdbase;
//       //::pointer<system_impl> *                                        m_psystemimpl;
// #if !defined(WINDOWS)
//       ::pointer<::exception_translator>                                 m_pexceptiontranslator;
// #endif
//       ::pointer<::factory::factory>                                     m_pfactoryFolder;
//
//       bool                                                              m_bPostedInitialRequest;
//
//
//       ::pointer<::apex::system>                                       m_psystemParent;
//
//       ::pointer < ::prototype::prototype >                              m_pprototype;
//       //::pointer < ::mutex >                                           m_pmutexFactory;
//       //string_map < ::pointer<::factory::factory >>                  m_mapFactory;
//       //string_map < ::pointer<::factory::factory >>                      m_mapFactory;
//
//
//       pointer< string_map < ::pointer<::regular_expression::context >>>                        m_pmapRegularExpressionContext;
//
// #ifdef __APPLE__
//       void * m_pmmos;
// #endif
//
//       //::pointer < ::draw2d::draw2d  >                          m_pdraw2d;
//
//
//
//
//       ::pointer < ::datetime::datetime >                       m_pdatetime;
//
//       ::pointer<::particle>                                    m_pmutexUiDestroyed;
//
//       ::pointer <::nano::nano >                                m_pnano;
//
//
//       ::pointer <::crypto::crypto >                            m_pcrypto;
//
//       string                                                            m_strOsUserTheme;
//
//       class ::time                                                        m_timeFileListingCache;
//       //critical_section                                                  m_csEnumText;
//       //string_map < i64_map < string > >                                 m_mapEnumToText;
//       //string_map < string_map < huge_integer > >                                 m_mapTextToEnum;
//
//
//       ::pointer<::internet::internet>                                   m_pinternet;
//       ::pointer<::url::url_context>                                     m_purlcontext;
//
//       ::pointer<class ::base64>                                  m_pbase64;
//
//       ::pointer<class ::xml::xml>                                     m_pxml;
//
//       ::pointer<class ::platform::node>                                     m_pnode;
//       ::pointer<geometry::geometry>                                   m_pgeometry;
//
//
//       ::pointer<::text::table>                                        m_ptexttable;
//
//
//       //enum_trace_level                                                  m_etracelevel;
//       class ::time                                                        m_timeMainStart;
//       //class ::time                                                        m_timeAfterApplicationFirstRequest;
//       bool                                                              m_bIsReadyForUserInteraction;
//
//
//       ::pointer<class ::directory_system>                                 m_pdirectorysystem;
//       ::pointer<class ::file_system>                                      m_pfilesystem;
//       ::pointer<class ::path_system>                                      m_ppathsystem;
//
//       ::pointer<::directory_system>                                           m_pdirectorysystem;
//       ::pointer<::file_system>                                          m_pfilesystem;
//
//
//       ::pointer < ::mutex >                                m_pmutexMatter;
//
//       ::pointer < ::mutex >                  m_pmutexHttpDownload;
//       string_array                           m_straHttpDownloading;
//       string_array                           m_straHttpExists;
//          //::pointer < ::windowing::windowing_base > m_pwindowingbase;
// //#if defined(WITH_X11) || defined(WITH_XCB)
//   //    ::particle_pointer                                 m_pmutexXlib;
// //#endif
//       ::pointer < ::factory::factory_item_interface >      m_pfactoryitemCompressZlib;
//       ::pointer < ::factory::factory_item_interface >      m_pfactoryitemUncompressZlib;
//       ::pointer < ::compress >                             m_pcompressZlibCrc32;
//
//
//
//


      system();
      ~system() override;
      


      void on_set_platform() override;


      void on_initialize_particle() override;


      virtual void do_graphics_and_windowing_system_factory();


      void initialize_system();

      virtual enum_trace_level get_trace_level();
      //void os_construct();

         virtual void initialize_matter();

#ifdef _DEBUG


      huge_integer increment_reference_count() override;


      huge_integer decrement_reference_count() override;


#endif

      virtual ::mathematics::mathematics * mathematics();

      virtual ::image::imaging * imaging();

// #if defined(WITH_X11) || defined(WITH_XCB)
//       virtual ::particle * x11_synchronization();
// #endif

      inline ::pointer<::platform::node> & node() { return m_pnode; }

      inline class ::base64 * base64() { return m_pbase64; };

      inline ::xml::xml * xml() { return m_pxml.get() ? m_pxml.get() : _xml(); }

      inline ::file_system * file_system() const { return m_pfilesystem; }

      inline ::directory_system * directory_system() const { return m_pdirectorysystem; }

      inline ::path_system * path_system() const { return m_ppathsystem; }

      virtual ::platform::system_factory* system_factory();

      virtual ::xml::xml * _xml();

      inline geometry::geometry * geometry() { return m_pgeometry; }

      inline ::datetime::datetime * datetime() { return m_pdatetime; }

      inline ::text::table * texttable() { return m_ptexttable; }

      inline ::internet::internet* internet() { return m_pinternet; }
      inline ::url::url_context* url() { return m_purlcontext; }

      ::particle * ui_destroyed_synchronization() { return m_pmutexUiDestroyed; }

      virtual ::nano::nano * nano();

      virtual ::micro::user * micro_user();
      virtual ::acme::windowing::windowing * acme_windowing();
      virtual ::windowing::windowing * windowing();

      virtual void defer_innate_ui();

      virtual ::innate_ui::innate_ui * innate_ui();
      
      //virtual nano::nano * nano()

      inline ::crypto::crypto * crypto() { return m_pcrypto; }

      virtual class ::manager_room * manager_room();

      //::acme::acme * acme() const { return m_pacme; }

      ::prototype::prototype * prototype() const { return m_pprototype; }

      virtual ::draw2d::draw2d * draw2d() const;
      virtual ::write_text::write_text * write_text() const;

         //virtual ::windowing::windowing_base * windowing_base();

      virtual string get_system_platform();
      virtual string get_system_configuration();





      virtual void defer_audio();

      virtual bool has_audio();

      virtual void init1();

      virtual void init2();

      void set_current_handles() override;

      virtual void TermSystem();


      virtual void erase_from_any_hook(::matter * pmatter);


      virtual void create_os_node();

      virtual string os_get_user_theme();


      template < typename BASE_TYPE >
      ::pointer<BASE_TYPE> create(const ::string & strComponent, const ::string & strImplementation)
      {

         auto & pfactory = this->factory(strComponent, strImplementation);

         if (!pfactory)
         {

            throw ::exception(error_resource);

         }

         auto p = pfactory->__call__create< BASE_TYPE >(this);

         if (!p)
         {

            return p;

         }

         return p;

      }


      virtual unsigned int crc32(unsigned int uCrc, const ::block & block);


      virtual void create_session(::collection::index iEdge = 0);

      virtual ::pointer<::platform::session>on_create_session(::collection::index iEdge);

      virtual ::platform::session* session(::collection::index iEdge = 0);


      virtual void add_session(::collection::index iEdge, ::platform::session* psession);
      virtual void on_add_session(::platform::session* psession);
      virtual void erase_session(::collection::index iEdge);


      void on_request(::request* prequest) override;


      void process_exit_status(::particle * pparticle, const ::e_status & estatus);


      virtual ::platform::application * get_main_app();


      virtual ::pointer<::factory::factory> & folder_factory();


      //using main::system_construct;


      virtual void system_construct(::platform::application * pacmeapplicationStartup);

#ifdef WINDOWS_DESKTOP

      void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, int nCmdShow);

#elif defined(UNIVERSAL_WINDOWS)

      void system_construct(const ::string_array & stra);

      //#else

         //void system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif

      virtual void speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang = "en-us", enum_gender egender = e_gender_none);


      virtual ::pointer<::factory::factory> & node_factory();


      virtual void inline_init();
      virtual void inline_term();


      virtual void process_init();


      virtual void call_init_system();


      virtual void init_system();


      virtual void on_start_system();


      virtual void defer_post_initial_request();


      virtual void canonical_system_main();

      virtual void system_main();


      void on_pre_run_task() override;


      virtual void on_branch_system_from_main_thread_startup();


      void main() override;


      virtual ::pointer<::platform::application> new_app(const ::scoped_string & scopedstrAppId);


      virtual void end();


      virtual void on_end();


      virtual void report_system_instance();

      //using ::manager::on_subject;
      //virtual void on_subject(::topic * ptopic) override;

      virtual class ::time get_update_poll_time(const ::atom & atom);


      virtual ::acme::library* on_get_library(const ::string& pszLibrary);




      //virtual ::pointer<::acme::library> & library(const ::string &strComponent, const ::string &strImplementation);


      virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
      virtual void open_link(string strUrl, string strProfile, string strTarget);
      virtual void open_url(string strUrl, string strProfile, string strTarget);


      //void __tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const override;


      //virtual void main_user_async(const ::procedure & procedure, ::enum_priority epriority = e_priority_normal);

      //virtual void main_user_sync(const ::procedure & procedure, const class time & time = one_minute(), enum_priority epriority = e_priority_normal);




      void init_task() override;
      void term_task() override;


      virtual string __get_text(const string & str);

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
//      m_mapEnumToText[typeid(e).name()][(huge_integer)e] = psz;
//
//      m_mapTextToEnum[typeid(e).name()][psz] = (huge_integer)e;
//
//   }

//
//   template < typename ENUM >
//   inline string enum_text(ENUM e)
//   {
//
//      critical_section_lock synchronouslock(&m_csEnumText);
//
//      return m_mapEnumToText[typeid(e).name()][(huge_integer)e];
//
//   }

//
//   template < class ENUM >
//   inline ENUM text_enum(ENUM& e, const ::string &psz, ENUM eDefault = (ENUM)0)
//   {
//
//      critical_section_lock lock(&m_csEnumText);
//
//      huge_integer iValue;
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
//      return enum_text(b.m_evalue, (huge_integer)(ENUM)b);
//
//   }


      ::task_group * task_group(::enum_priority epriority = ::e_priority_none);

      ::task_tool * task_tool(::enum_task_tool etool);



      static inline ::atom atom(const ::std::type_info & info);
      static inline ::atom atom(const ::scoped_string & scopedstr);
      static inline ::atom atom(const string & str);
      static inline ::atom atom(huge_integer i);
      //static inline ::atom_space & atom();
      inline ::atom atom(const ::payload & payload);
      inline ::atom atom(const property & prop);

      virtual void check_exit();

      virtual ::regular_expression_pointer create_regular_expression(const ::string & pszStyle, const string & str);
      //virtual ::pointer<::regular_expression::context> create_regular_expression_context(const ::string &pszStyle, int iCount);
      virtual ::pointer<::regular_expression::context> get_regular_expression_context(const ::string & pszStyle);

      virtual ::regular_expression_pointer compile_pcre(const string & str);
      virtual ::pointer<::regular_expression::context> get_pcre_context();
      //virtual int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)

      virtual void get_public_internet_domain_extension_list(string_array & stra);
      virtual ::string fetch_public_internet_domain_extension_list_text();

      virtual void system_id_update(huge_integer iUpdate, huge_integer iPayload);
      
      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void add_handler(::particle * pmatter, bool bPriority = false);

      virtual void add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal);
      
      virtual void erase_signal_handler(::signal_handler::base * pbase);

      //virtual void erase_signal_handlers(::particle * ppparticle);

      virtual void node_will_finish_launching();

      virtual void on_open_untitled_file();

      virtual void on_open_file(const ::string & pszFile);

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

      virtual void _compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation);
      virtual void _uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation, transfer_progress_function transferprogressfunction = {});

      virtual void zlib_compress(const ::payload& payloadTarget, const ::payload& payloadSource);
      virtual void zlib_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, transfer_progress_function transferprogressfunction = {});

      virtual bool fast_is_decompressable_folder(const ::file::path & path);

      //virtual void windowing_send(const ::procedure & procedure);
      //virtual void windowing_post(const ::procedure & procedure);

      
      bool _handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;


      //virtual void windowing_post_quit();

      virtual string get_latest_deployment_number(const ::string & strBranch);

      
      void destroy() override;





      //CLASS_DECL_ACME ::acme::library * lib(const ::scoped_string & scopedstr);



      //::file::path library_file_name(const ::string& str);


      //template < typename ENTRY >
      //ENTRY* library_call(const ::scoped_string & scopedstrLibrary, const ::scoped_string & scopedstrEntry)
      //{

      //   return lib(pszLibrary)->get<decltype(&ENTRY)>(pszEntry));

      //}

//#define LIBCALL(library, entry)  (system()->lib(#library)->get<decltype(&entry)>(#entry))


      virtual ::string implementation_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);
      virtual ::string library_name(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation);


      //class ::crypto::crypto * crypto();


      virtual ::file::path local_get_matter_cache_path();
      virtual ::file::path local_get_matter_cache_path(string strMatter);
      virtual ::file::path local_get_matter_path();
      virtual ::file::path local_get_matter_path(string strMatter);

      virtual void install_progress_add_up(int iAddUp = 1);


      virtual ::string get_application_server_name();


      virtual ::color::color background_color() const;

      virtual double luminance() const;

      virtual void set_background_color(const ::color::color & color);
      
      
      virtual bool dark_mode() const;
      virtual void on_application_dark_mode_change();

//      virtual int get_simple_ui_darkness();

//      virtual void set_simple_ui_darkness(int iWeatherDarkness);

      virtual void set_dark_mode(bool bDark);

      virtual ::color::color get_simple_ui_color(::enum_element eelement, ::user::enum_state estate = ::user::e_state_none);

      virtual ::color::color get_default_color(::color::color color);


// #if defined(WITH_X11)
//       virtual void x11_sync(const ::procedure & procedure);
//       virtual void x11_async(const ::procedure & procedure);
// #endif
      
      virtual bool defer_component_factory(const ::scoped_string & scopedstrComponent);
      virtual bool _defer_component_factory(const ::scoped_string & scopedstrComponent);
      
      //::pointer < ::message_box > & realize(::pointer < ::message_box > & pmessagebox);
      
      //::pointer < ::message_box > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

      //::pointer < ::message_box > exception_message_box(const ::exception & exception, const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

      //::pointer < ::message_box > message_console(const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

      //::pointer < ::message_box > exception_message_console(const ::exception & exception, const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);



// ::aqua::system

      ::pointer<::aqua::audio>                        m_paudio;

      ::pointer<::aqua::multimedia>                   m_pmultimedia;

      ::pointer<::aqua::audio_mixer>                  m_paudiomixer;

      ::pointer<::aqua::estamira>                     m_pestamira;



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
//       void init() override;
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
//       virtual void term() override;
//
//       //virtual void system_prep() override;
//
//       //::url::url                           & url()     { return m_urldepartment; }
//
//       //::thread * get_task(itask_t itask);
//       //itask_t get_thread_id(::thread * pthread);
//       //void set_thread(itask_t itask, ::thread * pthread);
//       //void unset_thread(itask_t itask, ::thread * pthread);
//
//       ::aura::estamira * estamira();
//
//       inline ::hardware::devices * hardware_devices() { return m_phardwaredevices; }
//
//       virtual void defer_initialize_hardware_devices();
//
//
//
//       ::aura::session * get_session();
//       //::aura::node * node();
//
//       inline ::gpu::approach * get_gpu() { if (!m_pgpu) create_gpu(); return m_pgpu.get(); };
//       inline ::gpu::approach * gpu() { return m_pgpu.get(); };
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
//       virtual void initialize_context() override;
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
//       virtual ::pointer<::data::node>load_xml(const ::string & pszXml) override;
//
//       virtual void verb() override; // ambigous inheritance from ::aura::system/::axis::application
//
//
//       //virtual bool is_system() const override;
//
//
//       virtual string crypto_md5_text(const ::string & str) override;
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
//       virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
//       virtual string get_locale_schema_dir() override;
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
//       virtual void on_allocation_error(const ::string & strName, ::object * pobjectSometimes) override;
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
//       //virtual unsigned int os_post_to_all_threads(const ::atom & atom,wparam wparam = 0,lparam lparam = 0) override;
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
//       virtual void thread_loop() override;
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
//       virtual void term2() override;
//
//       virtual void term1() override;
//
//       //virtual void term();
//
//       //virtual void TermSystem() override;
//
//
//       virtual void process_term() override;
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
//       static inline ::atom atom(huge_integer i);
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
//       //virtual ::collection::index openweather_find_city2(string strQuery, string & strCit, huge_integer & iId, double & dLat, double & dLon);
//       //virtual ::collection::index openweather_find_city2(string strQ1, string strQ2, string & strCit, huge_integer & iId, double & dLat, double & dLon, bool bPrefix);
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
//       //virtual void on_event(huge_natural u, ::particle * pparticle) override;
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
//       virtual string get_host_location_url() override;
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
//       //virtual void main() override;
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
//       //virtual bool adju(::collection::index iMonitor, unsigned int dwTemperature, double dBrightness, double dwGamma);
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
//


   };



} // namespace platform


//
//
//
//
////CLASS_DECL_ACME string get_latest_deployment_number(const ::string & strBranch);
//
//inline ::platform::system* system()
//{
//
//   return system();
//
//}
//
//
//


// inline ::platform::system * system()
// {
//
//    return ::platform::system::g_p;
//
// }
//
//
