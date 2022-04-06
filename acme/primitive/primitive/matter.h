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
   ::e_status                          m_estatus;



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
   inline matter() : m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(e_element_none), m_uError(0), m_countReference(0), m_eobject(e_object_none), m_psystem(nullptr), m_pobjrefdbg(nullptr) { }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(e_element_none), m_uError(0), m_countReference(0), m_eobject(eobject), m_psystem(nullptr), m_pobjrefdbg(nullptr) {  }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(matter.m_ematter), m_uError(matter.m_uError), m_countReference(0), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem), m_pobjrefdbg(nullptr) {  }
   inline matter(matter&& matter) : referenceable(matter),m_pmutex(matter.m_pmutex), m_estatus(e_status_none), m_ematter(matter.m_ematter), m_uError(matter.m_uError), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem), m_pobjrefdbg(matter.m_pobjrefdbg) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
   inline matter(class ::system * psystem) : m_psystem(psystem), m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(e_element_none), m_uError(0), m_eobject(e_object_none), m_pobjrefdbg(matter.m_pobjrefdbg) { }
#else
   inline matter() : m_pmutex(nullptr), m_estatus(e_status_none), m_uError(0), m_eobject(e_object_none), m_psystem(nullptr) { }
   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_estatus(e_status_none), m_uError(0), m_eobject(eobject), m_psystem(nullptr) { }
   inline matter(const matter& matter) : m_pmutex(nullptr), m_estatus(e_status_none), m_uError(matter.m_uError), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem) { if (matter.m_pmutex) defer_create_mutex(); }
   inline matter(matter&& matter) : element(matter), m_pmutex(matter.m_pmutex), m_estatus(e_status_none), m_uError(matter.m_uError), m_eobject(matter.m_eobject), m_psystem(matter.m_psystem) { matter.m_pmutex = nullptr; }
   inline matter(class ::system * psystem) : m_psystem(psystem), m_estatus(e_status_none), m_pmutex(nullptr), m_uError(0), m_eobject(e_object_none) { }
#endif

   ~matter() override;


   virtual void  assert_ok() const;
   virtual void  dump(dump_context& dumpcontext) const;


#if OBJECT_REFERENCE_COUNT_DEBUG

   object_reference_count_debug* m_pobjrefdbg;

   void add_ref_history(matter* p, const char* pszObjRefDbg);
   void dec_ref_history(matter* p, const char* pszObjRefDbgNotUsedCurrently);
   void check_pending_releases();

#endif


   void initialize_matter(::matter* pmatter) override;


   virtual void on_initialize_object();


   virtual void operator()();
   virtual void operator()(::message::message * pmessage);
   virtual void operator()(const ::payload & payload);



   //virtual ::topic_pointer _create_topic(const ::atom & atom);


   inline bool has_error() const {return m_uError != 0;}

   //inline bool is_set() const { return ::is_set(this); }


   inline ::count reference_count() const { return m_countReference; }
   
   
   inline bool is_shared2() const { return m_eobject & e_object_shared; }
   inline void set_shared(bool bSet = true) { m_eobject.set(e_object_shared, bSet); }


   virtual bool is_ready_to_quit() const;

   // synchronization_object/::mutex
   inline synchronization_object* mutex() const { return ::is_set_ptr(this) ? ((::matter*)this)->m_pmutex : nullptr; }
   void set_mutex(synchronization_object* psync);
   void defer_create_mutex();

   //void branch();


   inline class ::system* get_system() const { return (class ::system *) m_psystem; }

   inline ::app* get_app() { return _get_app(); }

   virtual ::app* _get_app();

   virtual bool is_thread() const;
   virtual ::thread * get_thread();
   virtual bool thread_is_running() const;


   virtual ::task * get_task();
   virtual const char * get_task_tag();
   //virtual ::index task_add(::task* pthread);
   virtual void task_erase(::task* pthread);

   virtual void notify_on_destroy(::property_object * pobject);


   virtual void kick_idle();


   virtual void set_finish();
   //void destroy() override;

   virtual void on_set_finish();




   //virtual void do_task();
   //virtual void on_task();


   virtual void task_osinit();
   virtual void __task_init();
   virtual void __task_main();
   virtual void __task_term();
   virtual void task_osterm();


//   virtual void add_composite(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void add_reference(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//
//
//   virtual void release_composite2(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void finalize_composite(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   virtual void release_reference(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   //virtual void set_generic_object_name(const char* pszName);



   //virtual ::task * defer_branch(const ::atom & atom, const ::routine & routine);


   void delete_this() override;


   virtual const char* debug_note() const;
   virtual ::element * clone() const;


   using element::has;
   using element::set;
   using element::clear;


   inline bool has(const ::eobject& eobject) const { return m_eobject.has(eobject); }
   inline void set(const ::eobject& eobject, bool bSet) { if (bSet) set(eobject); else clear(eobject); }
   inline void set(const ::eobject & eobject) { m_eobject |= eobject; }
   inline void clear(const ::eobject& eobject) { m_eobject -= eobject; }


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


   //virtual void on_finish();
   //virtual void set_finish(::property_object * pcontextobjectFinish);
   //virtual void set_finish();


   // returns success when object is ready to have destroy called
   // returns error_pending if any child or ascendant is still active
   //virtual void finish(::property_object * pcontextobjectFinish = nullptr);
   virtual void destroy_composites();


   virtual void post_quit();





   inline const ::element * context_trace_object() const { return this; }


   //virtual void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const;
   //virtual void __tracef(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...) const;
   //virtual void __tracev(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args) const;

   //virtual void __simple_tracev(enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args) const;
   //virtual void __simple_tracea(enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz) const;


   virtual enum_trace_category trace_category(const matter * pcontext) const;
   virtual enum_trace_category trace_category() const;


   virtual string topic_text() const;


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


   virtual void trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_information_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_warning_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_error_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_fatal_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);


   virtual void trace_arguments(enum_trace_level etracelevel, const char * pszFormat, va_list & arguments);
   virtual void trace_log_information_arguments(const char * pszFormat, va_list & arguments);
   virtual void trace_log_warning_arguments(const char * pszFormat, va_list & arguments);
   virtual void trace_log_error_arguments(const char * pszFormat, va_list & arguments);
   virtual void trace_log_fatal_arguments(const char * pszFormat, va_list & arguments);


   virtual void trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_information(enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_warning(enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_error(enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_fatal(enum_trace_category etracecategory, const char * pszFormat, ...);


   virtual void trace(enum_trace_level etracelevel, const char * pszFormat, ...);
   virtual void trace_log_information(const char * pszFormat, ...);
   virtual void trace_log_warning(const char * pszFormat, ...);
   virtual void trace_log_error(const char * pszFormat, ...);
   virtual void trace_log_fatal(const char * pszFormat, ...);


   virtual void trace_last_status();


   virtual void on_sequence(const ::payload & payload);

   virtual void clear_member() { }


   __pointer(::sequence < ::conversation >) message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok);


   inline ::topic_pointer create_topic(const ::atom & atom);


};

