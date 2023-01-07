// Created by camilo on 2022-11-26 00:24 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/time/time.h"


class frequency :
   public FREQUENCY
{
public:


   constexpr frequency(enum_zero ezero = e_zero) :FREQUENCY{} {}
   constexpr frequency(const ::FREQUENCY& frequency) :FREQUENCY(frequency) {}

   template < primitive_floating FLOATING >
   constexpr frequency operator *(FLOATING d) const
   {

      return FREQUENCY(m_d * d);

   }

   template < primitive_floating FLOATING >
   constexpr frequency operator / (FLOATING d) const
   {

      return FREQUENCY(m_d / d);

   }

};



template < primitive_floating FLOATING >
constexpr ::frequency operator / (FLOATING d, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000.0 + time.m_iNanosecond);

   return FREQUENCY(d * 1'000'000'000.0 / nanosecond);

}


template < primitive_integral INTEGRAL >
constexpr ::frequency operator / (INTEGRAL i, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000 + time.m_iNanosecond);

   return FREQUENCY((double)(i * 1'000'000'000) / (double)nanosecond);

}


template < primitive_floating FLOATING >
constexpr ::frequency operator * (FLOATING d, const frequency & frequency)
{

   return FREQUENCY(d * frequency.m_d);

}


template < primitive_floating FLOATING >
constexpr class time operator / (FLOATING d, const frequency & frequency)
{

   auto dSeconds = d / frequency.m_d;

   return { dSeconds };

}


template < primitive_integral INTEGRAL >
constexpr class time operator / (INTEGRAL i, const frequency & frequency)
{

   auto dSeconds = (double) i / frequency.m_d;

   return { dSeconds };

}


constexpr double operator * (const class ::time & time, const frequency & frequency)
{

   return time.floating_second() * frequency.m_d;

}


constexpr double operator * (const frequency & frequency, const class ::time & time)
{

   return frequency.m_d * time.floating_second();

}



