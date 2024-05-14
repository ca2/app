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


void operating_system_initialize_nano_user(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::macos::nano::user::window, ::nano::user::window_implementation>();
   pfactory->add_factory_item<::quartz2d::nano::user::device, ::nano::user::device>();
   pfactory->add_factory_item<::nano::user::brush>();
   pfactory->add_factory_item<::nano::user::font>();
   pfactory->add_factory_item<::nano::user::pen>();

   pfactory->add_factory_item<::nano::user::user>();

}



