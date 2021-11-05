#include "framework.h"
#include <time.h>


extern "C"
struct tm *gmtime_r(const time_t *timep,struct tm *result)
{

#ifdef WINDOWS


   if(gmtime_s(result,timep) != 0)
      return nullptr;

   return result;

#else

   static ::mutex m;
   synchronous_lock synchronouslock(&m);
   struct tm *tmp;
   tmp = gmtime(timep);
   *result = *tmp;
   return result;

#endif

}

#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)

#include <time.h>
#include <sys/timeb.h>
//#include <winpr/windows.h>

// From FreeRDP utils_pcap.c - 2015-07-24
extern "C"
int gettimeofday(struct timeval* tp, void* tz)
{
   struct _timeb timebuffer;
   _ftime(&timebuffer);
   tp->tv_sec = (long)timebuffer.time;
   tp->tv_usec = timebuffer.millitm * 1000;
   return 0;
}


#endif

