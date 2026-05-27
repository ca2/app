#include "framework.h"
//#include "aqua.h"
#include <math.h>

CLASS_DECL_AURA void pre_multiply_alpha(::u32 * puserinteraction, ::i32 cx, ::i32 cy, ::i32 stride)
{
   ::u8 * p = (::u8 *)puserinteraction;
   ::u8 a1;
   ::u8 a2;
   ::u8 a3;
   ::u8 a4;
   ::i32 s = stride * cy / 16;
#pragma loop(hint_parallel(0))
   for (::i32 i = 0; i < s; i++)
   {
      a1 = p[3];
      a2 = p[7];
      a3 = p[11];
      a4 = p[15];

      p[0] = (p[0] * a1) >> 8;
      p[1] = (p[1] * a1) >> 8;
      p[2] = (p[2] * a1) >> 8;

      p[4] = (p[4] * a2) >> 8;
      p[5] = (p[5] * a2) >> 8;
      p[6] = (p[6] * a2) >> 8;

      p[8] = (p[8] * a3) >> 8;
      p[9] = (p[9] * a3) >> 8;
      p[10] = (p[10] * a3) >> 8;

      p[12] = (p[12] * a4) >> 8;
      p[13] = (p[13] * a4) >> 8;
      p[14] = (p[14] * a4) >> 8;
      //puserinteraction[i]=((puserinteraction[i] & 0xff000000) >> 24) << 24
      //   | (((((puserinteraction[i] & 0xff0000) >> 16) * ((puserinteraction[i] & 0xff000000) >> 24)) << 8) & 0xff0000)
      //   | ((((puserinteraction[i] & 0xff00) >> 8) * ((puserinteraction[i] & 0xff000000) >> 24)) & 0xff00)
      //   | (((puserinteraction[i] & 0xff) * ((puserinteraction[i] & 0xff000000) >> 24)) >> 8);
      //puserinteraction++;
      p += 16;
   }

}

/*
extern "C"
::f64 hypot(::f64 x,::f64 y)
{
   return sqrt(x*x + y*y);
}
*/
