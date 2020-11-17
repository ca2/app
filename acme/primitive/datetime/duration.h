#pragma once


class CLASS_DECL_ACME duration
{
public:


   enum e_duration
   {

      duration_finite,
      duration_dirac,
      duration_infinite,

   };


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


   e_duration     m_eduration;
   ::i64          m_iNanoseconds;
   ::i64          m_iSeconds;


   explicit duration(long double dSeconds);
   duration(i64 iSeconds = 0, i64 iNanoseconds = 0);
   duration(u64 uSeconds, i64 iNanoseconds = 0) : duration((::i64) uSeconds, iNanoseconds) {}
   duration(i32 iSeconds, i64 iNanoseconds = 0) : duration((::i64) iSeconds, iNanoseconds) {}
   duration(u32 uSeconds, i64 iNanoseconds = 0) : duration((::i64) uSeconds, iNanoseconds) {}
   duration(e_duration eduration);
   duration(const class ::nanos & nanos);
   duration(const class ::millis & millis);
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


   //inline i64 get_total_nanoseconds() const;
   //inline i64 total_nanoseconds() const;
   //inline micros micros() const;
   //inline i64 total_microseconds() const;
   //inline i64 get_total_milliseconds() const;
   //inline i64 total_milliseconds() const;
   inline i64 get_total_seconds() const;
   inline i64 total_seconds() const;
   inline bool is_pos_infinity() const;
   inline bool is_infinite() const;
   inline bool is_null() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   inline bool operator == (const duration & duration) const;
   duration & operator = (const ::duration & tick);


   void normalize();


   inline class millis millis() const;
   //inline operator class millis() const;


   inline class micros micros() const;
   //inline operator class micros() const;


   inline class nanos nanos() const;
   //inline operator class nanos() const;


   inline operator bool() const;


   inline duration & operator = (const ::datetime::time_span & span);
   inline duration & operator += (const ::datetime::time_span & duration);
   inline duration & operator -= (const ::datetime::time_span & duration);


   inline time_t GetTimeSpan() const;


   duration operator - (const duration & duration) const;
   duration operator + (const duration & duration) const;


   void sleep() const;


};


inline duration::duration(::i64 iSeconds, ::i64 iNanoseconds)
{

   m_eduration = duration_finite;

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoseconds;

   normalize();

}


inline duration::duration(long double dSeconds)
{

   fset(dSeconds);

}


inline duration::duration(const ::duration& duration) :
   m_eduration(duration.m_eduration),
   m_iNanoseconds(duration.m_iNanoseconds),
   m_iSeconds(duration.m_iSeconds)
{

}


inline void duration::raw_set(i64 iSeconds, i64 iNanoseconds)
{

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoseconds;

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

   return m_iSeconds * 1000 + m_iNanoseconds / 1000000;

}


inline ::micros duration::micros() const
{

   return m_iSeconds * 1000000 + m_iNanoseconds / 1000;

}


//inline duration::operator ::millis() const
//{
//
//    return ::duration::millis();
//
//}


inline nanos duration::nanos() const
{

   return m_iNanoseconds + m_iSeconds * 1'000'000'000;

}


//inline duration::operator ::nanos() const
//{
//
//   return ::duration::nanos();
//
//}


//inline i64 duration::total_milliseconds() const
//{
//
//   return get_total_milliseconds();
//
//}
//
//
//inline i64 duration::total_microseconds() const
//{
//
//   return get_total_microseconds();
//
//}
//
//
//inline i64 duration::total_nanoseconds() const
//{
//   return get_total_nanoseconds();
//}


inline bool duration::is_pos_infinity() const
{

   return m_eduration == duration_infinite;

}


inline bool duration::is_infinite() const
{

   return m_eduration == duration_infinite;

}


bool duration::is_null() const
{
   return m_eduration == duration_finite && m_iSeconds <= 0 && m_iNanoseconds <= 0;
}

inline duration duration::infinite()
{

   return duration_infinite;

}

inline duration duration::pos_infinity()
{

   return duration::raw_create(0x7fffffffffffffffLL, 999999999);

}


inline duration duration::zero()
{

   return duration::create(0, 0);

}


inline bool duration::operator == (const duration & duration) const
{
   const_cast < class duration * >(this)->normalize();
   const_cast < class duration * >(&duration)->normalize();
   return m_iSeconds == duration.m_iSeconds
          && m_iNanoseconds == duration.m_iNanoseconds;
}

class CLASS_DECL_ACME nanosecond :
   public duration
{
public:


   inline nanosecond(i64 iNanoseconds = 0);
   inline nanosecond(u64 uNanoseconds) : nanosecond((::i64)uNanoseconds){}
   inline nanosecond(i32 iNanoseconds);
   inline nanosecond(u32 dwNanoseconds);
   nanosecond(long double dNanoseconds);

};


inline nanosecond operator "" _ns(unsigned long long int u) { return (::u64) u; }


class CLASS_DECL_ACME microsecond :
   public duration
{
public:


   inline microsecond(i64 iMicroseconds = 0);
   inline microsecond(u64 uMicroseconds) : microsecond((::i64)uMicroseconds) {}
   inline microsecond(i32 iMicroseconds);
   inline microsecond(u32 uMicroseconds);
   microsecond(long double dMicroseconds);

};

inline microsecond operator "" _us(unsigned long long int u) { return (::u64) u; }


class CLASS_DECL_ACME millisecond :
   public duration
{
public:


   inline millisecond(i64 iMillisecond = 0);
   inline millisecond(u64 uMillisecond);
   inline millisecond(i32 iMillisecond);
   inline millisecond(u32 uMillisecond);
   inline millisecond(double dMillisecond);
   millisecond(long double dMillisecond);

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

inline millisecond operator "" _ms(unsigned long long int u) { return (::u64) u; }


inline duration::duration(const ::tick_duration & tickduration)
{

    operator=(::millis(tickduration));

}


inline  duration::duration(const ::tick& tick)
{
   operator=(::millis(tick.m_i));
}

class CLASS_DECL_ACME seconds :
   public duration
{
public:


   inline seconds(i64 iSeconds = 0);
   inline seconds(u64 u) :seconds((::i64)u) {}
   inline seconds(i32 iSeconds);
   inline seconds(u32 dwSeconds);
   seconds(long double dSeconds);


};

inline seconds operator "" _s(unsigned long long int u) { return (::u64) u; }
inline seconds operator "" _s(long double d) { return d; }

class CLASS_DECL_ACME one_second :
   public duration
{
public:


   one_second() : duration(1) {}


};



class CLASS_DECL_ACME minutes :
   public duration
{
public:


   inline minutes(i64 iMinutes = 0);
   inline minutes(u64 u) :minutes((::i64)u) {}
   inline minutes(i32 iMinutes);
   inline minutes(u32 dwMinutes);
   inline minutes(long double dMinutes);


};


inline minutes operator "" _min(unsigned long long int u) { return (::u64) u; }

class CLASS_DECL_ACME one_minute :
   public duration
{
public:


   one_minute() : duration(60) {}


};




class CLASS_DECL_ACME hours :
   public duration
{
public:


   inline hours(i64 iHours, int iMinutes = 0, int iSeconds = 0);
   inline hours(u64 u, int iMinutes = 0, int iSeconds = 0) :hours((::i64)u, iMinutes, iSeconds) {}
   inline hours(i32 iHours, int iMinutes = 0, int iSeconds = 0);
   inline hours(u32 dwHours, int iMinutes = 0, int iSeconds = 0);
   inline hours(long double dHours);


};


inline hours operator "" _hours(unsigned long long int u) { return (::u64) u; }
inline hours operator "" _hour(unsigned long long int u) { return (::u64) u; }

class CLASS_DECL_ACME one_hour :
   public hours
{
public:


   one_hour(int iMinutes = 0, int iSeconds = 0) : hours(1, iMinutes, iSeconds) {}


};

class CLASS_DECL_ACME days :
   public duration
{
public:


   inline days(i64 iDays = 0);
   inline days(u64 u) :days((::i64)u) {}
   inline days(i32 iDays);
   inline days(u32 dwDays);
   inline days(long double dDays);


};

inline days operator "" _days(unsigned long long int u) { return (::u64) u; }
inline days operator "" _day(unsigned long long int u) { return (::u64) u; }

inline nanos::nanos(i64 i) :
   duration(i / (1000 * 1000 * 1000), (i % (1000 * 1000 * 1000)))
{

}


inline nanos::nanos(i32 i) :
   duration(i / (1000 * 1000 * 1000), (i % (1000 * 1000 * 1000)))
{

}


inline nanos::nanos(u32 dw) :
   duration(dw / (1000 * 1000 * 1000), (dw % (1000 * 1000 * 1000)))
{

}


inline micros::micros(i64 i) :
   duration(i / (1000 * 1000), (i % (1000 * 1000)) * 1000)
{

}


inline micros::micros(i32 i) :
   duration(i / (1000 * 1000), (i % (1000 * 1000)) * 1000)
{

}


inline micros::micros(u32 dw) :
   duration(dw / (1000 * 1000), (dw % (1000 * 1000)) * 1000)
{

}


inline millis::millis(i64 i) :
   duration(i / 1000, (i % 1000) * 1000000)
{

}


inline millis::millis(u64 u) :
duration(u / 1000, (u % 1000) * 1000000)
{

}


inline millis::millis(i32 i) :
   duration(i / 1000, (i % 1000) * 1000000)
{

}


inline millis::millis(u32 dw) :
   duration(dw / 1000, (dw % 1000) * 1000000)
{

}

inline millis::millis(double d) :
   duration((::i64) 0, (::i64) (d * 1'000'000.0))
{

}

inline seconds::seconds(i64 i) :
   duration(i)
{

}

inline seconds::seconds(i32 i) :
   duration(i)
{

}

inline seconds::seconds(u32 dw) :
   duration(dw)
{

}


inline seconds::seconds(long double d) :
   duration(d)
{

}



inline minutes::minutes(i64 i) :
   duration(i * 60)
{

}

inline minutes::minutes(i32 i) :
   duration(i * 60)
{

}

inline minutes::minutes(u32 dw) :
   duration(dw * 60)
{

}

inline minutes::minutes(long double d) :
   duration(d * 60.0)
{

}

inline hours::hours(i64 iHours, i32 iMinutes, i32 iSeconds) :
   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
{

}

inline hours::hours(i32 iHours, i32 iMinutes, i32 iSeconds) :
   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
{

}

inline hours::hours(u32 dwHours, i32 iMinutes, i32 iSeconds) :
   duration(dwHours * 3600 + iMinutes * 60 + iSeconds)
{

}

inline hours::hours(long double d) :
   duration(d * 3600.0)
{

}

inline days::days(i64 i) :
   duration(i * 86400)
{

}

inline days::days(i32 i) :
   duration(i * 86400)
{

}

inline days::days(u32 dw) :
   duration(dw * 86400)
{

}

inline days::days(long double d) :
   duration(d * 86400.0)
{

}

inline time_t duration::GetTimeSpan() const
{
   return total_seconds();
}


inline i64 duration::get_total_seconds() const
{
   return (get_total_milliseconds() + 500) / 1000;
}

inline i64 duration::total_seconds() const
{
   return (total_milliseconds() + 500) / 1000;
}


inline duration::operator bool() const
{

   return m_iSeconds != 0 || m_iNanoseconds != 0;

}


CLASS_DECL_ACME void Sleep(const duration & duration);














inline bool CLASS_DECL_ACME operator >(const duration & duration1, const duration & duration2)
{

   auto iCompare = duration1.m_iSeconds - duration2.m_iSeconds;

   if(iCompare > 0)
   {

      return true;

   }
   else if(iCompare == 0)
   {

      return duration1.m_iSeconds > duration2.m_iSeconds;

   }
   else
   {

      return false;

   }

}


inline bool CLASS_DECL_ACME operator < (const duration & duration1, const duration & duration2)
{

   auto iCompare = duration1.m_iSeconds - duration2.m_iSeconds;

   if(iCompare < 0)
   {

      return true;

   }
   else if(iCompare == 0)
   {

      return duration1.m_iSeconds < duration2.m_iSeconds;

   }
   else
   {

      return false;

   }

}




inline bool tick::operator == (const ::duration& duration) const { return m_i == duration.total_milliseconds(); }
inline bool tick::operator != (const ::duration& duration) const { return m_i != duration.total_milliseconds(); }
inline bool tick::operator < (const ::duration& duration) const { return m_i < duration.total_milliseconds(); }
inline bool tick::operator <= (const ::duration& duration) const { return m_i <= duration.total_milliseconds(); }
inline bool tick::operator > (const ::duration& duration) const { return m_i > duration.total_milliseconds(); }
inline bool tick::operator >= (const ::duration& duration) const { return m_i >= duration.total_milliseconds(); }
inline tick tick::operator - (const ::duration& duration) const { return m_i - duration.total_milliseconds(); }
inline tick tick::operator + (const ::duration& duration) const { return m_i + duration.total_milliseconds(); }
inline tick& tick::operator -= (const ::duration& duration) { m_i -= duration.total_milliseconds(); return *this; }
inline tick& tick::operator += (const ::duration& duration) { m_i += duration.total_milliseconds(); return *this; }


inline duration __random(const duration & d1, const duration & d2)
{

   auto iSeconds = __random(d1.m_iSeconds, d2.m_iSeconds);

   return duration(iSeconds, __random(
         (iSeconds > d1.m_iSeconds) ? 0 : d1.m_iNanoseconds,
         (iSeconds < d2.m_iSeconds) ? 999'999'999 : d2.m_iNanoseconds));

}


inline millis & millis::operator = (const duration & duration) { m_iMilliseconds = duration.millis(); return *this; }
inline nanos & nanos::operator = (const duration & duration) { m_iNanoseconds = duration.nanos(); return *this; }


#ifdef WINDOWS

inline u32 __os(const ::duration & duration) { return duration.is_infinite() ? U32_INFINITE_TIMEOUT : (duration.get_total_milliseconds() > (i64) MAXI32 ? U32_INFINITE_TIMEOUT : duration.get_total_milliseconds() < 0 ? 0 : (u32)duration.get_total_milliseconds()); }

#endif