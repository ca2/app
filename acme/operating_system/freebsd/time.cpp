#include "framework.h"
#include <sys/time.h>
#include <time.h>


CLASS_DECL_ACME INTEGRAL_NANOSECOND get_integral_nanosecond()
{
#ifdef RASPBIAN

   struct timeval tv;

   if(gettimeofday(&tv, nullptr) != 0)
   {

      return 0;

   }

   return tv.tv_sec * 1000 * 1000 * 1000 + tv.tv_usec * 1000;

#else

   struct timespec ts;

   if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
   {

      //error
      return INTEGRAL_NANOSECOND(0);

   }

   return INTEGRAL_NANOSECOND(ts.tv_sec * 1'000'000'000 + ts.tv_nsec);

#endif

}