//
//  ios_window.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#include "oswindow_data.h"







int is_window(oswindow oswindow);
int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant);
oswindow GetParent(::oswindow oswindow);
oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent);
int ShowWindow(::oswindow oswindow, i32 nCmdShow);
i32 GetWindowLongA(::oswindow oswindow, i32 nIndex);
i32 SetWindowLongA(::oswindow oswindow, i32 nIndex, i32 l);
int _001ClientToScreen(::oswindow oswindow, POINT * lppoint);
int _001ScreenToClient(::oswindow oswindow, POINT * lppoint);
i32 IsIconic(::oswindow oswindow);
i32 IsWindowVisible(::oswindow oswindow);


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA





