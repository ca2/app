//
//  ios_window.h
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//
#pragma once


#include "oswindow_data.h"







::i32 is_window(::acme::windowing::window * pacmewindowingwindow);
::i32 IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant);
// oswindow get_parent(::acme::windowing::window * pacmewindowingwindow);
// oswindow SetParent(::acme::windowing::window * pacmewindowingwindow, ::oswindow oswindowNewParent);
::i32 show_window(::acme::windowing::window * pacmewindowingwindow, ::i32 nCmdShow);
//::i32 GetWindowLongA(::acme::windowing::window * pacmewindowingwindow, ::i32 nIndex);
//::i32 SetWindowLongA(::acme::windowing::window * pacmewindowingwindow, ::i32 nIndex, ::i32 l);
::i32 client_to_screen(::acme::windowing::window * pacmewindowingwindow, ::i32_point * lppoint);
::i32 screen_to_client(::acme::windowing::window * pacmewindowingwindow, ::i32_point * lppoint);
::i32 IsIconic(::acme::windowing::window * pacmewindowingwindow);
::i32 IsWindowVisible(::acme::windowing::window * pacmewindowingwindow);


//#define GetWindowLong GetWindowLongA
//#define SetWindowLong SetWindowLongA





