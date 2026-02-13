// Created with ChatGPT by camilo on 2025-11-14 01:05 <3ThomasBorregaardSørensen!!
// Created with ChatGPT by camilo on 2026-01-29 05:54 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "../cpu_features.h"
#include "acme/_operating_system.h"


// ======================= ARCH SELECTION =======================

#if defined(_M_X64) || defined(_M_IX86) || defined(__x86_64__) || defined(__i386__)
#define CPU_X86_FAMILY
#endif

#if defined(_M_ARM64) || defined(__aarch64__)
#define CPU_ARM64
#endif

#if defined(_M_ARM) || defined(__arm__)
#define CPU_ARM32
#endif


// ======================= INCLUDES ==============================

#if defined(CPU_X86_FAMILY)
#include <immintrin.h>
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(LINUX)
#include <cpuid.h>
#endif
#endif

#if defined(CPU_ARM64) || defined(CPU_ARM32)
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#endif
#endif


// ======================= IMPLEMENTATION =======================

cpu_features::cpu_features()
{
   // Default everything off
   m_bSSE = false;
   m_bAVX = false;
   m_bAVX2 = false;
   m_bNEON = false;

#if defined(CPU_X86_FAMILY)

   int cpuInfo[4] = { 0 };

   // -------- CPUID leaf 1 --------
   __cpuid(cpuInfo, 1);

   m_bSSE = (cpuInfo[3] & (1 << 25)) != 0; // SSE
   m_bAVX = (cpuInfo[2] & (1 << 28)) != 0; // AVX

   // OS support for XSAVE/XRESTORE
   bool osUsesXSAVE_XRSTORE = (cpuInfo[2] & (1 << 27)) != 0;
   if (m_bAVX && osUsesXSAVE_XRSTORE)
   {
      unsigned long long xcrFeatureMask =
         _xgetbv(_XCR_XFEATURE_ENABLED_MASK);

      // XMM (bit 1) and YMM (bit 2)
      m_bAVX = (xcrFeatureMask & 0x6) == 0x6;
   }
   else
   {
      m_bAVX = false;
   }

   // -------- CPUID leaf 7 --------
   __cpuid(cpuInfo, 7);
   m_bAVX2 = (cpuInfo[1] & (1 << 5)) != 0;


#elif defined(CPU_ARM64) || defined(CPU_ARM32)

   // ARM has no CPUID equivalent
   // SIMD is a compile-time capability

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
   m_bNEON = true;
#else
   m_bNEON = false;
#endif

   // ARM has no SSE / AVX
   m_bSSE = false;
   m_bAVX = false;
   m_bAVX2 = false;

#else

   // Unknown architecture → scalar only

#endif
}


namespace operating_system
{


   ::string machine_architecture()
   {

      USHORT processMachine = 0;
      USHORT nativeMachine = 0;

      ::string strArchitecture;

      if (!IsWow64Process2(GetCurrentProcess(),
         &processMachine,
         &nativeMachine))
      {
         
         throw ::exception(error_failed);

      }


      switch (nativeMachine)
      {
      case IMAGE_FILE_MACHINE_ARM64:
         strArchitecture = "arm64";
         break;

      case IMAGE_FILE_MACHINE_AMD64:
         strArchitecture = "x64";
         break;

      case IMAGE_FILE_MACHINE_I386:
         strArchitecture = "x86";
         break;

      default:
         strArchitecture = "unknown";
         break;
      }

      return strArchitecture;

   }


} // namespace operating_system



