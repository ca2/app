//
// Created by camilo on 2022-10-24 15:03 <3ThomasBorregaardSorensen!!
//
#pragma once


inline time::time(const class duration & duration) : time(duration.time()) {}
inline time::time(const ::INTEGRAL_NANOSECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_NANOSECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_MICROSECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_MICROSECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_MILLISECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_MILLISECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_SECOND & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_SECOND & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_MINUTE & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_MINUTE & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_HOUR & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_HOUR & floating) : time((const ::duration &)floating) {}
inline time::time(const ::INTEGRAL_DAY & integral) : time((const ::duration &)integral) {}
inline time::time(const ::FLOATING_DAY & floating) : time((const ::duration &)floating) {}


inline duration& duration::operator = (const ::duration & duration)
{

   if(this != &duration)
   {

      m_iSecond = duration.m_iSecond;
      m_iNanosecond = duration.m_iNanosecond;

   }

   return *this;

}



