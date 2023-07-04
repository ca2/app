//
// Created by camilo on 2022-10-12 10:11 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "earth_time_shift.h"


namespace earth
{


   namespace gregorian
   {


      class CLASS_DECL_ACME time
      {
         public:


         int m_iDayOfWeek;


         ::i64 m_iNanoSecond;
         int m_iSecond;        /* Seconds.	[0-60] (1 leap second) */
         int m_iMinute;        /* Minutes.	[0-59] */
         int m_iHour;          /* Hours.	[0-23] */
         int m_iDay;           /* Day.		[1-31] */
         int m_iMonth;         /* Month.	[0-11] */
         int m_iYear;


         inline time()
         {


         }


         inline time(const ::earth::time &time, ::i64 iNanosecond, const time_shift &timeshift = time_shift::none());

         inline time(const class ::time &time, const time_shift &timeshift = time_shift::none());

         inline void set(const struct ::tm *ptm, ::i64 iNanosecond = 0)
         {

            m_iNanoSecond = iNanosecond;
            m_iSecond = ptm->tm_sec;
            m_iMinute = ptm->tm_min;
            m_iHour = ptm->tm_hour;
            m_iDay = ptm->tm_mday;
            m_iMonth = ptm->tm_mon;
            m_iYear = ptm->tm_year + 1900;

         }


         void set(const ::earth::time &time, ::i64 iNanosecond, const time_shift &timeshift);

         void set(const class ::time & time, const time_shift & timeshift);

         void set(const ::earth::time &time, const time_shift &timeshift);

         ::posix_time get_time_t();


         inline void get(struct ::tm *ptm)
         {

            ptm->tm_sec = m_iSecond;
            ptm->tm_min = m_iMinute;
            ptm->tm_hour = m_iHour;
            ptm->tm_mday = m_iDay;
            ptm->tm_mon = m_iMonth;
            ptm->tm_year = m_iYear - 1900;

         }


         void get(system_time_t *psystemtime);

         void set(const system_time_t *psystemtime);

         void get(file_time_t *pfiletime);

         void set(const file_time_t *pfiletime);


         void Now(const time_shift &timeshift = time_shift::none());


      };



   } // namespace gregorian


   inline int32_t is_leap_year(int32_t year)
   {
      if(year % 400 == 0)
         return 1;
      if(year % 100 == 0)
         return 0;
      if(year % 4 == 0)
         return 1;
      return 0;
   }


   inline int32_t days_from_0(int32_t year)
   {
      year--;
      return 365 * year + (year / 400) - (year/100) + (year / 4);
   }


   inline int32_t days_from_1970(int32_t year)
   {
      static const int days_from_0_to_1970 = days_from_0(1970);
      return days_from_0(year) - days_from_0_to_1970;
   }


   inline int32_t days_from_1jan(int32_t year,int32_t month,int32_t day)
   {
      static const int32_t days[2][12] =
              {
                      { 0,31,59,90,120,151,181,212,243,273,304,334},
                      { 0,31,60,91,121,152,182,213,244,274,305,335}
              };
      return days[is_leap_year(year)][month-1] + day - 1;
   }


   inline posix_time make_utc_time(tm const *t)
   {
      int year = t->tm_year + 1900;
      int month = t->tm_mon;
      if(month > 11)
      {
         year += month/12;
         month %= 12;
      }
      else if(month < 0)
      {
         int years_diff = (-month + 11)/12;
         year -= years_diff;
         month+=12 * years_diff;
      }
      month++;
      int day = t->tm_mday;
      int day_of_year = days_from_1jan(year,month,day);
      int days_since_epoch = days_from_1970(year) + day_of_year;

      posix_time seconds_in_day = 3600 * 24;
      posix_time result = seconds_in_day * days_since_epoch + 3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec;

      return result;


   }


} // namespace earth


