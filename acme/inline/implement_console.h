
#include "acme/exception/exception.h"

void application_main();

#include "acme/_operating_system.h"
#include "acme/operating_system/process.h"
#include APPLICATION_INCLUDE
#include <type_traits>

#if defined(__BSD__)
#include <stdio.h>
#endif




//void stage();
::acme::system * acme_system_init();
void acme_system_term();

#include "acme/platform/system.h"
#include "acme/platform/acme.h"

//::acme::layer g_layer;


#ifdef UNIVERSAL_WINDOWS
#include "acme/operating_system/console.inl"

#endif


#include "acme/platform/platform.h"
#include "acme/operating_system/acme_initialize.h"


//#ifdef WINDOWS
//CLASS_DECL_ACME void set_argc_argv_envp(int argc, wchar_t ** argv, wchar_t ** envp);
//#else
//CLASS_DECL_ACME void set_argc_argv_envp(int argc, char ** argv, char ** envp);
//#endif


//#include "acme/platform/acme.h"





namespace acme
{

   void initialize();

   void finalize();

}


#ifdef WINDOWS
int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
#else
int main(int argc, char ** argv, char ** envp)
#endif
{

   ::acme::singleton pacme;

   

   //::acme::acme_impl < ::SYSTEM_NAMESPACE::system > acme;

//#define DEEP_DEBUG
#ifdef DEEP_DEBUG
   printf("argc=%d\n", argc);
   for(int i = 0; i < argc; i++)
   {
      auto pszParameter = argv[i];
      if constexpr(std::is_same_v<decltype(*argv[0]), wchar_t>)
      {
         printf("argv[%d]=%S\n", i, (wchar_t*) pszParameter);
      }
      else
      {
         printf("argv[%d]=%s\n", i, (char *) pszParameter);
      }
   }
#endif

   pacme->initialize(argc, argv, envp);

   pacme->platform()->m_bConsole = true;

   //::acme::acme::g_pacme->m_pacmeapplication->m_bConsole = true;

   //string_array stra{ "StringNumber1", "StringNumber2", "StringNumber5" };

   //string str4("StringNumber4");

   //stra.insert_at(2, str4);


   ////   application.m_applicationflags.m_bConsole = true;
////
////
   //::acme::acme::g_pacme->m_pacmeapplication->implement_application();

   int iExitCode = -1;

   try
   {

      application_main();

   }
   catch (const ::exception& exception)
   {

      if (pacme->platform()->m_bConsole)
      {

         
         ::string strMessage(exception.get_message());
         
         strMessage.find_replace("\n", "\n      ");

         ::string strStack(exception.m_strCallStackTrace.c_str());
         
         strStack.find_replace("\n", "\n      ");

         fprintf(stderr,
            "\n"
            "\n"
            "\n"
            "\n"
            "      Error ---------------------------  ---   --   -    - \n"
            "                                                        --- --  -    -\n"
            "                                                                      --  -\n"
            "      \n"
            "      %s\n"
            "      \n"
            "      \n"
            "      \n"
            "      Callstack ---------  ---   --   -    - \n"
            "      \n"
            "      %s\n"
            "      \n"
            "      ------------------------------------------------------------------------\n"
            "\n"
            "\n"
            "\n"
            "\n"
            , strMessage.c_str(), strStack.c_str());

      }
      else
      {

         auto pmessagebox = __initialize_new_with(::acme::get()) ::message_box(exception, "Exception", "Exception", e_message_box_icon_error, exception.get_message() +"\n\nCallstack:\n"+ exception.m_strCallStackTrace);

         pmessagebox->sync();

      }

      iExitCode = exception.m_estatus.exit_code();

   }
   catch (...)
   {

      if (pacme->platform()->m_bConsole)
      {

         fprintf(stderr, "%s", "Unhandled Exception");

      }
      else
      {

         auto pmessagebox = __initialize_new_with(::acme::get()) ::message_box("Unhandled Exception");

         pmessagebox->sync();

      }

   }

   //return ::acme::acme::g_pacme->m_pacmeapplication->m_iExitCode;

   return iExitCode;


//   //sub_system subsystem(&acme);
//
//   //acme.m_pplatform = &subsystem;
//
//   //subsystem.m_pacme = &acme;
//   subsystem.m_argc = argc;
//#if defined(WINDOWS)  && defined(UNICODE)
//   subsystem.m_wargv = argv;
//   subsystem.m_wenvp = envp;
//#else
//   subsystem.m_argv = argv;
//   subsystem.m_envp = envp;
//#endif
//
//   main_hold mainhold;
//
//   //set_argc_argv_envp(argc, argv, envp);
//
//   ::pointer<APPLICATION_CLASS>papp(__allocate APPLICATION_CLASS());
//
//#ifdef NO_NETWORKING
//
//   papp->m_bNetworking = false;
//
//#endif

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
//      //__FACTORY(FACTORY)(factory());
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

//#ifdef APP_ID
//
//      papp->m_strAppId = APP_ID;
//
//#endif
//
//      papp->m_bConsole = true;
//  
//      papp->m_pfnImplement = &::implement;
//
//      try
//      {
//
//         __main(papp);
//
//      }
//      catch (const ::exception & exception)
//      {
//
//         string strReport;
//
//         strReport += "Exception has occurred:\n";
//         strReport += exception.m_strMessage + ";\n";
//         //strReport += "Command Line:\n";
//         //strReport += node()->get_command_line() + ";\n";
//         strReport += exception.m_strDetails;
//         strReport += "Callstack:\n";
//         strReport += exception.m_strCallstack;
//
//         fprintf(stderr, "%s", strReport.c_str());
//
//      }
//      catch (...)
//      {
//         
//         fprintf(stderr, "Unknown exception has occurred\n");
//         
//      }
//
////      papp->m_bConsole = true;
////
////      papp->m_strAppId = __APP_ID;
////
////      try
////      {
////
////         int iExitCode = papp->main_loop();
////
////         return iExitCode;
////
////      }
////      catch (const ::exception & exception)
////      {
////
////         fprintf(stderr, "Exception has occurred \"%s\"(\"%s\")", exception.m_strMessage.c_str(), exception.m_strDetails.c_str());
////
////      }
////      catch (...)
////      {
////
////         fprintf(stderr, "Unknown Exception has occurred");
////
////      }
//
//
////   process_set_args(argc, argv);
////
////   auto psystem = acme_system_init();
////
////   {
////
////#ifdef WINDOWS
////
////      wcsdup_array wcsdupa;
////
////      auto envp = psystem->node()->_get_envp(wcsdupa);
////
////#endif
//
////   ::e_status estatus = ::success;
////
////   //process_set_args(argc, argv);
////
////   auto psystem = acme_system_init();
////
////   if (!psystem)
////   {
////
////      return -1;
////
////   }
////
////   //psystem->m_bConsole = false;
////
////   //application_common(psystem);
////
////   //string strCommandLine(pCmdLine);
////
////   {
//////#ifdef WINDOWS
//////
//////      //wcsdup_array wcsdupa;
//////
//////      //auto envp = psystem->node()->_get_envp(wcsdupa);
//////
//////      platform_char** envp = nullptr;
//////
//////#endif
////
////      psystem->system_construct(argc, argv, envp);
////
////   //psystem->set_current_handles();
////
////   estatus = psystem->init_system();
////
////   if (!estatus)
////   {
////
////      return estatus.error_status();
////
////   }
////
////
////      implement(psystem);
////
////   }
////
////   acme_system_term();
////
////   return process_get_status();
//
////   }
//
//  // ::acme::finalize();

}


#include "acme/memory/_new.inl"


#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acme/_library.h"


#endif


#endif


//#include "acme/_defer.h"




#ifdef CUBE
#define STATIC_FACTORY_INCLUDE "_static_factory_.inl"
#include "acme/_static_factory.h"
#endif



