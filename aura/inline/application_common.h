#include "acme/_start.h"
#include "aura/_.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"
#include "aura/_defer.h"


#ifndef NO_DRAW2D
#ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

extern "C" void draw2d_gdiplus_factory_exchange();

#endif

extern "C" void draw2d_direct2d_factory_exchange();

#elif defined(__APPLE__)

extern "C" void draw2d_quartz_exchange();

#else

extern "C" void draw2d_factory_exchange();

#endif


extern "C" void draw2d_cairo_exchange();


#endif


#ifndef NO_IMAGING
#ifdef WINDOWS_DESKTOP

extern "C" void imaging_wic_factory_exchange();

#endif

extern "C" void imaging_freeimage_factory_exchange();

#endif

#ifdef WITH_GPU

extern "C" void gpu_opengl_factory_exchange();

#endif

#ifdef LINUX

#include "aura/os/binreloc.h"

const char* br_init_get_symbol();

#endif


CLASS_DECL_APEX ::estatus os_application_system_run(::apex::system* psystem);

CLASS_DECL_APEX ::estatus set_main_app_id(const char * pszAppId);


void application_common(::apex::system * psystem)
{

#ifdef MAIN_STRING

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


#ifdef NO_IMAGING

  psystem->m_bDraw2d = false;

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


   virtual ::apex::application* new_application() override { return new APPLICATION; }


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

   return MAIN_APP_ID;

}


#else


inline string executable_get_app_id()
{

   return "";

}


#endif



