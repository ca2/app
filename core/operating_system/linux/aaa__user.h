#pragma once


// Ubuntu apt-get install libx11-dev
// // Ubuntu apt-get install libx11-dev
// // CentOS yum install libX11-devel
//!!!#include <X11/X.h>
//!!!#include <X11/Xlib.h>
//!!!#include <X11/Xutil.h>
//!!!#include <X11/Xatom.h>
//#include <X11/Xatom.h>
// // Ubuntu apt-get install libcairo2-dev

#include <glib.h> // gtk3-devel


enum e_net_wm_state
{

   net_wm_state_above,
   net_wm_state_below,
   net_wm_state_hidden,
   net_wm_state_maximized_horz,
   net_wm_state_maximized_vert,
   net_wm_state_fullscreen,
   net_wm_state_skip_taskbar,
   net_wm_state_count,

};


e_net_wm_state net_wm_state(const ::string & pszText);
const char * net_wm_state_text(e_net_wm_state estate);


CLASS_DECL_CORE int xinerama_get_monitor_count();
CLASS_DECL_CORE int xinerama_get_monitor_rect(index i, RECT32 * prect);

CLASS_DECL_CORE int xinerama_get_screen_size(int& width, int& height);


int best_xinerama_monitor(::user::interaction * pinteraction, RECT32 * prectRet);

int best_xinerama_monitor(::user::interaction * pinteraction, const ::rectangle & rectangle, RECT32 * lprectRet);



void mapped_net_state_raw(bool add, Display * d, Window w, int iScreen, Atom state1, Atom state2);
void unmapped_net_state_raw(Display * d, Window w, ...);

#include "cross_win_gdi.h"


//#include "xdisplay.h"

//#include "osdisplay.h"

//#include "oswindow.h"

//#include "window_cairo.h"

//#include "window_xlib.h"

//#include "windowing.h"

#ifdef __cplusplus

void set_xcolor(XColor & color, color32_t color32);

#endif




CLASS_DECL_CORE i32 oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_CORE i32 oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_CORE i32 oswindow_find(Window window);
CLASS_DECL_CORE oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_CORE oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = nullptr);
CLASS_DECL_CORE oswindow_data * oswindow_get(Window window);
CLASS_DECL_CORE oswindow oswindow_defer_get(Window w);
CLASS_DECL_CORE bool oswindow_erase(Display * pdisplay, Window window);
CLASS_DECL_CORE bool oswindow_erase_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);



//#ifndef HWND_MESSAGE
//#define HWND_MESSAGE ((::oswindow_data *) (iptr) 1)
//#










class CLASS_DECL_CORE device_context
{
public:


   ::Display *             m_pdisplay;
   ::Drawable              m_drawable;
   ::GC                    m_gc;
   ::Pixmap                m_pixmap;
   ::Window                m_window;
   int                     m_iDepth;
   int                     m_iScreen;

   point                   m_point;
   point                   m_pointOffset;

   XFontSet                m_fontset;

   device_context();


};



//extern GMainContext * gtk_main_context;




gboolean gdk_callback_run_runnable(gpointer pdata);




#include <stdio.h>

#include <string.h>

Display * x11_get_display();

