//
// Created by camilo on 31/01/2022 19:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/nano/_nano.h"
#include "acme/operating_system.h"
//#include <X11/Xlib.h>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include "acme/operating_system/xcb/_.h"
// dnf install xcb-util-image-devel
#include <xcb/xcb_image.h>
#include <xcb/render.h>
// apt install libx11-xcb-dev
#include <X11/Xlib-xcb.h>

#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property



namespace xcb
{



   template < typename TYPE >
   using visual_id_map = map < xcb_visualid_t, TYPE >;

   using visual_pictformat_map = visual_id_map < xcb_render_pictformat_t >;

   using visual_depth_map = visual_id_map < uint32_t >;

   template < typename TYPE >
   using pictformat_map = map < xcb_render_pictformat_t, TYPE >;

   using pictformat_info_map = pictformat_map < const xcb_render_pictforminfo_t * >;


} // namespace xcb


namespace xcb
{


   class display;
   class window;


} // namespace xcb


void operating_system_initialize_xcb_nano(::factory::factory * pfactory);


#include "event_listener.h"

//#include "font.h"

#include "acme/operating_system/cairo/nano/device.h"

#include "window.h"


#include "display.h"



