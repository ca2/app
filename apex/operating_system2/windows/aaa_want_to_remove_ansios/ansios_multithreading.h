#ifndef APEX_ANSIOS_MULTITHREADING_H
#define APEX_ANSIOS_MULTITHREADING_H


#pragma once


#if defined(LINUX) // || defined(ANDROID)

void set_defer_process_x_message(bool (* pfn)(htask htask,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek));

#endif




#ifdef __cplusplus


class sync_object;


unsigned int WaitForMultipleObjectsEx(unsigned int dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, unsigned int tickTimeout, int_bool bAlertable);

unsigned int WaitForMultipleObjects(unsigned int dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, unsigned int tickTimeout);

#if !defined(UNIVERSAL_WINDOWS)

unsigned int MsgWaitForMultipleObjects(unsigned int dwSize, sync_object ** pwaitableptra, int_bool bWaitForAll, unsigned int tickTimeout, unsigned int dwWakeMask);

unsigned int MsgWaitForMultipleObjectsEx(unsigned int dwSize, sync_object ** pwaitableptra, unsigned int tickTimeout, unsigned int dwWakeMask, unsigned int dwFlags);

#endif

unsigned int WaitForSingleObject(sync_object * pwaitable, unsigned int dw::durations);

unsigned int WaitForSingleObjectEx(sync_object * pwaitable, unsigned int dw::durations, int_bool bAlertable);


#endif


/*
#define STATUS_WAIT_0            ((unsigned int   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((unsigned int   ) 0x00000080L)
#define STATUS_USER_APC          ((unsigned int   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((unsigned int   ) 0x00000102L)
 */

#define WAIT_FAILED              ((unsigned int   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((unsigned int   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((unsigned int   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((unsigned int   ) STATUS_ABANDONED_WAIT_0 + 0)

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










