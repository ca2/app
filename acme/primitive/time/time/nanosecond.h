// Created by camilo on 2023-07-04 18:45 <3ThomasBorregaardSorensen!!
#pragma once


struct nanosecond_t {};

struct nanosecond
{

   ::i64    m_iNanosecond;

   constexpr nanosecond() : m_iNanosecond(0) {}
   template < primitive_integral INTEGRAL >
   constexpr nanosecond(nanosecond_t, INTEGRAL iNanosecond) : m_iNanosecond(iNanosecond) {}
   constexpr nanosecond(const nanosecond &) = default;


   constexpr nanosecond operator + (nanosecond nanosecond)  const
   {
      return { nanosecond_t{}, m_iNanosecond + nanosecond.m_iNanosecond };
   }

   constexpr nanosecond operator - (nanosecond nanosecond)  const
   {
      return { nanosecond_t {}, m_iNanosecond - nanosecond.m_iNanosecond };
   }

   constexpr nanosecond & operator += (nanosecond nanosecond)
   {
      m_iNanosecond += nanosecond.m_iNanosecond;
      return *this;
   }

   constexpr nanosecond & operator -=(nanosecond nanosecond)
   {
      m_iNanosecond -= nanosecond.m_iNanosecond;
      return *this;
   }

   constexpr nanosecond & operator =(const nanosecond & nanosecond)
   {
      m_iNanosecond = nanosecond.m_iNanosecond;
      return *this;
   }

   template < primitive_integral INTEGRAL >
   constexpr nanosecond operator * (INTEGRAL i)  const
   {
      return { nanosecond_t{}, m_iNanosecond * i };
   }


};



