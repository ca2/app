#pragma once


//#if !defined(WINDOWS_DESKTOP)
//
//void set_defer_process_x_message(bool (* pfn)(htask_t htask,MESSAGE * pMsg,oswindow oswindow,bool bPeek));
//
//
//#ifdef __cplusplus
//
////#undef synchronization////class synchronization;
////
////#ifdef WINDOWS
////using hsynchronization = HANDLE;
////#else
////using hsynchronization = synchronization *;
////#endif
//
//#ifdef UNIVERSAL_WINDOWS
//
//#pragma warning (disable:4273)
//
//CLASS_DECL_APEX unsigned int WINAPI MsgWaitForMultipleObjects(unsigned int nCount, const HANDLE * pHandles, BOOL fWaitAll, unsigned int dw::times, unsigned int dwWakeMask);
//
//CLASS_DECL_APEX unsigned int WINAPI MsgWaitForMultipleObjectsEx(unsigned int nCount, const HANDLE* pHandles, unsigned int dw::times, unsigned int dwWakeMask, unsigned int dwFlags);
//
//#else
//
////unsigned int WaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout, int_bool bAlertable);
////
////unsigned int WaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout);
////
////unsigned int MsgWaitForMultipleObjects(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout, unsigned int dwWakeMask);
////
////unsigned int MsgWaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, unsigned int tickTimeout, unsigned int dwWakeMask, unsigned int dwFlags);
//
//#endif
//
//
//#ifndef UNIVERSAL_WINDOWS
//
//unsigned int WaitForSingleObject(hsynchronization hsynchronization, unsigned int dw::times);
//
//unsigned int WaitForSingleObjectEx(hsynchronization hsynchronization, unsigned int dw::times, int_bool bAlertable);
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
//// CLASS_DECL_APEX int_bool WINAPI GetMessage(MESSAGE * pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax);
//
//// CLASS_DECL_APEX int_bool WINAPI PeekMessage(MESSAGE * pMsg, oswindow oswindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg);
//
//// CLASS_DECL_APEX int_bool WINAPI PostThreadMessage(itask_t idthread, unsigned int Msg, WPARAM wParam, LPARAM lParam);
//
//// CLASS_DECL_APEX void mq_clear(itask_t htask);
//
//
//// #ifndef UNIVERSAL_WINDOWS
//
//// CLASS_DECL_APEX unsigned int WINAPI GetThreadId(htask_t Thread);
//
//// CLASS_DECL_APEX htask_t GetCurrentThread();
//
//// CLASS_DECL_APEX itask_t GetCurrentThreadId();
//
//// #endif
//
//
//#endif




