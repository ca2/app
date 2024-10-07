//
// Created by camilo on 31/01/2022 17:06 <3ThomasBorregaardSorensen!!
// 
// Created by camilo on 2024-09-26 00:32 <3ThomasBorregaardSorensen!!
// Merged from (acme)windowing on 2024-10-05 10:58 <3ThomasBorregaardSorensen!!
//
//
// (windowing_system) Created by 
//    camilo on 2024-05-26 22:45 <3ThomasBorregaardSorensen!!
// Merged from windowing_system to
//     windowing by camilo on 2024-10-05 10:35 <3ThomasBorregaardSorensen!!
//

//
#pragma once


namespace nano
{


   class display;


} // namespace nano


class ::nano::graphics::device;
class micro::interchange;


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



