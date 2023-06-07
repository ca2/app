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

         ::time_t get_time_t();


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


} // namespace earth