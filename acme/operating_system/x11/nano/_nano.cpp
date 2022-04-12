//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


::user::enum_desktop _get_edesktop();

::size_i32 operating_system_get_main_screen_size()
{

   return {1920, 1080};

}


void operating_system_initialize_x11_nano(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::x11::nano_window, ::nano_window_implementation>();

}


void operating_system_initialize_xcb_nano(::factory::factory * pfactory);


void operating_system_initialize_nano(::factory::factory * pfactory)
{


   auto edesktop = _get_edesktop();

   if(edesktop & ::user::e_desktop_kde)
   {

      operating_system_initialize_xcb_nano(pfactory);

   }
   else
   {

      operating_system_initialize_xcb_nano(pfactory);

   }


}