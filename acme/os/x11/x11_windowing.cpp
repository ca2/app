#include "framework.h"
#include "_x11.h"


//http://rosettacode.org/wiki/Window_creation/X11

#include <stdio.h>

#include <string.h>

extern ::mutex * x11_mutex();

static Display * s_pdisplay = NULL;

Display * x11_get_display()
{

   if(s_pdisplay == NULL)
   {

      s_pdisplay =  XOpenDisplay(NULL);

   }

   return s_pdisplay;

}

bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);
#define SIMPLE_UI_MAX_BUTTON_COUNT 8
bool __x11_hook_list_is_empty();



GC x11_create_gc(Colormap colormap, Display* pdisplay, Window window, byte a, byte r, byte g, byte b)
{

   GC gc = XCreateGC(pdisplay, window, 0, 0);

   COLORREF cr = ARGB(a, r * a / 255, g * a / 255, b * a / 255);

   XSetForeground (pdisplay, gc, cr);

   return gc;

}


void x11_message_box(const string & str, const string & strTitle, ::emessagebox emessagebox, ::future future)
{

   defer_init_x11();

   auto pdisplay = __new(simple_ui_display(str, strTitle, emessagebox, future));

   pdisplay->show();

}



CLASS_DECL_ACME string message_box_result_to_string(int iResult);

CLASS_DECL_ACME void x11_message_box(const string & strMessage, const string & strTitle, ::emessagebox emessagebox, ::future future);

::estatus os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::future future)
{

   x11_message_box(pszMessage, pszTitle, emessagebox, future);

   return ::success;

}



::mutex * g_pmutexX11 = nullptr;


mutex * x11_mutex() {return g_pmutexX11;}


void x11_defer_handle_just_hooks()
{

   if(get_platform_level() <= e_platform_level_apex)
   {

      x11_handle_just_hooks();

   }

}


void x11_handle_just_hooks()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XEvent e = {};

#if !defined(RASPBIAN)

   XGenericEventCookie * cookie;

#endif

   while(true)
   {

      XLockDisplay(pdisplay);

      XNextEvent(pdisplay, &e);

      XUnlockDisplay(pdisplay);

      try
      {


         __x11_hook_process_event(pdisplay, e, nullptr);

         if(__x11_hook_list_is_empty())
         {

            break;

         }

      }
      catch(...)
      {

      }

   }

}


bool init_x11();


bool g_bInitX11 = false;


void defer_init_x11()
{

   if(!g_bInitX11)
   {

      g_bInitX11 = true;

      init_x11();

   }

}


i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);


bool init_x11()
{

   if(!XInitThreads())
   {

      return false;

   }

   XSetErrorHandler(_c_XErrorHandler);

   g_pmutexX11 = new ::mutex();

   return true;

}



