#include "acme/_start.h"
#include "aura/_.h"
#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"
#include "aura/_defer.h"


//
//
//
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
//extern "C" void ([a-z0-9_]+)_factory(::factory::factory * pfactory);
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
//#ifdef LINUX
//
//#include "acme/node/operating_system/ansi/binreloc.h"
//
//const char* br_init_get_symbol();
//
//#endif
//
//
////fCLASS_DECL_AURA void os_application_system_run(::apex::system* psystem);
//
//CLASS_DECL_APEX void set_main_app_id(const ::string & pszAppId);
//
//
//void application_common(::apex::system * psystem)
//{
//
//#ifdef MAIN_STRING
//
//   __pointer(::aura::system) psystem = m_psystem;
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
//
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
//#ifndef NO_DRAW2D
//
//#ifdef WINDOWS_DESKTOP
//
//  psystem->([a-z0-9_]+)_factory("draw2d", "gdiplus", &([a-z0-9_]+)_factory);
//
//#elif _UWP
//
//  psystem->([a-z0-9_]+)_factory("draw2d", "direct2d", &([a-z0-9_]+)_factory);
//
//#elif defined(LINUX)
//
//  psystem->([a-z0-9_]+)_factory("draw2d", "cairo", &([a-z0-9_]+)_factory);
//
//#elif defined(__APPLE__)
//
//  psystem->([a-z0-9_]+)_factory("draw2d", "quartz", &([a-z0-9_]+)_factory);
//
//#else
//
//  psystem->([a-z0-9_]+)_factory("draw2d", &([a-z0-9_]+)_factory);
//
//#endif
//
//#endif
//
//#ifndef NO_IMAGING
//
//#ifdef WINDOWS_DESKTOP
//
//  psystem->([a-z0-9_]+)_factory("imaging", "wic", &([a-z0-9_]+)_factory);
//
//#else
//
//  psystem->([a-z0-9_]+)_factory("imaging", "freeimage", &([a-z0-9_]+)_factory);
//
//#endif
//
//#endif
//
//
//#ifdef WITH_GPU
//
//  psystem->([a-z0-9_]+)_factory("gpu", "opengl", &([a-z0-9_]+)_factory);
//
//#endif
//
//#endif
//
//#ifdef NO_IMAGING
//
//  psystem->m_bImaging = false;
//
//#endif
//
//
//#ifdef NO_DRAW2D
//
//  psystem->m_bDraw2d = false;
//
//#endif
//
//
//}
//
//
//#define __namespace_application_factory(APPID) \
//::static_application_factory < application > g_applicationfactory(APPID);
//
//
//#ifdef WINDOWS_DESKTOP
//
//#pragma comment(lib, "Dxva2.lib")
//
//#endif
//
//
//CLASS_DECL_ACME void set_main_thread();
//
//
//#ifdef _APP_ID
//
//
//inline string executable_get_app_id()
//{
//
//   return _APP_ID;
//
//}
//
//
//#elif defined(__APPLE__)
//
//
//string executable_get_app_id();
//
//#else
//
//inline string executable_get_app_id()
//{
//
//   return "";
//
//}
//
//
//#endif
//
//
//
