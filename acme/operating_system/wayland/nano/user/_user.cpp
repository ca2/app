//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/operating_system/cairo/nano/user/device.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"


void operating_system_initialize_wayland_nano_user(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::wayland::nano::user::window, ::nano::user::window_implementation>();

   //::wayland::display::get(pfactory);

}



