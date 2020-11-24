#pragma once


inline duration& duration::operator = (const class ::nanos & nanos)
{

   m_iSeconds = nanos.m_iNanoseconds / 1'000'000'000;

   m_iNanoseconds = nanos.m_iNanoseconds % 1'000'000'000;

   return *this;

}


inline duration& duration::operator = (const class ::micros & micros)
{

   m_iSeconds = micros.m_iMicroseconds / 1'000'000;

   m_iNanoseconds = (micros.m_iMicroseconds % 1'000'000) * 1'000;

   return *this;

}


inline duration& duration::operator = (const class ::millis & millis)
{

   m_iSeconds = millis.m_iMilliseconds / 1'000;

   m_iNanoseconds = (millis.m_iMilliseconds % 1'000) * 1'000'000;

   return *this;

}


inline duration& duration::operator = (const class ::secs & secs)
{

   m_iSeconds = secs.m_iSeconds;

   m_iNanoseconds = 0;

   return *this;

}


inline duration& duration::operator = (const ::duration & duration)
{

   if(this != &duration)
   {

      m_iSeconds = duration.m_iSeconds;
      m_iNanoseconds = duration.m_iNanoseconds;

   }

   return *this;

}





