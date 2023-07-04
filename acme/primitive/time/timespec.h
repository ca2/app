// Created by camilo on 2022-11-27 20:44 <3ThomasBorregaardSorensen!!
#pragma once


#include <time.h>


constexpr struct ::timespec& copy(struct ::timespec& timespec, const class ::time& time)
{

   timespec.tv_sec = (decltype(timespec.tv_sec))time.m_posixtime.m_iSecond;
   timespec.tv_nsec = (decltype(timespec.tv_nsec))time.m_nanosecond.m_iNanosecond;

   return timespec;

}


constexpr struct ::timespec& operator +=(struct ::timespec& timespec1, const struct ::timespec& timespec2)
{

   add_second_nanosecond(timespec1.tv_sec, timespec1.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);

   return timespec1;

}


constexpr struct ::timespec operator +(const struct ::timespec& timespec1, const struct ::timespec& timespec2)
{

   timespec timespec = timespec1;

   add_second_nanosecond(timespec.tv_sec, timespec.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);

   return timespec;

}


constexpr struct ::timespec& operator -=(struct ::timespec& timespec1, const struct ::timespec& timespec2)
{

   subtract_second_nanosecond(timespec1.tv_sec, timespec1.tv_nsec, timespec2.tv_sec, timespec2.tv_nsec);

   return timespec1;

}


constexpr struct ::timespec operator -(const struct ::timespec& timespec1, const struct ::timespec& timespec2)
{

   timespec timespec = timespec1;

   return timespec -= timespec2;

}


constexpr bool operator >(const struct ::timespec& timespec1, const struct ::timespec& timespec2)
{

   return timespec1.tv_sec > timespec2.tv_sec || (timespec1.tv_sec == timespec2.tv_sec && timespec1.tv_nsec > timespec2.tv_nsec);

}


constexpr timespec& normalize(timespec& timespec)
{

   timespec.tv_sec += timespec.tv_nsec / 1'000'000'000;

   timespec.tv_nsec %= 1'000'000'000;

   return timespec;

}


inline timespec& operator +=(timespec& timespec, const class time& time)
{

   return timespec += ::timespec
   {
      .tv_sec = (decltype(::timespec::tv_sec)) time.m_posixtime.m_iSecond, 
      .tv_nsec = (decltype(::timespec::tv_nsec)) time.m_nanosecond.m_iNanosecond
   };

}

