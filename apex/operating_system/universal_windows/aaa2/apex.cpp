#include "framework.h"
//#include "universal_windows.h"
//#include <winternl.h>
//#include <VersionHelpers.h>


namespace audio
{

   CLASS_DECL_APEX string get_default_library_name()
   {

      return "audio_xaudio";

   }

} // namespace audio


// int message_box_w(oswindow window,const unichar * pszMessage,const unichar * pszTitle,int iFlags)
// {


//    ::wait(::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler ([=]()
//    {

//       ::winrt::Windows::UI::Popups::MessageDialog ^ msg = ref new ::winrt::Windows::UI::Popups::MessageDialog(wstring(pszMessage), wstring(pszTitle));

// //UICommand^ continueCommand = ref new UICommand(
//       //      "Try again",
//       //    ref new UICommandInvokedHandler(this, &CancelCommand::CommandInvokedHandler));
//       ::winrt::Windows::UI::Popups::UICommand ^ upgradeCommand = ref new ::winrt::Windows::UI::Popups::UICommand(
//             "OK");

//       // Add the commands to the dialog
//       //msg->Commands->Append(continueCommand);
//       msg->Commands->Append(upgradeCommand);

//       // Set the command that will be invoked by default
//       msg->DefaultCommandIndex = 0;

//       // Set the command to be invoked when escape is pressed
//       msg->CancelCommandIndex = 0;

//       ::winrt::Windows::UI::Popups::IUICommand ^ command = wait(msg->ShowAsync());

//    })));

//    return 0;

// }


#ifndef _UWP




VOID WINAPI sleep(::u32 dw::durations)
{
   static HANDLE singletonEvent = nullptr;

   HANDLE sleepEvent = singletonEvent;

   // Demand create the event.
   if (!sleepEvent)
   {
      sleepEvent = CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

      if (!sleepEvent)
         return;

      HANDLE previousEvent = InterlockedCompareExchangePointerRelease(&singletonEvent, sleepEvent, nullptr);

      if (previousEvent)
      {
         // Back out if multiple threads try to demand create at the same time.
         CloseHandle(sleepEvent);
         sleepEvent = previousEvent;
      }
   }

   // Emulate sleep by waiting with timeout on an event that is never signalled.
   WaitForSingleObjectEx(sleepEvent, dw::durations, false);
}
#endif

// typedef bool
// (WINAPI * LPFN_ChangeWindowMessageFilter)(
// _In_ const ::atom & atom,
// _In_ ::u32 dwFlag);


// LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = nullptr;

/*
typedef
LSTATUS
( APIENTRY * LPFN_RegGetValueW) (
    HKEY hkey,
    const widechar * lpSubKey,
    const widechar * lpValue,
    ::u32 dwFlags,
    LPDWORD pdwType,
	 PVOID pvData,
    LPDWORD pcbData
    );

LPFN_RegGetValueW g_pfnRegGetValueW = nullptr;

*/

/*

bool os_initialize()
{

   ::os_thread::s_pmutex = new ::mutex();

   ::os_thread::s_pptra = new simple_array < os_thread * > ();

   //sleep(15 * 1000);

   if(!initialize_primitive_trace())
      return false;




#ifndef _UWP

   HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32, "RegGetValueW");

#endif

   return true;

}


bool os_finalize()
{

   finalize_primitive_trace();

   return true;

}
*/


/*Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput     = nullptr;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput    = nullptr;
ulong_ptr                        g_gdiplusToken             = nullptr;
ulong_ptr                        g_gdiplusHookToken         = nullptr;
*/




//int_bool main_initialize()
//{
//
//   //sleep(15 * 1000);
//
//   /*   g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
//      g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
//      g_gdiplusToken             = nullptr;
//      g_gdiplusHookToken         = nullptr;
//
//      //MessageBox(nullptr, "Gdiplus Failed to Startup. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);
//
//      g_pgdiplusStartupInput->SuppressBackgroundThread = true;
//
//      // Initialize GDI+.
//      Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);
//
//      if(statusStartup != Gdiplus::Ok)
//      {
//
//         MessageBox(nullptr, "Gdiplus Failed to Startup. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);
//
//         return false;
//
//      }
//
//      statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);
//
//
//      if(statusStartup != Gdiplus::Ok)
//      {
//
//         MessageBox(nullptr, "Gdiplus Failed to Hook. ca2 cannot continue.", "Gdiplus Failure", MB_ICONERROR);
//
//         return false;
//
//      }
//      */
//
//   //t_phtask = new htask();
//
//   //t_phtask->m_bRun = true;
//
//   //currentThread = new htask();
//
//
//   return true;
//
//}
//
//
//int_bool main_finalize()
//{
//
//
//   return true;
//
//}



string normalize_path(const char * lpcszPath)
{

   if(lpcszPath == nullptr)
      return "";

   if(*lpcszPath == '\0')
      return "";

   string path = lpcszPath;

   string oldpath;

   while(oldpath != path)
   {

      oldpath = path;

      path.replace("\\\\", "\\");

   }

   oldpath = "";

   while(oldpath != path)
   {

      oldpath = path;

      path.replace("...", "..");

   }

   iptr iFind;

   while((iFind = path.find("..")) >= 0)
   {

      if(iFind <= 0)
      {
         path = path.substr(2);
      }
      else
      {
         iptr iFind2 = path.reverse_find('\\', iFind);
         if(iFind2 < 0)
         {
            path = path.substr(0, iFind) + path.substr(iFind + 2);
         }
         else if(iFind2 == 0)
         {
            path = path.substr(3);
         }
         else
         {
            iptr iFind3 = path.reverse_find('\\', iFind2 - 1);
            if(iFind3 <= 0)
            {
               path = path.substr(iFind + 2);
            }
            else
            {
               path = path.substr(0, iFind3) + path.substr(iFind + 2);
            }
         }
      }
   }

   return path;

}



string key_to_char(wparam wparam, lparam lparam)
{
   throw ::exception(::exception("todo"));
}




//string get_last_error_message(u32 dwError)
//{
//   wstring wstr;
//   unichar * p = wstr.get_string_buffer(64 * 1024 / sizeof(unichar));
//   ::u32 dw = FormatMessageW(
//              FORMAT_MESSAGE_FROM_SYSTEM,
//              nullptr,
//              dwError,
//              0,
//              p,
//              wstr.get_length() / sizeof(unichar),
//              nullptr);
//   p[dw] = L'\0';
//   wstr.release_string_buffer();
//   string str(wstr);
//   return str;
//}




//::u32 WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ ::u32 dw::durations )
//{
//
//   return ::WaitForSingleObjectEx(hHandle, dw::durations, false);
//
//}



//CLASS_DECL_APEX
//HANDLE
//WINAPI
//CreateMutex(
//    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
//    _In_ BOOL bInitialOwner,
//    _In_opt_ const char * lpName
//    )
//{
//   return CreateMutexW(lpMutexAttributes, bInitialOwner, wstring(lpName));
//}

//CLASS_DECL_APEX char* getenv (const char* name)
//{
//   return "";
//}
//

//CLASS_DECL_APEX
//_Ret_maybenull_
//HANDLE
//WINAPI
//CreateMutexW(
//   _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
//   _In_ BOOL bInitialOwner,
//   _In_opt_ const widechar * lpName
//   )
//{
//   return ::CreateMutexEx(lpMutexAttributes, lpName, bInitialOwner ?  CREATE_MUTEX_INITIAL_OWNER : 0, DELETE | SYNCHRONIZE);
//}
//








//
//
//int_bool is_windows_nt()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
////   return IsWindowsXPOrGreater();
//
//   return true;
//
//#else
//
//   return !(GetVersion() & 0x80000000);
//
//#endif
//
//}
//
//
//





bool defer_co_initialize_ex(bool bMultiThread)
{

   auto ptask = ::get_task();

   if(!ptask)
   {

      return false;

   }

   HRESULT hr = ptask->m_hresultCoInitialize;

   if(!ptask->m_bitCoInitialize)
   {

      ptask->m_bitCoInitialize = true;
    
      hr = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);

   }

   if(FAILED(hr))
   {

      if (hr == 0x80010106)
      {

         return true;

      }

      ::output_debug_string("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");

      return false;

   }

   return true;

}


//bool defer_initialize_winsock();


bool __node_apex_pre_init()
{

   defer_initialize_winsock();

   HRESULT hresult = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);

   if(FAILED(hresult))
   {

      if(hresult == RPC_E_CHANGED_MODE)
      {

         hresult = ::CoInitializeEx(nullptr,COINIT_APARTMENTTHREADED);

         if(FAILED(hresult))
         {

            os_output_error_message("Failed to ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED) at __node_pre_init","__node_pre_init failure",e_message_box_icon_exclamation);

            return false;

         }

      }
      else
      {

         os_output_error_message("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init","__node_pre_init failure",e_message_box_icon_exclamation);

         return false;

      }

   }

   return true;

}

void CLASS_DECL_APEX __cdecl _ca2_purecall();

bool __node_apex_pos_init()
{

   _set_purecall_handler(_ca2_purecall);

   //HMODULE hmoduleUser32 = ::LoadLibrary("User32");
   //g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32,"ChangeWindowMessageFilter");


   //HMODULE hmoduleAdvApi32 = ::LoadLibrary("AdvApi32");
   //g_pfnRegGetValueW = (LPFN_RegGetValueW) ::GetProcAddress(hmoduleAdvApi32,"RegGetValueW");

   //g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();
   //g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();
   //g_gdiplusToken             = nullptr;
   //g_gdiplusHookToken         = nullptr;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   message_box(nullptr,"Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return false;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);


   //if(statusStartup != Gdiplus::Ok)
   //{

   //   message_box(nullptr,"Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return false;

   //}

   return true;

}


bool __node_apex_pre_term()
{

   return true;

}

bool __node_apex_pos_term()
{

   ::CoUninitialize();

   return true;

}

// void os_term_application()
// {

//    ::winrt::Windows::ApplicationModel::Core::CoreApplication::Exit();

// }







//int_bool is_windows_7_or_lower()
//{
//
//   return false; // metro is from windows 8
//
//}
