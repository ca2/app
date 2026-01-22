//
// Created by camilo on 2025-12-19 17:47 <3ThomasBorregaardSørensen!!
// Created on 2026-01-21 07:51 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"
#include <cstdint>

#if defined(__x86_64__) || defined(__i386__)

/*
   macOS does NOT provide <cpuid.h>.
   We must implement cpuid ourselves.
*/

static inline void cpuid(uint32_t leaf,
                         uint32_t subleaf,
                         uint32_t& eax,
                         uint32_t& ebx,
                         uint32_t& ecx,
                         uint32_t& edx)
{
#if defined(__i386__) && defined(__PIC__)
   // EBX is reserved for PIC on 32-bit
   __asm__ volatile (
      "xchg %%ebx, %1\n\t"
      "cpuid\n\t"
      "xchg %%ebx, %1\n\t"
      : "=a"(eax), "=&r"(ebx), "=c"(ecx), "=d"(edx)
      : "a"(leaf), "c"(subleaf)
   );
#else
   __asm__ volatile (
      "cpuid"
      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
      : "a"(leaf), "c"(subleaf)
   );
#endif
}

static inline uint64_t xgetbv(uint32_t index)
{
   uint32_t eax, edx;
   __asm__ volatile (
      ".byte 0x0f, 0x01, 0xd0" // xgetbv
      : "=a"(eax), "=d"(edx)
      : "c"(index)
   );
   return (uint64_t(edx) << 32) | eax;
}

cpu_features::cpu_features()
{
   uint32_t eax = 0, ebx = 0, ecx = 0, edx = 0;

   // ---- CPUID leaf 1: SSE / AVX / OSXSAVE ----
   cpuid(1, 0, eax, ebx, ecx, edx);

   m_bSSE = (edx & (1u << 25)) != 0; // SSE
   m_bAVX = (ecx & (1u << 28)) != 0; // AVX

   bool osUsesXSAVE_XRSTORE = (ecx & (1u << 27)) != 0; // OSXSAVE

   if (m_bAVX && osUsesXSAVE_XRSTORE)
   {
      // Check XCR0: XMM (bit 1) and YMM (bit 2)
      uint64_t xcr0 = xgetbv(0);
      m_bAVX = (xcr0 & 0x6) == 0x6;
   }
   else
   {
      m_bAVX = false;
   }

   // ---- CPUID leaf 7, subleaf 0: AVX2 ----
   cpuid(7, 0, eax, ebx, ecx, edx);
   m_bAVX2 = (ebx & (1u << 5)) != 0; // AVX2
}

//#else
//
//// Non-x86 fallback (Apple Silicon, etc.)
//cpu_features::cpu_features()
//{
//   m_bSSE  = false;
//   m_bAVX  = false;
//   m_bAVX2 = false;
//}
//
#endif
