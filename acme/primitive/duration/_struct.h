// Created by CSTBS on 2021-10-06 19:38 BRT <3ThomasBorregaardSørensen!!
#pragma once


struct DURATION { ::i64 m_iSecond; ::i64 m_iNanosecond; };

struct FREQUENCY { double m_d; /* Hz */ };

constexpr FREQUENCY operator "" _Hz(long double d) { return { (double) d }; }

#define DURATION_UNIT(unit, type, member)             \
struct unit                                           \
{                                                     \
                                                      \
   using BASE_TYPE = type;                            \
   type member;                                       \
                                                      \
   constexpr unit():member{} {}                       \
   constexpr unit(enum_zero):member{} {}              \
   constexpr unit(type t):member(t){}                 \
                                                      \
};


DURATION_UNIT(INTEGRAL_NANOSECOND   , ::i64, m_i);
DURATION_UNIT(INTEGRAL_MICROSECOND  , ::i64, m_i);
DURATION_UNIT(INTEGRAL_MILLISECOND  , ::i64, m_i);
DURATION_UNIT(INTEGRAL_SECOND       , ::i64, m_i);
DURATION_UNIT(INTEGRAL_MINUTE       , ::i64, m_i);
DURATION_UNIT(INTEGRAL_HOUR         , ::i64, m_i);
DURATION_UNIT(INTEGRAL_DAY          , ::i64, m_i);


DURATION_UNIT(FLOATING_NANOSECOND   , ::f64, m_d);
DURATION_UNIT(FLOATING_MICROSECOND  , ::f64, m_d);
DURATION_UNIT(FLOATING_MILLISECOND  , ::f64, m_d);
DURATION_UNIT(FLOATING_SECOND       , ::f64, m_d);
DURATION_UNIT(FLOATING_MINUTE       , ::f64, m_d);
DURATION_UNIT(FLOATING_HOUR         , ::f64, m_d);
DURATION_UNIT(FLOATING_DAY          , ::f64, m_d);


#define DEFAULT_MEMBER_COMPARISON(TYPE, MEMBER) \
inline bool operator == (const TYPE & t1, const TYPE & t2) { return t1.MEMBER == t2.MEMBER; } \
inline bool operator < (const TYPE & t1, const TYPE & t2) { return t1.MEMBER < t2.MEMBER; } \
inline bool operator <= (const TYPE & t1, const TYPE & t2) { return t1.MEMBER <= t2.MEMBER; } \
inline bool operator > (const TYPE & t1, const TYPE & t2) { return t1.MEMBER > t2.MEMBER; } \
inline bool operator >= (const TYPE & t1, const TYPE & t2) { return t1.MEMBER >= t2.MEMBER; } \
inline bool operator != (const TYPE & t1, const TYPE & t2) { return t1.MEMBER != t2.MEMBER; }


#define __DURATION_SETUP__(TYPE, MEMBER) \
DEFAULT_MEMBER_COMPARISON(TYPE, MEMBER)  \
inline bool operator ! (const TYPE & t1) { return t1.MEMBER <= 0; }


//__DURATION_SETUP__(INTEGRAL_NANOSECOND    , m_i)
//__DURATION_SETUP__(INTEGRAL_MICROSECOND   , m_i)
//__DURATION_SETUP__(INTEGRAL_MILLISECOND   , m_i)
//__DURATION_SETUP__(INTEGRAL_SECOND        , m_i)
//__DURATION_SETUP__(INTEGRAL_MINUTE        , m_i)
//__DURATION_SETUP__(INTEGRAL_HOUR          , m_i)
//__DURATION_SETUP__(INTEGRAL_DAY           , m_i)


//__DURATION_SETUP__(FLOATING_NANOSECOND    , m_d)
//__DURATION_SETUP__(FLOATING_MICROSECOND   , m_d)
//__DURATION_SETUP__(FLOATING_MILLISECOND   , m_d)
//__DURATION_SETUP__(FLOATING_SECOND        , m_d)
//__DURATION_SETUP__(FLOATING_MINUTE        , m_d)
//__DURATION_SETUP__(FLOATING_HOUR          , m_d)
//__DURATION_SETUP__(FLOATING_DAY           , m_d)


inline timespec & normalize(timespec & timespec)
{

   timespec.tv_sec += timespec.tv_nsec / 1'000'000'000;

   timespec.tv_nsec %= 1'000'000'000;

   return timespec;

}


inline timespec & operator +=(timespec & timespec, const struct ::INTEGRAL_MILLISECOND & integralmillisecond)
{

   timespec.tv_sec += integralmillisecond.m_i /1'000;

   timespec.tv_nsec += (integralmillisecond.m_i %1'000) *1'000'000;

   normalize(timespec);

   return timespec;

}





