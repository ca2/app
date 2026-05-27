//
//  macos_window.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//
#pragma once


namespace user
{


   class interaction;
   class interaction_impl;


} // namespace user

#ifndef __OBJC__

struct NSWindow;

#endif

//NSWindow * __nswindow(::acme::windowing::window * pacmewindowingwindow);


//#include "oswindow_data.h"

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA

::i32 get_main_screen_rectangle(::i32_rectangle * prectangle);


::i32 GetScreenRect(::i32_rectangle * prectangle, ::i32 iMonitor);


::i32 GetScreenCount();

::i32 GetWorkspaceRect(::i32_rectangle * prectangle, ::i32 iMonitor);


::i32 GetWorkspaceCount();



//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)


//i32_bool destroy_window(oswindow w);


//oswindow get_capture();
//oswindow set_capture(oswindow window);
//i32_bool release_capture();
//oswindow set_focus(oswindow window);
//oswindow get_focus();
//oswindow get_active_window();
//oswindow set_active_window(oswindow window);
//i32_bool enable_window(oswindow hwnd, i32_bool bEnable);

//void get_main_screen_rectangle(::i32_rectangle * prectangle);

//
//i32_bool SetForegroundWindow(oswindow window);
//i32_bool BringWindowToTop(oswindow window);
//
//void ns_redraw_window(oswindow window);
//


//void copy(CGRect & rectangle, const ::i32_rectangle * prectangle);
//
//void copy(::i32_rectangle * prectangle, const CGRect & rectangleSource);
//
//void screen_coordinates_aware_copy(CGRect & rectangle, const ::i32_rectangle * prectangle);
//
//void screen_coordinates_aware_copy(::i32_rectangle * prectangle, const CGRect & rectangleSource);
//
//#ifdef MM
//void copy(NSRect & rectangle, const ::i32_rectangle * prectangle);
//
//void copy(::i32_rectangle * prectangle, const NSRect & rectangleSource);
//
//void screen_coordinates_aware_copy(NSRect & rectangle, const ::i32_rectangle * prectangle);
//
//void screen_coordinates_aware_copy(::i32_rectangle * prectangle, const NSRect & rectangleSource);
//
//#endif



