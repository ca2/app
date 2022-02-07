

#include "_main_hold.h"


//void stage();
class ::system * acme_system_init();
void acme_system_term();

//#include "acme/platform/layer.h"

//::acme::layer g_layer;

#ifdef _UWP
#include "acme/operating_system/console.inl"

#endif

CLASS_DECL_ACME void process_set_args(int argc, platform_char ** argv);
void implement(class ::system * psystem);

#ifdef WINDOWS
int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
#else
int main(int argc, platform_char ** argv, platform_char ** envp)
#endif
{

   class ::main main;

   main.m_argc = argc;
#ifdef WINDOWS
   main.m_wargv = argv;
   main.m_wenvp = envp;
#else
   main.m_argv = argv;
   main.m_envp = envp;
#endif

   main.m_pfnImplement = &::implement;

   main.m_bConsole = true;

   __main(main);

   return main.m_iExitCode;


//   process_set_args(argc, argv);
//
//   auto psystem = acme_system_init();
//
//   {
//
//#ifdef WINDOWS
//
//      wcsdup_array wcsdupa;
//
//      auto envp = psystem->node()->_get_envp(wcsdupa);
//
//#endif

//   ::e_status estatus = ::success;
//
//   //process_set_args(argc, argv);
//
//   auto psystem = acme_system_init();
//
//   if (!psystem)
//   {
//
//      return -1;
//
//   }
//
//   //psystem->m_bConsole = false;
//
//   //application_common(psystem);
//
//   //string strCommandLine(pCmdLine);
//
//   {
////#ifdef WINDOWS
////
////      //wcsdup_array wcsdupa;
////
////      //auto envp = psystem->node()->_get_envp(wcsdupa);
////
////      platform_char** envp = nullptr;
////
////#endif
//
//      psystem->system_construct(argc, argv, envp);
//
//   //psystem->set_current_handles();
//
//   estatus = psystem->init_system();
//
//   if (!estatus)
//   {
//
//      return estatus.error_status();
//
//   }
//
//
//      implement(psystem);
//
//   }
//
//   acme_system_term();
//
//   return process_get_status();

}




#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acme/library.h"


#endif


#endif


#include "acme/_defer.h"



