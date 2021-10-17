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

#if OBJECT_REFERENCE_COUNT_DEBUG
   inline element() { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference")); }
   inline element(const element &) { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference (2)")); }
#else
   inline element() : m_countReference(1) { }
   inline element(const element &) : m_countReference(1) { }
#endif
   inline element(element && element) : m_countReference(element.m_countReference) {  }
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

   
   
};



