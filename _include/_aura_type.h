#pragma once


#include "_aura_integer.h"


#include "_aura_memory.h"


typedef u32 dword;
typedef i32 int_bool;


typedef unsigned char         uchar;


typedef unsigned char         byte;




#ifdef __cplusplus

template < typename TYPE, typename MINIMUM, typename MAXIMUM >
inline TYPE __minmax(const TYPE & value, const MINIMUM & min, const MAXIMUM & max)
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
