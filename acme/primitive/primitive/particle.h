// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/e_flag.h"


class extended_topic;


struct PARTICLE
{
public:


   ::e_flag                            m_eflagElement;


   PARTICLE()
   {

   }


   [[nodiscard]] inline bool has(enum_flag eflag) const { return (m_eflagElement & eflag) == eflag; }
   inline void set(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) | (::u64)(eflag)); }
   inline void set(enum_flag eflag, bool bSet) { if (bSet) set(eflag); else clear(eflag); }
   inline void clear(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) & (~(::u64)(eflag))); }


   inline void set_ok() { set(e_flag_success); clear(e_flag_timeout); clear(e_flag_failure); }
   inline void set_nok(enum_flag estatusFailure = e_flag_failure) { clear(e_flag_success); set(estatusFailure); }
   inline void set_modified(bool bModified = true) { set(e_flag_changed, bModified); }


   inline void set_fail() { set(e_flag_failure); clear(e_flag_success); }
   inline void set_timed_out() { set(e_flag_timeout); }
   inline void set_persistent(bool bSet = true) { set(e_flag_persist, bSet); }


   [[nodiscard]] inline bool is_ok() const { return has(e_flag_success); }
   [[nodiscard]] inline bool nok() const { return has(e_flag_failure) || has(e_flag_timeout); }
   [[nodiscard]] inline bool has_timed_out() { return has(e_flag_timeout); }
   [[nodiscard]] inline bool is_modified() const { return has(e_flag_changed); }
   [[nodiscard]] inline bool is_persistent() const { return has(e_flag_persist); }



   [[nodiscard]] inline bool is_finishing() const { return has(e_flag_finishing); }
   inline void set_finishing() { set(e_flag_finishing); }
   inline void unset_finishing() { clear(e_flag_finishing); }


   // [[nodiscard]] inline bool is_heap_allocated() const { return has(e_flag_heap_allocated); }
   // inline void set_heap_allocated() { set(e_flag_heap_allocated); }
   // inline void unset_heap_allocated() { clear(e_flag_heap_allocated); }


   [[nodiscard]] inline bool is_destroying() const { return has(e_flag_destroying); }
   inline void set_destroying() { set(e_flag_destroying); }
   inline void unset_destroying() { clear(e_flag_destroying); }


   [[nodiscard]] inline bool is_storing() const { return has(e_flag_storing); }
   [[nodiscard]] inline bool is_loading() const { return !is_storing(); }


   inline void set_storing() { set(e_flag_storing); }
   inline void set_loading() { clear(e_flag_storing); }


   inline void defer_set_storing() { if (!is_storing()) set_storing(); }
   inline void defer_set_loading() { if (!is_loading()) set_loading(); }


   //PARTICLE(const class ::atom & atom) :
   //   m_atom(atom)
   //{

   //}


   //PARTICLE(const PARTICLE & topic) :
   //   m_atom(topic.m_atom)
   //{

   //}


   //PARTICLE(PARTICLE && topic) :
   //   m_atom(topic.m_atom)
   //{

   //}


};



class CLASS_DECL_ACME particle :
   virtual public PARTICLE
{
public:


   ::interlocked_count                 m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG
   inline particle() { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference")); }
#else
   inline particle() : m_countReference(1) { }
#endif


   virtual ~particle();




#ifdef _DEBUG

   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

#else

   inline i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   inline i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   inline i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

#endif

   virtual void delete_this();


   virtual enum_type get_payload_type() const;

   virtual void destroy();

   virtual void initialize(::object * pobject);
   virtual void on_initialize_object();

   virtual void init_task();

   //virtual void initialize_matter(::matter * pmatter);
   virtual void call_run();


   virtual void run();
   virtual bool step();
   virtual void on_sequence();


   [[nodiscard]] virtual strsize sz_len() const;
   virtual void to_sz(char * sz, strsize len) const;



};



