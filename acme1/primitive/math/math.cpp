#include "framework.h"
//#include <math.h>


::i64 ceil_div(i64 num, i64 den)
{
   i64 quo = num / den;
   if((num % den) > 0)
      quo++;
   return quo;
}


double tri(double angle)
{

   angle = fmod(angle,3.1415 * 2.0) * 2.0 / 3.1415;

   if(angle < 1.0)
      return angle;
   else if(angle >= 1.0 && angle < 3.0)
      return 2.0 - angle;
   else
      return angle - 4.0;


}


CLASS_DECL_ACME extern const char log2_LogTable256[256] =
{
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
   (char)- 1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
   LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
   LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};
