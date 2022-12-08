//
//  u32hash.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/22.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


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
