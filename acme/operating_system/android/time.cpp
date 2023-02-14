// From linux/time.cpp by camilo on 2022-04-30 03:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include <sys/time.h>
#include <time.h>


CLASS_DECL_ACME ::i64 integral_nanosecond()
{

#ifdef RASPBIAN

   struct timeval tv;

   if (gettimeofday(&tv, nullptr) != 0)
   {

      return integral_nanosecond(0);

   }

   return integral_nanosecond(tv.tv_sec * 1000'000'000 + tv.tv_usec * 1'000);

#else

   struct timespec ts;

   if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
   {

      return integral_nanosecond(0);

   }

   return integral_nanosecond((::u64)ts.tv_sec * 1'000'000'000ull + (::u64)ts.tv_nsec);

#endif

}






//#include "linux/byteorder/swab.h"
//#include <math.h>
//#include <float.h>


//extern "C"
//{

   //extern "C"
CLASS_DECL_ACME i64 get_nanos()
{

   struct timespec ts;

   if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
   {
      //error
      return 0;
   }

   u64 u = ts.tv_sec;

   u *= 1000 * 1000 * 1000;

   u += ts.tv_nsec;

   return  u;

}

//} // extern "C"



















