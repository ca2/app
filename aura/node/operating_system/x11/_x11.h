#pragma once


#include "aura/os/linux/_linux.h"


//typedef bool X11_PROCESS_EVENT(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie * cookie);
//using LPFN_X11_PROCESS_EVENT = X11_PROCESS_EVENT *;



#include "x11_exception.h"
#include "x11_keyboard.h"
//#include "x11_message_box.h"
//
//class x11_hook :
//virtual public ::matter
//{
//public:
//
//
//
//   virtual bool process_event(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie * cookie);
//
//   ::e_status hook();
//   ::e_status unhook();
//
//
//};
//
//
//
////::e_status __x11_hook(x11_hook * phook);
////::e_status __x11_unhook(x11_hook * phook);
