//#include "application_common.h"
//#include "__apps.inl"



#include "acme/_operating_system.h"
#include "acme/platform/system_setup.h"

#include "acme/platform/acme.h"

#ifdef CUBE
#include "operating_system/appconfig.h"
#include "_static_factory_.inl"
#endif

#include "_main_hold.h"


#if defined(_UWP)
#if !defined(CUBE)
#include "acme/asset/new.cpp"
#endif
#elif defined(ANDROID)
#include "acme/asset/new.cpp"
#elif defined(APPLE_IOS)
#include "acme/asset/new.cpp"
#endif


//DECLARE_APPLICATION(APPLICATION);


//__FACTORY_IMPORT void IDENTIFIER_CONCATENATE(APPLICATION, _factory)(::factory::factory *);


//app_factory g_appfactory(&::IDENTIFIER_CONCATENATE(APPLICATION, _factory));



//__embed_resource(g_app)



#if !defined(CUBE)


#include "_new_impl.h"


//#include "acme/_library.h"


#endif


//#include "acme/_defer.h"


#if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN)
extern char _binary__matter_zip_start[];
extern char _binary__matter_zip_end[];
#endif

#ifdef WINDOWS

//CLASS_DECL_ACME void set_winmain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, int nCmdShow);

#else

//   #if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN) || defined(ANDROID)
//
//   void set_res(const char * p1, const char * p2);
//
//#endif

void set_argc_argv_envp(int argc, char ** argv, char ** envp);

#endif


int __implement();

#if defined(WINDOWS)
int WINAPI WinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
#elif defined(ANDROID)
extern "C" int android_main(int argc, char* argv[], char* envp[], const char* p1, const char* p2)
#else
int main(int argc, char * argv[], char * envp[])
#endif
{

//   acme::acme acme;
//
//   auto psubsystem = __new(subsystem);
//
//   auto pmainhold = __new(main_hold);

   ::acme::acme acme;

   ::sub_system subsystem(&acme);

   main_hold mainhold;

   #ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

   //if (!m_hinstanceThis)
   //{

   subsystem.m_hinstanceThis = hinstanceThis;
   subsystem.m_hinstancePrev = hinstancePrev;
   //}
   subsystem.m_nCmdShow = nCmdShow;
   //m_hPrevInstance = nullptr;

   if (subsystem.m_nCmdShow == -1000)
   {

      subsystem.m_nCmdShow = SW_SHOWDEFAULT;

   }

#elif defined(LINUX)

   m_bGtkApp = false;

#endif


      //set_winmain(hinstanceThis, hinstancePrev, nCmdShow);
   
   #else

      subsystem.m_argc = argc;

      subsystem.m_argv = argv;

      subsystem.m_envp = envp;

      #if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN)
   
         subsystem.set_resource_block(_binary__matter_zip_start, _binary__matter_zip_end);
   
      #elif defined(ANDROID)
   
         set_res(p1, p2);

      #endif   

   #endif

   int iExitCode = __implement();

   return iExitCode;

//   ///auto pmainhold = __new(main_hold);
//
//   auto papp = IDENTIFIER_CONCATENATE(new_, APP)();
//
//   //pmainhold->m_pacmeapplication = papp;
//
//#ifdef WINDOWS_DESKTOP
//   //{
//
//   //   auto papp = ::app_factory::new_app();
//
//      papp->m_argc = __argc;
//
//      papp->m_argv = __argv;
//
//      papp->m_wargv = __wargv;
//
//      papp->m_envp = *__p__environ();
//
//      papp->m_wenvp = *__p__wenviron();
//
//      papp->m_hinstanceThis = hinstanceThis;
//
//      papp->m_hinstancePrev = hinstancePrev;
//
//      papp->m_strCommandLine = ::GetCommandLineW();
//
//      papp->m_nCmdShow = nCmdShow;
//
//      //papp->m_bConsole = false;
//
//      //int iExitCode = papp->main_loop();
//
//      //return iExitCode;
//
//#elif !defined(_UWP)
//
//   papp->set_args(argc, argv, envp);
//
//#endif
//
//#if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN)
//
//   papp->m_pchar_binary__matter_zip_start = _binary__matter_zip_start;
//
//   papp->m_pchar_binary__matter_zip_end = _binary__matter_zip_end;
//
//#elif defined(ANDROID)
//
//   papp->m_pchar_binary__matter_zip_start = p1;
//
//   papp->m_pchar_binary__matter_zip_end = p2;
//
//#endif
//
//   int iExitCode = papp->main_loop();
//
//   return papp->m_estatus;

}



