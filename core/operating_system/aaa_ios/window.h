//
//  ios_window.h
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#include "oswindow_data.h"







int is_window(oswindow oswindow);
int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant);
oswindow get_parent(::oswindow oswindow);
oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent);
int ShowWindow(::oswindow oswindow, i32 nCmdShow);
i32 GetWindowLongA(::oswindow oswindow, i32 nIndex);
i32 SetWindowLongA(::oswindow oswindow, i32 nIndex, i32 l);
int client_to_screen(::oswindow oswindow, POINT32 * lppoint);
int screen_to_client(::oswindow oswindow, POINT32 * lppoint);
i32 IsIconic(::oswindow oswindow);
i32 IsWindowVisible(::oswindow oswindow);


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA





