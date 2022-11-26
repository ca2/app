#pragma once


namespace earth
{


   class CLASS_DECL_ACME time_span :
      public integral_second
   {
   public:


      using integral_second::integral_second;


      time_span() noexcept;
      time_span(i64 lDays,i32 nHours,i32 nMins,i32 nSecs) noexcept;


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

         return INTEGRAL_SECOND(GetTotalSeconds());

      }

      
      DECLARE_COMPARISON_WITH_TIME(inline)


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

      return INTEGRAL_SECOND(m_i + span.m_i);

   }


   inline time_span time_span::operator-(time_span span) const noexcept
   {

      return INTEGRAL_SECOND(m_i - span.m_i);

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


} // namespace earth


DEFINE_COMPARISON_WITH_TIME(inline, ::earth::time_span);



