#include "framework.h"
#include "_xcb.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>


//http://rosettacode.org/wiki/Window_creation/X11

#include <stdio.h>

#include <string.h>


extern ::particle * user_synchronization();



bool __xcb_hook_process_event(Display * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);


bool __xcb_hook_list_is_empty();


void xcb_defer_handle_just_hooks()
{

   if(get_platform_level() <= e_platform_level_apex)
   {

      xcb_handle_just_hooks();

   }

}


void xcb_handle_just_hooks()
{

   Display * pdisplay = x11_get_display();

   xcb_generic_event_t * pevent = nullptr;

//#if !defined(RASPBIAN)
//
//   XGenericEventCookie * cookie;
//
//#endif

   void * cookie = nullptr;

   while(true)
   {

      try
      {

         synchronous_lock synchronouslock(x11_mutex());

         XLockDisplay(pdisplay);

         xcb_connection_t * connection = xcb_connect(nullptr, nullptr);

         try
         {

            while(pevent = xcb_poll_for_event(connection))
            {

               __xcb_hook_process_event(pdisplay, pevent, nullptr);

               if(__xcb_hook_list_is_empty())
               {

                  break;

               }

            }

         }
         catch(...)
         {

         }

         __x11_hook_on_idle(pdisplay);

         xcb_disconnect(connection);

         XUnlockDisplay(pdisplay);

      }
      catch(...)
      {

      }

//      x11_wait_timer_or_event(pdisplay);

      if(__xcb_hook_list_is_empty())
      {

         break;

      }

   }

}



