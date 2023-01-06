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
      public integral_second
   {
   public:


      using integral_second::integral_second;


      time_span() noexcept;
      time_span(i64 lDays,i32 nHours,i32 nMins,i32 nSecs) noexcept;
      time_span(const ::integral_second & second) noexcept
         : integral_second(second.m_i) {}


      i64 GetDays() const noexcept;
      i64 GetTotalHours() const noexcept;
      i32 GetHours() const noexcept;
      i64 GetTotalMinutes() const noexcept;
      i32 GetMinutes() const noexcept;
      i64 GetTotalSeconds() const noexcept;
      i32 GetSeconds() const noexcept;

      time_t GetTimeSpan() const noexcept;

      time_span operator+(time_span span) const noexcept;
      time_span operator-(time_span span) const noexcept;
      time_span& operator+=(time_span span) noexcept;
      time_span& operator-=(time_span span) noexcept;

      operator time() const
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


   };


   inline time_span::time_span() noexcept
   {

   }


   inline time_span::time_span(i64 lDays, i32 nHours, i32 nMins, i32 nSecs) noexcept
   {

      m_i = nSecs + 60 * (nMins + 60 * (nHours + i64(24) * lDays));

   }


   inline i64 time_span::GetDays() const noexcept
   {

      return m_i / (24 * 3600);

   }


   inline i64 time_span::GetTotalHours() const noexcept
   {

      return m_i / 3600;

   }


   inline i32 time_span::GetHours() const noexcept
   {

      return ::i32(GetTotalHours() - (GetDays() * 24));

   }


   inline i64 time_span::GetTotalMinutes() const noexcept
   {

      return m_i / 60;

   }


   inline i32 time_span::GetMinutes() const noexcept
   {

      return ::i32(GetTotalMinutes() - (GetTotalHours() * 60));

   }


   inline i64 time_span::GetTotalSeconds() const noexcept
   {
      return m_i;

   }


   inline i32 time_span::GetSeconds() const noexcept
   {

      return(::i32(GetTotalSeconds() - (GetTotalMinutes() * 60)));

   }


   inline time_t time_span::GetTimeSpan() const noexcept
   {

      return(m_i);

   }


   inline time_span time_span::operator+(time_span span) const noexcept
   {

      return { m_i + span.m_i };

   }


   inline time_span time_span::operator-(time_span span) const noexcept
   {

      return integral_second(m_i - span.m_i);

   }


   inline time_span& time_span::operator+=(time_span span) noexcept
   {

      m_i += span.m_i;

      return *this;

   }


   inline time_span& time_span::operator-=(time_span span) noexcept
   {

      m_i -= span.m_i;

      return *this;

   }

   //DEFINE_COMPARISON_WITH_TIME(inline, time_span);

} // namespace earth






