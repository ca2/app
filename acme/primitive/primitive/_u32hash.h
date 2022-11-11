// Created by camilo on 2022-10-27 21:38 <3ThomasBorregaardSorensen!!
#pragma once


struct u32hash
{

   ::u32 m_u;


   template < typename T >
   u32hash(const T * p) : m_u((::u32)(::uptr)p) {}
   u32hash(::u32 u32) : m_u(u32) {}
   u32hash(const ::u32hash & u32hash) : m_u(u32hash.m_u) {}
   u32hash() {}

};


template<typename ARG_KEY>
inline u32hash u32_hash(ARG_KEY key) { return (u32hash)key; }


template<primitive_integral INTEGRAL>
inline u32hash u32_hash(INTEGRAL key) { return {(::u32) key}; }



