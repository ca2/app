#pragma once


#include "_aura_integer.h"


#include "acme/primitive/numeric/types.h"


typedef u32 dword;
typedef i32 int_bool;


typedef unsigned char         uchar;


//typedef unsigned char         u8;





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

inline double __rate(double d)
{

   return minimummax(d, 0., 1.);

}

inline float __rate(float f)
{

   return minimummax(f, 0.f, 1.f);

}


inline ::u8 as_byte(double d) { return (::u8) minimummax(d, 0, 255); }
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
