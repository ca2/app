#include "_app_common_impl.h"

//#error "not two use it"
//#ifdef CORE_LEVEL
//extern "C"
//CLASS_DECL_CORE ::i32_bool defer_core_init();
//extern "C"
//CLASS_DECL_CORE ::i32_bool defer_core_term();
//
//#endif

#ifdef ACID

::aura::application * get_acid_app();

#endif

#ifdef LINUX


const_char_pointer br_init_get_symbol();

void apex_application_run(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrProgName);



#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

extern const_char_pointer g_psz_br_init_symbol_app;

#ifndef LINUX_COMMAND_LINE

#define GET_COMMAND_LINE(ARGC, ARGV) linux_get_command_line(ARGC, ARGV)

#endif

//class string;

char_pointer linux_get_command_line(::i32 argc, char_pointer * argv); // malloc/strdup equivalent return

#endif // LINUX


#ifdef UNIVERSAL_WINDOWS

//#include "aura/_.h"
//
//#undef CoreApplication
//



[MTAThread]
::i32 main(Array < String ^ > ^ refstra)
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = ___new aura_main_data(refstra);

#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif

   return (::i32)aura_aura(pmaindata);

}

#else




::i32 impl_main(::i32 argc, char_pointer argv[]);

::i32 main(::i32 argc, char_pointer argv[])
{

   ::i32 iResult = impl_main(argc, argv);

   return iResult;

}

::i32 aura_main(::i32 argc, char_pointer argv[], char_pointer pszCommandLine, bool bConsole, bool bDraw2d);

#ifdef NO_DRAW2D

#undef USE_DRAW2D

#endif


#include "_main_impl.h"


#ifdef WINDOWS

::i32 windows_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, char_pointer pCmdLine, ::i32 nCmdShow);

::i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, char_pointer pCmdLine, ::i32 nCmdShow)
{

   return windows_main(hinstance, hPrevInstance, pCmdLine, nCmdShow);

}
//{
//
//#ifdef MAIN_DEFERRED_RUN
//
//   __main_deferred_run = MAIN_DEFERRED_RUN;
//
//#endif
//
//   if(__main_deferred_run)
//   {
//
//      ::i32 iExitCode = (*__main_deferred_run)(hinstance, hPrevInstance, pCmdLine, nCmdShow);
//
//
//      if(iExitCode >= 0)
//      {
//
//         return iExitCode;
//
//      }
//
//   }
//
//#ifdef CORE_LEVEL
//   defer_core_init();
//#endif
//
//   ::i32 iRet = -1;
//
//   {
//
//      ::pointer<class aura_aura> paura;
//
//      ::pointer<class aura_main_data> pmaindata;
//
//      {
//
//         //KEEP(thread_flag_prevent_create_thread);
//
//
//         paura = allocateø class aura_aura ();
//
//         pmaindata = allocateø aura_main_data(hinstance, hPrevInstance, pCmdLine, nCmdShow);
//
//#ifdef MAIN_RUNNER0
//
//         pmaindata->m_mainrunnera[0] = MAIN_RUNNER0;
//
//#endif
//
//#ifdef APPID
//
//         pmaindata->m_XstrAppId = APPID;
//
//#endif
//
//      }
//
//#ifdef ACID
//
//      return aura_aura(pmaindata, &get_acid_app);
//
//#else
//
//      iRet = aura_aura(pmaindata);
//
//#endif
//   }
//
//#ifdef CORE_LEVEL
//   defer_core_term();
//#endif
//
//   return iRet;

//}



#endif


#endif



#ifdef WINDOWS



#include "openssl/applink.c"



#endif


//#define APP_PRELUDE_LEVEL(prefix) \
//extern "C" \
//::aura::application * prefix##_get_new_app(::particle * pparticle); \
//prelude auraprelude(&prefix##_get_new_app);
//
//
//#define LIBRARY_PRELUDE(prefix) \
//extern "C" \
//::acme::library * prefix##_get_new_library(::particle * pparticle); \
//prelude auraprelude(&prefix##_get_new_library);


#if defined(LINUX) && !defined(LINUX_COMMAND_LINE)

char_pointer linux_get_command_line(::i32 argc, char_pointer * argv)
{

   string str = string(argv[0]) + (" : app=" MAINAPPID);

   return strdup(str);

}

#endif

