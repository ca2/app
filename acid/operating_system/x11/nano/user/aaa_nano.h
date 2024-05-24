//
// Created by camilo on 31/01/2022 19:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acid/nano/user/_nano.h"
#include "acid/operating_system.h"
#include <X11/Xlib.h>
#include "acid/operating_system/x11/_.h"


namespace x11
{


   class display;
   class window;


} // namespace x11


void operating_system_initialize_x11_nano_user(::factory::factory * pfactory);


#include "event_listener.h"

//#include "font.h"

#include "acid/operating_system/cairo/nano/device.h"

#include "window.h"


#include "display.h"



