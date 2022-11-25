#pragma once


#include "object_meta.h"
#include "property_object.h"
#include "acme/parallelization/create_task_attributes.h"
#include  "acme/primitive/collection/pointer_array.h"
//#include "acme/primitive/primitive/function.h"


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
   //virtual public material_object
   virtual public property_object
{
protected:


   bool                                            m_bCheckingChildrenTask;
   ::object *                                      m_pobjectParentTask;
   ::pointer < ::pointer_array < ::particle > >    m_pparticleaChildrenTask;
   //::pointer < ::procedure_map >                   m_pmapPropertyProcedure;


public:


   //::task_pointer                                 m_pthread;
   //::pointer<::apex::application>                           m_pacmeapplication;
   //::pointer<::apex::session>                         m_psession;
   //::pointer<::acme::system>                          acmesystem();
   //::acme::context *                                     m_pcontext;


   //pointer< pointer_array < ::object > >                m_pobjecta;
   //pointer< pointer_array < ::element > >                  m_pcompositea;
   //pointer< pointer_array < ::element > >                  m_preferencea;



   ::object_meta *                                       m_pmeta;
   //::i64                                              m_cRun;


   //object() : m_pmeta(nullptr) { }
   object():m_pmeta(nullptr) { m_pobjectParentTask = nullptr;
   //   m_pcontext = nullptr;
   }
   //object(::particle * pparticle);
   //object(const ::atom & atom):property_object(atom){ m_pobjectParentTask = nullptr; m_pcontext = nullptr; }
   //object(enum_default_initialization) : ::object() {  };
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


   //inline ::acme::system* get_system() const;

   //inline element_array * _composite_array() { return m_pcompositea; }
   //inline element_array * _reference_array() { return m_preferencea; }


   //inline element_array & composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   //inline element_array & reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }

   //virtual void add_object(::particle * pparticle);
   //virtual void on_delete_object(::particle * pparticle);

   //virtual void enumerate_composite(element_array& a);
   //virtual void enumerate_reference(element_array& a);

   //virtual void process_exit_status(const ::e_status & estatus);

   //inline ::object* this const { return this; }
   //virtual void set_object(::object* pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   //inline ::application* application() { return m_pacmeapplication; }


   //inline ::application* get_app() { return _get_application(); }


   template < typename BASE_TYPE >
   ::pointer<BASE_TYPE>file_as(const ::payload& payloadFile);


   virtual void add_procedure(const ::atom& idRoutine, const ::procedure & procedure);


   virtual void add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource);


   virtual ::procedure_array * procedure_array(const ::atom& idRoutine);

   template < typename ROUTINE_RUNNER_OBJECT, typename ROUTINE_RUNNER_METHOD >
   void for_routines_with_id(const ::atom & atom, ROUTINE_RUNNER_OBJECT proutinerunner, ROUTINE_RUNNER_METHOD routine_runner_method)
   {

      if (::is_null(m_pmeta) || m_pmeta->m_mapRoutine.is_empty())
      {

         return;

      }

      auto pprocedurea = this->procedure_array(atom);

      if (::is_null(pprocedurea))
      {

         //throw_exception(error_not_found);

         return;

      }

      for (auto routine : *pprocedurea)
      {

         (proutinerunner->*routine_runner_method)(routine);

      }

   }

   
   virtual void call_routine2(const ::procedure & procedure);


   inline void call_procedures(const ::atom & atom)
   {

      return for_routines_with_id(atom, this, &object::call_routine2);

   }


   inline void branch_procedures(const ::atom & atom)
   {

      return for_routines_with_id(atom, this, &object::post_procedure);

   }


   inline void send_routines_with_id(const ::atom & atom)
   {

      return for_routines_with_id(atom, this, &object::send_procedure);

   }



   //inline ::payload context_value(const ::payload& payload);


   virtual ::text::text __text(const ::atom& atom);


   virtual void task_erase(::task* ptask) override;


   virtual void sleep(const ::duration& duration);


   template < typename BASE_TYPE >
   void save_to(const ::payload& payloadFile, BASE_TYPE* pparticle);

   
   virtual void initialize(::particle * pparticle) override;
   virtual void set_finish() override;
   //virtual void destroy() override;

   virtual void add_task(::object* pobjectTask);
   virtual void erase_task(::object* pobjectTask);
   virtual void transfer_tasks_from(::object * ptask);
   virtual bool is_ascendant_task(::object * ptaskCandidateAscendant) const;

//   void destroy() override;

   //virtual void set_finish();


   virtual bool is_thread() const override;
   virtual bool task_get_run() const;
   virtual bool is_running() const;
   //virtual void child_post_quit(const char* pszTag);
   //virtual void child_post_quit_and_wait(const char* pszTag, const duration& duration);


   virtual void post_procedure(const ::procedure & procedure);
   virtual void send_procedure(const ::procedure& procedure);


   //void destroy() override;

   //virtual void finish(::property_object* pcontextobjectRootFinishingInitiator = nullptr) override;
   //virtual void set_finish(::property_object* pcontextobjectRootFinishingInitiator) override;
   //virtual void set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;
   //virtual void on_finish() override;

   virtual bool check_tasks_finished();

   void destroy() override;

   virtual void on_destroy();

   virtual void destroy_tasks();

   //void destroy_composites() override;

   //void release_references();



   //virtual void on_initialize_particle() override;


   //inline const char* topic_text();

   //context& __context(const ::payload& payload);

   //::payload __context_value(const ::payload& payload);

   //virtual void set_topic_text(const string& str);

   void create_object_meta();

   inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }

   inline ::acme::context* get_context() const { return m_pcontext; }

   //inline ::thread* get_thread() const { return m_pthread; }

   //inline ::application* get_app() const { return m_pacmeapplication; }

   //inline ::apex::session* get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_pacmeapplication; }

   //virtual string get_text(const ::payload& payload, const ::atom& atom) override;

   //#ifdef _DEBUG
   //   virtual void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   virtual void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   virtual void set_context_app(::apex::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   virtual void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   //virtual void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //   //virtual void set_context_user(::object * puserContext);
   //#else
   //   inline void set_context(::context* pcontext);
   //   inline void set_context_thread(::thread* pthread);
   //   inline void set_context_app(::apex::application* pappContext);
   //   inline void set_context_session(::apex::session* psessionContext);
   //   //inline void set_context_system(::apex::system* psystemContext);
   //   //inline void set_context_user(::object * puserContext);
   //#endif


      //virtual void set_object(::particle * pparticle) override;


      //inline void defer_set_object(::particle * pparticle);

   void call_run() override;


   inline i64 get_ref_count()
   {

      return m_countReference;

   }

   ::extended_topic_pointer create_extended_topic(const ::atom & atom) override;

   virtual void dev_log(string str);

//   ::object& operator = (const ::payload& payload);




   //static u32 s_thread_proc(void* p);


   //virtual void to_string(const string_exchange & str) const override;

   //::image_pointer create_image();
   //::image_pointer create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
   //::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);


   //template < typename BASE_TYPE >
   //inline void __release(::pointer<BASE_TYPE>& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline void __release(::pointer<BASE_TYPE>& preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void release_reference(::pointer<SOURCE>& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   //virtual void add_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual void add_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //virtual void release_composite2(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual void finalize_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual void release_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //template < typename BASE_TYPE >
   //inline void add_composite(::pointer<BASE_TYPE>& pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE>& preference, const SOURCE * psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE>& preference, const ::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE>& preference, const ::primitive::member < SOURCE > & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   virtual void delete_this() override;

   virtual void destruct();

   static void system(const ::string & pszProjectName);

   //virtual void enable_application_events(bool bEnable = true);

   virtual void handle_exception(const ::exception& e) override;

   virtual void top_handle_exception(const ::exception& e);

   virtual void process_exception(const ::exception& e);


   ::property_object* parent_property_set_holder() const override;

   //void copy_from(const object& o);


   virtual string get_tag() const;


   virtual void defer_update_object_id();
   virtual ::atom calc_default_object_id() const;


   void install_message_routing(::channel* pchannel) override;

   void message_receiver_destruct();

   void _001OnUpdate(::message::message* pmessage);

   //virtual void request_file(const ::payload& payloadFile);

   //virtual void request_file(const ::payload& payloadFile, ::payload varQuery);

   //virtual void request(arguments arguments);

   //virtual void do_request(::create* pcreate);

   virtual void do_request(::create* pcreate);

   //virtual pointer< ::extended::sequence < ::conversation > >  message_box(::user::interaction * puserinteraction, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual void message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual void message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //virtual void message_box_timeout(::user::primitive* puserinteractionOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());

   //virtual void release_references();

   //virtual ::pointer<::element>running(const char* pszTag) const;

   //virtual bool ___is_reference(::particle * pparticle) const;

   //virtual bool __is_composite(::particle * pparticle) const;

   virtual bool __is_child_task(::particle * pparticle) const;

   //virtual void on_finalize();

   virtual void call_request(::create* pcreate);


   virtual void request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
   virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom atom = ::atom());
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual void run() override;

   //virtual string lstr(const ::atom& atom, string strDefault = "");

   //virtual string __get_text(string str);

   //template < typename PRED >
   //::image_pointer get_image(const ::payload & payloadFile, ::u64 uTrait, PRED pred);

   //virtual ::image_pointer load_image(const ::payload & payloadFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_pointer load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
   //virtual ::image_pointer load_thumbnail(const char * pszPath);
   //virtual ::image_pointer load_dib(const ::file::path & pathDib);



   bool IsSerializable() const;

   //using property_object::branch;

   void branch(const ::procedure_array& routinea);
   void branch_each(const ::procedure_array& routinea);

   //using property_object::defer_branch;

   template < typename TASK >
   inline ::pointer<TASK>& defer_branch(::pointer<TASK> ptask, const ::procedure & procedure)
   {

      if (ptask && ptask->is_running())
      {

         return ptask;

      }

      __defer_construct_new(ptask);

      ptask->m_procedure = procedure;

      ptask->branch();

      return ptask;

   }


   template < typename THREAD >
   inline ::pointer<THREAD> defer_branch(::pointer<THREAD>pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }


   void defer_branch(::task_pointer& ptask, const ::procedure & procedure);


   //template < typename THREAD >
   //inline ::pointer<THREAD> start(::pointer<THREAD> pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   ::pointer<task>fork(const ::procedure & procedure,
      const ::particle_array & elementaHold = {},
      const create_task_attributes & createtaskattributes = nullptr);


   //inline ::task_pointer launch(const ::procedure & procedure);


   //template < typename METHOD >
   //inline ::task_pointer opt_fork(const ::procedure & procedure);


   //template < typename METHOD >
   //inline ::task_pointer fork(METHOD method);


//   template < typename PRED >
   //inline auto new_predicateicate_thread(PRED pred);

   //template < typename TYPE >
   //inline ::pointer<task>branch_procedure(void (TYPE::* pfnMemberProcedure)(),
   //   ::enum_priority epriority = e_priority_normal,
   //   ::u32 nStackSize = 0,
   //   ::u32 dwCreateFlags = 0 ARG_SEC_ATTRS_DEF)
   //{

   //   return fork([this, pfnMemberProcedure]()
   //   {

   //      TYPE* ptype = dynamic_cast <TYPE*> (this);

   //      (ptype->*pfnMemberProcedure)();

   //   },
   //      epriority,
   //      nStackSize,
   //      dwCreateFlags ADD_PASS_SEC_ATTRS);


   //}


   virtual ::pointer<::task>branch_procedure(const ::procedure & procedure, const create_task_attributes & createtaskattributes = nullptr);

   virtual ::pointer<::task>branch_procedure_synchronously(const ::procedure & procedure, const create_task_attributes & createtaskattributes = nullptr);

   virtual ::task_pointer run_procedure(bool bSyncronously, const ::procedure & procedure);

   //using property_object::branch;

   virtual ::pointer<::task> branch(const create_task_attributes & createtaskattributes = nullptr);

   virtual ::pointer<::task> branch_synchronously(const create_task_attributes & createtaskattributes = nullptr);

   //::task_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif




   //void add_update_notification(property * pproperty);
   //void add_update_notification(const ::atom & atom, bool bCreate = true);
   //void property_notify(const ::atom & atom, ::particle * pparticle);


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
   ::task_pointer branch_below_normal(void (TYPE::* pfn)())
   {

      return branch(pfn, ::e_priority_below_normal);

   }


   //template < typename TYPE >
   //void __construct(::task_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   //template < typename TYPE >
   //void __construct_below_normal(::task_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::task_pointer defer_branch(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);

   ::task_pointer defer_branch(const ::atom& atom, const ::procedure & procedure, enum_priority epriority = e_priority_normal);

   virtual ::particle * get_taskpool_container() override;

   //object() : m_pmeta(nullptr) { }
   //object(::particle * pparticle);
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




   //inline element_array* _composite_array() { return m_pcompositea; }
   //inline element_array* _reference_array() { return m_preferencea; }


   //inline element_array& composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   //inline element_array& reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }



   //virtual void process_exit_status(const ::e_status & estatus);

   //inline ::object* this const { return this; }
   //virtual void set_object(::object* pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;

   //inline ::application* application() { return m_pacmeapplication; }

   //template < typename TYPE, typename TYPE2 >
   //void __bind(reference < TYPE >& r, TYPE2& t)
   //{

   //   __refr(r, t);

   //}
   ///__bind(referer, referee, ...) __m_bind(referer, (referer)->referee, __VA_ARGS__)



   //template < typename BASE_TYPE >
   //::pointer<BASE_TYPE>file_as(const ::payload& payloadFile);


   //virtual void add_procedure(const ::atom& idRoutine, const ::procedure & procedure);


   //virtual void add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource);


   //virtual array < ::procedure >* routinea(const ::atom& idRoutine);


   //virtual void call_routine(const ::atom& idRoutine);


   //inline ::payload context_value(const ::payload& payload);


   //virtual void task_erase(::task* ptask) override;


   //virtual void sleep(const ::duration& duration);


   //template < typename BASE_TYPE >
   //void save_to(const ::payload& payloadFile, BASE_TYPE* pparticle);

   //virtual void initialize(::particle * pparticle) override;
   //virtual void destroy() override;

   //inline const char* topic_text();

   //context& __context(const ::payload& payload);

   //::payload __context_value(const ::payload& payload);

   //virtual void set_topic_text(const string& str);

   //void create_object_meta();

   //inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   //inline ::object_meta* get_meta() { defer_object_meta(); return m_pmeta; }

   //inline ::context* get_context() const { return m_pcontext; }

   ::acme::application * get_app() const;

   ::apex::session * get_session() const;

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_pacmeapplication; }

   //virtual string get_text(const ::payload& payload, const ::atom& atom) override;

//#ifdef _DEBUG
//   virtual void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void set_context_app(::apex::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   //virtual void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   //virtual void set_context_user(::object * puserContext);
//#else
//   inline void set_context(::context* pcontext);
//   inline void set_context_thread(::thread* pthread);
//   inline void set_context_app(::apex::application* pappContext);
//   inline void set_context_session(::apex::session* psessionContext);
//   //inline void set_context_system(::apex::system* psystemContext);
//   //inline void set_context_user(::object * puserContext);
//#endif


   //virtual void set_object(::particle * pparticle) override;


   //inline void defer_set_object(::particle * pparticle);

   //virtual void operator()() override;


   //inline i64 get_ref_count()
   //{

   //   return m_countReference;

   //}


   //virtual ::user::primitive* get_user_interaction_host();
   //virtual ::user::interaction * get_host_window();


   //virtual void dev_log(string str) const;

   ::object& operator = (const ::payload& payload);




   //static u32 s_thread_proc(void* p);


   virtual string as_string() const;


   // for composition (ownership)

   //template < typename BASE_TYPE >
   //inline void __construct(::pointer<BASE_TYPE> ptype);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __construct(::pointer<BASE_TYPE> ptype, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __construct(::pointer<BASE_TYPE> ptype, const ::pointer<SOURCE>psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __construct(::pointer<BASE_TYPE> ptype, const ptr < SOURCE > & psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline void __id_construct(::pointer<BASE_TYPE> ptype, const ::atom& atom);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __raw_construct(::pointer<BASE_TYPE> ptype, const SOURCE* psource);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __raw_construct(::pointer<BASE_TYPE> ptype, const ::pointer<SOURCE>psource);

   //template < typename TYPE >
   //inline void __raw_construct_new(::pointer<TYPE> ptype);

   //template < typename TYPE >
   //inline void __construct_new(::pointer<TYPE> ptype);




   //template < typename BASE_TYPE >
   //inline void __defer_construct(::pointer<BASE_TYPE> ptype) { return !ptype ? __construct(ptype) : void(::success); }

   //template < typename BASE_TYPE >
   //inline void __defer_id_compose(::pointer<BASE_TYPE> ptype, const ::atom& atom) { return !ptype ? __id_construct(ptype) : void(::success); }

   //template < typename TYPE >
   //inline void __defer_raw_compose_new(::pointer<TYPE> ptype) { return !ptype ? __raw_construct_new(ptype) : void(::success); }

   //template < typename TYPE >
   //inline void __defer_construct_new(::pointer<TYPE> ptype) { return !ptype ? __construct_new(ptype) : void(::success); }



   //template < typename BASE_TYPE >
   //inline void __construct(::pointer<BASE_TYPE> ptype);

   //template < typename BASE_TYPE >
   //inline void __id_construct(::pointer<BASE_TYPE> ptype, const ::atom& atom);

   //template < typename TYPE >
   //inline void __construct_new(::pointer<TYPE> ptype);

   //template < typename BASE_TYPE >
   //inline void __release(::pointer<BASE_TYPE> pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline void __release(::pointer<BASE_TYPE> preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void __release(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   //virtual void add_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual void add_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //virtual void release_composite2(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual void finalize_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;
   //virtual void release_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) override;


   //template < typename BASE_TYPE >
   //inline void add_composite(::pointer<BASE_TYPE> pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE> preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE> preference, const ::primitive::member < SOURCE >& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __defer_refer(::pointer<BASE_TYPE> preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __defer_refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //virtual void delete_this() override;

   //virtual void destruct();

   //static void system(const char* pszProjectName);

   //virtual void enable_application_events(bool bEnable = true);

   //virtual void handle_exception(const ::exception& e);

   //virtual void top_handle_exception(const ::exception& e);

   //virtual void process_exception(const ::exception& e);


   //::object* parent_property_set_holder() const override;

   //void copy_from(const object& o);


   //virtual string get_tag() const;
   //virtual bool is_thread() const override;
   //virtual bool task_get_run() const;
   //virtual bool is_running() const;
   //virtual void child_post_quit(const char* pszTag);
   //virtual void child_post_quit_and_wait(const char* pszTag, const duration& duration);
   //virtual void finish(::property_object* pcontextobjectFinish = nullptr) override;
   //virtual void set_finish(::property_object* pcontextobjectFinish) override;
   //virtual void set_finish_composites(::property_object* pcontextobjectFinish) override;
   //virtual void on_finish() override;


   //virtual void defer_update_object_id();
   //virtual ::atom calc_default_object_id() const;


   //virtual void install_message_routing(::channel* pchannel);

   //void message_receiver_destruct();

   //void _001OnUpdate(::message::message* pmessage);

   //virtual void request_file(const ::payload& payloadFile);

   //virtual void request_file(const ::payload& payloadFile, ::payload varQuery);

   //virtual void request(arguments arguments);

   //virtual void do_request(::create* pcreate);

   //virtual pointer< ::extended::future < ::conversation > >  message_box(const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual void message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   //virtual void message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //virtual void message_box_timeout(::user::primitive* puserinteractionOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());

   //virtual void release_references();

   //virtual ::pointer<::element>running(const ::string & pszTag) const;

   //virtual bool ___is_reference(::particle * pparticle) const;

   //virtual bool __is_composite(::particle * pparticle) const;

   //virtual bool __is_child_task(::task* ptask) const;

   //virtual void on_finalize();

   //virtual void call_request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
   //virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom atom = ::atom());
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   //virtual void run() override;

   //virtual string lstr(const ::atom& atom, string strDefault = "");

   //virtual string __get_text(string str);

   //template < typename PRED >
   //::image_pointer get_image(const ::payload & payloadFile, ::u64 uTrait, PRED pred);

   //virtual ::image_pointer load_image(const ::payload & payloadFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_pointer load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
   //virtual ::image_pointer load_thumbnail(const char * pszPath);
   //virtual ::image_pointer load_dib(const ::file::path & pathDib);



   //bool IsSerializable() const;


   //void start();


   void single_fork(const ::procedure_array& routinea);
   void multiple_fork(const ::procedure_array& routinea);

   //using topic::manager::defer_fork;

   //template < typename THREAD >
   //inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread, const ::procedure & procedure)
   //{

   //   if (pthread && pthread->is_running())
   //   {

   //      return pthread;

   //   }

   //   pthread->start(routine);

   //   return pthread;

   //}


   //template < typename THREAD >
   //inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread)
   //{

   //   if (pthread && pthread->is_running())
   //   {

   //      return pthread;

   //   }

   //   pthread->begin_thread();

   //   return pthread;

   //}


//   inline void defer_fork(::task_pointer& pthread, const ::procedure & procedure);


   //template < typename THREAD >
   //inline ::pointer<THREAD> start(::pointer<THREAD> pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::task_pointer fork(PRED pred);


   //inline ::task_pointer launch(const ::procedure & procedure);


   //template < typename METHOD >
   //inline ::task_pointer opt_fork(const ::procedure & procedure)
   //{

   //   auto ptask = ::get_task();

   //   synchronous_lock synchronouslock(ptask->synchronization());

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

   //inline ::file_pointer get_reader(const ::payload& payloadFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_pointer get_writer(const ::payload& payloadFile, const ::file::e_open & eopen = ::file::e_open());


   //virtual void to_string(string & str) const override;


   //virtual ::file_pointer get_file(const ::payload& payloadFile, const ::file::e_open& eopen);
   //inline ::file_pointer get_reader(const ::payload& payloadFile, const ::file::e_open& eopen = ::file::e_open_binary);
   //inline ::file_pointer get_writer(const ::payload& payloadFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //void add_update_notification(property * pproperty);
   //void add_update_notification(const ::atom & atom, bool bCreate = true);
   //void property_notify(const ::atom & atom, ::particle * pparticle);


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


   //template < typename TYPE >
   //::task_pointer start_below_normal(void (TYPE::* pfn)())
   //{

   //   return fork(pfn, ::e_priority_below_normal);

   //}


   //template < typename TYPE >
   //void __construct(::task_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   //template < typename TYPE >
   //void __construct_below_normal(::task_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::task_pointer __start_thread(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);


   //virtual element* get_taskpool_container() override;



};




#define __make_identifier(PART1, PART2) PART1 ## PART2


#define __defer_branch(procedure) defer_branch(m_p ## procedure, [this](){procedure();})


//CLASS_DECL_ACME void call_sync(const ::procedure_array& routinea);











#define __PROPERTIES(xxx) \
class __ ## xxx ## _properties : \
   public property_set \
{ \
public: \


#define __PROPERTY(type, name, ID) type & name = reference(ID)



#define __END_PROPERTIES(xxx) }; \
__ ## xxx ## _properties &  xxx ## _properties() {return *m_p ## xxx ## properties;} \
const __ ## xxx ## _properties & xxx ## _properties() const {return *m_p ## xxx ## properties;} \
inline void create_ ## xxx ## _properties() \
{ \
   if(::is_set(m_p ## xxx ## properties)) return; \
   m_p ## xxx ## properties = __new(__ ## xxx ## _properties()); \
   m_ppropertyset = m_p ## xxx ## properties; \
} \
::pointer<__ ## xxx ## _properties> m_p ## xxx ## properties














#include "acme/primitive/primitive/factory.h"


