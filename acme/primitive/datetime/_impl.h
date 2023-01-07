﻿#pragma once


//inline time& time::operator = (const class ::nanosecond & nanosecond)
//{
//
//   m_iSecond = nanosecond.m_i / 1'000'000'000;
//
//   m_iNanosecond = nanosecond.m_i % 1'000'000'000;
//
//   return *this;
//
//}


//inline time& time::operator = (const class ::microsecond & microsecond)
//{
//
//   m_secs = microsecond.m_i / 1'000'000;
//
//   m_nanos = (microsecond.m_i % 1'000'000) * 1'000;
//
//   return *this;
//
//}
//

//inline time& time::operator = (const class ::time & class ::time)
//{
//
//   m_secs = class ::time.m_i / 1'000;
//
//   m_nanos = (class ::time.m_i % 1'000) * 1'000'000;
//
//   return *this;
//
//}


//inline time& time::operator = (const class ::second & second)
//{
//
//   m_secs = second;
//
//   m_nanos = 0;
//
//   return *this;
//
//}



//
//inline nanosecond operator -(const ::nanosecond& nanosecond, const class time & time)
//{
//
//   return nanosecond.m_i - class ::time.m_i * 1'000'000;
//
//}
//
//
//inline time operator -(const class time & time, const class time & time)
//{
//
//   return time - (const class ::time &) class ::time;
//
//}
//


//
//inline bool time::timeout(const class time & time)
//{
//
//   auto now = this->now();
//
//   if (elapsed(now) < time)
//   {
//
//      return false;
//
//   }
//
//   operator =(now);
//
//   return true;
//
//}
//
//
//class ::time time::remaining(const class time & time, const class time & timeNow)
//{
//
//   auto timeRemaining = time - elapsed(timeNow);
//
//   return timeRemaining;
//
//}
//
//


namespace earth
{


   constexpr ::earth::time & time::operator+=(date_span span)
   {

      __UNREFERENCED_PARAMETER(span);

      //throw ::not_implemented();

      return *this;

   }


   constexpr ::earth::time & time::operator-=(date_span span)
   {

      __UNREFERENCED_PARAMETER(span);

      //throw ::not_implemented();

      return *this;

   }


   constexpr ::earth::time time::operator-(date_span span) const
   {

      __UNREFERENCED_PARAMETER(span);

      //throw ::not_implemented();

      return 0;

   }


   constexpr ::earth::time time::operator+(date_span span) const
   {

      __UNREFERENCED_PARAMETER(span);

      //throw_();

      return 0;

   }

   constexpr ::std::strong_ordering time_span::operator <=>(const class ::time & time) const
   {

      return m_time <=> time.integral_second();

   }


} // namespace earth







