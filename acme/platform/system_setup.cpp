//  Moved from Apex to Acme on 2021-03-20 18:39 <3ThomasBS_
#include "framework.h"
#include "system_setup.h"
#include "library.h"


::system_setup * system_setup::s_psetupList = nullptr;


system_setup::system_setup(::system_setup::enum_flag eflag, const char * pszName) :
   m_pfnFactory(nullptr),
   m_pszName(pszName),
   m_eflag(eflag)
{

   construct();

}

system_setup::system_setup(PFN_factory pfnFactory, const char* pszName) :
   m_pfnFactory(pfnFactory),
   m_pszName(pszName),
   m_eflag(flag_factory)
{

   construct();

}

//system_setup::system_setup(const char * lpszName, PFN_NEW_APEX_APPLICATION pfnNewAuraApplication) :
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
//system_setup::system_setup(const char * lpszName, PFN_NEW_APEX_LIBRARY pfnNewLibrary):
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


system_setup* system_setup::get_first(::system_setup::enum_flag eflag, const char* pszName)
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


PFN_factory system_setup::get_factory_function(const char* pszName)
{

   if (::is_null(pszName))
   {

      return nullptr;

   }

   auto psetup = s_psetupList;

   while (psetup != nullptr)
   {

      if (psetup->m_eflag == flag_factory && !stricmp(pszName, psetup->m_pszName))
      {

         return psetup->m_pfnFactory;

      }

      psetup = psetup->m_ppropertysetupNext;

   }

   return nullptr;


}

system_setup* system_setup::get_last(::system_setup::enum_flag eflag, const char* pszName)
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

//::system_setup * system_setup::get(const char * lpszName)
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


__pointer(::element) system_setup::create_element()
{

   auto pobject = _create_element();

   if (::is_set(pobject))
   {

      pobject->set_generic_object_name(m_pszName);

   }

   return pobject;

}


__pointer(::element) system_setup::create_application_as_element()
{

   auto papp = _create_application_as_element();

   if (::is_set(papp))
   {

      papp->set_application_id(m_pszName);

   }

   return papp;

}


__pointer(::acme::library) system_setup::create_library()
{

   auto plibrary = _create_library();

   if (::is_set(plibrary))
   {

      plibrary->m_strName = m_pszName;

   }

   return plibrary;

}



__pointer(::element) system_setup::_create_element()
{

   return nullptr;

}


__pointer(::element) system_setup::_create_application_as_element()
{

   return nullptr;

}


__pointer(::acme::library) system_setup::_create_library()
{

   return nullptr;

}