#include "framework.h"
////#include "acme/exception/exception.h"
#include "acme/operating_system/ansi/datetime_c.h"

////#include "acme/prototype/datetime/earth_time.h"
#include "acme/prototype/datetime/earth_gregorian_time.h"
#include "acme/prototype/datetime/system_time.h"
#include "acme/platform/nanosecond_timer.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/shared_posix/time.h"
#include "acme/operating_system/time.h"
#include <time.h>


extern "C"
struct tm * gmtime_r(const time_t * timep, struct tm * result)
{

   if (gmtime_s(result, timep) != 0)
   {

      return nullptr;

   }

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


CLASS_DECL_ACME void preempt_second(long long i)
{

   ::Sleep((DWORD) (i * 1'000));

}


CLASS_DECL_ACME void preempt_millisecond(long long i)
{

   ::Sleep((DWORD)i);

}


CLASS_DECL_ACME void preempt_microsecond(long long i)
{

   ::Sleep(1);

}


CLASS_DECL_ACME void preempt_nanosecond(long long i)
{

   ::Sleep(1);

}


// thread_local nanosecond_timer t_nanosecondtimer;


// CLASS_DECL_ACME void precision_wait(const class time & timeWait)
// {

//    t_nanosecondtimer.wait(timeWait);

// }




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


//void get_system_time(system_time* psystemtime)
//{
//
//   ::GetSystemTime((LPSYSTEMTIME)psystemtime);
//
//   //return ::success;
//
//}





void system_time_to_earth_time(posix_time * ptime, const system_time & systemtime, int nDST)
{

   struct tm tm;

   copy(&tm, &systemtime);

   ::earth::gregorian_time gregoriantime;

   copy(&gregoriantime, &tm);

   *ptime = gregoriantime.make_utc_time();

}


//void system_time_to_file_time(file_time* pfile_time, const system_time* psystemtime)
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


//CLASS_DECL_ACME system_time as_system_time(const ::posix_time & posixtime)
//{
//   
//   time_t time = posixtime.m_iSecond;
//
//   struct tm tm;
//
//   gmtime_r(&time, &tm);
//
//   system_time systemtime;
//
//   copy(&systemtime, &tm);
//
//   return systemtime;
//
//}


//CLASS_DECL_ACME file_time as_file_time(const ::posix_time & time)
//{
//
//   auto systemtime = as_system_time(time);
//
//   auto filetime = as_file_time(systemtime);
//
//   return filetime;
//
//}






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
//CLASS_DECL_ACME void file_time_to_system_time(system_time * psystemtime, const ::file_time & filetime)
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
//void file_time_to_system_time(system_time * psystemtime, const ::file_time & filetime)
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





void FileTimeToSystemTime(const file_time* pfile_time, system_time* psystemtime)
{

   if (!FileTimeToSystemTime((LPFILETIME) pfile_time, (LPSYSTEMTIME) psystemtime))
   {

      throw ::exception(error_failed);

   }

}



void SystemTimeToFileTime(const system_time* psystemtime, file_time* pfile_time)
{

   if (!SystemTimeToFileTime((LPSYSTEMTIME)pfile_time, (LPFILETIME)psystemtime))
   {

      throw ::exception(error_failed);

   }

}


void GetSystemTime(system_time* psystemtime)
{


   GetSystemTime((LPSYSTEMTIME)psystemtime);


}


void file_time_to_system_time(system_time * psystemtime, const ::file_time & filetime)
{

   FileTimeToSystemTime((FILETIME *) &filetime.m_uFileTime, (SYSTEMTIME *) psystemtime);

}


file_time as_file_time(const system_time & systemtime)
{

   FILETIME filetime;

   auto SYSTEMTIME = as_SYSTEMTIME(systemtime);

   SystemTimeToFileTime(&SYSTEMTIME, &filetime);

   return as_file_time(filetime);

}


//void get_system_time(system_time * psystemtime)
//{
//
//   GetSystemTime((SYSTEMTIME *) psystemtime);
//
//}



void get_system_time(system_time * psystemtime)
{

   GetSystemTime((SYSTEMTIME *) psystemtime);

}


void datetime_to_filetime(::file_time * pfiletime, const ::earth::time & time)
{

   SYSTEMTIME sysTime;

   sysTime.wYear = (unsigned short)time.year();
   sysTime.wMonth = (unsigned short)time.month();
   sysTime.wDay = (unsigned short)time.day();
   sysTime.wHour = (unsigned short)time.hour();
   sysTime.wMinute = (unsigned short)time.minute();
   sysTime.wSecond = (unsigned short)time.second();
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






//
//class ::time & time::Now()
//{
//
//   struct timespec timespec;
//
//   if (timespec_get(&timespec, TIME_UTC) != TIME_UTC)
//   {
//
//      throw "timespec_get failed!!";
//
//   }
//
//   m_iSecond = timespec.tv_sec;
//
//   m_iNanosecond = timespec.tv_nsec;
//
//   return *this;
//
//}





//
//
//file_time::file_time(const system_time & systemtime) :
//   file_time(as_file_time(as_FILETIME(as_SYSTEMTIME(systemtime))))
//{
//
//
//}


