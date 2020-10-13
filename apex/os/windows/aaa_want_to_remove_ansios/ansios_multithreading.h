#ifndef APEX_ANSIOS_MULTITHREADING_H
#define APEX_ANSIOS_MULTITHREADING_H


#pragma once


#if defined(LINUX) // || defined(ANDROID)

void set_defer_process_x_message(bool (* pfn)(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek));

#endif




#ifdef __cplusplus


class sync_object;


DWORD WaitForMultipleObjectsEx(DWORD dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, DWORD tickTimeout, int_bool bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, DWORD tickTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, DWORD tickTimeout, DWORD dwWakeMask);

DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, sync_object ** pwaitableptra, DWORD tickTimeout, DWORD dwWakeMask, DWORD dwFlags);

DWORD WaitForSingleObject(sync_object * pwaitable, DWORD dwMilliseconds);

DWORD WaitForSingleObjectEx(sync_object * pwaitable, DWORD dwMilliseconds, int_bool bAlertable);


#endif


/*
#define STATUS_WAIT_0            ((DWORD   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((DWORD   ) 0x00000080L)
#define STATUS_USER_APC          ((DWORD   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((DWORD   ) 0x00000102L)
 */

#define WAIT_FAILED              ((DWORD   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((DWORD   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


#if !defined(APPLEOS)

union semun {
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






#endif // APEX_ANSIOS_MULTITHREADING_H










