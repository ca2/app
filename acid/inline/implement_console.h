#ifdef CUBE
#include "acid/platform/factory_function.h"
#include "operating_system/appconfig.h"
#include "_static_factory_.inl"
DO_FACTORY(REFERENCE_FACTORY)
#endif

#include "acid/exception/exception.h"

::i32 application_main(::platform::platform * pplatform);

#include "_main_hold.h"
#include "acid/_operating_system.h"
#include "acid/operating_system/process.h"
#include APPLICATION_INCLUDE
#include <type_traits>

#if defined(FREEBSD) || defined(OPENBSD)
#include <stdio.h>
#endif




//void stage();
::acid::system * ace_system_init();
void ace_system_term();

#include "acid/platform/acid.h"

//::acid::layer g_layer;


#ifdef UNIVERSAL_WINDOWS
#include "acid/operating_system/console.inl"

#endif
#include "acid/platform/platform.h"
#include "acid/operating_system/ace_initialize.h"


//#ifdef WINDOWS
//CLASS_DECL_ACID void set_argc_argv_envp(int argc, wchar_t ** argv, wchar_t ** envp);
//#else
//CLASS_DECL_ACID void set_argc_argv_envp(int argc, char ** argv, char ** envp);
//#endif


//#include "acid/platform/acid.h"





namespace acid
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

   ::acid::singleton_pointer pace;

   

   //::acid::ace_impl < ::SYSTEM_NAMESPACE::system > acid;

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

   pace->initialize(argc, argv, envp);

   pace->platform()->m_bConsole = true;

   //::acid::acid::g_pace->m_paceapplication->m_bConsole = true;

   //string_array stra{ "StringNumber1", "StringNumber2", "StringNumber5" };

   //string str4("StringNumber4");

   //stra.insert_at(2, str4);


   ////   application.m_applicationflags.m_bConsole = true;
////
////
   //::acid::acid::g_pace->m_paceapplication->implement_application();

   int iExitCode = -1;

   try
   {

      iExitCode = application_main(pace->platform());

   }
   catch (const ::exception& exception)
   {

      if (pace->platform()->m_bConsole)
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

         ::message_box_synchronous(pace->platform(), exception.get_message(), "Exception", e_message_box_icon_error, exception.get_message() +"\n\nCallstack:\n"+ exception.m_strCallStackTrace);

      }

      iExitCode = exception.m_estatus.exit_code();

   }
   catch (...)
   {

      if (pace->platform()->m_bConsole)
      {

         fprintf(stderr, "%s", "Unhandled Exception");

      }
      else
      {

         ::message_box_synchronous(pace->platform(), "Unhandled Exception");

      }

   }

   //return ::acid::acid::g_pace->m_paceapplication->m_iExitCode;

   return iExitCode;


//   //sub_system subsystem(&acid);
//
//   //acid.m_pplatform = &subsystem;
//
//   //subsystem.m_pace = &acid;
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
//   ::pointer<APPLICATION_CLASS>papp(__allocate< APPLICATION_CLASS >());
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
////   auto psystem = ace_system_init();
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
////   auto psystem = ace_system_init();
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
////   ace_system_term();
////
////   return process_get_status();
//
////   }
//
//  // ::acid::finalize();

}


#include "acid/memory/_new.inl"


#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acid/_library.h"


#endif


#endif


//#include "acid/_defer.h"



