#pragma once


//#if !defined(WINDOWS_DESKTOP)
//
//void set_defer_process_x_message(bool (* pfn)(hthread_t hthread,MESSAGE * pMsg,oswindow oswindow,bool bPeek));
//
//
//#ifdef __cplusplus
//
////#undef synchronization_object
////class synchronization_object;
////
////#ifdef WINDOWS
////using HSYNC = HANDLE;
////#else
////using HSYNC = synchronization_object *;
////#endif
//
//#ifdef _UWP
//
//#pragma warning (disable:4273)
//
//CLASS_DECL_APEX ::u32 WINAPI MsgWaitForMultipleObjects(::u32 nCount, const HANDLE * pHandles, BOOL fWaitAll, ::u32 dwMilliseconds, ::u32 dwWakeMask);
//
//CLASS_DECL_APEX ::u32 WINAPI MsgWaitForMultipleObjectsEx(::u32 nCount, const HANDLE* pHandles, ::u32 dwMilliseconds, ::u32 dwWakeMask, ::u32 dwFlags);
//
//#else
//
////::u32 WaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable);
////
////::u32 WaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout);
////
////::u32 MsgWaitForMultipleObjects(::u32 dwSize, HSYNC * synca, int_bool bWaitForAll, ::u32 tickTimeout, ::u32 dwWakeMask);
////
////::u32 MsgWaitForMultipleObjectsEx(::u32 dwSize, HSYNC * synca, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags);
//
//#endif
//
//
//#ifndef _UWP
//
//::u32 WaitForSingleObject(HSYNC hsync, ::u32 dwMilliseconds);
//
//::u32 WaitForSingleObjectEx(HSYNC hsync, ::u32 dwMilliseconds, int_bool bAlertable);
//
//#endif
//
//
//#endif
//
//
//
//#if !defined(__APPLE__) && !defined(ANDROID)
//
//union semun
//{
//   int val; /* Value for SETVAL */
//   struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
//   unsigned short *array; /* Array for GETALL, SETALL */
//   struct seminfo *__buf; /* Buffer for IPC_INFO
//                                (Linux-specific) */
//};
//
//#endif
//
//#define MWMO_WAITALL        0x0001
//#define MWMO_ALERTABLE      0x0002
//#define MWMO_INPUTAVAILABLE 0x0004
//
//
//// class thread;
//// class message_queue;
//
//
//// CLASS_DECL_APEX int_bool WINAPI GetMessage(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);
//
//// CLASS_DECL_APEX int_bool WINAPI PeekMessage(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
//
//// CLASS_DECL_APEX int_bool WINAPI PostThreadMessage(ithread_t idthread, ::u32 Msg, WPARAM wParam, LPARAM lParam);
//
//// CLASS_DECL_APEX void mq_clear(ithread_t hthread);
//
//
//// #ifndef _UWP
//
//// CLASS_DECL_APEX ::u32 WINAPI GetThreadId(hthread_t Thread);
//
//// CLASS_DECL_APEX hthread_t GetCurrentThread();
//
//// CLASS_DECL_APEX ithread_t GetCurrentThreadId();
//
//// #endif
//
//
//#endif




