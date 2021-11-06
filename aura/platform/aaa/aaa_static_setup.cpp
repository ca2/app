#include "framework.h"
#include "static_setup.h"

::static_setup * static_setup::s_psetupList = nullptr;

static_setup::static_setup(::static_setup::enum_flag eflag, const ::string & pszName) :
   m_pszName(pszName),
   //m_pfnNewAuraApplication(nullptr),
   //m_pfnNewAuraLibrary(nullptr),
   m_eflag(eflag)
{

   construct();

}

//static_setup::static_setup(const ::string & lpszName, PFN_NEW_AURA_APPLICATION pfnNewAuraApplication) :
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
//static_setup::static_setup(const ::string & lpszName, PFN_NEW_AURA_LIBRARY pfnNewLibrary):
//   m_pszName(lpszName),
//   m_pfnNewAuraApplication(nullptr),
//   m_pfnNewAuraLibrary(pfnNewLibrary),
//   m_eflag(flag_library)
//{
//
//   construct();
//
//}


void static_setup::construct()
{

   m_ppropertysetupNext = s_psetupList;

   s_psetupList = this;

}


static_setup* static_setup::get_first(::static_setup::enum_flag eflag, const ::string & pszName)
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

//::static_setup * static_setup::get(const ::string & lpszName)
//{
//
//   if(s_papp == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   static_setup * papp = s_papp;
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


//bool static_setup::has_flag(::static_setup::enum_flag eflag)
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


::matter * static_setup::create_new_object()
{

   auto pobject = new_object();

   if (::is_set(pobject))
   {

      pobject->set_generic_object_name(m_pszName);

   }

   return pobject;

}


::aura::application* static_setup::create_new_application()
{

   auto papplication = new_application();

   if (::is_set(papplication))
   {

      papplication->m_strAppId = m_pszName;

   }

   return papplication;

}


::acme::library* static_setup::create_new_library()
{

   auto plibrary = new_library();

   if (::is_set(plibrary))
   {

      plibrary->m_strName = m_pszName;

   }

   return plibrary;

}



::matter * static_setup::new_object()
{

   return nullptr;

}


::aura::application* static_setup::new_application()
{

   return nullptr;

}


::acme::library* static_setup::new_library()
{

   return nullptr;

}
