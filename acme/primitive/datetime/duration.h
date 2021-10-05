#pragma once


class CLASS_DECL_ACME integral_nanosecond { public: integral_nanosecond(::i64 i = 1) :m_iNanosecond(i) {} ::i64 m_iNanosecond; operator ::i64() const { return m_iNanosecond; } };
class CLASS_DECL_ACME integral_microsecond { public: integral_microsecond(::i64 i = 1) :m_iMicrosecond(i) {} ::i64 m_iMicrosecond; operator ::i64() const { return m_iMicrosecond; } };
class CLASS_DECL_ACME integral_millisecond { public: integral_millisecond(::i64 i = 1) :m_iMillisecond(i) {} ::i64 m_iMillisecond; operator ::i64() const { return m_iMillisecond; } };
class CLASS_DECL_ACME integral_second { public: integral_second(::i64 i = 1) :m_iSecond(i) {} ::i64 m_iSecond; operator ::i64() const { return m_iSecond; } };
class CLASS_DECL_ACME integral_minute { public: integral_minute(::i64 i = 1) :m_iMinute(i) {} ::i64 m_iMinute; operator ::i64() const { return m_iMinute; } };
class CLASS_DECL_ACME integral_hour { public: integral_hour(::i64 i = 1) :m_iHour(i) {} ::i64 m_iHour; operator ::i64() const { return m_iHour; } };
class CLASS_DECL_ACME integral_day { public: integral_day(::i64 i = 1) :m_iDay(i) {} ::i64 m_iDay; operator ::i64() const { return m_iDay; } };


class CLASS_DECL_ACME floating_nanosecond { public: floating_nanosecond(::f64 d) :m_dNanosecond(d) {} ::f64 m_dNanosecond; operator ::f64() const { return m_dNanosecond; } };
class CLASS_DECL_ACME floating_microsecond { public: floating_microsecond(::f64 d) :m_dMicrosecond(d) {} ::f64 m_dMicrosecond; operator ::f64() const { return m_dMicrosecond; } };
class CLASS_DECL_ACME floating_millisecond { public: floating_millisecond(::f64 d) :m_dMillisecond(d) {} ::f64 m_dMillisecond; operator ::f64() const { return m_dMillisecond; } };
class CLASS_DECL_ACME floating_second { public: floating_second(::f64 d) :m_dSecond(d) {} ::f64 m_dSecond; operator ::f64() const { return m_dSecond; } };
class CLASS_DECL_ACME floating_minute { public: floating_minute(::f64 d) :m_dMinute(d) {} ::f64 m_dMinute; operator ::f64() const { return m_dMinute; } };
class CLASS_DECL_ACME floating_hour { public: floating_hour(::f64 d) :m_dHour(d) {} ::f64 m_dHour; operator ::f64() const { return m_dHour; } };
class CLASS_DECL_ACME floating_day { public: floating_day(::f64 d) :m_dDay(d) {} ::f64 m_dDay; operator ::f64() const { return m_dDay; } };

                                      
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


   ::i64                m_iNanosecond;
   ::i64                m_iSecond;


   duration() :
      m_iSecond(0), m_iNanosecond(0)
   { }

   explicit duration(long double dSeconds);
    
   template < primitive_integral INTEGRAL >
   duration(INTEGRAL iSeconds) :
      m_iSecond(iSeconds), m_iNanosecond(0)
   {
            
        
   }

    
   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
   duration(INTEGRAL1 iSeconds, INTEGRAL2 iNanoseconds) :
      m_iSecond(iSeconds), m_iNanosecond(iNanoseconds)
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

    
   duration(enum_raw, i64 iSeconds, i64 iNanoseconds = 0);
   duration(enum_normalize, i64 iSeconds, i64 iNanoseconds);
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


   inline bool is_pos_infinity() const;
   inline bool is_infinite() const;
   inline bool is_null() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();

   void Infinite() {*this=infinite();}
   void PosInfinity() {*this=pos_infinity();}
   void Zero() {*this=zero();}
   void Null() { Zero(); }

   //duration & operator = (const ::second & second);
   //duration & operator = (const ::millisecond & millisecond);
   //duration & operator = (const ::microsecond & microsecond);
   //duration & operator = (const ::nanosecond & nanosecond);
   duration & operator = (const ::duration & duration);

   inline bool timeout(const duration & duration);
   void normalize();

   inline operator bool() const;
   
   static inline ::duration now();

   inline duration & Now() { return operator=(now()); }

   inline ::duration elapsed(const duration & duration = now()) const { return duration - *this; }

   inline duration operator - (const ::duration & duration) const { return { e_normalize, m_iSecond - duration.m_iSecond, m_iNanosecond - duration.m_iNanosecond }; }
   inline duration operator + (const ::duration & duration) const { return { e_normalize, m_iSecond + duration.m_iSecond, m_iNanosecond + duration.m_iNanosecond }; }
   inline duration & operator -= (const ::duration & duration) { m_iSecond -= duration.m_iSecond; m_iNanosecond -= duration.m_iNanosecond; normalize();  return *this; }
   inline duration & operator += (const ::duration & duration) { m_iSecond += duration.m_iSecond; m_iNanosecond += duration.m_iNanosecond; normalize();  return *this; }


   inline duration & operator = (const ::datetime::time_span & span);
   inline duration & operator += (const ::datetime::time_span & duration);
   inline duration & operator -= (const ::datetime::time_span & duration);


   inline time_t GetTimeSpan() const;


   //duration operator - (const duration & duration) const;
   //duration operator + (const duration & duration) const;


   //void sleep() const;


   ::integral_day integral_day() const { return m_iSecond / 86'400; }
   ::integral_hour integral_hour() const { return m_iSecond / 3'600; }
   ::integral_minute integral_minute() const { return m_iSecond / 60; }
   ::integral_second integral_second() const { return m_iSecond; }
   ::integral_millisecond integral_millisecond() const { return m_iSecond * 1'000 + m_iNanosecond / 1'000'000; }
   ::integral_microsecond integral_microsecond() const { return m_iSecond * 1'000'000 + m_iNanosecond / 1'000; }
   ::integral_nanosecond integral_nanosecond() const { return m_iSecond * 1'000'000'000 + m_iNanosecond; }

   ::floating_day floating_day() const { return floating_second().m_dSecond / 86'400.0; }
   ::floating_hour floating_hour() const { return floating_second().m_dSecond / 3'600.0; }
   ::floating_minute floating_minute() const { return floating_second().m_dSecond / 60.0; }
   ::floating_second floating_second() const { return (double)m_iSecond + ((double) m_iNanosecond / 1'000'000'000.0); }
   ::floating_millisecond floating_millisecond() const { return ((::f64)integral_nanosecond().m_iNanosecond) / 1'000'000.0; }
   ::floating_microsecond floating_microsecond() const { return ((::f64)integral_nanosecond().m_iNanosecond) / 1'000.0; }
   ::floating_nanosecond floating_nanosecond() const { return (::f64) integral_nanosecond().m_iNanosecond; }

};


inline duration::duration(enum_raw, ::i64 iSeconds, ::i64 iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

}


inline duration::duration(enum_normalize, ::i64 iSeconds, ::i64 iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

   normalize();

}


inline duration::duration(long double dSeconds)
{

   fset(dSeconds);

}


inline duration::duration(const ::duration& duration) :
   m_iNanosecond(duration.m_iNanosecond),
   m_iSecond(duration.m_iSecond)
{

}


inline void duration::raw_set(i64 iSeconds, i64 iNanoseconds)
{

   m_iSecond = iSeconds;

   m_iNanosecond = iNanoseconds;

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


//class CLASS_DECL_ACME nanosecond :
//   public duration
//{
//public:
//
//
//   inline nanosecond() : duration() {}
//
//    
//
//   
//    
//   template < primitive_integral INTEGRAL >
//   inline nanosecond(INTEGRAL iNanoseconds);
//
//   template < primitive_floating FLOATING >
//   inline nanosecond(FLOATING fNanoseconds);
//    
//
//
//   nanosecond(const class ::nanosecond & nanosecond) : duration(nanosecond) {}
//   nanosecond(const class ::microsecond & microsecond) : duration(microsecond) {}
//   nanosecond(const class ::millisecond & millisecond) : duration(millisecond) {}
//   nanosecond(const class ::second & second) : duration(second) {}
//   nanosecond(const class ::duration & duration) : ::duration(duration) {}
//
//
//};


//inline nanosecond operator "" _ns(unsigned long long int u) { return (::u64) u; }


//class CLASS_DECL_ACME microsecond :
//   public duration
//{
//public:
//
//
//   inline microsecond() : duration() {}
//
//
//   
//   template < primitive_integral INTEGRAL >
//   inline microsecond(INTEGRAL iMicroseconds);
//
//
//   template < primitive_floating FLOATING >
//   inline microsecond(FLOATING fMicroseconds);
//   microsecond(const class ::nanosecond & nanosecond) : duration(nanosecond) {}
//   microsecond(const class ::microsecond & microsecond) : duration(microsecond) {}
//   microsecond(const class ::millisecond & millisecond) : duration(millisecond) {}
//   microsecond(const class ::second & second) : duration(second) {}
//   microsecond(const class ::duration & duration) : ::duration(duration) {}
//
//
//};


//inline microsecond operator "" _us(unsigned long long int u) { return (::u64) u; }


//class CLASS_DECL_ACME millisecond :
//   public duration
//{
//public:
//
//
//   inline millisecond() : duration() {}
//
//
//   
//    
//   template < primitive_integral INTEGRAL >
//   inline millisecond(INTEGRAL iMillisecond);
//
//
//   template < primitive_floating FLOATING >
//   inline millisecond(FLOATING fMillisecond);
//
//
//    
//    
//   millisecond(const class ::nanosecond & nanosecond) : duration(nanosecond) {}
//   millisecond(const class ::microsecond & microsecond) : duration(microsecond) {}
//   millisecond(const class ::millisecond & millisecond) : duration(millisecond) {}
//   millisecond(const class ::second & second) : duration(second) {}
//   millisecond(const class ::duration & duration) : ::duration(duration) {}
//
//
//};
//

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


//inline seconds operator "" _s(unsigned long long int u) { return (::u64) u; }
//inline seconds operator "" _s(long double d) { return (double) d; }


//class CLASS_DECL_ACME one_second :
//   public duration
//{
//public:
//
//
//   one_second() : duration((::i64)1) {}
//
//
//};
//
//
//class CLASS_DECL_ACME minutes :
//   public duration
//{
//public:
//
//
//   inline minutes() : duration() {}
//   
//   
//
//   
//   template < primitive_integral INTEGRAL >
//   inline minutes(INTEGRAL i) : duration(i * 60) {}
//   
//
//
//   minutes(const class ::nanosecond & nanosecond) : duration(nanosecond) {}
//   minutes(const class ::microsecond & microsecond) : duration(microsecond) {}
//   minutes(const class ::millisecond & millisecond) : duration(millisecond) {}
//   minutes(const class ::second & second) : duration(second) {}
//   minutes(const class ::duration & duration) : ::duration(duration) {}
//
//
//};

//
//inline minutes operator "" _min(unsigned long long int u) { return (::u64) u; }
//
//class CLASS_DECL_ACME one_minute :
//   public duration
//{
//public:
//
//
//   one_minute() : duration((::i64)60) {}
//
//
//};
//
//
//class CLASS_DECL_ACME hours :
//   public duration
//{
//public:
//
//
//   inline hours() : duration() {}
//
//
//
//   
//
//   template < primitive_integral INTEGRAL1 >
//   inline hours(INTEGRAL1 iHours);
//
//   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
//   inline hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes);
//
//   template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3 >
//   inline hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes, INTEGRAL3 iSeconds);
//
//   template < primitive_floating FLOATING >
//   inline hours(FLOATING fHours);
//
//   
//   
//
//   hours(const class ::nanosecond & nanosecond) : duration(nanosecond) {}
//   hours(const class ::microsecond & microsecond) : duration(microsecond) {}
//   hours(const class ::millisecond & millisecond) : duration(millisecond) {}
//   hours(const class ::second & second) : duration(second) {}
//   hours(const class ::duration & duration) : ::duration(duration) {}
//
//
//};


//inline ::duration operator "" _hours(unsigned long long int u) { return (::i64) u; }
//inline ::duration operator "" _hour(unsigned long long int u) { return (::i64) u; }


//class CLASS_DECL_ACME one_hour :
//   public hours
//{
//public:
//
//
//   one_hour(int iMinutes = 0, int iSeconds = 0) : hours((::i64)1, (::i64) iMinutes, (::i64)iSeconds) {}
//
//
//};


//class CLASS_DECL_ACME days :
//   public duration
//{
//public:
//
//
//
//   inline days() : duration(){}
//
//
//   
//   template < primitive_integral INTEGRAL >
//   inline days(INTEGRAL iDays);
//
//
//   template < primitive_floating FLOATING >
//   inline days(FLOATING fDays);
//
//   
//   
//   days(const class ::nanosecond & nanosecond) : duration(nanosecond) {}
//   days(const class ::microsecond & microsecond) : duration(microsecond) {}
//   days(const class ::millisecond & millisecond) : duration(millisecond) {}
//   days(const class ::second & second) : duration(second) {}
//   days(const class ::duration & duration) : ::duration(duration) {}
//
//
//};
//
//
//inline days operator "" _days(unsigned long long int u) { return (::i64) u; }
//inline days operator "" _day(unsigned long long int u) { return (::i64) u; }
//




//template < primitive_integral INTEGRAL >
//inline nanosecond::nanosecond(INTEGRAL i) :
//   duration(i / (1'000'000'000), (i % (1'000'000'000)))
//{
//
//}


//template < primitive_integral INTEGRAL >
//inline microsecond::microsecond(INTEGRAL i) :
//   duration(i / (1'000'000), (i % (1'000'000)) * 1'000)
//{
//
//}

//
//template < primitive_integral INTEGRAL1 >
//inline hours::hours(INTEGRAL1 iHours) :
//   duration(iHours * 3600)
//{
//
//}
//
//
//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
//inline hours::hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes) :
//   duration(iHours * 3600 + iMinutes * 60)
//{
//
//}
//
//
//template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL3 >
//inline hours::hours(INTEGRAL1 iHours, INTEGRAL2 iMinutes, INTEGRAL3 iSeconds) :
//   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
//{
//
//}
//
//
//template < primitive_floating FLOATING >
//inline hours::hours(FLOATING d) :
//   duration(d * 3600.0)
//{
//
//}
//
//
//template < primitive_integral INTEGRAL >
//inline days::days(INTEGRAL i) :
//   duration(i * 86400)
//{
//
//}
//
//
//template < primitive_floating FLOATING >
//inline days::days(FLOATING d) :
//   duration(d * 86400.0)
//{
//
//}
//

inline time_t duration::GetTimeSpan() const
{

   return m_iSecond;

}


//inline ::second duration::second() const
//{
//
//   return m_iSecond;
//
//}

//
//inline double duration::seconds() const
//{
//
//   return (double) m_iSecond + m_iNanosecond / 1'000'000'000.0;
//
//}


inline duration::operator bool() const
{

   return m_iSecond != 0 || m_iNanosecond != 0;

}


//CLASS_DECL_ACME void sleep(const duration & duration);


inline bool operator == (const duration & duration1, const ::duration & duration2) { return duration1.m_iSecond == duration2.m_iSecond && duration1.m_iNanosecond == duration2.m_iSecond; }
inline bool operator != (const duration & duration1, const ::duration & duration2) { return !(duration1 == duration2); }
inline bool operator < (const duration & duration1, const ::duration & duration2) { return duration1.m_iSecond < duration2.m_iSecond || (duration1.m_iSecond == duration2.m_iSecond && duration1.m_iNanosecond < duration2.m_iNanosecond); }
inline bool operator <= (const duration & duration1, const ::duration & duration2) { return duration1.m_iSecond < duration2.m_iSecond || (duration1.m_iSecond == duration2.m_iSecond && duration1.m_iNanosecond <= duration2.m_iNanosecond); }
inline bool operator > (const duration & duration1, const ::duration & duration2) { return !(duration1 <= duration2); }
inline bool operator >= (const duration & duration1, const ::duration & duration2) { return !(duration1 <= duration2); }


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


//inline bool millisecond::operator == (const ::duration& duration) const { return m_i == duration.millisecond().m_i; }
//inline bool millisecond::operator != (const ::duration& duration) const { return m_i != duration.millisecond().m_i; }
//inline bool millisecond::operator < (const ::duration& duration) const { return m_i < duration.millisecond().m_i; }
//inline bool millisecond::operator <= (const ::duration& duration) const { return m_i <= duration.millisecond().m_i; }
//inline bool millisecond::operator > (const ::duration& duration) const { return m_i > duration.millisecond().m_i; }
//inline bool millisecond::operator >= (const ::duration& duration) const { return m_i >= duration.millisecond().m_i; }
//inline millisecond millisecond::operator - (const ::duration& duration) const { return m_i - duration.millisecond().m_i; }
//inline millisecond millisecond::operator + (const ::duration& duration) const { return m_i + duration.millisecond().m_i; }
//inline millisecond& millisecond::operator -= (const ::duration& duration) { m_i -= duration.millisecond().m_i; return *this; }
//inline millisecond& millisecond::operator += (const ::duration& duration) { m_i += duration.millisecond().m_i; return *this; }


CLASS_DECL_ACME duration __random(const duration & d1, const duration & d2);

//
//inline second::second(const duration & duration) { m_i = duration.m_iSecond; }
//inline millisecond::millisecond(const duration & duration) { m_i = duration.millisecond().m_i; }
//inline microsecond::microsecond(const duration & duration) { m_i = duration.microsecond().m_i; }
//inline nanosecond::nanosecond(const duration & duration) { m_i = duration.nanosecond().m_i;  }


//#ifdef WINDOWS
//
//inline u32 __os(const ::duration & duration) { return duration.u32_millis(); }
//
//#endif





//template < primitive_floating FLOATING >
//inline nanosecond::nanosecond(FLOATING fNanos) :
//   duration((i64)(fNanos / (1'000'000'000.0)), (i64)fmod(fNanos, 1'000'000'000.0))
//{
//
//}


//template < primitive_floating FLOATING >
//inline microsecond::microsecond(FLOATING fMicroseconds) :
//   duration((i64)(fMicroseconds / 1'000'000.0), (i64)fmod(fMicroseconds * 1'000.0, 1'000'000'000.0))
//{
//
//}


//template < primitive_floating FLOATING >
//inline millisecond::millisecond(FLOATING fMilliseconds) :
//   duration((i64)(fMilliseconds / 1'000.0), (i64)fmod(fMilliseconds * 1'000'000.0, 1'000'000'000.0))
//{
//
//}





//inline ::duration day(unsigned long long u) { return ::duration(e_raw, u * 86400); }
//inline ::duration day(double d) { return ::duration(e_raw, (::i64)d * 86400.0, (::i64)(fmod(d * 86400.0, 1.0) * 1'000'000'000.0)); }
//
//inline ::duration hour(unsigned long long u) { return ::duration(e_raw, u * 3600); }
//inline ::duration hour(double d) { return ::duration(e_raw, (::i64)d * 3600.0, (::i64)(fmod(d * 3600.0, 1.0) * 1'000'000'000.0)); }
//
//inline ::duration minute(unsigned long long u) { return ::duration(e_raw, u * 60); }
//inline ::duration minute(double d) { return ::duration(e_raw, (::i64)d * 60.0, (::i64)(fmod(d * 60.0, 1.0) * 1'000'000'000.0)); }
//
//inline ::duration second(unsigned long long u) { return ::duration(e_raw, u); }
//inline ::duration second(double d) { return ::duration(e_raw, (::i64)d, (::i64)(fmod(d, 1.0) * 1'000'000'000.0)); }
//
//inline ::duration millisecond(unsigned long long u) { return ::duration(e_raw, u / 1'000, (u % 1'000) * 1'000'000); }
//inline ::duration millisecond(double d) { return ::duration(e_raw, (::i64)(d / 1'000.0), (::i64)(fmod(d, 1'000.0) * 1'000'000.0)); }
//
//inline ::duration microsecond(unsigned long long u) { return ::duration(e_raw, u / 1'000'000, (u % 1'000'000) * 1'000); }
//inline ::duration microsecond(double d) { return ::duration(e_raw, (::i64)(d / 1'000'000.0), (::i64)(fmod(d, 1'000'000.0) * 1'000.0)); }
//
//inline ::duration nanosecond(unsigned long long u) { return ::duration(e_raw, u / 1'000'000'000, (u % 1'000'000'000)); }
//inline ::duration nanosecond(double d) { return ::duration(e_raw, (::i64)(d / 1'000'000'000.0), (::i64)(fmod(d, 1'000'000'000.0))); }









