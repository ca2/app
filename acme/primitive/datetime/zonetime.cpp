#include "framework.h"
#include "zonetime.h"
#include "acme/primitive/datetime/earth_gregorian_time.h"
#include "acme/primitive/string/str.h"
#include <time.h>


namespace earth
{


   ::earth::zonetime zonetime::get_current_time(posix_time iZoneOffset) noexcept
   {

      zonetime t;

#ifdef WINDOWS

      t.m_posixtime = { posix_time_t {}, ::_time64(nullptr) };

#else

      t.m_posixtime = { posix_time_t {},::time(nullptr) };

#endif

      t.m_timeshift = (double) iZoneOffset.m_iSecond;

      return t;

   }

   
   zonetime::zonetime() noexcept :
      time(0)
   {

   }


   zonetime::zonetime(const zonetime & zonetime) noexcept :
      time(zonetime.m_posixtime),
      m_timeshift(zonetime.m_timeshift)
   {


   }


   zonetime::zonetime(posix_time zonetime, int iZoneOffset) noexcept :
      time(zonetime),
      m_timeshift((double)iZoneOffset)
   {

   }


   zonetime::zonetime(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 iZoneOffset)
   {


      struct tm atm;

      atm.tm_sec = nSec;
      atm.tm_min = nMin;
      atm.tm_hour = nHour;
      atm.tm_mday = nDay;
      atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
      atm.tm_year = nYear - 1900;     // tm_year is 1900 based
      atm.tm_isdst = 0;

      m_posixtime = ::earth::make_utc_time(&atm);

      /*
      Remember that:
      ENSURE( nYear >= 1900 );
      ENSURE( nMonth >= 1 && nMonth <= 12 );
      ENSURE( nDay >= 1 && nDay <= 31 );
      ENSURE( nHour >= 0 && nHour <= 23 );
      ENSURE( nMin >= 0 && nMin <= 59 );
      ENSURE( nSec >= 0 && nSec <= 59 );
      ASSUME(m_posixtime != -1);   */    // indicates an illegal input zonetime
      if (m_posixtime.m_iSecond == -1)
      {
         
         throw ::exception(error_invalid_time_type);

      }

   }


   struct tm* zonetime::GetZoneTm(struct tm* ptm) const
   {

      if (ptm != nullptr)
      {


#ifdef WINDOWS

         struct tm tmTemp;

         time_t t = m_posixtime.m_iSecond;

         t += (::i32) m_timeshift;

         errno_t err = _gmtime64_s(&tmTemp, &t);

         if (err != 0)
         {
            return nullptr;    // indicates that m_posixtime was not initialized!
         }

         *ptm = tmTemp;

         return ptm;

#else

         struct tm * ptmTemp;

         posix_time t = m_posixtime;

         t += (posix_time) m_timeshift.m_d;

         ptmTemp = gmtime(&t);

         // gmtime can return nullptr
         if (ptmTemp == nullptr)
         {

            return nullptr;

         }

         // but don't throw ::exception( exception or generate error...
         // (reason for commenting out below, fat to be erased...)
         //         if(errno != 0)
         //          return nullptr;

         *ptm = *ptmTemp;

         return ptm;

#endif

      }
      else
      {

         return nullptr;

      }


   }


   i32 zonetime::GetZoneYear() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? (ptm->tm_year) + 1900 : 0;

   }


   i32 zonetime::GetZoneMonth() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ptm->tm_mon + 1 : 0;

   }


   i32 zonetime::GetZoneDay() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ptm->tm_mday : 0;

   }


   i32 zonetime::GetZoneHour() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ptm->tm_hour : -1;

   }


   i32 zonetime::GetZoneMinute() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ptm->tm_min : -1;

   }


   i32 zonetime::GetZoneSecond() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ptm->tm_sec : -1;

   }


   i32 zonetime::GetZoneDayOfWeek() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ptm->tm_wday + 1 : 0;
      
   }


   string zonetime::FormatZone(string & str, const ::string & strFormat) const
   {

      str = strFormat;

      str.replace_with(as_string(GetZoneYear()), "%Y");
      str.replace_with(::str::zero_padded(as_string(GetZoneMonth()), 2), "%m");
      str.replace_with(::str::zero_padded(as_string(GetZoneDay()), 2), "%d");
      str.replace_with(::str::zero_padded(as_string(GetZoneHour()), 2), "%H");
      str.replace_with(::str::zero_padded(as_string(GetZoneMinute()), 2), "%M");
      str.replace_with(::str::zero_padded(as_string(GetZoneSecond()), 2), "%S");

      return str;

   }


   posix_time zonetime::GetZoneTimeOfDay() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return { posix_time_t{}, ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0 };

   }


   i64 zonetime::GetZoneDaySig() const noexcept
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   }


   string zonetime::FormatZone(const ::string & strFormat)
   {
   
      string str;
   
      FormatZone(str, strFormat);
   
      return str;

   }


} // namespace earth


//#ifdef __DEBUG
//
//
//dump_context & operator <<(dump_context & dumpcontext, ::earth::zonetime zonetime)
//{
//   //char psz[32];
//   //psz[0] = '\0';
//
//   ////   posix_time tmp = zonetime.get_time();
//   ////   errno_t err = _ctime64_s(psz, sizeof(psz), &tmp);
//
//   //errno_t err = 0;
//
//   //if ((err != 0) || (psz[0] == '\0') || (zonetime.get_time() == 0))
//   //{
//   //   dumpcontext << "::earth::zonetime(invalid #" << (iptr)zonetime.get_time() << ")";
//
//   //   return dumpcontext;
//   //}
//
//   //// format it
//   //dumpcontext << "::earth::zonetime(\"" << psz << "\")";
//
//   return dumpcontext;
//}
//
//#endif
