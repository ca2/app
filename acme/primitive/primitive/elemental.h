#pragma once


class update;
class action_context;
class var;
class layered;
class object;
class dump_context;
class sync;


inline ::object* __object(::layered* playered);


// ATTENTION
// Shared with:
// Objective-C++

class CLASS_DECL_ACME elemental
{
private:


   mutable sync * m_pmutex;


public:


   i64                     m_countReference;
   ::eobject               m_eobject;
   ::layered *             m_pobjectContext;


#if OBJ_REF_DBG
   inline elemental() : m_pmutex(nullptr), m_pobjectContext(nullptr), m_pobjrefdbg(nullptr), m_countReference(0) { add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_ADD_NOTE("Initial Reference")); }
   inline elemental(const eobject& eobject) : m_pmutex(nullptr), m_pobjectContext(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(eobject) { add_ref(OBJ_REF_DBG_THIS OBJ_REF_DBG_ADD_NOTE("Initial Reference (2)")); }
#else
   inline elemental() : m_pmutex(nullptr), m_pobjectContext(nullptr), m_countReference(1) { }
   inline elemental(const eobject & eobject) : m_pmutex(nullptr), m_pobjectContext(nullptr),m_countReference(1), m_eobject(eobject) { }
#endif

   virtual ~elemental();


   virtual void assert_valid() const;
   virtual void dump(dump_context& dumpcontext) const;


#if OBJ_REF_DBG

   obj_ref_dbg* m_pobjrefdbg;

   void add_ref_history(elemental* p, const char* pszObjRefDbg);
   void dec_ref_history(elemental* p, const char* pszObjRefDbgNotUsedCurrently);
   void check_pending_releases();

#endif

   inline bool is_set() const { return ::is_set(this); }

   // sync/mutex
   inline sync* mutex() const { return is_set() ? ((::elemental*)this)->m_pmutex : nullptr; }
   void set_mutex(sync* psync);
   void defer_create_mutex();



   inline ::object * get_context_object() const { return __object(m_pobjectContext); }
   virtual void set_context_object(::layered * pobjectContext);


   inline bool is_shared() const { return m_countReference > 1; }


   inline const char * type_c_str() const { return typeid(*this).name(); }
#ifdef WINDOWS
   inline const char * type_name() const { return type_c_str() + (sizeof("class ") - 1); }
#else
   inline const char * type_name() const { return type_c_str(); }
#endif

#if OBJ_REF_DBG
   template < typename TYPE, typename T >
   void ___assign(__pointer(TYPE)& ptr, T * p, const char * psz = nullptr)
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
   void ___release(TYPE * & p)
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

   virtual ::estatus initialize(::layered * pobjectContext);
   virtual void finalize();


#ifdef WINDOWS

   static DWORD WINAPI s_os_thread_proc(void* p);

#else

   static void* s_os_thread_proc(void* p);

#endif

   virtual ::estatus __thread_proc();


   virtual ::estatus osthread_init();
   virtual ::estatus __thread_init();
   virtual ::estatus __thread_main();
   virtual ::estatus __thread_term();
   virtual ::estatus osthread_term();


   ::estatus os_fork(
      ::e_priority epriority = priority_normal,
      u32 nStackSize = 0,
      u32 dwCreateFlags = 0,
      ITHREAD * pithread = nullptr,
      HTHREAD * phthread = nullptr);


   virtual ::estatus add_composite(::elemental* pobject);
   virtual ::estatus add_reference(::elemental* pobject);


   virtual ::estatus release_composite(::elemental* pobject);
   virtual ::estatus release_reference(::elemental* pobject);

   virtual ::estatus set_generic_object_name(const char* pszName);


   virtual void delete_this();

   virtual const char* debug_note() const;
   virtual ::elemental * clone() const;

   inline void set(const ::eobject & eobject) { m_eobject |= eobject; }
   inline void clear(const ::eobject& eobject) { m_eobject -= eobject; }
   inline void set(const ::eobject& eobject, bool bSet) { if (bSet) set(eobject); else clear(eobject); }

   inline bool has(const ::eobject& eobject) const { return m_eobject.has(eobject); }
   inline ::u64 get_object_flag() { return m_eobject; }

   virtual void set_finish();

   inline void set_ok() { set(e_object_success); clear(e_object_timeout); clear(e_object_failure); }
   inline void set_nok() { clear(e_object_success); }

   inline void set_fail() { set(e_object_failure); clear(e_object_success); }
   inline void set_timeout() { set(e_object_timeout); }
   inline void set_persistent(bool bSet = true) { set(e_object_persist, bSet); }

   inline bool is_ok() const { return has(e_object_success); }
   inline bool fail() const { return has(e_object_failure) || has(e_object_timeout); }
   inline bool is_persistent() { return has(e_object_persist); }

   inline bool is_storing() const { return has(e_object_storing); }
   inline bool is_loading() const { return !is_storing(); }

   inline void set_storing() { set(e_object_storing); }
   inline void set_loading() { clear(e_object_storing); }

   inline void defer_set_storing() { if (!is_storing()) set_storing(); }
   inline void defer_set_loading() { if (!is_loading()) set_loading(); }

   inline ::elemental * context_trace_object() const { return (::elemental *)this; }

   virtual void __tracea(elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
   virtual void __tracef(elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...);
   virtual void __tracev(elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);

   virtual e_trace_category trace_category(elemental * pcontext);
   virtual e_trace_category trace_category();


   virtual const char * topic_text() const;


   virtual void call_update(const ::id & id, const ::action_context & context);
   virtual void call_update(const ::id & id);
   virtual void call_update(::update * pupdate);
   virtual void update(::update * pupdate);
   virtual bool already_handled(::update * pupdate) const;

   virtual ::estatus call();
   virtual void call(const ::var & var);
   virtual ::estatus run();
   virtual void receive_response(const ::var& var);

   virtual void clear_member() { }

   virtual void exchange(::stream& s);

   virtual stream& write(::stream& stream) const;
   virtual stream& read(::stream& stream);


   virtual void to_string(string& str) const;
   virtual strsize sz_len() const;
   virtual void to_sz(char* sz, strsize len) const;



};



