// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSorensen
// Renamed to _nano by camilo on 2021-02-01 13:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "window.h"
#include "brush.h"
#include "font.h"
#include "pen.h"
#include "device.h"
#include "acme/user/nano/nano.h"
//#include "acme/primitive/primitive/_factory.h"


void operating_system_initialize_nano(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::windows::nano_window, ::nano_window_implementation >();
   pfactory->add_factory_item < ::windows::nano_brush, ::nano_brush >();
   pfactory->add_factory_item < ::windows::nano_font, ::nano_font >();
   pfactory->add_factory_item < ::windows::nano_pen, ::nano_pen >();
   pfactory->add_factory_item < ::windows::nano_device, ::nano_device >();

   pfactory->add_factory_item < ::nano::nano >();

   //::rectangle_i32 rectangleMainScreen;

   //rectangleMainScreen.left() = 0;
   //rectangleMainScreen.top() = 0; 
   //rectangleMainScreen.right() = GetSystemMetrics(SM_CXSCREEN);
   //rectangleMainScreen.bottom() = GetSystemMetrics(SM_CYSCREEN); 

   //operating_system_set_main_screen_rectangle(rectangleMainScreen);

}



