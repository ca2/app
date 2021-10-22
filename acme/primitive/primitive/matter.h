#pragma once


class CLASS_DECL_ACME matter :
   virtual public element
{
private:


   mutable synchronization_object *                      m_pmutex;


public:

   
   union
   {

      ::u32       m_uError;

      struct
      {

         bool        m_bTimeout : 1;

      };

   };

   
   ::eobject                           m_eobject;
   class ::system *                    m_psystem;


//#if OBJECT_REFERENCE_COUNT_DEBUG
//   inline matter() : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_uObject(0), m_psystem(nullptr) { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference")); }
//   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(eobject), m_uObject(0), m_psystem(nullptr) { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference (2)")); }
//   inline matter(const matter& matter) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(matter.m_eobject), m_uObject(0), m_psystem(nullptr) { if (matter.m_pmutex) defer_create_mutex(); increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference (3)")); }
//   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_pobjrefdbg(matter.m_pobjrefdbg), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_uObject(0), m_psystem(nullptr) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
//#else
//   inline matter() : m_pmutex(nullptr), m_countReference(1), m_uObject(0), m_psystem(nullptr) { }
//   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_countReference(1), m_eobject(eobject), m_uObject(0), m_psystem(nullptr) { }
//   inline matter(const matter& matter) : m_pmutex(nullptr), m_countReference(1), m_eobject(matter.m_eobject), m_uObject(0), m_psystem(nullptr) { if (matter.m_pmutex) defer_create_mutex(); }
//   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_uObject(0), m_psystem(nullptr) { matter.m_pmutex = nullptr; }
//#endif

#if OBJECT_REFERENCE_COUNT_DEBUG
   inline matter() : m_pmutex(nullptr), m_ematter(e_element_none), m_uError(0), m_countReference(0), m_eobject(e_object_none), m_psystem(nullptr), m_pobjrefdbg(nullptr) { }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_ematter(e_element_none), m_uError(0), m_countReference(0), m_eobject(eobject), m_psystem(nullptr), m_pobjrefdbg(nullptr) {  }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_ematter(matter.m_ematter), m_uError(matter.m_uError), m_countReference(0), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem), m_pobjrefdbg(nullptr) {  }
   inline matter(matter&& matter) : referenceable(matter),m_pmutex(matter.m_pmutex), m_ematter(matter.m_ematter), m_uError(matter.m_uError), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem), m_pobjrefdbg(matter.m_pobjrefdbg) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
   inline matter(class ::system * psystem) : m_psystem(psystem), m_pmutex(nullptr), m_ematter(e_element_none), m_uError(0), m_eobject(e_object_none), m_pobjrefdbg(matter.m_pobjrefdbg) { }
#else
   inline matter() : m_pmutex(nullptr), m_uError(0), m_eobject(e_object_none), m_psystem(nullptr) { }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_uError(0), m_eobject(eobject), m_psystem(nullptr) { }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_uError(matter.m_uError), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem) { if (matter.m_pmutex) defer_create_mutex(); }
   inline matter(matter&& matter) : element(matter), m_pmutex(matter.m_pmutex), m_uError(matter.m_uError), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem) { matter.m_pmutex = nullptr; }
   inline matter(class ::system * psystem) : m_psystem(psystem), m_pmutex(nullptr), m_uError(0), m_eobject(e_object_none) { }
#endif

   ~matter() override;


   virtual void  assert_valid() const;
   virtual void  dump(dump_context& dumpcontext) const;


#if OBJECT_REFERENCE_COUNT_DEBUG

   object_reference_count_debug* m_pobjrefdbg;

   void add_ref_history(matter* p, const char* pszObjRefDbg);
   void dec_ref_history(matter* p, const char* pszObjRefDbgNotUsedCurrently);
   void check_pending_releases();

#endif


   virtual ::enum_type get_payload_type() const;


   virtual ::e_status initialize_matter(::matter* pmatter);


   virtual ::e_status on_initialize_object();

   inline bool has_error() const {return m_uError != 0;}

   //inline bool is_set() const { return ::is_set(this); }


   inline bool is_shared() const { return m_countReference > 1; }


   virtual bool is_ready_to_quit() const;

   // synchronization_object/::mutex
   inline synchronization_object* mutex() const { return ::is_set_ptr(this) ? ((::matter*)this)->m_pmutex : nullptr; }
   void set_mutex(synchronization_object* psync);
   void defer_create_mutex();

   //::e_status branch();

   virtual DURATION timeout() const;

   inline class ::system* get_system() const { return (class ::system *) m_psystem; }

   inline ::application* get_application() { return _get_application(); }

   virtual ::application* _get_application();

   virtual bool is_thread() const;
   virtual ::thread * get_thread();
   virtual bool thread_is_running() const;


   virtual ::task * get_task();
   virtual const char * get_task_tag();
   //virtual ::index task_add(::task* pthread);
   virtual void task_erase(::task* pthread);

   virtual void notify_on_destroy(::property_object * pobject);


   virtual void kick_idle();


   inline string type_name() const { return ::demangle(typeid(*this).name()); }


   virtual ::e_status initialize(::object * pobject);
   virtual ::e_status set_finish();
   //::e_status destroy() override;

   virtual void on_set_finish();


   virtual ::e_status set_library_name(const char* pszLibraryName);
   // if this is an application/or nano application
   virtual ::e_status set_application_id(const char* pszApplicationId);


   //virtual ::e_status do_task();
   //virtual ::e_status on_task();


   virtual ::e_status osthread_init();
   virtual ::e_status __thread_init();
   virtual ::e_status __thread_main();
   virtual ::e_status __thread_term();
   virtual ::e_status osthread_term();


   virtual ::e_status add_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual ::e_status add_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual ::e_status release_composite2(::matter * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual ::e_status finalize_composite(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual ::e_status release_reference(::matter* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual ::e_status set_generic_object_name(const char* pszName);


   virtual ::matter * get_taskpool_container();


   virtual ::task_pool * taskpool();


   //virtual ::task * defer_branch(const ::id & id, const ::routine & routine);


   void delete_this() override;


   virtual const char* debug_note() const;
   virtual ::matter * clone() const;




   inline void set(const ::eobject & eobject) { m_eobject |= eobject; }
   inline void clear(const ::eobject& eobject) { m_eobject -= eobject; }
   inline void set(const ::eobject& eobject, bool bSet) { if (bSet) set(eobject); else clear(eobject); }


   inline bool has(const ::eobject& eobject) const { return m_eobject.has(eobject); }
   inline ::u64 get_object_flag() { return m_eobject; }


   //inline bool is(enum_matter ematter) const { return (m_ematter & ematter) == ematter; }
   //inline void set(enum_matter ematter) { m_ematter = (enum_matter) ((::u32)(m_ematter) | (::u32)(ematter)); }
   //inline void unset(enum_matter ematter) { m_ematter = (enum_matter)((::u32)(m_ematter) & (~(::u32)(ematter))); }


   //inline bool is_finishing() const { return is(e_element_finishing); }
   //inline void set_finishing() { set(e_element_finishing); }
   //inline void unset_finishing() { unset(e_element_finishing); }


   //inline bool is_heap_allocated() const { return is(e_element_heap_allocated); }
   //inline void set_heap_allocated() { set(e_element_heap_allocated); }
   //inline void unset_heap_allocated() { unset(e_element_heap_allocated); }


   //inline bool is_destroying() const { return is(e_element_destroying); }
   //inline void set_destroying() { set(e_element_destroying); }
   //inline void unset_destroying() { unset(e_element_destroying); }


   //virtual ::e_status on_finish();
   //virtual ::e_status set_finish(::property_object * pcontextobjectFinish);
   //virtual ::e_status set_finish();


   // returns success when object is ready to have destroy called
   // returns error_pending if any child or ascendant is still active
   //virtual ::e_status finish(::property_object * pcontextobjectFinish = nullptr);
   virtual     ::e_status     destroy()     ;
   virtual ::e_status destroy_composites();


   virtual void post_quit();


   inline void set_ok() { set(e_object_success); clear(e_object_timeout); clear(e_object_failure); }
   inline void set_nok(enum_object estatusFailure = e_object_failure) { clear(e_object_success); set(estatusFailure); }
   inline void set_modified(bool bModified = true) { set(e_object_changed, bModified); }


   inline void set_fail() { set(e_object_failure); clear(e_object_success); }
   inline void set_timeout() { set(e_object_timeout); }
   inline void set_persistent(bool bSet = true) { set(e_object_persist, bSet); }


   inline bool is_ok() const { return has(e_object_success); }
   inline bool nok() const { return has(e_object_failure) || has(e_object_timeout); }
   inline bool is_modified() const { return has(e_object_changed); }
   inline bool is_persistent() { return has(e_object_persist); }


   inline bool is_storing() const { return has(e_object_storing); }
   inline bool is_loading() const { return !is_storing(); }


   inline void set_storing() { set(e_object_storing); }
   inline void set_loading() { clear(e_object_storing); }


   inline void defer_set_storing() { if (!is_storing()) set_storing(); }
   inline void defer_set_loading() { if (!is_loading()) set_loading(); }


   inline const ::matter * context_trace_object() const { return this; }


   //virtual void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const;
   //virtual void __tracef(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...) const;
   //virtual void __tracev(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args) const;

   //virtual void __simple_tracev(enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args) const;
   //virtual void __simple_tracea(enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz) const;


   virtual enum_trace_category trace_category(const matter * pcontext) const;
   virtual enum_trace_category trace_category() const;


   virtual const char * topic_text() const;

   virtual ::e_status sync_wait();
   virtual ::e_status sync_wait(const ::duration & duration);




   inline tracer trace(enum_trace_level etracelevel, enum_trace_category etracecategory) { return tracer(m_psystem, etracelevel, etracecategory); }
   inline tracer trace_log_information(enum_trace_category etracecategory) { return tracer(m_psystem, e_trace_level_information, etracecategory); }
   inline tracer trace_log_warning(enum_trace_category etracecategory) { return tracer(m_psystem, e_trace_level_warning, etracecategory); }
   inline tracer trace_log_error(enum_trace_category etracecategory) { return tracer(m_psystem, e_trace_level_error, etracecategory); }
   inline tracer trace_log_fatal(enum_trace_category etracecategory) { return tracer(m_psystem, e_trace_level_fatal, etracecategory); }


   inline tracer trace(enum_trace_level etracelevel) { return tracer(m_psystem, etracelevel, trace_category()); }
   inline tracer trace_log_information() { return tracer(m_psystem, e_trace_level_information, trace_category()); }
   inline tracer trace_log_warning() { return tracer(m_psystem, e_trace_level_warning, trace_category()); }
   inline tracer trace_log_error() { return tracer(m_psystem, e_trace_level_error, trace_category()); }
   inline tracer trace_log_fatal() { return tracer(m_psystem, e_trace_level_fatal, trace_category()); }


   virtual void trace_last_status();


   virtual ::e_status operator()();
   virtual void operator()(::message::message * pmessage);
   virtual void operator()(const ::payload & payload);
   virtual ::e_status run();
   virtual ::e_status step();
   virtual ::payload realize();
   virtual void on_future(const ::payload & payload);

   virtual void clear_member() { }

   virtual void exchange(::stream& s);

   virtual stream& write(::stream& stream) const;
   virtual stream& read(::stream& stream);


   //virtual void to_string(string_exchange & str) const;
   virtual strsize sz_len() const;
   virtual void to_sz(char* sz, strsize len) const;

   virtual bool should_run_async() const;


};

