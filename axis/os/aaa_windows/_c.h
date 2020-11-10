#pragma once


#include <shellapi.h>
#include <wincrypt.h>

#include "multithreading.h"
#include "utils.h"
#include "graphics.h"



char get_drive_letter(const char * pDevicePath);


CLASS_DECL_AXIS void set_main_thread(HANDLE hThread);
CLASS_DECL_AXIS void set_main_thread_id(::u32 uThread);


CLASS_DECL_AXIS HANDLE get_main_thread();
CLASS_DECL_AXIS ::u32   get_main_thread_id();


CLASS_DECL_AXIS HMONITOR GetUiMonitorHandle(HWND hwnd);
CLASS_DECL_AXIS HMONITOR GetPrimaryMonitorHandle();
CLASS_DECL_AXIS bool GetPrimaryMonitorRect(RECT32 * prect);











CLASS_DECL_AXIS int WinRegGetValueW(HKEY hkey, LPCWSTR pSubKey, LPCWSTR lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);













CLASS_DECL_AXIS HFONT wingdi_CreatePointFont(int nPointSize, const char * pszFaceName, HDC hdc, LOGFONTW* lpLogFont = nullptr);


CLASS_DECL_AXIS HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc);






#define MESSAGE MSG
#define LPMESSAGE LPMSG





