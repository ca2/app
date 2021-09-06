#include <windows.h>
class RunBeforeMain
{
public:
   RunBeforeMain()
   {
      //HMODULE hNtDll = (HMODULE)LoadLibrary(_T("ntdll.dll"));
      //FARPROC lpNeeded = GetProcAddress(hNtDll, "NtWaitForMultipleObjects");
      //DebugBreakPoint();
   }
};

RunBeforeMain go;

#define __L(x) L ## x
#define _L(x) __L(x)


//CLASS_DECL_IMPORT char * c_get_first_argv();


CLASS_DECL_IMPORT int unicode_main(int argc, wchar_t ** argv, const char * pszAppId);


//[MTAThread]
int __stdcall wWinMain(HINSTANCE, HINSTANCE, WCHAR * psz, int)
{
   
   auto argc = __argc;

   auto wargv = __wargv;

   int iRet = unicode_main(argc, wargv, _APP_ID);

   return iRet;

}

//#include "openssl/applink.c"




//
//#include "openssl/applink.c"
//


