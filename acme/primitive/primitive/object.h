#pragma once


enum enum_method : ::i32;
enum enum_future : ::i32;


namespace user
{

   class primitive;

}

namespace acme
{

   class context;

}


namespace apex
{

 
   class context;


} // namespace apex


namespace aura
{


   class context;


} // namespace aura


class CLASS_DECL_ACME object :
   virtual public property_object
{
protected:


   ::object *                                         m_pobjectParentTask;
   __pointer(__pointer_array(::object))             m_pobjectaChildrenTask;


public:


   //::task_pointer                                 m_pthread;
   //__pointer(::application)                            m_papplication;
   //__pointer(::apex::session)                          m_psession;
   //__pointer(class ::system)                           m_psystem;
   ::acme::context *                                     m_pcontext;


   //__pointer(__pointer_array(::object))                m_pobjecta;
   __pointer(__pointer_array(::matter))                  m_pcompositea;
   __pointer(__pointer_array(::matter))                  m_preferencea;



   //::object_meta *                                    m_pmeta;
   //::i64                                              m_cRun;


   //object() : m_pmeta(nullptr) { }
   object() { m_pobjectParentTask = nullptr; m_pcontext = nullptr; }
   //object(::object * pobject);
   object(enum_default_initialization) : ::object() { m_pobjectParentTask = nullptr; m_pcontext = nullptr; };
   ~object() override;


#ifdef _DEBUG


   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#else


   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


#endif


   //inline class ::system* get_system() const;

   //inline matter_array * _composite_array() { return m_pcompositea; }
   //inline matter_array * _reference_array() { return m_preferencea; }


   //inline matter_array & composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   //inline matter_array & reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }

   //virtual void add_object(::object * pobject);
   //virtual void on_delete_object(::object * pobject);

   //virtual void enumerate_composite(matter_array& a);
   //virtual void enumerate_reference(matter_array& a);

   //virtual void process_exit_status(const ::e_status& estatus);

   //inline ::object* this const { return this; }
   //virtual ::e_status set_object(::object* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   //inline ::application* application() { return m_papplication; }


   //inline ::application* get_application() { return _get_application(); }

   //virtual ::application* _get_application() override;

   template < typename BASE_TYPE >
   __pointer(BASE_TYPE) file_as(const ::payload& varFile);


   //virtual void add_routine(const ::id& idRoutine, const ::routine& routine);


   //virtual void add_each_routine_from(const ::id& idRoutine, ::object* pobjectSource);


   //virtual array < ::routine >* routinea(const ::id& idRoutine);


   virtual void call_routine(const ::id& idRoutine);


   //inline ::payload context_value(const ::payload& payload);


   virtual ::text::text __text(const ::id& id);


   virtual void task_erase(::task* ptask) override;


   virtual ::e_status sleep(const ::duration& duration);


   template < typename BASE_TYPE >
   void save_to(const ::payload& varFile, BASE_TYPE* pobject);

   
   virtual ::e_status initialize(::object * pobject) override;
   virtual ::e_status set_finish() override;
   //virtual ::e_status destroy() override;

   virtual void add_task(::object* pobjectTask);
   virtual void erase_task(::object* pobjectTask);
   virtual void transfer_tasks_from(::object * ptask);
   virtual bool is_ascendant_task(::object * ptaskCandidateAscendant) const;

//   ::e_status destroy() override;

   //virtual ::e_status set_finish();


   virtual bool is_thread() const override;
   virtual bool task_get_run() const;
   virtual bool is_running() const;
   //virtual void child_post_quit(const char* pszTag);
   //virtual void child_post_quit_and_wait(const char* pszTag, const duration& duration);


   virtual ::e_status post(const ::routine& routine);


   //::e_status destroy() override;

   //virtual ::e_status finish(::property_object* pcontextobjectRootFinishingInitiator = nullptr) override;
   //virtual ::e_status set_finish(::property_object* pcontextobjectRootFinishingInitiator) override;
   //virtual ::e_status set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;
   //virtual ::e_status on_finish() override;

   virtual bool check_tasks_finished();

   ::e_status destroy() override;

   virtual ::e_status destroy_tasks();

   ::e_status destroy_composites() override;

   ::e_status release_references();



   //virtual ::e_status on_initialize_object() override;


   //inline const char* topic_text();

   //context& __context(const ::payload& payload);

   //::payload __context_value(const ::payload& payload);

   //virtual void set_topic_text(const string& str);

   //void create_object_meta();

   //inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   //inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }

   inline ::acme::context* get_context() const { return m_pcontext; }

   //inline ::thread* get_thread() const { return m_pthread; }

   //inline ::application* get_application() const { return m_papplication; }

   //inline ::apex::session* get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papplication; }

   virtual string get_text(const ::payload& payload, const ::id& id) override;

   //#ifdef _DEBUG
   //   virtual void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   virtual void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   virtual void set_context_app(::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   virtual void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   //virtual void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   //virtual void set_context_user(::object * puserContext);
   //#else
   //   inline void set_context(::context* pcontext);
   //   inline void set_context_thread(::thread* pthread);
   //   inline void set_context_app(::application* pappContext);
   //   inline void set_context_session(::apex::session* psessionContext);
   //   //inline void set_context_system(::apex::system* psystemContext);
   //   //inline void set_context_user(::object * puserContext);
   //#endif


      //virtual void set_object(::object * pobject) override;


      //inline void defer_set_object(::object * pobject);

   virtual ::e_status operator()() override;


   inline i64 get_ref_count()
   {

      return m_countReference;

   }


   //virtual ::user::primitive* get_user_interaction_host();
   //virtual ::user::interaction * get_host_window();


   virtual void dev_log(string str) const;

//   ::object& operator = (const ::payload& payload);




   //static u32 s_thread_proc(void* p);


   //virtual void to_string(const string_exchange & str) const override;

   //::image_transport create_image();
   //::image_transport create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_transport get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   //::image_transport matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   template < typename BASE_TYPE >
   inline __transport(BASE_TYPE) __create();

   template < typename BASE_TYPE >
   inline __transport(BASE_TYPE) __id_create(const ::id& id);

   template < typename TYPE >
   inline __transport(TYPE) __create_new();


   template < typename BASE_TYPE >
   inline ::e_status __defer_construct(__pointer(BASE_TYPE)& ptype);

   template < typename TYPE >
   inline ::e_status __defer_construct_new(__pointer(TYPE)& ptype);



   template < typename BASE_TYPE >
   inline ::e_status __construct(__pointer(BASE_TYPE)& ptype);

   template < typename BASE_TYPE >
   inline ::e_status __id_construct(__pointer(BASE_TYPE)& ptype, const ::id& id);

   template < typename TYPE >
   inline ::e_status __construct_new(__pointer(TYPE)& ptype);

   //template < typename BASE_TYPE >
   //inline ::e_status __release(__composite(BASE_TYPE) & pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline ::e_status __release(__reference(BASE_TYPE) & preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status release_reference(__pointer(SOURCE) & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   //virtual ::e_status add_composite(::matter * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual ::e_status add_reference(::matter * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //virtual ::e_status release_composite2(::matter * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual ::e_status finalize_composite(::matter * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual ::e_status release_reference(::matter * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //template < typename BASE_TYPE >
   //inline ::e_status add_composite(__composite(BASE_TYPE) & pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __refer(__reference(BASE_TYPE) & preference, const SOURCE * psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __refer(__reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __refer(__reference(BASE_TYPE) & preference, const ::primitive::member < SOURCE > & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status add_reference(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status add_reference(__reference(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   virtual void delete_this() override;

   virtual void destruct();

   static void system(const ::string & pszProjectName);

   //virtual ::e_status enable_application_events(bool bEnable = true);

   virtual ::e_status handle_exception(const ::exception::exception& e) override;

   virtual ::e_status top_handle_exception(const ::exception::exception& e);

   virtual ::e_status process_exception(const ::exception::exception& e);


   ::property_object* parent_property_set_holder() const override;

   //void copy_from(const object& o);


   virtual string get_tag() const;


   virtual void defer_update_object_id();
   virtual ::id calc_default_object_id() const;


   virtual void install_message_routing(::channel* pchannel);

   void message_receiver_destruct();

   void _001OnUpdate(::message::message* pmessage);

   //virtual ::e_status request_file(const ::payload& varFile);

   //virtual ::e_status request_file(const ::payload& varFile, ::payload varQuery);

   //virtual ::e_status request(arguments arguments);

   //virtual ::e_status do_request(::create* pcreate);

   virtual void do_request(::create* pcreate);

   virtual __pointer(::extended::future < ::conversation >)  message_box(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual ::e_status message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual ::e_status message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //virtual ::e_status message_box_timeout(::user::primitive* puserinteractionOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

   //virtual void release_references();

   //virtual __pointer(::matter) running(const char* pszTag) const;

   virtual bool ___is_reference(::matter* pobject) const;

   virtual bool __is_composite(::matter* pobject) const;

   virtual bool __is_child_task(::object * pobject) const;

   //virtual void on_finalize();

   virtual void call_request(::create* pcreate);


   virtual void request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::application* pappOnBehalfOf);
   virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id id = ::id());
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual ::e_status run() override;

   //virtual string lstr(const ::id& id, string strDefault = "");

   //virtual string __get_text(string str);

   //template < typename PRED >
   //::image_transport get_image(const ::payload & varFile, ::u64 uTrait, PRED pred);

   //virtual ::image_transport load_image(const ::payload & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_transport load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_transport load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_transport load_thumbnail(const ::payload & varFile, int w, int h);
   //virtual ::image_transport load_thumbnail(const char * pszPath);
   //virtual ::image_transport load_dib(const ::file::path & pathDib);



   bool IsSerializable() const;

   //using property_object::branch;

   void branch(const ::routine_array& routinea);
   void branch_each(const ::routine_array& routinea);

   //using property_object::defer_branch;

   template < typename TASK >
   inline __composite(TASK) & defer_branch(__composite(TASK) & ptask, const ::routine& routine)
   {

      if (ptask && ptask->is_running())
      {

         return ptask;

      }

      auto estatus = __defer_compose_new(ptask);

      if(!estatus)
      {

         return ptask;

      }

      ptask->m_pmatter = routine;

      ptask->branch();

      return ptask;

   }


   template < typename THREAD >
   inline __pointer(THREAD)& defer_branch(__pointer(THREAD)& pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }


   inline ::e_status defer_branch(::task_pointer& ptask, const ::routine& routine);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   template < typename PREDICATE >
   inline __transport(task) fork(PREDICATE predicate,
      ::enum_priority epriority = e_priority_normal,
      ::u32 nStackSize = 0,
      ::u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);


   //inline ::task_pointer launch(const ::routine& routine);


   //template < typename METHOD >
   //inline ::task_pointer opt_fork(const ::routine& routine);


   //template < typename METHOD >
   //inline ::task_pointer fork(METHOD method);


//   template < typename PRED >
   //inline auto new_predicateicate_thread(PRED pred);

   template < typename TYPE >
   inline __transport(task) branch_task(void (TYPE::* pfnMemberProcedure)(),
      ::enum_priority epriority = e_priority_normal,
      ::u32 nStackSize = 0,
      ::u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF)
   {

      return fork([this, pfnMemberProcedure]()
      {

         TYPE* ptype = dynamic_cast <TYPE*> (this);

         (ptype->*pfnMemberProcedure)();

      },
         epriority,
         nStackSize,
         dwCreateFlags ADD_PASS_SEC_ATTRS);


   }


   __transport(::task) branch_task(matter* pmatter,
      ::enum_priority epriority = e_priority_normal,
      ::u32 nStackSize = 0,
      ::u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);


   template < typename PRED >
   inline ::task_pointer predicate_run(bool bSync, PRED pred);

   //using property_object::branch;

   __transport(::task) branch(
      ::enum_priority epriority = ::e_priority_normal,
      ::u32 nStackSize = 0,
      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   //::task_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   inline ::file_transport get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   inline ::file_transport get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   inline ::file_transport fully_shared_reader(const ::payload& varFile) { return get_reader(varFile, ::file::e_open_share_deny_none); }

   //virtual void to_string(string & str) const override;


   virtual ::file_transport get_file(const ::payload& varFile, const ::file::e_open& eopen);
   //inline ::file_transport get_reader(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary);
   //inline ::file_transport get_writer(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //::e_status add_update_notification(property * pproperty);
   //::e_status add_update_notification(const ::id & id, bool bCreate = true);
   //::e_status property_notify(const ::id & id, ::matter * pmatter);


//   inline void format_topic_text(const char * psz, ...)
//   {
//
//      va_list valist;
//      va_start(valist, psz);
//      format_topic_text_v(psz, valist);
//      va_end(valist);
//
//   }
//
//
//   inline void format_topic_text_v(const char * psz, va_list valist)
//   {
//
//      string str;
//      str.FormatV(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(::e_status (TYPE:: * pfn)(), ::enum_priority epriority = ::e_priority_normal)
   //{

   //   TYPE * ptype = dynamic_cast <TYPE *>(this);

   //   return ptype->fork([ptype, pfn]()
   //      {

   //         return (ptype->*pfn)();

   //      }, NULL, 0, epriority);

   //}


   template < typename TYPE >
   ::task_pointer branch_below_normal(void (TYPE::* pfn)())
   {

      return branch(pfn, ::e_priority_below_normal);

   }


   template < typename TYPE >
   ::e_status __construct(::task_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   template < typename TYPE >
   ::e_status __construct_below_normal(::task_pointer& p, void (TYPE::* pfn)());


   template < typename TYPE >
   ::task_pointer defer_branch(const ::id& id, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);

   ::task_pointer defer_branch(const ::id& id, const ::routine & routine, enum_priority epriority = e_priority_normal);

   virtual matter* get_taskpool_container() override;

   //object() : m_pmeta(nullptr) { }
   //object(::object * pobject);
   //object(enum_default_initialization) : ::object() {};
   //virtual ~object();
//
//
//#ifdef _DEBUG
//
//
//   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
//   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
//   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
//
//
//#else
//
//
//   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
//   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
//   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
//
//
//#endif




   //inline matter_array* _composite_array() { return m_pcompositea; }
   //inline matter_array* _reference_array() { return m_preferencea; }


   //inline matter_array& composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   //inline matter_array& reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }



   //virtual void process_exit_status(const ::e_status& estatus);

   //inline ::object* this const { return this; }
   //virtual ::e_status set_object(::object* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   //inline ::application* application() { return m_papplication; }

   //template < typename TYPE, typename TYPE2 >
   //void __bind(reference < TYPE >& r, TYPE2& t)
   //{

   //   __refr(r, t);

   //}
   ///__bind(referer, referee, ...) __m_bind(referer, (referer)->referee, __VA_ARGS__)



   //template < typename BASE_TYPE >
   //__pointer(BASE_TYPE) file_as(const ::payload& varFile);


   //virtual void add_routine(const ::id& idRoutine, const ::routine& routine);


   //virtual void add_each_routine_from(const ::id& idRoutine, ::object* pobjectSource);


   //virtual array < ::routine >* routinea(const ::id& idRoutine);


   //virtual void call_routine(const ::id& idRoutine);


   //inline ::payload context_value(const ::payload& payload);


   //virtual void task_erase(::task* ptask) override;


   //virtual ::e_status sleep(const ::duration& duration);


   //template < typename BASE_TYPE >
   //void save_to(const ::payload& varFile, BASE_TYPE* pobject);

   //virtual ::e_status initialize(::object * pobject) override;
   //virtual ::e_status destroy() override;

   //inline const char* topic_text();

   //context& __context(const ::payload& payload);

   //::payload __context_value(const ::payload& payload);

   //virtual void set_topic_text(const string& str);

   //void create_object_meta();

   //inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   //inline ::object_meta* get_meta() { defer_object_meta(); return m_pmeta; }

   //inline ::context* get_context() const { return m_pcontext; }

   inline ::application * get_application() const;

   inline ::apex::session * get_session() const;

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papplication; }

   //virtual string get_text(const ::payload& payload, const ::id& id) override;

//#ifdef _DEBUG
//   virtual void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void set_context_app(::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   //virtual void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   //virtual void set_context_user(::object * puserContext);
//#else
//   inline void set_context(::context* pcontext);
//   inline void set_context_thread(::thread* pthread);
//   inline void set_context_app(::application* pappContext);
//   inline void set_context_session(::apex::session* psessionContext);
//   //inline void set_context_system(::apex::system* psystemContext);
//   //inline void set_context_user(::object * puserContext);
//#endif


   //virtual void set_object(::object * pobject) override;


   //inline void defer_set_object(::object * pobject);

   //virtual ::e_status operator()() override;


   //inline i64 get_ref_count()
   //{

   //   return m_countReference;

   //}


   //virtual ::user::primitive* get_user_interaction_host();
   //virtual ::user::interaction * get_host_window();


   //virtual void dev_log(string str) const;

   ::object& operator = (const ::payload& payload);




   //static u32 s_thread_proc(void* p);


   string to_string() const override;


   // for composition (ownership)

   template < typename BASE_TYPE >
   inline ::e_status __compose(__composite(BASE_TYPE)& ptype);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __compose(__composite(BASE_TYPE)& ptype, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __compose(__composite(BASE_TYPE)& ptype, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE >
   inline ::e_status __id_compose(__composite(BASE_TYPE)& ptype, const ::id& id);

   template < typename BASE_TYPE >
   inline ::e_status __raw_compose(__composite(BASE_TYPE)& ptype);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __raw_compose(__composite(BASE_TYPE)& ptype, const SOURCE* psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __raw_compose(__composite(BASE_TYPE)& ptype, const __pointer(SOURCE)& psource);

   template < typename TYPE >
   inline ::e_status __raw_compose_new(__composite(TYPE)& ptype);

   template < typename TYPE >
   inline ::e_status __compose_new(__composite(TYPE)& ptype);




   template < typename BASE_TYPE >
   inline ::e_status __defer_compose(__composite(BASE_TYPE)& ptype) { return !ptype ? __compose(ptype) : ::e_status(::success); }

   template < typename BASE_TYPE >
   inline ::e_status __defer_id_compose(__composite(BASE_TYPE)& ptype, const ::id& id) { return !ptype ? __id_compose(ptype) : ::e_status(::success); }

   template < typename TYPE >
   inline ::e_status __defer_raw_compose_new(__composite(TYPE)& ptype) { return !ptype ? __raw_compose_new(ptype) : ::e_status(::success); }

   template < typename TYPE >
   inline ::e_status __defer_compose_new(__composite(TYPE)& ptype) { return !ptype ? __compose_new(ptype) : ::e_status(::success); }



   //template < typename BASE_TYPE >
   //inline ::e_status __construct(__pointer(BASE_TYPE)& ptype);

   //template < typename BASE_TYPE >
   //inline ::e_status __id_construct(__pointer(BASE_TYPE)& ptype, const ::id& id);

   //template < typename TYPE >
   //inline ::e_status __construct_new(__pointer(TYPE)& ptype);

   template < typename BASE_TYPE >
   inline ::e_status __release(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE >
   inline ::e_status __release(__reference(BASE_TYPE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline ::e_status __release(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual ::e_status add_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual ::e_status add_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //virtual ::e_status release_composite2(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual ::e_status finalize_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual ::e_status release_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //template < typename BASE_TYPE >
   //inline ::e_status add_composite(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __refer(__reference(BASE_TYPE)& preference, const ::primitive::member < SOURCE >& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline ::e_status add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline ::e_status add_reference(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline ::e_status add_reference(__reference(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //virtual void delete_this() override;

   //virtual void destruct();

   //static void system(const char* pszProjectName);

   //virtual ::e_status enable_application_events(bool bEnable = true);

   //virtual ::e_status handle_exception(const ::exception::exception& e);

   //virtual ::e_status top_handle_exception(const ::exception::exception& e);

   //virtual ::e_status process_exception(const ::exception::exception& e);


   //::object* parent_property_set_holder() const override;

   //void copy_from(const object& o);


   //virtual string get_tag() const;
   //virtual bool is_thread() const override;
   //virtual bool task_get_run() const;
   //virtual bool is_running() const;
   //virtual void child_post_quit(const char* pszTag);
   //virtual void child_post_quit_and_wait(const char* pszTag, const duration& duration);
   //virtual ::e_status finish(::property_object* pcontextobjectFinish = nullptr) override;
   //virtual ::e_status set_finish(::property_object* pcontextobjectFinish) override;
   //virtual ::e_status set_finish_composites(::property_object* pcontextobjectFinish) override;
   //virtual void on_finish() override;


   //virtual void defer_update_object_id();
   //virtual ::id calc_default_object_id() const;


   //virtual void install_message_routing(::channel* pchannel);

   //void message_receiver_destruct();

   //void _001OnUpdate(::message::message* pmessage);

   //virtual ::e_status request_file(const ::payload& varFile);

   //virtual ::e_status request_file(const ::payload& varFile, ::payload varQuery);

   //virtual ::e_status request(arguments arguments);

   //virtual ::e_status do_request(::create* pcreate);

   //virtual __pointer(::extended::future < ::conversation >)  message_box(const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual ::e_status message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual ::e_status message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //virtual ::e_status message_box_timeout(::user::primitive* puserinteractionOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

   //virtual void release_references();

   //virtual __pointer(::matter) running(const ::string & pszTag) const;

   //virtual bool ___is_reference(::matter* pobject) const;

   //virtual bool __is_composite(::matter* pobject) const;

   //virtual bool __is_child_task(::task* ptask) const;

   //virtual void on_finalize();

   //virtual ::e_status call_request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::application* pappOnBehalfOf);
   //virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id id = ::id());
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   //virtual ::e_status run() override;

   //virtual string lstr(const ::id& id, string strDefault = "");

   //virtual string __get_text(string str);

   //template < typename PRED >
   //::image_transport get_image(const ::payload & varFile, ::u64 uTrait, PRED pred);

   //virtual ::image_transport load_image(const ::payload & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_transport load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_transport load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_transport load_thumbnail(const ::payload & varFile, int w, int h);
   //virtual ::image_transport load_thumbnail(const char * pszPath);
   //virtual ::image_transport load_dib(const ::file::path & pathDib);



   //bool IsSerializable() const;


   //void start();


   //void single_fork(const ::routine_array& routinea);
   //void multiple_fork(const ::routine_array& routinea);

   //using subject::manager::defer_fork;

   //template < typename THREAD >
   //inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread, const ::routine& routine)
   //{

   //   if (pthread && pthread->is_running())
   //   {

   //      return pthread;

   //   }

   //   pthread->start(routine);

   //   return pthread;

   //}


   //template < typename THREAD >
   //inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread)
   //{

   //   if (pthread && pthread->is_running())
   //   {

   //      return pthread;

   //   }

   //   pthread->begin_thread();

   //   return pthread;

   //}


//   inline ::e_status defer_fork(::task_pointer& pthread, const ::routine& routine);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::task_pointer fork(PRED pred);


   //inline ::task_pointer launch(const ::routine& routine);


   //template < typename METHOD >
   //inline ::task_pointer opt_fork(const ::routine& routine)
   //{

   //   auto ptask = ::get_task();

   //   synchronous_lock synchronouslock(ptask->mutex());

   //   if (ptask && ptask->m_bIsPredicate)
   //   {

   //      routine();

   //      return ptask;

   //   }

   //   return launch(routine);

   //}


   //template < typename METHOD >
   //inline ::task_pointer fork(METHOD method);


//   template < typename PRED >
  // inline auto new_predicate_task(PRED pred);

   //template < typename TYPE >
   //inline auto async(void (TYPE::* pfnMemberProcedure)())
   //{

   //   return fork([this, pfnMemberProcedure]()
   //   {

   //      TYPE* ptype = dynamic_cast <TYPE*> (this);

   //      (ptype->*pfnMemberProcedure)();

   //   });

   //}

   //template < typename PRED >
   //inline ::task_pointer predicate_run(bool bSync, PRED pred);

   //::task_pointer begin(
   //   ::enum_priority epriority = ::e_priority_normal,
   //   ::u32 nStackSize = 0,
   //   u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   //::task_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_transport get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_transport get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());


   //virtual void to_string(string & str) const override;


   //virtual ::file_transport get_file(const ::payload& varFile, const ::file::e_open& eopen);
   //inline ::file_transport get_reader(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary);
   //inline ::file_transport get_writer(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //::e_status add_update_notification(property * pproperty);
   //::e_status add_update_notification(const ::id & id, bool bCreate = true);
   //::e_status property_notify(const ::id & id, ::matter * pmatter);


//   inline void format_topic_text(const char * psz, ...)
//   {
//
//      va_list valist;
//      va_start(valist, psz);
//      format_topic_text_v(psz, valist);
//      va_end(valist);
//
//   }
//
//
//   inline void format_topic_text_v(const char * psz, va_list valist)
//   {
//
//      string str;
//      str.FormatV(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(::e_status (TYPE:: * pfn)(), ::enum_priority epriority = ::e_priority_normal)
   //{

   //   TYPE * ptype = dynamic_cast <TYPE *>(this);

   //   return ptype->fork([ptype, pfn]()
   //      {

   //         return (ptype->*pfn)();

   //      }, NULL, 0, epriority);

   //}


   //template < typename TYPE >
   //::task_pointer start_below_normal(void (TYPE::* pfn)())
   //{

   //   return fork(pfn, ::e_priority_below_normal);

   //}


   //template < typename TYPE >
   //::e_status __construct(::task_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   //template < typename TYPE >
   //::e_status __construct_below_normal(::task_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::task_pointer __start_thread(const ::id& id, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);


   //virtual matter* get_taskpool_container() override;


};


#define __make_identifier(PART1, PART2) PART1 ## PART2


#define __defer_branch(ID) defer_branch(m_ptask ## ID, __routine([this](){ID ## TaskProcedure();}))
                                                                     \

CLASS_DECL_ACME ::e_status call_sync(const ::routine_array& routinea);



