#pragma once


#include <wchar.h>

#include "graphics.h"


//#include "process.h"
#include "cross_win_gdi.h"
#include "cross_win_file.h"
#include "file.h"
//#include "file_watcher.h"
//#include "window_impl.h"

#include "exception_engine.h"

//#include "windowing.h"

#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"


void get_os_priority(int * piPolicy, sched_param * pparam, ::enum_priority epriority);
long long get_tick();




#define _fileno   fileno
#define _unlink   unlink


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


#ifndef __ANDROID__

union semun
{

   int val;
   struct semid_ds * buf;
   USHORT * array;

};

#endif

//CLASS_DECL_APEX unsigned int get_last_error();
//CLASS_DECL_APEX void set_last_error(unsigned int dw);


CLASS_DECL_APEX bool _istlead(int ch);










































