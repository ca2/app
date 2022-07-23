// Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:17 <3ThomasBorregaardSørensen!!
#pragma once


//#include "apex_main_data.h"


//namespace apex
//{


  // class application;


   //class library;


//} // namespace apex



extern "C"
typedef ::acme::library* NEW_LIBRARY();

typedef NEW_LIBRARY* PFN_NEW_LIBRARY;


extern "C"
typedef ::matter * NEW_MATTER();

typedef NEW_MATTER* PFN_NEW_MATTER;


struct CLASS_DECL_ACME apex_main_struct :
   public acme_main_struct
{


   bool                          m_bDataCentralRequired : 1;

   ::tristate                     m_bExperienceMainFrame;

   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                           m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_MATTER                m_pfnnewmatterApplication;
   PFN_NEW_LIBRARY               m_pfnnewlibrary;


   apex_main_struct();

   apex_main_struct& operator = (const apex_main_struct& mainstruct);
   

};



