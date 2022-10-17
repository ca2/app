﻿// From earth_time.h by camilo on 2022-10-08 00:15 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & stream, const ::earth::time_shift & timeshift)
{

   stream << timeshift.m_d;

   return stream;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & stream, ::earth::time_shift & timeshift)
{

   stream >> timeshift.m_d;

   return stream;

}


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & stream, const ::datetime::time_zone & t)
{

   stream << t.m_strZone;
   stream << t.m_dZone;
   stream << t.m_duration;

   return stream;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & stream, ::datetime::time_zone & t)
{

   stream >> t.m_strZone;
   stream >> t.m_dZone;
   stream >> t.m_duration;

   return stream;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::earth::zonetime & z)
{

   s >> z.m_i;
   s >> z.m_timeshift;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::earth::zonetime & z)
{

   s << z.m_i;
   s << z.m_timeshift;

   return s;

}


