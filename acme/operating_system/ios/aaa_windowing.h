//
//  ios_windowing.hpp
//  ios_acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 10/12/17.
//
#pragma once


#ifndef __OBJC__

struct UIWindow;

#endif

UIWindow * __uiwindow(::acme::windowing::window * pacmewindowingwindow);


::i32 get_main_screen_rectangle(::i32_rectangle * lprect);

::i32 GetScreenRect(::i32_rectangle * lprect, ::i32 iMonitor);

::i32 GetScreenCount();

::i32 GetWorkspaceRect(::i32_rectangle * lprect, ::i32 iMonitor);

::i32 GetWorkspaceCount();


//
//  ios_window.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//


//oswindow get_capture();
//oswindow set_capture(oswindow window);
//int_bool release_capture();
//oswindow set_focus(oswindow window);
//oswindow get_focus();
//oswindow get_active_window();
//oswindow set_active_window(oswindow window);


//void get_main_screen_rectangle(::i32_rectangle * lprect);

int_bool set_foreground_window(oswindow window);
int_bool BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);






#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA


void deactivate_window(oswindow window);


//oswindow get_window(oswindow window, ::i32 iParentHood);



