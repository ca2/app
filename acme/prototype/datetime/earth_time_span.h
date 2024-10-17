#pragma once

//
//#define _EARTH_TIME_SPAN_COMPARISON_WITH(TYPE) \
//   inline bool operator == (const TYPE & t) const { return operator == (class ::time(t)); } \
//   inline ::std::strong_ordering operator <=> (const TYPE & t) const { return operator <=> (class ::time(t)); }


#define _TIME_COMPARISON_WITH(TYPE) \
   inline bool operator == (const TYPE & t) const { return operator == ((class ::time) t); } \
   inline ::std::strong_ordering operator <=> (const TYPE & t) const { return operator <=> ((class ::time) t); }


namespace earth
{


   class CLASS_DECL_ACME time_span :
      public posix_time
   {
   public:


      //posix_time m_posixtime;


      constexpr time_span() noexcept;
      constexpr time_span(i64 lDays,i32 nHours,i32 nMins,i32 nSecs) noexcept;
      constexpr time_span(const posix_time & posixtime) noexcept : posix_time(posixtime) {}
      constexpr time_span(const class ::time & time) noexcept : posix_time(time) {}


      constexpr i64 days() const noexcept;
      constexpr i64 hours() const noexcept;
      constexpr i32 hour() const noexcept;
      constexpr i64 minutes() const noexcept;
      constexpr i32 minute() const noexcept;
      constexpr i64 seconds() const noexcept;
      constexpr i32 second() const noexcept;

      constexpr posix_time GetTimeSpan() const noexcept;

      constexpr time_span operator+(time_span span) const noexcept;
      constexpr time_span operator-(time_span span) const noexcept;
      constexpr time_span& operator+=(time_span span) noexcept;
      constexpr time_span& operator-=(time_span span) noexcept;

      constexpr operator time() const
      {

         return ::earth::time({ posix_time_t{}, seconds() });

      }

      
      //DECLARE_COMPARISON_WITH_TIME(inline)


//      _TIME_COMPARISON_WITH(::integral_nanosecond);
//      _TIME_COMPARISON_WITH(::integral_microsecond);
//      _TIME_COMPARISON_WITH(::integral_millisecond);
//      //_TIME_COMPARISON_WITH(::integral_second);
//      _TIME_COMPARISON_WITH(::integral_minute);
//      _TIME_COMPARISON_WITH(::integral_hour);
//      _TIME_COMPARISON_WITH(::integral_day);
//
//      _TIME_COMPARISON_WITH(::integral_nanosecond);
//      _TIME_COMPARISON_WITH(::integral_microsecond);
//      _TIME_COMPARISON_WITH(::integral_millisecond);
//      //_TIME_COMPARISON_WITH(::integral_second);
//      _TIME_COMPARISON_WITH(::integral_minute);
//      _TIME_COMPARISON_WITH(::integral_hour);
//      _TIME_COMPARISON_WITH(::integral_day);


//      _TIME_COMPARISON_WITH(::floating_nanosecond);
//      _TIME_COMPARISON_WITH(::floating_microsecond);
//      _TIME_COMPARISON_WITH(::floating_millisecond);
//      _TIME_COMPARISON_WITH(::floating_second);
//      _TIME_COMPARISON_WITH(::floating_minute);
//      _TIME_COMPARISON_WITH(::floating_hour);
//      _TIME_COMPARISON_WITH(::floating_day);
//
//      _TIME_COMPARISON_WITH(::floating_nanosecond);
//      _TIME_COMPARISON_WITH(::floating_microsecond);
//      _TIME_COMPARISON_WITH(::floating_millisecond);
//      _TIME_COMPARISON_WITH(::floating_second);
//      _TIME_COMPARISON_WITH(::floating_minute);
//      _TIME_COMPARISON_WITH(::floating_hour);
//      _TIME_COMPARISON_WITH(::floating_day);


      constexpr class ::time operator % (class ::time & time) const noexcept
      {

         return ((class ::time) * this) % time;

      }



      constexpr ::std::strong_ordering operator <=>(const class ::time & time) const;
      constexpr ::std::strong_ordering operator <=>(const time_span & timespan) const { return m_iSecond <=> timespan.m_iSecond; }

   };


   constexpr  time_span::time_span() noexcept
   {

   }


   constexpr time_span::time_span(i64 lDays, i32 nHours, i32 nMins, i32 nSecs) noexcept
   {

      m_iSecond = nSecs + 60 * (nMins + 60 * (nHours + i64(24) * lDays));

   }


   constexpr i64 time_span::days() const noexcept
   {

      return m_iSecond / (24 * 3600);

   }


   constexpr  i64 time_span::hours() const noexcept
   {

      return m_iSecond / 3600;

   }


   constexpr  i32 time_span::hour() const noexcept
   {

      return hours() % 24;

   }


   constexpr  i64 time_span::minutes() const noexcept
   {

      return m_iSecond / 60;

   }


   constexpr  i32 time_span::minute() const noexcept
   {

      return minutes() % 60;

   }


   constexpr  i64 time_span::seconds() const noexcept
   {
      
      return m_iSecond;

   }


   constexpr  i32 time_span::second() const noexcept
   {

      return m_iSecond % 60;

   }


   constexpr posix_time time_span::GetTimeSpan() const noexcept
   {

      return *this;

   }


   constexpr time_span time_span::operator+(time_span span) const noexcept
   {

      return posix_time::operator+(span);

   }


   constexpr  time_span time_span::operator-(time_span span) const noexcept
   {

      return posix_time::operator-(span);

   }


   constexpr time_span& time_span::operator+=(time_span span) noexcept
   {

      posix_time::operator +=(span);

      return *this;

   }


   constexpr  time_span& time_span::operator-=(time_span span) noexcept
   {

      posix_time::operator -=(span);

      return *this;

   }

   //DEFINE_COMPARISON_WITH_TIME(inline, time_span);

} // namespace earth






