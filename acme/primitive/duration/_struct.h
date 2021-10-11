// Created by CSTBS on 2021-10-06 19:38 BRT <3ThomasBorregaardS�rensen!!
#pragma once


struct DURATION { time_t m_iSecond; /* Seconds - >= 0 */ long m_iNanosecond; /* Nanoseconds - [0, 999999999] */ };


struct FREQUENCY { double m_d; /* Hz */ };


struct INTEGRAL_NANOSECOND { using BASE_TYPE = ::i64; ::i64 m_i; };
struct INTEGRAL_MICROSECOND { using BASE_TYPE = ::i64; ::i64 m_i; };
struct INTEGRAL_MILLISECOND { using BASE_TYPE = ::i64; ::i64 m_i; };
struct INTEGRAL_SECOND { using BASE_TYPE = ::i64; ::i64 m_i; };
struct INTEGRAL_MINUTE { using BASE_TYPE = ::i64; ::i64 m_i; };
struct INTEGRAL_HOUR { using BASE_TYPE = ::i64; ::i64 m_i; };
struct INTEGRAL_DAY { using BASE_TYPE = ::i64; ::i64 m_i; };


struct FLOATING_NANOSECOND { using BASE_TYPE = ::f64; ::f64 m_d; };
struct FLOATING_MICROSECOND { using BASE_TYPE = ::f64; ::f64 m_d; };
struct FLOATING_MILLISECOND { using BASE_TYPE = ::f64; ::f64 m_d; };
struct FLOATING_SECOND { using BASE_TYPE = ::f64; ::f64 m_d; };
struct FLOATING_MINUTE { using BASE_TYPE = ::f64;  ::f64 m_d; };
struct FLOATING_HOUR { using BASE_TYPE = ::f64;  ::f64 m_d; };
struct FLOATING_DAY { using BASE_TYPE = ::f64; ::f64 m_d; };


#define DEFAULT_MEMBER_COMPARISON(TYPE, MEMBER) \
inline bool operator == (const TYPE & t1, const TYPE & t2) { return t1.MEMBER == t2.MEMBER; } \
inline bool operator < (const TYPE & t1, const TYPE & t2) { return t1.MEMBER < t2.MEMBER; } \
inline bool operator <= (const TYPE & t1, const TYPE & t2) { return t1.MEMBER <= t2.MEMBER; } \
inline bool operator > (const TYPE & t1, const TYPE & t2) { return t1.MEMBER > t2.MEMBER; } \
inline bool operator >= (const TYPE & t1, const TYPE & t2) { return t1.MEMBER >= t2.MEMBER; } \
inline bool operator != (const TYPE & t1, const TYPE & t2) { return t1.MEMBER != t2.MEMBER; } 


DEFAULT_MEMBER_COMPARISON(INTEGRAL_NANOSECOND, m_i)
DEFAULT_MEMBER_COMPARISON(INTEGRAL_MICROSECOND, m_i)
DEFAULT_MEMBER_COMPARISON(INTEGRAL_MILLISECOND, m_i)
DEFAULT_MEMBER_COMPARISON(INTEGRAL_SECOND, m_i)
DEFAULT_MEMBER_COMPARISON(INTEGRAL_MINUTE, m_i)
DEFAULT_MEMBER_COMPARISON(INTEGRAL_HOUR, m_i)
DEFAULT_MEMBER_COMPARISON(INTEGRAL_DAY, m_i)


DEFAULT_MEMBER_COMPARISON(FLOATING_NANOSECOND, m_d)
DEFAULT_MEMBER_COMPARISON(FLOATING_MICROSECOND, m_d)
DEFAULT_MEMBER_COMPARISON(FLOATING_MILLISECOND, m_d)
DEFAULT_MEMBER_COMPARISON(FLOATING_SECOND, m_d)
DEFAULT_MEMBER_COMPARISON(FLOATING_MINUTE, m_d)
DEFAULT_MEMBER_COMPARISON(FLOATING_HOUR, m_d)
DEFAULT_MEMBER_COMPARISON(FLOATING_DAY, m_d)


constexpr INTEGRAL_MINUTE operator "" _min(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }
constexpr INTEGRAL_MINUTE operator "" _minute(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }
constexpr INTEGRAL_MINUTE operator "" _minutes(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }


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



