// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


#include "aura/windowing/_.h"


//!!!#include <X11/Xlib.h>


#include "acme/parallelization/mq.h"


namespace windowing
{

   class display;
   class window;


   display *get_display();

   void kick_idle();

   void __wait_timer_or_event(display *pdisplay);

   void __hook_on_idle(display *pdisplay);

   CLASS_DECL_ACME mutex *mutex();

   ::e_status defer_initialize_x11();
   void handle_just_hooks();
   void defer_handle_just_hooks();
   int message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
   bool __hook_process_event(display * pdisplay, void * pevent, void * cookie);

   //CLASS_DECL_ACME i32 find_message_only_window(::user::interaction_impl * puserinteractionimpl);
   //CLASS_DECL_ACME i32 find_window(Display * pdisplay, Window window);
   //CLASS_DECL_ACME i32 find_window(Window window);
   //CLASS_DECL_ACME oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
   //CLASS_DECL_ACME oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = nullptr, int iDepth = -1, int iScreen = -1, Colormap colormap = None);
   //CLASS_DECL_ACME oswindow_data * oswindow_get(Window window);
   //CLASS_DECL_ACME oswindow_data * oswindow_defer_get(Display * pdisplay, Window window);
   //CLASS_DECL_ACME oswindow oswindow_defer_get(Window w);
   //CLASS_DECL_ACME bool oswindow_remove(Display * pdisplay, Window window);
   //CLASS_DECL_ACME bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);

} // namespace windowing


#include "display.h"
#include "window.h"


//#include "event.h"
#include "buffer.h"


#include "exception.h"
#include "keyboard.h"
//#include "hook.h"
//#include "button.h"
//#include "simple_ui_display.h"
//#include "message_box.h"


#include "windowing.h"



