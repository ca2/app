#include "framework.h"
#include "acme/operating_system.h"
#include <time.h>


//CLASS_DECL_ACME void sleep(const ::duration& duration)
//{
//
//   auto ::duration = duration.::duration();
//
//   ::sleep(::duration);
//
//}


CLASS_DECL_ACME void preempt(const ::INTEGRAL_SECOND & integralsecond)
{

   ::Sleep((DWORD) (integralsecond.m_i * 1'000));

}


CLASS_DECL_ACME void preempt(const ::INTEGRAL_MILLISECOND & integralmillisecond)
{

   ::Sleep((DWORD)integralmillisecond.m_i);

}


CLASS_DECL_ACME void preempt(const ::INTEGRAL_MICROSECOND & integralmicrosecond)
{

   ::Sleep(1);

}


CLASS_DECL_ACME void preempt(const ::INTEGRAL_NANOSECOND & integralnanosecond)
{

   ::Sleep(1);

}


thread_local nanosecond_timer t_nanosecondtimer;


CLASS_DECL_ACME void precision_wait(const integral_nanosecond & integralnanosecond)
{

   t_nanosecondtimer.wait(integralnanosecond);

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

