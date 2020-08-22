#pragma once


namespace aura
{


   class library;
   class application;


} // namespace aura


extern "C" 
typedef ::aura::library * NEW_AURA_LIBRARY();

typedef NEW_AURA_LIBRARY * PFN_NEW_AURA_LIBRARY;

extern "C" 
typedef ::aura::application * NEW_AURA_APPLICATION();

typedef NEW_AURA_APPLICATION * PFN_NEW_AURA_APPLICATION;


typedef ::aura::application* __NEW_AURA_APPLICATION();

typedef __NEW_AURA_APPLICATION* __PFN_NEW_AURA_APPLICATION;


struct CLASS_DECL_AURA aura_main_struct
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
   PFN_NEW_AURA_APPLICATION      m_pfnNewAuraApplication;
   PFN_NEW_AURA_LIBRARY          m_pfnNewAuraLibrary;


   aura_main_struct() { memset(this, 0, sizeof(*this));
      
      
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



