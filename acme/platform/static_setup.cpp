//  Moved from Apex to Acme on 2021-03-20 18:39 <3ThomasBS_
#include "framework.h"
#include "static_setup.h"


::static_setup * static_setup::s_psetupList = nullptr;


static_setup::static_setup(::static_setup::enum_flag eflag, const char * pszName) :
   m_pfnFactoryExchange(nullptr),
   m_pszName(pszName),
   m_eflag(eflag)
{

   construct();

}

static_setup::static_setup(PFN_factory_exchange pfnFactoryExchange, const char* pszName) :
   m_pfnFactoryExchange(pfnFactoryExchange),
   m_pszName(pszName),
   m_eflag(flag_factory_exchange)
{

   construct();

}

//static_setup::static_setup(const char * lpszName, PFN_NEW_APEX_APPLICATION pfnNewAuraApplication) :
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
//static_setup::static_setup(const char * lpszName, PFN_NEW_APEX_LIBRARY pfnNewLibrary):
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


static_setup* static_setup::get_first(::static_setup::enum_flag eflag, const char* pszName)
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


PFN_factory_exchange static_setup::get_factory_exchange(const char* pszName)
{

   if (::is_null(pszName))
   {

      return nullptr;

   }

   auto psetup = s_psetupList;

   while (psetup != nullptr)
   {

      if (psetup->m_eflag == flag_factory_exchange && !stricmp(pszName, psetup->m_pszName))
      {

         return psetup->m_pfnFactoryExchange;

      }

      psetup = psetup->m_ppropertysetupNext;

   }

   return nullptr;


}

static_setup* static_setup::get_last(::static_setup::enum_flag eflag, const char* pszName)
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

//::static_setup * static_setup::get(const char * lpszName)
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


__pointer(::matter) static_setup::create_element()
{

   auto pobject = _create_element();

   if (::is_set(pobject))
   {

      pobject->set_generic_object_name(m_pszName);

   }

   return pobject;

}


::matter * static_setup::create_new_application()
{

   auto papplication = new_application_as_matter();

   if (::is_set(papplication))
   {

      papplication->set_application_id(m_pszName);

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


::matter * static_setup::new_application_as_matter()
{

   return nullptr;

}


::acme::library* static_setup::new_library()
{

   return nullptr;

}
