#pragma once


#include <shellapi.h>
#include <wincrypt.h>

#include "thread.h"
#include "utils.h"
//#include "graphics.h"


CLASS_DECL_ACME char get_drive_letter(const char * pDevicePath);


CLASS_DECL_ACME void set_main_thread(HANDLE hThread);
CLASS_DECL_ACME void set_main_thread_id(UINT uiThread);


CLASS_DECL_ACME HANDLE get_main_thread();
CLASS_DECL_ACME UINT   get_main_thread_id();


//CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd);
//CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle();
//CLASS_DECL_ACME bool GetPrimaryMonitorRect(RECT * prect);


CLASS_DECL_ACME int WinRegGetValueW(HKEY hkey, LPCWSTR pSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);



#define MESSAGE MSG
#define LPMESSAGE LPMSG



