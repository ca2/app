#pragma once


namespace acme
{


   class library;
   class application;


} // namespace acme


extern "C" 
typedef ::acme::library * NEW_ace_LIBRARY();

typedef NEW_ace_LIBRARY * PFN_NEW_ace_LIBRARY;

extern "C" 
typedef ::acme::application * NEW_ace_APPLICATION();

typedef NEW_ace_APPLICATION * PFN_NEW_ace_APPLICATION;


typedef ::acme::application* __NEW_ace_APPLICATION();

typedef __NEW_ace_APPLICATION* __PFN_NEW_ace_APPLICATION;


struct CLASS_DECL_ACME ace_main_struct
{

   bool                          m_bConsole;
   bool                          m_bDraw2d;
   bool                          m_bUser;
   bool                          m_bUserEx;
#if defined(LINUX)
   bool                             m_bGtkApp;
#endif
   bool                          m_bShowApplicationInformation;
   INT_STRING *                  m_pintstringLanguageResourceMap;
   int                              m_iMatterFromHttpCache;

   const char *                  m_pszMain;
   PFN_NEW_ace_APPLICATION      m_pfnNewaceApplication;
   PFN_NEW_ace_LIBRARY          m_pfnNewaceLibrary;


   ace_main_struct() { memset(this, 0, sizeof(*this));
      
      
      #if defined(ANDROID) || defined(_UWP) || defined(APPLE_IOS)

         m_iMatterFromHttpCache = 1;

      #elif defined(MACOS) || (defined(LINUX) && defined(DEBUG))

         m_iMatterFromHttpCache = -1; // -1 = overridable

      #else

         m_iMatterFromHttpCache = 0; // 0 = Roaming

      #endif
      
   }

   
   void application_initialize();
   void console_initialize();


};



