#pragma once


namespace datetime
{


   class CLASS_DECL_ACME zonetime :
      public time
   {
   public:


      __time64_t        m_iZoneOffset;


      static zonetime WINAPI get_current_time(__time64_t iZone) noexcept;

      zonetime() noexcept;
      zonetime(const zonetime & zonetime) noexcept;
      zonetime(__time64_t zonetime, int iZoneOffset) noexcept;
      zonetime(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 iZoneOffset);


      struct tm* GetZoneTm(struct tm* ptm) const;


      i32 GetZoneYear() const noexcept;
      i32 GetZoneMonth() const noexcept;
      i32 GetZoneDay() const noexcept;
      i32 GetZoneHour() const noexcept;
      i32 GetZoneMinute() const noexcept;
      i32 GetZoneSecond() const noexcept;
      i32 GetZoneDayOfWeek() const noexcept; // 1 = Sunday, 7 = Saturday

      __time64_t GetZoneTimeOfDay() const noexcept;
      i64 GetZoneDaySig() const noexcept;


      string FormatZone(string & str, const string & strFormat) const;
      string FormatZone(const string & strFormat);

   };

   inline string zonetime::FormatZone(const string & strFormat)
   {
      string str;
      FormatZone(str, strFormat);
      return str;
   }


} // namespace datetime


#ifdef __DEBUG
CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::datetime::zonetime time);
#endif


