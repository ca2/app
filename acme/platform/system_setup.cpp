//  Moved from Apex to Acme on 2021-03-20 18:39 <3ThomasBS_
#include "framework.h"
#include "system_setup.h"
#include "library.h"
//#include "acme/primitive/primitive/element.h"


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


CLASS_DECL_ACME ::string get_library_component(const string & strName)
{
   
   if (strName.begins("audio_resample_"))
   {

      return "audio_resample";

   }
   else if (strName.begins("audio_decode_"))
   {

      return "audio_resample";

   }
   else if (strName.begins("video_decode_"))
   {

      return "video_decode";

   }
   else if (strName.begins("video_input_"))
   {

      return "video_input";

   }
   else
   {

      auto iFind = strName.find('_');

      if (iFind < 0)
      {

         return strName;

      }

      return strName.Left(iFind);

   }

}


PFN_factory system_setup::get_factory_function(const char* pszName)
{

   if (::is_null(pszName))
   {

      return nullptr;

   }

   {

      auto psetup = s_psetupList;

      while (psetup != nullptr)
      {

         if (psetup->m_eflag == flag_factory && !stricmp(pszName, psetup->m_pszName))
         {

            return psetup->m_pfnFactory;

         }

         psetup = psetup->m_ppropertysetupNext;

      }

   }

   {

      auto psetup = s_psetupList;

      string strComponentSearch = get_library_component(pszName);

      while (psetup != nullptr)
      {

         if (psetup->m_eflag == flag_factory)
         {

            string strComponent = get_library_component(psetup->m_pszName);

            if (strComponent == strComponentSearch)
            {

               return psetup->m_pfnFactory;

            }

         }

         psetup = psetup->m_ppropertysetupNext;

      }

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


::pointer < ::particle > system_setup::create_particle()
{

   auto pparticle = _create_particle();

   if (::is_set(pparticle))
   {

      pparticle->set_generic_object_name(m_pszName);

   }

   return pparticle;

}


::pointer < ::particle > system_setup::create_application_as_particle()
{

   auto papp = _create_application_as_particle();

   if (::is_set(papp))
   {

      papp->set_application_id(m_pszName);

   }

   return papp;

}


::pointer<::acme::library>system_setup::create_library()
{

   auto plibrary = _create_library();

   if (::is_set(plibrary))
   {

      plibrary->m_strName = m_pszName;

   }

   return plibrary;

}



::pointer < ::particle > system_setup::_create_particle()
{

   return nullptr;

}


::pointer < ::particle > system_setup::_create_application_as_particle()
{

   return nullptr;

}


::pointer<::acme::library>system_setup::_create_library()
{

   return nullptr;

}
