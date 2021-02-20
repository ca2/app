/*
 * Nt time functions.
 *
 * RtlTimeToTimeFields, RtlTimeFieldsToTime and defines are taken from ReactOS and
 * adapted to wine with special permissions of the author. This code is
 * Copyright 2002 Rex Jolliff (rex@lvcablemodem.com)
 *
 * Copyright 1999 Juergen Schmied
 * Copyright 2007 Dmitry Timoshkov
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "framework.h"


#if !defined(WINDOWS)
#include <sys/time.h>

#endif

#ifdef _UWP
#define STATUS_SUCCESS 0
#define STATUS_PRIVILEGE_NOT_HELD        ((NTSTATUS) 0xC0000061)
#endif
//#include <time.h>

#define server_start_time 0

#if defined(LINUX)
/* Set the current time of day and timezone information.
   This call is restricted to the super-user.  */
extern "C" int settimeofday (const struct timeval *__tv, const struct timezone *__tz);
#endif


#define NONAMELESSUNION
#define NONAMELESSSTRUCT
#define HAVE_SETTIMEOFDAY
//#define WIN32_NO_STATUS
#define  _CRT_SECURE_NO_WARNINGS
#define __WINESRC__
//#define __CA__DLL


::i32 TIME_GetBias(void);


/*#ifdef _WIN32
#ifdef __CA__STATIC
   #define CLASS_DECL_BOOT
#elif defined(__CA__LIBRARY)
   #define CLASS_DECL_BOOT  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_BOOT  CLASS_DECL_IMPORT
#endif
#else
   #define CLASS_DECL_BOOT
#endif*/




//#ifdef _UWP
//#define STATUS_SUCCESS 0
//#define STATUS_PRIVILEGE_NOT_HELD 1
//#endif

//#include "windows_internals.h"
//#define CLASS_DECL_AURA
////#include "ca/ca/ca_verisimple_string.h"
////#include "ca/ca/ca_mutex.h"
////#include "ca/ca/ca_synch_lock.h"






static i32 init_tz_info(RTL_TIME_ZONE_INFORMATION *tzi);


::mutex * g_pmutexTz = nullptr;


#define TICKSPERSEC        10000000
#define TICKSPERMSEC       10000
#define SECSPERDAY         86400
#define SECSPERHOUR        3600
#define SECSPERMIN         60
#define MINSPERHOUR        60
#define HOURSPERDAY        24
#define EPOCHWEEKDAY       1  /* Jan 1, 1601 was Monday */
#define DAYSPERWEEK        7
#define EPOCHYEAR          1601
#define DAYSPERNORMALYEAR  365
#define DAYSPERLEAPYEAR    366
#define MONSPERYEAR        12
#define DAYSPERQUADRICENTENNIUM (365 * 400 + 97)
#define DAYSPERNORMALCENTURY (365 * 100 + 24)
#define DAYSPERNORMALQUADRENNIUM (365 * 4 + 1)

/* 1601 to 1970 is 369 years plus 89 leap days */
#define SECS_1601_TO_1970  ((369 * 365 + 89) * (ULONGLONG)SECSPERDAY)
#define TICKS_1601_TO_1970 (SECS_1601_TO_1970 * TICKSPERSEC)
/* 1601 to 1980 is 379 years plus 91 leap days */
#define SECS_1601_TO_1980  ((379 * 365 + 91) * (ULONGLONG)SECSPERDAY)
#define TICKS_1601_TO_1980 (SECS_1601_TO_1980 * TICKSPERSEC)
/* maximum ticks that can be represented as Unix time */
#define TICKS_1601_TO_UNIX_MAX ((SECS_1601_TO_1970 + INT_MAX) * TICKSPERSEC)


static const i32 MonthLengths[2][MONSPERYEAR] =
{
   { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
   { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static inline i32 IsLeapYear(i32 Year)
{
   return Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0) ? 1 : 0;
}

/******************************************************************************
 *       RtlTimeToTimeFields [NTDLL.@]
 *
 * Convert a time into a TIME_FIELDS structure.
 *
 * PARAMS
 *   liTime     [I] Time to convert.
 *   TimeFields [O] Destination for the converted time.
 *
 * RETURNS
 *   Nothing.
 */
CLASS_DECL_AURA void WINAPI RtlTimeToTimeFields(
const LARGE_INTEGER *liTime,
PTIME_FIELDS TimeFields)
{
   i32 SecondsInDay;
   u64 cleaps, years, yearday, months;
   u64 Days;
   ::i64 Time;

   /* Extract millisecond from time and convert time into seconds */
   TimeFields->Milliseconds =
   (CSHORT) (( liTime->QuadPart % TICKSPERSEC) / TICKSPERMSEC);
   Time = liTime->QuadPart / TICKSPERSEC;

   /* The native version of RtlTimeToTimeFields does not take leap seconds
    * into account */

   /* Split the time into days and seconds within the day */
   Days = Time / SECSPERDAY;
   SecondsInDay = Time % SECSPERDAY;

   /* compute time of day */
   TimeFields->Hour = (CSHORT) (SecondsInDay / SECSPERHOUR);
   SecondsInDay = SecondsInDay % SECSPERHOUR;
   TimeFields->Minute = (CSHORT) (SecondsInDay / SECSPERMIN);
   TimeFields->Second = (CSHORT) (SecondsInDay % SECSPERMIN);

   /* compute day of week */
   TimeFields->Weekday = (CSHORT) ((EPOCHWEEKDAY + Days) % DAYSPERWEEK);

   /* compute year, month and day of month. */
   cleaps=( 3 * ((4 * Days + 1227) / DAYSPERQUADRICENTENNIUM) + 3 ) / 4;
   Days += 28188 + cleaps;
   years = (20 * Days - 2442) / (5 * DAYSPERNORMALQUADRENNIUM);
   yearday = Days - (years * DAYSPERNORMALQUADRENNIUM)/4;
   months = (64 * yearday) / 1959;
   /* the result is based on a year starting on March.
    * To convert take 12 from Januari and Februari and
    * increase the year by one. */
   if( months < 14 )
   {
      TimeFields->Month = (CSHORT) (months - 1);
      TimeFields->Year = (CSHORT) (years + 1524);
   }
   else
   {
      TimeFields->Month = (CSHORT) (months - 13);
      TimeFields->Year = (CSHORT) (years + 1525);
   }
   /* calculation of day of month is based on the wonderful
    * sequence of ::i32( n * 30.6): it reproduces the
    * 31-30-31-30-31-31 month lengths exactly for small n's */
   TimeFields->Day = (CSHORT) (yearday - (1959 * months) / 64);
   return;
}

/******************************************************************************
 *       RtlTimeFieldsToTime [NTDLL.@]
 *
 * Convert a TIME_FIELDS structure into a time.
 *
 * PARAMS
 *   ftTimeFields [I] TIME_FIELDS structure to convert.
 *   Time         [O] Destination for the converted time.
 *
 * RETURNS
 *   Success: true.
 *   Failure: false.
 */
int_bool WINAPI RtlTimeFieldsToTime(
PTIME_FIELDS tfTimeFields,
PLARGE_INTEGER Time)
{
   i32 month, year, cleaps, day;

   /* FIXME: normalize the TIME_FIELDS structure here */
   /* No, native just returns 0 (error) if the fields are not */
   if( tfTimeFields->Milliseconds< 0 || tfTimeFields->Milliseconds > 999 ||
         tfTimeFields->Second < 0 || tfTimeFields->Second > 59 ||
         tfTimeFields->Minute < 0 || tfTimeFields->Minute > 59 ||
         tfTimeFields->Hour < 0 || tfTimeFields->Hour > 23 ||
         tfTimeFields->Month < 1 || tfTimeFields->Month > 12 ||
         tfTimeFields->Day < 1 ||
         tfTimeFields->Day > MonthLengths
         [ tfTimeFields->Month ==2 || IsLeapYear(tfTimeFields->Year)]
         [ tfTimeFields->Month - 1] ||
         tfTimeFields->Year < 1601 )
      return false;

   /* now calculate a day count from the date
    * First start counting years from March. This way the leap days
    * are added at the end of the year, not somewhere in the middle.
    * Formula's become so much less complicate that way.
    * To convert: add 12 to the month numbers of Jan and Feb, and
    * take 1 from the year */
   if(tfTimeFields->Month < 3)
   {
      month = tfTimeFields->Month + 13;
      year = tfTimeFields->Year - 1;
   }
   else
   {
      month = tfTimeFields->Month + 1;
      year = tfTimeFields->Year;
   }
   cleaps = (3 * (year / 100) + 3) / 4;   /* nr of "century leap years"*/
   day =  (36525 * year) / 100 - cleaps + /* year * dayperyr, corrected */
          (1959 * month) / 64 +         /* months * daypermonth */
          tfTimeFields->Day -          /* day of the month */
          584817 ;                      /* zero that on 1601-01-01 */
   /* done */

   Time->QuadPart = (((((::i64) day * HOURSPERDAY +
                        tfTimeFields->Hour) * MINSPERHOUR +
                       tfTimeFields->Minute) * SECSPERMIN +
                      tfTimeFields->Second ) * 1000 +
                     tfTimeFields->Milliseconds ) * TICKSPERMSEC;

   return true;
}

/***********************************************************************
 *       TIME_GetBias [internal]
 *
 * Helper function calculates delta local time from UTC.
 *
 * PARAMS
 *   utc [I] The current utc time.
 *   pdaylight [I] Local daylight.
 *
 * RETURNS
 *   The bias for the current timezone.
 */
::i32 TIME_GetBias(void)
{
   static time_t last_utc;
   static ::i32 last_bias;
   ::i32 ret;
   time_t utc;

   utc = time( nullptr );

   synchronization_lock ml(g_pmutexTz);
//    RtlEnterCriticalSection( &TIME_tz_section );
   if (utc != last_utc)
   {
      RTL_TIME_ZONE_INFORMATION tzi;
      i32 is_dst = init_tz_info( &tzi );

      last_utc = utc;
      last_bias = tzi.Bias;
      last_bias += is_dst ? tzi.DaylightBias : tzi.StandardBias;
      last_bias *= SECSPERMIN;
   }

   ret = last_bias;

   //RtlLeaveCriticalSection( &TIME_tz_section );
   return ret;
}

/******************************************************************************
 *        RtlLocalTimeToSystemTime [NTDLL.@]
 *
 * Convert a local time into system time.
 *
 * PARAMS
 *   LocalTime  [I] Local time to convert.
 *   SystemTime [O] Destination for the converted time.
 *
 * RETURNS
 *   Success: STATUS_SUCCESS.
 *   Failure: An NTSTATUS error code indicating the problem.
 */
NTSTATUS WINAPI RtlLocalTimeToSystemTime( const LARGE_INTEGER *LocalTime,
      PLARGE_INTEGER SystemTime)
{
   ::i32 bias;

//xxx    TRACE("(%point, %point)\n", LocalTime, SystemTime);

   bias = TIME_GetBias();
   SystemTime->QuadPart = LocalTime->QuadPart + bias * (::i64)TICKSPERSEC;
   return STATUS_SUCCESS;
}

/******************************************************************************
 *       RtlSystemTimeToLocalTime [NTDLL.@]
 *
 * Convert a system time into a local time.
 *
 * PARAMS
 *   SystemTime [I] System time to convert.
 *   LocalTime  [O] Destination for the converted time.
 *
 * RETURNS
 *   Success: STATUS_SUCCESS.
 *   Failure: An NTSTATUS error code indicating the problem.
 */
NTSTATUS WINAPI RtlSystemTimeToLocalTime( const LARGE_INTEGER *SystemTime,
      PLARGE_INTEGER LocalTime )
{
   ::i32 bias;

//xxx    TRACE("(%point, %point)\n", SystemTime, LocalTime);

   bias = TIME_GetBias();
   LocalTime->QuadPart = SystemTime->QuadPart - bias * (::i64)TICKSPERSEC;
   return STATUS_SUCCESS;
}

/******************************************************************************
 *       RtlTimeToSecondsSince1970 [NTDLL.@]
 *
 * Convert a time into a count of seconds since 1970.
 *
 * PARAMS
 *   Time    [I] Time to convert.
 *   Seconds [O] Destination for the converted time.
 *
 * RETURNS
 *   Success: true.
 *   Failure: false, if the resulting value will not fit in a ::u32.
 */
int_bool WINAPI RtlTimeToSecondsSince1970( const LARGE_INTEGER *Time, LPDWORD Seconds )
{
   ULONGLONG tmp = ((ULONGLONG)Time->u.HighPart << 32) | Time->u.LowPart;
   tmp = tmp / TICKSPERSEC - SECS_1601_TO_1970;
   if (tmp > 0xffffffff) return false;
   *Seconds = (::u32)tmp;
   return true;
}

/******************************************************************************
 *       RtlTimeToSecondsSince1980 [NTDLL.@]
 *
 * Convert a time into a count of seconds since 1980.
 *
 * PARAMS
 *   Time    [I] Time to convert.
 *   Seconds [O] Destination for the converted time.
 *
 * RETURNS
 *   Success: true.
 *   Failure: false, if the resulting value will not fit in a ::u32.
 */
int_bool WINAPI RtlTimeToSecondsSince1980( const LARGE_INTEGER *Time, LPDWORD Seconds )
{
   ULONGLONG tmp = ((ULONGLONG)Time->u.HighPart << 32) | Time->u.LowPart;
   tmp = tmp / TICKSPERSEC - SECS_1601_TO_1980;
   if (tmp > 0xffffffff) return false;
   *Seconds = (::u32)tmp;
   return true;
}

/******************************************************************************
 *       RtlSecondsSince1970ToTime [NTDLL.@]
 *
 * Convert a count of seconds since 1970 to a time.
 *
 * PARAMS
 *   Seconds [I] Time to convert.
 *   Time    [O] Destination for the converted time.
 *
 * RETURNS
 *   Nothing.
 */
void WINAPI RtlSecondsSince1970ToTime( ::u32 Seconds, LARGE_INTEGER *Time )
{
   ULONGLONG secs = Seconds * (ULONGLONG)TICKSPERSEC + TICKS_1601_TO_1970;
   Time->u.LowPart  = (::u32)secs;
   Time->u.HighPart = (::u32)(secs >> 32);
}

/******************************************************************************
 *       RtlSecondsSince1980ToTime [NTDLL.@]
 *
 * Convert a count of seconds since 1980 to a time.
 *
 * PARAMS
 *   Seconds [I] Time to convert.
 *   Time    [O] Destination for the converted time.
 *
 * RETURNS
 *   Nothing.
 */
void WINAPI RtlSecondsSince1980ToTime( ::u32 Seconds, LARGE_INTEGER *Time )
{
   ULONGLONG secs = Seconds * (ULONGLONG)TICKSPERSEC + TICKS_1601_TO_1980;
   Time->u.LowPart  = (::u32)secs;
   Time->u.HighPart = (::u32)(secs >> 32);
}

/******************************************************************************
 *       RtlTimeToElapsedTimeFields [NTDLL.@]
 *
 * Convert a time to a count of elapsed seconds.
 *
 * PARAMS
 *   Time       [I] Time to convert.
 *   TimeFields [O] Destination for the converted time.
 *
 * RETURNS
 *   Nothing.
 */
void WINAPI RtlTimeToElapsedTimeFields( const LARGE_INTEGER *Time, PTIME_FIELDS TimeFields )
{
   ::i64 time;
   ::i32 rem;

   time = Time->QuadPart / TICKSPERSEC;
   TimeFields->Milliseconds = (CSHORT) ((Time->QuadPart % TICKSPERSEC) / TICKSPERMSEC);

   /* time is now in seconds */
   TimeFields->Year  = 0;
   TimeFields->Month = 0;
   TimeFields->Day   = (CSHORT) (time / SECSPERDAY);

   /* rem is now the remaining seconds in the last day */
   rem = time % SECSPERDAY;
   TimeFields->Second = rem % 60;
   rem /= 60;
   TimeFields->Minute = rem % 60;
   TimeFields->Hour = rem / 60;
}

#ifdef _UWP


const ::i64 DELTA_EPOCH_IN_MICROSECS= 11644473600000000;

/* IN UNIX the use of the timezone struct is obsolete;
 I don't know why you use it. See http://linux.about.com/od/commands/l/blcmdl2_gettime.htm
 But if you want to use this structure to know about GMT(UTC) diffrence from your local time
 it will be next: tz_minuteswest is the real diffrence in minutes from GMT(UTC) and a tz_dsttime is a flag
 indicates whether daylight is now in use
*/
struct timezone2
{
   __int32  tz_minuteswest; /* minutes W of Greenwich */
   bool  tz_dsttime;     /* type of dst correction */
};

//
//i32 gettimeofday(timeval *tv/*in*/, struct timezone2 *tz/*in*/)
//{
//  FILETIME ft;
//  ::i64 tmpres = 0;
//  TIME_ZONE_INFORMATION tz_winapi;
//  i32 rez=0;
//
//   ZeroMemory(&ft,sizeof(ft));
//   ZeroMemory(&tz_winapi,sizeof(tz_winapi));
//
//    GetSystemTimeAsFileTime(&ft);
//
//    tmpres = ft.dwHighDateTime;
//    tmpres <<= 32;
//    tmpres |= ft.dwLowDateTime;
//
//    /*converting file time to unix epoch*/
//    tmpres /= 10;  /*convert into microseconds*/
//    tmpres -= DELTA_EPOCH_IN_MICROSECS;
//    tv->tv_sec = (__int32)(tmpres*0.000001);
//    tv->tv_usec =(tmpres%1000000);
//
//
//    //_tzset(),don't work properly, so we use GetTimeZoneInformation
//    rez=GetTimeZoneInformation(&tz_winapi);
//    tz->tz_dsttime=(rez==2)?true:false;
//    tz->tz_minuteswest = tz_winapi.Bias + ((rez==2)?tz_winapi.DaylightBias:0);
//
//  return 0;
//}

#endif

/***********************************************************************
 *       NtQuerySystemTime [NTDLL.@]
 *       ZwQuerySystemTime [NTDLL.@]
 *
 * Get the current system time.
 *
 * PARAMS
 *   Time [O] Destination for the current system time.
 *
 * RETURNS
 *   Success: STATUS_SUCCESS.
 *   Failure: An NTSTATUS error code indicating the problem.
 */
NTSTATUS WINAPI NtQuerySystemTime( PLARGE_INTEGER Time )
{

   struct timeval now;

   gettimeofday( &now, 0 );
   Time->QuadPart = now.tv_sec * (ULONGLONG)TICKSPERSEC + TICKS_1601_TO_1970;
   Time->QuadPart += now.tv_usec * 10;

   return STATUS_SUCCESS;

}

/******************************************************************************
 *  NtQueryPerformanceCounter	[NTDLL.@]
 *
 *  Note: Windows uses a timer clocked at a multiple of 1193182 Hz. There is a
 *  good number of applications that crash when the returned frequency is either
 *  lower or higher than what Windows gives. Also too high counter values are
 *  reported to give problems.
 */
NTSTATUS WINAPI NtQueryPerformanceCounter( PLARGE_INTEGER Counter, PLARGE_INTEGER Frequency )
{
   LARGE_INTEGER now;

   if (!Counter) return STATUS_ACCESS_VIOLATION;

   /* convert a counter that increments at a rate of 10 MHz
    * to one of 1.193182 MHz, with some care for arithmetic
    * overflow and good accuracy (21/176 = 0.11931818) */
   NtQuerySystemTime( &now );
   Counter->QuadPart = ((now.QuadPart - server_start_time) * 21) / 176;
   if (Frequency) Frequency->QuadPart = 1193182;
   return STATUS_SUCCESS;
}


/******************************************************************************
 * NtGetTickCount   (NTDLL.@)
 * ZwGetTickCount   (NTDLL.@)
 */
WINULONG WINAPI NtGetTickCount(void)
{
   LARGE_INTEGER now;

   NtQuerySystemTime( &now );
   return (CSHORT) ((now.QuadPart - server_start_time) / 10000);
}

/* calculate the mday of dst change date, so that for instance Sun 5 Oct 2007
 * (last Sunday in October of 2007) becomes Sun Oct 28 2007
 *
 * Note: year, day and month must be in unix format.
 */
static i32 weekday_to_mday(i32 year, i32 day, i32 mon, i32 day_of_week)
{
   struct tm date;
   time_t tmp;
   i32 wday, mday;

   /* find first day in the month matching week day of the date */
   __memset(&date, 0, sizeof(date));
   date.tm_year = year;
   date.tm_mon = mon;
   date.tm_mday = -1;
   date.tm_wday = -1;
   do
   {
      date.tm_mday++;
      tmp = mktime(&date);
   }
   while (date.tm_wday != day_of_week || date.tm_mon != mon);

   mday = date.tm_mday;

   /* find number of week days in the month matching week day of the date */
   wday = 1; /* 1 - 1st, ...., 5 - last */
   while (wday < day)
   {
      struct tm *tm;

      date.tm_mday += 7;
      tmp = mktime(&date);
      tm = localtime(&tmp);
      if (tm->tm_mon != mon)
         break;
      mday = tm->tm_mday;
      wday++;
   }

   return mday;
}

int_bool match_tz_date(const RTL_SYSTEM_TIME *st, const RTL_SYSTEM_TIME *reg_st)
{
   ::u16 wDay;

   if (st->wMonth != reg_st->wMonth) return false;

   if (!st->wMonth) return true; /* no transition dates */

   wDay = reg_st->wDay;
   if (!reg_st->wYear) /* date in a day-of-week format */
      wDay = weekday_to_mday(st->wYear - 1900, reg_st->wDay, reg_st->wMonth - 1, reg_st->wDayOfWeek);

   if (st->wDay != wDay ||
         st->wHour != reg_st->wHour ||
         st->wMinute != reg_st->wMinute ||
         st->wSecond != reg_st->wSecond ||
         st->wMilliseconds != reg_st->wMilliseconds) return false;

   return true;
}

int_bool match_tz_info(const RTL_TIME_ZONE_INFORMATION *tzi, const RTL_TIME_ZONE_INFORMATION *reg_tzi)
{
   if (tzi->Bias == reg_tzi->Bias &&
         match_tz_date(&tzi->StandardDate, &reg_tzi->StandardDate) &&
         match_tz_date(&tzi->DaylightDate, &reg_tzi->DaylightDate))
      return true;

   return false;
}

/*

static int_bool reg_query_value(HKEY hkey, const widechar * name, ::u32 type, void *data, ::u32 count)
{
    UNICODE_STRING nameW;
    char buf[256];
    KEY_VALUE_PARTIAL_INFORMATION *info = (KEY_VALUE_PARTIAL_INFORMATION *)buf;

    if (count > sizeof(buf) - sizeof(KEY_VALUE_PARTIAL_INFORMATION))
        return false;

    RtlInitUnicodeString(&nameW, name);

    if (NtQueryValueKey(hkey, &nameW, KeyValuePartialInformation,
                        buf, sizeof(buf), &count))
        return false;

    if (info->Type != type) return false;

    ::memcpy_dup(data, info->Data, info->DataLength);
    return true;
}

*/


static time_t find_dst_change(time_t minimum, time_t maximum, i32 *is_dst)
{
   time_t start;
   struct tm *tm;

   start = minimum;
   tm = localtime(&start);
   *is_dst = !tm->tm_isdst;
// xxx    TRACE("starting date isdst %d, %s", !*is_dst, ctime(&start));

   while (minimum <= maximum)
   {
      time_t pos = (minimum + maximum) / 2;
      tm = localtime(&pos);

      if (tm->tm_isdst != *is_dst)
         minimum = pos + 1;
      else
         maximum = pos - 1;
   }
   return minimum;
}

static i32 init_tz_info(RTL_TIME_ZONE_INFORMATION *tzi)
{
   static RTL_TIME_ZONE_INFORMATION cached_tzi;
   static i32 current_year = -1;
   struct tm *tm;
   time_t year_start, year_end, tmp, dlt = 0, iStandard = 0;
   i32 is_dst, current_is_dst;

   synchronization_lock ml(g_pmutexTz);
//    RtlEnterCriticalSection( &TIME_tz_section );

   year_start = time(nullptr);
   tm = localtime(&year_start);

   current_is_dst = tm->tm_isdst;
   if (current_year == tm->tm_year)
   {
      *tzi = cached_tzi;
//        RtlLeaveCriticalSection( &TIME_tz_section );
      return current_is_dst;
   }

   __memset(tzi, 0, sizeof(*tzi));

//xxx    TRACE("tz data will be valid through year %d\n", tm->tm_year + 1900);
   current_year = tm->tm_year;

   tm->tm_isdst = 0;
   tm->tm_mday = 1;
   tm->tm_mon = tm->tm_hour = tm->tm_min = tm->tm_sec = tm->tm_wday = tm->tm_yday = 0;
   year_start = mktime(tm);
//xxx    TRACE("year_start: %s", ctime(&year_start));

   tm->tm_mday = tm->tm_wday = tm->tm_yday = 0;
   tm->tm_mon = 12;
   tm->tm_hour = 23;
   tm->tm_min = tm->tm_sec = 59;
   year_end = mktime(tm);
//xxx    TRACE("year_end: %s", ctime(&year_end));

   tm = gmtime(&year_start);
   tzi->Bias = (::i32)(mktime(tm) - year_start) / 60;
//xxx    TRACE("bias: %d\n", tzi->Bias);

   tmp = find_dst_change(year_start, year_end, &is_dst);
   if (is_dst)
      dlt = tmp;
   else
      iStandard = tmp;

   tmp = find_dst_change(tmp, year_end, &is_dst);
   if (is_dst)
      dlt = tmp;
   else
      iStandard = tmp;

//xxx    TRACE("Standard: %s", ctimeiStandardstd));
//xxx    TRACE("dlt: %s", ctime(&dlt));

   if (dlt == iStandard || !dlt || !iStandard)
   {
//xxx   TRACE("there is no daylight saving rules in this time zone\n");
   }
   else
   {
      tmp = dlt - tzi->Bias * 60;
      tm = gmtime(&tmp);
//xxx   TRACE("dlt gmtime: %s", asctime(tm));

      tzi->DaylightBias = -60;
      tzi->DaylightDate.wYear = tm->tm_year + 1900;
      tzi->DaylightDate.wMonth = tm->tm_mon + 1;
      tzi->DaylightDate.wDayOfWeek = tm->tm_wday;
      tzi->DaylightDate.wDay = tm->tm_mday;
      tzi->DaylightDate.wHour = tm->tm_hour;
      tzi->DaylightDate.wMinute = tm->tm_min;
      tzi->DaylightDate.wSecond = tm->tm_sec;
      tzi->DaylightDate.wMilliseconds = 0;

//xxx        TRACE("daylight (d/m/y): %u/%02u/%04u day of week %u %u:%02u:%02u.%03u bias %d\n",
//xxx            tzi->DaylightDate.wDay, tzi->DaylightDate.wMonth,
//xxx            tzi->DaylightDate.wYear, tzi->DaylightDate.wDayOfWeek,
//xxx            tzi->DaylightDate.wHour, tzi->DaylightDate.wMinute,
//xxx            tzi->DaylightDate.wSecond, tzi->DaylightDate.wMilliseconds,
//xxx            tzi->DaylightBias);

      tmp = iStandard - tzi->Bias * 60 - tzi->DaylightBias * 60;
      tm = gmtime(&tmp);
//xxx        TRACE("Standard gmtime: %s", asctime(tm));

      tzi->StandardBias = 0;
      tzi->StandardDate.wYear = tm->tm_year + 1900;
      tzi->StandardDate.wMonth = tm->tm_mon + 1;
      tzi->StandardDate.wDayOfWeek = tm->tm_wday;
      tzi->StandardDate.wDay = tm->tm_mday;
      tzi->StandardDate.wHour = tm->tm_hour;
      tzi->StandardDate.wMinute = tm->tm_min;
      tzi->StandardDate.wSecond = tm->tm_sec;
      tzi->StandardDate.wMilliseconds = 0;

//xxx        TRACE("standard (d/m/y): %u/%02u/%04u day of week %u %u:%02u:%02u.%03u bias %d\n",
//xxx            tzi->StandardDate.wDay, tzi->StandardDate.wMonth,
//xxx            tzi->StandardDate.wYear, tzi->StandardDate.wDayOfWeek,
//xxx            tzi->StandardDate.wHour, tzi->StandardDate.wMinute,
//xxx            tzi->StandardDate.wSecond, tzi->StandardDate.wMilliseconds,
//xxx            tzi->StandardBias);
   }

//xxx    find_reg_tz_info(tzi);
//xxx    cached_tzi = *tzi;

   //RtlLeaveCriticalSection( &TIME_tz_section );

   return current_is_dst;
}

/***********************************************************************
 *      RtlQueryTimeZoneInformation [NTDLL.@]
 *
 * Get information about the current timezone.
 *
 * PARAMS
 *   tzinfo [O] Destination for the retrieved timezone info.
 *
 * RETURNS
 *   Success: STATUS_SUCCESS.
 *   Failure: An NTSTATUS error code indicating the problem.
 */
NTSTATUS WINAPI RtlQueryTimeZoneInformation(RTL_TIME_ZONE_INFORMATION *tzinfo)
{
   init_tz_info( tzinfo );

   return STATUS_SUCCESS;
}

/***********************************************************************
 *       RtlSetTimeZoneInformation [NTDLL.@]
 *
 * Set the current time zone information.
 *
 * PARAMS
 *   tzinfo [I] Timezone information to set.
 *
 * RETURNS
 *   Success: STATUS_SUCCESS.
 *   Failure: An NTSTATUS error code indicating the problem.
 *
 */
NTSTATUS WINAPI RtlSetTimeZoneInformation( const RTL_TIME_ZONE_INFORMATION *tzinfo )
{
   return STATUS_PRIVILEGE_NOT_HELD;
}

/***********************************************************************
 *        NtSetSystemTime [NTDLL.@]
 *        ZwSetSystemTime [NTDLL.@]
 *
 * Set the system time.
 *
 * PARAMS
 *   NewTime [I] The time to set.
 *   OldTime [O] Optional destination for the previous system time.
 *
 * RETURNS
 *   Success: STATUS_SUCCESS.
 *   Failure: An NTSTATUS error code indicating the problem.
 */
#ifndef _UWP
NTSTATUS WINAPI NtSetSystemTime(const LARGE_INTEGER *NewTime, LARGE_INTEGER *OldTime)
{
   struct timeval tv;
   //time_t tm_t;
   ::u32 sec, oldsec;
   LARGE_INTEGER tm;

   /* Return the old time if necessary */
   if (!OldTime) OldTime = &tm;

   NtQuerySystemTime( OldTime );
   RtlTimeToSecondsSince1970( OldTime, &oldsec );

   RtlTimeToSecondsSince1970( NewTime, &sec );

   /* set the new time */
   tv.tv_sec = sec;
   tv.tv_usec = 0;

#ifdef HAVE_SETTIMEOFDAY
   if (!settimeofday(&tv, nullptr)) /* 0 is OK, -1 is error */
      return STATUS_SUCCESS;
   //tm_t = sec;
   // xxx ERR("Cannot set time to %s, time adjustment %ld: %s\n",
   // xxx ctime(&tm_t), (long)(sec-oldsec), strerror(errno));
   if (errno == EPERM)
      return STATUS_PRIVILEGE_NOT_HELD;
   else
      return STATUS_INVALID_PARAMETER;
#else
   tm_t = sec;
   FIXME("setting time to %s not implemented for missing settimeofday\n",
         ctime(&tm_t));
   return STATUS_NOT_IMPLEMENTED;
#endif
}

/*********************************************************************
 *      LocalFileTimeToFileTime                         (KERNEL32.@)
 */
CLASS_DECL_AURA int_bool WINAPI LocalFileTimeToFileTime( const FILETIME *localft, LPFILETIME utcft )
{
   NTSTATUS status;
   LARGE_INTEGER local, utc;

   local.u.LowPart = localft->dwLowDateTime;
   local.u.HighPart = localft->dwHighDateTime;
   if (!(status = RtlLocalTimeToSystemTime( &local, &utc )))
   {
      utcft->dwLowDateTime = utc.u.LowPart;
      utcft->dwHighDateTime = utc.u.HighPart;
   }
   else
   {
      //set_last_error( RtlNtStatusToDosError(status) );
      set_last_error(1);

   }

   return !status;
}

/*********************************************************************
 *      FileTimeToLocalFileTime                         (KERNEL32.@)
 */
CLASS_DECL_AURA int_bool WINAPI FileTimeToLocalFileTime( const FILETIME *utcft, LPFILETIME localft )
{
   NTSTATUS status;
   LARGE_INTEGER local, utc;

   utc.u.LowPart = utcft->dwLowDateTime;
   utc.u.HighPart = utcft->dwHighDateTime;
   if (!(status = RtlSystemTimeToLocalTime( &utc, &local )))
   {
      localft->dwLowDateTime = local.u.LowPart;
      localft->dwHighDateTime = local.u.HighPart;
   }
   else
   {
      //set_last_error( RtlNtStatusToDosError(status) );
      set_last_error( 1);
   }


   return !status;
}




/*********************************************************************
 *      FileTimeToSystemTime                            (KERNEL32.@)
 */
int_bool WINAPI FileTimeToSystemTime( const FILETIME *ft, LPSYSTEMTIME syst )
{
   TIME_FIELDS tf;
   LARGE_INTEGER t;

   t.u.LowPart = ft->dwLowDateTime;
   t.u.HighPart = ft->dwHighDateTime;
   RtlTimeToTimeFields(&t, &tf);

   syst->wYear = tf.Year;
   syst->wMonth = tf.Month;
   syst->wDay = tf.Day;
   syst->wHour = tf.Hour;
   syst->wMinute = tf.Minute;
   syst->wSecond = tf.Second;
   syst->wMilliseconds = tf.Milliseconds;
   syst->wDayOfWeek = tf.Weekday;
   return true;
}


/*********************************************************************
 *      SystemTimeToFileTime                            (KERNEL32.@)
 */
int_bool WINAPI SystemTimeToFileTime( const SYSTEMTIME *syst, LPFILETIME ft )
{
   TIME_FIELDS tf;
   LARGE_INTEGER t;

   tf.Year = syst->wYear;
   tf.Month = syst->wMonth;
   tf.Day = syst->wDay;
   tf.Hour = syst->wHour;
   tf.Minute = syst->wMinute;
   tf.Second = syst->wSecond;
   tf.Milliseconds = syst->wMilliseconds;

   if( !RtlTimeFieldsToTime(&tf, &t))
   {
      set_last_error( ERROR_INVALID_PARAMETER);
      return false;
   }
   ft->dwLowDateTime = t.u.LowPart;
   ft->dwHighDateTime = t.u.HighPart;
   return true;
}


/***********************************************************************
 *              GetSystemTimeAsFileTime  (KERNEL32.@)
 *
 *  Get the current time in utc format.
 *
 *  RETURNS
 *   Nothing.
 */
CLASS_DECL_AURA void GetSystemTimeAsFileTime(
LPFILETIME time) /* [out] Destination for the current utc time */
{
   LARGE_INTEGER t;
   NtQuerySystemTime( &t );
   time->dwLowDateTime = t.u.LowPart;
   time->dwHighDateTime = t.u.HighPart;
}



/*********************************************************************
 *      GetSystemTime                                   (KERNEL32.@)
 *
 * Get the current system time.
 *
 * PARAMS
 *  systime [O] Destination for current time.
 *
 * RETURNS
 *  Nothing.
 */
CLASS_DECL_AURA void GetSystemTime(LPSYSTEMTIME systime)
{
   FILETIME ft;
   LARGE_INTEGER t;

   NtQuerySystemTime(&t);
   ft.dwLowDateTime = t.u.LowPart;
   ft.dwHighDateTime = t.u.HighPart;
   FileTimeToSystemTime(&ft, systime);
}


#endif // !defined(_UWP)




