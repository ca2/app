#pragma once


struct file_time_span_t {};


class CLASS_DECL_ACME file_time_span
{
public:


   huge_integer m_iFileTimeSpan;



   file_time_span() noexcept;
   file_time_span(const file_time_span& span) noexcept;
   file_time_span(file_time_span_t, huge_integer nSpan) noexcept;


   file_time_span& operator=(const file_time_span& span) noexcept;

   file_time_span& operator+=(file_time_span span) noexcept;
   file_time_span& operator-=(file_time_span span) noexcept;

   file_time_span operator+(file_time_span span) const noexcept;
   file_time_span operator-(file_time_span span) const noexcept;

   bool operator==(file_time_span span) const noexcept;
   //bool operator!=(file_time_span span) const noexcept;
   std::strong_ordering operator<=>(file_time_span span) const noexcept;
   //bool operator>(file_time_span span) const noexcept;
   //bool operator<=(file_time_span span) const noexcept;
   //bool operator>=(file_time_span span) const noexcept;

   huge_integer get_file_time_span() const noexcept;
   void set_file_time_span(huge_integer nSpan) noexcept;


   ::posix_time get_time_span() const noexcept;


};



