#undef ERROR


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


//CLASS_DECL_IMPORT char_pointer c_get_first_argv();


CLASS_DECL_IMPORT ::i32 unicode_main(::i32 argc, wchar_t ** argv, const ::scoped_string & scopedstrAppId);


//[MTAThread]
::i32 __stdcall wWinMain(HINSTANCE, HINSTANCE, WCHAR * psz, ::i32)
{
   
   auto argc = __argc;

   auto wargv = __wargv;

   ::i32 iRet = unicode_main(argc, wargv, _APP_ID);

   return iRet;

}

//#include "openssl/applink.c"




//
//#include "openssl/applink.c"
//


