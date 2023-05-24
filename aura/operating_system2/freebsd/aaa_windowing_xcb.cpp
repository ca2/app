#include "framework.h"
//#include "base/user/user/_component.h"
#include "acme/operating_system/x11/_x11.h"
#include "acme/operating_system/xcb/_xcb.h"
#include "_linux.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
//#include "sn/sn.h"
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


#define ENABLE_XGENERIC_EVENT 0


osdisplay_data * x11_main_display();


oswindow _x11_get_active_window();


bool x11_runnable_step();


message_queue * get_message_queue(itask_t idthread, bool bCreate);


void oswindow_set_active_window(oswindow oswindow);


CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor);





extern SnLauncheeContext* g_psncontext;



void xcb_check_status(int status, unsigned long window)
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


#ifdef XDISPLAY_LOCK_LOG

extern bool b_prevent_xdisplay_lock_log;

#endif



#if !defined(RASPBERRYPIOS)


bool x11_process_event(osdisplay_data * pdisplaydata, XEvent * pevent, XGenericEventCookie * cookie);


#else


bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e);


#endif



#if !defined(RASPBERRYPIOS)


bool xcb_process_event(osdisplay_data * pdisplaydata, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);


#else


bool xcb_process_event(osdisplay_data * pdisplaydata, xcb_generic_event_t & e);


#endif



#ifdef XDISPLAY_LOCK_LOG


extern bool b_prevent_xdisplay_lock_log;


#endif


bool post_ui_message(const MESSAGE & message);


bool xcb_on_event(xcb_generic_event_t * pevent)
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

   XGenericEventCookie * cookie = nullptr;

//#if defined(RASPBERRYPIOS)
//
//   cookie = nullptr;
//
//#else
//
//   if(g_pobjectaExtendedEventListener)
//   {
//
//      cookie = &ptopic->xcookie;
//
//   }
//   else
//   {
//
//      cookie = nullptr;
//
//   }
//
//#endif

   if(!__xcb_hook_process_event(pdisplay, pevent, cookie))
   {

#if !defined(RASPBERRYPIOS)

      if(!xcb_process_event(pdisplaydata, pevent, cookie))

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


//extern bool g_bFinishX11Thread;

void x11_add_gdk_filter();




//gboolean x11_source_func(gpointer)
//{

  // return false;

//}

bool xcb_message_handler(xcb_generic_event_t * pevent)
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

#if !defined(RASPBERRYPIOS)

            XGenericEventCookie * cookie;

#endif

//#if !defined(RASPBERRYPIOS)
//
//            if(g_pobjectaExtendedEventListener)
//            {
//
//               cookie = &e.xcookie;
//
//            }
//            else
//            {
//
//               cookie = nullptr;
//
//            }
//
//#endif

            if(!__xcb_hook_process_event(pdisplaydata->display(), pevent, cookie))
            {

#if !defined(RASPBERRYPIOS)

               if(!xcb_process_event(pdisplaydata, pevent, cookie))

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

         if(!x11_runnable_step())
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

//#if !defined(RASPBERRYPIOS)
//
//      g_pobjectaExtendedEventListener.release();
//
//#endif

      output_debug_string("x11_thread end thread");

      return false;

   }

   return true;

}


bool xcb_message_loop_step()
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

      xcb_generic_event_t * pevent;

      xcb_connection_t * connection = xcb_connect(nullptr, nullptr);

      while((pevent = xcb_poll_for_event(connection)) && !g_bFinishX11Thread)
      {

         try
         {

            //XEvent e = {};

#if !defined(RASPBERRYPIOS)

            XGenericEventCookie * cookie;

#endif

//#if !defined(RASPBERRYPIOS)
//
//            if(g_pobjectaExtendedEventListener)
//            {
//
//               cookie = &e.xcookie;
//
//            }
//            else
//            {
//
//               cookie = nullptr;
//
//            }
//
//#endif

            //XNextEvent(pdisplay, &e);

            if(!__xcb_hook_process_event(pdisplaydata->display(), pevent, cookie))
            {

#if !defined(RASPBERRYPIOS)

               if(!xcb_process_event(pdisplaydata, pevent, cookie))

#else

               if(!x11_process_event(pdisplaydata, pevent))

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

         if(!x11_runnable_step())
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

//#if !defined(RASPBERRYPIOS)
//
//      g_pobjectaExtendedEventListener.release();
//
//#endif

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

bool xcb_process_event(osdisplay_data * pdisplaydata, xcb_generic_event_t * pevent, XGenericEventCookie *cookie)

#else

bool x11_process_event(osdisplay_data * pdisplaydata, xcb_generic_event_t * pevent)

#endif
{

   XEvent e;

   e.type = 0;

   auto eevent = ptopic->response_type & ~0x80;

   switch(eevent)
   {
   case XCB_MOTION_NOTIFY:
   {

      xcb_motion_notify_event_t * pmotion = (xcb_motion_notify_event_t *) pevent;

      e.type = MotionNotify;

      e.xmotion.window = pmotion->event;

      e.xmotion.x_root = pmotion->root_x;

      e.xmotion.y_root = pmotion->root_y;

      e.xmotion.state = pmotion->state;

   }
   break;
   case XCB_EXPOSE:
   {

      xcb_expose_event_t * pexpose = (xcb_expose_event_t *) pevent;

      e.type = Expose;

      e.xexpose.window = pexpose->window;

   }
   break;
   case XCB_PROPERTY_NOTIFY:
   {

      xcb_property_notify_event_t * ppropertynotify = (xcb_property_notify_event_t *) pevent;

      e.type = PropertyNotify;

      e.xproperty.window = ppropertynotify->window;

      e.xproperty.atom = ppropertynotify->atom;

      e.xproperty.state = ppropertynotify->state;

      e.xproperty.time = ppropertynotify->time;

   }
   break;
   case XCB_MAP_NOTIFY:
   {

      xcb_map_notify_event_t * pmapnotifyevent = (xcb_map_notify_event_t *) pevent;

      e.type = MapNotify;

      e.xmap.window = pmapnotifyevent->window;

   }
   break;
   case XCB_UNMAP_NOTIFY:
   {

      xcb_unmap_notify_event_t * punmapnotifyevent = (xcb_unmap_notify_event_t *) pevent;

      e.type = UnmapNotify;

      e.xunmap.window = punmapnotifyevent->event;

   }
   break;
   case XCB_CONFIGURE_NOTIFY:
   {

      xcb_configure_notify_event_t * pconfigurenotifyevent = (xcb_configure_notify_event_t *) pevent;

      e.type = ConfigureNotify;

      e.xproperty.window = pconfigurenotifyevent->window;

   }
   break;
   case XCB_BUTTON_PRESS:
   case XCB_BUTTON_RELEASE:
   {

      xcb_button_press_event_t * pbutton = (xcb_button_press_event_t *) pevent;

      if(eevent == XCB_BUTTON_PRESS)
      {

         e.type = ButtonPress;

      }
      else
      {

         e.type = ButtonRelease;

      }

      e.xbutton.window = pbutton->event;

      e.xbutton.x() = pbutton->event_x;

      e.xbutton.y() = pbutton->event_y;

      e.xbutton.x_root = pbutton->root_x;

      e.xbutton.y_root = pbutton->root_y;

   }
   break;
   case XCB_KEY_PRESS:
   case XCB_KEY_RELEASE:
   {

      xcb_key_press_event_t * pkey = (xcb_key_press_event_t *) pevent;

      if(eevent == XCB_BUTTON_PRESS)
      {

         e.type = ButtonPress;

      }
      else
      {

         e.type = ButtonRelease;

      }

      e.xkey.window = pkey->event;

      e.xkey.time = pkey->time;

      e.xkey.keycode = pkey->detail;

      e.xkey.state = pkey->state;

   }
   break;
   case XCB_FOCUS_IN:
   {

      xcb_focus_in_event_t * pfocus= (xcb_focus_in_event_t *) pevent;

      e.type = FocusIn;

      e.xfocus.window = pfocus->event;

   }
   break;
   case XCB_DESTROY_NOTIFY:
   {

      xcb_destroy_notify_event_t * pdestroy = (xcb_destroy_notify_event_t *) pevent;

      e.type = DestroyNotify;

      e.xdestroywindow.window = pdestroy->event;

      return true;

   }
   break;
   case XCB_FOCUS_OUT:
   {

      xcb_focus_out_event_t * pfocus= (xcb_focus_out_event_t *) pevent;

      e.type = FocusOut;

      e.xfocus.window = pfocus->event;

   }
   break;
   default:
   {
      output_debug_string("axis_x11 case default:");
   }
   }

   if(e.type)
   {

      return x11_process_event(pdisplaydata, &e, cookie);

   }

   return false;

}



