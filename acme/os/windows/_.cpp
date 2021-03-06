#include "framework.h"
#include "acme/operating_system.h"


#include "acme/id.h"
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

CLASS_DECL_ACME bool is_verbose();


//class ::system * app_common_prelude(int & iError, ::create * & pmaininitdata, app_core & appcore,  HINSTANCE hinstance = nullptr, HINSTANCE hinstancePrev = nullptr, const char * pszCmdLine = nullptr, int nShowCmd = e_display_normal);
//int app_common_term(int iError, class ::system * psystem, app_core & appcore);



CLASS_DECL_ACME i32 __cdecl _memory_type(const void * p);


// typedef int
// (WINAPI * LPFN_ChangeWindowMessageFilter)(
// const ::id & id,
// ::u32 dwFlag);


//LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = nullptr;


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



bool __node_acme_pre_init()
{

   //xxdebug_box("__node_acme_pre_init","box",e_message_box_ok);

   //g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();

   //g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();

   //g_gdiplusToken             = NULL;

   //g_gdiplusHookToken         = NULL;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   message_box("Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   os_message_box(nullptr,"Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

// #ifndef USE_OS_IMAGE_LOADER

//    try
//    {

//       FreeImage_Initialise(false);

//    }
//    catch (...)
//    {

//       ::message_box(nullptr, "Failure to initialize FreeImage (::acme::init_core)", "FreeImage_Initialise failure", e_message_box_icon_exclamation);

//       return false;

//    }

// #endif // SMALLCODE



   return true;

}


void windows_registry_init();



bool __node_acme_pos_init()
{

   //_set_purecall_handler(_ca2_purecall);

   //HMODULE hmoduleUser32 = ::LoadLibraryW(L"User32");
   //g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   windows_registry_init();



   return true;

}


bool __node_acme_pre_term()
{



   return true;

}

bool __node_acme_pos_term()
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

      output_debug_string(L"acme terminating!\n");

   }

   //::CoUninitialize();


   WSACleanup();


   return true;

}






string key_to_char(wparam wparam, lparam lparam)

{



   unichar wsz[32];

   byte baState[256];

   for(int i = 0; i < 256; i++)
   {
      baState[i] = (byte) GetAsyncKeyState(i);
   }

   if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
   {
      baState[VK_SHIFT] |= 0x80;
   }


   i32 iRet = ToUnicodeEx((::u32) wparam, (::u32) lparam, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));


   if(iRet > 0)
   {

      wsz[iRet] = L'\0';

      string str;

      str = ::str::international::unicode_to_utf8(wsz);

      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_lower();
         }
         else
         {
            str.make_upper();
         }
      }
      else
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_upper();
         }
         else
         {
            str.make_lower();
         }
      }



      return str;

   }

   return "";

}


//string get_system_error_message(u32 dwError)
//{
//
//   LPWSTR pBuffer;
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





int_bool is_windows_98_or_lesser()
{

//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7) // Windows 7 or greater
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN) // Windows 7 or greater

   return false;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return
   osversioninfo.dwPlatformId == VER_PLATFORM_WIN32s
   || (osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && ((osversioninfo.dwMajorVersion == 4 && osversioninfo.dwMinorVersion <= 10) || osversioninfo.dwMajorVersion < 4));

#endif

}

int_bool is_windows_nt()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   return !(GetVersion() & 0x80000000);

#endif

}


int_bool is_windows_7_or_lower()
{

   return !IsWindows8OrGreater();

}


int_bool is_windows_8_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindows8OrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if(!GetVersionEx(&osversioninfo))
      return 0;

   __throw(todo);

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6 && osversioninfo.dwMinorVersion >= 2;

#endif

}


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


int_bool is_windows_nt_lesser_than_2000()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return false;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
   {

      return 0;

   }

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion < 5;

#endif

}


int_bool is_windows_native_unicode()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return true;

#else

   static int_bool s_bNativeUnicode = -1;

   if (bNativeUnicode == -1)
   {

      ::u32 dwVersion = GetVersion();

      // get the Windows version.

      ::u32 dwWindowsMajorVersion = (::u32)(LOBYTE(LOWORD(dwVersion)));
      ::u32 dwWindowsMinorVersion = (::u32)(HIBYTE(LOWORD(dwVersion)));

      // get the build number.

      ::u32 dwBuild;

      if (dwVersion < 0x80000000)              // Windows NT
         dwBuild = (::u32)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
         dwBuild = (::u32)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
         dwBuild = 0;

      if (dwVersion < 0x80000000)              // Windows NT
         s_bNativeUnicode = true;
      else if (dwWindowsMajorVersion < 4)      // Win32s
         s_bNativeUnicode = false;
      else                                     // Windows Me/98/95
         s_bNativeUnicode = false;

   }

   return bNativeUnicode;

#endif

}


// __is_valid_atom() returns true if the passed parameter is
// a valid local or global atom.
bool __is_valid_atom(ATOM nAtom)
{
   
   wchar_t sBuffer[256];

   if(GetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
   {
      
      return true;

   }
   
   DWORD dwError = ::GetLastError();

   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {

      return true;

   }

   if(GlobalGetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
   {

      return true;

   }

   dwError = ::GetLastError();

   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {

      return true;

   }

   return false;

}


// __is_valid_address() returns true if the passed parameter is
// a valid representation of a local or a global atom within a const char *.

bool __is_valid_atom(const char * psz)
{

   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));

}


bool __is_valid_atom(const wchar_t * psz)
{
   
   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));

}


int_bool IsWow64()
{

   int_bool bIsWow64 = false;

   if (!IsWow64Process(GetCurrentProcess(), &bIsWow64))
   {
      return false;
   }

   return bIsWow64 != false;

}


int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege)
{
   
   // do it only once
   static int_bool bEnabled = false;

   if (bEnabled)
   {
      
      return true;

   }

   bEnabled = true;

   HANDLE hToken = 0;

   TOKEN_PRIVILEGES tkp = { 0 };

   // Get a token for this process.
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
   {

      return false;

   }

   // Get the LUID for the privilege.
   if (LookupPrivilegeValue(nullptr, pszPrivilege, &tkp.Privileges[0].Luid))
   {
      
      tkp.PrivilegeCount = 1;  // one privilege to set
      
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // set the privilege for this process.
      AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)nullptr, 0);

      DWORD dwError = ::GetLastError();

      if (dwError != ERROR_SUCCESS)
      {

         return false;

      }

      return true;

   }

   return false;

}


CLASS_DECL_ACME string get_last_error_string()
{

   DWORD dwError = ::GetLastError();

   return get_error_string(dwError);

}


CLASS_DECL_ACME string get_error_string(DWORD dwError)
{

   WCHAR * pszError;

   FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *)&pszError, 0, nullptr);

   string strError(pszError);

   ::LocalFree(pszError);

   return strError;

}




bool __node_pos_init()
{

   return true;

}


bool __node_pre_term()
{

   return true;

}


bool __node_pos_term()
{

   return true;

}


CLASS_DECL_ACME string executable_get_app_id(hinstance hinstance)
{

   return read_resource_as_string(hinstance, 1, "APPID");

}


CLASS_DECL_ACME hinstance get_module_handle(const platform_char * psz)
{

   return (hinstance) GetModuleHandle(psz);

}

// CLASS_DECL_ACME ::millis os_get_system_update_poll_time(const ::id & id)
// {

//    if (id == id_os_dark_mode)
//    {

//       return 0;

//    }
//    else if (id == id_os_font_change)
//    {

//       return 0;

//    }
//    else if (id == id_font_enumeration)
//    {

//       return 0;

//    }

//    return 0;

//}

namespace windows
{

   class CLASS_DECL_ACME message_box :
      virtual public ::conversation
   {
   public:

      HWND                 m_hwnd;
      string               m_strMessage;
      string               m_strTitle;
      ::e_message_box      m_emessagebox;

      
      message_box() { m_hwnd = nullptr; m_emessagebox = e_message_box_ok; }

      ::enum_dialog_result show(HWND hwnd, const char* pszMessage, const char* pszTitle, const ::e_message_box& emessagebox)
      {

         m_hwnd = hwnd;
         m_strMessage = pszMessage;
         m_strTitle = pszTitle;
         m_emessagebox = emessagebox;

         return __show();

      }

      
         ::enum_dialog_result __show()
         {

            return
               (::enum_dialog_result)
               ::MessageBox(
                  m_hwnd,
                  wstring(m_strMessage),
                  wstring(m_strTitle),
                  (i32)m_emessagebox.m_eenum);

         }

   };


} // namespace windows



__pointer(::extended::future < ::conversation >) show_error_message(const string & strMessage, const string & strTitle, const ::e_message_box & emessagebox)
{

   wstring wstrMessage(strMessage);

   wstring wstrTitle(strTitle);

   auto pmessagebox = __new(windows::message_box);

   auto pfuture = pmessagebox->::extended::asynchronous <::conversation>::future();

   pmessagebox->m_edialogresult = pmessagebox->show(nullptr, strMessage, strTitle, emessagebox);

   pfuture->set_status(::success);

   return pfuture;

}



