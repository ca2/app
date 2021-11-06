#pragma once


inline u32 hash_cat(u32 uHash1, u32 uHash2) { return uHash1 << 16 | uHash2; }
inline u64 hash_cat(u64 uHash1, u64 uHash2) { return uHash1 << 32 | uHash2; }





//#if !defined(WINDOWS) && !defined(LINUX) && !defined(MACOS)
//
//template<>
//inline uptr uptr_hash<const unichar *> (const unichar * key)
//{
//   return uptr_hash<const u32* >((const u32*)key);
//}
//
//#endif



