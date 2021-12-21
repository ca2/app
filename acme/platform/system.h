#pragma once


class CLASS_DECL_ACME system :
   virtual public ::acme::context,
   virtual public ::main,
   virtual public ::task
{
public:


   __transport(::factory::factory)                                   m_pfactoryFolder;
   
   bool                                                              m_bPostedInitialRequest;


   __reference(::application)                                        m_papplicationStartup;
   __reference(::application)                                        m_papplicationMain;

   __composite(::apex::system)                                       m_psystemParent;


   ::mutex                                                           m_mutexFactory;
   string_map < __transport(::factory::factory) >                    m_mapFactory;


   ::mutex                                                           m_mutexComponentFactory;
   string_map < string_map < __transport(::factory::factory) > >     m_mapComponentFactory;


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


   ::mutex                                                           m_mutexLibrary4;
   ::acme::library_map                                               m_mapLibrary4;

   string                                                            m_strOsUserTheme;

   ::duration                                                        m_durationFileListingCache;
   //critical_section                                                  m_csEnumText;
   //string_map < i64_map < string > >                                 m_mapEnumToText;
   //string_map < string_map < i64 > >                                 m_mapTextToEnum;


   __composite(::url::department)                                    m_purldepartment;

   __composite(class ::str::base64)                                  m_pbase64;

   __composite(class ::xml::xml)                                     m_pxml;

   __transport(class ::acme::node)                                   m_pnode;
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


   inline __transport(::acme::node) & node() { return m_pnode; }

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

   virtual ::e_status defer_audio();

   virtual ::e_status init1();

   //virtual logger & log() { return *m_plogger; }

   virtual void set_current_handles();

   virtual void TermSystem();


   virtual void erase_from_any_hook(::matter * pmatter);


   virtual ::e_status create_os_node();

   virtual string os_get_user_theme();


   template < typename BASE_TYPE >
   __transport(BASE_TYPE) create(const ::string& strComponent, const ::string& strImplementation)
   {

      auto & pfactory = this->factory(strComponent, strImplementation);

      if (!pfactory)
      {

         return (const ::extended::status &) pfactory;

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

   void process_exit_status(::object* pobject, const ::e_status& estatus);


   virtual ::application* get_main_application();


   virtual __transport(::factory::factory) & folder_factory();


   ::e_status system_construct(const ::main & main) override;

   //using main::operator =;
   


   //virtual void system_construct(int argc, char** argv, char** envp);
   //virtual void system_construct(int argc, wchar_t** argv, wchar_t** envp);


#ifdef WINDOWS_DESKTOP

   ::e_status system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char* pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   ::e_status system_construct(const ::string_array & stra);

#elif defined(ANDROID)

   ::e_status system_construct(os_local* poslocal, const ::e_display& edisplay = ::e_display_none);

#else

   ::e_status system_construct(const char * pszCommandLine, const ::e_display& edisplay = ::e_display_none);

#endif


   virtual __transport(::factory::factory)& node_factory();


   virtual ::e_status inline_init();
   virtual ::e_status inline_term();


   virtual ::e_status process_init();


   virtual ::e_status call_init_system();


   virtual ::e_status init_system();


   virtual ::e_status on_start_system();


   virtual ::e_status post_initial_request();


   virtual ::e_status system_main();


   ::e_status on_pre_run_task() override;


   ::e_status main() override;




   virtual ::e_status end();


   virtual ::e_status on_end();

   //using ::manager::on_subject;
   //virtual void on_subject(::subject * psubject) override;

   virtual ::duration get_update_poll_time(const ::id& id);

   virtual ::acme::library* on_get_library(const ::string &pszLibrary);

   //virtual ::e_status set_factory_global(const ::string &pszComponent, const ::string &pszImplementation);

   //virtual __pointer(::acme::library) open_component_library(const ::string &pszComponent, const ::string &pszImplementation);

   virtual __transport(::acme::library) create_library(const ::string& strLibrary);

   virtual __transport(::acme::library)& library(const ::string& str);

   //virtual __transport(::acme::library)& library(const ::string& strComponent, const ::string& strImplementation);


   virtual __transport(::factory::factory)& factory(const ::string& strLibrary);


   //virtual __transport(::acme::library) & library(const ::string &strComponent, const ::string &strImplementation);


   virtual __transport(::factory::factory) & factory(const ::string& strComponent, const ::string& strImplementation);


   virtual ::e_status open_profile_link(string strUrl, string strProfile, string strTarget);
   virtual ::e_status open_link(string strUrl, string strProfile, string strTarget);
   virtual ::e_status open_url(string strUrl, string strProfile, string strTarget);


   //void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const override;


   //virtual ::e_status main_user_async(const ::routine & routine, ::enum_priority epriority = e_priority_normal);

   //virtual ::e_status main_user_sync(const ::routine & routine, const ::duration & duration = one_minute(), enum_priority epriority = e_priority_normal);


   ::task* get_task(itask_t itask);
   itask_t get_task_id(const ::task* ptask);
   void set_task(itask_t itask, ::task* ptask);
   void unset_task(itask_t itask, ::task* ptask);




   virtual string __get_text(const string& str);

#ifdef LINUX

   //!!!      virtual ::e_status defer_initialize_x11();

#endif


   //__pointer(::extended::sequence < ::conversation >) message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok) override;


   //virtual ::e_status on_initialize_window_object();
   //virtual ::e_status _on_initialize_window_object();

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

   template < typename PRED >
   inline ::count fork_count_end(::property_object* pobject, ::count iCount, PRED pred, index iStart, ::enum_priority epriority)
   {

      if (iCount <= 0)
      {

         return -1;

      }

      //auto psystem = ::apex::get_system();

      auto pgroup = task_group(epriority);

      synchronous_lock slGroup(mutex());

      ///   auto ptool = ::apex::get_system()->task_tool(op_fork_count);

      if (pgroup == nullptr || pgroup->get_count() <= 1)
      {

         for (index i = iStart; i < iCount; i++)
         {

            pred(i);

         }

         return 1;

      }

      if (!pgroup->prepare(::e_task_op_fork_count, iCount - iStart))
      {

         return -1;

      }

      synchronization_array ptra;

      ::count iScan = maximum(1, minimum(iCount - iStart, pgroup->task_count()));

      for (index iOrder = 0; iOrder < iScan; iOrder++)
      {

         __pointer(predicate_holder_base) pusermessage = __new(forking_count_predicate < PRED >(pobject, iOrder, iOrder + iStart, iScan, iCount, pred));

         if (!pgroup->add_predicate(pusermessage))
         {

            return -1;

         }

      }

      if (!(*pgroup)())
      {

         return -1;

      }

      return iScan;

   }


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
   virtual __transport(::regular_expression::context) get_regular_expression_context(const ::string &pszStyle);

   virtual ::regular_expression_pointer create_pcre(const string& str);
   virtual __transport(::regular_expression::context) get_pcre_context();
   //virtual int system::pcre_add_tokens(string_array& stra, const string& strTopic, const string& strRegexp, int nCount)

   virtual ::e_status get_public_internet_domain_extension_list(string_array& stra);

   virtual void system_id_update(::i64 iUpdate, ::i64 iPayload);

   virtual ::e_status node_will_finish_launching();
   
   virtual ::e_status on_open_untitled_file();
   
   virtual ::e_status on_open_file(const ::string &pszFile);

   //template < typename BASE_TYPE >
   //__transport(BASE_TYPE) create(const char * pszComponent, const char* pszImplementation)
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


   __transport(::compress) create_compress(const char* pszImplementation);
   __transport(::uncompress) create_uncompress(const char* pszImplementation);


   virtual ::e_status compress(::file::file* pfileOut, ::file::file* pfileIn, const char* pszImplementation);
   virtual ::e_status uncompress(::file::file* pfileOut, ::file::file* pfileIn, const char* pszImplementation);

   
   virtual bool fast_is_decompressable_folder(const ::file::path & path);


};



