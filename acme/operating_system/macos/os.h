#pragma once



#include <stdarg.h>
#include <wchar.h>

#include "cross_win_gdi.h"


#define _fileno   fileno
#define _unlink   unlink


#define WAIT_FAILED              ((::u32   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((::u32   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


oswindow get_capture();
oswindow set_capture(oswindow window);
int_bool release_capture();
oswindow set_foucs(oswindow window);
oswindow get_focus();
oswindow get_active_window();
oswindow set_active_window(oswindow window);


RECTANGLE_I32 get_main_screen_rectangle();


int GetScreenRect(RECTANGLE_I32 * prectangle, int iMonitor);


int GetScreenCount();

int GetWorkspaceRect(RECTANGLE_I32 * prectangle, int iMonitor);


int GetWorkspaceCount();


int_bool SetForegroundWindow(oswindow window);
int_bool BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);




