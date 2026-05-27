#pragma once




#define INTABS(i) (((i) >= 0) ? (i) : (-(i)))
#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-(f)))
#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-(d)))

//#ifndef
//#define minimum(a, b) (((a) < (b)) ? (a) : (b))
//#define maximum(a, b) (((b) < (a)) ? (a) : (b))


inline bool is_almost_equal(::f64 d1, ::f64 d2, ::f64 dTolerance)
{
   
   return DOUBLEABS(d1-d2) < dTolerance;
   
}

inline bool is_different(::f64 d1, ::f64 d2, ::f64 dTolerance)
{
   
   return !is_almost_equal(d1, d2, dTolerance);
   
}
