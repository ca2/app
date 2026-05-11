#pragma once



#include <stdarg.h>
#include <wchar.h>

#include "cross_win_gdi.h"
#include "acme/operating_system/window.h"

#define _fileno   fileno
#define _unlink   unlink


#define WAIT_FAILED              ((::u32   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((::u32   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


::operating_system::window get_capture();
::operating_system::window set_mouse_capture(const ::operating_system::window & operatingsystemwindow);
::i32_bool release_mouse_capture();
::operating_system::window set_keyboard_focus(const ::operating_system::window & operatingsystemwindow);
::operating_system::window get_keyboard_focus();
::operating_system::window get_active_window();
::operating_system::window set_active_window(const ::operating_system::window & operatingsystemwindow);


::i32_rectangle get_main_screen_rectangle();


int GetScreenRect(::i32_rectangle * prectangle, int iMonitor);


int GetScreenCount();

int GetWorkspaceRect(::i32_rectangle * prectangle, int iMonitor);


int GetWorkspaceCount();


::i32_bool set_foreground_window(const ::operating_system::window & operatingsystemwindow);
::i32_bool BringWindowToTop(const ::operating_system::window & operatingsystemwindow);

void ns_redraw_window(const ::operating_system::window & operatingsystemwindow);




