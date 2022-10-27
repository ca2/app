// Created by camilo on 2022-09-26 18:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "operating_system/_api.h"



inline bool is_null(const void * p, size_t s)
{

   return ((size_t)p <= s);

}


template < a_pointer POINTER >
inline bool is_null(POINTER p)
{

   return ((size_t)p <= 65536);

}


template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }

inline bool is_empty(const ansichar * p) { return is_string_empty(p); }
inline bool is_empty(const wd16char * p) { return is_string_empty(p); }
inline bool is_empty(const wd32char * p) { return is_string_empty(p); }


inline bool has_char(const ansichar * p) { return !is_empty(p); }
inline bool has_char(const wd16char * p) { return !is_empty(p); }
inline bool has_char(const wd32char * p) { return !is_empty(p); }


template < a_pointer POINTER >
inline bool is_set(POINTER p)
{

   return !is_null(p);

}


template<typename TYPE>
inline bool is_ref_set(const TYPE & t)
{

   return is_set(&t);

}


template<typename TYPE>
inline bool is_ok(const TYPE * p)
{

   return ::is_set(p) && p->is_ok();

}


template<typename TYPE>
inline bool is_ok(const ::pointer<TYPE> & p)
{

   return ::is_ok(p.m_p);

}


template<typename TYPE>
inline bool nok(TYPE & t)
{

   return !::is_ok(t);

}






template < typename TYPE, std::size_t SIZE >
inline std::size_t item_count(array_reference < TYPE, SIZE > &) { return SIZE; }


template < typename T >
inline byte byte_clip(const T & t) { return ((byte)(((t) < (byte)0) ? (byte)0 : (((t) > (byte)255) ? (byte)255 : (byte)t))); }


template < typename A, typename B >
void __swap(A & a, B & b)
{

   A aCopy = a;

   a = b;

   b = aCopy;

}



CLASS_DECL_ACME void throw_resource_exception(const char * pszMessage);

CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const char * pszMessage = nullptr, const char * pszDetails = nullptr, i32 iSkip = -1);







/////////////////////////////////////////////////////////////////////////////
// Verify that a nullptr-terminated string points to valid memory
inline bool __is_valid_string(const widechar * psz, memsize nMaxLength = INT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != nullptr);
}

// Verify that a nullptr-terminated string points to valid memory
inline bool __is_valid_string(const char * psz, memsize nMaxLength = UINT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != nullptr);
}

// Verify that a pointer points to valid memory
inline bool __is_valid_address(const void * p, memsize nBytes, bool bReadWrite = true)
{
#ifdef WINDOWS
   (bReadWrite);
   (nBytes);
#endif
   return (p != nullptr);
}
