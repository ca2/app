#include "_app_common_impl.h"

//#error "not two use it"
//#ifdef CORE_LEVEL
//extern "C"
//CLASS_DECL_ACID int_bool defer_core_init();
//extern "C"
//CLASS_DECL_ACID int_bool defer_core_term();
//
//#endif

#ifdef ACID

::acid::application * get_acid_app();

#endif

#ifdef LINUX


const char * br_init_get_symbol();

void apex_application_run(const ::scoped_string & scopedstrAppName, const ::scoped_string & scopedstrProgName);



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


#ifdef UNIVERSAL_WINDOWS

//#include "acid/_.h"
//
//#undef CoreApplication
//



[MTAThread]
int main(Array < String ^ > ^ refstra)
{

   class ace_ace acid;

   ap(ace_main_data) pmaindata = __new< ace_main_data >(refstra);

#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif

   return (int)ace_ace(pmaindata);

}

#else




int impl_main(int argc, char * argv[]);

int main(int argc, char * argv[])
{

   int iResult = impl_main(argc, argv);

   return iResult;

}

int ace_main(int argc, char * argv[], char * pszCommandLine, bool bConsole, bool bDraw2d);

#ifdef NO_DRAW2D

#undef USE_DRAW2D

#endif


#include "_main_impl.h"


#ifdef WINDOWS

i32 windows_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, int nCmdShow);

i32 WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, int nCmdShow)
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
//      ::pointer<class ace_ace> pace;
//
//      ::pointer<class ace_main_data> pmaindata;
//
//      {
//
//         //KEEP(thread_flag_prevent_create_thread);
//
//
//         pace = __allocate< class ace_ace >();
//
//         pmaindata = __allocate< ace_main_data >(hinstance, hPrevInstance, pCmdLine, nCmdShow);
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
//      return ace_ace(pmaindata, &get_acid_app);
//
//#else
//
//      iRet = ace_ace(pmaindata);
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
//::acid::application * prefix##_get_new_app(::particle * pparticle); \
//prelude aceprelude(&prefix##_get_new_app);
//
//
//#define LIBRARY_PRELUDE(prefix) \
//extern "C" \
//::acid::library * prefix##_get_new_library(::particle * pparticle); \
//prelude aceprelude(&prefix##_get_new_library);


#if defined(LINUX) && !defined(LINUX_COMMAND_LINE)

char * linux_get_command_line(int argc, char ** argv)
{

   string str = string(argv[0]) + (" : app=" MAINAPPID);

   return strdup(str);

}

#endif

