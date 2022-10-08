// From earth_time.h by camilo on 2022-10-08 00:15 <3ThomasBorregaardSorensen!!
#pragma once


inline binary_stream & operator <<(binary_stream & stream, const ::earth::time_shift & timeshift)
{

   stream << timeshift.m_d;

   return stream;

}


inline binary_stream & operator >>(binary_stream & stream, ::earth::time_shift & timeshift)
{

   stream >> timeshift.m_d;

   return stream;

}


inline binary_stream & operator <<(binary_stream & stream, const ::datetime::time_zone & t)
{

   stream << t.m_strZone;
   stream << t.m_dZone;
   stream << t.m_duration;

   return stream;

}


inline binary_stream & operator >>(binary_stream & stream, ::datetime::time_zone & t)
{

   stream >> t.m_strZone;
   stream >> t.m_dZone;
   stream >> t.m_duration;

   return stream;

}


inline binary_stream & operator >>(binary_stream & s, ::earth::zonetime & z)
{

   s >> z.m_i;
   s >> z.m_timeshift;

   return s;

}



inline binary_stream & operator <<(binary_stream & s, const ::earth::zonetime & z)
{

   s << z.m_i;
   s << z.m_timeshift;

   return s;

}




