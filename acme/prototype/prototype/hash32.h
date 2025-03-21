//
//  hash32.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/22.
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
//  Refactoring by camilo on 2023-01-09 10:32 <3ThomasBorregaardSorensen!!
//
#pragma once


struct hash32
{


   unsigned int m_u;


   hash32() : m_u(0) {};
   template < typename T >
   hash32(const T * p) : m_u((unsigned int)(::uptr)p) {};
   template < primitive_integral INTEGRAL >
   constexpr hash32(INTEGRAL i) : m_u((unsigned int)i) { }
   template < primitive_enum ENUM >
   constexpr hash32(ENUM e) : m_u((unsigned int)e) { }
   template < primitive_floating FLOATING >
   constexpr hash32(FLOATING f) : hash32(&f, sizeof(f)) { }
   template < typename T >
   constexpr hash32(const ::pointer < T > & t) : hash32(t.m_p) { }
   constexpr hash32(const void * p, memsize s):m_u(0) { while (--s >= 0) m_u = (m_u << 5) ^ *((unsigned char*&)p)++; }


   constexpr ::hash32 operator + (::hash32 u) 
   {
      return (m_u << 16) ^ u.m_u; 
   }


};


template < typename T >
::hash32 as_hash32(const T & t) { return (::hash32)t; }


//#include "acme/include/_numeric_concepts.h"
//#include "acme/prototype/prototype/enumeration.h"
//#include "acme/prototype/prototype/pointer.h"

//
//struct hash32
//{
//
//   unsigned int m_u;
//
//
//   template < typename T >
//   hash32(const T* p) : m_u((unsigned int)(::uptr)p) {}
//   template < primitive_integral INTEGRAL >
//   hash32(INTEGRAL i) : m_u((unsigned int)i) {}
//   template < a_enum ENUM >
//   hash32(const ::enumeration < ENUM > & e) : m_u((unsigned int)e.m_eenum) {}
//   hash32(float f) : m_u(*(unsigned int *)&f) {}
//   hash32(double d) : m_u(((unsigned int*)&d)[0]| ((unsigned int*)&d)[1]) {}
//   template < typename T >
//   hash32(const ::pointer < T >& t) : m_u((unsigned int)(::uptr)t.m_p) {}
//   hash32(const ::hash32& hash32) : m_u(hash32.m_u) {}
//   hash32() {}
//
//};
//
//
//
//


