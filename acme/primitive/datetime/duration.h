#pragma once


class CLASS_DECL_ACME duration
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


   ::nanos           m_nanos;
   ::secs            m_secs;


   duration() :
      m_secs(), m_nanos(0)
   { }

   explicit duration(long double dSeconds);
    
    
#ifdef CPP20
    

    template < primitive_integral INTEGRAL >
    duration(INTEGRAL iSeconds) :
        m_secs(iSeconds), m_nanos(0)
    {
            
        
    }

    
    template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
    duration(INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds) :
        m_secs(iSeconds), m_nanos(iNanoseconds)
    {
          
          
    }

    
    template < primitive_floating FLOATING >
    duration(FLOATING fSeconds)
    {
           
        fset(fSeconds);
           
    }
    

   template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
    duration(FLOATING1 fSeconds, FLOATING2 fNanoseconds)
   {
        
       fset(fSeconds, fNanoseconds);
        
   }

    
#else
    

    duration(::i64 iSeconds) :
       m_secs(iSeconds), m_nanos(0)
    { }


    duration(::i64 iSeconds, ::i64 iNanoseconds) :
       m_secs(iSeconds), m_nanos(iNanoseconds)
    { }

    
    duration(double dSeconds)
    {
        
        fset(dSeconds);
        
    }


    duration(double dSeconds, double dNanoseconds)
    {
           
        fset(dSeconds, dNanoseconds);
           
    }

    
#endif

    
   duration(enum_normalize, i64 iSeconds, i64 iNanoseconds);
   duration(const class ::nanos & nanos);
   duration(const class ::micros & micros);
   duration(const class ::millis & millis);
   duration(const class ::secs & secs);
   duration(const class ::duration & duration);


   inline void raw_set(i64 iSeconds, i64 iNanoseconds = 0);
   inline void set(i64 iSeconds, i64 iNanoseconds);
   inline void set_null();
   static inline duration raw_create(i64 iSeconds, i64 iNanoseconds);
   static inline duration create(i64 iSeconds, i64 iNanoseconds);
   static inline duration create_null();


   void fset(long double dSeconds);
   void fset(long double dSeconds, double dNanoseconds);
   static inline duration fcreate(long double dSeconds, double dNanoseconds);


   void set(i64 i, enum_unit eunit);
   void set(long double d, enum_unit eunit);


   inline ::nanos nanos() const;
   inline ::micros micros() const;
   inline ::millis millis() const;
   inline ::secs secs() const;
   inline ::u32 u32_millis() const;
   inline bool is_pos_infinity() const;
   inline bool is_infinite() const;
   inline bool is_null() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();

   void Infinite() {*this=infinite();}
   void PosInfinity() {*this=pos_infinity();}
   void Zero() {*this=zero();}

   duration & operator = (const ::secs & secs);
   duration & operator = (const ::millis & millis);
   duration & operator = (const ::micros & micros);
   duration & operator = (const ::nanos & nanos);
   duration & operator = (const ::duration & duration);


   void normalize();


   inline operator bool() const;


   inline duration operator - (const ::duration & duration) const { return { e_normalize, m_secs.m_i - duration.m_secs.m_i, m_nanos.m_i - duration.m_nanos.m_i }; }
   inline duration operator + (const ::duration & duration) const { return { e_normalize, m_secs.m_i + duration.m_secs.m_i, m_nanos.m_i + duration.m_nanos.m_i }; }
   inline duration & operator -= (const ::duration & duration) { m_secs.m_i -= duration.m_secs.m_i; m_nanos.m_i -= duration.m_nanos.m_i; normalize();  return *this; }
   inline duration & operator += (const ::duration & duration) { m_secs.m_i += duration.m_secs.m_i; m_nanos.m_i += duration.m_nanos.m_i; normalize();  return *this; }


   inline duration & operator = (const ::datetime::time_span & span);
   inline duration & operator += (const ::datetime::time_span & duration);
   inline duration & operator -= (const ::datetime::time_span & duration);


   inline time_t GetTimeSpan() const;


   //duration operator - (const duration & duration) const;
   //duration operator + (const duration & duration) const;


   void sleep() const;


};


inline duration::duration(enum_normalize, ::i64 iSeconds, ::i64 iNanoseconds)
{

   m_secs.m_i = iSeconds;

   m_nanos.m_i = iNanoseconds;

   normalize();

}


inline duration::duration(long double dSeconds)
{

   fset(dSeconds);

}


inline duration::duration(const ::duration& duration) :
   m_nanos(duration.m_nanos),
   m_secs(duration.m_secs)
{

}


inline void duration::raw_set(i64 iSeconds, i64 iNanoseconds)
{

   m_secs.m_i = iSeconds;

   m_nanos.m_i = iNanoseconds;

}


inline void duration::set(i64 iSeconds, i64 iNanoseconds)
{

   raw_set(iSeconds, iNanoseconds);

   normalize();

}


inline void duration::set_null()
{

   raw_set(0, 0);

}


inline duration duration::raw_create(i64 iSeconds, i64 iNanoseconds)
{

   duration duration;

   duration.raw_set(iSeconds, iNanoseconds);

   return duration;

}


inline duration duration::fcreate(long double d, double dNano)
{

   duration duration;

   duration.fset(d, dNano);

   return duration;

}


inline duration duration::create(i64 iSeconds, i64 iNanoseconds)
{

   duration duration;

   duration.set(iSeconds, iNanoseconds);

   return duration;

}


inline duration duration::create_null()
{

   duration duration;

   duration.set_null();

   return duration;

}


inline ::millis duration::millis() const
{

   if(m_secs.m_i >= (MAXI64 / 1000))
   {

      return MAXI64;

   }
   else if(m_secs.m_i <= (MINI64 / 1000))
   {

      return MINI64;

   }
   else
   {

      return m_secs.m_i * 1000 + m_nanos.m_i / 1000000;

   }

}


inline ::u32 duration::u32_millis() const
{

   return is_infinite() ? UINT_MAX : (::u32) minimum((::i64) UINT_MAX, millis().m_i);

}


inline ::micros duration::micros() const
{

   return m_secs.m_i * 1000000 + m_nanos.m_i / 1000;

}


inline nanos duration::nanos() const
{

   return m_nanos.m_i + m_secs.m_i * 1'000'000'000;

}


inline bool duration::is_pos_infinity() const
{

   return m_secs.m_i == MAXI64;

}


inline bool duration::is_infinite() const
{

   return m_secs.m_i == MAXI64;

}


bool duration::is_null() const
{

   return m_secs.m_i == 0 && m_nanos.m_i == 0;

}


inline duration duration::infinite()
{

   return {(::i64)MAXI64,(::i64)0};

}


inline duration duration::pos_infinity()
{

   return {(::i64)MAXI64, (::i64)0};

}


inline duration duration::zero()
{

   return {(::i64)0,(::i64) 0};

}


class CLASS_DECL_ACME nanosecond :
   public duration
{
public:


   inline nanosecond() : duration() {}

    
#ifdef CPP20
   
    
   template < primitive_integral INTEGRAL >
   inline nanosecond(INTEGRAL iNanoseconds);

   template < primitive_floating FLOATING >
   inline nanosecond(FLOATING fNanoseconds);
    
#else
    
    
   inline nanosecond(::i64 iNanoseconds);

   inline nanosecond(double fNanoseconds);

    
#endif

   nanosecond(const class ::nanos & nanos) : duration(nanos) {}
   nanosecond(const class ::micros & micros) : duration(micros) {}
   nanosecond(const class ::millis & millis) : duration(millis) {}
   nanosecond(const class ::secs & secs) : duration(secs) {}
   nanosecond(const class ::duration & duration) : ::duration(duration) {}


};


//inline nanosecond operator "" _ns(unsigned long long int u) { return (::u64) u; }


class CLASS_DECL_ACME microsecond :
   public duration
{
public:


   inline microsecond() : duration() {}

#ifdef CPP20
   
   template < primitive_integral INTEGRAL >
   inline microsecond(INTEGRAL iMicroseconds);


   template < primitive_floating FLOATING >
   inline microsecond(FLOATING fMicroseconds);

#else
    
    inline microsecond(::i64 iMicroseconds);


    inline microsecond(double fMicroseconds);

    
#endif

   microsecond(const class ::nanos & nanos) : duration(nanos) {}
   microsecond(const class ::micros & micros) : duration(micros) {}
   microsecond(const class ::millis & millis) : duration(millis) {}
   microsecond(const class ::secs & secs) : duration(secs) {}
   microsecond(const class ::duration & duration) : ::duration(duration) {}


};


//inline micros operator "" _us(unsigned long long int u) { return (::u64) u; }


class CLASS_DECL_ACME millisecond :
   public duration
{
public:


   inline millisecond() : duration() {}

#ifdef CPP20
   
    
   template < primitive_integral INTEGRAL >
   inline millisecond(INTEGRAL iMillisecond);


   template < primitive_floating FLOATING >
   inline millisecond(FLOATING fMillisecond);

#else
    
   inline millisecond(::i64 iMillisecond);


   inline millisecond(double fMillisecond);

    
#endif
    
    
   millisecond(const class ::nanos & nanos) : duration(nanos) {}
   millisecond(const class ::micros & micros) : duration(micros) {}
   millisecond(const class ::millis & millis) : duration(millis) {}
   millisecond(const class ::secs & secs) : duration(secs) {}
   millisecond(const class ::duration & duration) : ::duration(duration) {}


};


//
//const char *
//unsigned long long int
//long double
//char
//wchar_t
//char16_t
//char32_t
//const char *, std::size_t
//const wchar_t *, std::size_t
//const char16_t *, std::size_t
//const char32_t *, std::size_t





inline duration::duration(const ::millis & millis)
{

    m_secs.m_i = millis.m_i / 1'000;

    m_nanos.m_i = (millis.m_i % 1'000) * 1'000'000;

}


inline duration::duration(const ::secs & secs)
{

   m_secs = secs;

   m_nanos = 0;

}


inline  duration::duration(const ::micros & micros)
{

    m_secs.m_i = micros.m_i / 1'000'000;

    m_nanos.m_i = (micros.m_i % 1'000'000) * 1'000;

}


inline  duration::duration(const ::nanos & nanos)
{

    m_secs = nanos.m_i / 1'000'000'000;

    m_nanos = nanos.m_i % 1'000'000'000;

}


class CLASS_DECL_ACME seconds :
   public duration
{
public:


   inline seconds() : duration() {}


#ifdef CPP20
   
    
   template < primitive_integral INTEGRAL >
   inline seconds(INTEGRAL iSeconds) : duration(iSeconds) { }

   template < primitive_floating FLOATING >
   inline seconds(FLOATING fSeconds) : duration(fSeconds) { }
    
    
#else
    
    inline seconds(::i64 iSeconds) : duration(iSeconds) { }

    inline seconds(double fSeconds) : duration(fSeconds) { }
    
#endif
    
    
   seconds(const class ::nanos & nanos) : duration(nanos) {}
   seconds(const class ::micros & micros) : duration(micros) {}
   seconds(const class ::millis & millis) : duration(millis) {}
   seconds(const class ::secs & secs) : duration(secs) {}
   seconds(const class ::duration & duration) : ::duration(duration) {}



};


//inline seconds operator "" _s(unsigned long long int u) { return (::u64) u; }
inline seconds operator "" _s(long double d) { return (double) d; }


class CLASS_DECL_ACME one_second :
   public duration
{
public:


   one_second() : duration((::i64)1) {}


};


class CLASS_DECL_ACME minutes :
   public duration
{
public:


   inline minutes() : duration() {}
   
   
#ifdef CPP20
   
   template < primitive_integral INTEGRAL >
   inline minutes(INTEGRAL i) : duration(i) {}
   
#else
   
   inline minutes(::i64 i) : duration(i) {}

#endif

   minutes(const class ::nanos & nanos) : duration(nanos) {}
   minutes(const class ::micros & micros) : duration(micros) {}
   minutes(const class ::millis & millis) : duration(millis) {}
   minutes(const class ::secs & secs) : duration(secs) {}
   minutes(const class ::duration & duration) : ::duration(duration) {}


};


inline minutes operator "" _min(unsigned long long int u) { return (::u64) u; }

class CLASS_DECL_ACME one_minute :
   public duration
{
public:


   one_minute() : duration((::i64)60) {}


};


class CLASS_DECL_ACME hours :
   public duration
{
public:


   inline hours() : duration() {}


#ifdef CPP20
   

   template < primitive_integral INTEGRAL1 >
   inline hours(INTEGRAL1 iHours);

   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   inline hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes);

   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3 >
   inline hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes, INTEGRAL3 iSeconds);

   template < primitive_floating FLOATING >
   inline hours(FLOATING fHours);

   
#else
   
   
   inline hours(::i64 iHours);

   inline hours(::i64 iHours, ::i64 iMinutes);

   inline hours(::i64 iHours, ::i64 iMinutes, ::i64 iSeconds);

   inline hours(double dHours);

   
#endif
   

   hours(const class ::nanos & nanos) : duration(nanos) {}
   hours(const class ::micros & micros) : duration(micros) {}
   hours(const class ::millis & millis) : duration(millis) {}
   hours(const class ::secs & secs) : duration(secs) {}
   hours(const class ::duration & duration) : ::duration(duration) {}


};


inline hours operator "" _hours(unsigned long long int u) { return (::i64) u; }
inline hours operator "" _hour(unsigned long long int u) { return (::i64) u; }

class CLASS_DECL_ACME one_hour :
   public hours
{
public:


   one_hour(int iMinutes = 0, int iSeconds = 0) : hours((::i64)1, (::i64) iMinutes, (::i64)iSeconds) {}


};


class CLASS_DECL_ACME days :
   public duration
{
public:



   inline days() : duration(){}

#ifdef CPP20
   
   template < primitive_integral INTEGRAL >
   inline days(INTEGRAL iDays);


   template < primitive_floating FLOATING >
   inline days(FLOATING fDays);
   
   
#else
   
   
   inline days(::i64 iDays);


   inline days(double dDays);
   

#endif
   
   
   days(const class ::nanos & nanos) : duration(nanos) {}
   days(const class ::micros & micros) : duration(micros) {}
   days(const class ::millis & millis) : duration(millis) {}
   days(const class ::secs & secs) : duration(secs) {}
   days(const class ::duration & duration) : ::duration(duration) {}


};


inline days operator "" _days(unsigned long long int u) { return (::i64) u; }
inline days operator "" _day(unsigned long long int u) { return (::i64) u; }


#ifdef CPP20


template < primitive_integral INTEGRAL >
inline nanosecond::nanosecond(INTEGRAL i) :
   duration(i / (1'000'000'000), (i % (1'000'000'000)))
{

}


template < primitive_integral INTEGRAL >
inline microsecond::microsecond(INTEGRAL i) :
   duration(i / (1'000'000), (i % (1'000'000)) * 1'000)
{

}


template < primitive_integral INTEGRAL1 >
inline hours::hours(INTEGRAL1 iHours) :
   duration(iHours * 3600)
{

}


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
inline hours::hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes) :
   duration(iHours * 3600 + iMinutes * 60)
{

}


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3 >
inline hours::hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes, INTEGRAL3 iSeconds) :
   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
{

}


template < primitive_floating FLOATING >
inline hours::hours(FLOATING d) :
   duration(d * 3600.0)
{

}


template < primitive_integral INTEGRAL >
inline days::days(INTEGRAL i) :
   duration(i * 86400)
{

}


template < primitive_floating FLOATING >
inline days::days(FLOATING d) :
   duration(d * 86400.0)
{

}


#else




inline nanosecond::nanosecond(::i64 i) :
   duration(i / (1'000'000'000), (i % (1'000'000'000)))
{

}


inline microsecond::microsecond(::i64 i) :
   duration(i / (1'000'000), (i % (1'000'000)) * 1'000)
{

}


inline hours::hours(::i64 iHours) :
   duration(iHours * 3600)
{

}


inline hours::hours(::i64 iHours, ::i64 iMinutes) :
   duration(iHours * 3600 + iMinutes * 60)
{

}


inline hours::hours(::i64 iHours, ::i64 iMinutes, ::i64 iSeconds) :
   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
{

}


inline hours::hours(double d) :
   duration(d * 3600.0)
{

}


inline days::days(::i64 i) :
   duration(i * 86400)
{

}


inline days::days(double d) :
   duration(d * 86400.0)
{

}


#endif


inline time_t duration::GetTimeSpan() const
{

   return m_secs.m_i;

}


inline ::secs duration::secs() const
{

   return m_secs.m_i;

}


inline duration::operator bool() const
{

   return m_secs.m_i != 0 || m_nanos.m_i != 0;

}


//CLASS_DECL_ACME void sleep(const duration & duration);


inline bool operator == (const duration & duration1, const ::duration & duration2) { return duration1.m_secs.m_i == duration2.m_secs.m_i && duration1.m_nanos.m_i == duration2.m_secs.m_i; }
inline bool operator != (const duration & duration1, const ::duration & duration2) { return !(duration1 == duration2); }
inline bool operator < (const duration & duration1, const ::duration & duration2) { return duration1.m_secs.m_i < duration2.m_secs.m_i || (duration1.m_secs.m_i == duration2.m_secs.m_i && duration1.m_nanos.m_i < duration2.m_nanos.m_i); }
inline bool operator <= (const duration & duration1, const ::duration & duration2) { return duration1.m_secs.m_i < duration2.m_secs.m_i || (duration1.m_secs.m_i == duration2.m_secs.m_i && duration1.m_nanos.m_i <= duration2.m_nanos.m_i); }
inline bool operator > (const duration & duration1, const ::duration & duration2) { return !(duration1 <= duration2); }
inline bool operator >= (const duration & duration1, const ::duration & duration2) { return !(duration1 <= duration2); }


//inline bool CLASS_DECL_ACME operator >(const duration & duration1, const duration & duration2)
//{
//
//   auto iCompare = duration1.m_secs.m_i - duration2.m_secs.m_i;
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
//      return duration1.m_secs.m_i > duration2.m_secs.m_i;
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
//   auto iCompare = duration1.m_secs.m_i - duration2.m_secs.m_i;
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
//      return duration1.m_secs.m_i < duration2.m_secs.m_i;
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


//inline bool millis::operator == (const ::duration& duration) const { return m_i == duration.millis().m_i; }
//inline bool millis::operator != (const ::duration& duration) const { return m_i != duration.millis().m_i; }
//inline bool millis::operator < (const ::duration& duration) const { return m_i < duration.millis().m_i; }
//inline bool millis::operator <= (const ::duration& duration) const { return m_i <= duration.millis().m_i; }
//inline bool millis::operator > (const ::duration& duration) const { return m_i > duration.millis().m_i; }
//inline bool millis::operator >= (const ::duration& duration) const { return m_i >= duration.millis().m_i; }
//inline millis millis::operator - (const ::duration& duration) const { return m_i - duration.millis().m_i; }
//inline millis millis::operator + (const ::duration& duration) const { return m_i + duration.millis().m_i; }
//inline millis& millis::operator -= (const ::duration& duration) { m_i -= duration.millis().m_i; return *this; }
//inline millis& millis::operator += (const ::duration& duration) { m_i += duration.millis().m_i; return *this; }


CLASS_DECL_ACME duration __random(const duration & d1, const duration & d2);


inline secs::secs(const duration & duration) { m_i = duration.m_secs.m_i; }
inline millis::millis(const duration & duration) { m_i = duration.millis().m_i; }
inline micros::micros(const duration & duration) { m_i = duration.micros().m_i; }
inline nanos::nanos(const duration & duration) { m_i = duration.nanos().m_i;  }


#ifdef WINDOWS

inline u32 __os(const ::duration & duration) { return duration.u32_millis(); }

#endif


#ifdef CPP20


template < primitive_floating FLOATING >
inline nanosecond::nanosecond(FLOATING fNanos) :
   duration((i64)(fNanos / (1'000'000'000.0)), (i64)fmod(fNanos, 1'000'000'000.0))
{

}


template < primitive_floating FLOATING >
inline microsecond::microsecond(FLOATING fMicroseconds) :
   duration((i64)(fMicroseconds / 1'000'000.0), (i64)fmod(fMicroseconds * 1'000.0, 1'000'000'000.0))
{

}


template < primitive_floating FLOATING >
inline millisecond::millisecond(FLOATING fMilliseconds) :
   duration((i64)(fMilliseconds / 1'000.0), (i64)fmod(fMilliseconds * 1'000'000.0, 1'000'000'000.0))
{

}


#else


inline nanosecond::nanosecond(double dNanos) :
   duration((i64)(dNanos / (1'000'000'000.0)), (i64)fmod(dNanos, 1'000'000'000.0))
{

}


inline microsecond::microsecond(double dMicroseconds) :
   duration((i64)(dMicroseconds / 1'000'000.0), (i64)fmod(dMicroseconds * 1'000.0, 1'000'000'000.0))
{

}


inline millisecond::millisecond(double dMilliseconds) :
   duration((i64)(dMilliseconds / 1'000.0), (i64)fmod(dMilliseconds * 1'000'000.0, 1'000'000'000.0))
{

}


#endif



