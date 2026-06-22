//
// Android aarch64 CPU feature detection
// Adapted from Linux version with ChatGPT by
// camilo on 2026-02-05 14:50 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"

#include <cpu-features.h>
#include <string.h>
#include <sys/utsname.h>

cpu_features::cpu_features()
{
   uint64_t features = android_getCpuFeatures();
   AndroidCpuFamily family = android_getCpuFamily();

   // Default all to false
   m_bNEON = false;
   m_bFP = false;
   m_bAES = false;
   m_bSHA1 = false;
   m_bSHA2 = false;
   m_bCRC32 = false;
   m_bAtomics = false;

   m_bSSE = false;
   m_bAVX = false;
   m_bAVX2 = false;

   if (family == ANDROID_CPU_FAMILY_ARM64)
   {
      // ---- SIMD / FP ----
      m_bNEON = true;   // Always present on ARM64
      m_bFP   = true;   // Always present on ARM64

      // ---- Crypto ----
      m_bAES   = (features & ANDROID_CPU_ARM64_FEATURE_AES)   != 0;
      m_bSHA1  = (features & ANDROID_CPU_ARM64_FEATURE_SHA1)  != 0;
      m_bSHA2  = (features & ANDROID_CPU_ARM64_FEATURE_SHA2)  != 0;
      m_bCRC32 = (features & ANDROID_CPU_ARM64_FEATURE_CRC32) != 0;


#if defined(ANDROID_CPU_ARM64_FEATURE_ATOMICS)

      // ---- Atomics ----
      m_bAtomics = (features & ANDROID_CPU_ARM64_FEATURE_ATOMICS) != 0;

#else

      m_bAtomics = false;


#endif
   }
}


namespace operating_system
{


   ::string machine_architecture()
   {

      auto family = android_getCpuFamily();

      switch (family)
      {
      case ANDROID_CPU_FAMILY_ARM64:
         return "arm64";
      case ANDROID_CPU_FAMILY_ARM:
         return "arm";
      case ANDROID_CPU_FAMILY_X86_64:
         return "x86_64";
      case ANDROID_CPU_FAMILY_X86:
         return "x86";
      default:
         break;
      }

      struct utsname u;

      if (uname(&u) == 0)
      {

         if (!strcmp(u.machine, "aarch64"))
         {

            return "arm64";

         }
         else if (!strcmp(u.machine, "armv7l") || !strcmp(u.machine, "armv8l"))
         {

            return "arm";

         }
         else if (!strcmp(u.machine, "x86_64"))
         {

            return "x86_64";

         }
         else if (!strcmp(u.machine, "i386") || !strcmp(u.machine, "i686"))
         {

            return "x86";

         }

         return u.machine;

      }

#if defined(__aarch64__)
      return "arm64";
#elif defined(__arm__)
      return "arm";
#elif defined(__x86_64__)
      return "x86_64";
#elif defined(__i386__)
      return "x86";
#else
      return "(Unknown architecture)";
#endif

   }


} // namespace operating_system



