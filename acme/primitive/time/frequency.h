// Created by camilo on 2022-11-26 00:24 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/time/time.h"

constexpr double double_equal_delta = 0.0001;

constexpr bool double_equals(double d1, double d2, double delta)
{

   auto d = d1 - d2;

   return -(delta / 2.0) < d && d < (delta / 2.0);

}


constexpr bool double_equals(double d1, double d2)
{

   return double_equals(d1, d2, double_equal_delta);

}


constexpr ::std::strong_ordering double_order(double d1, double d2, double delta)
{

   auto d = d1 - d2;

   if (d > (delta / 2.0))
   {

      return std::strong_ordering::greater;

   }
   else if (d < -(delta / 2.0))
   {

      return std::strong_ordering::less;

   }
   else
   {

      return std::strong_ordering::equal;

   }

}


constexpr ::std::strong_ordering double_order(double d1, double d2)
{

   return double_order(d1, d2, double_equal_delta);

}


class frequency :
   public FREQUENCY
{
public:


   constexpr frequency(enum_zero ezero = e_zero) :FREQUENCY{} {}
   constexpr frequency(double dHertz) : FREQUENCY{dHertz} {}
   constexpr frequency(const ::FREQUENCY & frequency) : FREQUENCY(frequency) {}

   template < primitive_floating FLOATING >
   constexpr frequency operator *(FLOATING d) const
   {

      return FREQUENCY(m_dHertz * d);

   }

   template < primitive_floating FLOATING >
   constexpr frequency operator / (FLOATING d) const
   {

      return FREQUENCY(m_dHertz / d);

   }


   ::frequency operator = (const ::frequency & frequency)
   {

      m_dHertz = frequency.m_dHertz;

      return *this;

   }


   constexpr bool is_null() const { return m_dHertz == 0.0; }
   constexpr bool is_set() const { return m_dHertz != 0.0; }
   constexpr bool operator !() const { return this->is_null(); }
   

   SAFE_BOOL_OPERATOR(frequency);


   bool operator == (const ::frequency frequency) const
   {

      return double_equals(m_dHertz, frequency.m_dHertz);

   }


   ::std::strong_ordering operator <=> (const ::frequency frequency) const
   {

      return double_order(m_dHertz, frequency.m_dHertz);

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

   return FREQUENCY(d * frequency.m_dHertz);

}


template < primitive_floating FLOATING >
constexpr class time operator / (FLOATING d, const frequency & frequency)
{

   auto dSeconds = d / frequency.m_dHertz;

   return { dSeconds };

}


template < primitive_integral INTEGRAL >
constexpr class time operator / (INTEGRAL i, const frequency & frequency)
{

   auto dSeconds = (double) i / frequency.m_dHertz;

   return { dSeconds };

}


template < primitive_integral INTEGRAL >
constexpr ::frequency operator * (INTEGRAL i, const frequency & frequency)
{

   return (double)i * frequency.m_dHertz;

}


constexpr double operator * (const class ::time & time, const frequency & frequency)
{

   return time.floating_second() * frequency.m_dHertz;

}


constexpr double operator * (const frequency & frequency, const class ::time & time)
{

   return frequency.m_dHertz * time.floating_second();

}



