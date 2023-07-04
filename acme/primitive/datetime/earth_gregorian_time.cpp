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


   namespace gregorian
   {


      posix_time time::get_time_t()
      {

         struct tm tm;

         get(&tm);

         ::posix_time time;

//   #ifdef WINDOWS
//
//         time = _mkgmtime64(&tm);
//
//   #else
//         time = timegm(&tm);
//
//   #endif

         time = make_utc_time(&tm);

         return time;

      }


      void time::get(system_time_t * psystemtime)
      {

         psystemtime->wDayOfWeek = m_iDayOfWeek;

         psystemtime->wMilliseconds = (unsigned short) (m_iNanoSecond / 1'000'000);

         psystemtime->wSecond = m_iSecond;
         psystemtime->wMinute = m_iMinute;
         psystemtime->wHour = m_iHour;
         psystemtime->wDay = m_iDay;
         psystemtime->wMonth = m_iMonth;
         psystemtime->wYear = m_iYear;

      }


      void time::set(const system_time_t * psystemtime)
      {

         m_iDayOfWeek = psystemtime->wDayOfWeek   ;

         m_iNanoSecond = psystemtime->wMilliseconds *  1'000'000;

         m_iSecond = psystemtime->wSecond      ;
         m_iMinute = psystemtime->wMinute      ;
         m_iHour = psystemtime->wHour        ;
         m_iDay = psystemtime->wDay         ;
         m_iMonth = psystemtime->wMonth       ;
         m_iYear = psystemtime->wYear        ;

      }


      void time::get(file_time_t * pfiletime)
      {

         system_time systemtime;

         get(&systemtime);

         system_time_to_file_time(pfiletime, &systemtime);

      }


      void time::set(const file_time_t * pfiletime)
      {

         system_time systemtime;

         file_time_to_system_time(&systemtime, pfiletime);

         set(&systemtime);

      }


      void time::Now(const time_shift & timeshift)
      {

         ::earth::time time;

         time.Now();

         set(time, timeshift);

      }


      time::time(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift)
      {

         set(time, iNanosecond, timeshift);

      }


      void time::set(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift)
      {

         struct tm tm;

         time.tm_struct(&tm, timeshift);

         set(&tm, iNanosecond);

      }


      void time::set(const ::earth::time & time, const time_shift & timeshift)
      {

         set(time, 0, timeshift);

      }


      time::time(const class ::time & time, const time_shift & timeshift)
      {

         set(time, timeshift);

      }


      void time::set(const class ::time & time, const time_shift & timeshift)
      {

         set({(posix_time) time.m_iSecond }, time.m_iNanosecond, timeshift);

      }




   } // namespace gregorian


} // namespace earth



