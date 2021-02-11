#pragma once


enum enum_image_selection
{

   e_image_selection_default,
   e_image_selection_largest,
   e_image_selection_prefer_at_least_2x_larger,
   e_image_selection_prefer_larger,
   e_image_selection_prefer_smaller,
   e_image_selection_prefer_at_least_2x_smaller,
   e_image_selection_prefer_at_least_4x_smaller,
   e_image_selection_prefer_at_least_8x_smaller,

};


enum enum_font
{

   e_font_default,

   e_font_sans,
   e_font_sans_ui,
   e_font_sans_ex,
   e_font_sans_fx,

   e_font_serif,
   e_font_serif_ui,
   e_font_serif_ex,
   e_font_serif_fx,

   e_font_monospace,

};


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

enum enum_color
{

   e_color_none,       // 0
   e_color_red,        // 1
   e_color_green,      // 2
   e_color_blue,       // 3
   e_color_yellow,     // 4
   e_color_cyan,       // 5
   e_color_magenta,    // 6
   e_color_black,      // 7
   e_color_white,      // 8
   e_color_gray,       // 9

};


namespace draw2d
{


   enum enum_region
   {

      e_region_none,
      e_region_rect,
      e_region_oval,
      e_region_polygon,
      e_region_poly_polygon,
      e_region_round_rect,
      e_region_combine

   };


   enum enum_combine
   {

      e_combine_add,
      e_combine_exclude,
      e_combine_intersect,
      e_combine_xor,
      e_combine_copy,

   };


   enum e_smooth_mode
   {
      smooth_mode_none,
      smooth_mode_high,
      smooth_mode_anti_alias_8x4,
      smooth_mode_anti_alias_8x8,
   };


   enum enum_interpolation_mode
   {

      e_interpolation_mode_none = 0,
      e_interpolation_mode_nearest_neighbor,
      e_interpolation_mode_low_quality,
      e_interpolation_mode_high_quality_bicubic,

   };


   enum e_compositing_quality
   {
      compositing_quality_none,
      compositing_quality_high_speed,
      compositing_quality_high_quality,
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
      mipmap_isotropic, // 3x original size_i32 (a bit more or less if there are scan adjustments)
      mipmap_anisotropic, // 4x original size_i32 (a bit more or less if there are scan adjustments)

   };


   enum e_format
   {
      format_none,
      format_png,
      format_bmp,
      format_gif,
      format_jpeg,
   };


   enum enum_alpha_mode
   {

      alpha_mode_none,
      alpha_mode_set,
      alpha_mode_blend

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


   enum enum_pen
   {

      e_pen_null,
      e_pen_solid,
      e_pen_dot,
      e_pen_brush,
      e_pen_dash

   };


   enum enum_line_cap
   {

      e_line_cap_flat,
      e_line_cap_round,
      e_line_cap_square,

   };


   enum enum_pen_align
   {

      e_pen_align_center,
      e_pen_align_inset,

   };


   enum enum_line_join
   {

      e_line_join_miter,
      e_line_join_bevel,
      e_line_join_round,
      e_line_join_miter_clipped

   };


} // namespace draw2d


namespace write_text
{


   enum enum_rendering
   {

      e_rendering_undefined,
      e_rendering_none,
      e_rendering_anti_alias,
      e_rendering_anti_alias_grid_fit,
      e_rendering_single_bit_per_pixel,
      e_rendering_single_bit_per_pixel_grid_fit,
      e_rendering_clear_type_grid_fit

   };


} // namespace write_text



