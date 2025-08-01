#include "framework.h"
#include "earth_zone_time.h"
#include "earth_gregorian_time.h"
#include "acme/prototype/string/str.h"
#include <time.h>


namespace earth
{


   ::earth::zone_time zone_time::get_current_time(class ::time timeshift) noexcept
   {

      zone_time t;

#ifdef WINDOWS

      t.m_iSecond = ::_time64(nullptr);

#else

      t.m_iSecond = ::time(nullptr);

#endif

      t.m_timeshift = timeshift;

      return t;

   }

   
   zone_time::zone_time() noexcept
   {

   }


   zone_time::zone_time(const zone_time & zone_time) noexcept :
      time(zone_time),
      m_timeshift(zone_time.m_timeshift)
   {


   }


   zone_time::zone_time(posix_time zone_time, class ::time timeshift) noexcept :
      time(zone_time),
      m_timeshift(timeshift)
   {

   }


   zone_time::zone_time(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int iZoneOffset)
   {

       ::earth::gregorian_time gregoriantime;

       gregoriantime.m_iSecond = nSec;
       gregoriantime.m_iMinute = nMin;
       gregoriantime.m_iHour = nHour;
       gregoriantime.m_iDay = nDay;
       gregoriantime.m_iMonth = nMonth - 1;        // tm_mon is 0 based
       gregoriantime.m_iYear = nYear;
       //atm.tm_isdst = nDST;

//      struct tm atm;
//
//      atm.tm_sec = nSec;
//      atm.tm_min = nMin;
//      atm.tm_hour = nHour;
//      atm.tm_mday = nDay;
//      atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
//      atm.tm_year = nYear - 1900;     // tm_year is 1900 based
//      atm.tm_isdst = 0;

      time::operator=(gregoriantime.make_utc_time());

      m_timeshift.m_iSecond = iZoneOffset;
      m_timeshift.m_iNanosecond = 0;
         

      /*
      Remember that:
      ENSURE( nYear >= 1900 );
      ENSURE( nMonth >= 1 && nMonth <= 12 );
      ENSURE( nDay >= 1 && nDay <= 31 );
      ENSURE( nHour >= 0 && nHour <= 23 );
      ENSURE( nMin >= 0 && nMin <= 59 );
      ENSURE( nSec >= 0 && nSec <= 59 );
      ASSUME(m_posixtime != -1);   */    // indicates an illegal input zone_time
      if (m_iSecond == -1)
      {
         
         throw ::exception(error_invalid_time_type);

      }

   }


//   struct tm* zone_time::GetZoneTm(struct tm* ptm) const
//   {
//
//      if (ptm != nullptr)
//      {
//
//
//#ifdef WINDOWS
//
//         struct tm tmTemp;
//
//         time_t t = m_iSecond;
//
//         t += (int) m_timeshift;
//
//         errno_t err = _gmtime64_s(&tmTemp, &t);
//
//         if (err != 0)
//         {
//            return nullptr;    // indicates that m_posixtime was not initialized!
//         }
//
//         *ptm = tmTemp;
//
//         return ptm;
//
//#else
//
//         struct tm * ptmTemp;
//
//         auto t = m_iSecond;
//
//         t += (long long) m_timeshift.m_d;
//
//         ptmTemp = gmtime(&t);
//
//         // gmtime can return nullptr
//         if (ptmTemp == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         // but don't throw ::exception( exception or generate error...
//         // (reason for commenting out below, fat to be erased...)
//         //         if(errno != 0)
//         //          return nullptr;
//
//         *ptm = *ptmTemp;
//
//         return ptm;
//
//#endif
//
//      }
//      else
//      {
//
//         return nullptr;
//
//      }
//
//
//   }


   int zone_time::GetZoneYear() const noexcept
   {

        auto time = get_zone_time();

        return time.m_iYear;

   }


   int zone_time::GetZoneMonth() const noexcept
   {

       auto time = get_zone_time();

       return time.m_iMonth + 1;

   }


   int zone_time::GetZoneDay() const noexcept
   {

       {

           auto time = get_zone_time();

           return time.m_iDay;

       }

   }


   int zone_time::GetZoneHour() const noexcept
   {

       auto time = get_zone_time();

       return time.m_iHour;

   }



   int zone_time::GetZoneMinute() const noexcept
   {

       auto time = get_zone_time();

       return time.m_iMinute;

   }



   int zone_time::GetZoneSecond() const noexcept
   {

       auto time = get_zone_time();

       return time.m_iSecond;

   }



   int zone_time::GetZoneDayOfWeek() const noexcept
   {

       auto time = get_zone_time();

       return time.m_iDayOfWeek;

   }


   string zone_time::FormatZone(string & str, const ::scoped_string & scopedstrFormat) const
   {

      str = scopedstrFormat;

      str.replace_with(as_string(GetZoneYear()), "%Y");
      str.replace_with(::str::zero_padded(as_string(GetZoneMonth()), 2), "%m");
      str.replace_with(::str::zero_padded(as_string(GetZoneDay()), 2), "%d");
      str.replace_with(::str::zero_padded(as_string(GetZoneHour()), 2), "%H");
      str.replace_with(::str::zero_padded(as_string(GetZoneMinute()), 2), "%M");
      str.replace_with(::str::zero_padded(as_string(GetZoneSecond()), 2), "%S");

      return str;

   }


   posix_time zone_time::GetZoneTimeOfDay() const noexcept
   {

       auto time = get_zone_time();

      return { posix_time_t{}, (time.m_iHour * 3600) + (time.m_iMinute * 60) + time.m_iSecond };

   }


   long long zone_time::GetZoneDaySig() const noexcept
   {

       auto time = get_zone_time();

      return ((time.m_iYear -1900) * 500) + (time.m_iMonth * 40) + time.m_iDay;

   }


   string zone_time::FormatZone(const ::scoped_string & scopedstrFormat)
   {
   
      string str;
   
      FormatZone(str, scopedstrFormat);
   
      return str;

   }


} // namespace earth


//#ifdef _DEBUG
//
//
//dump_context & operator <<(dump_context & dumpcontext, ::earth::zone_time zone_time)
//{
//   //char psz[32];
//   //psz[0] = '\0';
//
//   ////   posix_time tmp = zone_time.get_time();
//   ////   errno_t err = _ctime64_s(scopedstr, sizeof(scopedstr), &tmp);
//
//   //errno_t err = 0;
//
//   //if ((err != 0) || (scopedstr[0] == '\0') || (zone_time.get_time() == 0))
//   //{
//   //   dumpcontext << "::earth::zone_time(invalid #" << (iptr)zone_time.get_time() << ")";
//
//   //   return dumpcontext;
//   //}
//
//   //// format it
//   //dumpcontext << "::earth::zone_time(\"" << psz << "\")";
//
//   return dumpcontext;
//}
//
//#endif
