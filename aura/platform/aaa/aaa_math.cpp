#include "framework.h"

#ifndef X86
//#include <math.h>
#endif

static int lastrand;

#ifdef WINDOWS
//extern "C" int _fltused = 0;
#else
int _fltused = 0;
#endif


CLASS_DECL_AURA int abs_dup(int i)
{
   if(i < 0)
      return -i;
   else
      return i;
}

CLASS_DECL_AURA double fabs_dup(double f)
{
   if(f < 0.0)
      return -f;
   else
      return f;
}

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_AURA double atan_dup(double d)
{
#ifdef X86
    _asmxxx
    {
        fld unsigned int PTR [d]
        fatan
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return atan(d);
#endif
}

CLASS_DECL_AURA double asin_dup(double d)
{
   return 2.0 * atan_dup(d / (1.0 + sqrt_dup(1.0 - d * d)));
}

CLASS_DECL_AURA double acos_dup(double d)
{
   return 2.0 * atan_dup(sqrt_dup(1.0 - d * d) / (1.0 + d));
}

CLASS_DECL_AURA double sqrt_dup(double d)
{
#ifdef X86
    _asmxxx
    {
        fld unsigned int PTR [d]
        fsqrt
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return sqrt(d);
#endif
}

CLASS_DECL_AURA double pow_dup(double aura, double e)
{
   return exp_dup(e * log_dup(aura));
}


CLASS_DECL_AURA double fmod_dup(double x, double y)
{
   return fmod(x, y);
}

CLASS_DECL_AURA double exp_dup(double d)
{
#ifdef X86
    _asmxxx
    {
        fld unsigned int PTR [d]
        fexp
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return exp(d);
#endif
}

CLASS_DECL_AURA double log_dup(double d)
{
#ifdef X86
    _asmxxx
    {
        fld unsigned int PTR [d]
        flog
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return log(d);
#endif
}

CLASS_DECL_AURA double tan_dup(double d)
{
#ifdef X86
    _asmxxx
    {
        fld unsigned int PTR [d]
        ftan
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return tan(d);
#endif
}

CLASS_DECL_AURA double sin_dup(double d)
{
#ifdef X86
    _asmxxx
    {
        fld unsigned int PTR [d]
        fsin
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return sin(d);
#endif
}

CLASS_DECL_AURA double cos_dup(double d)
{
#ifdef X86
    _asmxxxx
    {
        fld unsigned int PTR [d]
        fcos
        fstp unsigned int ptr[d]
    }
    return d;
#else
    return cos(d);
#endif
}

#endif

CLASS_DECL_AURA void srand_dup(unsigned int seed)
{
	lastrand = seed;
}

CLASS_DECL_AURA  int rand_dup()
{
	return (((lastrand = lastrand * 214013L + 2531011L) >> 16) & 0x7FFF);
}


/*long long ftoi64(double d)
{
   long long u = 0x7fffffffffffffff;
   long long l = 0x8000000000000000;
   double m;
   while(true)
   {
      if(u <= l)
         return l;
      m = ((double) u + (double) l) / 2.0;
      if(d >= m)
      {
         l = u / 2 + l / 2;
      }
      else
      {
         u = u / 2 + l / 2;
      }
   }
}*/

int ftol(double d)
{
   int u = I32_MAXIMUM;
   int l = I32_MINIMUM;
   double m;
   double delta;
   int i = 0;
   while(i < 128)
   {
      if(u <= l)
         return l;
      m = ((double) u + (double) l) / 2.0;
      delta = d - m;
      if(delta >= 0.0)
      {
         if(delta <= 0.5)
            return l;
         l = u / 2 + l / 2;
      }
      else
      {
         if(delta >= -0.5)
            return l;
         u = u / 2 + l / 2;
      }
      i++;
   }
   return l;
}
