//
//  apple_time.cpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 01/10/17.
//

#include "framework.h"
#include "acid/platform/system_setup.h"



//#include <mach/clock.h>
//#include <mach/mach.h>
#include <mach/mach_time.h>

//extern clock_serv_t g_cclock;

namespace acid
{
extern double g_machtime_conversion_factor;
} // namespace acid
void ns_Sleep(unsigned int uiMillis);


CLASS_DECL_ACID ::i64 _get_nanosecond()
{
   
   return mach_absolute_time() * ::acid::g_machtime_conversion_factor;
   
   //   mach_timespec_t mts;
   //
   //   clock_get_time(g_cclock, &mts);
   //
   //   return ((u64) mts.tv_sec * (u64)1000 * (u64)1000 * (u64)1000 )+ ((u64) mts.tv_nsec);
   
}

void utc_timespec(timespec * ptimespec);

CLASS_DECL_ACID ::i64 i64_nanosecond()
{
   
   struct timespec timespec;

   utc_timespec(&timespec);

   return timespec.tv_sec * 1'000'000'000 + timespec.tv_nsec;

}



