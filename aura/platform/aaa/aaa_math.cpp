#include "framework.h"

#ifndef X86
//#include <math.h>
#endif

static ::i32 lastrand;

#ifdef WINDOWS
//extern "C" ::i32 _fltused = 0;
#else
::i32 _fltused = 0;
#endif


CLASS_DECL_AURA ::i32 abs_dup(::i32 i)
{
   if(i < 0)
      return -i;
   else
      return i;
}

CLASS_DECL_AURA ::f64 fabs_dup(::f64 f)
{
   if(f < 0.0)
      return -f;
   else
      return f;
}

#ifdef SUPORTA_MATEMATICA_AVANCADA
CLASS_DECL_AURA ::f64 atan_dup(::f64 d)
{
#ifdef X86
    _asmxxx
    {
        fld ::u32 PTR [d]
        fatan
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return atan(d);
#endif
}

CLASS_DECL_AURA ::f64 asin_dup(::f64 d)
{
   return 2.0 * atan_dup(d / (1.0 + sqrt_dup(1.0 - d * d)));
}

CLASS_DECL_AURA ::f64 acos_dup(::f64 d)
{
   return 2.0 * atan_dup(sqrt_dup(1.0 - d * d) / (1.0 + d));
}

CLASS_DECL_AURA ::f64 sqrt_dup(::f64 d)
{
#ifdef X86
    _asmxxx
    {
        fld ::u32 PTR [d]
        fsqrt
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return sqrt(d);
#endif
}

CLASS_DECL_AURA ::f64 pow_dup(::f64 aura, ::f64 e)
{
   return exp_dup(e * log_dup(aura));
}


CLASS_DECL_AURA ::f64 fmod_dup(::f64 x, ::f64 y)
{
   return fmod(x, y);
}

CLASS_DECL_AURA ::f64 exp_dup(::f64 d)
{
#ifdef X86
    _asmxxx
    {
        fld ::u32 PTR [d]
        fexp
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return exp(d);
#endif
}

CLASS_DECL_AURA ::f64 log_dup(::f64 d)
{
#ifdef X86
    _asmxxx
    {
        fld ::u32 PTR [d]
        flog
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return log(d);
#endif
}

CLASS_DECL_AURA ::f64 tan_dup(::f64 d)
{
#ifdef X86
    _asmxxx
    {
        fld ::u32 PTR [d]
        ftan
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return tan(d);
#endif
}

CLASS_DECL_AURA ::f64 sin_dup(::f64 d)
{
#ifdef X86
    _asmxxx
    {
        fld ::u32 PTR [d]
        fsin
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return sin(d);
#endif
}

CLASS_DECL_AURA ::f64 cos_dup(::f64 d)
{
#ifdef X86
    _asmxxxx
    {
        fld ::u32 PTR [d]
        fcos
        fstp ::u32 ptr[d]
    }
    return d;
#else
    return cos(d);
#endif
}

#endif

CLASS_DECL_AURA void srand_dup(::u32 seed)
{
	lastrand = seed;
}

CLASS_DECL_AURA  ::i32 rand_dup()
{
	return (((lastrand = lastrand * 214013L + 2531011L) >> 16) & 0x7FFF);
}


/*::i64 ftoi64(::f64 d)
{
   ::i64 u = 0x7fffffffffffffff;
   ::i64 l = 0x8000000000000000;
   ::f64 m;
   while(true)
   {
      if(u <= l)
         return l;
      m = ((::f64) u + (::f64) l) / 2.0;
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

::i32 ftol(::f64 d)
{
   ::i32 u = I32_MAXIMUM;
   ::i32 l = I32_MINIMUM;
   ::f64 m;
   ::f64 delta;
   ::i32 i = 0;
   while(i < 128)
   {
      if(u <= l)
         return l;
      m = ((::f64) u + (::f64) l) / 2.0;
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
