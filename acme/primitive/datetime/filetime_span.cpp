#include "framework.h"

//
//namespace datetime
//{


   filetime_span::filetime_span() noexcept:
      m_nSpan(0)
   {
   }

   filetime_span::filetime_span(const filetime_span& span) noexcept:
      m_nSpan(span.m_nSpan)
   {
   }

   filetime_span::filetime_span(::i64 nSpan) noexcept:
      m_nSpan(nSpan)
   {
   }

   filetime_span& filetime_span::operator=(const filetime_span& span) noexcept
   {
      m_nSpan = span.m_nSpan;

      return *this;
   }

   filetime_span& filetime_span::operator+=(filetime_span span) noexcept
   {
      m_nSpan += span.m_nSpan;

      return *this;
   }

   filetime_span& filetime_span::operator-=(filetime_span span) noexcept
   {
      m_nSpan -= span.m_nSpan;

      return *this;
   }

   filetime_span filetime_span::operator+(filetime_span span) const noexcept
   {
      return(filetime_span(m_nSpan + span.m_nSpan));
   }

   filetime_span filetime_span::operator-(filetime_span span) const noexcept
   {
      return(filetime_span(m_nSpan - span.m_nSpan));
   }

   bool filetime_span::operator==(filetime_span span) const noexcept
   {
      return(m_nSpan == span.m_nSpan);
   }

   bool filetime_span::operator!=(filetime_span span) const noexcept
   {
      return(m_nSpan != span.m_nSpan);
   }

   bool filetime_span::operator<(filetime_span span) const noexcept
   {
      return(m_nSpan < span.m_nSpan);
   }

   bool filetime_span::operator>(filetime_span span) const noexcept
   {
      return(m_nSpan > span.m_nSpan);
   }

   bool filetime_span::operator<=(filetime_span span) const noexcept
   {
      return(m_nSpan <= span.m_nSpan);
   }

   bool filetime_span::operator>=(filetime_span span) const noexcept
   {
      return(m_nSpan >= span.m_nSpan);
   }

   ::i64 filetime_span::GetTimeSpan() const noexcept
   {
      return(m_nSpan);
   }

   void filetime_span::SetTimeSpan(::i64 nSpan) noexcept
   {
      m_nSpan = nSpan;
   }


//
//} // namespace datetime
//
//









