#include "application_common.h"
#include "__apps.inl"


#include "acme/platform/system_setup.h"


#include "_main_hold.h"


//__FACTORY_IMPORT void IDENTIFIER_CONCATENATE(APPLICATION, _factory)(::factory::factory *);


//app_factory g_appfactory(&::IDENTIFIER_CONCATENATE(APPLICATION, _factory));



//__embed_resource(g_app)



#if !defined(CUBE)


#include "_new_impl.h"


#include "acme/library.h"


#endif


#include "acme/_defer.h"

#ifdef WINDOWS_DESKTOP
int WINAPI WinMain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
#else
int main(int argc, char * argv[], char * envp[])
#endif
{

   main_hold mainhold;

   auto papp = __new(APPLICATION::application);

#ifdef WINDOWS_DESKTOP
   //{

   //   auto papp = ::app_factory::new_app();

      papp->m_argc = __argc;

      papp->m_argv = __argv;

      papp->m_wargv = __wargv;

      papp->m_envp = *__p__environ();

      papp->m_wenvp = *__p__wenviron();

      papp->m_hinstanceThis = hinstanceThis;

      papp->m_hinstancePrev = hinstancePrev;

      papp->m_strCommandLine = ::GetCommandLineW();

      papp->m_nCmdShow = nCmdShow;

      //papp->m_bConsole = false;

      //int iExitCode = papp->main_loop();

      //return iExitCode;

#else

   papp->set_args(argc, argv, envp);

#endif

#if defined(LINUX) || defined(FREEBSD)

   papp->m_pchar_binary__matter_zip_start = embed_resource::get_start();

   papp->m_pchar_binary__matter_zip_end = embed_resource::get_end();

#endif

   int iExitCode = papp->main_loop();

   return iExitCode;

}



