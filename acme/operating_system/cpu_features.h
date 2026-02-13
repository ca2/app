// Created with ChatGPT by camilo on 2025-11-14 01:27 <3ThomasBorregaardSørensen!!
#pragma once



struct CLASS_DECL_ACME cpu_features
{


   bool  m_bFP      = false;
   bool  m_bSHA1   = false;
   bool m_bSHA2    = false;
   bool m_bCRC32  = false;
   bool  m_bAES    = false;
   bool m_bAtomics= false;
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



