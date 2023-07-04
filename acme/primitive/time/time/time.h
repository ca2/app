// Refactoring by camilo on 2021-10-05 12:46 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/mathematics/numeric.h"
#include "acme/primitive/time/_structures.h"


#define _TIME_COMPARISON_WITH(TYPE) \
   inline bool operator == (const TYPE & t) const { return operator == ((class ::time) t); } \
   inline ::std::strong_ordering operator <=> (const TYPE & t) const { return operator <=> ((class ::time) t); }


class CLASS_DECL_ACME time :
   public TIME
{
public:


   enum enum_unit
   {

      unit_nanos,
      unit_micros,
      unit_millis,
      unit_seconds,
      unit_minutes,
      unit_hours,
      unit_days

   };


   static time s_timeFirst;

   constexpr time(enum_zero ezero = e_zero) :
      TIME{}
   {

   }


   time(enum_now)
   {

      Now();

   }


   constexpr time(enum_infinite)
   {

      *this = ::time::infinity();

   }



   constexpr time(const class ::time& time) : TIME{time} { }

   template < primitive_integer INTEGER >
   constexpr time(INTEGER iSecond)
      : TIME{ .m_posixtime = {posix_time_t{}, (::i64)iSecond}, .m_nanosecond = {nanosecond_t{}, 0} }
   {
      
      
   }

   template < primitive_floating FLOATING >
   time(FLOATING fSeconds)
   {

      fset(fSeconds);

   }

   template < primitive_integer INTEGER1, primitive_integral INTEGRAL2 >
   constexpr time(INTEGER1 iSecond, INTEGRAL2 iNanosecond) :
      TIME{ .m_posixtime = {posix_time_t{}, (::i64)iSecond}, .m_nanosecond = {nanosecond_t{}, (::i64)iNanosecond} }
   { }


   template < primitive_floating FLOATING, primitive_number NUMBER >
   time(FLOATING fSeconds, NUMBER nanoseconds)
   {
        
       fset(fSeconds, nanoseconds);
        
   }

   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   constexpr time(enum_raw, INTEGRAL1 iSecond, INTEGRAL2 iNanosecond)
   {
         m_posixtime.m_iSecond = iSecond;

         m_nanosecond.m_iNanosecond = iNanosecond;
   }

   template < primitive_integral INTEGRAL1 >
   constexpr time(enum_raw, INTEGRAL1 iSecond) : time(e_raw, iSecond, 0) {}
   
   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   constexpr time(enum_normalize, INTEGRAL1 iSecond, INTEGRAL2 iNanosecond)
   {

      m_posixtime.m_iSecond = iSecond + iNanosecond / 1'000'000'000;

      m_nanosecond.m_iNanosecond = iNanosecond % 1'000'000'000;
      
      while(m_nanosecond.m_iNanosecond < 0)
      {

         m_posixtime.m_iSecond--;

         m_nanosecond.m_iNanosecond += 1'000'000'000;

      }

   }


   constexpr time(const ::TIME & time) : TIME(time) {}


   constexpr void raw_set(posix_time posixtime, nanosecond nanosecond = { nanosecond_t{}, 0 });
   constexpr void set(posix_time posixtime, nanosecond nanosecond);
   constexpr void set_null();
   static constexpr time raw_create(posix_time posixtime, nanosecond nanosecond);
   static constexpr time create(posix_time posixtime, nanosecond nanosecond);
   static constexpr time create_null();


   void fset(long double dSeconds);
   void fset(long double dSeconds, double dNanoseconds);
   static time fcreate(long double dSeconds, double dNanoseconds);


   constexpr void set(i64 i, enum_unit eunit);
   void set(long double d, enum_unit eunit);


   //inline bool is_infinity() const;
   constexpr bool is_infinite() const;
   //constexpr bool is_zero() const;
   //constexpr bool is_set() const { return (m_posixtime.m_iSecond >= 0 && m_nanosecond.m_iNanosecond > 0) || (m_posixtime.m_iSecond > 0 && m_nanosecond.m_iNanosecond >= 0); }
   constexpr static class ::time infinity();
   //inline static time pos_infinity();
   //constexpr static time zero();
//   constexpr bool operator !() const {return is_null();}

   //constexpr void infinite() {*this=infinity();}
   //void PosInfinity() {*this=pos_infinity();}
   //constexpr void zero() { this->m_posixtime.m_iSecond = 0; this->m_nanosecond.m_iNanosecond = 0; }
   //constexpr void Null() { Zero(); }

   constexpr class ::time & operator = (const class time & time);
   constexpr class ::time & operator = (const ::earth::time_span & time);

   inline bool timeout(const class time & time) { return timeout(time, now()); }
   constexpr bool timeout(const class time & time, const class time & timeNow);
   constexpr void normalize();

   //constexpr operator bool() const;


   //constexpr  double operator() ()const { return floating_second(); }


   //static inline class ::time first();
  [[nodiscard]] static inline class ::time now() { return e_now; }

   inline bool is_past() const { return now() > *this; }

   inline class ::time & Now();
     

   inline class time elapsed() const { return elapsed(now()); }
   constexpr class time elapsed(const class time & time ) const { return time - *this; }


   inline time update_elapsed() { return update_elapsed(now()); }

   constexpr time update_elapsed(const class time & timeStop)
   {

      auto elapsed = timeStop - *this;

      operator=(timeStop);

      return elapsed;

   }

   inline double period_rate(const class time & timePeriod) const { return period_rate(timePeriod, now()); }

   constexpr double period_rate(const class time & timePeriod, const class time & time) const { return ((time - *this) % timePeriod) / timePeriod; }

   inline double ramp_up(const class time & timePeriod) const { return ramp_up(timePeriod, now()); }

   constexpr double ramp_up(const class time & timePeriod, const class time & time) const;

   //inline class ::time operator - (const class time & time) const { return { e_normalize, m_posixtime.m_iSecond - time.m_posixtime.m_iSecond, m_nanosecond.m_iNanosecond - time.m_nanosecond.m_iNanosecond }; }
   //inline class ::time operator + (const class time & time) const { return { e_normalize, m_posixtime.m_iSecond + time.m_posixtime.m_iSecond, m_nanosecond.m_iNanosecond + time.m_nanosecond.m_iNanosecond }; }
   constexpr  class ::time & operator -= (const class time & time) { m_posixtime.m_iSecond -= time.m_posixtime.m_iSecond; m_nanosecond.m_iNanosecond -= time.m_nanosecond.m_iNanosecond; normalize();  return *this; }
   constexpr  class ::time & operator += (const class time & time) { m_posixtime.m_iSecond += time.m_posixtime.m_iSecond; m_nanosecond.m_iNanosecond += time.m_nanosecond.m_iNanosecond; normalize();  return *this; }


   template < primitive_floating FLOATING >
   constexpr class ::time operator / (FLOATING d) const
   {

      auto nanosecond = (m_posixtime.m_iSecond * 1'000'000'000.0 + m_nanosecond.m_iNanosecond) / d;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

   }


   template < primitive_floating FLOATING >
   constexpr class ::time operator * (FLOATING d) const
   {

      auto nanosecond = (m_posixtime.m_iSecond * 1'000'000'000.0 + m_nanosecond.m_iNanosecond) * d;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

   }


   template < primitive_integral INTEGRAL >
   constexpr class ::time operator / (INTEGRAL i) const
   {

      auto nanosecond = (m_posixtime.m_iSecond * 1'000'000'000 + m_nanosecond.m_iNanosecond) / i;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

   }


   template < primitive_integral INTEGRAL >
   constexpr class ::time operator * (INTEGRAL i) const
   {

      auto nanosecond = (m_posixtime.m_iSecond * 1'000'000'000 + m_nanosecond.m_iNanosecond) * i;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

   }


   template < primitive_floating FLOATING >
   constexpr class ::time & operator /= (FLOATING d)
   {

      return operator=(*this / d);

   }


   template < primitive_floating FLOATING >
   constexpr class ::time & operator *= (FLOATING d)
   {

      return operator= (*this / d);

   }


   template < primitive_integral INTEGRAL >
   constexpr class ::time & operator /= (INTEGRAL i)
   {

      return operator= (*this / i);

   }


   template < primitive_integral INTEGRAL >
   constexpr  class ::time & operator *= (INTEGRAL i)
   {

      return operator= (*this * i);

   }


   constexpr  class ::time half() const;


   constexpr class ::time & operator %= (const class time & time);
   //class ::time operator % (const class time & time) const;


   constexpr posix_time GetTimeSpan() const;

   
   //inline bool timeout(const class time & time);
   
   inline time remaining(const class time & time, const class time & timeNow = e_now);


   constexpr  class ::time wait() const;

   bool on_off(const class time & period) const
   {

      return on_off(period, now());

   }


   constexpr bool on_off(const class time & period, const class time & now) const
   {

      return (elapsed(now) % period) < (period / 2);

   }

   
   // operator integral_day () const { return integral_day(); }
   // operator integral_hour () const { return integral_hour(); }
   // operator integral_minute () const { return integral_minute(); }
   // operator integral_second () const { return integral_second(); }
   // operator integral_millisecond () const { return integral_millisecond(); }
   // operator integral_microsecond () const { return integral_microsecond(); }
   // operator integral_nanosecond () const { return integral_nanosecond(); }

   // operator floating_day () const { return floating_day(); }
   // operator floating_hour () const { return floating_hour(); }
   // operator floating_minute () const { return floating_minute(); }
   // operator floating_second () const { return floating_second(); }
   // operator floating_millisecond () const { return floating_millisecond(); }
   // operator floating_microsecond () const { return floating_microsecond(); }
   // operator floating_nanosecond () const { return floating_nanosecond(); }






   constexpr::i64 integral_day() const { return m_posixtime.m_iSecond / 86'400; }
   constexpr::i64 integral_hour() const { return m_posixtime.m_iSecond / 3'600; }
   constexpr::i64 integral_minute() const { return m_posixtime.m_iSecond / 60; }
   constexpr::i64 integral_second() const { return m_posixtime.m_iSecond; }
   constexpr::i64 integral_millisecond() const { return m_posixtime.m_iSecond * 1'000 + m_nanosecond.m_iNanosecond / 1'000'000; }
   constexpr::i64 integral_microsecond() const { return m_posixtime.m_iSecond * 1'000'000 + m_nanosecond.m_iNanosecond / 1'000; }
   constexpr::i64 integral_nanosecond() const { return m_posixtime.m_iSecond * 1'000'000'000 + m_nanosecond.m_iNanosecond; }


   constexpr double floating_day() const { return floating_second() / 86'400.0; }
   constexpr double floating_hour() const { return floating_second() / 3'600.0; }
   constexpr double floating_minute() const { return floating_second() / 60.0; }
   constexpr double floating_second() const { return (double)m_posixtime.m_iSecond + ((double) m_nanosecond.m_iNanosecond / 1'000'000'000.0); }
   constexpr double floating_millisecond() const { return ((::f64)integral_nanosecond()) / 1'000'000.0; }
   constexpr double floating_microsecond() const { return ((::f64)integral_nanosecond()) / 1'000.0; }
   constexpr double floating_nanosecond() const { return (::f64)integral_nanosecond(); }


   ::i32 millisecond() const { return (::i32) (m_nanosecond.m_iNanosecond / 1'000'000); }


   constexpr  bool operator == (const class time & time) const { return m_posixtime.m_iSecond == time.m_posixtime.m_iSecond && m_nanosecond.m_iNanosecond == time.m_nanosecond.m_iNanosecond; }
   //inline bool operator != (const class time & time) const { return !operator ==(time); }
   constexpr  ::std::strong_ordering operator <=> (const class time & time) const
   { 
      
      auto order = m_posixtime.m_iSecond <=> time.m_posixtime.m_iSecond;

      return order != 0 ? order :  m_nanosecond.m_iNanosecond <=> time.m_nanosecond.m_iNanosecond; 

   }

   //inline bool operator <= (const class time & time) const { return m_posixtime.m_iSecond < time.m_posixtime.m_iSecond || (m_posixtime.m_iSecond == time.m_posixtime.m_iSecond && m_nanosecond.m_iNanosecond <= time.m_nanosecond.m_iNanosecond); }
   //inline bool operator > (const class time & time) const { return !operator <=(time); }
   //inline bool operator >= (const class time & time) const { return !operator <=(time); }
   ::pair < ::count, time > count_and_remainder(const class time & time) const
   {

      auto d = *this / time;

      auto count = (::count)::floor(d);

      auto remainder = *this % time;

      return { count, remainder };

   }

   constexpr time operator %(const class time & time) const;
   constexpr double operator /(const class time & time) const;
   constexpr time operator +(const class time & time) const { return { e_normalize, this->m_posixtime.m_iSecond + time.m_posixtime.m_iSecond, this->m_nanosecond.m_iNanosecond + time.m_nanosecond.m_iNanosecond }; }
   constexpr time operator -(const class time & time) const { return { e_normalize, this->m_posixtime.m_iSecond - time.m_posixtime.m_iSecond, this->m_nanosecond.m_iNanosecond - time.m_nanosecond.m_iNanosecond }; }


   constexpr time operator -() const { return { e_raw, -m_posixtime.m_iSecond, -m_nanosecond.m_iNanosecond}; }





   //_TIME_COMPARISON_WITH(::integral_nanosecond);
   //_TIME_COMPARISON_WITH(::integral_microsecond);
   //_TIME_COMPARISON_WITH(::integral_millisecond);
   //_TIME_COMPARISON_WITH(::integral_second);
   //_TIME_COMPARISON_WITH(::integral_minute);
   //_TIME_COMPARISON_WITH(::integral_hour);
   //_TIME_COMPARISON_WITH(::integral_day);

   ////_TIME_COMPARISON_WITH(::integral_nanosecond);
   ////_TIME_COMPARISON_WITH(::integral_microsecond);
   ////_TIME_COMPARISON_WITH(::integral_millisecond);
   ////_TIME_COMPARISON_WITH(::integral_second);
   ////_TIME_COMPARISON_WITH(::integral_minute);
   ////_TIME_COMPARISON_WITH(::integral_hour);
   ////_TIME_COMPARISON_WITH(::integral_day);


   //_TIME_COMPARISON_WITH(::floating_nanosecond);
   //_TIME_COMPARISON_WITH(::floating_microsecond);
   //_TIME_COMPARISON_WITH(::floating_millisecond);
   //_TIME_COMPARISON_WITH(::floating_second);
   //_TIME_COMPARISON_WITH(::floating_minute);
   //_TIME_COMPARISON_WITH(::floating_hour);
   //_TIME_COMPARISON_WITH(::floating_day);

   ////_TIME_COMPARISON_WITH(::floating_nanosecond);
   ////_TIME_COMPARISON_WITH(::floating_microsecond);
   ////_TIME_COMPARISON_WITH(::floating_millisecond);
   ////_TIME_COMPARISON_WITH(::floating_second);
   ////_TIME_COMPARISON_WITH(::floating_minute);
   ////_TIME_COMPARISON_WITH(::floating_hour);
   ////_TIME_COMPARISON_WITH(::floating_day);


   //inline bool operator == (const ::integral_nanosecond & integralnanosecond) const { return operator == (class ::time(integralnanosecond)); }
   //inline bool operator != (const ::integral_nanosecond & integralnanosecond) const { return operator != (class ::time(integralnanosecond)); }
   //inline bool operator < (const ::integral_nanosecond & integralnanosecond) const { return operator < (class ::time(integralnanosecond)); }
   //inline bool operator <= (const ::integral_nanosecond & integralnanosecond) const { return operator <= (class ::time(integralnanosecond)); }
   //inline bool operator > (const ::integral_nanosecond & integralnanosecond) const { return operator > (class ::time(integralnanosecond)); }
   //inline bool operator >= (const ::integral_nanosecond & integralnanosecond) const { return operator >= (class ::time(integralnanosecond)); }

   //inline bool operator == (const ::integral_microsecond & integralmicrosecond) const { return operator == (class ::time(integralmicrosecond)); }
   //inline bool operator != (const ::integral_microsecond & integralmicrosecond) const { return operator != (class ::time(integralmicrosecond)); }
   //inline bool operator < (const ::integral_microsecond & integralmicrosecond) const { return operator < (class ::time(integralmicrosecond)); }
   //inline bool operator <= (const ::integral_microsecond & integralmicrosecond) const { return operator <= (class ::time(integralmicrosecond)); }
   //inline bool operator > (const ::integral_microsecond & integralmicrosecond) const { return operator > (class ::time(integralmicrosecond)); }
   //inline bool operator >= (const ::integral_microsecond & integralmicrosecond) const { return operator >= (class ::time(integralmicrosecond)); }

   //inline bool operator == (const ::integral_millisecond & integralmillisecond) const { return operator == (class ::time(integralmillisecond)); }
   //inline bool operator != (const ::integral_millisecond & integralmillisecond) const { return operator != (class ::time(integralmillisecond)); }
   //inline bool operator < (const ::integral_millisecond & integralmillisecond) const { return operator < (class ::time(integralmillisecond)); }
   //inline bool operator <= (const ::integral_millisecond & integralmillisecond) const { return operator <= (class ::time(integralmillisecond)); }
   //inline bool operator > (const ::integral_millisecond & integralmillisecond) const { return operator > (class ::time(integralmillisecond)); }
   //inline bool operator >= (const ::integral_millisecond & integralmillisecond) const { return operator >= (class ::time(integralmillisecond)); }

   //inline bool operator == (const ::integral_second & integralsecond) const { return operator == (class ::time(integralsecond)); }
   //inline bool operator != (const ::integral_second & integralsecond) const { return operator != (class ::time(integralsecond)); }
   //inline bool operator < (const ::integral_second & integralsecond) const { return operator < (class ::time(integralsecond)); }
   //inline bool operator <= (const ::integral_second & integralsecond) const { return operator <= (class ::time(integralsecond)); }
   //inline bool operator > (const ::integral_second & integralsecond) const { return operator > (class ::time(integralsecond)); }
   //inline bool operator >= (const ::integral_second & integralsecond) const { return operator >= (class ::time(integralsecond)); }

   //inline bool operator == (const ::integral_minute & minute) const { return operator == (class ::time(minute)); }
   //inline bool operator != (const ::integral_minute & minute) const { return operator != (class ::time(minute)); }
   //inline bool operator < (const ::integral_minute & minute) const { return operator < (class ::time(minute)); }
   //inline bool operator <= (const ::integral_minute & minute) const { return operator <= (class ::time(minute)); }
   //inline bool operator > (const ::integral_minute & minute) const { return operator > (class ::time(minute)); }
   //inline bool operator >= (const ::integral_minute & minute) const { return operator >= (class ::time(minute)); }

   //inline bool operator == (const ::integral_hour & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::integral_hour & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::integral_hour & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::integral_hour & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::integral_hour & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::integral_hour & day) const { return operator >= (class ::time(day)); }

   //inline bool operator == (const ::integral_day & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::integral_day & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::integral_day & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::integral_day & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::integral_day & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::integral_day & day) const { return operator >= (class ::time(day)); }








   //inline bool operator == (const ::floating_nanosecond & floatingnanosecond) const { return operator == (class ::time(floatingnanosecond)); }
   //inline bool operator != (const ::floating_nanosecond & floatingnanosecond) const { return operator != (class ::time(floatingnanosecond)); }
   //inline bool operator < (const ::floating_nanosecond & floatingnanosecond) const { return operator < (class ::time(floatingnanosecond)); }
   //inline bool operator <= (const ::floating_nanosecond & floatingnanosecond) const { return operator <= (class ::time(floatingnanosecond)); }
   //inline bool operator > (const ::floating_nanosecond & floatingnanosecond) const { return operator > (class ::time(floatingnanosecond)); }
   //inline bool operator >= (const ::floating_nanosecond & floatingnanosecond) const { return operator >= (class ::time(floatingnanosecond)); }

   //inline bool operator == (const ::floating_microsecond & floatingmicrosecond) const { return operator == (class ::time(floatingmicrosecond)); }
   //inline bool operator != (const ::floating_microsecond & floatingmicrosecond) const { return operator != (class ::time(floatingmicrosecond)); }
   //inline bool operator < (const ::floating_microsecond & floatingmicrosecond) const { return operator < (class ::time(floatingmicrosecond)); }
   //inline bool operator <= (const ::floating_microsecond & floatingmicrosecond) const { return operator <= (class ::time(floatingmicrosecond)); }
   //inline bool operator > (const ::floating_microsecond & floatingmicrosecond) const { return operator > (class ::time(floatingmicrosecond)); }
   //inline bool operator >= (const ::floating_microsecond & floatingmicrosecond) const { return operator >= (class ::time(floatingmicrosecond)); }

   //inline bool operator == (const ::floating_millisecond & floatingmillisecond) const { return operator == (class ::time(floatingmillisecond)); }
   //inline bool operator != (const ::floating_millisecond & floatingmillisecond) const { return operator != (class ::time(floatingmillisecond)); }
   //inline bool operator < (const ::floating_millisecond & floatingmillisecond) const { return operator < (class ::time(floatingmillisecond)); }
   //inline bool operator <= (const ::floating_millisecond & floatingmillisecond) const { return operator <= (class ::time(floatingmillisecond)); }
   //inline bool operator > (const ::floating_millisecond & floatingmillisecond) const { return operator > (class ::time(floatingmillisecond)); }
   //inline bool operator >= (const ::floating_millisecond & floatingmillisecond) const { return operator >= (class ::time(floatingmillisecond)); }

   //inline bool operator == (const ::floating_second & floatingsecond) const { return operator == (class ::time(floatingsecond)); }
   //inline bool operator != (const ::floating_second & floatingsecond) const { return operator != (class ::time(floatingsecond)); }
   //inline bool operator < (const ::floating_second & floatingsecond) const { return operator < (class ::time(floatingsecond)); }
   //inline bool operator <= (const ::floating_second & floatingsecond) const { return operator <= (class ::time(floatingsecond)); }
   //inline bool operator > (const ::floating_second & floatingsecond) const { return operator > (class ::time(floatingsecond)); }
   //inline bool operator >= (const ::floating_second & floatingsecond) const { return operator >= (class ::time(floatingsecond)); }

   //inline bool operator == (const ::floating_minute & minute) const { return operator == (class ::time(minute)); }
   //inline bool operator != (const ::floating_minute & minute) const { return operator != (class ::time(minute)); }
   //inline bool operator < (const ::floating_minute & minute) const { return operator < (class ::time(minute)); }
   //inline bool operator <= (const ::floating_minute & minute) const { return operator <= (class ::time(minute)); }
   //inline bool operator > (const ::floating_minute & minute) const { return operator > (class ::time(minute)); }
   //inline bool operator >= (const ::floating_minute & minute) const { return operator >= (class ::time(minute)); }

   //inline bool operator == (const ::floating_hour & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::floating_hour & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::floating_hour & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::floating_hour & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::floating_hour & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::floating_hour & day) const { return operator >= (class ::time(day)); }

   //inline bool operator == (const ::floating_day & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::floating_day & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::floating_day & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::floating_day & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::floating_day & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::floating_day & day) const { return operator >= (class ::time(day)); }


   //inline bool operator == (const class time & time) const { return operator == (class ::time(floating_second(time.m_d))); }
   //inline bool operator != (const class time & time) const { return operator != (class ::time(floating_second(time.m_d))); }
   //inline bool operator < (const class time & time) const { return operator < (class ::time(floating_second(time.m_d))); }
   //inline bool operator <= (const class time & time) const { return operator <= (class ::time(floating_second(time.m_d))); }
   //inline bool operator > (const class time & time) const { return operator > (class ::time(floating_second(time.m_d))); }
   //inline bool operator >= (const class time & time) const { return operator >= (class ::time(floating_second(time.m_d))); }






   //time operator %(const ::integral_nanosecond & time) const { return operator % ((class ::time)time);}
   //double operator /(const ::integral_nanosecond & time) const { return operator / ((class ::time)time);}
   //time operator +(const ::integral_nanosecond & time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_nanosecond & time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_microsecond & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_microsecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_microsecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_microsecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_millisecond & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_millisecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_millisecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_millisecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_second & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_second& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_second& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_second& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_minute & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_minute& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_minute& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_minute& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_hour & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_hour& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_hour& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_hour& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_day & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_day& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_day& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_day& time) const { return operator - ((class ::time)time); }









   //time operator %(const ::floating_nanosecond & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_nanosecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_nanosecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_nanosecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_microsecond & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_microsecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_microsecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_microsecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_millisecond & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_millisecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_millisecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_millisecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_second & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_second& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_second& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_second& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_minute & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_minute& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_minute& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_minute& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_hour & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_hour& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_hour& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_hour& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_day & time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_day& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_day& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_day& time) const { return operator - ((class ::time)time); }








   //time operator %(const class time & time) const { return *this % class ::time(time);}
   //double operator /(const class time & time) const { return *this / class ::time(time);}
   //time operator +(const class time & time) const { return *this + class ::time(time); }
   //time operator -(const class time & time) const { return *this - class ::time(time); }







   //inline bool operator == (const ::integral_nanosecond& integralnanosecond) const { return operator == (class ::time(integralnanosecond)); }
   //inline bool operator != (const ::integral_nanosecond& integralnanosecond) const { return operator != (class ::time(integralnanosecond)); }
   //inline bool operator < (const ::integral_nanosecond& integralnanosecond) const { return operator < (class ::time(integralnanosecond)); }
   //inline bool operator <= (const ::integral_nanosecond& integralnanosecond) const { return operator <= (class ::time(integralnanosecond)); }
   //inline bool operator > (const ::integral_nanosecond& integralnanosecond) const { return operator > (class ::time(integralnanosecond)); }
   //inline bool operator >= (const ::integral_nanosecond& integralnanosecond) const { return operator >= (class ::time(integralnanosecond)); }

   //inline bool operator == (const ::integral_microsecond& integralmicrosecond) const { return operator == (class ::time(integralmicrosecond)); }
   //inline bool operator != (const ::integral_microsecond& integralmicrosecond) const { return operator != (class ::time(integralmicrosecond)); }
   //inline bool operator < (const ::integral_microsecond& integralmicrosecond) const { return operator < (class ::time(integralmicrosecond)); }
   //inline bool operator <= (const ::integral_microsecond& integralmicrosecond) const { return operator <= (class ::time(integralmicrosecond)); }
   //inline bool operator > (const ::integral_microsecond& integralmicrosecond) const { return operator > (class ::time(integralmicrosecond)); }
   //inline bool operator >= (const ::integral_microsecond& integralmicrosecond) const { return operator >= (class ::time(integralmicrosecond)); }

   //inline bool operator == (const ::integral_millisecond& integralmillisecond) const { return operator == (class ::time(integralmillisecond)); }
   //inline bool operator != (const ::integral_millisecond& integralmillisecond) const { return operator != (class ::time(integralmillisecond)); }
   //inline bool operator < (const ::integral_millisecond& integralmillisecond) const { return operator < (class ::time(integralmillisecond)); }
   //inline bool operator <= (const ::integral_millisecond& integralmillisecond) const { return operator <= (class ::time(integralmillisecond)); }
   //inline bool operator > (const ::integral_millisecond& integralmillisecond) const { return operator > (class ::time(integralmillisecond)); }
   //inline bool operator >= (const ::integral_millisecond& integralmillisecond) const { return operator >= (class ::time(integralmillisecond)); }

   //inline bool operator == (const ::integral_second& integralsecond) const { return operator == (class ::time(integralsecond)); }
   //inline bool operator != (const ::integral_second& integralsecond) const { return operator != (class ::time(integralsecond)); }
   //inline bool operator < (const ::integral_second& integralsecond) const { return operator < (class ::time(integralsecond)); }
   //inline bool operator <= (const ::integral_second& integralsecond) const { return operator <= (class ::time(integralsecond)); }
   //inline bool operator > (const ::integral_second& integralsecond) const { return operator > (class ::time(integralsecond)); }
   //inline bool operator >= (const ::integral_second& integralsecond) const { return operator >= (class ::time(integralsecond)); }

   //inline bool operator == (const ::integral_minute& minute) const { return operator == (class ::time(minute)); }
   //inline bool operator != (const ::integral_minute& minute) const { return operator != (class ::time(minute)); }
   //inline bool operator < (const ::integral_minute& minute) const { return operator < (class ::time(minute)); }
   //inline bool operator <= (const ::integral_minute& minute) const { return operator <= (class ::time(minute)); }
   //inline bool operator > (const ::integral_minute& minute) const { return operator > (class ::time(minute)); }
   //inline bool operator >= (const ::integral_minute& minute) const { return operator >= (class ::time(minute)); }

   //inline bool operator == (const ::integral_hour& day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::integral_hour& day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::integral_hour& day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::integral_hour& day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::integral_hour& day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::integral_hour& day) const { return operator >= (class ::time(day)); }

   //inline bool operator == (const ::integral_day& day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::integral_day& day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::integral_day& day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::integral_day& day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::integral_day& day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::integral_day& day) const { return operator >= (class ::time(day)); }








   //inline bool operator == (const ::floating_nanosecond& floatingnanosecond) const { return operator == (class ::time(floatingnanosecond)); }
   //inline bool operator != (const ::floating_nanosecond& floatingnanosecond) const { return operator != (class ::time(floatingnanosecond)); }
   //inline bool operator < (const ::floating_nanosecond& floatingnanosecond) const { return operator < (class ::time(floatingnanosecond)); }
   //inline bool operator <= (const ::floating_nanosecond& floatingnanosecond) const { return operator <= (class ::time(floatingnanosecond)); }
   //inline bool operator > (const ::floating_nanosecond& floatingnanosecond) const { return operator > (class ::time(floatingnanosecond)); }
   //inline bool operator >= (const ::floating_nanosecond& floatingnanosecond) const { return operator >= (class ::time(floatingnanosecond)); }

   //inline bool operator == (const ::floating_microsecond& floatingmicrosecond) const { return operator == (class ::time(floatingmicrosecond)); }
   //inline bool operator != (const ::floating_microsecond& floatingmicrosecond) const { return operator != (class ::time(floatingmicrosecond)); }
   //inline bool operator < (const ::floating_microsecond& floatingmicrosecond) const { return operator < (class ::time(floatingmicrosecond)); }
   //inline bool operator <= (const ::floating_microsecond& floatingmicrosecond) const { return operator <= (class ::time(floatingmicrosecond)); }
   //inline bool operator > (const ::floating_microsecond& floatingmicrosecond) const { return operator > (class ::time(floatingmicrosecond)); }
   //inline bool operator >= (const ::floating_microsecond& floatingmicrosecond) const { return operator >= (class ::time(floatingmicrosecond)); }

   //inline bool operator == (const ::floating_millisecond& floatingmillisecond) const { return operator == (class ::time(floatingmillisecond)); }
   //inline bool operator != (const ::floating_millisecond& floatingmillisecond) const { return operator != (class ::time(floatingmillisecond)); }
   //inline bool operator < (const ::floating_millisecond& floatingmillisecond) const { return operator < (class ::time(floatingmillisecond)); }
   //inline bool operator <= (const ::floating_millisecond& floatingmillisecond) const { return operator <= (class ::time(floatingmillisecond)); }
   //inline bool operator > (const ::floating_millisecond& floatingmillisecond) const { return operator > (class ::time(floatingmillisecond)); }
   //inline bool operator >= (const ::floating_millisecond& floatingmillisecond) const { return operator >= (class ::time(floatingmillisecond)); }

   //inline bool operator == (const ::floating_second& floatingsecond) const { return operator == (class ::time(floatingsecond)); }
   //inline bool operator != (const ::floating_second& floatingsecond) const { return operator != (class ::time(floatingsecond)); }
   //inline bool operator < (const ::floating_second& floatingsecond) const { return operator < (class ::time(floatingsecond)); }
   //inline bool operator <= (const ::floating_second& floatingsecond) const { return operator <= (class ::time(floatingsecond)); }
   //inline bool operator > (const ::floating_second& floatingsecond) const { return operator > (class ::time(floatingsecond)); }
   //inline bool operator >= (const ::floating_second& floatingsecond) const { return operator >= (class ::time(floatingsecond)); }

   //inline bool operator == (const ::floating_minute& minute) const { return operator == (class ::time(minute)); }
   //inline bool operator != (const ::floating_minute& minute) const { return operator != (class ::time(minute)); }
   //inline bool operator < (const ::floating_minute& minute) const { return operator < (class ::time(minute)); }
   //inline bool operator <= (const ::floating_minute& minute) const { return operator <= (class ::time(minute)); }
   //inline bool operator > (const ::floating_minute& minute) const { return operator > (class ::time(minute)); }
   //inline bool operator >= (const ::floating_minute& minute) const { return operator >= (class ::time(minute)); }

   //inline bool operator == (const ::floating_hour& day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::floating_hour& day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::floating_hour& day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::floating_hour& day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::floating_hour& day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::floating_hour& day) const { return operator >= (class ::time(day)); }

   //inline bool operator == (const ::floating_day& day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::floating_day& day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::floating_day& day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::floating_day& day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::floating_day& day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::floating_day& day) const { return operator >= (class ::time(day)); }








   //time operator %(const ::integral_nanosecond& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_nanosecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_nanosecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_nanosecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_microsecond& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_microsecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_microsecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_microsecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_millisecond& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_millisecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_millisecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_millisecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_second& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_second& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_second& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_second& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_minute& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_minute& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_minute& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_minute& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_hour& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_hour& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_hour& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_hour& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::integral_day& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::integral_day& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::integral_day& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::integral_day& time) const { return operator - ((class ::time)time); }









   //time operator %(const ::floating_nanosecond& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_nanosecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_nanosecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_nanosecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_microsecond& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_microsecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_microsecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_microsecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_millisecond& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_millisecond& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_millisecond& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_millisecond& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_second& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_second& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_second& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_second& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_minute& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_minute& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_minute& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_minute& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_hour& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_hour& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_hour& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_hour& time) const { return operator - ((class ::time)time); }


   //time operator %(const ::floating_day& time) const { return operator % ((class ::time)time); }
   //double operator /(const ::floating_day& time) const { return operator / ((class ::time)time); }
   //time operator +(const ::floating_day& time) const { return operator + ((class ::time)time); }
   //time operator -(const ::floating_day& time) const { return operator - ((class ::time)time); }




};


//inline doubled floatingtime() { return ::get_floating_second(); }

//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
//constexpr  time::time(enum_raw, INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds)
//{
//
//   m_posixtime.m_iSecond = iSeconds;
//
//   m_nanosecond.m_iNanosecond = iNanoseconds;
//
//}
//
//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
//constexpr  time::time(enum_normalize, INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds)
//{
//
//   m_posixtime.m_iSecond = iSeconds + iNanoseconds / 1'000'000'000;
//
//   m_nanosecond.m_iNanosecond = iNanoseconds % 1'000'000'000;
//
//   while(m_nanosecond.m_iNanosecond < 0)
//   {
//
//      m_posixtime.m_iSecond--;
//
//      m_nanosecond.m_iNanosecond += 1'000'000'000;
//
//   }
//
//}


//inline timeclass ::time(const class ::time& time) :
//   DURATION(time)
//{
//
//}


constexpr  void time::raw_set(posix_time posixtime, nanosecond nanosecond)
{

   m_posixtime = posixtime;

   m_nanosecond = nanosecond;

}


constexpr  void time::set(posix_time posixtime, nanosecond nanosecond)
{

   raw_set(posixtime, nanosecond);

   normalize();

}


constexpr void time::set_null()
{

   raw_set({ posix_time_t{}, 0 }, { nanosecond_t{}, 0 });

}


constexpr class ::time time::raw_create(posix_time posixtime, nanosecond nanosecond)
{

   time time;

   time.raw_set(posixtime, nanosecond);

   return time;

}



constexpr  class ::time time::create(posix_time posixtime, nanosecond nanosecond)
{

   time time;

   time.set(posixtime, nanosecond);

   return time;

}


constexpr  class ::time time::create_null()
{

   time time;

   time.set_null();

   return time;

}


//inline bool time::is_pos_infinity() const
//{
//
//   return m_posixtime.m_iSecond == ::numeric_info < decltype(m_posixtime.m_iSecond) > ::maximum();
//
//}
//

constexpr bool time::is_infinite() const
{

   return m_posixtime.m_iSecond == ::numeric_info < decltype(m_posixtime.m_iSecond) > ::maximum();

}


//constexpr bool time::is_zero() const
//{
//
//   return m_posixtime.m_iSecond < 0 || (m_posixtime.m_iSecond == 0 && m_nanosecond.m_iNanosecond <= 0);
//
//}


constexpr  class ::time time::infinity()
{

   return {(::i64)I64_MAXIMUM,(::i64)0};

}


//inline class ::time time::pos_infinity()
//{
//
//   return {(::i64)I64_MAXIMUM, (::i64)0};
//
//}


//constexpr  class ::time time::zero()
//{
//
//   return {(::i64)0,(::i64) 0};
//
//}


constexpr posix_time time::GetTimeSpan() const
{

   return m_posixtime;

}


//constexpr  time::operator bool() const
//{
//
//   return m_posixtime.m_iSecond != 0 || m_nanosecond.m_iNanosecond != 0;
//
//}


CLASS_DECL_ACME class ::time random(const class ::time & d1, const class ::time & d2);



//inline class ::time time::wait() const
//{
//
//   return is_infinite() ? ::time::infinite() : ::wait(m_posixtime.m_iSecond, m_nanosecond.m_iNanosecond);
//
//}


template < primitive_floating FLOATING >
class time operator * (FLOATING d, const class time & time)
{

   auto nanosecond = d * (time.m_posixtime.m_iSecond * 1'000'000'000.0 + time.m_nanosecond.m_iNanosecond);

   return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

}


template < primitive_integral INTEGRAL >
class time operator * (INTEGRAL i, const class time & time)
{

   auto nanosecond = i * (time.m_posixtime.m_iSecond * 1'000'000'000 + time.m_nanosecond.m_iNanosecond);

   return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

}


//template < typename DURATION >
//inline ::wait integral_time < DURATION >::wait() const
//{
//
//   class time time(*this);
//
//   return time.integral_nanosecond().m_i;
//
//}


constexpr bool time::timeout(const class time & time, const class time & timeNow)
{

   if (elapsed(timeNow) < time)
   {

      return false;

   }

   operator =(timeNow);

   return true;

}


inline class time time::remaining(const class time & time, const class time & timeNow)
{

   auto timeRemaining = time - elapsed(timeNow);

   return timeRemaining;

}





//constexpr struct ::timespec & copy(struct ::timespec & timespec, const class ::time & time)
//{
//
//   timespec.tv_sec = (decltype(timespec.tv_sec))time.m_posixtime.m_iSecond;
//   timespec.tv_nsec = (decltype(timespec.tv_nsec))time.m_nanosecond.m_iNanosecond;
//
//   return timespec;
//
//}
//
//
//constexpr struct ::timespec & add(struct ::timespec & timespec1, const struct ::timespec & timespec2)
//{
//
//   add_second_nanosecond(timespec1.tv_sec, timespec1.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);
//
//   return timespec1;
//
//}
//
//
//constexpr struct ::timespec addition(const struct ::timespec & timespec1, const struct ::timespec & timespec2)
//{
//
//   timespec timespec = timespec1;
//
//   add_second_nanosecond(timespec.tv_sec, timespec.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);
//
//   return timespec;
//
//}
//
//
//constexpr struct ::timespec & subtract(struct ::timespec & timespec1, const struct ::timespec & timespec2)
//{
//
//   subtract_second_nanosecond(timespec1.tv_sec, timespec1.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);
//
//   return timespec1;
//
//}
//
//
//constexpr struct ::timespec subtraction(const struct ::timespec & timespec1, const struct ::timespec & timespec2)
//{
//
//   timespec timespec = timespec1;
//
//   return subtract(timespec, timespec2);
//
//}
//
//
//constexpr bool operator >(const struct ::timespec & timespec1, const struct ::timespec & timespec2)
//{
//
//   return timespec1.tv_sec > timespec2.tv_sec || (timespec1.tv_sec == timespec2.tv_sec && timespec1.tv_nsec > timespec2.tv_nsec);
//
//}
//


//DEFINE_COMPARISON_WITH_TIME(inline, integral_nanosecond)
//DEFINE_COMPARISON_WITH_TIME(inline, integral_microsecond)
//DEFINE_COMPARISON_WITH_TIME(inline, integral_millisecond)
//DEFINE_COMPARISON_WITH_TIME(inline, integral_second)
//DEFINE_COMPARISON_WITH_TIME(inline, integral_minute)
//DEFINE_COMPARISON_WITH_TIME(inline, integral_hour)
//DEFINE_COMPARISON_WITH_TIME(inline, integral_day)
//
//
//DEFINE_COMPARISON_WITH_TIME(inline, floating_nanosecond)
//DEFINE_COMPARISON_WITH_TIME(inline, floating_microsecond)
//DEFINE_COMPARISON_WITH_TIME(inline, floating_millisecond)
//DEFINE_COMPARISON_WITH_TIME(inline, floating_second)
//DEFINE_COMPARISON_WITH_TIME(inline, floating_minute)
//DEFINE_COMPARISON_WITH_TIME(inline, floating_hour)
//DEFINE_COMPARISON_WITH_TIME(inline, floating_day)





template < primitive_integral INTEGRAL >
constexpr class time nanosecond_time(INTEGRAL i) { return { (INTEGRAL)i / 1'000'000'000, (long)(i % 1'000'000'000) }; }
template < primitive_floating FLOATING >
constexpr class time nanosecond_time(FLOATING f) { return { (FLOATING)(f / 1'000'000'000.0), (long)(fmod(f, 1'000'000'000.0)) }; }
template < primitive_integral INTEGRAL >
constexpr class time microsecond_time(INTEGRAL i) { return { i / 1'000'000, (long)((i % 1'000'000) * 1'000) }; }
template < primitive_floating FLOATING >
constexpr class time microsecond_time(FLOATING f) { return { (FLOATING)(f / 1'000'000.0), (long)(fmod(f, 1'000'000.0) * 1'000.0) }; }
template < primitive_integral INTEGRAL >
constexpr class time millisecond_time(INTEGRAL i) { return { i / 1'000, (long)((i % 1'000) * 1'000'000) }; }
template < primitive_floating FLOATING >
constexpr class time millisecond_time(FLOATING f) { return { (FLOATING)(f / 1'000.0), (long)(fmod(f, 1'000.0) * 1'000'000.0) }; }
template < primitive_integral INTEGRAL >
constexpr class time second_time(INTEGRAL i) { return { i }; }
template < primitive_integral NUMERATOR, primitive_integral DENOMINATOR >
constexpr class time second_time(NUMERATOR numerator, DENOMINATOR denominator)
{
   return  
   { 
      (::i64) (numerator / denominator),
      (::i64) ((numerator % denominator) * 1'000'000'000 / denominator)
   }; 
}
template < primitive_floating FLOATING >
constexpr class time second_time(FLOATING f) { return { (FLOATING)(f), (long)(fmod(f, 1.0) * 1'000'000'000.0) }; }
template < primitive_integral INTEGRAL >
constexpr class time minute_time(INTEGRAL i) { return { i * 60 }; }
template < primitive_floating FLOATING >
constexpr class time minute_time(FLOATING f) { return { (FLOATING)(f * 60.0), (long)(fmod(f * 60.0, 1.0) * 1'000'000'000.0) }; }
template < primitive_integral INTEGRAL >
constexpr class time hour_time(INTEGRAL i) { return { i * 3'600 }; }
template < primitive_floating FLOATING >
constexpr class time hour_time(FLOATING f) { return { (FLOATING)(f * 3'600.0), (long)(fmod(f * 3'600.0, 1.0) * 1'000'000'000.0) }; }
template < primitive_integral INTEGRAL >
constexpr class time day_time(INTEGRAL i) { return { i * 86'400 }; }
template < primitive_floating FLOATING >
constexpr class time day_time(FLOATING f) { return { (FLOATING)(f * 86'400.0), (long)(fmod(f * 86'400.0, 1.0) * 1'000'000'000.0) }; }




constexpr void time::normalize()
{

   m_posixtime.m_iSecond += m_nanosecond.m_iNanosecond / SECOND_NANOS;

   m_nanosecond.m_iNanosecond %= SECOND_NANOS;

   int iSecondSign = ::numeric::sign(m_posixtime.m_iSecond);

   int iNanosecondSign = ::numeric::sign(m_nanosecond.m_iNanosecond);

   if (iSecondSign == -iNanosecondSign && iSecondSign != 0)
   {

      m_posixtime.m_iSecond -= iSecondSign;

      m_nanosecond.m_iNanosecond += iSecondSign * SECOND_NANOS;

   }

}











constexpr class ::time time::half() const
{

   auto nanosecond = (m_posixtime.m_iSecond * 1'000'000'000 + m_nanosecond.m_iNanosecond);

   auto iSecond = (::i64)(nanosecond / 1'000'000'000);

   auto iNanosecond = (long)(nanosecond % 1'000'000'000);

   return { e_raw, iSecond, iNanosecond };

}



constexpr class ::time & time::operator %= (const class time & time)
{

   auto nanosecondThis = m_posixtime.m_iSecond * 1'000'000'000 + m_nanosecond.m_iNanosecond;

   auto nanosecond = time.m_posixtime.m_iSecond * 1'000'000'000 + time.m_nanosecond.m_iNanosecond;

   nanosecondThis %= nanosecond;

   m_posixtime.m_iSecond = nanosecondThis / 1'000'000'000;

   m_nanosecond.m_iNanosecond = nanosecondThis % 1'000'000'000;

   return *this;

}


constexpr class ::time time::operator % (const class time & time) const
{

   class ::time timeResult(*this);

   timeResult %= time;

   return timeResult;

}


constexpr double time::operator / (const class time & time) const
{

   auto nanosecondThis = m_posixtime.m_iSecond * 1'000'000'000 + m_nanosecond.m_iNanosecond;

   auto nanosecond = time.m_posixtime.m_iSecond * 1'000'000'000 + time.m_nanosecond.m_iNanosecond;

   return (double)nanosecondThis / (double)nanosecond;

}




constexpr void time::set(i64 i, enum_unit eunit)
{

   switch (eunit)
   {
   case unit_nanos:
      raw_set({ posix_time_t{}, i / (1000 * 1000 * 1000) }, { nanosecond_t{}, i % (1000 * 1000 * 1000) });
      break;
   case unit_micros:
      raw_set({ posix_time_t{},i / (1000 * 1000) }, { nanosecond_t{},(i / 1000) % (1000 * 1000 * 1000) });
      break;
   case unit_millis:
      raw_set({ posix_time_t{}, i / 1000 }, { nanosecond_t{},(i / (1000 * 1000)) % (1000 * 1000 * 1000) });
      break;
   case unit_seconds:
      raw_set({ posix_time_t{}, i }, { nanosecond_t{},0});
      break;
   case unit_minutes:
      raw_set({ posix_time_t{},i * 60 },{ nanosecond_t{},0});
      break;
   case unit_hours:
      raw_set({ posix_time_t{},i * 60 * 60 }, { nanosecond_t{}, 0 });
      break;
   default:
      throw_exception(error_bad_argument);

   };

}
