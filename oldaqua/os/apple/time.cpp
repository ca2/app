//
//  apple_time.cpp
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/17.
//

#include "framework.h"
#include "aqua/platform/static_start.h"



//#include <mach/clock.h>
//#include <mach/mach.h>
#include <mach/mach_time.h>

//extern clock_serv_t g_cclock;
//extern double g_machtime_conversion_factor;

void ns_Sleep(unsigned int uiMillis);


CLASS_DECL_AQUA i64 get_nanos()
{
   
   return ::aqua::mach_absolute_time() * ::aqua::g_machtime_conversion_factor;
   
   //   mach_timespec_t mts;
   //
   //   clock_get_time(g_cclock, &mts);
   //
   //   return ((u64) mts.tv_sec * (u64)1000 * (u64)1000 * (u64)1000 )+ ((u64) mts.tv_nsec);
   
}
