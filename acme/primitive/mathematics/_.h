#pragma once


typedef void GENERATE_RANDOM_BYTES(void * p, memsize s);
using PFN_GENERATE_RANDOM_BYTES = GENERATE_RANDOM_BYTES *;


CLASS_DECL_ACME void set_generate_random_bytes(PFN_GENERATE_RANDOM_BYTES pfngeneraterandombytes);
CLASS_DECL_ACME void generate_random_bytes(void * p, memsize s);




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


template < typename TYPE1, typename TYPE2 >
inline constexpr bool __lt(const TYPE1 & a, const TYPE2 & b) { return a < b; }
template < typename TYPE1, typename TYPE2 >
inline constexpr bool __le(const TYPE1 & a, const TYPE2 & b) { return a <= b; }


template < typename T1, typename T2 >
inline constexpr auto __ge(const T1 & a, const T2 & b) { return __le(b, a); }

template < typename T1, typename T2 >
inline constexpr auto __gt(const T1 & a, const T2 & b) { return __lt(b, a); }


template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
constexpr typename largest_type < SIGNED1, SIGNED2 >::type minimum(const SIGNED1 & a, const SIGNED2 & b) { return __lt(a, b) ? ((typename largest_type < SIGNED1, SIGNED2 >::type)a ): ((typename largest_type < SIGNED1, SIGNED2 >::type)b); }

template < primitive_unsigned UNSIGNED1, primitive_signed SIGNED2 >
constexpr SIGNED2 minimum(const UNSIGNED1 & a, const SIGNED2 & b) { return __lt(a, b) ? ((SIGNED2) a) : b; }

template < primitive_signed SIGNED1, primitive_unsigned UNSIGNED2 >
constexpr SIGNED1 minimum(const SIGNED1 & a, const UNSIGNED2 & b) { return __lt(a, b) ? a : ((SIGNED1) b); }

template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
constexpr typename largest_type < UNSIGNED1, UNSIGNED2 >::type minimum(const UNSIGNED1 & a, const UNSIGNED2 & b) { return __lt(a, b) ? ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)a) : ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)b); }


template < primitive_integral INTEGRAL1, primitive_floating FLOATING2 >
constexpr FLOATING2 minimum(const INTEGRAL1 & a, const FLOATING2 & b) { return __lt(a, b) ? ((FLOATING2)a) : b; }

template < primitive_floating FLOATING1, primitive_integral INTEGRAL2 >
constexpr FLOATING1 minimum(const FLOATING1 & a, const INTEGRAL2 & b) { return __lt(a, b) ? a : ((FLOATING1)b); }

template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
constexpr typename largest_type < FLOATING1, FLOATING2 >::type minimum(const FLOATING1 & a, const FLOATING2 & b) { return __lt(a, b) ? ((typename largest_type < FLOATING1, FLOATING2 >::type)a) : ((typename largest_type < FLOATING1, FLOATING2 >::type)b); }


template < typename TYPE1, typename TYPE2 >
constexpr TYPE1 minimum(const TYPE1 & a, const TYPE2 & b) { return __lt(a, b) ? a : ((TYPE1)b); }



template < primitive_signed SIGNED1, primitive_signed SIGNED2 >
constexpr typename largest_type < SIGNED1, SIGNED2 >::type maximum(const SIGNED1 & a, const SIGNED2 & b) { return __lt(b, a) ? ((typename largest_type < SIGNED1, SIGNED2 >::type)a) : ((typename largest_type < SIGNED1, SIGNED2 >::type)b); }

template < primitive_unsigned UNSIGNED1, primitive_signed SIGNED2 >
constexpr SIGNED2 maximum(const UNSIGNED1 & a, const SIGNED2 & b) { return __lt(b, a) ? ((SIGNED2)a) :  b; }

template < primitive_signed SIGNED1, primitive_unsigned UNSIGNED2 >
constexpr SIGNED1 maximum(const SIGNED1 & a, const UNSIGNED2 & b) { return __lt(b, a) ?  a : ((SIGNED1)b); }

template < primitive_unsigned UNSIGNED1, primitive_unsigned UNSIGNED2 >
constexpr typename largest_type < UNSIGNED1, UNSIGNED2 >::type maximum(const UNSIGNED1 & a, const UNSIGNED2 & b) { return __lt(b, a) ? ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)a) : ((typename largest_type < UNSIGNED1, UNSIGNED2 >::type)b); }

template < primitive_integral INTEGRAL1, primitive_floating FLOATING2 >
constexpr FLOATING2 maximum(const INTEGRAL1 & a, const FLOATING2 & b) { return __lt(b, a) ? ((FLOATING2)a) : b; }

template < primitive_floating FLOATING1, primitive_integral INTEGRAL2 >
constexpr FLOATING1 maximum(const FLOATING1 & a, const INTEGRAL2 & b) { return __lt(b, a) ? a : ((FLOATING1)b); }

template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
constexpr typename largest_type < FLOATING1, FLOATING2 >::type maximum(const FLOATING1 & a, const FLOATING2 & b) { return __lt(b, a) ? ((typename largest_type < FLOATING1, FLOATING2 >::type)a) : ((typename largest_type < FLOATING1, FLOATING2 >::type)b); }

template < typename TYPE1, typename TYPE2 >
constexpr TYPE1 maximum(const TYPE1 & a, const TYPE2 & b) { return __lt(b, a) ? a : ((TYPE1)b); }



#include "count.h"


#include "index.h"



template < primitive_signed SIGNED >
inline bool __found(SIGNED i) { return i >= 0; }
template < primitive_signed SIGNED >
inline bool __not_found(SIGNED i) { return i < 0; }




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





inline byte __byte_rate(double dRate, double dMin, double dMax)
{

   return (byte)(dRate * (dMax - dMin) + dMin);

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



//#endif







