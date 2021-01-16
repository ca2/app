//
//  ios_windowing.hpp
//  ios_apex
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


#ifndef __OBJC__

struct UIWindow;

#endif

UIWindow * __uiwindow(oswindow oswindow);


int GetMainScreenRect(LPRECT32 lprect);

int GetScreenRect(LPRECT32 lprect, int iMonitor);

int GetScreenCount();

int GetWkspaceRect(LPRECT32 lprect, int iMonitor);

int GetWkspaceCount();


//
//  ios_window.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//


//oswindow get_capture();
//oswindow set_capture(oswindow window);
//int_bool release_capture();
//oswindow set_focus(oswindow window);
//oswindow get_focus();
//oswindow get_active_window();
//oswindow set_active_window(oswindow window);


//void GetMainScreenRect(LPRECT32 lprect);

int_bool SetForegroundWindow(oswindow window);
int_bool BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);






#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA


void deactivate_window(oswindow window);


//oswindow get_window(oswindow window, int iParentHood);



