#pragma once


#include "acme/operating_system/windows/_windows.h"


inline void copy(MESSAGE * pmessage, const MSG * pmsg)
{

   pmessage->oswindow = (oswindow)(pmsg->hwnd);
   pmessage->m_atom = (enum_message)pmsg->message;
   pmessage->wParam = pmsg->wParam;
   pmessage->lParam = pmsg->lParam;
   pmessage->pt.x = pmsg->pt.x;
   pmessage->pt.y = pmsg->pt.y;
   pmessage->time = pmsg->time;


}

inline void copy(MSG * pmsg, const MESSAGE * pmessage)
{

   pmsg->hwnd = (HWND)(pmessage->oswindow);
   pmsg->message = (UINT)pmessage->m_atom.i64();
   pmsg->wParam = pmessage->wParam;
   pmsg->lParam = pmessage->lParam;
   pmsg->pt.x = pmessage->pt.x;
   pmsg->pt.y = pmessage->pt.y;
   pmsg->time = (DWORD)pmessage->time;


}



