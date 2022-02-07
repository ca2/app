#pragma once


#include "acme/operating_system/universal_windows/_universal_windows.h"
///#include "gdi_winrt.h"


#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif


//CLASS_DECL_APEX bool __cdecl __is_idle_message(::message::message * pmessage);
//CLASS_DECL_APEX bool __cdecl __is_idle_message(MESSAGE * pMsg);


//CLASS_DECL_APEX oswindow WINAPI WinGetFocus();
//CLASS_DECL_APEX oswindow WINAPI WinSetFocus(oswindow oswindow);


//CLASS_DECL_APEX string normalize_path(const char* lpcszPath);


//CLASS_DECL_APEX oswindow get_capture();
//CLASS_DECL_APEX oswindow set_capture(oswindow oswindow);
//CLASS_DECL_APEX int_bool release_capture();

//CLASS_DECL_APEX oswindow get_active_window();
//CLASS_DECL_APEX oswindow set_active_window(oswindow oswindow);



//CLASS_DECL_APEX int_bool is_window(oswindow oswindow);


//CLASS_DECL_APEX int WINAPI GetSystemMetrics(int i);

namespace user
{

   class interaction_impl;
   class interaction;
   //   class interaction;
   //
   //
} // namespace user


//#include "apex/graphics/graphics/buffer.h"
//#include "_UWP_gdi_winrt.h"


//#include "oswindow.h"



//#include "exception_engine.h"




//CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
//CLASS_DECL_APEX::winrt::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
//CLASS_DECL_APEX bool get_filetime(::winrt::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);


//#include "file_winrt.h"


