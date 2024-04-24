//
//  macos_window.h
//  apex
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

//NSWindow * __nswindow(oswindow oswindow);


//#include "oswindow_data.h"

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA

int get_main_screen_rectangle(::rectangle_i32 * prectangle);


int GetScreenRect(::rectangle_i32 * prectangle, int iMonitor);


int GetScreenCount();

int GetWorkspaceRect(::rectangle_i32 * prectangle, int iMonitor);


int GetWorkspaceCount();



//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)


//int_bool destroy_window(oswindow w);
//
//
////oswindow get_capture();
////oswindow set_capture(oswindow window);
////int_bool release_capture();
////oswindow set_focus(oswindow window);
////oswindow get_focus();
////oswindow get_active_window();
////oswindow set_active_window(oswindow window);
////int_bool enable_window(oswindow hwnd, int_bool bEnable);
//
////void get_main_screen_rectangle(::rectangle_i32 * prectangle);
//
//
//int_bool set_foreground_window(oswindow window);
//int_bool BringWindowToTop(oswindow window);
//
//void ns_redraw_window(oswindow window);
//
//
//
////void copy(CGRect & rectangle, const ::rectangle_i32 * prectangle);
////
////void copy(::rectangle_i32 * prectangle, const CGRect & rectangleSource);
////
////void screen_coordinates_aware_copy(CGRect & rectangle, const ::rectangle_i32 * prectangle);
////
////void screen_coordinates_aware_copy(::rectangle_i32 * prectangle, const CGRect & rectangleSource);
////
////#ifdef MM
////void copy(NSRect & rectangle, const ::rectangle_i32 * prectangle);
////
////void copy(::rectangle_i32 * prectangle, const NSRect & rectangleSource);
////
////void screen_coordinates_aware_copy(NSRect & rectangle, const ::rectangle_i32 * prectangle);
////
////void screen_coordinates_aware_copy(::rectangle_i32 * prectangle, const NSRect & rectangleSource);
////
////#endif
//
//

