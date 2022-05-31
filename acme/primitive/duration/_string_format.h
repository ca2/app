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

   str.format("%" PRId64 "ns", integral.m_i);

}



template < >
inline void to_string(string & str, const INTEGRAL_MICROSECOND & integral)
{

   str.format("%" PRId64 "µs", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_MILLISECOND & integral)
{

   str.format("%" PRId64 "ms", integral.m_i);

}



template < >
inline void to_string(string & str, const INTEGRAL_SECOND & integral)
{

   str.format("%" PRId64 "s", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_MINUTE & integral)
{

   str.format("%" PRId64 "minute(s)", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_HOUR & integral)
{

   str.format("%" PRId64 "hour(s)", integral.m_i);

}


template < >
inline void to_string(string & str, const INTEGRAL_DAY & integral)
{

   str.format("%" PRId64 "day(s)", integral.m_i);

}





