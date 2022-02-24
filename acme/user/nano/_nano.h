//
// Created by camilo on 31/01/2022 17:06 <3ThomasBorregaardSørensen!!
//
#pragma once


class nano_device;
class nano_window;


enum enum_nano_control
{

   e_nano_control_none,
   e_nano_control_still,
   e_nano_control_button,

};


#include "object.h"
#include "brush.h"
#include "font.h"
#include "pen.h"
#include "device.h"
#include "child.h"

#include "button.h"
#include "still.h"


#include "window_interface.h"
#include "window_implementation.h"
#include "window.h"


#include "popup_button.h"


#include "message_box.h"
#include "details_window.h"


namespace nano
{


   CLASS_DECL_ACME __pointer(nano_brush) create_solid_brush(::object * pobject, color32_t color);
   CLASS_DECL_ACME __pointer(nano_font) create_point_font(::object * pobject, int iPoint, enum_font efont, bool bBold = false);
   CLASS_DECL_ACME __pointer(nano_pen) create_pen(::object * pobject, int iWidth, color32_t color);


} // namespace nano



CLASS_DECL_ACME ::size_i32 operating_system_get_main_screen_size();

CLASS_DECL_ACME void initialize_nano();



