#pragma once


#if !defined(WINDOWS_DESKTOP)

void set_defer_process_x_message(bool (* pfn)(HTHREAD hthread,LPMESSAGE pMsg,oswindow oswindow,bool bPeek));


#ifdef __cplusplus

//#undef sync
//class sync;
//
//#ifdef WINDOWS
//using HSYNC = HANDLE;
//#else
//using HSYNC = sync *;
//#endif

#ifdef _UWP

#pragma warning (disable:4273)

CLASS_DECL_AURA DWORD WINAPI MsgWaitForMultipleObjects(DWORD nCount, const HANDLE * pHandles, BOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask);

CLASS_DECL_AURA DWORD WINAPI MsgWaitForMultipleObjectsEx(DWORD nCount, const HANDLE* pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags);

#else

DWORD WaitForMultipleObjectsEx(DWORD dwSize, HSYNC * synca, int_bool bWaitForAll, DWORD tickTimeout, int_bool bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, HSYNC * synca, int_bool bWaitForAll, DWORD tickTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, HSYNC * synca, int_bool bWaitForAll, DWORD tickTimeout, DWORD dwWakeMask);

DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, HSYNC * synca, DWORD tickTimeout, DWORD dwWakeMask, DWORD dwFlags);

#endif


#ifndef _UWP

DWORD WaitForSingleObject(HSYNC hsync, DWORD dwMilliseconds);

DWORD WaitForSingleObjectEx(HSYNC hsync, DWORD dwMilliseconds, int_bool bAlertable);

#endif


#endif


/*
#define STATUS_WAIT_0            ((DWORD   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((DWORD   ) 0x00000080L)
#define STATUS_USER_APC          ((DWORD   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((DWORD   ) 0x00000102L)
 */

#ifndef _UWP

#define WAIT_FAILED              ((DWORD   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((DWORD   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)

#endif

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


#if !defined(__APPLE__) && !defined(ANDROID)

union semun
{
   int val; /* Value for SETVAL */
   struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
   unsigned short *array; /* Array for GETALL, SETALL */
   struct seminfo *__buf; /* Buffer for IPC_INFO
                                (Linux-specific) */
};

#endif

#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004


// class thread;
// class mq;


// CLASS_DECL_AURA int_bool WINAPI GetMessage(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

// CLASS_DECL_AURA int_bool WINAPI PeekMessage(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

// CLASS_DECL_AURA int_bool WINAPI PostThreadMessage(ITHREAD idthread, UINT Msg, WPARAM wParam, LPARAM lParam);

// CLASS_DECL_AURA void mq_clear(ITHREAD hthread);


// #ifndef _UWP

// CLASS_DECL_AURA DWORD WINAPI GetThreadId(HTHREAD Thread);

// CLASS_DECL_AURA HTHREAD GetCurrentThread();

// CLASS_DECL_AURA ITHREAD GetCurrentThreadId();

// #endif


#endif




