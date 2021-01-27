#pragma once

#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <X11/Xft/Xft.h>
#include <X11/extensions/Xrender.h>


Display * x11_get_display();

Visual * get_32bit_visual(Display * pdisplay);

void x11_kick_idle();

void x11_wait_timer_or_event(Display * pdisplay);
void __x11_hook_on_idle(Display * pdisplay);
//
//#include "acme/user/_const.h"
//#include "acme/user/_const_key.h"
//#include "acme/graphics/draw2d/_const.h"
//#include "acme/graphics/draw2d/color.h"


CLASS_DECL_ACME mutex * x11_mutex();

//typedef bool X11_PROCESS_EVENT(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie * cookie);
//using LPFN_X11_PROCESS_EVENT = X11_PROCESS_EVENT *;



#include "x11_exception.h"
#include "x11_keyboard.h"
#include "x11_hook.h"
#include "x11_button.h"
#include "x11_simple_ui_display.h"
#include "x11_message_box.h"


::e_status defer_initialize_x11();
void x11_handle_just_hooks();
void x11_defer_handle_just_hooks();
int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


//::e_status __x11_hook(x11_hook * phook);
//::e_status __x11_unhook(x11_hook * phook);
