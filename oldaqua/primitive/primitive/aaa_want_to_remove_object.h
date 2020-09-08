#pragma once


class CLASS_DECL_AQUA object :
   virtual public context_object
{
public:


   void *                              m_pthis;
   //__composite(parents)                m_pparents;
   //__composite(children)               m_pchildren;
   ::i64                               m_countTasksPending;


   object();
   virtual ~object();


   virtual class sync * get_mutex() const override;

   inline class ::sync * get_mutex();

   virtual ::estatus finalize() override;

   virtual void delete_this() override;


   virtual __pointer(::object) clone() const;


   virtual void destruct();


   static void system(const char * pszProjectName);


   virtual bool enable_application_events(bool bEnable = true);


   /// route an exception on rethrow according to the source
   /// return false if it should stop what it was doing
   virtual bool handle_exception(::exception_pointer e);

   virtual bool top_handle_exception(::exception_pointer e);

   /// return false if it should stop what it was doing
   virtual bool process_exception(::exception_pointer e);


   void copy_this(const object & o);


   virtual bool is_thread() const;
   virtual string get_tag() const;
   virtual __pointer(::object) child_running(const char * pszTag) const;
   virtual bool child_running(::object * pobject) const;
   virtual void child_post_quit(const char * pszTag);
   virtual void child_post_quit_and_wait(const char * pszTag, const duration & duration);
   virtual bool thread_get_run();

   virtual void defer_update_object_id();
   virtual ::id calc_default_object_id() const;


   __pointer(thread) fork(
                           ::e_priority epriority = priority_normal,
                           UINT nStackSize = 0,
                           u32 dwCreateFlags = 0,
                           LPSECURITY_ATTRIBUTES pSecurityAttrs = nullptr);






   virtual void install_message_routing(::channel * pchannel);

   void message_receiver_destruct();

   void _001OnUpdate(::message::message * pmessage);


   virtual ::estatus     request_file(var varFile);
   virtual ::estatus     request_file(var varFile, var varQuery);
   virtual ::estatus     request(arguments arguments);

   virtual ::estatus     do_request(::create * pcreate);


   virtual void children_add(::object * pobjectChild);
   virtual void children_post_quit();
   virtual void children_wait_quit(duration duration);
   virtual void children_release(::object * pobjectChild);

   virtual bool children_is(::object * pobjectDescendantCandidate) const;


   virtual void children_post_quit_and_wait(duration durationTimeout);


   // after releasing a parent, the child shouldn't context_object it
   virtual void release_parents();
   virtual void release_children();

   virtual void set_finish();
   virtual void wait_quit(duration duration);

   virtual ::estatus     call_request(::create * pcreate);
   virtual void on_request(::create * pcreate);



   
   virtual string lstr(id id, string strDefault = "");

   
   virtual string __get_text(string str);

   
   using context_object::get_image;
   using context_object::matter_image;

   
   template < typename PRED >
   ::image_pointer get_image(const var & varFile, ::u64 uTrait, PRED pred);


   virtual ::image_pointer load_image(const var & varFile, bool bCache = true, bool bCreateHelperMaps = false);
   virtual ::image_pointer load_matter_image(const char * pszMatter, bool bCache = true, bool bCreateHelperMaps = false);
   virtual ::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   virtual ::image_pointer load_thumbnail(const var & varFile, int w, int h);
   virtual ::image_pointer load_thumbnail(const char * pszPath);
   virtual ::image_pointer load_dib(const ::file::path & pathDib);


   virtual void start_clock(e_clock eclock, duration duration);
   virtual void _task_clock(e_clock eclock, duration duration);
   virtual void on_clock(e_clock eclock);

   bool IsSerializable() const;


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();

   void start();

   //virtual __pointer(::object) alloc(const class ::type & type);

   //template < typename T >
   //inline __pointer(T) & alloc(__pointer(T) & point)
   //{

   //   return ::alloc(point, this);

   //}

   //template < typename T >
   //inline __pointer(T) alloc()
   //{

   //   return ::alloc < T >(this);

   //}

   virtual ::estatus     call() override;

   virtual ::estatus     run() override;

   template < typename PRED >
   inline ::thread * defer_fork(const char * pszTag, PRED pred);

   template < typename PRED >
   inline __pointer(::thread) & defer_fork(__pointer(::thread) & pthread, PRED pred);

   inline __pointer(::thread) & defer_fork(__pointer(::thread) & pthread)
   {

      return defer_fork(pthread,
      [this]()
      {

         this->call();

      });

   }

   

   template < typename PRED >
   inline __pointer(::thread) & fork(__pointer(::thread) & pthread, PRED pred, const char * pszTag = nullptr, int iCallStackAddUp = 0);

   template < typename PRED >
   inline ::thread * fork(PRED pred, const char * pszTag, int iCallStackAddUp = 0);

   template < typename PRED >
   inline ::thread * opt_fork(PRED pred);

   template < typename PRED >
   inline ::thread * fork(PRED pred);



   template < typename PRED >
   inline auto new_pred_thread(PRED pred);



   template < typename TYPE >
   inline ::thread * async(void (TYPE::*pfnMemberProcedure)())
   {

      return fork([=]()
      {

         TYPE * ptype = dynamic_cast <TYPE *> (this);

         (ptype->*pfnMemberProcedure)();

      });

   }

   template < typename PRED >
   inline ::thread * pred_run(bool bSync, PRED pred);



   __pointer(thread) begin(
   ::e_priority epriority = ::priority_normal,
   UINT nStackSize = 0,
   u32 dwCreateFlags = 0,
   LPSECURITY_ATTRIBUTES pSecurityAttrs = nullptr);



   thread * defer_fork(string strThread = "");


#ifdef __APPLE__
   virtual void ns_main_async(dispatch_block_t block);
#endif

   

};


















template < class c_derived >
inline i64 add_ref(c_derived * pca)
{

   if (::is_null(pca))
   {

      return -1;

   }

   return pca->add_ref(OBJ_REF_DBG_ARGS);

}


template < class c_derived >
inline i64 release(c_derived * & pca)
{

   if (::is_null(pca))
   {

      return -1;

   }

   c_derived * p = pca;

#ifdef DEBUG

   ::id id = p->m_id;
   //char * pszType = nullptr;
   //
   //try
   //{

   //   pszType = _strdup(typeid(*p).name());

   //}
   //catch (...)
   //{

   //   ::output_debug_string("exception release strdup(typeid(*p).name())\n");

   //}

#endif

   try
   {

      pca = nullptr;

   }
   catch (...)
   {

      ::output_debug_string("exception release pca = nullptr; (" + string(id) + ")\n");

   }

   try
   {

      return p->release();

   }
   catch(...)
   {

      ::output_debug_string("exception release p->release() (" + string(id) + ")\n");

   }

//#ifdef DEBUG
//
//   try
//   {
//
//      ::free(pszType);
//
//   }
//   catch (...)
//   {
//
//      ::output_debug_string("exception release ::free(pszType)\n");
//
//   }
//
//#endif

   return -1;

}



template < class c_derived >
inline i64 ref_count(c_derived * pca)
{

   if (pca == nullptr)
   {

      return -1;

   }

   return pca->get_ref_count();

}


CLASS_DECL_AQUA void call(::object * prunnable);


//CLASS_DECL_AQUA inline __pointer(::object) alloc(const ::type & type, ::object * pobject);









using runnable_pointer = __pointer(::object);



