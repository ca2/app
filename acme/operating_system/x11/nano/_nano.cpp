//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"
#include "acme/platform/node.h"


::user::enum_desktop _get_edesktop();


void operating_system_initialize_x11_nano(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::x11::nano_window, ::nano_window_implementation>();

   ::x11::display::get(pfactory->m_psystem);

}


void operating_system_initialize_xcb_nano(::factory::factory * pfactory);


void operating_system_initialize_nano(::factory::factory * pfactory)
{

   auto edesktop = _get_edesktop();

   auto psystem = pfactory->m_psystem;

   if(edesktop & ::user::e_desktop_kde && psystem->node()->has_xcb())
   {

      psystem->m_ewindowing = e_windowing_xcb;

   }
   else
   {

      psystem->m_ewindowing = e_windowing_x11;

      operating_system_initialize_x11_nano(pfactory);

   }

   if(psystem->m_ewindowing == e_windowing_xcb)
   {

      operating_system_initialize_xcb_nano(pfactory);

   }
   else
   {

      operating_system_initialize_x11_nano(pfactory);

   }

}