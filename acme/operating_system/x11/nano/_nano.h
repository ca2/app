//
// Created by camilo on 31/01/2022 19:00 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/user/nano/_nano.h"
#include "acme/operating_system.h"
#include <X11/Xlib.h>
#include "acme/operating_system/x11/_.h"


namespace x11
{


   class display;
   class window;


} // namespace x11


void operating_system_initialize_x11_nano(::factory::factory * pfactory);


#include "event_listener.h"

//#include "font.h"

#include "acme/operating_system/cairo/nano/device.h"

#include "window.h"


#include "display.h"



