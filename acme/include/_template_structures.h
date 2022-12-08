// Created by camilo on 2022-11-11 21:16 <3ThomasBorregaardSorensen!!
#pragma once


struct u32hash
{

   ::u32 m_u;


   template < typename T >
   u32hash(const T* p) : m_u((::u32)(::uptr)p) {}
   template < primitive_integral INTEGRAL >
   u32hash(INTEGRAL i) : m_u((::u32)i) {}
   template < a_enum ENUM >
   u32hash(const ::enumeration < ENUM > & e) : m_u((::u32)e.m_eenum) {}
   u32hash(::f32 f) : m_u(*(::u32 *)&f) {}
   u32hash(::f64 d) : m_u(((::u32*)&d)[0]| ((::u32*)&d)[1]) {}
   template < typename T >
   u32hash(const ::pointer < T >& t) : m_u((::u32)(::uptr)t.m_p) {}
   u32hash(const ::u32hash& u32hash) : m_u(u32hash.m_u) {}
   u32hash() {}

};





