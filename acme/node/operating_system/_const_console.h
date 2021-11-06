//
// Created by camilo on 01/05/2021. 00:31 BRT <3TBS_!!
//


enum enum_dos_color
{

   e_dos_color_foreground_blue_component = 0x0001,
   e_dos_color_foreground_green_component = 0x0002, // text color contains green.
   e_dos_color_foreground_red_component = 0x0004, // text color contains red.
   e_dos_color_foreground_intensity = 0x0008, // text color is intensified.
   e_dos_color_background_blue_component = 0x0010, // background color contains blue.
   e_dos_color_background_green_component = 0x0020, // background color contains green.
   e_dos_color_background_red_component = 0x0040, // background color contains red.
   e_dos_color_background_intensity = 0x0080, // background color is intensified.
   e_dos_color_foreground_white = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component | e_dos_color_foreground_red_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_blue = e_dos_color_foreground_blue_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_green = e_dos_color_foreground_green_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_red = e_dos_color_foreground_red_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_cyan = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_magenta = e_dos_color_foreground_blue_component | e_dos_color_foreground_red_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_yellow = e_dos_color_foreground_red_component | e_dos_color_foreground_green_component | e_dos_color_foreground_intensity,
   e_dos_color_foreground_gray = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component | e_dos_color_foreground_red_component,
   e_dos_color_foreground_dark_blue = e_dos_color_foreground_blue_component,
   e_dos_color_foreground_dark_green = e_dos_color_foreground_green_component,
   e_dos_color_foreground_dark_red = e_dos_color_foreground_red_component,
   e_dos_color_foreground_tungsten = e_dos_color_foreground_blue_component | e_dos_color_foreground_green_component,
   e_dos_color_foreground_purple = e_dos_color_foreground_blue_component | e_dos_color_foreground_red_component,
   e_dos_color_foreground_kaki = e_dos_color_foreground_red_component | e_dos_color_foreground_green_component,
   e_dos_color_foreground_black = 0,
   e_dos_color_background_white = e_dos_color_background_blue_component | e_dos_color_background_green_component | e_dos_color_background_red_component | e_dos_color_background_intensity,
   e_dos_color_background_blue = e_dos_color_background_blue_component | e_dos_color_background_intensity,
   e_dos_color_background_green = e_dos_color_background_green_component | e_dos_color_background_intensity,
   e_dos_color_background_red = e_dos_color_background_red_component | e_dos_color_background_intensity,
   e_dos_color_background_cyan = e_dos_color_background_blue_component | e_dos_color_background_green_component | e_dos_color_background_intensity,
   e_dos_color_background_magenta = e_dos_color_background_blue_component | e_dos_color_background_red_component | e_dos_color_background_intensity,
   e_dos_color_background_yellow = e_dos_color_background_red_component | e_dos_color_background_green_component | e_dos_color_background_intensity,
   e_dos_color_background_gray = e_dos_color_background_blue_component | e_dos_color_background_green_component | e_dos_color_background_red_component,
   e_dos_color_background_dark_blue = e_dos_color_background_blue_component,
   e_dos_color_background_dark_green = e_dos_color_background_green_component,
   e_dos_color_background_dark_red = e_dos_color_background_red_component,
   e_dos_color_background_tungsten = e_dos_color_background_blue_component | e_dos_color_background_green_component,
   e_dos_color_background_purple = e_dos_color_background_blue_component | e_dos_color_background_red_component,
   e_dos_color_background_kaki = e_dos_color_background_red_component | e_dos_color_background_green_component,
   e_dos_color_background_black = 0,

};



