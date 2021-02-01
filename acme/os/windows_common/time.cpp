#include "framework.h"
#include "acme/operating_system.h"




//CLASS_DECL_ACME void sleep(const ::duration& duration)
//{
//
//   auto millis = duration.millis();
//
//   ::sleep(millis);
//
//}


CLASS_DECL_ACME void sleep(const ::secs & secs)
{

   ::Sleep((DWORD) (secs.m_i * 1'000));

}


CLASS_DECL_ACME void sleep(const millis & millis)
{

   ::Sleep((DWORD) millis.m_i);

}


CLASS_DECL_ACME void sleep(const micros & micros)
{

   ::Sleep(1);

}


CLASS_DECL_ACME void sleep(const nanos & nanos)
{

   ::Sleep(1);

}






#include <time.h>
#include <sys/timeb.h>
//#include <winpr/windows.h>

// From FreeRDP utils_pcap.c - 2015-07-24
extern "C"
int gettimeofday(struct timeval * tp, void * tz)
{
   struct _timeb timebuffer;
   _ftime(&timebuffer);
   tp->tv_sec = (long)timebuffer.time;
   tp->tv_usec = timebuffer.millitm * 1000;
   return 0;
}



