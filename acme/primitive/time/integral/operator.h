// Created by camilo on 2023-01-06 17:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/time/time/time.h"



//template < primitive_integral INTEGRAL >
//constexpr class time operator * (const ::time & millisecond, INTEGRAL integral)
//{
//
//   return {
//      (millisecond.m_i * integral) / 1'000ull,
//      ((millisecond.m_i * integral) % 1'000) * 1'000'000
//   };
//
//}
//
//
//
//template < primitive_integral INTEGRAL >
//constexpr class time operator / (const ::integral_second & second, INTEGRAL integral)
//{
//
//   return {
//      second.m_i / integral,
//      ((second.m_i % integral) * 1'000'000'000ull) % integral
//   };
//
//}
//
//
//template < primitive_integral INTEGRAL >
//constexpr class time operator / (const ::integral_millisecond & millisecond, INTEGRAL integral)
//{
//
//   return {
//      (millisecond.m_i / integral) / 1'000ull,
//      ((millisecond.m_i % (integral * 1'000)) / integral)* 1'000'000
//   };
//
//}
//
//
//template < primitive_integral INTEGRAL >
//constexpr class time operator / (const ::integral_nanosecond & nanosecond, INTEGRAL integral)
//{
//
//   return {
//      (nanosecond.m_i / integral) / 1'000'000'000ull,
//      nanosecond.m_i / integral
//   };
//
//}
//
//
//
