#include "framework.h"
//#include "base/user/user/_component.h"
#include "aura/os/x11/_x11.h"
#include "_linux.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
////#include "sn/sn.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>
#include <X11/extensions/xf86vmode.h> // libxxf86vm-dev
//!!!#define pointer x11_pointer
//!!!#include <X11/extensions/Xrender.h>
//!!!#undef pointer
#include <unistd.h>
//#include <X11/XKBlib.h>
#include <X11/cursorfont.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/XKBlib.h>
//#define memory_new ACME_NEW
#include "aura/os/x11/_x11.h"
#include "acme/parallelization/message_queue.h"
#include "_glib.h"
#include <xcb/xcb.h>

bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


#define SIMPLE_UI_MAX_BUTTON_COUNT 8


bool __x11_hook_list_is_empty();

::point_i32 g_pointX11Cursor;


message_queue * get_message_queue(itask_t idthread, bool bCreate);


void oswindow_set_active_window(oswindow oswindow);


CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor);

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
::pointer< ::mutex > g_pmutexX11Runnable = nullptr;
list < ::pointer<::matter >>* g_prunnableptrlX11 = nullptr;
//::pointer< ::mutex > g_pmutexX11Sync = nullptr;
//manual_reset_event * g_peventX11Sync = nullptr;
//::pointer<::matter>g_prunnableX11Sync;
Window g_windowX11Client = 0;



int_bool _x11_get_cursor_pos(Display * d, ::point_i32 * ppointCursor);




//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

extern SnLauncheeContext* g_psncontext;
Display * x11_get_display();
void wm_toolwindow(oswindow w, bool bToolWindow);
void wm_state_hidden(oswindow w, bool bSet);
void wm_state_hidden_raw(oswindow w, bool bSet);
CLASS_DECL_AURA int_bool mq_erase_window_from_all_queues(oswindow oswindow);


int_bool x11_get_cursor_pos(::point_i32 * ppointCursor);

#if !defined(RASPBERRYPIOS)

int xi_opcode = -1;
::pointer<object_array>g_pobjectaExtendedEventListener;
void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
{

   if(!g_pobjectaExtendedEventListener)
   {

      __construct_new(g_pobjectaExtendedEventListener);

   }

   g_pobjectaExtendedEventListener->add(pdata);

   x11_fork([bMouse, bKeyboard]()
   {

      synchronous_lock synchronouslock(x11_mutex());

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



bool oswindow_erase(Display * display, Window window)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   auto pFind = oswindow_find(display, window);

   if(::is_null(pFind))
   {

      return false;

   }

   delete ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data::s_pdataptra->erase_at(iFind);

   return true;

}


bool oswindow_erase_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   auto pFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);

   if(::is_null(pFind))
   {

      return false;

   }

   delete ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data::s_pdataptra->erase_at(iFind);

   return true;

}


Atom get_window_long_atom(i32 nIndex);

// Change _NET_WM_STATE if Window is Mapped
void mapped_net_state_raw(bool add, Display * d, Window w, int iScreen, Atom state1, Atom state2)
{

   synchronous_lock synchronouslock(x11_mutex());

   XClientMessageEvent xclient;

#define _NET_WM_STATE_REMOVE        0    /* erase/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */

   zero(xclient);
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

   synchronous_lock synchronouslock(x11_mutex());

   XEvent xevent;

   unsigned int i;

   va_list argp;

   va_start(argp, w);

   zero(xevent);

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
                      (char *) atoms.get_data(), atoms.get_size());
   }
   else
   {

      XDeleteProperty(d, w, XInternAtom(d, "_NET_WM_STATE", False));

   }

   va_end(argp);

}


int_bool x11_get_window_rect(Display * d, Window window, ::rectangle_i32 * prectangle)

{

   XWindowAttributes attrs;

   if(!XGetWindowAttributes(d, window, &attrs))
   {

      windowing_output_debug_string("\n::x11_get_window_rect 1.1 (xgetwindowattributes failed)");

      return false;

   }

   int x = 0;

   int y = 0;

   int screen = XDefaultScreen((Display *) d);

   Window windowRoot = RootWindow((Display *) d, screen);

   Window child;

   XTranslateCoordinates( d, window, windowRoot, 0, 0, &x, &y, &child );

   prectangle->left      = x + attrs.x();

   prectangle->top       = y + attrs.y();

   prectangle->right     = x + attrs.x()    + attrs.width;

   prectangle->bottom    = y + attrs.y()    + attrs.height;



   windowing_output_debug_string("\n::x11_get_window_rect 2");

   return true;

}


static oswindow g_oswindowCapture;


oswindow get_capture()
{

   return g_oswindowCapture;

}


oswindow set_capture(oswindow window)
{

   synchronous_lock synchronouslock(x11_mutex());

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


int_bool release_capture()
{

   synchronous_lock synchronouslock(x11_mutex());

//    if(g_oswindowCapture == nullptr)
//    {

//       return false;

//    }

   windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

   xdisplay d(x11_get_display());

   int_bool bRet = XUngrabPointer(d, CurrentTime) != false;

   //if(bRet)
   {

      g_oswindowCapture = nullptr;

   }

   windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

   return bRet;

}


oswindow set_focus(oswindow window)
{

   synchronous_lock synchronouslock(x11_mutex());

   if(window == nullptr)
   {

      return nullptr;

   }

   windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");

   xdisplay d(window->display());

   if(!is_window(window))
   {

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");

      return nullptr;

   }

   oswindow windowOld = ::get_focus();

   if(!IsWindowVisibleRaw(window))
   {

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.2");

      return nullptr;

   }

   if(!XSetInputFocus(d, window->window(), RevertToNone, CurrentTime))
   {

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");

      return nullptr;

   }

   windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");

   return windowOld;

}


void x11_check_status(int status, unsigned long window)
{
   if (status == BadWindow)
   {
      printf("window atom # 0x%lx does not exists!", window);
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

               g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag -= ::e_window_flag_active;

               g_oswindowActive->m_pimpl->m_puserinteraction->post_message(e_message_activate, 0);

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

               g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag += ::e_window_flag_active;

               g_oswindowActive->m_pimpl->m_puserinteraction->post_message(e_message_activate, 1);

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

   synchronous_lock synchronouslock(x11_mutex());

   oswindow oswindow = nullptr;

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

bool point_is_window_origin(::point_i32 pointHitTest, oswindow oswindowExclude, int iMargin)
{

   bool bIsOrigin = false;

   x11_sync([pointHitTest, oswindowExclude, iMargin, &bIsOrigin]()
   {

      synchronous_lock synchronouslock(x11_mutex());

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

      ::rectangle_i32 rectangleTest;

      for(index i = 0; i < windowa.get_size(); i++)
      {

         string strItem = x11_get_name(display, windowa[i]);

         ::rectangle_i32 rectangleHigher;

         if(::is_set(oswindowExclude) && windowa[i] == oswindowExclude->window())
         {

            continue;

         }

         if(x11_get_window_rect(display, windowa[i], rectangleHigher))
         {

            ::rectangle_i32 rectangleHitTest;

            rectangleHitTest.set(rectangleHigher.origin(), ::size());

            rectangleHitTest.inflate(iMargin+1);

            if(rectangleHitTest.contains(pointHitTest))
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

//    synchronous_lock synchronouslock(x11_mutex());

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

//    auto pFind = windowa.find_last(oswindow->window());

//    if(::is_null(pFind))
//    {

//       return true;

//    }

//    ::rectangle_i32 rectangle;

//    x11_get_window_rect(display, oswindow->window(), rectangle);

//    //r = oswindow->m_pimpl->m_puserinteraction->window_rectangle();

//    string strTopic = x11_get_name(display, oswindow->window());

//    ::rectangle_i32 rectangleTest;

//    for(iFind++; iFind < windowa.get_size(); iFind++)
//    {

//       string strItem = x11_get_name(display, windowa[iFind]);

//       ::rectangle_i32 rectangleHigher;

//       if(x11_get_window_rect(display, windowa[iFind], rectangleHigher))
//       {

//          if(rectangleTest.intersect(rectangleHigher, rectangle))
//          {

//             return true;

//          }

//       }

//    }

//    return false;

// }



void upper_window_rects(oswindow oswindow, rectangle_i32_array & ra)
{

   synchronous_lock synchronouslock(x11_mutex());

   ra.erase_all();

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

   auto pFind = windowa.find_last(oswindow->window());

   if(::is_null(pFind))
   {

      return;

   }

   ::rectangle_i32 rectangle;

   x11_get_window_rect(display, oswindow->window(), rectangle);

   //r = oswindow->m_pimpl->m_puserinteraction->window_rectangle();

   //string strTopic = x11_get_name(display, oswindow->window());

   ::rectangle_i32 rectangleTest;

   for(iFind++; iFind < windowa.get_size(); iFind++)
   {

      //string strItem = x11_get_name(display, windowa[iFind]);

      ::rectangle_i32 rectangleHigher;

      if(x11_get_window_rect(display, windowa[iFind], rectangleHigher))
      {

         ra.add(rectangleHigher);

      }

   }

}


oswindow get_focus()
{

   synchronous_lock synchronouslock(x11_mutex());

   oswindow oswindow = nullptr;

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

   synchronous_lock synchronouslock(x11_mutex());

   {

      windowing_output_debug_string("\n::set_active_window 1");

      xdisplay d(window->display());

      XEvent xev;

      zero(xev);

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


oswindow oswindow_get_if_found(Window w)
{

   if(::oswindow_find(w) >= 0)
   {

      return ::oswindow_get(w);

   }

   return nullptr;

}


oswindow get_parent(oswindow oswindow);


oswindow _get_window_relative(oswindow oswindowParam, enum_relative erelative, Window * windowa, int numItems)
{

   if(windowa == nullptr)
   {

      windowing_output_debug_string("\n::_get_window_relative");

      return nullptr;

   }

   oswindow oswindow = nullptr;

   switch(erelative)
   {

      case e_relative_first_sibling:
      {

         oswindow = oswindow_get_if_found(windowa[0]);

      }
      break;
      case e_relative_last_sibling:
      {

         oswindow = oswindow_get_if_found(windowa[numItems - 1]);

      }
      break;
      case e_relative_next_sibling:
      case e_relative_previous_sibling:
      {

         int iFound = -1;

         for(int i = 0; i < numItems; i++)
         {

            if(windowa[i] == oswindowParam->window())
            {

               iFound = i;

               break;

            }

         }

         if(iFound < 0)
         {

            return nullptr;

         }

         if(erelative == e_relative_next_sibling)
         {

            if(iFound + 1 >= numItems)
            {

               return nullptr;

            }

            oswindow = ::oswindow_get_if_found(windowa[iFound + 1]);

         }
         else if(erelative == e_relative_previous_sibling)
         {

            if(iFound - 1 < 0)
            {

               return nullptr;

            }

            oswindow = ::oswindow_get_if_found(windowa[iFound - 1]);

         }
         else
         {

            return nullptr;

         }

      }
      default:
      {

         return nullptr;

      }

   }

   return oswindow;

}


oswindow get_window(oswindow oswindowParam, enum_relative erelative)
{

   if(::is_null(oswindowParam))
   {

      return nullptr;

   }

   synchronous_lock synchronouslock(x11_mutex());

   oswindow oswindow = nullptr;

   windowing_output_debug_string("\n::get_window 1");

   xdisplay d(oswindowParam->display());

   if(erelative == e_relative_first_sibling ||
   erelative == e_relative_last_sibling ||
   erelative == e_relative_next_sibling ||
   erelative == e_relative_previous_sibling)
   {

      ::oswindow oswindowParent = ::get_parent(oswindowParam);

      if(oswindowParent == nullptr)
      {

         Atom atomNetClientListStacking = XInternAtom(oswindowParam->display(), "_NET_CLIENT_LIST_STACKING", False);

         Atom atomActualType;

         int format;

         unsigned long numItems, bytesAfter;

         Window * windowa = 0;

         int status = XGetWindowProperty(
                  oswindowParam->display(),
                  RootWindow(oswindowParam->display(), oswindowParam->m_iScreen),
                  atomNetClientListStacking,
                  0L,
                  1024,
                  false,
                  AnyPropertyType,
                  &atomActualType,
                  &format,
                  &numItems,
                  &bytesAfter,
                  (unsigned char **) &windowa);

         if (status >= Success && numItems)
         {

            oswindow = _get_window_relative(oswindowParam, erelative, windowa, numItems);

         }

         if(windowa != NULL)
         {

            XFree(windowa);

         }

      }
      else
      {

         Window root = 0;
         Window parent = 0;
         Window *pchildren = nullptr;
         u32 numItems = 0;

         int status = XQueryTree(oswindowParam->display(), oswindowParent->window(),
                                 &root, &parent, &pchildren, &numItems);

         if (status >= Success && numItems)
         {

            oswindow = _get_window_relative(oswindowParam, erelative, pchildren, numItems);

         }

         if (pchildren != nullptr)
         {

            XFree(pchildren);

         }

      }

   }
   else
   {

      Window root = 0;
      Window parent = 0;
      Window * pchildren = nullptr;
      u32 numItems = 0;

      int status = XQueryTree(oswindowParam->display(), oswindowParam->window(),
                              &root, &parent, &pchildren, &numItems);

      if (status >= Success && numItems)
      {

         if(erelative == e_relative_first_child)
         {

            oswindow = oswindow_get_if_found(pchildren[0]);

         }
         else if(erelative == e_relative_last_child)
         {

            oswindow = oswindow_get_if_found(pchildren[numItems - 1]);

         }

      }

      if (pchildren != nullptr)
      {

         XFree(pchildren);

      }

   }

   return oswindow;

}


int_bool destroy_window(oswindow window)
{

   bool bOk = false;

   if(!is_window(window))
   {

      bOk = false;

      return false;

   }

   if(::is_set(window->m_pimpl))
   {

      ::pointer<::user::interaction>pinteraction = window->m_pimpl->m_puserinteraction;

      if(pinteraction.is_set())
      {

         pinteraction->send_message(e_message_destroy, 0, 0);

         mq_erase_window_from_all_queues(window);

         pinteraction->send_message(e_message_non_client_destroy, 0, 0);

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

      oswindow_erase_impl(window->m_pimpl);

   }

   x11_fork([window]()
   {

      synchronous_lock synchronouslock(x11_mutex());

      Display * pdisplay = window->display();

      Window win = window->window();

      oswindow_data * pdata = (oswindow_data *) (void *) window;

      bool bIs = is_window(window);

      oswindow_erase(pdisplay, win);

      windowing_output_debug_string("\n::DestroyWindow 1");

      xdisplay d(pdisplay);

      XUnmapWindow(pdisplay, win);

      XDestroyWindow(pdisplay, win);

      windowing_output_debug_string("\n::DestroyWindow 2");

   });

   return true;

}


int_bool is_window(oswindow oswindow)
{

   if(::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
   {

      return false;

   }

   return true;

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
permit persons to whom the Software is furnished to do so, topic to
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


//void message_box_paint(::draw2d::graphics_pointer & pgraphics, string_array & stra, bool_array  & baTab, int_array  & ya,::size_i32 * psize)
//{
//
//   synchronous_lock synchronouslock(x11_mutex());
//
//   pgraphics->fill_rectangle(::rectangle_i32(*psize), rgb(84, 90, 80));
//
//   ::draw2d::brush_pointer pen(e_create_new);
//
//   ppen->create_solid(0);
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
#define _NET_WM_STATE_REMOVE        0    // erase/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property

Atom * wm_get_list_raw(oswindow w, Atom atomList, unsigned long int * items);
int wm_test_state(oswindow w, const ::string & pszNetStateFlag);
int wm_test_state_raw(oswindow w, const ::string & pszNetStateFlag);
int wm_test_list_raw(oswindow w, Atom atomList, Atom atomFlag);
bool wm_add_erase_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet);


void wm_add_erase_state_mapped_raw(oswindow w, e_net_wm_state estate, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

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

   zero(xclient);

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


void wm_add_erase_state_mapped(oswindow w, e_net_wm_state estate, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::wm_add_erase_state_mapped 1");

   xdisplay d(w->display());

   wm_add_erase_state_mapped_raw(w, estate, bSet);

   windowing_output_debug_string("\n::wm_add_erase_state_mapped 2");

}


void wm_add_erase_state_unmapped_raw(oswindow w, e_net_wm_state estate, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

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

   wm_add_erase_list_raw(w, atomWmNetState, atomFlag, bSet);

}


void wm_add_erase_state_unmapped(oswindow w, e_net_wm_state estate, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::wm_add_erase_state_unmapped 1");

   xdisplay d(w->display());

   wm_add_erase_state_unmapped_raw(w, estate, bSet);

   windowing_output_debug_string("\n::wm_add_erase_state_unmapped 2");

}


void wm_add_erase_state_raw(oswindow w, e_net_wm_state estate, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   if(IsWindowVisibleRaw(w))
   {

      wm_add_erase_state_mapped_raw(w, estate, bSet);

   }
   else
   {

      wm_add_erase_state_unmapped_raw(w, estate, bSet);

   }

}


void wm_add_erase_state(oswindow w, e_net_wm_state estate, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::wm_add_erase_state 1");

   xdisplay d(w->display());

   wm_add_erase_state_raw(w, estate, bSet);

   windowing_output_debug_string("\n::wm_add_erase_state 2");

}


void wm_state_clear_raw(oswindow w, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   wm_add_erase_state_raw(w, net_wm_state_above, false);
   wm_add_erase_state_raw(w, net_wm_state_below, false);
   wm_add_erase_state_raw(w, net_wm_state_hidden, false);

}


//    wm_add_erase_state_raw(w, net_wm_state_maximized_horz, false);
//    wm_add_erase_state_raw(w, net_wm_state_maximized_vert, false);
//    wm_add_erase_state_raw(w, net_wm_state_fullscreen, false);


void wm_state_below_raw(oswindow w, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   wm_add_erase_state_raw(w, net_wm_state_hidden, false);
   wm_add_erase_state_raw(w, net_wm_state_above, false);
   wm_add_erase_state_raw(w, net_wm_state_below, bSet);

}


void wm_state_above_raw(oswindow w, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   wm_add_erase_state_raw(w, net_wm_state_hidden, false);
   wm_add_erase_state_raw(w, net_wm_state_below, false);
   wm_add_erase_state_raw(w, net_wm_state_above, bSet);

}


void wm_state_hidden_raw(oswindow w, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   wm_add_erase_state_raw(w, net_wm_state_below, false);
   wm_add_erase_state_raw(w, net_wm_state_above, false);
   wm_add_erase_state_raw(w, net_wm_state_hidden, bSet);

}


//void wm_state_hidden(oswindow w, bool bSet)
//{
//
//   synchronous_lock synchronouslock(x11_mutex());
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

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::wm_state_above 1");

   xdisplay d(w->display());

   wm_state_above_raw(w, bSet);

   windowing_output_debug_string("\n::wm_state_above 2");

}


void wm_state_below(oswindow w, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::wm_state_below 1");

   xdisplay d(w->display());

   wm_state_above_raw(w, bSet);

   windowing_output_debug_string("\n::wm_state_below 2");

}


void wm_state_hidden(oswindow w, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::wm_state_hidden 1");

   xdisplay d(w->display());

   wm_state_hidden_raw(w, bSet);

   windowing_output_debug_string("\n::wm_state_hidden 2");

}


void wm_toolwindow(oswindow w, bool bToolWindow)
{

   x11_fork([=]()
   {

      windowing_output_debug_string("\n::wm_toolwindow 1");

      synchronous_lock synchronouslock(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_toolwindow 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      wm_add_erase_state_raw(w, net_wm_state_skip_taskbar, bToolWindow);

      windowing_output_debug_string("\n::wm_toolwindow 2");

   });

}


void wm_hidden_state(oswindow w, bool bHidden)
{

   x11_sync([=]()
   {

      windowing_output_debug_string("\n::wm_hidden_state 1");

      synchronous_lock synchronouslock(x11_mutex());

      xdisplay d(w->display());

      if(d.is_null())
      {

         windowing_output_debug_string("\n::wm_hidden_state 1.1");

         fflush(stdout);

         return;

      }

      Window window = w->window();

      wm_add_erase_state_raw(w, net_wm_state_skip_taskbar, bHidden);

      windowing_output_debug_string("\n::wm_hidden_state 2");

   });

}


//void wm_arbitrarypositionwindow(oswindow w, bool bArbitraryPositionWindow)
//{
//
//   x11_fork([=]()
//            {
//
//               windowing_output_debug_string("\n::wm_arbitrarypositionwindow 1");
//
//               synchronous_lock synchronouslock(x11_mutex());
//
//               xdisplay d(w->display());
//
//               if(d.is_null())
//               {
//
//                  windowing_output_debug_string("\n::wm_arbitrarypositionwindow 1.1");
//
//                  fflush(stdout);
//
//                  return;
//
//               }
//
//               Window window = w->window();
//
//               Window windowRoot = d.default_root_window();
//
//               Atom atomWindowType = d.intern_atom("_NET_WM_WINDOW_TYPE", False);
//
//               if(atomWindowType != None)
//               {
//
//                  Atom atomWindowTypeValue;
//
//                  if(bArbitraryPositionWindow)
//                  {
//
//                     atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_UTILITY", False);
//
//                  }
//                  else
//                  {
//
//                     atomWindowTypeValue = d.intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
//
//                  }
//
//                  if(atomWindowType != None)
//                  {
//
//                     XChangeProperty(d, window, atomWindowType, XA_ATOM, 32, PropModeReplace, (unsigned char *) &atomWindowTypeValue, 1);
//
//                  }
//
//               }
//
//               windowing_output_debug_string("\n::wm_arbitrarypositionwindow 2");
//
//            });
//
//}


void wm_desktopwindow(oswindow w, bool bDesktopWindow)
{

   x11_fork([=]()
   {

      windowing_output_debug_string("\n::wm_desktopwindow 1");

      synchronous_lock synchronouslock(x11_mutex());

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

      synchronous_lock synchronouslock(x11_mutex());

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


void wm_splashwindow(oswindow w, bool bCenterWindow)
{

   x11_fork([=]()
            {

               windowing_output_debug_string("\n::wm_centerwindow 1");

               synchronous_lock synchronouslock(x11_mutex());

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

      synchronous_lock synchronouslock(x11_mutex());

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

      synchronous_lock synchronouslock(x11_mutex());

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


int_bool IsWindowVisibleRaw(Display * display, Window window);


void wm_iconify_window(oswindow oswindow)
{

   x11_fork([oswindow]()
   {

      synchronous_lock synchronouslock(x11_mutex());

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

         if(oswindow->m_pimpl->m_puserinteraction->layout().design().display() !=::e_display_iconic)
         {

            oswindow->m_pimpl->m_puserinteraction->layout().design() = ::e_display_iconic;

         }

         unmapped_net_state_raw(display, window, display.intern_atom("_NET_WM_STATE_HIDDEN", False));

      }

      windowing_output_debug_string("\n::wm_iconify_window 2");

   });

}


int_bool IsWindowVisibleRaw(Display * display, Window window)
{

   synchronous_lock synchronouslock(x11_mutex());

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display, window, &attr))
   {

      return false;

   }

   return attr.map_state == IsViewable;

}


int_bool IsWindowVisibleRaw(oswindow w)
{

   synchronous_lock synchronouslock(x11_mutex());

   Display * display = w->display();

   Window window = w->window();

   return IsWindowVisibleRaw(display, window);

}


Atom * wm_get_list_raw(oswindow w, Atom atomList, unsigned long int * pnum_items)
{

   synchronous_lock synchronouslock(x11_mutex());

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

   synchronous_lock synchronouslock(x11_mutex());

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


int wm_test_state_raw(oswindow w, const ::string & pszNetStateFlag)
{

   synchronous_lock synchronouslock(x11_mutex());

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


int wm_test_state(oswindow w, const ::string & pszNetStateFlag)
{

   synchronous_lock synchronouslock(x11_mutex());

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


bool wm_add_erase_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet)
{

   synchronous_lock synchronouslock(x11_mutex());

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

      auto pFind = -1;

      int i;

      for(i = 0; i < num_items; i++)
      {

         if(plist[i] == atomFlag)
         {

            iFind = i;

            break;

         }

      }

      if(::is_set(pFind))
      {

         memory_transfer(&plist[iFind], &plist[iFind + 1], (num_items - iFind - 1) *sizeof(Atom));

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

   critical_section_lock slOsWindow(::user::g_pcsImpl);

   return ::user::g_pmapImpl->operator[](oswindow);

#else

   return oswindow->m_pimpl;

#endif

}


//
//void x11_hook::hook()
//{
//
//   synchronous_lock synchronouslock(x11_mutex());
//
//   g_x11hooka.add(this);
//
//   return ::success;
//
//}
//
//void x11_hook::unhook()
//{
//
//   synchronous_lock synchronouslock(x11_mutex());
//
//   g_x11hooka.erase(this);
//
//   return ::success;
//
//}




#if !defined(RASPBERRYPIOS)


bool x11_process_event(osdisplay_data * pdisplaydata, XEvent * pevent, XGenericEventCookie * cookie);


#else


bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e);


#endif


void x11_post_message(MESSAGE & msg);


bool g_bSkipMouseMessageInXcess = true;


::u32 g_dwLastMotion = 0;


::u32 g_dwMotionSkipTimeout = 23;


#ifdef XDISPLAY_LOCK_LOG


extern bool b_prevent_xdisplay_lock_log;


#endif


bool x11_step()
{

   bool bDoneMuchThings = false;

//   {
//
//      synchronous_lock synchronouslock(g_pmutexX11Sync);
//
//      if(g_prunnableX11Sync)
//      {
//
//         g_prunnableX11Sync->operator()();
//
//         g_prunnableX11Sync.release();
//
//         g_peventX11Sync->SetEvent();
//
//         bDoneMuchThings = true;
//
//      }
//
//   }

   {

      synchronous_lock synchronouslock(g_pmutexX11Runnable);

      while(g_prunnableptrlX11->has_elements() && ::task_get_run())
      {

         ::pointer<::matter>prunnable = g_prunnableptrlX11->pop_front();

         synchronouslock.unlock();

         prunnable->operator()();

         synchronouslock.lock();

         bDoneMuchThings = true;

      }

   }

   return bDoneMuchThings;

}


bool post_ui_message(const MESSAGE & message);



//gboolean x11_source_func(gpointer ppointer);


Atom g_atomKickIdle = 0;


bool g_bFinishX11Thread = false;


//void start_x11_thread(osdisplay_data * pdisplaydata)
//{
//
//   Display *pdisplay = pdisplaydata->display();
//
//   if (pdisplay == nullptr)
//   {
//
//      return;
//
//   }
//
//   ::task_set_name("x11_thread");
//
////   g_pdisplayX11 = pdisplay;
//
//   {
//
//      synchronous_lock synchronouslock(x11_mutex());
//
//      xdisplay d(pdisplay);
//
//      g_atomKickIdle = XInternAtom(pdisplay, "__WM_KICKIDLE", False);
//
//      g_windowX11Client = XCreateSimpleWindow(pdisplay, DefaultRootWindow(pdisplay), 10, 10, 10, 10, 0, 0, 0);
//
//      XSelectInput(pdisplay, g_windowX11Client, StructureNotifyMask);
//
//      g_oswindowDesktop = oswindow_get(pdisplay, DefaultRootWindow(pdisplay));
//
//      g_oswindowDesktop->m_pimpl = nullptr;
//
//      XSelectInput(pdisplay, g_oswindowDesktop->window(), StructureNotifyMask | PropertyChangeMask);
//
//   }
//
//   g_idle_add(x11_source_func, pdisplaydata);
//
//}


bool g_bInitX11Thread = false;


void finish_x11_thread()
{

   g_bFinishX11Thread = true;

   g_bInitX11Thread = false;

}


osdisplay_data * x11_main_display();

bool x11_on_event(XEvent * pevent)
{

   osdisplay_data * pdisplaydata = (osdisplay_data *) x11_main_display();

   if(pdisplaydata == nullptr)
   {

      return false;

   }

   Display * pdisplay = pdisplaydata->display();

   if(pdisplay == nullptr)
   {

      return false;

   }


            XGenericEventCookie * cookie;


#if defined(RASPBERRYPIOS)

            cookie = nullptr;

#else

            if(g_pobjectaExtendedEventListener)
            {

               cookie = &ptopic->xcookie;

            }
            else
            {

               cookie = nullptr;

            }

#endif

   if(!__x11_hook_process_event(pdisplay, pevent, cookie))
   {

#if !defined(RASPBERRYPIOS)

      if(!x11_process_event(pdisplaydata, pevent, cookie))

#else

         if(!x11_process_event(pdisplaydata, e))

#endif
      {

         return false;

      }




   }

   return true;

}
//catch(...)
//{
//
//}
//
//return true;
//
//}


void x11_add_gdk_filter();




//gboolean x11_source_func(gpointer)
//{

  // return false;

//}

bool x11_message_handler(XEvent * pevent)
{

   osdisplay_data * pdisplaydata = (osdisplay_data *) x11_main_display();

   Display * pdisplay = pdisplaydata->display();

   if(pdisplay == nullptr)
   {

      return false;

   }


   try
   {

      synchronous_lock synchronouslock(x11_mutex());

      xdisplay d(pdisplay);


         try
         {

            XEvent & e = *pevent;

#if !defined(RASPBERRYPIOS)

            XGenericEventCookie * cookie;

#endif

#if !defined(RASPBERRYPIOS)

            if(g_pobjectaExtendedEventListener)
            {

               cookie = &e.xcookie;

            }
            else
            {

               cookie = nullptr;

            }

#endif

            if(!__x11_hook_process_event(pdisplaydata->display(), &e, cookie))
            {

#if !defined(RASPBERRYPIOS)

               if(!x11_process_event(pdisplaydata, &e, cookie))

#else

                  if(!x11_process_event(pdisplaydata, e))

#endif
               {


               }




            }

         }
         catch(...)
         {

         }

   }
   catch(...)
   {

   }

   while(!g_bFinishX11Thread)
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

      }

   }

   if(g_bFinishX11Thread)
   {

#if !defined(RASPBERRYPIOS)

      g_pobjectaExtendedEventListener.release();

#endif

      output_debug_string("x11_thread end thread");

      return false;

   }

   return true;

}

//gboolean x11_source_func(gpointer)
bool x11_message_loop_step()
{

   osdisplay_data * pdisplaydata = (osdisplay_data *) x11_main_display();

   Display * pdisplay = pdisplaydata->display();

   if(pdisplay == nullptr)
   {

      return true;

   }

//   if(!g_bInitX11Thread)
//   {
//
//      g_bInitX11Thread = true;
//
//      synchronous_lock synchronouslock(x11_mutex());
//
//      xdisplay d(pdisplay);
//
//      g_atomKickIdle = XInternAtom(pdisplay, "__WM_KICKIDLE", False);
//
//      g_windowX11Client = XCreateSimpleWindow(pdisplay, DefaultRootWindow(pdisplay), 10, 10, 10, 10, 0, 0, 0);
//
//      XSelectInput(pdisplay, g_windowX11Client, StructureNotifyMask);
//
//      g_oswindowDesktop = oswindow_get(pdisplay, DefaultRootWindow(pdisplay));
//
//      g_oswindowDesktop->m_pimpl = nullptr;
//
//      XSelectInput(pdisplay, g_oswindowDesktop->window(), StructureNotifyMask | PropertyChangeMask);
//
//   }


   try
   {

      synchronous_lock synchronouslock(x11_mutex());

      xdisplay d(pdisplay);

      while(XPending(pdisplay) && !g_bFinishX11Thread)
      {

         try
         {

            XEvent e = {};

#if !defined(RASPBERRYPIOS)

            XGenericEventCookie * cookie;

#endif

#if !defined(RASPBERRYPIOS)

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

            if(!__x11_hook_process_event(pdisplaydata->display(), &e, cookie))
            {

#if !defined(RASPBERRYPIOS)

               if(!x11_process_event(pdisplaydata, &e, cookie))

#else

               if(!x11_process_event(pdisplaydata, e))

#endif
               {

                  //XPutBackEvent(pdisplay, &e);

                  //break;

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

   while(!g_bFinishX11Thread)
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

      }

   }

   if(g_bFinishX11Thread)
   {

#if !defined(RASPBERRYPIOS)

      g_pobjectaExtendedEventListener.release();

#endif

      output_debug_string("x11_thread end thread");

      return false;

   }

   return true;

}


//#ifdef XDISPLAY_LOCK_LOG
//
//extern bool b_prevent_xdisplay_lock_log;
//
//#endif
//

//thread_pointer < XComposeStatus > t_pcomposestatus;
//thread_int_ptr < XIM > t_xim;
//thread_int_ptr < iptr > t_iXim;


//        XGenericEventCookie *cookie = (XGenericEventCookie*)&topic.xcookie;
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

#if !defined(RASPBERRYPIOS)
bool x11_process_event(osdisplay_data * pdisplaydata, XEvent * pevent, XGenericEventCookie *cookie)
#else
bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e)
#endif
{

   XEvent & e = *pevent;

   Display * pdisplay = pdisplaydata->m_pdisplay;

   MESSAGE msg;

   zero(msg);

   bool bRet = false;

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

#if !defined(RASPBERRYPIOS)

   if(cookie)
   {

      bool bProcessed = false;

      if (XGetEventData(pdisplay, cookie) &&   cookie->type == GenericEvent &&  cookie->extension == xi_opcode)
      {

         if(g_pobjectaExtendedEventListener && g_pobjectaExtendedEventListener->get_count() > 0)
         {

            ::enum_id eid;

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

            auto ptopic = ::auraacmesystem()->topic(eid);

            ptopic->payload("return") = is_return_key((XIRawEvent*)cookie->data);

            ptopic->payload("space") = is_space_key((XIRawEvent*)cookie->data);

            ::context context;

            for(auto & p : *g_pobjectaExtendedEventListener)
            {

               p->on_subject(ptopic, &context);

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

      return false;

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

      g_pointX11Cursor.x() = e.xmotion.x_root;

      g_pointX11Cursor.y() = e.xmotion.y_root;

      if(msg.hwnd != nullptr && msg.hwnd->m_pimpl != nullptr)
      {

         bool bOk = true;

         ::pointer<::user::interaction>pinteraction = msg.hwnd->m_pimpl->m_puserinteraction;

         if(pinteraction.is_set())
         {

            if(pinteraction->m_durationMouseMove.elapsed() < pinteraction->m_durationMouseMoveIgnore)
            {

               bOk = false;

            }

            if(bOk)
            {

               pinteraction->m_durationMouseMove.Now();

               pinteraction->m_pointMouseMove.x() = e.xmotion.x_root;

               pinteraction->m_pointMouseMove.y() = e.xmotion.y_root;

               if(false)
               {

                  if(pinteraction->m_durationMouseMovePeriod > 0)
                  {

                     ::size_i32 sizeDistance((pinteraction->m_pointMouseMoveSkip.x() - pinteraction->m_pointMouseMove.x()),
                        (pinteraction->m_pointMouseMoveSkip.y() - pinteraction->m_pointMouseMove.y()));

                     if(!pinteraction->m_durationMouseMoveSkip.timeout(pinteraction->m_durationMouseMovePeriod)
                        && sizeDistance.cx() * sizeDistance.cx() + sizeDistance.cy() * sizeDistance.cy() < pinteraction->m_iMouseMoveSkipSquareDistance)
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

      wparam wparam(0);

      if(e.xmotion.state & Button1Mask)
      {

         wparam |= MK_LBUTTON;

      }

      msg.message       = e_message_mouse_move;
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

         if(msg.hwnd->m_pimpl->m_puserinteraction->m_ewindowflag & ::e_window_flag_arbitrary_positioning)
         {

            msg.hwnd->m_pimpl->_001UpdateScreen();

         }
         else
         {

            msg.message = e_message_paint;
            msg.lParam = 0;
            msg.wParam = 0;

            post_ui_message(msg);

         }

         //msg.hwnd->m_pimpl->_001UpdateScreen();

            //::pointer<::user::interaction>pinteraction = msg.hwnd->m_pimpl->m_puserinteraction;

            //pinteraction->set_need_redraw();

            //pinteraction->post_redraw();

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

               oswindow_set_active_window(_x11_get_active_window());

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

                     if(pinteraction->layout().design().display() == ::e_display_iconic)
                     {

                        //acmefile()->put_contents("/home/camilo/xxx.txt", "");

                        // 1111111111111111111111111111111111111111111

                        //pinteraction->hide();

                        pinteraction->fork([=]()
                        {

                           auto edisplayPrevious = pinteraction->window_previous_display();

                           if(edisplayPrevious == ::e_display_iconic)
                           {

                              pinteraction->_001OnDeiconify(::e_display_normal);

                           }
                           else
                           {

                              pinteraction->_001OnDeiconify(edisplayPrevious);

                           }

                        });

                        bHandled = true;

                     }
                     else if(pinteraction->layout().sketch().display() == ::e_display_full_screen
                           && pinteraction->layout().design().display() != ::e_display_full_screen)
                     {

                        pinteraction->layout().sketch() = ::e_display_full_screen;

                     }

                  }
                  else
                  {

                     if(pinteraction->layout().design().display() != ::e_display_iconic
                     && pinteraction->layout().design().display() != ::e_display_none)
                     {

                        pinteraction->layout().sketch() = ::e_display_iconic;

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

      msg.message       = e_message_show_window;
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

            if(pinteraction->layout().design().display() == ::e_display_iconic && !msg.hwnd->is_iconic())
            {

//               ::enum_display edisplayPrevious = pinteraction->window_previous_display();
//
//               pinteraction->layout().sketch() = edisplayPrevious;
//
//               pinteraction->layout().design() = edisplayPrevious;
//
//               pinteraction->layout().output() = edisplayPrevious;
//
//               pinteraction->layout().window() = edisplayPrevious;
//
//               pinteraction->m_windowrectangle.m_edisplay = edisplayPrevious;

                  pinteraction->fork([=]()
                  {

                     auto edisplayPrevious = pinteraction->window_previous_display();

                     if(edisplayPrevious == ::e_display_iconic)
                     {

                        pinteraction->_001OnDeiconify(::e_display_normal);

                     }
                     else
                     {

                        pinteraction->_001OnDeiconify(edisplayPrevious);

                     }

                  });

               }

               {

                  //_x11_defer_check_configuration(msg.hwnd);

                  ::point_i32 point(e.xconfigure.x(), e.xconfigure.y());

                  ::size_i32 size(e.xconfigure.width, e.xconfigure.height);

                  auto pointWindow = pinteraction->screen_origin();

                  auto sizeWindow = pinteraction->layout().window().size();

                  // Robbers -> Smart -> Tough Law
                  // Kids -> Soft Law
                  // 5 year smart
                  // 80 year kids
                  // big companies are?
                  // small companies are?
                  // big companies moved by auto sustainability...
                  // No human is auto sustainable, it currently needs iPhone or something....
                  // so?
                  // art as vanity and not for auto sustainability...
                  // not just for six... six... six...
                  // because sometimes we want cake and flesh and raw fish and not carrots with bread and oreo...
                  // now I imagine: sick of eating flesh-free carrots and bread, and getting drunk with cheetos and oreo
                  // we should let the flesh and the cake for the doctors,
                  // lawyers, politicians, google collaborators, drug-makers,
                  // ill-makers, sue-makers, idea-makers, religious-people,
                  // that make memory_new ammendments to ammendment itself,
                  // people above-the-law... flesh save them...
                  // ... retired and poor, widow people, complaining of dead/gone people,
                  // must eat bird seed grains.... no redemption, only in paradise...
                  // slaves of THEIR their, given by the GODs, laws ...

                  // X11 "knows" window manager can redirect a request
                  // (evidence: override_redirect flag - but that when set leave you outside of much more things)
                  // Lets not fight this X11 "thing"
                  // Accept-"stall" "authocratic" "top-down" window manager set position and size.
                  // This means setting same size_i32 and position to all three sketch and window states.
                  // The buffer may need to be resized so don't mess with current design state.

                  bool bPositionFix = pinteraction->layout().sketch().origin() != point;

#ifdef X11_PERMISSIVE_WITH_WINDOW_MANAGERS_THE_LAW_MAKERS_BECAUSE_YEAH_KNOW_WHAT_IS_BETTER_FOR_THE_USER_BUTT_DEV_STAKE_IS_MONEY_MONEY_MONEY_COMMODITY_THEY_ARE_BURNING_VALUE_AND_BURYING_MONEY_AND_TREASURES_BELOW_THE_DEAD_LAKE_OF_AVERAGING_BUT_GOD_WILL_SHAKE_THIS_FOR_LIFE

               if(bPositionFix)
                  {

                     pinteraction->layout().sketch().origin() = point;

                     pinteraction->layout().window().origin() = point;

                     pinteraction->screen_origin() = point;

                     pinteraction->screen_origin() = point;

                     pinteraction->set_reposition(true);

                  }

#endif

                  bool bSizeFix = pinteraction->layout().sketch().size() != size;

#ifdef X11_PERMISSIVE_WITH_WINDOW_MANAGERS_THE_LAW_MAKERS_BECAUSE_YEAH_KNOW_WHAT_IS_BETTER_FOR_THE_USER_BUTT_DEV_STAKE_IS_MONEY_MONEY_MONEY_COMMODITY_THEY_ARE_BURNING_VALUE_AND_BURYING_MONEY_AND_TREASURES_BELOW_THE_DEAD_LAKE_OF_AVERAGING_BUT_GOD_WILL_SHAKE_THIS_FOR_LIFE_FOR_AWESOME_FILE

                  if(bSizeFix)
                  {

                     pinteraction->layout().sketch().size() = size;

                     pinteraction->layout().window().size() = size;

                     pinteraction->set_need_layout();

                  }

#endif

                  if(bPositionFix)
                  {

                     msg.message       = e_message_reposition;
                     msg.wParam        = 0;
                     msg.lParam        = point.lparam();

                     post_ui_message(msg);

                  }

                  if(bSizeFix)
                  {

                     msg.message       = e_message_size;
                     msg.wParam        = 0;
                     msg.lParam        = size.lparam();

                     post_ui_message(msg);

                  }

                  msg.hwnd->m_rectangle.set(point, size);

               }

            }

         }

      if(g_oswindowDesktop != nullptr && e.xconfigure.window == g_oswindowDesktop->window())
      {

         auto applicationa = psession->m_applicationa;

         try
         {

            for(auto & papp : applicationa)
            {

               try
               {

                  auto & app = App(papp);

                  auto uiptraFrame = app.m_puiptraFrame->interactiona();

                  for(auto & pframe : uiptraFrame)
                  {

                     try
                     {

                        pframe->post_message(e_message_display_change);

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

            msg.message = e_message_left_button_down;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = e_message_middle_button_down;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = e_message_right_button_down;

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

            msg.message = e_message_left_button_up;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = e_message_middle_button_up;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = e_message_right_button_up;

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

//      int l = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_point.x();
//      int t = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_point.y();
//      int w = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_size.cx();
//      int h = msg.hwnd->m_pimpl->m_puserinteraction->layout().sketch().m_size.cy();
//
//      ::rectangle_i32 r;
//
//      window_rectangle(msg.hwnd, &r);
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

      zero(buf);

      string strText;

      KeySym keysym = 0;

      if(e.xkey.type == KeyPress)
      {

         msg.message = e_message_key_down;

         Window window = msg.hwnd->m_window;

         auto & setThread = msg.hwnd->m_pimpl->get_property_set();

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

                  information("cannot Open Input Manager: Try default.\n");

                  XSetLocaleModifiers("@im=");

                  xim = XOpenIM(pdisplay, NULL, (char *) "ca2 Input Manager (default)", (char *) "ca2 Input Manager (default)");

                  if (!xim)
                  {

                     information("Couldn't Open Input Manager");

                  }

               }

               XIMStyle best_style = 0;

               if(xim)
               {

                  msg.hwnd->m_pimpl->payload("xim") = (iptr) xim;

                  XIMStyles * pximstyles = nullptr;

                  zero(pximstyles);

                  XGetIMValues (xim, XNQueryInputStyle, &pximstyles, NULL, NULL);

                  if(pximstyles)
                  {

                     XIMStyle * pstyle = nullptr;

                     int i = 0;

                     for (pstyle = pximstyles->supported_styles; i < pximstyles->count_styles; i++, pstyle++)
                     {

                        information("input style : 0x%X\n", *pstyle);

                        if ((*pstyle & XIMStatusNone || *pstyle & XIMStatusNothing) && (*pstyle & XIMPreeditNone || *pstyle & XIMPreeditNothing))
                        {

                           best_style = *pstyle;

                           break;

                        }

                     }

                     XFree(pximstyles);

                     if(best_style != 0)
                     {

                        msg.hwnd->m_pimpl->set("xim_flag", msg.hwnd->m_pimpl->payload("xim_flag").i32() | 2);

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

                  information("cannot create Input pcontext->m_papexcontext->\n");

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
                  strText.empty();
                  keysym = 0;
               break;

               case XLookupChars:
                  strText = string(buf, iCount);
                  keysym = 0;
               break;

               case XLookupKeySym:
                  strText.empty();
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

            strText.empty();

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
//                    usleep(10000_ms);
//                }
//
//            default:
//                break;
//            }
      }
      else if(e.xkey.type == KeyRelease)
      {

         msg.message = e_message_key_up;

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

         msgText.message = e_message_text_composition;

         msgText.wParam = 0;

         string * pstringText = memory_new string(strText);

         msgText.lParam = (LPARAM) (iptr) (string *) (pstringText);

         printf("x11_process_message e_message_text_composition\n");

         post_ui_message(msgText);

      }

   }
   break;
   case FocusIn:
   {

      ::output_debug_string("FocusIn\n");

      msg.message       = e_message_set_focus;

      if(msg.hwnd->m_pimpl != nullptr && msg.hwnd->m_pimpl->m_puserinteraction != nullptr)
      {

         msg.hwnd->m_pimpl->m_puserinteraction->m_ewindowflag |= ::e_window_flag_focus;

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
//            output_debug_string("B " + as_string(wFocus));
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
//            output_debug_string("D " + as_string(wFocus));
//
//            g_windowFocus = wFocus;
//
//         }
//
//      }
//
//      synchronous_lock synchronouslock(pdata->m_pmutexInput);
//
//      pdata->m_messsageaInput.add(msg);
         post_ui_message(msg);

      }

   }
   break;
   case DestroyNotify:
   {

      msg.hwnd          = oswindow_get(pdisplay, e.xdestroywindow.window);
      msg.message       = e_message_destroy;

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

               msg.message       = e_message_kill_focus;

               pinteraction->m_ewindowflag -= ::e_window_flag_focus;

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

      ::pointer<::user::message>spbase;

      spbase = psession->get_message_base(pvoidEvent, m_puserinteraction);

      try
      {

         ::pointer<::user::interaction>pinteraction = m_puserinteraction;

         while(pinteraction != nullptr && pinteraction->get_parent() != nullptr)
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

               pinteraction = pinteraction->get_parent();

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
   ::pointer<::user::message>channel::get_message_base(void * pevent,::user::interaction * puserinteraction)
   {

      throw ::exception(todo);

      return nullptr;

   }
//
//
//} // namespace aura
//

int_bool set_window_position(oswindow hwnd, oswindow hwndInsertAfter, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
{

   synchronous_lock synchronouslock(x11_mutex());

   return hwnd->set_window_position(hwndInsertAfter, x, y, cx, cy, nFlags);

}





int_bool window_rectangle(oswindow hwnd, ::rectangle_i32 * prectangle)
{

   synchronous_lock synchronouslock(x11_mutex());

   xdisplay d(hwnd->display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::window_rectangle 1.1");

      return false;

   }

   return x11_get_window_rect(d, hwnd->window(), prectangle);

}


int_bool client_rectangle(oswindow window, ::rectangle_i32 * prectangle)
{

   synchronous_lock synchronouslock(x11_mutex());

   xdisplay d(window->display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::client_rectangle 1.1 (display is null)");

      return false;

   }

   XWindowAttributes attr;

   if(XGetWindowAttributes(d, window->window(), &attr) == 0)
   {

      windowing_output_debug_string("\n::client_rectangle 1.2 (xgetwindowattributes failed");

      return false;

   }

   prectangle->left      = 0;

   prectangle->top       = 0;

   prectangle->right     = prectangle->left    + attr.width;

   prectangle->bottom    = prectangle->top     + attr.height;

   windowing_output_debug_string("\n::client_rectangle 2");

   return true;

}


int_bool ca2_GetClientRect(oswindow window, ::rectangle_i32 * prectangle)
{

   synchronous_lock synchronouslock(window->m_pimpl->m_puserinteraction->synchronization());

   window->m_pimpl->m_puserinteraction->window_rectangle(prectangle);

   offset_rect(prectangle, -prectangle->left, -prectangle->top);

   return true;

}




int_bool x11_get_cursor_pos(::point_i32 * ppointCursor)
{

   Window root_return;
   Window child_return;
   i32 win_x_return;
   i32 win_y_return;
   u32 mask_return;

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = true;

#endif

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::GetCursorPos 1");

   xdisplay d(x11_get_display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::GetCursorPos 1.1");

      return false;

   }

   XQueryPointer(d, d.default_root_window(), &root_return, &child_return, &ppointCursor->x, &ppointCursor->y, &win_x_return, &win_y_return, & mask_return);

#ifdef XDISPLAY_LOCK_LOG

   b_prevent_xdisplay_lock_log = false;

#endif

   windowing_output_debug_string("\n::GetCursorPos 2");

   return true;

}


int_bool GetCursorPos(::point_i32 * ppointCursor)
{

   x11_sync([&]()
   {

      synchronous_lock synchronouslock(x11_mutex());

      x11_get_cursor_pos(ppointCursor);

   });

   return true;

}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}


void wm_full_screen(oswindow w, const ::rectangle_i32 & rectangle)

{

   w->full_screen(rectangle);


}



CLASS_DECL_AURA void defer_dock_application(int_bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);

}


void sn_start_context();

void acme_defer_os_init_windowing();

int_bool os_init_windowing()
{

   acme_defer_os_init_windowing();

   g_pmutexX11Runnable = memory_new ::pointer < ::mutex >();

   g_prunnableptrlX11 = memory_new list < ::pointer<::matter >>);

//   g_pmutexX11Sync = memory_new ::pointer < ::mutex >();

   //g_peventX11Sync = memory_new manual_reset_event();

   oswindow_data::s_pdataptra = memory_new oswindow_dataptra;

   oswindow_data::s_pmutex = memory_new ::pointer < ::mutex >;

   osdisplay_data::s_pdataptra = memory_new osdisplay_dataptra;

   osdisplay_data::s_pmutex = memory_new ::pointer < ::mutex >;


   return true;

}


void os_term_windowing()
{

   ::acme::del(osdisplay_data::s_pmutex);

   ::acme::del(osdisplay_data::s_pdataptra);

   ::acme::del(oswindow_data::s_pmutex);

   ::acme::del(oswindow_data::s_pdataptra);

   {

      synchronous_lock synchronouslock(g_pmutexX11Runnable);

      ::acme::del(g_prunnableptrlX11);

   }

   ::acme::del(g_pmutexX11Runnable);

//   ::acme::del(g_peventX11Sync);

//   ::acme::del(g_pmutexX11Sync);

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

   synchronous_lock synchronouslock(x11_mutex());

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

   synchronous_lock synchronouslock(x11_mutex());

   windowing_output_debug_string("\n::x11_create_pixmap 1");

   xdisplay d(x11_get_display());

   if(d.is_null())
   {

      windowing_output_debug_string("\n::x11_create_pixmap 1.1");

      return 0;

   }

   return _x11_create_pixmap(d, pimage);

}


#ifdef RASPBERRYPIOS


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

      synchronous_lock synchronouslock(x11_mutex());

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

         synchronous_lock synchronouslock(x11_mutex());

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


#endif // RASPBERRYPIOS



int_bool WINAPI SetWindowPos(oswindow hWnd,oswindow hWndInsertAfter,i32 X,i32 Y,i32 cx,i32 cy,::u32 uFlags)
{

   return hWnd->set_window_position(hWndInsertAfter, X, Y, cx, cy, uFlags);

}




extern ::pointer< ::mutex > g_pmutexX11Runnable;
extern list < ::pointer<::matter >>* g_prunnableptrlX11;
extern ::pointer< ::mutex > g_pmutexX11Sync;
extern manual_reset_event * g_peventX11Sync;
extern ::pointer<::matter>g_prunnableX11Sync;


void x11_async_runnable(::matter * prunnable)
{

   {

      synchronous_lock synchronouslock(g_pmutexX11Runnable);

      g_prunnableptrlX11->add_tail(prunnable);

   }

   x11_kick_idle();

}


int_bool set_foregaura_window(oswindow oswindow)
{

   if(!::is_window(oswindow))
   {

      return false;

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

   return true;

}

int g_iX11Ref = 0;

void x11_term();

void x11_start();

void ui_post_quit();

void defer_term_ui()
{

   synchronous_lock synchronouslock(x11_mutex());

   g_iX11Ref--;

   if(g_iX11Ref <= 0)
   {

      finish_x11_thread();

      ui_post_quit();

   }

}


void x11_thread(osdisplay_data * pdisplaydata);


::task_pointer g_pthreadXlib;


itask_t g_itaskXlib;


itask_t x11_get_itask()
{

   return g_itaskXlib;

}


CLASS_DECL_ACME ::thread * x11_get_thread()
{

   return g_pthreadXlib;

}


osdisplay_data * x11_main_display();


void x11_store_name(oswindow oswindow, const ::string & pszName)
{

   string strName(pszName);

   x11_fork([oswindow, strName]()
   {

      synchronous_lock synchronouslock(x11_mutex());

      xdisplay d(oswindow->display());

      XStoreName(oswindow->display(), oswindow->window(), strName);

   });

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

   if(::is_null(pthread))
   {

      return false;

   }

   class ::message_queue * pmq = pthread->m_pmq;

   if(pmq == nullptr)
   {

      if(message.message == e_message_quit)
      {

         return false;

      }

      pmq = pthread->get_message_queue();

   }

   if(pmq == nullptr)
   {

      return false;

   }

   synchronous_lock ml(pmq->synchronization());

   if(message.message == e_message_quit)
   {

      output_debug_string("e_message_quit thread");

   }

   if(message.message == e_message_left_button_down)
   {

      output_debug_string("post_ui_message::e_message_left_button_down\n");

   }
   else if(message.message == e_message_left_button_up)
   {

      output_debug_string("post_ui_message::e_message_left_button_up\n");

   }

   pmq->m_messagea.add(message);

   pmq->m_eventNewMessage.set_event();

   return true;

}


int_bool set_foreground_window(oswindow oswindow)
{

   if(!::is_window(oswindow))
   {

      return false;

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

   return true;

}


void x11_main()
{

   while(!g_bFinishX11Thread)
   {

      x11_message_loop_step();

   }

}









message_queue * get_message_queue(itask_t idthread, bool bCreate);


void oswindow_set_active_window(oswindow oswindow);


CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor);




int_bool _x11_get_cursor_pos(Display * d, ::point_i32 * ppointCursor);




//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

extern SnLauncheeContext* g_psncontext;
Display * x11_get_display();
void wm_toolwindow(oswindow w, bool bToolWindow);
void wm_state_hidden(oswindow w, bool bSet);
void wm_state_hidden_raw(oswindow w, bool bSet);
CLASS_DECL_AURA int_bool mq_erase_window_from_all_queues(oswindow oswindow);


int_bool x11_get_cursor_pos(::point_i32 * ppointCursor);




void ui_post_quit();






void x11_thread(osdisplay_data * pdisplaydata);

//void __axis_x11_input_thread(osdisplay_data * pdisplaydata);





osdisplay_data * x11_main_display();



void ui_post_quit()
{

}




void os_menu_item_enable(void * pitem, bool bEnable)
{

}


void os_menu_item_check(void * pitem, bool bCheck)
{

}


oswindow get_parent(oswindow oswindow)
{

   return nullptr;

}

