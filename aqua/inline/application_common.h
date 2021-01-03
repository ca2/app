#include "acme/_start.h"
#include "aqua/_.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"
#include "aqua/_defer.h"


#ifdef LINUX

#include "aura/os/binreloc.h"

const char* br_init_get_symbol();

#endif


//CLASS_DECL_AQUA ::e_status os_application_system_run(::apex::system* psystem);

//CLASS_DECL_APEX ::e_status set_main_app_id(const char * pszAppId);


void application_common(::apex::system * psystem)
{

//#ifdef MAIN_STRING
//
//   psystem->m_pszMain = MAIN_STRING;
//
//#endif
//
////#ifdef MAINAPPID
////
////   psystem->m_pszMain = "app : app=" MAINAPPID;
////
////   set_main_app_id(MAIN_APP_ID);
////
////#endif

//#ifdef ACID_APP
//
//   psystem->m_pfnNewAuraApplication = &new_aura_application;
//
//#endif
//
//#ifdef ACID_LIBRARY
//
//   psystem->m_pfnNewLibrary = &new_aura_library;
//
//#endif

#ifdef LINUX

  br_init_set_symbol(br_init_get_symbol());

#endif




}




template < typename APPLICATION >
class static_application_factory :
   public static_setup
{
public:


   virtual ::apex::application* new_application() override
   {
      auto papplication = new APPLICATION;
#ifdef NO_IMAGING
      papplication->m_bImaging = false;
#endif

      return papplication;

   }


   static_application_factory(const char * pszName = "") :
      static_setup(flag_application, pszName)
   {


   }


};


#define __namespace_application_factory(APPID) \
::static_application_factory < application > g_applicationfactory(APPID);


#ifdef WINDOWS_DESKTOP

#pragma comment(lib, "Dxva2.lib")

#endif




#ifdef MAINAPPID


inline string executable_get_app_id()
{

   return MAINAPPID;

}


#elif defined(__APPLE__)


string executable_get_app_id();

#else

inline string executable_get_app_id()
{

   return "";

}


#endif



