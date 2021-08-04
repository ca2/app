#pragma once


enum enum_method : ::i32;
enum enum_future : ::i32;

namespace user
{

   class primitive;

}


class CLASS_DECL_APEX object :
   virtual public object
{
public:


   //::task_pointer                                m_pthread;
   //__pointer(::application)                     m_papplication;
   //__pointer(::apex::session)                         m_psession;
   //__pointer(class ::system)                          m_psystem;
   __pointer(::context)                               m_pcontext;



   //::object_meta *                                    m_pmeta;
   //::i64                                              m_cRun;


   //object() : m_pmeta(nullptr) { }
   object() { }
   //object(::object * pobject);
   object(enum_default_initialization) : ::object() {};
   virtual ~object();


#ifdef DEBUG
   
   
   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#else
   
   
   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


#endif

   
   inline ::apex::system* get_system() const;

   //inline matter_array * _composite_array() { return m_pcompositea; }
   //inline matter_array * _reference_array() { return m_preferencea; }


   //inline matter_array & composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   //inline matter_array & reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }



   virtual void process_exit_status(const ::e_status& estatus);

   //inline ::object* this const { return this; }
   //virtual ::e_status set_object(::object* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   inline ::application* application() { return m_papplication; }


   inline ::application* get_application() { return _get_application(); }

   virtual ::application* _get_application() override;

   template < typename BASE_TYPE >
   __pointer(BASE_TYPE) file_as(const ::payload & varFile);


   virtual void add_routine(const ::id & idRoutine, const ::routine & routine);


   virtual void add_each_routine_from(const ::id & idRoutine, ::object * pobjectSource);


   virtual array < ::routine > * routinea(const ::id & idRoutine);


   virtual void call_routine(const ::id & idRoutine);


   inline ::payload context_value(const ::payload & payload);


   virtual void task_erase(::task* ptask) override;


   virtual ::e_status sleep(const ::duration& duration);


   template < typename BASE_TYPE >
   void save_to(const ::payload & varFile, BASE_TYPE * pobject);

   virtual ::e_status initialize(::object * pobject) override;
   virtual ::e_status destroy() override;

   inline const ::string & topic_text();

   context& __context(const ::payload & payload);

   ::payload __context_value(const ::payload & payload);

   virtual void set_topic_text(const ::string & str);

   //void create_object_meta();

   //inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   //inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }

   inline ::context * get_context() const { return m_pcontext; }

   inline ::thread * get_thread() const { return m_pthread; }

   inline ::application * get_application() const { return m_papplication; }

   inline ::apex::session * get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papplication; }

   virtual string get_text(const ::payload & payload, const ::id& id) override;

//#ifdef DEBUG
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

   ::object & operator = (const ::payload & payload);

   


   //static u32 s_thread_proc(void* p);


   //virtual void to_string(const string_exchange & str) const override;

   //::image_result create_image();
   //::image_result create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_result get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   //::image_result matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   template < typename BASE_TYPE >
   inline __transport(BASE_TYPE) __create();

   template < typename BASE_TYPE >
   inline __transport(BASE_TYPE) __id_create(const ::id & id);

   template < typename TYPE >
   inline __transport(TYPE) __create_new();

   //inline ::e_status __compose(__composite(::image) & pimage);

   //inline ::e_status __compose(__composite(::image) & pimage, ::image * pimageSource);

   //inline ::e_status __defer_compose(__composite(::image) & pimage) { return !pimage ? __compose(pimage) : ::e_status(::success); }

   // for composition (ownership)

   //template < typename BASE_TYPE >
   //inline ::e_status __compose(__composite(BASE_TYPE) & pusermessage);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __compose(__composite(BASE_TYPE) & pusermessage, const SOURCE * psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __compose(__composite(BASE_TYPE) & pusermessage, const __pointer(SOURCE) & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline ::e_status __id_compose(__composite(BASE_TYPE) & pusermessage, const ::id & id);

   //template < typename BASE_TYPE >
   //inline ::e_status __raw_compose(__composite(BASE_TYPE) & pusermessage);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __raw_compose(__composite(BASE_TYPE) & pusermessage, const SOURCE * psource);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __raw_compose(__composite(BASE_TYPE) & pusermessage, const __pointer(SOURCE) & psource);

   //template < typename TYPE >
   //inline ::e_status __raw_compose_new(__composite(TYPE) & ptype);

   //template < typename TYPE >
   //inline ::e_status __compose_new(__composite(TYPE) & ptype);




   //template < typename BASE_TYPE >
   //inline ::e_status __defer_compose(__composite(BASE_TYPE) & pusermessage) { return !pusermessage ? __compose(pusermessage) : ::e_status(::success); }

   //template < typename BASE_TYPE >
   //inline ::e_status __defer_id_compose(__composite(BASE_TYPE) & pusermessage, const ::id & id) { return !pusermessage ? __id_compose(pusermessage) : ::e_status(::success); }

   //template < typename TYPE >
   //inline ::e_status __defer_raw_compose_new(__composite(TYPE) & ptype) { return !ptype ? __raw_compose_new(ptype) : ::e_status(::success); }

   //template < typename TYPE >
   //inline ::e_status __defer_compose_new(__composite(TYPE) & ptype) { return !ptype ? __compose_new(ptype) : ::e_status(::success); }




   template < typename BASE_TYPE >
   inline ::e_status __construct(__pointer(BASE_TYPE) & pusermessage);

   template < typename BASE_TYPE >
   inline ::e_status __id_construct(__pointer(BASE_TYPE) & pusermessage, const ::id & id);

   template < typename TYPE >
   inline ::e_status __construct_new(__pointer(TYPE) & pusermessage);

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

   virtual ::e_status enable_application_events(bool bEnable = true);

   virtual ::e_status handle_exception(const ::exception::exception & e) override;

   virtual ::e_status top_handle_exception(const ::exception::exception& e);

   virtual ::e_status process_exception(const ::exception::exception& e);


   ::property_object * parent_property_set_holder() const override;

   void copy_from(const object & o);


   virtual string get_tag() const;
   virtual bool is_thread() const override;
   virtual bool task_get_run() const;
   virtual bool is_running() const;
   virtual void child_post_quit(const ::string & pszTag);
   virtual void child_post_quit_and_wait(const ::string & pszTag, const duration & duration);
   virtual ::e_status finish(::property_object * pcontextobjectRootFinishingInitiator = nullptr) override;
   virtual ::e_status set_finish(::property_object* pcontextobjectRootFinishingInitiator) override;
   virtual ::e_status set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;
   virtual void on_finish() override;


   virtual void defer_update_object_id();
   virtual ::id calc_default_object_id() const;


   virtual void install_message_routing(::channel * pchannel);

   void message_receiver_destruct();

   void _001OnUpdate(::message::message * pmessage);

   virtual ::e_status request_file(const ::payload& varFile);

   virtual ::e_status request_file(const ::payload& varFile, ::payload varQuery);

   virtual ::e_status request(arguments arguments);

   virtual ::e_status do_request(::create * pcreate);

   virtual __pointer(::extended::future < ::conversation >)  message_box(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual ::e_status message_box_timeout(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual ::e_status message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //virtual ::e_status message_box_timeout(::user::primitive* puserinteractionOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

   virtual void release_references();

   virtual __pointer(::matter) running(const ::string & pszTag) const;

   virtual bool ___is_reference(::matter * pobject) const;

   virtual bool __is_composite(::matter * pobject) const;

   virtual bool __is_child_task(::task * ptask) const;

   virtual void on_finalize();

   virtual ::e_status call_request(::create * pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::application* pappOnBehalfOf);
   virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id id = ::id());
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual ::e_status run() override;

   virtual string lstr(const ::id & id, string strDefault = "");

   virtual string __get_text(string str);

   //template < typename PRED >
   //::image_result get_image(const ::payload & varFile, ::u64 uTrait, PRED pred);

   //virtual ::image_result load_image(const ::payload & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_result load_matter_image(const ::string & pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_result load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_result load_thumbnail(const ::payload & varFile, int w, int h);
   //virtual ::image_result load_thumbnail(const ::string & pszPath);
   //virtual ::image_result load_dib(const ::file::path & pathDib);



   bool IsSerializable() const;


   void start();


   void single_fork(const ::routine_array & routinea);
   void multiple_fork(const ::routine_array & routinea);

   using property_object::defer_fork;

   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread, const ::routine & routine)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }


   inline ::e_status defer_fork(::thread_pointer& pthread, const ::routine & routine);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   template < typename PRED >
   inline ::thread_pointer fork(PRED pred);


   inline ::thread_pointer launch(const ::routine & routine);


   //template < typename METHOD >
   inline ::task_pointer opt_fork(const ::routine & routine)
   {

      auto ptask = ::get_task();

      synchronous_lock synchronouslock(ptask->mutex());

      if (ptask && ptask->m_bIsPredicate)
      {

         routine();

         return ptask;

      }

      return launch(routine);

   }


   //template < typename METHOD >
   //inline ::thread_pointer fork(METHOD method);


   template < typename PRED >
   inline auto new_predicateicate_thread(PRED pred);

   template < typename TYPE >
   inline auto async(void (TYPE:: * pfnMemberProcedure)())
   {

      return fork([this,pfnMemberProcedure]()
         {

            TYPE * ptype = dynamic_cast <TYPE *> (this);

            (ptype->*pfnMemberProcedure)();

         });

   }

   template < typename PRED >
   inline ::thread_pointer predicate_run(bool bSync, PRED pred);

   ::thread_pointer begin(
      ::e_priority epriority = ::priority_normal,
      ::u32 nStackSize = 0,
      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_result get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_result get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());


   //virtual void to_string(string & str) const override;


   virtual ::file_result get_file(const ::payload& varFile, const ::file::e_open & eopen);
   inline ::file_result get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open_binary);
   inline ::file_result get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //::e_status add_update_notification(property * pproperty);
   //::e_status add_update_notification(const ::id & id, bool bCreate = true);
   //::e_status property_notify(const ::id & id, ::matter * pmatter);


//   inline void format_topic_text(const ::string & psz, ...)
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
//   inline void format_topic_text_v(const ::string & psz, va_list valist)
//   {
//
//      string str;
//      str.FormatV(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(::e_status (TYPE:: * pfn)(), ::e_priority epriority = ::priority_normal)
   //{

   //   TYPE * ptype = dynamic_cast <TYPE *>(this);

   //   return ptype->fork([ptype, pfn]()
   //      {

   //         return (ptype->*pfn)();

   //      }, NULL, 0, epriority);

   //}


   template < typename TYPE >
   ::thread_pointer start_below_normal(void (TYPE:: * pfn)())
   {

      return fork(pfn, ::priority_below_normal);

   }


   template < typename TYPE >
   ::e_status __construct(::thread_pointer & p, void (TYPE:: * pfn)(), e_priority epriority);

   template < typename TYPE >
   ::e_status __construct_below_normal(::thread_pointer & p, void (TYPE:: * pfn)());


   template < typename TYPE >
   ::thread_pointer __start_thread(const ::id & id, void(TYPE:: * pfn)(), e_priority epriority = priority_normal);


   virtual matter* get_taskpool_container() override;

   object() : m_pmeta(nullptr) { }
   //object(::object * pobject);
   object(enum_default_initialization) : ::object() {};
   virtual ~object();


#ifdef DEBUG


   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#else


   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


#endif




   inline matter_array* _composite_array() { return m_pcompositea; }
   inline matter_array* _reference_array() { return m_preferencea; }


   inline matter_array& composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   inline matter_array& reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }



   virtual void process_exit_status(const ::e_status& estatus);

   //inline ::object* this const { return this; }
   //virtual ::e_status set_object(::object* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   //inline ::application* application() { return m_papplication; }

   //template < typename TYPE, typename TYPE2 >
   //void __bind(reference < TYPE >& r, TYPE2& t)
   //{

   //   __refr(r, t);

   //}
   ///__bind(referer, referee, ...) __m_bind(referer, (referer)->referee, __VA_ARGS__)



   template < typename BASE_TYPE >
   __pointer(BASE_TYPE) file_as(const ::payload& varFile);


   virtual void add_routine(const ::id& idRoutine, const ::routine& routine);


   virtual void add_each_routine_from(const ::id& idRoutine, ::object* pobjectSource);


   virtual array < ::routine >* routinea(const ::id& idRoutine);


   virtual void call_routine(const ::id& idRoutine);


   inline ::payload context_value(const ::payload& payload);


   virtual void task_erase(::task* ptask) override;


   virtual ::e_status sleep(const ::duration& duration);


   template < typename BASE_TYPE >
   void save_to(const ::payload& varFile, BASE_TYPE* pobject);

   virtual ::e_status initialize(::object * pobject) override;
   virtual ::e_status destroy() override;

   inline const char* topic_text();

   context& __context(const ::payload& payload);

   ::payload __context_value(const ::payload& payload);

   virtual void set_topic_text(const string& str);

   void create_object_meta();

   inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   inline ::object_meta* get_meta() { defer_object_meta(); return m_pmeta; }

   inline ::context* get_context() const { return m_pcontext; }

   inline ::thread* get_thread() const { return m_pthread; }

   inline ::application* get_application() const { return m_papplication; }

   inline ::apex::session* get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papplication; }

   virtual string get_text(const ::payload& payload, const ::id& id) override;

#ifdef DEBUG
   virtual void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual void set_context_app(::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //virtual void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //virtual void set_context_user(::object * puserContext);
#else
   inline void set_context(::context* pcontext);
   inline void set_context_thread(::thread* pthread);
   inline void set_context_app(::application* pappContext);
   inline void set_context_session(::apex::session* psessionContext);
   //inline void set_context_system(::apex::system* psystemContext);
   //inline void set_context_user(::object * puserContext);
#endif


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

   ::object& operator = (const ::payload& payload);




   //static u32 s_thread_proc(void* p);


   virtual void to_string(const string_exchange& str) const override;

   //::image_result create_image();
   //::image_result create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_result get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   //::image_result matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   //template < typename BASE_TYPE >
   //inline __transport(BASE_TYPE) __create();

   //template < typename BASE_TYPE >
   //inline __transport(BASE_TYPE) __id_create(const ::id& id);

   //template < typename TYPE >
   //inline __transport(TYPE) __create_new();

   //inline ::e_status __compose(__composite(::image) & pimage);

   //inline ::e_status __compose(__composite(::image) & pimage, ::image * pimageSource);

   //inline ::e_status __defer_compose(__composite(::image) & pimage) { return !pimage ? __compose(pimage) : ::e_status(::success); }

   // for composition (ownership)

   template < typename BASE_TYPE >
   inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE >
   inline ::e_status __id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id);

   template < typename BASE_TYPE >
   inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource);

   template < typename TYPE >
   inline ::e_status __raw_compose_new(__composite(TYPE)& ptype);

   template < typename TYPE >
   inline ::e_status __compose_new(__composite(TYPE)& ptype);




   template < typename BASE_TYPE >
   inline ::e_status __defer_compose(__composite(BASE_TYPE)& pusermessage) { return !pusermessage ? __compose(pusermessage) : ::e_status(::success); }

   template < typename BASE_TYPE >
   inline ::e_status __defer_id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id) { return !pusermessage ? __id_compose(pusermessage) : ::e_status(::success); }

   template < typename TYPE >
   inline ::e_status __defer_raw_compose_new(__composite(TYPE)& ptype) { return !ptype ? __raw_compose_new(ptype) : ::e_status(::success); }

   template < typename TYPE >
   inline ::e_status __defer_compose_new(__composite(TYPE)& ptype) { return !ptype ? __compose_new(ptype) : ::e_status(::success); }



   //template < typename BASE_TYPE >
   //inline ::e_status __construct(__pointer(BASE_TYPE)& pusermessage);

   //template < typename BASE_TYPE >
   //inline ::e_status __id_construct(__pointer(BASE_TYPE)& pusermessage, const ::id& id);

   //template < typename TYPE >
   //inline ::e_status __construct_new(__pointer(TYPE)& pusermessage);

   template < typename BASE_TYPE >
   inline ::e_status __release(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE >
   inline ::e_status __release(__reference(BASE_TYPE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline ::e_status __release(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual ::e_status add_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual ::e_status add_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   virtual ::e_status release_composite2(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual ::e_status finalize_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual ::e_status release_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   template < typename BASE_TYPE >
   inline ::e_status add_composite(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

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

   virtual void delete_this() override;

   virtual void destruct();

   static void system(const char* pszProjectName);

   virtual ::e_status enable_application_events(bool bEnable = true);

   virtual ::e_status handle_exception(const ::exception::exception& e);

   virtual ::e_status top_handle_exception(const ::exception::exception& e);

   virtual ::e_status process_exception(const ::exception::exception& e);


   ::object* parent_property_set_holder() const override;

   void copy_from(const object& o);


   virtual string get_tag() const;
   virtual bool is_thread() const override;
   virtual bool task_get_run() const;
   virtual bool is_running() const;
   virtual void child_post_quit(const char* pszTag);
   virtual void child_post_quit_and_wait(const char* pszTag, const duration& duration);
   virtual ::e_status finish(::property_object* pcontextobjectFinish = nullptr) override;
   virtual ::e_status set_finish(::property_object* pcontextobjectFinish) override;
   virtual ::e_status set_finish_composites(::property_object* pcontextobjectFinish) override;
   virtual void on_finish() override;


   virtual void defer_update_object_id();
   virtual ::id calc_default_object_id() const;


   virtual void install_message_routing(::channel* pchannel);

   void message_receiver_destruct();

   void _001OnUpdate(::message::message* pmessage);

   virtual ::e_status request_file(const ::payload& varFile);

   virtual ::e_status request_file(const ::payload& varFile, ::payload varQuery);

   virtual ::e_status request(arguments arguments);

   virtual ::e_status do_request(::create* pcreate);

   virtual __pointer(::extended::future < ::conversation >)  message_box(const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual ::e_status message_box_timeout(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual ::e_status message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //virtual ::e_status message_box_timeout(::user::primitive* puserinteractionOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

   virtual void release_references();

   virtual __pointer(::matter) running(const char* pszTag) const;

   virtual bool ___is_reference(::matter* pobject) const;

   virtual bool __is_composite(::matter* pobject) const;

   virtual bool __is_child_task(::task* ptask) const;

   virtual void on_finalize();

   virtual ::e_status call_request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::application* pappOnBehalfOf);
   virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id id = ::id());
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& varFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual ::e_status run() override;

   virtual string lstr(const ::id& id, string strDefault = "");

   virtual string __get_text(string str);

   //template < typename PRED >
   //::image_result get_image(const ::payload & varFile, ::u64 uTrait, PRED pred);

   //virtual ::image_result load_image(const ::payload & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_result load_matter_image(const ::string & pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_result load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_result load_thumbnail(const ::payload & varFile, int w, int h);
   //virtual ::image_result load_thumbnail(const ::string & pszPath);
   //virtual ::image_result load_dib(const ::file::path & pathDib);



   bool IsSerializable() const;


   void start();


   void single_fork(const ::routine_array& routinea);
   void multiple_fork(const ::routine_array& routinea);

   using subject::manager::defer_fork;

   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread, const ::routine& routine)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }


   inline ::e_status defer_fork(::thread_pointer& pthread, const ::routine& routine);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   template < typename PRED >
   inline ::thread_pointer fork(PRED pred);


   //inline ::thread_pointer launch(const ::routine& routine);


   //template < typename METHOD >
   inline ::task_pointer opt_fork(const ::routine& routine)
   {

      auto ptask = ::get_task();

      synchronous_lock synchronouslock(ptask->mutex());

      if (ptask && ptask->m_bIsPredicate)
      {

         routine();

         return ptask;

      }

      return launch(routine);

   }


   //template < typename METHOD >
   //inline ::thread_pointer fork(METHOD method);


   template < typename PRED >
   inline auto new_predicate_task(PRED pred);

   template < typename TYPE >
   inline auto async(void (TYPE::* pfnMemberProcedure)())
   {

      return fork([this, pfnMemberProcedure]()
      {

         TYPE* ptype = dynamic_cast <TYPE*> (this);

         (ptype->*pfnMemberProcedure)();

      });

   }

   template < typename PRED >
   inline ::thread_pointer predicate_run(bool bSync, PRED pred);

   ::thread_pointer begin(
      ::e_priority epriority = ::priority_normal,
      ::u32 nStackSize = 0,
      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_result get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_result get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());


   //virtual void to_string(string & str) const override;


   virtual ::file_result get_file(const ::payload& varFile, const ::file::e_open& eopen);
   inline ::file_result get_reader(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary);
   inline ::file_result get_writer(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //::e_status add_update_notification(property * pproperty);
   //::e_status add_update_notification(const ::id & id, bool bCreate = true);
   //::e_status property_notify(const ::id & id, ::matter * pmatter);


//   inline void format_topic_text(const ::string & psz, ...)
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
//   inline void format_topic_text_v(const ::string & psz, va_list valist)
//   {
//
//      string str;
//      str.FormatV(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(::e_status (TYPE:: * pfn)(), ::e_priority epriority = ::priority_normal)
   //{

   //   TYPE * ptype = dynamic_cast <TYPE *>(this);

   //   return ptype->fork([ptype, pfn]()
   //      {

   //         return (ptype->*pfn)();

   //      }, NULL, 0, epriority);

   //}


   template < typename TYPE >
   ::thread_pointer start_below_normal(void (TYPE::* pfn)())
   {

      return fork(pfn, ::priority_below_normal);

   }


   //template < typename TYPE >
   //::e_status __construct(::thread_pointer& p, void (TYPE::* pfn)(), e_priority epriority);

   template < typename TYPE >
   ::e_status __construct_below_normal(::thread_pointer& p, void (TYPE::* pfn)());


   template < typename TYPE >
   ::thread_pointer __start_thread(const ::id& id, void(TYPE::* pfn)(), e_priority epriority = priority_normal);


   virtual matter* get_taskpool_container() override;


};


#define __make_identifier(PART1, PART2) PART1 ## PART2


#define __defer_fork(ID)                                             \
                                                                     \
do                                                                   \
{                                                                    \
                                                                     \
   auto & pthread = m_pthread ## ID;                                 \
                                                                     \
   if(!pthread)                                                      \
   {                                                                 \
                                                                     \
      __construct(pthread);                                          \
                                                                     \
      pthread->m_pmatter = __routine([this]()                        \
      {                                                              \
                                                                     \
         ID ## ThreadProcedure();                                    \
                                                                     \
      });                                                            \
                                                                     \
   }                                                                 \
                                                                     \
   defer_fork(pthread);                                              \
                                                                     \
} while(false)                                                       \
                                                                     \
   


CLASS_DECL_APEX ::e_status call_sync(const ::routine_array & routinea);



