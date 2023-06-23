#pragma once


#include <limits>


#include "_constant.h"




typedef void GENERATE_RANDOM_BYTES(void * p, memsize s);
using PFN_GENERATE_RANDOM_BYTES = GENERATE_RANDOM_BYTES *;


CLASS_DECL_ACME void set_generate_random_bytes(PFN_GENERATE_RANDOM_BYTES pfngeneraterandombytes);
CLASS_DECL_ACME void generate_random_bytes(void * p, memsize s);


inline ::std::strong_ordering strong_order(double d1, double d2)
{

   auto d = d1 - d2;

   if(d > std::numeric_limits<double>::epsilon())
   {

      return ::std::strong_ordering::greater;

   }
   else if(d < -std::numeric_limits<double>::epsilon())
   {

      return ::std::strong_ordering::less;

   }
   else
   {

      return ::std::strong_ordering::equal;

   }

}

template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
inline constexpr bool __lt(const SIGNED1 & a, const SIGNED2 & b) { return a < b; }
template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
inline constexpr bool __le(const SIGNED1 & a, const SIGNED2 & b) { return a <= b; }
template < primitive_unsigned UNSIGNED1, primitive_signed SIGNED2 >
inline constexpr bool __lt(const UNSIGNED1 & a, const SIGNED2 & b) { return b < 0 ? false : a < static_cast < u32 > (b); }
template < primitive_unsigned UNSIGNED1, primitive_signed SIGNED2 >
inline constexpr bool __le(const UNSIGNED1 & a, const SIGNED2 & b) { return b < 0 ? false : a <= static_cast <u32> (b); }


template < primitive_signed SIGNED1, primitive_unsigned UNSIGNED2 >
inline constexpr bool __lt(const SIGNED1 & a, const UNSIGNED2 & b) { return a < 0 ? true : static_cast <u32> (a) < b; }
template < primitive_signed SIGNED1, primitive_unsigned UNSIGNED2 >
inline constexpr bool __le(const SIGNED1 & a, const UNSIGNED2 & b) { return a < 0 ? false : static_cast <u64> (a) <= b; }


template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
inline constexpr bool __lt(const UNSIGNED1 & a, const UNSIGNED2 & b) { return a < b; }
template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
inline constexpr bool __le(const UNSIGNED1 & a, const UNSIGNED2 & b) { return a <= b; }


template < primitive_integral INTEGRAL1, primitive_floating FLOATING2 >
inline constexpr bool __lt(const INTEGRAL1 & a, const FLOATING2 & b) { return a < b; }
template < primitive_integral INTEGRAL1, primitive_floating FLOATING2 >
inline constexpr bool __le(const INTEGRAL1 & a, const FLOATING2 & b) { return a <= b; }


template < primitive_floating FLOATING1, primitive_integral INTEGRAL2 >
inline constexpr bool __lt(const FLOATING1 & a, const INTEGRAL2 & b) { return a < b; }
template < primitive_floating FLOATING1, primitive_integral INTEGRAL2 >
inline constexpr bool __le(const FLOATING1 & a, const INTEGRAL2 & b) { return a <= b; }


template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
inline constexpr bool __lt(const FLOATING1 & a, const FLOATING2 & b) { return a < b; }
template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
inline constexpr bool __le(const FLOATING1 & a, const FLOATING2 & b) { return a <= b; }


//template < typename TYPE1, typename TYPE2 >
//inline constexpr bool __lt(const TYPE1 & a, const TYPE2 & b) { return a < b; }
//template < typename TYPE1, typename TYPE2 >
//inline constexpr bool __le(const TYPE1 & a, const TYPE2 & b) { return a <= b; }
//
//
//template < typename T1, typename T2 >
//inline constexpr auto __ge(const T1 & a, const T2 & b) { return __le(b, a); }
//template < typename T1, typename T2 >
//inline constexpr auto __gt(const T1 & a, const T2 & b) { return __lt(b, a); }


//template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
//constexpr typename largest_type < SIGNED1, SIGNED2 >::type minimum(const SIGNED1 & a, const SIGNED2 & b) { return __lt(a, b) ? ((typename largest_type < SIGNED1, SIGNED2 >::type)a ): ((typename largest_type < SIGNED1, SIGNED2 >::type)b); }
//
//template < primitive_unsigned UNSIGNED1, primitive_signed SIGNED2 >
//constexpr SIGNED2 minimum(const UNSIGNED1 & a, const SIGNED2 & b) { return __lt(a, b) ? ((SIGNED2) a) : b; }
//
//template < primitive_signed SIGNED1, primitive_unsigned UNSIGNED2 >
//constexpr SIGNED1 minimum(const SIGNED1 & a, const UNSIGNED2 & b) { return __lt(a, b) ? a : ((SIGNED1) b); }
//
//template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
//constexpr typename largest_type < UNSIGNED1, UNSIGNED2 >::type minimum(const UNSIGNED1 & a, const UNSIGNED2 & b) { return __lt(a, b) ? ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)a) : ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)b); }
//
//
//template < primitive_integral INTEGRAL1, primitive_floating FLOATING2 >
//constexpr FLOATING2 minimum(const INTEGRAL1 & a, const FLOATING2 & b) { return __lt(a, b) ? ((FLOATING2)a) : b; }
//
//template < primitive_floating FLOATING1, primitive_integral INTEGRAL2 >
//constexpr FLOATING1 minimum(const FLOATING1 & a, const INTEGRAL2 & b) { return __lt(a, b) ? a : ((FLOATING1)b); }
//
//template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
//constexpr typename largest_type < FLOATING1, FLOATING2 >::type minimum(const FLOATING1 & a, const FLOATING2 & b) { return __lt(a, b) ? ((typename largest_type < FLOATING1, FLOATING2 >::type)a) : ((typename largest_type < FLOATING1, FLOATING2 >::type)b); }
//
//
//template < typename TYPE1, typename TYPE2 >
//constexpr TYPE1 minimum(const TYPE1 & a, const TYPE2 & b) { return __lt(a, b) ? a : ((TYPE1)b); }
//


//template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
//constexpr typename largest_type < SIGNED1, SIGNED2 >::type maximum(const SIGNED1 & a, const SIGNED2 & b) { return __lt(b, a) ? ((typename largest_type < SIGNED1, SIGNED2 >::type)a) : ((typename largest_type < SIGNED1, SIGNED2 >::type)b); }
//
//template < primitive_unsigned UNSIGNED1, primitive_signed SIGNED2 >
//constexpr SIGNED2 maximum(const UNSIGNED1 & a, const SIGNED2 & b) { return __lt(b, a) ? ((SIGNED2)a) :  b; }
//
//template < primitive_signed SIGNED1, primitive_unsigned UNSIGNED2 >
//constexpr SIGNED1 maximum(const SIGNED1 & a, const UNSIGNED2 & b) { return __lt(b, a) ?  a : ((SIGNED1)b); }
//
//template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
//constexpr typename largest_type < UNSIGNED1, UNSIGNED2 >::type maximum(const UNSIGNED1 & a, const UNSIGNED2 & b) { return __lt(b, a) ? ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)a) : ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)b); }
//
//template < primitive_integral INTEGRAL1, primitive_floating FLOATING2 >
//constexpr FLOATING2 maximum(const INTEGRAL1 & a, const FLOATING2 & b) { return __lt(b, a) ? ((FLOATING2)a) : b; }
//
//template < primitive_floating FLOATING1, primitive_integral INTEGRAL2 >
//constexpr FLOATING1 maximum(const FLOATING1 & a, const INTEGRAL2 & b) { return __lt(b, a) ? a : ((FLOATING1)b); }

//template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
//constexpr largest_type < FLOATING1, FLOATING2 > maximum(const FLOATING1 & a, const FLOATING2 & b) { return __lt(b, a) ? ((typename largest_type < FLOATING1, FLOATING2 >::type)a) : ((typename largest_type < FLOATING1, FLOATING2 >::type)b); }


namespace comparison
{

//   template < typename T1, typename T2 >
//
//constexpr ::std::strong_ordering order(const T1 & t1, const T2 & t2)
//{
//
//   return t1 <=> t2;
//
//}

   template < typename T1, typename T2 >
   class comparison2
   {
   public:


      constexpr ::std::strong_ordering order(const T1 & t1, const T2 & t2) const
      {

         return t1 <=> t2;

      }


   };


   template < primitive_signed S1, primitive_signed S2 >
   constexpr ::std::strong_ordering order(S1 s1, S2 s2)
   {

      return s1 <=> s2;

   }


   template < primitive_signed S1, primitive_signed S2 >
   class comparison2 < S1, S2 >
   {
   public:

      constexpr ::std::strong_ordering order(S1 s1, S2 s2) const
      {

         return s1 <=> s2;

      }

   };

template < primitive_unsigned U1, primitive_unsigned U2 >
constexpr ::std::strong_ordering order(U1 u1, U2 u2)
{

   return u1 <=> u2;

}
   template < primitive_unsigned U1, primitive_unsigned U2 >
   class comparison2 < U1, U2 >
   {
   public:

      constexpr ::std::strong_ordering order(U1 u1, U2 u2) const
      {

         return u1 <=> u2;

      }

   };

template < primitive_signed S, primitive_unsigned U >
constexpr ::std::strong_ordering order(S s, U u)
{

   return s < 0 ? ::std::strong_ordering::less : ::std::make_unsigned_t<S>(s) <=> u;

}
   template < primitive_signed S, primitive_unsigned U >
   class comparison2 < S, U >
   {
   public:

      constexpr ::std::strong_ordering order(S s, U u) const
      {

         return s < 0 ? ::std::strong_ordering::less : ::std::make_unsigned_t<S>(s) <=> u;

      }

   };
template < primitive_unsigned U, primitive_signed S >
constexpr ::std::strong_ordering order(U u, S s)
{

   return s < 0 ? ::std::strong_ordering::greater : u <=> ::std::make_unsigned_t<S>(s);

}
   template < primitive_unsigned U, primitive_signed S >
   class comparison2 < U, S >
   {
   public:



      constexpr ::std::strong_ordering order(U u, S s) const
      {

         return s < 0 ? ::std::strong_ordering::greater : u <=> ::std::make_unsigned_t<S>(s);

      }

   };
template < primitive_floating F1, primitive_floating F2 >

constexpr ::std::strong_ordering order(F1 f1, F2 f2)
{

   return ::strong_order(f1, f2);

}
   template < primitive_floating F1, primitive_floating F2 >
   class comparison2 < F1, F2 >
   {
   public:

      constexpr ::std::strong_ordering order(F1 f1, F2 f2) const
      {

         return ::strong_order(f1, f2);

      }

   };

template < primitive_floating F, primitive_integral T >

constexpr ::std::strong_ordering order(F f, T t)
{

#if defined(__GNUC__)

   if(f > t)
   {

      return ::std::strong_ordering::greater;

   }
   else if(f < t)
   {

      return ::std::strong_ordering::less;

   }
   else
   {

      return ::std::strong_ordering::equal;

   }

#else

   return ::std::strong_order(f, (F)t);

#endif



}
   template < primitive_floating F, primitive_integral T >
   class comparison2 < F, T >
   {
   public:

      constexpr ::std::strong_ordering order(F f, T t) const
      {

#if defined(__GNUC__) 

         if(f > t)
         {

            return ::std::strong_ordering::greater;

         }
         else if(f < t)
         {

            return ::std::strong_ordering::less;

         }
         else
         {

            return ::std::strong_ordering::equal;

         }

#else

         return ::std::strong_order(f, (F)t);

#endif



      }

   };

template < primitive_integral T, primitive_floating F >
constexpr ::std::strong_ordering order(T t, F f)
{

#if defined(__GNUC__)

   if(t > f)
   {

      return ::std::strong_ordering::greater;

   }
   else if(t < f)
   {

      return ::std::strong_ordering::less;

   }
   else
   {

      return ::std::strong_ordering::equal;

   }

#else

   return ::std::strong_order((F) t, f);

#endif

}

   template < primitive_integral T, primitive_floating F >
   class comparison2 < T, F >
   {
   public:

      constexpr ::std::strong_ordering order(T t, F f) const
      {

#if defined(__GNUC__)

         if(t > f)
         {

            return ::std::strong_ordering::greater;

         }
         else if(t < f)
         {

            return ::std::strong_ordering::less;

         }
         else
         {

            return ::std::strong_ordering::equal;

         }

#else

         return ::std::strong_order((F) t, f);

#endif

      }

   };



} //namespace comparison


//template < typename TYPE >
//constexpr TYPE minimum(const TYPE & a, const TYPE & b)
//{
//
//   return a <= b ? a : b;
//
//}


template < typename TYPE >
constexpr TYPE maximum(const TYPE & a, const TYPE & b)
{

   return a < b ? b : a;

}


template< typename TYPE, typename COMPARE >
constexpr TYPE compare_reduce(std::initializer_list<TYPE> list, COMPARE compare)
{

   auto p = list.begin();

   if (!p)
   {

      return {};

   }

   TYPE t = *p;

   p++;

   while(p != list.end())
   {

      if (compare(*p, t))
      {

         t = *p;

      }

      p++;

   }

   return t;

}


template< typename TYPE >
constexpr TYPE maximum(std::initializer_list<TYPE> list)
{

   return compare_reduce(list, [](auto a, auto b) {return a > b; });

}


template< typename TYPE >
constexpr TYPE minimum(std::initializer_list<TYPE> list)
{

   return compare_reduce(list, [](auto a, auto b) {return a < b; });

}


template < typename TYPE1, typename TYPE2 >
constexpr largest_type<TYPE1, TYPE2> maximum(const TYPE1 & a, const TYPE2 & b) 
{ 
   
   return ::comparison::comparison2<TYPE1, TYPE2>().order(a, b) >= 0 ?
      (largest_type<TYPE1, TYPE2>) a : (largest_type<TYPE1, TYPE2>)b;

}


template < primitive_number TYPE1, primitive_number TYPE2 >
constexpr smallest_type<TYPE1, TYPE2> natural_minimum(const TYPE1 & a, const TYPE2 & b)
{

   return ::comparison::comparison2<TYPE1, TYPE2>().order(a, b) <= 0 ?
      (smallest_type<TYPE1, TYPE2>) maximum(0, a) : (smallest_type<TYPE1, TYPE2>)maximum(0, b);

}


template < primitive_unsigned TYPE1, primitive_unsigned TYPE2 >
constexpr smallest_type<TYPE1, TYPE2> minimum(const TYPE1 & a, const TYPE2 & b)
{

   return ::comparison::comparison2<TYPE1, TYPE2>().order(a, b) <= 0 ?
      (smallest_type<TYPE1, TYPE2>) a : (smallest_type<TYPE1, TYPE2>)b;

}


template < typename TYPE1, typename TYPE2 >
constexpr largest_type<TYPE1, TYPE2> minimum(const TYPE1 & a, const TYPE2 & b)
{

   return ::comparison::comparison2<TYPE1, TYPE2>().order(a, b) <= 0 ?
      (largest_type<TYPE1, TYPE2>) a : (largest_type<TYPE1, TYPE2>)b;

}


CLASS_DECL_ACME i64 ceil_div(i64 num, i64 den);


CLASS_DECL_ACME double tri(double angle);


#ifdef __cplusplus


#include "natural.h"


#endif



CLASS_DECL_ACME int ccvt_dup(char * buf,int nchar, double arg, int ndigits,int *decpt,int *sign,int eflag);
CLASS_DECL_ACME int ecvt_dup(char * buf,int nchar, double arg, int ndigits,int *decpt,int *sign);
CLASS_DECL_ACME int fcvt_dup(char * buf,int nchar, double arg, int ndigits,int *decpt,int *sign);
CLASS_DECL_ACME int gcvt_dup(char * buf,int nchar, double arg, int ndigits);
CLASS_DECL_ACME int max_cvt_dup(char *buf,int nchar,double arg,int ndigits,int *decpt,int *sign, int * pi);




#define MATH_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844
#define MATH_HALF_PI 1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412671058533991074043256641153323546922
#define DEGREE_RADIAN 0.01745329251994329576923690768488612713442871888541725456097191440171009114603449443682241569634509482212304492507379059248385468
#define RADIAN_DEGREE 57.29577951308232087679815481410517033240547246656432154916024386120284714832155263244096899585111094418622338163286489328144827

#include <math.h>


namespace degree
{

   inline CLASS_DECL_ACME double to_radian(double dAngleDegrees)
   {

      return dAngleDegrees * DEGREE_RADIAN;

   }

   inline CLASS_DECL_ACME double sin(double dAngleDegrees)
   {

      return ::sin(to_radian(dAngleDegrees));

   }

   inline CLASS_DECL_ACME double cos(double dAngleDegrees)
   {

      return ::cos(to_radian(dAngleDegrees));

   }

   inline CLASS_DECL_ACME double tan(double dAngleDegrees)
   {

      return ::tan(to_radian(dAngleDegrees));

   }

} // namespace degree





inline ::u8 __byte_rate(double dRate, double dMin, double dMax)
{

   return (::u8)(dRate * (dMax - dMin) + dMin);

}


template < typename TYPE >
inline TYPE range_rate(TYPE iMin, TYPE iMax, double dRate)
{
   return (TYPE)((iMax - iMin) * dRate) + iMin;
}



#include "number_limits.h"



template < primitive_integral INTEGRAL >
inline short  __loword(INTEGRAL i) {return i & 0xffff; }


template < primitive_integral INTEGRAL >
inline short  __hiword(INTEGRAL i) {return (i >> 16) & 0xffff; }


//inline ::i64 as_i64(const char * psz, int iBase = 10)
//{
//
//   const char * pszEnd = nullptr;
//
//   return ansi_to_i64(psz, &pszEnd, iBase);
//
//}


CLASS_DECL_ACME int type_maximum_digits(enum_integer_type etype, int iBase = 10);


template < primitive_signed SIGNED >
inline int maximum_digits(int iBase)
{

   if constexpr (sizeof(SIGNED) == 1)
   {

      return type_maximum_digits(e_integer_type_i8, iBase);

   }
   else if constexpr (sizeof(SIGNED) == 2)
   {

      return type_maximum_digits(e_integer_type_i16, iBase);

   }
   else if constexpr (sizeof(SIGNED) == 4)
   {

      return type_maximum_digits(e_integer_type_i32, iBase);

   }
   else if constexpr (sizeof(SIGNED) == 8)
   {

      return type_maximum_digits(e_integer_type_i64, iBase);

   }
   else
   {

      throw_exception(error_unexpected);

      return -1;

   }

}


template < primitive_unsigned UNSIGNED >
inline int maximum_digits(int iBase)
{

   if constexpr (sizeof(UNSIGNED) == 1)
   {

      return type_maximum_digits(e_integer_type_u8, iBase);

   }
   else if constexpr (sizeof(UNSIGNED) == 2)
   {

      return type_maximum_digits(e_integer_type_u16, iBase);

   }
   else if constexpr (sizeof(UNSIGNED) == 4)
   {

      return type_maximum_digits(e_integer_type_u32, iBase);

   }
   else if constexpr (sizeof(UNSIGNED) == 8)
   {

      return type_maximum_digits(e_integer_type_u64, iBase);

   }
   else
   {

      throw_exception(error_unexpected);

      return -1;

   }

}


//CLASS_DECL_ACME int i8_maximum_digits(int iBase);
//CLASS_DECL_ACME int u8_maximum_digits(int iBase);
//
//CLASS_DECL_ACME int i16_maximum_digits(int iBase);
//CLASS_DECL_ACME int u16_maximum_digits(int iBase);
//
//CLASS_DECL_ACME int i32_maximum_digits(int iBase);
//CLASS_DECL_ACME int u32_maximum_digits(int iBase);
//
//CLASS_DECL_ACME int i64_maximum_digits(int iBase);
//CLASS_DECL_ACME int u64_maximum_digits(int iBase);


template <class T>
inline T square_power(T v)
{

   return v * v;

}



