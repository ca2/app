//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


void operating_system_initialize_xcb_nano(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::xcb::nano_window, ::nano_window_implementation>();

   ::xcb::display::get(pfactory->m_psystem);

}



