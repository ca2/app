// Created by camilo on 2021-10-05 12:52 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


template < typename DURATION >
inline DURATION now()
{

   throw "interface_only";

   return e_now;

}


#include "acme/primitive/time/integral/_.h"


#include "acme/primitive/time/floating/_.h"


#include "acme/primitive/time/time/_.h"


//template < typename DURATION >
//inline integral_time < DURATION > & integral_time < DURATION >::Now()
//{ 
//   
//   return this->operator=(::now < integral_time < DURATION > >()); 
//
//}


#define DURATION_OPERATOR_SETUP1(TYPE, type, MEMBER) \
inline TYPE operator-(const TYPE & t) { return (TYPE)(-t.MEMBER); } \
inline double operator /(const TYPE & t, const class time & time) { return (double)t.MEMBER / (double)time.type().MEMBER; } \
/*integral_time operator *(const BASE_TYPE & time, const class time & time) const { return BASE_TYPE(this->m_i * time.m_i); }*/ \
inline TYPE operator +(const TYPE & t, const class time & time) { return TYPE(t.MEMBER + time.type().MEMBER); } \
inline TYPE operator -(const TYPE & t, const class time & time) { return TYPE(t.MEMBER - time.type().MEMBER); }


//inline bool operator ==(const TYPE & t1, const TYPE & t2) { return t1.MEMBER == t2.MEMBER; } \
//inline ::std::strong_ordering operator <=>(const TYPE & t1, const TYPE & t2) { return ::comparison::order(t1.MEMBER, t2.MEMBER); } \



#define INTEGRAL_DURATION_SETUP1(TYPE, type) \
DURATION_OPERATOR_SETUP1(TYPE, type, m_i) \
inline TYPE operator %(const TYPE & t, const class time & time) { return TYPE(t.m_i % time.type().m_i); }


#define FLOATING_DURATION_SETUP1(TYPE, type) \
DURATION_OPERATOR_SETUP1(TYPE, type, m_d) \
inline TYPE operator %(const TYPE & t, const class time & time) { return TYPE(fmod(t.m_d, time.type().m_d)); }


//INTEGRAL_DURATION_SETUP1(integral_nanosecond    , integral_nanosecond   )
//INTEGRAL_DURATION_SETUP1(integral_microsecond   , integral_microsecond  )
//INTEGRAL_DURATION_SETUP1(integral_millisecond   , integral_millisecond  )
//INTEGRAL_DURATION_SETUP1(integral_second        , integral_second       )
//INTEGRAL_DURATION_SETUP1(integral_minute        , integral_minute       )
//INTEGRAL_DURATION_SETUP1(integral_hour          , integral_hour         )
//INTEGRAL_DURATION_SETUP1(integral_day           , integral_day          )
//
//
//FLOATING_DURATION_SETUP1(floating_nanosecond    , floating_nanosecond   )
//FLOATING_DURATION_SETUP1(floating_microsecond   , floating_microsecond  )
//FLOATING_DURATION_SETUP1(floating_millisecond   , floating_millisecond  )
//FLOATING_DURATION_SETUP1(floating_second        , floating_second       )
//FLOATING_DURATION_SETUP1(floating_minute        , floating_minute       )
//FLOATING_DURATION_SETUP1(floating_hour          , floating_hour         )
//FLOATING_DURATION_SETUP1(floating_day           , floating_day          )


//__DURATION_SETUP__(integral_nanosecond    , m_i)
//__DURATION_SETUP__(integral_microsecond   , m_i)
//__DURATION_SETUP__(integral_millisecond   , m_i)
//__DURATION_SETUP__(integral_second        , m_i)
//__DURATION_SETUP__(integral_minute        , m_i)
//__DURATION_SETUP__(integral_hour          , m_i)
//__DURATION_SETUP__(integral_day           , m_i)
//

//__DURATION_SETUP__(floating_nanosecond    , m_d)
//__DURATION_SETUP__(floating_microsecond   , m_d)
//__DURATION_SETUP__(floating_millisecond   , m_d)
//__DURATION_SETUP__(floating_second        , m_d)
//__DURATION_SETUP__(floating_minute        , m_d)
//__DURATION_SETUP__(floating_hour          , m_d)
//__DURATION_SETUP__(floating_day           , m_d)


//inline floating_second_t::floating_second_t(const class time & time)
//{
//
//   m_d = (double) time.m_iSecond + ((double) time.m_iNanosecond / 1'000'000'000.0);
//
//}

//
//inline integral_second_t::integral_second_t(const class time & time)
//{
//
//   //m_i = time.m_iSecond + (time.m_iNanosecond > 500'000'000 ? 1 : 0);
//
//   m_i = time.m_iSecond;
//
//}
