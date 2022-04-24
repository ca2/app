//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


::rectangle_i32 g_rectangleMainScreen;


::size_i32 operating_system_get_main_screen_size()
{

   return g_rectangleMainScreen;

}


void operating_system_set_main_screen_rectangle(const ::rectangle_i32 & rectangle)
{

   g_rectangleMainScreen = rectangle;

}


void operating_system_initialize_nano(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::macos::nano_window, ::nano_window_implementation>();
   pfactory->add_factory_item<::quartz2d::nano_device, ::nano_device>();
   pfactory->add_factory_item<::nano_brush>();
   pfactory->add_factory_item<::nano_font>();
   pfactory->add_factory_item<::nano_pen>();

}



