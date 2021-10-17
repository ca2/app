//
//  _string_format.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 09:29 BRT.
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
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



