// Refactoring by camilo on 2021-10-05 12:46 BRT <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME duration :
   public DURATION
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


   static duration s_durationFirst;

   duration(enum_zero ezero = e_zero) :
      DURATION{}
   {

   }


   duration(enum_now)
   {

      Now();

   }


   duration(enum_infinite)
   {

      Infinite();

   }


   duration(const ::INTEGRAL_NANOSECOND & integral) : duration(e_raw, (::i64)integral.m_i / 1'000'000'000, (long ) (integral.m_i % 1'000'000'000)) {}
   duration(const ::FLOATING_NANOSECOND & floating) : duration(e_raw, (::i64)(floating.m_d / 1'000'000'000.0), (long)(fmod(floating.m_d, 1'000'000'000.0))) {}
   duration(const ::INTEGRAL_MICROSECOND & integral) : duration(e_raw, integral.m_i / 1'000'000, (long) ((integral.m_i % 1'000'000) * 1'000)) {}
   duration(const ::FLOATING_MICROSECOND & floating) : duration(e_raw, (::i64)(floating.m_d / 1'000'000.0), (long)(fmod(floating.m_d, 1'000'000.0) * 1'000.0)) {}
   duration(const ::INTEGRAL_MILLISECOND & integral) : duration(e_raw, integral.m_i / 1'000, (long) ((integral.m_i % 1'000) * 1'000'000)) {}
   duration(const ::FLOATING_MILLISECOND & floating) : duration(e_raw, (::i64)(floating.m_d / 1'000.0), (long)(fmod(floating.m_d, 1'000.0) * 1'000'000.0)) {}
   duration(const ::INTEGRAL_SECOND & integral) : duration(e_raw, integral.m_i) {}
   duration(const ::FLOATING_SECOND & floating) : duration(e_raw, (::i64)(floating.m_d), (long)(fmod(floating.m_d, 1.0) * 1'000'000'000.0)) {}
   duration(const ::INTEGRAL_MINUTE & integral) : duration(e_raw, integral.m_i * 60) {}
   duration(const ::FLOATING_MINUTE & floating) : duration(e_raw, (::i64)(floating.m_d * 60.0), (long)(fmod(floating.m_d * 60.0, 1.0) * 1'000'000'000.0)) {}
   duration(const ::INTEGRAL_HOUR & integral) : duration(e_raw, integral.m_i * 3'600) {}
   duration(const ::FLOATING_HOUR & floating) : duration(e_raw, (::i64)(floating.m_d * 3'600.0), (long)(fmod(floating.m_d * 3'600.0, 1.0) * 1'000'000'000.0)) {}
   duration(const ::INTEGRAL_DAY & integral) : duration::duration(e_raw, integral.m_i * 86'400) {}
   duration(const ::FLOATING_DAY & floating) : duration(e_raw, (::i64)(floating.m_d * 86'400.0), (long)(fmod(floating.m_d * 86'400.0, 1.0) * 1'000'000'000.0)) {}

   duration(const class ::time& time) : duration(e_raw, (::i64)(time.m_d), (long)(fmod(time.m_d, 1.0) * 1'000'000'000.0)) {}

   template < primitive_integer INTEGER1, primitive_integral INTEGRAL2 >
   duration(INTEGER1 iSecond, INTEGRAL2 iNanosecond) :
      DURATION{ .m_iSecond = (time_t)iSecond, .m_iNanosecond = (long)iNanosecond }
   { }


   template < primitive_floating FLOATING, primitive_number NUMBER >
   duration(FLOATING fSeconds, NUMBER nanoseconds)
   {
        
       fset(fSeconds, nanoseconds);
        
   }

   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   duration(enum_raw, INTEGRAL1 iSecond, INTEGRAL2 iNanosecond);

   template < primitive_integral INTEGRAL1 >
   duration(enum_raw, INTEGRAL1 iSecond) : duration(e_raw, iSecond, 0) {}
   
   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   duration(enum_normalize, INTEGRAL1 iSecond, INTEGRAL2 iNanosecond);

   duration(const ::DURATION & duration):DURATION(duration) {}


   inline void raw_set(time_t iSeconds, long iNanoseconds = 0);
   inline void set(time_t iSeconds, long iNanoseconds);
   inline void set_null();
   static inline duration raw_create(time_t iSeconds, long iNanoseconds);
   static inline duration create(time_t iSeconds, long iNanoseconds);
   static inline duration create_null();


   void fset(long double dSeconds);
   void fset(long double dSeconds, double dNanoseconds);
   static inline duration fcreate(long double dSeconds, double dNanoseconds);


   void set(i64 i, enum_unit eunit);
   void set(long double d, enum_unit eunit);


   inline bool is_pos_infinity() const;
   inline bool is_infinite() const;
   inline bool is_null() const;
   inline bool is_set() const { return (m_iSecond >= 0 && m_iNanosecond > 0) || (m_iSecond > 0 && m_iNanosecond >= 0); }
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   inline bool operator !() const {return is_null();}

   void Infinite() {*this=infinite();}
   void PosInfinity() {*this=pos_infinity();}
   void Zero() {*this=zero();}
   void Null() { Zero(); }

   class ::duration & operator = (const class ::duration & duration);

   inline bool durationout(const class ::duration & duration);
   void normalize();

   inline operator bool() const;


   inline double operator() ()const { return floating_second().m_d; }


   operator const timespec * () const { return (const timespec *)this; }
   operator timespec * () { return (timespec *) this; }
   
   //static inline class ::duration first();
   static inline class ::duration now() { return e_now; }

   inline bool is_past() const { return now() > *this; }

   inline class ::duration & Now() { if (timespec_get((timespec *)this, TIME_UTC) != TIME_UTC) throw "timespec_get failed!!"; return *this; }

   inline class ::duration elapsed(const class ::duration & duration = now()) const { return duration - *this; }

   inline ::duration update_elapsed(const ::duration & durationStop = ::now < ::duration >())
   {

      auto elapsed = durationStop - *this;

      operator=(durationStop);

      return elapsed;

   }

   inline double period_rate(const class ::duration & durationPeriod, const class ::duration & duration = now()) const { return ((duration - *this) % durationPeriod) / durationPeriod; }

   
   //inline class ::duration operator - (const class ::duration & duration) const { return { e_normalize, m_iSecond - duration.m_iSecond, m_iNanosecond - duration.m_iNanosecond }; }
   //inline class ::duration operator + (const class ::duration & duration) const { return { e_normalize, m_iSecond + duration.m_iSecond, m_iNanosecond + duration.m_iNanosecond }; }
   inline class ::duration & operator -= (const class ::duration & duration) { m_iSecond -= duration.m_iSecond; m_iNanosecond -= duration.m_iNanosecond; normalize();  return *this; }
   inline class ::duration & operator += (const class ::duration & duration) { m_iSecond += duration.m_iSecond; m_iNanosecond += duration.m_iNanosecond; normalize();  return *this; }


   template < primitive_floating FLOATING >
   class ::duration operator / (FLOATING d) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000.0 + m_iNanosecond) / d;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

   }


   template < primitive_floating FLOATING >
   class ::duration operator * (FLOATING d) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000.0 + m_iNanosecond) * d;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

   }


   template < primitive_integral INTEGRAL >
   class ::duration operator / (INTEGRAL i) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000 + m_iNanosecond) / i;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

   }


   template < primitive_integral INTEGRAL >
   class ::duration operator * (INTEGRAL i) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000 + m_iNanosecond) * i;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

   }


   template < primitive_floating FLOATING >
   class ::duration & operator /= (FLOATING d)
   {

      return operator=(*this / d);

   }


   template < primitive_floating FLOATING >
   class ::duration & operator *= (FLOATING d)
   {

      return operator= (*this / d);

   }


   template < primitive_integral INTEGRAL >
   class ::duration & operator /= (INTEGRAL i)
   {

      return operator= (*this / i);

   }


   template < primitive_integral INTEGRAL >
   class ::duration & operator *= (INTEGRAL i)
   {

      return operator= (*this * i);

   }


   class ::duration half() const;


   class ::duration & operator %= (const class ::duration & duration);
   //class ::duration operator % (const class ::duration & duration) const;


   inline time_t GetTimeSpan() const;

   
   inline bool timeout(const duration & duration);
   
   inline ::duration remaining(const duration & duration, const ::duration & durationNow = e_now);




   operator class ::wait() const;




   
   
   operator INTEGRAL_DAY () const { return integral_day(); }
   operator INTEGRAL_HOUR () const { return integral_hour(); }
   operator INTEGRAL_MINUTE () const { return integral_minute(); }
   operator INTEGRAL_SECOND () const { return integral_second(); }
   operator INTEGRAL_MILLISECOND () const { return integral_millisecond(); }
   operator INTEGRAL_MICROSECOND () const { return integral_microsecond(); }
   operator INTEGRAL_NANOSECOND () const { return integral_nanosecond(); }

   operator FLOATING_DAY () const { return floating_day(); }
   operator FLOATING_HOUR () const { return floating_hour(); }
   operator FLOATING_MINUTE () const { return floating_minute(); }
   operator FLOATING_SECOND () const { return floating_second(); }
   operator FLOATING_MILLISECOND () const { return floating_millisecond(); }
   operator FLOATING_MICROSECOND () const { return floating_microsecond(); }
   operator FLOATING_NANOSECOND () const { return floating_nanosecond(); }








   ::integral_day integral_day() const { return INTEGRAL_DAY(m_iSecond / 86'400); }
   ::integral_hour integral_hour() const { return INTEGRAL_HOUR(m_iSecond / 3'600); }
   ::integral_minute integral_minute() const { return INTEGRAL_MINUTE(m_iSecond / 60); }
   ::integral_second integral_second() const { return INTEGRAL_SECOND(m_iSecond); }
   ::integral_millisecond integral_millisecond() const { return INTEGRAL_MILLISECOND(m_iSecond * 1'000 + m_iNanosecond / 1'000'000); }
   ::integral_microsecond integral_microsecond() const { return INTEGRAL_MICROSECOND(m_iSecond * 1'000'000 + m_iNanosecond / 1'000); }
   ::integral_nanosecond integral_nanosecond() const { return INTEGRAL_NANOSECOND(m_iSecond * 1'000'000'000 + m_iNanosecond); }


   ::floating_day floating_day() const { return FLOATING_DAY(floating_second().m_d / 86'400.0); }
   ::floating_hour floating_hour() const { return FLOATING_HOUR(floating_second().m_d / 3'600.0); }
   ::floating_minute floating_minute() const { return FLOATING_MINUTE(floating_second().m_d / 60.0); }
   ::floating_second floating_second() const { return FLOATING_SECOND((double)m_iSecond + ((double) m_iNanosecond / 1'000'000'000.0)); }
   ::floating_millisecond floating_millisecond() const { return FLOATING_MILLISECOND(((::f64)integral_nanosecond().m_i) / 1'000'000.0); }
   ::floating_microsecond floating_microsecond() const { return FLOATING_MICROSECOND(((::f64)integral_nanosecond().m_i) / 1'000.0); }
   ::floating_nanosecond floating_nanosecond() const { return FLOATING_NANOSECOND((::f64)integral_nanosecond().m_i); }


   ::i32 millisecond() const { return integral_millisecond().m_i % 1'000; }










   inline bool operator == (const class ::duration & duration) const { return m_iSecond == duration.m_iSecond && m_iNanosecond == duration.m_iSecond; }
   inline bool operator != (const class ::duration & duration) const { return !operator ==(duration); }
   inline bool operator < (const class ::duration & duration) const { return m_iSecond < duration.m_iSecond || (m_iSecond == duration.m_iSecond && m_iNanosecond < duration.m_iNanosecond); }
   inline bool operator <= (const class ::duration & duration) const { return m_iSecond < duration.m_iSecond || (m_iSecond == duration.m_iSecond && m_iNanosecond <= duration.m_iNanosecond); }
   inline bool operator > (const class ::duration & duration) const { return !operator <=(duration); }
   inline bool operator >= (const class ::duration & duration) const { return !operator <=(duration); }


   duration operator %(const ::duration & duration) const;
   double operator /(const ::duration & duration) const;
   duration operator +(const ::duration & duration) const { return { e_normalize, this->m_iSecond + duration.m_iSecond, this->m_iNanosecond + duration.m_iNanosecond }; }
   duration operator -(const ::duration & duration) const { return { e_normalize, this->m_iSecond - duration.m_iSecond, this->m_iNanosecond - duration.m_iNanosecond }; }


   duration operator -() const { return { e_raw, -m_iSecond, -m_iNanosecond }; }











   inline bool operator == (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator == (::duration(integralnanosecond)); }
   inline bool operator != (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator != (::duration(integralnanosecond)); }
   inline bool operator < (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator < (::duration(integralnanosecond)); }
   inline bool operator <= (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator <= (::duration(integralnanosecond)); }
   inline bool operator > (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator > (::duration(integralnanosecond)); }
   inline bool operator >= (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator >= (::duration(integralnanosecond)); }

   inline bool operator == (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator == (::duration(integralmicrosecond)); }
   inline bool operator != (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator != (::duration(integralmicrosecond)); }
   inline bool operator < (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator < (::duration(integralmicrosecond)); }
   inline bool operator <= (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator <= (::duration(integralmicrosecond)); }
   inline bool operator > (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator > (::duration(integralmicrosecond)); }
   inline bool operator >= (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator >= (::duration(integralmicrosecond)); }

   inline bool operator == (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator == (::duration(integralmillisecond)); }
   inline bool operator != (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator != (::duration(integralmillisecond)); }
   inline bool operator < (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator < (::duration(integralmillisecond)); }
   inline bool operator <= (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator <= (::duration(integralmillisecond)); }
   inline bool operator > (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator > (::duration(integralmillisecond)); }
   inline bool operator >= (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator >= (::duration(integralmillisecond)); }

   inline bool operator == (const ::INTEGRAL_SECOND & integralsecond) const { return operator == (::duration(integralsecond)); }
   inline bool operator != (const ::INTEGRAL_SECOND & integralsecond) const { return operator != (::duration(integralsecond)); }
   inline bool operator < (const ::INTEGRAL_SECOND & integralsecond) const { return operator < (::duration(integralsecond)); }
   inline bool operator <= (const ::INTEGRAL_SECOND & integralsecond) const { return operator <= (::duration(integralsecond)); }
   inline bool operator > (const ::INTEGRAL_SECOND & integralsecond) const { return operator > (::duration(integralsecond)); }
   inline bool operator >= (const ::INTEGRAL_SECOND & integralsecond) const { return operator >= (::duration(integralsecond)); }

   inline bool operator == (const ::INTEGRAL_MINUTE & minute) const { return operator == (::duration(minute)); }
   inline bool operator != (const ::INTEGRAL_MINUTE & minute) const { return operator != (::duration(minute)); }
   inline bool operator < (const ::INTEGRAL_MINUTE & minute) const { return operator < (::duration(minute)); }
   inline bool operator <= (const ::INTEGRAL_MINUTE & minute) const { return operator <= (::duration(minute)); }
   inline bool operator > (const ::INTEGRAL_MINUTE & minute) const { return operator > (::duration(minute)); }
   inline bool operator >= (const ::INTEGRAL_MINUTE & minute) const { return operator >= (::duration(minute)); }

   inline bool operator == (const ::INTEGRAL_HOUR & day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::INTEGRAL_HOUR & day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::INTEGRAL_HOUR & day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::INTEGRAL_HOUR & day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::INTEGRAL_HOUR & day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::INTEGRAL_HOUR & day) const { return operator >= (::duration(day)); }

   inline bool operator == (const ::INTEGRAL_DAY & day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::INTEGRAL_DAY & day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::INTEGRAL_DAY & day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::INTEGRAL_DAY & day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::INTEGRAL_DAY & day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::INTEGRAL_DAY & day) const { return operator >= (::duration(day)); }








   inline bool operator == (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator == (::duration(floatingnanosecond)); }
   inline bool operator != (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator != (::duration(floatingnanosecond)); }
   inline bool operator < (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator < (::duration(floatingnanosecond)); }
   inline bool operator <= (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator <= (::duration(floatingnanosecond)); }
   inline bool operator > (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator > (::duration(floatingnanosecond)); }
   inline bool operator >= (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator >= (::duration(floatingnanosecond)); }

   inline bool operator == (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator == (::duration(floatingmicrosecond)); }
   inline bool operator != (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator != (::duration(floatingmicrosecond)); }
   inline bool operator < (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator < (::duration(floatingmicrosecond)); }
   inline bool operator <= (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator <= (::duration(floatingmicrosecond)); }
   inline bool operator > (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator > (::duration(floatingmicrosecond)); }
   inline bool operator >= (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator >= (::duration(floatingmicrosecond)); }

   inline bool operator == (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator == (::duration(floatingmillisecond)); }
   inline bool operator != (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator != (::duration(floatingmillisecond)); }
   inline bool operator < (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator < (::duration(floatingmillisecond)); }
   inline bool operator <= (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator <= (::duration(floatingmillisecond)); }
   inline bool operator > (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator > (::duration(floatingmillisecond)); }
   inline bool operator >= (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator >= (::duration(floatingmillisecond)); }

   inline bool operator == (const ::FLOATING_SECOND & floatingsecond) const { return operator == (::duration(floatingsecond)); }
   inline bool operator != (const ::FLOATING_SECOND & floatingsecond) const { return operator != (::duration(floatingsecond)); }
   inline bool operator < (const ::FLOATING_SECOND & floatingsecond) const { return operator < (::duration(floatingsecond)); }
   inline bool operator <= (const ::FLOATING_SECOND & floatingsecond) const { return operator <= (::duration(floatingsecond)); }
   inline bool operator > (const ::FLOATING_SECOND & floatingsecond) const { return operator > (::duration(floatingsecond)); }
   inline bool operator >= (const ::FLOATING_SECOND & floatingsecond) const { return operator >= (::duration(floatingsecond)); }

   inline bool operator == (const ::FLOATING_MINUTE & minute) const { return operator == (::duration(minute)); }
   inline bool operator != (const ::FLOATING_MINUTE & minute) const { return operator != (::duration(minute)); }
   inline bool operator < (const ::FLOATING_MINUTE & minute) const { return operator < (::duration(minute)); }
   inline bool operator <= (const ::FLOATING_MINUTE & minute) const { return operator <= (::duration(minute)); }
   inline bool operator > (const ::FLOATING_MINUTE & minute) const { return operator > (::duration(minute)); }
   inline bool operator >= (const ::FLOATING_MINUTE & minute) const { return operator >= (::duration(minute)); }

   inline bool operator == (const ::FLOATING_HOUR & day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::FLOATING_HOUR & day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::FLOATING_HOUR & day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::FLOATING_HOUR & day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::FLOATING_HOUR & day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::FLOATING_HOUR & day) const { return operator >= (::duration(day)); }

   inline bool operator == (const ::FLOATING_DAY & day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::FLOATING_DAY & day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::FLOATING_DAY & day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::FLOATING_DAY & day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::FLOATING_DAY & day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::FLOATING_DAY & day) const { return operator >= (::duration(day)); }


   inline bool operator == (const class time & time) const { return operator == (::duration(FLOATING_SECOND(time.m_d))); }
   inline bool operator != (const class time & time) const { return operator != (::duration(FLOATING_SECOND(time.m_d))); }
   inline bool operator < (const class time & time) const { return operator < (::duration(FLOATING_SECOND(time.m_d))); }
   inline bool operator <= (const class time & time) const { return operator <= (::duration(FLOATING_SECOND(time.m_d))); }
   inline bool operator > (const class time & time) const { return operator > (::duration(FLOATING_SECOND(time.m_d))); }
   inline bool operator >= (const class time & time) const { return operator >= (::duration(FLOATING_SECOND(time.m_d))); }






   duration operator %(const ::INTEGRAL_NANOSECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_NANOSECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_NANOSECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_NANOSECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::INTEGRAL_MICROSECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_MICROSECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_MICROSECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_MICROSECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::INTEGRAL_MILLISECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_MILLISECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_MILLISECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_MILLISECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::INTEGRAL_SECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_SECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_SECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_SECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::INTEGRAL_MINUTE & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_MINUTE & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_MINUTE & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_MINUTE & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::INTEGRAL_HOUR & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_HOUR & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_HOUR & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_HOUR & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::INTEGRAL_DAY & duration) const { return *this % ::duration(duration);}
   double operator /(const ::INTEGRAL_DAY & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::INTEGRAL_DAY & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::INTEGRAL_DAY & duration) const { return *this - ::duration(duration); }









   duration operator %(const ::FLOATING_NANOSECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_NANOSECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_NANOSECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_NANOSECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::FLOATING_MICROSECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_MICROSECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_MICROSECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_MICROSECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::FLOATING_MILLISECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_MILLISECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_MILLISECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_MILLISECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::FLOATING_SECOND & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_SECOND & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_SECOND & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_SECOND & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::FLOATING_MINUTE & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_MINUTE & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_MINUTE & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_MINUTE & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::FLOATING_HOUR & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_HOUR & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_HOUR & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_HOUR & duration) const { return *this - ::duration(duration); }


   duration operator %(const ::FLOATING_DAY & duration) const { return *this % ::duration(duration);}
   double operator /(const ::FLOATING_DAY & duration) const { return *this / ::duration(duration);}
   duration operator +(const ::FLOATING_DAY & duration) const { return *this + ::duration(duration); }
   duration operator -(const ::FLOATING_DAY & duration) const { return *this - ::duration(duration); }








   duration operator %(const class time & time) const { return *this % ::duration(FLOATING_SECOND(time.m_d));}
   double operator /(const class time & time) const { return *this / ::duration(FLOATING_SECOND(time.m_d));}
   duration operator +(const class time & time) const { return *this + ::duration(FLOATING_SECOND(time.m_d)); }
   duration operator -(const class time & time) const { return *this - ::duration(FLOATING_SECOND(time.m_d)); }







   inline bool operator == (const ::integral_nanosecond& integralnanosecond) const { return operator == (::duration(integralnanosecond)); }
   inline bool operator != (const ::integral_nanosecond& integralnanosecond) const { return operator != (::duration(integralnanosecond)); }
   inline bool operator < (const ::integral_nanosecond& integralnanosecond) const { return operator < (::duration(integralnanosecond)); }
   inline bool operator <= (const ::integral_nanosecond& integralnanosecond) const { return operator <= (::duration(integralnanosecond)); }
   inline bool operator > (const ::integral_nanosecond& integralnanosecond) const { return operator > (::duration(integralnanosecond)); }
   inline bool operator >= (const ::integral_nanosecond& integralnanosecond) const { return operator >= (::duration(integralnanosecond)); }

   inline bool operator == (const ::integral_microsecond& integralmicrosecond) const { return operator == (::duration(integralmicrosecond)); }
   inline bool operator != (const ::integral_microsecond& integralmicrosecond) const { return operator != (::duration(integralmicrosecond)); }
   inline bool operator < (const ::integral_microsecond& integralmicrosecond) const { return operator < (::duration(integralmicrosecond)); }
   inline bool operator <= (const ::integral_microsecond& integralmicrosecond) const { return operator <= (::duration(integralmicrosecond)); }
   inline bool operator > (const ::integral_microsecond& integralmicrosecond) const { return operator > (::duration(integralmicrosecond)); }
   inline bool operator >= (const ::integral_microsecond& integralmicrosecond) const { return operator >= (::duration(integralmicrosecond)); }

   inline bool operator == (const ::integral_millisecond& integralmillisecond) const { return operator == (::duration(integralmillisecond)); }
   inline bool operator != (const ::integral_millisecond& integralmillisecond) const { return operator != (::duration(integralmillisecond)); }
   inline bool operator < (const ::integral_millisecond& integralmillisecond) const { return operator < (::duration(integralmillisecond)); }
   inline bool operator <= (const ::integral_millisecond& integralmillisecond) const { return operator <= (::duration(integralmillisecond)); }
   inline bool operator > (const ::integral_millisecond& integralmillisecond) const { return operator > (::duration(integralmillisecond)); }
   inline bool operator >= (const ::integral_millisecond& integralmillisecond) const { return operator >= (::duration(integralmillisecond)); }

   inline bool operator == (const ::integral_second& integralsecond) const { return operator == (::duration(integralsecond)); }
   inline bool operator != (const ::integral_second& integralsecond) const { return operator != (::duration(integralsecond)); }
   inline bool operator < (const ::integral_second& integralsecond) const { return operator < (::duration(integralsecond)); }
   inline bool operator <= (const ::integral_second& integralsecond) const { return operator <= (::duration(integralsecond)); }
   inline bool operator > (const ::integral_second& integralsecond) const { return operator > (::duration(integralsecond)); }
   inline bool operator >= (const ::integral_second& integralsecond) const { return operator >= (::duration(integralsecond)); }

   inline bool operator == (const ::integral_minute& minute) const { return operator == (::duration(minute)); }
   inline bool operator != (const ::integral_minute& minute) const { return operator != (::duration(minute)); }
   inline bool operator < (const ::integral_minute& minute) const { return operator < (::duration(minute)); }
   inline bool operator <= (const ::integral_minute& minute) const { return operator <= (::duration(minute)); }
   inline bool operator > (const ::integral_minute& minute) const { return operator > (::duration(minute)); }
   inline bool operator >= (const ::integral_minute& minute) const { return operator >= (::duration(minute)); }

   inline bool operator == (const ::integral_hour& day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::integral_hour& day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::integral_hour& day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::integral_hour& day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::integral_hour& day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::integral_hour& day) const { return operator >= (::duration(day)); }

   inline bool operator == (const ::integral_day& day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::integral_day& day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::integral_day& day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::integral_day& day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::integral_day& day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::integral_day& day) const { return operator >= (::duration(day)); }








   inline bool operator == (const ::floating_nanosecond& floatingnanosecond) const { return operator == (::duration(floatingnanosecond)); }
   inline bool operator != (const ::floating_nanosecond& floatingnanosecond) const { return operator != (::duration(floatingnanosecond)); }
   inline bool operator < (const ::floating_nanosecond& floatingnanosecond) const { return operator < (::duration(floatingnanosecond)); }
   inline bool operator <= (const ::floating_nanosecond& floatingnanosecond) const { return operator <= (::duration(floatingnanosecond)); }
   inline bool operator > (const ::floating_nanosecond& floatingnanosecond) const { return operator > (::duration(floatingnanosecond)); }
   inline bool operator >= (const ::floating_nanosecond& floatingnanosecond) const { return operator >= (::duration(floatingnanosecond)); }

   inline bool operator == (const ::floating_microsecond& floatingmicrosecond) const { return operator == (::duration(floatingmicrosecond)); }
   inline bool operator != (const ::floating_microsecond& floatingmicrosecond) const { return operator != (::duration(floatingmicrosecond)); }
   inline bool operator < (const ::floating_microsecond& floatingmicrosecond) const { return operator < (::duration(floatingmicrosecond)); }
   inline bool operator <= (const ::floating_microsecond& floatingmicrosecond) const { return operator <= (::duration(floatingmicrosecond)); }
   inline bool operator > (const ::floating_microsecond& floatingmicrosecond) const { return operator > (::duration(floatingmicrosecond)); }
   inline bool operator >= (const ::floating_microsecond& floatingmicrosecond) const { return operator >= (::duration(floatingmicrosecond)); }

   inline bool operator == (const ::floating_millisecond& floatingmillisecond) const { return operator == (::duration(floatingmillisecond)); }
   inline bool operator != (const ::floating_millisecond& floatingmillisecond) const { return operator != (::duration(floatingmillisecond)); }
   inline bool operator < (const ::floating_millisecond& floatingmillisecond) const { return operator < (::duration(floatingmillisecond)); }
   inline bool operator <= (const ::floating_millisecond& floatingmillisecond) const { return operator <= (::duration(floatingmillisecond)); }
   inline bool operator > (const ::floating_millisecond& floatingmillisecond) const { return operator > (::duration(floatingmillisecond)); }
   inline bool operator >= (const ::floating_millisecond& floatingmillisecond) const { return operator >= (::duration(floatingmillisecond)); }

   inline bool operator == (const ::floating_second& floatingsecond) const { return operator == (::duration(floatingsecond)); }
   inline bool operator != (const ::floating_second& floatingsecond) const { return operator != (::duration(floatingsecond)); }
   inline bool operator < (const ::floating_second& floatingsecond) const { return operator < (::duration(floatingsecond)); }
   inline bool operator <= (const ::floating_second& floatingsecond) const { return operator <= (::duration(floatingsecond)); }
   inline bool operator > (const ::floating_second& floatingsecond) const { return operator > (::duration(floatingsecond)); }
   inline bool operator >= (const ::floating_second& floatingsecond) const { return operator >= (::duration(floatingsecond)); }

   inline bool operator == (const ::floating_minute& minute) const { return operator == (::duration(minute)); }
   inline bool operator != (const ::floating_minute& minute) const { return operator != (::duration(minute)); }
   inline bool operator < (const ::floating_minute& minute) const { return operator < (::duration(minute)); }
   inline bool operator <= (const ::floating_minute& minute) const { return operator <= (::duration(minute)); }
   inline bool operator > (const ::floating_minute& minute) const { return operator > (::duration(minute)); }
   inline bool operator >= (const ::floating_minute& minute) const { return operator >= (::duration(minute)); }

   inline bool operator == (const ::floating_hour& day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::floating_hour& day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::floating_hour& day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::floating_hour& day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::floating_hour& day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::floating_hour& day) const { return operator >= (::duration(day)); }

   inline bool operator == (const ::floating_day& day) const { return operator == (::duration(day)); }
   inline bool operator != (const ::floating_day& day) const { return operator != (::duration(day)); }
   inline bool operator < (const ::floating_day& day) const { return operator < (::duration(day)); }
   inline bool operator <= (const ::floating_day& day) const { return operator <= (::duration(day)); }
   inline bool operator > (const ::floating_day& day) const { return operator > (::duration(day)); }
   inline bool operator >= (const ::floating_day& day) const { return operator >= (::duration(day)); }








   duration operator %(const ::integral_nanosecond& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_nanosecond& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_nanosecond& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_nanosecond& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::integral_microsecond& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_microsecond& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_microsecond& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_microsecond& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::integral_millisecond& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_millisecond& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_millisecond& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_millisecond& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::integral_second& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_second& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_second& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_second& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::integral_minute& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_minute& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_minute& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_minute& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::integral_hour& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_hour& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_hour& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_hour& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::integral_day& duration) const { return *this % ::duration(duration); }
   double operator /(const ::integral_day& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::integral_day& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::integral_day& duration) const { return *this - ::duration(duration); }









   duration operator %(const ::floating_nanosecond& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_nanosecond& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_nanosecond& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_nanosecond& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::floating_microsecond& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_microsecond& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_microsecond& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_microsecond& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::floating_millisecond& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_millisecond& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_millisecond& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_millisecond& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::floating_second& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_second& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_second& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_second& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::floating_minute& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_minute& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_minute& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_minute& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::floating_hour& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_hour& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_hour& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_hour& duration) const { return *this - ::duration(duration); }


   duration operator %(const ::floating_day& duration) const { return *this % ::duration(duration); }
   double operator /(const ::floating_day& duration) const { return *this / ::duration(duration); }
   duration operator +(const ::floating_day& duration) const { return *this + ::duration(duration); }
   duration operator -(const ::floating_day& duration) const { return *this - ::duration(duration); }




};


inline FLOATING_SECOND time() { return duration(e_now).floating_second(); }

template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
inline duration::duration(enum_raw, INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

}

template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
inline duration::duration(enum_normalize, INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds)
{

   m_iSecond = iSeconds + iNanoseconds / 1'000'000'000;

   m_iNanosecond = iNanoseconds % 1'000'000'000;
   
   while(m_iNanosecond < 0)
   {

      m_iSecond--;

      m_iNanosecond += 1'000'000'000;

   }

}


//inline duration::duration(const ::duration& duration) :
//   DURATION(duration)
//{
//
//}


inline void duration::raw_set(time_t iSeconds, long iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

}


inline void duration::set(time_t iSeconds, long iNanoseconds)
{

   raw_set(iSeconds, iNanoseconds);

   normalize();

}


inline void duration::set_null()
{

   raw_set(0, 0);

}


inline class ::duration duration::raw_create(time_t iSeconds, long iNanoseconds)
{

   duration duration;

   duration.raw_set(iSeconds, iNanoseconds);

   return duration;

}


inline class ::duration duration::fcreate(long double d, double dNano)
{

   duration duration;

   duration.fset(d, dNano);

   return duration;

}


inline class ::duration duration::create(time_t iSeconds, long iNanoseconds)
{

   duration duration;

   duration.set(iSeconds, iNanoseconds);

   return duration;

}


inline class ::duration duration::create_null()
{

   duration duration;

   duration.set_null();

   return duration;

}


inline bool duration::is_pos_infinity() const
{

   return m_iSecond == ::numeric_info < decltype(m_iSecond) > ::maximum();

}


inline bool duration::is_infinite() const
{

   return m_iSecond == ::numeric_info < decltype(m_iSecond) > ::maximum();

}


bool duration::is_null() const
{

   return m_iSecond == 0 && m_iNanosecond == 0;

}


inline class ::duration duration::infinite()
{

   return {(::i64)MAXI64,(::i64)0};

}


inline class ::duration duration::pos_infinity()
{

   return {(::i64)MAXI64, (::i64)0};

}


inline class ::duration duration::zero()
{

   return {(::i64)0,(::i64) 0};

}


inline time_t duration::GetTimeSpan() const
{

   return m_iSecond;

}


inline duration::operator bool() const
{

   return m_iSecond != 0 || m_iNanosecond != 0;

}


//CLASS_DECL_ACME void sleep(const duration & duration);




//inline bool CLASS_DECL_ACME operator >(const duration & duration1, const duration & duration2)
//{
//
//   auto iCompare = duration1.m_iSecond - duration2.m_iSecond;
//
//   if(iCompare > 0)
//   {
//
//      return true;
//
//   }
//   else if(iCompare == 0)
//   {
//
//      return duration1.m_iSecond > duration2.m_iSecond;
//
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//}
//
//
//inline bool CLASS_DECL_ACME operator < (const duration & duration1, const duration & duration2)
//{
//
//   auto iCompare = duration1.m_iSecond - duration2.m_iSecond;
//
//   if(iCompare < 0)
//   {
//
//      return true;
//
//   }
//   else if(iCompare == 0)
//   {
//
//      return duration1.m_iSecond < duration2.m_iSecond;
//
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//}


//inline bool ::duration::operator == (const ::duration& duration) const { return m_i == duration.::duration().m_i; }
//inline bool ::duration::operator != (const ::duration& duration) const { return m_i != duration.::duration().m_i; }
//inline bool ::duration::operator < (const ::duration& duration) const { return m_i < duration.::duration().m_i; }
//inline bool ::duration::operator <= (const ::duration& duration) const { return m_i <= duration.::duration().m_i; }
//inline bool ::duration::operator > (const ::duration& duration) const { return m_i > duration.::duration().m_i; }
//inline bool ::duration::operator >= (const ::duration& duration) const { return m_i >= duration.::duration().m_i; }
//inline ::duration ::duration::operator - (const ::duration& duration) const { return m_i - duration.::duration().m_i; }
//inline ::duration ::duration::operator + (const ::duration& duration) const { return m_i + duration.::duration().m_i; }
//inline ::duration& ::duration::operator -= (const ::duration& duration) { m_i -= duration.::duration().m_i; return *this; }
//inline ::duration& ::duration::operator += (const ::duration& duration) { m_i += duration.::duration().m_i; return *this; }


CLASS_DECL_ACME class ::duration __random(const class ::duration & d1, const class ::duration & d2);


inline duration::operator class ::wait() const
{

   return is_infinite() ? ::wait::__infinite() : floating_second().m_d;

}


class CLASS_DECL_ACME frequency :
   public FREQUENCY
{
public:


   frequency(enum_zero ezero = e_zero):FREQUENCY{} {}
   frequency(const ::FREQUENCY & frequency):FREQUENCY(frequency) {}
   
   
};


template < primitive_floating FLOATING >
class ::frequency operator / (FLOATING d, const ::duration & duration)
{

   auto nanosecond = (duration.m_iSecond * 1'000'000'000.0 + duration.m_iNanosecond);

   return d * 1'000'000'000.0 / nanosecond;

}


template < primitive_floating FLOATING >
class ::duration operator * (FLOATING d, const ::duration & duration)
{

   auto nanosecond = d * (duration.m_iSecond * 1'000'000'000.0 + duration.m_iNanosecond);

   return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

}


template < primitive_integral INTEGRAL >
class ::frequency operator / (INTEGRAL i, const ::duration & duration)
{

   auto nanosecond = (duration.m_iSecond * 1'000'000'000 + duration.m_iNanosecond);

   return FREQUENCY((double)(i * 1'000'000'000) / (double)nanosecond);

}


template < primitive_integral INTEGRAL >
class ::duration operator * (INTEGRAL i, const ::duration & duration)
{

   auto nanosecond = i * (duration.m_iSecond * 1'000'000'000 + duration.m_iNanosecond);

   return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

}
