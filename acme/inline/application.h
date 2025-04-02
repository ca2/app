//#include "application_common.h"
//#include "__apps.inl"

void application_main(::platform::system * psystem);

#include "acme/_operating_system.h"
#include "acme/platform/system_setup.h"


//#include "acme/platform/acme.h"

#ifdef CUBE
#include  "acme/platform/factory_function.h"
//#include "slashed_operating_system_appconfig.h"
#include "operating_system/appconfig.h"
#include "_static_factory_.inl"
DO_FACTORY(REFERENCE_FACTORY)
#endif

#include "_main_hold.h"


#include "acme/operating_system/acme_initialize.h"
#include "acme/operating_system/parallelization.h"


//DECLARE_APPLICATION(APPLICATION);

#ifdef WINDOWS
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#endif
//__FACTORY_IMPORT void IDENTIFIER_CONCATENATE(APPLICATION, _factory)(::factory::factory *);


//app_factory g_appfactory(&::IDENTIFIER_CONCATENATE(APPLICATION, _factory));



//__embed_resource(g_app)

#if defined(CUBE)
#include "acme/memory/_new.inl" // works for Windows Desktop(at CUBE/static builds)
#else
#include "acme/memory/_new.inl"
#include "_new_impl.h"
//#include "acme/_library.h"
#endif


#include "acme/platform/acme.h"


#if defined(LINUX) || defined(__BSD__) || defined(RASPBERRYPIOS)
extern char _binary__matter_zip_start[];
extern char _binary__matter_zip_end[];
#endif

#ifdef WINDOWS

//CLASS_DECL_ACME void set_winmain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, int nCmdShow);

#else

//   #if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD) || defined(RASPBERRYPIOS) || defined(ANDROID)
//
//   void set_res(const char * p1, const char * p2);
//
//#endif

void set_argc_argv_envp(int argc, char ** argv, char ** envp);

#endif


#ifdef NETBSD
#include <signal.h>
void set_global_exit_code(int iExitCode);
extern "C" void netbsd_cleanup(int signo);
#endif
	
bool os_on_init_thread();
void os_on_term_thread();

int __implement();

#if defined(WINDOWS)
int WINAPI wWinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, WCHAR* pCmdLine, int nCmdShow)
#elif defined(ANDROID)
extern "C" int android_main(int argc, char* argv[], char* envp[], const char* p1, const char* p2)
#else
int main(int argc, char * argv[], char * envp[])
#endif
{
   
   int iExitCode = -1;
   
   {
      
      auto psystem = ::as_pointer(new ::PLATFORM_LAYER_NAME::system());
      
#ifdef NETBSD
      
      ::print_line("NETBSD SIGINT installation");
      ::signal(SIGINT, netbsd_cleanup);
      ::print_line("NETBSD SIGTERM installation");
      ::signal(SIGTERM, netbsd_cleanup);
      ::print_line("NETBSD SIGHUP installation");
      ::signal(SIGHUP, netbsd_cleanup);
      
#endif
      
      
      //if (this->platform()->m_papplication->has_finishing_flag())
      //{
      
      //   return ::acme::acme::g_pacme->m_papplication->m_iExitCode;
      
      //}
      
#if defined(WINDOWS)
      
      psystem->initialize_system(hinstanceThis, hinstancePrev, pCmdLine, nCmdShow);
      
#else
      
      psystem->initialize_system(argc, argv, envp);
      
#endif
      
#if defined(LINUX) || defined(__BSD__) || defined(RASPBERRYPIOS)
      
      system.set_resource_block(_binary__matter_zip_start, _binary__matter_zip_end);
      
#elif defined(ANDROID)
      
      acme.platform()->set_resource_block(p1, p2);
      
#endif
      
      {
         
         ::os_on_init_thread();

         set_main_thread();
         
         application_main(psystem);

         ::os_on_term_thread();

      }
      
      iExitCode = psystem->m_iExitCode;
      
   }

   //system.on_system_before_destroy();

#ifdef NETBSD

set_global_exit_code(iExitCode);

netbsd_cleanup(0);

#else

   return iExitCode;
   
#endif
   //::acme::sub_application::g_p->m_pacmeapplicationSub->m_bConsole = true;

   ////   application.m_applicationflags.m_bConsole = true;
////
////
   //::acme::acme::g_pacme->m_papplication->implement_application();

   //return ::acme::acme::g_pacme->m_papplication->m_iExitCode;

//   acme::acme acme;
//
//   auto pplatform = __allocate subsystem();
//
//   auto pmainhold = __allocate main_hold();

//   ::main acme;
//
//   ::sub_system subsystem(&acme);
//
//   main_hold mainhold;
//
//   #ifdef WINDOWS
//
//#ifdef WINDOWS_DESKTOP
//
//   //if (!m_hinstanceThis)
//   //{
//
//   subsystem.m_hinstanceThis = hinstanceThis;
//   subsystem.m_hinstancePrev = hinstancePrev;
//   //}
//   subsystem.m_nCmdShow = nCmdShow;
//   //m_hPrevInstance = nullptr;
//
//   if (subsystem.m_nCmdShow == -1000)
//   {
//
//      subsystem.m_nCmdShow = SW_SHOWDEFAULT;
//
//   }
//
//#elif defined(LINUX)
//
//   m_bGtkApp = false;
//
//#endif
//
//
//      //set_winmain(hinstanceThis, hinstancePrev, nCmdShow);
//   
//   #else
//
//      subsystem.m_argc = argc;
//
//      subsystem.m_argv = argv;
//
//      subsystem.m_envp = envp;
//
//
//   #endif
//
//   int iExitCode = __implement();
//
//   return iExitCode;
//
////   ///auto pmainhold = __allocate main_hold();
////
////   auto papp = IDENTIFIER_CONCATENATE(new_, APP)();
////
////   //pmainhold->m_papplication = papp;
////
////#ifdef WINDOWS_DESKTOP
////   //{
////
////   //   auto papp = ::app_factory::new_app();
////
////      papp->m_argc = __argc;
////
////      papp->m_argv = __argv;
////
////      papp->m_wargv = __wargv;
////
////      papp->m_envp = *__p__environ();
////
////      papp->m_wenvp = *__p__wenviron();
////
////      papp->m_hinstanceThis = hinstanceThis;
////
////      papp->m_hinstancePrev = hinstancePrev;
////
////      papp->m_strCommandLine = ::GetCommandLineW();
////
////      papp->m_nCmdShow = nCmdShow;
////
////      //papp->m_bConsole = false;
////
////      //int iExitCode = papp->main_loop();
////
////      //return iExitCode;
////
////#elif !defined(UNIVERSAL_WINDOWS)
////
////   papp->set_args(argc, argv, envp);
////
////#endif
////
////#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD) || defined(RASPBERRYPIOS)
////
////   papp->m_pchar_binary__matter_zip_start = _binary__matter_zip_start;
////
////   papp->m_pchar_binary__matter_zip_end = _binary__matter_zip_end;
////
////#elif defined(ANDROID)
////
////   papp->m_pchar_binary__matter_zip_start = p1;
////
////   papp->m_pchar_binary__matter_zip_end = p2;
////
////#endif
////
////   int iExitCode = papp->main_loop();
////
////   return papp->m_estatus;

}



