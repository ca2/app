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

   bool                          m_bConsole;
   bool                          m_bDraw2d;
   bool                          m_bUser;
   bool                          m_bUserEx;
   bool                          m_bImaging;
#ifdef WINDOWS_DESKTOP
   bool                          m_bGdiplus;
#elif defined(LINUX)
   bool                          m_bGtkApp;
#endif
   bool                          m_bShowApplicationInformation;
   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                              m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_APEX_APPLICATION      m_pfnNewAuraApplication;
   PFN_NEW_APEX_LIBRARY          m_pfnNewAuraLibrary;


   apex_main_struct()
   {
      
      m_bConsole = false;
      m_bDraw2d = false;
      m_bUser = false;
      m_bUserEx = false;
      m_bImaging = false;
      #ifdef WINDOWS_DESKTOP
      m_bGdiplus = false;
      #elif defined(LINUX)
      m_bGtkApp = false;
      #endif
      m_bShowApplicationInformation = false;
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


   void application_initialize();
   void console_initialize();


};



