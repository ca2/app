//
//  _text_stream.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2022-11-09 14:30 BRT.
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


//#include "acme/filesystem/file/text_stream.h"


struct integral_nanosecond;
struct integral_microsecond;
struct integral_millisecond;
struct integral_second;
struct integral_minute;
struct integral_hour;
struct integral_day;



//// template < typename FILE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const integral_microsecond& integral);
//
//// template < typename FILE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const integral_millisecond& integral);
//
//// template < typename FILE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const integral_second& integral);
//
//// template < typename FILE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const integral_minute& integral);
//
//// template < typename FILE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const integral_hour& integral);
//
//// template < typename FILE >
//inline ::write_text_stream < FILE > & operator <<(::write_text_stream < FILE > & textstream, const integral_day& integral);

//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_nanosecond& integral)
//{
//
//   textstream.append_format("%" PRId64 "ns", integral.m_i);
//
//   return textstream;
//
//}
//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_microsecond& integral)
//{
//
//   textstream.append_format("%" PRId64 "μs", integral.m_i);
//
//   return textstream;
//
//}
//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_millisecond& integral)
//{
//
//   textstream.append_format("%" PRId64 "ms", integral.m_i);
//
//   return textstream;
//
//}
//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_second& integral)
//{
//
//   textstream.append_format("%" PRId64 "s", integral.m_i);
//
//   return textstream;
//
//}
//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_minute& integral)
//{
//
//   textstream.append_format("%" PRId64 "minute(s)", integral.m_i);
//
//   return textstream;
//
//}
//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_hour& integral)
//{
//
//   textstream.append_format("%" PRId64 "hour(s)", integral.m_i);
//
//   return textstream;
//
//}
//
//
//// template < typename FILE >
//inline ::write_text_stream < FILE >& operator <<(::write_text_stream < FILE >& textstream, const integral_day& integral)
//{
//
//   textstream.append_format("%" PRId64 "day(s)", integral.m_i);
//
//   return textstream;
//
//}
inline ::write_text_stream & operator <<(::write_text_stream & textstream, const class ::time & time)
{

   ::string strTime;

   strTime.format("%fs", time.floating_second());

   return textstream << strTime;

}
