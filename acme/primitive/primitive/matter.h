#pragma once


//class update;
//class task;
class action_context;
class var;
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


   mutable sync* m_pmutex;


public:


   i64                     m_countReference;
   ::eobject               m_eobject;


#if OBJ_REF_DBG
   inline matter() : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0) { add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_ADD_NOTE("Initial Reference")); }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(eobject) { add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_ADD_NOTE("Initial Reference (2)")); }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(matter.m_eobject) { if (matter.m_pmutex) defer_create_mutex(); add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_ADD_NOTE("Initial Reference (3)")); }
   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_pobjrefdbg(matter.m_pobjrefdbg), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
#else
   inline matter() : m_pmutex(nullptr), m_countReference(1) { }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_countReference(1), m_eobject(eobject) { }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(1), m_eobject(matter.m_eobject) { if (matter.m_pmutex) defer_create_mutex(); }
   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_pobjrefdbg(matter.m_pobjrefdbg), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject) { matter.m_pmutex = nullptr; matter.m_pobjectContext = nullptr; }
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


   virtual ::index thread_add(::thread* pthread);
   virtual void thread_remove(::thread* pthread);
   virtual void thread_on_term(::thread* pthread);


   //::estatus add_update(const ::id & id);
   //::estatus remove_update(const ::id& id);
   void remove_from_any_source();

   inline bool is_shared() const { return m_countReference > 1; }


   inline const char* type_c_str() const { return typeid(*this).name(); }
#ifdef WINDOWS
   inline const char* type_name() const { return type_c_str() + (sizeof("class ") - 1); }
#else
   inline const char* type_name() const { return type_c_str(); }
#endif

#if OBJ_REF_DBG
   template < typename TYPE, typename T >
   void ___assign(__pointer(TYPE)& ptr, T* p, const char* psz = nullptr)
   {
      auto pold = ptr.m_p;
      ptr.m_p = p;
      p->add_ref(this, psz);
      ___release(pold);
   }
   template < typename TYPE >
   void ___release(__pointer(TYPE)& ptr)
   {
      ___release(ptr.m_p);
   }
   template < typename TYPE >
   void ___release(TYPE*& p)
   {
      if (is_set(p))
      {
         try
         {
            p->release(this);
         }
         catch (...)
         {
         }
         p = nullptr;
      }
   }
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

   virtual ::estatus initialize(::layered* pobjectContext);
   virtual void finalize();



   virtual ::estatus on_task();


   virtual ::estatus osthread_init();
   virtual ::estatus __thread_init();
   virtual ::estatus __thread_main();
   virtual ::estatus __thread_term();
   virtual ::estatus osthread_term();




   //virtual ::estatus fork_update(
   //   ::i64 iUpdate,
   //   ::e_priority epriority = priority_normal,
   //   u32 nStackSize = 0,
   //   u32 dwCreateFlags = 0,
   //   ITHREAD* pithread = nullptr,
   //   HTHREAD* phthread = nullptr);

   //virtual ::estatus fork_run(
   //   ::e_priority epriority = priority_normal,
   //   u32 nStackSize = 0,
   //   u32 dwCreateFlags = 0,
   //   ITHREAD* pithread = nullptr,
   //   HTHREAD* phthread = nullptr);



   virtual ::estatus add_composite(::matter* pobject OBJ_REF_DBG_ADD_PARAMS);
   virtual ::estatus add_reference(::matter* pobject OBJ_REF_DBG_ADD_PARAMS);


   virtual ::estatus release_composite(::matter* pobject OBJ_REF_DBG_ADD_PARAMS);
   virtual ::estatus release_reference(::matter* pobject OBJ_REF_DBG_ADD_PARAMS);

   virtual ::estatus set_generic_object_name(const char* pszName);


   virtual void delete_this();

   virtual const char* debug_note() const;
   virtual ::matter * clone() const;

   inline void set(const ::eobject & eobject) { m_eobject |= eobject; }
   inline void clear(const ::eobject& eobject) { m_eobject -= eobject; }
   inline void set(const ::eobject& eobject, bool bSet) { if (bSet) set(eobject); else clear(eobject); }

   inline bool has(const ::eobject& eobject) const { return m_eobject.has(eobject); }
   inline ::u64 get_object_flag() { return m_eobject; }

   virtual void set_finish();

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


   //virtual void apply_update(const ::id & id, const ::action_context & context);
   //virtual void apply_update(const ::id & id);
   virtual void apply(::action * paction);
   virtual void on_apply(::action * paction);
   //virtual bool already_handled(::update * pupdate) const;

   virtual ::estatus call();
   virtual void call(const ::var & var);
   virtual ::estatus run();
   virtual ::var realize();
   virtual void receive_response(const ::var& var);

   virtual void clear_member() { }

   virtual void exchange(::stream& s);

   virtual stream& write(::stream& stream) const;
   virtual stream& read(::stream& stream);


   virtual void to_string(const string_exchange & str) const;
   virtual strsize sz_len() const;
   virtual void to_sz(char* sz, strsize len) const;



   //virtual ::estatus __thread_procedure() override;


};

