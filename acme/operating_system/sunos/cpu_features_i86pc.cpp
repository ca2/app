//
// Linux cpufeatureamd64 by camilo on 2025-12-19 17:47 <3ThomasBorregaardSørensen!!
// For sunos i86pc by camilo on 2026-09-28 16:14 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//

#include "platform.h"
#include "acme/operating_system/cpu_features.h"


#if defined(__i386__) || defined(__x86_64__) || defined(__amd64__)

#include <cpuid.h>
#include <cstdint>


static inline uint64_t xgetbv(uint32_t index)
{

   uint32_t eax = 0;

   uint32_t edx = 0;


   __asm__ volatile(
      ".byte 0x0f, 0x01, 0xd0"
      : "=a"(eax), "=d"(edx)
      : "c"(index));


   return ((uint64_t)edx << 32) | eax;

}


cpu_features::cpu_features()
{

   ::u32 eax = 0;

   ::u32 ebx = 0;

   ::u32 ecx = 0;

   ::u32 edx = 0;


   m_bSSE = false;

   m_bAVX = false;

   m_bAVX2 = false;


   //
   // Get maximum supported basic CPUID leaf.
   //

   auto uMaximumLeaf = __get_cpuid_max(0, nullptr);


   //
   // CPUID leaf 1
   //
   // EDX bit 25 = SSE
   //
   // ECX bit 27 = OSXSAVE
   // ECX bit 28 = AVX
   //

   if(uMaximumLeaf >= 1)
   {

      if(__get_cpuid(1, &eax, &ebx, &ecx, &edx))
      {

         m_bSSE =
            (edx & (1u << 25)) != 0;


         bool bCpuHasAVX =
            (ecx & (1u << 28)) != 0;


         bool bOSUsesXSAVE =
            (ecx & (1u << 27)) != 0;


         if(bCpuHasAVX && bOSUsesXSAVE)
         {

            //
            // XGETBV is valid here because OSXSAVE is set.
            //
            // XCR0:
            //
            // bit 1 = XMM state
            // bit 2 = YMM state
            //
            // Both must be enabled by the OS before AVX instructions
            // can safely be used by this process.
            //

            auto xcrFeatureMask =
               xgetbv(0);


            m_bAVX =
               (xcrFeatureMask & 0x6) == 0x6;

         }

      }

   }


   //
   // CPUID leaf 7, subleaf 0
   //
   // EBX bit 5 = AVX2
   //
   // Only report AVX2 if AVX state is actually usable by the OS.
   //

   if(m_bAVX && uMaximumLeaf >= 7)
   {

      eax = 0;

      ebx = 0;

      ecx = 0;

      edx = 0;


      __cpuid_count(
         7,
         0,
         eax,
         ebx,
         ecx,
         edx);


      m_bAVX2 =
         (ebx & (1u << 5)) != 0;

   }

}


#else


cpu_features::cpu_features()
{

   m_bSSE = false;

   m_bAVX = false;

   m_bAVX2 = false;

}


#endif
