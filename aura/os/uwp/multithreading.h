#pragma once



#ifndef _UWP

typedef struct tag_MSG
{
   oswindow    hwnd;
   ::u32        message;
   WPARAM      wParam;
   LPARAM      lParam;
   POINT32       pt;
} MESSAGE, * LPMESSAGE;
#endif



//CLASS_DECL_AURA int_bool WINAPI GetMessage(LPMESSAGE lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

//CLASS_DECL_AURA int_bool WINAPI PeekMessage(LPMESSAGE lpMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax,::u32 wRemoveMsg);

//CLASS_DECL_AURA int_bool WINAPI PostThreadMessage(ithread_t idthread, ::u32 Msg, WPARAM wParam, LPARAM lParam);


//CLASS_DECL_AURA void WINAPI TlsShutdown();


#ifndef _UWP

CLASS_DECL_AURA BOOL WINAPI SetThreadPriority(hthread_t hthread,int iPriority);

CLASS_DECL_AURA int WINAPI GetThreadPriority(hthread_t hthread);

#endif



//::u32 WinMsgWaitForMultipleObjects(::u32 dwSize,const HANDLE * lphandles,::u32 tickTimeout,::u32 dwWakeMask,::u32 dwFlags);
