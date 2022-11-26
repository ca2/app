// Created by camilo on 2022-11-26 00:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/time/time.h"


class frequency :
   public FREQUENCY
{
public:


   frequency(enum_zero ezero = e_zero) :FREQUENCY{} {}
   frequency(const ::FREQUENCY& frequency) :FREQUENCY(frequency) {}


};



template < primitive_floating FLOATING >
class ::frequency operator / (FLOATING d, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000.0 + time.m_iNanosecond);

   return d * 1'000'000'000.0 / nanosecond;

}


template < primitive_integral INTEGRAL >
class ::frequency operator / (INTEGRAL i, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000 + time.m_iNanosecond);

   return FREQUENCY((double)(i * 1'000'000'000) / (double)nanosecond);

}



