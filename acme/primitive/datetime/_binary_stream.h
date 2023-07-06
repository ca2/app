// From earth_time.h by camilo on 2022-10-08 00:15 <3ThomasBorregaardSorensen!!
#pragma once


//#include "earth_time.h"
//#include "time_span.h"
#include "earth_zone_time.h"


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & s, ::earth::time & z)
{

   s >> z.m_iSecond;

   return s;

}


// template < typename FILE >
inline binary_stream & operator <<(binary_stream & s, const ::earth::time & z)
{

   s << z.m_iSecond;

   return s;

}


// template < typename FILE >
inline binary_stream & operator <<(binary_stream & stream, const ::earth::time_shift & timeshift)
{

   stream << timeshift.m_d;

   return stream;

}


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & stream, ::earth::time_shift & timeshift)
{

   stream >> timeshift.m_d;

   return stream;

}


// template < typename FILE >
inline binary_stream & operator <<(binary_stream & stream, const ::datetime::time_zone & t)
{

   stream << t.m_strZone;
   stream << t.m_dZone;
   stream << t.m_time;

   return stream;

}


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & stream, ::datetime::time_zone & t)
{

   stream >> t.m_strZone;
   stream >> t.m_dZone;
   stream >> t.m_time;

   return stream;

}


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & s, ::earth::zone_time & z)
{

   s >> z.m_iSecond;
   s >> z.m_timeshift;

   return s;

}


// template < typename FILE >
inline binary_stream & operator <<(binary_stream & s, const ::earth::zone_time & z)
{

   s << z.m_iSecond;
   s << z.m_timeshift;

   return s;

}




