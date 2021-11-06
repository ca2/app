#pragma once


#include "acme/node/operating_system/windows/_windows.h"


inline void copy(MESSAGE * pmessage, const MSG * pmsg)
{

   pmessage->oswindow = (oswindow)(pmsg->hwnd);
   pmessage->m_id = (enum_message)pmsg->message;
   pmessage->wParam = pmsg->wParam;
   pmessage->lParam = pmsg->lParam;
   pmessage->pt = pmsg->pt;
   pmessage->time = pmsg->time;


}

inline void copy(MSG * pmsg, const MESSAGE * pmessage)
{

   pmsg->hwnd = (HWND)(pmessage->oswindow);
   pmsg->message = (UINT)pmessage->m_id.i64();
   pmsg->wParam = pmessage->wParam;
   pmsg->lParam = pmessage->lParam;
   pmsg->pt.x = pmessage->pt.x;
   pmsg->pt.y = pmessage->pt.y;
   pmsg->time = (DWORD)pmessage->time;


}



