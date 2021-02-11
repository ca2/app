#pragma once


namespace apex
{


   class library;
   class application;


} // namespace apex


extern "C"
typedef ::apex::library * NEW_APEX_LIBRARY();

typedef NEW_APEX_LIBRARY * PFN_NEW_APEX_LIBRARY;

typedef ::apex::application* NEW_APEX_APPLICATION();

typedef NEW_APEX_APPLICATION* PFN_NEW_APEX_APPLICATION;


struct CLASS_DECL_APEX apex_main_struct
{

   ::logic::bit                  m_bLocalization;
   ::logic::bit                  m_bConsole;
   ::logic::bit                  m_bDraw2d;
   ::logic::bit                  m_bWriteText;
   ::logic::bit                  m_bUser;
   ::logic::bit                  m_bUserEx;
   ::logic::bit                  m_bImaging;
#ifdef WINDOWS_DESKTOP
   ::logic::bit                  m_bGdiplus;
#elif defined(LINUX)
   ::logic::bit                  m_bGtkApp;
#endif
   ::logic::bit                         m_bShowApplicationInformation;
   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                           m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_APEX_APPLICATION      m_pfnNewAuraApplication;
   PFN_NEW_APEX_LIBRARY          m_pfnNewAuraLibrary;


   apex_main_struct()
   {
      

      m_pintstringLanguageResourceMap = nullptr;

      #if defined(ANDROID) || defined(_UWP) || defined(APPLE_IOS)

         m_iMatterFromHttpCache = 1;

      #elif defined(MACOS) || (defined(LINUX) && defined(DEBUG))

         m_iMatterFromHttpCache = -1; // -1 = overridable

      #else

         m_iMatterFromHttpCache = 0; // 0 = Roaming

      #endif
      
      m_pszMain = nullptr;
      m_pfnNewAuraApplication = nullptr;
      m_pfnNewAuraLibrary = nullptr;
      
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
         m_pfnNewAuraApplication = mainstruct.m_pfnNewAuraApplication;
         m_pfnNewAuraLibrary = mainstruct.m_pfnNewAuraLibrary;

      }
      
      return *this;
   }
   

   //void application_initialize();
   //void console_initialize();


};



