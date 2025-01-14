#pragma once



#ifndef UNIVERSAL_WINDOWS

typedef struct tag_MSG
{
   oswindow    hwnd;
   unsigned int        message;
   WPARAM      wParam;
   LPARAM      lParam;
   ::int_point       pt;
} MESSAGE, * MESSAGE *;
#endif



//CLASS_DECL_APEX int_bool WINAPI GetMessage(MESSAGE * lpMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);

//CLASS_DECL_APEX int_bool WINAPI PeekMessage(MESSAGE * lpMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax,unsigned int wRemoveMsg);

//CLASS_DECL_APEX int_bool WINAPI PostThreadMessage(itask idthread, unsigned int Msg, WPARAM wParam, LPARAM lParam);


//CLASS_DECL_APEX void WINAPI TlsShutdown();


#ifndef UNIVERSAL_WINDOWS

CLASS_DECL_APEX BOOL WINAPI SetThreadPriority(htask htask,int iPriority);

CLASS_DECL_APEX int WINAPI GetThreadPriority(htask htask);

#endif



//unsigned int WinMsgWaitForMultipleObjects(unsigned int dwSize,const HANDLE * lphandles,unsigned int tickTimeout,unsigned int dwWakeMask,unsigned int dwFlags);
