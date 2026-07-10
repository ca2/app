// Created by camilo on 2022-11-26 00:24 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/time/time.h"

constexpr ::f64 f64_equal_delta = 0.0001;

constexpr bool f64_equals(::f64 d1, ::f64 d2, ::f64 delta)
{

   auto d = d1 - d2;

   return -(delta / 2.0) < d && d < (delta / 2.0);

}


constexpr bool f64_equals(::f64 d1, ::f64 d2)
{

   return f64_equals(d1, d2, f64_equal_delta);

}


constexpr ::std::strong_ordering f64_order(::f64 d1, ::f64 d2, ::f64 delta)
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


constexpr ::std::strong_ordering f64_order(::f64 d1, ::f64 d2)
{

   return f64_order(d1, d2, f64_equal_delta);

}


class frequency :
   public FREQUENCY
{
public:


   constexpr frequency() :FREQUENCY{0.} {}
   constexpr frequency(::f64 dHertz) : FREQUENCY{dHertz} {}
   constexpr frequency(const ::FREQUENCY & frequency) : FREQUENCY(frequency) {}

   template < prototype_floating FLOATING >
   constexpr frequency operator *(FLOATING d) const
   {

      return m_dHertz * d;

   }

   template < prototype_floating FLOATING >
   constexpr frequency operator / (FLOATING d) const
   {

      return m_dHertz / d;

   }


   ::frequency operator = (const ::frequency & frequency)
   {

      m_dHertz = frequency.m_dHertz;

      return *this;

   }


   constexpr bool is_null() const { return m_dHertz == 0.0; }
   constexpr bool is_set() const { return m_dHertz != 0.0; }
   constexpr bool operator !() const { return this->is_null(); }
   

   explicit operator bool() const noexcept { return this->is_set(); }


   bool operator == (const ::frequency frequency) const
   {

      return f64_equals(m_dHertz, frequency.m_dHertz);

   }


   ::std::strong_ordering operator <=> (const ::frequency frequency) const
   {

      return f64_order(m_dHertz, frequency.m_dHertz);

   }


   ::f64 hertz() const { return m_dHertz; }



};



template < prototype_floating FLOATING >
constexpr ::frequency operator / (FLOATING d, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000.0 + time.m_iNanosecond);

   return FREQUENCY{d * 1'000'000'000.0 / nanosecond};

}


template < prototype_integral INTEGRAL >
constexpr ::frequency operator / (INTEGRAL i, const class time& time)
{

   auto nanosecond = (time.m_iSecond * 1'000'000'000 + time.m_iNanosecond);

   return FREQUENCY{(::f64)(i * 1'000'000'000) / (::f64)nanosecond};

}


template < prototype_floating FLOATING >
constexpr ::frequency operator * (FLOATING d, const frequency & frequency)
{

   return FREQUENCY{ d * frequency.m_dHertz};

}


template < prototype_floating FLOATING >
constexpr class time operator / (FLOATING d, const frequency & frequency)
{

   auto dSeconds = d / frequency.m_dHertz;

   return { dSeconds };

}


template < prototype_integral INTEGRAL >
constexpr class time operator / (INTEGRAL i, const frequency & frequency)
{

   auto dSeconds = (::f64) i / frequency.m_dHertz;

   return { dSeconds };

}


template < prototype_integral INTEGRAL >
constexpr ::frequency operator * (INTEGRAL i, const frequency & frequency)
{

   return (::f64)i * frequency.m_dHertz;

}


constexpr ::f64 operator * (const class ::time & time, const frequency & frequency)
{

   return time.floating_second() * frequency.m_dHertz;

}


constexpr ::f64 operator * (const frequency & frequency, const class ::time & time)
{

   return frequency.m_dHertz * time.floating_second();

}



