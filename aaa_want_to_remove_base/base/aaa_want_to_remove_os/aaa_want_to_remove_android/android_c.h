#pragma once


#include "axis/os/android/android.h"






struct hthread;






struct oswindow_data;






int_bool IsChild(oswindow oswindowParent, ::oswindow oswindowcandidateChildOrDescendant);
oswindow GetParent(::oswindow oswindow);
oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent);
int_bool ShowWindow(::oswindow oswindow, i32 nCmdShow);
LONG GetWindowLongA(::oswindow oswindow, i32 nIndex);
LONG SetWindowLongA(::oswindow oswindow, i32 nIndex, LONG l);
int_bool _001ClientToScreen(::oswindow oswindow, LPPOINT lppoint);
int_bool _001ScreenToClient(::oswindow oswindow, LPPOINT lppoint);
i32 IsIconic(::oswindow oswindow);
i32 IsWindowVisible(::oswindow oswindow);
void on_post_nc_destroy(::oswindow oswindow);
bool is_message_only_window(::oswindow oswindow);

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_AURA int_bool IsWindow(oswindow oswindow);






