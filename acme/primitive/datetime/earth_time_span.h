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


   class CLASS_DECL_ACME time_span
   {
   public:


      time_t m_time;


      constexpr time_span() noexcept;
      constexpr time_span(i64 lDays,i32 nHours,i32 nMins,i32 nSecs) noexcept;
      constexpr time_span(const time_t & time) noexcept : m_time(time) {}


      constexpr i64 GetDays() const noexcept;
      constexpr i64 GetTotalHours() const noexcept;
      constexpr i32 GetHours() const noexcept;
      constexpr i64 GetTotalMinutes() const noexcept;
      constexpr i32 GetMinutes() const noexcept;
      constexpr i64 GetTotalSeconds() const noexcept;
      constexpr i32 GetSeconds() const noexcept;

      constexpr time_t GetTimeSpan() const noexcept;

      constexpr time_span operator+(time_span span) const noexcept;
      constexpr time_span operator-(time_span span) const noexcept;
      constexpr time_span& operator+=(time_span span) noexcept;
      constexpr time_span& operator-=(time_span span) noexcept;

      constexpr operator time() const
      {

         return ::earth::time(GetTotalSeconds());

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


      constexpr ::std::strong_ordering operator <=>(const class ::time & time) const;
      constexpr ::std::strong_ordering operator <=>(const time_span & timespan) const { return m_time <=> timespan.m_time; }

   };


   constexpr  time_span::time_span() noexcept
   {

   }


   constexpr  time_span::time_span(i64 lDays, i32 nHours, i32 nMins, i32 nSecs) noexcept
   {

      m_time = nSecs + 60 * (nMins + 60 * (nHours + i64(24) * lDays));

   }


   constexpr  i64 time_span::GetDays() const noexcept
   {

      return m_time / (24 * 3600);

   }


   constexpr  i64 time_span::GetTotalHours() const noexcept
   {

      return m_time / 3600;

   }


   constexpr  i32 time_span::GetHours() const noexcept
   {

      return ::i32(GetTotalHours() - (GetDays() * 24));

   }


   constexpr  i64 time_span::GetTotalMinutes() const noexcept
   {

      return m_time / 60;

   }


   constexpr  i32 time_span::GetMinutes() const noexcept
   {

      return ::i32(GetTotalMinutes() - (GetTotalHours() * 60));

   }


   constexpr  i64 time_span::GetTotalSeconds() const noexcept
   {
      return m_time;

   }


   constexpr  i32 time_span::GetSeconds() const noexcept
   {

      return(::i32(GetTotalSeconds() - (GetTotalMinutes() * 60)));

   }


   constexpr  time_t time_span::GetTimeSpan() const noexcept
   {

      return(m_time);

   }


   constexpr  time_span time_span::operator+(time_span span) const noexcept
   {

      return { m_time + span.m_time };

   }


   constexpr  time_span time_span::operator-(time_span span) const noexcept
   {

      return m_time - span.m_time;

   }


   constexpr  time_span& time_span::operator+=(time_span span) noexcept
   {

      m_time += span.m_time;

      return *this;

   }


   constexpr  time_span& time_span::operator-=(time_span span) noexcept
   {

      m_time -= span.m_time;

      return *this;

   }

   //DEFINE_COMPARISON_WITH_TIME(inline, time_span);

} // namespace earth






