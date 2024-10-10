//
// Created by camilo on 2024-10-03 04:51 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/operating_system/x11/_.h"
#include <X11/Xlib.h>


inline Display * as_x11_display(::x11::display_t * px11display)
{

   return (Display *) px11display;

}



inline Window as_x11_window(::x11::window_t x11window)
{

   return (Window) x11window;

}


inline Visual * as_x11_visual(::x11::visual_t * px11visual)
{

   return (Visual *) px11visual;

}


inline Display * as_x11_display(const ::x11::handle_t & handle)
{

   return as_x11_display(handle.m_pdisplay);

}


inline Window as_x11_window(const ::x11::handle_t & handle)
{

   return as_x11_window(handle.m_window);

}


inline Visual * as_x11_visual(const ::x11::handle_t & handle)
{

   return as_x11_visual(handle.m_pvisual);

}


inline XEvent * as_x11_event(const ::x11::event_t * pevent)
{

   return (XEvent *) pevent;

}


inline ::x11::handle_t as_x11_handle(Display * pdisplay, Window window, Visual * pvisual)
{

   return {(::x11::display_t *) pdisplay, (::x11::window_t) window, (::x11::visual_t *) pvisual};

}


#define __x11_handle(handle) as_x11_display(handle), as_x11_window(handle)

#define __x11_handle_with_visual(handle) as_x11_display(handle), as_x11_window(handle), as_x11_visual(handle)



