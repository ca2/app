//
// Created by camilo on 09/04/2022.
// Modified 2023-10-05 23:50
//
#pragma once


//s#include "_atom.h"


//void x11_check_status(int status, unsigned long window);



//#ifndef WITH_XI
//#define WITH_XI
//#endif

//#define pointer x11_pointer

#include <wayland-client.h>
#include <wayland-server.h>
#include <wayland-cursor.h>
#include <wayland-client-protocol.h>
#include "wayland-gtk_shell1.h"
#include "wayland-xdg_activation_v1.h"
#include "wayland-xdg_wm_base.h"
//#include <X11/Xutil.h>
//#include <X11/extensions/Xrender.h>
//#include <X11/Xatom.h>

//#undef pointer



//Visual * get_32bit_visual(Display * pdisplay);


//void x11_kick_idle();


//void x11_wait_timer_or_event(Display * pdisplay);
//void __x11_hook_on_idle(Display * pdisplay);


//CLASS_DECL_ACME ::particle * user_synchronization();


//#include "x11_exception.h"
//#include "x11_keyboard.h"
//#include "x11_hook.h"
//#include "x11_button.h"
//#include "x11_simple_ui_display.h"
//#include "x11_message_box.h"


//::e_status deferx_initializex_x11();
//void x11_handle_just_hooks();
//void x11_defer_handle_just_hooks();
//int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
//bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


//class x11color32_t
//{
//public:
//
//
//   ::u32 m_u32;
//
//
//   x11color32_t(){m_u32=0;}
//   x11color32_t(const ::color::color & color)
//   {
//
//      auto opacity = color.u8_opacity();
//
//      m_u32 = make_u32(
//              color.u8_blue() * opacity / 255,
//              color.u8_green() * opacity / 255,
//              color.u8_red() * opacity / 255,
//              opacity);
//
//   }
//
//
//   operator unsigned long () const { return m_u32; }
//
//
//};

namespace wayland
{

   namespace nano
   {

      namespace user
      {
         void copy(xdg_toplevel_resize_edge * presizeedge, ::experience::enum_frame * peframeSizing);

         inline bool xdg_toplevel_state_array_contains(::wl_array * pwlarray, xdg_toplevel_state state)
         {

            ::collection::count c = pwlarray->size / sizeof(state);

            for(::collection::index i = 0; i < c; i++)
            {

               if(((xdg_toplevel_state *)pwlarray->data)[i] == state)
               {

                  return true;

               }

            }

            return false;

         }
      } // namespace user
   } // namespace nano
} // namespace wayland

