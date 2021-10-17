// Created by camilo on 2021-08-01 22:55 Thomas Month!! <3ThomasBS__!!
#pragma once


class CLASS_DECL_ACME elemental
{
public:

   
   ::interlocked_count                 m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG
   inline elemental() { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference")); }
   inline elemental(const elemental &) { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference (2)")); }
#else
   inline elemental() : m_countReference(1) { }
   inline elemental(const elemental &) : m_countReference(1) { }
#endif
   inline elemental(elemental && elemental) : m_countReference(elemental.m_countReference) {  }
   virtual ~elemental() {}


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


};



