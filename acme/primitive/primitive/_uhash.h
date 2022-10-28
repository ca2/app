// Created by camilo on 2022-10-27 21:38 <3ThomasBorregaardSorensen!!
#pragma once


template<typename ARG_KEY>
inline uptr uptr_hash(ARG_KEY key) { return (uptr)((uptr)key); }


//#if OSBIT == 64

template<typename ARG_KEY>
inline u32 u32_hash(ARG_KEY key) { return (u32)(uptr_hash<ARG_KEY>(key)); }

//#endif

