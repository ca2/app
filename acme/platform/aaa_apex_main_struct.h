// acme/platform/apex_main_struct.h Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:17 <3ThomasBorregaardSørensen!!
// acme/platform/acme_main_struct.h Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
// acme/platform/acme_main_struct.h Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:17 <3ThomasBorregaardSørensen!!
#pragma once


#include "main.h"


// class CLASS_DECL_ACME acme_main_struct :
//    public ::main
// {
// public:
// //
// //
// //   //int                              m_argc;
// //   //char**                           m_argv;
// //   //char**                           m_envp;
// //   //wchar_t**                        m_wargv;
// //   //wchar_t**                        m_wenvp;
// //   //int                              m_iExitCode;
// //   //string                           m_strCommandLine;
// //   //string                           m_strAppId;
// //
// //
// //
// //   acme_main_data()
// //   {
// //
// //      m_argc = 0;
// //      m_argv = nullptr;
// //      m_envp = nullptr;
// //      m_wargv = nullptr;
// //      m_wenvp = nullptr;
// //      m_iExitCode = 0;
// //
// //   }
// //
// //
// //   void system_construct(main_arguments & mainarguments);
// //
// //
// //   //void system_construct(int argc, char** argv, char** envp);
// //  
// //
// //   //void system_construct(int argc, wchar_t** argv, wchar_t** envp);
// //
// //
// //   //void system_construct(const ::scoped_string & scopedstrCommandLine);
// //
// //
// };




// #pragma once


// //#include "apex_main_data.h"


// //namespace apex
// //{


//   // class application;


//    //class library;


// //} // namespace apex



extern "C"
typedef ::acme::library* NEW_LIBRARY();

typedef NEW_LIBRARY* PFN_NEW_LIBRARY;


extern "C"
typedef ::matter * NEW_MATTER();

typedef NEW_MATTER* PFN_NEW_MATTER;


struct CLASS_DECL_ACME main_struct :
   public ::main
{


   bool                          m_bDataCentralRequired : 1;

   ::tristate                    m_bExperienceMainFrame;

   ::i32_sz *                  m_pintstringLanguageResourceMap;
   int                           m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_MATTER                m_pfnnewmatterApplication;
   PFN_NEW_LIBRARY               m_pfnnewlibrary;


   apex_main_struct();

   apex_main_struct& operator = (const apex_main_struct& mainstruct);
   

};



