#pragma once


class CLASS_DECL_ACME system :
   virtual public ::acme::context,
   virtual public ::main,
   virtual public ::task
{
public:


   //__pointer(system_impl) *                                                     m_psystemimpl;

   __pointer(::factory::factory)                                   m_pfactoryFolder;
   
   bool                                                              m_bPostedInitialRequest;


   __reference(::application)                                        m_papplicationStartup;
   __reference(::application)                                        m_papplicationMain;

   __composite(::apex::system)                                       m_psystemParent;

   ::mutex                                                           m_mutexLibrary4;
   ::acme::library_map                                               m_mapLibrary4;


   ::mutex                                                           m_mutexFactory;
   //string_map < __pointer(::factory::factory) >                  m_mapFactory;
   string_map < __pointer(::factory::factory) >                      m_mapFactory;


   ::mutex                                                           m_mutexComponentFactory;
   string_map < string_map < __pointer(::factory::factory) > >       m_mapComponentFactory;


   __pointer(string_map < __pointer(::regular_expression::context) >)                        m_pmapRegularExpressionContext;

#ifdef MACOS
   void *                                                            m_pmmos;
#endif

   ::mutex                                                           m_mutexTask;
   task_map                                                          m_taskmap;
   task_id_map                                                       m_taskidmap;
   ::mutex                                                           m_mutexTaskOn;
   map < itask_t, itask_t >                                          m_mapTaskOn;


   __composite(class ::datetime::department)                         m_pdatetime;



   string                                                            m_strOsUserTheme;

   ::duration                                                        m_durationFileListingCache;
   //critical_section                                                  m_csEnumText;
   //string_map < i64_map < string > >                                 m_mapEnumToText;
   //string_map < string_map < i64 > >                                 m_mapTextToEnum;


   __composite(::url::department)                                    m_purldepartment;

   __composite(class ::str::base64)                                  m_pbase64;

   __composite(class ::xml::xml)                                     m_pxml;

   __pointer(class ::acme::node)                                   m_pnode;
   __composite(class ::acme_dir)                                     m_pacmedir;
   __composite(class ::acme_file)                                    m_pacmefile;
   __composite(class ::acme_path)                                    m_pacmepath;
   __composite(geometry::geometry)                                   m_pgeometry;


   __composite(::text::table)                                        m_ptexttable;


   enum_trace_level                                                  m_etracelevel;


   system();
   ~system() override;


   void os_construct();


#ifdef _DEBUG


   i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


   i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


   inline __pointer(::acme::node) & node() { return m_pnode; }

   inline class ::str::base64* base64() { return m_pbase64; };

   inline ::xml::xml* xml() { return m_pxml.get() ? m_pxml.get() : _xml(); }

   inline acme_dir* acmedir() const { return m_pacmedir; }

   inline acme_path* acmepath() const { return m_pacmepath; }

   virtual ::xml::xml* _xml();

   inline geometry::geometry* geometry() { return m_pgeometry; }

   inline ::datetime::department* datetime() { return m_pdatetime; }

   inline ::text::table* texttable() { return m_ptexttable; }

   inline ::url::department* url() { return m_purldepartment; }

   //inline class ::trace::log& log() { return *m_ptracelog; }

   virtual void defer_audio();

   virtual void init1();

   //virtual logger & log() { return *m_plogger; }

   virtual void set_current_handles();

   virtual void TermSystem();


   virtual void erase_from_any_hook(::matter * pmatter);


   virtual void create_os_node();

   virtual string os_get_user_theme();


   template < typename BASE_TYPE >
   __pointer(BASE_TYPE) create(const ::string& strComponent, const ::string& strImplementation)
   {

      auto & pfactory = this->factory(strComponent, strImplementation);

      if (!pfactory)
      {

         throw_status(error_resource);

      }

      auto p = pfactory->create< BASE_TYPE >();

      if (!p)
      {

         return p;

      }

      return p;

   }


   virtual ::u32 crc32(::u32 uCrc, const ::block & block);

   //virtual enum_linux_distribution get_linux_distribution() const;

   //virtual enum_operating_system get_operating_system() const;

   //virtual ::user::enum_desktop get_edesktop();

   //virtual ::user::enum_desktop calc_edesktop();

//#ifdef LINUX
//    inline enum_linux_distribution get_linux_distribution() const {return m_elinuxdistribution;}
//#endif

   //virtual void defer_calc_os_dark_mode();

   //virtual ::user::enum_desktop calc_edesktop();

   //virtual void defer_calc_os_user_theme();

   void process_exit_status(::object* pobject, const ::e_status3& estatus);


   virtual ::application* get_main_application();


   virtual __pointer(::factory::factory) & folder_factory();


   void system_construct(const ::main & main) override;

   //using main::operator =;
   


   //virtual void system_construct(int argc, char** argv, char** envp);
   //virtual void system_construct(int argc, wchar_t** argv, wchar_t** envp);


#ifdef WINDOWS_DESKTOP

   void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char* pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   void system_construct(const ::string_array & stra);

#elif defined(ANDROID)

   void system_construct(os_local* poslocal, const ::e_display& edisplay = ::e_display_none);

#else

   void system_construct(const char * pszCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif


   virtual __pointer(::factory::factory)& node_factory();


   virtual void inline_init();
   virtual void inline_term();


   virtual void process_init();


   virtual void call_init_system();


   virtual void init_system();


   virtual void on_start_system();


   virtual void post_initial_request();


   virtual void system_main();


   void on_pre_run_task() override;


   void main() override;




   virtual void end();


   virtual void on_end();

   //using ::manager::on_subject;
   //virtual void on_subject(::subject * psubject) override;

   virtual ::duration get_update_poll_time(const ::id& id);

   virtual ::acme::library* on_get_library(const ::string &pszLibrary);

   //virtual void set_factory_global(const ::string &pszComponent, const ::string &pszImplementation);

   //virtual __pointer(::acme::library) open_component_library(const ::string &pszComponent, const ::string &pszImplementation);

   virtual __pointer(::acme::library) create_library(const ::string& strLibrary);

   virtual __pointer(::acme::library)& library(const ::string& str);

   //virtual __pointer(::acme::library)& library(const ::string& strComponent, const ::string& strImplementation);


   virtual __pointer(::factory::factory)& factory(const ::string& strLibrary);


   //virtual __pointer(::acme::library) & library(const ::string &strComponent, const ::string &strImplementation);


   virtual __pointer(::factory::factory) & factory(const ::string& strComponent, const ::string& strImplementation);


   virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
   virtual void open_link(string strUrl, string strProfile, string strTarget);
   virtual void open_url(string strUrl, string strProfile, string strTarget);


   //void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const override;


   //virtual void main_user_async(const ::routine & routine, ::enum_priority epriority = e_priority_normal);

   //virtual void main_user_sync(const ::routine & routine, const ::duration & duration = one_minute(), enum_priority epriority = e_priority_normal);


   ::task* get_task(itask_t itask);
   itask_t get_task_id(const ::task* ptask);
   void set_task(itask_t itask, ::task* ptask);
   void unset_task(itask_t itask, ::task* ptask);




   virtual string __get_text(const string& str);

#ifdef LINUX

   //!!!      virtual void defer_initialize_x11();

#endif


   //__pointer(::extended::sequence < ::conversation >) message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;


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


   ::task_group* task_group(::enum_priority epriority = ::e_priority_none);

   ::task_tool* task_tool(::enum_task_tool etool);

   virtual bool is_task_on(itask_t id);

   virtual bool is_active(::task* ptask);

   virtual void set_task_on(itask_t id);

   virtual void set_task_off(itask_t id);


   static inline ::id id(const ::std::type_info& info);
   static inline ::id id(const char * psz);
   static inline ::id id(const string& str);
   static inline ::id id(i64 i);
   static inline ::id_space& id();
   inline ::id id(const ::payload& payload);
   inline ::id id(const property& prop);

   virtual void check_exit();

   virtual ::regular_expression_pointer create_regular_expression(const ::string &pszStyle, const string& str);
   //virtual __pointer(::regular_expression::context) create_regular_expression_context(const ::string &pszStyle, int iCount);
   virtual __pointer(::regular_expression::context) get_regular_expression_context(const ::string &pszStyle);

   virtual ::regular_expression_pointer create_pcre(const string& str);
   virtual __pointer(::regular_expression::context) get_pcre_context();
   //virtual int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)

   virtual void get_public_internet_domain_extension_list(string_array& stra);

   virtual void system_id_update(::i64 iUpdate, ::i64 iPayload);

   virtual void node_will_finish_launching();
   
   virtual void on_open_untitled_file();
   
   virtual void on_open_file(const ::string &pszFile);

   //template < typename BASE_TYPE >
   //__pointer(BASE_TYPE) create(const char * pszComponent, const char* pszImplementation)
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


   void new_compress(::compress ** ppcompress, const char* pszImplementation);
   void new_uncompress(::uncompress ** ppuncompress, const char* pszImplementation);


   virtual void compress(::file::file* pfileOut, ::file::file* pfileIn, const char* pszImplementation);
   virtual void uncompress(::file::file* pfileOut, ::file::file* pfileIn, const char* pszImplementation);

   
   virtual bool fast_is_decompressable_folder(const ::file::path & path);


};



