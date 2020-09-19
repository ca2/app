#pragma once

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
#include "x11_message_box.h"

class x11_hook :
virtual public ::generic
{
public:



   virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);

   ::estatus hook();
   ::estatus unhook();


};


void defer_init_x11();
void x11_handle_just_hooks();
void x11_defer_handle_just_hooks();
void x11_message_box(const string & str, const string & strTitle, ::emessagebox emessagebox, ::callback callback);
bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);


//::estatus __x11_hook(x11_hook * phook);
//::estatus __x11_unhook(x11_hook * phook);
