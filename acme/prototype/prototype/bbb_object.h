// Created on 2021-03-08 by GOD:ThomasBS_-Creature-camilo 09:56 I love you, ThomasBS_!!
#pragma once


enum enum_method : int;
enum enum_future : int;


class CLASS_DECL_APEX object :
   virtual public ::manager
{
protected:


   ::pointer<matter_array>                           m_pcompositea;
   ::pointer<matter_array>                           m_preferencea;



public:

   ::object_meta* m_pmeta;
   long long                                              m_cRun;


   object() : m_pmeta(nullptr) { }
   //object(::particle * pparticle);
   object(enum_default_initialization) : ::object() {};
   virtual ~object();


#ifdef _DEBUG


   virtual long long increment_reference_count() override;
   virtual long long decrement_reference_count() override;
   virtual long long release() override;


#else


   virtual long long increment_reference_count();
   virtual long long decrement_reference_count();
   virtual long long release();


#endif




   inline matter_array* _composite_array() { return m_pcompositea; }
   inline matter_array* _reference_array() { return m_preferencea; }


   inline matter_array& composite_array() { ::__defer_construct_new(m_pcompositea); return *m_pcompositea; }
   inline matter_array& reference_array() { ::__defer_construct_new(m_preferencea); return *m_preferencea; }



   virtual void process_exit_status(const ::e_status & estatus);

   //inline ::object* this const { return this; }
   //virtual void set_object(::object* pparticle) override;

   //inline ::application* application() { return m_papplication; }

   //template < typename TYPE, typename TYPE2 >
   //void __bind(reference < TYPE >& r, TYPE2& t)
   //{

   //   __refr(r, t);

   //}
   ///__bind(referer, referee, ...) __m_bind(referer, (referer)->referee, __VA_ARGS__)



   template < typename BASE_TYPE >
   ::pointer<BASE_TYPE>file_as(const ::payload& payloadFile);


   virtual void add_procedure(const ::atom& idRoutine, const ::procedure & procedure);


   virtual void add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource);


   virtual array < ::procedure >* routinea(const ::atom& idRoutine);


   virtual void call_routine(const ::atom& idRoutine);


   inline ::payload context_value(const ::payload& payload);


   virtual void task_erase(::task* ptask) override;


   virtual void sleep(const class ::time& time);


   template < typename BASE_TYPE >
   void save_to(const ::payload& payloadFile, BASE_TYPE* pparticle);

   virtual void initialize(::particle * pparticle) override;
   virtual void destroy() override;

   inline const char* topic_text();

   context& __context(const ::payload& payload);

   ::payload __context_value(const ::payload& payload);

   virtual void set_topic_text(const ::scoped_string & scopedstr);

   void create_object_meta();

   inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   inline ::object_meta* get_meta() { defer_object_meta(); return m_pmeta; }

   inline ::handler_context* get_context() const { return m_papplication; }

   inline ::thread* get_thread() const { return m_pthread; }

   inline ::application* get_app() const { return m_papplication; }

   inline ::apex::session* get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papplication; }

   virtual string get_text(const ::payload& payload, const ::atom& atom) override;

#ifdef _DEBUG
   virtual void set_context(::handler_context* pcontext);
   virtual void set_context_thread(::thread* pthread);
   virtual void set_context_app(::apex::application* pappContext);
   virtual void set_context_session(::apex::session* psessionContext);
   //virtual void set_context_system(::apex::system* psystemContext);
   //virtual void set_context_user(::object * puserContext);
#else
   inline void set_context(::handler_context* pcontext);
   inline void set_context_thread(::thread* pthread);
   inline void set_context_app(::apex::application* pappContext);
   inline void set_context_session(::apex::session* psessionContext);
   //inline void set_context_system(::apex::system* psystemContext);
   //inline void set_context_user(::object * puserContext);
#endif


   //virtual void set_object(::particle * pparticle) override;


   //inline void defer_set_object(::particle * pparticle);

   virtual void operator()() override;


   inline long long get_ref_count()
   {

      return m_countReference;

   }


   //virtual ::user::interaction_base* get_user_interaction_host();
   //virtual ::user::interaction * get_host_user_interaction();


   virtual void dev_log(string str) const;

   ::object& operator = (const ::payload& payload);




   //static unsigned int s_thread_proc(void* p);


   virtual void to_string(const string_exchange& str) const override;

   //::image::image_pointer create_image();
   //::image::image_pointer create_image(const ::int_size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
   //::image::image_pointer matter_image(const ::scoped_string & scopedstrMatter, bool bCache = true, bool bSync = true);

   //template < typename BASE_TYPE >
   //inline ::pointer<BASE_TYPE>__øcreate();

   //template < typename BASE_TYPE >
   //inline ::pointer<BASE_TYPE>__id_create(const ::atom& atom);

   //template < typename TYPE >
   //inline ::pointer<TYPE>__create_new();

   //inline void __øconstruct(::pointer<::image::image>& pimage);

   //inline void __øconstruct(::pointer<::image::image>& pimage, ::image::image *pimageSource);

   //inline void __defer_construct(::pointer<::image::image>& pimage) { return !pimage ? __øconstruct(pimage) : void(::success); }

   // for composition (ownership)

   template < typename BASE_TYPE >
   inline void __øconstruct(::pointer<BASE_TYPE> pusermessage);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __øconstruct(::pointer<BASE_TYPE> pusermessage, const SOURCE* psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __øconstruct(::pointer<BASE_TYPE> pusermessage, const ::pointer<SOURCE>psource);

   template < typename BASE_TYPE >
   inline void __id_construct(::pointer<BASE_TYPE> pusermessage, const ::atom& atom);

   template < typename BASE_TYPE >
   inline void __raw_construct(::pointer<BASE_TYPE> pusermessage);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __raw_construct(::pointer<BASE_TYPE> pusermessage, const SOURCE* psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __raw_construct(::pointer<BASE_TYPE> pusermessage, const ::pointer<SOURCE>psource);

   template < typename TYPE >
   inline void __raw_construct_new(::pointer<TYPE> ptype);

   template < typename TYPE >
   inline void __construct_new(::pointer<TYPE> ptype);




   template < typename BASE_TYPE >
   inline void __defer_construct(::pointer<BASE_TYPE> pusermessage) { return !pusermessage ? __øconstruct(pusermessage) : void(::success); }

   template < typename BASE_TYPE >
   inline void __defer_id_compose(::pointer<BASE_TYPE> pusermessage, const ::atom& atom) { return !pusermessage ? __id_construct(pusermessage) : void(::success); }

   template < typename TYPE >
   inline void __defer_raw_compose_new(::pointer<TYPE> ptype) { return !ptype ? __raw_construct_new(ptype) : void(::success); }

   template < typename TYPE >
   inline void __defer_construct_new(::pointer<TYPE> ptype) { return !ptype ? __construct_new(ptype) : void(::success); }



   //template < typename BASE_TYPE >
   //inline void __øconstruct(::pointer<BASE_TYPE> pusermessage);

   //template < typename BASE_TYPE >
   //inline void __id_construct(::pointer<BASE_TYPE> pusermessage, const ::atom& atom);

   //template < typename TYPE >
   //inline void __construct_new(::pointer<TYPE> pusermessage);

   template < typename BASE_TYPE >
   inline void __release(::pointer<BASE_TYPE> pcomposite);

   template < typename BASE_TYPE >
   inline void __release(::pointer<BASE_TYPE> preference);

   template < typename SOURCE >
   inline void __release(::pointer<SOURCE> psource);


   virtual void add_composite(::particle * pparticle) override;
   virtual void add_reference(::particle * pparticle) override;


   virtual void release_composite2(::particle * pparticle) override;
   virtual void finalize_composite(::particle * pparticle) override;
   virtual void release_reference(::particle * pparticle) override;


   template < typename BASE_TYPE >
   inline void add_composite(::pointer<BASE_TYPE> pcomposite);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __refer(::pointer<BASE_TYPE> preference, const SOURCE* psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline void __refer(::pointer<BASE_TYPE> preference, const ::primitive::member < SOURCE >& psource);

   template < typename SOURCE >
   inline void add_reference(SOURCE* psource);

   template < typename SOURCE >
   inline void add_reference(::pointer<SOURCE> psource);

   template < typename SOURCE >
   inline void add_reference(::pointer<SOURCE> psource);

   virtual void delete_this() override;

   virtual void destruct();

   static void system(const ::scoped_string & scopedstrProjectName);

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
   virtual void child_post_quit(const ::scoped_string & scopedstrTag);
   virtual void child_post_quit_and_wait(const ::scoped_string & scopedstrTag, const time& time);
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

   virtual pointer< ::extended::future < ::conversation > >  message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok);
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   //virtual void message_box_timeout(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, timeTimeout, emessagebox, process);

   //}

   //virtual void message_box(::user::interaction_base* puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //virtual void message_box_timeout(::user::interaction_base* puserinteractionOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class ::time& timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());

   virtual void release_references();

   virtual ::pointer<::matter>running(const ::scoped_string & scopedstrTag) const;

   virtual bool ___is_reference(::particle * pparticle) const;

   virtual bool __is_composite(::particle * pparticle) const;

   virtual bool __is_child_task(::particle * ptask) const;

   virtual void on_finalize();

   virtual void call_request(::create* pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
   //virtual void on_request(::create* pcreate);
   // 
   virtual void main();
   // 
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom atom = ::atom());
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual void run() override;

   virtual string lstr(const ::atom& atom, string strDefault = "");

   virtual string __get_text(string str);

   //template < typename PRED >
   //::image::image_pointer get_image(const ::payload & payloadFile, unsigned long long uTrait, PRED pred);

   //virtual ::image::image_pointer load_image(const ::payload & payloadFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image::image_pointer load_matter_image(const ::scoped_string & scopedstrMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
   //virtual ::image::image_pointer load_thumbnail(const ::file::path & path);
   //virtual ::image::image_pointer load_dib(const ::file::path & pathDib);



   bool IsSerializable() const;


   void start();


   void single_fork(const ::procedure_array& routinea);
   void multiple_fork(const ::procedure_array& routinea);

   using topic::manager::defer_fork;

   template < typename THREAD >
   inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread, const ::procedure & procedure)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread)
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
   //inline ::pointer<THREAD> start(::pointer<THREAD> pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::thread_pointer fork(PRED pred);
   ::thread_pointer fork(const ::add_procedure & procedure);


   //inline ::thread_pointer launch(const ::procedure & procedure);


   //template < typename METHOD >
   inline ::task_pointer opt_fork(const ::procedure & procedure)
   {

      auto ptask = ::get_task();

      synchronous_lock synchronouslock(ptask->synchronization());

      if (ptask && ptask->m_bIsPredicate)
      {

         routine();

         return ptask;

      }

      return launch(routine);

   }


   //template < typename METHOD >
   //inline ::thread_pointer fork(METHOD method);


   template < typename PREDICATE >
   inline auto new_predicate_task(PREDICATE pred);
   //inline auto new_predicate_task(PRED pred);

   template < typename TYPE >
   inline auto async(void (TYPE::* pfnMemberProcedure)())
   {

      return fork([this, pfnMemberProcedure]()
         {

            TYPE* ptype = dynamic_cast <TYPE*> (this);

            (ptype->*pfnMemberProcedure)();

         });

   }

   //template < typename PRED >
   inline ::thread_pointer predicate_run(bool bSync, const ::add_procedure & procedure);

   ::thread_pointer begin(
      ::enum_priority epriority = ::e_priority_normal,
      unsigned int nStackSize = 0,
      unsigned int dwCreateFlags = 0 ARG_SEC_ATTRS_DEF);

   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());
   //inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());


   //virtual void to_string(string & str) const override;


   virtual ::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen);
   inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary);
   inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //void add_update_notification(property * pproperty);
   //void add_update_notification(const ::atom & atom, bool bCreate = true);
   //void property_notify(const ::atom & atom, ::matter * pmatter);


//   inline void format_topic_text(const ::scoped_string & scopedstr, ...)
//   {
//
//      va_list valist;
//      va_start(valist, psz);
//      format_topic_text_v(scopedstr, valist);
//      va_end(valist);
//
//   }
//
//
//   inline void format_topic_text_v(const ::scoped_string & scopedstr, va_list valist)
//   {
//
//      string str;
//      str.formatf_arguments(scopedstr, valist);
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
   //void __øconstruct(::thread_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

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
      __øconstruct(pthread);                                          \
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





