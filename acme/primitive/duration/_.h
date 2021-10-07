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



enum enum_now
{

   
   e_now,


};


template < typename DURATION >
DURATION now()
{

   throw "interface_only";

   return 0;

}


#include "integral/_.h"


#include "floating/_.h"


#include "duration/_.h"

