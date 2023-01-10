//
//  u32hash.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
//  Refactoring by camilo on 2023-01-09 10:32 <3ThomasBorregaardSorensen!!
//
#pragma once


struct u32hash
{


   ::u32 m_u;


   u32hash() : m_u(0) {};
   template < typename T >
   u32hash(const T * p) : m_u((::u32)(::uptr)p) {};
   template < primitive_integral INTEGRAL >
   constexpr u32hash(INTEGRAL i) : m_u((::u32)i) { }
   template < primitive_enum ENUM >
   constexpr u32hash(ENUM e) : m_u((::u32)e) { }
   template < primitive_floating FLOATING >
   constexpr u32hash(FLOATING f) : u32hash(&f, sizeof(f)) { }
   template < typename T >
   constexpr u32hash(const ::pointer < T > & t) : u32hash(t.m_p) { }
   constexpr u32hash(const void * p, memsize s):m_u(0) { while (--s >= 0) m_u = (m_u << 5) ^ *((byte*&)p)++; }


   constexpr ::u32hash operator + (::u32hash u) 
   {
      return (m_u << 16) ^ u.m_u; 
   }


};


template < typename T >
::u32hash u32_hash(T t) { return (::u32hash)t; }


//#include "acme/include/_numeric_concepts.h"
//#include "acme/primitive/primitive/enumeration.h"
//#include "acme/primitive/primitive/pointer.h"

//
//struct u32hash
//{
//
//   ::u32 m_u;
//
//
//   template < typename T >
//   u32hash(const T* p) : m_u((::u32)(::uptr)p) {}
//   template < primitive_integral INTEGRAL >
//   u32hash(INTEGRAL i) : m_u((::u32)i) {}
//   template < a_enum ENUM >
//   u32hash(const ::enumeration < ENUM > & e) : m_u((::u32)e.m_eenum) {}
//   u32hash(::f32 f) : m_u(*(::u32 *)&f) {}
//   u32hash(::f64 d) : m_u(((::u32*)&d)[0]| ((::u32*)&d)[1]) {}
//   template < typename T >
//   u32hash(const ::pointer < T >& t) : m_u((::u32)(::uptr)t.m_p) {}
//   u32hash(const ::u32hash& u32hash) : m_u(u32hash.m_u) {}
//   u32hash() {}
//
//};
//
//
//
//



