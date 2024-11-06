//
// Created by camilo on 2022-10-12 10:11 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "earth_time_shift.h"


namespace earth
{


   class CLASS_DECL_ACME gregorian_time
   {
   public:


      int m_iDayOfWeek;


      huge_integer m_iNanoSecond;
      int m_iSecond;        /* Seconds.	[0-60] (1 leap second) */
      int m_iMinute;        /* Minutes.	[0-59] */
      int m_iHour;          /* Hours.	[0-23] */
      int m_iDay;           /* Day.		[1-31] */
      int m_iMonth;         /* Month.	[0-11] */
      int m_iYear;


      inline gregorian_time()
      {

         m_iDayOfWeek = 0;


         m_iNanoSecond = 0;
         m_iSecond =0;        /* Seconds.	[0-60] (1 leap second) */
         m_iMinute =0 ;        /* Minutes.	[0-59] */
         m_iHour=0;          /* Hours.	[0-23] */
         m_iDay=0;           /* Day.		[1-31] */
         m_iMonth=0;         /* Month.	[0-11] */
         m_iYear=0;

      }


      explicit gregorian_time(const ::posix_time & posixtime, huge_integer iNanosecond = 0, const class ::time & timeshift = {});
      explicit gregorian_time(const class ::time & time, const class ::time & timeshift = {});
      explicit gregorian_time(const ::system_time & systemtime, const class ::time & timeshift = {});
      explicit gregorian_time(const ::file_time & filetime, const class ::time & timeshift = {});


      void set(const ::posix_time & time, huge_integer iNanosecond, const class ::time & timeshift);

      void set(const class ::time & time, const class ::time & timeshift);

      //void set(const ::earth::time & time, const class ::time & timeshift);

      ::posix_time get_posix_time();


      //         inline void get(struct ::tm *ptm)
      //         {
      //
      //            ptm->tm_sec = m_iSecond;
      //            ptm->tm_min = m_iMinute;
      //            ptm->tm_hour = m_iHour;
      //            ptm->tm_mday = m_iDay;
      //            ptm->tm_mon = m_iMonth;
      //            ptm->tm_year = m_iYear - 1900;
      //
      //         }


      //void get(system_time_t * psystemtime);

      //void get(file_time & filetime);



      //void Now(const class ::time &timeshift = {});


      posix_time make_utc_time() const;


   };

   constexpr int32_t is_leap_year(int year)
   {
      if (year % 400 == 0)
         return 1;
      if (year % 100 == 0)
         return 0;
      if (year % 4 == 0)
         return 1;
      return 0;
   }


   constexpr int days_from_0(int year)
   {
      year--;
      return 365 * year + (year / 400) - (year / 100) + (year / 4);
   }


   constexpr int days_from_1970(int year)
   {
      const auto days_from_0_to_1970 = days_from_0(1970);
      return days_from_0(year) - days_from_0_to_1970;
   }


   CLASS_DECL_ACME int days_from_1jan(int year, int month, int day);




} // namespace earth


