//
//  macos_window.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
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

int get_main_screen_rectangle(RECT32 * prect);


int GetScreenRect(RECT32 * prect, int iMonitor);


int GetScreenCount();

int GetWorkspaceRect(RECT32 * prect, int iMonitor);


int GetWorkspaceCount();



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

//void get_main_screen_rectangle(RECT32 * prect);


int_bool set_foreground_window(oswindow window);
int_bool BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);



//void copy(CGRect & rectangle, const RECT32 * prect);
//
//void copy(RECT32 * prect, const CGRect & rectangleSource);
//
//void screen_coordinates_aware_copy(CGRect & rectangle, const RECT32 * prect);
//
//void screen_coordinates_aware_copy(RECT32 * prect, const CGRect & rectangleSource);
//
//#ifdef MM
//void copy(NSRect & rectangle, const RECT32 * prect);
//
//void copy(RECT32 * prect, const NSRect & rectangleSource);
//
//void screen_coordinates_aware_copy(NSRect & rectangle, const RECT32 * prect);
//
//void screen_coordinates_aware_copy(RECT32 * prect, const NSRect & rectangleSource);
//
//#endif



