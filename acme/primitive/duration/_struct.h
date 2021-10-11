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


#define __DURATION_SETUP__(TYPE, MEMBER) \
DEFAULT_MEMBER_COMPARISON(TYPE, MEMBER)  \
inline bool operator ! (const TYPE & t1) { return t1.MEMBER <= 0; }


__DURATION_SETUP__(INTEGRAL_NANOSECOND, m_i)
__DURATION_SETUP__(INTEGRAL_MICROSECOND, m_i)
__DURATION_SETUP__(INTEGRAL_MILLISECOND, m_i)
__DURATION_SETUP__(INTEGRAL_SECOND, m_i)
__DURATION_SETUP__(INTEGRAL_MINUTE, m_i)
__DURATION_SETUP__(INTEGRAL_HOUR, m_i)
__DURATION_SETUP__(INTEGRAL_DAY, m_i)


__DURATION_SETUP__(FLOATING_NANOSECOND, m_d)
__DURATION_SETUP__(FLOATING_MICROSECOND, m_d)
__DURATION_SETUP__(FLOATING_MILLISECOND, m_d)
__DURATION_SETUP__(FLOATING_SECOND, m_d)
__DURATION_SETUP__(FLOATING_MINUTE, m_d)
__DURATION_SETUP__(FLOATING_HOUR, m_d)
__DURATION_SETUP__(FLOATING_DAY, m_d)


constexpr INTEGRAL_NANOSECOND operator "" _ns(unsigned long long int u) { return (INTEGRAL_NANOSECOND)u; }


constexpr INTEGRAL_MICROSECOND operator "" _us(unsigned long long int u) { return (INTEGRAL_MICROSECOND)u; }
constexpr INTEGRAL_MICROSECOND operator "" _μs(unsigned long long int u) { return (INTEGRAL_MICROSECOND)u; }


constexpr INTEGRAL_MILLISECOND operator "" _ms(unsigned long long int u) { return (INTEGRAL_MILLISECOND)u; }


constexpr INTEGRAL_SECOND operator "" _s(unsigned long long int u) { return (INTEGRAL_SECOND)u; }


constexpr INTEGRAL_MINUTE operator "" _min(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }
constexpr INTEGRAL_MINUTE operator "" _minute(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }
constexpr INTEGRAL_MINUTE operator "" _minutes(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }


constexpr INTEGRAL_HOUR operator "" _h(unsigned long long int u) { return (INTEGRAL_HOUR)u; }
constexpr INTEGRAL_HOUR operator "" _hour(unsigned long long int u) { return (INTEGRAL_HOUR)u; }
constexpr INTEGRAL_HOUR operator "" _hours(unsigned long long int u) { return (INTEGRAL_HOUR)u; }


constexpr INTEGRAL_DAY operator "" _day(unsigned long long int u) { return (INTEGRAL_DAY)u; }
constexpr INTEGRAL_DAY operator "" _days(unsigned long long int u) { return (INTEGRAL_DAY)u; }


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




CLASS_DECL_ACME INTEGRAL_NANOSECOND get_integral_nanosecond();

inline INTEGRAL_MICROSECOND get_integral_microsecond() { return INTEGRAL_MICROSECOND(get_integral_nanosecond().m_i / 1'000); }

inline INTEGRAL_MILLISECOND get_integral_millisecond() { return INTEGRAL_MILLISECOND(get_integral_nanosecond().m_i / 1'000'000); }

inline INTEGRAL_SECOND get_integral_second() { return INTEGRAL_SECOND(get_integral_nanosecond().m_i / 1'000'000'000); }

inline INTEGRAL_MINUTE get_integral_minute() { return INTEGRAL_MINUTE(get_integral_nanosecond().m_i / 60'000'000'000); }

inline INTEGRAL_HOUR get_integral_hour() { return INTEGRAL_HOUR(get_integral_nanosecond().m_i / 3'600'000'000'000); }

inline INTEGRAL_DAY get_integral_day() { return INTEGRAL_DAY(get_integral_nanosecond().m_i / 86'400'000'000'000); }



