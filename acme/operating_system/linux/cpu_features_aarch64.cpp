//
// Linux aarch64 (Raspberry Pi OS) CPU feature detection
// Adapted from Apple Silicon version
// by camilo on 2026-02-01 16:02 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/operating_system/cpu_features.h"

// defined(__linux__) && defined(__aarch64__)

#include <sys/auxv.h>
#include <asm/hwcap.h>

cpu_features::cpu_features()
{
   const unsigned long hwcap  = getauxval(AT_HWCAP);
   const unsigned long hwcap2 = getauxval(AT_HWCAP2);

   // ---- SIMD / FP ----
   m_bNEON  = (hwcap & HWCAP_ASIMD) != 0;   // ARMv8 NEON (ASIMD)
   m_bFP    = (hwcap & HWCAP_FP)    != 0;

   // ---- Crypto ----
   m_bAES   = (hwcap & HWCAP_AES)   != 0;
   m_bSHA1  = (hwcap & HWCAP_SHA1)  != 0;
   m_bSHA2  = (hwcap & HWCAP_SHA2)  != 0;
   m_bCRC32 = (hwcap & HWCAP_CRC32) != 0;

   // ---- Atomics ----
   // ARMv8.1+ LSE atomics
   m_bAtomics = (hwcap & HWCAP_ATOMICS) != 0;

   // ---- No x86 features on ARM ----
   m_bSSE  = false;
   m_bAVX  = false;
   m_bAVX2 = false;
}

