#pragma once


#include <shellapi.h>
#include <wincrypt.h>

#include "parallelization.h"
#include "utils.h"
#include "graphics.h"



char get_drive_letter(const char * pDevicePath);


CLASS_DECL_AXIS void set_main_hthread(hthread_t hthread);
CLASS_DECL_AXIS void set_main_ithread(ithread_t ithread);


CLASS_DECL_AXIS HANDLE get_main_hthread();
CLASS_DECL_AXIS ::u32   get_main_ithread();


CLASS_DECL_AXIS HMONITOR GetUiMonitorHandle(HWND hwnd);
CLASS_DECL_AXIS HMONITOR GetPrimaryMonitorHandle();
CLASS_DECL_AXIS bool GetPrimaryMonitorRect(RECT32 * prect);











CLASS_DECL_AXIS int WinRegGetValueW(HKEY hkey, const widechar * pSubKey, const widechar * lpValue, ::u32 dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);













CLASS_DECL_AXIS HFONT wingdi_CreatePointFont(int nPointSize, const char * pszFaceName, HDC hdc, LOGFONTW* lpLogFont = nullptr);


CLASS_DECL_AXIS HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc);






#define MESSAGE MSG
#define LPMESSAGE LPMSG





