#pragma once


namespace datetime
{


   class CLASS_DECL_APEX file_time_span
   {
   protected:


      LONGLONG m_nSpan;


   public:


      file_time_span() noexcept;
      file_time_span(const file_time_span& span) noexcept;
      file_time_span(LONGLONG nSpan) noexcept;


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

      LONGLONG GetTimeSpan() const noexcept;
      void SetTimeSpan(LONGLONG nSpan) noexcept;


   };


} // namespace datetime









