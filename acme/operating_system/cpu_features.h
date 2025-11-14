// Created with ChatGPT by camilo on 2025-11-14 01:27 <3ThomasBorregaardSørensen!!
#pragma once



struct CLASS_DECL_ACME cpu_features
{


   bool m_bSSE = false;
   bool m_bAVX = false;
   bool m_bAVX2 = false;


   cpu_features();


};



static inline cpu_features g_cpufeatures;



