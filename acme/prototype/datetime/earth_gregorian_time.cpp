//
// Created by camilo on 2022-10-23 21:38 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "earth_gregorian_time.h"
//#include "earth_time.h"
#include "system_time.h"
#include "acme/operating_system/time.h"


namespace earth
{


   inline int32_t days_from_1jan(int year, int month, int day)
   {
      static const int32_t days[2][12] =
      {
              { 0,31,59,90,120,151,181,212,243,273,304,334},
              { 0,31,60,91,121,152,182,213,244,274,305,335}
      };
      return days[is_leap_year(year)][month - 1] + day - 1;
   }


   posix_time gregorian_time::get_posix_time()
   {

      //         struct tm tm;
      //
      //         get(&tm);
      //
      //         ::posix_time time;

      //   #ifdef WINDOWS
      //
      //         time = _mkgmtime64(&tm);
      //
      //   #else
      //         time = timegm(&tm);
      //
      //   #endif

               //time = make_utc_time(&tm);

               //return time;

      return make_utc_time();

   }


   gregorian_time::gregorian_time(const system_time & systemtime, const class ::time & timeshift)
   {

      m_iDayOfWeek = systemtime.wDayOfWeek;

      m_iNanoSecond = systemtime.wMilliseconds * 1'000'000;

      m_iSecond = systemtime.wSecond;
      m_iMinute = systemtime.wMinute;
      m_iHour = systemtime.wHour;
      m_iDay = systemtime.wDay;
      m_iMonth = systemtime.wMonth;
      m_iYear = systemtime.wYear;

   }


   //void gregorian_time::get(file_time & filetime)
   //{

   //   system_time systemtime;

   //   get(&systemtime);

   //   filetime = as_file_time(&systemtime);

   //}


   gregorian_time::gregorian_time(const ::file_time & filetime, const class ::time & timeshift) :
      gregorian_time(system_time(filetime), timeshift)
   {

      //system_time systemtime;

      //file_time_to_system_time(&systemtime, filetime);

      //set(&systemtime);

   }


   //void time::Now(const class ::time & timeshift)
   //{

   //   ::earth::time time;

   //   time.Now();

   //   set(time, timeshift);

   //}

  
   gregorian_time::gregorian_time(const ::posix_time & posixtime, huge_integer iNanosecond, const class ::time & timeshift)
   {

      set(posixtime, iNanosecond, timeshift);

   }


   //void gregorian_time::set(const ::earth::time & time, const class ::time & timeshift)
   //{

   //   set(time, 0, timeshift);

   //}


   gregorian_time::gregorian_time(const class ::time & time, const class ::time & timeshift)
   {

      set(time, time.m_iNanosecond, timeshift);

   }


   void gregorian_time::set(const class ::time & time, const class ::time & timeshift)
   {

      set(time, time.m_iNanosecond, timeshift);

   }


   posix_time gregorian_time::make_utc_time() const
   {

      int year = m_iYear;

      int month = m_iMonth;

      if (month > 11)
      {
         year += month / 12;
         month %= 12;
      }
      else if (month < 0)
      {
         int years_diff = (-month + 11) / 12;
         year -= years_diff;
         month += 12 * years_diff;
      }
      month++;
      int day = m_iDay;
      int day_of_year = days_from_1jan(year, month, day);
      int days_since_epoch = days_from_1970(year) + day_of_year;

      huge_integer seconds_in_day = 3600 * 24;

      huge_integer result = seconds_in_day * days_since_epoch + 3600 * m_iHour + 60 * m_iMinute + m_iSecond;

      return { posix_time_t{}, result };

   }


} // namespace earth



