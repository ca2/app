#pragma once


//#include "earth_time.h"


namespace earth
{


   class CLASS_DECL_ACME zone_time :
      public time
   {
   public:


      class ::time     m_timeshift;


      zone_time() noexcept;
      zone_time(const zone_time & zonetime) noexcept;
      zone_time(posix_time zonetime, class ::time timeshift) noexcept;
      zone_time(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int iZoneOffset);


      static zone_time get_current_time(class ::time timeshift) noexcept;

      ::earth::gregorian_time get_zone_time() const;

      int GetZoneYear() const noexcept;
      int GetZoneMonth() const noexcept;
      int GetZoneDay() const noexcept;
      int GetZoneHour() const noexcept;
      int GetZoneMinute() const noexcept;
      int GetZoneSecond() const noexcept;
      int GetZoneDayOfWeek() const noexcept; // 1 = Sunday, 7 = Saturday

      posix_time GetZoneTimeOfDay() const noexcept;
      long long GetZoneDaySig() const noexcept;


      string FormatZone(string & str, const ::string & strFormat) const;
      string FormatZone(const ::string & strFormat);

      
   };


} // namespace earth


//#ifdef _DEBUG
//CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::earth::zone_time time);
//#endif


