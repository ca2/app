#pragma once

namespace datetime
{


   class CLASS_DECL_ACME time_span
   {
   public:


      time_t m_timeSpan;


      time_span() noexcept;
      time_span(time_t time) noexcept;
      time_span(const ::millis & millis) noexcept;
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
      bool operator==(time_span span) const noexcept;
      bool operator!=(time_span span) const noexcept;
      bool operator<(time_span span) const noexcept;
      bool operator>(time_span span) const noexcept;
      bool operator<=(time_span span) const noexcept;
      bool operator>=(time_span span) const noexcept;

      string Format(const char * pszFormat) const;
      
      operator duration() const
      {
         return seconds(GetTotalSeconds());
      }

      operator millis() const
      {
         return GetTotalSeconds() * 1000;
   }

#ifdef _AFX
      //   CArchive& Serialize64(CArchive& ar);
#endif

   };

   inline time_span::time_span() noexcept :
      m_timeSpan(0)
   {
   }

   inline time_span::time_span(time_t time) noexcept :
      m_timeSpan(time)
   {
   }

   inline time_span::time_span(const ::millis & millis) noexcept :
      m_timeSpan(millis.seconds())
   {
   }

   inline time_span::time_span(i64 lDays, i32 nHours, i32 nMins, i32 nSecs) noexcept
   {
      m_timeSpan = nSecs + 60 * (nMins + 60 * (nHours + i64(24) * lDays));
   }

   inline i64 time_span::GetDays() const noexcept
   {
      return(m_timeSpan / (24 * 3600));
   }

   inline i64 time_span::GetTotalHours() const noexcept
   {
      return(m_timeSpan / 3600);
   }

   inline i32 time_span::GetHours() const noexcept
   {
      return(::i32(GetTotalHours() - (GetDays() * 24)));
   }

   inline i64 time_span::GetTotalMinutes() const noexcept
   {
      return(m_timeSpan / 60);
   }

   inline i32 time_span::GetMinutes() const noexcept
   {
      return(::i32(GetTotalMinutes() - (GetTotalHours() * 60)));
   }

   inline i64 time_span::GetTotalSeconds() const noexcept
   {
      return(m_timeSpan);
   }

   inline i32 time_span::GetSeconds() const noexcept
   {
      return(::i32(GetTotalSeconds() - (GetTotalMinutes() * 60)));
   }

   inline time_t time_span::GetTimeSpan() const noexcept
   {
      return(m_timeSpan);
   }

   inline time_span time_span::operator+(time_span span) const noexcept
   {
      return(time_span(m_timeSpan + span.m_timeSpan));
   }

   inline time_span time_span::operator-(time_span span) const noexcept
   {
      return(time_span(m_timeSpan - span.m_timeSpan));
   }

   inline time_span& time_span::operator+=(time_span span) noexcept
   {
      m_timeSpan += span.m_timeSpan;
      return *this;
   }

   inline time_span& time_span::operator-=(time_span span) noexcept
   {
      m_timeSpan -= span.m_timeSpan;
      return *this;
   }

   inline bool time_span::operator==(time_span span) const noexcept
   {
      return(m_timeSpan == span.m_timeSpan);
   }

   inline bool time_span::operator!=(time_span span) const noexcept
   {
      return(m_timeSpan != span.m_timeSpan);
   }

   inline bool time_span::operator<(time_span span) const noexcept
   {
      return(m_timeSpan < span.m_timeSpan);
   }

   inline bool time_span::operator>(time_span span) const noexcept
   {
      return(m_timeSpan > span.m_timeSpan);
   }

   inline bool time_span::operator<=(time_span span) const noexcept
   {
      return(m_timeSpan <= span.m_timeSpan);
   }

   inline bool time_span::operator>=(time_span span) const noexcept
   {
      return(m_timeSpan >= span.m_timeSpan);
   }



} // namespace datetime





