#pragma once


enum enum_align
{


   e_align_none                 = 0,
   e_align_left                 = 1,
   e_align_top                  = 2,
   e_align_bottom               = 4,
   e_align_right                = 8,
   e_align_vertical_center      = 16,
   e_align_horizontal_center    = 32,
   e_align_horizontal           = e_align_left | e_align_right | e_align_horizontal_center,
   e_align_vertical             = e_align_bottom | e_align_top | e_align_vertical_center,
   e_align_top_left             = e_align_top | e_align_left,
   e_align_top_right            = e_align_top | e_align_right,
   e_align_bottom_left          = e_align_bottom | e_align_left,
   e_align_bottom_right         = e_align_bottom | e_align_right,
   e_align_top_center           = e_align_top | e_align_horizontal_center,
   e_align_bottom_center        = e_align_bottom | e_align_horizontal_center,
   e_align_left_center          = e_align_left | e_align_vertical_center,
   e_align_right_center         = e_align_right | e_align_vertical_center,
   e_align_center               = e_align_horizontal_center | e_align_vertical_center,


};



