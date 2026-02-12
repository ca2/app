//
//  ios_window.h
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//
#pragma once


#include "oswindow_data.h"







int is_window(::acme::windowing::window * pacmewindowingwindow);
int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant);
// oswindow get_parent(::::acme::windowing::window * pacmewindowingwindow);
// oswindow SetParent(::::acme::windowing::window * pacmewindowingwindow, ::oswindow oswindowNewParent);
int show_window(::::acme::windowing::window * pacmewindowingwindow, int nCmdShow);
//int GetWindowLongA(::::acme::windowing::window * pacmewindowingwindow, int nIndex);
//int SetWindowLongA(::::acme::windowing::window * pacmewindowingwindow, int nIndex, int l);
int client_to_screen(::::acme::windowing::window * pacmewindowingwindow, ::int_point * lppoint);
int screen_to_client(::::acme::windowing::window * pacmewindowingwindow, ::int_point * lppoint);
int IsIconic(::::acme::windowing::window * pacmewindowingwindow);
int IsWindowVisible(::::acme::windowing::window * pacmewindowingwindow);


//#define GetWindowLong GetWindowLongA
//#define SetWindowLong SetWindowLongA





