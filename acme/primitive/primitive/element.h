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

   enum_flag                           m_eflagElement;


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

   
   inline bool is(enum_flag eflag) const { return (m_eflagElement & eflag) == eflag; }
   inline void set(enum_flag eflag) { m_eflagElement = (enum_flag)((::u32)(eflag) | (::u32)(eflag)); }
   inline void unset(enum_flag eflag) { m_eflagElement = (enum_flag)((::u32)(eflag) & (~(::u32)(eflag))); }


   inline bool is_finishing() const { return is(e_flag_finishing); }
   inline void set_finishing() { set(e_flag_finishing); }
   inline void unset_finishing() { unset(e_flag_finishing); }


   inline bool is_heap_allocated() const { return is(e_flag_heap_allocated); }
   inline void set_heap_allocated() { set(e_flag_heap_allocated); }
   inline void unset_heap_allocated() { unset(e_flag_heap_allocated); }


   inline bool is_destroying() const { return is(e_flag_destroying); }
   inline void set_destroying() { set(e_flag_destroying); }
   inline void unset_destroying() { unset(e_flag_destroying); }

      
};



