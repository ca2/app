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



