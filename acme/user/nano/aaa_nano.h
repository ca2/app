//
// Created by camilo on 31/01/2022 17:06 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace nano
{


   class display;


} // namespace nano


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



//CLASS_DECL_ACME void operating_system_get_main_screen_size(int & cx, int & cy);

CLASS_DECL_ACME void initialize_nano();



