#include "framework.h"
#include "file_time_span.h"


file_time_span::file_time_span() noexcept:
   m_iFileTimeSpan(0)
{

}


file_time_span::file_time_span(const file_time_span& span) noexcept:
   m_iFileTimeSpan(span.m_iFileTimeSpan)
{

}


file_time_span::file_time_span(file_time_span_t, ::i64 nSpan) noexcept:
   m_iFileTimeSpan(nSpan)
{

}


file_time_span& file_time_span::operator=(const file_time_span& span) noexcept
{

   m_iFileTimeSpan = span.m_iFileTimeSpan;

   return *this;

}


file_time_span& file_time_span::operator+=(file_time_span span) noexcept
{

   m_iFileTimeSpan += span.m_iFileTimeSpan;

   return *this;

}


file_time_span& file_time_span::operator-=(file_time_span span) noexcept
{

   m_iFileTimeSpan -= span.m_iFileTimeSpan;

   return *this;

}


file_time_span file_time_span::operator+(file_time_span span) const noexcept
{

   return { file_time_span_t{}, m_iFileTimeSpan + span.m_iFileTimeSpan };

}


file_time_span file_time_span::operator-(file_time_span span) const noexcept
{

   return { file_time_span_t{}, m_iFileTimeSpan - span.m_iFileTimeSpan };

}


bool file_time_span::operator==(file_time_span span) const noexcept
{

   return m_iFileTimeSpan == span.m_iFileTimeSpan;

}

//
//bool file_time_span::operator!=(file_time_span span) const noexcept
//{
//
//   return(m_iFileTimeSpan != span.m_iFileTimeSpan);
//
//}
//
//
//bool file_time_span::operator<(file_time_span span) const noexcept
//{
//
//   return(m_iFileTimeSpan < span.m_iFileTimeSpan);
//
//}
//
//
//bool file_time_span::operator>(file_time_span span) const noexcept
//{
//
//   return(m_iFileTimeSpan > span.m_iFileTimeSpan);
//
//}
//
//
//bool file_time_span::operator<=(file_time_span span) const noexcept
//{
//
//   return(m_iFileTimeSpan <= span.m_iFileTimeSpan);
//
//}


std::strong_ordering file_time_span::operator<=>(file_time_span span) const noexcept
{

   return m_iFileTimeSpan <=> span.m_iFileTimeSpan;

}


::i64 file_time_span::get_file_time_span() const noexcept
{

   return(m_iFileTimeSpan);

}


void file_time_span::set_file_time_span(::i64 nSpan) noexcept
{

   m_iFileTimeSpan = nSpan;

}


::posix_time file_time_span::get_time_span() const noexcept
{

   return { posix_time_t{}, m_iFileTimeSpan * 100 };

}
