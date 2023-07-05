#pragma once


//#include "earth_time.h"


namespace earth
{


   class CLASS_DECL_ACME zonetime :
      public time
   {
   public:


      time_shift     m_timeshift;


      static zonetime get_current_time(posix_time iZone) noexcept;

      zonetime() noexcept;
      zonetime(const zonetime & zonetime) noexcept;
      zonetime(posix_time zonetime, int iZoneOffset) noexcept;
      zonetime(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 iZoneOffset);


      ::earth::gregorian::time get_zone_time() const;

      i32 GetZoneYear() const noexcept;
      i32 GetZoneMonth() const noexcept;
      i32 GetZoneDay() const noexcept;
      i32 GetZoneHour() const noexcept;
      i32 GetZoneMinute() const noexcept;
      i32 GetZoneSecond() const noexcept;
      i32 GetZoneDayOfWeek() const noexcept; // 1 = Sunday, 7 = Saturday

      posix_time GetZoneTimeOfDay() const noexcept;
      i64 GetZoneDaySig() const noexcept;


      string FormatZone(string & str, const ::string & strFormat) const;
      string FormatZone(const ::string & strFormat);

      
   };


} // namespace earth


//#ifdef __DEBUG
//CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::earth::zonetime time);
//#endif


