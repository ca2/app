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

   ::set                         m_bConsole;
   ::set                         m_bDraw2d;
   ::set                         m_bUser;
   ::set                         m_bUserEx;
   ::set                         m_bImaging;
#ifdef WINDOWS_DESKTOP
   ::set                         m_bGdiplus;
#elif defined(LINUX)
   ::set                         m_bGtkApp;
#endif
   ::set                         m_bShowApplicationInformation;
   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                           m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_APEX_APPLICATION      m_pfnNewAuraApplication;
   PFN_NEW_APEX_LIBRARY          m_pfnNewAuraLibrary;


   apex_main_struct()
   {
      
      //m_bConsole = false;
      //m_bDraw2d = true;
      //m_bUser = true;
      //m_bUserEx = true;
      //m_bImaging = true;
      //#ifdef WINDOWS_DESKTOP
      //m_bGdiplus = true;
      //#elif defined(LINUX)
      //m_bGtkApp = true;
      //#endif
      //m_bShowApplicationInformation = true;
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


   //void application_initialize();
   //void console_initialize();


};



