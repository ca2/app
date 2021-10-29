// Created by camilo on 2021-08-01 22:55 Thomas Month!! <3ThomasBS__!!
#pragma once



// ATTENTION
// Shared with:
// Objective-C++



class CLASS_DECL_ACME element :
   virtual public handler
{
public:

   
   ::interlocked_count                 m_countReference;

   ::e_flag                            m_eflagElement;


#if OBJECT_REFERENCE_COUNT_DEBUG
   inline element() : m_eflagElement(e_flag_none) { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference")); }
   inline element(const enum_flag & element) : m_eflagElement(element.m_eelementflag) { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference (2)")); }
#else
   inline element() : m_eflagElement(e_flag_none), m_countReference(1) { }
   inline element(const element& element) : m_eflagElement(element.m_eflagElement), m_countReference(1) { }
#endif
   inline element(element && element) : m_eflagElement(element.m_eflagElement), m_countReference(element.m_countReference) {  }
   virtual ~element() {}


#ifdef _DEBUG

   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

#else

   inline i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   inline i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   inline i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

#endif

   virtual void delete_this() { delete this; };


   
   // <3ThomasBorregaardSørensen__!! likes handler concept...
   //void route(::signal * psignal) override;
   //void signal(::signal * psignal) override;
   //void route(::subject * psubject, ::context * pcontext) override;
   //void post_process(::subject * psubject, ::context * pcontext) override;

   // <3TBS_!! handle -> call_member <3TBS_!!
   virtual ::e_status call_member(::i64 i64);
   // <3ThomasBS_!! handle -> handle <3ThomasBS_!!
   //::e_status handle(const  emessage, i64 iData = 0, ::matter * pmatter = nullptr) override;
   void handle(::subject * psubject, ::context * pcontext) override;
   void handle(::message::message * pmessage) override;


   virtual ::e_status operator()();
   virtual void operator()(::message::message * pmessage);
   virtual void operator()(const ::payload & payload);
   virtual ::e_status run();
   virtual ::e_status step();
   virtual ::payload realize();


   virtual ::e_status wait();
   virtual ::e_status wait(const ::duration & duration);


   virtual DURATION timeout() const;


   virtual ::element * get_taskpool_container();


   virtual ::task_pool * taskpool();


   virtual ::e_status initialize(::object* pobject);


   virtual ::e_status initialize_matter(::matter* pmatter);


   inline bool has(enum_flag eflag) const { return (m_eflagElement & eflag) == eflag; }
   inline void set(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) | (::u64)(eflag)); }
   inline void set(enum_flag eflag, bool bSet) { if(bSet) set(eflag); else clear(eflag); }
   inline void clear(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) & (~(::u64)(eflag))); }


   inline void set_ok() { set(e_flag_success); clear(e_flag_timeout); clear(e_flag_failure); }
   inline void set_nok(enum_flag estatusFailure = e_flag_failure) { clear(e_flag_success); set(estatusFailure); }
   inline void set_modified(bool bModified = true) { set(e_flag_changed, bModified); }


   inline void set_fail() { set(e_flag_failure); clear(e_flag_success); }
   inline void set_timeout() { set(e_flag_timeout); }
   inline void set_persistent(bool bSet = true) { set(e_flag_persist, bSet); }


   inline bool is_ok() const { return has(e_flag_success); }
   inline bool nok() const { return has(e_flag_failure) || has(e_flag_timeout); }
   inline bool is_modified() const { return has(e_flag_changed); }
   inline bool is_persistent() { return has(e_flag_persist); }



   inline bool is_finishing() const { return has(e_flag_finishing); }
   inline void set_finishing() { set(e_flag_finishing); }
   inline void unset_finishing() { clear(e_flag_finishing); }


   inline bool is_heap_allocated() const { return has(e_flag_heap_allocated); }
   inline void set_heap_allocated() { set(e_flag_heap_allocated); }
   inline void unset_heap_allocated() { clear(e_flag_heap_allocated); }


   inline bool is_destroying() const { return has(e_flag_destroying); }
   inline void set_destroying() { set(e_flag_destroying); }
   inline void unset_destroying() { clear(e_flag_destroying); }


   inline bool is_storing() const { return has(e_flag_storing); }
   inline bool is_loading() const { return !is_storing(); }


   inline void set_storing() { set(e_flag_storing); }
   inline void set_loading() { clear(e_flag_storing); }


   inline void defer_set_storing() { if (!is_storing()) set_storing(); }
   inline void defer_set_loading() { if (!is_loading()) set_loading(); }


   virtual bool should_run_async() const;


   //virtual void to_string(string_exchange & str) const;
   virtual strsize sz_len() const;
   virtual void to_sz(char* sz, strsize len) const;


   virtual ::enum_type get_payload_type() const;


   virtual void exchange(::stream& s);

   virtual stream& write(::stream& stream) const;
   virtual stream& read(::stream& stream);


   virtual ::e_status add_composite(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual ::e_status add_reference(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual ::e_status release_composite2(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual ::e_status finalize_composite(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual ::e_status release_reference(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual ::e_status destroy();


};




#ifndef _DEBUG

inline i64 element::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


inline i64 element::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


inline i64 element::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif



