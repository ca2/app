#include "framework.h"
#include "acme/operating_system.h"
#include <time.h>


//CLASS_DECL_ACME void sleep(const ::duration& duration)
//{
//
//   auto millis = duration.millis();
//
//   ::sleep(millis);
//
//}

CLASS_DECL_ACME void preempt(const ::secs & secs)
{

   ::Sleep((DWORD) (secs.m_i * 1'000));

}


CLASS_DECL_ACME void preempt(const millis & millis)
{

   ::Sleep((DWORD) millis.m_i);

}


CLASS_DECL_ACME void preempt(const micros & micros)
{

   ::Sleep(1);

}


CLASS_DECL_ACME void preempt(const nanos & nanos)
{

   ::Sleep(1);

}


thread_local nano_timer t_nanotimer;


CLASS_DECL_ACME void precision_wait_seconds(double d)
{

   t_nanotimer.wait_nano((::u64) (d * 1'000'000'000.0));

}


CLASS_DECL_ACME void precision_wait_milliseconds(double d)
{

   t_nanotimer.wait_nano((::u64)(d * 1'000'000.0));

}


CLASS_DECL_ACME void precision_wait_microseconds(double d)
{

   t_nanotimer.wait_nano((::u64)(d * 1'000.0));

}


CLASS_DECL_ACME void precision_wait_nanoseconds(::u64 u)
{

   t_nanotimer.wait_nano(u);

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


::e_status get_system_time(system_time_t* psystemtime)
{

   ::GetSystemTime((LPSYSTEMTIME)psystemtime);

   return ::success;

}





::e_status system_time_to_time(time_t* ptime, const system_time_t* psystemtime, i32 nDST)
{

   struct tm tm;

   __copy(tm, psystemtime);

   *ptime = _mkgmtime(&tm);

   return ::success;

}


::e_status system_time_to_file_time(filetime_t* pfiletime, const system_time_t* psystemtime)
{

   if (!SystemTimeToFileTime((const SYSTEMTIME*)psystemtime, (FILETIME*)pfiletime))
   {

      return error_failed;

   }

   return success;

}


::e_status time_to_system_time(system_time_t* psystemtime, const time_t* ptime)
{
   
   struct tm tm;

   gmtime_r(ptime, &tm);

   __copy(psystemtime, tm);

   return ::success;

}


::e_status time_to_file_time(filetime_t* pfiletime, const time_t* ptime)
{

   system_time_t systemtime;

   auto estatus = time_to_system_time(&systemtime, ptime);

   if(!estatus)
   {

      return estatus;

   }

   estatus = system_time_to_file_time(pfiletime, &systemtime);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}






//
//CLASS_DECL_ACME int_bool get_filetime(HANDLE hFile, LPFILETIME pCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
//{
//
//   return GetFileTime(hFile, pCreationTime, lpLastAccessTime, lpLastWriteTime) != false;
//
//}



CLASS_DECL_ACME ::e_status file_time_to_system_time(system_time_t * psystemtime, const filetime_t * pfiletime)
{

   if (!FileTimeToSystemTime((FILETIME *)pfiletime, (SYSTEMTIME *)psystemtime))
   {

      return error_failed;

   }

   return ::success;

}




//
//
//::e_status file_time_to_system_time(system_time_t * psystemtime, const filetime_t * pfiletime)
//{
//
//   if (!FileTimeToSystemTime((FILETIME *)pfiletime, (SYSTEMTIME *)psystemtime))
//   {
//
//      return error_failed;
//
//   }
//
//   return ::success;
//
//}
//



CLASS_DECL_ACME int_bool get_filetime(HANDLE hFile, LPFILETIME pCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{

   return GetFileTime(hFile, pCreationTime, lpLastAccessTime, lpLastWriteTime) != false;

}

