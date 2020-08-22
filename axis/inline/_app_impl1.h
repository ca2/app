#include "_app_common_impl.h"

//#error "not two use it"
//#ifdef CORE_LEVEL
//extern "C"
//CLASS_DECL_AXIS int_bool defer_core_init();
//extern "C"
//CLASS_DECL_AXIS int_bool defer_core_term();
//
//#endif

#ifdef ACID

::aura::application * get_acid_app();

#endif

#ifdef LINUX


const char * br_init_get_symbol();

void bloat_pad_run(const char * pszAppName, const char * pszProgName);



#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

extern const char * g_psz_br_init_symbol_app;

#ifndef LINUX_COMMAND_LINE

#define GET_COMMAND_LINE(ARGC, ARGV) linux_get_command_line(ARGC, ARGV)

#endif

//class string;

char * linux_get_command_line(int argc, char ** argv); // malloc/strdup equivalent return

#endif // LINUX


#ifdef _UWP

//#include "aura/_.h"
//
//#undef CoreApplication
//

#undef new

[MTAThread]
int main(Array < String ^ > ^ refstra)
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(refstra);

#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif

   return (int)aura_aura(pmaindata);

}

#else


#undef new

int impl_main(int argc, char * argv[]);

int main(int argc, char * argv[])
{

   int iResult = impl_main(argc, argv);

   return iResult;

}

int aura_main(int argc, char * argv[], char * pszCommandLine, bool bConsole, bool bDraw2d);

#ifdef NO_DRAW2D

#undef USE_DRAW2D

#endif


#include "_main_impl.h"


#ifdef WINDOWS

i32 windows_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow);

i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow)
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
//      int iExitCode = (*__main_deferred_run)(hinstance, hPrevInstance, pCmdLine, nCmdShow);
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
//   int iRet = -1;
//
//   {
//
//      __pointer(class aura_aura) paura;
//
//      __pointer(class aura_main_data) pmaindata;
//
//      {
//
//         //__keep(thread_flag_prevent_create_thread);
//
//
//         paura = __new(class aura_aura);
//
//         pmaindata = __new(aura_main_data(hinstance, hPrevInstance, pCmdLine, nCmdShow));
//
//#ifdef MAIN_RUNNER0
//
//         pmaindata->m_mainrunnera[0] = MAIN_RUNNER0;
//
//#endif
//
//#ifdef APPID
//
//         pmaindata->m_strAppId = APPID;
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
//::aura::application * prefix##_get_new_app(::object * pobject); \
//prelude auraprelude(&prefix##_get_new_app);
//
//
//#define LIBRARY_PRELUDE(prefix) \
//extern "C" \
//::aura::library * prefix##_get_new_library(::object * pobject); \
//prelude auraprelude(&prefix##_get_new_library);


#if defined(LINUX) && !defined(LINUX_COMMAND_LINE)

char * linux_get_command_line(int argc, char ** argv)
{

   string str = string(argv[0]) + (" : app=" MAINAPPID);

   return strdup(str);

}

#endif

