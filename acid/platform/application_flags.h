// Split into application_flags.h by camilo on 2022-11-29 23:06 <3ThomasBorregaardSorensen!!
// ReCreated/Merged (from ace_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSorensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
// ReCreated/Merged (from ace_main_data and apex_main_data) on 2022-09-25 01:35 BRT <3ThomasBorregaardSorensen!!
#pragma once


struct CLASS_DECL_ACID APPLICATION_FLAGS // : public ::acid::reference
{

   bool                             m_bFork;


   ::logic::boolean                       m_bResource;
   ::logic::boolean                       m_bCrypto;
   ::logic::boolean                       m_bLocalization;
   ::logic::boolean                       m_bNetworking;
   //::logic::boolean                       m_bConsole;
   ::logic::boolean                       m_bSession;
   ::logic::boolean                       m_bCreateAppShorcut;
   ::logic::boolean                       m_bDraw2d;
   ::logic::boolean                       m_bWriteText;
   ::logic::boolean                       m_bUser;
   ::logic::boolean                       m_bUserEx;
   ::logic::boolean                       m_bImaging;
   ::logic::boolean                       m_bAudio;
   ::logic::boolean                       m_bMidi;
   ::logic::boolean                       m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::logic::boolean                       m_bGdiplus;
#elif defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
   ::logic::boolean                       m_bGtkApp;
#endif
   ::logic::boolean                       m_bShowApplicationInformation;
   ::logic::boolean                       m_bDataCentralRequired;

   ::logic::boolean                       m_bExperienceMainFrame;
   ::logic::boolean                       m_bVerbose;
//   //PFN_NEW_MATTER                   m_pfnnewmatterApplication;
//   //PFN_NEW_LIBRARY                  m_pfnnewlibrary;
//   PFN_DEFER_TERM                      m_pfnDeferTerm;

   APPLICATION_FLAGS();


   void copy_application_flags(const APPLICATION_FLAGS& applicationflags)
   {

      memory_copy(this, &applicationflags, sizeof(APPLICATION_FLAGS));

   }


};


//#ifdef LINUX
//
//extern char _binary__matter_zip_start[] __attribute__((weak_import));
//extern char _binary__matter_zip_end[] __attribute__((weak_import));
//
//#endif



