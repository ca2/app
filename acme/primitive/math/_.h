#pragma once

// SIGNED SIGNED
inline constexpr bool __lt(const i64 & a, const i64 & b) { return a < b; }
inline constexpr bool __lt(const i32 & a, const i64 & b) { return a < b; }
inline constexpr bool __lt(const i64 & a, const i32 & b) { return a < b; }

// UNSIGNED SIGNED
inline constexpr bool __lt(const UINT & a, const int & b) { return b < 0 ? false : a < static_cast < u32 > (b); }
inline constexpr bool __lt(const size_t & a, const i64 & b) { return b < 0 ? false : a < static_cast < u64 > (b); }

// SIGNED UNSIGNED
inline constexpr bool __lt(const int & a, const UINT & b) { return a < 0 ? true : static_cast <u32> (a) < b; }
inline constexpr bool __lt(const i64 & a, const size_t & b) { return a < 0 ? true : static_cast <u64> (a) < b; }


// UNSIGNED SIGNED
inline constexpr bool __le(const UINT & a, const int & b) { return b < 0 ? false : a <= static_cast <u32> (b); }
inline constexpr bool __le(const size_t & a, const i64 & b) { return b < 0 ? false : a <= static_cast <u64> (b); }

// SIGNED UNSIGNED
inline constexpr bool __le(const int & a, const UINT & b) { return a < 0 ? false : static_cast <u32> (a) <= b; }
inline constexpr bool __le(const i64 & a, const size_t & b) { return a < 0 ? false : static_cast <u64> (a) <= b; }


template < typename A, typename B >
inline constexpr auto __gt(const A & a, const B & b) { return __lt(b, a); }

template < typename A, typename B >
inline constexpr auto __ge(const A & a, const B & b) { return __le(b, a); }


// UNSIGNED SIGNED
constexpr int __min(const UINT & a, const int & b) { return __lt(a, b) ? (i32) a : b; }
constexpr i64 __min(const size_t & a, const i64 & b) { return __lt(a, b) ? (i64) a : b; }

// SIGNED UNSIGNED
constexpr int __min(const int & a, const UINT & b) { return __lt(a, b) ? a : (i32) b; }
constexpr i64 __min(const i64 & a, const size_t & b) { return __lt(a, b) ? a : (i64) b; }


// UNSIGNED SIGNED
constexpr UINT __max(const UINT & a, const int & b) { return __lt(b, a) ? a : (UINT) b; }
constexpr size_t __max(const size_t & a, const i64 & b) { return __lt(b, a) ? a : (size_t) b; }

// SIGNED UNSIGNED
constexpr UINT __max(const int & a, const UINT & b) { return __lt(b, a) ? (UINT) a : b; }
constexpr size_t __max(const i64 & a, const size_t & b) { return __lt(b, a) ? (size_t) a : b; }


#include "count.h"


#include "index.h"


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
