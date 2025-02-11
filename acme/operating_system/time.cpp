#include "framework.h"
#include "time.h"
////#include "acme/prototype/datetime/earth_time.h"
#include "acme/prototype/datetime/system_time.h"
//#include "acme/prototype/time/time.h"
#if !defined(WINDOWS)
#include "acme/operating_system/ansi/windows_time.h"
#endif
#include <time.h>
#if defined(LINUX) || defined(__APPLE__)
#include <unistd.h>
#endif


CLASS_DECL_ACME void __seed_srand()
{

   srand((unsigned int)(time(nullptr)));

}


//CLASS_DECL_ACME void sleep(const ::time& dur)
//{
//
//   sleep((unsigned int)dur.total_milliseconds());
//
//}


CLASS_DECL_ACME void preempt_second(long long i);
CLASS_DECL_ACME void preempt_millisecond(long long i);
CLASS_DECL_ACME void preempt_microsecond(long long i);
CLASS_DECL_ACME void preempt_nanosecond(long long i);


CLASS_DECL_ACME void preempt(const class time & time)
{

   if(time >= 20_s)
   {

      preempt_second(time.integral_second());

   }
   else if (time >= 1_ms)
   {

      preempt_millisecond(time.integral_millisecond());

   }
   else if (time >= 20_μs)
   {

      preempt_microsecond(time.integral_microsecond());

   }
   else
   {

      preempt_nanosecond(time.integral_nanosecond());

   }

}



// SYSTEMTIME
// Specifies a date and time, using individual members for 
// the month, day, year, weekday, hour, minute, second, and ::time. 
// The time is either in coordinated universal time (UTC) or local time, 
// depending on the function that is being called.
// 
// wYear - 1601 - 30827
// wMonth - 1 - 12
// wDayOfWeek - 0 Sunday
// wDay - 1 - 31
// wHour - 0 - 23
// wMinute - 0 - 59
// wSecond - 0 - 59
// wMilliseconds - 0 - 999


// struct tm
// Structure containing a calendar date and time broken down into its components.
//
// The structure contains nine members of type int(in any order), which are :
//
// C90(C++98)C99(C++11)
// Member	Type	Meaning	Range
// tm_sec	int	seconds after the minute	0 - 61 *
// tm_min	int	minutes after the hour	0 - 59
// tm_hour	int	hours since midnight	0 - 23
// tm_mday	int	day of the month	1 - 31
// tm_mon	int	months since January	0 - 11
// tm_year	int	years since 1900
// tm_wday	int	days since Sunday	0 - 6
// tm_yday	int	days since January 1	0 - 365
// tm_isdst	int	Daylight Saving Time flag
// 
// The Daylight Saving Time flag(tm_isdst) is greater than zero if
// Daylight Saving Time is in effect, zero if Daylight Saving Time is not in effect,
// and less than zero if the information is not available.
// * tm_sec is generally 0 - 59. The extra range is to accommodate for 
// leap seconds in certain systems.


void copy(system_time & systemtimeUTC, const struct tm & tmUTC)
{

   systemtimeUTC.wYear = tmUTC.tm_year + 1900; 
   systemtimeUTC.wMonth = tmUTC.tm_mon + 1;
   systemtimeUTC.wDay = tmUTC.tm_mday;
   systemtimeUTC.wDayOfWeek = tmUTC.tm_wday;
   systemtimeUTC.wHour = tmUTC.tm_hour;
   systemtimeUTC.wMinute = tmUTC.tm_min;
   systemtimeUTC.wSecond = tmUTC.tm_sec;
   systemtimeUTC.wMilliseconds = 0;

}


void copy(struct tm & tmUTC, const system_time & systemtimeUTC)
{

   tmUTC.tm_year = systemtimeUTC.wYear - 1900;
   tmUTC.tm_mon = systemtimeUTC.wMonth - 1;
   tmUTC.tm_mday = systemtimeUTC.wDay;
   tmUTC.tm_wday = systemtimeUTC.wDayOfWeek;
   tmUTC.tm_yday = -1; // todo
   tmUTC.tm_hour = systemtimeUTC.wHour;
   tmUTC.tm_min = systemtimeUTC.wMinute;
   tmUTC.tm_sec = systemtimeUTC.wSecond + (systemtimeUTC.wMilliseconds >= 500 ? (systemtimeUTC.wMilliseconds >= 1500 ? 2 : 1) : 0);
   tmUTC.tm_isdst = ISDST_NO_DAYLIGHT_SAVINGS; // UTC doesn't observe daylight savings (this is what camilox guess...)

}


//file_time system_time_as_file_time()
//{
//
//   //system_time systemtime;
//
//   //auto estatus = get_system_time(&systemtime);
//
//   auto systemtime = now_as_system_time();
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   /*estatus = */
//   
//   return as_file_time(systemtime);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   //return estatus;
//
//}


//void file_time_to_system_time(system_time* psystemtime, const ::file_time & filetime)
//{
//
//   if (!FileTimeToSystemTime((const FILETIME*)pfile_time, (SYSTEMTIME*)psystemtime))
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
//
//void file_time_to_local_file_time(file_time* pfile_timeLocal, const ::file_time & filetime)
//{
//
//   if (!FileTimeToLocalFileTime((const FILETIME*)pfile_time, (FILETIME*)pfile_timeLocal))
//   {
//
//      return error_failed;
//
//   }
//
//   return success;
//
//}
//
//
//void is_valid_file_time(const ::file_time & filetime)
//{
//
//   SYSTEMTIME systemtime{};
//
//   if (!FileTimeToSystemTime((const FILETIME*)pfile_time, (SYSTEMTIME*)&systemtime))
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
//
//::posix_time as_posix_time(const ::file_time & filetime, int nDST)
//{
//
//   auto systemtime = as_system_time(filetime);
//
//   auto posixtime = as_posix_time(systemtime, nDST);
//
//   return posixtime;
//
//}


//file_time now_as_file_time()
//{
//
//   auto filetime = system_time_as_file_time();
//
//   return filetime;
//
//}


void copy(tm * ptm, const system_time * psystemtime)
{

   ptm->tm_hour   = psystemtime->wHour;
   ptm->tm_min    = psystemtime->wMinute;
   ptm->tm_sec    = psystemtime->wSecond;
   ptm->tm_mon    = psystemtime->wMonth;
   ptm->tm_mday   = psystemtime->wDay;
   ptm->tm_year   = psystemtime->wYear;

}


void copy(system_time * psystemtime, const tm * ptm)
{

   psystemtime->wYear = (unsigned short)ptm->tm_year;
   psystemtime->wMonth = (unsigned short)ptm->tm_mon;
   psystemtime->wDayOfWeek = (unsigned short)ptm->tm_wday;
   psystemtime->wDay = (unsigned short)ptm->tm_mday;
   psystemtime->wHour = (unsigned short)ptm->tm_hour;
   psystemtime->wMinute = (unsigned short)ptm->tm_min;
   psystemtime->wSecond = (unsigned short)ptm->tm_sec;
   psystemtime->wMilliseconds = 0;

}




//CLASS_DECL_ACME file_time as_file_time(const class ::time & time)
//{
//
//   unsigned long long nanoseconds = time.m_iNanosecond + time.m_iSecond * 1'000'000'000;
//
//   nanoseconds += EPOCH_DIFFERENCE_NANOS;
//
//   return { ::file_time_t{}, nanoseconds / 100 };
//
//}


posix_time::posix_time(now_t):
   m_iSecond(time(nullptr))
{


}

