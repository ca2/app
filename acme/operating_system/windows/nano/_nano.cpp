// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSørensen
// Renamed to _nano by camilo on 2021-02-01 13:44 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/user/nano/_nano.h"
#include "_nano.h"


void operating_system_initialize_nano()
{


   ____creatable_from_base(::windows::nano_window, ::nano_window_implementation);
   ____creatable_from_base(::windows::nano_brush, ::nano_brush);
   ____creatable_from_base(::windows::nano_font, ::nano_font);
   ____creatable_from_base(::windows::nano_pen, ::nano_pen);
   ____creatable_from_base(::windows::nano_device, ::nano_device);


}


::size_i32 operating_system_get_main_screen_size()
{

   return { GetSystemMetrics(SM_CXSCREEN),  GetSystemMetrics(SM_CYSCREEN) };

}



