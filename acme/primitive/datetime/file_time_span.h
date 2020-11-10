#pragma once


namespace datetime
{


   class CLASS_DECL_ACME file_time_span
   {
   protected:


      ::i64 m_nSpan;


   public:


      file_time_span() noexcept;
      file_time_span(const file_time_span& span) noexcept;
      file_time_span(::i64 nSpan) noexcept;


      file_time_span& operator=(const file_time_span& span) noexcept;

      file_time_span& operator+=(file_time_span span) noexcept;
      file_time_span& operator-=(file_time_span span) noexcept;

      file_time_span operator+(file_time_span span) const noexcept;
      file_time_span operator-(file_time_span span) const noexcept;

      bool operator==(file_time_span span) const noexcept;
      bool operator!=(file_time_span span) const noexcept;
      bool operator<(file_time_span span) const noexcept;
      bool operator>(file_time_span span) const noexcept;
      bool operator<=(file_time_span span) const noexcept;
      bool operator>=(file_time_span span) const noexcept;

      ::i64 GetTimeSpan() const noexcept;
      void SetTimeSpan(::i64 nSpan) noexcept;


   };


} // namespace datetime









