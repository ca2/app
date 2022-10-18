// Created by camilo on 2021-10-05 12:52 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


template < typename DURATION >
inline DURATION now()
{

   throw "interface_only";

   return e_now;

}


#include "integral/_.h"


#include "floating/_.h"


#include "duration/_.h"


template < typename DURATION >
inline integral_duration < DURATION > & integral_duration < DURATION >::Now()
{ 
   
   return this->operator=(::now < integral_duration < DURATION > >()); 

}


#define DURATION_OPERATOR_SETUP1(TYPE, type, MEMBER) \
inline TYPE operator-(const TYPE & t) { return (TYPE)(-t.MEMBER); } \
inline double operator /(const TYPE & t, const ::duration & duration) { return (double)t.MEMBER / (double)duration.type().MEMBER; } \
/*integral_duration operator *(const BASE_TYPE & duration, const ::duration & duration) const { return BASE_TYPE(this->m_i * duration.m_i); }*/ \
inline TYPE operator +(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER + duration.type().MEMBER); } \
inline TYPE operator -(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER - duration.type().MEMBER); } \

#define INTEGRAL_DURATION_SETUP1(TYPE, type) \
DURATION_OPERATOR_SETUP1(TYPE, type, m_i) \
inline TYPE operator %(const TYPE & t, const ::duration & duration) { return TYPE(t.m_i % duration.type().m_i); }

#define FLOATING_DURATION_SETUP1(TYPE, type) \
DURATION_OPERATOR_SETUP1(TYPE, type, m_d) \
inline TYPE operator %(const TYPE & t, const ::duration & duration) { return TYPE(fmod(t.m_d, duration.type().m_d)); }


INTEGRAL_DURATION_SETUP1(INTEGRAL_NANOSECOND    , integral_nanosecond   )
INTEGRAL_DURATION_SETUP1(INTEGRAL_MICROSECOND   , integral_microsecond  )
INTEGRAL_DURATION_SETUP1(INTEGRAL_MILLISECOND   , integral_millisecond  )
INTEGRAL_DURATION_SETUP1(INTEGRAL_SECOND        , integral_second       )
INTEGRAL_DURATION_SETUP1(INTEGRAL_MINUTE        , integral_minute       )
INTEGRAL_DURATION_SETUP1(INTEGRAL_HOUR          , integral_hour         )
INTEGRAL_DURATION_SETUP1(INTEGRAL_DAY           , integral_day          )


FLOATING_DURATION_SETUP1(FLOATING_NANOSECOND    , floating_nanosecond   )
FLOATING_DURATION_SETUP1(FLOATING_MICROSECOND   , floating_microsecond  )
FLOATING_DURATION_SETUP1(FLOATING_MILLISECOND   , floating_millisecond  )
FLOATING_DURATION_SETUP1(FLOATING_SECOND        , floating_second       )
FLOATING_DURATION_SETUP1(FLOATING_MINUTE        , floating_minute       )
FLOATING_DURATION_SETUP1(FLOATING_HOUR          , floating_hour         )
FLOATING_DURATION_SETUP1(FLOATING_DAY           , floating_day          )


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



