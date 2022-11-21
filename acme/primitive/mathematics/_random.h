// from acme/include/_.h by camilo on 2022-11-08 00:52 <3ThomasBorregaardSorensen!!
#pragma once




template<typename TYPE>
inline TYPE* __random_bytes(TYPE* p, memsize s);

template<typename TYPE>
inline TYPE& __random(TYPE& t);

template<typename TYPE>
inline TYPE __random();



//template < primitive_floating FLOATING1, primitive_floating FLOATING2, primitive_floating FLOATING_RESULT = typename ::largest_type < FLOATING1, FLOATING2 >::type >
//inline FLOATING_RESULT __random(const FLOATING1 & i1, const FLOATING2 & i2);
//
//
//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL_RESULT = typename ::largest_type < INTEGRAL1, INTEGRAL2 >::type >
//inline INTEGRAL_RESULT __random(const INTEGRAL1 & i1, const INTEGRAL2 & i2);


template < primitive_floating FLOATING1, primitive_floating FLOATING2, primitive_floating FLOATING_RESULT = typename ::largest_type < FLOATING1, FLOATING2 >::type >
inline FLOATING_RESULT __random(const FLOATING1 & f1, const FLOATING2 & f2)
{

   if (f1 == f2) return f1;

   FLOATING_RESULT fMin = minimum(f1, f2);

   FLOATING_RESULT fMax = maximum(f1, f2);

   FLOATING_RESULT fRange = fMax - fMin;

   ::u64 u;

   __random(u);

   return (FLOATING_RESULT) (((u * fRange) / (FLOATING_RESULT)MAXU64) + fMin);

}



template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL_RESULT = typename ::largest_type < INTEGRAL1, INTEGRAL2 >::type >
inline INTEGRAL_RESULT __random(const INTEGRAL1 & i1, const INTEGRAL2 & i2)
{

   if (i1 == i2) return i1;

   INTEGRAL_RESULT iMin = minimum(i1, i2);

   INTEGRAL_RESULT iMax = maximum(i1, i2);

   INTEGRAL_RESULT iRange = iMax - iMin;

   u64 u;

   __random(u);

   return(INTEGRAL_RESULT) ((u % (iRange + 1)) + iMin);

}

