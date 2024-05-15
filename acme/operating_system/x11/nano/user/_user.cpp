//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "user.h"
#include "acme/operating_system/cairo/nano/user/device.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"

namespace nano
{
   namespace user
   {
      ::user::enum_desktop get_edesktop();
   }//namespace user
}// namespace nano


void operating_system_initialize_x11_nano_user(::factory::factory * pfactory)
{

   operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::x11::nano::user::window, ::nano::user::window_implementation>();

   pfactory->add_factory_item<::x11::nano::user::user, ::nano::user::user>();

   //::x11::display::_nano_0get(pfactory);

}


void operating_system_initialize_xcb_nano_user(::factory::factory * pfactory);

#if !defined(FREEBSD) && !defined(OPENBSD)


void operating_system_initialize_wayland_nano_user(::factory::factory * pfactory);

#endif

void operating_system_initialize_nano_user(::factory::factory * pfactory)
{

   auto edesktop = ::nano::user::get_edesktop();

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

      operating_system_initialize_x11_nano_user(pfactory);

   }

   auto edisplaytype = ::nano::user::get_display_type();

#ifdef HAS_WAYLAND

   //if(psystem->node()->is_wayland())
   if(edisplaytype == e_display_type_wayland)
   {

      operating_system_initialize_wayland_nano_user(pfactory);

   }
   else

#endif

   if(psystem->m_ewindowing == e_windowing_xcb)
   {

      operating_system_initialize_xcb_nano_user(pfactory);

   }
   else
   {

      operating_system_initialize_x11_nano_user(pfactory);

   }

}
