// From freebsd/time.cpp by camilo on 2024-09-02 19:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <sys/time.h>
#include <time.h>


CLASS_DECL_ACME long long long_long_nanosecond()
{
#ifdef RASPBERRYPIOS

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
      return 0;

   }

   return ts.tv_sec * 1'000'000'000 + ts.tv_nsec;

#endif

}
