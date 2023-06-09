#include "framework.h"


//void dump_context::write(float f)
//{
//
//   char szBuffer[32];
//
//#ifdef WINDOWS
//
//   _gcvt_s(szBuffer, 32, f, FLT_DIG);
//
//#else
//
//   snprintf(szBuffer, sizeof(szBuffer), "%.6f", f);
//
//#endif
//
//   return write(szBuffer);
//
//}
//
//
//void dump_context::write(double d)
//{
//
//   char szBuffer[32];
//
//#ifdef WINDOWS
//
//   _gcvt_s(szBuffer, 32, d, DBL_DIG);
//
//#elif defined(ANDROID) || defined(FREEBSD)
//
//   sprintf(szBuffer, "%.6f", d);
//
//#else
//
//   //gcvt(d, DBL_DIG, szBuffer);
//
//   snprintf(szBuffer, sizeof(szBuffer), "%.6f", d);
//
//#endif
//
//   return write(szBuffer);
//
//}
//
//
//
