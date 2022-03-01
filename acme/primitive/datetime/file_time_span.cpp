#include "framework.h"

//
//namespace datetime
//{


   file_time_span::file_time_span() noexcept:
      m_nSpan(0)
   {
   }

   file_time_span::file_time_span(const file_time_span& span) noexcept:
      m_nSpan(span.m_nSpan)
   {
   }

   file_time_span::file_time_span(::i64 nSpan) noexcept:
      m_nSpan(nSpan)
   {
   }

   file_time_span& file_time_span::operator=(const file_time_span& span) noexcept
   {
      m_nSpan = span.m_nSpan;

      return *this;
   }

   file_time_span& file_time_span::operator+=(file_time_span span) noexcept
   {
      m_nSpan += span.m_nSpan;

      return *this;
   }

   file_time_span& file_time_span::operator-=(file_time_span span) noexcept
   {
      m_nSpan -= span.m_nSpan;

      return *this;
   }

   file_time_span file_time_span::operator+(file_time_span span) const noexcept
   {
      return(file_time_span(m_nSpan + span.m_nSpan));
   }

   file_time_span file_time_span::operator-(file_time_span span) const noexcept
   {
      return(file_time_span(m_nSpan - span.m_nSpan));
   }

   bool file_time_span::operator==(file_time_span span) const noexcept
   {
      return(m_nSpan == span.m_nSpan);
   }

   bool file_time_span::operator!=(file_time_span span) const noexcept
   {
      return(m_nSpan != span.m_nSpan);
   }

   bool file_time_span::operator<(file_time_span span) const noexcept
   {
      return(m_nSpan < span.m_nSpan);
   }

   bool file_time_span::operator>(file_time_span span) const noexcept
   {
      return(m_nSpan > span.m_nSpan);
   }

   bool file_time_span::operator<=(file_time_span span) const noexcept
   {
      return(m_nSpan <= span.m_nSpan);
   }

   bool file_time_span::operator>=(file_time_span span) const noexcept
   {
      return(m_nSpan >= span.m_nSpan);
   }

   ::i64 file_time_span::GetTimeSpan() const noexcept
   {
      return(m_nSpan);
   }

   void file_time_span::SetTimeSpan(::i64 nSpan) noexcept
   {
      m_nSpan = nSpan;
   }


//
//} // namespace datetime
//
//









