// Created by camilo on 2022-10-27 21:38 <3ThomasBorregaardSorensen!!
#pragma once


struct u32hash
{

   u32 m_nHashValue;

};


template<typename ARG_KEY>
inline u32hash u32_hash(ARG_KEY key) { return (u32hash)key; }

template<primitive_integral INTEGRAL>
inline u32hash u32_hash(INTEGRAL key) { return { (::u32)key }; }

//#if OSBIT == 64

//template<typename ARG_KEY>
//inline u32 u32_hash(ARG_KEY key) { return (u32)(uptr_hash<ARG_KEY>(key)); }

//#endif

