

#include "_main_hold.h"
#include "acme/_api.h"
#include "acme/operating_system/process.h"
#include APPLICATION_INCLUDE

//void stage();
::acme::system * acme_system_init();
void acme_system_term();

//#include "acme/platform/layer.h"

//::acme::layer g_layer;

#ifdef _UWP
#include "acme/operating_system/console.inl"

#endif
#include "acme/platform/subsystem.h"

#ifdef WINDOWS
CLASS_DECL_ACME void set_argc_argv_envp(int argc, wchar_t ** argv, wchar_t ** envp);
#else
CLASS_DECL_ACME void set_argc_argv_envp(int argc, char ** argv, char ** envp);
#endif


#include "acme/platform/acme.h"


void implement(::acme::context * pcontext);


namespace acme
{

   void initialize();

   void finalize();

}



#ifdef WINDOWS
int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
#else
int main(int argc, platform_char ** argv, platform_char ** envp)
#endif
{

   ::acme::acme acme;

   subsystem subsystem;

   main_hold mainhold;

   set_argc_argv_envp(argc, argv, envp);

   ::pointer<APPLICATION_CLASS>papp(__new(APPLICATION_CLASS));

#ifdef NO_NETWORKING

   papp->m_bNetworking = false;

#endif

//#ifdef WINDOWS
//
//   papp->get_arguments_from_command_line();
//
//#else
//
//   papp->set_args(argc, argv, envp);
//
//#endif


//   {
//      //__FACTORY(FACTORY)(::factory::get_factory());
//
//      class ::main main;
//
//      //Sleep(30'000);
//
//      main.m_argc = argc;
//
//#ifdef WINDOWS
//
//      main.m_wargv = argv;
//      main.m_wenvp = envp;
//
//#else
//
//      main.m_argv = argv;
//      main.m_envp = envp;
//
//#endif

#ifdef APP_ID

      papp->m_strAppId = APP_ID;

#endif

      papp->m_bConsole = true;
  
      papp->m_pfnImplement = &::implement;

      try
      {

         __main(papp);

      }
      catch (const ::exception & exception)
      {

         string strReport;

         strReport += "Exception has occurred:\n";
         strReport += exception.m_strMessage + ";\n";
         strReport += "Command Line:\n";
         strReport += get_command_line() + ";\n";
         strReport += exception.m_strDetails;
         strReport += "Callstack:\n";
         strReport += exception.m_strCallstack;

         fprintf(stderr, "%s", strReport.c_str());

      }
      catch (...)
      {
         
         fprintf(stderr, "Unknown exception has occurred\n");
         
      }

//      papp->m_bConsole = true;
//
//      papp->m_strAppId = __APP_ID;
//
//      try
//      {
//
//         int iExitCode = papp->main_loop();
//
//         return iExitCode;
//
//      }
//      catch (const ::exception & exception)
//      {
//
//         fprintf(stderr, "Exception has occurred \"%s\"(\"%s\")", exception.m_strMessage.c_str(), exception.m_strDetails.c_str());
//
//      }
//      catch (...)
//      {
//
//         fprintf(stderr, "Unknown Exception has occurred");
//
//      }


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

//   }

  // ::acme::finalize();

}




#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acme/library.h"


#endif


#endif


//#include "acme/_defer.h"



