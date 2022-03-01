//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"

::size_i32 operating_system_get_main_screen_size()
{

   return {1920, 1080};

}



void operating_system_initialize_nano(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::macos::nano_window, ::nano_window_implementation>();
   pfactory->add_factory_item<::quartz2d::nano_device, ::nano_device>();
   pfactory->add_factory_item<::nano_brush>();
   pfactory->add_factory_item<::nano_font>();
   pfactory->add_factory_item<::nano_pen>();

}



