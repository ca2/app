// Created by camilo on 2023-07-04 18:43 <3ThomasBorregaardSorensen!!
#pragma once



struct posix_time_t {};

struct CLASS_DECL_ACME posix_time
{

   ::i64    m_iSecond;

   constexpr posix_time() : m_iSecond(0) {}
   constexpr posix_time(zero_t) : m_iSecond(0) {}
   template < primitive_integral INTEGRAL >
   constexpr posix_time(posix_time_t, INTEGRAL iSecond) : m_iSecond(iSecond) {}
   constexpr posix_time(const posix_time &) = default;
   posix_time(now_t);

   constexpr posix_time operator + (posix_time posixtime)  const
   {
      return { posix_time_t{}, m_iSecond + posixtime.m_iSecond };
   }

   constexpr posix_time operator - (posix_time posixtime)  const
   {
      return { posix_time_t{}, m_iSecond - posixtime.m_iSecond };
   }

   constexpr posix_time & operator += (posix_time posixtime)
   {
      m_iSecond += posixtime.m_iSecond;
      return *this;
   }

   constexpr posix_time & operator -=(posix_time posixtime)
   {
      m_iSecond = posixtime.m_iSecond;
      return *this;
   }

   constexpr posix_time & operator =(const posix_time & posixtime)
   {
      m_iSecond = posixtime.m_iSecond;
      return *this;
   }

   template < primitive_integral INTEGRAL >
   constexpr posix_time operator * (INTEGRAL i)  const
   {
      return { posix_time_t{}, m_iSecond * i };
   }


};


