//
//  macos_window.h
//  aqua
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

NSWindow * __nswindow(oswindow oswindow);


//#include "oswindow_data.h"

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA

int GetMainScreenRect(RECT * prect);


int GetScreenRect(RECT * prect, int iMonitor);


int GetScreenCount();

int GetWkspaceRect(RECT * prect, int iMonitor);


int GetWkspaceCount();



//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)


WINBOOL destroy_window(oswindow w);


oswindow get_capture();
oswindow set_capture(oswindow window);
WINBOOL release_capture();
oswindow set_focus(oswindow window);
oswindow get_focus();
oswindow get_active_window();
oswindow set_active_window(oswindow window);
WINBOOL enable_window(oswindow hwnd, WINBOOL bEnable);

//void GetMainScreenRect(RECT * prect);


WINBOOL SetForegroundWindow(oswindow window);
WINBOOL BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);



//void copy(CGRect & rect, const RECT * prect);
//
//void copy(RECT * prect, const CGRect & rectSrc);
//
//void window_copy(CGRect & rect, const RECT * prect);
//
//void window_copy(RECT * prect, const CGRect & rectSrc);
//
//#ifdef MM
//void copy(NSRect & rect, const RECT * prect);
//
//void copy(RECT * prect, const NSRect & rectSrc);
//
//void window_copy(NSRect & rect, const RECT * prect);
//
//void window_copy(RECT * prect, const NSRect & rectSrc);
//
//#endif



