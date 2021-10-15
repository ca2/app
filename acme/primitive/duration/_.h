// Created by camilo on 2021-10-05 12:52 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


template < >
inline void to_string(string & str, const INTEGRAL_NANOSECOND & integral)
{

   str.Format("%" PRId64 "ns", integral.m_i);

}



template < >
inline void to_string(string & str, const INTEGRAL_MICROSECOND & integral)
{

   str.Format("%" PRId64 "µs", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_MILLISECOND & integral)
{

   str.Format("%" PRId64 "ms", integral.m_i);

}



template < >
inline void to_string(string & str, const INTEGRAL_SECOND & integral)
{

   str.Format("%" PRId64 "s", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_MINUTE & integral)
{

   str.Format("%" PRId64 "minute(s)", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_HOUR & integral)
{

   str.Format("%" PRId64 "hour(s)", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_DAY & integral)
{

   str.Format("%" PRId64 "day(s)", integral.m_i);

}


template < typename DURATION >
inline DURATION now()
{

   throw "interface_only";

   return 0;

}


#include "integral/_.h"


#include "floating/_.h"


#include "duration/_.h"



template < typename DURATION >
inline integral_duration < DURATION > & integral_duration < DURATION >::Now()
{ 
   
   return operator=(::now < integral_duration >()); 

}


template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator %(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator /(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator *(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i * integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator +(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i + integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator -(const INTEGRAL_NANOSECOND & duration, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i - integral)); }


template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator %(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator /(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator *(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i * integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator +(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i + integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator -(const INTEGRAL_MICROSECOND & duration, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i - integral)); }


template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator %(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator /(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator *(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i * integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator +(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i + integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator -(const INTEGRAL_MILLISECOND & duration, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i - integral)); }


template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator %(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator /(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator *(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i * integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator +(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i + integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator -(const INTEGRAL_SECOND & duration, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(duration.m_i - integral)); }


template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator %(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator /(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator *(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i * integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator +(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i + integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator -(const INTEGRAL_MINUTE & duration, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(duration.m_i - integral)); }


template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator %(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator /(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator *(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i * integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator +(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i + integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator -(const INTEGRAL_HOUR & duration, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(duration.m_i - integral)); }


template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator %(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i % integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator /(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i / integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator *(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i * integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator +(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i + integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator -(const INTEGRAL_DAY & duration, INTEGRAL integral) { return INTEGRAL_DAY(duration.m_i - integral); }


template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator %(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator /(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator *(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i * floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator +(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i + floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator -(const INTEGRAL_NANOSECOND & duration, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(duration.m_i - floating)); }


template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator %(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator /(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator *(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i * floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator +(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i + floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator -(const INTEGRAL_MICROSECOND & duration, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(duration.m_i - floating)); }


template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator %(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator /(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator *(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i * floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator +(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i + floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator -(const INTEGRAL_MILLISECOND & duration, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(duration.m_i - floating)); }


template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator %(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator /(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator *(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i * floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator +(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i + floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator -(const INTEGRAL_SECOND & duration, FLOATING floating) { return INTEGRAL_SECOND((::i64)(duration.m_i - floating)); }


template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator %(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator /(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator *(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i * floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator +(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i + floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator -(const INTEGRAL_MINUTE & duration, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(duration.m_i - floating)); }


template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator %(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator /(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator *(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i * floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator +(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i + floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator -(const INTEGRAL_HOUR & duration, FLOATING floating) { return INTEGRAL_HOUR((::i64)(duration.m_i - floating)); }


template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator %(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i % floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator /(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i / floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator *(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i * floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator +(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i + floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator -(const INTEGRAL_DAY & duration, FLOATING floating) { return INTEGRAL_DAY(duration.m_i - floating); }


template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator %(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator /(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator *(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d * integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator +(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d + integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator -(const FLOATING_NANOSECOND & duration, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(duration.m_d - integral)); }


template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator %(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator /(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator *(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d * integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator +(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d + integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator -(const FLOATING_MICROSECOND & duration, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(duration.m_d - integral)); }


template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator %(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator /(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator *(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d * integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator +(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d + integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator -(const FLOATING_MILLISECOND & duration, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(duration.m_d - integral)); }


template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator %(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator /(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator *(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d * integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator +(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d + integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator -(const FLOATING_SECOND & duration, INTEGRAL integral) { return FLOATING_SECOND((::f64)(duration.m_d - integral)); }


template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator %(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator /(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator *(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d * integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator +(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d + integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator -(const FLOATING_MINUTE & duration, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(duration.m_d - integral)); }


template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator %(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator /(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator *(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d * integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator +(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d + integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator -(const FLOATING_HOUR & duration, INTEGRAL integral) { return FLOATING_HOUR((::f64)(duration.m_d - integral)); }


template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator %(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d % integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator /(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d / integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator *(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d * integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator +(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d + integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator -(const FLOATING_DAY & duration, INTEGRAL integral) { return FLOATING_DAY(duration.m_d - integral); }


template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator %(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator /(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator *(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d * floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator +(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d + floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator -(const FLOATING_NANOSECOND & duration, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(duration.m_d - floating)); }


template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator %(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator /(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator *(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d * floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator +(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d + floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator -(const FLOATING_MICROSECOND & duration, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(duration.m_d - floating)); }


template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator %(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator /(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator *(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d * floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator +(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d + floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator -(const FLOATING_MILLISECOND & duration, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(duration.m_d - floating)); }


template < primitive_floating FLOATING >
inline FLOATING_SECOND operator %(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator /(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator *(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d * floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator +(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d + floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator -(const FLOATING_SECOND & duration, FLOATING floating) { return FLOATING_SECOND((::f64)(duration.m_d - floating)); }


template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator %(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator /(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator *(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d * floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator +(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d + floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator -(const FLOATING_MINUTE & duration, FLOATING floating) { return FLOATING_MINUTE((::f64)(duration.m_d - floating)); }


template < primitive_floating FLOATING >
inline FLOATING_HOUR operator %(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator /(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator *(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d * floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator +(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d + floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator -(const FLOATING_HOUR & duration, FLOATING floating) { return FLOATING_HOUR((::f64)(duration.m_d - floating)); }


template < primitive_floating FLOATING >
inline FLOATING_DAY operator %(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d % floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator /(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d / floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator *(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d * floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator +(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d + floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator -(const FLOATING_DAY & duration, FLOATING floating) { return FLOATING_DAY(duration.m_d - floating); }


#define DEFAULT_MEMBER_NUMBER(TYPE, MEMBER) \
inline TYPE operator-(const TYPE & t) { return (TYPE)(-t.MEMBER); } \
inline double operator /(const TYPE & t, const ::duration & duration) { return (double)t.MEMBER / (double)TYPE(duration).MEMBER; } \
/*integral_duration operator *(const BASE_TYPE & duration, const ::duration & duration) const { return BASE_TYPE(this->m_i * duration.m_i); }*/ \
inline TYPE operator +(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER + TYPE(duration).MEMBER); } \
inline TYPE operator -(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER - TYPE(duration).MEMBER); } \

#define DEFAULT_MEMBER_INTEGRAL(TYPE, MEMBER) \
DEFAULT_MEMBER_NUMBER(TYPE, MEMBER) \
inline TYPE operator %(const TYPE & t, const ::duration & duration) { return TYPE(t.MEMBER % TYPE(duration).MEMBER); }

#define DEFAULT_MEMBER_FLOATINGL(TYPE, MEMBER) \
DEFAULT_MEMBER_NUMBER(TYPE, MEMBER) \
inline TYPE operator %(const TYPE & t, const ::duration & duration) { return TYPE(fmod(t.MEMBER, TYPE(duration).MEMBER)); }


DEFAULT_MEMBER_NUMBER(INTEGRAL_NANOSECOND, m_i)
DEFAULT_MEMBER_NUMBER(INTEGRAL_MICROSECOND, m_i)
DEFAULT_MEMBER_NUMBER(INTEGRAL_MILLISECOND, m_i)
DEFAULT_MEMBER_NUMBER(INTEGRAL_SECOND, m_i)
DEFAULT_MEMBER_NUMBER(INTEGRAL_MINUTE, m_i)
DEFAULT_MEMBER_NUMBER(INTEGRAL_HOUR, m_i)
DEFAULT_MEMBER_NUMBER(INTEGRAL_DAY, m_i)


DEFAULT_MEMBER_NUMBER(FLOATING_NANOSECOND, m_d)
DEFAULT_MEMBER_NUMBER(FLOATING_MICROSECOND, m_d)
DEFAULT_MEMBER_NUMBER(FLOATING_MILLISECOND, m_d)
DEFAULT_MEMBER_NUMBER(FLOATING_SECOND, m_d)
DEFAULT_MEMBER_NUMBER(FLOATING_MINUTE, m_d)
DEFAULT_MEMBER_NUMBER(FLOATING_HOUR, m_d)
DEFAULT_MEMBER_NUMBER(FLOATING_DAY, m_d)



