// Refactoring by camilo on 2021-10-05 12:46 BRT <3ThomasBorregaardS�rensen!!
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
   duration(const ::INTEGRAL_SECOND & integral) : duration(e_raw, (::i64)integral.m_i) {}
   duration(const ::FLOATING_SECOND & floating) : duration(e_raw, (::i64)(floating.m_d), (long)(fmod(floating.m_d, 1.0) * 1'000'000'000.0)) {}
   duration(const ::INTEGRAL_MINUTE & integral) : duration(e_raw, integral.m_i * 60) {}
   duration(const ::FLOATING_MINUTE & floating) : duration(e_raw, (::i64)(floating.m_d * 60.0), (long)(fmod(floating.m_d * 60.0, 1.0) * 1'000'000'000.0)) {}
   duration(const ::INTEGRAL_HOUR & integral) : duration(e_raw, integral.m_i * 3'600) {}
   duration(const ::FLOATING_HOUR & floating) : duration(e_raw, (::i64)(floating.m_d * 3'600.0), (long)(fmod(floating.m_d * 3'600.0, 1.0) * 1'000'000'000.0)) {}
   duration(const ::INTEGRAL_DAY & integral) : duration::duration(e_raw, integral.m_i * 86'400) {}
   duration(const ::FLOATING_DAY & floating) : duration(e_raw, (::i64)(floating.m_d * 86'400.0), (long)(fmod(floating.m_d * 86'400.0, 1.0) * 1'000'000'000.0)) {}


   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   duration(INTEGRAL1 iSecond, INTEGRAL2 iNanosecond) :
      DURATION{ .m_iSecond = (time_t)iSecond, .m_iNanosecond = (long)iNanosecond }
   {


   }


   template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
    duration(FLOATING1 fSeconds, FLOATING2 fNanoseconds)
   {
        
       fset(fSeconds, fNanoseconds);
        
   }


   duration(enum_raw, time_t iSeconds, long iNanoseconds = 0);
   duration(enum_normalize, time_t iSeconds, long iNanoseconds);
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
   static inline class ::duration now() { duration duration; duration.Now(); return duration; }

   inline class ::duration & Now() { if (timespec_get((timespec *)this, TIME_UTC) != TIME_UTC) throw "timespec_get failed!!"; return *this; }

   inline class ::duration elapsed(const class ::duration & duration = now()) const { return duration - *this; }

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


   operator ::wait() const;


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


   duration operator %(const ::duration & duration) const;
   double operator /(const ::duration & duration) const;
   //integral_duration operator *(const ::duration & duration) const { return BASE_TYPE(this->m_i * duration.m_i); }
   duration operator +(const ::duration & duration) const { return { e_normalize, this->m_iSecond + duration.m_iSecond, this->m_iNanosecond + duration.m_iNanosecond }; }
   duration operator -(const ::duration & duration) const { return { e_normalize, this->m_iSecond - duration.m_iSecond, this->m_iNanosecond - duration.m_iNanosecond }; }

   duration operator -() const { return { e_raw, -m_iSecond, -m_iNanosecond }; }

   duration operator %(const ::INTEGRAL_NANOSECOND & integral) const { return operator %(::duration(integral)); }
   double operator /(const ::INTEGRAL_NANOSECOND & integral) const { return operator /(::duration(integral)); }
   //integral_duration operator *(const ::INTEGRAL_NANOSECOND & integral) const { return BASE_TYPE(this->m_i * duration.m_i); }
   duration operator +(const ::INTEGRAL_NANOSECOND & integral) const { return operator +(::duration(integral)); }
   duration operator -(const ::INTEGRAL_NANOSECOND & integral) const { return operator -(::duration(integral)); }


};


inline double time() { return duration(e_now).floating_second().m_d; }


inline duration::duration(enum_raw, ::time_t iSeconds, long iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

}


inline duration::duration(enum_normalize, ::time_t iSeconds, long iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

   normalize();

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

   return m_iSecond == MAXI64;

}


inline bool duration::is_infinite() const
{

   return m_iSecond == MAXI64;

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

   return INTEGRAL_MILLISECOND(is_infinite() ? INT64_MAX : integral_millisecond().m_i);

}



class CLASS_DECL_ACME frequency
{
public:

   
   double m_d; // Hz


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

   return (double)(i * 1'000'000'000) / (double)nanosecond;

}


template < primitive_integral INTEGRAL >
class ::duration operator * (INTEGRAL i, const ::duration & duration)
{

   auto nanosecond = i * (duration.m_iSecond * 1'000'000'000 + duration.m_iNanosecond);

   return { e_raw, (::i64)(nanosecond / 1'000'000'000), (long)(nanosecond % 1'000'000'000) };

}
