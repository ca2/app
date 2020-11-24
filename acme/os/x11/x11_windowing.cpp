#include "framework.h"
#include "_x11.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>


//http://rosettacode.org/wiki/Window_creation/X11

#include <stdio.h>

#include <string.h>


extern ::mutex * x11_mutex();


Display * g_pdisplayX11= nullptr;


int g_fdX11[2] = {};


Display * x11_get_display()
{

   if(g_pdisplayX11 == NULL)
   {

      g_pdisplayX11 =  XOpenDisplay(NULL);

   }

   return g_pdisplayX11;

}


bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);


#define SIMPLE_UI_MAX_BUTTON_COUNT 8


bool __x11_hook_list_is_empty();



GC x11_create_gc(Colormap colormap, Display* pdisplay, Window window, byte a, byte r, byte g, byte b)
{

   GC gc = XCreateGC(pdisplay, window, 0, 0);

   color32_t cr = ARGB(a, r * a / 255, g * a / 255, b * a / 255);

   XSetForeground (pdisplay, gc, cr);

   return gc;

}


int x11_message_box(const string & str, const string & strTitle, ::emessagebox emessagebox)
{

   defer_init_x11();

   auto pdisplay = __new(simple_ui_display(str, strTitle, emessagebox));

   return pdisplay->show();

}



CLASS_DECL_ACME string message_box_result_to_string(int iResult);

CLASS_DECL_ACME void x11_message_box(const string & strMessage, const string & strTitle, ::emessagebox emessagebox, const ::promise::process & process);

//::estatus os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::future future)
//{
//
//   x11_message_box(pszMessage, pszTitle, emessagebox, future);
//
//   return ::success;
//
//}


bool g_bX11Idle = false;


void x11_kick_idle()
{

   if(g_bX11Idle)
   {

      return;

   }

   g_bX11Idle = true;

   char ch = 1;

   ::write(g_fdX11[1], &ch, 1);

}


void x11_wait_timer_or_event(Display * pdisplay)
{

   struct timeval tv;

   // This returns the FD of the X11 display (or something like that)
   int x11_fd = ConnectionNumber(pdisplay);

   fd_set in_fds;

   // Create a File Description Set containing x11_fd
   FD_ZERO(&in_fds);
   FD_SET(x11_fd, &in_fds);
   FD_SET(g_fdX11[0], &in_fds);

   // Set our timer.  One second sounds good.
   tv.tv_usec = 0;
   tv.tv_sec = 1;

   // Wait for X Event or a Timer
   int num_ready_fds = select(max(x11_fd, g_fdX11[0]) + 1, &in_fds, NULL, NULL, &tv);

   if (num_ready_fds > 0)
   {

      //printf("Event Received!\n");

      g_bX11Idle = false;

      char buf[32];

      int iRead;

      while((iRead = read(g_fdX11[0], buf, sizeof(buf)))>0)
      {

         //printf("X11 fork count = %d\n", iRead);

      }

   }
   else if (num_ready_fds == 0)
   {

      // Handle timer here
      //printf("Timer Fired!\n");

   }
   else
   {

      //printf("An error occured!\n");

   }

}


::mutex * g_pmutexX11 = nullptr;


bool g_bAcmeInitWindowing = false;


void acme_defer_os_init_windowing()
{

   if(g_bAcmeInitWindowing)
   {

      return;

   }

   g_bAcmeInitWindowing = true;

   pipe(g_fdX11);

   int retval = fcntl(g_fdX11[0], F_SETFL, fcntl(g_fdX11[0], F_GETFL) | O_NONBLOCK);

   g_pmutexX11 = new ::mutex();

}


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

   Display * pdisplay = x11_get_display();

   XEvent e = {};

#if !defined(RASPBIAN)

   XGenericEventCookie * cookie;

#endif

   while(true)
   {

      try
      {

         sync_lock sl(x11_mutex());

         XLockDisplay(pdisplay);

         try
         {

            while(XPending(pdisplay))
            {

               XNextEvent(pdisplay, &e);

               __x11_hook_process_event(pdisplay, e, nullptr);

               if(__x11_hook_list_is_empty())
               {

                  break;

               }

            }

         }
         catch(...)
         {

         }

         __x11_hook_on_idle(pdisplay);

         XUnlockDisplay(pdisplay);

      }
      catch(...)
      {

      }

      x11_wait_timer_or_event(pdisplay);

      if(__x11_hook_list_is_empty())
      {

         break;

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





