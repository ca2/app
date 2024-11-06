//
//  u32hash.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/22.
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
//  Refactoring by camilo on 2023-01-09 10:32 <3ThomasBorregaardSorensen!!
//
#pragma once


struct u32hash
{


   unsigned int m_u;


   u32hash() : m_u(0) {};
   template < typename T >
   u32hash(const T * p) : m_u((unsigned int)(::uptr)p) {};
   template < primitive_integral INTEGRAL >
   constexpr u32hash(INTEGRAL i) : m_u((unsigned int)i) { }
   template < primitive_enum ENUM >
   constexpr u32hash(ENUM e) : m_u((unsigned int)e) { }
   template < primitive_floating FLOATING >
   constexpr u32hash(FLOATING f) : u32hash(&f, sizeof(f)) { }
   template < typename T >
   constexpr u32hash(const ::pointer < T > & t) : u32hash(t.m_p) { }
   constexpr u32hash(const void * p, memsize s):m_u(0) { while (--s >= 0) m_u = (m_u << 5) ^ *((unsigned char*&)p)++; }


   constexpr ::u32hash operator + (::u32hash u) 
   {
      return (m_u << 16) ^ u.m_u; 
   }


};


template < typename T >
::u32hash unsigned_int_hash(const T & t) { return (::u32hash)t; }


//#include "acme/include/_numeric_concepts.h"
//#include "acme/prototype/prototype/enumeration.h"
//#include "acme/prototype/prototype/pointer.h"

//
//struct u32hash
//{
//
//   unsigned int m_u;
//
//
//   template < typename T >
//   u32hash(const T* p) : m_u((unsigned int)(::uptr)p) {}
//   template < primitive_integral INTEGRAL >
//   u32hash(INTEGRAL i) : m_u((unsigned int)i) {}
//   template < a_enum ENUM >
//   u32hash(const ::enumeration < ENUM > & e) : m_u((unsigned int)e.m_eenum) {}
//   u32hash(float f) : m_u(*(unsigned int *)&f) {}
//   u32hash(double d) : m_u(((unsigned int*)&d)[0]| ((unsigned int*)&d)[1]) {}
//   template < typename T >
//   u32hash(const ::pointer < T >& t) : m_u((unsigned int)(::uptr)t.m_p) {}
//   u32hash(const ::u32hash& u32hash) : m_u(u32hash.m_u) {}
//   u32hash() {}
//
//};
//
//
//
//


