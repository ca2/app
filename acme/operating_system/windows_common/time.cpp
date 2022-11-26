#include "framework.h"
////#include "acme/exception/exception.h"
#include "acme/operating_system/ansi/datetime_c.h"
//#include "acme/operating_system/time.h"
////#include "acme/primitive/datetime/earth_time.h"
#include "acme/primitive/datetime/system_time.h"
#include "acme/platform/nanosecond_timer.h"
#include "acme/_operating_system.h"
#include <time.h>


extern "C"
struct tm * gmtime_r(const time_t * timep, struct tm * result)
{

   if (gmtime_s(result, timep) != 0)
      return nullptr;

   return result;


}


//CLASS_DECL_ACME void sleep(const class time & time)
//{
//
//   auto ::time = time.::time();
//
//   ::sleep(::time);
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


CLASS_DECL_ACME void precision_wait(const class time & timeWait)
{

   t_nanosecondtimer.wait(timeWait);

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


//void get_system_time(system_time_t* psystemtime)
//{
//
//   ::GetSystemTime((LPSYSTEMTIME)psystemtime);
//
//   //return ::success;
//
//}





void system_time_to_time(time_t * ptime, const system_time_t * psystemtime, i32 nDST)
{

   struct tm tm;

   copy(tm, *psystemtime);

   *ptime = make_utc_time(&tm);

}


//void system_time_to_file_time(file_time_t* pfile_time, const system_time_t* psystemtime)
//{
//
//   if (!SystemTimeToFileTime((const SYSTEMTIME*)psystemtime, (FILETIME*)pfile_time))
//   {
//
//      throw ::exception(error_failed);
//
//   }
//
//   //return success;
//
//}


void time_to_system_time(system_time_t* psystemtime, const time_t* ptime)
{
   
   struct tm tm;

   gmtime_r(ptime, &tm);

   copy(*psystemtime, tm);

}


CLASS_DECL_ACME void time_to_file_time(file_time_t* pfile_time, const time_t* ptime)
{

   system_time_t systemtime;

   /*auto estatus = */ time_to_system_time(&systemtime, ptime);

   //if(!estatus)
   //{

   //   return estatus;

   //}

   /* estatus = */ system_time_to_file_time(pfile_time, &systemtime);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}






//
//CLASS_DECL_ACME int_bool get_file_time(HANDLE hFile, LPFILETIME pCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
//{
//
//   return GetFileTime(hFile, pCreationTime, lpLastAccessTime, lpLastWriteTime) != false;
//
//}
//
//
//
//CLASS_DECL_ACME void file_time_to_system_time(system_time_t * psystemtime, const file_time_t * pfile_time)
//{
//
//   FileTimeToSystemTime((FILETIME*)pfile_time, (SYSTEMTIME*)psystemtime);
//   //{
//
//   //   return error_failed;
//
//   //}
//
//   //return ::success;
//
//}
//
//


//
//
//void file_time_to_system_time(system_time_t * psystemtime, const file_time_t * pfile_time)
//{
//
//   if (!FileTimeToSystemTime((FILETIME *)pfile_time, (SYSTEMTIME *)psystemtime))
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



CLASS_DECL_ACME int_bool get_file_time(HANDLE hFile, LPFILETIME pCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{

   return GetFileTime(hFile, pCreationTime, lpLastAccessTime, lpLastWriteTime) != false;

}





void FileTimeToSystemTime(const file_time_t* pfile_time, system_time_t* psystemtime)
{

   if (!FileTimeToSystemTime((LPFILETIME) pfile_time, (LPSYSTEMTIME) psystemtime))
   {

      throw ::exception(error_failed);

   }

}



void SystemTimeToFileTime(const system_time_t* psystemtime, file_time_t* pfile_time)
{

   if (!SystemTimeToFileTime((LPSYSTEMTIME)pfile_time, (LPFILETIME)psystemtime))
   {

      throw ::exception(error_failed);

   }

}


void GetSystemTime(system_time_t* psystemtime)
{


   GetSystemTime((LPSYSTEMTIME)psystemtime);


}


void file_time_to_system_time(system_time_t * psystemtime, const file_time_t * pfile_time)
{

   FileTimeToSystemTime((FILETIME *) pfile_time, (SYSTEMTIME *) psystemtime);

}


void system_time_to_file_time(file_time_t * pfile_time, const system_time_t * psystemtime)
{

   SystemTimeToFileTime((SYSTEMTIME *) psystemtime, (FILETIME *) pfile_time);

}


//void get_system_time(system_time_t * psystemtime)
//{
//
//   GetSystemTime((SYSTEMTIME *) psystemtime);
//
//}



void get_system_time(system_time_t * psystemtime)
{

   GetSystemTime((SYSTEMTIME *) psystemtime);

}


void datetime_to_filetime(::file_time_t * pfiletime, const ::earth::time & time)
{

   SYSTEMTIME sysTime;

   sysTime.wYear = (::u16)time.year();
   sysTime.wMonth = (::u16)time.month();
   sysTime.wDay = (::u16)time.day();
   sysTime.wHour = (::u16)time.hour();
   sysTime.wMinute = (::u16)time.minute();
   sysTime.wSecond = (::u16)time.second();
   sysTime.wMilliseconds = 0;

   // convert system time to local file time
   FILETIME localTime;

   DWORD dwLastError = ::GetLastError();

   if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
   {

      DWORD dwLastError = ::GetLastError();

      auto estatus = ::windows::last_error_status(dwLastError);

      throw ::exception(estatus);

   }

   // convert local file time to UTC file time
   if (!LocalFileTimeToFileTime(&localTime, (FILETIME *)pfiletime))
   {

      DWORD dwLastError = ::GetLastError();

      auto estatus = ::windows::last_error_status(dwLastError);

      throw ::exception(estatus);

   }

   //return ::success;

}



