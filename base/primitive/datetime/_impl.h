#pragma once


//inline duration& duration::operator = (const ::tick& tick)
//{
//
//   operator = (::millis(tick.m_i));
//
//   return *this;
//
//}


inline duration& duration::operator = (const ::duration& duration)
{

   if(this != &duration)
   {

      m_eduration = duration.m_eduration;
      m_iSeconds = duration.m_iSeconds;
      m_iNanoseconds = duration.m_iNanoseconds;

   }

   return *this;

}

//
//inline tick & tick::operator = (const duration & duration)
//{
//
//   m_i = duration.get_total_milliseconds();
//
//   return *this;
//
//}

//
//inline tick & tick::operator = (const ::datetime::time_span & span)
//{
//
//   m_i = span.GetTotalSeconds() * 1'000;
//
//   return *this;
//
//}


