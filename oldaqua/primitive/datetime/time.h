#pragma once


#if defined(ANDROID) || defined(__APPLE__)

struct tm;

#endif


namespace datetime
{


   enum e_now
   {

      now,

   };


   class CLASS_DECL_AQUA time
   {
   public:

#if defined(ANDROID) || defined(APPLEOS) || defined(SOLARIS) || defined(RASPBIAN)
      time_t         m_time;
#else
      __time64_t m_time;
#endif


      static time get_current_time() noexcept;
      inline static time now() noexcept { return get_current_time(); }
      static bool is_valid_FILETIME(const FILETIME& ft) noexcept;


      time() noexcept;
      inline time(e_now) noexcept { m_time = now().m_time; }
      time(__time64_t time) noexcept;
      time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, i32 nDST = -1);
      time(WORD wDosDate, WORD wDosTime, i32 nDST = -1);
      time(const SYSTEMTIME& st, i32 nDST = -1);
      time(const FILETIME& ft, i32 nDST = -1);

      time& operator=(const time & time) noexcept;


      time& operator+=( date_span span );
      time& operator-=( date_span span );

      time& operator+=( time_span span ) noexcept;
      time& operator-=( time_span span ) noexcept;

      time& operator+=( const duration & span ) noexcept;
      time& operator-=( const duration & span ) noexcept;

      time_span operator-( time time ) const noexcept;
      time operator-( time_span span ) const noexcept;
      time operator+( time_span span ) const noexcept;

      time operator-( date_span span ) const;
      time operator+( date_span span ) const;

      time operator-(const duration & duration) const;
      time operator+(const duration & duration) const;

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

      bool get_as_system_time( SYSTEMTIME& st ) const noexcept;

      __time64_t get_time() const noexcept;

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

      string Format(string & str, const string & strFormat) const;
      string FormatGmt(string & str, const string & strFormat) const;
      string Format(const string & strFormat);
      string FormatGmt(const string & strFormat);

      time get_sunday() const;

      __time64_t GetTimeOfDay() const noexcept;
      __time64_t GetGmtTimeOfDay() const noexcept;

      i64 GetDaySig() const noexcept;
      i64 GetGmtDaySig() const noexcept;


      FILETIME to_file_time() const;
      SYSTEMTIME to_system_time() const;

      time_span elapsed() const;
      time_span abs_diff(const ::datetime::time & time) const;

   };



   enum _CTIMESPANFORMATSTEP
   {
      _CTFS_NONE   = 0,
      _CTFS_FORMAT = 1,
      _CTFS_NZ     = 2
   };
#define _CTIMESPANFORMATS 3



   inline string time::Format(const string & strFormat)
   {
      string str;
      Format(str, strFormat);
      return str;
   }
   inline string time::FormatGmt(const string & strFormat)
   {
      string str;
      FormatGmt(str, strFormat);
      return str;
   }

   inline bool time::operator==(time time) const noexcept
   {
      return(m_time == time.m_time);
   }

   inline bool time::operator!=(time time) const noexcept
   {
      return(m_time != time.m_time);
   }

   inline bool time::operator<(time time) const noexcept
   {
      return(m_time < time.m_time);
   }

   inline bool time::operator>(time time) const noexcept
   {
      return(m_time > time.m_time);
   }

   inline bool time::operator<=(time time) const noexcept
   {
      return(m_time <= time.m_time);
   }

   inline bool time::operator>=(time time) const noexcept
   {
      return(m_time >= time.m_time);
   }

   inline time_span time::operator-(time time) const noexcept
   {
      return(time_span(m_time - time.m_time));
   }

   inline ::datetime::time time::operator-(time_span span) const noexcept
   {
      return(time(m_time - span.GetTimeSpan()));
   }

   inline ::datetime::time time::operator+(time_span span) const noexcept
   {
      return m_time + span.m_timeSpan;
   }

   inline ::datetime::time time::operator-(const duration & duration) const
   {
      return time(m_time - duration.GetTimeSpan());
   }

   inline ::datetime::time time::operator+(const duration & duration) const
   {
      return time(m_time + duration.GetTimeSpan());
   }

inline time::time() noexcept :
   m_time(0)
   {
   }

inline time::time(__time64_t time)  noexcept :
   m_time(time)
   {
   }


} // namespace datetime


#ifdef __DEBUG
CLASS_DECL_AQUA dump_context & operator <<(dump_context & dumpcontext, ::datetime::time time);
CLASS_DECL_AQUA dump_context & operator <<(dump_context & dumpcontext, ::datetime::time_span time);
#endif




inline CLASS_DECL_AQUA ::datetime::time_span operator - (const duration & duration, const ::datetime::time & time)
{

   return ::datetime::time_span(::datetime::time::get_current_time().m_time - duration.GetTimeSpan() - time.m_time);

}


inline CLASS_DECL_AQUA ::datetime::time operator + (const duration & duration, const ::datetime::time & time)
{

   return ::datetime::time(duration.GetTimeSpan() + time.m_time);

}


