﻿#pragma once



#ifndef _UWP

typedef struct tag_MSG
{
   oswindow    hwnd;
   ::u32        message;
   WPARAM      wParam;
   LPARAM      lParam;
   POINT_I32       pt;
} MESSAGE, * MESSAGE *;
#endif



//CLASS_DECL_APEX int_bool WINAPI GetMessage(MESSAGE * lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

//CLASS_DECL_APEX int_bool WINAPI PeekMessage(MESSAGE * lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax,::u32 wRemoveMsg);

//CLASS_DECL_APEX int_bool WINAPI PostThreadMessage(itask_t idthread, ::u32 Msg, WPARAM wParam, LPARAM lParam);


//CLASS_DECL_APEX void WINAPI TlsShutdown();


#ifndef _UWP

CLASS_DECL_APEX BOOL WINAPI SetThreadPriority(htask_t htask,int iPriority);

CLASS_DECL_APEX int WINAPI GetThreadPriority(htask_t htask);

#endif



//::u32 WinMsgWaitForMultipleObjects(::u32 dwSize,const HANDLE * lphandles,::u32 tickTimeout,::u32 dwWakeMask,::u32 dwFlags);
