// Created by CSTBS on 2021-10-06 19:38 BRT <3ThomasBorregaardSørensen!!
#pragma once


//#include "acme/primitive/comparison/compare.h"


struct TIME { ::i64 m_iSecond; ::i64 m_iNanosecond; };

struct FREQUENCY { double m_d; /* Hz */ };

constexpr FREQUENCY operator "" _Hz(long double d) { return { (double) d }; }


class time;


#define DECLARE_COMPARISON_WITH_TIME(EXPORT_CLAUSE_DECL) \
EXPORT_CLAUSE_DECL bool operator == (const class  ::time & time) const; \
EXPORT_CLAUSE_DECL ::std::strong_ordering operator <=> (const class  ::time & time) const; 
//\
//EXPORT_CLAUSE_DECL bool operator <= (const class  ::time & time) const; \
//EXPORT_CLAUSE_DECL bool operator > (const class  ::time & time) const; \
//EXPORT_CLAUSE_DECL bool operator >= (const class  ::time & time) const; \
//EXPORT_CLAUSE_DECL bool operator != (const class  ::time & time)  const;


#define DEFINE_COMPARISON_WITH_TIME(EXPORT_CLAUSE_DECL, TYPE) \
EXPORT_CLAUSE_DECL bool TYPE::operator == (const class  ::time & time) const { return ((class ::time)*this) == time; } \
EXPORT_CLAUSE_DECL ::std::strong_ordering TYPE::operator <=> (const class  ::time & time) const { return ((class ::time)*this) <=> time; } 
//\
//EXPORT_CLAUSE_DECL bool TYPE::operator <= (const class  ::time & time) const { return ((class ::time)*this) <= time; } \
//EXPORT_CLAUSE_DECL bool TYPE::operator > (const class  ::time & time) const { return ((class ::time)*this) > time; } \
//EXPORT_CLAUSE_DECL bool TYPE::operator >= (const class  ::time & time) const { return ((class ::time)*this) >= time; } \
//EXPORT_CLAUSE_DECL bool TYPE::operator != (const class  ::time & time) const { return ((class ::time)*this) != time; }


#define NON_INLINE


//#define DECLARE_COMPARISON_WITH_TIME \
//inline bool operator == (const class time & time); \
//inline bool operator < (const class time & time);  \
//inline bool operator <= (const class time & time); \
//inline bool operator > (const class time & time);  \
//inline bool operator >= (const class time & time); \
//inline bool operator != (const class time & time); 


//#define INLINE_COMPARISON_WITH_DURATION \
//inline bool operator == (const class time & time) const { return class ::time(*this) == time; } \
//inline bool operator < (const class time & time) const { return class ::time(*this) < time; } \
//inline bool operator <= (const class time & time) const { return class ::time(*this) <= time; } \
//inline bool operator > (const class time & time) const { return class ::time(*this) > time; } \
//inline bool operator >= (const class time & time) const { return class ::time(*this) >= time; } \
//inline bool operator != (const class time & time) const { return class ::time(*this) != time; } 



#define DURATION_UNIT(unit, type, member)                                     \
struct unit                                                                   \
{                                                                             \
                                                                              \
   using BASE_TYPE = type;                                                    \
   type member;                                                               \
                                                                              \
   constexpr unit():member{} {}                                               \
   constexpr unit(enum_zero):member{} {}                                      \
   constexpr unit(type t):member(t){}                                         \
                                                                              \
   bool operator == (const unit & u) const { return member == u.member; }     \
   ::std::strong_ordering operator <=> (const unit & u) const { return ::comparison::order(member, u.member); } \
   DECLARE_COMPARISON_WITH_TIME(inline)                                       \
                                                                              \
};






DURATION_UNIT(integral_nanosecond   , ::i64, m_i);
DURATION_UNIT(integral_microsecond  , ::i64, m_i);
DURATION_UNIT(integral_millisecond  , ::i64, m_i);
DURATION_UNIT(integral_second       , ::i64, m_i);
DURATION_UNIT(integral_minute       , ::i64, m_i);
DURATION_UNIT(integral_hour         , ::i64, m_i);
DURATION_UNIT(integral_day          , ::i64, m_i);


DURATION_UNIT(floating_nanosecond   , ::f64, m_d);
DURATION_UNIT(floating_microsecond  , ::f64, m_d);
DURATION_UNIT(floating_millisecond  , ::f64, m_d);
DURATION_UNIT(floating_second       , ::f64, m_d);
DURATION_UNIT(floating_minute       , ::f64, m_d);
DURATION_UNIT(floating_hour         , ::f64, m_d);
DURATION_UNIT(floating_day          , ::f64, m_d);


#define DEFAULT_MEMBER_COMPARISON(TYPE, MEMBER) \
inline bool operator == (const TYPE & t2) const { return this->MEMBER == t2.MEMBER; } \
inline ::std::strong_ordering operator <=>  (const TYPE & t2) const { return this->MEMBER <=> t2.MEMBER; } 
//\
//inline bool operator <= (const TYPE & t2) const { return this->MEMBER <= t2.MEMBER; } \
//inline bool operator >  (const TYPE & t2) const { return this->MEMBER > t2.MEMBER; } \
//inline bool operator >= (const TYPE & t2) const { return this->MEMBER >= t2.MEMBER; } \
//inline bool operator != (const TYPE & t2) const { return this->MEMBER != t2.MEMBER; }


#define __DURATION_SETUP__(TYPE, MEMBER) \
DEFAULT_MEMBER_COMPARISON(TYPE, MEMBER)  \
inline bool operator ! () { return this->MEMBER <= 0; }


//__DURATION_SETUP__(integral_nanosecond    , m_i)
//__DURATION_SETUP__(integral_microsecond   , m_i)
//__DURATION_SETUP__(integral_millisecond   , m_i)
//__DURATION_SETUP__(integral_second        , m_i)
//__DURATION_SETUP__(integral_minute        , m_i)
//__DURATION_SETUP__(integral_hour          , m_i)
//__DURATION_SETUP__(integral_day           , m_i)


//__DURATION_SETUP__(floating_nanosecond    , m_d)
//__DURATION_SETUP__(floating_microsecond   , m_d)
//__DURATION_SETUP__(floating_millisecond   , m_d)
//__DURATION_SETUP__(floating_second        , m_d)
//__DURATION_SETUP__(floating_minute        , m_d)
//__DURATION_SETUP__(floating_hour          , m_d)
//__DURATION_SETUP__(floating_day           , m_d)



//inline timespec & operator +=(timespec & timespec, const struct ::integral_millisecond & integralmillisecond)
//{
//
//   timespec.tv_sec += integralmillisecond.m_i /1'000;
//
//   timespec.tv_nsec += (integralmillisecond.m_i %1'000) *1'000'000;
//
//   normalize(timespec);
//
//   return timespec;
//
//}
//
//






template < typename INTEGRAL_TIME_UNIT >
concept integral_time_unit =
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_day > ||
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_hour > ||
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_minute > ||
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_second > ||
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_millisecond > ||
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_microsecond > ||
::std::is_same_v < INTEGRAL_TIME_UNIT, integral_nanosecond >;





template < typename FLOATING_TIME_UNIT >
concept floating_time_unit =
::std::is_same_v < FLOATING_TIME_UNIT, floating_day > ||
::std::is_same_v < FLOATING_TIME_UNIT, floating_hour > ||
::std::is_same_v < FLOATING_TIME_UNIT, floating_minute > ||
::std::is_same_v < FLOATING_TIME_UNIT, floating_second > ||
::std::is_same_v < FLOATING_TIME_UNIT, floating_millisecond > ||
::std::is_same_v < FLOATING_TIME_UNIT, floating_microsecond > ||
::std::is_same_v < FLOATING_TIME_UNIT, floating_nanosecond >;




