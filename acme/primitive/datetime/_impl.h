#pragma once


inline duration& duration::operator = (const class ::nanos & nanos)
{

   m_secs = nanos.m_iNanoseconds / 1'000'000'000;

   m_nanos = nanos.m_iNanoseconds % 1'000'000'000;

   return *this;

}


inline duration& duration::operator = (const class ::micros & micros)
{

   m_secs = micros.m_iMicroseconds / 1'000'000;

   m_nanos = (micros.m_iMicroseconds % 1'000'000) * 1'000;

   return *this;

}


inline duration& duration::operator = (const class ::millis & millis)
{

   m_secs = millis.m_iMilliseconds / 1'000;

   m_nanos = (millis.m_iMilliseconds % 1'000) * 1'000'000;

   return *this;

}


inline duration& duration::operator = (const class ::secs & secs)
{

   m_secs = secs;

   m_nanos = 0;

   return *this;

}


inline duration& duration::operator = (const ::duration & duration)
{

   if(this != &duration)
   {

      m_secs = duration.m_secs;
      m_nanos = duration.m_nanos;

   }

   return *this;

}





