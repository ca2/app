//
//  _string_format.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 09:29 BRT.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


inline ::string __string(const INTEGRAL_NANOSECOND & integral)
{

   return __string_format("%" PRId64 "ns", integral.m_i);

}


inline ::string __string(const INTEGRAL_MICROSECOND & integral)
{

   return __string_format("%" PRId64 "µs", integral.m_i);

}


inline ::string __string(const INTEGRAL_MILLISECOND & integral)
{

   return __string_format("%" PRId64 "ms", integral.m_i);

}


inline ::string __string(const INTEGRAL_SECOND & integral)
{

   return __string_format("%" PRId64 "s", integral.m_i);

}


inline ::string __string(const INTEGRAL_MINUTE & integral)
{

   return __string_format("%" PRId64 "minute(s)", integral.m_i);

}


inline ::string __string(const INTEGRAL_HOUR & integral)
{

   return __string_format("%" PRId64 "hour(s)", integral.m_i);

}


inline ::string __string(const INTEGRAL_DAY & integral)
{

   return __string_format("%" PRId64 "day(s)", integral.m_i);

}



