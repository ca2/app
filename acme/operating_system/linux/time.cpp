#include "framework.h"
#include <sys/time.h>
#include <time.h>


CLASS_DECL_ACME ::i64 integral_nanosecond()
{
   
#ifdef RASPBIAN

   struct timeval tv;

   if(gettimeofday(&tv, nullptr) != 0)
   {

      return integral_nanosecond(0);

   }

   return integral_nanosecond(tv.tv_sec * 1000'000'000 + tv.tv_usec * 1'000);

#else

   struct timespec ts;

   if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
   {

      return 0;

   }

   return ts.tv_sec * 1'000'000'000 + ts.tv_nsec;

#endif

}



