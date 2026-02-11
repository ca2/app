//
// Created by camilo on 2026-01-02 17:47 <3ThomasBorregaardSørensen!!
//
//
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <x86intrin.h>  // For xgetbv
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
   __asm__ volatile (
       "cpuid"
       : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
       : "a"(1)
   );

   m_bSSE = (edx & (1u << 25)) != 0; // SSE
   m_bAVX = (ecx & (1u << 28)) != 0; // AVX

   bool osUsesXSAVE_XRSTORE = (ecx & (1u << 27)) != 0; // OSXSAVE

   if (m_bAVX && osUsesXSAVE_XRSTORE)
   {
      // Check XCR0 for XMM (bit 1) and YMM (bit 2)
      uint64_t xcrFeatureMask = xgetbv(0);
      m_bAVX = (xcrFeatureMask & 0x6) == 0x6;
   }

   // CPUID leaf 7, subleaf 0: AVX2
   __asm__ volatile (
       "cpuid"
       : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
       : "a"(7), "c"(0)
   );
   m_bAVX2 = (ebx & (1u << 5)) != 0; // AVX2
}



#include "framework.h"
#include <sys/utsname.h>
#include <string.h>


namespace operating_system
{

// From linux/cpu_features.cpp by camilo on 2026-02-09 12:49 <3ThomasBorregaardSørensen!!

   ::string machine_architecture()
   {

      struct utsname u;

      uname(&u);

      //if (!strcmp(u.machine, "aarch64"))
      {

        // return "aarch64";

      }
      //else if (!strcmp(u.machine, "x86_64"))
      {

        // return "x86_64";

      }
      //else
      {

        // return "(Unknown architecture)";
        return u.machine;

      }

   }


} // namespace operating_system


