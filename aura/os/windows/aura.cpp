#include "framework.h"
#include "aura/node/_node.h"
#include <VersionHelpers.h>

#ifndef USE_OS_IMAGE_LOADER

#include "FreeImage/FreeImage.h"

#endif

#undef new
#include "gdiplus.h"
#include <ddeml.h>
#define new ACME_NEW


void __term_threading();
void __term_windowing();

//bool is_verbose();


::aura::system * app_common_prelude(int & iError, ::create * & pmaininitdata, app_core & appcore,  HINSTANCE hinstance = nullptr, HINSTANCE hinstancePrev = nullptr, const char * pszCmdLine = nullptr, int nShowCmd = display_normal);
int app_common_term(int iError, ::aura::system * psystem, app_core & appcore);



CLASS_DECL_AURA i32 __cdecl _memory_type(const void * p);

//Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput     = nullptr;
//Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput    = nullptr;
//DWORD_PTR                        g_gdiplusToken             = NULL;
//DWORD_PTR                        g_gdiplusHookToken         = NULL;


// typedef int
// (WINAPI * LPFN_ChangeWindowMessageFilter)(
// const ::id & id,
// ::u32 dwFlag);


// LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = nullptr;

typedef
LSTATUS
( APIENTRY * LPFN_RegGetValueW) (
HKEY hkey,
LPCWSTR pSubKey,

LPCWSTR pValue,

u32 dwFlags,
LPDWORD pdwType,
PVOID pvData,
LPDWORD pcbData
);

//LPFN_RegGetValueW g_pfnRegGetValueW = nullptr;


// bool defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
// {

//    auto pthread = ::get_task();

//    if(!pthread)
//    {

//       return false;

//    }

//    HRESULT hr = pthread->m_hresultCoInitialize;

//    if(!pthread->m_bCoInitialize)
//    {

//       pthread->m_bCoInitialize = true;
   
//       if (bMultiThread)
//       {

//          hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

//       }
//       else
//       {

//          hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | (bDisableOleDDE ? COINIT_DISABLE_OLE1DDE : 0));

//       }

//       pthread->m_hresultCoInitialize = hr;

//    }

//    if(FAILED(hr))
//    {

//       ::output_debug_string("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");

//       return false;

//    }

//    return true;

// }

bool __node_aura_pre_init()
{

   //xxdebug_box("__node_aura_pre_init","box",MB_OK);

   //g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();

   //g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();

   //g_gdiplusToken             = NULL;

   //g_gdiplusHookToken         = NULL;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   os_message_box("Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   os_message_box("Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

// #ifndef USE_OS_IMAGE_LOADER

//    try
//    {

//       FreeImage_Initialise(FALSE);

//    }
//    catch (...)
//    {

//       ::message_box(nullptr, "Failure to initialize FreeImage (::aura::init_core)", "FreeImage_Initialise failure", MB_ICONEXCLAMATION);

//       return false;

//    }

// #endif // SMALLCODE



   return true;

}

bool __node_aura_pos_init()
{

   _set_purecall_handler(_ca2_purecall);

   // HMODULE hmoduleUser32 = ::LoadLibraryW(L"User32");
   // g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   //HMODULE hmoduleAdvApi32 = ::LoadLibraryW(L"AdvApi32");
   //g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");



   return true;

}


bool __node_aura_pre_term()
{



   return true;

}

bool __node_aura_pos_term()
{


// #ifndef USE_OS_IMAGE_LOADER

//    try
//    {

//       FreeImage_DeInitialise();

//    }
//    catch (...)
//    {

//    }

// #endif // USE_OS_IMAGE_LOADER


   //if (g_pgdiplusStartupOutput != nullptr)
   //{

   //   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);


   //   ::Gdiplus::GdiplusShutdown(g_gdiplusToken);


   //   ::acme::del(g_pgdiplusStartupInput);
   //   ::acme::del(g_pgdiplusStartupOutput);
   //}

   if (is_verbose())
   {

      output_debug_string(L"aura terminating!\n");

   }

   //::CoUninitialize();


   WSACleanup();


   return true;

}


//int WinRegGetValueW(HKEY hkey, LPCWSTR pSubKey, LPCWSTR lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData)
//
//{
//
//   if(g_pfnRegGetValueW != nullptr)
//   {
//      return g_pfnRegGetValueW(hkey, pSubKey, lpValue, dwFlags, pdwType, pvData, pcbData);
//
//   }
//   else
//   {
//      LSTATUS lstatus = RegQueryValueExW(hkey, pSubKey, nullptr, pdwType, (byte *) pvData, pcbData);
//
//      if(lstatus == ERROR_SUCCESS)
//      {
//         if(pvData != nullptr && (dwFlags & RRF_RT_REG_SZ) != 0 && *pdwType == REG_SZ)
//         {
//            ((WCHAR *)pvData)[*pcbData] = L'\0';
//         }
//      }
//      return lstatus;
//   }
//}
//




//string key_to_char(WPARAM wparam, LPARAM lparam)
//
//{
//
//
//
//   unichar wsz[32];
//
//   byte baState[256];
//
//   for(int i = 0; i < 256; i++)
//   {
//      baState[i] = (byte) GetAsyncKeyState(i);
//   }
//
//   if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
//   {
//      baState[VK_SHIFT] |= 0x80;
//   }
//
//
//   i32 iRet = ToUnicodeEx((::u32) wparam, (::u32) lparam, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));
//
//
//   if(iRet > 0)
//   {
//
//      wsz[iRet] = L'\0';
//
//      string str;
//
//      str = ::str::international::unicode_to_utf8(wsz);
//
//      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
//      {
//         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
//         {
//            str.make_lower();
//         }
//         else
//         {
//            str.make_upper();
//         }
//      }
//      else
//      {
//         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
//         {
//            str.make_upper();
//         }
//         else
//         {
//            str.make_lower();
//         }
//      }
//
//
//
//      return str;
//
//   }
//
//   return "";
//
//}

//string get_system_error_message(u32 dwError)
//{
//
//   LPWSTR pBuffer;
//
//
//   HMODULE Hand = nullptr;
//
//   if(!FormatMessageW(
//         FORMAT_MESSAGE_ALLOCATE_BUFFER |
//         FORMAT_MESSAGE_FROM_SYSTEM,
//         nullptr,
//         dwError,
//         0,
//         (LPWSTR) &pBuffer,
//
//         1,
//         nullptr))
//   {
//
//      HMODULE Hand = ::LoadLibraryW(L"NTDLL.DLL");
//
//      if(!FormatMessageW(
//            FORMAT_MESSAGE_ALLOCATE_BUFFER |
//            FORMAT_MESSAGE_FROM_SYSTEM |
//            FORMAT_MESSAGE_FROM_HMODULE,
//            Hand,
//            dwError,
//            0,
//            (LPWSTR) &pBuffer,
//
//            1,
//            nullptr))
//      {
//         FreeLibrary(Hand);
//         return "";
//      }
//
//   }
//
//   string str(pBuffer);
//
//
//   LocalFree(pBuffer);
//
//
//   if(Hand != nullptr)
//   {
//      FreeLibrary(Hand);
//   }
//
//   return str;
//
//}
//



/*

// This example checks if the operating system is of "NT-type"
// (which means Windows NT, 2000, XP).
int GetVersion_ex1()
{
   ::u32    dwVersion = GetVersion();
   // Get major and minor version numbers of Windows
   ::u16 loword = LOWORD(dwVersion);
   int lowbyte = LOBYTE(loword);
   int hibyte = HIBYTE(loword);

   debug_print("Window major version = %d and minor version = %d\n", lowbyte, hibyte);

   if (!(dwVersion & 0x80000000))                // Windows NT, 2000, XP
      return 1;
   else         // Windows 95, 98, ME
      return 0;
}


*/





//int_bool is_windows_98_or_lesser()
//{
//
////#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7) // Windows 7 or greater
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN) // Windows 7 or greater
//
//   return FALSE;
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return
//   osversioninfo.dwPlatformId == VER_PLATFORM_WIN32s
//   || (osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && ((osversioninfo.dwMajorVersion == 4 && osversioninfo.dwMinorVersion <= 10) || osversioninfo.dwMajorVersion < 4));
//
//#endif
//
//}
//
//int_bool is_windows_nt()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   return !(GetVersion() & 0x80000000);
//
//#endif
//
//}


//int_bool is_windows_7_or_lower()
//{
//
//   return !IsWindows8OrGreater();
//
//}


//int_bool is_windows_8_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindows8OrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if(!GetVersionEx(&osversioninfo))
//      return 0;
//
//   __throw(todo());
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6 && osversioninfo.dwMinorVersion >= 2;
//
//#endif
//
//}


//int_bool is_windows_vista_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsVistaOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6;
//
//#endif
//
//}


//int_bool is_windows_xp_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && (osversioninfo.dwMajorVersion > 5 || (osversioninfo.dwMajorVersion == 5 && osversioninfo.dwMinorVersion >= 1);
//
//#endif
//
//}
//
//
//int_bool is_windows_2000_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 5;
//
//#endif
//
//}


//int_bool is_windows_nt_lesser_than_2000()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return FALSE;
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion < 5;
//
//#endif
//
//}

//int_bool is_windows_native_unicode()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return TRUE;
//
//#else
//
//   static int_bool s_bNativeUnicode = -1;
//
//   if (bNativeUnicode == -1)
//   {
//
//      ::u32 dwVersion = GetVersion();
//
//      // get the Windows version.
//
//      ::u32 dwWindowsMajorVersion = (::u32)(LOBYTE(LOWORD(dwVersion)));
//      ::u32 dwWindowsMinorVersion = (::u32)(HIBYTE(LOWORD(dwVersion)));
//
//      // get the build number.
//
//      ::u32 dwBuild;
//
//      if (dwVersion < 0x80000000)              // Windows NT
//         dwBuild = (::u32)(HIWORD(dwVersion));
//      else if (dwWindowsMajorVersion < 4)      // Win32s
//         dwBuild = (::u32)(HIWORD(dwVersion) & ~0x8000);
//      else                                     // Windows Me/98/95
//         dwBuild = 0;
//
//      if (dwVersion < 0x80000000)              // Windows NT
//         s_bNativeUnicode = TRUE;
//      else if (dwWindowsMajorVersion < 4)      // Win32s
//         s_bNativeUnicode = FALSE;
//      else                                     // Windows Me/98/95
//         s_bNativeUnicode = FALSE;
//
//   }
//
//   return bNativeUnicode;
//
//#endif
//
//}





// __is_valid_atom() returns TRUE if the passed parameter is
// a valid local or global atom.

//bool __is_valid_atom(ATOM nAtom)
//{
//   wchar_t sBuffer[256];
//   if(GetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
//   {
//      return TRUE;
//   }
//   ::u32 dwError = get_last_error();
//   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
//   {
//      return TRUE;
//   }
//   if(GlobalGetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
//   {
//      return TRUE;
//   }
//   dwError = get_last_error();
//   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
//   {
//      return TRUE;
//   }
//   return FALSE;
//}
//
// __is_valid_address() returns TRUE if the passed parameter is
// a valid representation of a local or a global atom within a const char *.

//bool __is_valid_atom(const char * psz)
//{
//   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));
//}


//
//bool __is_valid_atom(const wchar_t * psz)
//{
//   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));
//}
//



//int get_processor_count()
//{
//
//   SYSTEM_INFO sysinfo;
//   GetSystemInfo(&sysinfo);
//
//   return sysinfo.dwNumberOfProcessors;
//
//}





//CLASS_DECL_AURA string get_last_error_string()
//{
//
//   return get_error_string(::get_last_error());
//
//}
//
//CLASS_DECL_AURA string get_error_string(u64 u)
//{
//
//   ::u32 dwError = (::u32) u;
//
//   wchar_t * pszError;
//
//   FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (LPWSTR)&pszError, 0, nullptr);
//
//   string strError(pszError);
//
//   ::LocalFree(pszError);
//
//   return strError;
//
//}
//
//
//CLASS_DECL_AURA string expand_env(string str)
//{
//
//   wstring wstr;
//
//   ExpandEnvironmentStringsW(wstring(str), wstr.get_string_buffer(8192), (::u32)wstr.get_length());
//
//   return wstr;
//
//}





