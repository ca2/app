// Created on 2021-03-08 by GOD:ThomasBS_-Creature-camilo 09:56 I love you, ThomasBS_!!
#pragma once


enum enum_method : ::i32;
enum enum_future : ::i32;

namespace user
{

   class primitive;

}


class CLASS_DECL_APEX object :
   virtual public ::manager
{
protected:


   __pointer(matter_array)                            m_pcompositea;
   __pointer(matter_array)                            m_preferencea;



public:

   ::object_meta* m_pmeta;
   ::i64                                              m_cRun;


   object() : m_pmeta(nullptr) { }
   //object(::object * pobject);
   object(enum_default_initialization) : ::object() {};
   virtual ~object();


#ifdef _DEBUG


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



   virtual void process_exit_status(const ::e_status & estatus);

   //inline ::object* this const { return this; }
   //virtual void set_object(::object* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   //inline ::application* application() { return m_papp; }

   //template < typename TYPE, typename TYPE2 >
   //void __bind(reference < TYPE >& r, TYPE2& t)
   //{

   //   __refr(r, t);

   //}
   ///__bind(referer, referee, ...) __m_bind(referer, (referer)->referee, __VA_ARGS__)



   template < typename BASE_TYPE >
   __pointer(BASE_TYPE) file_as(const ::payload& payloadFile);


   virtual void add_procedure(const ::atom& idRoutine, const ::procedure & procedure);


   virtual void add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource);


   virtual array < ::procedure >* routinea(const ::atom& idRoutine);


   virtual void call_routine(const ::atom& idRoutine);


   inline ::payload context_value(const ::payload& payload);


   virtual void task_erase(::task* ptask) override;


   virtual void sleep(const ::duration& duration);


   template < typename BASE_TYPE >
   void save_to(const ::payload& payloadFile, BASE_TYPE* pobject);

   virtual void initialize(::object * pobject) override;
   virtual void destroy() override;

   inline const char* topic_text();

   context& __context(const ::payload& payload);

   ::payload __context_value(const ::payload& payload);

   virtual void set_topic_text(const string& str);

   void create_object_meta();

   inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   inline ::object_meta* get_meta() { defer_object_meta(); return m_pmeta; }

   inline ::context* get_context() const { return m_pcontext; }

   inline ::thread* get_thread() const { return m_pthread; }

   inline ::application* get_app() const { return m_papp; }

   inline ::apex::session* get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papp; }

   virtual string get_text(const ::payload& payload, const ::atom& atom) override;

#ifdef _DEBUG
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

   virtual void operator()() override;


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

   //::image_pointer create_image();
   //::image_pointer create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
   //::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   //template < typename BASE_TYPE >
   //inline __pointer(BASE_TYPE) __create();

   //template < typename BASE_TYPE >
   //inline __pointer(BASE_TYPE) __id_create(const ::atom& atom);

   //template < typename TYPE >
   //inline __pointer(TYPE) __create_new();

   //inline void __compose(__composite(::image) & pimage);

   //inline void __compose(__composite(::image) & pimage, ::image * pimageSource);

   //inline void __defer_compose(__composite(::image) & pimage) { return !pimage ? __compose(pimage) : void(::success); }

   // for composition (ownership)

   template < typename BASE_TYPE >
   inline void __compose(__composite(BASE_TYPE)& pusermessage);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE >
   inline void __id_compose(__composite(BASE_TYPE)& pusermessage, const ::atom& atom);

   template < typename BASE_TYPE >
   inline void __raw_compose(__composite(BASE_TYPE)& pusermessage);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __raw_compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __raw_compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource);

   template < typename TYPE >
   inline void __raw_compose_new(__composite(TYPE)& ptype);

   template < typename TYPE >
   inline void __compose_new(__composite(TYPE)& ptype);




   template < typename BASE_TYPE >
   inline void __defer_compose(__composite(BASE_TYPE)& pusermessage) { return !pusermessage ? __compose(pusermessage) : void(::success); }

   template < typename BASE_TYPE >
   inline void __defer_id_compose(__composite(BASE_TYPE)& pusermessage, const ::atom& atom) { return !pusermessage ? __id_compose(pusermessage) : void(::success); }

   template < typename TYPE >
   inline void __defer_raw_compose_new(__composite(TYPE)& ptype) { return !ptype ? __raw_compose_new(ptype) : void(::success); }

   template < typename TYPE >
   inline void __defer_compose_new(__composite(TYPE)& ptype) { return !ptype ? __compose_new(ptype) : void(::success); }



   //template < typename BASE_TYPE >
   //inline void __construct(__pointer(BASE_TYPE)& pusermessage);

   //template < typename BASE_TYPE >
   //inline void __id_construct(__pointer(BASE_TYPE)& pusermessage, const ::atom& atom);

   //template < typename TYPE >
   //inline void __construct_new(__pointer(TYPE)& pusermessage);

   template < typename BASE_TYPE >
   inline void __release(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE >
   inline void __release(__reference(BASE_TYPE)& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline void __release(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual void add_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual void add_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   virtual void release_composite2(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual void finalize_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   virtual void release_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   template < typename BASE_TYPE >
   inline void add_composite(__composite(BASE_TYPE)& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __refer(__reference(BASE_TYPE)& preference, const ::primitive::member < SOURCE >& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline void add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline void add_reference(__pointer(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   template < typename SOURCE >
   inline void add_reference(__reference(SOURCE)& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   virtual void delete_this() override;

   virtual void destruct();

   static void system(const char* pszProjectName);

   virtual void enable_application_events(bool bEnable = true);

   virtual void handle_exception(const ::exception& e);

   virtual void top_handle_exception(const ::exception& e);

   virtual void process_exception(const ::exception& e);


   ::object* parent_property_set_holder() const override;

   void copy_from(const object& o);


   virtual string get_tag() const;
   virtual bool is_thread() const override;
   virtual bool task_get_run() const;
   virtual bool is_running() const;
   virtual void child_post_quit(const char* pszTag);
   virtual void child_post_quit_and_wait(const char* pszTag, const duration& duration);
   virtual void finish(::property_object* pcontextobjectFinish = nullptr) override;
   virtual void set_finish(::property_object* pcontextobjectFinish) override;
   virtual void set_finish_composites(::property_object* pcontextobjectFinish) override;
   virtual void on_finish() override;


   virtual void defer_update_object_id();
   virtual ::atom calc_default_object_id() const;


   virtual void install_message_routing(::channel* pchannel);

   void message_receiver_destruct();

   void _001OnUpdate(::message::message* pmessage);

   virtual void request_file(const ::payload& payloadFile);

   virtual void request_file(const ::payload& payloadFile, ::payload varQuery);

   virtual void request(arguments arguments);

   virtual void do_request(::create* pcreate);

   virtual __pointer(::extended::future < ::conversation >)  message_box(const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual void message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual void message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //virtual void message_box_timeout(::user::primitive* puserinteractionOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

   virtual void release_references();

   virtual __pointer(::matter) running(const char* pszTag) const;

   virtual bool ___is_reference(::matter* pobject) const;

   virtual bool __is_composite(::matter* pobject) const;

   virtual bool __is_child_task(::task* ptask) const;

   virtual void on_finalize();

   virtual void call_request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::application* pappOnBehalfOf);
   virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& payloadFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom atom = ::atom());
   //virtual ::user::document* open_document_file(::application* pappOnBehalfOf, const ::payload& payloadFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual void run() override;

   virtual string lstr(const ::atom& atom, string strDefault = "");

   virtual string __get_text(string str);

   //template < typename PRED >
   //::image_pointer get_image(const ::payload & payloadFile, ::u64 uTrait, PRED pred);

   //virtual ::image_pointer load_image(const ::payload & payloadFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_pointer load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
   //virtual ::image_pointer load_thumbnail(const char * pszPath);
   //virtual ::image_pointer load_dib(const ::file::path & pathDib);



   bool IsSerializable() const;


   void start();


   void single_fork(const ::procedure_array& routinea);
   void multiple_fork(const ::procedure_array& routinea);

   using topic::manager::defer_fork;

   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread, const ::procedure & procedure)
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


   inline void defer_fork(::thread_pointer& pthread, const ::procedure & procedure);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   template < typename PRED >
   inline ::thread_pointer fork(PRED pred);


   //inline ::thread_pointer launch(const ::procedure & procedure);


   //template < typename METHOD >
   inline ::task_pointer opt_fork(const ::procedure & procedure)
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
      ::enum_priority epriority = ::e_priority_normal,
      ::u32 nStackSize = 0,
      u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_pointer get_reader(const ::payload& payloadFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_pointer get_writer(const ::payload& payloadFile, const ::file::e_open & eopen = ::file::e_open());


   //virtual void to_string(string & str) const override;


   virtual ::file_pointer get_file(const ::payload& payloadFile, const ::file::e_open& eopen);
   inline ::file_pointer get_reader(const ::payload& payloadFile, const ::file::e_open& eopen = ::file::e_open_binary);
   inline ::file_pointer get_writer(const ::payload& payloadFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //void add_update_notification(property * pproperty);
   //void add_update_notification(const ::atom & atom, bool bCreate = true);
   //void property_notify(const ::atom & atom, ::matter * pmatter);


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
//      str.format_arguments(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(void (TYPE:: * pfn)(), ::enum_priority epriority = ::e_priority_normal)
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

      return fork(pfn, ::e_priority_below_normal);

   }


   //template < typename TYPE >
   //void __construct(::thread_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   template < typename TYPE >
   void __construct_below_normal(::thread_pointer& p, void (TYPE::* pfn)());


   template < typename TYPE >
   ::thread_pointer __start_thread(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);


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



CLASS_DECL_APEXvoid call_sync(const ::procedure_array& routinea);





