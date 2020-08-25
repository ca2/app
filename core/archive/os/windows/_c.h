#pragma once


#include <shellapi.h>
#include <wincrypt.h>

#include "multithreading.h"
#include "utils.h"
#include "graphics.h"



char get_drive_letter(const char * pDevicePath);


CLASS_DECL_AURA void set_main_thread(HANDLE hThread);
CLASS_DECL_AURA void set_main_thread_id(UINT uiThread);


CLASS_DECL_AURA HANDLE get_main_thread();
CLASS_DECL_AURA UINT   get_main_thread_id();


CLASS_DECL_AURA HMONITOR GetUiMonitorHandle(HWND hwnd);
CLASS_DECL_AURA HMONITOR GetPrimaryMonitorHandle();
CLASS_DECL_AURA bool GetPrimaryMonitorRect(RECT * prect);











CLASS_DECL_AURA int WinRegGetValueW(HKEY hkey, LPCWSTR pSubKey, LPCWSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);













CLASS_DECL_AURA HFONT wingdi_CreatePointFont(int nPointSize, const char * pszFaceName, HDC hdc, LOGFONTW* lpLogFont = nullptr);


CLASS_DECL_AURA HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc);






#define MESSAGE MSG
#define LPMESSAGE LPMSG





