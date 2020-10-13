#pragma once



#ifndef _UWP

typedef struct tag_MSG
{
   oswindow    hwnd;
   UINT        message;
   WPARAM      wParam;
   LPARAM      lParam;
   POINT       pt;
} MESSAGE, * LPMESSAGE;
#endif



//CLASS_DECL_APEX int_bool WINAPI GetMessage(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

//CLASS_DECL_APEX int_bool WINAPI PeekMessage(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax,UINT wRemoveMsg);

//CLASS_DECL_APEX int_bool WINAPI PostThreadMessage(ITHREAD idthread, UINT Msg, WPARAM wParam, LPARAM lParam);


//CLASS_DECL_APEX void WINAPI TlsShutdown();


#ifndef _UWP

CLASS_DECL_APEX BOOL WINAPI SetThreadPriority(HTHREAD hThread,int iPriority);

CLASS_DECL_APEX int WINAPI GetThreadPriority(HTHREAD hThread);

#endif



//DWORD WinMsgWaitForMultipleObjects(DWORD dwSize,const HANDLE * lphandles,DWORD tickTimeout,DWORD dwWakeMask,DWORD dwFlags);
