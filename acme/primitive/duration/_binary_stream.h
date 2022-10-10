// First compilation from other files by camilo on 2022-10-07 23:20 <3ThomasBorregaardSorensen!!
#pragma once


inline binary_stream & operator <<(binary_stream & s, const ::DURATION & duration)
{

   s << duration.m_iSecond;
   s << duration.m_iNanosecond;

   return s;

}


inline binary_stream & operator >>(binary_stream & s, ::DURATION & duration)
{

   s >> duration.m_iSecond;
   s >> duration.m_iNanosecond;

   return s;

}


