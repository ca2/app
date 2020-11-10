#pragma once


#include <shellapi.h>
#include <wincrypt.h>

#include "thread.h"
#include "utils.h"
//#include "graphics.h"


CLASS_DECL_ACME char get_drive_letter(const char * pDevicePath);


CLASS_DECL_ACME void set_main_hthread(hthread_t hthread);
CLASS_DECL_ACME void set_main_ithread(ithread_t ithread);


CLASS_DECL_ACME hthread_t get_main_hthread();
CLASS_DECL_ACME ithread_t get_main_ithread();


//CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd);
//CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle();
//CLASS_DECL_ACME bool GetPrimaryMonitorRect(RECT32 * prect);


CLASS_DECL_ACME int WinRegGetValueW(HKEY hkey, LPCWSTR pSubKey, LPCWSTR lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);



#define MESSAGE MSG
#define LPMESSAGE LPMSG



