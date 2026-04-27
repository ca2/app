#include "framework.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/platform/debug.h"
#include "acme/windowing/window.h"


#include "acme/_operating_system.h"
#include "acme/operating_system/windows/windows.h"


#include <Shlobj.h>
#include <Shellapi.h>


CLASS_DECL_ACME ::uptr duplicate_handle(const ::uptr & u)
{

   auto h = (HANDLE) u;

   DuplicateHandle(GetCurrentProcess(), ::GetCurrentThread(), GetCurrentProcess(), &h, 0, false, DUPLICATE_SAME_ACCESS);

   return (::uptr) h;

}


CLASS_DECL_ACME HMODULE GetModuleFromFunction(void* pFunc);


namespace windows
{


   CLASS_DECL_ACME hinstance hinstance_from_function(void *pVoid)
   {

      HMODULE hmodule = ::GetModuleFromFunction(pVoid);

      HINSTANCE hInstance = (HINSTANCE)hmodule;

      ::hinstance hinstance;

      hinstance = hInstance;

      return hinstance;

   }


   CLASS_DECL_ACME bool get_window_rect(const ::operating_system::window & operatingsystemwindow, ::int_rectangle & rectangle)
   {

      RECT _winRectø{};

      if (!::GetWindowRect(::as_HWND(operatingsystemwindow), &_winRectø))
      {

         return false;

      }

      rectangle = _winRectø;

      return true;

   }


   CLASS_DECL_ACME ::int_rectangle get_window_rect(const ::operating_system::window & operatingsystemwindow)
   {

      ::int_rectangle rectangle;

      if (!get_window_rect(operatingsystemwindow, rectangle))
      {

         throw_last_error_exception("GetWindowRect failed");

      }

      return rectangle;

   }


   CLASS_DECL_ACME ::operating_system::window get_window(const ::operating_system::window & operatingsystemwindowCommand, int iGetWindowCommand)
   {

      auto hwndCmd = ::as_HWND(operatingsystemwindowCommand);

      auto hwnd = ::GetWindow(hwndCmd, iGetWindowCommand);

      auto operatingsystemwindow = ::as_operating_system_window(hwnd);

      return operatingsystemwindow;

   }


   CLASS_DECL_ACME ::iptr get_window_long(const ::operating_system::window & operatingsystemwindow, int iGetWindowLong)
   {

      auto hwnd = ::as_HWND(operatingsystemwindow);

      ::iptr i = ::GetWindowLongPtrW(hwnd, iGetWindowLong);

      return i;

   }


   CLASS_DECL_ACME ::itask get_window_thread_id(const ::operating_system::window & operatingsystemwindow)
   {

      auto hwnd = ::as_HWND(operatingsystemwindow);

      DWORD dwThreadID = ::GetWindowThreadProcessId(hwnd, nullptr);

      return dwThreadID;

   }


   CLASS_DECL_ACME ::itask get_window_thread_process_id(const ::operating_system::window & operatingsystemwindow, ::process_identifier & processidentifier)
   {

      auto hwnd = ::as_HWND(operatingsystemwindow);

      DWORD dwProcessID = 0;

      DWORD dwThreadID = ::GetWindowThreadProcessId(hwnd, &dwProcessID);

      if (dwThreadID)
      {

         processidentifier = dwProcessID;

      }

      return dwThreadID;

   }


   CLASS_DECL_ACME ::process_identifier get_window_thread_process_id(const ::operating_system::window & operatingsystemwindow)
   {

      auto hwnd = ::as_HWND(operatingsystemwindow);

      DWORD dwProcessID = 0;

      DWORD dwThreadID = ::GetWindowThreadProcessId(hwnd, &dwProcessID);

      ::process_identifier processidentifier{};

      if (dwThreadID)
      {

         processidentifier = dwProcessID;

      }

      return processidentifier;

   }


   CLASS_DECL_ACME ::operating_system::window get_foreground_window()
   {

      auto hwnd = ::GetForegroundWindow();

      auto operatingsystemwindow = ::as_operating_system_window(hwnd);

      return operatingsystemwindow;

   }

   //protected:

   static BOOL CALLBACK findWindowsByClassFunc(HWND hwnd, LPARAM lparam);
   static BOOL CALLBACK findWindowsByNameFunc(HWND hwnd, LPARAM lparam);


      struct WindowsParam
   {
      ::comparable_array_base<::operating_system::window> *hwndVector;
      const ::string_array_base *classNames;
   };

   BOOL CALLBACK findWindowsByClassFunc(HWND hwnd, LPARAM lparam)
   {
      if (IsWindowVisible(hwnd) != 0) {
         WindowsParam *windowsParam = (WindowsParam *)lparam;
         //::sStringVector::iterator classNameIter;

         const size_t maxTcharCount = 256;
         TCHAR winName[maxTcharCount];
         if (GetClassName(hwnd, winName, maxTcharCount) != 0) {
            ::string nextWinName(winName);

            if (nextWinName.has_character() && hwnd != 0)
               {
               for (auto & str : *windowsParam->classNames)
               {
                  if (str == nextWinName)
                  {
                     windowsParam->hwndVector->add(::as_operating_system_window(hwnd));
                  }
               }

            }

            // Recursion
            EnumChildWindows(hwnd, findWindowsByClassFunc, (::lparam) windowsParam);
         }
      }
      return TRUE;
   }

   ::comparable_array_base<::operating_system::window> findWindowsByClass(const ::string_array_base & straClassNames)
   {
      ::comparable_array_base<::operating_system::window> hwnda;
      if (straClassNames.empty()) {
         return hwnda;
      }
      WindowsParam windowsParam;
      windowsParam.classNames = &straClassNames;
      windowsParam.hwndVector = &hwnda;
      EnumWindows(findWindowsByClassFunc, (LPARAM)&windowsParam);
      return hwnda;
   }

   BOOL CALLBACK findWindowsByNameFunc(HWND hwnd, LPARAM lparam)
   {
      if (IsWindowVisible(hwnd) != 0) {
         const size_t maxTcharCount = 256;
         TCHAR nameChars[maxTcharCount];
         if (GetWindowText(hwnd, nameChars, maxTcharCount) != 0) {
            ::string winName(nameChars);
            winName.make_lower();

            if (winName.has_character() && hwnd != 0) {
               WindowsParam *winParams = (WindowsParam *)lparam;
               auto substr = winParams->classNames->first();
               if (winName.contains( substr)) {
                  winParams->hwndVector->add(::as_operating_system_window(hwnd));
                  return FALSE;
               }
            }
         }
      }
      return TRUE;
   }

   ::operating_system::window findFirstWindowByName(const ::scoped_string & scopedstrWindowNamePart)
   {
      ::comparable_array_base<::operating_system::window> hwnda;
      ::string_array_base winNameVector;
      winNameVector.add(scopedstrWindowNamePart);
      winNameVector[0].make_lower();
      WindowsParam winParams = { &hwnda, &winNameVector };

      EnumWindows(findWindowsByNameFunc, (::lparam)&winParams);
      if (hwnda.has_element()) {
         return hwnda.first();
      } else {
         return 0;
      }
   }



} // namespace windows



::file::path dir_ca2_module()
{

#if defined(__ANDROID__)

   return path_system()->app_module().folder();

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

   if (!GetFullPathNameW(wstrModuleFilePath, (unsigned int)wstrModuleFilePath.length(), pFolder, &pszModuleFileName))
   {

      return "";

   }

   wstrModuleFolder.release_buffer();

   if(wstrModuleFolder.has_character())
   {

      wstrModuleFolder.trim_right(L"\\/");

   }

   return ::string(wstrModuleFolder);

#elif defined(__APPLE__)

   string str;

   {

//         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
//
//         if(str.has_character())
//         {
//            str = ::file::path(str).folder();
//            goto found;
//
//         }
//
//
//         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
//
//         if(str.has_character())
//         {
//            str = ::file::path(str).folder();
//            goto found;
//
//         }

      str = get_exe_path();


      if(str.has_character())
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
//   if (!GetFullPathNameW(wstrModuleFilePath, (unsigned int)wstrModuleFilePath.length(), pFolder, &pszModuleFileName))
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


}


void __node_acme_pos_init()
{


}


void __node_acme_pre_term()
{


}


void __node_acme_pos_term()
{


}


string read_resource_as_string(hinstance hinst, unsigned int nID, const ::scoped_string & scopedstrType, character_count iReadAtMostByteCount = -1)
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

   unsigned int dwResSize = ::SizeofResource((HINSTANCE)hinst, hrsrc);

   string str;

   char * psz = nullptr;

   if (hres != nullptr)
   {

      unsigned int * pnRes = (unsigned int *)::LockResource(hres);

      iReadAtMostByteCount = iReadAtMostByteCount < 0 ? dwResSize : minimum(iReadAtMostByteCount, (character_count)dwResSize);

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

//    wstring wstrUrl(scopedstrUrl);

//    ::ShellExecuteW(nullptr, L"open", wstrUrl, nullptr, nullptr, SW_SHOWNORMAL);

// }

//
//
//CLASS_DECL_ACME string get_error_string(long long iError)
//{
//
//
//}
//


//void windows_message_box_factory(::factory::factory * pfactory);


//void windows_factory(::factory::factory * pfactory)
//{
//
//   windows_message_box_factory(pfactory);
//
//}


CLASS_DECL_ACME ::file::path windows_bash_path(const ::file::path& path)
{

   if (path.size() > 3)
   {

      if (::character_isalpha(path[0])
         && path[1] == ':'
         && (path[2] == '/' || path[2] == '\\'))
      {

         ::string str;

         str = "/";

         str += ::character_tolower(path[0]);

         str += "/";

         str += path.substr(3);

         return str;

      }

   }

   return path;

}


namespace windows
{


   HWND get_mouse_capture(itask itask)
   {

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      HWND hwndCapture = nullptr;

      if (GetGUIThreadInfo((DWORD)itask.m_i, &info))
      {

         hwndCapture = info.hwndCapture;

      }

      if (!hwndCapture)
      {

         hwndCapture = ::GetCapture();

      }

      return hwndCapture;

   }


   bool set_mouse_capture(itask itask, HWND hwnd)
   {

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      if (::GetGUIThreadInfo((DWORD)itask.m_i, &info))
      {

         if (info.hwndCapture == hwnd)
         {

            return false;

         }

         DWORD currentThreadId = ::GetCurrentThreadId();

         if ((DWORD)itask.m_i != currentThreadId)
         {

            ::AttachThreadInput(currentThreadId, (DWORD)itask.m_i, TRUE);

         }

         ::SetCapture(hwnd);

         if ((DWORD)itask.m_i != currentThreadId)
         {

            ::AttachThreadInput(currentThreadId, (DWORD)itask.m_i, FALSE);

         }

      }
      else
      {

         auto hwndCapture = ::GetCapture();

         if (hwndCapture == hwnd)
         {

            return false;

         }

         ::SetCapture(hwnd);

      }

      return true;

   }


   bool defer_release_mouse_capture(itask itask, HWND hwnd)
   {

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      if (::GetGUIThreadInfo((DWORD)itask.m_i, &info))
      {

         if (info.hwndCapture != hwnd)
         {

            return false;

         }

         DWORD currentThreadId = ::GetCurrentThreadId();

         if ((DWORD)itask.m_i != currentThreadId)
         {

            ::AttachThreadInput(currentThreadId, (DWORD)itask.m_i, TRUE);

         }

         ::ReleaseCapture();

         if ((DWORD)itask.m_i != currentThreadId)
         {

            ::AttachThreadInput(currentThreadId, (DWORD)itask.m_i, FALSE);

         }

      }
      else
      {

         auto hwndCapture = ::GetCapture();

         if (hwndCapture == hwnd)
         {

            return false;

         }

         ::ReleaseCapture();

      }

      return true;

   }


} // namespace windows






CLASS_DECL_ACME HMODULE GetModuleFromFunction(void* pFunc)
{
   HMODULE hModule = NULL;

   GetModuleHandleEx(
      GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
      GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
      (LPCTSTR)pFunc,
      &hModule
   );

   return hModule;
}


CLASS_DECL_ACME void copy(MSG& msg, const MESSAGE& message)
{

    msg.hwnd = ::as_HWND(message.m_operatingsystemwindow);
    msg.message = (UINT)message.m_eusermessage;
    msg.wParam = message.m_wparam;
    msg.lParam = message.m_lparam;
    msg.pt.x = message.m_point.x;
    msg.pt.y = message.m_point.y;
    msg.time = (DWORD)message.m_time;

}


// CLASS_DECL_ACME HINSTANCE hinstance_from_function(void * pFunc)
// {
//
//    return (HINSTANCE) GetModuleFromFunction(pFunc);
//
// }
//



namespace windows
{



int message_box(
                HWND hwnd,
                const ::scoped_string & scopedstrMessage,
                const ::scoped_string & scopedstrCaption,
                UINT uType)
{
   
   auto iResult = ::MessageBox(hwnd, ::wstring(scopedstrMessage), ::wstring(scopedstrCaption), uType);
   
   return iResult;
   
}



} 
