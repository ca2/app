#include "framework.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/platform/debug.h"


#include "acme/_operating_system.h"


#include <Shlobj.h>
#include <Shellapi.h>


CLASS_DECL_ACME HANDLE duplicate_handle(HANDLE h)
{

   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &h, 0, false, DUPLICATE_SAME_ACCESS);

   return h;

}



::file::path dir_ca2_module()
{

#if defined(ANDROID)

   return acmepath()->app_module().folder();

#elif defined(UNIVERSAL_WINDOWS)

   wstring wstrModuleFilePath;

   auto pwszModuleFilePath = wstrModuleFilePath.get_buffer(MAX_PATH * 8);

   if (!GetModuleFileNameW(nullptr, pwszModuleFilePath, MAX_PATH * 8))
   {

      return "";

   }

   wstrModuleFilePath.release_buffer();

   LPWSTR pszModuleFileName;

   wstring wstrModuleFolder;

   auto pwszModuleFolder = wstrModuleFolder.get_buffer(MAX_PATH * 8);

   if (!GetFullPathNameW(wstrModuleFilePath, MAX_PATH * 8, pwszModuleFolder, &pszModuleFileName))
   {

      return "";

   }

   wstrModuleFolder.release_buffer();

   wstrModuleFolder.case_insensitive_ends_eat("\\");
   wstrModuleFolder.case_insensitive_ends_eat("/");
   wstrModuleFolder.case_insensitive_ends_eat("\\");
   wstrModuleFolder.case_insensitive_ends_eat("/");

   return string(wstrModuleFolder);


#elif defined(WINDOWS)


   wstring wstrModuleFolder;


   wstring wstrModuleFilePath;


   HMODULE hmodule = ::GetModuleHandleA("acme.dll");

   if (hmodule == nullptr)
   {

      hmodule = ::GetModuleHandleA("spalib.dll");

   }

   if(hmodule == nullptr)
   {

      PWSTR pwstr = nullptr;

      try
      {

         HRESULT hr = SHGetKnownFolderPath(
            FOLDERID_ProgramFilesX86,
            KF_FLAG_DEFAULT,
            nullptr,
            &pwstr);

         auto p = wstrModuleFilePath.get_buffer(MAX_PATH * 8);

         wcscpy(p, pwstr);

         wstrModuleFilePath.release_buffer();

      }
      catch (...)
      {


      }

      if (pwstr)
      {

         ::CoTaskMemFree(pwstr);
         pwstr = nullptr;

      }


      //if(wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '\\'

      //      || wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '/')

      //{
      //   wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] = '\0';

      //}

      wstrModuleFilePath += L"\\ca2\\";

#ifdef X86

      wstrModuleFilePath += L"/stage/x86/";

#else
      wstrModuleFilePath += L"/stage/x64/";

#endif

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);


   }

   auto p = wstrModuleFilePath.get_buffer(MAX_PATH * 8);

   if (!GetModuleFileNameW(hmodule, p, MAX_PATH * 8))
   {

      return "";

   }

   wstrModuleFilePath.release_buffer();

   LPWSTR pszModuleFileName;

   auto pFolder = wstrModuleFolder.get_buffer(MAX_PATH * 8);

   if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), pFolder, &pszModuleFileName))
   {

      return "";

   }

   wstrModuleFolder.release_buffer();

   if(wstrModuleFolder.has_char())
   {

      wstrModuleFolder.trim_right(L"\\/");

   }

   return ::string(wstrModuleFolder);

#elif defined(__APPLE__)

   string str;

   {

//         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
//
//         if(str.has_char())
//         {
//            str = ::file::path(str).folder();
//            goto found;
//
//         }
//
//
//         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
//
//         if(str.has_char())
//         {
//            str = ::file::path(str).folder();
//            goto found;
//
//         }

      str = get_exe_path();


      if(str.has_char())
      {
         str = ::file::path(str).folder();
         goto found;
      }


   }
found:
   ;

   return str;

#else

   string strModuleFolder;

   auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);

   void * handle = dlopen("libacme.so", RTLD_NOW);

   if(handle == nullptr)
   {

      strcpy(wstrModuleFolder, "/ca2/");

   }
   else
   {

      link_map * plm;

      dlinfo(handle, RTLD_DI_LINKMAP, &plm);

      strcpy(wstrModuleFolder, plm->l_name);

      dlclose(handle);

      strcpy(wstrModuleFolder, ::file_path_folder(wstrModuleFolder));

   }

   return string(wstrModuleFolder);



#endif


}



//::file::path dir_base_module()
//{
//
//#if defined(UNIVERSAL_WINDOWS)
//
//   return "";
//
//#elif defined(WINDOWS)
//
//   auto sizeBuffer = MAX_PATH * 8;
//
//   wstring wstrModuleFolder;
//   
//   //wstring wstrModuleFilePath;
//
//   //auto pszModuleFilePath = wstrModuleFilePath.get_buffer(sizeBuffer);
//
//   HMODULE hmodule = ::GetModuleHandleA("acme.dll");
//
//   if (hmodule == nullptr)
//   {
//
//      hmodule = ::GetModuleHandleA("spalib.dll");
//
//   }
//
//   if (hmodule == nullptr)
//   {
//
//      wstrModuleFilePath = _wgetenv(L"PROGRAMFILES(X86)");
//
//      if (wstrModuleFilePath.is_empty())
//      {
//
//         auto p = wstrModuleFilePath.get_buffer(sizeBuffer);
//
//         SHGetSpecialFolderPathW(nullptr, p, CSIDL_PROGRAM_FILES, false);
//
//         wstrModuleFilePath.release_buffer();
//
//      }
//
//      wstrModuleFilePath.trim_right(L"\\/");
//
//      wstrModuleFilePath += L"\\ca2\\";
//
//#ifdef X86
//
//      wstrModuleFilePath += L"/stage/x86/";
//
//#else
//      wstrModuleFilePath += L"/stage/x64/";
//
//#endif
//
//      wstrModuleFolder = wstrModuleFilePath;
//
//      return string(wstrModuleFolder);
//
//   }
//
//   auto pModuleFilePath = wstrModuleFilePath.get_buffer(MAX_PATH * 8);
//
//   if (!GetModuleFileNameW(hmodule, pModuleFilePath, MAX_PATH * 8))
//   {
//
//      return "";
//
//   }
//
//   LPWSTR pszModuleFileName;
//
//   auto pFolder = wstrModuleFolder.get_buffer(MAX_PATH *8);
//
//   if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), pFolder, &pszModuleFileName))
//   {
//
//      return "";
//
//   }
//
//   wstrModuleFolder.release_buffer();
//
//   wstrModuleFolder.trim_right(L"\\/");
//
//   return ::string(wstrModuleFolder);
//
//#else
//
//   string strModuleFolder;
//
//   auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);
//
//   throw ::exception(todo);
//
//   return wstrModuleFolder;
//
//#endif
//
//}


void __node_acme_pre_init()
{

   //xxdebug_box("__node_acme_pre_init","box",e_message_box_ok);

   //g_pgdiplusStartupInput     = normal_new Gdiplus::GdiplusStartupInput();

   //g_pgdiplusStartupOutput    = normal_new Gdiplus::GdiplusStartupOutput();

   //g_gdiplusToken             = NULL;

   //g_gdiplusHookToken         = NULL;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   output_error_message("Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   message_box_synchronous(nullptr,"Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

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



   //return true;

}


void __node_acme_pos_init()
{

   //_set_purecall_handler(_ca2_purecall);

   //HMODULE hmoduleUser32 = ::LoadLibraryW(L"User32");
   //g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");





   //return true;

}


void __node_acme_pre_term()
{



   //return true;

}


void __node_acme_pos_term()
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

   //if (is_verbose())
   //{

   //   infomration(L"acme terminating!\n");

   //}

   //::CoUninitialize();


   //WSACleanup();


   //return true;

}


void attach_thread_input_to_main_thread(bool bAttach)
{

   MSG msg;

   if (bAttach)
   {

      PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

   }

   AttachThreadInput(::GetCurrentThreadId(), (DWORD)get_main_user_itask(), bAttach ? true : false);

}


string read_resource_as_string(hinstance hinst, ::u32 nID, const ::scoped_string & scopedstrType, strsize iReadAtMostByteCount = -1)
{

   HRSRC hrsrc = ::FindResourceW((HINSTANCE)hinst, MAKEINTRESOURCEW(nID), wstring(scopedstrType));

   if (hrsrc == nullptr)
   {

      return "";

   }

   HGLOBAL hres = ::LoadResource((HINSTANCE)hinst, hrsrc);

   if (hres == nullptr)
   {

      return "";

   }

   u32 dwResSize = ::SizeofResource((HINSTANCE)hinst, hrsrc);

   string str;

   char * psz = nullptr;

   if (hres != nullptr)
   {

      ::u32 * pnRes = (::u32 *)::LockResource(hres);

      iReadAtMostByteCount = iReadAtMostByteCount < 0 ? dwResSize : minimum(iReadAtMostByteCount, (strsize)dwResSize);

      psz = str.get_buffer(iReadAtMostByteCount);

      ::memory_copy(psz, pnRes, iReadAtMostByteCount);

      psz[dwResSize] = '\0';

      str.release_buffer(iReadAtMostByteCount);

   }

   return str;

}


CLASS_DECL_ACME string executable_get_app_id(hinstance hinstance)
{

   return read_resource_as_string(hinstance, 1, "APPID");

}


// Get the horizontal and vertical screen sizes in pixel
void operating_system_get_main_screen_size(int& cx, int& cy)
{
   
   const HWND hwndDesktop = GetDesktopWindow();
   
   RECT rectDesktop;

   GetWindowRect(hwndDesktop, &rectDesktop);

   cx = rectDesktop.right - rectDesktop.left;

   cy = rectDesktop.bottom - rectDesktop.top;

}


// CLASS_DECL_ACME void operating_system_open_url(const ::scoped_string & scopedstrUrl)
// {

//    wstring wstrUrl(pszUrl);

//    ::ShellExecuteW(nullptr, L"open", wstrUrl, nullptr, nullptr, SW_SHOWNORMAL);

// }

//
//
//CLASS_DECL_ACME string get_error_string(::i64 iError)
//{
//
//
//}
//


