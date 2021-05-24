#pragma once


inline duration& duration::operator = (const class ::nanos & nanos)
{

   m_secs = nanos.m_i / 1'000'000'000;

   m_nanos = nanos.m_i % 1'000'000'000;

   return *this;

}


inline duration& duration::operator = (const class ::micros & micros)
{

   m_secs = micros.m_i / 1'000'000;

   m_nanos = (micros.m_i % 1'000'000) * 1'000;

   return *this;

}


inline duration& duration::operator = (const class ::millis & millis)
{

   m_secs = millis.m_i / 1'000;

   m_nanos = (millis.m_i % 1'000) * 1'000'000;

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


inline nanos operator -(const ::nanos& nanos, const ::millis & millis)
{

   return nanos.m_i - millis.m_i * 1'000'000;

}


inline duration operator -(const ::duration & duration, const ::millis & millis)
{

   return duration - (const ::duration &) millis;

}


inline ::i64 _first_sec() { return _get_millis() / 1'000; }
inline ::i64 _get_secs() { return _get_millis() / 1'000; }


inline ::i64 _first_millis() { return _get_micros() / 1'000; }
inline ::i64 _get_millis() { return _get_micros() / 1'000; }


inline ::i64 _first_micros() { return _get_nanos() / 1'000; }
inline ::i64 _get_micros() { return _get_nanos() / 1'000; }


inline millis::millis(enum enum_now) { m_i = _get_millis(); }
inline millis millis::now() { return get_millis(); }


namespace papaya
{


   namespace chill
   {


      template <  >
      inline millis default_value < millis >()
      {

         // estimate a delay of half of maximum millis positive value
         return ::get_millis() - (MAXI64 >> 1);

      }


   } // namespace chill


} // namespace papaya


inline bool millis::timeout(const millis& tickTimeout)
{

   auto millisNow = get_millis();

   if (millisNow - m_i < tickTimeout.m_i)
   {

      return false;

   }

   m_i = millisNow.m_i;

   return true;

}



