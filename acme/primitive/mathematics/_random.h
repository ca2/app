// from acme/include/_.h by camilo on 2022-11-08 00:52 <3ThomasBorregaardSorensen!!
#pragma once




template<typename TYPE>
inline TYPE* __random_bytes(TYPE* p, memsize s);

template<typename TYPE>
inline TYPE& __random(TYPE& t);

template<typename TYPE>
inline TYPE __random();



template < primitive_floating FLOATING1, primitive_floating FLOATING2, primitive_floating FLOATING_RESULT = typename ::largest_type < FLOATING1, FLOATING2 >::type >
inline FLOATING_RESULT __random(FLOATING1 i1, FLOATING2 i2);


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL_RESULT = typename ::largest_type < INTEGRAL1, INTEGRAL2 >::type >
inline INTEGRAL_RESULT __random(INTEGRAL1 i1, INTEGRAL2 i2);



