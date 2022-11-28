// Created by camilo on 2022-11-26 00:24 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/time/time.h"


class frequency :
   public FREQUENCY
{
public:


   frequency(enum_zero ezero = e_zero) :FREQUENCY{} {}
   frequency(const ::FREQUENCY& frequency) :FREQUENCY(frequency) {}

   template < primitive_floating FLOATING >
   frequency operator *(FLOATING d) const
   {

      return FREQUENCY(m_d * d);

   }

   template < primitive_floating FLOATING >
   frequency operator / (FLOATING d) const
   {

      return FREQUENCY(m_d / d);

   }

};



template < primitive_floating FLOATING >
class ::frequency operator / (FLOATING d, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000.0 + time.m_iNanosecond);

   return FREQUENCY(d * 1'000'000'000.0 / nanosecond);

}


template < primitive_integral INTEGRAL >
class ::frequency operator / (INTEGRAL i, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000 + time.m_iNanosecond);

   return FREQUENCY((double)(i * 1'000'000'000) / (double)nanosecond);

}


template < primitive_floating FLOATING >
class ::frequency operator * (FLOATING d, const class frequency & frequency)
{

   return FREQUENCY(d * frequency.m_d);

}


template < primitive_floating FLOATING >
class time operator / (FLOATING d, const class frequency & frequency)
{

   auto dSeconds = d / frequency.m_d;

   return { dSeconds };

}


template < primitive_integral INTEGRAL >
class time operator / (INTEGRAL i, const class frequency & frequency)
{

   auto dSeconds = (double) i / frequency.m_d;

   return { dSeconds };

}


double operator * (const class ::time & time, const class frequency & frequency)
{

   return time.floating_second().m_d * frequency.m_d;

}


double operator * (const class frequency & frequency, const class ::time & time)
{

   return frequency.m_d * time.floating_second().m_d;

}






