// First compilation from other files by camilo on 2022-10-07 23:20 <3ThomasBorregaardSorensen!!
// added binary_stream.h on 2022-10-15 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::posix_time & posixtime)
{

   s << posixtime.m_iSecond;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::posix_time & posixtime)
{

   s >> posixtime.m_iSecond;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::nanosecond & nanosecond)
{

   s << nanosecond.m_iNanosecond;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::nanosecond & nanosecond)
{

   s >> nanosecond.m_iNanosecond;

   return s;

}






template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const class ::time & time)
{

   s << (const ::posix_time &) time;
   s << (const ::nanosecond &) time;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, class ::time & time)
{

   s >> (::posix_time &)time;
   s >> (::nanosecond &)time;

   return s;

}


