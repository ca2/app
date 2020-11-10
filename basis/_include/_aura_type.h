#pragma once


#include "_aura_integer.h"


#include "_aura_memory.h"


typedef u32 dword;
typedef i32 int_bool;


typedef unsigned char         uchar;
typedef unsigned short int    ::u16;
typedef unsigned int          ::u32;

typedef unsigned char         byte;


#include <limits.h>

inline int is_i32(i64 i)
{

   if (i > (i64)MAXI32)
   {

      return 0;

   }


   if (i < (i64)MINI32)
   {

      return 0;

   }

   return 1;

}


#ifdef __cplusplus

template < typename TYPE, typename min, typename max >
inline TYPE __minmax(const TYPE & value, const min & min, const max & max)
{

   if (value < (TYPE)min)
   {

      return (TYPE)min;

   }
   else if ((TYPE)max < value)
   {

      return (TYPE)max;

   }

   return value;

}

inline double __rate(double d)
{

   return __minmax(d, 0., 1.);

}

inline float __rate(float f)
{

   return __minmax(f, 0.f, 1.f);

}


inline byte __byte(double d) { return (byte) __minmax(d, 0, 255); }
inline byte __byte(::i64 i) { return (byte)__minmax(i, 0, 255); }

#endif