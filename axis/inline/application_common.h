#include "aura/_.h"
#include "aura/platform/app_core.h"
#include "aura/platform/static_setup.h"
#include "aura/_defer.h"


#ifdef LINUX

#include "aura/os/binreloc.h"

const char* br_init_get_symbol();

#endif


//CLASS_DECL_AXIS ::e_status os_application_system_run(::aura::system* psystem);


void application_common(aura_main_struct * pmainstruct)
{

#ifdef MAIN_STRING

   pmainstruct->m_pszMain = MAIN_STRING;

#endif

#ifdef MAINAPPID

   pmainstruct->m_pszMain = "app : app=" MAINAPPID;

#endif

#ifdef ACID_APP

   pmainstruct->m_pfnNewAuraApplication = &new_aura_application;

#endif

#ifdef ACID_LIBRARY

   pmainstruct->m_pfnNewLibrary = &new_aura_library;

#endif

#ifdef LINUX

  br_init_set_symbol(br_init_get_symbol());

#endif

}




template < typename APPLICATION >
class static_application_factory :
   public static_setup
{
public:


   virtual ::aura::application* new_application() override { return new APPLICATION; }


   static_application_factory(const ::string & pszName = "") :
      static_setup(flag_application, pszName)
   {


   }


};


// #define __namespace_application_factory(NAMESPACE, APPID) \
// namespace NAMESPACE { \
// ::static_application_factory < ::NAMESPACE::application > g_applicationfactory(APPID);\
// } \
// extern "C" \
// CLASS_DECL_EXPORT ::aura::application * new_aura_application() \
// {\
//    return ::NAMESPACE::g_applicationfactory.new_application(); \
// }

//#define __namespace_application_factory(APPID) \
//::static_application_factory < application > g_applicationfactory(APPID);




// \
// extern "C" \
// CLASS_DECL_EXPORT ::acme::library * get_new_library() \
// {\
//    return ::NAMESPACE::g_libraryfactory.new_library(); \
// }


// #define __namespace_library_factory2(N1, N2, LIBRARY) \
// namespace N1 { namespace N2 { \
// ::static_library_factory < library > g_libraryfactory(LIBRARY);\
// } }


//  \
// extern "C" \
// CLASS_DECL_EXPORT ::acme::library * get_new_library() \
// {\
//    return ::N1::N2::g_libraryfactory.new_library(); \
// }


#ifdef WINDOWS_DESKTOP

#pragma comment(lib, "Dxva2.lib")

#endif



