#ifndef APEX_ANSIOS_MULTITHREADING_H
#define APEX_ANSIOS_MULTITHREADING_H


#pragma once


#if defined(LINUX) // || defined(ANDROID)

void set_defer_process_x_message(bool (* pfn)(htask_t hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek));

#endif




#ifdef __cplusplus


class sync_object;


::u32 WaitForMultipleObjectsEx(::u32 dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable);

::u32 WaitForMultipleObjects(::u32 dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, ::u32 tickTimeout);

::u32 MsgWaitForMultipleObjects(::u32 dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, ::u32 tickTimeout, ::u32 dwWakeMask);

::u32 MsgWaitForMultipleObjectsEx(::u32 dwSize, sync_object ** pwaitableptra, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags);

::u32 WaitForSingleObject(sync_object * pwaitable, ::u32 dwMilliseconds);

::u32 WaitForSingleObjectEx(sync_object * pwaitable, ::u32 dwMilliseconds, int_bool bAlertable);


#endif


/*
#define STATUS_WAIT_0            ((::u32   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((::u32   ) 0x00000080L)
#define STATUS_USER_APC          ((::u32   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((::u32   ) 0x00000102L)
 */

#define WAIT_FAILED              ((::u32   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((::u32   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)

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










