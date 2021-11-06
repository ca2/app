#include "framework.h"
#include "acme/operating_system.h"
#include <time.h>
#if defined(LINUX) || defined(__APPLE__)
#include <unistd.h>
#endif


CLASS_DECL_ACME void __seed_srand()
{

   srand((unsigned int)(time(nullptr)));

}


//CLASS_DECL_ACME void sleep(const ::duration& dur)
//{
//
//   sleep((::u32)dur.total_milliseconds());
//
//}


CLASS_DECL_ACME void preempt(const duration & duration)
{

   auto second = duration.integral_second();

   if(second >= 20_s)
   {

      preempt(second);

   }
   else
   {

      auto millisecond = duration.integral_millisecond();

      if (millisecond >= 20_ms)
      {

         preempt(millisecond);

      }
      else
      {

         auto microsecond = duration.integral_microsecond();

         if (microsecond >= 20_µs)
         {

            preempt(microsecond);

         }
         else
         {

            preempt(duration.integral_nanosecond());

         }

      }

   }


}



// SYSTEMTIME
// Specifies a date and time, using individual members for 
// the month, day, year, weekday, hour, minute, second, and ::duration. 
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


void copy(system_time_t* psystemtimeUTC, const struct tm* ptmUTC)
{

   psystemtimeUTC->wYear = ptmUTC->tm_year + 1900; 
   psystemtimeUTC->wMonth = ptmUTC->tm_mon + 1;
   psystemtimeUTC->wDay = ptmUTC->tm_mday;
   psystemtimeUTC->wDayOfWeek = ptmUTC->tm_wday;
   psystemtimeUTC->wHour = ptmUTC->tm_hour;
   psystemtimeUTC->wMinute = ptmUTC->tm_min;
   psystemtimeUTC->wSecond = ptmUTC->tm_sec;
   psystemtimeUTC->wMilliseconds = 0;

}


void copy(struct tm* ptmUTC, const system_time_t* psystemtimeUTC)
{

   ptmUTC->tm_year = psystemtimeUTC->wYear - 1900;
   ptmUTC->tm_mon = psystemtimeUTC->wMonth - 1;
   ptmUTC->tm_mday = psystemtimeUTC->wDay;
   ptmUTC->tm_wday = psystemtimeUTC->wDayOfWeek;
   ptmUTC->tm_yday = -1; // todo
   ptmUTC->tm_hour = psystemtimeUTC->wHour;
   ptmUTC->tm_min = psystemtimeUTC->wMinute;
   ptmUTC->tm_sec = psystemtimeUTC->wSecond + (psystemtimeUTC->wMilliseconds >= 500 ? (psystemtimeUTC->wMilliseconds >= 1500 ? 2 : 1) : 0);
   ptmUTC->tm_isdst = ISDST_NO_DAYLIGHT_SAVINGS; // UTC doesn't observe daylight savings (this is what camilox guess...)

}


::e_status get_system_time_as_file_time(filetime_t* pfiletime)
{

   system_time_t systemtime;

   auto estatus = get_system_time(&systemtime);

   if (!estatus)
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


//::e_status file_time_to_system_time(system_time_t* psystemtime, const filetime_t* pfiletime)
//{
//
//   if (!FileTimeToSystemTime((const FILETIME*)pfiletime, (SYSTEMTIME*)psystemtime))
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
//::e_status file_time_to_local_file_time(filetime_t* pfiletimeLocal, const filetime_t* pfiletime)
//{
//
//   if (!FileTimeToLocalFileTime((const FILETIME*)pfiletime, (FILETIME*)pfiletimeLocal))
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
//::e_status is_valid_filetime(const filetime_t* pfiletime)
//{
//
//   SYSTEMTIME systemtime{};
//
//   if (!FileTimeToSystemTime((const FILETIME*)pfiletime, (SYSTEMTIME*)&systemtime))
//   {
//
//      return error_failed;
//
//   }
//
//   return ::success;
//
//}


::e_status file_time_to_time(time_t* ptime, const filetime_t* pfiletime, i32 nDST)
{

   system_time_t systemtime{};

   auto estatus = file_time_to_system_time(&systemtime, pfiletime);

   if(!estatus)
   {

      return estatus;

   }

   estatus = system_time_to_time(ptime, &systemtime);

   if(!estatus)
   {

      return estatus;

   }

   return estatus;

}


filetime get_filetime_now()
{

   filetime_t filetime=0;

   auto estatus = get_system_time_as_file_time(&filetime);

   if(!estatus)
   {

      return 0;

   }

   return filetime;

}


::e_status system_time_to_tm(tm * ptm, const system_time_t * psystemtime)
{

   ptm->tm_hour   = psystemtime->wHour;
   ptm->tm_min    = psystemtime->wMinute;
   ptm->tm_sec    = psystemtime->wSecond;
   ptm->tm_mon    = psystemtime->wMonth;
   ptm->tm_mday   = psystemtime->wDay;
   ptm->tm_year   = psystemtime->wYear;

   return ::success;

}


::e_status tm_to_system_time(system_time_t * psystemtime, const tm * ptm)
{

   psystemtime->wHour      = ptm->tm_hour    ;
   psystemtime->wMinute    = ptm->tm_min     ;
   psystemtime->wSecond    = ptm->tm_sec     ;
   psystemtime->wMonth     = ptm->tm_mon     ;
   psystemtime->wDay       = ptm->tm_mday    ;
   psystemtime->wYear      = ptm->tm_year    ;

   return ::success;

}



