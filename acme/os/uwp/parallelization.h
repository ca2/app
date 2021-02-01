#pragma once



#ifndef _UWP


#endif



//CLASS_DECL_ACME int_bool WINAPI GetMessage(MESSAGE * lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

//CLASS_DECL_ACME int_bool WINAPI PeekMessage(MESSAGE * lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax,::u32 wRemoveMsg);

//CLASS_DECL_ACME int_bool WINAPI PostThreadMessage(ithread_t idthread, ::u32 Msg, WPARAM wParam, LPARAM lParam);


CLASS_DECL_ACME void WINAPI TlsShutdown();


#ifndef _UWP

CLASS_DECL_ACME BOOL WINAPI SetThreadPriority(hthread_t hthread,int iPriority);

CLASS_DECL_ACME int WINAPI GetThreadPriority(hthread_t hthread);

#endif



//::u32 WinMsgWaitForMultipleObjects(::u32 dwSize,const HANDLE * lphandles,::u32 tickTimeout,::u32 dwWakeMask,::u32 dwFlags);
