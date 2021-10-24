#pragma once


#if defined(ANDROID) || defined(__APPLE__)

struct tm;

#endif



enum _CTIMESPANFORMATSTEP
{
   _CTFS_NONE = 0,
   _CTFS_FORMAT = 1,
   _CTFS_NZ = 2
};
#define _CTIMESPANFORMATS 3


namespace datetime
{


   class CLASS_DECL_ACME time :
      public integral_second
   {
   public:


      using integral_second::integral_second;


      time() noexcept;
      inline time(enum_now) noexcept { m_i = now().m_i; }
      time(const time & time);
      time(time_t time) noexcept;
      time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 nDST = -1);
      time(const filetime & ft);
#ifdef WINDOWS
      time(::u16 wDosDate, ::u16 wDosTime, i32 nDST = -1);
#endif


      static time now() noexcept;




      time& operator=(const time & time) noexcept;


      time& operator+=( date_span span );
      time& operator-=( date_span span );

      time& operator+=( time_span span ) noexcept;
      time& operator-=( time_span span ) noexcept;

      //time& operator+=( const duration & span ) noexcept;
      //time& operator-=( const duration & span ) noexcept;

      time_span operator-( time time ) const noexcept;
      time operator-( time_span span ) const noexcept;
      time operator+( time_span span ) const noexcept;

      time operator-( date_span span ) const;
      time operator+( date_span span ) const;

      //time operator-(const duration & duration) const;
      //time operator+(const duration & duration) const;

      bool operator==( time time ) const noexcept;
      bool operator!=( time time ) const noexcept;
      bool operator<( time time ) const noexcept;
      bool operator>( time time ) const noexcept;
      bool operator<=( time time ) const noexcept;
      bool operator>=( time time ) const noexcept;

      struct ::tm* GetGmtTm( struct ::tm* ptm ) const;
      struct ::tm* GetLocalTm( struct ::tm* ptm ) const;
      /*
      #if !_SECURE_TEMPLATE
      _INSECURE_DEPRECATE("Pass an output time structure to time::GetGmtTm")
      struct tm* GetGmtTm() const noexcept;
      _INSECURE_DEPRECATE("Pass an output time structure to time::GetLocalTm")
      struct tm* GetLocalTm() const noexcept;
      #endif
      */


      time_t get_time() const noexcept;

      i32 GetYear() const noexcept;
      i32 GetMonth() const noexcept;
      i32 GetDay() const noexcept;
      i32 GetHour() const noexcept;
      i32 GetMinute() const noexcept;
      i32 GetSecond() const noexcept;
      i32 GetDayOfWeek() const noexcept; // 1 = Sunday, 7 = Saturday

      i32 GetGmtYear() const noexcept;
      i32 GetGmtMonth() const noexcept;
      i32 GetGmtDay() const noexcept;
      i32 GetGmtHour() const noexcept;
      i32 GetGmtMinute() const noexcept;
      i32 GetGmtSecond() const noexcept;
      i32 GetGmtDayOfWeek() const noexcept;

      //string Format(string & str, const ::string & strFormat) const;
      //string FormatGmt(string & str, const ::string & strFormat) const;
      //string Format(const ::string & strFormat);
      //string FormatGmt(const ::string & strFormat);

      time get_sunday() const;

      time_t GetTimeOfDay() const noexcept;
      time_t GetGmtTimeOfDay() const noexcept;

      i64 GetDaySig() const noexcept;
      i64 GetGmtDaySig() const noexcept;

//      filetime to_filetime() const;
//
//#ifdef WINDOWS
//      SYSTEMTIME to_SYSTEMTIME() const;
//#endif

      time_span elapsed() const;
      time_span abs_diff(const ::datetime::time & time) const;

   };



   inline bool time::operator==(time time) const noexcept
   {
      return(m_i == time.m_i);
   }

   inline bool time::operator!=(time time) const noexcept
   {
      return(m_i != time.m_i);
   }

   inline bool time::operator<(time time) const noexcept
   {
      return(m_i < time.m_i);
   }

   inline bool time::operator>(time time) const noexcept
   {
      return(m_i > time.m_i);
   }

   inline bool time::operator<=(time time) const noexcept
   {
      return(m_i <= time.m_i);
   }

   inline bool time::operator>=(time time) const noexcept
   {
      return(m_i >= time.m_i);
   }

   inline time_span time::operator-(time time) const noexcept
   {
      return INTEGRAL_SECOND(m_i - time.m_i);
   }

   inline ::datetime::time time::operator-(time_span span) const noexcept
   {
      return INTEGRAL_SECOND(m_i - span.m_i);
   }

   inline ::datetime::time time::operator+(time_span span) const noexcept
   {
      return m_i + span.m_i;
   }

   //inline ::datetime::time time::operator-(const duration & duration) const
   //{
   //   return time(m_i - duration.GetTimeSpan());
   //}

   //inline ::datetime::time time::operator+(const duration & duration) const
   //{
   //   return time(m_i + duration.GetTimeSpan());
   //}

   inline time::time() noexcept :
      integral_second(INTEGRAL_SECOND(0))
      {
      }
   inline time::time(const time & time) :
      integral_second(INTEGRAL_SECOND(time))
   {

   }


   inline time::time(time_t time)  noexcept :
      integral_second(INTEGRAL_SECOND(time))
   {

   }



} // namespace datetime



//inline CLASS_DECL_ACME ::datetime::time_span operator - (const duration & duration, const ::datetime::time & time)
//{
//
//   return ::datetime::time::now() - duration.GetTimeSpan() - time;
//
//}
//
//
//inline CLASS_DECL_ACME ::datetime::time operator + (const duration & duration, const ::datetime::time & time)
//{
//
//   return ::datetime::time(duration.GetTimeSpan() + time.m_i);
//
//}

//
//#ifdef WINDOWS
//
//CLASS_DECL_ACME SYSTEMTIME __SYSTEMTIME(const ::datetime::time & time);
//
//#endif


COMPARISON_WITH_DURATION(::datetime::time)


