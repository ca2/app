#ifndef BASE_SOLARIS_SOLARIS_H
#define BASE_SOLARIS_SOLARIS_H


#pragma once



#include <wchar.h>

#include "solaris_graphics.h"
#include "solaris_http_lib.h"
#include "solaris_http.h"
#include "solaris_process.h"
#include "solaris_cross_win_gdi.h"
#include "solaris_cross_win_file.h"
#include "solaris_file.h"
#include "solaris_file_watcher.h"
//#include "solaris_cairo_keep.h"
#include "solaris_window_xlib.h"



#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"



unsigned int ::get_tick();




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

CLASS_DECL_APEX bool _istlead(int ch);


#endif // BASE_SOLARIS_SOLARIS_H




