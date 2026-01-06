//
// Created by camilo on 2025-12-19 17:47 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"
#include <cpuid.h>     // __get_cpuid, __cpuid_count
//#include <immintrin.h> // _xgetbv
#include <cstdint>



static inline uint64_t xgetbv(uint32_t index)
{
   uint32_t eax, edx;
   __asm__ volatile (
       ".byte 0x0f, 0x01, 0xd0" // xgetbv
       : "=a"(eax), "=d"(edx)
       : "c"(index)
   );
   return ((uint64_t)edx << 32) | eax;
}
cpu_features::cpu_features()
{
   unsigned int eax, ebx, ecx, edx;

   // CPUID leaf 1: SSE / AVX / XSAVE
   if (__get_cpuid(1, &eax, &ebx, &ecx, &edx))
   {
      m_bSSE = (edx & (1u << 25)) != 0; // SSE
      m_bAVX = (ecx & (1u << 28)) != 0; // AVX

      bool osUsesXSAVE_XRSTORE = (ecx & (1u << 27)) != 0; // OSXSAVE

      if (m_bAVX && osUsesXSAVE_XRSTORE)
      {
         // Check XCR0 for XMM (bit 1) and YMM (bit 2)
         uint64_t xcrFeatureMask = xgetbv(0);
         m_bAVX = (xcrFeatureMask & 0x6) == 0x6;
      }
   }
   else
   {
      m_bSSE  = false;
      m_bAVX  = false;
   }

   // CPUID leaf 7, subleaf 0: AVX2
   __cpuid_count(7, 0, eax, ebx, ecx, edx);
   m_bAVX2 = (ebx & (1u << 5)) != 0; // AVX2
}