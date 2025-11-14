// Created with ChatGPT by camilo on 2025-11-14 01:05 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "cpu_features.h"
#include <immintrin.h>


//CLASS_DECL_ACME int g_iCpuFeatures; // 0=scalar,1=SSE,2=AVX,3=AVX2
//
//// ---------------- CPU Feature Detection ----------------
//#if defined(_MSC_VER)
//#include <intrin.h>
//#else
//#include <cpuid.h>
//#endif
//
//CLASS_DECL_ACME void detect_cpu_features()
//{
//   int features = 0;
//#if defined(_MSC_VER)
//   int info[4];
//   __cpuid(info, 1);
//   bool sse_present = (info[3] & (1 << 25)) != 0;
//   bool sse2_present = (info[3] & (1 << 26)) != 0;
//   bool avx_supported = (info[2] & (1 << 28)) != 0;
//   bool osxsave = (info[2] & (1 << 27)) != 0;
//   if (avx_supported && osxsave)
//   {
//      unsigned long long xcr = _xgetbv(0);
//      if ((xcr & 0x6) == 0x6)
//         features = 2; // AVX
//   }
//   else if (sse_present && sse2_present)
//      features = 1;
//   int info7[4];
//   __cpuidex(info7, 7, 0);
//   if (info7[1] & (1 << 5))
//      features = 3; // AVX2
//#else
//   unsigned int eax, ebx, ecx, edx;
//   __cpuid(1, eax, ebx, ecx, edx);
//   bool sse_present = (edx & (1 << 25)) != 0;
//   bool sse2_present = (edx & (1 << 26)) != 0;
//   bool avx_supported = (ecx & (1 << 28)) != 0;
//   bool osxsave = (ecx & (1 << 27)) != 0;
//   if (avx_supported && osxsave)
//   {
//      unsigned int xcr0_lo, xcr0_hi;
//      asm volatile("xgetbv" : "=a"(xcr0_lo), "=d"(xcr0_hi) : "c"(0));
//      if ((xcr0_lo & 0x6) == 0x6)
//         features = 2; // AVX
//   }
//   else if (sse_present && sse2_present)
//      features = 1;
//   unsigned int eax7, ebx7, ecx7, edx7;
//   __cpuid_count(7, 0, eax7, ebx7, ecx7, edx7);
//   if (ebx7 & (1 << 5))
//      features = 3; // AVX2
//#endif
//   g_iCpuFeatures = features;
//}
//




//CLASS_DECL_ACME enum_cpu detect_cpu()
//{
//   enum_cpu flags = e_cpu_none;
//
//   int info[4];
//   __cpuid(info, 1);
//   if (info[3] & (1 << 25))
//      flags = enum_cpu(uint32_t(flags) | uint32_t(e_cpu_sse)); // SSE
//   if (info[2] & (1 << 28))
//      flags = enum_cpu(uint32_t(flags) | uint32_t(e_cpu_avx)); // AVX
//
//   __cpuid(info, 7);
//   if (info[1] & (1 << 5))
//      flags = enum_cpu(uint32_t(flags) | uint32_t(e_cpu_avx2)); // AVX2
//
//   return flags;
//}
//
////// Global runtime-detected flag
////inline CPUFlags g_cpuFlags = detect_cpu_flags();
//


cpu_features::cpu_features()
{
   int cpuInfo[4] = {0};

   // Get SSE / AVX support
   __cpuid(cpuInfo, 1);
   m_bSSE = (cpuInfo[3] & (1 << 25)) != 0; // SSE
   m_bAVX = (cpuInfo[2] & (1 << 28)) != 0; // AVX

   // Check OS support for XSAVE/XRESTORE
   bool osUsesXSAVE_XRSTORE = (cpuInfo[2] & (1 << 27)) != 0;
   if (m_bAVX && osUsesXSAVE_XRSTORE)
   {
      unsigned long long xcrFeatureMask = _xgetbv(_XCR_XFEATURE_ENABLED_MASK);
      m_bAVX &= (xcrFeatureMask & 0x6) == 0x6; // XMM and YMM state enabled
   }

   // AVX2 support
   __cpuid(cpuInfo, 7);
   m_bAVX2 = (cpuInfo[1] & (1 << 5)) != 0; // AVX2

}
