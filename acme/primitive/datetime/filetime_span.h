#pragma once


class CLASS_DECL_ACME filetime_span
{
protected:


   ::i64 m_nSpan;


public:


   filetime_span() noexcept;
   filetime_span(const filetime_span& span) noexcept;
   filetime_span(::i64 nSpan) noexcept;


   filetime_span& operator=(const filetime_span& span) noexcept;

   filetime_span& operator+=(filetime_span span) noexcept;
   filetime_span& operator-=(filetime_span span) noexcept;

   filetime_span operator+(filetime_span span) const noexcept;
   filetime_span operator-(filetime_span span) const noexcept;

   bool operator==(filetime_span span) const noexcept;
   bool operator!=(filetime_span span) const noexcept;
   bool operator<(filetime_span span) const noexcept;
   bool operator>(filetime_span span) const noexcept;
   bool operator<=(filetime_span span) const noexcept;
   bool operator>=(filetime_span span) const noexcept;

   ::i64 GetTimeSpan() const noexcept;
   void SetTimeSpan(::i64 nSpan) noexcept;


};









