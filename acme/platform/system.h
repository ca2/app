// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSørensen!!
#pragma once


#include "sub_system.h"
//#include "acme.h"
#include "context.h"
#include "plane_system.h"
#include "application_flags.h"
#include "acme/memory/counter.h"
#include "acme/parallelization/_types.h"
#include "acme/primitive/collection/map.h"
#include "acme/primitive/primitive/factory.h"


namespace acme
{


   class CLASS_DECL_ACME system :
      //virtual public ::object,
      virtual public ::acme::context,
      //virtual public ::task,
      virtual public ::plane_system
   {
   public:

      //::APPLICATION_FLAGS                      m_applicationflags;
      sub_system *                                                      m_psubsystem;


      ::apex::system* m_papexsystem;
      ::aqua::system* m_paquasystem;
      ::aura::system* m_paurasystem;
      ::axis::system* m_paxissystem;
      ::base::system* m_pbasesystem;
      ::bred::system* m_pbredsystem;
      ::core::system* m_pcoresystem;


      ::acme::session_map                               m_sessionmap;


      bool                                            m_bFinalizeIfNoSessionSetting;
      bool                                            m_bFinalizeIfNoSession;


      // FROM MAIN (Now APPLICATION_FLAGS : merged on other classes?)

      ::i32_sz* m_pintstringLanguageResourceMap;
      int                              m_iMatterFromHttpCache;

      const char* m_pszMain;

      // END FROM MAIN (Now APPLICATION_FLAGS)

      // FROM ::main (Now main2)

      ::file::path                     m_pathCacheDirectory;
      class ::time                          m_timeStart;
      class ::time                          m_timeAfterApplicationFirstRequest;

      int                              m_iExitCode = 0;


      // END FROM ::main (Now main2)


      //::pointer<::acme::application>     acmeapplication();
      // ::pointer<::acme::application>     acmeapplication();


      //::pointer<main_hold_base>                                         m_pmainholdbase;
      enum_windowing                                                    m_ewindowing;
      //::pointer<system_impl> *                                        m_psystemimpl;
#if !defined(WINDOWS)
      ::pointer<::exception_translator>                                 m_pexceptiontranslator;
#endif
      ::pointer<::factory::factory>                                     m_pfactoryFolder;

      bool                                                              m_bPostedInitialRequest;


      ::pointer<::apex::system>                                       m_psystemParent;


      //::pointer < ::mutex >                                           m_pmutexFactory;
      //string_map < ::pointer<::factory::factory >>                  m_mapFactory;
      //string_map < ::pointer<::factory::factory >>                      m_mapFactory;


      pointer< string_map < ::pointer<::regular_expression::context >>>                        m_pmapRegularExpressionContext;

#ifdef __APPLE__
      void * m_pmmos;
#endif

      ::pointer < ::particle >                                 m_pmutexTask;
      task_map                                                 m_taskmap;
      task_id_map                                              m_taskidmap;
      ::pointer < ::particle >                                 m_pmutexTaskOn;
      
      
      ::map < itask_t, itask_t >                               m_mapTaskOn;


      ::pointer < ::datetime::datetime >                       m_pdatetime;

      ::pointer<::particle>                                    m_pmutexUiDestroyed;

      ::pointer <::nano::nano >                                m_pnano;

      ::pointer <::crypto::crypto >                            m_pcrypto;


      string                                                            m_strOsUserTheme;

      class ::time                                                        m_timeFileListingCache;
      //critical_section                                                  m_csEnumText;
      //string_map < i64_map < string > >                                 m_mapEnumToText;
      //string_map < string_map < i64 > >                                 m_mapTextToEnum;


      ::pointer<::url::url>                                    m_purl;

      ::pointer<class ::base64>                                  m_pbase64;

      ::pointer<class ::xml::xml>                                     m_pxml;

      ::pointer<class ::acme::node>                                     m_pnode;
      ::pointer<geometry::geometry>                                   m_pgeometry;


      ::pointer<::text::table>                                        m_ptexttable;


      enum_trace_level                                                  m_etracelevel;
      class ::time                                                        m_timeMainStart;
      //class ::time                                                        m_timeAfterApplicationFirstRequest;
      bool                                                              m_bIsReadyForUserInteraction;


      ::pointer<class ::acme_directory>                                 m_pacmedirectory;
      ::pointer<class ::acme_file>                                      m_pacmefile;
      ::pointer<class ::acme_path>                                      m_pacmepath;

      ::pointer<::dir_system>                                           m_pdirsystem;
      ::pointer<::file_system>                                          m_pfilesystem;


      ::pointer < logger >                                              m_plogger;


      system();
      ~system() override;
      
      
      void initialize_system();


      void os_construct();


#ifdef _DEBUG


      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      inline ::pointer<::acme::node> & node() { return m_pnode; }

      inline class ::base64 * base64() { return m_pbase64; };

      inline ::xml::xml * xml() { return m_pxml.get() ? m_pxml.get() : _xml(); }

      inline ::acme_file * acmefile() const { return m_pacmefile; }

      inline ::acme_directory * acmedirectory() const { return m_pacmedirectory; }

      inline ::acme_path * acmepath() const { return m_pacmepath; }

      virtual ::xml::xml * _xml();

      inline geometry::geometry * geometry() { return m_pgeometry; }

      inline ::datetime::datetime * datetime() { return m_pdatetime; }

      inline ::text::table * texttable() { return m_ptexttable; }

      inline ::url::url * url() { return m_purl; }

      ::particle * ui_destroyed_synchronization() { return m_pmutexUiDestroyed; }

      inline ::nano::nano * nano() { return m_pnano; }

      inline ::crypto::crypto * crypto() { return m_pcrypto; }


      virtual void defer_audio();

      virtual bool has_audio();

      virtual void init1();

      virtual void init2();

      virtual void set_current_handles();

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

         auto p = pfactory->create< BASE_TYPE >();

         if (!p)
         {

            return p;

         }

         return p;

      }


      virtual ::u32 crc32(::u32 uCrc, const ::block & block);


      virtual void create_session(index iEdge = 0);

      virtual ::pointer<::acme::session>on_create_session(index iEdge);

      virtual ::acme::session* session(index iEdge = 0);


      virtual void add_session(index iEdge, ::acme::session* psession);
      virtual void on_add_session(::acme::session* psession);
      virtual void erase_session(index iEdge);


      void on_request(::request* prequest) override;


      void process_exit_status(::particle * pparticle, const ::e_status & estatus);


      virtual ::acme::application * get_main_app();


      virtual ::pointer<::factory::factory> & folder_factory();


      //using main::system_construct;


      virtual void system_construct(::acme::application * pacmeapplicationStartup);

#ifdef WINDOWS_DESKTOP

      void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

      void system_construct(const ::string_array & stra);

      //#else

         //void system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif


      virtual ::pointer<::factory::factory> & node_factory();


      virtual void inline_init();
      virtual void inline_term();


      virtual void process_init();


      virtual void call_init_system();


      virtual void init_system();


      virtual void on_start_system();


      virtual void defer_post_initial_request();


      virtual void system_main();


      void on_pre_run_task() override;


      void main() override;


      virtual ::pointer<::acme::application> new_app(const ::scoped_string & scopedstrAppId);


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


      ::task * get_task(itask_t itask);
      itask_t get_task_id(const ::task * ptask);
      void set_task(itask_t itask, ::task * ptask);
      void unset_task(itask_t itask, ::task * ptask);


      void init_task() override;
      void term_task() override;


      virtual string __get_text(const string & str);

#ifdef LINUX

      //!!!      virtual void defer_initialize_x11();

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
//      m_mapEnumToText[typeid(e).name()][(i64)e] = psz;
//
//      m_mapTextToEnum[typeid(e).name()][psz] = (i64)e;
//
//   }

//
//   template < typename ENUM >
//   inline string enum_text(ENUM e)
//   {
//
//      critical_section_lock synchronouslock(&m_csEnumText);
//
//      return m_mapEnumToText[typeid(e).name()][(i64)e];
//
//   }

//
//   template < class ENUM >
//   inline ENUM text_enum(ENUM& e, const ::string &psz, ENUM eDefault = (ENUM)0)
//   {
//
//      critical_section_lock lock(&m_csEnumText);
//
//      i64 iValue;
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
//      return enum_text(b.m_evalue, (i64)(ENUM)b);
//
//   }


      ::task_group * task_group(::enum_priority epriority = ::e_priority_none);

      ::task_tool * task_tool(::enum_task_tool etool);

      virtual bool is_task_on(itask_t atom);

      virtual bool is_active(::task * ptask);

      virtual void set_task_on(itask_t atom);

      virtual void set_task_off(itask_t atom);


      static inline ::atom atom(const ::std::type_info & info);
      static inline ::atom atom(const ::scoped_string & scopedstr);
      static inline ::atom atom(const string & str);
      static inline ::atom atom(i64 i);
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

      virtual void system_id_update(::i64 iUpdate, ::i64 iPayload);
      
      void handle(::topic* ptopic, ::context* pcontext) override;

      virtual void add_handler(::matter * pmatter, bool bPriority = false);

      virtual void add_signal_handler(const ::signal_handler& signalhandler, const ::atom & atomSignal);

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


      void new_compress(::compress ** ppcompress, const ::scoped_string & scopedstrImplementation);
      void new_uncompress(::uncompress ** ppuncompress, const ::scoped_string & scopedstrImplementation);


      virtual void compress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation);
      virtual void uncompress(const ::payload & payloadTarget, const ::payload & payloadSource, const ::scoped_string & scopedstrImplementation);


      virtual bool fast_is_decompressable_folder(const ::file::path & path);

      virtual void windowing_send(const ::procedure & procedure);
      virtual void windowing_post(const ::procedure & procedure);

      
      bool _handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;


      //virtual void windowing_post_quit();

      virtual string get_latest_deployment_number(const ::string & strBranch);

      
      void destroy() override;





      // [HERE] 
      //  __node_library should be here at acme
      // 
      //  -- e.g. cannot lie inside a plugin, 
      // because it is used to load a plugin
      //
      void* operating_system_library_open(const ::file::path & path, string& strMessage);
      void* operating_system_library_touch(const ::file::path & path, string& strMessage);
      void* operating_system_library_open_ca2(const ::file::path & path, string& strMessage);
      bool operating_system_library_close(void* plibrary);
      void* operating_system_library_raw_get(void* plibrary, const ::scoped_string & scopedstrEntryName);


      //CLASS_DECL_ACME ::acme::library * lib(const ::scoped_string & scopedstr);



      ::file::path libfilename(const ::string& str);


      //template < typename ENTRY >
      //ENTRY* library_call(const ::scoped_string & scopedstrLibrary, const ::scoped_string & scopedstrEntry)
      //{

      //   return lib(pszLibrary)->get<decltype(&ENTRY)>(pszEntry));

      //}

//#define LIBCALL(library, entry)  (acmesystem()->lib(#library)->get<decltype(&entry)>(#entry))




   };






} // namespace acme





//CLASS_DECL_ACME string get_latest_deployment_number(const ::string & strBranch);



