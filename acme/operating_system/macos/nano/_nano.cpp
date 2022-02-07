//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"

::size_i32 operating_system_get_main_screen_size()
{

   return {1920, 1080};

}



void operating_system_initialize_nano()
{

   ::factory::add_factory_item<::macos::nano_window, ::nano_window_implementation>();
   ::factory::add_factory_item<::nano_brush>();
   ::factory::add_factory_item<::nano_font>();
   ::factory::add_factory_item<::nano_pen>();

}



