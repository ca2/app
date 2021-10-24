#include "acme/_start.h"
#include "apex/_.h"
#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"
#include "apex/_defer.h"
#include "acme/inline/implement.h"


CLASS_DECL_ACME void set_main_thread();

//#ifndef NO_DRAW2D
//#ifdef WINDOWS
//
//#ifdef WINDOWS_DESKTOP
//
//extern "C" void draw2d_gdiplus_factory_exchange(::factory_map * pfactorymap);
//
//#endif
//
//extern "C" void draw2d_direct2d_factory_exchange(::factory_map * pfactorymap);
//
//#elif defined(__APPLE__)
//
//extern "C" void draw2d_quartz_exchange();
//
//#else
//
//extern "C" void draw2d_factory_exchange(::factory_map * pfactorymap);
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
//extern "C" void imaging_wic_factory_exchange(::factory_map * pfactorymap);
//
//#endif
//
//extern "C" void imaging_freeimage_factory_exchange(::factory_map * pfactorymap);
//
//#endif
//
//#ifdef WITH_GPU
//
//extern "C" void gpu_opengl_factory_exchange(::factory_map * pfactorymap);
//
//#endif
//
#ifdef LINUX

#include "apex/node/operating_system/binreloc.h"

const char* br_init_get_symbol();

#endif


//CLASS_DECL_APEX ::e_status os_application_system_run(::apex::system* psystem);


void application_common(::apex::system * psystem)
{

#ifdef MAIN_STRING

   pmainstruct->m_pszMain = MAIN_STRING;

#endif

#ifdef MAINAPPID

   pmainstruct->m_pszMain = "app : app=" MAINAPPID;

#endif

#ifdef ACID_APP

   pmainstruct->m_pfnNewAuraApplication = &new_apex_application;

#endif

#ifdef ACID_LIBRARY

   pmainstruct->m_pfnNewLibrary = &new_apex_library;

#endif

#ifdef LINUX

  br_init_set_symbol(br_init_get_symbol());

#endif


#ifdef CUBE

//#ifndef NO_DRAW2D
//
//#ifdef WINDOWS_DESKTOP
//
//  psystem->set_factory_exchange("draw2d", "gdiplus", &draw2d_gdiplus_factory_exchange);
//
//#elif _UWP
//
//  psystem->set_factory_exchange("draw2d", "direct2d", &draw2d_direct2d_factory_exchange);
//
//#elif defined(LINUX)
//
//  psystem->set_factory_exchange("draw2d", "cairo", &draw2d_cairo_factory_exchange);
//
//#elif defined(__APPLE__)
//
//  psystem->set_factory_exchange("draw2d", "quartz", &draw2d_quartz_factory_exchange);
//
//#else
//
//  psystem->set_factory_exchange("draw2d", &draw2d_factory_exchange);
//
//#endif
//
//#endif
//
//#ifndef NO_IMAGING
//
//#ifdef WINDOWS_DESKTOP
//
//  psystem->set_factory_exchange("imaging", "wic", &imaging_wic_factory_exchange);
//
//#else
//
//  psystem->set_factory_exchange("imaging", "freeimage", &imaging_freeimage_factory_exchange);
//
//#endif
//
//#endif
//
//
//#ifdef WITH_GPU
//
//  psystem->set_factory_exchange("gpu", "opengl", &gpu_opengl_factory_exchange);
//
//#endif


#endif

#ifdef NO_AUDIO

   psystem->m_bImaging = false;

#endif

}

//
//template < typename APPLICATION >
//class static_application_factory :
//   public static_setup
//{
//public:
//
//
//   virtual ::application* new_application() { return new APPLICATION; }
//
//
//   static_application_factory(const char * pszName = "") :
//      static_setup(flag_application, pszName)
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


#elif defined(LINUX)


inline string executable_get_app_id()
{

   return "";

}


#endif



