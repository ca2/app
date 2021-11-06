#pragma once


enum enum_image
{

   image_none,
   image_grayscale,

};


enum e_rotate_flip
{
   rotate_none_flip_none = 0,
   rotate_90_flip_none = 1,
   rotate_180_flip_none = 2,
   rotate_270_flip_none = 3,

   rotate_none_flip_x = 4,
   rotate_90_flip_x = 5,
   rotate_180_flip_x = 6,
   rotate_270_flip_x = 7,

   rotate_none_flip_y = rotate_180_flip_x,
   rotate_90_flip_y = rotate_270_flip_x,
   rotate_180_flip_y = rotate_none_flip_x,
   rotate_270_flip_y = rotate_90_flip_x,

   rotate_none_flip_xy = rotate_180_flip_none,
   rotate_90_flip_xy = rotate_270_flip_none,
   rotate_180_flip_xy = rotate_none_flip_none,
   rotate_270_flip_xy = rotate_90_flip_none
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










   enum e_smooth_mode
   {
      smooth_mode_none,
      smooth_mode_high,
      smooth_mode_anti_alias_8x4,
      smooth_mode_anti_alias_8x8,
   };


   enum e_disposal
   {
      disposal_undefined = 0,
      disposal_none = 1,
      disposal_background = 2,
      disposal_previous = 3
   };


   enum e_mipmap
   {

      mipmap_none,
      mipmap_isotropic, // 3x original size (a bit more or less if there are scan adjustments)
      mipmap_anisotropic, // 4x original size (a bit more or less if there are scan adjustments)

   };


   enum e_format
   {
      format_png,
      format_bmp,
      format_gif,
      format_jpeg,
   };



   enum enum_alpha_mode
   {
      e_alpha_mode_set,
      e_alpha_mode_blend
   };


   enum enum_fill_mode
   {
      fill_mode_winding,
      fill_mode_alternate
   };


   enum enum_unit
   {

      unit_pixel,
      unit_point,
      unit_em

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




