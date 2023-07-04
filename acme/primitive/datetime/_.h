#pragma once


struct system_time_t;


class file_time;


class system_time;

//
//inline int32_t is_leap_year(int32_t year)
//{
//
//   return year % 400 == 0 ? 1 : (year % 100 == 0 ? 0 : (year % 4 == 0 ? 1 : 0));
//
//}
//
//
//inline int32_t days_from_0(int32_t year)
//{
//
//  year--;
//
//  return 365 * year + (year / 400) - (year/100) + (year / 4);
//
//}
//
//
//inline int32_t days_from_1970(int32_t year)
//{
//
//  static const int days_from_0_to_1970 = days_from_0(1970);
//
//  return days_from_0(year) - days_from_0_to_1970;
//
//}
//
//
//inline int32_t days_from_1jan(int32_t year,int32_t month,int32_t day)
//{
//
//   static const int32_t days[2][12] =
//   {
//
//      { 0,31,59,90,120,151,181,212,243,273,304,334},
//      { 0,31,60,91,121,152,182,213,244,274,305,335}
//
//   };
//
//   return days[is_leap_year(year)][month-1] + day - 1;
//
//}
//
//// seconds since Epoch in UTC
//inline time_t make_utc_time(struct tm const *t)
//{
//
//   int year = t->tm_year + 1900;
//
//   int month = t->tm_mon;
//
//   if(month > 11)
//   {
//
//      year += month/12;
//
//      month %= 12;
//
//   }
//   else if(month < 0)
//   {
//
//      int years_diff = (-month + 11)/12;
//
//      year -= years_diff;
//
//      month+=12 * years_diff;
//
//   }
//
//   month++;
//
//   int day = t->tm_mday;
//
//   int day_of_year = days_from_1jan(year,month,day);
//
//   int days_since_epoch = days_from_1970(year) + day_of_year;
//
//   time_t seconds_in_day = 3600 * 24;
//
//   time_t result = seconds_in_day * days_since_epoch + 3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec;
//
//   return result;
//
//}


//class second;
//class time;
//class microsecond;
//class nanosecond;
class time;


namespace earth
{

    class time;
    class time_span;
    class zonetime;
    class date_span;
 
} // namespace earth


namespace datetime
{

   
   class time_zone;


} // namespace datetime;

#ifdef WINDOWS


extern "C" CLASS_DECL_ACME time_t timegm(struct tm *tmp);


#endif


extern "C" CLASS_DECL_ACME int c_localtime_offset();



//#include "micro_time.h"
//
//
//#include "time_span.h"
//
//
//#include "date_span.h"
//
//
//#include "earth_time.h"
//
//
//#include "system_time.h"
//
//
//#include "result.h"
//
//
//#include "microsecond_sleep.h"
//
//
//#ifdef WINDOWS
//
//
//extern "C" CLASS_DECL_ACME time_t timegm(struct tm *tmp);
//
//
//#endif
//
//
//extern "C" CLASS_DECL_ACME int c_localtime_offset();
//
//
//#include "micro_time.h"
//
//
//
