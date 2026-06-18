#pragma once


#include "_aura_integer.h"


#include "acme/prototype/numeric/types.h"


typedef u32 dword;
typedef i32 i32_bool;


typedef unsigned long ulong;


typedef u8         uchar;



//typedef ::u8         uch;

typedef i8 * char_pointer ;
typedef const i8 * const_char_pointer ;


#ifdef __cplusplus

template < typename TYPE, typename MINIMUM, typename MAXIMUM >
inline TYPE minimummax(const TYPE & value, const MINIMUM & minimum, const MAXIMUM & maximum)
{

   if (value < (TYPE)minimum)
   {

      return (TYPE)minimum;

   }
   else if ((TYPE)maximum < value)
   {

      return (TYPE)maximum;

   }

   return value;

}

inline ::f64 __rate(::f64 d)
{

   return minimummax(d, 0., 1.);

}

inline ::f32 __rate(::f32 f)
{

   return minimummax(f, 0.f, 1.f);

}


inline ::u8 as_byte(::f64 d) { return (::u8) minimummax(d, 0, 255); }
inline ::u8 as_byte(::i64 i) { return (::u8)minimummax(i, 0, 255); }

#endif

//inline bool is_null(const void * p)
//{
//
//   return (uptr) p < 65536;
//
//}
//inline bool is_set(const void * p)
//{
//
//   return !is_null(p);
//
//}
