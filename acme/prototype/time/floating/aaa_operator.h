// Created by camilo on 2023-01-06 23:28 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/time/time/time.h"



//template < primitive_floating FLOATING >
//constexpr class time operator * (const ::floating_millisecond & millisecond, INTEGRAL integral)
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
//template < primitive_floating FLOATING >
//constexpr class time operator / (const ::floating_second & second, FLOATING floating)
//{
//
//   return {
//      (long long) (second.m_d / floating),
//      (long long) (fmod(second.m_d / floating, 1.0) * 1'000'000'000.0)
//   };
//
//}
////
////
////template < primitive_integral INTEGRAL >
////constexpr class time operator / (const ::integral_millisecond & millisecond, INTEGRAL integral)
////{
////
////   return {
////      (millisecond.m_i / integral) / 1'000ull,
////      ((millisecond.m_i % (integral * 1'000)) / integral) * 1'000'000
////   };
////
////}
////
////
////template < primitive_integral INTEGRAL >
////constexpr class time operator / (const ::integral_nanosecond & nanosecond, INTEGRAL integral)
////{
////
////   return {
////      (nanosecond.m_i / integral) / 1'000'000'000ull,
////      nanosecond.m_i / integral
////   };
////
////}
////
////
////
