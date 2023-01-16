// Split into application_flags.h by camilo on 2022-11-29 23:06 <3ThomasBorregaardSørensen!!
// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSørensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
// ReCreated/Merged (from acme_main_data and apex_main_data) on 2022-09-25 01:35 BRT <3ThomasBorregaardSørensen!!
#pragma once


struct CLASS_DECL_ACME APPLICATION_FLAGS // : public ::acme::reference
{

   bool                             m_bFork;


   ::tristate                       m_bResource;
   ::tristate                       m_bCrypto;
   ::tristate                       m_bLocalization;
   ::tristate                       m_bNetworking;
   ::tristate                       m_bConsole;
   ::tristate                       m_bCreateAppShorcut;
   ::tristate                       m_bDraw2d;
   ::tristate                       m_bWriteText;
   ::tristate                       m_bUser;
   ::tristate                       m_bUserEx;
   ::tristate                       m_bImaging;
   ::tristate                       m_bAudio;
   ::tristate                       m_bMidi;
   ::tristate                       m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::tristate                       m_bGdiplus;
#elif defined(LINUX) || defined(FREEBSD)
   ::tristate                       m_bGtkApp;
#endif
   ::tristate                       m_bShowApplicationInformation;
   ::tristate                       m_bDataCentralRequired;

   ::tristate                       m_bExperienceMainFrame;
   ::tristate                       m_bVerbose;
//   //PFN_NEW_MATTER                   m_pfnnewmatterApplication;
//   //PFN_NEW_LIBRARY                  m_pfnnewlibrary;
//   PFN_DEFER_TERM                      m_pfnDeferTerm;

   APPLICATION_FLAGS();


   void copy_application_flags(const APPLICATION_FLAGS& applicationflags)
   {

      memcpy(this, &applicationflags, sizeof(APPLICATION_FLAGS));

   }


};


//#ifdef LINUX
//
//extern char _binary__matter_zip_start[] __attribute__((weak_import));
//extern char _binary__matter_zip_end[] __attribute__((weak_import));
//
//#endif



