#include "framework.h"


void dump_context::write(float f)
{

   char szBuffer[32];

#ifdef WINDOWS

   _gcvt_s(szBuffer, 32, f, FLT_DIG);

#elif defined(ANDROID)

   sprintf(szBuffer, "%.6f", f);

#else

   gcvt(f, FLT_DIG, szBuffer);

#endif

   return write(szBuffer);

}


void dump_context::write(double d)
{

   char szBuffer[32];

#ifdef WINDOWS

   _gcvt_s(szBuffer, 32, d, DBL_DIG);

#elif defined(ANDROID)

   sprintf(szBuffer, "%.6f", d);

#else

   gcvt(d, DBL_DIG, szBuffer);

#endif

   return write(szBuffer);

}



