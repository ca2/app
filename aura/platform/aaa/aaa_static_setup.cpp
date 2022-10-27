#include "framework.h"
#include "system_setup.h"

::system_setup * system_setup::s_psetupList = nullptr;

system_setup::system_setup(::system_setup::enum_flag eflag, const ::string & pszName) :
   m_pszName(pszName),
   //m_pfnNewAuraApplication(nullptr),
   //m_pfnNewAuraLibrary(nullptr),
   m_eflag(eflag)
{

   construct();

}

//system_setup::system_setup(const ::string & lpszName, PFN_NEW_AURA_APPLICATION pfnNewAuraApplication) :
//   m_pszName(lpszName),
//   m_pfnNewAuraApplication(pfnNewAuraApplication),
//   m_pfnNewAuraLibrary(nullptr),
//   m_eflag(flag_application)
//{
//
//   construct();
//
//}
//
//
//system_setup::system_setup(const ::string & lpszName, PFN_NEW_AURA_LIBRARY pfnNewLibrary):
//   m_pszName(lpszName),
//   m_pfnNewAuraApplication(nullptr),
//   m_pfnNewAuraLibrary(pfnNewLibrary),
//   m_eflag(flag_library)
//{
//
//   construct();
//
//}


void system_setup::construct()
{

   m_ppropertysetupNext = s_psetupList;

   s_psetupList = this;

}


system_setup* system_setup::get_first(::system_setup::enum_flag eflag, const ::string & pszName)
{

   auto psetup = s_psetupList;

   while (psetup != nullptr)
   {

      if ((int)(psetup->m_eflag & eflag) == (int)eflag
         && (string(pszName).is_empty() || (!stricmp(pszName, psetup->m_pszName))))
      {

         return psetup;

      }

      psetup = psetup->m_ppropertysetupNext;

   }

   return nullptr;


}

//::system_setup * system_setup::get(const ::string & lpszName)
//{
//
//   if(s_papp == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   system_setup * papp = s_papp;
//
//   if (papp != nullptr && !ansi_cmp(lpszName, "acid"))
//   {
//
//      return papp;
//
//   }
//
//   while(papp != nullptr)
//   {
//
//      if(!ansi_compare_ci(papp->m_pszName, lpszName))
//      {
//
//         return papp;
//
//      }
//
//      papp = papp->m_pappNext;
//
//   }
//
//   return nullptr;
//
//}


//bool system_setup::has_flag(::system_setup::enum_flag eflag)
//{
//
//   auto psetup = s_psetupList;
//
//   while (psetup != nullptr)
//   {
//
//      if ((int)(psetup->m_eflag & eflag) == (int) eflag)
//      {
//
//         return true;
//
//      }
//
//      psetup = psetup->m_pappNext;
//
//   }
//
//   return false;
//
//}


::matter * system_setup::create_new_object()
{

   auto pparticle = new_object();

   if (::is_set(pparticle))
   {

      pparticle->set_generic_object_name(m_pszName);

   }

   return pparticle;

}


::aura::application* system_setup::create_new_application()
{

   auto papp = new_application();

   if (::is_set(papp))
   {

      papp->m_strAppId = m_pszName;

   }

   return papp;

}


::acme::library* system_setup::create_new_library()
{

   auto plibrary = new_library();

   if (::is_set(plibrary))
   {

      plibrary->m_strName = m_pszName;

   }

   return plibrary;

}



::matter * system_setup::new_object()
{

   return nullptr;

}


::aura::application* system_setup::new_application()
{

   return nullptr;

}


::acme::library* system_setup::new_library()
{

   return nullptr;

}
