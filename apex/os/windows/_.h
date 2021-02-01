#pragma once


#include "acme/os/windows/_.h"


inline void copy(MESSAGE * pmessage, const MSG * pmsg)
{

   pmessage->hwnd       = pmsg->hwnd;
   pmessage->message    = pmsg->message;
   pmessage->wParam     = pmsg->wParam;
   pmessage->lParam     = pmsg->lParam;
   pmessage->pt         = pmsg->pt;
   pmessage->time       = pmsg->time;


}


#ifdef WINDOWS_DESKTOP

CLASS_DECL_APEX BOOL LaunchAppIntoDifferentSession(const char * pszProcess, const char * pszCommand, const char * pszDir, STARTUPINFO * psi, PROCESS_INFORMATION * ppi, int iSession = -1);

CLASS_DECL_APEX BOOL LaunchAppIntoSystemAcc(const char * pszProcess, const char * pszCommand, const char * pszDir, STARTUPINFO * psi, PROCESS_INFORMATION * ppi);

#endif // WINDOWS_DESKTOP



CLASS_DECL_APEX HMONITOR GetPrimaryMonitorHandle();
CLASS_DECL_APEX HMONITOR GetUiMonitorHandle(HWND hwnd);


CLASS_DECL_APEX HFONT wingdi_CreatePointFont(int nPointSize, const char * pszFaceName, HDC hdc, LOGFONTW* lpLogFont = nullptr);

CLASS_DECL_APEX HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc);


#include "windowing.h"



