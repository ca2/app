#include "framework.h"


inline DWORD GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}



//DWORD ::get_tick()
//{
//
//   return (DWORD) GetTickCount();
//
//}
//
//
//





#include "framework.h"
#include <sys/time.h>

// http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
// http://stackoverflow.com/users/346736/jbenet

#include <mach/clock.h>
#include <mach/mach.h>

//u64 get_nanos()
//{
//   
//   clock_serv_t cclock;
//   mach_timespec_t mts;
//   host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
//   clock_get_time(cclock, &mts);
//   mach_port_deallocate(mach_task_self(), cclock);
//   
//   return ((u64) mts.tv_sec * (u64)1000 * (u64)1000 * (u64)1000 )+ ((u64) mts.tv_nsec);
//   
//}
//



//CLASS_DECL_ACME void sleep(const duration & duration)
//{
//   
//   usleep((unsigned int) duration.get_total_milliseconds() * 1000);
//   
//}


CLASS_DECL_ACME void Sleep(unsigned int dwMillis)
{
   
   usleep(dwMillis * 1000);
   
}

