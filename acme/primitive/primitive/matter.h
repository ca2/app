#pragma once


class context_object;
class task;
class action_context;
class payload;
class layered;
class object;
class dump_context;
class sync;
class __id;
class string_exchange;


inline ::object* __object(::layered* playered);




// ATTENTION
// Shared with:
// Objective-C++

class CLASS_DECL_ACME matter
{
private:


   mutable sync *                      m_pmutex;


public:

   union
   {

      ::u64       m_uObject;

      struct
      {

         bool     m_bitSetFinish : 1;
         bool     m_bitFinishing : 1;
         bool     m_bitProcessed : 1;

      };

   };

   i64                                 m_countReference;
   ::eobject                           m_eobject;




#if OBJ_REF_DBG
   inline matter() : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_uObject(0) { add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_COMMA_NOTE("Initial Reference")); }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(eobject), m_uObject(0)  { add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_COMMA_NOTE("Initial Reference (2)")); }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(matter.m_eobject), m_uObject(0) { if (matter.m_pmutex) defer_create_mutex(); add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_COMMA_NOTE("Initial Reference (3)")); }
   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_pobjrefdbg(matter.m_pobjrefdbg), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_uObject(0) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
#else
   inline matter() : m_pmutex(nullptr), m_countReference(1), m_uObject(0) { }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_countReference(1), m_eobject(eobject), m_uObject(0) { }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_countReference(1), m_eobject(matter.m_eobject), m_uObject(0) { if (matter.m_pmutex) defer_create_mutex(); }
   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_uObject(0) { matter.m_pmutex = nullptr; }
#endif

   virtual ~matter();


   virtual void assert_valid() const;
   virtual void dump(dump_context& dumpcontext) const;


#if OBJ_REF_DBG

   obj_ref_dbg* m_pobjrefdbg;

   void add_ref_history(matter* p, const char* pszObjRefDbg);
   void dec_ref_history(matter* p, const char* pszObjRefDbgNotUsedCurrently);
   void check_pending_releases();

#endif

   inline bool is_set() const { return ::is_set(this); }

   // sync/mutex
   inline sync* mutex() const { return is_set() ? ((::matter*)this)->m_pmutex : nullptr; }
   void set_mutex(sync* psync);
   void defer_create_mutex();


   virtual ::context_object * _get_context_object();


   virtual bool is_thread() const;
   virtual ::thread * get_thread();
   virtual bool thread_is_running() const;


   virtual ::task * get_task();
   virtual const char * get_task_tag();
   //virtual ::index task_add(::task* pthread);
   virtual void task_remove(::task* pthread);


   virtual void notify_on_finish(::context_object * pcontextobject);


   virtual void kick_idle();

   //::e_status add_update(const ::id & id);
   //::e_status remove_update(const ::id& id);
   void remove_from_any_source();

   inline bool is_shared() const { return m_countReference > 1; }


   inline const char* type_c_str() const { return typeid(*this).name(); }
#ifdef WINDOWS
   inline const char* type_name() const { return type_c_str() + (sizeof("class ") - 1); }
#else
   inline const char* type_name() const { return type_c_str(); }
#endif

#ifdef DEBUG
   virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
   virtual i64 release(OBJ_REF_DBG_PARAMS);
#else
   inline i64 add_ref(OBJ_REF_DBG_PARAMS);
   inline i64 dec_ref(OBJ_REF_DBG_PARAMS);
   inline i64 release(OBJ_REF_DBG_PARAMS);
#endif

   virtual ::e_status initialize(::layered* pobjectContext);
   virtual void finalize();


   virtual ::e_status do_task();
   virtual ::e_status on_task();


   virtual ::e_status osthread_init();
   virtual ::e_status __thread_init();
   virtual ::e_status __thread_main();
   virtual ::e_status __thread_term();
   virtual ::e_status osthread_term();


   virtual ::e_status add_composite(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS);
   virtual ::e_status add_reference(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS);


   virtual ::e_status release_composite2(::matter * pobject OBJ_REF_DBG_COMMA_PARAMS);
   virtual ::e_status finalize_composite(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS);
   virtual ::e_status release_reference(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS);


   virtual ::e_status set_generic_object_name(const char* pszName);


   virtual ::matter * get_taskpool_container();


   virtual ::layered * taskpool();


   virtual ::task* defer_start_task(const ::id & id, const ::promise::routine & routine);


   virtual void delete_this();


   virtual const char* debug_note() const;
   virtual ::matter * clone() const;


   inline void set(const ::eobject & eobject) { m_eobject |= eobject; }
   inline void clear(const ::eobject& eobject) { m_eobject -= eobject; }
   inline void set(const ::eobject& eobject, bool bSet) { if (bSet) set(eobject); else clear(eobject); }


   inline bool has(const ::eobject& eobject) const { return m_eobject.has(eobject); }
   inline ::u64 get_object_flag() { return m_eobject; }


   inline void clear_finish_bit() { m_bitSetFinish = false; }
   inline void set_finish_bit() { m_bitSetFinish = true; }
   inline bool finish_bit() const { return m_bitSetFinish; }


   virtual void on_finish();
   virtual ::e_status set_finish(::context_object * pcontextobjectFinish);
   virtual ::e_status set_finish_composites(::context_object * pcontextobjectFinish);


   // returns success when object is ready to have finalize called
   // returns error_pending if any child or ascendant is still active
   virtual ::e_status finish(::context_object * pcontextobjectFinish = nullptr);


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


   inline ::matter * context_trace_object() const { return (::matter *)this; }


   virtual void __tracea(matter * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
   virtual void __tracef(matter * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...);
   virtual void __tracev(matter * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);


   virtual e_trace_category trace_category(matter * pcontext);
   virtual e_trace_category trace_category();


   virtual const char * topic_text() const;

   virtual void sync_wait();
   virtual void sync_wait(const ::duration & duration);


   virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext);


   virtual ::e_status operator()();
   virtual void operator()(const ::payload & payload);
   virtual ::e_status run();
   virtual ::payload realize();
   virtual void on_future(const ::payload& payload);

   virtual void clear_member() { }

   virtual void exchange(::stream& s);

   virtual stream& write(::stream& stream) const;
   virtual stream& read(::stream& stream);


   virtual void to_string(const string_exchange & str) const;
   virtual strsize sz_len() const;
   virtual void to_sz(char* sz, strsize len) const;

   virtual bool should_run_async() const;


};

