//
// Created by camilo on 31/01/2022 16:09 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/nano/user/brush.h"
#include "acme/nano/user/font.h"
#include "acme/nano/user/user.h"
#include "acme/nano/user/pen.h"
#include "device.h"
#include "window.h"


extern "C" void nano_user_macos_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::macos::nano::user::interchange, ::nano::user::window_implementation>();
   pfactory->add_factory_item<::quartz2d::nano::graphics::device, ::nano::graphics::device>();
   pfactory->add_factory_item<::nano::graphics::brush>();
   pfactory->add_factory_item<::nano::graphics::font>();
   pfactory->add_factory_item<::nano::graphics::pen>();

   pfactory->add_factory_item<::nano::user::user>();

}



