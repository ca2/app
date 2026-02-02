// Created with ChatGPT by camilo on 2025-11-14 01:27 <3ThomasBorregaardSørensen!!
#pragma once



struct CLASS_DECL_ACME cpu_features
{


#if (defined(__APPLE__) || defined(LINUX)) && defined(__aarch64__)

// ---- SIMD / FP ----
    bool  m_bFP      = false;

   // ---- Crypto ----
    bool  m_bAES    = false;
    bool  m_bSHA1   = false;
    bool m_bSHA2    = false;
    bool m_bCRC32  = false;

   // ---- Atomics ----
    bool m_bAtomics= false;
#endif
    
    

   bool m_bNEON = false;
   bool m_bSSE = false;
   bool m_bAVX = false;
   bool m_bAVX2 = false;


   cpu_features();


};



static inline cpu_features g_cpufeatures;



namespace operating_system
{

   
   CLASS_DECL_ACME ::string machine_architecture();


} // namespace operating_system



