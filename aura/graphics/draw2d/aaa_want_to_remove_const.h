#pragma once


enum enum_image
{

   e_image_none,
   e_image_grayscale,

};


enum enum_rotate_flip
{
   e_rotate_none_flip_none = 0,
   e_rotate_90_flip_none = 1,
   e_rotate_180_flip_none = 2,
   e_rotate_270_flip_none = 3,

   e_rotate_none_flip_x = 4,
   e_rotate_90_flip_x = 5,
   e_rotate_180_flip_x = 6,
   e_rotate_270_flip_x = 7,

   e_rotate_none_flip_y = e_rotate_180_flip_x,
   e_rotate_90_flip_y = e_rotate_270_flip_x,
   e_rotate_180_flip_y = e_rotate_none_flip_x,
   e_rotate_270_flip_y = e_rotate_90_flip_x,

   e_rotate_none_flip_xy = e_rotate_180_flip_none,
   e_rotate_90_flip_xy = e_rotate_270_flip_none,
   e_rotate_180_flip_xy = e_rotate_none_flip_none,
   e_rotate_270_flip_xy = e_rotate_90_flip_none
};

enum e_stock_icon
{

   stock_icon_none,
   stock_icon_control_box_begin,
   stock_icon_close = stock_icon_control_box_begin, // button_close
   stock_icon_level_up, // button_up
   stock_icon_level_down, // button_down
   stock_icon_iconify, // button_minimize
   stock_icon_restore, // button_restore
   stock_icon_zoom, // button_maximize
   stock_icon_notify, // button_notify_icon
   stock_icon_transparent_frame, // button_transparent_frame
   stock_icon_dock, // button_dock
   stock_icon_control_box_end = stock_icon_dock

};

enum e_color
{

   color_none,       // 0
   color_red,        // 1
   color_green,      // 2
   color_blue,       // 3
   color_yellow,     // 4
   color_cyan,       // 5
   color_magenta,    // 6
   color_black,      // 7
   color_white,      // 8 - <3tbs ∞
   color_gray,       // 9

};


namespace draw2d
{










   enum enum_smooth_mode
   {
      e_smooth_mode_none,
      e_smooth_mode_high,
      e_smooth_mode_anti_alias_8x4,
      e_smooth_mode_anti_alias_8x8,
   };


   enum enum_disposal
   {
      e_disposal_undefined = 0,
      e_disposal_none = 1,
      e_disposal_background = 2,
      e_disposal_previous = 3
   };


   enum enum_mipmap
   {

      e_mipmap_none,
      e_mipmap_isotropic, // 3x original size (a bit more or less if there are scan adjustments)
      e_mipmap_anisotropic, // 4x original size (a bit more or less if there are scan adjustments)

   };


   enum enum_format
   {
      e_format_png,
      e_format_bmp,
      e_format_gif,
      e_format_jpeg,
   };



   enum enum_alpha_mode
   {
      e_alpha_mode_set,
      e_alpha_mode_blend
   };


   enum enum_fill_mode
   {
      e_fill_mode_winding,
      e_fill_mode_alternate
   };


   enum enum_unit
   {

      e_unit_pixel,
      e_unit_point,
      e_unit_em

   };


   enum ::write_text::enum_rendering
   {

      text_rendering_hint_undefined,
      text_rendering_hint_none,
      text_rendering_hint_anti_alias,
      text_rendering_hint_anti_alias_grid_fit,
      text_rendering_hint_single_bit_per_pixel,
      text_rendering_hint_single_bit_per_pixel_grid_fit,
      text_rendering_hint_clear_type_grid_fit

   };


} // namespace draw2d




