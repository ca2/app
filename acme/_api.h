// Created by camilo on 2022-09-26 18:31 <3ThomasBorregaardSorensen!!
#pragma once


#include "operating_system/_api.h"



namespace sort
{


   template<typename TYPE>
   inline void swap(TYPE & a, TYPE & b)
   {
      auto t = a;
      a = b;
      b = t;

   }


} // namespace sort


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


