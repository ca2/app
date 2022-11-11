#pragma once


inline u32hash hash_cat(u32hash uHash1, u32hash uHash2) { return uHash1.m_u << 16 | uHash2.m_u; }
inline u64 hash_cat(u64 uHash1, u64 uHash2) { return uHash1 << 32 | uHash2; }





//#if !defined(WINDOWS) && !defined(LINUX) && !defined(MACOS)
//
//template<>
//inline uptr u32_hash<const unichar *> (const unichar * key)
//{
//   return u32_hash<const u32* >((const u32*)key);
//}
//
//#endif



