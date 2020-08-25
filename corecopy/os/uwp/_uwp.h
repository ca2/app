#pragma once


#include "gdi_winrt.h"


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


//CLASS_DECL_CORE bool __cdecl __is_idle_message(::message::message * pmessage);
//CLASS_DECL_CORE bool __cdecl __is_idle_message(MESSAGE * pMsg);


//CLASS_DECL_CORE oswindow WINAPI WinGetFocus();
//CLASS_DECL_CORE oswindow WINAPI WinSetFocus(oswindow oswindow);


CLASS_DECL_CORE string normalize_path(const char* lpcszPath);


CLASS_DECL_CORE oswindow get_capture();
CLASS_DECL_CORE oswindow set_capture(oswindow oswindow);
CLASS_DECL_CORE WINBOOL release_capture();

CLASS_DECL_CORE oswindow get_active_window();
CLASS_DECL_CORE oswindow set_active_window(oswindow oswindow);



CLASS_DECL_CORE int_bool is_window(oswindow oswindow);


//CLASS_DECL_CORE int WINAPI GetSystemMetrics(int i);

namespace user
{

   class interaction_impl;
   class interaction;
   //   class interaction;
   //
   //
} // namespace user


#include "aura/graphics/graphics/buffer.h"
//#include "_UWP_gdi_winrt.h"


#include "oswindow.h"



#include "exception_engine.h"




//CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
//CLASS_DECL_CORE::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
//CLASS_DECL_CORE bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);


#include "file_winrt.h"


