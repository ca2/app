#pragma once




#define INTABS(i) (((i) >= 0) ? (i) : (-i))
#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-f))
#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-d))

//#ifndef
//#define minimum(a, b) (((a) < (b)) ? (a) : (b))
//#define maximum(a, b) (((b) < (a)) ? (a) : (b))


inline bool is_same(double d1, double d2, double dTolerance)
{
   
   return DOUBLEABS(d1-d2) < dTolerance;
   
}

inline bool is_different(double d1, double d2, double dTolerance)
{
   
   return !is_same(d1, d2, dTolerance);
   
}
