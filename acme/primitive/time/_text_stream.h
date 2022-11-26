//
//  _text_stream.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2022-11-09 14:30 BRT.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


//#include "acme/filesystem/file/text_stream.h"


struct INTEGRAL_NANOSECOND;
struct INTEGRAL_MICROSECOND;
struct INTEGRAL_MILLISECOND;
struct INTEGRAL_SECOND;
struct INTEGRAL_MINUTE;
struct INTEGRAL_HOUR;
struct INTEGRAL_DAY;



template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const INTEGRAL_MICROSECOND& integral);

template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const INTEGRAL_MILLISECOND& integral);

template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const INTEGRAL_SECOND& integral);

template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const INTEGRAL_MINUTE& integral);

template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const INTEGRAL_HOUR& integral);

template < typename FILE >
inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const INTEGRAL_DAY& integral);


template < typename FILE, typename DURATION >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_time < DURATION >& time)
{

   return textstream << (const DURATION & ) time;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_NANOSECOND& integral)
{

   textstream.append_format("%" PRId64 "ns", integral.m_i);

   return textstream;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_MICROSECOND& integral)
{

   textstream.append_format("%" PRId64 "µs", integral.m_i);

   return textstream;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_MILLISECOND& integral)
{

   textstream.append_format("%" PRId64 "ms", integral.m_i);

   return textstream;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_SECOND& integral)
{

   textstream.append_format("%" PRId64 "s", integral.m_i);

   return textstream;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_MINUTE& integral)
{

   textstream.append_format("%" PRId64 "minute(s)", integral.m_i);

   return textstream;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_HOUR& integral)
{

   textstream.append_format("%" PRId64 "hour(s)", integral.m_i);

   return textstream;

}


template < typename FILE >
inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const INTEGRAL_DAY& integral)
{

   textstream.append_format("%" PRId64 "day(s)", integral.m_i);

   return textstream;

}
