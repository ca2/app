#pragma once


namespace apex
{


   class application;


   class library;


} // namespace apex





struct CLASS_DECL_APEX apex_main_struct
{

   bool                          m_bDataCentralRequired : 1;

   ::boolean                  m_bLocalization;
   ::boolean                  m_bConsole;
   ::boolean                  m_bDraw2d;
   ::boolean                  m_bWriteText;
   ::boolean                  m_bUser;
   ::boolean                  m_bUserEx;
   ::boolean                  m_bImaging;
   ::boolean                  m_bAudio;
   ::boolean                  m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::boolean                  m_bGdiplus;
#elif defined(LINUX)
   ::boolean                  m_bGtkApp;
#endif
   ::boolean                  m_bShowApplicationInformation;
   ::boolean                  m_bPreferNoFrameWindow;
   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                           m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_MATTER                m_pfnnewmatterApplication;
   PFN_NEW_LIBRARY               m_pfnnewlibrary;


   apex_main_struct()
   {

      m_bDataCentralRequired = false;

      m_pintstringLanguageResourceMap = nullptr;

      #if defined(ANDROID) || defined(_UWP) || defined(APPLE_IOS)

         m_iMatterFromHttpCache = 1;

      #elif defined(MACOS) || (defined(LINUX) && defined(DEBUG))

         m_iMatterFromHttpCache = -1; // -1 = overridable

      #else

         m_iMatterFromHttpCache = 0; // 0 = Roaming

      #endif
      
      m_pszMain = nullptr;
      m_pfnnewmatterApplication = nullptr;
      m_pfnnewlibrary = nullptr;
      
   }


   apex_main_struct & operator = (const apex_main_struct & mainstruct)
   {
      
      if(this != &mainstruct)
      {
         
         m_bLocalization = mainstruct.m_bLocalization;
         m_bConsole = mainstruct.m_bConsole;
         m_bDraw2d= mainstruct.m_bDraw2d;
         m_bWriteText = mainstruct.m_bWriteText;
         m_bUser= mainstruct.m_bUser;
         m_bUserEx= mainstruct.m_bUserEx;
         m_bImaging= mainstruct.m_bImaging;
         
         #ifdef WINDOWS_DESKTOP
         m_bGdiplus = mainstruct.m_bGdiplus;
         #elif defined(LINUX)
         m_bGtkApp = mainstruct.m_bGtkApp;
         #endif
         m_bShowApplicationInformation= mainstruct.m_bShowApplicationInformation;
         m_pintstringLanguageResourceMap= mainstruct.m_pintstringLanguageResourceMap;
         m_iMatterFromHttpCache= mainstruct.m_iMatterFromHttpCache;

         m_pszMain = mainstruct.m_pszMain;
         m_pfnnewmatterApplication = mainstruct.m_pfnnewmatterApplication;
         m_pfnnewlibrary = mainstruct.m_pfnnewlibrary;

      }
      
      return *this;
   }
   

   //void application_initialize();
   //void console_initialize();


};



