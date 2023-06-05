// from acme/include/_.h by camilo on 2022-11-08 00:52 <3ThomasBorregaardSørensen!!
#pragma once




template<typename TYPE>
inline TYPE* random(TYPE* p, memsize s);

template<typename TYPE>
inline TYPE& random(TYPE& t);

template<typename TYPE>
inline TYPE random();


template < typename UNIT_TYPE, primitive_number NUMBER >
inline UNIT_TYPE linear_rate(const UNIT_TYPE & t1, const UNIT_TYPE & t2, NUMBER numerator, NUMBER denominator)
{

   if (t2 == t1)
   {

      return t1;

   }

   return (UNIT_TYPE)(((double)(t2 - t1) * (double)numerator / (double)denominator) + (double)t1);

}


template < typename UNIT_TYPE >
inline UNIT_TYPE minimum_maximum_rand(const UNIT_TYPE & t1, const UNIT_TYPE & t2)
{

   return linear_rate(t1, t2, ::rand(), RAND_MAX);

}


template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
inline ::largest_type < FLOATING1, FLOATING2 > random(const FLOATING1 & f1, const FLOATING2 & f2)
{

   if (f1 == f2) return f1;

   ::largest_type < FLOATING1, FLOATING2 > fMin = minimum(f1, f2);

   ::largest_type < FLOATING1, FLOATING2 > fMax = maximum(f1, f2);

   ::largest_type < FLOATING1, FLOATING2 > fRange = fMax - fMin;

   ::u64 u;

   random(u);

   return (::largest_type < FLOATING1, FLOATING2 >) (((u * fRange) / (::largest_type < FLOATING1, FLOATING2 >)MAXU64) + fMin);

}


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
inline ::largest_type < INTEGRAL1, INTEGRAL2 > random(const INTEGRAL1 & i1, const INTEGRAL2 & i2)
{

   if (i1 == i2) return i1;

   ::largest_type < INTEGRAL1, INTEGRAL2 > iMin = minimum(i1, i2);

   ::largest_type < INTEGRAL1, INTEGRAL2 > iMax = maximum(i1, i2);

   ::largest_type < INTEGRAL1, INTEGRAL2 > iRange = iMax - iMin;

   u64 u;

   random(u);

   return(::largest_type < INTEGRAL1, INTEGRAL2 >) ((u % (iRange + 1)) + iMin);

}



