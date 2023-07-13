// Split into application_flags.h by camilo on 2022-11-29 23:06 <3ThomasBorregaardSorensen!!
// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSorensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
// ReCreated/Merged (from acme_main_data and apex_main_data) on 2022-09-25 01:35 BRT <3ThomasBorregaardSorensen!!
#pragma once


struct CLASS_DECL_ACME APPLICATION_FLAGS // : public ::acme::reference
{

   bool                             m_bFork;


   ::boolean                       m_bResource;
   ::boolean                       m_bCrypto;
   ::boolean                       m_bLocalization;
   ::boolean                       m_bNetworking;
   ::boolean                       m_bConsole;
   ::boolean                       m_bSession;
   ::boolean                       m_bCreateAppShorcut;
   ::boolean                       m_bDraw2d;
   ::boolean                       m_bWriteText;
   ::boolean                       m_bUser;
   ::boolean                       m_bUserEx;
   ::boolean                       m_bImaging;
   ::boolean                       m_bAudio;
   ::boolean                       m_bMidi;
   ::boolean                       m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::boolean                       m_bGdiplus;
#elif defined(LINUX) || defined(FREEBSD)
   ::boolean                       m_bGtkApp;
#endif
   ::boolean                       m_bShowApplicationInformation;
   ::boolean                       m_bDataCentralRequired;

   ::boolean                       m_bExperienceMainFrame;
   ::boolean                       m_bVerbose;
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



