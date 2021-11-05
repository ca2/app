#include "framework.h"
//#include "aqua.h"
#include <math.h>

CLASS_DECL_AURA void pre_multiply_alpha(unsigned int * puserinteraction, int cx, int cy, int stride)
{
   unsigned char * p = (unsigned char *)puserinteraction;
   unsigned char a1;
   unsigned char a2;
   unsigned char a3;
   unsigned char a4;
   int s = stride * cy / 16;
#pragma loop(hint_parallel(0))
   for (int i = 0; i < s; i++)
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
double hypot(double x,double y)
{
   return sqrt(x*x + y*y);
}
*/
