#include "framework.h"

#include <sys/time.h>

unsigned int GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (unsigned int) ((ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu);

}



//unsigned int ::get_tick()
//{
//
//   return (unsigned int) GetTickCount();
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

//unsigned long long get_nanos()
//{
//   
//   clock_serv_t cclock;
//   mach_timespec_t mts;
//   host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
//   clock_get_time(cclock, &mts);
//   mach_port_deallocate(mach_task_self(), cclock);
//   
//   return ((unsigned long long) mts.tv_sec * (unsigned long long)1000 * (unsigned long long)1000 * (unsigned long long)1000 )+ ((unsigned long long) mts.tv_nsec);
//   
//}
//



//CLASS_DECL_ACME void sleep(const class time & time)
//{
//   
//   usleep((unsigned int) time.get_total_milliseconds() * 1000);
//   
//}


//CLASS_DECL_ACME void sleep(unsigned int dwMillis)
//{
//
//   usleep(dwMillis * 1000);
//
//}

