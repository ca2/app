//
// Apple Silicon CPU feature detection
// Created on 2026-01-21 07:54 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"
#define user __apple__user
#include <sys/sysctl.h>
#include <cstring>

#if defined(__APPLE__) && defined(__aarch64__)

static bool sysctl_bool(const char* name)
{
   int value = 0;
   size_t size = sizeof(value);
   if (sysctlbyname(name, &value, &size, nullptr, 0) != 0)
      return false;
   return value != 0;
}

cpu_features::cpu_features()
{
   // ---- SIMD / FP ----
   m_bNEON        = sysctl_bool("hw.optional.neon");
   m_bFP          = sysctl_bool("hw.optional.floatingpoint");

   // ---- Crypto ----
   m_bAES         = sysctl_bool("hw.optional.arm.FEAT_AES");
   m_bSHA1        = sysctl_bool("hw.optional.arm.FEAT_SHA1");
   m_bSHA2        = sysctl_bool("hw.optional.arm.FEAT_SHA256");
   m_bCRC32       = sysctl_bool("hw.optional.armv8_crc32");

   // ---- Atomics ----
   m_bAtomics     = sysctl_bool("hw.optional.armv8_1_atomics");

   // ---- No x86 features on ARM ----
   m_bSSE         = false;
   m_bAVX         = false;
   m_bAVX2        = false;
}

#endif
