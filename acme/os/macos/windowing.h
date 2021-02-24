//
//  macos_window.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
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

int GetMainScreenRect(RECTANGLE_I32 * prectangle);


int GetScreenRect(RECTANGLE_I32 * prectangle, int iMonitor);


int GetScreenCount();

int GetWorkspaceRect(RECTANGLE_I32 * prectangle, int iMonitor);


int GetWorkspaceCount();



//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)


int_bool destroy_window(oswindow w);


//oswindow get_capture();
//oswindow set_capture(oswindow window);
//int_bool release_capture();
//oswindow set_focus(oswindow window);
//oswindow get_focus();
//oswindow get_active_window();
//oswindow set_active_window(oswindow window);
//int_bool enable_window(oswindow hwnd, int_bool bEnable);

//void GetMainScreenRect(RECTANGLE_I32 * prectangle);


int_bool SetForegroundWindow(oswindow window);
int_bool BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);



//void copy(CGRect & rectangle, const RECTANGLE_I32 * prectangle);
//
//void copy(RECTANGLE_I32 * prectangle, const CGRect & rectSrc);
//
//void window_copy(CGRect & rectangle, const RECTANGLE_I32 * prectangle);
//
//void window_copy(RECTANGLE_I32 * prectangle, const CGRect & rectSrc);
//
//#ifdef MM
//void copy(NSRect & rectangle, const RECTANGLE_I32 * prectangle);
//
//void copy(RECTANGLE_I32 * prectangle, const NSRect & rectSrc);
//
//void window_copy(NSRect & rectangle, const RECTANGLE_I32 * prectangle);
//
//void window_copy(RECTANGLE_I32 * prectangle, const NSRect & rectSrc);
//
//#endif



