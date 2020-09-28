#pragma once


enum enum_method : ::i32;
enum enum_future : ::i32;

namespace user
{

   class primitive;

}

class CLASS_DECL_APEX object :
   virtual public context_object
{
protected:


   __pointer(::thread)                                m_pthreadContext;
   __pointer(::apex::application)                     m_pappContext;
   __pointer(::apex::session)                         m_psessionContext;
   __pointer(::apex::system)                          m_psystemContext;
   //__pointer(::object)                                m_puserContext;
   __pointer(::context)                               m_pcontextContext;
   __pointer(object_addra)                            m_pcompositea;
   __pointer(object_addra)                            m_preferencea;


public:

   //void *                                             m_pObjectThis;
   ::object_meta *                                    m_pmeta;
   ::i64                                              m_cRun;


   object() : m_pmeta(nullptr) { set_layer(0, this); }
   object(::layered * pobjectContext);
   object(e_default_init) : ::object() {};
   virtual ~object();


#ifdef DEBUG
   virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
   virtual i64 release(OBJ_REF_DBG_PARAMS) override;
#else
   virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 release(OBJ_REF_DBG_PARAMS);
#endif


   inline ::apex::application * get_context_application() { return m_pappContext.m_p; }


   template < typename BASE_TYPE >
   __pointer(BASE_TYPE) file_as(const var & varFile);


   virtual void add(const ::method & method);
   virtual void add(const ::future & future);

   virtual void add_methods_from(const ::id & id, ::object * pobjectSource);
   virtual void add_futures_from(const ::id & id, ::object * pobjectSource);

   virtual array < ::method > * methods(const ::id & idMethod);
   virtual array < ::future > * futures(const ::id & idFuture);

   virtual void call(const ::id & idMethod);
   virtual void send(const ::id & idFuture, const ::var & var);


   template < typename PRED >
   inline object & operator +=(const ::method & method)
   {

      add(method);

      return *this;

   }

   template < typename PRED >
   inline object& operator +=(const ::future & future)
   {

      add(future);

      return *this;

   }


   template < typename PRED >
   inline void add_method(const ::id & id, PRED pred, ::elemental* pobjectHold = nullptr)
   {

      add(::method(id, pred, pobjectHold));

   }

   template < typename PRED >
   inline void add_future(const ::id & id, PRED pred, ::elemental * pobjectHold = nullptr)
   {

      add(::future(id, pred, pobjectHold));

   }

   template < typename PRED >
   inline void add(enum_method emethod, PRED pred)
   {

      add(::method((::i64) emethod, pred));

   }

   template < typename PRED >
   inline void add(enum_future efuture, PRED pred)
   {

      add(::future((::i64) efuture, pred));

   }

   inline var context_value(const var& var);

   template < typename BASE_TYPE >
   void save_to(const var & varFile, BASE_TYPE * pobject);

   virtual ::estatus initialize(::layered * pobjectContext) override;
   virtual void finalize() override;

   inline const char * topic_text();

   context& __context(const var& var);

   var __context_value(const var& var);

   virtual void set_topic_text(const string & str);

   void create_object_meta();

   inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   ::object_meta * meta() { defer_object_meta(); return m_pmeta; }

   ::context * get_context() const { return m_pcontextContext; }

   ::thread * get_context_thread() const { return m_pthreadContext; }

   ::apex::application * get_context_application() const { return m_pappContext; }

   ::apex::session * get_context_session() const { return m_psessionContext; }

   ::apex::system * get_context_system() const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   ::apex::application * get_app() const { return get_context_application(); }

   virtual string get_text(const var& var, const ::id& id) override;

#ifdef DEBUG
   virtual void set_context(::context* pcontext);
   virtual void set_context_thread(::thread* pthread);
   virtual void set_context_app(::apex::application* pappContext);
   virtual void set_context_session(::apex::session* psessionContext);
   virtual void set_context_system(::apex::system* psystemContext);
   //virtual void set_context_user(::object * puserContext);
#else
   inline void set_context(::context* pcontext);
   inline void set_context_thread(::thread* pthread);
   inline void set_context_app(::apex::application* pappContext);
   inline void set_context_session(::apex::session* psessionContext);
   inline void set_context_system(::apex::system* psystemContext);
   //inline void set_context_user(::object * puserContext);
#endif


   virtual void set_context_object(::layered * pobjectContext) override;


   inline void defer_set_context_object(::layered * pobjectContext);

   virtual ::estatus call() override;


   inline i64 get_ref_count()
   {

      return m_countReference;

   }


   virtual ::user::primitive* get_user_interaction_host();
   

   virtual void dev_log(string str) const;

   ::object & operator = (const var & var);

   


   //static u32 s_thread_proc(void* p);


   virtual void to_string(string & str) const override;

   //::image_result create_image();
   //::image_result create_image(const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_result get_image(const var & varFile, bool bCache = true, bool bSync = true);
   //::image_result matter_image(const string & strMatter, bool bCache = true, bool bSync = true);

   template < typename BASE_TYPE >
   inline __result(BASE_TYPE) __create();

   template < typename BASE_TYPE >
   inline __result(BASE_TYPE) __id_create(const ::id & id);

   template < typename TYPE >
   inline __result(TYPE) __create_new();

   //inline ::estatus __compose(__composite(::image) & pimage);

   //inline ::estatus __compose(__composite(::image) & pimage, ::image * pimageSource);

   //inline ::estatus __defer_compose(__composite(::image) & pimage) { return !pimage ? __compose(pimage) : ::estatus(::success); }

   // for composition (ownership)

   template < typename BASE_TYPE >
   inline ::estatus __compose(__composite(BASE_TYPE) & pbase);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __compose(__composite(BASE_TYPE) & pbase, const SOURCE * psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __compose(__composite(BASE_TYPE) & pbase, const __pointer(SOURCE) & psource);

   template < typename BASE_TYPE >
   inline ::estatus __id_compose(__composite(BASE_TYPE) & pbase, const ::id & id);

   template < typename BASE_TYPE >
   inline ::estatus __raw_compose(__composite(BASE_TYPE) & pbase);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __raw_compose(__composite(BASE_TYPE) & pbase, const SOURCE * psource);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __raw_compose(__composite(BASE_TYPE) & pbase, const __pointer(SOURCE) & psource);

   template < typename TYPE >
   inline ::estatus __raw_compose_new(__composite(TYPE) & ptype);

   template < typename TYPE >
   inline ::estatus __compose_new(__composite(TYPE) & ptype);




   template < typename BASE_TYPE >
   inline ::estatus __defer_compose(__composite(BASE_TYPE) & pbase) { return !pbase ? __compose(pbase) : ::estatus(::success); }

   template < typename BASE_TYPE >
   inline ::estatus __defer_id_compose(__composite(BASE_TYPE) & pbase, const ::id & id) { return !pbase ? __id_compose(pbase) : ::estatus(::success); }

   template < typename TYPE >
   inline ::estatus __defer_raw_compose_new(__composite(TYPE) & ptype) { return !ptype ? __raw_compose_new(ptype) : ::estatus(::success); }

   template < typename TYPE >
   inline ::estatus __defer_compose_new(__composite(TYPE) & ptype) { return !ptype ? __compose_new(ptype) : ::estatus(::success); }




   template < typename BASE_TYPE >
   inline ::estatus __construct(__pointer(BASE_TYPE) & pbase);

   template < typename BASE_TYPE >
   inline ::estatus __id_construct(__pointer(BASE_TYPE) & pbase, const ::id & id);

   template < typename TYPE >
   inline ::estatus __construct_new(__pointer(TYPE) & pbase);

   template < typename BASE_TYPE >
   inline ::estatus __release(__composite(BASE_TYPE) & pcomposite);

   template < typename BASE_TYPE >
   inline ::estatus __release(__reference(BASE_TYPE) & preference);

   template < typename SOURCE >
   inline ::estatus release_reference(__pointer(SOURCE) & psource);


   virtual ::estatus add_composite(::elemental* pobject) override;
   virtual ::estatus add_reference(::elemental* pobject) override;


   virtual ::estatus release_composite(::elemental* pobject) override;
   virtual ::estatus release_reference(::elemental* pobject) override;




   template < typename BASE_TYPE >
   inline ::estatus add_composite(__composite(BASE_TYPE) & p);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __refer(__reference(BASE_TYPE) & p, const SOURCE * psource, const char * pszObjRefDbg = nullptr);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __refer(__reference(BASE_TYPE) & p, const __pointer(SOURCE) & psource, const char* pszObjRefDbg = nullptr);

   template < typename BASE_TYPE, typename SOURCE >
   inline ::estatus __refer(__reference(BASE_TYPE) & p, const ::primitive::member < SOURCE > & psource, const char* pszObjRefDbg = nullptr);

   template < typename SOURCE >
   inline ::estatus add_reference(SOURCE* psource);

   template < typename SOURCE >
   inline ::estatus add_reference(__pointer(SOURCE)& psource);

   template < typename SOURCE >
   inline ::estatus add_reference(__reference(SOURCE)& psource);

   virtual void delete_this() override;

   virtual void destruct();

   static void system(const char * pszProjectName);

   virtual bool enable_application_events(bool bEnable = true);

   virtual bool handle_exception(::exception_pointer pe);

   virtual bool top_handle_exception(::exception_pointer pe);

   virtual bool process_exception(::exception_pointer pe);


   ::object * parent_property_set_holder() const override;

   void copy_from(const object & o);


   virtual string get_tag() const;
   virtual bool is_thread() const;
   virtual bool thread_get_run() const;
   virtual bool is_running() const;
   virtual void child_post_quit(const char * pszTag);
   virtual void child_post_quit_and_wait(const char * pszTag, const duration & duration);
   virtual void set_finish() override;
   virtual void set_finish_composites();

   virtual void defer_update_object_id();
   virtual ::id calc_default_object_id() const;


   virtual void install_message_routing(::channel * pchannel);

   void message_receiver_destruct();

   void _001OnUpdate(::message::message * pmessage);

   virtual ::estatus request_file(const var& varFile);

   virtual ::estatus request_file(const var& varFile, var varQuery);

   virtual ::estatus request(arguments arguments);

   virtual ::estatus do_request(::create * pcreate);

   inline ::estatus message_box(const char* pszMessage, const char* pszTitle = nullptr, ::emessagebox emessagebox = message_box_ok, ::future future = ::future())
   {
   
      return message_box(nullptr, pszMessage, pszTitle, emessagebox, future);

   }


   inline ::estatus message_box_timeout(const char* pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), ::emessagebox emessagebox = message_box_ok, ::future future = ::future())
   {

      return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, future);

   }

   virtual ::estatus message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle = nullptr, ::emessagebox emessagebox = message_box_ok, ::future future = ::future());
   virtual ::estatus message_box_timeout(::user::primitive* pwndOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), ::emessagebox emessagebox = message_box_ok, ::future future = ::future());

   virtual void release_references();

   virtual __pointer(::object) running(const char * pszTag) const;

   virtual bool ___is_reference(::elemental * pobject) const;

   virtual bool __is_composite(::elemental * pobject) const;

   virtual void on_finalize();

   virtual ::estatus call_request(::create * pcreate);

   //// former user::server
   //virtual ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
   virtual void on_request(::create* pcreate);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const var& varFile, const var & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = window_flag_none, ::id id = ::id());
   //virtual ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const var& varFile);
   //virtual ::user::document* create_subdocument(::user::impact_data* pimpactdata);


   virtual ::estatus run() override;

   virtual string lstr(const ::id & id, string strDefault = "");

   virtual string __get_text(string str);

   //template < typename PRED >
   //::image_result get_image(const var & varFile, ::u64 uTrait, PRED pred);

   //virtual ::image_result load_image(const var & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_result load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   //virtual ::image_result load_matter_icon(string_array & straMatter, string strIcon);
   //virtual ::image_result load_thumbnail(const var & varFile, int w, int h);
   //virtual ::image_result load_thumbnail(const char * pszPath);
   //virtual ::image_result load_dib(const ::file::path & pathDib);


   virtual void start_clock(e_clock eclock, duration duration);
   virtual void _task_clock(e_clock eclock, duration duration);
   virtual void on_clock(e_clock eclock);

   bool IsSerializable() const;


   void start();


   void single_fork(const runnable_array & runnablea);
   void multiple_fork(const runnable_array & runnablea);

   template < typename PRED >
   inline ::thread_pointer defer_fork(const char * pszTag, PRED pred);

   template < typename PRED >
   inline ::thread_pointer & defer_fork(::thread_pointer & pthread, PRED pred);

   inline ::thread_pointer & defer_fork(::thread_pointer & pthread)
   {

      return defer_fork(pthread,
         [this]()
         {

            this->call();

         });

   }


   template < typename PRED >
   inline ::thread_pointer & fork(::thread_pointer & pthread, PRED pred, const char * pszTag = nullptr, int iCallStackAddUp = 0);

   template < typename PRED >
   inline auto fork(PRED pred, const char * pszTag, int iCallStackAddUp = 0, e_priority = priority_normal);

   template < typename PRED >
   inline auto opt_fork(PRED pred);

   template < typename PRED >
   inline auto fork(PRED pred);

   template < typename PRED >
   inline auto new_pred_thread(PRED pred);

   template < typename TYPE >
   inline auto async(void (TYPE:: * pfnMemberProcedure)())
   {

      return fork([=]()
         {

            TYPE * ptype = dynamic_cast <TYPE *> (this);

            (ptype->*pfnMemberProcedure)();

         });

   }

   template < typename PRED >
   inline ::thread_pointer pred_run(bool bSync, PRED pred);

   ::thread_pointer begin(
      ::e_priority epriority = ::priority_normal,
      UINT nStackSize = 0,
      u32 dwCreateFlags = 0,
      LPSECURITY_ATTRIBUTES pSecurityAttrs = nullptr);

   ::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//   virtual void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_result get_reader(const ::var& varFile, const ::efileopen& efileopen = ::efileopen());
   //inline ::file_result get_writer(const ::var& varFile, const ::efileopen& efileopen = ::efileopen());


   //virtual void to_string(string & str) const override;


   virtual ::file_result get_file(const var& varFile, efileopen eopen);
   inline ::file_result get_reader(const var& varFile, efileopen eopen = ::file::type_binary);
   inline ::file_result get_writer(const var& varFile, efileopen eopen = ::file::type_binary | ::file::defer_create_directory | ::file::mode_create);



   ::estatus bind_update(property * pproperty);
   ::estatus bind_update(const ::id & id, bool bCreate = true);
   ::estatus bind_update(const ::id & id, ::object * pobject);


   inline void format_topic_text(const char * psz, ...)
   {

      va_list valist;
      va_start(valist, psz);
      format_topic_text_v(psz, valist);
      va_end(valist);

   }


   inline void format_topic_text_v(const char * psz, va_list valist)
   {

      string str;
      str.FormatV(psz, valist);
      set_topic_text(str);

   }


   template < typename TYPE >
   auto member_fork(::estatus (TYPE:: * pfn)(), ::e_priority epriority = ::priority_normal)
   {

      TYPE * ptype = dynamic_cast <TYPE *>(this);

      return ptype->fork([ptype, pfn]()
         {

            return (ptype->*pfn)();

         }, NULL, 0, epriority);

   }


   template < typename TYPE >
   ::thread_pointer start_below_normal(void (TYPE:: * pfn)())
   {

      return fork(pfn, ::priority_below_normal);

   }

   //::estatus __construct(::image_pointer & p, const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::estatus __preserve(::image_pointer & p, const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1);


   template < typename TYPE >
   ::estatus __construct(::thread_pointer & p, void (TYPE:: * pfn)(), e_priority epriority);

   template < typename TYPE >
   ::estatus __construct_below_normal(::thread_pointer & p, void (TYPE:: * pfn)());


   template < typename TYPE >
   ::thread_pointer __start_thread(const ::id & id, void(TYPE:: * pfn)(), e_priority epriority = priority_normal);




};


#define __start(ID) defer_fork(#ID, [this]() { ID(); } )



CLASS_DECL_APEX ::estatus call_sync(const runnable_array & runnablea);



