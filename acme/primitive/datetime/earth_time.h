#pragma once


#include "earth_time_shift.h"
#include "acme/primitive/time/_time.h"


#if defined(ANDROID) || defined(__APPLE__)

struct tm;

#endif

struct release_time_for_project;

enum _CTIMESPANFORMATSTEP
{
   _CTFS_NONE = 0,
   _CTFS_FORMAT = 1,
   _CTFS_NZ = 2
};
#define _CTIMESPANFORMATS 3


namespace earth
{

   class gregorian_time;

   // it is in UTC by default?
   class CLASS_DECL_ACME time :
      public posix_time
   {
   public:


      //posix_time        m_posixtime;


      constexpr time() noexcept;

      inline time(now_t) noexcept : posix_time(now_t{}) { }

      //constexpr time(const time &time);

      constexpr time(const posix_time & time) noexcept;

      time(i32 nYear, i32 nMonth, i32 nDay, i32 nHour, i32 nMin, i32 nSec,
           const class ::time &timeshift = {});
      time(const release_time_for_project & release_time_for_project);
      explicit time(const ::earth::gregorian_time & gregoriantime,
         const class ::time & timeshift = {});
      explicit time(const file_time & filetime,
         const class ::time & timeshift = {});
      explicit time(const ::system_time & systemtime,
         const class ::time & timeshift = {});

#ifdef WINDOWS
      time(::u16 wDosDate, ::u16 wDosTime, i32 nDST = -1);
#endif


      static time now() noexcept;

      void Now() { *this = now(); }
      void Null() { *this = posix_time({ posix_time_t{}, 0 }); }


      constexpr time &operator=(const time &time) noexcept;


      bool is_null_or_positive() const { return m_iSecond >= 0; }

      bool is_positive() const { return m_iSecond > 0; }

      time &operator+=(date_span span);

      time &operator-=(date_span span);

      constexpr time &operator+=(time_span span) noexcept;

      constexpr time &operator-=(time_span span) noexcept;

      //time& operator+=( const time & span ) noexcept;
      //time& operator-=( const time & span ) noexcept;

      constexpr class ::time operator % (class ::time & time) const noexcept
      {

         return ((class ::time)*this) % time;

      }

      constexpr time_span operator-(time time) const noexcept;

      constexpr time operator-(time_span span) const noexcept;

      constexpr time operator+(time_span span) const noexcept;

      time operator-(date_span span) const;

      time operator+(date_span span) const;

      constexpr time operator+(class ::time & time) const;

      //time operator-(const class time & time) const;
      //time operator+(const class time & time) const;

      constexpr bool operator==(time time) const noexcept;

      //constexpr bool operator!=(time time) const noexcept;

      constexpr ::std::strong_ordering operator<=>(::earth::time time) const noexcept;

      //constexpr bool operator>(time time) const noexcept;

      //constexpr bool operator<=(time time) const noexcept;

      //constexpr bool operator>=(time time) const noexcept;

      posix_time get_time() const noexcept;

      i32 year(const class ::time &timeshift = {}) const noexcept;

      i32 month(const class ::time &timeshift = {}) const noexcept;

      i32 day(const class ::time &timeshift = {}) const noexcept;

      i32 hour(const class ::time &timeshift = {}) const noexcept;

      i32 minute(const class ::time &timeshift = {}) const noexcept;

      i32 second(const class ::time &timeshift = {}) const noexcept;

      i32 day_of_week(const class ::time &timeshift = {}) const noexcept; // 1 = Sunday, 7 = Saturday


      time get_sunday(const class ::time &timeshift = {}) const;

      posix_time time_of_day(const class ::time &timeshift = {}) const noexcept;

      i64 day_sig(const class ::time &timeshift = {}) const noexcept;


      time_span elapsed() const;

      time_span abs_diff(const ::earth::time &time) const;


      bool operator == (const class  ::time & time) const; \
      ::std::strong_ordering operator <=> (const class  ::time & time) const;


      ::i64 total_minutes(const class ::time & timeshift = {}) const noexcept;


   };


   constexpr  bool time::operator==(time time) const noexcept
   {
      return m_iSecond == time.m_iSecond;

   }


   //constexpr  bool time::operator!=(time time) const noexcept
   //{

   //   return m_posixtime != time.m_posixtime;

   //}


   constexpr ::std::strong_ordering time::operator<=>(::earth::time time) const noexcept
   {

      return m_iSecond <=> time.m_iSecond;

   }


   //constexpr  bool time::operator>(time time) const noexcept
   //{

   //   return m_posixtime > time.m_posixtime;

   //}


   //constexpr  bool time::operator<=(time time) const noexcept
   //{

   //   return m_posixtime <= time.m_posixtime;

   //}


   //constexpr  bool time::operator>=(time time) const noexcept
   //{

   //   return m_posixtime >= time.m_posixtime;

   //}


} // namespace earth


#include "earth_time_span.h"


namespace earth
{


   constexpr time_span time::operator-(time time) const noexcept
   {

      return posix_time::operator - (time);

   }


   constexpr ::earth::time time::operator-(time_span span) const noexcept
   {

      return posix_time::operator - (span);

   }


   constexpr  ::earth::time time::operator+(time_span span) const noexcept
   {

      return posix_time::operator + (span);

   }


   constexpr  time::time() noexcept// :
      //posixtime({ posix_time_t{}, 0 })
   {

   }


//   constexpr  time::time(const class time & time) :
//      posix_time(time)
//   {
//
//   }


   constexpr time::time(const posix_time & time) noexcept :
      posix_time(time)
   {

   }


   constexpr ::earth::time & time::operator=(const class time & time) noexcept
   {

      posix_time::operator =(time);
      
      return *this;

   }


   constexpr ::earth::time & time::operator+=(time_span span) noexcept
   {

      posix_time::operator+=(span);

      return *this;

   }


   constexpr ::earth::time & time::operator-=(time_span span) noexcept
   {

      posix_time::operator -= (span);

      return *this;

   }


   


   //DEFINE_COMPARISON_WITH_TIME(inline, time)

} // namespace earth






