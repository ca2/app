//
// Android aarch64 CPU feature detection
// Adapted from Linux version with ChatGPT by
// camilo on 2026-02-05 14:50 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"

#include <cpu-features.h>

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



