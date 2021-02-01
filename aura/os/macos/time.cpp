#include "framework.h"
#include <sys/time.h>

// http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
// http://stackoverflow.com/users/346736/jbenet
// https://stackoverflow.com/users/847987/charphacy
// https://stackoverflow.com/users/1211018/point_i32-marecki

//#include <mach/clock.h>
//#include <mach/mach.h>
#include <mach/mach_time.h>

//extern clock_serv_t g_cclock;
//extern double g_machtime_conversion_factor;

void ns_Sleep(unsigned int uiMillis);

//u64 get_nanos()
//{
//
//   return mach_absolute_time() * g_machtime_conversion_factor;
//
//   //   mach_timespec_t mts;
//   //
//   //   clock_get_time(g_cclock, &mts);
//   //
//   //   return ((u64) mts.tv_sec * (u64)1000 * (u64)1000 * (u64)1000 )+ ((u64) mts.tv_nsec);
//
//}

//CLASS_DECL_AURA void sleep(const duration & duration)
//{
//
//   ns_Sleep((unsigned int) duration.get_total_milliseconds());
//
//}


CLASS_DECL_AURA void sleep(unsigned int dwMillis)
{

   usleep(dwMillis * 1000);

}
