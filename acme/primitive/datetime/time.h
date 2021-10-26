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


class time_shift
{
public:

   double      m_d;

   static constexpr time_shift none() // UTC
   { 
      
      return { 0.0 };
   
   }

   static inline time_shift local()
   {
      time_t zero = 0;
      const tm* lt = localtime(&zero);
      int unaligned = lt->tm_sec + (lt->tm_min + (lt->tm_hour * 60)) * 60;
      return { (double)(lt->tm_mon ? unaligned - 24 * 60 * 60 : unaligned) };
   }


};


namespace datetime
{


   // it is in UTC by default?
   class CLASS_DECL_ACME time :
      public integral_second
   {
   public:


      using integral_second::integral_second;


      time() noexcept;
      inline time(enum_now) noexcept { m_i = now().m_i; }
      time(const time & time);
      time(time_t time) noexcept;
      time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec, const ::time_shift& timeshift = ::time_shift::none());
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

      struct ::tm* tm_struct( struct ::tm* ptm, const time_shift& timeshift = ::time_shift::none()) const;


      time_t get_time() const noexcept;

      i32 year(const time_shift & timeshift = ::time_shift::none()) const noexcept;
      i32 month(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      i32 day(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      i32 hour(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      i32 minute(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      i32 second(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      i32 day_of_week(const time_shift& timeshift = ::time_shift::none()) const noexcept; // 1 = Sunday, 7 = Saturday


      time get_sunday(const time_shift& timeshift = ::time_shift::none()) const;

      time_t time_of_day(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      
      i64 day_sig(const time_shift& timeshift = ::time_shift::none()) const noexcept;
      
      
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


