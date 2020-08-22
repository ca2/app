#pragma once

#ifdef index
#undef index
#endif // index


typedef iptr index;


#define __priindex PRIiPTR


CLASS_DECL_AURA extern const char log2_LogTable256[256];

//inline bool __found(::index i) { return i >= 0; }
//inline bool __not_found(::index i) { return i < 0; }
//inline bool __found(::index i) { return i >= 0; }
//inline bool __not_found(::index i) { return i < 0; }

inline u32 u32_log2(u32 v)
{

   //unsigned int v; // 32-bit word to find the log of
   unsigned r;     // r will be lg(v)
   unsigned int t, tt; // temporaries

   if ((tt = (v >> 16)))
   {
      r = (t = tt >> 8) ? 24 + log2_LogTable256[t] : 16 + log2_LogTable256[tt];
   }
   else
   {
      r = (t = v >> 8) ? 8 + log2_LogTable256[t] : log2_LogTable256[v];
   }

   return r;
}
