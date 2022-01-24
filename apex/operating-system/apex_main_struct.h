#pragma once


namespace apex
{


   class application;


   class library;


} // namespace apex


struct CLASS_DECL_APEX apex_main_struct :
   virtual public ::main
{


   bool                          m_bDataCentralRequired : 1;

   ::boolean                     m_bExperienceMainFrame;

   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                           m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_MATTER                m_pfnnewmatterApplication;
   PFN_NEW_LIBRARY               m_pfnnewlibrary;


   apex_main_struct();

   apex_main_struct& operator = (const apex_main_struct& mainstruct);
   

};



