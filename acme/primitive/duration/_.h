// Created by camilo on 2021-10-05 12:52 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


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
inline double operator /(const TYPE & t, const ::duration & duration) { return (double)t.MEMBER / (double)type(duration).MEMBER; } \
/*integral_duration operator *(const BASE_TYPE & duration, const ::duration & duration) const { return BASE_TYPE(this->m_i * duration.m_i); }*/ \
inline TYPE operator +(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER + type(duration).MEMBER); } \
inline TYPE operator -(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER - type(duration).MEMBER); } \

#define INTEGRAL_DURATION_SETUP1(TYPE, type) \
DURATION_OPERATOR_SETUP1(TYPE, type, m_i) \
inline TYPE operator %(const TYPE & t, const ::duration & duration) { return TYPE(t.m_i % type(duration).m_i); }

#define FLOATING_DURATION_SETUP1(TYPE, type) \
DURATION_OPERATOR_SETUP1(TYPE, type, m_d) \
inline TYPE operator %(const TYPE & t, const ::duration & duration) { return TYPE(fmod(t.m_d, type(duration).m_d)); }


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



