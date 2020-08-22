#pragma once


enum e_align
{
   align_none                 = 0,
   align_left                 = 1,
   align_top                  = 2,
   align_bottom               = 4,
   align_right                = 8,
   align_vertical_center      = 16,
   align_horizontal_center    = 32,
   align_horizontal           = align_left | align_right | align_horizontal_center,
   align_vertical             = align_bottom | align_top | align_vertical_center,
   align_top_left             = align_top | align_left,
   align_top_right            = align_top | align_right,
   align_bottom_left          = align_bottom | align_left,
   align_bottom_right         = align_bottom | align_right,
   align_top_center           = align_top | align_horizontal_center,
   align_bottom_center        = align_bottom | align_horizontal_center,
   align_left_center          = align_left | align_vertical_center,
   align_right_center         = align_right | align_vertical_center,
   align_center               = align_horizontal_center | align_vertical_center,
};
