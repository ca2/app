//#include "acme/_start.h"
//#include "aqua/_.h"
//#include "apex/platform/app_core.h"
//#include "acme/platform/system_setup.h"
//#include "aqua/_defer.h"

//
//
//#ifdef LINUX
//
//#include "acme/operating_system/ansi/binreloc.h"
//
//const char* br_init_get_symbol();
//
//#endif
//
//
////CLASS_DECL_AQUA void os_application_system_run(::apex::system* psystem);
//
////CLASS_DECL_APEX void set_main_app_id(const scoped_string & strAppId);
//
//
//void application_common(::apex::system * psystem)
//{
//
////#ifdef MAIN_STRING
////
////   psystem->m_pszMain = MAIN_STRING;
////
////#endif
////
//////#ifdef MAINAPPID
//////
//////   psystem->m_pszMain = "app : app=" MAINAPPID;
//////
//////   set_main_app_id(MAIN_APP_ID);
//////
//////#endif
//
////#ifdef ACID_APP
////
////   psystem->m_pfnNewAuraApplication = &new_aura_application;
////
////#endif
////
////#ifdef ACID_LIBRARY
////
////   psystem->m_pfnNewLibrary = &new_aura_library;
////
////#endif
//
//#ifdef LINUX
//
//  br_init_set_symbol(br_init_get_symbol());
//
//#endif
//
//
//
//
//}
//
//
//
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
//
//
//#ifdef MAINAPPID
//
//
//inline string executable_get_app_id()
//{
//
//   return MAINAPPID;
//
//}
//
//
//#elif defined(__APPLE__)
//
//
//string executable_get_app_id();
//
////#else
////
////inline string executable_get_app_id()
////{
////
////   return "";
////
////}
////
//
//#endif
//
//
//
