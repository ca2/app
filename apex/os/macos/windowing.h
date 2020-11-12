//
//  macos_window.h
//  apex
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

int GetMainScreenRect(RECT32 * prect);


int GetScreenRect(RECT32 * prect, int iMonitor);


int GetScreenCount();

int GetWkspaceRect(RECT32 * prect, int iMonitor);


int GetWkspaceCount();



//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)


int_bool destroy_window(oswindow w);


oswindow get_capture();
oswindow set_capture(oswindow window);
int_bool release_capture();
oswindow set_focus(oswindow window);
oswindow get_focus();
oswindow get_active_window();
oswindow set_active_window(oswindow window);
int_bool enable_window(oswindow hwnd, int_bool bEnable);

//void GetMainScreenRect(RECT32 * prect);


int_bool SetForegroundWindow(oswindow window);
int_bool BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);



//void copy(CGRect & rect, const RECT32 * prect);
//
//void copy(RECT32 * prect, const CGRect & rectSrc);
//
//void window_copy(CGRect & rect, const RECT32 * prect);
//
//void window_copy(RECT32 * prect, const CGRect & rectSrc);
//
//#ifdef MM
//void copy(NSRect & rect, const RECT32 * prect);
//
//void copy(RECT32 * prect, const NSRect & rectSrc);
//
//void window_copy(NSRect & rect, const RECT32 * prect);
//
//void window_copy(RECT32 * prect, const NSRect & rectSrc);
//
//#endif



