#pragma once


#include "earth_time_shift.h"
//#include "acme/primitive/time/_.h"


#if defined(ANDROID) || defined(__APPLE__)

struct tm;

#endif



enum _CTIMESPANFORMATSTEP
{
   _CTFS_NONE = 0,
   _CTFS_FORMAT = 1,
   _CTFS_NZ = 2
};
#define _CTIMESPANFORMATS 3


namespace earth
{

   namespace gregorian
   {

      class time;

   }

   // it is in UTC by default?
   class CLASS_DECL_ACME time :
      public integral_second
   {
   public:


      using integral_second::integral_second;


      time() noexcept;

      inline time(enum_now) noexcept { m_i = now().m_i; }

      time(const time &time);

      time(time_t time) noexcept;

      time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec,
           const time_shift &timeshift = time_shift::none());
      time(const ::earth::gregorian::time & gregoriantime, 
         const time_shift & timeshift = time_shift::none());

      time(const file_time &ft);

#ifdef WINDOWS
      time(::u16 wDosDate, ::u16 wDosTime, i32 nDST = -1);
#endif


      static time now() noexcept;


      time &operator=(const time &time) noexcept;


      time &operator+=(date_span span);

      time &operator-=(date_span span);

      time &operator+=(time_span span) noexcept;

      time &operator-=(time_span span) noexcept;

      //time& operator+=( const time & span ) noexcept;
      //time& operator-=( const time & span ) noexcept;

      time_span operator-(time time) const noexcept;

      time operator-(time_span span) const noexcept;

      time operator+(time_span span) const noexcept;

      time operator-(date_span span) const;

      time operator+(date_span span) const;

      //time operator-(const class time & time) const;
      //time operator+(const class time & time) const;

      bool operator==(time time) const noexcept;

      bool operator!=(time time) const noexcept;

      bool operator<(time time) const noexcept;

      bool operator>(time time) const noexcept;

      bool operator<=(time time) const noexcept;

      bool operator>=(time time) const noexcept;

      struct ::tm *tm_struct(struct ::tm *ptm, const ::earth::time_shift &timeshift = time_shift::none()) const;

      time_t get_time() const noexcept;

      i32 year(const time_shift &timeshift = time_shift::none()) const noexcept;

      i32 month(const time_shift &timeshift = time_shift::none()) const noexcept;

      i32 day(const time_shift &timeshift = time_shift::none()) const noexcept;

      i32 hour(const time_shift &timeshift = time_shift::none()) const noexcept;

      i32 minute(const time_shift &timeshift = time_shift::none()) const noexcept;

      i32 second(const time_shift &timeshift = time_shift::none()) const noexcept;

      i32 day_of_week(const time_shift &timeshift = time_shift::none()) const noexcept; // 1 = Sunday, 7 = Saturday


      time get_sunday(const time_shift &timeshift = time_shift::none()) const;

      time_t time_of_day(const time_shift &timeshift = time_shift::none()) const noexcept;

      i64 day_sig(const time_shift &timeshift = time_shift::none()) const noexcept;


      time_span elapsed() const;

      time_span abs_diff(const ::earth::time &time) const;


      DECLARE_COMPARISON_WITH_TIME(inline)

   };


   inline bool time::operator==(time time) const noexcept
   {
      return m_i == time.m_i;

   }


   inline bool time::operator!=(time time) const noexcept
   {

      return m_i != time.m_i;

   }


   inline bool time::operator<(time time) const noexcept
   {

      return m_i < time.m_i;

   }


   inline bool time::operator>(time time) const noexcept
   {

      return m_i > time.m_i;

   }


   inline bool time::operator<=(time time) const noexcept
   {

      return m_i <= time.m_i;

   }


   inline bool time::operator>=(time time) const noexcept
   {

      return m_i >= time.m_i;

   }


} // namespace earth


#include "time_span.h"


namespace earth
{


   inline time_span time::operator-(time time) const noexcept
   {

      return INTEGRAL_SECOND(m_i - time.m_i);

   }


   inline ::earth::time time::operator-(time_span span) const noexcept
   {

      return INTEGRAL_SECOND(m_i - span.m_i);

   }


   inline ::earth::time time::operator+(time_span span) const noexcept
   {

      return m_i + span.m_i;

   }


   inline time::time() noexcept :
      integral_second(INTEGRAL_SECOND(0))
   {

   }


   inline time::time(const class time & time) :
      integral_second(INTEGRAL_SECOND(time))
   {

   }


   inline time::time(time_t time)  noexcept :
      integral_second(INTEGRAL_SECOND(time))
   {

   }




} // namespace earth


DEFINE_COMPARISON_WITH_TIME(inline, ::earth::time)



