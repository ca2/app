#pragma once


#include "_aura_integer.h"


#include "acme/prototype/numeric/types.h"


typedef unsigned int dword;
typedef int int_bool;


typedef unsigned char         uchar;


//typedef unsigned char         uch;





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


inline unsigned char as_byte(double d) { return (unsigned char) minimummax(d, 0, 255); }
inline unsigned char as_byte(::i64 i) { return (unsigned char)minimummax(i, 0, 255); }

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
