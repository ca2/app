#pragma once


template < typename T1, typename T2 >
inline bool clip_convert(T1& t1, const T2& t2);


template < typename T1, typename T2 >
inline T1 clip_convert(const T2& t2);


template < typename T1, typename T2 >
inline bool clip_convert_add(T1& t1, const T2& t2);


template < typename T1, typename T2 >
inline bool clip_convert_difference(T1& t1, const T2& t2);


template < typename T1, typename T2 >
inline bool clip_convert_multiply(T1& t1, const T2& t2);


// division by zero protection isn't this function's current responsability and maybe never should be
template < typename T1, typename T2 >
inline bool clip_convert_divide(T1& t1, const T2& t2);


template < typename TMIN, typename TMAX, typename T  >
inline T& clip(const TMIN& minimum, const TMAX& maximum, T& t);



