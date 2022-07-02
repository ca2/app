#include "acme/_start.h"
#include "apex/_.h"
//#include "apex/platform/app_core.h"
#include "acme/platform/system_setup.h"
#include "apex/_defer.h"
#include "acme/inline/implement.h"


CLASS_DECL_ACME void set_main_user_thread();


//#ifdef __APP_ID
//
//static set_app_id g_setappid(__APP_ID);
//
//#endif


//#ifndef NO_DRAW2D
//#ifdef WINDOWS
//
//#ifdef WINDOWS_DESKTOP
//
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//#endif
//
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//#elif defined(__APPLE__)
//
//extern "C" void draw2d_quartz_exchange();
//
//#else
//
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//#endif
//
//
//extern "C" void draw2d_cairo_exchange();
//
//
//#endif
//
//
//#ifndef NO_IMAGING
//#ifdef WINDOWS_DESKTOP
//
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//#endif
//
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//#endif
//
//#ifdef WITH_GPU
//
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
//
//#endif
//
#ifdef LINUX

#include "apex/operating_system/binreloc.h"

const char* br_init_get_symbol();

#endif


//CLASS_DECL_APEX void os_application_system_run(::apex::system* psystem);

//
//void application_common(::apex::system * psystem)
//{
//
//#ifdef MAIN_STRING
//
//   pmainstruct->m_pszMain = MAIN_STRING;
//
//#endif
//
//#ifdef MAINAPPID
//
//   pmainstruct->m_pszMain = "app : app=" MAINAPPID;
//
//#endif
//
//#ifdef ACID_APP
//
//   pmainstruct->m_pfnNewAuraApplication = &new_apex_application;
//
//#endif
//
//#ifdef ACID_LIBRARY
//
//   pmainstruct->m_pfnNewLibrary = &new_apex_library;
//
//#endif
//
//#ifdef LINUX
//
//  br_init_set_symbol(br_init_get_symbol());
//
//#endif
//
//
//#ifdef CUBE
//
////#ifndef NO_DRAW2D
////
////#ifdef WINDOWS_DESKTOP
////
////  psystem->([a-z0-9_]+)_factory("draw2d", "gdiplus", &([a-z0-9_]+)_factory);
////
////#elif _UWP
////
////  psystem->([a-z0-9_]+)_factory("draw2d", "direct2d", &([a-z0-9_]+)_factory);
////
////#elif defined(LINUX)
////
////  psystem->([a-z0-9_]+)_factory("draw2d", "cairo", &([a-z0-9_]+)_factory);
////
////#elif defined(__APPLE__)
////
////  psystem->([a-z0-9_]+)_factory("draw2d", "quartz", &([a-z0-9_]+)_factory);
////
////#else
////
////  psystem->([a-z0-9_]+)_factory("draw2d", &([a-z0-9_]+)_factory);
////
////#endif
////
////#endif
////
////#ifndef NO_IMAGING
////
////#ifdef WINDOWS_DESKTOP
////
////  psystem->([a-z0-9_]+)_factory("imaging", "wic", &([a-z0-9_]+)_factory);
////
////#else
////
////  psystem->([a-z0-9_]+)_factory("imaging", "freeimage", &([a-z0-9_]+)_factory);
////
////#endif
////
////#endif
////
////
////#ifdef WITH_GPU
////
////  psystem->([a-z0-9_]+)_factory("gpu", "opengl", &([a-z0-9_]+)_factory);
////
////#endif
//
//
//#endif
//
//#ifdef NO_AUDIO
//
//   psystem->m_bImaging = false;
//
//#endif
//
//}

//
//template < typename APPLICATION >
//class static_application_factory :
//   public system_setup
//{
//public:
//
//
//   virtual ::application* new_application() { return new APPLICATION; }
//
//
//   static_application_factory(const char * pszName = "") :
//      system_setup(flag_application, pszName)
//   {
//
//
//   }
//
//
//};
//

#define __namespace_application_factory(APPID) \
::static_application_factory < application > g_applicationfactory(APPID);


#ifdef WINDOWS_DESKTOP


#pragma comment(lib, "Dxva2.lib")


#endif


#ifdef MAIN_APP_ID


inline string executable_get_app_id()
{

   return MAIN_APP_ID;

}


//#elif defined(LINUX)
//
//
//inline string executable_get_app_id()
//{
//
//   return "";
//
//}


#endif



