//#include "application_common.h"
//#include "__apps.inl"


#include "acme/operating_system.h"
#include "acme/platform/system_setup.h"


//#include "_main_hold.h"


//DECLARE_APPLICATION(APPLICATION);


//__FACTORY_IMPORT void IDENTIFIER_CONCATENATE(APPLICATION, _factory)(::factory::factory *);


//app_factory g_appfactory(&::IDENTIFIER_CONCATENATE(APPLICATION, _factory));



//__embed_resource(g_app)



#if !defined(CUBE)


#include "_new_impl.h"


//#include "acme/library.h"


#endif


#include "acme/_defer.h"


#if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN)
extern char _binary__matter_zip_start[];
extern char _binary__matter_zip_end[];
#endif

#ifdef WINDOWS
CLASS_DECL_ACME void set_winmain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, int nCmdShow);
#endif
void set_res(const char * p1, const char * p2);

int __implement();

#if defined(WINDOWS)
int WINAPI WinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
#elif defined(ANDROID)
extern "C" int IDENTIFIER_CONCATENATE(main_, APPLICATION)(int argc, char* argv[], char* envp[], const char* p1, const char* p2)
#else
int main(int argc, char * argv[], char * envp[])
#endif
{

   #ifdef WINDOWS

      set_winmain(hinstanceThis, hinstancePrev, nCmdShow);
   
   #elif defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN)
   
      set_res(_binary__matter_zip_start, _binary__matter_zip_end);
   
   #elif defined(ANDROID)
   
      set_res(p1, p2);
   
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



