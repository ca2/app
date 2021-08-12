#include "acme/_start.h"
#include "aura/_.h"
#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"
#include "aura/_defer.h"


#ifndef NO_DRAW2D
#ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

extern "C" void draw2d_gdiplus_factory_exchange(::factory_map * pfactorymap);

#endif

extern "C" void draw2d_direct2d_factory_exchange(::factory_map * pfactorymap);

#elif defined(__APPLE__)

extern "C" void draw2d_quartz_factory_exchange(::factory_map * pfactorymap);

#else

extern "C" void draw2d_factory_exchange(::factory_map * pfactorymap);

#endif


extern "C" void draw2d_cairo_exchange();


#endif


#ifndef NO_IMAGING
#ifdef WINDOWS_DESKTOP

extern "C" void imaging_wic_factory_exchange(::factory_map * pfactorymap);

#endif

extern "C" void imaging_freeimage_factory_exchange(::factory_map * pfactorymap);

#endif

#ifdef WITH_GPU

extern "C" void gpu_opengl_factory_exchange(::factory_map * pfactorymap);

#endif

#ifdef LINUX

#include "acme/node/operating_system/ansi/binreloc.h"

const char* br_init_get_symbol();

#endif


//fCLASS_DECL_AURA ::e_status os_application_system_run(::apex::system* psystem);

CLASS_DECL_APEX ::e_status set_main_app_id(const ::string & pszAppId);


void application_common(::apex::system * psystem)
{

#ifdef MAIN_STRING

   __pointer(::aura::system) psystem = m_psystem;

   psystem->m_pszMain = MAIN_STRING;

#endif

//#ifdef MAINAPPID
//
//   psystem->m_pszMain = "app : app=" MAINAPPID;
//
//   set_main_app_id(MAIN_APP_ID);
//
//#endif

#ifdef ACID_APP

   psystem->m_pfnNewAuraApplication = &new_aura_application;

#endif

#ifdef ACID_LIBRARY

   psystem->m_pfnNewLibrary = &new_aura_library;

#endif

#ifdef LINUX

  br_init_set_symbol(br_init_get_symbol());

#endif


#ifdef CUBE

#ifndef NO_DRAW2D

#ifdef WINDOWS_DESKTOP

  psystem->set_factory_exchange("draw2d", "gdiplus", &draw2d_gdiplus_factory_exchange);

#elif _UWP

  psystem->set_factory_exchange("draw2d", "direct2d", &draw2d_direct2d_factory_exchange);

#elif defined(LINUX)

  psystem->set_factory_exchange("draw2d", "cairo", &draw2d_cairo_factory_exchange);

#elif defined(__APPLE__)

  psystem->set_factory_exchange("draw2d", "quartz", &draw2d_quartz_factory_exchange);

#else

  psystem->set_factory_exchange("draw2d", &draw2d_factory_exchange);

#endif

#endif

#ifndef NO_IMAGING

#ifdef WINDOWS_DESKTOP

  psystem->set_factory_exchange("imaging", "wic", &imaging_wic_factory_exchange);

#else

  psystem->set_factory_exchange("imaging", "freeimage", &imaging_freeimage_factory_exchange);

#endif

#endif


#ifdef WITH_GPU

  psystem->set_factory_exchange("gpu", "opengl", &gpu_opengl_factory_exchange);

#endif

#endif

#ifdef NO_IMAGING

  psystem->m_bImaging = false;

#endif


#ifdef NO_DRAW2D

  psystem->m_bDraw2d = false;

#endif


}




template < typename APPLICATION >
class static_application_factory :
   public static_setup
{
public:


   virtual ::matter* new_application_as_matter() override
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


CLASS_DECL_ACME void set_main_thread();


#ifdef _APP_ID


inline string executable_get_app_id()
{

   return _APP_ID;

}


#elif defined(__APPLE__)


string executable_get_app_id();

#else

inline string executable_get_app_id()
{

   return "";

}


#endif



