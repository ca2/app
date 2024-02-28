#pragma once


#include <wchar.h>

#include "graphics.h"


#include "process.h"
#include "cross_win_gdi.h"
#include "cross_win_file.h"
#include "file.h"
//#include "file_watcher.h"
//#include "window_impl.h"

#include "exception_engine.h"

//#include "windowing.h"

#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"


void get_os_priority(i32 * piPolicy, sched_param * pparam, ::enum_priority epriority);
::i64 get_tick();


CLASS_DECL_ACME void * __node_library_touch(const ::file::path & path, string & strMessage);
CLASS_DECL_ACME void * __node_library_open(const ::file::path & path, string & strMessage);



#define _fileno   fileno
#define _unlink   unlink


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


//CLASS_DECL_ACME ::u32 get_last_error();
//CLASS_DECL_ACME void set_last_error(::u32 dw);


CLASS_DECL_ACME bool _istlead(i32 ch);










































