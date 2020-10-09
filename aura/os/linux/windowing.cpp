#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "acme/os/x11/_x11.h"
#include "_linux.h"
#include "acme/const/id.h"
#include "acme/const/message.h"
#include "third/sn/sn.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>
#include <X11/extensions/xf86vmode.h>
#define pointer x11_pointer
#include <X11/extensions/Xrender.h>
#undef pointer
#include <unistd.h>
//#include <X11/XKBlib.h>
#include <X11/cursorfont.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/XKBlib.h>
#define new ACME_NEW
#include "aura/os/x11/_x11.h"
#include "acme/multithreading/mq.h"


::point g_pointX11Cursor;
//::tick g_tickLastMouseMove;
//::tick g_tickLastX11WindowConfigurationCheck;


//void _x11_defer_check_configuration(oswindow oswindow);
//void x11_defer_check_configuration(oswindow oswindow);


mq * get_mq(ITHREAD idthread, bool bCreate);


void oswindow_set_active_window(oswindow oswindow);


CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point & pointCursor);

bool is_return_key(XIRawEvent *event)
{

   int i;
   double *val, *raw_val;

   switch(event->evtype)
   {
   case XI_RawKeyPress:
   case XI_RawKeyRelease:
      {

         val = event->valuators.values;

         raw_val = event->raw_values;

         if(event->detail == 36)
         {

            return true;

         }

         printf("is_return_key    detail: %d\n", event->detail);

         for (i = 0; i < event->valuators.mask_len * 8; i++)
         {

            if (XIMaskIsSet(event->valuators.mask, i))
            {

               printf("is_return_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);

            }

         }

         printf("\n");

      }

      break;

   }

   return false;

}


bool is_space_key(XIRawEvent *event)
{

   int i;
   double *val, *raw_val;

   switch(event->evtype)
   {
   case XI_RawKeyPress:
   case XI_RawKeyRelease:
      {

         val = event->valuators.values;

         raw_val = event->raw_values;

         if(event->detail == 65)
         {

            return true;

         }

         printf("is_space_key    detail: %d\n", event->detail);

         for (i = 0; i < event->valuators.mask_len * 8; i++)
         {

            if (XIMaskIsSet(event->valuators.mask, i))
            {

               printf("is_space_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);

            }

         }

         printf("\n");

      }

      break;

   }

   return false;

}


// Tutor Exilius Q(t)List streaming contribution
::mutex * g_pmutexX11Runnable = nullptr;
list < __pointer(::element) > * g_prunnableptrlX11 = nullptr;
::mutex * g_pmutexX11Sync = nullptr;
manual_reset_event * g_peventX11Sync = nullptr;
__pointer(::element) g_prunnableX11Sync;
Display * g_pdisplayX11= nullptr;
int g_fdX11[2] = {};


WINBOOL _x11_get_cursor_pos(Display * d, LPPOINT ppointCursor);




//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

extern SnLauncheeContext* g_psncontext;
Display * x11_get_display();
void wm_toolwindow(oswindow w, bool bToolWindow);
void wm_state_hidden(oswindow w, bool bSet);
void wm_state_hidden_raw(oswindow w, bool bSet);
CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);


WINBOOL x11_get_cursor_pos(LPPOINT ppointCursor);

#if !defined(RASPBIAN)

int xi_opcode = -1;
__pointer(object_array) g_pobjectaExtendedEventListener;
void x11_register_extended_event_listener(::element * pdata, bool bMouse, bool bKeyboard)
{

   if(!g_pobjectaExtendedEventListener)
   {

      __construct_new(g_pobjectaExtendedEventListener);

   }

   g_pobjectaExtendedEventListener->add(pdata);

   x11_fork([bMouse, bKeyboard]()
   {

      sync_lock sl(x11_mutex());

      xdisplay d(x11_get_display());

      int event, error;

      if (!XQueryExtension(d, "XInputExtension", &xi_opcode, &event, &error))
      {

         printf("X Input extension not available.\n");

         return;

      }

      XIEventMask mask[2];
      XIEventMask *m;
      Window win;
      int deviceid = -1;
      int use_root = 1;
      int rc;

      if (!use_root)
      return ;
         win = DefaultRootWindow(d.display());
      //else
         //win = create_win(display);

                   /* Select for motion events */
                   m = &mask[0];
                   m->deviceid = (deviceid == -1) ? XIAllDevices : deviceid;
                   m->mask_len = XIMaskLen(XI_LASTEVENT);
                   m->mask = (unsigned char *)calloc(m->mask_len, sizeof(char));
                   if(bMouse)
                   {
                   XISetMask(m->mask, XI_ButtonPress);
                   XISetMask(m->mask, XI_ButtonRelease);
                   }
                   if(bKeyboard)
                   {
                   XISetMask(m->mask, XI_KeyPress);
                   XISetMask(m->mask, XI_KeyRelease);
                   }
                   /*
                   XISetMask(m->mask, XI_Motion);
                   XISetMask(m->mask, XI_DeviceChanged);
                   XISetMask(m->mask, XI_Enter);
                   XISetMask(m->mask, XI_Leave);
                   XISetMask(m->mask, XI_FocusIn);
                   XISetMask(m->mask, XI_FocusOut);
               #if HAVE_XI22
                   XISetMask(m->mask, XI_TouchBegin);
                   XISetMask(m->mask, XI_TouchUpdate);
                   XISetMask(m->mask, XI_TouchEnd);
               #endif
                  */
                   if (m->deviceid == XIAllDevices)
                       XISetMask(m->mask, XI_HierarchyChanged);
                   XISetMask(m->mask, XI_PropertyEvent);

                   m = &mask[1];
                   m->deviceid = (deviceid == -1) ? XIAllMasterDevices : deviceid;
                   m->mask_len = XIMaskLen(XI_LASTEVENT);
                   m->mask = (unsigned char*)calloc(m->mask_len, sizeof(char));
                   if(bMouse)
                   {
                   XISetMask(m->mask, XI_RawButtonPress);
                   XISetMask(m->mask, XI_RawButtonRelease);
                   }

                   if(bKeyboard)
                   {
                   XISetMask(m->mask, XI_RawKeyPress);
                   XISetMask(m->mask, XI_RawKeyRelease);

                   }
                   /*
                   XISetMask(m->mask, XI_RawMotion);
               #if HAVE_XI22
                   XISetMask(m->mask, XI_RawTouchBegin);
                   XISetMask(m->mask, XI_RawTouchUpdate);
                   XISetMask(m->mask, XI_RawTouchEnd);
               #endif
               */

         XISelectEvents(d.display(), win, &mask[0], use_root ? 2 : 1);
    //if (!use_root) {
      //  XISelectEvents(display, DefaultRootWindow(display), &mask[1], 1);
        //XMapWindow(display, win);
    //
    XSync(d.display(), False);

    free(mask[0].mask);
    free(mask[1].mask);


   });

}

#endif


Window g_windowFocus = 0;

#ifdef LINUX
i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
#endif





struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};


#define MWM_HINTS_DECORATIONS   (1L << 1)


/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)




oswindow oswindow_defer_get(Window window)
{

   return oswindow_get(window);

}



bool oswindow_remove(Display * display, Window window)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   iptr iFind = oswindow_find(display, window);

   if(iFind < 0)
   {

      return false;

   }

   delete ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   iptr iFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);

   if(iFind < 0)
   {

      return false;

   }

   delete ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


Atom get_window_long_atom(i32 nIndex);

// Change _NET_WM_STATE if Window is Mapped
void mapped_net_state_raw(bool add, Display * d, Window w, int iScreen, Atom state1, Atom state2)
{

   sync_lock sl(x11_mutex());

   XClientMessageEvent xclient;

#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */

   xxf_zero(xclient);
   xclient.type = ClientMessage;
   xclient.window = w;
   xclient.message_type = XInternAtom(d, "_NET_WM_STATE", False);
   xclient.format = 32;
   xclient.data.l[0] = add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
   xclient.data.l[1] = state1;
   xclient.data.l[2] = state2;
   xclient.data.l[3] = 1; /* source indication */
   xclient.data.l[4] = 0;

   XSendEvent (d, RootWindow(d, iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient);

}


void unmapped_net_state_raw(Display * d, Window w, ...)
{

   sync_lock sl(x11_mutex());

   XEvent xevent;

   unsigned int i;

   va_list argp;

   va_start(argp, w);

   xxf_zero(xevent);

   array < Atom > atoms;

   while(true)
   {

      Atom atom = va_arg(argp, int);

      if(atom == 0)
      {

         break;

      }

      atoms.add(atom);

   }

   if(atoms.has_elements())
   {

      XChangeProperty(d, w, XInternAtom(d, "_NET_WM_STATE", False),
                      XA_ATOM, 32, PropModeReplace,
                      (guchar*) atoms.get_data(), atoms.get_size());
   }
   else
   {

      XDeleteProperty(d, w, XInternAtom(d, "_NET_WM_STATE", False));

   }

   va_end(argp);

}


WINBOOL x11_get_window_rect(Display * d, Window window, RECT * prect)

{

   XWindowAttributes attrs;

   if(!XGetWindowAttributes(d, window, &attrs))
   {

      windowing_output_debug_string("\n::x11_get_window_rect 1.1 (xgetwindowattributes failed)");

      return FALSE;

   }

   int x = 0;

   int y = 0;

   int screen = XDefaultScreen((Display *) d);

   Window windowRoot = RootWindow((Display *) d, screen);

   Window child;

   XTranslateCoordinates( d, window, windowRoot, 0, 0, &x, &y, &child );

   prect->left      = x + attrs.x;

   prect->top       = y + attrs.y;

   prect->right     = x + attrs.x    + attrs.width;

   prect->bottom    = y + attrs.y    + attrs.height;



   windowing_output_debug_string("\n::x11_get_window_rect 2");

   return TRUE;

}


static oswindow g_oswindowCapture;


oswindow get_capture()
{

   return g_oswindowCapture;

}


oswindow set_capture(oswindow window)
{

   sync_lock sl(x11_mutex());

   oswindow windowOld(g_oswindowCapture);

   if(window->display() == nullptr)
   {

      return nullptr;

   }

   if(window->window() == None)
   {

      return nullptr;

   }

   windowing_output_debug_string("\noswindow_data::SetCapture 1");

   xdisplay d(window->display());

   if(XGrabPointer(d, window->window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime) == GrabSuccess)
   {

      g_oswindowCapture = window;

      windowing_output_debug_string("\noswindow_data::SetCapture 2");

      return windowOld;

   }

   windowing_output_debug_string("\noswindow_data::SetCapture 2.1");

   return nullptr;

}


WINBOOL release_capture()
{

   sync_lock sl(x11_mutex());

//    if(g_oswindowCapture == nullptr)
//    {

//       return FALSE;

//    }

   windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

   xdisplay d(x11_get_display());

   WINBOOL bRet = XUngrabPointer(d, CurrentTime) != FALSE;

   //if(bRet)
   {

      g_oswindowCapture = nullptr;

   }

   windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

   return bRet;

}


oswindow set_focus(oswindow window)
{

   sync_lock sl(x11_mutex());

   if(window == nullptr)
   {

      return nullptr;

   }

   windowing_output_debug_string("\noswindow_data::SetFocus 1");

   xdisplay d(window->display());

   if(!is_window(window))
   {

      windowing_output_debug_string("\noswindow_data::SetFocus 1.1");

      return nullptr;

   }

   oswindow windowOld = ::get_focus();

   if(!IsWindowVisibleRaw(window))
   {

      windowing_output_debug_string("\noswindow_data::SetFocus 1.2");

      return nullptr;

   }

   if(!XSetInputFocus(d, window->window(), RevertToNone, CurrentTime))
   {

      windowing_output_debug_string("\noswindow_data::SetFocus 1.3");

      return nullptr;

   }

   windowing_output_debug_string("\noswindow_data::SetFocus 2");

   return windowOld;

}


void x11_check_status(int status, unsigned long window)
{
   if (status == BadWindow)
   {
      printf("window id # 0x%lx does not exists!", window);
      //   exit(1);
   }

   if (status != Success)
   {
      printf("XGetWindowProperty failed!");
      // exit(2);
   }
}
#define MAXSTR 1000
unsigned char* x11_get_string_property(Display * display, Window window, char* property_name)
{

   unsigned char * prop;
   Atom actual_type, filter_atom;
   int actual_format, status;
   unsigned long nitems, bytes_after;

   filter_atom = XInternAtom(display, property_name, True);
   status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
                               &actual_type, &actual_format, &nitems, &bytes_after, &prop);
   x11_check_status(status, window);
   return prop;

}

unsigned long x11_get_long_property(Display * d, Window w, char* property_name)
{
   unsigned char * prop =x11_get_string_property(d, w, property_name);
   unsigned long long_property = prop[0] + (prop[1]<<8) + (prop[2]<<16) + (prop[3]<<24);
   return long_property;
}

string x11_get_name(Display * display, Window w)
{

   string str;

   char* name = NULL;
   int status = XFetchName(display, w, &name);
   if (status >= Success)
   {
      str =name;
   }
   XFree(name);
   return str;

}

#ifdef XDISPLAY_LOCK_LOG

extern bool b_prevent_xdisplay_lock_log;

#endif


oswindow g_oswindowActive;


oswindow get_active_window()
{

   return g_oswindowActive;

}


void oswindow_set_active_window(oswindow oswindow)
{

   if(g_oswindowActive)
   {

      try
      {

         if(g_oswindowActive->m_pimpl)
         {

            if(g_oswindowActive->m_pimpl->m_puserinteraction)
            {

               g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag -= ::window_flag_active;

            }

         }

      }
      catch(...)
      {

      }

   }

   g_oswindowActive = oswindow;

   if(g_oswindowActive)
   {

      try
      {

         if(g_oswindowActive->m_pimpl)
         {

            if(g_oswindowActive->m_pimpl->m_puserinteraction)
            {

               g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag += ::window_flag_active;

            }

         }

      }
      catch(...)
      {

      }

   }

}


oswindow _x11_get_active_window(Display * pdisplay)
{

   int screen = XDefaultScreen(pdisplay);

   Window windowRoot = RootWindow(pdisplay, screen);

   Window window = x11_get_long_property(pdisplay, windowRoot, (char*) "_NET_ACTIVE_WINDOW");

   oswindow oswindow = oswindow_defer_get(window);

   windowing_output_debug_string("\n::GetActiveWindow 2");

   return oswindow;

}


oswindow _x11_get_active_window()
{

   sync_lock sl(x11_mutex());

   oswindow pwindow = nullptr;

   windowing_output_debug_string("\n::GetFocus 1");

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

   xdisplay d(x11_get_display());

   windowing_output_debug_string("\n::GetFocus 1.01");

   if(d.is_null())
   {

      windowing_output_debug_string("\n::GetFocus 1.1");

      return pwindow;

   }

   return _x11_get_active_window(d);
   //int screen = XDefaultScreen((Display *) d);

   //Window windowRoot = RootWindow((Display *) d, screen);

   //Window window = x11_get_long_property(d, windowRoot, (char*) "_NET_ACTIVE_WINDOW");

   ///pwindow = oswindow_defer_get(window);

  // windowing_output_debug_string("\n::GetActiveWindow 2");

//   return pwindow;

}


Window * x11_window_list(Display *disp, unsigned long * len)
{

   Atom prop = XInternAtom(disp,"_NET_CLIENT_LIST_STACKING",False);

   if(prop == 0)
   {

      prop = XInternAtom(disp,"_NET_CLIENT_LIST",False);

   }

   if(prop == 0)
   {

      return nullptr;

   }

   Atom type;
   int form;
   unsigned long remain;
   unsigned char *list;

   errno = 0;
   if (XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1024,False,XA_WINDOW,
                          &type,&form,len,&remain,&list) != Success)
   {
      output_debug_string("winlist() -- GetWinProp");
      return nullptr;
   }

   return (Window*)list;
}



bool x11_window_list(Display *disp, array < Window > & windowa)
{

   unsigned long len = 0;

   Window * list = (Window*)x11_window_list(disp,&len);


   if(list == nullptr)
   {

      return false;

   }

   for (int i=0; i<(int)len; i++)
   {

      windowa.add(list[i]);

   }

   XFree(list);

   return true;

}

bool point_is_window_origin(POINT pointHitTest, oswindow oswindowExclude, int iMargin)
{

   bool bIsOrigin = false;

   x11_sync([pointHitTest, oswindowExclude, iMargin, &bIsOrigin]()
   {

      sync_lock sl(x11_mutex());

      windowing_output_debug_string("\n::GetFocus 1");

#ifdef XDISPLAY_LOCK_LOG

      b_prevent_xdisplay_lock_log = false;

#endif

      xdisplay display(x11_get_display());

      windowing_output_debug_string("\n::GetFocus 1.01");

      if(display.is_null())
      {

         windowing_output_debug_string("\n::GetFocus 1.1");

         return;

      }

      comparable_array < Window > windowa;

      if(!x11_window_list(display, windowa))
      {

         bIsOrigin = true;

         return;

      }

      ::rect rectTest;

      for(index i = 0; i < windowa.get_size(); i++)
      {

         string strItem = x11_get_name(display, windowa[i]);

         ::rect rectHigher;

         if(::is_set(oswindowExclude) && windowa[i] == oswindowExclude->window())
         {

            continue;

         }

         if(x11_get_window_rect(display, windowa[i], rectHigher))
         {

            ::rect rectHitTest;

            rectHitTest.set(rectHigher.origin(), ::size());

            rectHitTest.inflate(iMargin+1);

            if(rectHitTest.contains(pointHitTest))
            {

               bIsOrigin = true;

               return;

            }

         }

      }

   });

   return bIsOrigin;

}


// int_bool is_window_occluded(oswindow oswindow)
// {

//    sync_lock sl(x11_mutex());

//    windowing_output_debug_string("\n::GetFocus 1");

// #ifdef XDISPLAY_LOCK_LOG

//    b_prevent_xdisplay_lock_log = false;

// #endif

//    xdisplay display(oswindow->display());

//    windowing_output_debug_string("\n::GetFocus 1.01");

//    if(display.is_null())
//    {

//       windowing_output_debug_string("\n::GetFocus 1.1");

//       return false;

//    }

//    comparable_array < Window > windowa;

//    if(!x11_window_list(display, windowa))
//    {

//       return true;

//    }

//    if(windowa.last() == oswindow->window())
//    {

//       return false;

//    }

//    index iFind = windowa.find_last(oswindow->window());

//    if(iFind < 0)
//    {

//       return true;

//    }

//    ::rect rect;

//    x11_get_window_rect(display, oswindow->window(), rect);

//    //r = oswindow->m_pimpl->m_puserinteraction->get_window_rect();

//    string strTopic = x11_get_name(display, oswindow->window());

//    ::rect rectTest;

//    for(iFind++; iFind < windowa.get_size(); iFind++)
//    {

//       string strItem = x11_get_name(display, windowa[iFind]);

//       ::rect rectHigher;

//       if(x11_get_window_rect(display, windowa[iFind], rectHigher))
//       {

//          if(rectTest.intersect(rectHigher, rect))
//          {

//             return true;

//          }

//       }

//    }

//    return false;

// }



void upper_window_rects(oswindow oswindow, rect_array & ra)
{

   sync_lock sl(x11_mutex());

   ra.remove_all();

   windowing_output_debug_string("\n::GetFocus 1");

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

   xdisplay display(oswindow->display());

   windowing_output_debug_string("\n::GetFocus 1.01");

   if(display.is_null())
   {

      windowing_output_debug_string("\n::GetFocus 1.1");

      return;

   }

   comparable_array < Window > windowa;

   if(!x11_window_list(display, windowa))
   {

      return;

   }

   if(windowa.last() == oswindow->window())
   {

      return;

   }

   index iFind = windowa.find_last(oswindow->window());

   if(iFind < 0)
   {

      return;

   }

   ::rect rect;

   x11_get_window_rect(display, oswindow->window(), rect);

   //r = oswindow->m_pimpl->m_puserinteraction->get_window_rect();

   //string strTopic = x11_get_name(display, oswindow->window());

   ::rect rectTest;

   for(iFind++; iFind < windowa.get_size(); iFind++)
   {

      //string strItem = x11_get_name(display, windowa[iFind]);

      ::rect rectHigher;

      if(x11_get_window_rect(display, windowa[iFind], rectHigher))
      {

         ra.add(rectHigher);

      }

   }

}


oswindow get_focus()
{

   sync_lock sl(x11_mutex());

   oswindow pwindow = nullptr;

   windowing_output_debug_string("\n::GetFocus 1");

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

   xdisplay d(x11_get_display());

   windowing_output_debug_string("\n::GetFocus 1.01");

   if(d.is_null())
   {

      windowing_output_debug_string("\n::GetFocus 1.1");

      return nullptr;

   }

   Window window = None;

   int revert_to = 0;

   bool bOk = XGetInputFocus(d, &window, &revert_to) != 0;

   if(!bOk)
   {

      windowing_output_debug_string("\n::GetFocus 1.2");

      return nullptr;

   }

   if(window == None || window == PointerRoot)
   {

      windowing_output_debug_string("\n::GetFocus 1.3");

      return nullptr;

   }

   pwindow = oswindow_defer_get(window);

   windowing_output_debug_string("\n::GetFocus 2");

   return pwindow;

}


oswindow set_active_window(oswindow window)
{

   sync_lock sl(x11_mutex());

   {

      windowing_output_debug_string("\n::set_active_window 1");

      xdisplay d(window->display());

      XEvent xev;

      xxf_zero(xev);

      Window windowRoot = window->root_window_raw();

      Atom atomActiveWindow = d.intern_atom("_NET_ACTIVE_WINDOW", False);

      xev.xclient.type = ClientMessage;
      xev.xclient.send_event = True;
      xev.xclient.display = d;
      xev.xclient.window = window->window();
      xev.xclient.message_type = atomActiveWindow;
      xev.xclient.format = 32;
      xev.xclient.data.l[0] = 1;
      xev.xclient.data.l[1] = 0;
      xev.xclient.data.l[2] = 0;
      xev.xclient.data.l[3] = 0;
      xev.xclient.data.l[4] = 0;

      XSendEvent (d, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

      windowing_output_debug_string("\n::set_active_window 2");

   }

   return ::set_focus(window);

}


oswindow oswindow_get_next_found(Display * pdisplay, long *array, int iStart, int numItems)
{

   for(index i = iStart; i < numItems; i++)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return nullptr;

}


oswindow oswindow_get_previous_found(Display * pdisplay, long *array, int iStart)
{

   for(index i = iStart; i >= 0; i--)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return nullptr;

}


oswindow oswindow_get_next_found(Window *array, int iStart, int numItems)
{

   for(index i = iStart; i < numItems; i++)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return nullptr;

}


oswindow oswindow_get_previous_found(Window *array, int iStart)
{

   for(index i = iStart; i >= 0; i--)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return nullptr;

}


oswindow GetParent(oswindow oswindow);


oswindow get_window(oswindow windowParam, int iParentHood)
{

   sync_lock sl(x11_mutex());

   oswindow window = windowParam;

   if(window == nullptr)
   {

      return nullptr;

   }

   windowing_output_debug_string("\n::get_window 1");

   xdisplay d(window->display());

   Window w = window->window();

   if(iParentHood == GW_HWNDFIRST || iParentHood == GW_HWNDLAST || iParentHood == GW_HWNDNEXT || iParentHood == GW_HWNDPREV)
   {

      window = ::GetParent(window);

      if(window == nullptr)
      {

         window = windowParam;

         w = window->get_parent_handle();

         Atom a = XInternAtom(windowParam->display(), "_NET_CLIENT_LIST_STACKING", False);

         Atom actualType;

         int format;

         unsigned long numItems, bytesAfter;

         unsigned char *data =0;

         int status = XGetWindowProperty(
                      windowParam->display(),
                      RootWindow(windowParam->display(), windowParam->m_iScreen),
                      a,
                      0L,
                      1024,
                      false,
                      AnyPropertyType,
                      &actualType,
                      &format,
                      &numItems,
                      &bytesAfter,
                      &data);

         if (status >= Success && numItems)
         {

            long * array = (long*) data;

            switch(iParentHood)
            {
            case GW_CHILD:
            case GW_HWNDFIRST:
            {

               if(data == nullptr)
               {

                  windowing_output_debug_string("\n::get_window 2");

                  return nullptr;

               }

               window = oswindow_get_next_found(windowParam->display(), array, 0, numItems);

            }
            break;
            case GW_HWNDLAST:
            {

               if(data == nullptr)
               {

                  windowing_output_debug_string("\n::get_window 3");

                  return nullptr;

               }

               window = oswindow_get_previous_found(windowParam->display(), array, numItems - 1);

            }
            break;
            case GW_HWNDNEXT:
            case GW_HWNDPREV:
            {

               if(data == nullptr) // ????
               {

                  windowing_output_debug_string("\n::get_window 4");

                  return nullptr;

               }

               int iFound = -1;

               for(int i = 0; i < numItems; i++)
               {

                  if(array[i] == windowParam->window())
                  {

                     iFound = i;

                     break;

                  }

               }

               if(iFound < 0)
               {

                  XFree(data);

                  windowing_output_debug_string("\n::get_window 5");

                  return nullptr;

               }

               if(iParentHood == GW_HWNDNEXT)
               {

                  if(iFound + 1 >= numItems)
                  {

                     XFree(data);

                     windowing_output_debug_string("\n::get_window 6");

                     return nullptr;

                  }

                  window = ::oswindow_get_next_found(windowParam->display(), array, iFound + 1, numItems);

               }
               else
               {

                  if(iFound - 1 < 0)
                  {

                     XFree(data);

                     windowing_output_debug_string("\n::get_window 7");

                     return nullptr;

                  }

                  window = ::oswindow_get_previous_found(windowParam->display(), array, iFound - 1);

               }

            }

            }

            XFree(data);

            windowing_output_debug_string("\n::get_window 8");

            return window;

         }
      }

   }

   Window root = 0;
   Window parent = 0;
   Window * pchildren = nullptr;
   u32 ncount = 0;


   XQueryTree(window->display(), w, &root, &parent, &pchildren, &ncount);

   switch(iParentHood)
   {
   case GW_CHILD:
   case GW_HWNDFIRST:
   {

      if(pchildren == nullptr)
      {

         windowing_output_debug_string("\n::get_window 9");

         return nullptr;

      }

      window = ::oswindow_get_next_found(pchildren, 0, ncount);

   }
   break;
   case GW_HWNDLAST:
   {

      if(pchildren == nullptr)
      {

         windowing_output_debug_string("\n::get_window 10");

         return nullptr;

      }

      window = ::oswindow_get_previous_found(pchildren, ncount - 1);

   }
   break;
   case GW_HWNDNEXT:
   case GW_HWNDPREV:
   {

      if(pchildren == nullptr) // ????
      {

         windowing_output_debug_string("\n::get_window 11");

         return nullptr;

      }

      int iFound = -1;

      for(int i = 0; i < ncount; i++)
      {
         if(pchildren[i] == windowParam->window())
         {
            iFound = i;
            break;
         }
      }

      if(iFound < 0)
      {

         windowing_output_debug_string("\n::get_window 12");

         return nullptr;

      }

      if(iParentHood == GW_HWNDNEXT)
      {

         if(iFound + 1 >= ncount)
         {

            windowing_output_debug_string("\n::get_window 13");

            return nullptr;

         }

         window = ::oswindow_get_next_found(pchildren, iFound + 1, ncount);

      }
      else
      {

         if(iFound - 1 < 0)
         {

            windowing_output_debug_string("\n::get_window 14");

            return nullptr;

         }

         window = ::oswindow_get_previous_found(pchildren, iFound - 1);

      }

   }

   }

   if(pchildren != nullptr)
      XFree(pchildren);

   windowing_output_debug_string("\n::get_window 15");

   return window;

}


WINBOOL destroy_window(oswindow window)
{

   bool bOk = false;


   if(!is_window(window))
   {

      bOk = false;

      return FALSE;

   }

   if(::is_set(window->m_pimpl))
   {

      __pointer(::user::interaction) pinteraction = window->m_pimpl->m_puserinteraction;

      if(pinteraction.is_set())
      {

         pinteraction->send_message(WM_DESTROY, 0, 0);

         mq_remove_window_from_all_queues(window);

         pinteraction->send_message(WM_NCDESTROY, 0, 0);

      }
      else
      {

         try
         {

            //window->m_pimpl->release();

         }
         catch(...)
         {

         }

      }

      oswindow_remove_impl(window->m_pimpl);

   }

   x11_fork([window]()
   {

      sync_lock sl(x11_mutex());

      Display * pdisplay = window->display();

      Window win = window->window();

      oswindow_data * pdata = (oswindow_data *) (void *) window;

      bool bIs = is_window(window);

      oswindow_remove(pdisplay, win);

      windowing_output_debug_string("\n::DestroyWindow 1");

      xdisplay d(pdisplay);

      XUnmapWindow(pdisplay, win);

      XDestroyWindow(pdisplay, win);

      windowing_output_debug_string("\n::DestroyWindow 2");

   });

   return true;

}


WINBOOL is_window(oswindow oswindow)
{

   if(::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
   {

      return FALSE;

   }

   return TRUE;

}


oswindow g_oswindowDesktop;


Display * x11_get_display();




oswindow get_desktop_window()
{

   return g_oswindowDesktop;

}


/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to uxse, cxopy, mxodify, mxerge, pxublish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Cairo)?oldid=10388
*/


#define SIZEX 100
#define SIZEY  50


//void message_box_paint(::draw2d::graphics_pointer & pgraphics, string_array & stra, bool_array  & baTab, int_array  & ya,SIZE * psize)
//{
//
//   sync_lock sl(x11_mutex());
//
//   pgraphics->fill_rect(::rect(*psize), RGB(84, 90, 80));
//
//   ::draw2d::brush_pointer pen(e_create_new);
//
//   pen->create_solid(0);
//
//   for(index i = 0; i < stra.get_count(); i++)
//   {
//
//      pgraphics->text_out(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
//
//   }
//
//}
//
#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property

Atom * wm_get_list_raw(oswindow w, Atom atomList, unsigned long int * items);
int wm_test_state(oswindow w, const char * pszNetStateFlag);
int wm_test_state_raw(oswindow w, const char * pszNetStateFlag);
int wm_test_list_raw(oswindow w, Atom atomList, Atom atomFlag);
bool wm_add_remove_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet);


void wm_add_remove_state_mapped_raw(oswindow w, e_net_wm_state estate, bool bSet)
{

   sync_lock sl(x11_mutex());

   if(w->m_iaNetWmState[estate] == (bSet ? 1 : 0))
   {

      return;

   }

   w->m_iaNetWmState[estate] = (bSet ? 1 : 0);

   Display * display = w->display();

   Window window = w->window();

   Window windowRoot = DefaultRootWindow(display);

   auto atomFlag = w->m_osdisplay->intern_atom(estate, true);

   auto atomWmNetState = w->m_osdisplay->net_wm_state_atom(true);

   if(wm_test_list_raw(w, atomWmNetState, atomFlag))
   {

      if(bSet)
      {

         return;

      }

   }
   else
   {

      if(!bSet)
      {

         return;

      }

   }

   XClientMessageEvent xclient;

   xxf_zero(xclient);

   xclient.type            = ClientMessage;
   xclient.window          = window;
   xclient.message_type    = atomWmNetState;
   xclient.format          = 32;
   xclient.data.l[0]       = bSet ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
   xclient.data.l[1]       = atomFlag;
   xclient.data.l[2]       = 0;
   xclient.data.l[3]       = 0;
   xclient.data.l[4]       = 0;

   XSendEvent(display, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient );

}


void wm_add_remove_state_mapped(oswindow w, e_net_wm_state estate, bool bSet)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_add_remove_state_mapped 1");

   xdisplay d(w->display());

   wm_add_remove_state_mapped_raw(w, estate, bSet);

   windowing_output_debug_string("\n::wm_add_remove_state_mapped 2");

}


void wm_add_remove_state_unmapped_raw(oswindow w, e_net_wm_state estate, bool bSet)
{

   sync_lock sl(x11_mutex());

   if(w->m_iaNetWmState[estate] == (bSet ? 1 : 0))
   {

      return;

   }

   w->m_iaNetWmState[estate] = (bSet ? 1 : 0);

   Display * display = w->display();

   Window window = w->window();

   int iScreen = DefaultScreen(display);

   Window windowRoot = RootWindow(display, iScreen);

   Atom atomFlag = w->m_osdisplay->intern_atom(estate, true);

   Atom atomWmNetState = w->m_osdisplay->net_wm_state_atom(true);

   wm_add_remove_list_raw(w, atomWmNetState, atomFlag, bSet);

}


void wm_add_remove_state_unmapped(oswindow w, e_net_wm_state estate, bool bSet)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_add_remove_state_unmapped 1");

   xdisplay d(w->display());

   wm_add_remove_state_unmapped_raw(w, estate, bSet);

   windowing_output_debug_string("\n::wm_add_remove_state_unmapped 2");

}


void wm_add_remove_state_raw(oswindow w, e_net_wm_state estate, bool bSet)
{

   sync_lock sl(x11_mutex());

   if(IsWindowVisibleRaw(w))
   {

      wm_add_remove_state_mapped_raw(w, estate, bSet);

   }
   else
   {

      wm_add_remove_state_unmapped_raw(w, estate, bSet);

   }

}


void wm_add_remove_state(oswindow w, e_net_wm_state estate, bool bSet)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_add_remove_state 1");

   xdisplay d(w->display());

   wm_add_remove_state_raw(w, estate, bSet);

   windowing_output_debug_string("\n::wm_add_remove_state 2");

}


void wm_state_clear_raw(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   wm_add_remove_state_raw(w, net_wm_state_above, false);
   wm_add_remove_state_raw(w, net_wm_state_below, false);
   wm_add_remove_state_raw(w, net_wm_state_hidden, false);

}


//    wm_add_remove_state_raw(w, net_wm_state_maximized_horz, false);
//    wm_add_remove_state_raw(w, net_wm_state_maximized_vert, false);
//    wm_add_remove_state_raw(w, net_wm_state_fullscreen, false);


void wm_state_below_raw(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   wm_add_remove_state_raw(w, net_wm_state_hidden, false);
   wm_add_remove_state_raw(w, net_wm_state_above, false);
   wm_add_remove_state_raw(w, net_wm_state_below, bSet);

}


void wm_state_above_raw(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   wm_add_remove_state_raw(w, net_wm_state_hidden, false);
   wm_add_remove_state_raw(w, net_wm_state_below, false);
   wm_add_remove_state_raw(w, net_wm_state_above, bSet);

}


void wm_state_hidden_raw(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   wm_add_remove_state_raw(w, net_wm_state_below, false);
   wm_add_remove_state_raw(w, net_wm_state_above, false);
   wm_add_remove_state_raw(w, net_wm_state_hidden, bSet);

}


//void wm_state_hidden(oswindow w, bool bSet)
//{
//
//   sync_lock sl(x11_mutex());
//
//   windowing_output_debug_string("\n::wm_state_above 1");
//
//   xdisplay d(w->display());
//
//   wm_state_hidden_raw(w, bSet);
//
//}


void wm_state_above(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_state_above 1");

   xdisplay d(w->display());

   wm_state_above_raw(w, bSet);

   windowing_output_debug_string("\n::wm_state_above 2");

}


void wm_state_below(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_state_below 1");

   xdisplay d(w->display());

   wm_state_above_raw(w, bSet);

   windowing_output_debug_string("\n::wm_state_below 2");

}


void wm_state_hidden(oswindow w, bool bSet)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_state_hidden 1");

   xdisplay d(w->display());

   wm_state_hidden_raw(w, bSet);

   windowing_output_debug_string("\n::wm_state_hidden 2");

}


void wm_toolwindow(oswindow w, bool bToolWindow)
{

   x11_sync([=]()
   {

      windowing_output_debug_string("\n::wm_toolwindow 1");

      sync_lock sl(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_toolwindow 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      wm_add_remove_state_raw(w, net_wm_state_skip_taskbar, bToolWindow);

      windowing_output_debug_string("\n::wm_toolwindow 2");

   });

}


void wm_hidden_state(oswindow w, bool bHidden)
{

   x11_sync([=]()
   {

      windowing_output_debug_string("\n::wm_hidden_state 1");

      sync_lock sl(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_hidden_state 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      wm_add_remove_state_raw(w, net_wm_state_skip_taskbar, bHidden);

      windowing_output_debug_string("\n::wm_hidden_state 2");

   });

}


void wm_desktopwindow(oswindow w, bool bDesktopWindow)
{

   x11_fork([=]()
   {

      windowing_output_debug_string("\n::wm_desktopwindow 1");

      sync_lock sl(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_desktopwindow 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      Window windowRoot = d.default_root_window();

      Atom atomWindowType = d.intern_atom("_NET_WM_WINDOW_TYPE", False);

      if(atomWindowType != None)
      {

         Atom atomWindowTypeValue;

         if(bDesktopWindow)
         {

            atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_DESKTOP", False);

         }
         else
         {

            atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);

         }

         if(atomWindowType != None)
         {

            XChangeProperty(d, window, atomWindowType, XA_ATOM, 32, PropModeReplace, (unsigned char *) &atomWindowTypeValue, 1);

         }

      }

      windowing_output_debug_string("\n::wm_desktopwindow 2");

   });

}


void wm_centerwindow(oswindow w, bool bCenterWindow)
{

   x11_fork([=]()
   {

      windowing_output_debug_string("\n::wm_centerwindow 1");

      sync_lock sl(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_centerwindow 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      Window windowRoot = d.default_root_window();

      Atom atomWindowType = d.intern_atom("_NET_WM_WINDOW_TYPE", False);

      if(atomWindowType != None)
      {

         Atom atomWindowTypeValue;

         if(bCenterWindow)
         {

            atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", False);

         }
         else
         {

            atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);

         }

         if(atomWindowType != None)
         {

            XChangeProperty(d, window, atomWindowType, XA_ATOM, 32, PropModeReplace, (unsigned char *) &atomWindowTypeValue, 1);

         }

      }

      windowing_output_debug_string("\n::wm_centerwindow 2");

   });

}


void wm_dockwindow(oswindow w, bool bDockWindow)
{

   x11_fork([=]()
   {

      windowing_output_debug_string("\n::wm_dockwindow 1");

      sync_lock sl(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_dockwindow 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      Window windowRoot = d.default_root_window();

      Atom atomWindowType = d.intern_atom("_NET_WM_WINDOW_TYPE", False);

      if(atomWindowType != None)
      {

         Atom atomWindowTypeValue;

         if(bDockWindow)
         {

            atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_DOCK", False);

         }
         else
         {

            atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);

         }

         if(atomWindowType != None)
         {

            XChangeProperty(d, window, atomWindowType, XA_ATOM, 32, PropModeReplace, (unsigned char *) &atomWindowTypeValue, 1);

         }

      }

      windowing_output_debug_string("\n::wm_dockwindow 2");

   });

}


void wm_nodecorations(oswindow w, int bMap)
{

   x11_fork([=]()
   {

      windowing_output_debug_string("\n::wm_nodecorations 1");

      sync_lock sl(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         return;

      }

      _wm_nodecorations(w, bMap);

   });

}

void _wm_nodecorations(oswindow w, int bMap)
{

   Window window = w->window();

   Window windowRoot = DefaultRootWindow(w->display());

   bool bCreateAtom = true;

   Atom atomMotifHints = XInternAtom(w->display(), "_MOTIF_WM_HINTS", bCreateAtom ? True : False);

   if(atomMotifHints != None)
   {

      MWMHints hints = {MWM_HINTS_DECORATIONS, 0, MWM_DECOR_NONE, 0, 0};

      XChangeProperty(w->display(), window, atomMotifHints, atomMotifHints, 32, PropModeReplace, (unsigned char *)&hints, sizeof(MWMHints) / 4);

   }

   if(bMap)
   {

      XUnmapWindow(w->display(), window);

      XMapWindow(w->display(), window);

   }

   windowing_output_debug_string("\n::wm_nodecorations 2");

}


WINBOOL IsWindowVisibleRaw(Display * display, Window window);


void wm_iconify_window(oswindow oswindow)
{

   x11_fork([oswindow]()
   {

      sync_lock sl(x11_mutex());

      xdisplay display(oswindow->display());

      windowing_output_debug_string("\n::wm_iconify_window 1");

      if(display.is_null())
      {

         windowing_output_debug_string("\n::wm_iconify_window 1.1");

         return;

      }

      Window window = oswindow->window();

      int iScreen = DefaultScreen(display.operator Display *());

      if(IsWindowVisibleRaw(display, window))
      {

         XIconifyWindow(display, window, iScreen);

      }
      else
      {

         if(oswindow->m_pimpl->m_puserinteraction->layout().design().display() !=::display_iconic)
         {

            oswindow->m_pimpl->m_puserinteraction->layout().design() = ::display_iconic;

         }

         unmapped_net_state_raw(display, window, display.intern_atom("_NET_WM_STATE_HIDDEN", False));

      }

      windowing_output_debug_string("\n::wm_iconify_window 2");

   });

}


WINBOOL IsWindowVisibleRaw(Display * display, Window window)
{

   sync_lock sl(x11_mutex());

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display, window, &attr))
   {

      return false;

   }

   return attr.map_state == IsViewable;

}


WINBOOL IsWindowVisibleRaw(oswindow w)
{

   sync_lock sl(x11_mutex());

   Display * display = w->display();

   Window window = w->window();

   return IsWindowVisibleRaw(display, window);

}


Atom * wm_get_list_raw(oswindow w, Atom atomList, unsigned long int * pnum_items)
{

   sync_lock sl(x11_mutex());

   if(atomList == None )
   {

      return nullptr;

   }

   Display * display = w->display();

   Window window = w->window();

   Atom actual_type;

   int actual_format;

   unsigned long int bytes_after;

   Atom *atoms = nullptr;

   XGetWindowProperty(display, window, atomList, 0, 1024, False, XA_ATOM, &actual_type, &actual_format, pnum_items, &bytes_after, (unsigned char**)&atoms);

   return atoms;

}


int wm_test_list_raw(oswindow w, Atom atomList, Atom atomFlag)
{

   sync_lock sl(x11_mutex());

   Display * display = w->display();

   Window window = w->window();

   Atom actual_type;

   int actual_format;

   unsigned long i, num_items;

   Atom *atoms = wm_get_list_raw(w, atomList, &num_items);

   if(atoms == nullptr)
   {

      return 0;

   }

   bool bFind = false;

   for(i = 0; i < num_items; i++)
   {

      if(atoms[i] == atomFlag)
      {

         bFind = true;

         break;

      }

   }

   XFree(atoms);

   return bFind ? 1 : 0;

}


int wm_test_state_raw(oswindow w, const char * pszNetStateFlag)
{

   sync_lock sl(x11_mutex());

   Atom atomFlag = XInternAtom(w->display(), pszNetStateFlag, 1);

   if( atomFlag == None )
   {

      windowing_output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");

      return 0;

   }

   Atom atomNetState = XInternAtom(w->display(), "_NET_WM_STATE", 1);

   if( atomNetState == None )
   {

      windowing_output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

      return 0;

   }

   return wm_test_list_raw(w, atomNetState, atomFlag);

}


int wm_test_state(oswindow w, const char * pszNetStateFlag)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::wm_test_state 1");

   xdisplay d(w->display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::wm_test_state 1.1");

      return 0;

   }

   int i = wm_test_state_raw(w, pszNetStateFlag);

   windowing_output_debug_string("\n::wm_test_state 2");

   return i;

}


bool wm_add_remove_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet)
{

   sync_lock sl(x11_mutex());

   if( atomFlag == None )
   {

      return false;

   }

   if( atomList == None )
   {

      return false;

   }

   Display * display = w->display();

   Window window = w->window();

   int scr = DefaultScreen(display);

   Window rootw = RootWindow(display,scr);

   if(bSet)
   {

      if(!wm_test_list_raw(w, atomList, atomFlag))
      {

         XChangeProperty(display,window,atomList,XA_ATOM,32,PropModeAppend, (unsigned char *)&atomFlag,1);

      }

   }
   else
   {

      unsigned long num_items;

      Atom * plist = wm_get_list_raw(w, atomList, &num_items);

      if(plist == nullptr)
      {

         return false;

      }

      int iFind = -1;

      int i;

      for(i = 0; i < num_items; i++)
      {

         if(plist[i] == atomFlag)
         {

            iFind = i;

            break;

         }

      }

      if(iFind >= 0)
      {

         __memmov(&plist[iFind], &plist[iFind + 1], (num_items - iFind - 1) *sizeof(Atom));

         XChangeProperty(display,window,atomList,XA_ATOM,32,PropModeReplace, (unsigned char *)plist,num_items-1);

      }

      XFree(plist);

   }

   return true;

}



::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if (is_null(oswindow))
   {

      return nullptr;

   }

#ifdef WINDOWS_DESKTOP

   cslock slOsWindow(::user::g_pcsImpl);

   return ::user::g_pmapImpl->operator[](oswindow);

#else

   return oswindow->m_pimpl;

#endif

}

__pointer_array(x11_hook) g_x11hooka;

//LPFN_X11_PROCESS_EVENT g_x11processeventa[8];

::estatus x11_hook::hook()
{

   sync_lock sl(x11_mutex());

   g_x11hooka.add(this);

   return ::success;

}

::estatus x11_hook::unhook()
{

   sync_lock sl(x11_mutex());

   g_x11hooka.remove(this);

   return ::success;

}

//
//bool __x11_hook_process_event(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie * cookie)
//{
//
//   for(auto & phook : g_x11hooka)
//   {
//
//      if(phook->process_event(pdisplaydata, e, cookie))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//   for(int i = 0; i < g_cX11; i++)
//   {
//
//      if(g_x11processeventa[i] == pfn)
//      {
//
//         memmove(g_x11processeventa + i, g_x11processeventa + i + 1, g_cX11 - i - 1);
//
//         g_cX11--;
//
//         return ::success;
//
//      }
//
//   }
//
//   return ::error_failed;
//
//}

#if !defined(RASPBIAN)
bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie * cookie);
#else
bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e);
#endif

//bool __x11_hook_process_event(osdisplay_data * pdisplaydata, XEvent & e);

void x11_post_message(MESSAGE & msg);

bool g_bSkipMouseMessageInXcess = true;
DWORD g_dwLastMotion = 0;
DWORD g_dwMotionSkipTimeout = 23;

#ifdef XDISPLAY_LOCK_LOG

extern bool b_prevent_xdisplay_lock_log;

#endif


bool x11_step()
{

   bool bDoneMuchThings = false;

   {

      sync_lock sl(g_pmutexX11Sync);

      if(g_prunnableX11Sync)
      {

         g_prunnableX11Sync->call();

         g_prunnableX11Sync.release();

         g_peventX11Sync->SetEvent();

         bDoneMuchThings = true;

      }

   }

   {

      sync_lock sl(g_pmutexX11Runnable);

      while(g_prunnableptrlX11->has_elements() && ::thread_get_run())
      {

         __pointer(::element) prunnable = g_prunnableptrlX11->pop_front();

         sl.unlock();

         prunnable->call();

         sl.lock();

         bDoneMuchThings = true;

      }

   }

   return bDoneMuchThings;

}


bool post_ui_message(const MESSAGE & message);





Window g_windowX11Client = 0;


Atom g_atomKickIdle = 0;


void x11_thread(osdisplay_data * pdisplaydata)
{

   Display * pdisplay = pdisplaydata->display();

   if(pdisplay == nullptr)
   {

      return;

   }

   ::thread_set_name("x11_thread");

   g_pdisplayX11 = pdisplay;

   {

      sync_lock sl(x11_mutex());

      xdisplay d(pdisplay);

      g_atomKickIdle = XInternAtom(pdisplay, "__WM_KICKIDLE", False);

      g_windowX11Client = XCreateSimpleWindow(pdisplay, DefaultRootWindow(pdisplay), 10, 10, 10, 10, 0, 0, 0);

      XSelectInput(pdisplay, g_windowX11Client, StructureNotifyMask);

      g_oswindowDesktop = oswindow_get(pdisplay, DefaultRootWindow(pdisplay));

      g_oswindowDesktop->m_pimpl = nullptr;

      XSelectInput(pdisplay, g_oswindowDesktop->window(), StructureNotifyMask | PropertyChangeMask);

   }

   XEvent e = {};

#if !defined(RASPBIAN)

   XGenericEventCookie * cookie;

#endif

   int retval = fcntl(g_fdX11[0], F_SETFL, fcntl(g_fdX11[0], F_GETFL) | O_NONBLOCK);

   while(::get_context_system() != nullptr && ::thread_get_run())
   {

      try
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

         sync_lock sl(x11_mutex());

         xdisplay d(pdisplay);

         while(XPending(pdisplay) && ::thread_get_run())
         {

            try
            {

#if !defined(RASPBIAN)

               if(g_pobjectaExtendedEventListener)
               {

                  cookie = &e.xcookie;

               }
               else
               {

                  cookie = nullptr;

               }

#endif

               XNextEvent(pdisplay, &e);

               if(!__x11_hook_process_event(pdisplaydata->display(), e, cookie))
               {

#if !defined(RASPBIAN)

               x11_process_event(pdisplaydata, e, cookie);

#else

               x11_process_event(pdisplaydata, e);

#endif

               }

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      while(::thread_get_run())
      {

         try
         {

            if(!x11_step())
            {

               break;

            }

         }
         catch(...)
         {

            break;

         }

      }


   }

#if !defined(RASPBIAN)

   g_pobjectaExtendedEventListener.release();

#endif

   output_debug_string("x11_thread end thread");

}


#ifdef XDISPLAY_LOCK_LOG

extern bool b_prevent_xdisplay_lock_log;

#endif


//thread_pointer < XComposeStatus > t_pcomposestatus;
//thread_int_ptr < XIM > t_xim;
//thread_int_ptr < iptr > t_iXim;


//        XGenericEventCookie *cookie = (XGenericEventCookie*)&ev.xcookie;
//        XNextEvent(display, (XEvent*)&ev);
//
//        if (XGetEventData(display, cookie) &&
//            cookie->type == GenericEvent) //&&            cookie->extension == xi_opcode)
//        {
//            printf("EVENT type %d (%s)\n", cookie->evtype, type_to_name(cookie->evtype));
//            switch (cookie->evtype)
//            {
//                case XI_DeviceChanged:
//                    //print_devicechangedevent(display, cookie->data);
//                    break;
//                case XI_HierarchyChanged:
//                    //print_hierarchychangedevent(cookie->data);
//                    break;
//                case XI_RawKeyPress:
//                printf("RawKeyPress");
//                break;
//                case XI_RawKeyRelease:
//                printf("RawKeyRelease");
//                break;
//                case XI_RawButtonPress:
//                printf("RawButtonPress");
//                break;
//                case XI_RawButtonRelease:
//                printf("RawButtonRelease");
//                break;
//                case XI_RawMotion:
//                case XI_RawTouchBegin:
//                case XI_RawTouchUpdate:
//                case XI_RawTouchEnd:
//                    //print_rawevent(cookie->data);
//                    break;
//                case XI_Enter:
//                case XI_Leave:
//                case XI_FocusIn:
//                case XI_FocusOut:
//                    //print_enterleave(cookie->data);
//                    break;
//                case XI_PropertyEvent:
//                    //print_propertyevent(display, cookie->data);
//                    break;
//                default:
//                    //print_deviceevent(cookie->data);
//                    break;
//            }
//        }
//
//        XFreeEventData(display, cookie);
//    }
//
//    XDestroyWindow(display, win);
//
//
//    x11_

#if !defined(RASPBIAN)
bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie *cookie)
#else
bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e)
#endif
{

   //sync_lock sl(x11_mutex());

   Display * pdisplay = pdisplaydata->m_pdisplay;

   MESSAGE msg;

   xxf_zero(msg);

   bool bRet = false;

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

#if !defined(RASPBIAN)

   if(cookie)
   {

      bool bProcessed = false;

      if (XGetEventData(pdisplay, cookie) &&   cookie->type == GenericEvent &&  cookie->extension == xi_opcode)
      {

         if(g_pobjectaExtendedEventListener && g_pobjectaExtendedEventListener->get_count() > 0)
         {

            auto pupdate = new_update();

            e_id eid;

            switch (cookie->evtype)
            {

                case XI_RawKeyPress:
                eid = id_raw_keydown;
                break;
                case XI_RawKeyRelease:
                eid = id_raw_keyup;
                break;
                case XI_RawButtonPress:
                eid = id_raw_buttondown;
                break;
                case XI_RawButtonRelease:
                eid = id_raw_buttonup;
                break;

            }

            pupdate->m_id = eid;

            pupdate->value("return") = is_return_key((XIRawEvent*)cookie->data);

            pupdate->value("space") = is_space_key((XIRawEvent*)cookie->data);

            for(auto & p : *g_pobjectaExtendedEventListener)
            {

               p->call_update(pupdate);

            }

            bProcessed = true;

         }

      }

      XFreeEventData(pdisplay, cookie);

      if(bProcessed)
      {

         return true;

      }

   }

#endif

   msg.time = 0;

   msg.hwnd = oswindow_defer_get(pdisplay, e.xany.window);

   if(msg.hwnd == nullptr)
   {

      windowing_output_debug_string("\nmsg.hwnd == nullptr");

      return true;

   }

   if(e.xany.type == ClientMessage && e.xany.window == g_windowX11Client
   && e.xclient.message_type == g_atomKickIdle)
   {

      output_debug_string("\nkick idle received\n");

      return true;

   }

   switch(e.type)
   {
   case MotionNotify:
   {

      g_pointX11Cursor.x = e.xmotion.x_root;

      g_pointX11Cursor.y = e.xmotion.y_root;

      if(msg.hwnd != nullptr && msg.hwnd->m_pimpl != nullptr)
      {

         bool bOk = true;

         __pointer(::user::interaction) pinteraction = msg.hwnd->m_pimpl->m_puserinteraction;

         if(pinteraction.is_set())
         {

            if(pinteraction->m_tickMouseMove.elapsed() < pinteraction->m_tickMouseMoveIgnore)
            {

               bOk = false;

            }

            if(bOk)
            {

               pinteraction->m_tickMouseMove.Now();

               pinteraction->m_pointMouseMove.x = e.xmotion.x_root;

               pinteraction->m_pointMouseMove.y = e.xmotion.y_root;

               if(false)
               {

                  if(pinteraction->m_tickMouseMovePeriod > 0)
                  {

                     ::size sizeDistance((pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
                        (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));

                     if(!pinteraction->m_tickMouseMoveSkip.timeout(pinteraction->m_tickMouseMovePeriod)
                        && sizeDistance.cx * sizeDistance.cx + sizeDistance.cy * sizeDistance.cy < pinteraction->m_iMouseMoveSkipSquareDistance)
                     {

                        pinteraction->m_iMouseMoveSkipCount++;

                        pinteraction->m_bMouseMovePending = true;

                        if(pinteraction->m_iMouseMoveSkipCount == 2)
                        {

                           //output_debug_string("\nmmv>skip 2!");

                        }
                        else if(pinteraction->m_iMouseMoveSkipCount == 5)
                        {

                           //output_debug_string("\nmmv>Skip 5!!!");

                        }
                        else if(pinteraction->m_iMouseMoveSkipCount == 10)
                        {

                           //output_debug_string("\nmmv>SKIP 10 !!!!!!!!!");

                        }

                        return true;

                     }

                     pinteraction->m_iMouseMoveSkipCount = 0;

                     pinteraction->m_pointMouseMoveSkip = pinteraction->m_pointMouseMove;

                  }

               }

            }

         }

         if(!bOk)
         {

            return true;

         }

      }

      WPARAM wparam(0);

      if(e.xmotion.state & Button1Mask)
      {

         wparam |= MK_LBUTTON;

      }

      msg.message       = WM_MOUSEMOVE;
      msg.wParam        = wparam;
      msg.lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);
      msg.time          = e.xmotion.time;

      post_ui_message(msg);

   }
   break;
   case Expose:
   {

      if(e.xexpose.count == 0)
      {

         msg.message       = WM_PAINT;
         msg.lParam        = 0;
         msg.wParam        = 0;

         post_ui_message(msg);

      }

   }
   break;
   case PropertyNotify:
   {

      if(pdisplaydata->m_atomWmState == None)
      {

         pdisplaydata->m_atomWmState = pdisplaydata->intern_atom("WM_STATE", false);

      }

      {

         if(e.xany.window == pdisplaydata->default_root_window())
         {

            Atom atom = XInternAtom(pdisplay, "_NET_ACTIVE_WINDOW", False);

            if(atom == e.xproperty.atom)
            {

               oswindow_set_active_window(get_active_window());

            }

         }

      }

      msg.time = e.xproperty.time;

      if(msg.hwnd != nullptr && msg.hwnd->m_pimpl != nullptr)
      {

         int iIconic = -1;

         if(e.xproperty.atom == pdisplaydata->m_atomWmState)
         {

            iIconic = msg.hwnd->is_iconic() ? 1 : 0;

         }

         ::user::interaction * pinteraction = msg.hwnd->m_pimpl->m_puserinteraction;

         if(pinteraction != nullptr)
         {

            ::user::primitive * pimpl = pinteraction->m_pimpl;

            bool bHandled = false;

            if(pimpl != nullptr)
            {

               if(iIconic >= 0)
               {

                  if(iIconic == 0)
                  {

                     if(pinteraction->layout().design().display() == ::display_iconic)
                     {

                        //file_put_contents("/home/camilo/xxx.txt", "");

                        // 1111111111111111111111111111111111111111111

                        //pinteraction->hide();

                        pinteraction->fork([=]()
                        {

                           auto edisplayPrevious = pinteraction->window_previous_display();

                           if(edisplayPrevious == ::display_iconic)
                           {

                              pinteraction->_001OnDeiconify(::display_normal);

                           }
                           else
                           {

                              pinteraction->_001OnDeiconify(edisplayPrevious);

                           }

                        });

                        bHandled = true;

                     }
                     else if(pinteraction->layout().sketch().display() == ::display_full_screen
                           && pinteraction->layout().design().display() != ::display_full_screen)
                     {

                        pinteraction->layout().sketch() = ::display_full_screen;

                     }

                  }
                  else
                  {

                     if(pinteraction->layout().design().display() != ::display_iconic
                     && pinteraction->layout().design().display() != ::display_none)
                     {

                        pinteraction->layout().sketch() = ::display_iconic;

                     }

                  }

               }

            }

         }

      }

   }
   break;
   case MapNotify:
   case UnmapNotify:
   {

      msg.message       = WM_SHOWWINDOW;
      msg.wParam        = e.type == MapNotify;
      msg.lParam        = 0;

      post_ui_message(msg);

   }
   break;
   case ConfigureNotify:
   {

      ::user::primitive_impl * pimpl = msg.hwnd->m_pimpl;

      if(pimpl != nullptr)
      {

         ::user::interaction * pinteraction = pimpl->m_puserinteraction;

         if(pinteraction != nullptr)
         {

            if(pinteraction->layout().design().display() == ::display_iconic && !msg.hwnd->is_iconic())
            {

//               ::e_display edisplayPrevious = pinteraction->window_previous_display();
//
//               pinteraction->layout().sketch() = edisplayPrevious;
//
//               pinteraction->layout().design() = edisplayPrevious;
//
//               pinteraction->layout().output() = edisplayPrevious;
//
//               pinteraction->layout().window() = edisplayPrevious;
//
//               pinteraction->m_windowrect.m_edisplay = edisplayPrevious;

                  pinteraction->fork([=]()
                  {

                     auto edisplayPrevious = pinteraction->window_previous_display();

                     if(edisplayPrevious == ::display_iconic)
                     {

                        pinteraction->_001OnDeiconify(::display_normal);

                     }
                     else
                     {

                        pinteraction->_001OnDeiconify(edisplayPrevious);

                     }

                  });

               }

               {

                  //_x11_defer_check_configuration(msg.hwnd);

                  ::point point(e.xconfigure.x, e.xconfigure.y);

                  ::size size(e.xconfigure.width, e.xconfigure.height);

                  auto pointWindow = pinteraction->layout().window().screen_origin();

                  auto sizeWindow = pinteraction->layout().window().size();

                  if(pointWindow != point)
                  {

                     msg.message       = WM_MOVE;
                     msg.wParam        = 0;
                     msg.lParam        = point.lparam();

                     post_ui_message(msg);

                  }

                  if(sizeWindow != size)
                  {

                     msg.message       = WM_SIZE;
                     msg.wParam        = 0;
                     msg.lParam        = size.lparam();

                     post_ui_message(msg);

                  }

                  msg.hwnd->m_rect.set(point, size);

               }

            }

         }

      if(g_oswindowDesktop != nullptr && e.xconfigure.window == g_oswindowDesktop->window())
      {

         auto applicationa = Session.m_applicationa;

         try
         {

            for(auto & papplication : applicationa)
            {

               try
               {

                  auto & app = App(papplication);

                  auto uiptraFrame = app.m_puiptraFrame->interactiona();

                  for(auto & pframe : uiptraFrame)
                  {

                     try
                     {

                        pframe->post_message(WM_DISPLAYCHANGE);

                     }
                     catch(...)
                     {

                     }

                  }

               }
               catch(...)
               {

               }

            }

         }
         catch(...)
         {

         }

      }

   }
   break;
   case ButtonPress:
   case ButtonRelease:
   {

      bRet                 = true;

      msg.time          = e.xbutton.time;

      if(e.xbutton.type == ButtonPress)
      {

         if(e.xbutton.button == Button1)
         {

            ::output_debug_string("ButtonPress::Button1\n");

            msg.message = WM_LBUTTONDOWN;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = WM_MBUTTONDOWN;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = WM_RBUTTONDOWN;

         }
         else
         {

            bRet = false;

         }

      }
      else if(e.xbutton.type == ButtonRelease)
      {

         if(e.xbutton.button == Button1)
         {

            ::output_debug_string("ButtonRelease::Button1\n");

            msg.message = WM_LBUTTONUP;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = WM_MBUTTONUP;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = WM_RBUTTONUP;

         }
         else
         {

            bRet = false;

         }

      }
      else
      {

         bRet = false;

      }

      int XRoot = e.xbutton.x_root;

      int YRoot = e.xbutton.y_root;

//      int l = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_point.x;
//      int t = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_point.y;
//      int w = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_size.cx;
//      int h = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_size.cy;
//
//      ::rect r;
//
//      get_window_rect(msg.hwnd, &r);
//
//      int l1 = r.left;
//      int t1 = r.top;
//      int w1 = r.width();
//      int h1 = r.height();


      if(bRet)
      {

         msg.wParam        = 0;

         msg.lParam        = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);

         post_ui_message(msg);

      }

   }
   break;
   case KeyPress:
   case KeyRelease:
   {

      msg.time = e.xkey.time;

      bRet                 = true;

      char buf[32];

      xxf_zeroa(buf);

      string strText;

      KeySym keysym = 0;

      if(e.xkey.type == KeyPress)
      {

         msg.message = WM_KEYDOWN;

         Window window = msg.hwnd->m_window;

         auto & setThread = ::get_thread()->get_property_set();

         XIC xic = msg.hwnd->m_xic;

         XIM xim = (XIM) setThread["xim"].iptr();

         if(xic == nullptr && (msg.hwnd->m_iXic & 1) == 0)
         {

            if(((iptr) (setThread["xim_flag"].i32()) & 1) == 0)
            {

               setThread["xim_flag"] = 1;

               xim = XOpenIM(pdisplay, NULL, (char *) "ca2 Input Manager", (char *) "ca2 Input Manager");

               if (!xim)
               {

                  TRACE("cannot Open Input Manager: Try default.\n");

                  XSetLocaleModifiers("@im=");

                  xim = XOpenIM(pdisplay, NULL, (char *) "ca2 Input Manager (default)", (char *) "ca2 Input Manager (default)");

                  if (!xim)
                  {

                     TRACE("Couldn't Open Input Manager");

                  }

               }

               XIMStyle best_style = 0;

               if(xim)
               {

                  ::get_thread()->value("xim") = (iptr) xim;

                  XIMStyles * pximstyles = nullptr;

                  xxf_zerop(pximstyles);

                  XGetIMValues (xim, XNQueryInputStyle, &pximstyles, NULL, NULL);

                  if(pximstyles)
                  {

                     XIMStyle * pstyle = nullptr;

                     int i = 0;

                     for (pstyle = pximstyles->supported_styles; i < pximstyles->count_styles; i++, pstyle++)
                     {

                        TRACE("input style : 0x%X\n", *pstyle);

                        if ((*pstyle & XIMStatusNone || *pstyle & XIMStatusNothing) && (*pstyle & XIMPreeditNone || *pstyle & XIMPreeditNothing))
                        {

                           best_style = *pstyle;

                           break;

                        }

                     }

                     XFree(pximstyles);

                     if(best_style != 0)
                     {

                        ::get_thread()->set("xim_flag", ::get_thread()->value("xim_flag").i32() | 2);

                     }

                  }

               }

            }

            if(((iptr)setThread["xim_flag"].i32() & 2) != 0 && (msg.hwnd->m_iXic & 1) == 0)
            {

               msg.hwnd->m_iXic = 1;

               xic = XCreateIC(
                  xim,
                  XNInputStyle,
                  (XIMPreeditNothing | XIMStatusNothing),
                  XNClientWindow, window,
                  XNFocusWindow, window,
                  NULL);

               if (xic)
               {

                  msg.hwnd->m_iXic |= 2;

                  msg.hwnd->m_xic = xic;

               }
               else
               {

                  TRACE("cannot create Input Context.\n");

               }

            }

         }

         if((msg.hwnd->m_iXic & 3) == 3)
         {

            Status status_return;

            int iCount = Xutf8LookupString (xic, &e.xkey, buf, sizeof(buf), &keysym, &status_return);

            switch(status_return)
            {
               case XLookupNone:
                  strText.Empty();
                  keysym = 0;
               break;

               case XLookupChars:
                  strText = string(buf, iCount);
                  keysym = 0;
               break;

               case XLookupKeySym:
                  strText.Empty();
               break;

               case XLookupBoth:
                  strText = string(buf, iCount);
                  break;

               default:
               break;

            };

         }

         if(keysym == XK_BackSpace
         || keysym == XK_Delete
         || keysym == XK_Tab
         || keysym == XK_Return
         || keysym == XK_Left
         || keysym == XK_Right
         || keysym == XK_Up
         || keysym == XK_Down
         || keysym == XK_Page_Up
         || keysym == XK_Page_Down
         || keysym == XK_Home
         || keysym == XK_End)
         {

            strText.Empty();

         }


  //case XK_Escape:
//                dv_dpy->dontdraw = 1;
//                xv_pause=0;
//                XvStopVideo(dv_dpy->dpy, dv_dpy->port, dv_dpy->win);
//                XDestroyWindow(dv_dpy->dpy, dv_dpy->win);
//                break;
//
//            case XK_Q:
//            case XK_q:
//                xv_pause=0;
//                dv_dpy->dontdraw = (dv_dpy->dontdraw) ? 0:1;
//                break;
//
//            case XK_space:
//                xv_pause = (xv_pause)?0:1;
//                while(xv_pause) {
//                    dv_display_event(dv_dpy);
//                    usleep(10000);
//                }
//
//            default:
//                break;
//            }
      }
      else if(e.xkey.type == KeyRelease)
      {

         msg.message = WM_KEYUP;

      }
      else
      {

         bRet = false;

      }

      if(bRet)
      {

         KeySym keysym = XkbKeycodeToKeysym(pdisplay, e.xkey.keycode, 0, e.xkey.state & ShiftMask ? 1 : 0);

         msg.wParam        = e.xkey.keycode;

         msg.lParam        = keysym;

         post_ui_message(msg);

      }

      if(strText.has_char() && !(e.xkey.state & ControlMask))
      {

         MESSAGE msgText(msg);

         msgText.message = message_text_composition;

         msgText.wParam = 0;

         string * pstringText = new string(strText);

         msgText.lParam = (LPARAM) (iptr) (string *) (pstringText);

         printf("x11_process_message message_text_composition\n");

         post_ui_message(msgText);

      }

   }
   break;
   case FocusIn:
   {

      ::output_debug_string("FocusIn\n");

      msg.message       = WM_SETFOCUS;

      if(msg.hwnd->m_pimpl != nullptr && msg.hwnd->m_pimpl->m_puserinteraction != nullptr)
      {

         msg.hwnd->m_pimpl->m_puserinteraction->m_ewindowflag |= ::window_flag_focus;

      //msg.wParam = (WPARAM) oswindow_get(display(), e.xfocus.window);

//      Window wFocus = 0;
//
//      int revert_to_return = 0;
//
//      int iStatus = XGetInputFocus(display, &wFocus, &revert_to_return);
//
//      //if(iStatus == Success)
//      if(iStatus)
//      {
//
//         if(wFocus == e.xfocus.window)
//         {
//
//            output_debug_string("A\n");
//
//         }
//         else
//         {
//
//            output_debug_string("B " + __str(wFocus));
//
//            g_windowFocus = wFocus;
//
//         }
//
//         if(wFocus == g_windowFocus)
//         {
//
//            output_debug_string("C\n");
//
//         }
//         else
//         {
//
//            output_debug_string("D " + __str(wFocus));
//
//            g_windowFocus = wFocus;
//
//         }
//
//      }
//
//      sync_lock sl(pdata->m_pmutexInput);
//
//      pdata->m_messsageaInput.add(msg);
         post_ui_message(msg);

      }

   }
   break;
   case DestroyNotify:
   {

      msg.hwnd          = oswindow_get(pdisplay, e.xdestroywindow.window);
      msg.message       = WM_DESTROY;

      post_ui_message(msg);

      return true;

   }
   break;
   case FocusOut:
   {

      ::output_debug_string("FocusOut\n");

      auto oswindow = msg.hwnd;

      if(::is_set(oswindow))
      {

         auto pimpl = msg.hwnd->m_pimpl;

         if(::is_set(pimpl))
         {

            auto pinteraction = pimpl->m_puserinteraction;

            if(::is_set(pinteraction))
            {

               msg.message       = WM_KILLFOCUS;

               pinteraction->m_ewindowflag -= window_flag_focus;

               Window wFocus = 0;

               int revert_to_return = 0;

               XGetInputFocus(pdisplay, &wFocus, &revert_to_return);

               msg.wParam = (WPARAM) oswindow_get(pdisplay, wFocus);

               post_ui_message(msg);

            }

         }

      }

   }
   break;
   default:
   {
      output_debug_string("axis_x11 case default:");
   }
   }

   // processed

   return true;

}


namespace user
{


   LRESULT interaction_child::send_x11_event(void * pvoidEvent)
   {

      XEvent * pevent = (XEvent *) pvoidEvent;

      ___pointer < ::message::base > spbase;

      spbase = Session.get_message_base(pvoidEvent, m_puserinteraction);

      try
      {

         __pointer(::user::interaction) pinteraction = m_puserinteraction;

         while(pinteraction != nullptr && pinteraction->GetParent() != nullptr)
         {

            try
            {

               pinteraction->pre_translate_message(spbase);

            }
            catch(...)
            {

               break;

            }

            if(spbase->m_bRet)
            {

               return spbase->m_lresult;

            }

            try
            {

               pinteraction = pinteraction->GetParent();

            }
            catch(...)
            {

               break;

            }

         }

      }
      catch(...)
      {

      }

      message_handler(spbase);

      return spbase->m_lresult;

   }


} // namespace user


//namespace aura
//{
//
//
   __pointer(::message::base) channel::get_message_base(void * pevent,::user::interaction * pwnd)
   {

      __throw(todo());

      return nullptr;

   }
//
//
//} // namespace aura
//

WINBOOL set_window_pos(oswindow hwnd, oswindow hwndInsertAfter, i32 x, i32 y, i32 cx, i32 cy, UINT nFlags)
{

   sync_lock sl(x11_mutex());

   return hwnd->set_window_pos(hwndInsertAfter, x, y, cx, cy, nFlags);

}





WINBOOL get_window_rect(oswindow hwnd, RECT * prect)
{

   sync_lock sl(x11_mutex());

   xdisplay d(hwnd->display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::get_window_rect 1.1");

      return FALSE;

   }

   return x11_get_window_rect(d, hwnd->window(), prect);

}


WINBOOL get_client_rect(oswindow window, RECT * prect)
{

   sync_lock sl(x11_mutex());

   xdisplay d(window->display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::get_client_rect 1.1 (display is null)");

      return FALSE;

   }

   XWindowAttributes attr;

   if(XGetWindowAttributes(d, window->window(), &attr) == 0)
   {

      windowing_output_debug_string("\n::get_client_rect 1.2 (xgetwindowattributes failed");

      return FALSE;

   }

   prect->left      = 0;

   prect->top       = 0;

   prect->right     = prect->left    + attr.width;

   prect->bottom    = prect->top     + attr.height;

   windowing_output_debug_string("\n::get_client_rect 2");

   return TRUE;

}


WINBOOL ca2_GetClientRect(oswindow window, RECT * prect)
{

   sync_lock sl(window->m_pimpl->m_puserinteraction->mutex());

   window->m_pimpl->m_puserinteraction->get_window_rect(prect);

   OffsetRect(prect, -prect->left, -prect->top);

   return TRUE;

}




WINBOOL x11_get_cursor_pos(LPPOINT ppointCursor)
{

   Window root_return;
   Window child_return;
   i32 win_x_return;
   i32 win_y_return;
   u32 mask_return;

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = true;

#endif

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::GetCursorPos 1");

   xdisplay d(x11_get_display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::GetCursorPos 1.1");

      return FALSE;

   }

   XQueryPointer(d, d.default_root_window(), &root_return, &child_return, &ppointCursor->x, &ppointCursor->y, &win_x_return, &win_y_return, & mask_return);

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

   windowing_output_debug_string("\n::GetCursorPos 2");

   return TRUE;

}


WINBOOL GetCursorPos(LPPOINT ppointCursor)
{

   x11_sync([&]()
   {

      sync_lock sl(x11_mutex());

      x11_get_cursor_pos(ppointCursor);

   });

   return TRUE;

}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}


void wm_full_screen(oswindow w, const ::rect & rect)

{

   w->full_screen(rect);


}



CLASS_DECL_AURA void defer_dock_application(int_bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);

}


void sn_start_context();


int_bool os_init_windowing()
{

   pipe(g_fdX11);

   g_pmutexX11Runnable = new ::mutex();

   g_prunnableptrlX11 = new list < __pointer(::element) >();

   g_pmutexX11Sync = new ::mutex();

   g_peventX11Sync = new manual_reset_event();

   oswindow_data::s_pdataptra = new oswindow_dataptra;

   oswindow_data::s_pmutex = new ::mutex;

   osdisplay_data::s_pdataptra = new osdisplay_dataptra;

   osdisplay_data::s_pmutex = new ::mutex;


   return true;

}


void os_term_windowing()
{

   ::acme::del(osdisplay_data::s_pmutex);

   ::acme::del(osdisplay_data::s_pdataptra);

   ::acme::del(oswindow_data::s_pmutex);

   ::acme::del(oswindow_data::s_pdataptra);

   {

      sync_lock sl(g_pmutexX11Runnable);

      ::acme::del(g_prunnableptrlX11);

   }

   ::acme::del(g_pmutexX11Runnable);

   ::acme::del(g_peventX11Sync);

   ::acme::del(g_pmutexX11Sync);

}


int xlib_error_handler(Display * d, XErrorEvent * e)
{

   if(e->request_code == 12)
   {

      if(e->error_code == BadValue)
      {

      }

   }

   char sz[1024];

   XGetErrorText(d, e->error_code, sz, sizeof(sz));

   fputs(sz, stderr);

   abort();

}


i64 oswindow_id(oswindow w)
{

   return w->window();

}




XImage * _x11_create_image(Display * pdisplay,  ::image_pointer pimage)
{

   pimage->map();

   char * image32 = (char *) pimage->get_data();

   int width = pimage->width();

   int height = pimage->height();

   int depth = 32; // works fine with depth = 24

   int bitmap_pad = 32; // 32 for 24 and 32 bpp, 16, for 15&16

   int bytes_per_line = pimage->scan_size(); // number of bytes in the client image between the start of one scanline and the start of the next

   XImage * pximage = XCreateImage(pdisplay, CopyFromParent, depth, ZPixmap, 0, image32, width, height, bitmap_pad, bytes_per_line);

   return pximage;

}


XImage * x11_create_image(::image * pimage)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::x11_create_image 1");

   xdisplay d(x11_get_display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::x11_create_image 1.1");

      return nullptr;

   }

   return _x11_create_image(d,  pimage);

}


Pixmap _x11_create_pixmap(Display * pdisplay, ::image_pointer pimage)
{

   if(!pimage)
   {

      return 0;

   }

   XImage * pximage = _x11_create_image(pdisplay,  pimage);

   if(pximage == nullptr)
   {

      return 0;

   }

   int depth = 32; // works fine with depth = 24

   Pixmap pixmap = XCreatePixmap(pdisplay, XDefaultRootWindow(pdisplay), pimage->width(), pimage->height(), depth);

   XGCValues gcvalues = {};

   GC gc = XCreateGC(pdisplay, pixmap, 0, &gcvalues);

   XPutImage(pdisplay, pixmap, gc, pximage, 0, 0, 0, 0,pimage->width(), pimage->height());

   XFreeGC(pdisplay, gc);

   return pixmap;

}


Pixmap x11_create_pixmap(::image * pimage)
{

   sync_lock sl(x11_mutex());

   windowing_output_debug_string("\n::x11_create_pixmap 1");

   xdisplay d(x11_get_display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::x11_create_pixmap 1.1");

      return 0;

   }

   return _x11_create_pixmap(d, pimage);

}


#ifdef RASPBIAN


HCURSOR imaging::CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
{

   return hcursor_null;

}


#else


Picture _xrender_create_picture(oswindow window, ::image_pointer pimage)
{

   Pixmap pixmap = _x11_create_pixmap(window->display(), pimage);

   if(pixmap == 0)
   {

      return 0;

   }


//	bool hasNamePixmap = false;
//
//	int event_base, error_base;
//
//	if (XCompositeQueryExtension(window->display(), &event_base, &error_base))
//	{
//
//		int major = 0;
//
//		int minor = 2;
//
//		XCompositeQueryVersion(window->display(), &major, &minor);
//
//		if(major > 0 || minor >= 2 )
//		{
//
//         hasNamePixmap = true;
//
//      }
//
//	}

   auto dpy = window->display();

   auto vis = window->m_visual;

   XRenderPictFormat * pformat   = XRenderFindVisualFormat(dpy, &vis);

   bool hasAlpha                 = (pformat->type == PictTypeDirect && pformat->direct.alphaMask);
   int x                         = 0;
   int y                         = 0;
   int width                     = pimage->width();
   int height                    = pimage->height();

   XRenderPictureAttributes pa   = {};

   Picture picture               = XRenderCreatePicture(window->display(), pixmap, pformat, CPSubwindowMode, &pa);

   return picture;

}


Picture xrender_create_picture(oswindow window, ::image_pointer pimage)
{

   Picture picture = 0;

   x11_sync([&]()
   {

      sync_lock sl(x11_mutex());

      windowing_output_debug_string("\n::xrender_create_picture 1");

      xdisplay d(window->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::xrender_create_picture 1.1");

         return;

      }

      picture = _xrender_create_picture(window, pimage);

   });

   return picture;

}


HCURSOR context_image::CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
{

   HCURSOR hcursor = HNULL;

   if(::is_ok(pimage))
   {

      x11_sync([&hcursor, window, pimage, xHotSpot, yHotSpot]()
      {

         sync_lock sl(x11_mutex());

         windowing_output_debug_string("\n::CreateAlphaCursor 1");

         xdisplay d(window->display());

         if(d.is_null())
         {

            windowing_output_debug_string("\n::CreateAlphaCursor 1.1");

            return;

         }

         Picture picture = _xrender_create_picture(window, pimage);

         hcursor = XRenderCreateCursor(d, picture, xHotSpot, yHotSpot);

      });

   }

   return hcursor;


}


#endif // RASPBIAN



WINBOOL WINAPI SetWindowPos(oswindow hWnd,oswindow hWndInsertAfter,i32 X,i32 Y,i32 cx,i32 cy,UINT uFlags)
{

   return hWnd->set_window_pos(hWndInsertAfter, X, Y, cx, cy, uFlags);

}

void x11_kick_idle()
{

   if(!g_pdisplayX11)
   {

      return;

   }

   if(!g_windowX11Client)
   {

      return;

   }

   //sync_lock sl(x11_mutex());

   char ch = 1;

   ::write(g_fdX11[1], &ch, 1);

//   windowing_output_debug_string("\n::x11_kick_idle");
//
//   xdisplay d(g_pdisplayX11);
//
//   XClientMessageEvent dummyEvent;
//
//   memset(&dummyEvent, 0, sizeof(XClientMessageEvent));
//
//   dummyEvent.message_type = g_atomKickIdle;
//
//   dummyEvent.type = ClientMessage;
//
//   dummyEvent.window = g_windowX11Client;
//
//   dummyEvent.format = 32;
//
//   XSendEvent(g_pdisplayX11, g_windowX11Client, 0, 0, (XEvent*)&dummyEvent);
//
//   XFlush(g_pdisplayX11);
//
}


extern ::mutex * g_pmutexX11Runnable;
extern list < __pointer(::element) > * g_prunnableptrlX11;
extern ::mutex * g_pmutexX11Sync;
extern manual_reset_event * g_peventX11Sync;
extern __pointer(::element) g_prunnableX11Sync;


void x11_async_runnable(::element * prunnable)
{

   {

      sync_lock sl(g_pmutexX11Runnable);

      g_prunnableptrlX11->add_tail(prunnable);

   }

   x11_kick_idle();

}


WINBOOL set_foregaura_window(oswindow oswindow)
{

   if(!::is_window(oswindow))
   {

      return FALSE;

   }

   x11_fork([oswindow]()
   {

      xdisplay d(oswindow->display());

      if(d.is_null())
      {

         return;

      }

      XRaiseWindow(d, oswindow->window());

      XSetInputFocus(d, oswindow->window(), RevertToNone, CurrentTime);

   });

   return TRUE;

}

int g_iX11Ref = 0;


void x11_term();

void x11_start();

void x11_stop();

void defer_init_ui()
{

   if(g_iX11Ref > 0)
   {

      return;

   }

   g_iX11Ref = 1;

   x11_start();


}


void ui_post_quit();


void defer_term_ui()
{

   sync_lock sl(x11_mutex());

   g_iX11Ref--;

   if(g_iX11Ref <= 0)
   {

      x11_stop();

      ui_post_quit();

   }

}





void x11_thread(osdisplay_data * pdisplaydata);

//void __axis_x11_input_thread(osdisplay_data * pdisplaydata);

//pthread_t g_pthreadX11;

__pointer(::thread) g_pthreadXlib;
ITHREAD g_ithreadXlib;

//void * x11_thread_proc(void * p)
//{
//
//   osdisplay_data * pdisplaydata = (osdisplay_data *) p;
//
//   auto pthread = __create_new < thread > ();
//
//   ::set_thread(pthread);
//
//   g_pthreadXlib = pthread;
//
//   pthread->SetCurrentHandles();
//
//   x11_thread(pdisplaydata);
//
//   return nullptr;
//
//}


osdisplay_data * x11_main_display();


void x11_start()
{

   auto psystem = ::get_context_system();

   auto psession = psystem->get_context_session();

   g_pthreadXlib = psession->fork([]()
   {

      g_ithreadXlib = ::get_current_ithread();

      auto posdisplay = x11_main_display();

      x11_thread(posdisplay);

   });


}


void x11_stop()
{

   g_pthreadXlib.release();

}


void ui_post_quit()
{

}


void x11_store_name(oswindow oswindow, const char * pszName)
{

   string strName(pszName);

   x11_fork([oswindow, strName]()
   {

      sync_lock sl(x11_mutex());

      xdisplay d(oswindow->display());

      XStoreName(oswindow->display(), oswindow->window(), strName);

   });

}


//void _x11_defer_check_configuration(oswindow oswindow)
//{
//
//   sync_lock sl(x11_mutex());
//
//   xdisplay display(oswindow->display());
//
//   auto pimpl = oswindow->m_pimpl;
//
//   if(::is_null(pimpl))
//   {
//
//      return ;
//
//   }
//
//   auto pinteraction = pimpl->m_puserinteraction;
//
//   if(::is_null(pinteraction))
//   {
//
//      return;
//
//   }
//
//   ::rect rect;
//
//   x11_get_window_rect(display, oswindow->window(), rect);
//
//   auto point = rect.top_left();
//
//   tick tickLastMoveDiff = pinteraction->value("tickLastMoveDiff").i64();
//   tick tickLastSizeDiff = pinteraction->value("tickLastSizeDiff").i64();
//   bool bMoveDiff = pinteraction->value("bMoveDiff").get_bool();
//   bool bSizeDiff = pinteraction->value("bsizeDiff").get_bool();
//
//   if(!bMoveDiff)
//   {
//
//      if(pinteraction->layout().sketch().m_point != point)
//      {
//
//         bMoveDiff = true;
//
//         tickLastMoveDiff.Now();
//
//      }
//
//   }
//
//   auto size = rect.size();
//
//   if(!bSizeDiff)
//   {
//
//      if(pinteraction->layout().sketch().m_size != size)
//      {
//
//         bSizeDiff = true;
//
//         tickLastSizeDiff.Now();
//
//      }
//
//   }
//
//   bool bRedraw = false;
//
//   if(bMoveDiff && tickLastMoveDiff > 2_s
//   && bSizeDiff && tickLastSizeDiff > 2_s)
//   {
//
//      pinteraction->move_to(point);
//
//      pinteraction->set_reposition();
//
//      pinteraction->set_size(size);
//
//      pinteraction->set_need_layout();
//
//      bRedraw = true;
//
//      bMoveDiff = false;
//
//      bSizeDiff = false;
//
//   }
//   else if(bMoveDiff && tickLastMoveDiff > 3_s)
//   {
//
//      pinteraction->move_to(point);
//
//      pinteraction->set_reposition();
//
//      bRedraw = true;
//
//      bMoveDiff = false;
//
//   }
//   else if(bSizeDiff && tickLastSizeDiff > 3_s)
//   {
//
//      pinteraction->set_size(size);
//
//      pinteraction->set_need_layout();
//
//      bRedraw = true;
//
//      bSizeDiff = false;
//
//   }
//
//   if(bRedraw)
//   {
//
//      pinteraction->post_redraw();
//
//   }
//
//   pinteraction->value("bMoveDiff") = bMoveDiff;
//   pinteraction->value("bsizeDiff") = bSizeDiff;
//   pinteraction->value("tickLastMoveDiff") = __i64(tickLastMoveDiff);
//   pinteraction->value("tickLastSizeDiff") = __i64(tickLastSizeDiff);
//
//}


//void _x11_defer_check_configuration(oswindow oswindow)
//{
//
//   sync_lock sl(x11_mutex());
//
//   xdisplay display(oswindow->display());
//
//   auto pimpl = oswindow->m_pimpl;
//
//   if(::is_null(pimpl))
//   {
//
//      return ;
//
//   }
//
//   auto pinteraction = pimpl->m_puserinteraction;
//
//   if(::is_null(pinteraction))
//   {
//
//      return;
//
//   }
//
//   ::rect rectSource;
//
//   x11_get_window_rect(display, oswindow->window(), rectSource);
//
//   ::rect rectTarget;
//
//   pinteraction->get_window_rect(rectTarget);
//
//   if(rectTarget != rectSource)
//   {
//
//      pinteraction->place(rectSource);
//
//      pinteraction->set_reposition();
//
//      pinteraction->set_need_layout();
//
//      pinteraction->post_redraw();
//
//   }
//
//}


//void x11_defer_check_configuration(oswindow oswindow)
//{
//
//   x11_sync([oswindow]()
//   {
//
//      _x11_defer_check_configuration(oswindow);
//
//   });
//
//}



void os_menu_item_enable(void * pitem, bool bEnable)
{

}


void os_menu_item_check(void * pitem, bool bCheck)
{

}





oswindow GetParent(oswindow oswindow)
{

   return nullptr;

}


bool post_ui_message(const MESSAGE & message)
{

   oswindow oswindow = message.hwnd;

   ASSERT(oswindow != nullptr);

   ::user::interaction * pinteraction = oswindow_interaction(oswindow);

   ::thread * pthread = nullptr;

   if(::is_set(pinteraction))
   {

      pthread = pinteraction->m_pthreadUserInteraction;

   }
   else
   {

      pthread = oswindow->m_pimpl->m_pthreadUserImpl;

   }

   if(::is_null(pthread))
   {

      return false;

   }

   class ::mq * pmq = pthread->m_pmq;

   if(pmq == nullptr)
   {

      if(message.message == WM_QUIT)
      {

         return false;

      }

      pmq = pthread->get_mq();

   }

   if(pmq == nullptr)
   {

      return false;

   }

   sync_lock ml(pmq->mutex());

   if(message.message == WM_QUIT)
   {

      output_debug_string("WM_QUIT thread");

   }

   if(message.message == WM_LBUTTONDOWN)
   {

      output_debug_string("post_ui_message::WM_LBUTTONDOWN\n");

   }
   else if(message.message == WM_LBUTTONUP)
   {

      output_debug_string("post_ui_message::WM_LBUTTONUP\n");

   }

   pmq->m_messagea.add(message);

   pmq->m_eventNewMessage.set_event();

   return true;

}


WINBOOL set_foreground_window(oswindow oswindow)
{

   if(!::is_window(oswindow))
   {

      return FALSE;

   }

   x11_fork([oswindow]()
   {

      xdisplay d(oswindow->display());

      if(d.is_null())
      {

         return;

      }

      XRaiseWindow(d, oswindow->window());

      XSetInputFocus(d, oswindow->window(), RevertToNone, CurrentTime);

   });

   return TRUE;

}



