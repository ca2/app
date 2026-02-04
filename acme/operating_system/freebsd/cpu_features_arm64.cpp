//
// Created by camilo on 2026-01-02 17:47 <3ThomasBorregaardSørensen!!
//
//
// Changed by camilo on 2026-02-02 09:44 <3ThomasBorregaardSørensen!!
//
// Changed by camilo on 2026-02-03 07:44 <3ThomasBorregaardSørensen!!

#include "framework.h"
#include "acme/operating_system/cpu_features.h"

#include <sys/types.h>
#include <sys/sysctl.h>
#include <cstdint>

cpu_features::cpu_features()
{

   // x86-only features — never available on ARM
   m_bSSE  = false;
   m_bAVX  = false;
   m_bAVX2 = false;

   int value = 0;
   size_t size = sizeof(value);

   // NEON (always present on ARM64, but sysctl confirms it)
   if (sysctlbyname("hw.optional.neon", &value, &size, nullptr, 0) == 0)
      m_bNEON = (value != 0);
   else
      m_bNEON = true; // ARM64 guarantees NEON

   // Optional ARMv8 features (if you care)
   m_bAES = false;
   size = sizeof(value);
   if (sysctlbyname("hw.optional.armv8_aes", &value, &size, nullptr, 0) == 0)
      m_bAES = (value != 0);

   m_bSHA2 = false;
   size = sizeof(value);
   if (sysctlbyname("hw.optional.armv8_sha2", &value, &size, nullptr, 0) == 0)
      m_bSHA2 = (value != 0);


}
