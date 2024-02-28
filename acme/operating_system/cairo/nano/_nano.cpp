//
// Created by camilo on 11/04-April/2022. 12:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "device.h"
#include "acme/user/nano/brush.h"
#include "acme/user/nano/font.h"
#include "acme/user/nano/pen.h"
#include "acme/primitive/primitive/factory.h"


void operating_system_initialize_cairo_nano(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::nano_brush>();
   pfactory->add_factory_item<::nano_font>();
   pfactory->add_factory_item<::nano_pen>();
   pfactory->add_factory_item<::cairo::nano_device, ::nano_device>();

}



