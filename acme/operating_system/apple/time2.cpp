//
//  apple_time.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/10/17.
//

#include "framework.h"
#include "acme/platform/system_setup.h"



//#include <mach/clock.h>
//#include <mach/mach.h>
#include <mach/mach_time.h>

//extern clock_serv_t g_cclock;

namespace acme
{
extern double g_machtime_conversion_factor;
} // namespace acme
void ns_Sleep(unsigned int uiMillis);


CLASS_DECL_ACME long long _get_nanosecond()
{
   
   return mach_absolute_time() * ::acme::g_machtime_conversion_factor;
   
   //   mach_timespec_t mts;
   //
   //   clock_get_time(g_cclock, &mts);
   //
   //   return ((unsigned long long) mts.tv_sec * (unsigned long long)1000 * (unsigned long long)1000 * (unsigned long long)1000 )+ ((unsigned long long) mts.tv_nsec);
   
}

void utc_timespec(timespec * ptimespec);

CLASS_DECL_ACME long long long_long_nanosecond()
{
   
   struct timespec timespec;

   utc_timespec(&timespec);

   return timespec.tv_sec * 1'000'000'000 + timespec.tv_nsec;

}



