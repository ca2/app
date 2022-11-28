// Refactoring by camilo on 2021-10-05 12:46 BRT <3ThomasBorregaardSørensen!!
#pragma once


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

   time(enum_zero ezero = e_zero) :
      TIME{}
   {

   }


   time(enum_now)
   {

      Now();

   }


   time(enum_infinite)
   {

      Infinite();

   }


   time(const ::INTEGRAL_NANOSECOND & integral) : time(e_raw, (::i64)integral.m_i / 1'000'000'000, (long ) (integral.m_i % 1'000'000'000)) {}
   time(const ::FLOATING_NANOSECOND & floating) : time(e_raw, (::i64)(floating.m_d / 1'000'000'000.0), (long)(fmod(floating.m_d, 1'000'000'000.0))) {}
   time(const ::INTEGRAL_MICROSECOND & integral) : time(e_raw, integral.m_i / 1'000'000, (long) ((integral.m_i % 1'000'000) * 1'000)) {}
   time(const ::FLOATING_MICROSECOND & floating) : time(e_raw, (::i64)(floating.m_d / 1'000'000.0), (long)(fmod(floating.m_d, 1'000'000.0) * 1'000.0)) {}
   time(const ::INTEGRAL_MILLISECOND & integral) : time(e_raw, integral.m_i / 1'000, (long) ((integral.m_i % 1'000) * 1'000'000)) {}
   time(const ::FLOATING_MILLISECOND & floating) : time(e_raw, (::i64)(floating.m_d / 1'000.0), (long)(fmod(floating.m_d, 1'000.0) * 1'000'000.0)) {}
   time(const ::INTEGRAL_SECOND & integral) : time(e_raw, integral.m_i) {}
   time(const ::FLOATING_SECOND & floating) : time(e_raw, (::i64)(floating.m_d), (long)(fmod(floating.m_d, 1.0) * 1'000'000'000.0)) {}
   time(const ::INTEGRAL_MINUTE & integral) : time(e_raw, integral.m_i * 60) {}
   time(const ::FLOATING_MINUTE & floating) : time(e_raw, (::i64)(floating.m_d * 60.0), (long)(fmod(floating.m_d * 60.0, 1.0) * 1'000'000'000.0)) {}
   time(const ::INTEGRAL_HOUR & integral) : time(e_raw, integral.m_i * 3'600) {}
   time(const ::FLOATING_HOUR & floating) : time(e_raw, (::i64)(floating.m_d * 3'600.0), (long)(fmod(floating.m_d * 3'600.0, 1.0) * 1'000'000'000.0)) {}
   time(const ::INTEGRAL_DAY & integral) : time(e_raw, integral.m_i * 86'400) {}
   time(const ::FLOATING_DAY & floating) : time(e_raw, (::i64)(floating.m_d * 86'400.0), (long)(fmod(floating.m_d * 86'400.0, 1.0) * 1'000'000'000.0)) {}

   time(const class ::time& time) : TIME{time} { }

   template < primitive_integer INTEGER1, primitive_integral INTEGRAL2 >
   time(INTEGER1 iSecond, INTEGRAL2 iNanosecond) :
      TIME{ .m_iSecond = (time_t)iSecond, .m_iNanosecond = (long)iNanosecond }
   { }


   template < primitive_floating FLOATING, primitive_number NUMBER >
   time(FLOATING fSeconds, NUMBER nanoseconds)
   {
        
       fset(fSeconds, nanoseconds);
        
   }

   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   time(enum_raw, INTEGRAL1 iSecond, INTEGRAL2 iNanosecond);

   template < primitive_integral INTEGRAL1 >
   time(enum_raw, INTEGRAL1 iSecond) : time(e_raw, iSecond, 0) {}
   
   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   time(enum_normalize, INTEGRAL1 iSecond, INTEGRAL2 iNanosecond);

   time(const ::TIME & time) : TIME(time) {}


   inline void raw_set(time_t iSeconds, long iNanoseconds = 0);
   inline void set(time_t iSeconds, long iNanoseconds);
   inline void set_null();
   static inline time raw_create(time_t iSeconds, long iNanoseconds);
   static inline time create(time_t iSeconds, long iNanoseconds);
   static inline time create_null();


   void fset(long double dSeconds);
   void fset(long double dSeconds, double dNanoseconds);
   static inline time fcreate(long double dSeconds, double dNanoseconds);


   void set(i64 i, enum_unit eunit);
   void set(long double d, enum_unit eunit);


   //inline bool is_infinity() const;
   constexpr bool is_infinite() const;
   inline bool is_null() const;
   inline bool is_set() const { return (m_iSecond >= 0 && m_iNanosecond > 0) || (m_iSecond > 0 && m_iNanosecond >= 0); }
   inline static time infinite();
   //inline static time pos_infinity();
   inline static time zero();
   inline bool operator !() const {return is_null();}

   void Infinite() {*this=infinite();}
   //void PosInfinity() {*this=pos_infinity();}
   void Zero() {*this=zero();}
   void Null() { Zero(); }

   class ::time & operator = (const class time & time);

   inline bool timeout(const class time & time);
   void normalize();

   inline operator bool() const;


   inline double operator() ()const { return floating_second().m_d; }


   operator const timespec * () const { return (const timespec *)this; }
   operator timespec * () { return (timespec *) this; }
   
   //static inline class ::time first();
   static inline class ::time now() { return e_now; }

   inline bool is_past() const { return now() > *this; }

   inline class ::time & Now()
   { 
      
      struct timespec timespec; 
      
      if (timespec_get(&timespec, TIME_UTC) != TIME_UTC) 
      {
         
         throw "timespec_get failed!!"; 
         
      }

      m_iSecond = timespec.tv_sec;

      m_iNanosecond = timespec.tv_nsec;
      
      return *this; 
      
   }
   

   inline class time elapsed(const class time & time = now()) const { return time - *this; }

   inline time update_elapsed(const class time & timeStop = ::now < time >())
   {

      auto elapsed = timeStop - *this;

      operator=(timeStop);

      return elapsed;

   }

   inline double period_rate(const class time & timePeriod, const class time & time = now()) const { return ((time - *this) % timePeriod) / timePeriod; }

   
   //inline class ::time operator - (const class time & time) const { return { e_normalize, m_iSecond - time.m_iSecond, m_iNanosecond - time.m_iNanosecond }; }
   //inline class ::time operator + (const class time & time) const { return { e_normalize, m_iSecond + time.m_iSecond, m_iNanosecond + time.m_iNanosecond }; }
   inline class ::time & operator -= (const class time & time) { m_iSecond -= time.m_iSecond; m_iNanosecond -= time.m_iNanosecond; normalize();  return *this; }
   inline class ::time & operator += (const class time & time) { m_iSecond += time.m_iSecond; m_iNanosecond += time.m_iNanosecond; normalize();  return *this; }


   template < primitive_floating FLOATING >
   class ::time operator / (FLOATING d) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000.0 + m_iNanosecond) / d;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

   }


   template < primitive_floating FLOATING >
   class ::time operator * (FLOATING d) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000.0 + m_iNanosecond) * d;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

   }


   template < primitive_integral INTEGRAL >
   class ::time operator / (INTEGRAL i) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000 + m_iNanosecond) / i;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

   }


   template < primitive_integral INTEGRAL >
   class ::time operator * (INTEGRAL i) const
   {

      auto nanosecond = (m_iSecond * 1'000'000'000 + m_iNanosecond) * i;

      return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

   }


   template < primitive_floating FLOATING >
   class ::time & operator /= (FLOATING d)
   {

      return operator=(*this / d);

   }


   template < primitive_floating FLOATING >
   class ::time & operator *= (FLOATING d)
   {

      return operator= (*this / d);

   }


   template < primitive_integral INTEGRAL >
   class ::time & operator /= (INTEGRAL i)
   {

      return operator= (*this / i);

   }


   template < primitive_integral INTEGRAL >
   class ::time & operator *= (INTEGRAL i)
   {

      return operator= (*this * i);

   }


   class ::time half() const;


   class ::time & operator %= (const class time & time);
   //class ::time operator % (const class time & time) const;


   inline time_t GetTimeSpan() const;

   
   //inline bool timeout(const class time & time);
   
   inline time remaining(const class time & time, const class time & timeNow = e_now);


   inline class ::time wait() const;

   
   // operator INTEGRAL_DAY () const { return integral_day(); }
   // operator INTEGRAL_HOUR () const { return integral_hour(); }
   // operator INTEGRAL_MINUTE () const { return integral_minute(); }
   // operator INTEGRAL_SECOND () const { return integral_second(); }
   // operator INTEGRAL_MILLISECOND () const { return integral_millisecond(); }
   // operator INTEGRAL_MICROSECOND () const { return integral_microsecond(); }
   // operator INTEGRAL_NANOSECOND () const { return integral_nanosecond(); }

   // operator FLOATING_DAY () const { return floating_day(); }
   // operator FLOATING_HOUR () const { return floating_hour(); }
   // operator FLOATING_MINUTE () const { return floating_minute(); }
   // operator FLOATING_SECOND () const { return floating_second(); }
   // operator FLOATING_MILLISECOND () const { return floating_millisecond(); }
   // operator FLOATING_MICROSECOND () const { return floating_microsecond(); }
   // operator FLOATING_NANOSECOND () const { return floating_nanosecond(); }








   ::integral_day integral_day() const { return INTEGRAL_DAY(m_iSecond / 86'400); }
   ::integral_hour integral_hour() const { return INTEGRAL_HOUR(m_iSecond / 3'600); }
   ::integral_minute integral_minute() const { return INTEGRAL_MINUTE(m_iSecond / 60); }
   ::integral_second integral_second() const { return INTEGRAL_SECOND(m_iSecond); }
   constexpr ::integral_millisecond integral_millisecond() const { return INTEGRAL_MILLISECOND(m_iSecond * 1'000 + m_iNanosecond / 1'000'000); }
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










   inline bool operator == (const class time & time) const { return m_iSecond == time.m_iSecond && m_iNanosecond == time.m_iSecond; }
   inline bool operator != (const class time & time) const { return !operator ==(time); }
   inline bool operator < (const class time & time) const { return m_iSecond < time.m_iSecond || (m_iSecond == time.m_iSecond && m_iNanosecond < time.m_iNanosecond); }
   inline bool operator <= (const class time & time) const { return m_iSecond < time.m_iSecond || (m_iSecond == time.m_iSecond && m_iNanosecond <= time.m_iNanosecond); }
   inline bool operator > (const class time & time) const { return !operator <=(time); }
   inline bool operator >= (const class time & time) const { return !operator <=(time); }


   time operator %(const class time & time) const;
   double operator /(const class time & time) const;
   time operator +(const class time & time) const { return { e_normalize, this->m_iSecond + time.m_iSecond, this->m_iNanosecond + time.m_iNanosecond }; }
   time operator -(const class time & time) const { return { e_normalize, this->m_iSecond - time.m_iSecond, this->m_iNanosecond - time.m_iNanosecond }; }


   time operator -() const { return { e_raw, -m_iSecond, -m_iNanosecond }; }











   //inline bool operator == (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator == (class ::time(integralnanosecond)); }
   //inline bool operator != (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator != (class ::time(integralnanosecond)); }
   //inline bool operator < (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator < (class ::time(integralnanosecond)); }
   //inline bool operator <= (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator <= (class ::time(integralnanosecond)); }
   //inline bool operator > (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator > (class ::time(integralnanosecond)); }
   //inline bool operator >= (const ::INTEGRAL_NANOSECOND & integralnanosecond) const { return operator >= (class ::time(integralnanosecond)); }

   //inline bool operator == (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator == (class ::time(integralmicrosecond)); }
   //inline bool operator != (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator != (class ::time(integralmicrosecond)); }
   //inline bool operator < (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator < (class ::time(integralmicrosecond)); }
   //inline bool operator <= (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator <= (class ::time(integralmicrosecond)); }
   //inline bool operator > (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator > (class ::time(integralmicrosecond)); }
   //inline bool operator >= (const ::INTEGRAL_MICROSECOND & integralmicrosecond) const { return operator >= (class ::time(integralmicrosecond)); }

   //inline bool operator == (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator == (class ::time(integralmillisecond)); }
   //inline bool operator != (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator != (class ::time(integralmillisecond)); }
   //inline bool operator < (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator < (class ::time(integralmillisecond)); }
   //inline bool operator <= (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator <= (class ::time(integralmillisecond)); }
   //inline bool operator > (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator > (class ::time(integralmillisecond)); }
   //inline bool operator >= (const ::INTEGRAL_MILLISECOND & integralmillisecond) const { return operator >= (class ::time(integralmillisecond)); }

   //inline bool operator == (const ::INTEGRAL_SECOND & integralsecond) const { return operator == (class ::time(integralsecond)); }
   //inline bool operator != (const ::INTEGRAL_SECOND & integralsecond) const { return operator != (class ::time(integralsecond)); }
   //inline bool operator < (const ::INTEGRAL_SECOND & integralsecond) const { return operator < (class ::time(integralsecond)); }
   //inline bool operator <= (const ::INTEGRAL_SECOND & integralsecond) const { return operator <= (class ::time(integralsecond)); }
   //inline bool operator > (const ::INTEGRAL_SECOND & integralsecond) const { return operator > (class ::time(integralsecond)); }
   //inline bool operator >= (const ::INTEGRAL_SECOND & integralsecond) const { return operator >= (class ::time(integralsecond)); }

   //inline bool operator == (const ::INTEGRAL_MINUTE & minute) const { return operator == (class ::time(minute)); }
   //inline bool operator != (const ::INTEGRAL_MINUTE & minute) const { return operator != (class ::time(minute)); }
   //inline bool operator < (const ::INTEGRAL_MINUTE & minute) const { return operator < (class ::time(minute)); }
   //inline bool operator <= (const ::INTEGRAL_MINUTE & minute) const { return operator <= (class ::time(minute)); }
   //inline bool operator > (const ::INTEGRAL_MINUTE & minute) const { return operator > (class ::time(minute)); }
   //inline bool operator >= (const ::INTEGRAL_MINUTE & minute) const { return operator >= (class ::time(minute)); }

   //inline bool operator == (const ::INTEGRAL_HOUR & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::INTEGRAL_HOUR & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::INTEGRAL_HOUR & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::INTEGRAL_HOUR & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::INTEGRAL_HOUR & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::INTEGRAL_HOUR & day) const { return operator >= (class ::time(day)); }

   //inline bool operator == (const ::INTEGRAL_DAY & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::INTEGRAL_DAY & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::INTEGRAL_DAY & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::INTEGRAL_DAY & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::INTEGRAL_DAY & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::INTEGRAL_DAY & day) const { return operator >= (class ::time(day)); }








   //inline bool operator == (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator == (class ::time(floatingnanosecond)); }
   //inline bool operator != (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator != (class ::time(floatingnanosecond)); }
   //inline bool operator < (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator < (class ::time(floatingnanosecond)); }
   //inline bool operator <= (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator <= (class ::time(floatingnanosecond)); }
   //inline bool operator > (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator > (class ::time(floatingnanosecond)); }
   //inline bool operator >= (const ::FLOATING_NANOSECOND & floatingnanosecond) const { return operator >= (class ::time(floatingnanosecond)); }

   //inline bool operator == (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator == (class ::time(floatingmicrosecond)); }
   //inline bool operator != (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator != (class ::time(floatingmicrosecond)); }
   //inline bool operator < (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator < (class ::time(floatingmicrosecond)); }
   //inline bool operator <= (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator <= (class ::time(floatingmicrosecond)); }
   //inline bool operator > (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator > (class ::time(floatingmicrosecond)); }
   //inline bool operator >= (const ::FLOATING_MICROSECOND & floatingmicrosecond) const { return operator >= (class ::time(floatingmicrosecond)); }

   //inline bool operator == (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator == (class ::time(floatingmillisecond)); }
   //inline bool operator != (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator != (class ::time(floatingmillisecond)); }
   //inline bool operator < (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator < (class ::time(floatingmillisecond)); }
   //inline bool operator <= (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator <= (class ::time(floatingmillisecond)); }
   //inline bool operator > (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator > (class ::time(floatingmillisecond)); }
   //inline bool operator >= (const ::FLOATING_MILLISECOND & floatingmillisecond) const { return operator >= (class ::time(floatingmillisecond)); }

   //inline bool operator == (const ::FLOATING_SECOND & floatingsecond) const { return operator == (class ::time(floatingsecond)); }
   //inline bool operator != (const ::FLOATING_SECOND & floatingsecond) const { return operator != (class ::time(floatingsecond)); }
   //inline bool operator < (const ::FLOATING_SECOND & floatingsecond) const { return operator < (class ::time(floatingsecond)); }
   //inline bool operator <= (const ::FLOATING_SECOND & floatingsecond) const { return operator <= (class ::time(floatingsecond)); }
   //inline bool operator > (const ::FLOATING_SECOND & floatingsecond) const { return operator > (class ::time(floatingsecond)); }
   //inline bool operator >= (const ::FLOATING_SECOND & floatingsecond) const { return operator >= (class ::time(floatingsecond)); }

   //inline bool operator == (const ::FLOATING_MINUTE & minute) const { return operator == (class ::time(minute)); }
   //inline bool operator != (const ::FLOATING_MINUTE & minute) const { return operator != (class ::time(minute)); }
   //inline bool operator < (const ::FLOATING_MINUTE & minute) const { return operator < (class ::time(minute)); }
   //inline bool operator <= (const ::FLOATING_MINUTE & minute) const { return operator <= (class ::time(minute)); }
   //inline bool operator > (const ::FLOATING_MINUTE & minute) const { return operator > (class ::time(minute)); }
   //inline bool operator >= (const ::FLOATING_MINUTE & minute) const { return operator >= (class ::time(minute)); }

   //inline bool operator == (const ::FLOATING_HOUR & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::FLOATING_HOUR & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::FLOATING_HOUR & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::FLOATING_HOUR & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::FLOATING_HOUR & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::FLOATING_HOUR & day) const { return operator >= (class ::time(day)); }

   //inline bool operator == (const ::FLOATING_DAY & day) const { return operator == (class ::time(day)); }
   //inline bool operator != (const ::FLOATING_DAY & day) const { return operator != (class ::time(day)); }
   //inline bool operator < (const ::FLOATING_DAY & day) const { return operator < (class ::time(day)); }
   //inline bool operator <= (const ::FLOATING_DAY & day) const { return operator <= (class ::time(day)); }
   //inline bool operator > (const ::FLOATING_DAY & day) const { return operator > (class ::time(day)); }
   //inline bool operator >= (const ::FLOATING_DAY & day) const { return operator >= (class ::time(day)); }


   //inline bool operator == (const class time & time) const { return operator == (class ::time(FLOATING_SECOND(time.m_d))); }
   //inline bool operator != (const class time & time) const { return operator != (class ::time(FLOATING_SECOND(time.m_d))); }
   //inline bool operator < (const class time & time) const { return operator < (class ::time(FLOATING_SECOND(time.m_d))); }
   //inline bool operator <= (const class time & time) const { return operator <= (class ::time(FLOATING_SECOND(time.m_d))); }
   //inline bool operator > (const class time & time) const { return operator > (class ::time(FLOATING_SECOND(time.m_d))); }
   //inline bool operator >= (const class time & time) const { return operator >= (class ::time(FLOATING_SECOND(time.m_d))); }






   time operator %(const ::INTEGRAL_NANOSECOND & time) const { return operator % ((class ::time)time);}
   double operator /(const ::INTEGRAL_NANOSECOND & time) const { return operator / ((class ::time)time);}
   time operator +(const ::INTEGRAL_NANOSECOND & time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_NANOSECOND & time) const { return operator - ((class ::time)time); }


   time operator %(const ::INTEGRAL_MICROSECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::INTEGRAL_MICROSECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::INTEGRAL_MICROSECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_MICROSECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::INTEGRAL_MILLISECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::INTEGRAL_MILLISECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::INTEGRAL_MILLISECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_MILLISECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::INTEGRAL_SECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::INTEGRAL_SECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::INTEGRAL_SECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_SECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::INTEGRAL_MINUTE & time) const { return operator % ((class ::time)time); }
   double operator /(const ::INTEGRAL_MINUTE& time) const { return operator / ((class ::time)time); }
   time operator +(const ::INTEGRAL_MINUTE& time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_MINUTE& time) const { return operator - ((class ::time)time); }


   time operator %(const ::INTEGRAL_HOUR & time) const { return operator % ((class ::time)time); }
   double operator /(const ::INTEGRAL_HOUR& time) const { return operator / ((class ::time)time); }
   time operator +(const ::INTEGRAL_HOUR& time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_HOUR& time) const { return operator - ((class ::time)time); }


   time operator %(const ::INTEGRAL_DAY & time) const { return operator % ((class ::time)time); }
   double operator /(const ::INTEGRAL_DAY& time) const { return operator / ((class ::time)time); }
   time operator +(const ::INTEGRAL_DAY& time) const { return operator + ((class ::time)time); }
   time operator -(const ::INTEGRAL_DAY& time) const { return operator - ((class ::time)time); }









   time operator %(const ::FLOATING_NANOSECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_NANOSECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_NANOSECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_NANOSECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::FLOATING_MICROSECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_MICROSECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_MICROSECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_MICROSECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::FLOATING_MILLISECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_MILLISECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_MILLISECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_MILLISECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::FLOATING_SECOND & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_SECOND& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_SECOND& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_SECOND& time) const { return operator - ((class ::time)time); }


   time operator %(const ::FLOATING_MINUTE & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_MINUTE& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_MINUTE& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_MINUTE& time) const { return operator - ((class ::time)time); }


   time operator %(const ::FLOATING_HOUR & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_HOUR& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_HOUR& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_HOUR& time) const { return operator - ((class ::time)time); }


   time operator %(const ::FLOATING_DAY & time) const { return operator % ((class ::time)time); }
   double operator /(const ::FLOATING_DAY& time) const { return operator / ((class ::time)time); }
   time operator +(const ::FLOATING_DAY& time) const { return operator + ((class ::time)time); }
   time operator -(const ::FLOATING_DAY& time) const { return operator - ((class ::time)time); }








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








   time operator %(const ::integral_nanosecond& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_nanosecond& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_nanosecond& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_nanosecond& time) const { return operator - ((class ::time)time); }


   time operator %(const ::integral_microsecond& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_microsecond& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_microsecond& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_microsecond& time) const { return operator - ((class ::time)time); }


   time operator %(const ::integral_millisecond& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_millisecond& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_millisecond& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_millisecond& time) const { return operator - ((class ::time)time); }


   time operator %(const ::integral_second& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_second& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_second& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_second& time) const { return operator - ((class ::time)time); }


   time operator %(const ::integral_minute& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_minute& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_minute& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_minute& time) const { return operator - ((class ::time)time); }


   time operator %(const ::integral_hour& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_hour& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_hour& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_hour& time) const { return operator - ((class ::time)time); }


   time operator %(const ::integral_day& time) const { return operator % ((class ::time)time); }
   double operator /(const ::integral_day& time) const { return operator / ((class ::time)time); }
   time operator +(const ::integral_day& time) const { return operator + ((class ::time)time); }
   time operator -(const ::integral_day& time) const { return operator - ((class ::time)time); }









   time operator %(const ::floating_nanosecond& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_nanosecond& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_nanosecond& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_nanosecond& time) const { return operator - ((class ::time)time); }


   time operator %(const ::floating_microsecond& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_microsecond& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_microsecond& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_microsecond& time) const { return operator - ((class ::time)time); }


   time operator %(const ::floating_millisecond& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_millisecond& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_millisecond& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_millisecond& time) const { return operator - ((class ::time)time); }


   time operator %(const ::floating_second& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_second& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_second& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_second& time) const { return operator - ((class ::time)time); }


   time operator %(const ::floating_minute& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_minute& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_minute& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_minute& time) const { return operator - ((class ::time)time); }


   time operator %(const ::floating_hour& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_hour& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_hour& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_hour& time) const { return operator - ((class ::time)time); }


   time operator %(const ::floating_day& time) const { return operator % ((class ::time)time); }
   double operator /(const ::floating_day& time) const { return operator / ((class ::time)time); }
   time operator +(const ::floating_day& time) const { return operator + ((class ::time)time); }
   time operator -(const ::floating_day& time) const { return operator - ((class ::time)time); }




};


inline FLOATING_SECOND time() { return ::get_floating_second(); }

template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
inline time::time(enum_raw, INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

}

template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
inline time::time(enum_normalize, INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds)
{

   m_iSecond = iSeconds + iNanoseconds / 1'000'000'000;

   m_iNanosecond = iNanoseconds % 1'000'000'000;
   
   while(m_iNanosecond < 0)
   {

      m_iSecond--;

      m_iNanosecond += 1'000'000'000;

   }

}


//inline timeclass ::time(const class ::time& time) :
//   DURATION(time)
//{
//
//}


inline void time::raw_set(time_t iSeconds, long iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

}


inline void time::set(time_t iSeconds, long iNanoseconds)
{

   raw_set(iSeconds, iNanoseconds);

   normalize();

}


inline void time::set_null()
{

   raw_set(0, 0);

}


inline class ::time time::raw_create(time_t iSeconds, long iNanoseconds)
{

   time time;

   time.raw_set(iSeconds, iNanoseconds);

   return time;

}


inline class ::time time::fcreate(long double d, double dNano)
{

   time time;

   time.fset(d, dNano);

   return time;

}


inline class ::time time::create(time_t iSeconds, long iNanoseconds)
{

   time time;

   time.set(iSeconds, iNanoseconds);

   return time;

}


inline class ::time time::create_null()
{

   time time;

   time.set_null();

   return time;

}


//inline bool time::is_pos_infinity() const
//{
//
//   return m_iSecond == ::numeric_info < decltype(m_iSecond) > ::maximum();
//
//}
//

constexpr bool time::is_infinite() const
{

   return m_iSecond == ::numeric_info < decltype(m_iSecond) > ::maximum();

}


bool time::is_null() const
{

   return m_iSecond == 0 && m_iNanosecond == 0;

}


inline class ::time time::infinite()
{

   return {(::i64)MAXI64,(::i64)0};

}


//inline class ::time time::pos_infinity()
//{
//
//   return {(::i64)MAXI64, (::i64)0};
//
//}


inline class ::time time::zero()
{

   return {(::i64)0,(::i64) 0};

}


inline time_t time::GetTimeSpan() const
{

   return m_iSecond;

}


inline time::operator bool() const
{

   return m_iSecond != 0 || m_iNanosecond != 0;

}


CLASS_DECL_ACME class ::time __random(const class ::time & d1, const class ::time & d2);



//inline class ::time time::wait() const
//{
//
//   return is_infinite() ? ::time::infinite() : ::wait(m_iSecond, m_iNanosecond);
//
//}


template < primitive_floating FLOATING >
class time operator * (FLOATING d, const class time & time)
{

   auto nanosecond = d * (time.m_iSecond * 1'000'000'000.0 + time.m_iNanosecond);

   return { e_raw, (::i64)(nanosecond / 1'000'000'000.0), (long)fmod(nanosecond, 1'000'000'000.0) };

}


template < primitive_integral INTEGRAL >
class time operator * (INTEGRAL i, const class time & time)
{

   auto nanosecond = i * (time.m_iSecond * 1'000'000'000 + time.m_iNanosecond);

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


inline bool time::timeout(const class time & time)
{

   auto now = this->now();

   if (elapsed(now) < time)
   {

      return false;

   }

   operator =(now);

   return true;

}


inline class time time::remaining(const class time & time, const class time & timeNow)
{

   auto timeRemaining = time - elapsed(timeNow);

   return timeRemaining;

}





constexpr struct ::timespec & copy(struct ::timespec & timespec, const class ::time & time)
{

   timespec.tv_sec = (decltype(timespec.tv_sec))time.m_iSecond;
   timespec.tv_nsec = (decltype(timespec.tv_nsec))time.m_iNanosecond;

   return timespec;

}


constexpr struct ::timespec & add(struct ::timespec & timespec1, const struct ::timespec & timespec2)
{

   add_second_nanosecond(timespec1.tv_sec, timespec1.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);

   return timespec1;

}


constexpr struct ::timespec addition(const struct ::timespec & timespec1, const struct ::timespec & timespec2)
{

   timespec timespec = timespec1;

   add_second_nanosecond(timespec.tv_sec, timespec.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);

   return timespec;

}


constexpr struct ::timespec & subtract(struct ::timespec & timespec1, const struct ::timespec & timespec2)
{

   subtract_second_nanosecond(timespec1.tv_sec, timespec1.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);

   return timespec1;

}


constexpr struct ::timespec subtraction(const struct ::timespec & timespec1, const struct ::timespec & timespec2)
{

   timespec timespec = timespec1;

   return subtract(timespec, timespec2);

}


constexpr bool operator >(const struct ::timespec & timespec1, const struct ::timespec & timespec2)
{

   return timespec1.tv_sec > timespec2.tv_sec || (timespec1.tv_sec == timespec2.tv_sec && timespec1.tv_nsec > timespec2.tv_nsec);

}



