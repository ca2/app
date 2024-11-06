//
//  ios_window.h
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//
#pragma once


#include "oswindow_data.h"







int is_window(oswindow oswindow);
int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant);
// oswindow get_parent(::oswindow oswindow);
// oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent);
int ShowWindow(::oswindow oswindow, int nCmdShow);
int GetWindowLongA(::oswindow oswindow, int nIndex);
int SetWindowLongA(::oswindow oswindow, int nIndex, int l);
int client_to_screen(::oswindow oswindow, ::point_i32 * lppoint);
int screen_to_client(::oswindow oswindow, ::point_i32 * lppoint);
int IsIconic(::oswindow oswindow);
int IsWindowVisible(::oswindow oswindow);


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA





