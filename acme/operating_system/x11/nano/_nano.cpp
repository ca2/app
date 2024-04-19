//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "nano.h"
#include "acme/operating_system/cairo/nano/device.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"


::user::enum_desktop get_edesktop();


void operating_system_initialize_x11_nano(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::x11::nano_window, ::nano_window_implementation>();

   pfactory->add_factory_item<::x11::nano, ::nano::nano>();

   ::x11::display::get(pfactory);

}


void operating_system_initialize_xcb_nano(::factory::factory * pfactory);

#if !defined(FREEBSD) && !defined(OPENBSD)


void operating_system_initialize_wayland_nano(::factory::factory * pfactory);

#endif

void operating_system_initialize_nano(::factory::factory * pfactory)
{

   auto edesktop = get_edesktop();

   auto psystem = pfactory->system();

#if !defined(FREEBSD) && !defined(OPENBSD)

   if(psystem->node()->is_wayland())
   {

      psystem->m_ewindowing = e_windowing_wayland;

   }
   else

#endif
   if(edesktop & ::user::e_desktop_kde && psystem->node()->has_xcb())
   {

      psystem->m_ewindowing = e_windowing_xcb;

   }
   else
   {

      psystem->m_ewindowing = e_windowing_x11;

      operating_system_initialize_x11_nano(pfactory);

   }

   auto edisplaytype = ::get_display_type();

#ifdef HAS_WAYLAND

   //if(psystem->node()->is_wayland())
   if(edisplaytype == e_display_type_wayland)
   {

      operating_system_initialize_wayland_nano(pfactory);

   }
   else

#endif

   if(psystem->m_ewindowing == e_windowing_xcb)
   {

      operating_system_initialize_xcb_nano(pfactory);

   }
   else
   {

      operating_system_initialize_x11_nano(pfactory);

   }

}