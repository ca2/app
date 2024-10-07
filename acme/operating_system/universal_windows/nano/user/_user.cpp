// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSorensen
// Renamed to _nano by camilo on 2021-02-01 13:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"
#include "acme/platform/factory_function.h"
//#include "acme/prototype/prototype/_factory.h"


extern "C" void nano_user_universal_windows_factory(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::universal_windows::micro::interchange, ::micro::window_implementation >();
   //pfactory->add_factory_item < ::windows::nano::graphics::brush, ::nano::graphics::brush >();
   //pfactory->add_factory_item < ::windows::nano::graphics::font, ::nano::graphics::font >();
   //pfactory->add_factory_item < ::windows::nano::graphics::pen, ::nano::graphics::pen >();
   //pfactory->add_factory_item < ::windows::nano::graphics::device, ::nano::graphics::device >();

   //pfactory->add_factory_item < ::micro::user >();

   //::rectangle_i32 rectangleMainScreen;

   //rectangleMainScreen.left() = 0;
   //rectangleMainScreen.top() = 0; 
   //rectangleMainScreen.right() = GetSystemMetrics(SM_CXSCREEN);
   //rectangleMainScreen.bottom() = GetSystemMetrics(SM_CYSCREEN); 

   //operating_system_set_main_screen_rectangle(rectangleMainScreen);

}


_REFERENCE_FACTORY(nano_user_universal_windows);



