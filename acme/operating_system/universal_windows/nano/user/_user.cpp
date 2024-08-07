// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSorensen
// Renamed to _nano by camilo on 2021-02-01 13:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"
#include "acme/platform/factory_function.h"
//#include "acme/primitive/primitive/_factory.h"


extern "C" void nano_user_universal_windows_factory(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::universal_windows::nano::user::window, ::nano::user::window_implementation >();
   //pfactory->add_factory_item < ::windows::nano::user::brush, ::nano::user::brush >();
   //pfactory->add_factory_item < ::windows::nano::user::font, ::nano::user::font >();
   //pfactory->add_factory_item < ::windows::nano::user::pen, ::nano::user::pen >();
   //pfactory->add_factory_item < ::windows::nano::user::device, ::nano::user::device >();

   //pfactory->add_factory_item < ::nano::user::user >();

   //::rectangle_i32 rectangleMainScreen;

   //rectangleMainScreen.left() = 0;
   //rectangleMainScreen.top() = 0; 
   //rectangleMainScreen.right() = GetSystemMetrics(SM_CXSCREEN);
   //rectangleMainScreen.bottom() = GetSystemMetrics(SM_CYSCREEN); 

   //operating_system_set_main_screen_rectangle(rectangleMainScreen);

}


_REFERENCE_FACTORY(nano_user_universal_windows);



