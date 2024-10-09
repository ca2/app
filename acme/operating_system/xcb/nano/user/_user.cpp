//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/user/micro/user.h"
#include "acme/platform/system.h"
#include "acme/operating_system/cairo/nano/user/device.h"


void operating_system_initialize_xcb_nano_user(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::xcb::micro::interchange, ::micro::window_implementation>();

   pfactory->add_factory_item<::micro::user>();

   ::xcb::acme::windowing::display::get(pfactory);

}



