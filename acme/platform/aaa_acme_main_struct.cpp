// apex_main_struct constructor by camilo on 2021-11-16 14:53 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


apex_main_struct::apex_main_struct()
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

   if (m_bExperienceMainFrame.is_none())
   {

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

      m_bExperienceMainFrame = false;

#else 

      m_bExperienceMainFrame = true;

#endif

   }

   m_pszMain = nullptr;
   m_pfnnewmatterApplication = nullptr;
   m_pfnnewlibrary = nullptr;

}


apex_main_struct& apex_main_struct::operator = (const apex_main_struct& mainstruct)
{

   if (this != &mainstruct)
   {

      m_bLocalization = mainstruct.m_bLocalization;
      m_bConsole = mainstruct.m_bConsole;
      m_bDraw2d = mainstruct.m_bDraw2d;
      m_bWriteText = mainstruct.m_bWriteText;
      m_bUser = mainstruct.m_bUser;
      m_bUserEx = mainstruct.m_bUserEx;
      m_bImaging = mainstruct.m_bImaging;
      m_bAudio = mainstruct.m_bAudio;
      m_bMidi = mainstruct.m_bMidi;

#ifdef WINDOWS_DESKTOP
      m_bGdiplus = mainstruct.m_bGdiplus;
#elif defined(LINUX)
      m_bGtkApp = mainstruct.m_bGtkApp;
#endif
      m_bShowApplicationInformation = mainstruct.m_bShowApplicationInformation;
      m_pintstringLanguageResourceMap = mainstruct.m_pintstringLanguageResourceMap;
      m_iMatterFromHttpCache = mainstruct.m_iMatterFromHttpCache;

      m_pszMain = mainstruct.m_pszMain;
      m_pfnnewmatterApplication = mainstruct.m_pfnnewmatterApplication;
      m_pfnnewlibrary = mainstruct.m_pfnnewlibrary;

   }

   return *this;
}


