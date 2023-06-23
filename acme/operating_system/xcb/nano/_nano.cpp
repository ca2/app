//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/platform/system.h"
#include "acme/operating_system/cairo/nano/device.h"


void operating_system_initialize_xcb_nano(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::xcb::nano_window, ::nano_window_implementation>();

   ::xcb::display::get(pfactory);

}



