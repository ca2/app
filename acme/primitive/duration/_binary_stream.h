// First compilation from other files by camilo on 2022-10-07 23:20 <3ThomasBorregaardSorensen!!
// added binary_stream.h on 2022-10-15 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::DURATION & duration)
{

   s << duration.m_iSecond;
   s << duration.m_iNanosecond;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::DURATION & duration)
{

   s >> duration.m_iSecond;
   s >> duration.m_iNanosecond;

   return s;

}


