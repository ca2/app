#pragma once


//!!!#include <X11/Xlib.h>
//!!!#include <xcb/xcb.h>


Display * x11_get_display();


Visual * get_32bit_visual(Display * pdisplay);


void x11_wait_timer_or_event(Display * pdisplay);
void __x11_hook_on_idle(Display * pdisplay);


CLASS_DECL_ACME ::pointer< ::mutex > user_mutex();


#include "xcb_hook.h"


void xcb_handle_just_hooks();
void xcb_defer_handle_just_hooks();
bool __xcb_hook_process_event(Display * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);



